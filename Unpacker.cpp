#include<unistd.h>


#include <queue>
#include <cstring>

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "TFile.h"
#include "TTree.h"

#include "Sig.h"
#include "TimeSorter.h"
#include "HitBuilder.h"
#include "STARKJR_Event.h"


void print_usage()
{
	fprintf(stdout,"STARKJR_Unpacker \\\n");
	fprintf(stdout,"--input,-i <file.dat>\\\n");
	fprintf(stdout,"--output,-o <file.root>\\\n");
	fprintf(stdout,"--map,-m <file.txt>\\\n");
	fprintf(stdout,"--timewindow,-tw <timewindow> ## 8 ns for NKfadc\\\n");
}

int main(int argc, char *argv[])
{
	char *inputfilename;
	char *outputfilename;
	char *mapfilename;
 	int64_t timewindow = 0;



	if (argc<2)
	{
		print_usage();
		return -1;
	}
	for (int i=1; i<argc; i++)
	{
		if ((strcmp(argv[i],"--input")==0 || strcmp(argv[i],"-i")==0) && (argv[i+1]))
		{
			inputfilename = argv[++i];
		}
		else if ((strcmp(argv[i],"--output")==0 || strcmp(argv[i],"-o")==0) && (argv[i+1]))
		{
			outputfilename = argv[++i];
		}
		else if ((strcmp(argv[i],"--map")==0 || strcmp(argv[i],"-m")==0) && (argv[i+1]))
		{
			mapfilename = argv[++i];
		}
		else if ((strcmp(argv[i],"--timewindow")==0 || strcmp(argv[i],"-tw")==0) && (argv[i+1]))
		{
			timewindow = atoll(argv[++i]);
		}
	
		else if (strcmp(argv[i],"-h")==0)
		{
			print_usage();
			return 0;
		}
		else
		{
			fprintf(stderr,"invalid opt\n");
			print_usage();
			return -1;
		}
	}
	if (inputfilename==NULL || outputfilename==NULL)
	{
		fprintf(stderr,"Specify input file name and output file name\n");
		return -1;
	}

	TimeSorter timesorter(inputfilename);
	timesorter.SetTimeWindow(timewindow);

	HitBuilder hitbuilder;
	hitbuilder.ReadMapFile(mapfilename);


	TFile *file = new TFile(outputfilename,"recreate");
	TTree *tree = new TTree("nkfadc","nkfadc");
	STARKJR_Event starkjr_event = STARKJR_Event();
	tree->Branch("STARKJR_Event", "STARKJR_Event", &starkjr_event, 32000, 0 );



	timesorter.ReadAndFillQ();
	timesorter.PrintSize();

	while(!timesorter.AllEmpty())
	{
		timesorter.ClearCoinSig();
		//hitbuilder.Clear();

		uint64_t minlgt = timesorter.GetMinLGT();
		int size =0;
		size+=timesorter.FindSigWithLGT(minlgt);
		size+=timesorter.FindSigWithLGT(minlgt);
		vector<Sig> v_sig_coin = timesorter.GetCoinvSig();
		
		starkjr_event = STARKJR_Event(v_sig_coin);


		//fprintf(stdout,"event.size() %d\n",event.size());
		//if(!event.empty()) 
		tree->Fill();
	}

	tree->Write();
	file->Close();

	return 0;

}

