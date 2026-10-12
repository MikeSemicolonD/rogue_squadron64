#include "common.h"

#include "common_types.h"
#include "rs_math.h"
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

typedef struct { f32 x, y, z; } TcV3;
typedef union { TcV3 v; f32 w[4]; } TcV4;

typedef struct {
    u8 pad0[0x18];
    TcV3 off[2];
    f32 yaw[2];
    f32 lo74[2];
    f32 hi74[2];
    f32 lo7C[2];
    f32 hi7C[2];
    u8 pad58[8];
} TcRow;

extern TcRow tcRows[] __asm__("D_mission_overlay_8010AFF0");
typedef struct {
    u8 pad0[0x18];
    s32 w[2];
} TcCue;
extern TcCue tcCues[] __asm__("D_mission_overlay_8010AFB0");
extern TcV3 D_mission_overlay_8010AF6C;
void tcMat34(void *, void *, f32) __asm__("mat34CrossRowsAndCopyPos");
extern void mat3x3InverseInto(void *, void *);
extern u8 computeActorAnchorDeltaAfterLOS(s32);
extern f32 *getObjectMeshTransformOrLocal(s32, void *);
extern void computeAnchorRelativePositionByDistanceRatio(void *, f32 *, s32, void *);
extern void vec3NormalizeInto(void *, void *);
extern void buildRotationMatrixSlot1(void *, f32);
extern f32 vec3Dot(void *, void *);
extern f32 vec3Length(void *);
extern f32 constMinusSinfApprox(f32);
extern void vec3Cross(void *, void *, void *);
extern void normalize_vector(void *);
extern void quatFromAxisAngle(void *, void *, f32);
extern void rotateVec3ByQuat(void *, void *, void *);

static __inline__ void tcRot(void *q, void *a, void *b) {
    rotateVec3ByQuat(q, a, b);
}

static __inline__ void tcXf(void *m, void *a, void *b) {
    transformVec3ByMat34(m, a, b);
}

