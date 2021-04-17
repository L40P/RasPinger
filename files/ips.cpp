#include "ips.h"

#include "files.h"

#include <fstream>
#include <sstream>
#include <vector>



std::vector<std::string> DEFAULT_IPS = {
	"1.1.1.1", "1.0.0.1", "8.8.8.8", "8.8.4.4"
};

std::vector<std::string> vector_ips = {};
long unsigned int index_ips = 0;

void ips::init() {
	std::ostringstream default_ips;
	for (std::string ip : DEFAULT_IPS)
		default_ips << ip << "\n";
	files::checkFile(files::FILE_CONFIG, default_ips.str());

	std::ifstream file_ips = std::ifstream(files::FILE_IPS, std::fstream::in);
	for (std::string line; getline(file_ips, line); )
		if (!line.empty())
			vector_ips.push_back(line);

	file_ips.close();
}

std::string ips::nextIP() {
	std::string* ip = &vector_ips[index_ips];
	index_ips++;
	if (index_ips >= vector_ips.size())
		index_ips = 0;
	return *ip;
}
