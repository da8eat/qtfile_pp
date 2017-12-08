#ifndef __MOV_ATOM_ELST_HPP__
#define __MOV_ATOM_ELST_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>

struct Reader;

struct ELSTAtom : public MOVAtom
{
private:
	ELSTAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);

	size_t entries() const;
	unsigned int entryDuration(size_t index) const;
	unsigned int entryTime(size_t index) const;
	double entryRate(size_t index) const;
private:
	struct EditEntry
	{
		unsigned int duration;
		unsigned int time;
		double rate;
	};
private:
	std::vector<EditEntry> m_entries;
};

#endif //__MOV_ATOM_ELST_HPP__
