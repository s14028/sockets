#pragma once
#include <optional>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdint>
#include "enumTransportLayer.h"
#include "socket.h"

class ServerSocket : public Socket
{
public:
	ServerSocket();

	bool listen(std::uint16_t maxConnection);
	std::optional<Socket> accept();
	virtual bool bind(const std::string IP, const std::uint16_t port, const TransportLayerType& type = TransportLayerType::TCP);
};
