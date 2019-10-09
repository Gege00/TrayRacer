#pragma once

#include "material.h"


class Diffuse : public Material {


public:

	math::vec3 albedo; 
	
	Diffuse(const math::vec3& albedo)
		:albedo(albedo)	{};
	
	virtual bool scatter(const Ray& rayIn, const hitRecord& hRec, math::vec3& attenuation, Ray& scattered) const;
};