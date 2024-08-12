

#include "FileReader.h"

FileReader::FileReader(char* inputfilename, int itype)
	:currfilename(inputfilename), type(itype)
{
	fp = fopen(currfilename,"rb");
	if (fp==NULL)
	{
		fprintf(stderr,"No file named \"%s\"\n",inputfilename);
		exit(-2);
	}
	fseek(fp, 0L, SEEK_END);
	file_size = ftell(fp);
	fprintf(stdout, "Opened innput File: \"%s\" (%d Bytes)\n",inputfilename, file_size);
	if (file_size<0)
	{
		fprintf(stderr, "file size is larger than 2GB\n");
		exit(-3);
	}
	fseek(fp, 0, SEEK_SET);
	data_read=0;
	evt_processed=0;
	if (itype==0) fprintf(stdout, "type: MTE\n");
	else if (itype==1) fprintf(stdout, "type: TCB\n");
	else if (itype==2) fprintf(stdout, "type: FADC\n");
	else {fprintf(stderr, "type: unknown!\n"); exit(-1);}

}

FileReader::~FileReader()
{
	fclose(fp);
}

int FileReader::ReadNextAndFill()
{
	if (data_read >= file_size)
	{
		fprintf(stdout, "data_read >= file_size (reached file end)\n");
		return 0;
	}
	//fprintf(stdout, "data_reading after = %d/%d\n", data_read, file_size);
	int ret = fread(data, 1, 32, fp);
	data_length = data[0] & 0xFF;
	if (data_length != 32) 
	{
		fprintf(stderr, "\ndata_length %u!=32\n data_read += fread(data, 1, 8160, fp);\n",data_length);
		ret += fread(data, 1, 8160, fp);
	}      
	else
	{
		Sig sig_tmp(data);
		timesorter->Push(sig_tmp);
		evt_processed++;
	}
	data_read+=ret;
	if ((data_read & 0xff)==0)
	{
		fprintf(stdout, "\rdata_read to= %d/%d\t", data_read, file_size);
		fprintf(stdout,"evt_processed %d", evt_processed);
		fflush(stdout);
	}
	return ret;
}

void FileReader::ReadLoop()
{
	while (data_read < file_size)
	{
		ReadNextAndFill();
	}
	readerEnd=1;
}
		




