#include "RenderWindow.h"

// scroll wheel
void RenderWindow::scroll_callback(GLFWwindow* window, double x, double y) {
	
}

// key press events
void RenderWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	// pressed tick idk if this matters but whater

	if (action == GLFW_PRESS) {
		if (keyboard_buttons[key].pressed) {
			keyboard_buttons[key].held = true;
			return;
		}
		keyboard_buttons[key].start_press = current_tick;
		keyboard_buttons[key].pressed = 1;
	}
	if (action == GLFW_RELEASE) {
		keyboard_buttons[key].held = false;
		keyboard_buttons[key].pressed = 0;
	}
}

//resize events i think
void RenderWindow::framebuffer_size_callback(GLFWwindow* window, int width, int height) {

}

// mouse moving
void RenderWindow::cursor_position_callback(GLFWwindow* window, double x, double y) {
	if (cursor_enabled)
		return;

	camera_theta += (mouse_last[0] - x) * RenderWindow::CAMERA_SENSITIVITY;

	double dy = (mouse_last[1] - y) * RenderWindow::CAMERA_SENSITIVITY;
	if (abs(camera_phi + dy) < 87.0f)
		camera_phi += dy;

	mouse_last[0] = x;
	mouse_last[1] = y;
}

// mouse clicks
void RenderWindow::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

}

