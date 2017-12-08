#ifndef __MOV_ATOM_NO_PROP_HPP__
#define __MOV_ATOM_NO_PROP_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>
#include <unordered_map>

struct Reader;

//this atom will handle all atoms that has no properties but holds sub-atoms
//like trak, edts so on
struct NOPROPAtom : public MOVAtom
{
private:
	NOPROPAtom(int id, long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
};

#endif //__MOV_ATOM_NO_PROP_HPP__
