#include <iostream>
#include <iomanip>

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "sphere.h"
#include "hittable.h"
#include "hittableList.h"
#include <memory>


color rayColor(const ray& r, const hittable& world)
{
    hitRecord rec;
    if (world.hit(r, 0, 100000.0, rec))
    {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    vec3 unitDirection = normalize(r.direction());
    double a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() 
{
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    int imageHeight = int(400 / aspectRatio);

    // world
    hittableList world;
    
    world.add(std::make_shared<sphere>(vec3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(vec3(0, -100.5, -1), 100));

    // Camera
    double focalLength = 1.0;
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    
    vec3 cameraCenter = point3(0, 0, 0);
    vec3 viewport_u = vec3(viewportWidth, 0, 0);
    vec3 viewport_v = vec3(0, -viewportHeight, 0);

    vec3 pixelDelta_u = viewport_u / imageWidth;
    vec3 pixelDelta_v = viewport_v / imageHeight;

    vec3 viewportUpperLeft = cameraCenter - vec3(0, 0, focalLength) - viewport_u / 2 - viewport_v / 2;
    vec3 pixel00Loc = viewportUpperLeft + 0.5 * (pixelDelta_u + pixelDelta_v);

    sphere s = sphere(vec3(0, 0, -1), 0.5);
    hitRecord rec;

    // Render
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    for (int j = 0; j < imageHeight; j++) 
    {
        std::clog << "\rProgress: " << std::fixed << std::setprecision(2) << (static_cast<double>(j) / imageHeight) * 100 << "% " << std::flush;
        for (int i = 0; i < imageWidth; i++) 
        {
            vec3 pixelCenter = pixel00Loc + (i * pixelDelta_u) + (j * pixelDelta_v);
            vec3 rayDirection = pixelCenter - cameraCenter;
            ray r(cameraCenter, rayDirection);

            color pixelColor = rayColor(r, world);

            writeColor(pixelColor);
        }
    }

    std::clog << "\rDone.               \n";

    return 0;
}