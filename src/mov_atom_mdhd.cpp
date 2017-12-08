#include <mov_atom_mdhd.hpp>
#include <mov_io.hpp>

MDHDAtom::MDHDAtom(long long position, long long size)
	: MOVAtom('mdhd', position, size)
{
}

std::shared_ptr<MOVAtom> MDHDAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) MDHDAtom(position, size));
}

bool MDHDAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length() || m_size != 32) { //92  is size of TrakHeader structure
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	m_creationTime = readInteger<unsigned int>(r);
	m_modificationTime = readInteger<unsigned int>(r);
	m_timeScale = readInteger<unsigned int>(r);
	m_duration = readInteger<unsigned int>(r);

	m_language = readInteger<unsigned short>(r);
	m_quolity = readInteger<unsigned short>(r);

	return end == r -> position();
}

unsigned int MDHDAtom::getDuration() const {
	return m_duration;
}

unsigned int MDHDAtom::getTimeScale() const {
	return m_timeScale;
}


