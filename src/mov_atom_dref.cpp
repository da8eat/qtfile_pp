/*
 * mov_atom_dref.cpp is part of qtfile++.
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

#include <mov_atom_dref.hpp>
#include <mov_io.hpp>

#include <mov_atom_factory.hpp>

DREFAtom::DREFAtom(long long position, long long size)
	: MOVAtom('dref', position, size)
{
}

std::shared_ptr<MOVAtom> DREFAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) DREFAtom(position, size));
}

bool DREFAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) {
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}
	
	unsigned int bytes = static_cast<unsigned int>(m_size - 8 - 4 - 4);//size, type version, flags and entries count
	unsigned int entries = readInteger<unsigned int>(r);

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



