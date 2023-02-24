#include "config.h"

#include "files.h"

#include <fstream>
#include <sstream>
#include <vector>



struct KeyStringMap {
	std::vector<std::pair<std::string, config::Key>> MAP;

	std::string translate(config::Key key) {
		for(std::pair<std::string, config::Key> pair : MAP) {
			if(pair.second == key) {
				return pair.first;
			}
		}
		
		return "";
	}

	config::Key translate(std::string string) {
		for(std::pair<std::string, config::Key> pair : MAP) {
			if(pair.first == string) {
				return pair.second;
			}
		}
		
		return config::Key::UNDEFINED;
	}
};

KeyStringMap mapKeyString = {{
	{"", config::Key::UNDEFINED},
	{"PIN_GREEN", config::Key::PIN_GREEN},
	{"PIN_RED", config::Key::PIN_RED},
	{"PING_PACKETSIZE", config::Key::PING_PACKETSIZE},
	{"PING_TIMEOUT", config::Key::PING_TIMEOUT},
	{"PING_TTL", config::Key::PING_TTL},
	{"PING_INTERVAL", config::Key::PING_INTERVAL}
}};

struct KeyValue {
	config::Key key;
	long value;
	KeyValue(config::Key key, long value) {
		this->key = key;
		this->value = value;
	}
	KeyValue(std::string key, std::string value) {
		this->key = mapKeyString.translate(key);
		this->value = std::stol(value);
	}
};

std::vector<KeyValue> configDefault = {
	{config::Key::PIN_GREEN, 15},
	{config::Key::PIN_RED, 14},
	{config::Key::PING_PACKETSIZE, 36},
	{config::Key::PING_TIMEOUT, 1},
	{config::Key::PING_TTL, 255},
	{config::Key::PING_INTERVAL, 1000}
};

std::vector<KeyValue> configLoaded = {};

void config::init() {
	std::ostringstream default_config;
	for(KeyValue keyvalue : configDefault) {
		default_config << mapKeyString.translate(keyvalue.key) << "=" << keyvalue.value << "\n";
	}
	
	files::checkFile(files::FILE_CONFIG, default_config.str());

	std::ifstream file_config(files::FILE_CONFIG, std::fstream::in);

	for(std::string line; getline(file_config, line); ) {
		if(line.empty()) break;
		
		std::istringstream stream(line);
		std::string key;
		
		if(getline(stream, key, '=')) {
			std::string value;
			if(getline(stream, value)) {
				configLoaded.push_back(KeyValue(key, value));
			}
		}
	}

	file_config.close();
}

const long config::getValue(Key key) {
	for(KeyValue keyvalue : configLoaded) {
		if(keyvalue.key == key) {
			return keyvalue.value;
		}
	}

	for(KeyValue keyvalue : configDefault) {
		if(keyvalue.key == key) {
			return keyvalue.value;
		}
	}

	return 0;
}
