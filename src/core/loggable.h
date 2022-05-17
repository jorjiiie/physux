//loggable.h

#ifndef LOGGABLE_H
#define LOGGABLE_H

#include <string>
#include <vector>
#include <fstream>

class Loggable {
	public:
		Loggable();
		virtual void log_data(std::ofstream&) = 0;
		virtual void log_init(std::ofstream&) = 0;
		virtual ~Loggable() = 0;
};


#endif