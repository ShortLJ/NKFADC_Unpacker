
#include "Global.h"

#include "NK.h"

void sample_spectrum_2d()
{
	TChain *chain  = new TChain("nkfadc");
	chain->Add("output.root");
	NK *nk = new NK(chain);

	const Long64_t entries = nk->fChain->GetEntries();
	const Long64_t permille = entries/1000;

	uint8_t ix6;
	uint8_t iohmic;
	uint8_t istrip;


	TH2I *h2N_run_ADCohmic;
	TH2I *h2N_run_ADCstripU;
	TH2I *h2N_run_ADCstripD;
	h2N_run_ADCohmic = new TH2I(
				Form("h2N_run_ADCohmic"),
				Form("h2N_run_ADCohmic; Ohmic idx; ADC; count"),
				Nohmic*Ndet, 0, Nohmic*Ndet,	
				0x10000>>3, 0,0x10000);
	h2N_run_ADCstripU = new TH2I(
				Form("h2N_run_ADCstripU"),
				Form("h2N_run_ADCstripU; strip idx; ADC; count"),
				Nstrip*Ndet/2, 0, Nstrip*Ndet/2,	
				0x10000>>3, 0,0x10000);
	h2N_run_ADCstripD = new TH2I(
				Form("h2N_run_ADCstripD"),
				Form("h2N_run_ADCstripD; strip idx; ADC; count"),
				Nstrip*Ndet/2, 0, Nstrip*Ndet/2,	
				0x10000>>3, 0,0x10000);






	Long64_t ient=0;
	for (ient=0; ient<entries; ient++)
	{
		nk->GetEntry(ient);

		STARKJR_Event *starkjr_event = nk->STARKJR_Event;
		

		vector<X6Hit>::iterator x6hit;
		for (x6hit=starkjr_event->v_x6hit.begin(); x6hit!=starkjr_event->v_x6hit.end(); ++x6hit)
		{
			ix6 = x6hit->det;
			vector<OhmicHit>::iterator ohmichit;
			vector<StripHit>::iterator striphit;
			for (ohmichit=x6hit->v_ohmichit.begin(); ohmichit!=x6hit->v_ohmichit.end(); ++ohmichit)
			{
				iohmic = ohmichit->idx;
				h2N_run_ADCohmic->Fill(iohmic+ix6*Nohmic, ohmichit->peak);
			}
			for (striphit=x6hit->v_strpUhit.begin(); striphit!=x6hit->v_strpUhit.end(); ++striphit)
			{
				istrip = striphit->idx;
				h2N_run_ADCstripU->Fill(istrip+ix6*Nstrip/2, striphit->peak);
			}
			for (striphit=x6hit->v_strpDhit.begin(); striphit!=x6hit->v_strpDhit.end(); ++striphit)
			{
				istrip = striphit->idx;
				h2N_run_ADCstripD->Fill(istrip+ix6*Nstrip/2, striphit->peak);
			}
		}
	}
	
	TVirtualPad *pad;
	TCanvas *c1 = new TCanvas("c1_Ohmic","c1_Ohmic",1200,800);
	pad = c1->cd();
	h2N_run_ADCohmic->Draw("colz");


	TCanvas *c2 = new TCanvas("c2_StripU","c2_StripU",1200,800);
	pad = c2->cd();
	h2N_run_ADCstripU->Draw("colz");

	TCanvas *c3 = new TCanvas("c3_StripD","c3_StripD",1200,800);
	pad = c3->cd();
	h2N_run_ADCstripD->Draw("colz");



}
