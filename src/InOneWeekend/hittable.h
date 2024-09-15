#pragma once

#include "ray.h"

class hitRecord 
{
public:
    point3 p;
    vec3 normal;
    double t = 500.0;
    bool frontFace;

    void setFaceNormal(const ray& r, const vec3& outwardNormal)
    {
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class hittable
{
public:
	virtual ~hittable() = default;

	virtual bool hit(const ray& r, double rayMin, double rayMax, hitRecord& rec) const = 0;
};