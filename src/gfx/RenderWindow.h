#ifndef RENDER_WINDOW_H
#define RENDER_WINDOW_H

#include <iostream>
#include <cstdlib>
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

struct Button {
	int start_press;
	bool pressed;
};

class RenderWindow {
	private:
		GLFWwindow* window;
		int mouseX, mouseY;
		Button mouse_buttons[GLFW_MOUSE_BUTTON_LAST] = {};
		Button keyboard_buttons[GLFW_KEY_LAST] = {};
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

		glm::vec3 camera_position, camera_up;
		float camera_theta, camera_phi, camera_focus_length;

		bool cursor_enabled = true;
		glm::vec3 calculate_look();

		void norm_no_up_axis(glm::vec3&);
	protected:
		void key_callback(GLFWwindow*, int, int, int, int);
		void framebuffer_size_callback(GLFWwindow*, int, int);
		void scroll_callback(GLFWwindow*, double, double);
		void mouse_button_callback(GLFWwindow*, int, int, int);
		void cursor_position_callback(GLFWwindow*, double, double);

	public:
		static constexpr double CAMERA_SENSITIVITY = 0.05;
		static constexpr float MOVEMENT_SPEED = 0.03;
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
