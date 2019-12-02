#include "onb.h"


void ONB::build(const math::vec3& n) {
	w = math::unit_vec(n);
	v = math::vec3(math::cross( w, (fabsf(w.x) > 0.9) ? math::vec3(0, 1, 0) : math::vec3(1, 0, 0)));
	u = math::cross(w,v);
	
}
