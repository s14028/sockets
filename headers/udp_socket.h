#pragma once

#include <vector>
#include <tuple>
#include <string>

#include "socket.h"

namespace sck
{
class udp_socket : protected socket
{
public:
	udp_socket();

protected:
	void set_socket();

public:
	bool bind(const std::string IP, const std::uint16_t port);
	unsigned int write(const std::string IP, const std::uint16_t port, std::string& data);
	std::tuple<const std::string, const std::uint16_t, std::string> read(const unsigned int number_of_bytes);

	void close();
};
}
