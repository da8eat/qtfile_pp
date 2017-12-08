/*
 * mov_atom_ftyp.cpp is part of qtfile++.
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



