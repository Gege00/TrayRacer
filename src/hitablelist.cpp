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
