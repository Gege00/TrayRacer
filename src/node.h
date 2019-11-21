#pragma once

#include "hitable.h"
#include <assert.h>
#include "utils.h"


class Node : public Hitable {


public:
	Node() = delete;
	Node(Hitable **l, int n, float t0, float t1);

	virtual bool hit(const Ray& r, float tmin, float tmax, hitRecord& hRec)const;
	virtual	bool boundingBox(float t0, float t1, AABB& aabb) const;


	Hitable *a;
	Hitable *b;
	AABB aabb;


};

struct AABBAxisComparator {

	AABBAxisComparator(int axis) {
		assert(axis <= 3 && axis >= 0);
		this->_axis = axis;

	}

	bool operator()(const Hitable* a, const Hitable* b) const {
		AABB left, right;

		assert(!a->boundingBox(0, 0, left) || b->boundingBox(0, 0, right));

		return (left.min()[_axis] - right.min()[_axis] < 0.0f);

	}

	//int operator()(const void* a, const void* b) {
	//	AABB left, right;
	//	auto *ah = *(Hitable **)a;
	//	auto *bh = *(Hitable **)b;

	//	
	//	assert(!ah->boundingBox(0, 0, left) || bh->boundingBox(0, 0, right));

	//	return (left.min()[_axis] - right.min()[_axis] < 0.0f) ? -1 : 1;

	//}
	//
	private:
	int _axis;
};
