#include "socket.h"
#include <string>
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

namespace sck
{

bool socket::accept(int server)
{
	sockaddr_in socket_info;
	socklen_t client_length = sizeof(sockaddr_in);
	int status = ::accept(server, (sockaddr*)&socket_info, &client_length);
	if(status < 0)
	{
		return false;
	}

	socket_int = status;
	return true;
}

void socket::set_socket()
{
	socket_int = ::socket(AF_INET, SOCK_STREAM, 0);
}

void socket::set_info(sockaddr_in& socket_info, const std::uint16_t port)
{
	socket_info.sin_family = AF_INET;
	socket_info.sin_port = htons(port);
}

bool socket::bind(sockaddr_in& socket_info, const std::string IP, const std::uint16_t port)
{
	hostent* address = gethostbyname(std::data(IP));
	if(!address)
	{
		return false;
	}

	std::memcpy(&socket_info.sin_addr.s_addr, address->h_addr, address->h_length);
	set_info(socket_info, port);
	set_socket();
	return socket_int >= 0;
}

bool socket::connect(const std::string IP, const std::uint16_t port)
{
	sockaddr_in socket_info;
	std::memset(&socket_info, 0, sizeof(sockaddr_in));
	bool could_bind = bind(socket_info, IP, port);

	if(!could_bind)
	{
		return false;
	}
	return ::connect(socket_int, (sockaddr*)&socket_info, sizeof(sockaddr_in)) == 0;
}

int socket::get_socket_int()
{
	return socket_int;
}

socket::operator bool() const
{
	return socket_int >= 0;
}


void socket::close()
{
	::close(socket_int);
}

unsigned int socket::write(std::string& data)
{
	char* array = static_cast<char*>(std::data(data));
	unsigned int number_of_bytes = std::size(data);
	int wrote_bytes = ::write(socket_int, array, number_of_bytes);
	return wrote_bytes;
}

std::string socket::read(const unsigned int number_of_bytes)
{
	std::string data(number_of_bytes, '\0');
	char* array = static_cast<char*>(std::data(data));
	unsigned int read_bytes = ::read(socket_int, array, number_of_bytes);
	return data;
}
}
