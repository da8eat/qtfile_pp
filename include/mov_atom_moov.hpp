#ifndef __MOV_ATOM_MOOV_HPP__
#define __MOV_ATOM_MOOV_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>
#include <unordered_map>

struct Reader;

struct MOOVAtom : public MOVAtom
{
private:
	MOOVAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
	MOVAtom * getTrack(size_t index); //get track by index, index starts from 0 tracks stored in same order stored in file
	size_t tracksCount() const;
private:
	std::vector<MOVAtom *> m_tracks;
};

#endif //__MOV_ATOM_MOOV_HPP__
