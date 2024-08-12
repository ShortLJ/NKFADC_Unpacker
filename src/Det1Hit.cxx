#include "Det1Hit.h"


Det1Hit::Det1Hit(Sig sig)
	: Sig(sig)
{
	uint8_t itype = map_type[sig.sid][sig.mid][sig.ch];
	det=map_det[sig.sid][sig.mid][sig.ch];
	pdet = det;
	pcry = 0;
	//pdet = det >> 2; // clover number
	//pcry = det & 0x03; // crystal idx
	idx=map_idx[itype][sig.sid][sig.mid][sig.ch];
	Energy=0;

}

Det1Hit::Det1Hit(uint8_t idet, uint8_t iidx, Sig sig)
	: det(idet), idx(iidx), Sig(sig) // example: SegHit(a,b,sig) -> b-th segment of a-th crystal
{	
	pdet = det;
	pcry = 0;
	//pdet = det >> 2; // clover number
	//pcry = det & 0x03; // crystal idx
	Energy=0;
}



void Det1Hit::Clear()
{
}


