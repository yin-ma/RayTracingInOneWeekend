#pragma once

#include "hittable.h"
#include "color.h"
#include <iostream>
#include <iomanip>

class camera
{
public:
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    int imageHeight = 225;

	void render(const hittable& world) 
    {
        initialize();

        std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
        for (int j = 0; j < imageHeight; j++)
        {
            std::clog << "\rProgress: " << std::fixed << std::setprecision(2) << (static_cast<double>(j) / imageHeight) * 100 << "% " << std::flush;
            for (int i = 0; i < imageWidth; i++)
            {
                vec3 pixelCenter = pixel00Loc + (i * pixelDelta_u) + (j * pixelDelta_v);
                vec3 rayDirection = pixelCenter - center;
                ray r(center, rayDirection);

                color pixelColor = rayColor(r, world);
                writeColor(pixelColor);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:  
    point3 center;        
    point3 pixel00Loc;    
    vec3   pixelDelta_u;  
    vec3   pixelDelta_v;

	void initialize() 
    {
        imageHeight = int(400 / aspectRatio);

        double focalLength = 1.0;
        double viewportHeight = 2.0;
        double viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

        center = point3(0, 0, 0);
        vec3 viewport_u = vec3(viewportWidth, 0, 0);
        vec3 viewport_v = vec3(0, -viewportHeight, 0);

        pixelDelta_u = viewport_u / imageWidth;
        pixelDelta_v = viewport_v / imageHeight;

        vec3 viewportUpperLeft = center - vec3(0, 0, focalLength) - viewport_u / 2 - viewport_v / 2;
        pixel00Loc = viewportUpperLeft + 0.5 * (pixelDelta_u + pixelDelta_v);
    }

	color rayColor(const ray& r, const hittable& world) const 
	{
        hitRecord rec;

        if (world.hit(r, 0, 500.0, rec))
        {
            return 0.5 * (rec.normal + color(1, 1, 1));
        }

        vec3 unitDirection = normalize(r.direction());
        double a = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);

	}
};