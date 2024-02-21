
#define Ncry 4
#define Nfv 2
#define Nseg 8

#include "NK.h"

void sample_spectrum()
{
	TChain *chain  = new TChain("nkfadc");
	chain->Add("output.root");
	NK *nk = new NK(chain);

	const Long64_t entries = nk->fChain->GetEntries();
	const Long64_t permille = entries/1000;

	uint8_t icry;
	uint8_t ifv;
	uint8_t iseg;



	TH1I *h1_ADC_FV[Ncry][Nfv];
	for (icry=0; icry<Ncry; icry++)	for (ifv=0; ifv<Nfv; ifv++)
	{
		h1_ADC_FV[icry][ifv] = new TH1I(
				Form("h1_ADC_FV_cry%u_fv%u",icry,ifv),
				Form("h1_ADC_FV_cry%u_fv%u; ADC; count",icry,ifv),
				0x10000>>3, 0,0x10000);
	}
	TH1I *h1_ADC_Seg[Ncry][Nseg];
	for (icry=0; icry<Ncry; icry++)	for (iseg=0; iseg<Nseg; iseg++)
	{
		h1_ADC_Seg[icry][iseg] = new TH1I(
				Form("h1_ADC_Seg_cry%u_seg%u",icry,iseg),
				Form("h1_ADC_Seg_cry%u_seg%u; ADC; count",icry,iseg),
				0x10000>>3, 0,0x10000);
	}
	


	Long64_t ient=0;
	for (ient=0; ient<entries; ient++)
	{
		nk->GetEntry(ient);

		ASGARD_Event *asgard_event = nk->ASGARD_Event;
		

		vector<CryHit>::iterator cryhit;
		for (cryhit=asgard_event->v_cryhit.begin(); cryhit!=asgard_event->v_cryhit.end(); ++cryhit)
		{
			icry = cryhit->pcry;
			vector<FVHit>::iterator fvhit;
			vector<SegHit>::iterator seghit;
			for (fvhit=cryhit->v_fvhit.begin(); fvhit!=cryhit->v_fvhit.end(); ++fvhit)
			{
				ifv = fvhit->idx;
				h1_ADC_FV[icry][ifv]->Fill(fvhit->peak);
			}
			for (seghit=cryhit->v_seghit.begin(); seghit!=cryhit->v_seghit.end(); ++seghit)
			{
				iseg = seghit->idx;
				h1_ADC_Seg[icry][iseg]->Fill(seghit->peak);
			}
	
		}



	}
	
	TVirtualPad *pad;
	TCanvas *c1 = new TCanvas("c1_FV","c1_FV",1200,800);
	c1->Divide(4,2);

	for (icry=0; icry<Ncry; icry++)	for (ifv=0; ifv<Nfv; ifv++)
	{
		pad = c1->cd(1+icry+Ncry*ifv);
		h1_ADC_FV[icry][ifv]->Draw();

	}

	TCanvas *c2 = new TCanvas("c2_Seg","c2_Seg",1200,800);
	c2->Divide(4,8);
	for (icry=0; icry<Ncry; icry++)	for (iseg=0; iseg<Nseg; iseg++)
	{
		pad = c2->cd(1+icry+Ncry*iseg);
		h1_ADC_Seg[icry][iseg]->Draw();
	}


}
