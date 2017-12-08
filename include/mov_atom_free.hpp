#ifndef __MOV_ATOM_FREE_HPP__
#define __MOV_ATOM_FREE_HPP__

#include <memory>
#include "mov_atom.hpp"

struct Reader;

struct FREEAtom : public MOVAtom
{
private:
	FREEAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
};

struct SKIPAtom : public MOVAtom
{
private:
	SKIPAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
};

#endif //__MOV_ATOM_FREE_HPP__
