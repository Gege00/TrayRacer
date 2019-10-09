#include <iostream>
#include <fstream>
#include <cfloat>
#include <random>


#include "vec3.h"
#include "ray.h"
#include "hitablelist.h"
#include "sphere.h"
#include "camera.h"
#include "metal.h"
#include "diffuse.h"


math::vec3 color(const Ray& ray, Hitable *w, int depth) {
	hitRecord tRec;

	if (w->hit(ray, 0.001, FLT_MAX, tRec)) {
		Ray scatteredRay;
		math::vec3 attenuation;
		if (depth < 50 && tRec.matPtr->scatter(ray, tRec, attenuation, scatteredRay)) {
			return attenuation * color(scatteredRay, w, depth++);
		}
		return math::vec3(0.0);
	}

	math::vec3 unitDirection = math::unit_vec(ray.direction());
	float t = 0.5f *(unitDirection.y + 1.0f);
	return (1.0 - t)*math::vec3(1.0) + t * math::vec3(0.5, 0.7, 1.0);
}



int main() {

	int nX = 400;
	int nY = 200;
	int ns = 100;
	std::ofstream outfile("render.ppm", std::ios_base::out);
	outfile << "P3\n" << nX << " " << nY << "\n255\n";
	std::cout << "P3\n" << nX << " " << nY << "\n255\n";
	Hitable *hList[4];
	hList[0] = new Sphere(math::vec3(0, 0, -1), 0.5, new Diffuse(math::vec3(0.8,0.3,0.3)));
	hList[1] = new Sphere(math::vec3(0, -100.5, -1), 100, new Diffuse(math::vec3(0.8,0.8,0.0)));
	hList[2] = new Sphere(math::vec3(1, 0, -1), 0.5, new Metal(math::vec3(0.8,0.6,0.2),0.01f));
	hList[3] = new Sphere(math::vec3(-1, 0, -1), 0.5, new Metal(math::vec3(0.8),1.0f));

	
	Hitable *w = new Hitablelist(hList, 4);

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
				c = c + color(ray, w,0);
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