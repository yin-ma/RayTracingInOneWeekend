#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

class hittableList : public hittable
{
public:
	std::vector<std::shared_ptr<hittable>> objects;

	hittableList() {}
	
	hittableList(std::shared_ptr<hittable> object)
	{
		add(object);
	}

	void clear()
	{
		objects.clear();
	}

	void add(std::shared_ptr<hittable> object)
	{
		objects.push_back(object);
	}

	bool hit(const ray& r, double rayMin, double rayMax, hitRecord& rec) const override
	{
		hitRecord temp;
		bool hitAnything = false;
		double closestSoFar = rayMax;

		for (const auto& object : objects)
		{
			if (object->hit(r, rayMin, rayMax, temp))
			{
				hitAnything = true;
				if (closestSoFar > temp.t)
				{
					closestSoFar = temp.t;
					rec = temp;
				}

			}
		}

		return hitAnything;

	}

};