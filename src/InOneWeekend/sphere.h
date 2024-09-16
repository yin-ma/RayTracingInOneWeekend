#pragma once

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
public:
    sphere(const point3& center, double radius, std::shared_ptr<material> mat)
        : center(center), radius(std::fmax(0, radius)), mat(mat)
    {
        // TODO: init mat
    }

    bool hit(const ray& r, double rayMin, double rayMax, hitRecord& rec) const override
    {
        vec3 oc = center - r.origin();
        double a = dot(r.direction(), r.direction());
        double h = dot(r.direction(), oc);
        double c = dot(oc, oc) - radius * radius;
        double discriminant = h * h - a * c;

        if (discriminant < 0)
        {
            return false;
        }

        double sqrtd = std::sqrt(discriminant);

        double root = (h - sqrtd) / a;
        if (root <= rayMin || root >= rayMax)
        {
            root = (h + sqrtd) / a;
            if (root <= rayMin || rayMax <= root) return false;
        }

        rec.p = r.at(root);
        rec.t = root;
        rec.mat = mat;
        vec3 outwardNormal = (rec.p - center) / radius;
        rec.setFaceNormal(r, outwardNormal);

        return true;
    }

private:
    point3 center;
    double radius;
    std::shared_ptr<material> mat;
};