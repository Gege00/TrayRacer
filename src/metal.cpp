#include "metal.h"
#include "sphere.h"


bool Metal::scatter(const Ray& rayIn, const hitRecord& hit, math::vec3& attenuation, Ray& scattered, float& pdf) const {

	scattered = Ray(hit.p, reflect(math::unit_vec(rayIn.direction()), hit.normal) + fuzz* primitive::Sphere::randomPointInUnitSphere());
	attenuation = albedo;
	auto dotP = math::dot(scattered.direction(), hit.normal);
	return  dotP> 0;
}




