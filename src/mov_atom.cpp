#include <mov_atom.hpp>
#include <mov_io.hpp>

MOVAtom::MOVAtom(int id, long long position, long long size)
	: m_id(id)
	, m_position(position)
	, m_size(size)
{

}

int MOVAtom::id() const {
	return m_id;
}

long long MOVAtom::position() const {
	return m_position;
}

long long MOVAtom::size() const {
	return m_size;
}

const unsigned char * MOVAtom::data() const { //if we have not implemented or unknown atom it will be read to the memory
	
	return m_data.data();
}

bool MOVAtom::read(Reader * r) {
	unsigned int size = static_cast<unsigned int>(m_size - 8); //8 bytes for size and id

	m_data.resize(size);
	return r -> read(m_data.data(), size) == size;
}

bool MOVAtom::readVersionAndFlags(Reader * r) {
	if (r -> read(&m_version, sizeof(m_version)) != sizeof(m_version)) {
		return false;
	}

	for (size_t i = 0; i < 3; ++i) {
		if (r -> read(&m_flags[i], sizeof(m_flags[i])) != sizeof(m_flags[i])) {
			return false;
		}
	}

	return true;
}

MOVAtom * MOVAtom::getChild(int id) const {
	auto atom = m_atoms.find(id);

	if (atom == m_atoms.end()) {
		return 0;
	}

	return atom -> second;
}

