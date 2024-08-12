
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

#define Ndet 4 // 4 bunch x 1 det/bunch
#define Ntype 1 // Det1 .... DetN for each det
#define Ndet1 1 // 1 each det1-type for a det
//#define Ndet2 1 // 1 each det2-type for a det

#include <stdint.h>
extern uint8_t	map_type		[N_SID][N_MID][N_CHA];// = {{{0xFF}}};
extern uint8_t	map_det			[N_SID][N_MID][N_CHA];// = {{{0xFF}}};
extern uint8_t	map_idx[Ntype]	[N_SID][N_MID][N_CHA];// = {{{0xFF}}};


#endif // __GLOBAL__

