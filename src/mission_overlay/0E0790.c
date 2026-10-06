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

typedef struct { f32 x, y, z; } FV3;
void initActorMotionParamsF(s32, f32, s32, s32, f32) __asm__("initActorMotionParams");
void setPoolEntryPhaseAndMarkActiveF(u16, f32, s32) __asm__("setPoolEntryPhaseAndMarkActive");
extern u8 isPendingChildNpcActive(s32);
extern u8 validateActorTargetLOS(s32);
extern u8 evaluateTargetTrackingVisibility(s32, s32, s32);
extern void applyToObjectSubstructByFlag(s32, f32, f32, s32);
extern void tickObjectAnimSubstruct(s32, void *, f32, s32);
extern void buildRotationMatrixSlot0(void *, s32);
extern void composeRotationMatrixSlot1(void *, s32);
extern void transformVec3ByMat34(void *, void *, void *);
extern void setPoolEntryPhaseAndMarkActive(u16, s32, s32);
extern void setPoolEntryPhase(u16, s32);
extern s32 gObjectiveCounts[];
extern u8 gObjectiveBooleans[];

typedef struct {
    s32 a, b, c;
} V3I;

typedef struct {
    f32 v[12];
} NpcXform30B;

void transformCraftAnchorsAndApplySubFx(void *npcv, f32 dt) {
    u8 *npc = npcv;
    NpcXform30B save;
    f32 mtx[12];
    V3I pos;
    u8 r;
    s32 i;
    u8 *s5;
    u8 *t;
    u8 *t2;
    s32 st;
    u8 *p;
    s32 ty;

    ty = npc[0xB2];
    if (ty < 5) {
        if (ty >= 2) return;
    }
    {
        s5 = *(u8 **)(*(u8 **)(npc + 0x38) + 0x1A8);
        for (i = 0; npc[0xB2] == 0 ? i < 2 : i < 3; i++) {
        {
            if (isPendingChildNpcActive(*(s32 *)(npc + 0x38)) != 1) {
                goto next;
            }
            r = 0;
            save = *(NpcXform30B *)npc;
            p = npc + i * 4;
            buildRotationMatrixSlot0(mtx, *(s32 *)(p + 0x98));
            composeRotationMatrixSlot1(mtx, *(s32 *)(p + 0x8C));
            transformVec3ByMat34(mtx, &save.v[3], npc + 0xC);
            transformVec3ByMat34(mtx, &save.v[6], npc + 0x18);
            switch (npc[0xB2]) {
            case 0:
                if (i == 0) {
                    r = validateActorTargetLOS(*(s32 *)(npc + 0x38));
                } else if (i == 1) {
                    {
                        u8 *q = (u8 *)(D_main_bss_80137CE4 * 4 + *(s32 *)(npc + 0x34));
                        r = evaluateTargetTrackingVisibility(*(s32 *)(npc + 0x38), *(s32 *)(q + 0x104), *(s32 *)(q + 0x100));
                    }
                }
                break;
            case 1:
                if (i == 0) {
                    r = validateActorTargetLOS(*(s32 *)(npc + 0x38));
                } else {
                    pos = *(V3I *)(npc + 0xC);
                    ((FV3 *)(npc + 0xC))->x = -((FV3 *)(npc + 0xC))->x;
                    ((FV3 *)(npc + 0xC))->y = -((FV3 *)(npc + 0xC))->y;
                    ((FV3 *)(npc + 0xC))->z = -((FV3 *)(npc + 0xC))->z;
                    r = evaluateTargetTrackingVisibility(*(s32 *)(npc + 0x38), *(s32 *)((u8 *)(D_main_bss_80137CE4 * 4 + *(s32 *)(npc + 0x34)) + 0x104), *(s32 *)((u8 *)(D_main_bss_80137CE4 * 4 + *(s32 *)(npc + 0x34)) + 0x100));
                    *(V3I *)(npc + 0xC) = pos;
                }
                break;
            default:
                goto next;
            }
            if (r == 1) {
                switch (i) {
                case 0:
                    applyToObjectSubstructByFlag(*(s32 *)(npc + 0x38), dt, 0.0f, 0);
                    break;
                case 1:
                    applyToObjectSubstructByFlag(*(s32 *)(npc + 0x38), dt, 0.0f, 1);
                    break;
                case 2:
                    tickObjectAnimSubstruct(*(s32 *)(npc + 0x38), s5 + 0xB4, dt, 0);
                    break;
                }
            }
            *(NpcXform30B *)npc = save;
        }
next:;
        }
        if (npc[0xB2] != 0) return;
        t = *(u8 **)(npc + 0x34);
        if (*(s32 *)(t + 0x128) != 0 && gObjectiveBooleans[*(s32 *)(t + 0x128) - 1] == 0) return;
        if (*(s32 *)(t + 0x12C) != 0 && gObjectiveCounts[*(s32 *)(t + 0x12C) - 1] < *(s32 *)(t + 0x130)) return;
        if (s5[0xB3] == 0) {
            s5[0xB3] = 1;
            t2 = (u8 *)(D_main_bss_80137CE4 * 4 + *(s32 *)(npc + 0x34));
            initActorMotionParamsF(*(s32 *)(npc + 0x38), 180.0f, *(s32 *)(t2 + 0xD4), *(s32 *)(t2 + 0xDC), *(f32 *)(t2 + 0xE0));
            setPoolEntryPhaseAndMarkActiveF(*(u16 *)(npc + 0xC8), 5000.0f, 0);
            npc[0xC7] = 0;
        }
        st = npc[0xC7];
        if (st == 3) {
            setPoolEntryPhase(*(u16 *)(npc + 0xC8), 0);
            npc[0xC7] = npc[0xC7] + 1;
        } else if (st != 4) {
            npc[0xC7] = st + 1;
        }
        tickObjectAnimSubstruct(*(s32 *)(npc + 0x38), s5 + 0xB4, dt, 0);
    }
}

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

