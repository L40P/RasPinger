#ifndef LOG_H
#define LOG_H

#include <iostream>

namespace log {
	void init();
	void clear();
	void write(const char* text);
}

#endif
