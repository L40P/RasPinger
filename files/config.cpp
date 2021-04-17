#include "config.h"

#include "files.h"

#include <fstream>
#include <map>
#include <sstream>
#include <vector>



struct KeyStringMap {
	std::vector<std::pair<std::string, config::Key>> MAP;

	std::string translate(config::Key key) {
		for (std::pair<std::string, config::Key> pair : MAP)
			if (pair.second == key)
				return pair.first;
		return "";
	}

	config::Key translate(std::string string) {
		for (std::pair<std::string, config::Key> pair : MAP)
			if (pair.first == string)
				return pair.second;
		return config::UNDEFINED;
	}
};
KeyStringMap ENUM_STRING = {{
	{"", config::UNDEFINED},
	{"PIN_GREEN", config::PIN_GREEN},
	{"PIN_RED", config::PIN_RED},
	{"PING_PACKETSIZE", config::PING_PACKETSIZE},
	{"PING_TIMEOUT", config::PING_TIMEOUT},
	{"PING_TTL", config::PING_TTL},
	{"PING_INTERVAL", config::PING_INTERVAL}
}};

struct KeyValue {
	config::Key key;
	long value;
	KeyValue(config::Key key, long value) {
		this->key = key;
		this->value = value;
	}
	KeyValue(std::string key, std::string value) {
		this->key = ENUM_STRING.translate(key);
		this->value = std::stol(value);
	}
};

std::vector<KeyValue> DEFAULT_CONFIG = {
	{config::PIN_GREEN, 15},
	{config::PIN_RED, 14},
	{config::PING_PACKETSIZE, 36},
	{config::PING_TIMEOUT, 1},
	{config::PING_TTL, 255},
	{config::PING_INTERVAL, 1}
};

std::vector<KeyValue> LOADED_CONFIG = {};

void config::init() {
	std::ostringstream default_config;
	for (KeyValue keyvalue : DEFAULT_CONFIG)
		default_config << ENUM_STRING.translate(keyvalue.key) << "=" << keyvalue.value << "\n";
	files::checkFile(files::FILE_CONFIG, default_config.str());

	std::ifstream file_config(files::FILE_CONFIG, std::fstream::in);

	for (std::string line; getline(file_config, line); ) {
		if (line.empty()) break;
		std::istringstream stream(line);
		std::string key;
		if (getline(stream, key, '=')) {
			std::string value;
			if (getline(stream, value))
				LOADED_CONFIG.push_back(KeyValue(key, value));
		}
	}

	file_config.close();
}

const long config::getValue(Key key) {
	for (KeyValue keyvalue : LOADED_CONFIG)
		if (keyvalue.key == key)
			return keyvalue.value;

	for (KeyValue keyvalue : DEFAULT_CONFIG)
		if (keyvalue.key == key)
			return keyvalue.value;

	return 0;
}
