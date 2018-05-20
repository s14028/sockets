#include "server.h"
#include <iostream>
#include <cstdint>
#include "enumTransportLayer.h"
#include "socket.h"

int main(int argc, char *argv[])
{
	ServerSocket server;

	bool couldBind = server.bind("127.0.0.1", 10000);
	std::cout << std::boolalpha << couldBind << std::endl;

	if(!couldBind)
	{
		return 1;
	}

	bool couldListen = server.listen(1);

	std::cout << couldListen << std::endl;
	if(!couldListen)
	{
		return 1;
	}
	
	std::optional<Socket> anotherSocket = server.accept();

	if(!anotherSocket)
	{
		std::cout << "Can't recieve socket." << std::endl;
		return 0;
	}
	Socket socket = *anotherSocket;
	std::vector<unsigned char> message(255);
	socket >> message;
	std::cout << static_cast<unsigned char*>(&message.front()) << std::endl;
	socket.close();
	server.close();
	return 0;
}
