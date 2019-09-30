#pragma once


#include "ray.h"

class Camera
{
public:
	math::vec3 origin;
	math::vec3 lowerLeft;
	math::vec3 horizontal;
	math::vec3 vertical;
	
	
	Camera();

	Ray getRay(float u, float v);
	
};

