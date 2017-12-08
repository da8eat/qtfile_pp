/*
 * mov_atom_mdhd.cpp is part of qtfile++.
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

#include <mov_atom_mdhd.hpp>
#include <mov_io.hpp>

MDHDAtom::MDHDAtom(long long position, long long size)
	: MOVAtom('mdhd', position, size)
{
}

std::shared_ptr<MOVAtom> MDHDAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) MDHDAtom(position, size));
}

bool MDHDAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length() || m_size != 32) { //92  is size of TrakHeader structure
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	m_creationTime = readInteger<unsigned int>(r);
	m_modificationTime = readInteger<unsigned int>(r);
	m_timeScale = readInteger<unsigned int>(r);
	m_duration = readInteger<unsigned int>(r);

	m_language = readInteger<unsigned short>(r);
	m_quolity = readInteger<unsigned short>(r);

	return end == r -> position();
}

unsigned int MDHDAtom::getDuration() const {
	return m_duration;
}

unsigned int MDHDAtom::getTimeScale() const {
	return m_timeScale;
}


