#pragma once
#include <math.h>

namespace math {

	struct vec3 {

	public:

		union
		{
			struct {
				float a[3];
			};
			struct {
				float x, y, z;
			};
		};

		vec3() { };
		vec3(float t)
		{
			x = t;
			y = t; z = t;

		}
		vec3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		
		float operator[] (int i) const { return a[i]; }
		float& operator[] (int i) { return a[i]; }
		
		inline vec3& operator+=(const vec3 &v2);
		inline vec3& operator-=(const vec3 &v2);
		inline vec3& operator*=(const vec3 &v2);
		inline vec3& operator/=(const vec3 &v2);
		inline vec3& operator*=(const float f);
		inline vec3& operator/=(const float f);



		
		inline friend vec3 operator *(const vec3& v1, const vec3& v2) {
			return vec3(v1.x*v2.x, v1.y*v2.y, v1.z*v2.z);
		}

		inline friend vec3 operator+(const vec3& v1, const vec3& v2) {
			return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
		}
		inline friend vec3 operator+(float t, const vec3& v) {
			return v + t;
		}
		
		inline friend vec3 operator*(const vec3& v, float t) {
			return vec3(v.x*t, v.y*t, v.z*t);
		}

		
		inline friend vec3 operator*( float t, const vec3& v) {
			return v * t;
		}
		
		inline friend vec3 operator/(const vec3& v, float t) {
			return vec3(v.x / t, v.y / t, v.z / t);
		}

		inline friend vec3 operator-(const vec3& v1, const vec3& v2) {
			return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
			
		}

		inline float length() const {
			return sqrt(x*x + y * y + z * z);
		}

		inline float sqr_len() const {
			return x * x + y * y + z * z;
		}

		void  make_unit_vector();


	};

	float dot(const vec3& v1, const vec3& v2);
	vec3 cross(const vec3& v1, const vec3& v2);

	vec3 unit_vec(vec3 v);

	

};