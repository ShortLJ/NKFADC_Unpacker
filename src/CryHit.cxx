#include "CryHit.h"

CryHit::CryHit(uint8_t idet, vector<Sig> v_sig_fv, vector<Sig> v_sig_seg)
	: det(idet)
{
	pdet = det >> 2;
	pcry = det & 0x03;
	Clear();
	vector<Sig>::iterator it;
	for (it=v_sig_fv.begin(); it!=v_sig_fv.end(); ++it)
	{
		v_fvhit.push_back(FVHit(*it));
	}
	for (it=v_sig_seg.begin(); it!=v_sig_seg.end(); ++it)
	{
		v_seghit.push_back(FVHit(*it));
	}
}


void CryHit::Print()
{
	fprintf(stdout,"CryHit::Print(): det %u pdet %u pcrystal %u\n",det,pdet,pcry);
	vector<FVHit>::iterator it_fvhit;
	for (it_fvhit=v_fvhit.begin(); it_fvhit!=v_fvhit.end();it_fvhit++)
	{
		(*it_fvhit).Print();
	}
	vector<SegHit>::iterator it_seghit;
	for (it_seghit=v_seghit.begin(); it_seghit!=v_seghit.end();it_seghit++)
	{
		(*it_seghit).Print();
	}
}

void CryHit::Clear()
{
	v_seghit.clear();
	v_fvhit.clear();
}

bool CryHit::isValid()
{
	if (v_fvhit.empty()) return 0;
	if (v_seghit.empty()) return 0;
	return 1;
}



