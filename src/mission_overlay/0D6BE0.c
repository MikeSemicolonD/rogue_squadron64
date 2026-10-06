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

#define TD_ABSF(x) ({ f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(x)); _r; })

typedef struct {
    u8 pad0[0x4C];
    u32 flags;
    f32 f50, f54, f58;
    s32 w5C, w60, w64;
    u8 q68[0x10];
    f32 f78, f7C, f80;
} TdDef;

extern u8 D_main_bss_80139560[];
extern u16 D_main_bss_80139574;
extern u8 D_main_bss_80130B39;
extern u8 D_mission_overlay_8010A880[];
void npcInitSimpleModel(void *);
void *walkMeshdef0List(char *);
void composeEulerRotationXYZ(void *, s32, s32, s32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, f32);
void composeRotationMatrixSlot2(void *, f32);
void addVec3At0x24(void *, f32, f32, f32);
u16 popNpcSlotFromTail(u16, void *);
s32 lookupHmtMaterialByName(void *, char *, void *);
void createAndInitObject(void *, s32, void *, void *, s32);
s32 getLevelDatItemByName(char *);
void initActorAsType1(s32, s32, s32, f32, f32, f32, f32);
void updateObjectFlags110(s32, s32, s32);
s32 getNpcCurrentHealth(s32);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void releaseMeshAsset(void *);
void func_mission_overlay_800AA6D0(void *, f32, void *);
void dispatchEffectByActorType(s32, f32);
u8 func_mission_overlay_800EFDE0(s32, s32, s32, f32);
u8 validateActorTargetLOS(s32);
void applyToObjectSubstructByFlag(s32, f32, f32, s32);
u8 evaluateTargetTrackingVisibility(s32, f32, f32);
s16 rand(void);
void composeRandomRotationMatrix(void *, void *, f32, s32, s32, s32);
void scaleVec3ByRandomRange(void *, f32, f32);
void spawnDebris1Npc(void *, void *, f32, f32, f32);
void spawnDestructionEffectBurst(void *, u16, f32, f32, f32, f32);
void spawnSplineWalkerCraft(void *, f32, f32, s32);
void spawnNpcType0xAFromTemplate(void *, f32);
void spawnByteAnimDebrisDefault(void *);
void destroyNpcSlotByIndex(u16);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyObjectOwnedNpcSlot(s32);
void clearVec4QuadStruct(void *);
void applyScaleToMat3x4(void *, s32, s32, s32);
void composeQuatToMat3x4(void *, void *);
s32 updateActive3DAudioSource(void *, void *, void *, u8);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
void extrapolateNpcPositionForCurrentMode(void *);
s32 getObjectDetailLevel(s32);
void func_mission_overlay_800EFD6C(s32);
s32 dealDamageToNpc(s32, u16);
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
void clearPendingChildNpc(s32);
void setObjectFlagBit4(void *);
void setType1ActorParams(s32, s32, u8, u8, u8, s32);
void setObjectDetailLevel(s32, s32);
void dispatchSlotAction5IfActive(void *, void *);

static __inline__ void tdB0(f32 *m, f32 a) {
    buildRotationMatrixSlot0(m, a);
}

static __inline__ void tdC1(f32 *m, f32 a) {
    composeRotationMatrixSlot1(m, a);
}

static __inline__ void tdXf(f32 *m, void *a, void *b) {
    transformVec3ByMat34(m, a, b);
}

static __inline__ void tdAll(f32 *m, u8 *n, f32 *save) {
    buildRotationMatrixSlot0(m, *(f32 *)(n + 0x58));
    composeRotationMatrixSlot1(m, *(f32 *)(n + 0x54));
    transformVec3ByMat34(m, &save[3], n + 0xC);
    transformVec3ByMat34(m, &save[6], n + 0x18);
}

