#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <map>

class RenderWindow;
struct GLFWwindow;


struct Global {
	inline static std::map<GLFWwindow*, RenderWindow*> window_map;
};

#endif