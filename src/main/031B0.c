#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/031B0", getResetVectorRegion);

INCLUDE_ASM("asm/nonmatchings/main/031B0", fatalErrorHalt);

extern s32 D_80000318;
extern u8 *D_main_bss_8010FCB0;

s32 getUsableRdramSize(void) {
    if (*(u32 *)(D_main_bss_8010FCB0 + 0x44) & 0x2000) {
        return 0x400000;
    }
    return D_80000318;
}

INCLUDE_ASM("asm/nonmatchings/main/031B0", fake_func_8000268C);
