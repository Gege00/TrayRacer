#include "hitablelist.h"

bool Hitablelist::hit(const Ray & ray, float t_min, float t_max, hitRecord& rec) const
{
	hitRecord tRec;
	bool isHit = false;
	double closest = t_max;
	for (int i = 0; i < listSize; i++)
	{
		if(list[i]->hit(ray,t_min,closest,tRec)) {
			isHit = true;
			closest = tRec.t;
			rec = tRec;
		}
	}

	return isHit;
	
}


bool Hitablelist::boundingBox(float t0, float t1, AABB& aabb) const {
	if (listSize < 1) return false;
	AABB temp;
	bool isHit = list[0]->boundingBox(t0, t1, temp);
	if (!isHit) return false;
	aabb=temp;
	for (int i=1; i<listSize; i++) {

		if (list[i]->boundingBox(t0, t1, temp))
			aabb = AABB::overlap(aabb, temp);
		else return false;
		
	}
	return true;
}
