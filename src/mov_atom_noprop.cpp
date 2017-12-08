#include <mov_atom_noprop.hpp>
#include <mov_io.hpp>
#include <mov_atom_factory.hpp>

NOPROPAtom::NOPROPAtom(int id, long long position, long long size)
	: MOVAtom(id, position, size)
{
}

std::shared_ptr<MOVAtom> NOPROPAtom::create(int id, long long position, long long size) {
	return std::shared_ptr<MOVAtom>(new (std::nothrow) NOPROPAtom(id, position, size));
}

bool NOPROPAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) {
		return false;
	}

	unsigned int bytes = static_cast<unsigned int>(m_size - 8); //minus moov size and moov id

	while (bytes >= 8 && !r -> eof()) {//enough to store atom

		long long pos = r -> position();
		unsigned int size = readInteger<unsigned int>(r); //dont think we should ever check for extended size e.g. size > 2^32 as its possible only with mdat atom which top level atom
		int type = readInteger<int>(r);

		std::shared_ptr<MOVAtom> atom = createAtom(type, pos, static_cast<long long>(size));
		if (!atom -> read(r)) {
			return false; //we dont clean up container so we can analyze which exactly atom breaks structure and if possible to repair file
		}

		m_atoms[type] = atom.get(); //we dont really care if any atom duplicated (like free) main purpose to store atoms that has some needed info and mostly its unique atoms if not it will be handled like track case
		m_childs.push_back(atom);
		bytes -= size;
	}

	if (bytes) {
		return false;
	}
	
	return end == r -> position();
}


