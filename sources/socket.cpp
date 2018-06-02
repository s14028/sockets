#include "socket.h"
#include <string>
#include <cstdint>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

Socket::Socket()
{
}

Socket::Socket(const Socket& anotherSocket)
{
	this->socketInt = anotherSocket.socketInt;
}

Socket::Socket(Socket&& anotherSocket)
{
	this->socketInt = std::move(anotherSocket.socketInt);
	anotherSocket.socketInt = -1;
}
	
bool Socket::accept(int server)
{
	sockaddr_in socketInfo;
	socklen_t clientLength = sizeof(sockaddr_in);
	int status = ::accept(server, (sockaddr*)&socketInfo, &clientLength);
	if(status < 0)
	{
		return false;
	}

	socketInt = status;
	return true;
}


void Socket::setSocket()
{
	socketInt = socket(AF_INET, SOCK_STREAM, 0);
}

void Socket::setInfo(sockaddr_in& socketInfo, const std::uint16_t port)
{
	socketInfo.sin_family = AF_INET;
	socketInfo.sin_port = htons(port);
}

bool Socket::bind(sockaddr_in& socketInfo, const std::string IP, const std::uint16_t port)
{
	hostent* address = gethostbyname(IP.c_str());
	if(!address)
	{
		return false;
	}

	std::memcpy(&socketInfo.sin_addr.s_addr, address->h_addr, address->h_length);
	setInfo(socketInfo, port);
	setSocket();
	return socketInt >= 0;
}

bool Socket::connect(const std::string IP, const std::uint16_t port)
{
	sockaddr_in socketInfo;
	std::memset(&socketInfo, 0, sizeof(sockaddr_in));
	bool couldBind = bind(socketInfo, IP, port);

	if(!couldBind)
	{
		return false;
	}
	return ::connect(socketInt, (sockaddr*)&socketInfo, sizeof(sockaddr_in)) == 0;
}

int Socket::getSocketInt()
{
	return socketInt;
}

Socket::operator bool() const
{
	return socketInt >= 0;
}


void Socket::close()
{
	::close(socketInt);
}

Socket& Socket::operator<<(std::vector<unsigned char>& bytes)
{
	unsigned char* array = static_cast<unsigned char*>(&bytes.front());
	unsigned int size = bytes.size();
	int wroteBytes = ::write(socketInt, array, size);

	bytes[wroteBytes] = '\0';
	return *this;
}

Socket& Socket::operator>>(std::vector<unsigned char>& bytes)
{
	unsigned char* array = static_cast<unsigned char*>(&bytes.front());
	unsigned int size = bytes.capacity();
	unsigned int readBytes = ::read(socketInt, array, size);

	bytes.push_back('\0');
	return *this;
}
