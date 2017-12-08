#include <mov_atom_clcp.hpp>
#include <mov_io.hpp>

#include <mov_atom_factory.hpp>

CLCPAtom::CLCPAtom(int id, long long position, long long size)
	: MOVAtom(id, position, size)
{
}

std::shared_ptr<MOVAtom> CLCPAtom::create(int id, long long position, long long size) {
	return std::shared_ptr<MOVAtom>(new (std::nothrow) CLCPAtom(id, position, size));
}

bool CLCPAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) { 
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	unsigned int entries = readInteger<unsigned int>(r);
	unsigned int bytes = static_cast<unsigned int>(m_size - 8 - 4 - 4); //its possible to have cmpl atom, but as arule there is no subatom even thought entries equal to 1

	for (unsigned int i = 0; i < entries && bytes >= 8; ++i) {
		long long pos = r -> position();
		unsigned int size = readInteger<unsigned int>(r);
		int type = readInteger<int>(r);

		std::shared_ptr<MOVAtom> atom = createAtom(type, pos, static_cast<long long>(size));
		if (!atom -> read(r)) {
			return false;
		}

		m_atoms[type] = atom.get();
		m_childs.push_back(atom);
		bytes -= size;
	}

	return end == r -> position();
}

