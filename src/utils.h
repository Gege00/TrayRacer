#pragma once

#include <random>
#include <corecrt_math_defines.h>

namespace utils {


	inline double randDouble() {
		static std::default_random_engine e{};
		static std::mt19937 gen(e);
		static std::uniform_real_distribution<double> d{ 0,1 };
		return d(e);
	}

	inline math::vec3 randomUnitDisk() {

		math::vec3 point(0.0f,0.0f,0.0f);
		while (math::dot(point, point) >= 1) {
			point = math::vec3(randDouble(), randDouble(), 0.0f) * 2 - math::vec3(1, 1, 0);
		}
		return point;

	}


	inline math::vec3 randomCosineDir() {
		float r1 = randDouble();
		float r2 = randDouble();
		float z = sqrt(1 - r2);
		float phi = 2 * M_PI*r1;
		float x = cos(phi)*sqrt(r2);
		float y = sin(phi)*sqrt(r2);
		return math::vec3(x, y, z);
	}
	

	inline float ffmin(float a, float b) { return a < b ? a : b; }
	inline float ffmax(float a, float b) { return a > b ? a : b; }

}
