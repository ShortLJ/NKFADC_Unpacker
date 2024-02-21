#include "Global.h"
#include "Sig.h"

#ifndef __FVHIT__
#define __FVHIT__

using namespace std;

class FVHit : public Sig
{
	public:
		uint8_t det;
		uint8_t pdet;
		uint8_t pcry;
		uint8_t idx;

		float Energy; // 32 bit: 1bit sign, 8bit exponent, 23bit fraction > 16 bit ADC

		FVHit(){	};
		FVHit(Sig sig);
		FVHit(uint8_t det, uint8_t idx, Sig sig);
		~FVHit(){	};

		void Clear();

	public:

		/*
		virtual void Clear(Option_t* = "");

		void SetValues(Int_t _detID, Int_t _stripID, Int_t _padID,
				Int_t _stripValU, Int_t _stripValD, Int_t _padVal);

		inline Int_t    GetStripSum()  { return (stripValU + stripValD); }
		inline Int_t    GetStripDiff() { return (stripValU - stripValD); }
		inline Double_t GetStripDiffR() { return double(GetStripDiff())/GetStripSum(); }

		ClassDef(TAnaX6, 1)
		*/
};



#endif // __FVHIT__



