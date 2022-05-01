#include <chrono>
#include <iostream>
#include <thread>

#include "gfx/RenderWindow.h"
#include "core/v3d.h"
#include "renderable.h"
#include "core/util.h"

#define DEBUG_MODE 
#include "core/debug.h"

int main() {
	std::cout << "aaa" << std::endl;

	auto tt = util::clock();

	RenderWindow::initGlfw();
	RenderWindow joe(1920, 1200, "hola");
	std::cout << "hi\n";
	v3d x(1,1,1);
	x = v3d(5,5,5);
	std::cout << x << "\n";

	joe.main_loop();
	std::this_thread::sleep_for(std::chrono::milliseconds(200));

	std::cout << util::elapsed(tt, util::clock()) << "\n";

	ASSERT(x.z != 0, "test assert!\n");
	std::cout << "dhd\n";	



	return 0;
}
