#ifndef __MOV_ATOM_MDHD_HPP__
#define __MOV_ATOM_TKHD_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>

struct Reader;

struct MDHDAtom : public MOVAtom
{
private:
	MDHDAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
public:
	unsigned int getDuration() const;
	unsigned int getTimeScale() const;
private:
	unsigned int m_creationTime;
	unsigned int m_modificationTime;
	unsigned int m_timeScale;
	unsigned int m_duration;

	unsigned short m_language;
	unsigned short m_quolity;
};

#endif //__MOV_ATOM_TKHD_HPP__
