#ifndef __MOV_ATOM_STSC_HPP__
#define __MOV_ATOM_STSC_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>
#include <utility>

struct Reader;

struct STSCAtom : public MOVAtom
{
public:
	struct STSCTable {
		unsigned int firstSample;
		unsigned int samples;
		unsigned int id;
	};
private:
	STSCAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
public:
	//first - chunk number, second - first frame in chunk
	std::pair<unsigned int, unsigned int> getChunkNumber(unsigned int sample) const;
private:
	std::vector<STSCTable> m_stsc; //we need it fo find duration
	std::vector<unsigned int> m_offset;
};

#endif //__MOV_ATOM_STSC_HPP__
