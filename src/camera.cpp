#include "camera.h"


Camera::Camera() {
	
	origin = math::vec3(0);
	lowerLeft = math::vec3(-2.0, -1.0, -1.0);
	horizontal = math::vec3(4.0, 0.0, 0.0);
	vertical = math::vec3(0.0, 2.0f, 0.0f);
};

Ray Camera::getRay(float u, float v) {
	return Ray(origin, lowerLeft + vertical * v + horizontal * u - origin);
}
