#include "socket.h"
#include "streamSocket.h"
#include "enumTransportLayer.h"
#include <string>
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

Socket::Socket(std::uint16_t port, const TransportLayerType& type)
{
	std::memset(&socketInfo, 0, sizeof(sockaddr_in));
	setSocket(type);
	setInfo(port);
}

Socket::Socket(const Socket& anotherSocket)
{
	this->socketInfo = anotherSocket.socketInfo;
	this->socketInt = anotherSocket.socketInt;
}

Socket::Socket()
{
	std::memset(&socketInfo, 0, sizeof(sockaddr_in));
}

Socket::Socket(std::string ip, std::uint16_t port, const TransportLayerType& type)
{
	std::memset(&socketInfo, 0, sizeof(sockaddr_in));
	setSocket(type);
	connect(ip, port);
}

SocketStream Socket::stream()
{
	return SocketStream(socketInt);
}
	
bool Socket::accept(int server)
{
	socklen_t clientLength = sizeof(sockaddr_in);
	int status = ::accept(server, (sockaddr*)&socketInfo, &clientLength);
	if(status < 0)
		return false;

	socketInt = status;
	bindStatus = true;
	return true;
}


void Socket::setSocket(const TransportLayerType& type)
{
	if(type == TransportLayerType::TCP)
		socketInt = socket(AF_INET, SOCK_STREAM, 0);
	else if(type == TransportLayerType::UDP)
		socketInt = socket(AF_INET, SOCK_DGRAM, 0);
}

void Socket::setInfo(std::uint16_t port)
{
	socketInfo.sin_addr.s_addr = INADDR_ANY;
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons(port);
}

void Socket::connect(std::string ip, std::uint16_t port)
{
	hostent* server = gethostbyname(ip.c_str());
	if(!server)
	{
		bindStatus = false;
		return;
	}
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons(port);

	std::memcpy(&socketInfo.sin_addr.s_addr, server->h_addr, server->h_length);

	bindStatus = ::connect(socketInt, (sockaddr*)&socketInfo, sizeof(sockaddr_in)) >= 0;
}

Socket::operator bool() const
{
	return socketInt >= 0 && bindStatus;
}

void Socket::close()
{
	::close(socketInt);
}
