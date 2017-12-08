#ifndef __MOV_ATOM_FTYP_HPP__
#define __MOV_ATOM_FTYP_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>

struct Reader;

struct FTYPAtom : public MOVAtom
{
private:
	FTYPAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
private:
	int m_majorBrand;
	int m_minorBrand;

	std::vector<int> m_compatibleBrands;
};

#endif //__MOV_ATOM_FTYP_HPP__
