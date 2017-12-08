#ifndef __MOV_IO_HPP__
#define __MOV_IO_HPP__

#include <cassert>
#include <algorithm>
#include <string>

struct Reader
{
	virtual unsigned int read(void * buffer, unsigned int size) const = 0;
	virtual long long position() const = 0;
	virtual long long length() const = 0;
	virtual void seek(long long pos) const = 0;
	virtual bool eof() const = 0;
};

template <class T>
T readInteger(Reader * r) {
	T res = 0;
	unsigned int size = r -> read(&res, sizeof(T));
	assert(size == sizeof(T));

	unsigned char * buff = reinterpret_cast<unsigned char *>(&res);

	for (unsigned int i = 0; i < size / 2; ++i)
	{
		std::swap(buff[i], buff[sizeof(T) - i - 1]);
	}

	return res;
}

double readFloat16_16(Reader * r);
double readFloat2_30(Reader * r);
double readFloat8_8(Reader * r);
std::string readCountedString(Reader * r);

#endif //__MOV_IO_HPP__
