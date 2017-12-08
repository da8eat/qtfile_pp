/*
 * mov_file_io.hpp is part of qtfile++.
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

#ifndef __MOV_FILE_IO_HPP__
#define __MOV_FILE_IO_HPP__

#include <string>
#include <memory>

#if defined(_WIN32)
typedef std::wstring mov_string;
#else
typedef std::string mov_string;
#endif

struct Reader;

std::shared_ptr<Reader> createReader(const mov_string & path);


#endif //__MOV_FILE_IO_HPP__
