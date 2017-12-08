#ifndef __MOV_ATOM_DREF_HPP__
#define __MOV_ATOM_DREF_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>

struct Reader;

struct DREFAtom : public MOVAtom
{
private:
	DREFAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
};

#endif //__MOV_ATOM_DREF_HPP__
