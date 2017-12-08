#include <mov_atom_elst.hpp>
#include <mov_io.hpp>

ELSTAtom::ELSTAtom(long long position, long long size)
	: MOVAtom('elst', position, size)
{
}

std::shared_ptr<MOVAtom> ELSTAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) ELSTAtom(position, size));
}

bool ELSTAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) {
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}
	
	unsigned int entries = readInteger<unsigned int>(r);

	for (unsigned int i = 0; i < entries; ++i) {
		EditEntry e;
		e.duration = readInteger<unsigned int>(r);
		e.time = readInteger<unsigned int>(r);
		e.rate = readFloat16_16(r);

		m_entries.push_back(e);
	}

	return end == r -> position();
}

size_t ELSTAtom::entries() const {
	return m_entries.size();
}
unsigned int ELSTAtom::entryDuration(size_t index) const {
	if (index >= m_entries.size()) {
		return 0;
	}

	return m_entries[index].duration;
}
unsigned int ELSTAtom::entryTime(size_t index) const {
	if (index >= m_entries.size()) {
		return 0;
	}

	return m_entries[index].time;
}
double ELSTAtom::entryRate(size_t index) const {
	if (index >= m_entries.size()) {
		return 0;
	}

	return m_entries[index].rate;
}



