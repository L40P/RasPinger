#include "log.h"

#include "files.h"

#include <fstream>
#include <iostream>
#include <mutex>



std::mutex MUTEX_LOG;
std::ofstream file_log = std::ofstream();

void log::init() {
	files::checkFile(files::FILE_LOG, "\nStarted on " + files::timestamp() + "\n\n");
	
	file_log.open(files::FILE_LOG, std::fstream::out | std::fstream::app);
	
	std::cerr.rdbuf(file_log.rdbuf());
}

void log::clear() {
	std::lock_guard<std::mutex> LOCK(MUTEX_LOG);
	
	file_log.close();
	file_log.open(files::FILE_LOG, std::fstream::out | std::fstream::trunc);
	file_log << "\nStarted on " << files::timestamp() << "\n\n";
	
	std::cerr.rdbuf(file_log.rdbuf());
}

void log::write(const char* text) {
	std::lock_guard<std::mutex> LOCK(MUTEX_LOG);
	
	file_log << "[" << files::timestamp() << "] " << text << std::endl;
}
