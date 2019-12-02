#include "dielectric.h"
#include "utils.h"


bool Dielectric::scatter(const Ray& rayIn, const hitRecord& hit, math::vec3& attenuation, Ray& scattered, float& pdf) const {

	math::vec3 reflected = reflect(rayIn.direction(), hit.normal);

	float niNt;
	math::vec3 outNorm;
	math::vec3 refracted;
	attenuation = math::vec3(1.0f	, 1.0f, 1.0f);

	float reflectProb;
	float cosine;
	
	if(math::dot(rayIn.direction(),hit.normal)>0) {
		outNorm =  hit.normal *-1;
		niNt = ref_idx;
		cosine = ref_idx * math::dot(rayIn.direction(), hit.normal) / rayIn.direction().length();
	}

	else {
		outNorm = hit.normal;
		niNt = 1.0 / ref_idx;
		cosine = -math::dot(rayIn.direction(), hit.normal) / rayIn.direction().length();

	}
	if (refract(rayIn.direction(), outNorm, niNt, refracted)) {
		reflectProb = schlick(cosine, ref_idx);
	}else{
		reflectProb = 1.0f;
	}
	if(utils::randDouble()<reflectProb) {
		scattered = Ray(hit.p, reflected);
	}
	else {
		scattered = Ray(hit.p, refracted);
	}
	
	return true;

	
}

bool Dielectric::refract(const math::vec3& v, const math::vec3& n, float niNt, math::vec3& refracted) const {
	math::vec3 unitVec = unit_vec(v);
	float dt = math::dot(unitVec, n);
	float disc = 1.0 - niNt * niNt*(1 - dt * dt);
	if(disc>0) {
		refracted = niNt * (unitVec - n * dt) - n * sqrt(disc);
		return true;
	}

	return false;
}
