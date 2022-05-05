// renderable things
// we can have like other things that are not interactive but renderable
#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "v3d.h"
#include "triangle.h"

class Renderable {

	protected:
		std::vector<Triangle> vertices;
		std::shared_ptr<Shader> shader;

	public:
		Renderable(std::shared_ptr<Shader>);
		void render();
		void add_data();
};

#endif
