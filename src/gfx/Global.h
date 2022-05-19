#ifndef GLOBAL_H
#define GLOBAL_H

#include <map>

class RenderWindow;
struct GLFWwindow;


struct Global {
	static double TIME_STEP;
	static constexpr double DEFAULT_TIME_STEP = 0.1;
	// static constexpr double CONSTANT_ELECTRIC = 1.0;
	static constexpr double CONSTANT_ELECTRIC = 0.0001;
	static constexpr double EPSILON = 0.0001;
	inline static std::map<GLFWwindow*, RenderWindow*> window_map;
};

#endif