#include "shader.h"
#define DEBUG_MODE 
#include "debug.h"


std::shared_ptr<Shader> Shader::shaders[Shader::SHADER_COUNT + 1];

GLuint Shader::compile_shader(std::string shader_path, GLenum type) {

	FILE *source_file = std::fopen(shader_path.c_str(), "rb");

	throw_if(source_file == NULL, "Failed to open shader file " + shader_path);
	char *shader_source;
	long len;

	fseek(source_file, 0, SEEK_END);
	len = ftell(source_file);

	ASSERT(len > 0, "baba");

	fseek(source_file, 0, SEEK_SET);

	shader_source = (char* ) calloc(1, len);

	ASSERT(shader_source != NULL, "you suck at programming?");

	fread(shader_source, 1, len, source_file);

	ASSERT(strlen(shader_source) > 0, "yoinks");

	fclose(source_file);

	GLuint shader;
	shader = glCreateShader(type);
	// shader = glCreateShader(type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
	    glGetShaderInfoLog(shader, 512, NULL, infoLog);
	    std::cerr << infoLog << std::endl;
	    std::string errmsg =  "ERROR::SHADER::" + std::string(type == GL_VERTEX_SHADER ? "VERTEX":"FRAGMENT") +"COMPILATION FAILED";
	    throw_if(1, errmsg);
	}

	free(shader_source);

	return shader;
}

Shader::Shader(std::string vs_path, std::string fs_path) {
	vs_handle = compile_shader(vs_path, GL_VERTEX_SHADER);
	fs_handle = compile_shader(fs_path, GL_FRAGMENT_SHADER);
	handle = glCreateProgram();

	glAttachShader(handle, vs_handle);
	glAttachShader(handle, fs_handle);

	glLinkProgram(handle);

	// add a throw if here

	std::cerr << "successfully compiled shader" << std::endl;
}

// must be called after RenderWindow init
void Shader::init_shaders() {
	shaders[1] = std::make_shared<Shader>("../src/shaders/basic.vs", "../src/shaders/basic.fs");
}


Shader::Shader(const Shader& o) : handle(o.handle), vs_handle(o.vs_handle), fs_handle(o.fs_handle) {}

GLuint Shader::get_program() {
	return handle;
}