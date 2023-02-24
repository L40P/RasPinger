#include "gpio.h"

#include "../files/config.h"
#include "../files/dat.h"

#include <mutex>
#include <pigpiod_if2.h>



std::mutex MUTEX_GPIO;
int PIN_RED;
int PIN_GREEN;
int PI_ID;

bool red = false;
void setRed(bool value) {
	if(value == red) return;
	
	gpio_write(PI_ID, PIN_RED, value ? PI_HIGH : PI_LOW);
	red = value;
}

bool green = false;
void setGreen(bool value) {
	if(value == green) return;
	
	gpio_write(PI_ID, PIN_GREEN, value ? PI_HIGH : PI_LOW);
	green = value;
}

void gpio::init() {
	PI_ID = pigpio_start(0, 0);
	
	if(PI_ID < 0) throw std::runtime_error("pigpio initialization failed");
	
	PIN_RED = config::getValue(config::Key::PIN_RED);
	PIN_GREEN = config::getValue(config::Key::PIN_GREEN);
	
	set_mode(PI_ID, PIN_RED, PI_OUTPUT);
	set_mode(PI_ID, PIN_GREEN, PI_OUTPUT);
	gpio_write(PI_ID, PIN_RED, PI_LOW);
	gpio_write(PI_ID, PIN_GREEN, PI_LOW);
}

void gpio::update() {
	std::lock_guard<std::mutex> LOCK(MUTEX_GPIO);
	
	setRed(dat::wasAnyNotReached());
	setGreen(dat::wasAnyReached());
}
