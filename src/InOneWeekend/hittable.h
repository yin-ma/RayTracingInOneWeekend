#pragma once

#include "ray.h"

class material;

class hitRecord 
{
public:
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat;
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