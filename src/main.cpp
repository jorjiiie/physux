#include <chrono>
#include <iostream>
#include <thread>

#include <filesystem>
#include <iostream>

#include "gfx/RenderWindow.h"
#include "core/v3d.h"
#include "renderable.h"
#include "core/util.h"

#define DEBUG_MODE 
#include "core/debug.h"

int main() {

	// initialization
	// for some reason shaders need to be initialized after the window??
	// makes it infinitely unscalable lol
	RenderWindow::initGlfw();

	//construct window
	RenderWindow joe(800, 600, "hola");
	Shader::init_shaders();



	// initialize the test (either)
	// joe.test2();
	joe.magnetic_field_test();

	// run the window loop
	joe.main_loop();



	// return 0
	return 0;
}
