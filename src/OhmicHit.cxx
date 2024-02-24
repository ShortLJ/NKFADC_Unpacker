#include "OhmicHit.h"


OhmicHit::OhmicHit(Sig sig)
	: Sig(sig)
{
	uint8_t itype = map_type[sig.sid][sig.mid][sig.ch];
	det=map_det[sig.sid][sig.mid][sig.ch];
	idx=map_idx[itype][sig.sid][sig.mid][sig.ch];
	Energy=0;

}

OhmicHit::OhmicHit(uint8_t idet, uint8_t iidx, Sig sig)
	: det(idet), idx(iidx), Sig(sig)
{	
	Energy=0;
}



void OhmicHit::Clear()
{
}


