#include "common.h"
#include "common_types.h"
#include "rs_math.h"

s32 setNpcHealth(s32, void *, void *);
void initActorMotionParams(s32, s32, s32, s32, f32);
void initObjectAnimSubstruct(s32, s32, s32, s32, f32, void *, s32, f32, f32, s32);
void setObjectDetailLevel(s32, s32);
s32 spawnObjectImpactEffectWithSound(u8 *arg0, s32 arg1);
extern s32 D_main_bss_80137CE4;

void func_mission_overlay_800E9AE0(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 4);
    u8 *d;
    s32 o;
    s32 p;
    f32 one;

    if (setNpcHealth(*(s32 *)(s1 + 0x38), *(u8 **)(s1 + 0x34) + 0x6C, *(u8 **)(s1 + 0x34)) > 0) {
        one = 1.0f;
        o = D_main_bss_80137CE4 * 4;
        *(s16 *)(s1 + 0x6C) = 0;
        *(s32 *)(s1 + 0x60) = 0;
        *(s16 *)(s1 + 0x6E) = 0;
        *(f32 *)(s1 + 0x5C) = one;
        *(f32 *)(s1 + 0x58) = *(f32 *)(o + *(s32 *)(s1 + 0x34) + 0xBC) * 10.0f;
        p = o + *(s32 *)(s1 + 0x34);
        d = *(u8 **)(s1 + 0x34);
        initActorMotionParams(*(s32 *)(s1 + 0x38), *(s32 *)(p + 0xB4), *(s32 *)(p + 0xB8), *(s32 *)(p + 0xC0), *(f32 *)(p + 0xC4));
        initObjectAnimSubstruct(*(s32 *)(s1 + 0x38), *(s32 *)(d + 0xC8), *(s32 *)(d + 0xCC), *(s32 *)(d + 0xD0), *(f32 *)(d + 0xD4), spawnObjectImpactEffectWithSound, 0, 10.0f, 15.0f, 0);
        __asm__("" :: "r"(d)); __asm__("" :: "r"(d)); 
        setObjectDetailLevel(*(s32 *)(s1 + 0x38), *(s32 *)(*(u8 **)(s1 + 0x34) + 0xA0));
    } else {
        __asm__("" :: "r"(d));
        *(s16 *)(s1 + 0x6C) = 3;
    }
}


extern f32 D_mission_overlay_8010B184[];
extern u8 D_mission_overlay_8010B198[];
extern f32 D_mission_overlay_8010B19C[];
extern u8 D_mission_overlay_8010B1AC[];
extern f32 D_mission_overlay_8010B1B0[];
extern u8 D_mission_overlay_8010B1B8[];
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

void playStateGatedDestroySound(u8 *o, f32 dt, u8 arg2) {
    f32 *tbl;
    u8 *flags;
    f32 t;
    u16 idx;

    switch (*(s16 *)(o + 0x84)) {
    case 0:
        tbl = D_mission_overlay_8010B184;
        flags = D_mission_overlay_8010B198;
        break;
    case 1:
        tbl = D_mission_overlay_8010B19C;
        flags = D_mission_overlay_8010B1AC;
        break;
    case 2:
        tbl = D_mission_overlay_8010B1B0;
        flags = D_mission_overlay_8010B1B8;
        break;
    default:
        return;
    }
    t = *(f32 *)(o + 0x70) + dt / *(f32 *)(o + 0xA0);
    *(f32 *)(o + 0x70) = t;
    if (t > 1.0f) {
        *(u16 *)(o + 0x78) = 0;
        *(f32 *)(o + 0x70) = *(f32 *)(o + 0x9C);
        *(f32 *)(o + 0x74) = tbl[0];
        return;
    }
    if (arg2 == 0 && *(f32 *)(o + 0x74) <= t) {
        idx = *(u16 *)(o + 0x78);
        *(u16 *)(o + 0x78) = idx + 1;
        if (flags[(s16)idx] == 0) {
            play3DSoundEvent(0, o, o + 0x24, 12.0f, 0.3f, 0, 0x62, 0x78, 0x28);
        } else {
            play3DSoundEvent(0, o, o + 0x24, 12.0f, 0.3f, 0, 0x63, 0x78, 0x28);
        }
        *(f32 *)(o + 0x74) = tbl[*(s16 *)(o + 0x78)];
    }
}

s16 getObjectNpcTypeId(s32);
s32 lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
s32 setObjectSubstructF10IfReady(s32, f32, s32);
s32 slotDispatcherIter(s32, s32, void *);
s32 tickProgressChannel(s32, void *, s32, s32);
s32 triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);
extern s32 D_main_bss_80137CE4;
extern u8 D_mission_overlay_8010B178[];

