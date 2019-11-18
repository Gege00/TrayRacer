#include "vec3.h"



namespace math {



	void vec3::make_unit_vector() {
		float k = 1.0f / length();
		x *= k;
		y *= k;
		z *= k;

	}

	vec3& vec3::operator+=(const vec3 &v2) {

		x += v2.x;
		y += v2.y;
		z += v2.z;
		return *this;
	}


	vec3& vec3::operator-=(const vec3 &v2) {

		x -= v2.x;
		y -= v2.y;
		z -= v2.z;
		return *this;
	}

	vec3& vec3::operator*=(const vec3 &v2) {

		x *= v2.x;
		y *= v2.y;
		z *= v2.z;
		return *this;
	}
	vec3& vec3::operator/=(const vec3 &v2) {

		x /= v2.x;
		y /= v2.y;
		z /= v2.z;
		return *this;
	}


	vec3& vec3::operator*=(const float t) {

		x *= t;
		y *= t;
		z *= t;
		return *this;
	}

	vec3& vec3::operator/=(const float t) {

		x /= t;
		y /= t;
		z /= t;
		return *this;
	}

	vec3 unit_vec(vec3 v) {
		return v / v.length();
	}

	float dot(const vec3& v1, const vec3& v2) {
		return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
	}

	vec3 cross(const vec3& v1, const vec3& v2) {
		return vec3(
			v1.y* v2.z - v1.z*v2.y,
			v1.z*v2.x - v1.x*v2.z,
			v1.x*v2.y - v1.y*v2.x);
	}



}