#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F60);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F68);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F74);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F80);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F88);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A7F94);

typedef struct {
    u8 pad0[0x24];
    f32 f24;
    f32 f28;
    f32 f2C;
} CueTblA;

extern CueTblA sCueTblA[] __asm__("D_mission_overlay_8010ABA0");
extern s32 D_main_bss_80137CE4;
extern s32 D_mission_overlay_8010C0B0;
extern s32 D_mission_overlay_8010C0B4;
extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern void initActorMotionParams(s32, s32, s32, s32, f32);
extern void initObjectAnimSubstruct(s32, s32, s32, s32, f32, void *, s32, f32, f32, s32);
extern void initAnimSubstructFromParams(void *, s32, s32, s32, f32, void *, f32, f32, s32);
extern s32 playAttachmentMaterialSoundVariantA();
extern s32 playAttachmentMaterialSoundVariantB();
extern s32 playAttachmentCueWithSlotIter();
extern void playDualTextureAttachmentCueMode0();
extern void playDualTextureAttachmentCueMode1();
extern s32 playAttachmentMaterialSoundSimple();

void applyCraftAnimAndDetailParams(u8 *arg0, u8 *arg1) {
    u8 *npc;
    u8 *def;
    u8 *p;
    u8 *q;
    s32 i;
    s32 k;
    s32 t;

    npc = *(u8 **)(arg0 + 4);
    def = *(u8 **)(npc + 0x34);
    p = arg1;
    q = npc;
    *(s16 *)(npc + 0xB4) = 0;
    for (i = 0; i < 3; i++) {
        ((s32 *)(npc + 0x8C))[i] = 0;
        ((s32 *)(npc + 0x98))[i] = 0;
        ((f32 *)(arg1 + 0x10))[i] = 1.0f;
        ((s32 *)(arg1 + 0x1C))[i] = 0;
    }
    *(s16 *)(npc + 0xB6) = 0;
    arg1[0xB3] = 0;
    *(f32 *)(arg1 + 0xC) = *(f32 *)(*(u8 **)(npc + 0x34) + 0x90);
    npc[0xC6] = 0;
    npc[0xB1] = 0;
    setNpcHealth(*(s32 *)(npc + 0x38), *(u8 **)(npc + 0x34) + 0x6C, *(u8 **)(npc + 0x34));
    setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(*(u8 **)(npc + 0x34) + 0xA4));
    switch (npc[0xB2]) {
    case 0:
        k = D_main_bss_80137CE4;
        *(f32 *)(arg1 + 8) = *(f32 *)(k * 4 + *(s32 *)(npc + 0x34) + 0xD8);
        t = k * 4 + *(s32 *)(npc + 0x34);
        initActorMotionParams(*(s32 *)(npc + 0x38), *(s32 *)(t + 0xD0), *(s32 *)(t + 0xD4), *(s32 *)(t + 0xDC), *(f32 *)(t + 0xE0));
        initObjectAnimSubstruct(*(s32 *)(npc + 0x38), *(s32 *)(def + 0xE4), *(s32 *)(def + 0xE8), *(s32 *)(def + 0xEC), *(f32 *)(def + 0xF0), playAttachmentMaterialSoundVariantA, 0, sCueTblA[npc[0xB2]].f24, 15.0f, 0);
        initObjectAnimSubstruct(*(s32 *)(npc + 0x38), *(s32 *)(def + 0xE4), *(s32 *)(def + 0xE8), *(s32 *)(def + 0xEC), *(f32 *)(def + 0xF0), playAttachmentMaterialSoundVariantB, 1, sCueTblA[npc[0xB2]].f28, 15.0f, 0);
        initAnimSubstructFromParams(arg1 + 0xB4, *(s32 *)(def + 0x108), *(s32 *)(def + 0x10C), *(s32 *)(def + 0x110), *(f32 *)(def + 0x114), playAttachmentCueWithSlotIter, sCueTblA[npc[0xB2]].f2C, 50.0f, 0);
        npc[0xFC] = 3;
        npc[0xFD] = 0;
        D_mission_overlay_8010C0B4 = 0;
        break;
    case 1:
        k = D_main_bss_80137CE4;
        *(f32 *)(arg1 + 8) = *(f32 *)(k * 4 + *(s32 *)(npc + 0x34) + 0xD8);
        t = k * 4 + *(s32 *)(npc + 0x34);
        initActorMotionParams(*(s32 *)(npc + 0x38), *(s32 *)(t + 0xD0), *(s32 *)(t + 0xD4), *(s32 *)(t + 0xDC), *(f32 *)(t + 0xE0));
        initObjectAnimSubstruct(*(s32 *)(npc + 0x38), *(s32 *)(def + 0xE4), *(s32 *)(def + 0xE8), *(s32 *)(def + 0xEC), *(f32 *)(def + 0xF0), playDualTextureAttachmentCueMode0, 0, sCueTblA[npc[0xB2]].f24, 15.0f, 0);
        initObjectAnimSubstruct(*(s32 *)(npc + 0x38), *(s32 *)(def + 0xE4), *(s32 *)(def + 0xE8), *(s32 *)(def + 0xEC), *(f32 *)(def + 0xF0), playDualTextureAttachmentCueMode1, 1, sCueTblA[npc[0xB2]].f28, 15.0f, 0);
        initAnimSubstructFromParams(arg1 + 0xB4, *(s32 *)(def + 0x108), *(s32 *)(def + 0x10C), *(s32 *)(def + 0x110), *(f32 *)(def + 0x114), playAttachmentMaterialSoundSimple, sCueTblA[npc[0xB2]].f2C, 50.0f, 0);
        break;
    case 3:
        npc[0xFC] = 3;
        npc[0xFD] = 0;
        D_mission_overlay_8010C0B0 = 0;
        break;
    }
}

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

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3FAtt0;

