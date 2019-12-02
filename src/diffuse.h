#pragma once

#include "material.h"
#include "texture.h"


class Diffuse : public Material {


public:

	Texture* albedo; 
	
	Diffuse(Texture* texture)
		:albedo(texture)	{};
	
	bool scatter(const Ray& rayIn, const hitRecord& hRec, math::vec3& attenuation, Ray& scattered,float& pdf) const override;
	float scatteringPdf(const Ray& rayIn, const hitRecord& hit,const Ray& scattered) const override;
};
