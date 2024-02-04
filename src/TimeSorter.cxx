
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "TimeSorter.h"



TimeSorter::TimeSorter(char *inputfilename)
{
	fp = fopen(inputfilename,"rb");
	if (fp==NULL)
	{
		fprintf(stderr,"No file named \"%s\"\n",inputfilename);
		exit(-2);
	}
	fseek(fp, 0L, SEEK_END);
	file_size = ftell(fp)/10;
	fprintf(stdout, "Opened innput File: \"%s\" (%d Bytes)\n",inputfilename, file_size);
	if (file_size<0)
	{
		fprintf(stderr, "file size is larger than 2GB\n");
		exit(-3);
	}
	fseek(fp, 0, SEEK_SET);
	data_read=0;
}



TimeSorter::~TimeSorter()
{
	fclose(fp);
}

int TimeSorter::ReadAndFillQ()
{
	int evt_processed = 0;
	while (data_read < file_size)
	{
		//fprintf(stdout, "data_reading after = %d/%d\n", data_read, file_size);
		data_read += fread(data, 1, 32, fp);
		data_length = data[0] & 0x00FF;
		if (data_length != 32) 
		{
			fprintf(stderr, "\ndata_length %u!=32\n data_read += fread(data, 1, 8160, fp);\n",data_length);
			data_read += fread(data, 1, 8160, fp);
		}      
		else
		{
			sig_tmp = Sig(data);
		}
		fprintf(stdout, "\rdata_read to= %d/%d\t", data_read, file_size);

		Push(sig_tmp);
		evt_processed++;
		fprintf(stdout,"evt_processed %d", evt_processed);
		fflush(stdout);


	}
	fprintf(stdout,"\n");
	fprintf(stdout,"\n");

	return evt_processed;
}

bool TimeSorter::AllEmpty()
{
	for (isid=0; isid<Nsid; isid++)	for (imid=0; imid<Nmid; imid++)	for (ich=0; ich<Nch; ich++)
	{
		if (!Empty(isid,imid,ich)) return 0;
	}
	return 1;
}

uint64_t TimeSorter::GetMinLGT()
{
	uint64_t ret=-1;
	//bool fir=1;
	for (isid=0; isid<Nsid; isid++)	for (imid=0; imid<Nmid; imid++)	for (ich=0; ich<Nch; ich++) if (!Empty(isid,imid,ich))
	{
		//if (fir) {ret=Top(isid,imid,ich).local_gate_time; fir=0; }
		if (ret > Top(isid,imid,ich).local_gate_time)
			ret = Top(isid,imid,ich).local_gate_time;
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
	for (isid=0; isid<Nsid; isid++)	for (imid=0; imid<Nmid; imid++)	for (ich=0; ich<Nch; ich++) if (!Empty(isid,imid,ich))
	{
		if (Top(isid,imid,ich).local_gate_time - lgt <= timewindow)
		{
			v_sig.push_back(Top(isid,imid,ich));
			Pop(isid,imid,ich);
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


uint32_t TimeSorter::Pop(uint8_t isid, uint8_t imid, uint8_t ich)
{
	checker(isid,imid,ich);
	if(Size(isid,imid,ich)==0) exit(-5);
	q_sig[isid][imid][ich].pop();
	return Size(isid,imid,ich);
}

bool TimeSorter::Empty(uint8_t isid, uint8_t imid, uint8_t ich)
{
	checker(isid,imid,ich);
	return q_sig[isid][imid][ich].empty();
}

void TimeSorter::Push(Sig sig)
{
	isid = sig.sid; 
	imid = sig.mid;
	ich = sig.ch;
	checker(isid,imid,ich);
	q_sig[isid][imid][ich].push(sig);
}

uint32_t TimeSorter::Size(uint8_t isid, uint8_t imid, uint8_t ich)
{
	checker(isid,imid,ich);
	return q_sig[isid][imid][ich].size();
}

Sig TimeSorter::Top(uint8_t isid, uint8_t imid, uint8_t ich)
{	
	checker(isid,imid,ich);
	if(Empty(isid,imid,ich))
	{
		fprintf(stderr,"q_sig[isid%u][imid%u][ich%u] is empty, but you tried to call Top()!!\n",isid,imid,ich); exit(-6);
	}
	return q_sig[isid][imid][ich].top();
}

void TimeSorter::Clear()
{

	for(isid=0; isid<Nsid; isid++)	for(imid=0; imid<Nmid; imid++)	for(ich=0; ich<Nch; ich++)
	{
		while(q_sig[isid][imid][ich].size()>0) 
		{
			Pop(isid,imid,ich);
		}
	}
}

void TimeSorter::PrintTop(uint8_t isid, uint8_t imid, uint8_t ich)
{
	checker(isid,imid,ich);
	Top(isid,imid,ich).Print();
}

void TimeSorter::PrintTopAndPop(uint8_t isid, uint8_t imid, uint8_t ich)
{
	PrintTop(isid,imid,ich);
	Pop(isid,imid,ich);
}

void TimeSorter::PrintTopAll()
{
	for(isid=0; isid<Nsid; isid++)	for(imid=0; imid<Nmid; imid++)	for(ich=0; ich<Nch; ich++) if(imid%2==1)
	{
		if(Empty(isid,imid,ich)) continue;
		PrintTop(isid, imid, ich);
	}
}

void TimeSorter::PrintSize()
{
	for(isid=0; isid<Nsid; isid++)	for(imid=0; imid<Nmid; imid++)	//if(imid%2==1)
	{
		fprintf(stdout,"\nsid %u mid %u\t", isid, imid);
		for (ich=0     ; ich<Nch/2; ich++)	fprintf(stdout, "%u\t", Size(isid, imid, ich) );
		fprintf(stdout,"\nsid %u mid %u\t", isid, imid);
		for (ich=Nch/2 ; ich<Nch  ; ich++)	fprintf(stdout, "%u\t", Size(isid, imid, ich) );
		
	}
	fprintf(stdout,"\n");
}



bool TimeSorter::checker(uint8_t isid, uint8_t imid, uint8_t ich)
{
	if(isid<Nsid && imid<Nmid && ich<Nch) return true;
	else
	{
		fprintf(stderr,"TimeSorter::checker(uint8_t isid, uint8_t imid, uint8_t ich): (isid%u<Nsid%d && imid%u<Nmid%d && ich%u<Nch%d)\n", isid,Nsid,imid,Nmid,ich,Nch);
		exit(-4);
		return false;
	}
	return false;
}

