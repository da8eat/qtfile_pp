/*
 * mov_file.hpp is part of qtfile++.
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

#ifndef __MOV_FILE_HPP__
#define __MOV_FILE_HPP__

#include <memory>
#include "mov_defs.hpp"

struct Reader;
struct MOVAtom;

struct MOVFile
{
public:
	bool open(const mov_string & path);
public:
	size_t tracksCount() const;
	size_t samplesCount(size_t trackIndex) const;
	size_t sampleSize(size_t trackIndex, size_t sampleIndex) const;
	size_t syncPointLeft(size_t trackIndex, size_t sampleIndex) const; //closest sync frame to sampleIndex, from rannge: [0..sampleIndex] or -1 if not found
	size_t syncPointRight(size_t trackIndex, size_t sampleIndex) const; //closest sync frame to sampleIndex, from rannge: [sampleIndex..samplesCount()) or -1 if not found

	int getTrackType(size_t trackIndex) const; //check list of possible types in mov_defs.hpp
	
	Timecode getSampleTimecode(size_t trackIndex, size_t sampleIndex) const;
	Timecode getSampleDuration(size_t trackIndex, size_t sampleIndex) const;

	bool readSample(size_t trackIndex, size_t sampleIndex, void * buffer);

	std::shared_ptr<VideoInfo> getVideoInfo(size_t trackIndex) const; //track index value from range: [0..tracksCount())
	std::shared_ptr<AudioInfo> getAudioInfo(size_t trackIndex) const; //track index value from range: [0..tracksCount())
	std::shared_ptr<CaptionsInfo> getCaptionsInfo(size_t trackIndex) const; //track index value from range: [0..tracksCount())
	std::shared_ptr<TimecodeInfo> getTimecodeInfo(size_t trackIndex) const; //track index value from range: [0..tracksCount())
private:
	std::shared_ptr<MOVAtom> m_root;
	std::shared_ptr<Reader> m_reader;
};

#endif //__MOV_FILE_HPP__