s32 spawnObjectImpactEffectWithSound(u8 *arg0, s32 arg1) {
    u8 sp28[0x30];
    struct {
        s16 a;
        s16 b;
        s32 pad4[2];
        f32 c;
        f32 d;
        s32 pad[2];
    } sp58;
    s32 temp_s0;
    u8 *temp_s1;

    temp_s1 = *(u8 **)(arg0 + 4);
    lookupHmtTextureByName(*(s32 *)(temp_s1 + 0x30), "a_b", arg1, sp28, 0, 0);
    if (arg1 == 0) {
        setObjectSubstructF10IfReady(*(s32 *)(temp_s1 + 0x38), 0.06666667f, 0);
        *(s32 *)(temp_s1 + 0x5C) = 0;
    }
    temp_s0 = tickProgressChannel(*(s32 *)(temp_s1 + 0x38), sp28, 0, 0) & 0xFF;
    if (temp_s0 == 1) {
        sp58.a = 0;
        sp58.b = getObjectNpcTypeId(*(s32 *)(temp_s1 + 0x38));
        sp58.c = 5.0f;
        sp58.d = *(f32 *)(*(u8 **)(temp_s1 + 0x34) + D_main_bss_80137CE4 * 4 + 0xD8);
        slotDispatcherIter(triggerCueWithSlotEffect(*(s32 *)(temp_s1 + 0x38), 4, sp28, D_mission_overlay_8010B178, temp_s0, 10.0f, -1.0f) & 0xFFFF, 0xA, &sp58);
        play3DSoundEvent(0, temp_s1, temp_s1 + 0x24, 20.0f, 0.4f, 0, 0xD, 0x78, 0x28);
    }
    return 0;
}

typedef struct { s32 x, y, z; } CoV3i;
typedef struct {
    u8 pad0[0x38];
    s32 obj;
    u8 pad3C[0x18];
    f32 f54;
    f32 f58;
    u8 pad5C[8];
    f32 f64;
    f32 f68;
} CoNpc;
extern f32 D_mission_overlay_8010B16C[];
u8 isPendingChildNpcActive(s32);
u8 computeActorAnchorDeltaAfterLOS(s32);
void *getObjectMeshTransformOrLocal(s32, void *);
void computeAnchorRelativePositionByDistanceRatio(void *, void *, f32, void *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void mat3x3InverseInto(void *, void *);
void transformVec3ByMat34(void *, void *, void *);
f32 vec3NormalizeInto(void *, void *);
void buildRotationMatrixSlot0(void *, f32);
void buildRotationMatrixSlot1(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
f32 vec3Dot(void *, void *);
f32 vec3Length(void *);
f32 constMinusSinfApprox(f32);
void vec3Cross(void *, void *, void *);
f32 normalize_vector(void *);
void quatFromAxisAngle(void *, void *, f32);
void rotateVec3ByQuat(void *, void *, void *);

void computeNpcOrientationFromAimVectors(void *arg0, f32 dt) {
    register CoNpc *npc asm("$19") = arg0;
    f32 mtx[12];
    f32 inv[12];
    f32 dir[3];
    f32 v80[3];
    f32 v90[3];
    f32 meshbuf[12];
    f32 deg;
    register f32 ang asm("$f20");
    f32 lim;
    f32 a;
    f32 b;

    if (isPendingChildNpcActive(npc->obj) == 1 && computeActorAnchorDeltaAfterLOS(npc->obj) == 1) {
        f32 axis[4];
        f32 q[4];
        f32 cr[4];
        f32 t1[4];
        f32 t2[4];

        computeAnchorRelativePositionByDistanceRatio(npc, getObjectMeshTransformOrLocal(npc->obj, meshbuf), 10.0f, v90);
        mat34CrossRowsAndCopyPos(mtx, npc, 1.0f);
        mat3x3InverseInto(inv, mtx);
        transformVec3ByMat34(inv, v90, v80);
        v80[0] += npc->f54 * -0.033912f;
        v80[1] += npc->f54 * 13.6147f;
        v80[2] += npc->f54 * -6.70809f;
        vec3NormalizeInto(dir, v80);
        buildRotationMatrixSlot0(mtx, npc->f68);
        composeRotationMatrixSlot1(mtx, npc->f64);
        transformVec3ByMat34(mtx, D_mission_overlay_8010B16C, v80);
        ang = constMinusSinfApprox(vec3Dot(v80, dir)) * 57.29578f;
        if (0.001f < ang) {
            lim = npc->f58 * dt;
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
            ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B16C, axis) / (vec3Length(D_mission_overlay_8010B16C) * vec3Length(axis))) * 57.29578f;
            *(CoV3i *)t1 = *(CoV3i *)D_mission_overlay_8010B16C;
            t1[1] = 0.0f;
            *(CoV3i *)t2 = *(CoV3i *)axis;
            t2[1] = 0.0f;
            vec3Cross(cr, t1, t2);
            if (!(0.0f <= cr[1])) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(mtx, -ang);
            transformVec3ByMat34(mtx, dir, axis);
            axis[0] = 0.0f;
            npc->f64 = ang;
            b = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B16C, axis) / (vec3Length(D_mission_overlay_8010B16C) * vec3Length(axis))) * 57.29578f;
            if (!(axis[1] <= 0.0f)) {
                b = -b;
            }
            npc->f68 = b;
            if (25.0f < npc->f64) {
                npc->f64 = 25.0f;
            } else if (npc->f64 < -25.0f) {
                npc->f64 = -25.0f;
            }
            if (25.0f < npc->f68) {
                npc->f68 = 25.0f;
            } else if (npc->f68 < -25.0f) {
                npc->f68 = -25.0f;
            }
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

        buildRotationMatrixSlot0(m, npc->f68);
        composeRotationMatrixSlot1(m, npc->f64);
        transformVec3ByMat34(m, D_mission_overlay_8010B16C, v);
        ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B16C, v)) * 57.29578f;
        if (0.001f < ang) {
            { register f32 t asm("$f0") = dt * 30.0f; register f32 l2 asm("$f2") = npc->f58 * t; lim = l2; }
            if (lim < ang) {
                ang = lim;
            }
            vec3Cross(axis, v, D_mission_overlay_8010B16C);
            normalize_vector(axis);
            quatFromAxisAngle(q, axis, ang);
            rotateVec3ByQuat(q, v, r);
            axis[1] = 0.0f;
            axis[0] = r[0];
            axis[2] = r[2];
            ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B16C, axis) / (vec3Length(D_mission_overlay_8010B16C) * vec3Length(axis))) * 57.29578f;
            *(CoV3i *)t1 = *(CoV3i *)D_mission_overlay_8010B16C;
            t1[1] = 0.0f;
            *(CoV3i *)t2 = *(CoV3i *)axis;
            t2[1] = 0.0f;
            vec3Cross(cr, t1, t2);
            if (!(0.0f <= cr[1])) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(m, -ang);
            transformVec3ByMat34(m, r, axis);
            axis[0] = 0.0f;
            npc->f64 = ang;
            b = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B16C, axis) / (vec3Length(D_mission_overlay_8010B16C) * vec3Length(axis))) * 57.29578f;
            if (!(axis[1] <= 0.0f)) {
                b = -b;
            }
            npc->f68 = b;
        }
    }
}

