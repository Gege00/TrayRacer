#pragma once

#include "ray.h"

class Material;

struct hitRecord {

	float t;
	math::vec3 p;
	math::vec3 normal;
	Material *matPtr;
};


class Hitable {

public:
	virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& hit) const = 0;
};