#include <mov_atom_stsz.hpp>
#include <mov_io.hpp>

STSZAtom::STSZAtom(long long position, long long size)
	: MOVAtom('stsz', position, size)
{
}

std::shared_ptr<MOVAtom> STSZAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) STSZAtom(position, size));
}

bool STSZAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) { 
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	m_sampleSize = readInteger<unsigned int>(r);
	unsigned int entries = readInteger<unsigned int>(r);

	for (unsigned int i = 0; i < entries; ++i) {
		unsigned int size = readInteger<unsigned int>(r);
		m_stsz.push_back(size);
	}

	return end == r -> position();
}

unsigned int STSZAtom::getSampleSize(unsigned int sample) const {
	if (m_sampleSize) {
		return m_sampleSize;
	}

	if (sample >= m_stsz.size()) {
		return 0;
	}

	return m_stsz[sample];
}
