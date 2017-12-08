/*
 * mov_atom_elst.hpp is part of qtfile++.
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

#ifndef __MOV_ATOM_ELST_HPP__
#define __MOV_ATOM_ELST_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>

struct Reader;

struct ELSTAtom : public MOVAtom
{
private:
	ELSTAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);

	size_t entries() const;
	unsigned int entryDuration(size_t index) const;
	unsigned int entryTime(size_t index) const;
	double entryRate(size_t index) const;
private:
	struct EditEntry
	{
		unsigned int duration;
		unsigned int time;
		double rate;
	};
private:
	std::vector<EditEntry> m_entries;
};

#endif //__MOV_ATOM_ELST_HPP__
