#include "server.h"
#include "socket.h"
#include <cstdint>
#include <unistd.h>
#include <netinet/in.h>

namespace sck
{

bool server_socket::listen(std::uint16_t max_connections)
{
	return ::listen(socket::get_socket_int(), max_connections) == 0;
}

std::optional<socket> server_socket::accept()
{
	socket client;
	bool status = client.accept(socket::get_socket_int());

	if(!status)
	{
		return {};
	}

	return {client};
}

bool server_socket::bind(const std::string IP, const std::uint16_t port)
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
}
