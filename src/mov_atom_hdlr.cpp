/*
 * mov_atom_hdlr.cpp is part of qtfile++.
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

#include <mov_atom_hdlr.hpp>
#include <mov_io.hpp>

HDLRAtom::HDLRAtom(long long position, long long size)
	: MOVAtom('hdlr', position, size)
{
}

std::shared_ptr<MOVAtom> HDLRAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) HDLRAtom(position, size));
}

bool HDLRAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) { 
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	m_type = readInteger<int>(r);
	m_subtype = readInteger<int>(r);
	m_manufacturer = readInteger<unsigned int>(r);
	m_flags = readInteger<unsigned int>(r);
	m_mask = readInteger<unsigned int>(r);
	
	m_name = readCountedString(r);

	

	return end == r -> position();
}

int HDLRAtom::getType() const {
	return m_type;
}

int HDLRAtom::getSubType() const {
	return m_subtype;
}

std::string HDLRAtom::getName() const {
	return m_name;
}

