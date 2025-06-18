
#include <queue>

#include "Global.h"
#include "Sig.h"


#ifndef __TIMESORTER__
#define __TIMESORTER__

using namespace std;

class TimeSorter
{
	public:
		TimeSorter();
		~TimeSorter();

		void Push(Sig sig);
		uint32_t Pop(uint8_t sid, uint8_t mid, uint8_t cha);
		Sig Top(uint8_t sid, uint8_t mid, uint8_t cha);
		void PrintSize();
		bool AllEmpty();

		void SetTimeWindow(int64_t tw) {timewindow=tw;}
		uint64_t GetMinLGT();
		int FindSigWithLGT(uint64_t lgt);
		vector<Sig> GetCoinvSig() {return v_sig;}
		void PrintCoin();

		void ClearCoinSig() {v_sig.clear();}


	private:
		Sig sig_tmp;

		priority_queue<Sig> q_sig[Nsid][Nmid][Ncha];
		uint8_t isid; uint8_t imid; uint8_t icha;
	
		bool Empty(uint8_t sid, uint8_t mid, uint8_t cha);
		uint32_t Size(uint8_t sid, uint8_t mid, uint8_t cha);
		virtual void Clear();
		void PrintTopAll();
		void PrintTop(uint8_t sid, uint8_t mid, uint8_t cha);
		void PrintTopAndPop(uint8_t sid, uint8_t mid, uint8_t cha);
		void Print(uint8_t sid, uint8_t mid, uint8_t cha);

		bool checker(uint8_t sid, uint8_t mid, uint8_t cha);
	private:
		int64_t timewindow = 0;
		vector<Sig> v_sig;
};








#endif // __TIMESORTER__


