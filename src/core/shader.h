#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <vector>
#include <ostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define SHADER_COUNT SHADER_DEFAULT
#define SHADER_MAX_SOURCE_SZ 20000

class Shader {
	public:
		enum ShaderType {
			SHADER_NONE = 0,
			SHADER_DEFAULT
		};

		Shader(std::string, std::string);

	private:
		GLuint handle, vs_handle, fs_handle;
		GLuint compile_shader(std::string, GLenum);
};

#endif