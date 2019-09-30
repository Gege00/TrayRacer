#pragma once
#include "hitable.h"

class Sphere: public Hitable {

public:

	math::vec3 center;
	float radius;
	
	Sphere() {};
	Sphere(math::vec3 center, float radius)
		:center(center), radius(radius) {};

	virtual bool hit(const Ray& ray, float t_min, float t_max, hitRecord& hit) const;

	
};

