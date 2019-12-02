#pragma once
#include "hitable.h"

namespace primitive{

class Sphere: public Hitable {

public:

	math::vec3 center;
	float radius;
	Material* materialPtr;

	
	Sphere() {};
	Sphere(math::vec3 center, float radius, Material* matPtr)
		:center(center), radius(radius), materialPtr(matPtr) {};

	virtual bool hit(const Ray& ray, float t_min, float t_max, hitRecord& hit) const;
	virtual bool boundingBox(float t0, float t1, AABB& aabb) const;

	static math::vec3 randomPointInUnitSphere();
};

}