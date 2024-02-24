

#include "Global.h"

#include "TimeSorter.h"
//#include "segHit.h"
//#include "FVHit.h"
//#include "CryHit.h"

#ifndef __HITBUILDER__
#define __HITBUILDER__

uint8_t	map_type		[N_SID][N_MID][N_CHA];// = {{{0xFF}}};
uint8_t	map_det			[N_SID][N_MID][N_CHA];// = {{{0xFF}}};
uint8_t	map_idx[Ntype]	[N_SID][N_MID][N_CHA];// = {{{0xFF}}};




using namespace std;

class HitBuilder
{
	public:
		HitBuilder();
		~HitBuilder();

		void ReadMapFile(const char *);
		void SortByDet(vector<Sig>);
		int Size(uint8_t idet, uint8_t itype);
		//CryHit GetCryHit(uint8_t idet);


		void Clear();
		bool isGood();


	private:

		vector<Sig> 	v_sig[Ntype][Ndet];

		uint8_t itype; 
		uint8_t idet; uint8_t iidx;
		uint8_t isid; uint8_t imid; uint8_t ich;

		bool isvalid(uint8_t, uint8_t,uint8_t);
		
};
#endif // __HITBUILDER__




