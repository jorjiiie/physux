// renderable things
// we can have like other things that are not interactive but renderable
#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Renderable {
	private:
		// model
		GLuint vbo, ibo;
	public:
		void render();
};

#endif
