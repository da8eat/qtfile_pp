/*
 * mov_atom_free.cpp is part of qtfile++.
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

#include <mov_atom_free.hpp>
#include <mov_io.hpp>

FREEAtom::FREEAtom(long long position, long long size)
	: MOVAtom('free', position, size)
{
}

std::shared_ptr<MOVAtom> FREEAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) FREEAtom(position, size));
}

//we dont read mdat becase its just padding
bool FREEAtom::read(Reader * r) {
	if (m_size == 0) { //it means current atom takes rest of file
	
		m_size = r -> length() - m_position;
	}

	long long end = m_size + m_position;

	r -> seek(end);
	return end == r -> position();
}

SKIPAtom::SKIPAtom(long long position, long long size)
	: MOVAtom('skip', position, size)
{
}

std::shared_ptr<MOVAtom> SKIPAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) SKIPAtom(position, size));
}

//we dont read mdat becase its just padding
bool SKIPAtom::read(Reader * r) {
	if (m_size == 0) { //it means current atom takes rest of file

		m_size = r -> length() - m_position;
	}

	long long end = m_size + m_position;

	r -> seek(end);
	return end == r -> position();
}



