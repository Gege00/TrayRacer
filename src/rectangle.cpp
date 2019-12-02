#include "rectangle.h"
#include <cassert>


bool primitive::rect::XY::hit(const Ray& r, float t_min, float t_max, hitRecord& hitRecord) const {
	if(r.a.x<-1000)_CrtDbgBreak();
	float t = (k - r.origin().z) / r.direction().z;
	if(t<t_min || t>t_max) {
		return false;
	}

	float x = r.origin().x + t * r.direction().x;
	float y = r.origin().y + t * r.direction().y;
	if(x<x0 || x>x1 || y<y0 || y>y1) {
		return false;
	}
	hitRecord.u = (x - x0) / (x1 - x0);
	hitRecord.v = (y - y0) / (y1 - y0);
	hitRecord.matPtr = mat;
	hitRecord.t = t;
	hitRecord.p = r.point_at_parameter(t);
	hitRecord.normal = math::vec3(0, 0, flipped ? -1 : 1);
	return true;
	
}



bool primitive::rect::XZ::hit(const Ray& r, float t_min, float t_max, hitRecord& hitRecord) const {
	float t = (k - r.origin().y) / r.direction().y;
	if (t<t_min || t>t_max) {
		return false;
	}

	float x = r.origin().x + t * r.direction().x;
	float z = r.origin().z + t * r.direction().z;
	if (x<x0 || x>x1 || z<z0 || z>z1) {
		return false;
	}
	hitRecord.u = (x - x0) / (x1 - x0);
	hitRecord.v = (z - z0) / (z1 - z0);
	hitRecord.matPtr = mat;
	hitRecord.t = t;
	hitRecord.p = r.point_at_parameter(t);
	hitRecord.normal = math::vec3(0, flipped ? -1 : 1, 0);
	return true;
	
}

bool primitive::rect::YZ::hit(const Ray& r, float t_min, float t_max, hitRecord& hitRecord) const {

	float t = (k - r.origin().x) / r.direction().x; 
	
	
	if (t<t_min || t>t_max) { 
		return false;
	}

	float y = r.origin().y + t * r.direction().y;
	float z = r.origin().z + t * r.direction().z;
	if (y<y0 || y>y1 || z<z0 || z>z1) {
		return false;
	}
	hitRecord.u = (y - y0) / (y1 - y0);
	hitRecord.v = (z - z0) / (z1 - z0);
	hitRecord.matPtr = mat;
	hitRecord.t = t;
	hitRecord.p = r.point_at_parameter(t);
	hitRecord.normal = math::vec3(flipped ? -1 : 1,0 , 0);
	return true;
	
}


bool primitive::rect::XY::boundingBox(float t0, float t1, AABB& aabb) const {
	aabb = AABB(math::vec3(x0, y0, k - 0.001), math::vec3(x1, y1, k + 0.001));
	return true;
}

bool primitive::rect::XZ::boundingBox(float t0, float t1, AABB& aabb) const {
	aabb = AABB(math::vec3(x0,  k - 0.001,z0), math::vec3(x1, k + 0.001,z1));
	return true;
}


bool primitive::rect::YZ::boundingBox(float t0, float t1, AABB& aabb) const {
	aabb = AABB(math::vec3(k - 0.001,y0, z0), math::vec3(k + 0.001,y1, z1));
	return true;
}
