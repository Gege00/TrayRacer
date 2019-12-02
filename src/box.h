#pragma once
#include "hitable.h"

namespace primitive {

	class Box :
		public Hitable
	{

		math::vec3 pmin, pmax;
		Hitable *list;

	public:
		Box();
		Box(const math::vec3& p0, const math::vec3& p1, Material *mat);


		bool hit(const Ray& r, float t_min, float t_max, hitRecord& hit) const override;
		bool boundingBox(float t0, float t1, AABB& aabb) const override;
	};
}
