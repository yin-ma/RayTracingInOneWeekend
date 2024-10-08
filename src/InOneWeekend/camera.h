#pragma once

#include "hittable.h"
#include "color.h"
#include "material.h"
#include <iostream>
#include <iomanip>

class camera
{
public:
    double aspectRatio  = 16.0 / 9.0;
    int imageWidth      = 400;
    int imageHeight     = 225;
    int samplesPerPixel = 10;
    int maxDepth        = 10;

    double vfov   = 90;
    vec3 lookfrom = vec3(0, 0, 0);
    vec3 lookat   = vec3(0, 0, -1);
    vec3 up       = vec3(0, 1, 0);

    double defocusAngle = 0;
    double focusDist = 10;

	void render(const hittable& world) 
    {
        initialize();

        std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
        for (int j = 0; j < imageHeight; j++)
        {
            std::clog << "\rProgress: " << std::fixed << std::setprecision(2) << (static_cast<double>(j) / imageHeight) * 100 << "% " << std::flush;
            for (int i = 0; i < imageWidth; i++)
            {
                color pixelColor = color(0, 0, 0);
                for (int sample = 0; sample < samplesPerPixel; sample++)
                {
                    ray r = getRay(i, j);
                    pixelColor += rayColor(r, maxDepth, world);
                }

                writeColor(pixelColor * 1.0 / samplesPerPixel);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:  
    point3 center;        
    point3 pixel00Loc;    
    vec3   pixelDelta_u;  
    vec3   pixelDelta_v;
    vec3   u, v, w;
    vec3   defocusDisk_u;
    vec3   defocusDisk_v;

	void initialize() 
    {
        imageHeight = int(imageWidth / aspectRatio);

        center = lookfrom;

        double theta = degreesToRadians(vfov);
        double h = std::tan(theta / 2);

        double viewportHeight = 2 * h * focusDist;
        double viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);

        w = normalize(lookfrom - lookat);
        u = normalize(cross(up, w));
        v = cross(w, u);

        vec3 viewport_u = viewportWidth * u;
        vec3 viewport_v = viewportHeight * -v;

        pixelDelta_u = viewport_u / imageWidth;
        pixelDelta_v = viewport_v / imageHeight;

        vec3 viewportUpperLeft = center - (focusDist * w) - viewport_u / 2 - viewport_v / 2;
        pixel00Loc = viewportUpperLeft + 0.5 * (pixelDelta_u + pixelDelta_v);

        double defocusRadius = focusDist * std::tan(degreesToRadians(defocusAngle / 2));
        defocusDisk_u = u * defocusRadius;
        defocusDisk_v = v * defocusRadius;
    }

	color rayColor(const ray& r, int depth, const hittable& world) const 
	{
        if (depth <= 0)
            return color(0, 0, 0);

        hitRecord rec;

        if (world.hit(r, 0.001, 500.0, rec))
        {
            ray scattered;
            color attenuation;
            if (rec.mat->scatter(r, rec, attenuation, scattered))
                return attenuation * rayColor(scattered, depth - 1, world);
            return color(0, 0, 0);
        }

        vec3 unitDirection = normalize(r.direction());
        double a = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
	}

    ray getRay(int i, int j) const
    {
        vec3 offset = vec3(randomDouble() - 0.5, randomDouble() - 0.5, 0.0);

        vec3 pixelSample = pixel00Loc + ((i + offset.x()) * pixelDelta_u) + ((j + offset.y()) * pixelDelta_v);
        vec3 rayOrigin = (defocusAngle <= 0) ? center : defocusDiskSample() ;
        vec3 rayDirection = pixelSample - rayOrigin;

        return ray(rayOrigin, rayDirection);
    }

    vec3 defocusDiskSample() const
    {
        vec3 p = randomInUnitDisk();
        return center + (p[0] * defocusDisk_u) + (p[1] * defocusDisk_v);
    }
};