s32 playDualTextureAttachmentCue(s32 arg0, s32 unused, s32 arg2) {
    AttachMtxA mtx1;
    AttachMtxA mtx2;
    AttachMtxA scratch;
    V3FAtt0 saved;
    f32 prog1;
    f32 prog2;
    f32 scale;
    u8 *npc;
    u8 *sub;
    u8 ok;
    u8 *base;

    npc = *(u8 **)(arg0 + 4);
    sub = *(u8 **)(*(u8 **)(npc + 0x38) + 0x1A8);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), arg2 == 0 ? D_mission_overlay_800A7FB0 : D_mission_overlay_800A7FB8, 0, &mtx1, (s32)&scratch, 0);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), arg2 == 0 ? D_mission_overlay_800A7FB0 : D_mission_overlay_800A7FB8, 1, &mtx2, (s32)&scratch, 1);
    scale = *(f32 *)(*(u8 **)(npc + 0x34) + D_main_bss_80137CE4 * 4 + 0xF4);
    if (scale != 0.0f) {
        resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx1, ((AttachTblEntry *)((u8 *)D_mission_overlay_8010ABA0 + arg2 * 4 + npc[0xB2] * 0x30))->f24, scale);
        resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx2, ((AttachTblEntry *)((u8 *)D_mission_overlay_8010ABA0 + arg2 * 4 + npc[0xB2] * 0x30))->f24, scale);
    }
    ok = 0;
    if (arg2 == 0) {
        if (tickProgressChannel(*(s32 *)(npc + 0x38), &mtx1, 0, &prog1) == 1) {
            ok = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx2, 0, &prog2) == 1;
        }
    } else {
        saved = *(V3FAtt0 *)(npc + 0xC);
        *(f32 *)(npc + 0xC) = -*(f32 *)(npc + 0xC);
        *(f32 *)(npc + 0x10) = -*(f32 *)(npc + 0x10);
        *(f32 *)(npc + 0x14) = -*(f32 *)(npc + 0x14);
        if (tickProgressChannel(*(s32 *)(npc + 0x38), &mtx1, 1, &prog1) == 1) {
            ok = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx2, 1, &prog2) == 1;
        }
        *(V3FAtt0 *)(npc + 0xC) = saved;
    }
    if (ok == 1) {
        base = arg2 * 12 + (u8 *)D_mission_overlay_8010ABA0;
        *(f32 *)(sub + (arg2 << 2) + 0x10) = 0.0f;
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, &mtx1, npc[0xB2] * 0x30 + (u8 *)D_mission_overlay_8010ABA0 + arg2 * 12, 0, ((AttachTblEntry *)((u8 *)D_mission_overlay_8010ABA0 + arg2 * 4 + npc[0xB2] * 0x30))->f24, prog1);
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, &mtx2, npc[0xB2] * 0x30 + (u8 *)D_mission_overlay_8010ABA0 + arg2 * 12, 0, ((AttachTblEntry *)((u8 *)D_mission_overlay_8010ABA0 + arg2 * 4 + npc[0xB2] * 0x30))->f24, prog2);
        play3DSoundEvent(0, npc, npc + 0x24, 15.0f, 0.3f, 0, 0xD, 0x6E, 0x28);
    }
    return 0;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3FAtt;

