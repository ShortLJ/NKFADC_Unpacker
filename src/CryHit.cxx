#include "CryHit.h"

ClassImp(CryHit)

CryHit::CryHit(){	}

CryHit::CryHit(uint8_t idet, uint8_t icry, vector<Sig> v_sig_fv, vector<Sig> v_sig_seg)
	: det(idet), crystal(icry)
{
	Clear();
	vector<Sig>::iterator it;
	for (it=v_sig_fv.begin(); it!=v_sig_fv.end(); it++)
	{
		v_fvhit.push_back(FVHit(*it));
	}
	for (it=v_sig_seg.begin(); it!=v_sig_seg.end(); it++)
	{
		v_seghit.push_back(FVHit(*it));
	}
	checkid();
}




CryHit::CryHit(vector<FVHit> vfh, vector<SegHit> vsh)
	:v_fvhit(vfh), v_seghit(vsh)
{	
	if(vfh.size()==0 || vsh.size()==0)
	{
		fprintf(stderr,"CryHit::CryHit(vector<FVHit> vfh, vector<SegHit> vsh) with size 0\n");
		exit(-8);
	}
	det = vfh.at(0).det;
	crystal = vfh.at(0).crystal;
	checkid();

}

CryHit::~CryHit()
{	}

void CryHit::Print()
{
	fprintf(stdout,"CryHit::Print(): det %u crystal %u\n",det,crystal);
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

bool CryHit::checkid()
{
	vector<FVHit>::iterator it_fvhit;
	for (it_fvhit=v_fvhit.begin(); it_fvhit!=v_fvhit.end();it_fvhit++)
	{
		if((*it_fvhit).det!=det || (*it_fvhit).crystal!=crystal)
		{
			fprintf(stderr,"CryHit::CryHit(vector<FVHit> v_fvhit, vector<SegHit> vsh) fv det %u %u/crystal%u %u is not identical\n", (*it_fvhit).det, det, (*it_fvhit).crystal, crystal);
			exit(-9);
		}
	}
	vector<SegHit>::iterator it_seghit;
	for (it_seghit=v_seghit.begin(); it_seghit!=v_seghit.end();it_seghit++)
	{
		if((*it_seghit).det!=det || (*it_seghit).crystal!=crystal)
		{
			fprintf(stderr,"CryHit::CryHit(vector<FVHit> vfh, vector<SegHit> vsh) seg det/crystal is not identical\n");
			exit(-9);
		}
	}
	return 1;
}


