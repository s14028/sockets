#include "udp_socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

namespace sck
{

udp_socket::udp_socket()
{
}

void udp_socket::set_socket()
{
	socket_int = ::socket(AF_INET, SOCK_DGRAM, 0);
}

bool udp_socket::bind(const std::string IP, const std::uint16_t port)
{
	sockaddr_in socket_info;
	std::memset(&socket_info, 0, sizeof(sockaddr_in));

	bool could_bind = socket::bind(socket_info, IP, port);

	if(!could_bind)
	{
		return false;
	}
	return ::bind(socket::get_socket_int(), (sockaddr*)&socket_info, sizeof(sockaddr_in)) == 0;
}

unsigned int udp_socket::write(const std::string IP, const std::uint16_t port, std::string& data)
{
	char* array = static_cast<char*>(std::data(data));
	unsigned int number_of_bytes = std::size(data);

	sockaddr_in socket_info;
	std::memset(&socket_info, 0, sizeof(sockaddr_in));

	hostent* address = gethostbyname(std::data(IP));

	if(!address)
	{
		return false;
	}

	std::memcpy(&socket_info.sin_addr.s_addr, address->h_addr, address->h_length);
	socket_info.sin_family = AF_INET;
	socket_info.sin_port = htons(port);

	sendto(socket_int, array, number_of_bytes, 0, (struct sockaddr*) &socket_info, sizeof(sockaddr_in));
	return true;
}

std::tuple<const std::string, const std::uint16_t, std::string> udp_socket::read(const unsigned int number_of_bytes)
{
	std::string data(number_of_bytes, '\0');
	char* array = static_cast<char*>(std::data(data));
	unsigned int sa_size = sizeof(sockaddr_in);

	sockaddr_in socket_info;
	std::memset(&socket_info, 0, sa_size);

	recvfrom(socket_int, array, number_of_bytes, 0, (struct sockaddr*) &socket_info, &sa_size);
	std::string IP = inet_ntoa(socket_info.sin_addr);
	std::uint16_t port = ntohs(socket_info.sin_port);

	return std::make_tuple(IP, port, data);
}

void udp_socket::close()
{
	::close(socket_int);
}
}
