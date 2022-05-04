// renderable things
// we can have like other things that are not interactive but renderable
#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "shader.h"

class Renderable {
	private:
		// model
		GLuint vbo, ibo;
		Shader shader;
	public:
		void render();
};

#endif
