#include <cstdio>


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
		map_crystal		[isid][imid][ich] = 0XFF;
		for (itype=0; itype<Ntype; itype++)
			map_idx[itype]	[isid][imid][ich] = 0xFF;
	}

	/*
	FILE *fr = fopen(file,"r");
	if(fr==NULL)
	{
		fprintf(stderr,"map file is not opened.\n");
		exit(-6);
	}
	const int ndeci = 8;
	//uint8_t a[ndeci];	// type det crystal sid mid chL chU idx0
	uint8_t chL, chU, idx0;
	char line[100];
	while (fgets(line, sizeof line, fr))
	{
		if (*line == '#') continue;
		if (sscanf(line, "%u %u %u %u %u %u %u",
			&type,&idet,&icry,&isid,&imid,&chL,&chU,&idx0) !=ndeci)
		{
			fprintf(stderr,"failed to read map file\n");
			exit(-7);
		}
		else
		{
			fprintf(stdout,"%u %u %u %u %u %u %u %u\n",itype,idet,icry,isid,imid,chL,chU,idx0);
			for (ich=a[7]; ich<=a[8]; ich++)
			{
				map_type		[isid][imid][ich] = itype;
				map_det			[isid][imid][ich] = idet;
				map_crystal		[isid][imid][ich] = icry;
				map_idx[itype]	[isid][imid][ich] = idx0++;
			}
		}
	}
	*/
	for (idet=0; idet<Ndet; idet++) for (icry=0; icry<Ncry; icry++) for (ifv=0; ifv<Nfv; ifv++)
	{
		itype=0;
		isid=idet; imid=icry+1; ich=ifv+0; 
		map_det			[isid][imid][ich] = idet;
		map_crystal		[isid][imid][ich] = icry;
		map_type		[isid][imid][ich] = itype;
		map_idx[itype]	[isid][imid][ich] = ifv;
	}
	for (idet=0; idet<Ndet; idet++) for (icry=0; icry<Ncry; icry++) for (iseg=0; iseg<Nseg; iseg++)
	{
		itype=1;
		isid=idet; imid=icry+1; ich=iseg+2; 
		map_det			[isid][imid][ich] = idet;
		map_crystal		[isid][imid][ich] = icry;
		map_type		[isid][imid][ich] = itype;
		map_idx[itype]	[isid][imid][ich] = iseg;
	}
	for (isid=0; isid<Nsid; isid++)	for (imid=0; imid<Nmid; imid++)
	{
		for(ich=0; ich<Nch; ich++)
			fprintf(stdout,"%u\t",map_crystal       [isid][imid][ich]);
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
		icry  = map_crystal		[isid][imid][ich];
		iidx  = map_idx[itype]	[isid][imid][ich];
		//fprintf(stdout, "HitBuilder::SortByDet(vector<Sig> v_sig_coin): sid %u mid %u ch %u itype %u idet %u icry %u iidx %u\n",
		//	isid, imid, ich, itype, idet, icry, iidx);

		if(!isvalid(itype, idet, icry, iidx))
		{
			fprintf(stderr,"HitBuilder::SortByDet(vector<Sig> v_sig_coin): not valid\n");
			fprintf(stderr, "HitBuilder::SortByDet(vector<Sig> v_sig_coin): sid %u mid %u ch %u itype %u idet %u icry %u iidx %u\n",
					isid, imid, ich, itype, idet, icry, iidx);
			return;
		}
		v_sig[idet][icry][itype].push_back(*it_sig);
	}
}

int HitBuilder::Size(uint8_t idet, uint8_t icry, uint8_t itype)
{
	return v_sig[idet][icry][itype].size();
}



CryHit HitBuilder::GetCryHit(uint8_t idet, uint8_t icry)
{
	//fprintf(stdout,"v_sig[idet%u][icry%u][0].size() %ld v_sig[idet%u][icry%u][1].size() %ld\n",
	//		idet,icry,v_sig[idet][icry][0].size(),
	//		idet,icry,v_sig[idet][icry][1].size());
	//fprintf(stdout,"CryHit HitBuilder::GetCryHit(uint8_t idet, uint8_t icry)\n");
	CryHit tmp(idet,icry,v_sig[idet][icry][0], v_sig[idet][icry][1]);
	return tmp;
}

void HitBuilder::Clear()
{
	for (idet=0; idet<Ndet; idet++)	for (icry=0; icry<Ncry; icry++)	
	{
		for (itype=0; itype<Ntype; itype++)
		{
			v_sig[idet][icry][itype].clear();
		}
	}
}



bool HitBuilder::isvalid(uint8_t itype, uint8_t idet, uint8_t icry, uint8_t iidx )
{
	/*if (itype==0Xff) return 0;
	if (idet ==0xff) return 0;
	if (icry ==0xff) return 0;
	if (itype==0 && ifv  ==0xff) return 0;
	if (itype==1 && iseg ==0xff) return 0;*/
	
	/*if (itype>=Ntype) return 0;
	if (idet >=Ndet ) return 0;
	if (icry >=Ncry ) return 0;
	if (itype==0 && ifv  >=Nfv  ) return 0;
	if (itype==1 && iseg >=Nseg ) return 0;*/
	
	if (itype>=Ntype)	{fprintf(stderr,"itype%u>=Ntype%u\n", itype, Ntype); return 0;}
	if (idet>=Ndet)	{fprintf(stderr,"idet%u>=Ndet%u\n", idet, Ndet); return 0;}
	if (icry>=Ncry)	{fprintf(stderr,"icry%u>=Ncry%u\n", icry, Ncry); return 0;}
	if (itype==0 && iidx>=Nfv)	{fprintf(stderr,"ifv%u>=Nfv%u\n", ifv, Nfv); return 0;}
	if (itype==1 && iidx>=Nseg)	{fprintf(stderr,"iseg%u>=Nseg%u\n", iseg, Nseg); return 0;}
	return 1;
}


bool HitBuilder::isGood()
{
	return 1;
	///////////// where we will put constraints for identifying a particle hit
}








