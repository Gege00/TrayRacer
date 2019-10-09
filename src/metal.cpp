#include "metal.h"
#include "sphere.h"


bool Metal::scatter(const Ray& rayIn, const hitRecord& hRec, math::vec3& attenuation, Ray& scattered) const {

	scattered = Ray(hRec.p, reflect(math::unit_vec(rayIn.direction()), hRec.normal) + fuzz*Sphere::randomPointInUnitSphere());
	attenuation = albedo;
	auto dotP = math::dot(scattered.direction(), hRec.normal);
	return  dotP> 0;
}



math::vec3 Metal::reflect(const math::vec3& v, const math::vec3& n) const {
	return v - 2 * math::dot(v, n)*n;
}
