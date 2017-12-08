#ifndef __MOV_ATOM_MDAT_HPP__
#define __MOV_ATOM_MDAT_HPP__

#include <memory>
#include "mov_atom.hpp"

struct Reader;

struct MDATAtom : public MOVAtom
{
private:
	MDATAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
private:
	bool m_extendedSize;
};

struct WIDEAtom : public MOVAtom
{
private:
	WIDEAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
};

#endif //__MOV_ATOM_MDAT_HPP__
