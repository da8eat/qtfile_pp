#ifndef __MOV_ATOM_PRFL_HPP__
#define __MOV_ATOM_PRFL_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>

struct Reader;

struct PRFLAtom : public MOVAtom
{
private:
	PRFLAtom(long long position, long long size);
public:
	static std::shared_ptr<MOVAtom> create(int id, long long position, long long size);
public:
	virtual bool read(Reader * r);
private:
	struct Feature
	{
		unsigned int resetved;
		unsigned int partID;
		unsigned int featureCode;
		unsigned int featureValue;
	};
private:
	std::vector<Feature> m_features;
};

#endif //__MOV_ATOM_PRFL_HPP__
