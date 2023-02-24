#ifndef DAT_H
#define DAT_H

#include <string>

namespace dat {
	void init();
	void setStatus(std::string ip, std::string status, bool success);
	bool wasAnyReached();
	bool wasAnyNotReached();
}

#endif
