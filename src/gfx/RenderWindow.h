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

#include "../core/renderable.h"
#include "../core/shader.h"
#include "../core/tangible.h"
#include "../core/util.h"

struct Button {
	bool pressed;
	int last_tick, pressed_tick;
};



class RenderWindow {
	private:
		GLFWwindow* window;
		int mouseX, mouseY;
		Button mouse_buttons[GLFW_MOUSE_BUTTON_LAST];
		Button keyboard_buttons[GLFW_KEY_LAST];
		// each shader has a vao kind of, and then you bind the vbos to the vaos
		GLuint vao;
		GLuint vbo;
		std::vector<std::shared_ptr<Renderable> > objects;
		
		glm::mat4 cam_projection, cam_view;

	protected:
		static void key_callback(GLFWwindow*, int, int, int, int);
		static void framebuffer_size_callback(GLFWwindow*, int, int);
		static void scroll_callback(GLFWwindow*, double, double);
		static void mouse_button_callback(GLFWwindow*, int, int, int);
		static void cursor_position_callback(GLFWwindow*, double, double);

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
