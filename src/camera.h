#pragma once


#include "ray.h"

class Camera
{
public:
	math::vec3 origin;
	math::vec3 lowerLeft;
	math::vec3 horizontal;
	math::vec3 vertical;
	float lensRadius;
	math::vec3  u, v, w;
	
	Camera(math::vec3 position,math::vec3 lookAt,math::vec3 up,float fov, float aspect, float aperture,float focus_dist);

	Ray getRay(float u, float v);
	
};