#include "common_types.h"
extern void clearModelAnimChannelEntry(s32);
extern void releaseModelAnimSlot(s32);
extern s32 flattenAnimTreeAndAllocateSlot(s32, s32);
extern s32 markModelAnimChannelEntryActive(s32, s32);
extern void setModelAnimSlotCycleDuration(s32, f32);
extern void playStateGatedDestroySound(u8 *, f32, u8);

typedef struct {
    u8 pad0[0x30];
    s32 *p30;
    u8 pad34[0x20];
    f32 f54;
    u8 pad58[0x2C];
    s16 s84;
    u8 pad86[2];
    s32 a88[2];
    u8 pad90[4];
    s32 i94;
    s32 i98;
    s32 i9C;
    f32 fA0;
    f32 fA4;
    u8 padA8[0xB];
    u8 bB3;
} AnimObj;

void func_mission_overlay_800EA470(AnimObj *arg0) {
    f32 t;
    clearModelAnimChannelEntry(arg0->i98);
    releaseModelAnimSlot(arg0->i94);
    switch (arg0->bB3) {
    case 1:
        arg0->s84 = 2;
        arg0->fA0 = 1.0f / (arg0->fA0 * arg0->fA4);
        arg0->fA4 = 0.14400001f / arg0->f54;
        break;
    case 2:
        arg0->i9C = 0;
        arg0->s84 = 1;
        arg0->fA0 = 1.0f / (arg0->fA0 * arg0->fA4);
        arg0->fA4 = 0.074999996f / arg0->f54;
        break;
    case 3:
        arg0->s84 = 0;
        arg0->fA0 = 1.0f / (arg0->fA0 * arg0->fA4);
        arg0->fA4 = 0.06f / arg0->f54;
        break;
    default:
        return;
    }
    arg0->fA0 = 1.0f / (arg0->fA0 * arg0->fA4);
    arg0->i94 = flattenAnimTreeAndAllocateSlot(arg0->p30[6], arg0->a88[arg0->s84]);
    arg0->i98 = markModelAnimChannelEntryActive(arg0->i94, 0);
    setModelAnimSlotCycleDuration(arg0->i94, arg0->fA0);
    playStateGatedDestroySound((u8 *)arg0, 10.0f, 1);
    arg0->bB3 = 0;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8748);

typedef struct { f32 x, y, z; } PVec3;
typedef struct { f32 m[12]; } PMat;
typedef struct { u8 c[4]; } PCol;
typedef struct {
    PVec3 pos;
    PVec3 fwd;
    PVec3 up;
    PVec3 vel;
    u8 *mesh;
    u8 *rec;
    s32 obj;
    u8 *node0;
    u8 *node1;
    u8 *mat0;
    u8 *mat1;
    u8 *ctx;
    f32 radius;
    f32 scale;
    f32 f58;
    f32 f5C;
    f32 f60;
    f32 f64;
    f32 f68;
    s16 mode;
    s16 pad6E;
    f32 f70;
    f32 f74;
    u16 s78;
    u16 slot7A;
    u16 slot7C;
    u16 pad7E;
    u16 slot80;
    u16 slot82;
    s16 animIdx;
    s16 pad86;
    s32 anim[3];
    s32 animSlot;
    s32 chan;
    f32 phase;
    f32 dur;
    f32 rate;
    f32 fA8;
    s32 iAC;
    u8 bB0;
    u8 bB1;
    u8 bB2;
    u8 bB3;
    s32 outCount;
} AtPt;

