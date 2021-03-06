/*
 * mov_atom_stsc.cpp is part of qtfile++.
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

#include <mov_atom_stsc.hpp>
#include <mov_io.hpp>

#include <algorithm>

STSCAtom::STSCAtom(long long position, long long size)
	: MOVAtom('stsc', position, size)
{
}

std::shared_ptr<MOVAtom> STSCAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) STSCAtom(position, size));
}

bool STSCAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) { 
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	unsigned int entries = readInteger<unsigned int>(r);

	unsigned int bound = 0;
	unsigned int prevChunk = 0;
	for (unsigned int i = 0; i < entries; ++i) {
		STSCTable t;
		t.firstSample = readInteger<unsigned int>(r);
		t.samples = readInteger<unsigned int>(r);
		t.id = readInteger<unsigned int>(r);

		bound += (t.firstSample - prevChunk) * t.samples;
		prevChunk = t.firstSample;

		m_stsc.push_back(t);
		m_offset.push_back(bound);
	}

	return end == r -> position();
}

std::pair<unsigned int, unsigned int> STSCAtom::getChunkNumber(unsigned int sample) const {
	auto it = std::upper_bound(m_offset.begin(), m_offset.end(), sample);

	if (it == m_offset.end()) {
		return std::make_pair(0, 0); //I assume broken stsc or someone passed sample value bigger than samples in track
	}

	unsigned int chunk = 0;
	unsigned int frame = 0; 

	unsigned int index = static_cast<unsigned int>(it - m_offset.begin());

	if (index) {
		frame = m_offset[index - 1];
	}

	chunk = m_stsc[index].firstSample - 1;
	chunk += (sample - frame) / m_stsc[index].samples;
	frame += (chunk - m_stsc[index].firstSample + 1) * m_stsc[index].samples;

	return std::make_pair(chunk, frame);
}
