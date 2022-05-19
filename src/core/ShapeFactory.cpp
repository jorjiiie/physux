// shapefactory.cpp

#include "ShapeFactory.h"
#define DEBUG_MODE
#include "debug.h"


std::vector<Triangle> ShapeFactory::generate_sphere(double radius, const v3d& position, 
											int vslices, int hslices, const v3d& rgb) {

	ASSERT(vslices > 0 && hslices > 0, "slice error man");

	std::vector<std::vector< v3d> > vertices(vslices+1, std::vector<v3d>(hslices+1));

	// std::cerr << rgb << " " << radius  << "\n";

	double invV = 1.0 / vslices;
	double invH = 1.0 / hslices;
	for (int i=0; i<=vslices; i++) {

		double phi = 90.0 - 180.0 * i * invV;
		double cos_phi = glm::cos(glm::radians(phi));
		double sin_phi = glm::sin(glm::radians(phi));

		for (int j=0; j<=hslices;j++) {
			double theta = 360 * j * invH;

			vertices[i][j] = position + 
							 v3d(cos_phi * glm::cos(glm::radians(theta)),
								 cos_phi * glm::sin(glm::radians(theta)),
								 sin_phi) * radius;
		}

	}
	std::vector<Triangle> mesh;

	for (int i=0; i<vslices; i++) {
		for (int j=0; j<hslices; j++) {
			std::pair<Triangle, Triangle> quad = ShapeFactory::generate_quad(vertices[i][j], vertices[i][j+1], vertices[i+1][j+1], vertices[i+1][j], rgb);
			mesh.push_back(quad.first);
			mesh.push_back(quad.second);
		}
	}
	
		// std::cerr << mesh.size() << " mesh triangles!\n";
	return mesh;
}


// generates a quad 
std::pair<Triangle, Triangle> ShapeFactory::generate_quad(const v3d& a, const v3d& b, const v3d& c, const v3d& d, const v3d& rgb) {
	// A&C are opposite, B&D are opposite;
	// also no alpha!

	// if you think about this, then youd be 100% able to use face culling but that is too much thinking
	Triangle tri_alpha(a,b,c,rgb);

	Triangle tri_beta(a,c,d,rgb);

	return std::make_pair(tri_alpha, tri_beta);

}
