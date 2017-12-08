#include <mov_atom.hpp>
#include <mov_atom_factory.hpp>

#include <unordered_map>

#include <mov_atom_mdat.hpp>
#include <mov_atom_free.hpp>
#include <mov_atom_ftyp.hpp>
#include <mov_atom_moov.hpp>
#include <mov_atom_mvhd.hpp>
#include <mov_atom_prfl.hpp>
#include <mov_atom_noprop.hpp>
#include <mov_atom_tkhd.hpp>
#include <mov_atom_elst.hpp>
#include <mov_atom_mdhd.hpp>
#include <mov_atom_hdlr.hpp>
#include <mov_atom_mhd.hpp>
#include <mov_atom_mhd.hpp>
#include <mov_atom_dref.hpp>
#include <mov_atom_stsd.hpp>
#include <mov_atom_clcp.hpp>
#include <mov_atom_stts.hpp>
#include <mov_atom_stsc.hpp>
#include <mov_atom_stsz.hpp>
#include <mov_atom_stco.hpp>

#include <mov_atom_tmcddata.hpp>

typedef std::shared_ptr<MOVAtom> ( * CreateAtom)(int id, long long position, long long size);

struct AtomFactory
{
	static AtomFactory * instance();
	std::shared_ptr<MOVAtom> create(int id, long long position, long long size, bool stsd = false);
private:
	AtomFactory();
	void fillMainFactory();
	void fillStsdFactory();
private:
	std::unordered_map<int, CreateAtom> m_factory;
	std::unordered_map<int, CreateAtom> m_stsdFactory;
};

AtomFactory * AtomFactory::instance() {
	static AtomFactory af;
	return &af;
}

std::shared_ptr<MOVAtom> AtomFactory::create(int id, long long position, long long size, bool stsd) {
	if (stsd) {
		auto creator = m_stsdFactory.find(id);
		if (creator != m_stsdFactory.end()) {
			return creator -> second(id, position, size); //otherwise check main factory
		}
	}
	auto creator = m_factory.find(id);

	if (creator == m_factory.end()) {
		return std::shared_ptr<MOVAtom>(new (std::nothrow) MOVAtom(id, position, size));
	}

	return creator -> second(id, position, size);
}

AtomFactory::AtomFactory() {
	fillMainFactory();
	fillStsdFactory();
}

void AtomFactory::fillMainFactory() {
	m_factory['mdat'] = MDATAtom::create;
	m_factory['wide'] = WIDEAtom::create;
	m_factory['free'] = FREEAtom::create;
	m_factory['skip'] = SKIPAtom::create;
	m_factory['ftyp'] = FTYPAtom::create;
	m_factory['moov'] = MOOVAtom::create;
	m_factory['mvhd'] = MVHDAtom::create;
	m_factory['prfl'] = PRFLAtom::create;
	m_factory['trak'] = NOPROPAtom::create;
	m_factory['tkhd'] = TKHDAtom::create;
	m_factory['edts'] = NOPROPAtom::create;
	m_factory['mdia'] = NOPROPAtom::create;
	//m_factory['tref'] = NOPROPAtom::create; //tref contains track refs so same atom name but different structure (size, name and id) so we will just parse it manually if needed
	m_factory['tapt'] = NOPROPAtom::create;
	m_factory['elst'] = ELSTAtom::create;
	m_factory['mdhd'] = MDHDAtom::create;
	m_factory['hdlr'] = HDLRAtom::create;
	m_factory['minf'] = NOPROPAtom::create;
	m_factory['dinf'] = NOPROPAtom::create;
	m_factory['gmhd'] = NOPROPAtom::create;
	m_factory['vmhd'] = VMHDAtom::create;
	m_factory['smhd'] = SMHDAtom::create;
	m_factory['dref'] = DREFAtom::create;
	m_factory['stbl'] = NOPROPAtom::create;
	m_factory['tmcd'] = NOPROPAtom::create;
	m_factory['stsd'] = STSDAtom::create;
	m_factory['c708'] = CLCPAtom::create;
	m_factory['c608'] = CLCPAtom::create;
	m_factory['stts'] = STTSAtom::create;
	m_factory['stsc'] = STSCAtom::create;
	m_factory['stsz'] = STSZAtom::create;
	m_factory['stco'] = STCOAtom::create;
	m_factory['co64'] = STCOAtom::create;
}

void AtomFactory::fillStsdFactory() {
	m_stsdFactory['tmcd'] = TMCDDataAtom::create;
}

std::shared_ptr<MOVAtom> createAtom(int id, long long position, long long size) {
	return AtomFactory::instance() -> create(id, position, size);
}

std::shared_ptr<MOVAtom> createStsdSubAtom(int id, long long position, long long size) {
	return AtomFactory::instance() -> create(id, position, size, true);
}
