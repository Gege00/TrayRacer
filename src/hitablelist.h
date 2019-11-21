#pragma once

#include "hitable.h"

class Hitablelist : public Hitable {

public:
	Hitable **list;
	int listSize;


	Hitablelist() {};
	Hitablelist(Hitable **l, int n)
		:list(l), listSize(n) {};
	
	virtual bool hit(const Ray& ray, float t_min, float t_max, hitRecord& rec) const;
	virtual	bool boundingBox(float t0, float t1, AABB& aabb) const;
};