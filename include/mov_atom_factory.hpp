#ifndef __MOV_ATOM_FACTORY_HPP__
#define __MOV_ATOM_FACTORY_HPP__

#include <memory>

struct MOVAtom;
std::shared_ptr<MOVAtom> createAtom(int id, long long position, long long size);
std::shared_ptr<MOVAtom> createStsdSubAtom(int id, long long position, long long size);

#endif //__MOV_ATOM_FACTORY_HPP__