s32 npcTankDroidUpdate(u8 *arg0, u16 action, u8 *arg2) {
    u8 *n = *(u8 **)(arg0 + 4);
    union {
        struct {
            TickMtx save;
            f32 m[12];
        } a;
        struct {
            f32 p[4];
            f32 v[4];
        } b;
    } u;
    f32 dt;

    switch (action) {
    case 1:
        {
        u8 *rec = arg2;
        f32 kk;
        *(u8 **)(n + 0x34) = arg2;
        *(void **)(n + 0x30) = walkMeshdef0List("tankdroid");
        *(u8 **)(*(u8 **)(n + 0x30) + 4) = D_mission_overlay_8010A880;
        *(f32 *)(n + 0) = *(f32 *)(arg2 + 0x10);
        *(f32 *)(n + 4) = *(f32 *)(arg2 + 0x14);
        *(f32 *)(n + 8) = *(f32 *)(arg2 + 0x18);
        composeEulerRotationXYZ(n, *(s32 *)(arg2 + 0x1C), *(s32 *)(arg2 + 0x20), *(s32 *)(arg2 + 0x24));
        *(f32 *)(n + 0x24) = *(f32 *)(n + 0x28) = *(f32 *)(n + 0x2C) = 0.0f;
        kk = 1.0f / *(f32 *)(**(u8 ***)(n + 0x30) + 0x34);
        *(f32 *)(n + 0x50) = kk * *(f32 *)(arg2 + 0x28);
        initVec4TripletFromArgs(*(u8 **)(n + 0x30) + 0x28, kk * *(f32 *)(arg2 + 0x28), kk * *(f32 *)(arg2 + 0x2C), kk * *(f32 *)(arg2 + 0x30));
        composeRotationMatrixSlot0(*(u8 **)(n + 0x30) + 0x28, *(f32 *)(arg2 + 0x1C));
        composeRotationMatrixSlot1(*(u8 **)(n + 0x30) + 0x28, *(f32 *)(arg2 + 0x20));
        composeRotationMatrixSlot2(*(u8 **)(n + 0x30) + 0x28, *(f32 *)(arg2 + 0x24));
        addVec3At0x24(*(u8 **)(n + 0x30) + 0x28, *(f32 *)(n + 0), *(f32 *)(n + 4), *(f32 *)(n + 8));
        *(u8 **)(arg0 + 8) = n;
        *(void **)(arg0 + 0xC) = *(void **)(n + 0x30);
        {
            u8 *b = D_main_bss_80139560;
            s32 o;
            *(u16 *)(n + 0x60) = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
            o = 0x2C;
            if (*(s32 *)(arg2 + 0xA0) == 1) {
                o = 0x2E;
            }
            *(u16 *)(n + 0x62) = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            *(f32 *)(n + 0x5C) = (*(f32 *)(n + 0x50) / 0.075f) * -0.54f;
            *(s32 *)(n + 0x3C) = lookupHmtMaterialByName(*(void **)(n + 0x30), "toptrns", n + 0x44);
            *(s32 *)(n + 0x40) = lookupHmtMaterialByName(*(void **)(n + 0x30), "barreltr", n + 0x48);
            o = 0x12;
            if (*(s32 *)(arg2 + 0xA0) == 1) {
                o = 0xE;
            }
            *(u16 *)(n + 0x64) = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            if (*(s32 *)(arg2 + 0xA4) != 0) {
                o = 0x18;
                if (*(s32 *)(arg2 + 0xA0) == 1) {
                    o = 0x1A;
                }
                *(u16 *)(n + 0x66) = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            } else {
                *(u16 *)(n + 0x66) = 0xFFFF;
            }
        }
        *(f32 *)(n + 0x4C) = *(f32 *)(**(u8 ***)(n + 0x30) + 0x44) * *(f32 *)(n + 0x50);
        *(f32 *)(n + 0x54) = 0.0f;
        *(f32 *)(n + 0x58) = 0.0f;
        n[0xF2] = 0;
        n[0xF0] = 0;
        n[0xF1] = 0;
        createAndInitObject(n + 0x38, 0, arg0, npcInitSimpleModel, 0);
        {
            char *name = (char *)(*(s32 *)(rec + 0x8C) + (s32)rec);
            if (*name != '-') {
                s32 item = getLevelDatItemByName(name);
                initActorAsType1(*(s32 *)(n + 0x38), item, ((s32 *)(*(u8 **)(n + 0x34) + 0x90))[D_main_bss_80137CE4], 0.0f, 0.0f, 0.0f, 0.0f);
                updateObjectFlags110(*(s32 *)(n + 0x38), 7, 0);
                n[0xF1] = 1;
                play3DSoundEventVariant(n + 0xAC, n, n + 0x24, 12.0f, 0.5f, 0xF, 0x3B, 1, 0x78, 0);
            }
        }
        }
        return 1;
    case 2:
        if (n[0xF0] == 1) {
            n[0xF0] = 0;
            factor5RemoveListNode(n + 0x68);
        }
        if (n[0xF1] == 1) {
            n[0xF1] = 0;
            factor5RemoveListNode(n + 0xAC);
        }
        initActorRenderDescriptorIfUninit(*(s32 *)(n + 0x38), getNpcCurrentHealth(*(s32 *)(n + 0x38)) < 1, *(void **)(n + 0x34), 0, *(u8 **)(n + 0x34) + 0x70);
        clearPendingAndDestroyChildNpc(n + 0x38);
        releaseMeshAsset(*(void **)(n + 0x30));
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        {
        f32 inc = dt * 4.0f;
        if (*(f32 *)(n + 0xF8) < 1.0f) {
            *(f32 *)(n + 0xF8) += inc;
            if (*(f32 *)(n + 0xF8) > 1.0f) {
                *(f32 *)(n + 0xF8) = 1.0f;
                *(f32 *)(n + 0xFC) = 0.0f;
            } else if (*(f32 *)(n + 0xF8) < 0.2f) {
                *(f32 *)(n + 0xFC) = *(f32 *)(n + 0xF8) * 5.0f;
            } else {
                *(f32 *)(n + 0xFC) = 1.0f - (*(f32 *)(n + 0xF8) - 0.2f) * 1.25f;
            }
        }
        }
        switch (n[0xF3]) {
        case 0:
            n[0xF3] = 1;
        case 1:
            func_mission_overlay_800AA6D0(n, dt, *(u8 **)(n + 0x34) + 0x34);
            dispatchEffectByActorType(*(s32 *)(n + 0x38), dt);
            if (func_mission_overlay_800EFDE0(*(s32 *)(n + 0x38), *(s32 *)(*(u8 **)(n + 0x34) + 0xA8), *(s32 *)(*(u8 **)(n + 0x34) + 0xAC), dt) != 0) {
                n[0xF3] = 1;
            }
            npcTankDroidComputeAimMotion(n, dt);
            if (isPendingChildNpcActive(*(s32 *)(n + 0x38)) == 1) {
                u.a.save = *(TickMtx *)n;
                tdB0(u.a.m, *(f32 *)(n + 0x58));
                tdC1(u.a.m, *(f32 *)(n + 0x54));
                tdXf(u.a.m, &u.a.save.m[3], n + 0xC);
                tdXf(u.a.m, &u.a.save.m[6], n + 0x18);
                if (validateActorTargetLOS(*(s32 *)(n + 0x38)) == 1) {
                    applyToObjectSubstructByFlag(*(s32 *)(n + 0x38), dt, 0.0f, 0);
                }
                if (evaluateTargetTrackingVisibility(*(s32 *)(n + 0x38), 80.0f, ((f32 *)(*(u8 **)(n + 0x34) + 0xD4))[D_main_bss_80137CE4]) == 1) {
                    applyToObjectSubstructByFlag(*(s32 *)(n + 0x38), dt, 0.0f, 1);
                }
                *(TickMtx *)n = u.a.save;
            }
            break;
        case 2:
            {
            s32 i;
            s32 cnt;
            cnt = (s16)(rand() % 2) + 3;
            for (i = 0; i < cnt; i++) {
                f32 a, b;
                composeRandomRotationMatrix(u.b.p, u.b.v, *(f32 *)(n + 0x4C) * 0.5f, 0x5A, 0, 0);
                u.b.p[0] += *(f32 *)(n + 0);
                u.b.p[1] += *(f32 *)(n + 4);
                u.b.p[2] += *(f32 *)(n + 8);
                scaleVec3ByRandomRange(u.b.v, 3.0f, 4.0f);
                a = TD_ABSF(((f32)(rand() & 0x7F) - 64.0f) / 12.8f) + 27.0f;
                b = TD_ABSF(((f32)(rand() & 0x7F) - 64.0f) / 91.42857f) + 0.6f;
                spawnDebris1Npc(u.b.p, u.b.v, a, b, TD_ABSF(((f32)(rand() & 0x7F) - 64.0f) / 320.0f) + 0.2f);
            }
            spawnDestructionEffectBurst(n, 0xFFFF, 1.0f, 0.7f, 1.2f, 0.5f);
            spawnSplineWalkerCraft(n, *(f32 *)(n + 0x50) * 8.0f, *(f32 *)(n + 0x50) * 10.0f, 0xC);
            spawnNpcType0xAFromTemplate(n, *(f32 *)(n + 0x4C) * 5.0f);
            spawnByteAnimDebrisDefault(n);
            play3DSoundEvent(0, n, n + 0x24, 24.0f, 0.7f, 0, 0x21, 0x7D, 0x50);
            }
        destroy:
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        if (isNpcWithinActiveReferenceRange(n) == 0) {
            if (++*(s8 *)(n + 0xF2) >= 0x15) {
                goto destroy;
            }
        } else {
            n[0xF2] = 0;
        }
        destroyObjectOwnedNpcSlot(*(s32 *)(n + 0x38));
        return 1;
    case 4:
        {
        register u8 *d asm("$16");
        u8 *m;
        d = *(u8 **)(n + 0x44);
        m = *(u8 **)(n + 0x3C) + 0x1C;
        clearVec4QuadStruct(m);
        if (((TdDef *)d)->flags & 1) {
            addVec3At0x24(m, -((TdDef *)d)->f50, -((TdDef *)d)->f54, -((TdDef *)d)->f58);
        }
        if (((TdDef *)d)->flags & 2) {
            applyScaleToMat3x4(m, ((TdDef *)d)->w5C, ((TdDef *)d)->w60, ((TdDef *)d)->w64);
        }
        if (((TdDef *)d)->flags & 4) {
            composeQuatToMat3x4(m, ((TdDef *)d)->q68);
        }
        composeRotationMatrixSlot1(m, *(f32 *)(n + 0x54));
        {
        u32 fl = ((TdDef *)d)->flags;
        if ((fl & 9) == 9) {
            addVec3At0x24(m, ((TdDef *)d)->f78 + ((TdDef *)d)->f50, ((TdDef *)d)->f7C + ((TdDef *)d)->f54, ((TdDef *)d)->f80 + ((TdDef *)d)->f58);
        } else if ((fl & 9) == 8) {
            addVec3At0x24(m, ((TdDef *)d)->f78, ((TdDef *)d)->f7C, ((TdDef *)d)->f80);
        } else if (fl & 1) {
            addVec3At0x24(m, ((TdDef *)d)->f50, ((TdDef *)d)->f54, ((TdDef *)d)->f58);
        }
        }
        d = *(u8 **)(n + 0x48);
        m = *(u8 **)(n + 0x40) + 0x1C;
        clearVec4QuadStruct(m);
        if (((TdDef *)d)->flags & 1) {
            addVec3At0x24(m, -((TdDef *)d)->f50, -((TdDef *)d)->f54, -((TdDef *)d)->f58);
        }
        if (((TdDef *)d)->flags & 2) {
            applyScaleToMat3x4(m, ((TdDef *)d)->w5C, ((TdDef *)d)->w60, ((TdDef *)d)->w64);
        }
        if (((TdDef *)d)->flags & 4) {
            composeQuatToMat3x4(m, ((TdDef *)d)->q68);
        }
        addVec3At0x24(m, 0.0f, 0.0f, -*(f32 *)(n + 0xFC) * 1.2f);
        composeRotationMatrixSlot0(m, *(f32 *)(n + 0x58));
        {
        u32 fl = ((TdDef *)d)->flags;
        if ((fl & 9) == 9) {
            addVec3At0x24(m, ((TdDef *)d)->f78 + ((TdDef *)d)->f50, ((TdDef *)d)->f7C + ((TdDef *)d)->f54, ((TdDef *)d)->f80 + ((TdDef *)d)->f58);
        } else if ((fl & 9) == 8) {
            addVec3At0x24(m, ((TdDef *)d)->f78, ((TdDef *)d)->f7C, ((TdDef *)d)->f80);
        } else if (fl & 1) {
            addVec3At0x24(m, ((TdDef *)d)->f50, ((TdDef *)d)->f54, ((TdDef *)d)->f58);
        }
        }
        if (n[0xF0] != 0) {
            updateActive3DAudioSource(n + 0x68, n, n + 0x24, 0x64);
        }
        mat34CrossRowsAndCopyPos(*(u8 **)(n + 0x30) + 0x28, n, *(f32 *)(n + 0x50));
        addNpcToVisibilityBucket(*(s32 *)arg2, *(void **)(n + 0x30), n, *(f32 *)(n + 0x4C));
        }
        return 1;
    case 5:
        {
        u8 *q = arg2;
        if (getNpcCurrentHealth(*(s32 *)(n + 0x38)) > 0) {
            extrapolateNpcPositionForCurrentMode(arg2);
            play3DSoundEvent(0, n, n + 0x24, 24.0f, 0.5f, 0, 0x2A, 0x7D, 0x50);
            if (getObjectDetailLevel(*(s32 *)(n + 0x38)) == 1 && D_main_bss_80130B39 == 0) {
                func_mission_overlay_800EFD6C(0x1F4);
            }
            if (dealDamageToNpc(*(s32 *)(n + 0x38), *(u16 *)(q + 6)) <= 0) {
                n[0xF3] = 2;
                unregisterAndFreeNpcSlot(*(u16 *)(n + 0x60), arg0);
                unregisterAndFreeNpcSlot(*(u16 *)(n + 0x62), arg0);
                unregisterAndFreeNpcSlot(*(u16 *)(n + 0x64), arg0);
                if (*(u16 *)(n + 0x66) != 0xFFFF) {
                    unregisterAndFreeNpcSlot(*(u16 *)(n + 0x66), arg0);
                }
                popNpcSlotFromTail(D_main_bss_80139574, arg0);
                {
                    u8 *r = *(u8 **)(n + 0x34);
                    datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(*(u8 **)(n + 0x34) + 0x84));
                }
                tallyMidDetailObject(arg0);
                clearPendingChildNpc(*(s32 *)(n + 0x38));
                setObjectFlagBit4(arg0);
                if (n[0xF0] == 1) {
                    n[0xF0] = 0;
                    factor5RemoveListNode(n + 0x68);
                }
                if (n[0xF1] == 1) {
                    n[0xF1] = 0;
                    factor5RemoveListNode(n + 0xAC);
                }
            }
        }
        if (*(u16 *)q != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)q);
        }
        return 1;
        }
    case 9:
        {
        u8 *a9 = arg2;
        switch (arg2[0x18]) {
        case 1:
            setType1ActorParams(*(s32 *)(n + 0x38), *(s32 *)arg2, arg2[9], arg2[0xA], arg2[8], *(s32 *)(arg2 + 4));
            return 1;
        case 2:
        case 3:
            break;
        case 8:
            if (getNpcCurrentHealth(*(s32 *)(n + 0x38)) > 0) {
                u8 *b;
                s32 o;
                unregisterAndFreeNpcSlot(*(u16 *)(n + 0x62), arg0);
                b = D_main_bss_80139560;
                o = 0x2C;
                if (*(s32 *)arg2 == 1) {
                    o = 0x2E;
                }
                *(u16 *)(n + 0x62) = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                unregisterAndFreeNpcSlot(*(u16 *)(n + 0x64), arg0);
                o = 0x12;
                if (*(s32 *)arg2 == 1) {
                    o = 0xE;
                }
                *(u16 *)(n + 0x64) = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                if (*(u16 *)(n + 0x66) != 0xFFFF) {
                    unregisterAndFreeNpcSlot(*(u16 *)(n + 0x66), arg0);
                    if (*(s32 *)(*(u8 **)(n + 0x34) + 0xA4) != 0) {
                        o = 0x18;
                        if (*(s32 *)arg2 == 1) {
                            o = 0x1A;
                        }
                        *(u16 *)(n + 0x66) = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    }
                }
                setObjectDetailLevel(*(s32 *)(n + 0x38), *(s32 *)a9);
            }
            return 1;
        }
        }
        break;
    case 7:
        dispatchSlotAction5IfActive(arg0, arg2);
        break;
    }
    return 1;
}

s32 npcTickEffectChannelShared(s32, s32, s32);

void npcTickEffectChannelSharedMode0(s32 arg0, s32 arg1) {
    npcTickEffectChannelShared(arg0, arg1, 0);
}

s32 npcTickEffectChannelShared(s32, s32, s32);

void npcTickEffectChannelSharedMode1(s32 arg0, s32 arg1) {
    npcTickEffectChannelShared(arg0, arg1, 1);
}