void tickCraftSplineOrientationVariant(u8 *npc, f32 dt) {
    f32 m1[12];
    f32 m2[12];
    TcV3 tgt;
    TcV3 dir;
    TcV3 rel;
    f32 buf[12];
    f32 ang;
    f32 ang2;
    f32 lim;
    u8 r;
    s32 i;

    for (i = 0; i < 2; i++) {
        tcMat34(m1, npc, 1.0f);
        mat3x3InverseInto(m2, m1);
        if (npc[0x99] != 0) {
            r = 0;
            if (isPendingChildNpcActive(*(s32 *)(npc + 0x38)) == 1) {
                r = computeActorAnchorDeltaAfterLOS(*(s32 *)(npc + 0x38)) == 1;
            }
        } else {
            switch (i) {
            case 0:
                r = 0;
                if (isPendingChildNpcActive(*(s32 *)(npc + 0x38)) == 1) {
                    r = computeActorAnchorDeltaAfterLOS(*(s32 *)(npc + 0x38)) == 1;
                }
                break;
            case 1:
                r = 0;
                tgt = *(TcV3 *)(npc + 0xC);
                *(f32 *)(npc + 0xC) = -*(f32 *)(npc + 0xC);
                *(f32 *)(npc + 0x10) = -*(f32 *)(npc + 0x10);
                *(f32 *)(npc + 0x14) = -*(f32 *)(npc + 0x14);
                if (isPendingChildNpcActive(*(s32 *)(npc + 0x38)) == 1) {
                    r = computeActorAnchorDeltaAfterLOS(*(s32 *)(npc + 0x38)) == 1;
                }
                *(TcV3 *)(npc + 0xC) = tgt;
                break;
            default:
                continue;
            }
        }
        if (r == 1) {
            computeAnchorRelativePositionByDistanceRatio(npc, getObjectMeshTransformOrLocal(*(s32 *)(npc + 0x38), buf), tcCues[npc[0x99]].w[i], &rel);
            transformVec3ByMat34(m2, &rel, &dir);
            dir.x += tcRows[npc[0x99]].off[i].x * *(f32 *)(npc + 0x70);
            dir.y += tcRows[npc[0x99]].off[i].y * *(f32 *)(npc + 0x70);
            dir.z += tcRows[npc[0x99]].off[i].z * *(f32 *)(npc + 0x70);
            vec3NormalizeInto(&tgt, &dir);
            buildRotationMatrixSlot0(m1, ((f32 *)(npc + 0x7C))[i] + tcRows[npc[0x99]].yaw[i]);
            composeRotationMatrixSlot1(m1, ((f32 *)(npc + 0x74))[i]);
            transformVec3ByMat34(m1, &D_mission_overlay_8010AF6C, &dir);
            ang = constMinusSinfApprox(vec3Dot(&dir, &tgt)) * 57.29578f;
            if (ang > 0.001f) {
                TcV3 axis;
                f32 q[4];
                TcV4 c;
                TcV4 a;
                TcV4 b;
                lim = *(f32 *)(npc + 0x9C) * (dt * 30.0f);
                if (lim < ang) {
                    ang = lim;
                }
                vec3Cross(&axis, &dir, &tgt);
                normalize_vector(&axis);
                quatFromAxisAngle(q, &axis, ang);
                rotateVec3ByQuat(q, &dir, &tgt);
                axis.x = tgt.x;
                axis.y = 0.0f;
                axis.z = tgt.z;
                ang = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010AF6C, &axis) / (vec3Length(&D_mission_overlay_8010AF6C) * vec3Length(&axis))) * 57.29578f;
                a.v = D_mission_overlay_8010AF6C;
                a.v.y = 0.0f;
                b.v = axis;
                b.v.y = 0.0f;
                vec3Cross(&c, &a, &b);
                if (!(c.v.y >= 0.0f)) {
                    ang = -ang;
                }
                buildRotationMatrixSlot1(m1, -ang + tcRows[npc[0x99]].yaw[i]);
                transformVec3ByMat34(m1, &tgt, &axis);
                *(s32 *)&axis.x = 0;
                ((f32 *)(npc + 0x74))[i] = ang + tcRows[npc[0x99]].yaw[i];
                ang2 = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010AF6C, &axis) / (vec3Length(&D_mission_overlay_8010AF6C) * vec3Length(&axis))) * 57.29578f;
                if (!(axis.y <= 0.0f)) {
                    ang2 = -ang2;
                }
                ((f32 *)(npc + 0x7C))[i] = ang2 + tcRows[npc[0x99]].yaw[i];
                if (tcRows[npc[0x99]].yaw[i] == 0.0f) {
                    if (((f32 *)(npc + 0x74))[i] > tcRows[npc[0x99]].lo74[i]) {
                        ((f32 *)(npc + 0x74))[i] = tcRows[npc[0x99]].lo74[i];
                    } else if (((f32 *)(npc + 0x74))[i] < tcRows[npc[0x99]].hi74[i]) {
                        ((f32 *)(npc + 0x74))[i] = tcRows[npc[0x99]].hi74[i];
                    }
                    if (tcRows[npc[0x99]].lo7C[i] < ((f32 *)(npc + 0x7C))[i]) {
                        ((f32 *)(npc + 0x7C))[i] = tcRows[npc[0x99]].lo7C[i];
                    } else if (((f32 *)(npc + 0x7C))[i] < tcRows[npc[0x99]].hi7C[i]) {
                        ((f32 *)(npc + 0x7C))[i] = tcRows[npc[0x99]].hi7C[i];
                    }
                } else {
                    if (((f32 *)(npc + 0x74))[i] > 180.0f) {
                        if (tcRows[npc[0x99]].lo74[i] < 360.0f - ((f32 *)(npc + 0x74))[i]) {
                            ((f32 *)(npc + 0x74))[i] = 360.0f - tcRows[npc[0x99]].lo74[i];
                        }
                    } else if (tcRows[npc[0x99]].lo74[i] < ((f32 *)(npc + 0x74))[i]) {
                        ((f32 *)(npc + 0x74))[i] = tcRows[npc[0x99]].lo74[i];
                    }
                    if (((f32 *)(npc + 0x7C))[i] > 180.0f) {
                        if (tcRows[npc[0x99]].lo7C[i] < 360.0f - ((f32 *)(npc + 0x7C))[i]) {
                            ((f32 *)(npc + 0x7C))[i] = 360.0f - tcRows[npc[0x99]].lo7C[i];
                        }
                    } else if (-((f32 *)(npc + 0x7C))[i] < tcRows[npc[0x99]].hi7C[i]) {
                        ((f32 *)(npc + 0x7C))[i] = -tcRows[npc[0x99]].hi7C[i];
                    }
                }
            }
        } else {
            f32 m[12];
            TcV3 tgt2;
            TcV3 dir2;

            buildRotationMatrixSlot0(m, ((f32 *)(npc + 0x7C))[i]);
            composeRotationMatrixSlot1(m, ((f32 *)(npc + 0x74))[i]);
            transformVec3ByMat34(m, &D_mission_overlay_8010AF6C, &dir2);
            ang = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010AF6C, &dir2)) * 57.29578f;
            if (ang > 0.001f) {
                TcV3 axis;
                f32 q[4];
                TcV3 c;
                TcV3 a;
                TcV3 b;
                lim = *(f32 *)(npc + 0x9C) * (dt * 30.0f);
                if (lim < ang) {
                    ang = lim;
                }
                vec3Cross(&axis, &dir2, &D_mission_overlay_8010AF6C);
                normalize_vector(&axis);
                quatFromAxisAngle(q, &axis, ang);
                tcRot(q, &dir2, &tgt2);
                axis.x = tgt2.x;
                axis.y = 0.0f;
                axis.z = tgt2.z;
                ang = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010AF6C, &axis) / (vec3Length(&D_mission_overlay_8010AF6C) * vec3Length(&axis))) * 57.29578f;
                a = D_mission_overlay_8010AF6C;
                a.y = 0.0f;
                b = axis;
                b.y = 0.0f;
                vec3Cross(&c, &a, &b);
                if (!(c.y >= 0.0f)) {
                    ang = -ang;
                }
                buildRotationMatrixSlot1(m, -ang);
                transformVec3ByMat34(m, &tgt2, &axis);
                *(s32 *)&axis.x = 0;
                ((f32 *)(npc + 0x74))[i] = ang;
                ang2 = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010AF6C, &axis) / (vec3Length(&D_mission_overlay_8010AF6C) * vec3Length(&axis))) * 57.29578f;
                if (!(axis.y <= 0.0f)) {
                    ang2 = -ang2;
                }
                ((f32 *)(npc + 0x7C))[i] = ang2;
            }
        }
    }
}

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

