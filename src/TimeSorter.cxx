
#include <stdlib.h>

#include "TimeSorter.h"



TimeSorter::TimeSorter()
{
}



TimeSorter::~TimeSorter()
{
}

bool TimeSorter::AllEmpty()
{
	for (isid=0; isid<Nsid; isid++)	for (imid=0; imid<Nmid; imid++)	for (icha=0; icha<Ncha; icha++)
	{
		if (!Empty(isid,imid,icha)) return 0;
	}
	return 1;
}

uint64_t TimeSorter::GetMinLGT()
{
	uint64_t ret=-1;
	//bool fir=1;
	for (isid=0; isid<Nsid; isid++)	for (imid=0; imid<Nmid; imid++)	for (icha=0; icha<Ncha; icha++) if (!Empty(isid,imid,icha))
	{
		//if (fir) {ret=Top(isid,imid,icha).local_gate_time; fir=0; }
		if (ret > Top(isid,imid,icha).local_gate_time)
			ret = Top(isid,imid,icha).local_gate_time;
	}
	if(ret==-1)
	{
		fprintf(stderr,"TimeSorter::GetMinLGT(): all q is empty\n");
		exit (-11);
	}
	return ret;
}

int TimeSorter::FindSigWithLGT(uint64_t lgt)
{
	int ret=0;
	for (isid=0; isid<Nsid; isid++)	for (imid=0; imid<Nmid; imid++)	for (icha=0; icha<Ncha; icha++) if (!Empty(isid,imid,icha))
	{
		if (Top(isid,imid,icha).local_gate_time - lgt <= timewindow)
		{
			v_sig.push_back(Top(isid,imid,icha));
			Pop(isid,imid,icha);
			ret++;
		}
	}
	return ret;
}

void TimeSorter::PrintCoin()
{
	fprintf(stdout,"//// Coincidence built ////\n");
	vector<Sig>::iterator it_sig;
	for (it_sig = v_sig.begin(); it_sig!=v_sig.end(); it_sig++)
		(*it_sig).Print();
}



//////// internal methods ////////////// 


uint32_t TimeSorter::Pop(uint8_t isid, uint8_t imid, uint8_t icha)
{
	checker(isid,imid,icha);
	if(Size(isid,imid,icha)==0) exit(-5);
	q_sig[isid][imid][icha].pop();
	return Size(isid,imid,icha);
}

bool TimeSorter::Empty(uint8_t isid, uint8_t imid, uint8_t icha)
{
	checker(isid,imid,icha);
	return q_sig[isid][imid][icha].empty();
}

void TimeSorter::Push(Sig sig)
{
	isid = sig.sid; 
	imid = sig.mid;
	icha = sig.cha;
	checker(isid,imid,icha);
	q_sig[isid][imid][icha].push(sig);
}

uint32_t TimeSorter::Size(uint8_t isid, uint8_t imid, uint8_t icha)
{
	checker(isid,imid,icha);
	return q_sig[isid][imid][icha].size();
}

Sig TimeSorter::Top(uint8_t isid, uint8_t imid, uint8_t icha)
{	
	checker(isid,imid,icha);
	if(Empty(isid,imid,icha))
	{
		fprintf(stderr,"q_sig[isid%u][imid%u][icha%u] is empty, but you tried to call Top()!!\n",isid,imid,icha); exit(-6);
	}
	return q_sig[isid][imid][icha].top();
}

void TimeSorter::Clear()
{

	for(isid=0; isid<Nsid; isid++)	for(imid=0; imid<Nmid; imid++)	for(icha=0; icha<Ncha; icha++)
	{
		while(q_sig[isid][imid][icha].size()>0) 
		{
			Pop(isid,imid,icha);
		}
	}
}

void TimeSorter::PrintTop(uint8_t isid, uint8_t imid, uint8_t icha)
{
	checker(isid,imid,icha);
	Top(isid,imid,icha).Print();
}

void TimeSorter::PrintTopAndPop(uint8_t isid, uint8_t imid, uint8_t icha)
{
	PrintTop(isid,imid,icha);
	Pop(isid,imid,icha);
}

void TimeSorter::PrintTopAll()
{
	for(isid=0; isid<Nsid; isid++)	for(imid=0; imid<Nmid; imid++)	for(icha=0; icha<Ncha; icha++) if(imid%2==1)
	{
		if(Empty(isid,imid,icha)) continue;
		PrintTop(isid, imid, icha);
	}
}

void TimeSorter::PrintSize()
{
	for(isid=0; isid<Nsid; isid++)	for(imid=0; imid<Nmid; imid++)	//if(imid%2==1)
	{
		fprintf(stdout,"\nsid %u mid %u\t", isid, imid);
		for (icha=0     ; icha<Ncha/2; icha++)	fprintf(stdout, "%u\t", Size(isid, imid, icha) );
		fprintf(stdout,"\nsid %u mid %u\t", isid, imid);
		for (icha=Ncha/2 ; icha<Ncha  ; icha++)	fprintf(stdout, "%u\t", Size(isid, imid, icha) );
		
	}
	fprintf(stdout,"\n");
}



bool TimeSorter::checker(uint8_t isid, uint8_t imid, uint8_t icha)
{
	if(isid<Nsid && imid<Nmid && icha<Ncha) return true;
	else
	{
		fprintf(stderr,"TimeSorter::checker(uint8_t isid, uint8_t imid, uint8_t icha): (isid%u<Nsid%d && imid%u<Nmid%d && icha%u<Ncha%d)\n", isid,Nsid,imid,Nmid,icha,Ncha);
		exit(-4);
		return false;
	}
	return false;
}

