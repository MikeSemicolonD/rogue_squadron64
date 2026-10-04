#include "common.h"

#include "common_types.h"
#include "player.h"

extern void clearVec4QuadStruct(void *);
extern u8 D_main_bss_80137CF4;
extern u8 D_main_bss_80138890;
extern u8 D_main_bss_80138925;
extern u8 D_main_bss_80138838;
extern u8 D_main_bss_80138839;
extern u8 D_main_bss_80138927;
extern u8 D_main_bss_80138924;

void initPlayerStructs(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        clearVec4QuadStruct((u8 *)&gPlayers[i] + 0x254);
        gPlayers[i].unk000 = 0;
        gPlayers[i].inner.unk294 = 0;
        gPlayers[i].inner.unk298 = 0;
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
