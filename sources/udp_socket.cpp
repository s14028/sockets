#include "udp_socket.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

UDPSocket::UDPSocket()
{
}

void UDPSocket::setSocket()
{
	socketInt = socket(AF_INET, SOCK_DGRAM, 0);
}

bool UDPSocket::bind(const std::string IP, const std::uint16_t port)
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

bool UDPSocket::write(const std::string IP, const std::uint16_t port, std::vector<unsigned char>& bytes)
{
	unsigned char* array = static_cast<unsigned char*>(&bytes.front());
	unsigned int size = bytes.size();

	sockaddr_in socketInfo;
	std::memset(&socketInfo, 0, sizeof(sockaddr_in));

	hostent* address = gethostbyname(IP.c_str());

	if(!address)
	{
		return false;
	}

	std::memcpy(&socketInfo.sin_addr.s_addr, address->h_addr, address->h_length);
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons(port);

	sendto(socketInt, array, size, 0, (struct sockaddr*) &socketInfo, sizeof(sockaddr_in));
	return true;
}

std::tuple<const std::string, const std::uint16_t, std::vector<unsigned char>> UDPSocket::read(const unsigned int size)
{
	std::vector<unsigned char> bytes(size + 1);
	unsigned char* array = static_cast<unsigned char*>(&bytes.front());
	unsigned int sa_size = sizeof(sockaddr_in);

	sockaddr_in socketInfo;
	std::memset(&socketInfo, 0, sa_size);

	recvfrom(socketInt, array, size, 0, (struct sockaddr*) &socketInfo, &sa_size);
	bytes[size] = '\0';
	
	std::string IP = inet_ntoa(socketInfo.sin_addr);
	std::uint16_t port = ntohs(socketInfo.sin_port);

	return std::make_tuple(IP, port, bytes);
}
