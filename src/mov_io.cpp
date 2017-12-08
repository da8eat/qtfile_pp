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
