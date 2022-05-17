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


	// Logger logger;

	// std::shared_ptr<Particle> part = std::make_shared<Particle>(10, 3, .6);
	// logger.attach(part);
	// return 0;
	// joe.init_test();

	joe.test2();
	// joe.tick();
	// std::cout << sizeof(Triangle) << std::endl;
	joe.main_loop();




	return 0;
}
