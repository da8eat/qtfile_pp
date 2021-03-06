/*
 * mov_reader.cpp is part of qtfile++.
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

#include <mov_reader.hpp>
#include <mov_file_io.hpp>
#include <mov_io.hpp>
#include <mov_atom_noprop.hpp>
#include <mov_atom.hpp>
#include <mov_atom_moov.hpp>
#include <mov_atom_tkhd.hpp>
#include <mov_atom_stsz.hpp>
#include <mov_atom_hdlr.hpp>

inline MOVAtom * getAtom(MOVAtom * root, const std::vector<int> & chain) {
	if (!root) {
		return 0;
	}

	MOVAtom * result = root;

	for (auto i : chain) {
		result = result -> getChild(i);

		if (!result) {
			break;
		}
	}

	return result;
}

bool MOVReader::open(const mov_string & path) {
	m_reader = createReader(path);

	if (!m_reader) {
		return false;
	}

	m_root = NOPROPAtom::create('root', 0, m_reader -> length());

	if (!m_root || !m_root -> read(m_reader.get())) {
		return false;
	}

	return !!m_root -> getChild('moov');
}

size_t MOVReader::tracksCount() const {
	MOOVAtom * moov = dynamic_cast<MOOVAtom *>(m_root -> getChild('moov'));

	if (moov) {
		return moov -> tracksCount();
	}

	return 0;
}

size_t MOVReader::samplesCount(size_t trackIndex) const {
	//most correct way will be to check stsz

	MOOVAtom * moov = dynamic_cast<MOOVAtom *>(m_root -> getChild('moov'));

	if (moov) {
		STSZAtom * stsz = dynamic_cast<STSZAtom *>(getAtom(moov -> getTrack(trackIndex), {'mdia', 'minf', 'stbl', 'stsz'}));

		if (stsz) {
			return stsz -> entriesCount(); //todo update logic for raw audio case
		}
	}

	return 0;
}

size_t MOVReader::sampleSize(size_t trackIndex, size_t sampleIndex) const {
	MOOVAtom * moov = dynamic_cast<MOOVAtom *>(m_root -> getChild('moov'));

	if (moov) {
		STSZAtom * stsz = dynamic_cast<STSZAtom *>(getAtom(moov -> getTrack(trackIndex), { 'mdia', 'minf', 'stbl', 'stsz' }));

		if (stsz) {
			return stsz -> getSampleSize(sampleIndex); //todo update logic for raw audio case
		}
	}

	return 0;
}

size_t MOVReader::syncPointLeft(size_t trackIndex, size_t sampleIndex) const {
	return 0;
}

size_t MOVReader::syncPointRight(size_t trackIndex, size_t sampleIndex) const {
	return 0;
}

int MOVReader::getTrackType(size_t trackIndex) const {
	MOOVAtom * moov = dynamic_cast<MOOVAtom *>(m_root -> getChild('moov'));

	if (moov) {
		HDLRAtom * hdlr = dynamic_cast<HDLRAtom *>(getAtom(moov -> getTrack(trackIndex), { 'mdia', 'hdrl' }));

		if (hdlr) {
			switch (hdlr -> getSubType())
			{
			case 'vide':
				return TrackType::Video;
			case 'soun':
				return TrackType::Audio;
			case 'clcp':
				return TrackType::Captions;
			case 'tmcd':
				return TrackType::Timecode;
			default:
				break;
			}
		}
	}

	return TrackType::Unknown;
}

Timecode MOVReader::getSampleTimecode(size_t trackIndex, size_t sampleIndex) const {
	Timecode tc = { 0, 0, 0, 0, false };
	return tc;
}

Timecode MOVReader::getSampleDuration(size_t trackIndex, size_t sampleIndex) const {
	Timecode tc = { 0, 0, 0, 0, false };
	return tc;
}

bool MOVReader::readSample(size_t trackIndex, size_t sampleIndex, void * buffer) {
	return false;
}

std::shared_ptr<VideoInfo> MOVReader::getVideoInfo(size_t trackIndex) const {
	return 0;
}

std::shared_ptr<AudioInfo> MOVReader::getAudioInfo(size_t trackIndex) const {
	return 0;
}

std::shared_ptr<CaptionsInfo> MOVReader::getCaptionsInfo(size_t trackIndex) const {
	return 0;
}

std::shared_ptr<TimecodeInfo> MOVReader::getTimecodeInfo(size_t trackIndex) const {
	return 0;
}




