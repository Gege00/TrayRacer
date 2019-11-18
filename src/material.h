#pragma once
#include "hitable.h"



class Material
{
public:

  	 	virtual bool scatter(const Ray& rayIn, const hitRecord& hRec, math::vec3& attenuation, Ray& scattered) const = 0;

		math::vec3 reflect(const math::vec3& v, const math::vec3& n) const {
			return v - 2 * math::dot(v, n)*n;
		}

		float schlick(float cos,float ref_idx) const {
			float r0 = (1 - ref_idx) / (1 + ref_idx);
			r0 = r0 * r0;
			return r0 + (1 - r0)*pow((1 - cos), 5);
		}
	
};

