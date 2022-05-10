#include "RenderWindow.h"

// scroll wheel
void RenderWindow::scroll_callback(GLFWwindow* window, double x, double y) {
	
}

// key press events
void RenderWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// pressed tick idk if this matters but whater
	if (action == GLFW_PRESS)
		keyboard_buttons[key] = current_tick;
	if (action == GLFW_RELEASE)
		keyboard_buttons[key] = 0;
}

//resize events i think
void RenderWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height) {

}

// mouse moving
void RenderWindow::cursor_position_callback(GLFWwindow* window, double x, double y) {

}

// mouse clicks
void RenderWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

}

