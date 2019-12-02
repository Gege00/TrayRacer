#pragma once
#include "vec3.h"


class ONB {


	union {
		struct {
			math::vec3 axis[3];
		};

		struct {
			math::vec3 u, v, w;
		};
	};

public:
	ONB() {};

	inline math::vec3 operator[](int i)const { return axis[i]; }
	math::vec3 getU() const { return u; }
	math::vec3 getV() const { return v; }
	math::vec3 getW() const { return w; }

	math::vec3 local(float a, float b, float c) const { return a * u + a * v + a * w; }
	math::vec3 local(const math::vec3& a) const { return a.x * u + a.y * v + a.z * w; }
	
	void build(const math::vec3& n);
	
};
