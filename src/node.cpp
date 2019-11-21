#include "node.h"


Node::Node(Hitable** l, int n, float t0, float t1) {

	
	auto axis = (int)3 * utils::randDouble();

	auto* first = &l;
	auto* last = (l + n);
	
	std::sort(l, l+n, AABBAxisComparator(axis));

	
	
	if(n==1) {
		a = b = l[0];
	}
	else if(n==2) {
		a = l[0];
		b = l[1];
	}

	else {
		a = new Node(l, n / 2, t0, t1);
		b = new Node(l + n / 2, n - n / 2, t0, t1);
	}
	AABB tA, tB;
	
	assert(!a->boundingBox(t0, t1, tA) || b->boundingBox(0, 0, tB));

	aabb = AABB::overlap(tA, tB);
	
}

bool Node::hit(const Ray& r, float tmin, float tmax, hitRecord& hRec) const {
	
	if(aabb.hit(r,tmin,tmax)) {
		hitRecord leftRec, rightRec;
		auto hitLeft = a->hit(r, tmin, tmax, leftRec);
		auto hitRight = b->hit(r, tmin, tmax, rightRec);
		if(hitLeft && hitRight) {
			if(leftRec.t< rightRec.t) 
				hRec = leftRec;
			else hRec = rightRec;
			return true;
		}
		if(hitLeft){
			hRec = leftRec;
			return true;
		}
		if(hitRight) {
			hRec = rightRec;
			return true;
		}
	}
	return false;

}

bool Node::boundingBox(float t0, float t1, AABB& aabb) const {
	aabb = this->aabb;
	return true;
}
