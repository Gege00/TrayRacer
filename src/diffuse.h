#pragma once

#include "material.h"
#include "texture.h"


class Diffuse : public Material {


public:

	Texture* albedo; 
	
	Diffuse(Texture* texture)
		:albedo(texture)	{};
	
	virtual bool scatter(const Ray& rayIn, const hitRecord& hRec, math::vec3& attenuation, Ray& scattered) const;
};
