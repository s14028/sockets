#include "server.h"
#include "socket.h"
#include <cstdint>
#include <unistd.h>
#include <netinet/in.h>
#include "enumTransportLayer.h"


ServerSocket::ServerSocket(std::uint16_t port, const TransportLayerType& type) : Socket(port, type)
{
	int status = bind(socketInt, (sockaddr*)&socketInfo, sizeof(sockaddr_in));
	bindStatus = status >= 0;
}

void ServerSocket::listen(std::uint16_t maxConnection)
{
	::listen(socketInt, maxConnection);
}

Socket ServerSocket::accept()
{
	Socket client;
	bool status = client.accept(socketInt);

	if(!status)
		throw 1;

	return client;
}
