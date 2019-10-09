#include "sphere.h"
#include <random>

bool Sphere::hit(const Ray & ray, float t_min, float t_max, hitRecord & hit) const
{
	math::vec3 oc = ray.origin() - center;
	float a = math::dot(ray.direction(), ray.direction());
	float b = math::dot(ray.direction(), oc);
	float c = math::dot(oc, oc) - radius * radius;
	float discriminant = b * b - a*c;
	if (discriminant > 0) {
		float t = (-b - sqrt(b*b - a * c)) / a;
		if (t< t_max && t> t_min) {
			hit.t = t;
			hit.p = ray.point_at_parameter(t);
			hit.normal = (hit.p - center) / radius;
			hit.matPtr = materialPtr;
			return true;
		}
		t = (-b + sqrt(b*b - a * c)) / a;
		if (t<t_max && t> t_min) {
			hit.t = t;
			hit.p = ray.point_at_parameter(t);
			hit.normal = (hit.p - center) / radius;
			hit.matPtr = materialPtr;
			return true;
		}
	}
	return false;

}


math::vec3 Sphere::randomPointInUnitSphere() {
	{
		math::vec3 p;
		do {
			p = 2.0*math::vec3((rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0))) - math::vec3(1);
		} while (p.sqr_len() >= 1.0);

		return p;

	}
		
}
