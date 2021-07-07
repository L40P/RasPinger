#ifndef DAT_H
#define DAT_H

#include <iostream>
#include <string>

namespace dat {
	extern int i;

	void init();
	void setStatus(std::string ip, std::string status, bool success);
	bool hasReached();
	bool hasNotReached();
}

#endif
