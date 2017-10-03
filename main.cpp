#include "server.h"
#include <iostream>
#include <cstdint>
#include "streamSocket.h"
#include "enumTransportLayer.h"
#include "socket.h"

int main(int argc, char *argv[])
{
	ServerSocket server(10001, TransportLayerType::TCP);
	
	if(!server)
		return 1;

	server.listen(1);
	
	Socket anotherSocket = server.accept();

	SocketStream stream = anotherSocket.stream();

	unsigned char* buffer = new unsigned char[257];
	buffer[256] = '\0';
	stream.read(buffer, 256);
	std::cout << buffer << std::endl;
	server.close();
	return 0;
}
