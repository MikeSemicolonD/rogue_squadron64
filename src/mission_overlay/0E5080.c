#include "common.h"

#include "common_types.h"
INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E5080", D_mission_overlay_800A8290);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E5080", D_mission_overlay_800A8298);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E5080", D_mission_overlay_800A82A0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E5080", D_mission_overlay_800A82AC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E5080", D_mission_overlay_800A82B8);

typedef struct {
    u8 pad0[0x18];
    f32 f18;
    f32 f1C;
} CueSlotF;

extern CueSlotF sCueSlotsF[] __asm__("D_mission_overlay_8010AFB0");
extern s32 D_main_bss_80137CE4;
extern s32 setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern void initActorMotionParams(s32, f32, f32, f32, f32);
extern void initObjectAnimSubstruct(s32, s32, s32, s32, f32, void *, s32, f32, f32, s32);
s32 playDualTextureAttachmentCueB();
s32 playDualTextureAttachmentCueC();
s32 playAttachmentMaterialSoundSimpleB();

void resetCraftInstanceMotionState(void *arg0) {
    u8 *npc;
    u8 *def;
    s32 i;
    s32 k;

    npc = *(u8 **)((u8 *)arg0 + 4);
    def = *(u8 **)(npc + 0x34);
    npc[0x9A] = 0;
    for (i = 0; i < 2; i++) {
        ((s32 *)(npc + 0x74))[i] = 0;
        ((s32 *)(npc + 0x7C))[i] = 0;
        ((f32 *)(npc + 0xA4))[i] = 1.0f;
        ((s32 *)(npc + 0xAC))[i] = 0;
    }
    npc[0x9B] = 0;
    *(f32 *)(npc + 0xA0) = *(f32 *)(*(u8 **)(npc + 0x34) + 0x90);
    setNpcHealth(*(s32 *)(npc + 0x38), *(u8 **)(npc + 0x34) + 0x6C, *(u8 **)(npc + 0x34));
    setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(*(u8 **)(npc + 0x34) + 0xA8));
    k = D_main_bss_80137CE4;
    *(f32 *)(npc + 0x9C) = ((f32 *)(*(u8 **)(npc + 0x34) + 0xC0))[k];
    initActorMotionParams(*(s32 *)(npc + 0x38), ((f32 *)(*(u8 **)(npc + 0x34) + 0xB8))[k], ((f32 *)(*(u8 **)(npc + 0x34) + 0xBC))[k], ((f32 *)(*(u8 **)(npc + 0x34) + 0xC4))[k], ((f32 *)(*(u8 **)(npc + 0x34) + 0xC8))[k]);
    switch (npc[0x99]) {
    case 0:
        initObjectAnimSubstruct(*(s32 *)(npc + 0x38), *(s32 *)(def + 0xCC), *(s32 *)(def + 0xD0), *(s32 *)(def + 0xD4), *(f32 *)(def + 0xD8), playDualTextureAttachmentCueB, 0, sCueSlotsF[npc[0x99]].f18, 15.0f, 0);
        initObjectAnimSubstruct(*(s32 *)(npc + 0x38), *(s32 *)(def + 0xCC), *(s32 *)(def + 0xD0), *(s32 *)(def + 0xD4), *(f32 *)(def + 0xD8), playAttachmentMaterialSoundSimpleB, 1, sCueSlotsF[npc[0x99]].f1C, 15.0f, 0);
        break;
    case 1:
        initObjectAnimSubstruct(*(s32 *)(npc + 0x38), *(s32 *)(def + 0xCC), *(s32 *)(def + 0xD0), *(s32 *)(def + 0xD4), *(f32 *)(def + 0xD8), playDualTextureAttachmentCueC, 0, sCueSlotsF[npc[0x99]].f18, 15.0f, 0);
        break;
    }
}

typedef struct {
    u8 pad0[0x18];
    s32 w18;
    s32 w1C;
} CueSlotI;

typedef struct {
    f32 m[12];
} AttachMtxB;

extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern void resolveNpcAttachmentPos(s32, AttachMtxB *, s32, f32);
extern u8 tickProgressChannel(s32, AttachMtxB *, s32, f32 *);
extern void triggerCueWithSlotEffect(s32, s32, AttachMtxB *, void *, s32, f32, f32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 playDualTextureAttachmentCueB(void *arg0) {
    AttachMtxB mtx1;
    AttachMtxB mtx2;
    AttachMtxB scratch;
    f32 prog1;
    f32 prog2;
    f32 rate;
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 r;

    lookupHmtTextureByName(*(s32 *)(npc + 0x30), "b_c", 0, &mtx1, (s32)&scratch, 0);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), "b_c", 1, &mtx2, (s32)&scratch, 1);
    rate = ((f32 *)(*(u8 **)(npc + 0x34) + 0xDC))[D_main_bss_80137CE4];
    if (rate != 0.0f) {
        resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx1, ((CueSlotI *)sCueSlotsF)[npc[0x99]].w18, rate);
        resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx2, ((CueSlotI *)sCueSlotsF)[npc[0x99]].w18, rate);
    }
    r = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx1, 0, &prog1);
    if (r == 1) {
        r = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx2, 0, &prog2);
        if (r == 1) {
            *(f32 *)(npc + 0xA4) = 0.0f;
            triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, &mtx1, &sCueSlotsF[npc[0x99]], r, sCueSlotsF[npc[0x99]].f18, prog1);
            triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, &mtx2, &sCueSlotsF[npc[0x99]], 0, sCueSlotsF[npc[0x99]].f18, prog2);
            play3DSoundEvent(0, npc, npc + 0x24, 14.0f, 0.1f, 0, 0x1D, 0x78, 0x28);
        }
    }
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E5080", D_mission_overlay_800A82D4);

typedef struct {
    f32 m[12];
} AttachMtxBDup;

extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern void resolveNpcAttachmentPos(s32, AttachMtxB *, s32, f32);
extern u8 tickProgressChannel(s32, AttachMtxB *, s32, f32 *);
extern void triggerCueWithSlotEffect(s32, s32, AttachMtxB *, void *, s32, f32, f32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern char D_mission_overlay_800A82D4[];
typedef struct {
    u8 pad0[0x18];
    s32 w18;
    s32 w1C;
} CueSlotB;
extern CueSlotB D_mission_overlay_8010AFB0[];
extern u8 D_mission_overlay_8010AFBC[];
extern s32 D_main_bss_80137CE4;

s32 playAttachmentMaterialSoundSimpleB(void *arg0) {
    AttachMtxB mtx;
    f32 progress;
    f32 rate;
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 r;

    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A82D4, 0, &mtx, 0, 0);
    rate = ((f32 *)(*(u8 **)(npc + 0x34) + 0xDC))[D_main_bss_80137CE4];
    if (rate != 0.0f) {
        resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx, D_mission_overlay_8010AFB0[npc[0x99]].w1C, rate);
    }
    r = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx, 1, &progress);
    if (r == 1) {
        *(f32 *)(npc + 0xA8) = 0.0f;
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, &mtx, D_mission_overlay_8010AFBC + (npc[0x99] << 5), r, *(f32 *)(D_mission_overlay_8010AFBC + (npc[0x99] << 5) + 0x10), progress);
        play3DSoundEvent(0, npc, npc + 0x24, 14.0f, 0.1f, 0, 0x1D, 0x78, 0x28);
    }
    return 0;
}

s32 playDualTextureAttachmentCueC(void *arg0)
{
  int new_var2;
  AttachMtxB mtx1;
  AttachMtxB mtx2;
  f32 prog1;
  s32 *new_var;
  f32 prog2;
  f32 rate;
  CueSlotB *new_var4;
  u8 *npc = *((u8 **) (((u8 *) arg0) + 4));
  u8 r;
  u8 *new_var3;
  lookupHmtTextureByName(*((s32 *) (npc + 0x30)), D_mission_overlay_800A82D4, 0, &mtx1, 0, 0);
  lookupHmtTextureByName(*((s32 *) (npc + 0x30)), "b", 0, &mtx2, 0, 0);
  rate = ((f32 *) ((*((u8 **) (npc + 0x34))) + 0xDC))[D_main_bss_80137CE4];
  new_var2 = 0x38;
  if (rate != 0.0f)
  {
    resolveNpcAttachmentPos(*((s32 *) (npc + new_var2)), &mtx1, D_mission_overlay_8010AFB0[npc[0x99]].w18, rate);
    resolveNpcAttachmentPos(*((s32 *) (npc + new_var2)), &mtx2, D_mission_overlay_8010AFB0[npc[0x99]].w1C, rate);
  }
  r = tickProgressChannel(*((s32 *) (npc + new_var2)), &mtx1, 0, &prog1);
  if (r == 1)
  {
    r = tickProgressChannel(*((s32 *) (npc + 0x38)), &mtx2, 0, &prog2);
    if (r == 1)
    {
      new_var3 = npc;
      new_var4 = D_mission_overlay_8010AFB0;
      new_var = (s32 *) (new_var3 + new_var2);
      *((f32 *) (new_var3 + 0xA4)) = 0.0f;
      *((f32 *) (new_var3 + 0xA8)) = 0.0f;
      triggerCueWithSlotEffect(*new_var, 2, &mtx1, &D_mission_overlay_8010AFB0[new_var3[0x99]], r, *((f32 *) (((new_var3[0x99] << 5) + ((u8 *) new_var4)) + 0x18)), prog1);
      triggerCueWithSlotEffect(*new_var, 2, &mtx2, (new_var3[0x99] << 5) + (&D_mission_overlay_8010AFB0->pad0[0xC]), 0, *((f32 *) (((new_var3[0x99] << 5) + ((u8 *) new_var4)) + 0x1C)), prog2);
      play3DSoundEvent(0, new_var3, new_var3 + 0x24, 14.0f, 0.1f, 0, 0x1D, 0x6E, 0x28);
    }
  }
  return 0;
}

