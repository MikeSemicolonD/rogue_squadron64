#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/56630", initVoiceSubtitleSystem);

INCLUDE_ASM("asm/nonmatchings/main/56630", linkHudNodeAndComputeScreenPos);

INCLUDE_ASM("asm/nonmatchings/main/56630", tickVoiceSubtitleDisplay);

INCLUDE_ASM("asm/nonmatchings/main/56630", setSubtitleOverlayScreenPos);

s32 resetPlayerSlotChannelTransform(u16);
s32 rs_free(s32);
extern s32 D_main_bss_80139010;
extern u16 D_main_bss_80139014;

void freeSubtitleOverlay(void) {
    resetPlayerSlotChannelTransform(D_main_bss_80139014);
    rs_free(D_main_bss_80139010);
}

INCLUDE_ASM("asm/nonmatchings/main/56630", setActiveVoiceLine);

INCLUDE_ASM("asm/nonmatchings/main/56630", clearActiveVoiceLine);

INCLUDE_ASM("asm/nonmatchings/main/56630", fake_func_80056344);
