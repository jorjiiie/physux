#include "shader.h"
#define DEBUG_MODE 
#include "debug.h"

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
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << infoLog << std::endl;
        throw_if(1, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
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
}
Shader::Shader(const Shader& o) : handle(o.handle), vs_handle(o.vs_handle), fs_handle(o.fs_handle) {}