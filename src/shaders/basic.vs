#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 camera_mat;
uniform vec3 model_pos;

out vec4 vertex_col;

void main() {

	vertex_col = vec4(color,1.0);
	// vertex_col = mvp[0];

	gl_Position = camera_mat * vec4(position + model_pos, 1.0);

}