s32 playAttachmentMaterialSoundSimple(u8 *arg0) {
    AttachMtxA mtx;
    V3FAtt saved;
    f32 progress;
    f32 scale;
    u8 *npc;
    u8 *sub;
    s32 r;

    npc = *(u8 **)(arg0 + 4);
    sub = *(u8 **)(*(u8 **)(npc + 0x38) + 0x1A8);
    saved = *(V3FAtt *)(npc + 0xC);
    *(f32 *)(npc + 0xC) = -*(f32 *)(npc + 0xC);
    *(f32 *)(npc + 0x10) = -*(f32 *)(npc + 0x10);
    *(f32 *)(npc + 0x14) = -*(f32 *)(npc + 0x14);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A7FC0, *(s16 *)(npc + 0xB6), &mtx, 0, 0);
    scale = *(f32 *)(*(u8 **)(npc + 0x34) + D_main_bss_80137CE4 * 4 + 0xF4);
    if (scale != 0.0f) {
        resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx, D_mission_overlay_8010ABA0[npc[0xB2]].f2C, scale);
    }
    r = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx, (s32)sub + 0xB4, &progress);
    *(V3FAtt *)(npc + 0xC) = saved;
    *(u16 *)(npc + 0xB6) = *(u16 *)(npc + 0xB6) ^ 1;
    if ((r & 0xFF) == 1) {
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 0xB, &mtx, 0, 0, D_mission_overlay_8010ABA0[npc[0xB2]].f2C, progress);
        play3DSoundEvent(0, npc, npc + 0x24, 15.0f, 0.3f, 0, 0x30, 0x6E, 0x28);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", transformCraftAnchorsAndApplySubFx);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", tickCraftSplineOrientation);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", tickCraftSplineOrientationDual);

extern u8 *D_main_bss_801375D8;

void tickTrainCarStateMachine(u8 *arg0) {
    u8 *p;
    u8 *e;
    s32 i;
    s32 cnt;

    if (arg0[0xFD] == 0) {
        if ((((arg0[0xFC] = arg0[0xFC] - 1)) << 24) <= 0) {
            arg0[0xFD] = 1;
            if (arg0[0xB2] == 0) {
                e = *(u8 **)(arg0 + 0x34);
                if (*(s32 *)(e + 0x134) == 0) {
                    *(s16 *)(arg0 + 0xFA) = 0;
                    return;
                }
                p = e + (*(s32 *)(e + 0x138) + 0x134);
            } else {
                e = *(u8 **)(arg0 + 0x34);
                if (*(s32 *)(e + 0xD4) == 0) {
                    *(s16 *)(arg0 + 0xFA) = 0;
                    return;
                }
                p = e + (*(s32 *)(e + 0xD8) + 0xD4);
            }
            for (i = 0, cnt = 1; i < 16; i++) {
                if (cnt == 0) {
                    break;
                }
                e = *(u8 **)(*(u8 **)(D_main_bss_801375D8 + 4) + *(u16 *)(p + 2) * 4);
                *(u16 *)(arg0 + i * 2 + 0xCA) = *(u16 *)(e + 6);
                *(u8 *)(arg0 + i + 0xEA) = 1;
                switch (*(u16 *)e) {
                case 0x2F:
                    cnt = *(s32 *)(e + 0x134);
                    p = e + (*(s32 *)(e + 0x138) + 0x134);
                    break;
                case 0x30:
                    cnt = *(s32 *)(e + 0x11C);
                    p = e + (*(s32 *)(e + 0x120) + 0x11C);
                    break;
                case 0x34:
                    cnt = *(s32 *)(e + 0xD4);
                    p = e + (*(s32 *)(e + 0xD8) + 0xD4);
                    break;
                case 0x31:
                case 0x35:
                    cnt = *(s32 *)(e + 0xC8);
                    p = e + (*(s32 *)(e + 0xCC) + 0xC8);
                    break;
                }
            }
            *(s16 *)(arg0 + 0xFA) = i;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", buildDebrisTransformStack);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A805C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", slerpFrameTowardTargetAxis);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A8084);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E0790", D_mission_overlay_800A8090);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", tickWalkerCraftWithLimbsAndDestruction);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", npcTrainCarUpdate);

s32 playDualTextureAttachmentCue(s32, s32, s32);

void playDualTextureAttachmentCueMode0(s32 arg0, s32 arg1) {
    playDualTextureAttachmentCue(arg0, arg1, 0);
}

s32 playDualTextureAttachmentCue(s32, s32, s32);

void playDualTextureAttachmentCueMode1(s32 arg0, s32 arg1) {
    playDualTextureAttachmentCue(arg0, arg1, 1);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", fake_func_800E406C);
