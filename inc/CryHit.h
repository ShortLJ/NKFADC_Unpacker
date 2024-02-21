#include "TObject.h"

#include <vector>

#include "Global.h"
#include "SegHit.h"
#include "FVHit.h"

#ifndef __CRYHIT__
#define __CRYHIT__

using namespace std;

class CryHit //: public TObject
{
	public:
		uint8_t det;
		uint8_t pdet;
		uint8_t pcry;

		vector<FVHit> v_fvhit;
		vector<SegHit> v_seghit;
		

		CryHit(){	};
		CryHit(uint8_t idet, vector<Sig> v_sig_fv, vector<Sig> v_sig_seg);
		~CryHit(){	};

		void Clear();
		void Print();

	public:

		/*
		virtual void Clear(Option_t* = "");

		void SetValues(Int_t _CryID, Int_t _stripID, Int_t _padID,
				Int_t _stripValU, Int_t _stripValD, Int_t _padVal);

		inline Int_t    GetStripSum()  { return (stripValU + stripValD); }
		inline Int_t    GetStripDiff() { return (stripValU - stripValD); }
		inline Double_t GetStripDiffR() { return double(GetStripDiff())/GetStripSum(); }

		ClassDef(TAnaX6, 1)
		*/
	private:
		bool isValid();
};



#endif // __CRYHIT__



