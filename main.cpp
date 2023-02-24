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
	
	INTERVAL = config::getValue(config::Key::PING_INTERVAL);
}

void loop() {
	threading::newThread(ips::nextIP());
	
	delay(INTERVAL);
}

int main() {
	init();
	
	while(true) {
		loop();
	}
	
	return 0;
}
