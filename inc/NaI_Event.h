#include "Sig.h"
#include "NaIHit.h"
#include <stdlib.h>
#include <vector>

#ifndef __NaI_EVENT__
#define __NaI_EVENT__

using namespace std;

class NaI_Event
{
	public:
		vector<NaIHit> v_naihit;

		NaI_Event(){	v_naihit.clear();	}
		NaI_Event(vector<Sig>);
		~NaI_Event(){	};


	private:
		bool isValid(uint8_t itype, uint8_t idet);
};


#endif //__NaI_EVENT__


