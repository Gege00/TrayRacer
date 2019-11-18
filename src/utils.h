#pragma once


#include <functional>
#include <random>

namespace utils {


	inline double randDouble() {
		static std::default_random_engine e{};
		static std::mt19937 gen(e);
		static std::uniform_real_distribution<double> d{ 0,1 };
		return d(e);
	}

	inline math::vec3 randomUnitDisk() {

		math::vec3 point(0);
		while(math::dot(point,point)>=1) {
			point = math::vec3(randDouble(), randDouble(), 0.0f)*2 -math::vec3(1,1,0);
		}
		return point;
		
	}

}