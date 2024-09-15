#include <iostream>
#include <iomanip>

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "sphere.h"
#include "hittable.h"
#include "hittableList.h"

#include "camera.h"
#include <memory>


int main() 
{
    // world
    hittableList world;
    
    world.add(std::make_shared<sphere>(vec3(0, 0, -1), 0.5));
    world.add(std::make_shared<sphere>(vec3(0, -100.5, -1), 100));

    // Camera
    camera cam;
    cam.render(world);

    return 0;
}