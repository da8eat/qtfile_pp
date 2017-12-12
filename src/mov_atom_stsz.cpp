/*
 * mov_atom_stsz.cpp is part of qtfile++.
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

#include <mov_atom_stsz.hpp>
#include <mov_io.hpp>

STSZAtom::STSZAtom(long long position, long long size)
	: MOVAtom('stsz', position, size)
{
}

std::shared_ptr<MOVAtom> STSZAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) STSZAtom(position, size));
}

bool STSZAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) { 
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	m_sampleSize = readInteger<unsigned int>(r);
	m_entriesCount = readInteger<unsigned int>(r);

	if (!m_sampleSize) {
		for (unsigned int i = 0; i < m_entriesCount; ++i) {
			unsigned int size = readInteger<unsigned int>(r);
			m_stsz.push_back(size);
		}
	}

	return end == r -> position();
}

unsigned int STSZAtom::entriesCount() const {
	return m_entriesCount;
}

unsigned int STSZAtom::getSampleSize(size_t sample) const {
	if (m_sampleSize) {
		return m_sampleSize;
	}

	if (sample >= m_stsz.size()) {
		return 0;
	}

	return m_stsz[sample];
}
