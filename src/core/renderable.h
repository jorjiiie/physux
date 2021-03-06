// renderable things
// we can have like other things that are not interactive but renderable
#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "shader.h"
#include "v3d.h"
#include "triangle.h"

class Renderable {

	protected:
		std::vector<Triangle> mesh;
		std::shared_ptr<Shader> shader;
		GLuint vbo;
		v3d position;
	public:
		Renderable();
		// sphere constructor
		Renderable(double radius, std::shared_ptr<Shader>);
		Renderable(std::vector<Triangle>, std::shared_ptr<Shader>);
		void render();
		void update_position(const v3d&);
};

#endif
