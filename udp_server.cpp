#include <iostream>
#include "udp_socket.h"
#include <iterator>
#include <algorithm>

int main()
{
	UDPSocket socket;
	bool couldBind = socket.bind("127.0.0.1", 10001);

	if(!couldBind)
	{
		std::cout << "Cann't bind." << std::endl;
	}

	auto [IP, port, data] = socket.read(1024);

	std::cout << "Recieved packet from " << IP << std::endl;
	std::cout << "Port " << port << std::endl;

	std::cout << "Message" << std::endl;
	std::copy(std::begin(data), std::end(data), std::ostream_iterator<char>(std::cout, ""));
	std::cout << std::endl;

	socket.write(IP, port, data);
	return 0;
}
