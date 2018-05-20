#pragma once
#include <vector>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdint>
#include <cstring>
#include <string>
#include "enumTransportLayer.h"

class Socket
{
	friend class ServerSocket;
protected:
	int socketInt;

public:
	Socket();
	Socket(const Socket& anotherSocket);
	Socket(Socket&& socket);

protected:
	bool accept(int server);
	void setSocket(const TransportLayerType& type);
	void setInfo(sockaddr_in& socketInfo, const std::uint16_t port);
	bool bind(sockaddr_in& socketInfo, const std::string IP, const std::uint16_t port, const TransportLayerType& type = TransportLayerType::TCP);
	int getSocketInt();

public:
	Socket& operator<<(std::vector<unsigned char>& bytes);
	Socket& operator>>(std::vector<unsigned char>& bytes);
	virtual bool bind(const std::string IP, const std::uint16_t port, const TransportLayerType& type = TransportLayerType::TCP);
	virtual operator bool() const;
	void close();

};