/*
 * mov_atom_stsz.hpp is part of qtfile++.
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

#ifndef __MOV_ATOM_STSZ_HPP__
#define __MOV_ATOM_STSZ_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>
#include <utility>

struct Reader;

struct STSZAtom : public MOVAtom
{
private:
	STSZAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
public:
	unsigned int getSampleSize(unsigned int sample) const;
private:
	unsigned int m_sampleSize;
	std::vector<unsigned int> m_stsz; //we need it fo find duration
};

#endif //__MOV_ATOM_STSZ_HPP__