extern u8 D_main_bss_80130B63;
extern f32 D_main_bss_80130BA4;
extern u8 *D_main_bss_80138D1C;
extern u8 D_main_bss_80138058[];
extern u16 D_main_bss_80139560[];
extern u16 D_main_bss_80139574;
extern s32 gCurrentLevel;
extern char D_mission_overlay_800A8748[];
extern u8 D_mission_overlay_8010B160[];
extern f32 D_mission_overlay_8010C0C0_f __asm__("D_mission_overlay_8010C0C0");
void func_mission_overlay_800E9AE0(u8 *);
void *walkMeshdef0List(char *);
void composeEulerRotationXYZ(void *, s32, s32, s32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, s32);
void composeRotationMatrixSlot1I(void *, s32) __asm__("composeRotationMatrixSlot1");
void composeRotationMatrixSlot2(void *, s32);
void composeRotationMatrixSlot0F(void *, f32) __asm__("composeRotationMatrixSlot0");
void composeRotationMatrixSlot1(void *, f32);
void addVec3At0x24(void *, f32, f32, f32);
u16 popNpcSlotFromTail(u16, void *);
s32 lookupHmtMaterialByName(void *, char *, void *);
void *allocateAndInitCraftNpcContext(f32, f32, s32);
void createAndInitObject(void *, s32, void *, void *, void *);
void *getLevelDatItemByName(char *);
void initActorAsType1(s32, void *, s32, s32, f32, f32, s32);
void updateObjectFlags110(s32, s32, s32);
s32 load_model_animation(char *);
s16 rand(void);
void seekAllModelAnimChannelsInSlotToTime(s32, f32);
void rs_free(void *);
void destroyNpcSlotByIndex(u16);
s32 getNpcCurrentHealth(s32);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void releaseMeshAsset(void *);
void func_mission_overlay_800AA6D0(void *, f32, void *);
void dispatchEffectByActorType(s32, f32);
void setType1ActorParams(s32, f32, u8, u8, u8, s32);
u8 func_mission_overlay_800EFDE0(s32, s32, s32, f32);
void computeNpcOrientationFromAimVectors(void *, f32);
u8 isPendingChildNpcActive(s32);
void buildRotationMatrixSlot0(void *, f32);
void transformVec3ByMat34(void *, void *, void *);
u8 validateActorTargetLOS(s32);
void applyToObjectSubstructByFlag(s32, f32, f32, s32);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyObjectOwnedNpcSlot(s32);
void transformMeshPartIntoWorld(void *, void *);
void spawnNpcType0xAFromTemplate(void *, f32);
void spawnByteAnimDebrisDefault(void *);
void spawnOrientedNpc(s32, void *, s32, void *, f32, f32, f32, f32);
void spawnDestructionEffectBurst(void *, s32, f32, f32, f32, f32);
void composeRandomRotationMatrix(void *, void *, f32, s32, s32, s32);
void scaleVec3ByRandomRange(void *, f32, f32);
void spawnDebris1Npc(void *, void *, f32, f32, f32);
void spawnSplineWalkerCraft(void *, f32, f32, s32);
s32 checkAndReturnByteFlagAsU8(s32, void *, void *, f32);
s32 sampleTerrainAtNpcPosition(void *, void *, void *, s32);
void parseModelAnimType2Entry(s32);
void clearVec4QuadStruct(void *);
void applyScaleToMat3x4(void *, f32, f32, f32);
void composeQuatToMat3x4(void *, void *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void addNpcToVisibilityBucket(s32, void *, void *, f32);
void enqueueMeshTypeForCleanup(void *);
void advanceNpcOnCurvedPath(s32, s32, void *, void *);
void extrapolateNpcPositionForCurrentMode(void *);
s32 dealDamageToNpc(s32, u16);
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
s32 clearPendingChildNpc(s32);
void setObjectFlagBit4(void *);
s32 getObjectDetailLevel(s32);
s32 getPlayerField2(s32);
void playSpeechClip(s32, s32, f32, s32);
void setObjectDetailLevel(s32, s32);
void dispatchSlotAction5IfActive(void *, void *);

static __inline__ void atPtRotate(AtPt *s1, f32 *r1, f32 *r2, PMat *b) {
    buildRotationMatrixSlot0(b, s1->f68);
    composeRotationMatrixSlot1(b, s1->f64);
    transformVec3ByMat34(b, r1, &s1->fwd);
    transformVec3ByMat34(b, r2, &s1->up);
}

static __inline__ s32 atPtCheckLOS(AtPt *s1, PMat *a, PMat *b) {
    s32 flag = 0;
    if ((u8)isPendingChildNpcActive(s1->obj) == 1) {
        *a = *(PMat *)s1;
        buildRotationMatrixSlot0(b, s1->f68);
        composeRotationMatrixSlot1(b, s1->f64);
        transformVec3ByMat34(b, &a->m[3], &s1->fwd);
        transformVec3ByMat34(b, &a->m[6], &s1->up);
        if (validateActorTargetLOS(s1->obj) == 1) {
            flag = 1;
        }
        *(PMat *)s1 = *a;
    }
    return flag;
}

static __inline__ void atPtSpawnPair(f32 k, f32 *v0, PCol *col) {
    register f32 *v asm("$16") = v0;
    f32 a = 1.0f;
    f32 b = 0.6f;
    spawnOrientedNpc(0x8002, v, 0, NULL, k * 0.75f, k * 1.2f, a, b);
    spawnOrientedNpc(0x8003, v, 0, col, k * b, k, a, b);
}

s32 npcAtPtUpdate(u8 *arg0, s32 action, u8 *arg2) {
    AtPt *s1 = *(AtPt **)(arg0 + 4);
    PMat sp28;
    PMat sp58;
    f32 dt;
    char *name;
    u8 *rec;
    u8 *msg;
    u8 *a4;
    u8 *a5;
    u8 *a9;
    s32 flag;
    s32 act;

    act = action;
    switch ((u16)action) {
    case 1:
    case 8:
        rec = arg2;
        msg = arg2;
        if (!(*(u16 *)(arg0 + 0x14) & 0x20)) {
            s1->rec = arg2;
            s1->pos.x = *(f32 *)(arg2 + 0x10);
            s1->pos.y = *(f32 *)(arg2 + 0x14);
            s1->pos.z = *(f32 *)(arg2 + 0x18);
            name = (char *)(*(s32 *)(arg2 + 0x8C) + (s32)arg2);
        } else {
            rec = *(u8 **)(arg2 + 0xC);
            s1->rec = rec;
            if (*(u8 *)(*(u8 **)(arg2 + 4) + 2) == 3) {
                s1->pos = **(PVec3 **)(arg2 + 8);
                name = *(char **)arg2;
            } else {
                name = D_mission_overlay_800A8748;
                s1->pos.x = 0.0f;
                s1->pos.y = 0.0f;
                s1->pos.z = 0.0f;
            }
        }
        {
            u8 *t;
            u8 *mesh;
            *(u8 **)((u8 *)s1 + 0x30) = walkMeshdef0List("atpt_imp");
            mesh = *(u8 **)((u8 *)s1 + 0x30);
            if (D_main_bss_80130B63 != 0) {
                t = D_mission_overlay_8010B160;
            } else {
                t = &D_mission_overlay_8010B160[8];
            }
            *(u8 **)(mesh + 4) = t;
        }
        composeEulerRotationXYZ(s1, *(s32 *)(rec + 0x1C), *(s32 *)(rec + 0x20), *(s32 *)(rec + 0x24));
        s1->vel.x = s1->vel.y = s1->vel.z = 0.0f;
        {
            f32 inv = 1.0f / *(f32 *)(*(u8 **)s1->mesh + 0x34);
            s1->scale = inv * *(f32 *)(rec + 0x28);
            initVec4TripletFromArgs(s1->mesh + 0x28, inv * *(f32 *)(rec + 0x28), inv * *(f32 *)(rec + 0x2C), inv * *(f32 *)(rec + 0x30));
        }
        composeRotationMatrixSlot0(s1->mesh + 0x28, *(s32 *)(rec + 0x1C));
        composeRotationMatrixSlot1I(s1->mesh + 0x28, *(s32 *)(rec + 0x20));
        composeRotationMatrixSlot2(s1->mesh + 0x28, *(s32 *)(rec + 0x24));
        addVec3At0x24(s1->mesh + 0x28, s1->pos.x, s1->pos.y, s1->pos.z);
        *(AtPt **)(arg0 + 8) = s1;
        *(u8 **)(arg0 + 0xC) = s1->mesh;
        {
            u8 *b = (u8 *)D_main_bss_80139560;
            s32 o;
            s1->slot7A = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
            o = 0x2C;
            if (*(s32 *)(rec + 0xA0) == 1) {
                o = 0x2E;
            }
            s1->slot7C = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            s1->node0 = (u8 *)lookupHmtMaterialByName(s1->mesh, "rohr_tra", &s1->mat0);
            s1->node1 = (u8 *)lookupHmtMaterialByName(s1->mesh, "barrel_t", &s1->mat1);
            o = 0x12;
            if (*(s32 *)(rec + 0xA0) == 1) {
                o = 0xE;
            }
            s1->slot80 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            if (*(s32 *)(rec + 0xA8) != 0) {
                o = 0x18;
                if (*(s32 *)(rec + 0xA0) == 1) {
                    o = 0x1A;
                }
                s1->slot82 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            } else {
                s1->slot82 = 0xFFFF;
            }
        }
        {
            f32 sc = s1->scale;
            s1->radius = *(f32 *)(*(u8 **)s1->mesh + 0x44) * sc;
            s1->f64 = 0.0f;
            s1->f68 = 0.0f;
            s1->outCount = 0;
            s1->ctx = allocateAndInitCraftNpcContext(sc * 6.0f, sc * 10.0f, 0xA);
        }
        *(f32 *)(s1->ctx + 0x14) = 1.0f;
        *(f32 *)(s1->ctx + 4) = s1->scale * 0.0f;
        *(f32 *)(s1->ctx + 0x10) = 0.0f;
        *(f32 *)(s1->ctx + 0x18) = 0.6f;
        createAndInitObject(&s1->obj, 0, arg0, func_mission_overlay_800E9AE0, (u16)act == 1 ? NULL : msg);
        if (*name != '-') {
            void *item = getLevelDatItemByName(name);
            u8 *r = s1->rec;
            initActorAsType1(s1->obj, item, *(s32 *)(r + 0x90), *(s32 *)(r + 0x9C), *(f32 *)(r + 0x94), *(f32 *)(s1->rec + 0x98), 0);
            updateObjectFlags110(s1->obj, 0x17, 0);
        }
        s1->animIdx = 0;
        s1->f70 = 0.0f;
        s1->rate = 0.06f / s1->scale;
        s1->f74 = D_mission_overlay_8010B184[0];
        s1->s78 = 0;
        s1->bB3 = 0;
        s1->anim[0] = load_model_animation("reb_stuff/atpt_walk");
        s1->anim[1] = load_model_animation("reb_stuff/atpt_start");
        s1->anim[2] = load_model_animation("reb_stuff/atpt_stop");
        s1->animSlot = flattenAnimTreeAndAllocateSlot(*(s32 *)(s1->mesh + 0x18), s1->anim[s1->animIdx]);
        s1->chan = markModelAnimChannelEntryActive(s1->animSlot, 0);
        s1->phase = FABSF_VAL(((f32)(rand() & 0x7F) - 64.0f) * 0.015625f);
        s1->dur = 1.0f / (*(f32 *)(s1->rec + 0x90) * s1->rate);
        setModelAnimSlotCycleDuration(s1->animSlot, s1->dur);
        seekAllModelAnimChannelsInSlotToTime(s1->animSlot, 0.0f);
        return 1;
    case 2:
        if (s1->anim[0] != 0) {
            s1->anim[0] = 0;
            clearModelAnimChannelEntry(s1->chan);
            releaseModelAnimSlot(s1->animSlot);
        }
        rs_free(s1->ctx);
        initActorRenderDescriptorIfUninit(s1->obj, getNpcCurrentHealth(s1->obj) < 1, s1->rec, 0, s1->rec + 0x70);
        clearPendingAndDestroyChildNpc(&s1->obj);
        releaseMeshAsset(s1->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        {
            f32 inc = dt * 4.0f;
            if (s1->f5C < 1.0f) {
                s1->f5C += inc;
                if (1.0f < s1->f5C) {
                    s1->f5C = 1.0f;
                    s1->f60 = 0.0f;
                } else if (s1->f5C < 0.2f) {
                    s1->f60 = s1->f5C * 5.0f;
                } else {
                    s1->f60 = 1.0f - (s1->f5C - 0.2f) * 1.25f;
                }
            }
        }
        switch (s1->mode) {
        case 0:
            s1->mode = 1;
        case 1:
            switch (s1->animIdx) {
            case 0:
                func_mission_overlay_800AA6D0(s1, dt, s1->rec + 0x34);
                dispatchEffectByActorType(s1->obj, dt);
                s1->phase += dt / s1->dur;
                if (s1->phase >= 1.0f) {
                    s1->phase -= 1.0f;
                    if (s1->bB3 != 0) {
                        func_mission_overlay_800EA470((AnimObj *)s1);
                    }
                }
                playStateGatedDestroySound((u8 *)s1, dt, 0);
                break;
            case 1:
                func_mission_overlay_800AA6D0(s1, dt, s1->rec + 0x34);
                dispatchEffectByActorType(s1->obj, dt);
                s1->phase += dt / s1->dur;
                if (s1->phase >= 1.0f) {
                    s1->phase -= 1.0f;
                    s1->bB3 = 3;
                    func_mission_overlay_800EA470((AnimObj *)s1);
                }
                playStateGatedDestroySound((u8 *)s1, dt, 0);
                break;
            case 2:
                if (s1->phase < 1.0f) {
                    s1->phase += dt / s1->dur;
                    if (s1->phase >= 1.0f) {
                        s1->phase = 1.0f;
                        setType1ActorParams(s1->obj, s1->fA8, s1->bB1, s1->bB2, s1->bB0, s1->iAC);
                    } else {
                        func_mission_overlay_800AA6D0(s1, dt, s1->rec + 0x34);
                        dispatchEffectByActorType(s1->obj, dt);
                        playStateGatedDestroySound((u8 *)s1, dt, 0);
                    }
                } else {
                    dispatchEffectByActorType(s1->obj, dt);
                    if (s1->bB3 != 0) {
                        func_mission_overlay_800EA470((AnimObj *)s1);
                    }
                }
                break;
            }
            seekAllModelAnimChannelsInSlotToTime(s1->animSlot, s1->phase * s1->dur);
            if (func_mission_overlay_800EFDE0(s1->obj, *(s32 *)(s1->rec + 0xAC), *(s32 *)(s1->rec + 0xB0), dt)) {
                s1->mode = 1;
            }
            computeNpcOrientationFromAimVectors(s1, dt);
            flag = 0;
            if ((u8)isPendingChildNpcActive(s1->obj) == 1) {
                sp28 = *(PMat *)s1;
                atPtRotate(s1, &sp28.m[3], &sp28.m[6], &sp58);
                if (validateActorTargetLOS(s1->obj) == 1) {
                    flag = 1;
                }
                *(PMat *)s1 = sp28;
            }
            if (flag == 1) {
                applyToObjectSubstructByFlag(s1->obj, dt, 0.0f, 0);
            }
            break;
        case 2:
            {
                f32 k;
                s32 i;
                s32 n;
                *(PCol *)&sp58 = (PCol){ { 0x9C, 0x52, 0x10, 0xFF } };
                k = s1->scale * 13.333f;
                transformMeshPartIntoWorld(s1->mesh, (((f32 *)&sp28) + 8));
                spawnNpcType0xAFromTemplate((((f32 *)&sp28) + 8), s1->radius * 3.0f);
                spawnByteAnimDebrisDefault(s1);
                play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.7f, 0, 0x21, 0x7D, 0x50);
                if (D_main_bss_80130B63 != 0) {
                spawn:
                    atPtSpawnPair(k, (((f32 *)&sp28) + 8), (PCol *)&sp58);
                } else {
                    switch (gCurrentLevel) {
                    case 3:
                    case 6:
                    case 9:
                    case 13:
                        break;
                    default:
                        goto spawn;
                    }
                }
                spawnDestructionEffectBurst(s1, 0xFFFF, 1.6f, k * 1.6f, 1.4f, 1.0f);
                n = (s16)(rand() % 3) + 4;
                for (i = 0; i < n; i++) {
                    f32 a;
                    f32 b;
                    composeRandomRotationMatrix(((f32 *)&sp28), (((f32 *)&sp28) + 4), s1->radius * 0.5f, 0x3C, 0, 0);
                    ((f32 *)&sp28)[0] += (((f32 *)&sp28) + 8)[0];
                    ((f32 *)&sp28)[1] += (((f32 *)&sp28) + 8)[1];
                    ((f32 *)&sp28)[2] += (((f32 *)&sp28) + 8)[2];
                    scaleVec3ByRandomRange((((f32 *)&sp28) + 4), 3.0f, 4.0f);
                    a = FABSF_VAL(((f32)(rand() & 0x7F) - 64.0f) / 12.8f) + 12.0f;
                    b = FABSF_VAL(((f32)(rand() & 0x7F) - 64.0f) * 0.0078125f) + 1.4f;
                    spawnDebris1Npc(((f32 *)&sp28), (((f32 *)&sp28) + 4), a, b, FABSF_VAL(((f32)(rand() & 0x7F) - 64.0f) / 320.0f) + 0.2f);
                }
                {
                    f32 sc = s1->scale;
                    spawnSplineWalkerCraft(s1, sc * 14.400001f, sc * 20.0f, 0xC);
                }
                s1->mode = 3;
            }
        destroy:
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        if (*(s32 *)(s1->rec + 0x88) == 0) {
            s1->outCount = 0;
        } else if (isNpcWithinActiveReferenceRange(s1) != 0) {
            s1->outCount = 0;
        } else {
            s1->outCount++;
            if (s1->outCount >= 0x15) {
                goto destroy;
            }
        }
        destroyObjectOwnedNpcSlot(s1->obj);
        return 1;
    case 4:
        a4 = arg2;
        if (checkAndReturnByteFlagAsU8(*(s32 *)arg2, s1->mesh, s1, s1->radius) != 0) {
            if (s1->mode != 3) {
                u8 *m;
                u8 *mp;
                {
                    f32 x = s1->pos.x - s1->fwd.x * s1->scale * 0.3f;
                    f32 y;
                    f32 z;
                    ((f32 *)&sp28)[0] = x;
                    y = s1->pos.y - s1->scale * 20.0f;
                    ((f32 *)&sp28)[1] = y;
                    z = s1->pos.z - s1->fwd.z * s1->scale * 0.3f;
                    m = D_main_bss_80138D1C + 0x28;
                    ((f32 *)&sp28)[2] = z;
                    (((f32 *)&sp28) + 4)[0] = *(f32 *)(m + 0x24);
                    (((f32 *)&sp28) + 4)[1] = *(f32 *)(m + 0x28);
                    (((f32 *)&sp28) + 4)[2] = *(f32 *)(m + 0x2C);
                    (((f32 *)&sp28) + 8)[0] = x - (((f32 *)&sp28) + 4)[0];
                    (((f32 *)&sp28) + 8)[1] = y - (((f32 *)&sp28) + 4)[1];
                    (((f32 *)&sp28) + 8)[2] = z - (((f32 *)&sp28) + 4)[2];
                    if (sampleTerrainAtNpcPosition((((f32 *)&sp28) + 4), (((f32 *)&sp28) + 8), D_main_bss_80138058, 0) == 0) {
                        parseModelAnimType2Entry(s1->animSlot);
                    }
                }
                mp = s1->mat0;
                m = s1->node0 + 0x1C;
                addVec3At0x24(m, -*(f32 *)(mp + 0x50), -*(f32 *)(mp + 0x54), -*(f32 *)(mp + 0x58));
                composeRotationMatrixSlot0F(m, s1->f68);
                composeRotationMatrixSlot1(m, s1->f64);
                addVec3At0x24(m, *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x58));
                mp = s1->mat1;
                m = s1->node1 + 0x1C;
                clearVec4QuadStruct(m);
                if (*(s32 *)(mp + 0x4C) & 1) {
                    addVec3At0x24(m, -*(f32 *)(mp + 0x50), -*(f32 *)(mp + 0x54), -*(f32 *)(mp + 0x58));
                }
                if (*(s32 *)(mp + 0x4C) & 2) {
                    applyScaleToMat3x4(m, *(f32 *)(mp + 0x5C), *(f32 *)(mp + 0x60), *(f32 *)(mp + 0x64));
                }
                if (*(s32 *)(mp + 0x4C) & 4) {
                    composeQuatToMat3x4(m, mp + 0x68);
                }
                addVec3At0x24(m, 0.0f, 0.0f, s1->f60 * -2.0f);
                if ((*(s32 *)(mp + 0x4C) & 9) == 9) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x78) + *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x7C) + *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x80) + *(f32 *)(mp + 0x58));
                } else if ((*(s32 *)(mp + 0x4C) & 9) == 8) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x78), *(f32 *)(mp + 0x7C), *(f32 *)(mp + 0x80));
                } else if (*(s32 *)(mp + 0x4C) & 1) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x58));
                }
            }
            mat34CrossRowsAndCopyPos(s1->mesh + 0x28, s1, s1->scale);
            addNpcToVisibilityBucket(*(s32 *)a4, s1->mesh, s1, s1->radius);
        } else {
            enqueueMeshTypeForCleanup(s1->mesh);
            mat34CrossRowsAndCopyPos(s1->mesh + 0x28, s1, s1->scale);
        }
        if (s1->ctx != NULL) {
            advanceNpcOnCurvedPath(*(s32 *)(a4 + 8), *(s32 *)a4, s1, s1->ctx);
            return 1;
        }
        return 1;
    case 5:
        a5 = arg2;
        if (getNpcCurrentHealth(s1->obj) > 0) {
            extrapolateNpcPositionForCurrentMode(arg2);
            play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.5f, 0, 0x2A, 0x7D, 0x50);
            if (dealDamageToNpc(s1->obj, *(u16 *)(arg2 + 6)) <= 0) {
                s1->mode = 2;
                unregisterAndFreeNpcSlot(s1->slot7A, arg0);
                unregisterAndFreeNpcSlot(s1->slot7C, arg0);
                unregisterAndFreeNpcSlot(s1->slot80, arg0);
                if (s1->slot82 != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s1->slot82, arg0);
                }
                popNpcSlotFromTail(D_main_bss_80139574, arg0);
                {
                    u8 *r = s1->rec;
                    datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s1->rec + 0x84));
                }
                tallyMidDetailObject(arg0);
                clearPendingChildNpc(s1->obj);
                setObjectFlagBit4(arg0);
            } else if (*(u16 *)(arg2 + 2) != 0xFFFF && getObjectDetailLevel(s1->obj) == 0 && *(u16 *)(arg2 + 2) == (u16)getPlayerField2(0) && D_mission_overlay_8010C0C0_f < D_main_bss_80130BA4) {
                D_mission_overlay_8010C0C0_f = D_main_bss_80130BA4 + 20.0f;
                playSpeechClip(gCurrentLevel == 0xB ? ((rand() & 1) ? 0x1F0 : 0x217) : 0x217, 0x73, 0.0f, 0);
            }
        }
        if (*(u16 *)a5 != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)a5);
            return 1;
        }
        return 1;
    case 9:
        a9 = arg2;
        switch (arg2[0x18]) {
        case 1:
            s1->bB1 = arg2[9];
            s1->bB2 = arg2[0xA];
            s1->bB0 = arg2[8];
            s1->iAC = *(s32 *)(arg2 + 4);
            s1->fA8 = *(f32 *)arg2;
            s1->bB3 = 1;
            break;
        case 2:
            s1->dur = 1.0f / (*(f32 *)arg2 * s1->rate);
            setModelAnimSlotCycleDuration(s1->animSlot, s1->dur);
            return 1;
        case 3:
            s1->bB3 = 2;
            break;
        case 8:
            if (getNpcCurrentHealth(s1->obj) > 0) {
                u8 *b;
                s32 o;
                unregisterAndFreeNpcSlot(s1->slot7C, arg0);
                b = (u8 *)D_main_bss_80139560;
                o = 0x2C;
                if (*(s32 *)arg2 == 1) {
                    o = 0x2E;
                }
                s1->slot7C = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                unregisterAndFreeNpcSlot(s1->slot80, arg0);
                o = 0x12;
                if (*(s32 *)arg2 == 1) {
                    o = 0xE;
                }
                s1->slot80 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                if (s1->slot82 != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s1->slot82, arg0);
                    if (*(s32 *)(s1->rec + 0xA8) != 0) {
                        o = 0x18;
                        if (*(s32 *)arg2 == 1) {
                            o = 0x1A;
                        }
                        s1->slot82 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    }
                }
                setObjectDetailLevel(s1->obj, *(s32 *)a9);
                return 1;
            }
            return 1;
        default:
            return 1;
        }
        break;
    case 7:
        dispatchSlotAction5IfActive(arg0, arg2);
        break;
    }
    return 1;
}


extern s32 D_mission_overlay_8010C0C0;

void resetObjectPoolListHead(void) {
    D_mission_overlay_8010C0C0 = 0;
}

static u32 D_mission_overlay_800A8888[] __attribute__((section(".rodata"))) = { 0xE4400000, 0x8FC20020 };
