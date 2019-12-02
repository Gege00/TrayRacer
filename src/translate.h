#pragma once
#include "hitable.h"


class Translate: public Hitable {

public:

	Hitable *target;
	math::vec3 offset;

	
	Translate(Hitable *t, const math::vec3& displacement)
		: target(t), offset(displacement) {}


	bool hit(const Ray& r, float t_min, float t_max, hitRecord& hit) const override;
	bool boundingBox(float t0, float t1, AABB& aabb) const override;
};


class RotateY: public Hitable {

	Hitable *target;
	float sinTheta;
	float cosTheta;
	bool hasbox;
	AABB bb;

public:


	explicit RotateY(Hitable* target, float angle);

	bool hit(const Ray& r, float t_min, float t_max, hitRecord& hit) const override;
	bool boundingBox(float t0, float t1, AABB& aabb) const override;
};
