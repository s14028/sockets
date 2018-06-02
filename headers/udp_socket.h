#pragma once

#include <vector>
#include <tuple>
#include <string>

#include "socket.h"

class UDPSocket : protected Socket
{
public:
	UDPSocket();

	void setSocket();
	bool bind(const std::string IP, const std::uint16_t port);

	bool write(const std::string IP, const std::uint16_t port, std::vector<unsigned char>& bytes);
	std::tuple<const std::string, const std::uint16_t, std::vector<unsigned char>> read(const unsigned int size);

	void close();
};
