#include "common.h"
#include "common_types.h"

typedef struct {
    f32 m[12];
} Tca3Mtx;
typedef struct {
    Tca3Mtx mtx;
    u8 pad30[8];
    s32 obj;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    u8 pad50[0x14];
    s16 h64;
} Tca3Npc;
u8 isPendingChildNpcActive(s32);
u8 validateActorTargetLOS(s32);
void buildRotationMatrixSlot0(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
void transformVec3ByMat34(void *, void *, void *);
extern u8 D_main_bss_80130B63;
s32 playAttachmentCueNoTexture(void *arg0);
extern void tca3InitAnim(s32, f32, f32, f32, f32, void *, s32, f32, f32, f32) __asm__("initObjectAnimSubstruct");
extern void applyToObjectSubstructByFlag(s32, f32, f32, s32);

void transformCraftAnchorsApplySubFx3(Tca3Npc *npc, f32 dt) {
    Tca3Mtx saved;
    f32 m[12];
    u8 r;
    u8 r2;

    if (isPendingChildNpcActive(npc->obj) == 1) {
        saved = npc->mtx;
        buildRotationMatrixSlot0(m, npc->f4C);
        composeRotationMatrixSlot1(m, npc->f48);
        transformVec3ByMat34(m, &saved.m[3], &npc->mtx.m[3]);
        transformVec3ByMat34(m, &saved.m[6], &npc->mtx.m[6]);
        r = validateActorTargetLOS(npc->obj);
        if (r == 1) {
            if (D_main_bss_80130B63 != 0) {
                npc->h64 = 3;
            } else {
                r2 = isPendingChildNpcActive(npc->obj);
                if (r2 == r && validateActorTargetLOS(npc->obj) == r2) {
                    {
                        union { s32 i; f32 f; } u1, u0;
                        u1.i = 0x3F800000;
                        u0.i = 0;
                        tca3InitAnim(npc->obj, u1.f, u0.f, u1.f, u0.f, playAttachmentCueNoTexture, 0, 10.0f, 15.0f, u0.f);
                    }
                    applyToObjectSubstructByFlag(npc->obj, dt, 0.0f, 0);
                }
            }
        }
        npc->mtx = saved;
    }
}

typedef struct {
    u8 pad0[0x38];
    s32 obj;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    u8 pad50[0xC];
    f32 f5C;
} FsNpc;
typedef struct { s32 x, y, z; } FsV3i;
extern f32 D_mission_overlay_8010B0B0[];
u8 isPendingChildNpcActive(s32);
u8 computeActorAnchorDeltaAfterLOS(s32);
void *getObjectMeshTransformOrLocal(s32, void *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void mat3x3InverseInto(void *, void *);
void transformVec3ByMat34(void *, void *, void *);
void vec3NormalizeInto(void *, void *);
void buildRotationMatrixSlot0(void *, f32);
void buildRotationMatrixSlot1(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
f32 vec3Dot(void *, void *);
f32 vec3Length(void *);
f32 constMinusSinfApprox(f32);
void vec3Cross(void *, void *, void *);
void normalize_vector(void *);
void quatFromAxisAngle(void *, void *, f32);
void rotateVec3ByQuat(void *, void *, void *);

void tickFighterSquadronWithSplinePaths(FsNpc *npc, f32 dt) {
    f32 mtx[12];
    f32 inv[12];
    f32 dir[4];
    f32 v80[4];
    f32 meshbuf[12];
    f32 ang;
    f32 lim;
    f32 b;

    if (isPendingChildNpcActive(npc->obj) == 1 && computeActorAnchorDeltaAfterLOS(npc->obj) == 1) {
        f32 axis[4];
        f32 q[4];
        f32 cr[4];
        f32 t1[4];
        f32 t2[4];
        void *mesh;

        mesh = getObjectMeshTransformOrLocal(npc->obj, meshbuf);
        mat34CrossRowsAndCopyPos(mtx, npc, 1.0f);
        mat3x3InverseInto(inv, mtx);
        transformVec3ByMat34(inv, mesh, v80);
        vec3NormalizeInto(dir, v80);
        buildRotationMatrixSlot0(mtx, npc->f4C);
        composeRotationMatrixSlot1(mtx, npc->f48);
        transformVec3ByMat34(mtx, D_mission_overlay_8010B0B0, v80);
        ang = constMinusSinfApprox(vec3Dot(v80, dir)) * 57.29578f;
        if (0.001f < ang) {
            lim = npc->f5C * (dt * 30.0f);
            if (lim < ang) {
                ang = lim;
            }
            vec3Cross(axis, v80, dir);
            normalize_vector(axis);
            quatFromAxisAngle(q, axis, ang);
            rotateVec3ByQuat(q, v80, dir);
            axis[1] = 0.0f;
            axis[0] = dir[0];
            axis[2] = dir[2];
            ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B0B0, axis) / (vec3Length(D_mission_overlay_8010B0B0) * vec3Length(axis))) * 57.29578f;
            *(FsV3i *)t1 = *(FsV3i *)D_mission_overlay_8010B0B0;
            t1[1] = 0.0f;
            *(FsV3i *)t2 = *(FsV3i *)axis;
            t2[1] = 0.0f;
            vec3Cross(cr, t1, t2);
            if (!(0.0f <= cr[1])) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(mtx, -ang);
            transformVec3ByMat34(mtx, dir, axis);
            axis[0] = 0.0f;
            npc->f48 = ang;
            b = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B0B0, axis) / (vec3Length(D_mission_overlay_8010B0B0) * vec3Length(axis))) * 57.29578f;
            if (!(axis[1] <= 0.0f)) {
                b = -b;
            }
            npc->f4C = b;
        }
    } else {
        f32 m[12];
        f32 r[4];
        f32 v[4];
        f32 axis[4];
        f32 q[4];
        f32 cr[4];
        f32 t1[4];
        f32 t2[4];

        buildRotationMatrixSlot0(m, npc->f4C);
        composeRotationMatrixSlot1(m, npc->f48);
        transformVec3ByMat34(m, D_mission_overlay_8010B0B0, v);
        ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B0B0, v)) * 57.29578f;
        if (0.001f < ang) {
            lim = npc->f5C * (dt * 30.0f);
            if (lim < ang) {
                ang = lim;
            }
            vec3Cross(axis, v, D_mission_overlay_8010B0B0);
            normalize_vector(axis);
            quatFromAxisAngle(q, axis, ang);
            rotateVec3ByQuat(q, v, r);
            axis[1] = 0.0f;
            axis[0] = r[0];
            axis[2] = r[2];
            ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B0B0, axis) / (vec3Length(D_mission_overlay_8010B0B0) * vec3Length(axis))) * 57.29578f;
            *(FsV3i *)t1 = *(FsV3i *)D_mission_overlay_8010B0B0;
            t1[1] = 0.0f;
            *(FsV3i *)t2 = *(FsV3i *)axis;
            t2[1] = 0.0f;
            vec3Cross(cr, t1, t2);
            if (!(0.0f <= cr[1])) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(m, -ang);
            transformVec3ByMat34(m, r, axis);
            axis[0] = 0.0f;
            npc->f48 = ang;
            b = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B0B0, axis) / (vec3Length(D_mission_overlay_8010B0B0) * vec3Length(axis))) * 57.29578f;
            if (!(axis[1] <= 0.0f)) {
                b = -b;
            }
            npc->f4C = b;
        }
    }
}

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
