#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/56630", initVoiceSubtitleSystem);

INCLUDE_ASM("asm/nonmatchings/main/56630", linkHudNodeAndComputeScreenPos);

INCLUDE_ASM("asm/nonmatchings/main/56630", tickVoiceSubtitleDisplay);

extern s32 D_main_bss_80139010;
s32 getBootConfigField12();
s32 getBootConfigField14();

void setSubtitleOverlayScreenPos(s16 arg0, s16 arg1) {
    (*(u16 *)((u8 *)(D_main_bss_80139010) + 0x12)) = (u16) (((arg0 + 0x18) * (getBootConfigField12() & 0xFFFF)) / 320);
    (*(s16 *)((u8 *)(D_main_bss_80139010) + 0x14)) = (s16) ((arg1 * (getBootConfigField14() & 0xFFFF)) / 224);
    (*(s16 *)((u8 *)(D_main_bss_80139010) + 0x16)) = (s16) ((((getBootConfigField12() & 0xFFFF) * 0x128) / 320) - (*(u16 *)((u8 *)(D_main_bss_80139010) + 0x12)));
}

s32 resetPlayerSlotChannelTransform(u16);
s32 rs_free(s32);
extern s32 D_main_bss_80139010;
extern u16 D_main_bss_80139014;

void freeSubtitleOverlay(void) {
    resetPlayerSlotChannelTransform(D_main_bss_80139014);
    rs_free(D_main_bss_80139010);
}

s32 getVoiceText(u16);

typedef struct {
    s16 id;
    u8 unk2;
    u8 unk3;
    s32 unk4;
    s32 unk8;
} ActiveVoiceLine;

void setActiveVoiceLine(s32 arg0, s32 arg1) {
    ActiveVoiceLine *p;

    ((ActiveVoiceLine *)D_main_bss_80139010)->id = arg0;
    getVoiceText(arg0);
    p = (ActiveVoiceLine *)D_main_bss_80139010;
    ((u8 *)p)[3] = 0;
    p->unk8 = arg1;
    ((ActiveVoiceLine *)D_main_bss_80139010)->unk2 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main/56630", clearActiveVoiceLine);

INCLUDE_ASM("asm/nonmatchings/main/56630", fake_func_80056344);
