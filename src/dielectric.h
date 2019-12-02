#pragma once
#include "material.h"


class Dielectric: public Material {


	float ref_idx;

public:

	Dielectric(float ri): ref_idx(ri){}

	
	
	bool scatter(const Ray& rayIn, const hitRecord& hit, math::vec3& attenuation, Ray& scattered, float& pdf) const override;

	bool refract(const math::vec3& v, const math::vec3& n, float niNt, math::vec3& refracted) const;
};
