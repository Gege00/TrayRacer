#include <iostream>
#include <fstream>
#include <cfloat>
#include <random>

#include "vec3.h"
#include "ray.h"
#include "hitablelist.h"
#include "sphere.h"
#include "camera.h"

math::vec3 randomPointInSphere() {
	math::vec3 p;
	do {
		p = 2.0*math::vec3((rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0)), (rand() / (RAND_MAX + 1.0))) - math::vec3(1);
		} while (p.sqr_len() >= 1.0);

	return p;

}

math::vec3 color(const Ray& ray, Hitable *w) {
	hitRecord tRec;

	if (w->hit(ray, 0.001, FLT_MAX, tRec)) {
		math::vec3 target = tRec.p + tRec.normal + randomPointInSphere();
		return 0.5*color(Ray(tRec.p,target-tRec.p),w);
	}

	math::vec3 unitDirection = math::unit_vec(ray.direction());
	float t = 0.5f *(unitDirection.y + 1.0f);
	return (1.0 - t)*math::vec3(1.0) + t * math::vec3(0.5, 0.7, 1.0);
	//return math::vec3(1.0);
}



int main() {

	int nX = 400;
	int nY = 200;
	int ns = 100;
	std::ofstream outfile("render.ppm", std::ios_base::out);
	outfile << "P3\n" << nX << " " << nY << "\n255\n";
	std::cout << "P3\n" << nX << " " << nY << "\n255\n";
	Hitable *hList[2];
	hList[0] = new Sphere(math::vec3(0, 0, -1), 0.5);
	hList[1] = new Sphere(math::vec3(0, -100.5, -1), 100);
	Hitable *w = new Hitablelist(hList, 2);

	Camera cam;
	std::default_random_engine e{};
	std::mt19937 gen(e);
	std::uniform_real_distribution<double> d{ 0,1 };

	for (int j = nY - 1; j >= 0; j--) {
		for (int i = 0; i < nX; i++) {
			math::vec3 c(0);
			for (int s = 0; s < ns; s++) {
				/*float u = float(i + ((double)rand() / (RAND_MAX))) / float(nX);
				float v = float(j + ((double)rand() / (RAND_MAX))) / float(nY);*/
				
				float u = float(i + d(e))/ float(nX);
				float v = float(j + d(e))/ float(nY);
				Ray ray = cam.getRay(u, v);
				math::vec3 p = ray.point_at_parameter(2.0);
				c = c + color(ray, w);
			}
			c = c / float(ns);
			c = math::vec3(sqrt(c.x), sqrt(c.y), sqrt(c.z));
			int r = int(255.99*c.x);
			int g = int(255.99*c.y);
			int b = int(255.99*c.z);

			outfile << r << " " << g << " " << b << "\n";
			std::cout << r << " " << g << " " << b << "\n";
		}

	}

	return 0;
}