typedef struct {
    f32 f0;
    s32 v4[3];
    f32 f10, f14, f18, f1C;
    s32 w20, w24;
    f32 f28, f2C;
    s32 w30, w34;
    f32 f38;
    s16 h3C, h3E;
    f32 f40, f44, f48, f4C, f50, f54, f58, f5C;
    s32 w60;
    s32 w64;
    s32 w68;
    u8 b6C, b6D;
    u8 pad6E[2];
    s16 h70, h72, h74, h76;
    s32 w78;
    u16 h7C;
} TwCtx;
extern s32 D_main_bss_80130C04;
extern s32 D_main_bss_80130C08;
extern void initNpcContextFromTransform(TwCtx *, void *, s32);
extern s32 spawnRandomBurstNpcVariantWrapper(void *);
extern void assignNpcTargetAndPosition(s32, u16, f32 *, f32);

void tickWalkerCraftWithLimbsAndDestruction(void *argv) {
    u8 *arg0 = argv;
    TwCtx c;
    f32 v[3];
    s32 id;
    f32 zero;
    initNpcContextFromTransform(&c, arg0, 0);
    c.b6C = 2;
    c.b6D = 0x10;
    c.h70 = 0x80;
    c.h72 = 0x400;
    c.w64 = D_main_bss_80130C08 + 0x18;
    c.w68 = D_main_bss_80130C04;
    c.f14 = -3.0f;
    c.f58 = 1.0f;
    c.h3C = 0;
    c.h3E = 0;
    c.h7C |= 2;
    zero = 0.0f;
    c.f40 = 4.0f;
    c.f18 = zero;
    c.f10 = zero;
    c.f38 = 0.1f;
    c.f54 = 0.8f;
    c.f48 = 1.0f;
    c.w78 |= 0x09000000;
    id = spawnRandomBurstNpcVariantWrapper(&c) & 0xFFFF;
    v[0] = zero;
    v[2] = zero;
    v[1] = -0.1f;
    assignNpcTargetAndPosition(id, *(u16 *)(*(u8 **)(arg0 + 0x38) + 0x198), v, 0.3f);
    id = spawnRandomBurstNpcVariantWrapper(&c) & 0xFFFF;
    v[0] = zero;
    v[1] = -0.1f;
    v[2] = -0.6f;
    assignNpcTargetAndPosition(id, *(u16 *)(*(u8 **)(arg0 + 0x38) + 0x198), v, 0.3f);
    id = spawnRandomBurstNpcVariantWrapper(&c) & 0xFFFF;
    v[0] = zero;
    v[1] = -0.1f;
    v[2] = 0.6f;
    assignNpcTargetAndPosition(id, *(u16 *)(*(u8 **)(arg0 + 0x38) + 0x198), v, 0.3f);
}

