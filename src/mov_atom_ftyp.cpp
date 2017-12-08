#include <mov_atom_ftyp.hpp>
#include <mov_io.hpp>

FTYPAtom::FTYPAtom(long long position, long long size)
	: MOVAtom('ftyp', position, size)
{
}

std::shared_ptr<MOVAtom> FTYPAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) FTYPAtom(position, size));
}

bool FTYPAtom::read(Reader * r) {
	long long end = m_size + m_position;

	//should be at least major and minor brands as all fields are 32bit integers size whould be double word aligned
	// all ftyps i saw were 32 bytes size but qtff not quite clear about it
	if (end > r -> length() || m_size < 16 || (m_size & 3)) {
		return false;
	}
	
	m_majorBrand = readInteger<int>(r);
	m_minorBrand = readInteger<int>(r);

	unsigned int rest = static_cast<unsigned int>(m_size - 16);

	for (unsigned int i = 0; i < rest / 4; ++i) {
		int brand = readInteger<int>(r);
		m_compatibleBrands.push_back(brand);
	}


	return end == r -> position();
}



