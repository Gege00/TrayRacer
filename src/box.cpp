#include "box.h"
#include "rectangle.h"
#include "hitablelist.h"


using namespace primitive;

Box::Box()
{
}


Box::Box(const math::vec3& p0, const math::vec3& p1, Material* mat) {
	pmin = p0;
	pmax = p1;

	Hitable **planes = new Hitable*[6];

	planes[0] = new rect::XY(p0.x, p1.x, p0.y, p1.y, p1.z, mat);
	planes[1] = new rect::XY(p0.x, p1.x, p0.y, p1.y, p0.z, mat,true);
	planes[2] = new rect::XZ(p0.x, p1.x, p0.z, p1.z, p1.y,mat);
	planes[3]= new rect::XZ(p0.x, p1.x, p0.z, p1.z, p0.y,mat,true); 
	planes[4] = new rect::YZ(p0.y, p1.y, p0.z, p1.z, p1.x, mat);
	planes[5]= new rect::YZ(p0.y, p1.y, p0.z, p1.z, p0.x, mat,true);

	list = new Hitablelist(planes, 6);

	
}

bool Box::hit(const Ray& r, float t_min, float t_max, hitRecord& hit) const {
	return list->hit(r, t_min, t_max, hit);
}



bool Box::boundingBox(float t0, float t1, AABB& aabb) const {
	return false;
}
