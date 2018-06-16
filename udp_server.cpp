#include <iostream>
#include "udp_socket.h"
#include <iterator>
#include <algorithm>

int main()
{
	sck::udp_socket soc;
	bool could_bind = soc.bind("127.0.0.1", 10001);

	if(!could_bind)
	{
		std::cout << "Cann't bind." << std::endl;
	}

	auto [IP, port, data] = soc.read(1024);

	std::cout << "Recieved packet from " << IP << std::endl;
	std::cout << "Port " << port << std::endl;

	std::cout << "Message" << std::endl;
	std::cout << data << std::endl;

	soc.write(IP, port, data);
	return 0;
}
