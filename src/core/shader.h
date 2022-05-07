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

class Shader {
	public:
		// this design is probably not the best for adding a lot of shaders but its fine
		enum ShaderType {
			SHADER_NONE = 0,
			SHADER_DEFAULT
		};
		Shader(std::string, std::string);
		Shader(const Shader&);

		GLuint get_program();
		static void init_shaders();

		static std::shared_ptr<Shader> shaders[SHADER_COUNT + 1];
	private:
		GLuint handle, vs_handle, fs_handle;
		GLuint compile_shader(std::string, GLenum);

		Shader& operator=(const Shader&);

};

#endif