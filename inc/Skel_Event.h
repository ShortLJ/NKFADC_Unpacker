#include "Sig.h"
#include "SingleHit.h"


#ifndef __SKEL_EVENT__
#define __SKEL_EVENT__

using namespace std;

class Skel_Event
{
	public:
		vector<SingleHit> v_singlehit;

		Skel_Event(){	v_singlehit.clear();	}
		Skel_Event(vector<Sig>);
		~Skel_Event(){	};


	private:
		bool isValid(uint8_t itype, uint8_t idet);
};


#endif //__SKEL_EVENT__


