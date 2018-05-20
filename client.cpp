#include <iostream>
#include "socket.h"
#include "enumTransportLayer.h"
int main()
{
	Socket socket;
	bool couldBind = socket.bind("127.0.0.1", 10000);

	std::cout << std::boolalpha << couldBind << std::endl;

	if(!couldBind)
	{
		return 1;
	}
	std::vector<unsigned char> message = {'H', 'e', 'l', 'l', 'o', '\0'};
	socket << message;
	socket.close();
	return 0;
}
