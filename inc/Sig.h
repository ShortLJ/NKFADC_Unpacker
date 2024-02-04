

#include <stdio.h>
#include <stdint.h>

#ifndef __SIG__
#define __SIG__

class Sig
{
	public: 
		uint32_t tcb_trigger_number;
		uint64_t tcb_trigger_time;

		uint32_t local_trigger_number;
		uint64_t local_gate_time;

		uint8_t sid;
		uint8_t mid;
		uint8_t ch;

		uint16_t peak;
		uint16_t timing;

		uint8_t flag; // pile_up flag @ bit1, hit flag @ bit0

		Sig() {	}
		Sig(uint8_t *data);
		~Sig() {	}

	public: 
		void Print();

		bool operator<(const Sig sig) const
		{
			return this->local_gate_time > sig.local_gate_time;
		}
	protected:


	private:
		uint8_t data_length;
		uint8_t trigger_type;

		uint32_t local_trigger_pattern;

		uint16_t tcb_trigger_fine_time;
		uint32_t tcb_trigger_coarse_time;
		uint16_t local_gate_fine_time;
		uint64_t local_gate_coarse_time;

};


#endif // __SIG__
