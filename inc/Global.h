
#ifndef __GLOBAL__
#define __GLOBAL__


//// maxium
#define N_SID 16 // 0~15 sid mask 0xF0
#define N_MID 10 // 0~9 mid mask 0x0F but a crate has 10 board slots
#define N_CHA 10 // 0~9 cha mask 0xFF but NKFADC10 has 10 mcx inputs

//// used
#define Nsid 2
#define Nmid 10
#define Nch 10

#define Ndet 1
#define Ncry 4 // 4 crystals for each detector
#define Ntype 2 // FV, seg for each crystal
#define Nseg 8 // 8 segments for each crystal
#define Nfv 2 // 8 full volume for each crystal

#include <stdint.h>
extern uint8_t	map_type		[N_SID][N_MID][N_CHA];// = {{{0xFF}}};
extern uint8_t	map_det			[N_SID][N_MID][N_CHA];// = {{{0xFF}}};
extern uint8_t	map_crystal		[N_SID][N_MID][N_CHA];// = {{{0xFF}}};
extern uint8_t	map_idx[Ntype]	[N_SID][N_MID][N_CHA];// = {{{0xFF}}};


#endif // __GLOBAL__

