#include "sphere.h"

bool Sphere::hit(const Ray & ray, float t_min, float t_max, hitRecord & hit) const
{
	math::vec3 oc = ray.origin() - center;
	float a = math::dot(ray.direction(), ray.direction());
	float b = 2.0f * math::dot(ray.direction(), oc);
	float c = math::dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;
	if (discriminant > 0) {
		float t = (-b - sqrt(b*b - a * c)) / a;
		if (t< t_max && t> t_min) {
			hit.t = t;
			hit.p = ray.point_at_parameter(t);
			hit.normal = (hit.p - center) / radius;
			return true;
		}
		t = (-b + sqrt(b*b - a * c)) / a;
		if (t<t_max && t> t_min) {
			hit.t = t;
			hit.p = ray.point_at_parameter(t);
			hit.normal = (hit.p - center) / radius;
			return true;
		}
	}
	return false;

}
