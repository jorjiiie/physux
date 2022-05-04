#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <chrono>

#include "v3d.h"

namespace util {
	std::chrono::time_point<std::chrono::system_clock> clock();
	double elapsed(const std::chrono::time_point<std::chrono::system_clock>, const std::chrono::time_point<std::chrono::system_clock>);
}



#endif