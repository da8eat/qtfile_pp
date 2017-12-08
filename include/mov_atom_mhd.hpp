#ifndef __MOV_ATOM_MHD_HPP__
#define __MOV_ATOM_MHD_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>

struct Reader;

struct VMHDAtom : public MOVAtom
{
private:
	VMHDAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
private:
	unsigned short m_graphicsMode;
	unsigned short m_opcolorRed;
	unsigned short m_opcolorGreen;
	unsigned short m_opcolorBlue;
};

struct SMHDAtom : public MOVAtom
{
private:
	SMHDAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
private:
	double m_balance; //float8.8
	unsigned short m_reserved;
};

struct GMINAtom : public MOVAtom
{
private:
	GMINAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
private:
	unsigned short m_graphicsMode;
	unsigned short m_opcolorRed;
	unsigned short m_opcolorGreen;
	unsigned short m_opcolorBlue;

	double m_balance; //float8.8
	unsigned short m_reserved;
};

#endif //__MOV_ATOM_MHD_HPP__
