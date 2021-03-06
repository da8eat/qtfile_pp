/*
 * mov_atom_elst.cpp is part of qtfile++.
 *
 * Copyright (C) 2017 -  Alex Mogurenko <alex@mogurenko.com>
 *
 * qtfile++ is open source library: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * qtfile++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with qtfile++.  If not, see <http://www.gnu.org/licenses/>
 */

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



