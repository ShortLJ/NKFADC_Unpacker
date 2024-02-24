#include "Sig.h"
#include "X6Hit.h"


#ifndef __STARKJR_EVENT__
#define __STARKJR_EVENT__

using namespace std;

class STARKJR_Event
{
	public:
		vector<X6Hit> v_x6hit;

		STARKJR_Event(){	v_x6hit.clear();	}
		STARKJR_Event(vector<Sig>);
		~STARKJR_Event(){	};


	private:
		bool isValid(uint8_t itype, uint8_t idet);
};


#endif //__STARKJR_EVENT__


