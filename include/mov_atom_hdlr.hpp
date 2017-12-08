#ifndef __MOV_ATOM_HDLR_HPP__
#define __MOV_ATOM_HDLR_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>
#include <string>

struct Reader;

struct HDLRAtom : public MOVAtom
{
private:
	HDLRAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
public:
	int getType() const;
	int getSubType() const;
	std::string getName() const;
private:
	int m_type;
	int m_subtype;
	unsigned int m_manufacturer;
	unsigned int m_flags;
	unsigned int m_mask;
	std::string m_name;

};

#endif //__MOV_ATOM_HDLR_HPP__
