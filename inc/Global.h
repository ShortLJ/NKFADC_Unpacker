
#ifndef __GLOBAL__
#define __GLOBAL__


//// maxium
#define N_SID 16 // 0~15 sid mask 0xF0
#define N_MID 10 // 0~9 mid mask 0x0F but a crate has 10 board slots
#define N_CHA 32 // 0~9 cha mask 0xFF but NKFADC10 has 10 mcx inputs

//// used
#define Nsid 1
#define Nmid 10
#define Nch 32

#define Ndet 6 // 6 'X6' for backward
#define Ntype 2 // pad(ohmic) and strip(junction)
#define Ntype0 4 // 4 pads per x6
#define Ntype1 16 // 8 strips per x6, Up and Down

#define Nohmic Ntype0
#define Nstrip Ntype1

#include <stdint.h>
extern uint8_t	map_type		[N_SID][N_MID][N_CHA];// = {{{0xFF}}};
extern uint8_t	map_det			[N_SID][N_MID][N_CHA];// = {{{0xFF}}};
extern uint8_t	map_idx[Ntype]	[N_SID][N_MID][N_CHA];// = {{{0xFF}}};


#endif // __GLOBAL__

