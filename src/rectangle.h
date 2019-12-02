#pragma once
#include "hitable.h"

namespace primitive {
	namespace rect {


		class XY : public Hitable {

			Material *mat;
			float x0, x1, y0, y1, k;
			bool flipped;

		public:
			XY() = delete;
			XY(float x0, float x1, float y0, float y1, float k, Material *mat, bool flipNormal = false)
				:x0(x0), x1(x1), y0(y0), y1(y1), k(k), mat(mat), flipped(flipNormal) {};


			bool hit(const Ray& r, float t_min, float t_max, hitRecord& hitRecord) const override;
			bool boundingBox(float t0, float t1, AABB& aabb) const override;
		};


		class XZ : public Hitable {
			Material *mat;
			float x0, x1, z0, z1, k;
			bool flipped;

		public:
			XZ() = delete;
			XZ(float x0, float x1, float z0, float z1, float k, Material *mat, bool flipNormal = false)
				:x0(x0), x1(x1), z0(z0), z1(z1), k(k), mat(mat), flipped(flipNormal) {};


			bool hit(const Ray& r, float t_min, float t_max, hitRecord& hitRecord) const override;
			bool boundingBox(float t0, float t1, AABB& aabb) const override;
		};



		class YZ : public Hitable {
			Material *mat;
			float y0, y1, z0, z1, k;
			bool flipped;

		public:
			YZ() = delete;
			YZ(float y0, float y1, float z0, float z1, float k, Material *mat, bool flipNormal = false)
				:y0(y0), y1(y1), z0(z0), z1(z1), k(k), mat(mat), flipped(flipNormal) {};


			bool hit(const Ray& r, float t_min, float t_max, hitRecord& hitRecord) const override;
			bool boundingBox(float t0, float t1, AABB& aabb) const override;
		};



	}


}

