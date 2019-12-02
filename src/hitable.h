#pragma once

#include "ray.h"
#include "aabb.h"

class Material;

struct hitRecord {

	float t;
	float u;
	float v;
	math::vec3 p;
	math::vec3 normal;
	Material *matPtr;
};


class Hitable {

public:
	virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& hitRecord) const = 0;
	virtual bool boundingBox(float t0, float t1, AABB& aabb) const = 0;


	
};

