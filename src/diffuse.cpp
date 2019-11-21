#include "diffuse.h"
#include "sphere.h"


bool Diffuse::scatter(const Ray& rayIn, const hitRecord& hRec, math::vec3& attenuation, Ray& scattered) const {
	math::vec3 target = hRec.p + hRec.normal + Sphere::randomPointInUnitSphere();
	scattered = Ray(hRec.p, target - hRec.p);
	attenuation = albedo->value(0,0,hRec.p);
	return true;
}
