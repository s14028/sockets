#pragma once
#include <vector>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdint>
#include <cstring>
#include <string>

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
	virtual void setSocket();
	void setInfo(sockaddr_in& socketInfo, const std::uint16_t port);
	bool bind(sockaddr_in& socketInfo, const std::string IP, const std::uint16_t port);
	int getSocketInt();

public:
	Socket& operator<<(std::vector<unsigned char>& bytes);
	Socket& operator>>(std::vector<unsigned char>& bytes);
	virtual bool connect(const std::string IP, const std::uint16_t port);
	virtual operator bool() const;
	void close();
};
