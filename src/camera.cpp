#ifndef  _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include "camera.h"
#include "math.h"
#include "utils.h"

Camera::Camera(math::vec3 position, math::vec3 lookAt, math::vec3 up, float fov, float aspect, float aperture, float focus_dist) {

	math::vec3 u, v, w;

	float angle = fov * M_PI / 180;
	float height = tan(angle/2);
	float width = aspect * (height);
	
	lensRadius = aperture / 2;
	
	origin = position;
	w = math::unit_vec(position - lookAt);
	u = math::unit_vec(math::cross(up,w));
	v = math::cross(w, u);
	
	lowerLeft = origin - width * u*focus_dist - height *focus_dist*v - w*focus_dist;
	horizontal = 2 * width*u *focus_dist;
	vertical = 2 * height*v * focus_dist;
};

Ray Camera::getRay(float u, float v) {

	math::vec3 rd = lensRadius * utils::randomUnitDisk();
	auto offset = u * rd.x + v * rd.y;
	
	return Ray(origin+offset, lowerLeft + vertical * v + horizontal * u - origin-offset);
}
