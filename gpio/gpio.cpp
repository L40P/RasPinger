#include "gpio.h"

#include "../files/config.h"
#include "../files/dat.h"

#include <mutex>
#include <wiringPi.h>



std::mutex MUTEX_GPIO;
int PIN_RED;
int PIN_GREEN;

bool red = false;
void setRed(bool value) {
	if (value == red)
		return;

	digitalWrite(PIN_RED, value ? 1 : 0);
	red = value;
}

bool green = false;
void setGreen(bool value) {
	if (value == green)
		return;

	digitalWrite(PIN_GREEN, value ? 1 : 0);
	green = value;
}

void gpio::init() {
	wiringPiSetupSys();
	PIN_RED = config::getValue(config::PIN_RED);
	PIN_GREEN = config::getValue(config::PIN_GREEN);

	pinMode(PIN_RED, OUTPUT);
	pinMode(PIN_GREEN, OUTPUT);
	digitalWrite(PIN_RED, 0);
	digitalWrite(PIN_GREEN, 0);
}

void gpio::update() {
	std::lock_guard<std::mutex> LOCK(MUTEX_GPIO);

	setRed(dat::hasNotReached());
	setGreen(dat::hasReached());
}
