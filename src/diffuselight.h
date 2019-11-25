#pragma once
#include "material.h"
#include "texture.h"

class DiffuseLight : public Material
{

	Texture* _emitTexture;

	
public:
	DiffuseLight(Texture* a) : _emitTexture(a) {};
	~DiffuseLight();


	virtual bool scatter(const Ray& rayIn, const hitRecord& hRec, math::vec3& attenuation, Ray& scattered) const;
	virtual math::vec3 emitted(float u, float v, const math::vec3& p) const;
};