typedef struct { u8 r, g, b, a; } WcCol;
typedef struct {
    f32 x, y, z;
    u8 padC[0x18];
    f32 vel[3];
    s32 part;
    u8 pad34[0x38];
    f32 f6C;
    f32 f70;
    u8 pad74[0x25];
    u8 b99;
} WcObj;
extern WcCol D_mission_overlay_800A8304;
s16 wcRand(void) __asm__("rand");
void transformMeshPartIntoWorld(s32, void *);
void spawnNpcType0xAFromTemplate(void *, f32);
void spawnByteAnimDebrisDefault(void *);
void composeRandomRotationMatrix(void *, void *, f32, s32, s32, s32);
void scaleVec3ByRandomRange(void *, f32, f32);
void spawnDebris1Npc(void *, void *, f32, f32, f32);
void spawnOrientedNpc(s32, void *, s32, void *, f32, f32, f32, f32);
void spawnWaterSprayDebrisAndBurst(void *, f32, f32, f32, f32, f32);

void npcWaterCraftHandleDestruction(WcObj *o) {
    f32 p[3];
    f32 v[3];
    f32 pos[3];
    WcCol col;
    f32 sc;
    s32 i;
    s32 n;
    f32 a, b;

    col = D_mission_overlay_800A8304;
    switch (o->b99) {
    case 0:
        transformMeshPartIntoWorld(o->part, pos);
        sc = o->f70 * 13.333f;
        spawnNpcType0xAFromTemplate(pos, o->f6C * 2.5f);
        spawnByteAnimDebrisDefault(o);
        switch (o->b99) {
        case 0:
            play3DSoundEvent(0, o, o->vel, 24.0f, 0.5f, 0, 0x21, 0x7D, 0x50);
            break;
        case 1:
            play3DSoundEvent(0, o, o->vel, 24.0f, 0.7f, 0, 0x21, 0x7D, 0x50);
            break;
        }
        n = (s16)(wcRand() % 3) + 4;
        for (i = 0; i < n; i++) {
            composeRandomRotationMatrix(p, v, o->f6C * 0.5f, 0x3C, 0, 0);
            p[0] += pos[0];
            p[1] += pos[1];
            p[2] += pos[2];
            scaleVec3ByRandomRange(v, 2.0f, 3.0f);
            a = FABSF_VAL(((f32)(wcRand() & 0x7F) - 64.0f) / 12.8f);
            a = a + 12.0f;
            b = FABSF_VAL(((f32)(wcRand() & 0x7F) - 64.0f) * 0.015625f);
            b = b + 1.0f;
            spawnDebris1Npc(p, v, a, b, FABSF_VAL(((f32)(wcRand() & 0x7F) - 64.0f) / 320.0f) + 0.2f);
        }
        spawnWaterSprayDebrisAndBurst(o, sc * 1.5f, sc * 2.5f, sc * 3.0f, sc * 6.0f, 1.0f);
        break;
    case 1:
        transformMeshPartIntoWorld(o->part, pos);
        sc = o->f70 * 40.0f;
        spawnNpcType0xAFromTemplate(pos, o->f6C * 2.5f);
        spawnByteAnimDebrisDefault(o);
        switch (o->b99) {
        case 0:
            play3DSoundEvent(0, o, o->vel, 24.0f, 0.5f, 0, 0x21, 0x7D, 0x50);
            break;
        case 1:
            play3DSoundEvent(0, o, o->vel, 24.0f, 0.7f, 0, 0x21, 0x7D, 0x50);
            break;
        }
        spawnOrientedNpc(0x8002, pos, 0, 0, sc * 0.75f, sc * 1.2f, 1.0f, 0.6f);
        spawnOrientedNpc(0x8001, pos, 0, &col, sc * 0.5f, sc * 0.7f, 1.0f, 0.4f);
        n = (s16)(wcRand() % 5) + 10;
        for (i = 0; i < n; i++) {
            composeRandomRotationMatrix(p, v, o->f6C * 0.5f, 0x3C, 0, 0);
            p[0] += pos[0];
            p[1] += pos[1];
            p[2] += pos[2];
            scaleVec3ByRandomRange(v, 2.0f, 3.0f);
            a = FABSF_VAL(((f32)(wcRand() & 0x7F) - 64.0f) / 12.8f);
            a = a + 12.0f;
            b = FABSF_VAL(((f32)(wcRand() & 0x7F) - 64.0f) * 0.03125f);
            b = b + 2.5f;
            spawnDebris1Npc(p, v, a, b, FABSF_VAL(((f32)(wcRand() & 0x7F) - 64.0f) / 320.0f) + 0.2f);
        }
        spawnWaterSprayDebrisAndBurst(o, sc * 4.0f, sc * 6.0f, sc * 5.0f, sc * 10.0f, 2.0f);
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E5080", npcWaterCraftUpdate);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E5080", fake_func_800E71C8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E5080", D_mission_overlay_800A84B8);
