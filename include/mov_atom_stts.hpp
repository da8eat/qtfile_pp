#ifndef __MOV_ATOM_STTS_HPP__
#define __MOV_ATOM_STTS_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>
#include <utility>

struct Reader;

struct STTSAtom : public MOVAtom
{
private:
	STTSAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
public:
	unsigned int getSampleDuration(unsigned int sample) const;
private:
	std::vector<std::pair<unsigned int, unsigned int> > m_stts; //we need it fo find duration
};

#endif //__MOV_ATOM_STTS_HPP__
