#include <mov_atom_stco.hpp>
#include <mov_io.hpp>

STCOAtom::STCOAtom(int id, long long position, long long size)
	: MOVAtom(id, position, size)
{
}

std::shared_ptr<MOVAtom> STCOAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) STCOAtom(id, position, size));
}

bool STCOAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) { 
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	unsigned int entries = readInteger<unsigned int>(r);

	if (m_id == 'stco') {
		read32(entries, r);
	}
	else {
		read64(entries, r);
	}

	return end == r -> position();
}

long long STCOAtom::getChunkOffset(unsigned int chunk) const {
	if (chunk >= m_stco.size()) {
		return 0;
	}

	return m_stco[chunk];
}

void STCOAtom::read32(unsigned int entries, Reader * r) {
	for (unsigned int i = 0; i < entries; ++i) {
		unsigned int offset = readInteger<unsigned int>(r);
		m_stco.push_back(static_cast<long long>(offset));
	}
}

void STCOAtom::read64(unsigned int entries, Reader * r) {
	for (unsigned int i = 0; i < entries; ++i) {
		long long offset = readInteger<long long>(r);
		m_stco.push_back(static_cast<long long>(offset));
	}
}

