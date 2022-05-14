// factory for shapes lol
#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H


#include "renderable.h"


namespace ShapeFactory {
	std::vector<Triangle> generate_sphere(double, const v3d&, int, int, const v3d&);
	std::pair<Triangle, Triangle> generate_quad(const v3d&, const v3d&, const v3d&, const v3d&, const v3d&);

}

#endif