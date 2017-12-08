/*
 * mov_atom_mhd.hpp is part of qtfile++.
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

#ifndef __MOV_ATOM_MHD_HPP__
#define __MOV_ATOM_MHD_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>

struct Reader;

struct VMHDAtom : public MOVAtom
{
private:
	VMHDAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
private:
	unsigned short m_graphicsMode;
	unsigned short m_opcolorRed;
	unsigned short m_opcolorGreen;
	unsigned short m_opcolorBlue;
};

struct SMHDAtom : public MOVAtom
{
private:
	SMHDAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
private:
	double m_balance; //float8.8
	unsigned short m_reserved;
};

struct GMINAtom : public MOVAtom
{
private:
	GMINAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
private:
	unsigned short m_graphicsMode;
	unsigned short m_opcolorRed;
	unsigned short m_opcolorGreen;
	unsigned short m_opcolorBlue;

	double m_balance; //float8.8
	unsigned short m_reserved;
};

#endif //__MOV_ATOM_MHD_HPP__
