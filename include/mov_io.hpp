/*
 * mov_io.hpp is part of qtfile++.
 *
 * Copyright (C) 2017 -  Alex Mogurenko <alex@mogurenko.com>
 *
 * qtfile++ is open source library: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * qtfile++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with qtfile++.  If not, see <http://www.gnu.org/licenses/>
 */

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
