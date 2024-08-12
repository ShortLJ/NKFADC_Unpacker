
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
		uint32_t Pop(uint8_t sid, uint8_t mid, uint8_t ch);
		Sig Top(uint8_t sid, uint8_t mid, uint8_t ch);
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

		priority_queue<Sig> q_sig[Nsid][Nmid][Nch];
		uint8_t isid; uint8_t imid; uint8_t ich;
	
		bool Empty(uint8_t sid, uint8_t mid, uint8_t ch);
		uint32_t Size(uint8_t sid, uint8_t mid, uint8_t ch);
		virtual void Clear();
		void PrintTopAll();
		void PrintTop(uint8_t sid, uint8_t mid, uint8_t ch);
		void PrintTopAndPop(uint8_t sid, uint8_t mid, uint8_t ch);
		void Print(uint8_t sid, uint8_t mid, uint8_t ch);

		bool checker(uint8_t sid, uint8_t mid, uint8_t ch);
	private:
		int64_t timewindow = 0;
		vector<Sig> v_sig;
};








#endif // __TIMESORTER__


