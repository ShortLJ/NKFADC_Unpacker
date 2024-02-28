
#define Ncry 4
#define Nfv 2
#define Nseg 8

#include "NK.h"

void sample_spectrum_2d()
{
	TChain *chain  = new TChain("nkfadc");
	chain->Add("output.root");
	NK *nk = new NK(chain);

	const Long64_t entries = nk->fChain->GetEntries();
	const Long64_t permille = entries/1000;

	uint8_t icry;
	uint8_t ifv;
	uint8_t iseg;


	TH2I *h2N_idx_ADCfv;
	TH2I *h2N_idx_ADCseg;
	h2N_idx_ADCfv = new TH2I(
				Form("h2N_idx_ADCfv"),
				Form("h2N_idx_ADCfv; FV idx; ADC; count"),
				Nfv*Ncry, 0, Nfv*Ncry,	
				0x10000>>3, 0,0x10000);
	h2N_idx_ADCseg = new TH2I(
				Form("h2N_idx_ADCseg"),
				Form("h2N_idx_ADCseg; seg idx; ADC; count"),
				Nseg*Ncry, 0, Nseg*Ncry,	
				0x10000>>3, 0,0x10000);





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
				h2N_idx_ADCfv->Fill(ifv+icry*Nfv, fvhit->peak);
			}
			for (seghit=cryhit->v_seghit.begin(); seghit!=cryhit->v_seghit.end(); ++seghit)
			{
				iseg = seghit->idx;
				h2N_idx_ADCseg->Fill(iseg+icry*Nseg, seghit->peak);
			}
	
		}



	}
	
	TVirtualPad *pad;
	TCanvas *c1 = new TCanvas("c1_FV","c1_FV",1200,800);
	pad = c1->cd();
	h2N_idx_ADCfv->Draw("colz");


	TCanvas *c2 = new TCanvas("c2_Seg","c2_Seg",1200,800);
	pad = c2->cd();
	h2N_idx_ADCseg->Draw("colz");


}
