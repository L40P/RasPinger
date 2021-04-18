#include "files/config.h"
#include "files/files.h"
#include "files/ips.h"
#include "gpio/gpio.h"
#include "ping/ping.h"
#include "ping/threading.h"

#include <iostream>
#include <wiringPi.h>



unsigned int INTERVAL;

void init() {
	files::init();
	gpio::init();
	ping::init();
	std::cout << "init\n";
	INTERVAL = config::getValue(config::PING_INTERVAL);
}

void loop() {
	std::cout << "loop\n";
	threading::newThread(ips::nextIP());
	std::cout << "thread\n";
	delay(INTERVAL);
}

int main(void)
{
	init();

	while (true)
		loop();

	return 0;
}
