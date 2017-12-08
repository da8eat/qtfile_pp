/*
 * mov_atom_factory.hpp is part of qtfile++.
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

#ifndef __MOV_ATOM_FACTORY_HPP__
#define __MOV_ATOM_FACTORY_HPP__

#include <memory>

struct MOVAtom;
std::shared_ptr<MOVAtom> createAtom(int id, long long position, long long size);
std::shared_ptr<MOVAtom> createStsdSubAtom(int id, long long position, long long size);

#endif //__MOV_ATOM_FACTORY_HPP__
