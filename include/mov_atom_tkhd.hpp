/*
 * mov_atom_tkhd.hpp is part of qtfile++.
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

#ifndef __MOV_ATOM_TKHD_HPP__
#define __MOV_ATOM_TKHD_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>

struct Reader;

struct TKHDAtom : public MOVAtom
{
private:
	TKHDAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
public:
	unsigned int getDuration() const;
	unsigned int getWidth() const;
	unsigned int getHeight() const;
private:
	unsigned int m_creationTime;
	unsigned int m_modificationTime;
	unsigned int m_trackID;
	unsigned int m_reserved0;
	unsigned int m_duration;
	unsigned char m_reserved1[8];

	unsigned short m_layer;
	unsigned short m_alternateGroup;
	unsigned short m_volume;
	unsigned short m_reserved2;

	double m_matrix[3][3];

	unsigned int m_trackWidth;
	unsigned int m_trackHeight;

};

#endif //__MOV_ATOM_TKHD_HPP__
