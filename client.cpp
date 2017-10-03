#include <iostream>
#include "socket.h"
#include "enumTransportLayer.h"
#include "streamSocket.h"

int main()
{
	Socket socket("127.0.0.1", 10001);
	if(!socket)
		return 1;
	SocketStream stream = socket.stream();
	
	stream.write("Hello.", 7);
	return 0;
}
