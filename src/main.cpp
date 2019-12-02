#include "common.h"


#include <iostream>
#include <fstream>
#include <cfloat>



math::vec3 color(const Ray& ray, Hitable *w, int depth) {
	hitRecord tRec;

	if (w->hit(ray, 0.001, FLT_MAX, tRec)) {
		Ray scatteredRay;
		math::vec3 attenuation;
		float pdf;
		math::vec3 emitted = tRec.matPtr->emitted(tRec.u, tRec.v, tRec.p);
		if (depth < 50 && tRec.matPtr->scatter(ray, tRec, attenuation, scatteredRay,pdf)) {

			
 			return   emitted + 
				attenuation
				*tRec.matPtr->scatteringPdf(ray,tRec,scatteredRay)
				*color(scatteredRay, w, depth+1) / pdf;
		}
		 return emitted;
	}

	return math::vec3(0);
}

Texture *checker = new CheckerTexture(
	new ConstantTexture(math::vec3(0.2, 0.3, 0.1)),
	new ConstantTexture(math::vec3(0.9, 0.9, 0.9)));
//
//Hitable *random_scene() {
//	int n =5000;
//	Hitable **list = new Hitable*[n + 1];
//	list[0] = new primitive::Sphere(math::vec3(0, -1000, 0), 1000, new Diffuse(checker));
//	int i = 1;
//	for (int a = -5; a < 5; a++) {
//		for (int b = -5; b < 5; b++) {
//			float choose_mat = utils::randDouble();
//			math::vec3 center(a + utils::randDouble(), 0.2, b + 0.9*utils::randDouble());
//			if ((center - math::vec3(4, 0.2, 0)).length() > 0.9) {
//				if (choose_mat < 0.8) {  // diffuse
//					list[i++] = new primitive::Sphere(center, 0.2,
//						new Diffuse(checker));
//				}
//				else if (choose_mat < 0.95) { // metal
//					list[i++] = new primitive::Sphere(center, 0.2,
//						new Metal(math::vec3(0.5*(1 + utils::randDouble()),
//							0.5*(1 + utils::randDouble()),
//							0.5*(1 + utils::randDouble())),
//							0.5*utils::randDouble()));
//				}
//				else {  // glass
//					list[i++] = new primitive::Sphere(center, 0.2, new Dielectric(1.5));
//				}
//			}
//		}
//	}
//
//	list[i++] = new primitive::Sphere(math::vec3(0, 1, 0), 1.0, new Dielectric(1.5));
//	list[i++] = new primitive::Sphere(math::vec3(-4, 1, 0), 1.0, new Diffuse(checker));
//	list[i++] = new primitive::Sphere(math::vec3(4, 1, 0), 1.0, new Metal(math::vec3(0.7, 0.6, 0.5), 0.0));
//
////	return new Hitablelist(list, i);
//	return new Hitablelist(list, i);
//}

//Hitable *two_spheres() {
//	
//	int n = 50;
//	Hitable **list = new Hitable*[n + 1];
//	list[0] = new primitive::Sphere(math::vec3(0, -10, 0), 10, new Diffuse(checker));
//	list[1] = new primitive::Sphere(math::vec3(0, 10, 0), 10, new Diffuse(checker));
//	//return new Hitablelist(list, 2);
//	return new Node(list, 2, 0, 1);
//	
//}
//
//Hitable *simpleLight() {
//	Hitable** list = new Hitable*[4];
//	list[0] = new primitive::Sphere(math::vec3(0, -1000, 0), 1000, new Diffuse(checker));
//	list[1] = new primitive::Sphere(math::vec3(0, 2, 0), 2, new Diffuse(checker));
//	list[2] = new primitive::Sphere(math::vec3(0, 7, 0), 2, new DiffuseLight( new ConstantTexture(math::vec3(4))));
//	list[3] = new primitive::rect::XY(3, 5, 1, 3, -2, new DiffuseLight(new ConstantTexture(math::vec3(4))));
//
//	return new Hitablelist(list, 4);
//	
//}


void cornellBox(Hitable **scene,Camera **cam, float aspect) {

	Hitable **list = new Hitable*[8];
	int i = 0;

	Material *red =   new Diffuse(new ConstantTexture(math::vec3(0.65, 0.05, 0.05)));
	Material *white = new Diffuse(new ConstantTexture(math::vec3(0.73, 0.73, 0.73)));
	Material *green = new Diffuse(new ConstantTexture(math::vec3(0.12, 0.45, 0.15)));
	Material *light = new DiffuseLight(new ConstantTexture(math::vec3(15, 15, 15)));


	list[i++] = new primitive::rect::YZ(0, 555, 0, 555, 555, green,true); 	list[i++] = new primitive::rect::YZ(0, 555, 0, 555, 0, red);
	list[i++] = new primitive::rect::XZ(213,343,227, 332, 554, light);
	list[i++] = new primitive::rect::XZ(0,555,0,555,555,white,true);
	list[i++] = new primitive::rect::XZ(0, 555, 0, 555, 0, white);
	list[i++] = new primitive::rect::XY(0, 555, 0, 555, 555, white,true);
	list[i++] = new Translate(
		new RotateY(new primitive::Box(math::vec3(0, 0, 0), math::vec3(165, 165, 165), white), -18),
		math::vec3(130, 0, 65)
	);
	list[i++] = new Translate(
		new RotateY(new primitive::Box(math::vec3(0, 0, 0), math::vec3(165, 330, 165), white), 15),
		math::vec3(265, 0, 295)
	);
	*scene = new Hitablelist(list, i);
	float dist = 10;
	float apert = 0;
	float fov = 40.0;
	math::vec3 lookFrom(278, 278, -800);
	math::vec3 lookAt(278, 278, 0);
	*cam = new Camera(lookFrom, lookAt, math::vec3(0, 1, 0), fov,aspect, apert, dist);
	
}




int main() {

	int nX = 500;
	int nY = 500;
	int ns =200;
	std::ofstream outfile("render.ppm", std::ios_base::out);
	outfile << "P3\n" << nX << " " << nY << "\n255\n";
	std::cout << "P3\n" << nX << " " << nY << "\n255\n";

	

	float R = cos(M_PI / 4);
			
	//hList[0] = new Sphere(math::vec3(-R,0,-1), R, new Diffuse(math::vec3(0, 0, 1)));
	//hList[1] = new Sphere(math::vec3(R, 0, -1), R, new Diffuse(math::vec3(1, 0, 0)));

	Camera *cam;
	Hitable *w;
	cornellBox(&w,&cam, (float)nX / (float)nY);




	for (int j = nY - 1; j >= 0; j--) {
		for (int i = 0; i < nX; i++) {
			math::vec3 c(0);
			for (int s = 0; s < ns; s++) {
				/*float u = float(i + ((double)rand() / (RAND_MAX))) / float(nX);
				float v = float(j + ((double)rand() / (RAND_MAX))) / float(nY);*/
				
				float u = float(i + utils::randDouble())/ float(nX);
				float v = float(j + utils::randDouble())/ float(nY);
				Ray ray = cam->getRay(u, v);
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
	outfile.close();

	return 0;
}
