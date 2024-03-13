
#include "Global.h"

#include "NK.h"

void sample_spectrum_2d_sumdiff()
{
	TChain *chain  = new TChain("nkfadc");
	chain->Add("output.root");
	NK *nk = new NK(chain);

	const Long64_t entries = nk->fChain->GetEntries();
	const Long64_t permille = entries/1000;

	uint8_t ix6;
	uint8_t iohmic;
	uint8_t istrip, jstrip;


	TH2I *h2N_idx_ADCohmic;
	TH2I *h2N_idx_ADCstripSum;
	TH2I *h2N_idx_ADCstripDiff;
	h2N_idx_ADCohmic = new TH2I(
				Form("h2N_idx_ADCohmic"),
				Form("h2N_idx_ADCohmic; Ohmic idx; ADC; count"),
				Nohmic*Ndet, 0, Nohmic*Ndet,	
				0x10000>>3, 0,0x10000);
	h2N_idx_ADCstripSum = new TH2I(
				Form("h2N_idx_ADCstripSum"),
				Form("h2N_idx_ADCstripSum; strip idx; ADC; count"),
				Nstrip*Ndet/2, 0, Nstrip*Ndet/2,	
				0x10000>>3, 0,0x10000);
	h2N_idx_ADCstripDiff = new TH2I(
				Form("h2N_idx_ADCstripDiff"),
				Form("h2N_idx_ADCstripDiff; strip idx; ADC; count"),
				Nstrip*Ndet/2, 0, Nstrip*Ndet/2,	
				0x10000>>3,-1*(0x10000>>1),0x10000>>1);






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
			vector<StripHit>::iterator stripU, stripD;
			for (ohmichit=x6hit->v_ohmichit.begin(); ohmichit!=x6hit->v_ohmichit.end(); ++ohmichit)
			{
				iohmic = ohmichit->idx;
				h2N_idx_ADCohmic->Fill(iohmic+ix6*Nohmic, ohmichit->peak);
			}
			for (stripU=x6hit->v_strpUhit.begin(); stripU!=x6hit->v_strpUhit.end(); ++stripU)	for (stripD=x6hit->v_strpDhit.begin(); stripD!=x6hit->v_strpDhit.end(); ++stripD) if (stripU!=stripD)
			{
				istrip = stripU->idx;
				jstrip = stripD->idx;
				h2N_idx_ADCstripSum->Fill(istrip+ix6*Nstrip/2, (stripU->peak + stripD->peak));
				h2N_idx_ADCstripDiff->Fill(istrip+ix6*Nstrip/2, (stripU->peak - stripD->peak));
			}
		}
	}
	
	TVirtualPad *pad;
	TCanvas *c1 = new TCanvas("c1_Ohmic","c1_Ohmic",1200,800);
	pad = c1->cd();
	h2N_idx_ADCohmic->Draw("colz");


	TCanvas *c2 = new TCanvas("c2_StripU","c2_StripU",1200,800);
	pad = c2->cd();
	h2N_idx_ADCstripSum->Draw("colz");

	TCanvas *c3 = new TCanvas("c3_StripD","c3_StripD",1200,800);
	pad = c3->cd();
	h2N_idx_ADCstripDiff->Draw("colz");



}
