
#include "NKFADC_Skel.C"
#define Ndim 2

void DrawHist_peak_peak()
{
	TChain *ch = new TChain("nkfadc");
	ch->Add("aa.root");
	NKFADC_Skel *nk = new NKFADC_Skel(ch);

	const Long64_t nent = nk->fChain->GetEntries();

	uint8_t isid[Ndim];
	uint8_t imid[Ndim];
	uint8_t icha[Ndim];

	uint32_t iidx[Ndim];
	uint8_t idet[Ndim];

	TH2I *h2_peak_peak[4][4];
	for (idet[0]=0; idet[0]<4; idet[0]++) for (idet[1]=0; idet[1]<4; idet[1]++) 
	{
		h2_peak_peak[idet[0]][idet[1]] = new TH2I (
			Form("h2_peak_peak_%02d_%02d",idet[0],idet[1]),
			Form("h2_peak_peak_%02d_%02d; peak%02d; peak%02d",idet[0],idet[1], idet[0],idet[1]),
			0b1<<10, 0, 0b1<<(16-3),
			0b1<<10, 0, 0b1<<(16-3) );
	}


	//TH2I *h2_cha_peak = new TH2I("h2_cha_peak","h2_cha_peak; cha; peak", 
	//		Nsid*Nmid*Nch, 0, Nsid*Nmid*Nch,
	//		0b1<<10, 0, 0b1<<(16-4));

	Long64_t ient=0;
	Long64_t loop=0;

	for ( ient=0, loop=0;
			ient<nent;
			ient++, loop++)
	{
		if ((loop&0xff)==0)
		{
			fprintf(stdout, "\rient %lld of %lld (%.1f%%)",ient,nent,100.*ient/nent);
		}

		nk->GetEntry(ient);

		vector<SingleHit>::iterator it_SingleHit[Ndim];
		vector<Det1Hit>::iterator it_Det1Hit[Ndim];

		for ( it_SingleHit[0]=nk->Skel_Event->v_singlehit.begin(); it_SingleHit[0]!=nk->Skel_Event->v_singlehit.end(); it_SingleHit[0]++)
		{
			for ( it_Det1Hit[0]=it_SingleHit[0]->v_det1hit.begin(); it_Det1Hit[0]!=it_SingleHit[0]->v_det1hit.end(); it_Det1Hit[0]++)
			{
				isid[0] = it_Det1Hit[0]->sid;
				imid[0] = it_Det1Hit[0]->mid - 1;
				icha[0] = it_Det1Hit[0]->ch;
				iidx[0] = icha[0]+Nch*(imid[0]+Nmid*isid[0]);
				idet[0] = icha[0]+2*isid[0];

				for ( it_SingleHit[1]=nk->Skel_Event->v_singlehit.begin(); it_SingleHit[1]!=nk->Skel_Event->v_singlehit.end(); it_SingleHit[1]++)
				{
					for ( it_Det1Hit[1]=it_SingleHit[1]->v_det1hit.begin(); it_Det1Hit[1]!=it_SingleHit[1]->v_det1hit.end(); it_Det1Hit[1]++)
					{
						isid[1] = it_Det1Hit[1]->sid;
						imid[1] = it_Det1Hit[1]->mid - 1;
						icha[1] = it_Det1Hit[1]->ch;
						iidx[1] = icha[1]+Nch*(imid[1]+Nmid*isid[1]);
						idet[1] = icha[1]+2*isid[1];

						h2_peak_peak[idet[0]][idet[1]]->Fill(it_Det1Hit[0]->peak, it_Det1Hit[1]->peak);
					}
				}
			}
		}
	}
	fprintf(stdout, "\rient %lld of %lld (%.1f%%)",ient,nent,100.*ient/nent);
	fprintf(stdout,"\n");
}




