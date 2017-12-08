/*
 * mov_atom_stsc.hpp is part of qtfile++.
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

#ifndef __MOV_ATOM_STSC_HPP__
#define __MOV_ATOM_STSC_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>
#include <utility>

struct Reader;

struct STSCAtom : public MOVAtom
{
public:
	struct STSCTable {
		unsigned int firstSample;
		unsigned int samples;
		unsigned int id;
	};
private:
	STSCAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
public:
	//first - chunk number, second - first frame in chunk
	std::pair<unsigned int, unsigned int> getChunkNumber(unsigned int sample) const;
private:
	std::vector<STSCTable> m_stsc; //we need it fo find duration
	std::vector<unsigned int> m_offset;
};

#endif //__MOV_ATOM_STSC_HPP__
