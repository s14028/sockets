#include <unistd.h>
#include "streamSocket.h"

SocketStream::SocketStream(int socketInt) : socketInt(socketInt)
{

}

bool SocketStream::read(unsigned char* array, unsigned int size)
{
	return ::read(socketInt, array, size) >= 0;
}

bool SocketStream::write(unsigned char* array, unsigned int size)
{
	return ::write(socketInt, array, size) >= 0;
}

bool SocketStream::write(const char* array, unsigned int size)
{
	return ::write(socketInt, array, size) >= 0;
}
