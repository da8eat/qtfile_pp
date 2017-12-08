#include <mov_atom_tkhd.hpp>
#include <mov_io.hpp>

TKHDAtom::TKHDAtom(long long position, long long size)
	: MOVAtom('tkhd', position, size)
{
}

std::shared_ptr<MOVAtom> TKHDAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) TKHDAtom(position, size));
}

bool TKHDAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length() || m_size != 92) { //92  is size of TrakHeader structure
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	m_creationTime = readInteger<unsigned int>(r);
	m_modificationTime = readInteger<unsigned int>(r);
	m_trackID = readInteger<unsigned int>(r);
	m_reserved0 = readInteger<unsigned int>(r);
	m_duration = readInteger<unsigned int>(r);
	
	for (size_t i = 0; i < 8; ++i) {
		if (r->read(&m_reserved1[i], sizeof(m_reserved1[i])) != sizeof(m_reserved1[i])) {
			return false;
		}
	}

	m_layer = readInteger<unsigned short>(r);
	m_alternateGroup = readInteger<unsigned short>(r);
	m_volume = readInteger<unsigned short>(r);
	m_reserved2 = readInteger<unsigned short>(r);

	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; i < 2; ++j) {
			m_matrix[i][j] = readFloat16_16(r);
		}
		m_matrix[i][2] = readFloat2_30(r);
	}

	m_trackWidth = readInteger<unsigned int>(r);
	m_trackHeight = readInteger<unsigned int>(r);

	return end == r -> position();
}

unsigned int TKHDAtom::getDuration() const {
	return m_duration;
}
unsigned int TKHDAtom::getWidth() const {
	return m_trackWidth;
}
unsigned int TKHDAtom::getHeight() const {
	return m_trackHeight;
}

