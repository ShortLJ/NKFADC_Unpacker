#include <cstdio>
#include <stdlib.h>


#include "HitBuilder.h"


HitBuilder::HitBuilder()
{
	//b_first=1;
}

HitBuilder::~HitBuilder()
{	}

void HitBuilder::ReadMapFile(const char *filename)
{
	for (isid=0; isid<Nsid; isid++)	for (imid=0; imid<Nmid; imid++)	for (ich=0; ich<Nch; ich++)
	{
		map_type		[isid][imid][ich] = 0xFF;
		map_det			[isid][imid][ich] = 0xFF;
		for (itype=0; itype<Ntype; itype++)
			map_idx[itype]	[isid][imid][ich] = 0xFF;
	}

	
	FILE *fr = fopen(filename,"r");
	if(fr==NULL)
	{
		fprintf(stderr,"map file is not opened.\n");
		exit(-6);
	}
	const int ndeci = 7;
	uint8_t chL, chU, idx0;
	char line[100];
	while (fgets(line, sizeof line, fr))
	{
		if (*line == '#') continue;
		if (sscanf(line, "%hhu %hhu %hhu %hhu %hhu %hhu %hhu",
			&itype,&idet,&isid,&imid,&chL,&chU,&idx0) !=ndeci)
		{
			fprintf(stderr,"failed to read map file\n");
			exit(-7);
		}
		else
		{
			fprintf(stdout,"%u %u %u %u %u %u %u\n",itype,idet,isid,imid,chL,chU,idx0);
			for (ich=chL; ich<=chU; ich++)
			{
				map_type		[isid][imid][ich] = itype;
				map_det			[isid][imid][ich] = idet;
				map_idx[itype]	[isid][imid][ich] = idx0++;
			}
		}
	}
	for (isid=0; isid<Nsid; isid++)	for (imid=0; imid<Nmid; imid++)
	{
		for(ich=0; ich<Nch; ich++)
			fprintf(stdout,"%u\t",map_idx[1]       [isid][imid][ich]);
		fprintf(stdout,"\n");
	}
}



void HitBuilder::SortByDet(vector<Sig> v_sig_coin)
{
	vector<Sig>::iterator it_sig;
	for (it_sig=v_sig_coin.begin(); it_sig!=v_sig_coin.end(); it_sig++)
	{
		isid = (*it_sig).sid; imid = (*it_sig).mid; ich = (*it_sig).ch;
		itype = map_type		[isid][imid][ich];
		idet  = map_det			[isid][imid][ich];
		iidx  = map_idx[itype]	[isid][imid][ich];

		if(!isvalid(itype, idet, iidx))
		{
			fprintf(stderr,"HitBuilder::SortByDet(vector<Sig> v_sig_coin): not valid\n");
			fprintf(stderr, "HitBuilder::SortByDet(vector<Sig> v_sig_coin): sid %u mid %u ch %u itype %u idet %u iidx %u\n",
					isid, imid, ich, itype, idet, iidx);
			return;
		}
		v_sig[itype][idet].push_back(*it_sig);
	}
}

int HitBuilder::Size(uint8_t itype, uint8_t idet)
{
	return v_sig[itype][idet].size();
}



/*CryHit HitBuilder::GetCryHit(uint8_t idet)
{
	CryHit tmp(idet,v_sig[idet][0], v_sig[idet][1]);
	return tmp;
}*/

void HitBuilder::Clear()
{
	for (itype=0; itype<Ntype; itype++)
	{
		for (idet=0; idet<Ndet; idet++)
		{
			v_sig[itype][idet].clear();
		}
	}
}



bool HitBuilder::isvalid(uint8_t itype, uint8_t idet, uint8_t iidx )
{
	if (itype>=Ntype)	{fprintf(stderr,"itype%u>=Ntype%u\n", itype, Ntype); return 0;}
	if (idet>=Ndet)	{fprintf(stderr,"idet%u>=Ndet%u\n", idet, Ndet); return 0;}
	if (itype==0 && iidx>=Ntype0)	{fprintf(stderr,"iidx0%u>=Ntype0%u\n", iidx, Ntype0); return 0;}
	if (itype==1 && iidx>=Ntype1)	{fprintf(stderr,"iidx1%u>=Ntype1%u\n", iidx, Ntype1); return 0;}
	return 1;
}


bool HitBuilder::isGood()
{
	return 1;
	///////////// where we will put constraints for identifying a particle hit
}








