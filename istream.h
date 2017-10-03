#pragma once
class IStream
{
	virtual bool read(unsigned char*, unsigned int) = 0;
	virtual bool write(unsigned char*, unsigned int) = 0;
	virtual bool write(const char*, unsigned int) = 0;
};