typedef struct {
    f32 v[12];
} NpcXform30;

typedef struct {
    u8 pad0[0x30];
    f32 yaw[2];
    u8 pad38[0x28];
} AnchorYawRow;

extern AnchorYawRow D_mission_overlay_8010AFF0[];
extern u8 isPendingChildNpcActive(s32);
extern u8 validateActorTargetLOS(s32);
extern void applyToObjectSubstructByFlag(s32, f32, f32, s32);
extern void buildRotationMatrixSlot0(void *, f32);
extern void composeRotationMatrixSlot1(void *, f32);
extern void transformVec3ByMat34(void *, void *, void *);

void transformCraftAnchorsApplySubFx2(u8 *npc, f32 dt) {
    NpcXform30 save;
    f32 mtx[12];
    s32 i;
    u8 r;

    for (i = 0; i < 2; i++) {
        if (isPendingChildNpcActive(*(s32 *)(npc + 0x38)) != 1) {
            continue;
        }
        save = *(NpcXform30 *)npc;
        buildRotationMatrixSlot0(mtx, ((f32 *)(npc + 0x7C))[i] + D_mission_overlay_8010AFF0[npc[0x99]].yaw[i]);
        composeRotationMatrixSlot1(mtx, ((f32 *)(npc + 0x74))[i]);
        transformVec3ByMat34(mtx, &save.v[3], npc + 0xC);
        transformVec3ByMat34(mtx, &save.v[6], npc + 0x18);
        switch (npc[0x99]) {
        case 0:
        case 1:
            r = validateActorTargetLOS(*(s32 *)(npc + 0x38));
            break;
        default:
            *(NpcXform30 *)npc = save;
            continue;
        }
        if (r == 1) {
            switch (i) {
            case 0:
                applyToObjectSubstructByFlag(*(s32 *)(npc + 0x38), dt, 0.0f, 0);
                break;
            case 1:
                applyToObjectSubstructByFlag(*(s32 *)(npc + 0x38), dt, 0.0f, 1);
                break;
            }
        }
        *(NpcXform30 *)npc = save;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E5080", tickCraftSplineOrientationVariant);

typedef struct {
    /* 0x00 */ u8 pad0[0x4C];
    /* 0x4C */ u32 flags;
    /* 0x50 */ f32 f50;
    /* 0x54 */ f32 f54;
    /* 0x58 */ f32 f58;
    /* 0x5C */ s32 w5C;
    /* 0x60 */ s32 w60;
    /* 0x64 */ s32 w64;
    /* 0x68 */ u8 q68[0x10];
    /* 0x78 */ f32 f78;
    /* 0x7C */ f32 f7C;
    /* 0x80 */ f32 f80;
} TsdDef;

typedef struct {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ u8 mat[1];
} TsdObj;

typedef struct {
    u8 pad0[0x58];
    f32 f58;
} TsdRow;

typedef struct {
    /* 0x00 */ u8 pad0[0x30];
    /* 0x30 */ u8 *p30;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ s32 h38;
    /* 0x3C */ TsdObj *o3C[2];
    /* 0x44 */ TsdObj *o44[2];
    /* 0x4C */ TsdObj *o4C[2];
    /* 0x54 */ TsdDef *d54[2];
    /* 0x5C */ TsdDef *d5C[2];
    /* 0x64 */ TsdDef *d64[2];
    /* 0x6C */ u8 pad6C[4];
    /* 0x70 */ s32 w70;
    /* 0x74 */ f32 a74[2];
    /* 0x7C */ f32 a7C[2];
    /* 0x84 */ u8 pad84[0x99 - 0x84];
    /* 0x99 */ u8 b99;
    /* 0x9A */ u8 pad9A[0xAC - 0x9A];
    /* 0xAC */ f32 aAC[2];
} TsdOwner;

void mat34CrossRowsAndCopyPos(void *, void *, s32);
s32 getNpcCurrentHealth(s32);
void clearVec4QuadStruct(void *);
void addVec3At0x24(void *, f32, f32, f32);
void applyScaleToMat3x4(void *, s32, s32, s32);
void composeQuatToMat3x4(void *, void *);
void composeRotationMatrixSlot0(void *, f32);

void tickStructureWithDestructionAndChildren(TsdOwner *s) {
    s32 i;
    TsdObj *o;
    TsdDef *d;
    u8 *m;
    u32 fl;

    mat34CrossRowsAndCopyPos(s->p30 + 0x28, s, s->w70);
    if (getNpcCurrentHealth(s->h38) > 0) {
        i = 0;
        do {
            if (s->o3C[i] != NULL) {
                o = s->o3C[i];
                m = o->mat;
                d = s->d54[i];
                clearVec4QuadStruct(m);
                if (d->flags & 1) {
                    addVec3At0x24(m, -d->f50, -d->f54, -d->f58);
                }
                if (d->flags & 2) {
                    applyScaleToMat3x4(m, d->w5C, d->w60, d->w64);
                }
                if (d->flags & 4) {
                    composeQuatToMat3x4(m, d->q68);
                }
                composeRotationMatrixSlot1(m, s->a74[i]);
                fl = d->flags;
                if ((fl & 9) == 9) {
                    addVec3At0x24(m, d->f78 + d->f50, d->f7C + d->f54, d->f80 + d->f58);
                } else if ((fl & 9) == 8) {
                    addVec3At0x24(m, d->f78, d->f7C, d->f80);
                } else if (fl & 1) {
                    addVec3At0x24(m, d->f50, d->f54, d->f58);
                }
            }
            if (s->o44[i] != NULL) {
                o = s->o44[i];
                m = o->mat;
                d = s->d5C[i];
                clearVec4QuadStruct(m);
                if (d->flags & 1) {
                    addVec3At0x24(m, -d->f50, -d->f54, -d->f58);
                }
                if (d->flags & 2) {
                    applyScaleToMat3x4(m, d->w5C, d->w60, d->w64);
                }
                if (d->flags & 4) {
                    composeQuatToMat3x4(m, d->q68);
                }
                if (s->o4C[i] == NULL) {
                    addVec3At0x24(m, 0.0f, 0.0f, -s->aAC[i] * ((TsdRow *)((u8 *)D_mission_overlay_8010AFF0 + (s->b99 * 0x60 + i * 4)))->f58);
                }
                composeRotationMatrixSlot0(m, s->a7C[i]);
                fl = d->flags;
                if ((fl & 9) == 9) {
                    addVec3At0x24(m, d->f78 + d->f50, d->f7C + d->f54, d->f80 + d->f58);
                } else if ((fl & 9) == 8) {
                    addVec3At0x24(m, d->f78, d->f7C, d->f80);
                } else if (fl & 1) {
                    addVec3At0x24(m, d->f50, d->f54, d->f58);
                }
            }
            if (s->o4C[i] != NULL) {
                o = s->o4C[i];
                m = o->mat;
                d = s->d64[i];
                clearVec4QuadStruct(m);
                if (d->flags & 1) {
                    addVec3At0x24(m, -d->f50, -d->f54, -d->f58);
                }
                if (d->flags & 2) {
                    applyScaleToMat3x4(m, d->w5C, d->w60, d->w64);
                }
                if (d->flags & 4) {
                    composeQuatToMat3x4(m, d->q68);
                }
                addVec3At0x24(m, 0.0f, 0.0f, -s->aAC[i] * ((TsdRow *)((u8 *)D_mission_overlay_8010AFF0 + (s->b99 * 0x60 + i * 4)))->f58);
                fl = d->flags;
                if ((fl & 9) == 9) {
                    addVec3At0x24(m, d->f78 + d->f50, d->f7C + d->f54, d->f80 + d->f58);
                } else if ((fl & 9) == 8) {
                    addVec3At0x24(m, d->f78, d->f7C, d->f80);
                } else if (fl & 1) {
                    addVec3At0x24(m, d->f50, d->f54, d->f58);
                }
            }
            i++;
        } while (i < 2);
    }
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E5080", D_mission_overlay_800A8304);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E5080", npcWaterCraftHandleDestruction);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E5080", npcWaterCraftUpdate);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E5080", fake_func_800E71C8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E5080", D_mission_overlay_800A84B8);
