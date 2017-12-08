#include <mov_atom_mhd.hpp>
#include <mov_io.hpp>

VMHDAtom::VMHDAtom(long long position, long long size)
	: MOVAtom('vmhd', position, size)
{
}

std::shared_ptr<MOVAtom> VMHDAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) VMHDAtom(position, size));
}

bool VMHDAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length() || m_size != 20) {
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	m_graphicsMode = readInteger<unsigned short>(r);
	m_opcolorRed = readInteger<unsigned short>(r);
	m_opcolorGreen = readInteger<unsigned short>(r);
	m_opcolorBlue = readInteger<unsigned short>(r);
	
	return end == r -> position();
}

SMHDAtom::SMHDAtom(long long position, long long size)
	: MOVAtom('smhd', position, size)
{
}

std::shared_ptr<MOVAtom> SMHDAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) SMHDAtom(position, size));
}

bool SMHDAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r -> length() || m_size != 16) {
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	m_balance = readFloat8_8(r);
	m_reserved = readInteger<unsigned short>(r);

	return end == r -> position();
}

GMINAtom::GMINAtom(long long position, long long size)
	: MOVAtom('gmin', position, size)
{
}

std::shared_ptr<MOVAtom> GMINAtom::create(int id, long long position, long long size) {
	static_cast<void>(id);
	return std::shared_ptr<MOVAtom>(new (std::nothrow) GMINAtom(position, size));
}

bool GMINAtom::read(Reader * r) {
	long long end = m_size + m_position;

	if (end > r->length() || m_size != 20) {
		return false;
	}

	if (!readVersionAndFlags(r)) {
		return false;
	}

	m_graphicsMode = readInteger<unsigned short>(r);
	m_opcolorRed = readInteger<unsigned short>(r);
	m_opcolorGreen = readInteger<unsigned short>(r);
	m_opcolorBlue = readInteger<unsigned short>(r);

	m_balance = readFloat8_8(r);
	m_reserved = readInteger<unsigned short>(r);

	return end == r->position();
}

