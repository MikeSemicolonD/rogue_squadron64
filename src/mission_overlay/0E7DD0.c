#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E7DD0", transformCraftAnchorsApplySubFx3);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E7DD0", tickFighterSquadronWithSplinePaths);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E7DD0", npcGroundTroopUpdate);

typedef struct {
    f32 m[12];
} AttachMtx;

extern void resolveNpcAttachmentPos(s32, AttachMtx *, f32, f32);
extern u8 tickProgressChannel(s32, AttachMtx *, s32, f32 *);
extern void triggerCueWithSlotEffect(s32, s32, AttachMtx *, void *, s32, f32, f32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern u8 D_mission_overlay_8010B0BC[];

s32 playAttachmentCueNoTexture(void *arg0) {
    AttachMtx mtx;
    f32 progress;
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 r;

    mtx = *(AttachMtx *)npc;
    mtx.m[1] -= *(f32 *)(npc + 0x44) * 2.4f;
    resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx, 10.0f, 45.0f);
    r = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx, 0, &progress);
    if (r == 1) {
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 6, &mtx, D_mission_overlay_8010B0BC, r, 10.0f, progress);
        play3DSoundEvent(0, npc, npc + 0x24, 12.0f, 0.8f, 0, 0x1D, 0x6E, 0x28);
    }
    return 0;
}

#include "common_types.h"

extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern void initActorMotionParams(s32, f32, f32, f32, f32);
extern void initObjectAnimSubstruct(s32, f32, f32, f32, f32, void *, s32, f32, f32, f32);
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
