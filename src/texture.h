#pragma once
#include "vec3.h"

class Texture
{
public:
	virtual math::vec3 value(float u, float v, const math::vec3& p) const = 0;

};
class ConstantTexture : public Texture {
public:
	ConstantTexture() {}
	ConstantTexture(math::vec3 c) : color(c) {}
	virtual math::vec3 value(float u, float v, const math::vec3& p) const {
		return color;
	}
	math::vec3 color;
};

class CheckerTexture: public Texture {

public:
	CheckerTexture(Texture *t0, Texture *t1) : odd(t0), even(t1){}
	virtual math::vec3 value(float u, float v, const math::vec3& p) const {

		float sines = sin(10 * p.x)*sin(10 * p.y) * sin(10 * p.z);
		
		return sines < 0 ? odd->value(u, v, p) : even->value(u,v,p);
	}

	private:
	Texture *odd, *even;
	
};
