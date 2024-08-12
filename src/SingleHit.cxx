#include "SingleHit.h"

SingleHit::SingleHit(uint8_t idet, vector<Sig> v_sig_det1/*, vector<Sig> v_sig_det2*/)
	: det(idet)
{
	pdet = det >> 2;
	pcry = det & 0x03;
	Clear();
	vector<Sig>::iterator it;
	for (it=v_sig_det1.begin(); it!=v_sig_det1.end(); ++it)
	{
		v_det1hit.push_back(Det1Hit(*it));
	}
	/*for (it=v_sig_det2.begin(); it!=v_sig_det2.end(); ++it)
	{
		v_det2hit.push_back(Det2Hit(*it));
	}*/
}


void SingleHit::Print()
{
	fprintf(stdout,"SingleHit::Print(): det %u pdet %u pcrystal %u\n",det,pdet,pcry);
	vector<Det1Hit>::iterator it_det1hit;
	for (it_det1hit=v_det1hit.begin(); it_det1hit!=v_det1hit.end();it_det1hit++)
	{
		(*it_det1hit).Print();
	}
	/*vector<Det2Hit>::iterator it_det2hit;
	for (it_det2hit=v_det2hit.begin(); it_det2hit!=v_det2hit.end();it_det2hit++)
	{
		(*it_det2hit).Print();
	}*/
}

void SingleHit::Clear()
{
	v_det1hit.clear();
	//v_det2hit.clear();
}

bool SingleHit::isValid()
{
	if (v_det1hit.empty()) return 0;
	//if (v_det2hit.empty()) return 0;
	return 1;
}



