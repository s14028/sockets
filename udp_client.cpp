#include <iostream>
#include "udp_socket.h"
#include <iterator>
#include <algorithm>

int main()
{
	sck::udp_socket soc;
	bool could_bind = soc.bind("127.0.0.1", 10000);

	if(!could_bind)
	{
		std::cout << "Cann't bind." << std::endl;
	}

	std::string message = "Hello";
	soc.write("127.0.0.1", 10001, message);

	auto [IP, port, data] = soc.read(6);

	std::cout << "Recieved packet from " << IP << std::endl;
	std::cout << "Port " << port << std::endl;

	std::cout << "Message" << std::endl;
	std::cout << data << std::endl;

	soc.close();
	return 0;
}
