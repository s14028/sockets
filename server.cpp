#include "server.h"
#include <iostream>
#include <cstdint>
#include "socket.h"

int main(int argc, char *argv[])
{
	sck::server_socket server;

	bool could_bind = server.bind("127.0.0.1", 10000);
	std::cout << std::boolalpha << could_bind << std::endl;

	if(!could_bind)
	{
		return 1;
	}

	bool could_listen = server.listen(1);

	std::cout << could_listen << std::endl;
	if(!could_listen)
	{
		return 1;
	}
	
	std::optional<sck::socket> soc = server.accept();

	if(!soc)
	{
		std::cout << "Can't recieve socket." << std::endl;
		return 0;
	}
	sck::socket s = *soc;
	
	std::string message = s.read(256);
	std::cout << message << std::endl;

	s.close();
	server.close();
	return 0;
}
