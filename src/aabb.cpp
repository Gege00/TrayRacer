#include "aabb.h"

#include <limits>
#include "utils.h"


AABB::AABB()
{
	_vmin = math::vec3(std::numeric_limits<float>::min());
	_vmax = math::vec3(std::numeric_limits<float>::max());

}

AABB::AABB(math::vec3 min, math::vec3 max)
{
	_vmin = min;
	_vmax = max;

}



bool AABB::hit(const Ray& r, float tmin, float tmax) const
{
	for (int i = 0; i < 3; i++)
	{
		float t0 = utils::ffmin(
			_vmin[i] - r.origin[i] / r.direction[i],
			_vmax[i] - r.origin[i] / r.direction[i]);
		float t1 = utils::ffmax(
			_vmin[i] - r.origin[i] / r.direction[i],
			_vmax[i] - r.origin[i] / r.direction[i]);
		tmin = utils::ffmax(t0, tmin);
		tmax = utils::ffmin(t1, tmax);
		if(tmax<=tmin)
		{
			return false;
		}

		return true;
	}
}

