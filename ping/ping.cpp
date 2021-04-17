#include "ping.h"

#include "../files/config.h"

#include <array>
#include <memory>
#include <sstream>



long PACKETSIZE;
long TIMEOUT;
long TTL;

void ping::init() {
	PACKETSIZE = config::getValue(config::PING_PACKETSIZE);
	if (PACKETSIZE < 28) PACKETSIZE = 28;
	else if (PACKETSIZE > 65535) PACKETSIZE = 65535;
	PACKETSIZE -= 28;

	TIMEOUT = config::getValue(config::PING_TIMEOUT);
	if (TIMEOUT < 0) TIMEOUT = 0;
	else if (TIMEOUT > 2147) TIMEOUT = 2147;

	TTL = config::getValue(config::PING_TTL);
	if (TTL < 1) TTL = 1;
	else if (TTL > 255) TTL = 255;
}

ping::RegexPattern ping::REGEX_RTT(R"(^[\s\S]*rtt min/avg/max/mdev = [0-9]+\.[0-9]+/([0-9]+\.[0-9]+)/[0-9]+\.[0-9]+/[0-9]+\.[0-9]+ ms[\s\S]*$)");

ping::RegexResult ping::RegexPattern::match(std::string string) {
	std::smatch regex_match;
	bool success = std::regex_match(string, regex_match, regex);

	if (success)
		return RegexResult(success, regex_match[1]);
	else
		return RegexResult(success, "");
}

std::string execCommand(const char* command) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);

	if (!pipe) throw std::runtime_error("Command execution failed");

	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
		result += buffer.data();

	return result;
}

std::string ping::ping(std::string address) {
	// ping -q -c 1 -s packetsize -w timeout -W timeout -t ttl address
	std::ostringstream command;
	command << "ping -q -c 1 -s " << PACKETSIZE << " -w " << TIMEOUT << " -W " << TIMEOUT << " -t " << TTL << " " << address;

	return execCommand(command.str().c_str());
}
