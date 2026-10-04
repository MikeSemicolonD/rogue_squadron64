#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F60);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F68);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F74);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F80);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F88);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F94);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", applyCraftAnimAndDetailParams);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7FB0);

typedef struct {
    f32 m[12];
} AttachMtxA;

extern char D_mission_overlay_800A7FB0[];
typedef struct {
    u8 pad0[0x24];
    f32 f24;
    f32 f28;
    f32 f2C;
} AttachTblEntry;

extern AttachTblEntry D_mission_overlay_8010ABA0[];
extern s32 D_main_bss_80137CE4;
void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
void setObjectSubstructF10IfReady(s32, f32, s32);
void resolveNpcAttachmentPos(s32, void *, f32, f32);
u8 tickProgressChannel(s32, void *, s32, f32 *);
void triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 playAttachmentMaterialSoundVariantA(u8 *arg0, s32 arg1) {
    AttachMtxA mtx;
    f32 progress;
    f32 scale;
    u8 *npc;
    u8 *sub;

    npc = *(u8 **)(arg0 + 4);
    sub = *(u8 **)(*(u8 **)(npc + 0x38) + 0x1A8);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A7FB0, arg1, &mtx, 0, 0);
    if (arg1 != 3) {
        setObjectSubstructF10IfReady(*(s32 *)(npc + 0x38), 0.033333335f, 0);
        if (arg1 == 0) {
            *(s32 *)(sub + 0x10) = 0;
        }
    }
    scale = *(f32 *)(*(u8 **)(npc + 0x34) + D_main_bss_80137CE4 * 4 + 0xF4);
    if (scale != 0.0f) {
        resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx, D_mission_overlay_8010ABA0[npc[0xB2]].f24, scale);
    }
    if (tickProgressChannel(*(s32 *)(npc + 0x38), &mtx, 0, &progress) == 1) {
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, &mtx, &D_mission_overlay_8010ABA0[npc[0xB2]], 0, D_mission_overlay_8010ABA0[npc[0xB2]].f24, progress);
        play3DSoundEvent(0, npc, npc + 0x24, 15.0f, 0.31f, 0, 0x1D, 0x6E, 0x28);
    }
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7FB8);

typedef struct {
    u8 pad0[0x1C];
    f32 f1C;
    u8 pad20[0x10];
} AttachTblB;

extern char D_mission_overlay_800A7FB8[];
extern AttachTblB D_mission_overlay_8010ABAC[];

s32 playAttachmentMaterialSoundVariantB(u8 *arg0, s32 arg1) {
    AttachMtxA mtx;
    f32 progress;
    f32 scale;
    u8 *npc;
    u8 *sub;

    npc = *(u8 **)(arg0 + 4);
    sub = *(u8 **)(*(u8 **)(npc + 0x38) + 0x1A8);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A7FB8, arg1, &mtx, 0, 0);
    if (arg1 == 0) {
        setObjectSubstructF10IfReady(*(s32 *)(npc + 0x38), 0.033333335f, 1);
        *(s32 *)(sub + 0x14) = 0;
    }
    scale = *(f32 *)(*(u8 **)(npc + 0x34) + D_main_bss_80137CE4 * 4 + 0xF4);
    if (scale != 0.0f) {
        resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx, D_mission_overlay_8010ABA0[npc[0xB2]].f28, scale);
    }
    if (tickProgressChannel(*(s32 *)(npc + 0x38), &mtx, 1, &progress) == 1) {
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, &mtx, &D_mission_overlay_8010ABAC[npc[0xB2]], 0, *(f32 *)(npc[0xB2] * 0x30 + (u8 *)D_mission_overlay_8010ABAC + 0x1C), progress);
        play3DSoundEvent(0, npc, npc + 0x24, 15.0f, 0.3f, 0, 0xD, 0x6E, 0x28);
    }
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7FC0);

extern char D_mission_overlay_800A7FC0[];
s16 getObjectNpcTypeId(s32);
s32 slotDispatcherIter(s32, s32, void *);
s32 triggerCueWithSlotEffectRet(s32, s32, void *, void *, s32, f32, f32) __asm__("triggerCueWithSlotEffect");

s32 playAttachmentCueWithSlotIter(u8 *arg0) {
    AttachMtxA mtx;
    struct {
        s16 a;
        s16 b;
        f32 c;
        f32 d;
        f32 e;
        f32 f;
        u8 g;
        u8 pad[0xB];
    } sp58;
    f32 progress;
    u8 *npc;
    u8 *sub;
    s32 t;
    s32 r;

    npc = *(u8 **)(arg0 + 4);
    sub = *(u8 **)(*(u8 **)(npc + 0x38) + 0x1A8);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A7FC0, *(s16 *)(npc + 0xB6), &mtx, 0, 0);
    *(s16 *)(npc + 0xB6) = (*(s16 *)(npc + 0xB6) + 1) % 5;
    r = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx, (s32)sub + 0xB4, &progress) & 0xFF;
    if (r == 1) {
        sp58.a = 0;
        sp58.b = getObjectNpcTypeId(*(s32 *)(npc + 0x38));
        sp58.g = r;
        sp58.c = 0.033333335f;
        sp58.d = 5.0f;
        sp58.e = 6.0f;
        sp58.f = 10.0f;
        t = triggerCueWithSlotEffectRet(*(s32 *)(npc + 0x38), 0xB, &mtx, 0, 0, D_mission_overlay_8010ABA0[npc[0xB2]].f2C, progress) & 0xFFFF;
        if (t != 0xFFFF) {
            slotDispatcherIter(t, 0xA, &sp58);
        }
        play3DSoundEvent(0, npc, npc + 0x24, 15.0f, 0.3f, 0, 0x30, 0x6E, 0x28);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", playDualTextureAttachmentCue);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", playAttachmentMaterialSoundSimple);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", transformCraftAnchorsAndApplySubFx);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", tickCraftSplineOrientation);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", tickCraftSplineOrientationDual);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", tickTrainCarStateMachine);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", buildDebrisTransformStack);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A805C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", slerpFrameTowardTargetAxis);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A8084);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A8090);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", tickWalkerCraftWithLimbsAndDestruction);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", npcTrainCarUpdate);

void playDualTextureAttachmentCue(s32, s32, s32);

void playDualTextureAttachmentCueMode0(s32 arg0, s32 arg1) {
    playDualTextureAttachmentCue(arg0, arg1, 0);
}

void playDualTextureAttachmentCue(s32, s32, s32);

void playDualTextureAttachmentCueMode1(s32 arg0, s32 arg1) {
    playDualTextureAttachmentCue(arg0, arg1, 1);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", fake_func_800E406C);
