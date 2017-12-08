#include <mov_atom_tmcddata.hpp>
#include <mov_io.hpp>

#include <mov_atom_factory.hpp>

TMCDDataAtom::TMCDDataAtom(long long position, long long size)
	: MOVAtom('tmcd', position, size)
{
}

std::shared_ptr<MOVAtom> TMCDDataAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) TMCDDataAtom(position, size));
}

bool TMCDDataAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) { 
		return false;
	}

	for (int i = 0; i < 6; ++i) {//flags 
		r -> read(&m_reserved0[0], 1);
	}

	m_dataRefIdx = readInteger<unsigned short>(r);
	m_reserved1 = readInteger<unsigned int>(r);
	m_dropFlag = readInteger<unsigned int>(r);
	m_timeScale = readInteger<unsigned int>(r);
	m_frameDuration = readInteger<unsigned int>(r);
	
	r -> read(&m_timebase, 1);
	r -> read(&m_reserved2, 1);
	
	unsigned int bytes = static_cast<unsigned int>(m_size - 8 - 6 - 2 - 4 - 4 - 4 - 4 - 1 - 1);// its possible extra atom follows like Name

	while (bytes >= 8)
	{
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

unsigned int TMCDDataAtom::dropFrame() const {
	return m_dropFlag;
}

unsigned int TMCDDataAtom::timeScale() const {
	return m_timeScale;
}

unsigned int TMCDDataAtom::fameDuration() const {
	return m_frameDuration;
}

unsigned int TMCDDataAtom::timeBase() const {
	return m_timebase;
}

