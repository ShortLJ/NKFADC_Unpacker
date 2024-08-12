
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>



#include "Global.h"
#include "Sig.h"
#include "TimeSorter.h"

#ifndef __FILEREADER__
#define __FILEREADER__

using namespace std;

class FileReader
{
	public:
		FileReader(char* inputfilename, int itype);
		~FileReader();
		void RegisterTimeSorter (TimeSorter *ts){timesorter=ts;}
		void ReadLoop();
		bool readerEnd=0;

	private:
		char* currfilename;	
		int type; // MTE, TCB, FADC

		FILE *fp;
		int file_size;
		int data_read;
		int evt_processed;
		uint8_t data[8192];
		uint8_t data_length;

		TimeSorter *timesorter;
		int ReadNextAndFill();



};





#endif // __FILEREADER__
