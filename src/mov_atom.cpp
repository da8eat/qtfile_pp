/*
 * mov_atom.cpp is part of qtfile++.
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

