#include "server.h"
#include "socket.h"
#include <cstdint>
#include <unistd.h>
#include <netinet/in.h>


ServerSocket::ServerSocket()
{
}

bool ServerSocket::listen(std::uint16_t maxConnection)
{
	return ::listen(Socket::getSocketInt(), maxConnection) == 0;
}

std::optional<Socket> ServerSocket::accept()
{
	Socket client;
	bool status = client.accept(Socket::getSocketInt());

	if(!status)
	{
		return {};
	}

	return {client};
}

bool ServerSocket::bind(const std::string IP, const std::uint16_t port)
{
	sockaddr_in socketInfo;
	std::memset(&socketInfo, 0, sizeof(sockaddr_in));

	bool couldBind = Socket::bind(socketInfo, IP, port);

	if(!couldBind)
	{
		return false;
	}
	return ::bind(Socket::getSocketInt(), (sockaddr*)&socketInfo, sizeof(sockaddr_in)) == 0;
}
