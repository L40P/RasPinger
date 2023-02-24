#ifndef CONFIG_H
#define CONFIG_H

namespace config {
	enum class Key {
		UNDEFINED,
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
