#include <mov_atom_mvhd.hpp>
#include <mov_io.hpp>

MVHDAtom::MVHDAtom(long long position, long long size)
	: MOVAtom('mvhd', position, size)
{
}

std::shared_ptr<MOVAtom> MVHDAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) MVHDAtom(position, size));
}

bool MVHDAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length() || m_size != 108) { //108  is size of MovieHeader structure
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	m_creationTime = readInteger<unsigned int>(r);
	m_modificationTime = readInteger<unsigned int>(r);
	m_timeScale = readInteger<unsigned int>(r);
	m_duration = readInteger<unsigned int>(r);
	m_preferredRate = readFloat16_16(r);
	m_preferredVolume = readInteger<unsigned short>(r);
	
	for (size_t i = 0; i < 10; ++i) {
		if (r->read(&m_reserved[i], sizeof(m_reserved[i])) != sizeof(m_reserved[i])) {
			return false;
		}
	}

	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; i < 2; ++j) {
			m_matrix[i][j] = readFloat16_16(r);
		}
		m_matrix[i][2] = readFloat2_30(r);
	}

	m_previewTime = readInteger<unsigned int>(r);
	m_previewDuration = readInteger<unsigned int>(r);
	m_posterTime = readInteger<unsigned int>(r);
	m_selectionTime = readInteger<unsigned int>(r);
	m_selectionDuration = readInteger<unsigned int>(r);
	m_currentTime = readInteger<unsigned int>(r);
	m_nextTrackID = readInteger<unsigned int>(r);

	return end == r -> position();
}

unsigned int MVHDAtom::getDuration() const {
	return m_duration;
}

unsigned int MVHDAtom::getTimeScale() const {
	return m_timeScale;
}

