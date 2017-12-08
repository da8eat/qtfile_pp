/*
 * mov_atom_mdat.cpp is part of qtfile++.
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

#include <mov_atom_mdat.hpp>
#include <mov_io.hpp>

MDATAtom::MDATAtom(long long position, long long size)
	: MOVAtom('mdat', position, size)
	, m_extendedSize(false)
{
}

std::shared_ptr<MOVAtom> MDATAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) MDATAtom(position, size));
}

//we dont read mdat becase its whole raw mediadata of file, we just skip it in case mdat followed by other atoms need to be read
bool MDATAtom::read(Reader * r) {
	long long position = r -> position();

	m_extendedSize = (position - m_position) == 16;

	if (m_size == 0) { //it means current atom takes rest of file
	
		m_size = r -> length() - m_position;
	}

	long long end = m_size + m_position;

	r -> seek(end);
	return end == r -> position();
}

WIDEAtom::WIDEAtom(long long position, long long size)
	: MOVAtom('wide', position, size)
{
}

std::shared_ptr<MOVAtom> WIDEAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) WIDEAtom(position, size));
}

//should be 8 bytes
bool WIDEAtom::read(Reader * r) {
	if (m_size != 8) {
		return false;
	}

	long long end = m_size + m_position;

	r -> seek(end);
	return end == r -> position();
}



