#include <iostream>
#include "socket.h"
#include "enumTransportLayer.h"
int main()
{
	Socket socket;
	bool couldConnect = socket.connect("127.0.0.1", 10000);

	std::cout << std::boolalpha << couldConnect << std::endl;

	if(!couldConnect)
	{
		return 1;
	}
	std::vector<unsigned char> message = {'H', 'e', 'l', 'l', 'o', '\0'};
	socket << message;
	socket.close();
	return 0;
}
