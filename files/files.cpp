#include "files.h"

#include "config.h"
#include "dat.h"
#include "ips.h"
#include "log.h"

#include <ctime>
#include <fstream>



std::string files::APP_NAME =		"RasPinger";
std::string files::DIRECTORY =		"/home/pi/" + APP_NAME;
std::string files::FILE_LOG =		DIRECTORY + "/" + APP_NAME + ".log";
std::string files::FILE_CONFIG =	DIRECTORY + "/" + APP_NAME + ".conf";
std::string files::FILE_IPS =		DIRECTORY + "/" + APP_NAME + "_IPs.conf";
std::string files::FILE_DAT =		DIRECTORY + "/" + APP_NAME + ".dat";

void files::init() {
	log::init();
	config::init();
	ips::init();
	dat::init();
}

void files::checkFile(std::string path, std::string defaultContent) {
	std::fstream file(path, std::fstream::in);
	
	if(file.peek() == std::fstream::traits_type::eof()) {
		file.close();
		file.open(path, std::fstream::out);
		file << defaultContent;
	}
	
	file.close();
}

std::string files::timestamp() {
	time_t now = std::time(0);
	struct tm* time = std::localtime(&now);
	
	char buffer[30];
	std::strftime(buffer, 30, "%d.%m.%Y %H:%M:%S", time);
	
	return std::string(buffer).substr(0, 19);
}
