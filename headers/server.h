#pragma once
#include <optional>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdint>
#include "socket.h"

namespace sck
{
class server_socket : public virtual socket
{
public:
	server_socket() = default;
	server_socket(const server_socket& server) = default;
	server_socket(server_socket&& server) = default;

	bool listen(std::uint16_t max_connections);
	std::optional<socket> accept();
	virtual bool bind(const std::string IP, const std::uint16_t port);
};
}
