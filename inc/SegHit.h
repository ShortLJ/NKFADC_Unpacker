
#include "Global.h"

#include "TObject.h"
#include "Sig.h"

#ifndef __SEGHIT__
#define __SEGHIT__

using namespace std;

class SegHit : public Sig
{
	public:
		uint8_t det;
		uint8_t crystal;
		uint8_t idx;

		float Energy; // 32 bit: 1bit sign, 8bit exponent, 23bit fraction > 16 bit ADC

		SegHit();
		SegHit(Sig sig);
		SegHit(uint8_t det, uint8_t crystal, uint8_t idx, Sig sig);
		~SegHit();

		void Clear();

		ClassDef(SegHit, 1)


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



#endif // __SEGHIT__



