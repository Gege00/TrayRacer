#include "diffuselight.h"


bool DiffuseLight::scatter(const Ray& rayIn, const hitRecord& hRec, math::vec3& attenuation, Ray& scattered) const {
	return false;
}

math::vec3 DiffuseLight::emitted(float u, float v, const math::vec3& p) const {

	return _emitTexture->value(u, v, p);
}
