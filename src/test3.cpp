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

	RenderWindow::initGlfw();
	RenderWindow joe(800, 600, "hola");
	Shader::init_shaders();

	std::cerr << "MADE IT PAST THIS PART" << std::endl;
	joe.init_test();

	std::cout << sizeof(Triangle) << std::endl;
	joe.main_loop();




	return 0;
}
