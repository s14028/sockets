#pragma once
#include <vector>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdint>
#include <cstring>
#include <string>

namespace sck
{
class socket
{
	friend class server_socket;
protected:
	int socket_int;

public:
	socket() = default;
	socket(const socket& another_socket) = default;
	socket(socket&& another_socket) = default;

protected:
	bool accept(int server);
	virtual void set_socket();
	void set_info(sockaddr_in& socket_info, const std::uint16_t port);
	bool bind(sockaddr_in& socket_info, const std::string IP, const std::uint16_t port);
	int get_socket_int();

public:
	std::string read(const unsigned int number_of_bytes = 512);
	unsigned int write(std::string& data);
	virtual bool connect(const std::string IP, const std::uint16_t port);
	virtual operator bool() const;
	void close();
};
}
