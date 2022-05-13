// factory for shapes lol
#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H


#include "renderable.h"


namespace ShapeFactory {
	std::shared_ptr<Renderable> generate_sphere(double, glm::vec3&, int, int);
	std::pair<Triangle, Triangle> generate_quad(const v3d&, const v3d&, const v3d&, const v3d&, const v3d&);

}

#endif