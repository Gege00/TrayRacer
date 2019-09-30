#pragma once
#include "vec3.h"

class Ray {
public:

	math::vec3 a;
	math::vec3 b;

	Ray(){};
	Ray(const math::vec3& a, const math::vec3& b)
		: a(a), b(b) {};


	inline math::vec3 origin() const { return a; }
	inline math::vec3 direction() const { return b; }


	math::vec3 point_at_parameter(float t) const { return a + b*t; }


	
}; 