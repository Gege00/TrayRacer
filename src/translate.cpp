#ifndef  _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include "translate.h"
#include <cfloat>


bool Translate::hit(const Ray& r, float t_min, float t_max, hitRecord& hit) const {
	Ray translated(r.origin() - offset, r.direction());
	if(target->hit(translated,t_min,t_max,hit) ) {
		hit.p = hit.p + offset;
		return true;
	}
	return false;
	
}

bool Translate::boundingBox(float t0, float t1, AABB& aabb) const {

	if (target->boundingBox(t0, t1, aabb)) {
		aabb = AABB(aabb.min() + offset, aabb.max() + offset);
		return true;
	}
	return false;
	
}


RotateY::RotateY(Hitable* target, float angle) :target(target)  {
	float radians = (M_PI / 180) * angle;
	sinTheta = sin(radians);
	cosTheta = cos(radians);
	hasbox = target->boundingBox(0, 1, bb);
	math::vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
	math::vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < 2; k++) {
				float x = bb.max().x * i + (1 - i)*bb.min().x;
				float y = j * bb.max().y + (1 - j)*bb.min().y;
				float z = k * bb.max().z + (1 - k)*bb.min().z;
				float newx = cosTheta * x + sinTheta * z;
				float newz = -sinTheta * x + cosTheta * z;
				math::vec3 temp(newx, y, newz);
				for (int c = 0; c < 3; c++)
				{
					if (temp[c] > max[c])
						max[c] = temp[c];
					if (temp[c] < min[c])
						min[c] = temp[c];
				}
			}
		}
	}
	bb = AABB(min, max);

	
}

//TODO: implement matricies
bool RotateY::hit(const Ray& r, float t_min, float t_max, hitRecord& hit) const {
	
	math::vec3 origin = r.origin();
	math::vec3 direction = r.direction();
	origin[0] = cosTheta * r.origin().x - sinTheta * r.origin().z;
	origin[2] = sinTheta * r.origin().x + cosTheta * r.origin().z;
	direction[0] = cosTheta * r.direction().x - sinTheta * r.direction().z;
	direction[2] = sinTheta * r.direction().x + cosTheta * r.direction().z;
	Ray rotated(origin, direction);
	if (target->hit(rotated, t_min, t_max, hit)) {
		math::vec3 p = hit.p;
		math::vec3 normal = hit.normal;
		p[0] = cosTheta * hit.p.x + sinTheta * hit.p.z;
		p[2] = -sinTheta * hit.p.x + cosTheta * hit.p.z;
		normal[0] = cosTheta * hit.normal.x + sinTheta * hit.normal.z;
		normal[2] = -sinTheta * hit.normal.x + cosTheta * hit.normal.z;
		hit.p = p;
		hit.normal = normal;
		return true;
	}
	return false;


	
}

bool RotateY::boundingBox(float t0, float t1, AABB& aabb) const {

	aabb = bb;
	return hasbox;
}
