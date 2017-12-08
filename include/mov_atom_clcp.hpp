#ifndef __MOV_ATOM_CLCP_HPP__
#define __MOV_ATOM_CLCP_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>
#include <string>

struct Reader;

struct CLCPAtom : public MOVAtom
{
private:
	//could be c608 or c708
	CLCPAtom(int id, long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
};

#endif //__MOV_ATOM_CLCP_HPP__
