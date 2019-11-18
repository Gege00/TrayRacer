#ifndef  _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <iostream>
#include <fstream>
#include <cfloat>


#include "vec3.h"
#include "ray.h"
#include "hitablelist.h"
#include "sphere.h"
#include "camera.h"
#include "metal.h"
#include "diffuse.h"
#include "dielectric.h"
#include "utils.h"
#include "math.h"

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


Hitable *random_scene() {
	int n = 100;
	Hitable **list = new Hitable*[n + 1];
	list[0] = new Sphere(math::vec3(0, -1000, 0), 1000, new Diffuse(math::vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = utils::randDouble();
			math::vec3 center(a + utils::randDouble(), 0.2, b + 0.9*utils::randDouble());
			if ((center - math::vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {  // diffuse
					list[i++] = new Sphere(center, 0.2,
						new Diffuse(math::vec3(
							utils::randDouble()*utils::randDouble(),
							utils::randDouble()*utils::randDouble(),
							utils::randDouble()*utils::randDouble())
						)
					);
				}
				else if (choose_mat < 0.95) { // metal
					list[i++] = new Sphere(center, 0.2,
						new Metal(math::vec3(0.5*(1 + utils::randDouble()),
							0.5*(1 + utils::randDouble()),
							0.5*(1 + utils::randDouble())),
							0.5*utils::randDouble()));
				}
				else {  // glass
					list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new Sphere(math::vec3(0, 1, 0), 1.0, new Dielectric(1.5));
	list[i++] = new Sphere(math::vec3(-4, 1, 0), 1.0, new Diffuse(math::vec3(0.4, 0.2, 0.1)));
	list[i++] = new Sphere(math::vec3(4, 1, 0), 1.0, new Metal(math::vec3(0.7, 0.6, 0.5), 0.0));

	return new Hitablelist(list, i);
}



int main() {

	int nX = 400;
	int nY = 200;
	int ns = 100;
	std::ofstream outfile("render.ppm", std::ios_base::out);
	outfile << "P3\n" << nX << " " << nY << "\n255\n";
	std::cout << "P3\n" << nX << " " << nY << "\n255\n";


	float R = cos(M_PI / 4);
			
	//hList[0] = new Sphere(math::vec3(-R,0,-1), R, new Diffuse(math::vec3(0, 0, 1)));
	//hList[1] = new Sphere(math::vec3(R, 0, -1), R, new Diffuse(math::vec3(1, 0, 0)));

	
	Hitable *w = random_scene();
	math::vec3 lookFrom(3, 3, 2);
	math::vec3 lookAt(0, 0, -1);
	

	Camera cam(lookFrom,lookAt,math::vec3(0,1,0),90,(float)nX/(float)nY,2.0f, (lookFrom - lookAt).length());


	for (int j = nY - 1; j >= 0; j--) {
		for (int i = 0; i < nX; i++) {
			math::vec3 c(0);
			for (int s = 0; s < ns; s++) {
				/*float u = float(i + ((double)rand() / (RAND_MAX))) / float(nX);
				float v = float(j + ((double)rand() / (RAND_MAX))) / float(nY);*/
				
				float u = float(i + utils::randDouble())/ float(nX);
				float v = float(j + utils::randDouble())/ float(nY);
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
