//logger.cpp

#include "logger.h"

#define DEBUG_MODE

#include "../core/debug.h"



namespace fs = std::filesystem;

// inits
int Logger::particle_number = 0;
const std::string Logger::FILE_PATH = "../data/";

const std::string Logger::FILE_HEADER = "particle";

const std::string Logger::FILE_ENDING = ".csv";

Logger::Logger() {

	DATA_PATH = FILE_PATH;
   
// normal mode it will create the new directories
#ifndef DEBUG_MODE
	std::string date = util::get_date();
	DATA_PATH += "Run " + date.substr(0,date.length()-1);
#else
	DATA_PATH += "run_debug";
#endif
	DATA_PATH += '/';

	std::cerr << DATA_PATH << std::endl;
#ifndef DEBUG_MODE
	// make a new directory!
	throw_if(!fs::create_directory(DATA_PATH), "directory failed to create");
#endif

}

void Logger::attach(const std::shared_ptr<Loggable> log_item) {

	//open an ofstream for the thing

	if (log_items.find(log_item) != log_items.end()) {
		std::cerr << "Loggable item already added\n";
		return;
	}

	std::string filename = DATA_PATH + Logger::FILE_HEADER + std::to_string(Logger::particle_number) + Logger::FILE_ENDING;
	std::ofstream log_item_stream(filename);

	log_items[log_item] = std::move(log_item_stream);

	log_item->log_init(log_items[log_item]);

	Logger::particle_number++;
	std::cerr << "ATTACHING PARTICLE " << Logger::particle_number << "\n";
}

void Logger::log_data() {
	for (auto& k : log_items) {
		std::shared_ptr<Loggable> log_item = k.first;
		log_item->log_data(k.second);
	}
}

void Logger::remove(const std::shared_ptr<Loggable> log_item) {
	if (log_items.find(log_item) == log_items.end()) {
		std::cerr << "Loggable item not found, removing nothing\n";
		return;
	}

	log_items[log_item].close();
	log_items.erase(log_item);

}
