#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Global.hpp"

#include "../core/renderable.h"
#include "../core/shader.h"
#include "../core/tangible.h"
#include "../core/util.h"


class RenderWindow {
	private:
		GLFWwindow* window;
		int mouseX, mouseY;
		int mouse_buttons[GLFW_MOUSE_BUTTON_LAST];
		int keyboard_buttons[GLFW_KEY_LAST];
		double mouse_last[2];
		double current_tick_mouse[2];
		// each shader has a vao kind of, and then you bind the vbos to the vaos
		GLuint vao;
		GLuint vbo;
		GLuint mvp_uniform;
		std::vector<std::shared_ptr<Renderable> > objects;
		std::vector<std::shared_ptr<Tangible> > scene_physics;


		int current_tick;

		int d_width, d_height;

		glm::vec3 cam_pos;
		double cam_theta, cam_phi;

	protected:
		void key_callback(GLFWwindow*, int, int, int, int);
		void framebuffer_size_callback(GLFWwindow*, int, int);
		void scroll_callback(GLFWwindow*, double, double);
		void mouse_button_callback(GLFWwindow*, int, int, int);
		void cursor_position_callback(GLFWwindow*, double, double);

	public:
		RenderWindow(int, int, std::string);
		// maybe render should take a vector of 'drawables'
		void render();
		// one thread handles ticks and another handles rendering?
		// dont do that because i dont know why we need that yet
		void update();
		void tick();
		void add_object(Renderable);
		void main_loop();
		static void initGlfw();
		static void init_shaders();

		void init_test();
		// static RenderWindow* self;
};

#endif
