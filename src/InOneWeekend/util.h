#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

const double pi = 3.1415926535897932385;


inline double randomDouble()
{
	// return [0, 1)
	return std::rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max)
{
	// return [min, max)
	return min + (max - min) * randomDouble();
}

inline double degreesToRadians(double degrees) {
	return degrees * pi / 180.0;
}