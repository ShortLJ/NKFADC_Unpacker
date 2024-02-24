#include "X6Hit.h"

X6Hit::X6Hit(uint8_t idet, vector<Sig> v_sig_ohmic, vector<Sig> v_sig_strip)
	: det(idet)
{
	Clear();
	vector<Sig>::iterator it;
	for (it=v_sig_ohmic.begin(); it!=v_sig_ohmic.end(); ++it)
	{
		v_ohmichit.push_back(OhmicHit(*it));
	}
	for (it=v_sig_strip.begin(); it!=v_sig_strip.end(); ++it)
	{
		if (!((*it).ch & 0b1)) 
			v_strpUhit.push_back(StripHit(*it));
		else //if ( ((*it).ch & 0b1)) 
			v_strpDhit.push_back(StripHit(*it));
	}
}


void X6Hit::Print()
{
	fprintf(stdout,"X6Hit::Print(): det %u det %u \n",det,det);
	vector<OhmicHit>::iterator it_ohmichit;
	for (it_ohmichit=v_ohmichit.begin(); it_ohmichit!=v_ohmichit.end();it_ohmichit++)
	{
		(*it_ohmichit).Print();
	}
	vector<StripHit>::iterator it_striphit;
	for (it_striphit=v_strpUhit.begin(); it_striphit!=v_strpUhit.end();it_striphit++)
	{
		(*it_striphit).Print();
	}
	for (it_striphit=v_strpDhit.begin(); it_striphit!=v_strpDhit.end();it_striphit++)
	{
		(*it_striphit).Print();
	}
}

void X6Hit::Clear()
{
	v_ohmichit.clear();
	v_strpUhit.clear();
	v_strpDhit.clear();
}

bool X6Hit::isValid()
{
	if (v_ohmichit.empty()) return 0;
	if (v_strpUhit.empty()) return 0;
	if (v_strpDhit.empty()) return 0;
	return 1;
}



