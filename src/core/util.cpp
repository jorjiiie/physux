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

std::string util::get_date() {
	auto time_now = util::clock();
	std::time_t now2 = std::chrono::system_clock::to_time_t(time_now);
	return std::string(std::ctime(&now2));
}
