#include <iostream>
#include <iomanip>

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "sphere.h"
#include "hittable.h"
#include "hittableList.h"
#include "material.h"
#include "util.h"

#include "camera.h"
#include <memory>


int main() 
{
    // world
    hittableList world;
    
    auto materialGround = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto materialCenter = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto materialLeft = std::make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto materialRight = std::make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, materialCenter));
    world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, materialRight));


    // Camera
    camera cam;
    cam.aspectRatio     = 16.0 / 9.0;
    cam.imageWidth      = 400;
    cam.samplesPerPixel = 5;
    cam.maxDepth        = 5;
    cam.render(world);

    return 0;
}