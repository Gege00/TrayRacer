#include "diffuselight.h"


bool DiffuseLight::scatter(const Ray& rayIn, const hitRecord& hit, math::vec3& attenuation, Ray& scattered, float& pdf) const {
	return false;
}



float DiffuseLight::scatteringPdf(const Ray& rayIn, const hitRecord& hit, Ray& scattered) const {
	return 0;
}

math::vec3 DiffuseLight::emitted(float u, float v, const math::vec3& p) const {

	return _emitTexture->value(u, v, p);
}
