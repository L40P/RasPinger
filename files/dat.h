#pragma once
#ifndef DAT_H
#define DAT_H

#include <iostream>
#include <string>

namespace dat {
	void init();
	void setStatus(std::string ip, std::string status, bool success);
	bool hasReached();
	bool hasNotReached();
}

#endif
