#pragma once
#include <unistd.h>
#include <netinet/in.h>
#include <cstdint>
#include <cstring>
#include <string>
#include "streamSocket.h"
#include "enumTransportLayer.h"

class Socket
{
public:
	sockaddr_in socketInfo;
	bool bindStatus;
	int socketInt;


	Socket(std::uint16_t port, const TransportLayerType& type);

	Socket(const Socket& anotherSocket);

	Socket();
	
	Socket(std::string ip, std::uint16_t port, const TransportLayerType& type = TransportLayerType::TCP);

	SocketStream stream();

	virtual operator bool() const;

	void close();
	bool accept(int server);


	void setSocket(const TransportLayerType& type);

	void setInfo(std::uint16_t port);

	void connect(std::string ip, std::uint16_t port);
};
