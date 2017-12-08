#include <mov_atom_stts.hpp>
#include <mov_io.hpp>

#include <algorithm>

STTSAtom::STTSAtom(long long position, long long size)
	: MOVAtom('stts', position, size)
{
}

std::shared_ptr<MOVAtom> STTSAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) STTSAtom(position, size));
}

bool STTSAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length()) { 
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	unsigned int entries = readInteger<unsigned int>(r);

	unsigned int bound = 0;
	for (unsigned int i = 0; i < entries; ++i) {
		unsigned int samples = readInteger<unsigned int>(r);
		unsigned int duration = readInteger<unsigned int>(r);

		bound += samples;
		m_stts.push_back(std::make_pair(bound, duration));
	}

	return end == r -> position();
}

unsigned int STTSAtom::getSampleDuration(unsigned int sample) const {
	auto it = std::upper_bound(m_stts.begin(), m_stts.end(), sample, [](auto a, auto b) -> bool { return a < b.second; });

	if (it == m_stts.end()) {
		return 0; //I assume broken stts or someone passed sample value bigger than samples in track
	}

	return it -> second;
}
