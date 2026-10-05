#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D6BE0", npcInitSimpleModel);

typedef struct { f32 m[12]; } TickMtx;
extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern void resolveNpcAttachmentPos(s32, TickMtx *, f32, f32);
extern u8 tickProgressChannel(s32, TickMtx *, s32, f32 *);
extern u16 triggerCueWithSlotEffect(s32, s32, TickMtx *, void *, s32, f32, f32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void slotDispatcherIter(s32, s32, s16 *);
extern s32 D_main_bss_80137CE4;
extern u8 D_mission_overlay_8010A890[];
extern u8 D_mission_overlay_8010A89C[];

s32 npcTickEffectChannelShared(s32 arg0, s32 arg1, s32 arg2) {
    TickMtx mtx;
    struct { s16 h58; u8 pad5A[0x16]; f32 f70; s8 b74; } p;
    f32 prog;
    f32 fv;
    u8 r;
    u8 *npc = *(u8 **)(arg0 + 4);

    if (arg2 == 0) {
        lookupHmtTextureByName(*(s32 *)(npc + 0x30), "a", 0, &mtx, 0, 0);
        r = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx, 0, &prog);
        if (r == 1) {
            fv = ((f32 *)(*(u8 **)(npc + 0x34) + 0xC0))[D_main_bss_80137CE4];
            fv = (fv + 10.0f) * 0.25f;
            p.b74 = 0;
            p.f70 = fv;
            if (fv > 50.0f) {
                p.f70 = 50.0f;
            }
            p.h58 = 2;
            *(s32 *)(npc + 0xF8) = 0;
            slotDispatcherIter(triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, &mtx, D_mission_overlay_8010A890, r, 10.0f, prog), 0xA, (s16 *)&p);
            play3DSoundEvent(0, npc, npc + 0x24, 10.0f, 0.3f, 0, 0xD, 0x7D, 0x28);
        }
    } else {
        lookupHmtTextureByName(*(s32 *)(npc + 0x30), "b", 0, &mtx, 0, 0);
        fv = ((f32 *)(*(u8 **)(npc + 0x34) + 0xD4))[D_main_bss_80137CE4];
        if (fv != 0.0f) {
            resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx, 10.0f, fv);
        }
        r = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx, 1, &prog);
        if (r == 1) {
            triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, &mtx, D_mission_overlay_8010A89C, r, 10.0f, prog);
            play3DSoundEvent(0, npc, npc + 0x24, 10.0f, 0.1f, 0, 0x1D, 0x78, 0x28);
        }
    }
    return 0;
}

typedef struct { f32 x, y, z; } AimV3;
typedef union { AimV3 v; f32 w[4]; } AimV4;
extern AimV3 D_mission_overlay_8010A884;
extern u8 isPendingChildNpcActive(s32);
extern u8 computeActorAnchorDeltaAfterLOS(s32);
extern f32 *getObjectMeshTransformOrLocal(s32, void *);
extern void mat34CrossRowsAndCopyPos(void *, void *, f32);
extern void mat3x3InverseInto(void *, void *);
extern void transformVec3ByMat34(void *, void *, void *);
extern void vec3NormalizeInto(void *, void *);
extern void buildRotationMatrixSlot0(void *, f32);
extern void buildRotationMatrixSlot1(void *, f32);
extern void composeRotationMatrixSlot1(void *, f32);
extern f32 vec3Dot(void *, void *);
extern f32 vec3Length(void *);
extern f32 constMinusSinfApprox(f32);
extern void vec3Cross(void *, void *, void *);
extern void normalize_vector(void *);
extern void quatFromAxisAngle(void *, void *, f32);
extern void rotateVec3ByQuat(void *, void *, void *);
extern void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
extern void factor5RemoveListNode(void *);

