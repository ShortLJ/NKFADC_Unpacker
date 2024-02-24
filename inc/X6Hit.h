#include "TObject.h"

#include <vector>

#include "Global.h"
#include "StripHit.h"
#include "OhmicHit.h"

#ifndef __X6HIT__
#define __X6HIT__

using namespace std;

class X6Hit //: public TObject
{
	public:
		uint8_t det;

		vector<OhmicHit> v_ohmichit;
		vector<StripHit> v_strpUhit;
		vector<StripHit> v_strpDhit;
		

		X6Hit(){	};
		X6Hit(uint8_t idet, vector<Sig> v_sig_ohmic, vector<Sig> v_sig_strip);
		~X6Hit(){	};

		void Clear();
		void Print();

	public:

		/*
		virtual void Clear(Option_t* = "");

		void SetValues(Int_t _X6ID, Int_t _stripID, Int_t _padID,
				Int_t _stripValU, Int_t _stripValD, Int_t _padVal);

		inline Int_t    GetStripSum()  { return (stripValU + stripValD); }
		inline Int_t    GetStripDiff() { return (stripValU - stripValD); }
		inline Double_t GetStripDiffR() { return double(GetStripDiff())/GetStripSum(); }

		ClassDef(TAnaX6, 1)
		*/
	private:
		bool isValid();
};



#endif // __X6HIT__



