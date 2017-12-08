#ifndef __MOV_ATOM_STCO_HPP__
#define __MOV_ATOM_STCO_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>
#include <utility>

struct Reader;

struct STCOAtom : public MOVAtom
{
private:
	STCOAtom(int id, long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
public:
	long long getChunkOffset(unsigned int chunk) const;
private:
	void read32(unsigned int entries, Reader * r);
	void read64(unsigned int entries, Reader * r);
private:
	unsigned int m_sampleSize;
	std::vector<long long> m_stco; //we need it fo find duration
};

#endif //__MOV_ATOM_STSZ_HPP__
