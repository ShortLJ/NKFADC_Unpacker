#include "SegHit.h"

ClassImp(SegHit)

SegHit::SegHit(){	}

SegHit::SegHit(Sig sig)
	: Sig(sig)
{
	uint8_t itype=map_type[sig.sid][sig.mid][sig.ch];
	det=map_det[sig.sid][sig.mid][sig.ch];
	crystal=map_crystal[sig.sid][sig.mid][sig.ch];
	idx=map_idx[itype][sig.sid][sig.mid][sig.ch];
}

SegHit::SegHit(uint8_t idet, uint8_t icry, uint8_t iidx, Sig sig)
	: det(idet), crystal(icry), idx(iidx), Sig(sig)
{	
	Energy=0;
}

SegHit::~SegHit()
{	}



void SegHit::Clear()
{
}