typedef struct { f32 x, y, z; } TcVec3;
typedef struct {
    TcVec3 pos;
    TcVec3 fwd;
    TcVec3 up;
    TcVec3 vel;
    u8 *mesh;
    u8 *rec;
    s32 obj;
    u8 *node0[3];
    u8 *node1[3];
    u8 *node2[3];
    u8 *mat0[3];
    u8 *mat1[3];
    u8 *mat2[3];
    f32 radius;
    f32 scale;
    u8 pad8C[0x18];
    u8 *ctx;
    u16 slotA8;
    u16 slotAA;
    u16 slotAC;
    u16 slotAE;
    s8 outCount;
    u8 flagB1;
    u8 type;
    s8 cntB3;
    s16 mode;
    u16 padB6;
    f32 fB8;
    f32 fBC;
    f32 timer;
    u8 bC4;
    u8 bC5;
    u8 bC6;
    u8 bC7;
    s16 assetC8;
    u16 ids[16];
    u8 live[16];
    s16 count;
    u8 bFC;
    u8 bFD;
} TcObj;
typedef struct {
    f32 phase;
    f32 rate;
    u8 pad8[4];
    s32 iC;
    f32 aDC[3];
    f32 aE4[3];
    u8 audio0[0x44];
    u8 audio1[0x44];
    u8 on0;
    u8 on1;
    u8 vol;
} TcSub;
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u16 u18;
    u16 u1A;
} TcParam;
extern TcParam D_mission_overlay_8010AB14[];
typedef struct { s32 a[3]; s32 b[3]; s32 c[3]; u8 pad[0x6C]; } TcNames;
extern TcNames D_mission_overlay_8010AC90[];
extern s32 D_mission_overlay_8010AB00[];
extern u16 D_main_bss_80139560[];
extern u8 D_main_bss_80130B39;
extern f32 D_main_bss_80130BA4;
extern f32 D_mission_overlay_8010C0B0_f __asm__("D_mission_overlay_8010C0B0");
extern f32 D_mission_overlay_8010C0B4_f __asm__("D_mission_overlay_8010C0B4");
extern s32 gObjectiveCounts[];
extern u8 gObjectiveBooleans[];
extern char D_mission_overlay_800A8084[];
extern char D_mission_overlay_800A8090[];
s16 rand(void);
f32 sinf(f32);
u8 *walkMeshdef0List(char *);
s16 loadAssetIntoNewSlot(char *, char *);
void composeEulerRotationXYZ(void *, s32, s32, s32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, s32);
void composeRotationMatrixSlot1(void *, s32);
void composeRotationMatrixSlot2(void *, s32);
void addVec3At0x24(void *, f32, f32, f32);
u16 popNpcSlotFromTail(u16, void *);
u8 *lookupHmtMaterialByName(void *, s32, void *);
void createAndInitObject(void *, s32, void *, void *, s32);
s32 getLevelDatItemByName(char *);
void initActorAsType1(s32, s32, s32, s32, f32, f32, s32);
void updateObjectFlags110(s32, s32, s32);
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
u8 *allocateAndInitCraftNpcContext(f32, f32, u16);
void factor5RemoveListNode(void *);
void rs_free(void *);
s32 getNpcCurrentHealth(s32);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void releaseMeshAsset(void *);
void func_mission_overlay_800AA6D0(void *, f32, void *);
void dispatchEffectByActorType(s32, f32);
void buildDebrisTransformStack(void *, f32);
u8 *getNpcContextByIndex(u16);
s32 func_mission_overlay_800EFDE0(s32, s32, s32, f32);
void tickCraftSplineOrientationDual(void *, f32);
void transformCraftAnchorsAndApplySubFx(void *, f32);
void tickWalkerCraftWithLimbsAndDestruction(void *);
void spawnNpcType0xAFromTemplate(void *, f32);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
u8 slerpFrameTowardTargetAxis(void *, f32);
void composeRandomRotationMatrix(void *, void *, f32, s32, s32, s32);
void scaleVec3ByRandomRange(void *, f32, f32);
void spawnDebris1Npc(void *, void *, f32, f32, f32);
void spawnDestructionEffectBurst(void *, s32, f32, f32, f32, f32);
void zmemcpy(void *, void *, s32);
void transformLimbStrideAnchorsLocal(u16, void *, void *);
void gameStateByteGatedNpcHelper(s32, void *, s32, f32, f32, f32);
void destroyNpcSlotByIndex(u16);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyObjectOwnedNpcSlot(s32);
void updateActive3DAudioSource(void *, void *, void *, s32);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
void advanceNpcOnCurvedPath(s32, s32, void *, void *);
s32 getPlayerField2(s32);
void playSpeechClip(s32, s32, f32, s32);
void vec3ExtrapolateFirstOrder(s32, s32, void *, f32);
void spawnRandomScaleColoredEffectAltVariant(void *, f32);
void extrapolateNpcPositionForCurrentMode(void *);
s32 getObjectDetailLevel(s32);
void func_mission_overlay_800EFD6C(s32);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void spawnRandomParticleWithParent(s32, u16, f32, s32);
s32 dealDamageToNpc(s32, u16);
void unregisterAndFreeNpcSlot(u16, void *);
void tallyMidDetailObject(void *);
s32 clearPendingChildNpc(s32);
void setObjectFlagBit4(void *);
void setType1ActorParams(s32, s32, u8, u8, u8, s32);
void updateType1AnimRamp(s32, s32, s32, s32, s32);
void dispatchSlotAction5IfActive(void *, void *);
#define TCABSF(x) ({ f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(x)); _r; })

