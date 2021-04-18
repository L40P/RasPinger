#pragma once
#ifndef PING_H
#define PING_H

#include <iostream>
#include <regex>
#include <string>

namespace ping {

	struct RegexResult {
		bool success;
		std::string match;

		RegexResult(bool success, std::string match) {
			this->success = success;
			this->match = success ? match : "Not reached";
		}
	};

	struct RegexPattern {
		std::string pattern;
		std::regex regex;

		RegexResult match(std::string string);

		RegexPattern(std::string pattern) {
			this->pattern = pattern;
			regex = std::regex(pattern);
		}
	};

	extern RegexPattern REGEX_RTT;

	void init();
	std::string ping(std::string address);
}

#endif
