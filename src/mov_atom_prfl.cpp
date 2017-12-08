#include <mov_atom_prfl.hpp>
#include <mov_io.hpp>

PRFLAtom::PRFLAtom(long long position, long long size)
	: MOVAtom('prfl', position, size)
{
}

std::shared_ptr<MOVAtom> PRFLAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) PRFLAtom(position, size));
}

bool PRFLAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) {
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}
	
	unsigned int features = readInteger<unsigned int>(r);

	for (unsigned int i = 0; i < features; ++i) {
		Feature f;
		f.resetved = readInteger<unsigned int>(r);
		f.partID = readInteger<unsigned int>(r);
		f.featureCode = readInteger<unsigned int>(r);
		f.featureValue = readInteger<unsigned int>(r);

		m_features.push_back(f);
	}

	return end == r -> position();
}



