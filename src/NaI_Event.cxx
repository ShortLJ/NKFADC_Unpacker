

#include "NaI_Event.h"

NaI_Event::NaI_Event(vector<Sig> v_sigs)
{
	v_naihit.clear();

	vector<Sig> v_sig_sort[Ntype][Ndet];

	vector<Sig>::iterator it_sig;
	for (it_sig=v_sigs.begin(); it_sig!=v_sigs.end(); it_sig++)
	{
		uint8_t isid = it_sig->sid;
		uint8_t imid = it_sig->mid;
		uint8_t ich =  it_sig->ch;
		uint8_t itype = map_type		[isid][imid][ich]; if (itype==255) continue;
		uint8_t idet  = map_det			[isid][imid][ich];
		uint8_t iidx  = map_idx[itype]	[isid][imid][ich];
		if (!isValid(itype,idet))
		{
			fprintf(stderr,"NaI_Event::NaI_Event(vector<Sig> v_sigs): not valid\n");
			exit(-10);
		}
		v_sig_sort[itype][idet].push_back(*it_sig);

		NaIHit naihit = NaIHit(idet,0,*it_sig);
		v_naihit.push_back(naihit);
	}
	/*for (uint8_t idet=0; idet<Ndet; idet++)
	{
		if (v_sig_sort[0][idet].size()>0)
		{
			NaIHit naihit = NaIHit(idet,0,v_sig_sort[0][idet]);
			v_naihit.push_back(naihit);
		}
	}*/
}

bool NaI_Event::isValid(uint8_t itype, uint8_t idet)
{
	if (itype>=Ntype)	{fprintf(stderr,"itype%u>=Ntype%u\n", itype, Ntype); return 0;}
	if (idet>=Ndet)	{fprintf(stderr,"idet%u>=Ndet%u\n", idet, Ndet); return 0;}
	return 1;
}
