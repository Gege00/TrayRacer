#pragma once
#include "material.h"


class Metal: public Material {

public:

	math::vec3 albedo;
	float fuzz;
	
	Metal(const math::vec3& albedo, float fuzz)
		:albedo(albedo) {
		this->fuzz = fuzz > 1.0f ? 1.0f : fuzz;
	};

	virtual bool scatter(const Ray& rayIn, const hitRecord& hRec, math::vec3& attenuation, Ray& scattered) const;
	 
	
	
};