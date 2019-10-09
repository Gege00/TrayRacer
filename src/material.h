#pragma once
#include "hitable.h"



class Material
{
public:

  	 	virtual bool scatter(const Ray& rayIn, const hitRecord& hRec, math::vec3& attenuation, Ray& scattered) const = 0;

	
};

