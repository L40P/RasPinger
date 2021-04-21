#include "threading.h"

#include "ping.h"
#include "../files/dat.h"
#include "../files/log.h"
#include "../gpio/gpio.h"

#include <iostream>
#include <algorithm>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>



std::mutex MUTEX_THREADING;
std::vector<std::thread> THREADPOOL = {};

void run(std::string address) {
	ping::RegexResult result = ping::REGEX_RTT.match(ping::ping(address));

	dat::setStatus(address, result.match, result.success);
	std::stringstream ss;
	ss << "Ping result from " << address << " - " << result.match << " (" << result.success << ")";
	log::write(ss.str().c_str());
	gpio::update();
}

void terminate(std::thread::id id) {
	std::lock_guard<std::mutex> LOCK(MUTEX_THREADING);

	auto iterator = std::find_if(THREADPOOL.begin(), THREADPOOL.end(), [=](std::thread& t) { return (t.get_id() == id); });
	if (iterator != THREADPOOL.end()) {
		iterator->join();
		THREADPOOL.erase(iterator);
	}
}

void threadMethod(std::string address) {
	run(address);
	std::thread(terminate, std::this_thread::get_id()).detach();
}

void threading::newThread(std::string address) {
	std::lock_guard<std::mutex> LOCK(MUTEX_THREADING);
	THREADPOOL.push_back(std::thread(threadMethod, address));
}
