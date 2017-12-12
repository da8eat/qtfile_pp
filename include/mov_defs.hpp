/*
 * mov_defs.hpp is part of qtfile++.
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

#ifndef __MOV_DEFS_HPP__
#define __MOV_DEFS_HPP__

#include <string>

#if defined(_WIN32)
typedef std::wstring mov_string;
#else
typedef std::string mov_string;
#endif

struct TrackType {
	enum {
		Video,
		Audio,
		Captions,
		Timecode,
		Unknown //technically not implemented
	};
};

struct VideoInfo {

};

struct AudioInfo {

};

struct CaptionsInfo {

};

struct TimecodeInfo {

};

struct Timecode {
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	unsigned int frame;

	int dropFlag;
};

#endif //__MOV_FILE_IO_HPP__
