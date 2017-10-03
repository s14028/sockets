#pragma once
#include "istream.h"

class SocketStream : public IStream
{
	int socketInt;
public:
	SocketStream(int socketInt);

	bool read(unsigned char* array, unsigned int size);
	bool write(unsigned char* array, unsigned int size);
	bool write(const char* array, unsigned int size);
};
