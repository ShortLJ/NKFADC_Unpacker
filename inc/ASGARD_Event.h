#include "Sig.h"
#include "CryHit.h"


#ifndef __ASGARD_EVENT__
#define __ASGARD_EVENT__

using namespace std;

class ASGARD_Event
{
	public:
		vector<CryHit> v_cryhit;

		ASGARD_Event(){	v_cryhit.clear();	}
		ASGARD_Event(vector<Sig>);
		~ASGARD_Event(){	};


	private:
		bool isValid(uint8_t itype, uint8_t idet);
};


#endif //__ASGARD_EVENT__


