#pragma once
#include "vec3.h"
#include "ray.h"



class AABB
{
	math::vec3 _vmin;
	math::vec3  _vmax;

public:
	AABB();
	AABB(math::vec3 min, math::vec3 max);

	math::vec3 max() const
	{
		return _vmax;
	}
	const math::vec3 min() const
	{
		return _vmin;
	}


	bool hit(const Ray &r, float tmin, float tmax) const;
	
};

