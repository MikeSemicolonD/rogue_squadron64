#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/5FA70", steerOrientationTowardTarget);

INCLUDE_RODATA("asm/nonmatchings/main/5FA70", D_main_8003B224);

INCLUDE_ASM("asm/nonmatchings/main/5FA70", levelOrientationToReferenceAxis);

INCLUDE_RODATA("asm/nonmatchings/main/5FA70", D_main_8003B248);

INCLUDE_ASM("asm/nonmatchings/main/5FA70", emitTrailPuffAndCue);

INCLUDE_ASM("asm/nonmatchings/main/5FA70", guidedEffectNpcHandler);

extern s8 D_main_bss_80139860;
extern s8 D_main_bss_80139864[];

void initWeaponSlotIndexTable(void) {
    s32 i;
    s8 *p;

    i = 3;
    p = D_main_bss_80139864 + i;
    do {
        *p-- = i;
    } while (--i >= 0);
    D_main_bss_80139860 = 4;
}

INCLUDE_RODATA("asm/nonmatchings/main/5FA70", D_main_8003B2F4);
