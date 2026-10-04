#include "common.h"
#include "common_types.h"

#include "player.h"
void clearVec4QuadStruct(void *);
extern u8 D_main_bss_80137CF4;
extern u8 D_main_bss_80138838;
extern u8 D_main_bss_80138839;
extern u8 D_main_bss_80138890;
extern u8 D_main_bss_80138924;
extern u8 D_main_bss_80138925;
extern u8 D_main_bss_80138927;
extern u8 D_main_bss_8013800C[][0x2A0];
void initPlayerStructs(void) {
    s32 i;
    u8 *p;

    for (i = 0; i < 1; i++) {
        clearVec4QuadStruct(D_main_bss_8013800C[i]);
        p = D_main_bss_8013800C[i] - 0x254;
        p[0] = 0;
        *(u32 *)(p + 0x298) = 0;
        *(u32 *)(p + 0x29C) = 0;
    }
    gPlayers[0].unk000 = 1;
    D_main_bss_80137CF4 = 0;
    D_main_bss_80138890 = 0;
    D_main_bss_80138925 = 0;
    D_main_bss_80138838 = 0;
    D_main_bss_80138839 = 0;
    D_main_bss_80138927 = 0;
    D_main_bss_80138924 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main/561F0", fake_func_80055698);
