#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>

namespace config {

	enum Key {
		UNDEFINED = -1,
		PIN_GREEN,
		PIN_RED,
		PING_PACKETSIZE,
		PING_TIMEOUT,
		PING_TTL,
		PING_INTERVAL,
	};

	void init();
	const long getValue(Key key);
}

#endif
