#ifndef  _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include "diffuse.h"
#include "sphere.h"
#include "onb.h"
#include "utils.h"


bool Diffuse::scatter(const Ray& rayIn, const hitRecord& hRec, math::vec3& attenuation, Ray& scattered, float& pdf) const {
	//math::vec3 direction;
	//do {
	//	direction = primitive::Sphere::randomPointInUnitSphere();
	//} while (math::dot(direction, hRec.normal) < 0);
	//
	//scattered = Ray(hRec.p, math::unit_vec(direction));
	//attenuation = albedo->value(hRec.u, hRec.v, hRec.p);
	//pdf = 0.5 / M_PI;
	//return true;


	ONB onb;
	onb.build(hRec.normal);
	math::vec3 direction = onb.local(utils::randomCosineDir());
	scattered = Ray(hRec.p, math::unit_vec(direction));
	attenuation = albedo->value(hRec.u, hRec.v, hRec.p);
	pdf = math::dot(onb.getW(), scattered.direction()) / M_PI;
	return true;
}

float Diffuse::scatteringPdf(const Ray& rayIn, const hitRecord& hit,const Ray& scattered) const {

	float cos = math::dot(hit.normal, math::unit_vec(scattered.direction()));
	if (cos < 0) return  0;
	return cos / M_PI;

}
		
