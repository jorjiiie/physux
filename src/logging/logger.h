//logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>
#include <ctime>

#include "../core/particle.h"
#include "../core/util.h"

class Logger {
	private:
		static int particle_number;

		// pair to the file
		// when removing, close the file dumbass
		std::map<std::shared_ptr<Loggable> , std::ofstream> log_items;

		std::string DATA_PATH;
	public:
		Logger();
		void attach(const std::shared_ptr<Loggable>); 
		void log_data();
		void remove(const std::shared_ptr<Loggable>);
		static const std::string FILE_PATH;
		static const std::string FILE_HEADER;
		static const std::string FILE_ENDING;



};


#endif