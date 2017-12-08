/*
 * mov_atom_moov.hpp is part of qtfile++.
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

#ifndef __MOV_ATOM_MOOV_HPP__
#define __MOV_ATOM_MOOV_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>
#include <unordered_map>

struct Reader;

struct MOOVAtom : public MOVAtom
{
private:
	MOOVAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
	MOVAtom * getTrack(size_t index); //get track by index, index starts from 0 tracks stored in same order stored in file
	size_t tracksCount() const;
private:
	std::vector<MOVAtom *> m_tracks;
};

#endif //__MOV_ATOM_MOOV_HPP__
