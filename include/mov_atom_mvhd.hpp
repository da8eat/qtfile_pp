#ifndef __MOV_ATOM_MVHD_HPP__
#define __MOV_ATOM_MVHD_HPP__

#include <memory>
#include "mov_atom.hpp"

#include <vector>

struct Reader;

struct MVHDAtom : public MOVAtom
{
private:
	MVHDAtom(long long position, long long size);
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
	double m_preferredRate;
	unsigned short m_preferredVolume;
	unsigned char m_reserved[10];

	double m_matrix[3][3];

	unsigned int m_previewTime;
	unsigned int m_previewDuration;
	unsigned int m_posterTime;
	unsigned int m_selectionTime;
	unsigned int m_selectionDuration;
	unsigned int m_currentTime;
	unsigned int m_nextTrackID;

};

#endif //__MOV_ATOM_MVHD_HPP__
