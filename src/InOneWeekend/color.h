#pragma once

#include "vec3.h"

#include <iostream>

using color = vec3;

void writeColor(const color& pixelColor) {
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    // Write out the pixel color components.
    std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
