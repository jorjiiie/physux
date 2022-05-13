// shapefactory.cpp

#include "ShapeFactory.h"


/*
std::shared_ptr<Renderable> generate_sphere(double radius, glm::vec3& position, int vslices, int hslices) {
	

}
*/

// generates a quad 
std::pair<Triangle, Triangle> ShapeFactory::generate_quad(const v3d& a, const v3d& b, const v3d& c, const v3d& d, const v3d& rgb) {
	// A&C are opposite, B&D are opposite;
	// also no alpha!

	Triangle tri_alpha(a,b,c,rgb);

	Triangle tri_beta(a,c,d,rgb);

	return std::make_pair(tri_alpha, tri_beta);

}
