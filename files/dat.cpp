#include "dat.h"

#include "files.h"
#include "log.h"

#include <fstream>
#include <mutex>
#include <sstream>
#include <vector>



struct IP_Status {
	std::string ip = "";
	std::string status = "";
	bool success = false;
	IP_Status(std::string ip, std::string status, bool success) {
		this->ip = ip;
		this->status = status;
		this->success = success;
	}
};

std::mutex MUTEX_DAT;
std::vector<IP_Status*> vector_ipstatus;

void dat::init() {
	files::checkFile(files::FILE_DAT, "");
}

void dumpIPStatus() {
	std::ofstream file_dat = std::ofstream(files::FILE_DAT, std::fstream::out | std::fstream::trunc);

	for (IP_Status* is : vector_ipstatus)
		file_dat << is->ip << " - " << is->status << "\n";

	file_dat.close();
}

void dat::setStatus(std::string ip, std::string status, bool success) {
	std::lock_guard<std::mutex> LOCK(MUTEX_DAT);

	for (IP_Status* is : vector_ipstatus)
		if (is->ip == ip) {
			std::stringstream ss;
			ss << ip << " old=" << is->status << " new=" << status;
			log::write(ss.str().c_str());

			is->status = status;
			is->success = success;

			goto DUMP;
		}

	vector_ipstatus.push_back(new IP_Status(ip, status, success));

DUMP:
	dumpIPStatus();
}

bool dat::hasReached() {
	std::lock_guard<std::mutex> LOCK(MUTEX_DAT);

	for (IP_Status* is : vector_ipstatus)
		if (is->success)
			return true;

	return false;
}

bool dat::hasNotReached() {
	std::lock_guard<std::mutex> LOCK(MUTEX_DAT);
	
	for (IP_Status* is : vector_ipstatus)
		if (!is->success)
			return true;

	return false;
}
