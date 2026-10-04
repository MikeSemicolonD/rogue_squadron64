#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/55250", tickWrappingTimerAccumulatorList);

INCLUDE_ASM("asm/nonmatchings/main/55250", loadAssetIntoNewSlot);

INCLUDE_ASM("asm/nonmatchings/main/55250", allocAnimationPhasePool);

s32 rs_free(s32);
extern s32 D_main_bss_80137C80;
extern s32 D_main_bss_80137C84;

void freeAnimationPhasePool(void) {
    s32 var_s0;
    void *temp_a0;

    var_s0 = 0;
    if (D_main_bss_80137C80 > 0) {
        do {
            temp_a0 = (var_s0 * 0x10) + D_main_bss_80137C84;
            if ((*(u16 *)((u8 *)(temp_a0) + 6)) & 0x8000) {
                rs_free((*(s32 *)((u8 *)(temp_a0) + 0)));
            }
            var_s0 += 1;
        } while (var_s0 < D_main_bss_80137C80);
    }
    rs_free(D_main_bss_80137C84);
}

INCLUDE_ASM("asm/nonmatchings/main/55250", setPoolEntryPhaseAndMarkActive);

INCLUDE_ASM("asm/nonmatchings/main/55250", setPoolEntryPhase);

INCLUDE_ASM("asm/nonmatchings/main/55250", getPoolEntryFrameIndex);

typedef struct {
    u8 unk0[4];
    u16 unk4;
    u8 unk6[4];
} TextureAnimSlot;

extern TextureAnimSlot D_main_bss_80137C90[];

void resetTextureAnimSlots(void) {
    s32 i;

    for (i = 7; i >= 0; i--) {
        D_main_bss_80137C90[i].unk4 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/55250", registerTextureAnimSlot);

INCLUDE_ASM("asm/nonmatchings/main/55250", tickTextureAnimSlots);
