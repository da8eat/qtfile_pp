/*
 * mov_io.cpp is part of qtfile++.
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

#include <mov_io.hpp>

double readFloat16_16(Reader * r) {
	unsigned int v = readInteger<unsigned int>(r);

	return static_cast<double>(v >> 16) + static_cast<double>(v & 0xffff) / (1 << 16);
}

double readFloat2_30(Reader * r) {
	unsigned int v = readInteger<unsigned int>(r);

	return static_cast<double>(v >> 30) + static_cast<double>(v & 0x3fffffff) / (1 << 30);
}

double readFloat8_8(Reader * r) {
	short v = readInteger<short>(r);

	return static_cast<double>(v >> 8) + static_cast<double>(v & 0xff) / (1 << 8);
}

std::string readCountedString(Reader * r) {
	unsigned char size = 0;
	r -> read(&size, 1);

	char buffer[256] = { 0 };

	if (size) {
		r -> read(buffer, size);
	}

	return std::string(buffer);
}
