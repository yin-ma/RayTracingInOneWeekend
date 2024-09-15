#include <iostream>
#include "vec3.h"

int main() {

    int imageWidth = 256;
    int imageHeight = 256;

    vec3 v = vec3(1.0, 2.0, 3.0);
    std::cout << v.x() << " " << v.y() << " " << v.z() << " " << std::endl;

    // Render
    //std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
    //for (int j = 0; j < imageHeight; j++) {
    //    std::clog << "\rScanlines remaining: " << j / imageHeight * 100 << '% ' << std::flush;
    //    for (int i = 0; i < imageWidth; i++) {
    //        auto r = double(i) / (imageWidth - 1);
    //        auto g = double(j) / (imageHeight - 1);
    //        auto b = 0.0;

    //        int ir = int(255.999 * r);
    //        int ig = int(255.999 * g);
    //        int ib = int(255.999 * b);

    //        std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    //    }
    //}

    std::clog << "\rDone.                 \n";
}