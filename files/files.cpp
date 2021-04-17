#include "files.h"

#include "config.h"
#include "dat.h"
#include "ips.h"
#include "log.h"

#include <ctime>
#include <fstream>



std::string files::DIRECTORY = "/home/pi/Pinger";
std::string files::FILE_LOG = DIRECTORY + "/Pinger.log";
std::string files::FILE_CONFIG = DIRECTORY + "/Pinger.conf";
std::string files::FILE_IPS = DIRECTORY + "/Pinger_IPs.conf";
std::string files::FILE_DAT = DIRECTORY + "/Pinger.dat";

void files::init() {
	log::init();
	config::init();
	ips::init();
	dat::init();
}

void files::checkFile(std::string path, std::string defaultContent) {
	std::fstream file(path, std::fstream::in);
	if (file.peek() == std::fstream::traits_type::eof()) {
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
