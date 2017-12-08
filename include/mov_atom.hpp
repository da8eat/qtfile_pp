/*
 * mov_atom.hpp is part of qtfile++.
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

#ifndef __MOV_ATOM_HPP__
#define __MOV_ATOM_HPP__

#include <vector>
#include <map>
#include <memory>

struct Reader;

struct MOVAtom
{
public:
	MOVAtom(int id, long long position, long long size);
public:
	int id() const;
	long long position() const;
	long long size() const;

	const unsigned char * data() const; //if we have not implemented or unknown atom it will be read to the memory
	virtual bool read(Reader * r);
	MOVAtom * getChild(int id) const;
protected:
	bool readVersionAndFlags(Reader * r);
protected:
	int m_id;
	long long m_position;
	long long m_size;

	//will be presented in most atoms
	unsigned char m_version;
	unsigned char m_flags[3];

	std::vector<unsigned char> m_data;
	std::vector<std::shared_ptr<MOVAtom> > m_childs;
	std::map<int, MOVAtom *> m_atoms; //we can use hash map, but frankly in almost all cases there will be max 3-5 atoms

};

#endif //__MOV_ATOM_HPP__
