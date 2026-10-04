#include "common.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E7DD0", transformCraftAnchorsApplySubFx3);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E7DD0", tickFighterSquadronWithSplinePaths);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E7DD0", npcGroundTroopUpdate);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E7DD0", playAttachmentCueNoTexture);

#include "common_types.h"

extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern void initActorMotionParams(s32, f32, f32, f32, f32);
extern void initObjectAnimSubstruct(s32, f32, f32, f32, f32, void *, s32, f32, f32, f32);
extern void playAttachmentCueNoTexture(void);
extern s32 D_main_bss_80137CE4;

void applyCraftAnimDetailParamsB(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);

    *(s16 *)(npc + 0x64) = 0;
    *(f32 *)(npc + 0x58) = *(f32 *)(*(u8 **)(npc + 0x34) + 0x90);
    *(f32 *)(npc + 0x5C) = 10.0f;
    setNpcHealth(*(s32 *)(npc + 0x38), *(u8 **)(npc + 0x34) + 0x6C, *(u8 **)(npc + 0x34));
    setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(*(u8 **)(npc + 0x34) + 0xA0));
    if (*(s16 *)(npc + 0x60) == 0) {
        initActorMotionParams(*(s32 *)(npc + 0x38), ((f32 *)(*(u8 **)(npc + 0x34) + 0xAC))[D_main_bss_80137CE4], ((f32 *)(*(u8 **)(npc + 0x34) + 0xB0))[D_main_bss_80137CE4], ((f32 *)(*(u8 **)(npc + 0x34) + 0xB4))[D_main_bss_80137CE4], ((f32 *)(*(u8 **)(npc + 0x34) + 0xB8))[D_main_bss_80137CE4]);
        initObjectAnimSubstruct(*(s32 *)(npc + 0x38), 1.0f, 0.0f, 1.0f, 0.0f, playAttachmentCueNoTexture, 0, 10.0f, 15.0f, 0.0f);
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E7DD0", fake_func_800E8A34);
