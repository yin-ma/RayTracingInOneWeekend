#pragma once

#include "hittable.h"
#include "color.h"

class material
{
public:
	virtual ~material() = default;

	virtual bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const
	{
		return false;
	}
};

class lambertian : public material
{
public:
	lambertian(const color& albedo) : albedo(albedo) {}

	bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override
	{
		vec3 scatterDirection = rec.normal + randomUnitVector();

		if (scatterDirection.nearZero())
			scatterDirection = rec.normal;

		scattered = ray(rec.p, scatterDirection);
		attenuation = albedo;
		return true;
	}

private:
	color albedo;
};


class metal : public material
{
public:
	metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

	bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override
	{
		vec3 reflected = reflect(rIn.direction(), rec.normal);
		reflected = normalize(reflected) + (fuzz * randomUnitVector());
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

private:
	color albedo;
	float fuzz;
};