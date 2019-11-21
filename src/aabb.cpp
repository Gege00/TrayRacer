#include "aabb.h"

#include <limits>
#include "utils.h"
#include "hitable.h"


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
			_vmin[i] - r.origin()[i]   / r.direction()[i],
			_vmax[i] - r.origin()[i] / r.direction()[i]);
		float t1 = utils::ffmax(
			_vmin[i] - r.origin()[i] / r.direction()[i],
			_vmax[i] - r.origin()[i] / r.direction()[i]);
		tmin = utils::ffmax(t0, tmin);
		tmax = utils::ffmin(t1, tmax);
		if(tmax<=tmin)
		{
			return false;
		}

		return true;
	}
}

AABB AABB::overlap(AABB& b0, AABB& b1) {
	math::vec3 min(
		utils::ffmin(b0.min().x, b1.min().x),
		utils::ffmin(b0.min().y,b1.min().y),
		utils::ffmin(b0.min().z,b1.min().z));

	math::vec3 max(
		utils::ffmax(b0.max().x, b1.max().x),
		utils::ffmax(b0.max().y, b1.max().y),
		utils::ffmax(b0.max().z, b1.max().z));
	return AABB(min, max);
}