void npcTankDroidComputeAimMotion(u8 *npc, f32 dt) {
    f32 m1[12];
    f32 m2[12];
    AimV3 tgt;
    AimV3 dir;
    f32 buf[12];
    f32 *pos;
    f32 ang;
    f32 ang2;
    f32 lim;
    u8 r;
    s32 los;

    r = isPendingChildNpcActive(*(s32 *)(npc + 0x38));
    if (r != 1) goto other;
    los = computeActorAnchorDeltaAfterLOS(*(s32 *)(npc + 0x38));
    if (los == r) {
        pos = getObjectMeshTransformOrLocal(*(s32 *)(npc + 0x38), buf);
        mat34CrossRowsAndCopyPos(m1, npc, 1.0f);
        mat3x3InverseInto(m2, m1);
        transformVec3ByMat34(m2, pos, &dir);
        dir.y -= *(f32 *)(npc + 0x5C);
        vec3NormalizeInto(&tgt, &dir);
        buildRotationMatrixSlot0(m1, *(f32 *)(npc + 0x58));
        composeRotationMatrixSlot1(m1, *(f32 *)(npc + 0x54));
        transformVec3ByMat34(m1, &D_mission_overlay_8010A884, &dir);
        ang = constMinusSinfApprox(vec3Dot(&dir, &tgt)) * 57.29578f;
        if (ang > 0.001f) {
            AimV3 axis;
            f32 q[4];
            AimV4 c;
            AimV4 a;
            AimV4 b;
            if (ang > 10.0f && npc[0xF0] == 0) {
                npc[0xF0] = los;
                play3DSoundEventVariant(npc + 0x68, npc, npc + 0x24, 8.0f, 0.1f, 7, 0x4A, los, 0x6E, 0x28);
            }
            lim = *(f32 *)(npc + 0xF4) * (dt * 30.0f);
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
            ang = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010A884, &axis) / (vec3Length(&D_mission_overlay_8010A884) * vec3Length(&axis))) * 57.29578f;
            a.v = D_mission_overlay_8010A884;
            a.v.y = 0.0f;
            b.v = axis;
            b.v.y = 0.0f;
            vec3Cross(&c, &a, &b);
            if (!(c.v.y >= 0.0f)) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(m1, -ang);
            transformVec3ByMat34(m1, &tgt, &axis);
            axis.x = 0.0f;
            *(f32 *)(npc + 0x54) = ang;
            ang2 = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010A884, &axis) / (vec3Length(&D_mission_overlay_8010A884) * vec3Length(&axis))) * 57.29578f;
            if (!(axis.y <= 0.0f)) {
                ang2 = -ang2;
            }
            *(f32 *)(npc + 0x58) = ang2;
            if (ang2 > 35.0f) {
                *(f32 *)(npc + 0x58) = 35.0f;
            } else if (ang2 < -10.0f) {
                *(f32 *)(npc + 0x58) = -10.0f;
            }
        } else if (npc[0xF0] == los) {
            npc[0xF0] = 0;
            factor5RemoveListNode(npc + 0x68);
        }
    } else {
        f32 m[12];
        AimV3 tgt2;
        AimV3 dir2;

other:
        buildRotationMatrixSlot0(m, *(f32 *)(npc + 0x58));
        composeRotationMatrixSlot1(m, *(f32 *)(npc + 0x54));
        transformVec3ByMat34(m, &D_mission_overlay_8010A884, &dir2);
        ang = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010A884, &dir2)) * 57.29578f;
        if (ang > 0.001f) {
            AimV3 axis;
            f32 q[4];
            AimV3 c;
            AimV3 a;
            AimV3 b;
            if (ang > 10.0f && npc[0xF0] == 0) {
                npc[0xF0] = 1;
                play3DSoundEventVariant(npc + 0x68, npc, npc + 0x24, 8.0f, 0.1f, 7, 0x4A, 1, 0x6E, 0x28);
            }
            lim = *(f32 *)(npc + 0xF4) * (dt * 30.0f);
            if (lim < ang) {
                ang = lim;
            }
            vec3Cross(&axis, &dir2, &D_mission_overlay_8010A884);
            normalize_vector(&axis);
            quatFromAxisAngle(q, &axis, ang);
            rotateVec3ByQuat(q, &dir2, &tgt2);
            axis.x = tgt2.x;
            axis.y = 0.0f;
            axis.z = tgt2.z;
            ang = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010A884, &axis) / (vec3Length(&D_mission_overlay_8010A884) * vec3Length(&axis))) * 57.29578f;
            a = D_mission_overlay_8010A884;
            a.y = 0.0f;
            b = axis;
            b.y = 0.0f;
            vec3Cross(&c, &a, &b);
            if (!(c.y >= 0.0f)) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(m, -ang);
            transformVec3ByMat34(m, &tgt2, &axis);
            axis.x = 0.0f;
            *(f32 *)(npc + 0x54) = ang;
            ang2 = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010A884, &axis) / (vec3Length(&D_mission_overlay_8010A884) * vec3Length(&axis))) * 57.29578f;
            if (!(axis.y <= 0.0f)) {
                ang2 = -ang2;
            }
            *(f32 *)(npc + 0x58) = ang2;
            return;
        }
        if (npc[0xF0] == 1) {
            npc[0xF0] = 0;
            factor5RemoveListNode(npc + 0x68);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D6BE0", npcTankDroidUpdate);

s32 npcTickEffectChannelShared(s32, s32, s32);

void npcTickEffectChannelSharedMode0(s32 arg0, s32 arg1) {
    npcTickEffectChannelShared(arg0, arg1, 0);
}

s32 npcTickEffectChannelShared(s32, s32, s32);

void npcTickEffectChannelSharedMode1(s32 arg0, s32 arg1) {
    npcTickEffectChannelShared(arg0, arg1, 1);
}
