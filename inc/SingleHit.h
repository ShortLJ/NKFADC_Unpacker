//#include "TObject.h"

#include <vector>

#include "Global.h"
#include "Det1Hit.h"
//#include "Det2Hit.h"

#ifndef __SINGLEHIT__
#define __SINGLEHIT__

using namespace std;

class SingleHit //: public TObject
{
	public:
		uint8_t det;
		uint8_t pdet;
		uint8_t pcry;

		vector<Det1Hit> v_det1hit;
		//vector<Det2Hit> v_det2hit;
		

		SingleHit(){	};
		SingleHit(uint8_t idet, vector<Sig> v_sig_det1/*, vector<Sig> v_sig_det2*/);
		~SingleHit(){	};

		void Clear();
		void Print();

	public:

		/*
		virtual void Clear(Option_t* = "");

		void SetValues(Int_t _SingleID, Int_t _stripID, Int_t _padID,
				Int_t _stripValU, Int_t _stripValD, Int_t _padVal);

		ClassDef(TAnaX6, 1)
		*/
	private:
		bool isValid();
};



#endif // __SINGLEHIT__