s32 npcTrainCarUpdate(u8 *arg0, u16 action, u8 *arg2) {
    TcObj *s2 = *(TcObj **)(arg0 + 4);
    f32 sp[20];
    u8 *rec;
    u8 *a5;
    u8 *a9;
    TcSub *sub;
    f32 dt;
    char *name;
    s32 i;
    s32 *hp;

    switch (action) {
    case 1:
        rec = arg2;
        s2->rec = arg2;
        switch (*(u16 *)rec) {
        default:
        case 0x2F:
            s2->type = 0;
            name = "tr_engine";
            break;
        case 0x30:
            s2->type = 1;
            name = "tr_defense";
            break;
        case 0x31:
            s2->type = 2;
            name = "tr_container";
            break;
        case 0x34:
            s2->type = 3;
            name = "r_tr_engine";
            break;
        case 0x35:
            s2->type = 4;
            name = "r_tr_cargo";
            break;
        }
        s2->mesh = walkMeshdef0List(name);
        *(s32 **)(s2->mesh + 4) = D_mission_overlay_8010AB00;
        if (s2->type == 0) {
            s2->assetC8 = loadAssetIntoNewSlot("trn_eng_topmain", "imp_stuff/trainhatch");
        }
        s2->pos.x = *(f32 *)(rec + 0x10);
        s2->pos.y = *(f32 *)(rec + 0x14);
        s2->pos.z = *(f32 *)(rec + 0x18);
        composeEulerRotationXYZ(s2, *(s32 *)(rec + 0x1C), *(s32 *)(rec + 0x20), *(s32 *)(rec + 0x24));
        s2->vel.x = s2->vel.y = s2->vel.z = 0.0f;
        {
            f32 inv = 1.0f / *(f32 *)(*(u8 **)s2->mesh + 0x34);
            s2->scale = inv * *(f32 *)(rec + 0x28);
            initVec4TripletFromArgs(s2->mesh + 0x28, inv * *(f32 *)(rec + 0x28), inv * *(f32 *)(rec + 0x2C), inv * *(f32 *)(rec + 0x30));
        }
        composeRotationMatrixSlot0(s2->mesh + 0x28, *(s32 *)(rec + 0x1C));
        composeRotationMatrixSlot1(s2->mesh + 0x28, *(s32 *)(rec + 0x20));
        composeRotationMatrixSlot2(s2->mesh + 0x28, *(s32 *)(rec + 0x24));
        addVec3At0x24(s2->mesh + 0x28, s2->pos.x, s2->pos.y, s2->pos.z);
        s2->radius = *(f32 *)(*(u8 **)s2->mesh + 0x44) * s2->scale;
        *(TcObj **)(arg0 + 8) = s2;
        *(u8 **)(arg0 + 0xC) = s2->mesh;
        s2->outCount = 0;
        for (i = 0; i < 3; i++) {
            s32 n = D_mission_overlay_8010AC90[s2->type].a[i];
            if (n != 0) {
                s2->node0[i] = lookupHmtMaterialByName(s2->mesh, n, &s2->mat0[i]);
            } else {
                s2->node0[i] = NULL;
            }
            n = D_mission_overlay_8010AC90[s2->type].b[i];
            if (n != 0) {
                s2->node1[i] = lookupHmtMaterialByName(s2->mesh, n, &s2->mat1[i]);
            } else {
                s2->node1[i] = NULL;
            }
            n = D_mission_overlay_8010AC90[s2->type].c[i];
            if (n != 0) {
                s2->node2[i] = lookupHmtMaterialByName(s2->mesh, n, &s2->mat2[i]);
            } else {
                s2->node2[i] = NULL;
            }
        }
        {
            u8 *b = (u8 *)D_main_bss_80139560;
            s32 o;
            s2->slotA8 = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
            o = 0x2C;
            if (*(s32 *)(rec + 0xA4) == 1) {
                o = 0x2E;
            }
            s2->slotAA = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            o = 0x12;
            if (*(s32 *)(rec + 0xA4) == 1) {
                o = 0xE;
            }
            s2->slotAC = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            if (*(s32 *)(rec + 0xA8) != 0) {
                o = 0x18;
                if (*(s32 *)(rec + 0xA4) == 1) {
                    o = 0x1A;
                }
                s2->slotAE = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            } else {
                s2->slotAE = 0xFFFF;
            }
        }
        createAndInitObject(&s2->obj, 0xE0, arg0, applyCraftAnimAndDetailParams, 0);
        {
            TcSub *sb1 = *(TcSub **)(s2->obj + 0x1A8);
            sb1->phase = TCABSF(((f32)(rand() & 0x7F) - 64.0f) / 320.0f);
            sb1->on0 = 0;
            sb1->on1 = 0;
            sb1->rate = 1.0f;
            name = (char *)(*(s32 *)(rec + 0x8C) + (s32)rec);
            if (*name != '-') {
                s32 item = getLevelDatItemByName(name);
                u8 *r = s2->rec;
                initActorAsType1(s2->obj, item, sb1->iC, *(s32 *)(r + 0x9C), *(f32 *)(r + 0x94), *(f32 *)(s2->rec + 0x98), 0);
                updateObjectFlags110(s2->obj, 3, 0);
                {
                    TcSub *p = *(TcSub **)(s2->obj + 0x1A8);
                    if (s2->type == 0 || s2->type == 3) {
                        p->on1 = 1;
                        p->vol = 0x78;
                        play3DSoundEventVariant(p->audio1, s2, &s2->vel, 10.0f, 0.6f, 0xF, 0x45, 1, 0x78, 0);
                    }
                }
            }
        }
        {
            TcParam *t = D_mission_overlay_8010AB14;
            s2->ctx = allocateAndInitCraftNpcContext(t[s2->type].fC * s2->scale, t[s2->type].f8 * s2->scale, t[s2->type].u1A);
            *(f32 *)(s2->ctx + 0x14) = t[s2->type].f0;
            *(f32 *)(s2->ctx + 4) = t[s2->type].f10 * s2->scale;
            *(f32 *)(s2->ctx + 0x10) = t[s2->type].f4;
            *(f32 *)(s2->ctx + 0x18) = t[s2->type].f14;
        }
        break;
    case 2:
        {
            TcSub *p = *(TcSub **)(s2->obj + 0x1A8);
            if (p->on0 == 1) {
                p->on0 = 0;
                factor5RemoveListNode(p->audio0);
            }
        }
        {
            TcSub *p = *(TcSub **)(s2->obj + 0x1A8);
            if (p->on1 == 1) {
                p->on1 = 0;
                factor5RemoveListNode(p->audio1);
            }
        }
        if (s2->ctx != NULL) {
            rs_free(s2->ctx);
        }
        initActorRenderDescriptorIfUninit(s2->obj, getNpcCurrentHealth(s2->obj) < 1, s2->rec, 0, s2->rec + 0x70);
        clearPendingAndDestroyChildNpc(&s2->obj);
        releaseMeshAsset(s2->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        sub = *(TcSub **)(s2->obj + 0x1A8);
        {
            f32 inc = dt * 4.0f;
            s32 j;
            for (j = 0; j < 3; j++) {
                if (sub->aDC[j] < 1.0f) {
                    sub->aDC[j] += inc;
                    if (1.0f < sub->aDC[j]) {
                        sub->aDC[j] = 1.0f;
                        sub->aE4[j] = 0.0f;
                    } else if (sub->aDC[j] < 0.2f) {
                        sub->aE4[j] = sub->aDC[j] * 5.0f;
                    } else {
                        sub->aE4[j] = 1.0f - (sub->aDC[j] - 0.2f) * 1.25f;
                    }
                }
            }
        }
        switch (s2->mode) {
        case 0:
            s2->mode = 1;
        case 1:
            func_mission_overlay_800AA6D0(s2, dt, s2->rec + 0x34);
            dispatchEffectByActorType(s2->obj, dt);
            {
                TcSub *p = *(TcSub **)(s2->obj + 0x1A8);
                p->phase += dt * p->rate;
                if (p->phase > 1.0f) {
                    p->phase -= 2.0f;
                }
                s2->pos.y += sinf(p->phase * 3.1415927f) * *(f32 *)(s2->rec + 0xA0) * 0.25f;
            }
            buildDebrisTransformStack(s2, dt);
            switch (s2->type) {
            case 3:
                tickTrainCarStateMachine((u8 *)s2);
                if ((s2->type == 0 || s2->type == 3) && s2->bFD == 1) {
                    s32 k;
                    for (k = s2->count - 1; k >= 0; k--) {
                        if (s2->live[k] == 1) {
                            if (getNpcCurrentHealth(*(s32 *)(getNpcContextByIndex(s2->ids[k]) + 0x10)) > 0) {
                                break;
                            }
                            ((u8 *)sp)[0x18] = 0xA;
                            s2->live[k] = 0;
                            slotDispatcherIter(s2->ids[k], 9, sp);
                        }
                    }
                }
                break;
            case 0:
                tickTrainCarStateMachine((u8 *)s2);
                if ((s2->type == 0 || s2->type == 3) && s2->bFD == 1) {
                    s32 k;
                    for (k = s2->count - 1; k >= 0; k--) {
                        if (s2->live[k] == 1) {
                            if (getNpcCurrentHealth(*(s32 *)(getNpcContextByIndex(s2->ids[k]) + 0x10)) > 0) {
                                break;
                            }
                            ((u8 *)sp)[0x18] = 0xA;
                            s2->live[k] = 0;
                            slotDispatcherIter(s2->ids[k], 9, sp);
                        }
                    }
                }
            case 1:
                if (s2->flagB1 == 0) {
                    func_mission_overlay_800EFDE0(s2->obj, *(s32 *)(s2->rec + 0xC8), *(s32 *)(s2->rec + 0xCC), dt);
                    tickCraftSplineOrientationDual(s2, dt);
                    transformCraftAnchorsAndApplySubFx(s2, dt);
                }
                break;
            }
            break;
        case 2:
            dispatchEffectByActorType(s2->obj, dt);
            {
                TcSub *p = *(TcSub **)(s2->obj + 0x1A8);
                p->phase += dt * p->rate;
                if (p->phase > 1.0f) {
                    p->phase -= 2.0f;
                }
                s2->pos.y += sinf(p->phase * 3.1415927f) * *(f32 *)(s2->rec + 0xA0) * 0.25f;
            }
            buildDebrisTransformStack(s2, dt);
            if (s2->bC5 == 0) {
                s2->bC5 = 1;
                tickWalkerCraftWithLimbsAndDestruction(s2);
            } else {
                s2->timer -= dt;
                if (s2->timer <= 0.0f) {
                    s2->timer = (s16)(rand() % 4) * 0.033333335f;
                    if (--s2->cntB3 > 0) {
                        sp[0] = s2->pos.x + ((f32)(rand() & 0x7F) - 64.0f) / 640.0f;
                        sp[1] = s2->pos.y - 0.6f;
                        sp[2] = s2->pos.z + ((f32)(rand() & 0x7F) - 64.0f) * 0.015625f;
                        spawnNpcType0xAFromTemplate(sp, TCABSF(((f32)(rand() & 0x7F) - 64.0f) * 0.015625f) + 1.0f);
                        play3DSoundEvent(0, s2, &s2->vel, 24.0f, 0.4f, 0, 0x2A, 0x6E, 0x50);
                    } else {
                        spawnNpcType0xAFromTemplate(s2, s2->radius * 3.0f);
                        play3DSoundEvent(0, s2, &s2->vel, 24.0f, 0.5f, 0, 0x23, 0x7D, 0x50);
                        if (s2->type == 0 || s2->type == 3) {
                            s2->bC6 = 1;
                        } else {
                            releaseMeshAsset(s2->mesh);
                            if (s2->type == 3 || s2->type == 4) {
                                s2->mesh = walkMeshdef0List(D_mission_overlay_800A8084);
                            } else {
                                s2->mesh = walkMeshdef0List(D_mission_overlay_800A8090);
                            }
                            *(u8 **)(getNpcContextByIndex(*(u16 *)(s2->obj + 0x198)) + 0xC) = s2->mesh;
                            mat34CrossRowsAndCopyPos(s2->mesh + 0x28, s2, s2->scale);
                        }
                        if (s2->bC6 != 0) s2->mode = 4; else s2->mode = 3;
                        s2->fB8 = 0.0f;
                        s2->fBC = 0.0f;
                        s2->bC4 = (rand() & 1) ? 2 : 5;
                    }
                }
            }
            break;
        case 4:
            {
                u8 r = slerpFrameTowardTargetAxis(s2, dt);
                buildDebrisTransformStack(s2, dt);
                if (r == 1) {
                    s32 k;
                    s32 n = (s16)(rand() % 5) + 5;
                    for (k = 0; k < n; ) {
                        f32 a;
                        f32 b;
                        f32 c;
                        composeRandomRotationMatrix(sp, &sp[4], s2->radius * 0.5f, 0x5A, 0, 0);
                        sp[0] += s2->pos.x;
                        sp[1] += s2->pos.y;
                        sp[2] += s2->pos.z;
                        scaleVec3ByRandomRange(&sp[4], 3.0f, 4.0f);
                        a = TCABSF(((f32)(rand() & 0x7F) - 64.0f) * 0.03125f * 5.0f) + 20.0f;
                        b = TCABSF(((f32)(rand() & 0x7F) - 64.0f) / 25.6f) + 2.0f;
                        c = TCABSF(((f32)(rand() & 0x7F) - 64.0f) / 213.33333f) + 0.3f;
                        spawnDebris1Npc(sp, &sp[4], a, b, c);
                        k++;
                    }
                    spawnDestructionEffectBurst(s2, 0xFFFF, 2.0f, 1.5f, 1.2f, 0.8f);
                    zmemcpy(&sp[8], s2, 0x30);
                    transformLimbStrideAnchorsLocal(*(u16 *)(arg0 + 0x16), &sp[17], sp);
                    sp[8] += sp[0];
                    sp[9] += sp[1];
                    sp[10] += sp[2];
                    gameStateByteGatedNpcHelper(2, &sp[8], 0, s2->radius * 0.7f, s2->radius * 1.1f, 0.5f);
                    spawnNpcType0xAFromTemplate(s2, s2->radius * 3.5f);
                    play3DSoundEvent(0, s2, &s2->vel, 24.0f, 0.5f, 0, 0x23, 0x7D, 0x50);
                destroy:
                    destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                    return 1;
                }
            }
            break;
        case 3:
            dispatchEffectByActorType(s2->obj, dt);
            {
                TcSub *p = *(TcSub **)(s2->obj + 0x1A8);
                p->phase += dt * p->rate;
                if (p->phase > 1.0f) {
                    p->phase -= 2.0f;
                }
                s2->pos.y += sinf(p->phase * 3.1415927f) * *(f32 *)(s2->rec + 0xA0) * 0.25f;
            }
            buildDebrisTransformStack(s2, dt);
            if (s2->bC6 != 0) {
                s2->mode = 4;
            }
            break;
        }
        if (*(s32 *)(s2->rec + 0x88) == 0) {
            s2->outCount = 0;
        } else if (isNpcWithinActiveReferenceRange(s2) != 0) {
            s2->outCount = 0;
        } else {
            s2->outCount++;
            if (s2->outCount >= 0x15) {
                goto destroy;
            }
        }
        destroyObjectOwnedNpcSlot(s2->obj);
        return 1;
    case 4:
        sub = *(TcSub **)(s2->obj + 0x1A8);
        if (sub->on0 != 0) {
            updateActive3DAudioSource(sub->audio0, s2, &s2->vel, 0x6E);
        }
        if (sub->on1 != 0) {
            updateActive3DAudioSource(sub->audio1, s2, &s2->vel, sub->vol);
        }
        addNpcToVisibilityBucket(*(s32 *)arg2, s2->mesh, s2, s2->radius);
        if (s2->ctx != NULL) {
            advanceNpcOnCurvedPath(*(s32 *)(arg2 + 8), *(s32 *)arg2, s2, s2->ctx);
            return 1;
        }
        return 1;
    case 5:
        a5 = arg2;
        if (*(u16 *)a5 != 0xFFFF) {
            s32 clip = -1;
            f32 *last = NULL;
            switch (s2->type) {
            case 0:
            case 1:
            case 2:
                if (*(u16 *)(a5 + 4) != 0xC && (u16)getPlayerField2(0) == *(u16 *)(a5 + 2)) {
                    clip = 0x15D;
                    last = &D_mission_overlay_8010C0B4_f;
                }
                break;
            case 3:
            case 4:
                if ((u16)getPlayerField2(0) == *(u16 *)(a5 + 2)) {
                    clip = 0xC4;
                    if (rand() & 1) {
                        clip = 0xAA;
                    }
                    last = &D_mission_overlay_8010C0B0_f;
                }
                break;
            default:
                goto noclip;
            }
            if (clip != -1 && D_main_bss_80130BA4 - *last >= 10.0f) {
                *last = D_main_bss_80130BA4;
                playSpeechClip(clip, 0x73, 0.0f, 2);
            }
        }
    noclip:
        switch (*(u16 *)(a5 + 4)) {
        case 0xC:
            if (*(s32 *)(a5 + 8) != 0) {
                vec3ExtrapolateFirstOrder(*(s32 *)(a5 + 8), 0, sp, 0.05f);
                spawnRandomScaleColoredEffectAltVariant(sp, 0.4f);
            }
            play3DSoundEvent(0, s2, &s2->vel, 18.0f, 0.3f, 0, 0x35, 0x78, 0x50);
            if (getObjectDetailLevel(s2->obj) == 1 && D_main_bss_80130B39 == 0) {
                func_mission_overlay_800EFD6C(0x1F4);
            }
            hp = (s32 *)(s2->rec + 0xC4);
            if (s2->flagB1 == 0) {
                if ((hp[D_main_bss_80137CE4] -= *(u16 *)(a5 + 6)) <= 0) {
                    u8 *r = s2->rec;
                    s32 k;
                    s2->flagB1 = 1;
                    datItemSetObjectiveBooleanCount(*(s32 *)(r + 0xB4), *(s32 *)(r + 0xB8), *(s32 *)(r + 0xAC), *(s32 *)(r + 0xB0), *(s32 *)(r + 0xBC), *(s32 *)(s2->rec + 0xC0));
                    for (k = 0; k < 6; k++) {
                        spawnRandomParticleWithParent(0, *(u16 *)(arg0 + 0x16), 0.4f, 1);
                    }
                }
            }
            break;
        case 0xB:
            if (*(u16 *)(a5 + 2) == *(u16 *)(arg0 + 0x16)) {
                break;
            }
        default:
            if (getNpcCurrentHealth(s2->obj) > 0) {
                extrapolateNpcPositionForCurrentMode(a5);
                play3DSoundEvent(0, s2, &s2->vel, 24.0f, 0.4f, 0, 0x2A, 0x6E, 0x50);
                if (s2->type == 0) {
                    u8 *r = s2->rec;
                    if (*(s32 *)(r + 0x11C) != 0 && gObjectiveBooleans[*(s32 *)(r + 0x11C) - 1] == 0) {
                        break;
                    }
                    if (*(s32 *)(r + 0x120) != 0 && gObjectiveCounts[*(s32 *)(r + 0x120) - 1] < *(s32 *)(r + 0x124)) {
                        break;
                    }
                }
                if (s2->type == 3) {
                    u8 *r = s2->rec;
                    if (*(s32 *)(r + 0xC8) != 0 && gObjectiveBooleans[*(s32 *)(r + 0xC8) - 1] == 0) {
                        break;
                    }
                    if (*(s32 *)(r + 0xCC) != 0 && gObjectiveCounts[*(s32 *)(r + 0xCC) - 1] < *(s32 *)(r + 0xD0)) {
                        break;
                    }
                }
                if (getObjectDetailLevel(s2->obj) == 1 && D_main_bss_80130B39 == 0) {
                    func_mission_overlay_800EFD6C(0x1F4);
                }
                if (dealDamageToNpc(s2->obj, *(u16 *)(a5 + 6)) <= 0) {
                    s2->mode = 2;
                    s2->cntB3 = rand() % 8 + 0xA;
                    s2->bC5 = 0;
                    s2->timer = 0.0f;
                    unregisterAndFreeNpcSlot(s2->slotA8, arg0);
                    if (s2->slotAE != 0xFFFF) {
                        unregisterAndFreeNpcSlot(s2->slotAE, arg0);
                    }
                    {
                        u8 *r = s2->rec;
                        datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s2->rec + 0x84));
                    }
                    tallyMidDetailObject(arg0);
                    clearPendingChildNpc(s2->obj);
                    setObjectFlagBit4(arg0);
                    {
                        TcSub *p = *(TcSub **)(s2->obj + 0x1A8);
                        if (p->on0 == 1) {
                            p->on0 = 0;
                            factor5RemoveListNode(p->audio0);
                        }
                    }
                    {
                        TcSub *p = *(TcSub **)(s2->obj + 0x1A8);
                        if (p->on1 == 1) {
                            p->on1 = 0;
                            factor5RemoveListNode(p->audio1);
                        }
                    }
                }
            }
            break;
        }
        if (*(u16 *)a5 != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)a5);
            return 1;
        }
        return 1;
    case 9:
        a9 = arg2;
        switch (a9[0x18]) {
        case 1:
            setType1ActorParams(s2->obj, *(s32 *)a9, a9[9], a9[0xA], a9[8], *(s32 *)(a9 + 4));
            return 1;
        case 2:
        case 3:
            break;
        case 10:
            s2->bC6 = 1;
            break;
        case 5:
            if ((s2->type == 0 || s2->type == 3) && s2->bFD != 0) {
                s32 k;
                for (k = 0; k < s2->count; k++) {
                    if (s2->live[k] == 1) {
                        slotDispatcherIter(s2->ids[k], 9, a9);
                    }
                }
            }
            updateType1AnimRamp(s2->obj, *(s32 *)(a9 + 4), *(s32 *)(a9 + 8), *(s32 *)(a9 + 0xC), a9[0x10]);
            return 1;
        case 8:
            if (getNpcCurrentHealth(s2->obj) > 0) {
                u8 *b;
                s32 o;
                unregisterAndFreeNpcSlot(s2->slotAA, arg0);
                b = (u8 *)D_main_bss_80139560;
                o = 0x2C;
                if (*(s32 *)a9 == 1) {
                    o = 0x2E;
                }
                s2->slotAA = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                unregisterAndFreeNpcSlot(s2->slotAC, arg0);
                o = 0x12;
                if (*(s32 *)a9 == 1) {
                    o = 0xE;
                }
                s2->slotAC = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                if (s2->slotAE != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s2->slotAE, arg0);
                    if (*(s32 *)(s2->rec + 0xA8) != 0) {
                        o = 0x18;
                        if (*(s32 *)a9 == 1) {
                            o = 0x1A;
                        }
                        s2->slotAE = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    }
                }
                setObjectDetailLevel(s2->obj, *(s32 *)a9);
                return 1;
            }
            return 1;
        }
        break;
    case 7:
        dispatchSlotAction5IfActive(arg0, arg2);
        break;
    }
    return 1;
}

s32 playDualTextureAttachmentCue(s32, s32, s32);

void playDualTextureAttachmentCueMode0(s32 arg0, s32 arg1) {
    playDualTextureAttachmentCue(arg0, arg1, 0);
}

s32 playDualTextureAttachmentCue(s32, s32, s32);

void playDualTextureAttachmentCueMode1(s32 arg0, s32 arg1) {
    playDualTextureAttachmentCue(arg0, arg1, 1);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E0790", fake_func_800E406C);
