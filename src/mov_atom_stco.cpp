/*
 * mov_atom_stco.cpp is part of qtfile++.
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

