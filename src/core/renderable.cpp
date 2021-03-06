//renderable.cpp
#include "renderable.h"

Renderable::Renderable() {
	// does nothing :skull:
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle) * mesh.size(), &mesh[0], GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    position = v3d(0,0,0);
}

Renderable::Renderable(double radius, std::shared_ptr<Shader> pshad) : shader(pshad) {

}
Renderable::Renderable(std::vector<Triangle> p_mesh, std::shared_ptr<Shader> pshad) : shader(pshad) {

	mesh = p_mesh;
	shader = pshad;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle) * mesh.size(), &mesh[0], GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    position = v3d(0,0,0);
}

void Renderable::update_position(const v3d& pos) {
	position = pos;
}
void Renderable::render() {
	// render the stuffs

	glUseProgram(shader->get_program());

    GLuint mod_uniform = glGetUniformLocation(Shader::shaders[Shader::SHADER_DEFAULT]->get_program(), "model_pos");

    // std::cerr << mesh.size() << " " << position << "\n";
    glUniform3f(mod_uniform, position.x, position.y, position.z);

    // set the offset
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// glBufferSubData(GL_ARRAY_BUFFER, sizeof(Triangle) * mesh.size(), &mesh[0], GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Triangle) * mesh.size(), &mesh[0]);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(Triangle::Point), (const void*) 0);
	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, sizeof(Triangle::Point), (const void*) (sizeof (v3d)));

	glDrawArrays(GL_TRIANGLES, 0, mesh.size()*3);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);

}