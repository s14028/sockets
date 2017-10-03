#pragma once
#include <unistd.h>
#include <netinet/in.h>
#include <cstdint>
#include "enumTransportLayer.h"
#include "socket.h"

class ServerSocket : public Socket
{
public:
	ServerSocket(std::uint16_t port, const TransportLayerType& type);

	void listen(std::uint16_t maxConnection);

	Socket accept();
};
