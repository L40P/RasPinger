#pragma once
#ifndef FILES_H
#define FILES_H

#include <string>

namespace files {
	extern std::string DIRECTORY;
	extern std::string FILE_LOG;
	extern std::string FILE_CONFIG;
	extern std::string FILE_IPS;
	extern std::string FILE_DAT;

	void checkFile(std::string path, std::string defaultContent);
	void init();
	std::string timestamp();
}

#endif
