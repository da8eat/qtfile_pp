#ifndef __MOV_ATOM_STSZ_HPP__
#define __MOV_ATOM_STSZ_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>
#include <utility>

struct Reader;

struct STSZAtom : public MOVAtom
{
private:
	STSZAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
public:
	unsigned int getSampleSize(unsigned int sample) const;
private:
	unsigned int m_sampleSize;
	std::vector<unsigned int> m_stsz; //we need it fo find duration
};

#endif //__MOV_ATOM_STSZ_HPP__
