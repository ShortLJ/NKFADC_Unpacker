#include "SegHit.h"

SegHit::SegHit(){	}

SegHit::SegHit(Sig sig)
	: Sig(sig)
{
	uint8_t itype=map_type[sig.sid][sig.mid][sig.ch];
	det=map_det[sig.sid][sig.mid][sig.ch];
	pdet = det >> 2;
	pcry = det & 0x03;
	idx=map_idx[itype][sig.sid][sig.mid][sig.ch];
	Energy=0;

}

SegHit::SegHit(uint8_t idet, uint8_t iidx, Sig sig)
	: det(idet), idx(iidx), Sig(sig)
{	
	pdet = det >> 2;
	pcry = det & 0x03;
	Energy=0;
}

SegHit::~SegHit()
{	}



void SegHit::Clear()
{
}


