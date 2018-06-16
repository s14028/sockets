#include <iostream>
#include "socket.h"
int main()
{
	sck::socket soc;
	bool could_connect = soc.connect("127.0.0.1", 10000);

	std::cout << std::boolalpha << could_connect << std::endl;

	if(!could_connect)
	{
		return 1;
	}
	std::string message = "Hello";
	soc.write(message);
	soc.close();

	return 0;
}
