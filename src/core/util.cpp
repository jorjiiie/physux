#include "util.h"

std::ostream& operator<<(std::ostream& stream, const v3d& vec) {
	stream << "[" << vec.x << "," << vec.y << "," << vec.z << "]";
	return stream;
}

std::chrono::time_point<std::chrono::system_clock> util::clock() {
	return std::chrono::system_clock::now();
}
double util::elapsed(const std::chrono::time_point<std::chrono::system_clock> start, const std::chrono::time_point<std::chrono::system_clock> end) {
	std::chrono::duration<double> time = end - start;
	return time.count();
}
