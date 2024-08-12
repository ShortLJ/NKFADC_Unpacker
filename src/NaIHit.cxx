#include "NaIHit.h"


NaIHit::NaIHit(Sig sig)
	: Sig(sig)
{
	uint8_t itype = map_type[sig.sid][sig.mid][sig.ch];
	det=map_det[sig.sid][sig.mid][sig.ch];
	pdet = det;
	pcry = 0;
	idx=map_idx[itype][sig.sid][sig.mid][sig.ch];
	Energy=0;

}

NaIHit::NaIHit(uint8_t idet, uint8_t iidx, Sig sig)
	: det(idet), idx(iidx), Sig(sig)
{	
	pdet = det;
	pcry = 0;
	Energy=0;
}



void NaIHit::Clear()
{
}


