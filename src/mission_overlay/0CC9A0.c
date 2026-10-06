#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", findNearestNpcWithinRange);

struct IaObj { u8 pad0[0x34]; u8 *f34; s32 f38; u8 pad3C[0xAA]; u8 fE6; u8 padE7[0x10]; f32 fF8; };
typedef struct { u8 pad0[4]; struct IaObj *obj; } IaActor;
extern s32 D_main_bss_80137CE4;
s32 setNpcHealth(s32, u8 *, u8 *);
void setObjectDetailLevel(s32, s32);
void initActorMotionParams(s32, s32, s32, s32, f32);
void initObjectAnimSubstruct(s32, s32, s32, s32, f32, s32 (*)(), s32, f32, f32, s32);
void setEffectIntensity(s32, s32);
s32 tickActorTexturedSoundEffect();

void initActorFromSpawnTemplate(IaActor *arg0) {
    struct IaObj *o = arg0->obj;
    u8 *e = o->f34;
    s32 h;
    u8 *e2;
    u8 *t;
    s32 off;
    s8 st;

    h = setNpcHealth(o->f38, e + 0x6C, e);
    setObjectDetailLevel(o->f38, *(s32 *)(o->f34 + 0xA0));
    st = 4;
    if (h > 0) {
        e2 = o->f34;
        if (*(s32 *)(e2 + 0x4C) >= 0) {
            o->fE6 = 0;
            off = D_main_bss_80137CE4 * 4;
            o->fF8 = *(f32 *)((u8 *)(off + (s32)o->f34) + 0xB8) * 3.0f;
            t = (u8 *)(off + (s32)e2);
            initActorMotionParams(o->f38, *(s32 *)(t + 0xB0), *(s32 *)(t + 0xB4), *(s32 *)(t + 0xBC), *(f32 *)(t + 0xC0));
            initObjectAnimSubstruct(o->f38, *(s32 *)(e2 + 0xC4), *(s32 *)(e2 + 0xC8), *(s32 *)(e2 + 0xCC), *(f32 *)(e2 + 0xD0), tickActorTexturedSoundEffect, 0, 10.0f, 15.0f, 0);
            setEffectIntensity(o->f38, *(s32 *)(e2 + 0xD8));
            return;
        }
        st = 3;
    }
    o->fE6 = st;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CC9A0", D_mission_overlay_800A6D60);

typedef struct { s16 a; s16 b; u8 pad4[8]; f32 c; f32 d; u8 pad[0xC]; } SndArgs;
typedef struct { u8 pad0[4]; struct Obj *obj; } SndActor;
struct Obj { u8 pad0[0x24]; u8 pos[0xC]; s32 f30; s32 pad34; s32 f38; };
extern u8 D_mission_overlay_800A6D60[];
extern u8 D_mission_overlay_8010A624[];
s32 lookupHmtTextureByName(s32, u8 *, s32, u8 *, s32, s32);
s32 setObjectSubstructF10IfReady(s32, f32, s32);
s32 tickProgressChannel(s32, u8 *, s32, s32);
s16 getObjectNpcTypeId(s32);
s32 triggerCueWithSlotEffect(s32, s32, u8 *, u8 *, s32, f32, f32);
s32 slotDispatcherIter(s32, s32, SndArgs *);
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
s32 tickActorTexturedSoundEffect(u8 *arg0, s32 arg1) {
    u8 buf[0x30];
    SndArgs args;
    struct Obj *o = ((SndActor *)arg0)->obj;
    s32 r;
    if (arg1 == 0) {
        lookupHmtTextureByName(o->f30, D_mission_overlay_800A6D60, 0, buf, 0, 0);
        setObjectSubstructF10IfReady(o->f38, 0.06666667f, 0);
    } else {
        lookupHmtTextureByName(o->f30, "b", 0, buf, 0, 0);
    }
    r = tickProgressChannel(o->f38, buf, 0, 0) & 0xFF;
    if (r == 1) {
        args.a = 0;
        args.b = getObjectNpcTypeId(o->f38);
        args.c = 5.0f;
        args.d = 10.0f;
        slotDispatcherIter(triggerCueWithSlotEffect(o->f38, 5, buf, D_mission_overlay_8010A624, r, 10.0f, -1.0f) & 0xFFFF, 0xA, &args);
        play3DSoundEvent(0, o, o->pos, 20.0f, 0.4f, 0, 0xD, 0x78, 0x28);
    }
    return 0;
}

typedef struct { s32 x, y, z; } AbV3i;
typedef struct {
    u8 pad0[0x38];
    s32 obj;
    u8 pad3C[0x18];
    f32 f54;
    f32 f58;
    f32 f5C;
    u8 pad60[0x33];
    u8 b93;
    u8 audio[0x64];
    f32 fF8;
} AbNpc;
extern f32 D_mission_overlay_8010A618[];
void factor5RemoveListNode(void *);
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
u8 isPendingU8(s32) __asm__("isPendingChildNpcActive");
u8 computeActorAnchorDeltaAfterLOS(s32);
void *getObjectMeshTransformOrLocal(s32, void *);
void computeAnchorRelativePositionByDistanceRatio(void *, void *, f32, void *);
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

void tickAtAtBodyTransform(void *arg0, f32 dt) {
    register AbNpc *npc asm("$20") = arg0;
    f32 mtx[12];
    f32 inv[12];
    f32 dir[3];
    f32 v80[3];
    f32 v90[3];
    f32 meshbuf[12];
    f32 deg;
    f32 ang;
    f32 lim;
    f32 a;
    f32 b;

    if (isPendingU8(npc->obj) == 1 && computeActorAnchorDeltaAfterLOS(npc->obj) == 1) {
        f32 axis[4];
        f32 q[4];
        f32 cr[4];
        f32 t1[4];
        f32 t2[4];

        computeAnchorRelativePositionByDistanceRatio(npc, getObjectMeshTransformOrLocal(npc->obj, meshbuf), 10.0f, v90);
        mat34CrossRowsAndCopyPos(mtx, npc, 1.0f);
        mat3x3InverseInto(inv, mtx);
        transformVec3ByMat34(inv, v90, v80);
        v80[0] += npc->f54 * -0.851765f;
        v80[1] += npc->f54 * 55.2586f;
        v80[2] += npc->f54 * -33.5938f;
        vec3NormalizeInto(dir, v80);
        buildRotationMatrixSlot0(mtx, npc->f5C);
        composeRotationMatrixSlot1(mtx, npc->f58);
        transformVec3ByMat34(mtx, D_mission_overlay_8010A618, v80);
        ang = constMinusSinfApprox(vec3Dot(v80, dir)) * 57.29578f;
        if (0.001f < ang) {
            if (5.0f < ang) {
                if (npc->b93 == 0) {
                    npc->b93 = 1;
                    play3DSoundEventVariant(npc->audio, npc, (u8 *)npc + 0x24, 9.0f, 0.1f, 7, 0x49, 1, 0x6E, 0x28);
                }
            } else if (npc->b93 == 1) {
                npc->b93 = 0;
                factor5RemoveListNode(npc->audio);
            }
            lim = npc->fF8 * dt;
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
            ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A618, axis) / (vec3Length(D_mission_overlay_8010A618) * vec3Length(axis))) * 57.29578f;
            *(AbV3i *)t1 = *(AbV3i *)D_mission_overlay_8010A618;
            t1[1] = 0.0f;
            *(AbV3i *)t2 = *(AbV3i *)axis;
            t2[1] = 0.0f;
            vec3Cross(cr, t1, t2);
            if (!(0.0f <= cr[1])) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(mtx, -ang);
            transformVec3ByMat34(mtx, dir, axis);
            axis[0] = 0.0f;
            npc->f58 = ang;
            b = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A618, axis) / (vec3Length(D_mission_overlay_8010A618) * vec3Length(axis))) * 57.29578f;
            if (!(axis[1] <= 0.0f)) {
                b = -b;
            }
            npc->f5C = b;
            if (22.0f < npc->f58) {
                npc->f58 = 22.0f;
            } else if (npc->f58 < -22.0f) {
                npc->f58 = -22.0f;
            }
            if (30.0f < npc->f5C) {
                npc->f5C = 30.0f;
            } else if (npc->f5C < -30.0f) {
                npc->f5C = -30.0f;
            }
        } else if (npc->b93 == 1) {
            npc->b93 = 0;
            factor5RemoveListNode(npc->audio);
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

        buildRotationMatrixSlot0(m, npc->f5C);
        composeRotationMatrixSlot1(m, npc->f58);
        transformVec3ByMat34(m, D_mission_overlay_8010A618, v);
        ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A618, v)) * 57.29578f;
        if (0.001f < ang) {
            if (5.0f < ang) {
                if (npc->b93 == 0) {
                    npc->b93 = 1;
                    play3DSoundEventVariant(npc->audio, npc, (u8 *)npc + 0x24, 9.0f, 0.1f, 7, 0x49, 1, 0x6E, 0x28);
                }
            } else if (npc->b93 == 1) {
                npc->b93 = 0;
                factor5RemoveListNode(npc->audio);
            }
            lim = npc->fF8 * dt;
            if (lim < ang) {
                ang = lim;
            }
            vec3Cross(axis, v, D_mission_overlay_8010A618);
            normalize_vector(axis);
            quatFromAxisAngle(q, axis, ang);
            rotateVec3ByQuat(q, v, r);
            axis[1] = 0.0f;
            axis[0] = r[0];
            axis[2] = r[2];
            ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A618, axis) / (vec3Length(D_mission_overlay_8010A618) * vec3Length(axis))) * 57.29578f;
            *(AbV3i *)t1 = *(AbV3i *)D_mission_overlay_8010A618;
            t1[1] = 0.0f;
            *(AbV3i *)t2 = *(AbV3i *)axis;
            t2[1] = 0.0f;
            vec3Cross(cr, t1, t2);
            if (!(0.0f <= cr[1])) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(m, -ang);
            transformVec3ByMat34(m, r, axis);
            axis[0] = 0.0f;
            npc->f58 = ang;
            b = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A618, axis) / (vec3Length(D_mission_overlay_8010A618) * vec3Length(axis))) * 57.29578f;
            if (!(axis[1] <= 0.0f)) {
                b = -b;
            }
            npc->f5C = b;
        } else if (npc->b93 == 1) {
            npc->b93 = 0;
            factor5RemoveListNode(npc->audio);
        }
    }
}

extern void clearModelAnimChannelEntry(s32);
extern void releaseModelAnimSlot(s32);
extern void initActorRenderDescriptorWithNpcVelocity(s32, s32);
extern s32 flattenAnimTreeAndAllocateSlot(s32, s32);
extern s32 markModelAnimChannelEntryActive(s32, s32);
extern void setModelAnimSlotCycleDuration(s32, f32);
extern f32 D_mission_overlay_8010A630;

void tickAtAtAudioAndWeaponState(u8 *arg0) {
    f32 t;
    f32 t2;

    clearModelAnimChannelEntry(*(s32 *)(arg0 + 0x7C));
    releaseModelAnimSlot(*(s32 *)(arg0 + 0x78));
    arg0[0x6F] = 1;
    t = *(f32 *)(arg0 + 0x84) * *(f32 *)(arg0 + 0x88);
    *(f32 *)(arg0 + 0x88) = 0.101220004f / *(f32 *)(arg0 + 0x54);
    *(f32 *)(arg0 + 0x84) = 1.0f / t;
    play3DSoundEvent(0, arg0, arg0 + 0x24, 24.0f, 0.8f, 0, 0x60, 0x7F, 0x7F);
    arg0[0x6D] = 0;
    initActorRenderDescriptorWithNpcVelocity(*(s32 *)(arg0 + 0x38), *(s32 *)(arg0 + 0x34));
    *(f32 *)(arg0 + 0x84) = 1.0f / (*(f32 *)(arg0 + 0x84) * *(f32 *)(arg0 + 0x88));
    *(s32 *)(arg0 + 0x78) = flattenAnimTreeAndAllocateSlot(*(s32 *)(*(u8 **)(arg0 + 0x30) + 0x18), *(s32 *)(arg0 + (arg0[0x6F] << 2) + 0x70));
    *(s32 *)(arg0 + 0x7C) = markModelAnimChannelEntryActive(*(s32 *)(arg0 + 0x78), 0);
    setModelAnimSlotCycleDuration(*(s32 *)(arg0 + 0x78), *(f32 *)(arg0 + 0x84));
    if (arg0[0x6F] == 0) {
        register f32 d asm("$f4") = *(f32 *)(arg0 + 0x84);
        register f32 c asm("$f0") = 10.0f;
        register f32 y asm("$f2") = *(f32 *)(arg0 + 0xF0);
        t2 = y + c / d;
        *(f32 *)(arg0 + 0xF0) = t2;
        if (t2 > 1.0f) {
            arg0[0xE7] = 0;
            *(f32 *)(arg0 + 0xF0) = *(f32 *)(arg0 + 0x80);
            *(f32 *)(arg0 + 0xF4) = D_mission_overlay_8010A630;
        }
    }
    arg0[0x90] = 0;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CC9A0", D_mission_overlay_800A6DCC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CC9A0", D_mission_overlay_800A6DD0);

s32 findActiveNpcInSlotChain(u16, void *);
u8 *getNpcContextField8(s32);
s32 revalidateNpcSlotIterator(void *);
extern u16 D_main_bss_80139582;

typedef struct { u8 pad[0x18]; u8 action; u8 pad19[7]; } AtAtSlotArgs;

void processAtAtSubFeatureSlot(u8 *arg0) {
    f32 buf[12];
    u8 iter[8];
    f32 d[3];
    u8 name[4];
    AtAtSlotArgs args;
    u8 *npc;
    u16 idx;
    s32 r;
    f32 dy;
    f32 dx;
    f32 dz;
    f32 rad;

    name[0] = 0x73;
    name[1] = 0x66;
    name[2] = arg0[0x6E] + 0x31;
    name[3] = 0;
    lookupHmtTextureByName(*(s32 *)(arg0 + 0x30), name, 0, (u8 *)buf, 0, 0);
    r = findActiveNpcInSlotChain(D_main_bss_80139582, iter);
    if ((r & 0xFFFF) != 0xFFFF) {
        do {
            idx = r;
            npc = getNpcContextField8(idx);
            dy = *(f32 *)(npc + 4) - buf[1];
            d[1] = dy;
            if (dy < 0.05f) {
                dx = *(f32 *)npc - buf[0];
                d[0] = dx;
                dz = *(f32 *)(npc + 8) - buf[2];
                d[2] = dz;
                rad = (*(f32 *)(arg0 + 0x54) / 0.042175f) * 0.3239f;
                if (dx * dx + dz * dz <= rad * rad) {
                    args.action = 9;
                    slotDispatcherIter(idx, 9, &args);
                }
            }
            r = revalidateNpcSlotIterator(iter);
        } while ((r & 0xFFFF) != 0xFFFF);
    }
    arg0[0x6E] = (arg0[0x6E] + 1) & 3;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CC9A0", D_mission_overlay_800A6DE0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", npcAtAtHandleDestruction);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", spawnAtAtFootstepDustBurst);

extern u8 D_mission_overlay_800A6DCC[];
extern u8 D_main_bss_80138058[];
extern void computeWalkerLimbStrideTargets(u16, f32 *, f32 *, f32 *, f32);
extern f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
extern void spawnAtAtFootstepDustBurst(f32 *);

void updateAtAtLegArticulation(struct Obj *arg0) {
    Vec3f sp18;
    Vec3f sp28;
    Vec3f sp38;
    Vec3f sp48;
    f32 sp58[12];
    s32 j;
    f32 s;

    lookupHmtTextureByName(arg0->f30, D_mission_overlay_800A6DCC, 0, (u8 *)sp58, 0, 0);
    computeWalkerLimbStrideTargets(*(u16 *)((u8 *)arg0->f38 + 0x198), sp18, sp28, sp38, 0.7f);
    sp18[0] = sp58[0] - sp28[0] * 0.5f - sp38[0] * 0.5f;
    sp18[1] = sp58[1] - sp28[1] * 0.5f - sp38[1] * 0.5f;
    sp18[2] = sp58[2] - sp28[2] * 0.5f - sp38[2] * 0.5f;
    j = 0;
    do {
        s = (f32)j;
        sp48[0] = sp18[0] + sp38[0] * 0.5f * s;
        sp48[2] = sp18[2] + sp38[2] * 0.5f * s;
        sp48[1] = wrapAngleToCyclicRange(sp48[0], sp48[2], D_main_bss_80138058, 0);
        spawnAtAtFootstepDustBurst(sp48);
        sp48[0] = sp18[0] + sp28[0] + sp38[0] * 0.5f * s;
        sp48[2] = sp18[2] + sp28[2] + sp38[2] * 0.5f * s;
        j++;
        sp48[1] = wrapAngleToCyclicRange(sp48[0], sp48[2], D_main_bss_80138058, 0);
        spawnAtAtFootstepDustBurst(sp48);
    } while (j < 3);
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CC9A0", D_mission_overlay_800A6ECC);

typedef struct { f32 x, y, z; } AtVec3;
typedef struct { s32 w[12]; } AtBlk;
typedef struct { u16 id; u16 pad2; s32 val; u8 pad8[0x10]; u8 type; } AtMsg;
typedef struct {
    AtVec3 pos;
    AtVec3 fwd;
    AtVec3 up;
    AtVec3 vel;
    u8 *mesh;
    u8 *rec;
    s32 obj;
    u8 *n3C;
    u8 *n40;
    u8 *m44;
    u8 *m48;
    u8 *ctx;
    f32 radius;
    f32 scale;
    f32 f58;
    f32 f5C;
    u16 slot60;
    u16 slot62;
    u16 pad64;
    u16 slot66;
    u16 slot68;
    u16 slot6A;
    u8 b6C;
    s8 step6D;
    u8 b6E;
    u8 b6F;
    s32 anim[2];
    s32 animSlot;
    s32 chan;
    f32 t80;
    f32 dur84;
    f32 rate88;
    f32 pad8C;
    u8 b90;
    u8 b91;
    u8 b92;
    u8 b93;
    u8 audio[0x44];
    s32 iD8;
    f32 fDC;
    u16 sE0;
    u16 sE2;
    s16 sE4;
    u8 state;
    s8 sE7;
    u16 sE8;
    u16 padEA;
    s32 iEC;
    f32 fF0;
    f32 fF4;
    f32 fF8;
    f32 fFC;
} AtObj;
extern u16 D_main_bss_80139560[];
extern u16 D_main_bss_80139580[];
extern f32 D_A630arr[] __asm__("D_mission_overlay_8010A630");
extern s32 D_main_bss_80138D1C;
extern s32 D_mission_overlay_8010A610[];
extern s32 D_mission_overlay_8010A614[];
extern u8 D_mission_overlay_8010A654[];
extern s32 D_mission_overlay_8010C9E0;
extern char D_mission_overlay_800A6ECC[];
extern u8 D_mission_overlay_800A6DD0[];
s16 rand(void);
u8 *walkMeshdef0List(char *);
void composeEulerRotationXYZ(void *, s32, s32, s32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
void composeRotationMatrixSlot2(void *, s32);
void composeRotationMatrixSlot0i(void *, s32) __asm__("composeRotationMatrixSlot0");
void composeRotationMatrixSlot1i(void *, s32) __asm__("composeRotationMatrixSlot1");
void addVec3At0x24(void *, f32, f32, f32);
u16 popNpcSlotFromTail(u16, void *);
u8 *lookupHmtMaterialByName(void *, char *, void *);
u16 spawnInheritedNpcVariantC(u16, void *, void *);
u8 *allocateAndInitCraftNpcContext(f32, f32, u16);
void createAndInitObject(void *, s32, void *, void *, void *);
s32 getLevelDatItemByName(char *);
void initActorAsType1(s32, s32, s32, s32, f32, f32, s32);
void updateObjectFlags110(s32, s32, s32);
s32 load_model_animation(char *);
void clearPendingChildNpc(s32);
void setObjectFlagBit4(void *);
void seekAllModelAnimChannelsInSlotToTime(s32, f32);
void spawnNpcWithRandomRotation(void *);
void spawnHeavyMechSubEffect(void *, void *, char *);
void factor5RemoveListNode(void *);
void rs_free(void *);
void destroyNpcSlotByIndex(u16);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void releaseMeshAsset(void *);
void func_mission_overlay_800AA6D0(void *, f32, void *);
void dispatchEffectByActorType(s32, f32);
s32 func_mission_overlay_800EFDE0(s32, s32, s32, f32);
void tickAtAtBodyTransform(void *, f32);
s32 isPendingChildNpcActive(s32);
s32 validateActorTargetLOS(s32);
void applyToObjectSubstructByFlag(s32, f32, s32, f32);
s32 getNpcCurrentHealth(s32);
s32 dealDamageToNpc(s32, s32);
void npcAtAtHandleDestruction(void *, s32);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
void unregisterAndFreeNpcSlot(u16, void *);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyObjectOwnedNpcSlot(s32);
s32 checkAndReturnByteFlagAsU8(s32, void *, void *, f32);
s32 sampleTerrainAtNpcPosition(void *, void *, void *, s32);
void parseModelAnimType2Entry(s32);
void buildRotationMatrixSlot1(void *, f32);
void zmemcpy(void *, void *, s32);
void mat3x4Multiply(void *, void *, void *);
void clearVec4QuadStruct(void *);
void applyScaleToMat3x4(void *, f32, f32, f32);
void composeQuatToMat3x4(void *, void *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
void enqueueMeshTypeForCleanup(void *);
void updateActive3DAudioSource(void *, void *, void *, s32);
void advanceNpcOnCurvedPath(s32, s32, void *, void *);
void extrapolateNpcPositionForCurrentMode(void *);
s32 rs_strcmp(char *, char *);
f32 getActorCurrentValueByType(s32);
void updateType1AnimRamp(s32, f32, f32, f32, s32);
void dispatchSlotAction5IfActive(void *, void *);
#define ATABSF(x) ({ f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(x)); _r; })

s32 npcAtAtUpdate(u8 *arg0, u16 action, u8 *arg2) {
    AtObj *s1 = *(AtObj **)(arg0 + 4);
    f32 sp[48];
    f32 dt;

    switch (action) {
    case 1:
    case 8:
        {
            register u8 *rec asm("$18");
            u8 *a1c = arg2;
            char *name;
            s32 hp;
            u16 fl;
            rec = arg2;
            __asm__("" : "+r"(rec));
            fl = *(u16 *)(arg0 + 0x14) | 0x100;
            *(u16 *)(arg0 + 0x14) = fl;
            if (!(fl & 0x20)) {
                s1->rec = arg2;
                s1->pos.x = *(f32 *)(arg2 + 0x10);
                s1->pos.y = *(f32 *)(arg2 + 0x14);
                s1->pos.z = *(f32 *)(arg2 + 0x18);
                name = (char *)(*(s32 *)(arg2 + 0x8C) + (s32)arg2);
            } else {
                rec = *(u8 **)(arg2 + 0xC);
                s1->rec = rec;
                if (*(u8 *)(*(u8 **)(arg2 + 4) + 2) == 3) {
                    s1->pos = **(AtVec3 **)(arg2 + 8);
                    name = *(char **)arg2;
                } else {
                    name = D_mission_overlay_800A6ECC;
                    s1->pos.x = 0.0f;
                    s1->pos.y = 0.0f;
                    s1->pos.z = 0.0f;
                }
            }
            hp = *(s32 *)(s1->rec + D_main_bss_80137CE4 * 4 + 0x6C);
            s1->mesh = walkMeshdef0List("atat");
            *(s32 **)(s1->mesh + 4) = D_mission_overlay_8010A610;
            composeEulerRotationXYZ(s1, *(s32 *)(rec + 0x1C), *(s32 *)(rec + 0x20), *(s32 *)(rec + 0x24));
            s1->vel.x = s1->vel.y = s1->vel.z = 0.0f;
            {
                f32 inv = 1.0f / *(f32 *)(*(u8 **)s1->mesh + 0x34);
                s1->scale = inv * *(f32 *)(rec + 0x28);
                initVec4TripletFromArgs(s1->mesh + 0x28, inv * *(f32 *)(rec + 0x28), inv * *(f32 *)(rec + 0x2C), inv * *(f32 *)(rec + 0x30));
            }
            composeRotationMatrixSlot0i(s1->mesh + 0x28, *(s32 *)(rec + 0x1C));
            composeRotationMatrixSlot1i(s1->mesh + 0x28, *(s32 *)(rec + 0x20));
            composeRotationMatrixSlot2(s1->mesh + 0x28, *(s32 *)(rec + 0x24));
            addVec3At0x24(s1->mesh + 0x28, s1->pos.x, s1->pos.y, s1->pos.z);
            *(AtObj **)(arg0 + 8) = s1;
            *(u8 **)(arg0 + 0xC) = s1->mesh;
            if (hp > 0) {
                u8 *b = (u8 *)D_main_bss_80139560;
                s32 o;
                s1->slot60 = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
                s1->n3C = lookupHmtMaterialByName(s1->mesh, "joint_4", &s1->m44);
                s1->n40 = lookupHmtMaterialByName(s1->mesh, "head", &s1->m48);
                {
                    s32 o1 = 0x12;
                    if (*(s32 *)(rec + 0xA0) == 1) {
                        o1 = 0xE;
                    }
                    s1->slot66 = popNpcSlotFromTail(*(u16 *)(o1 + b), arg0);
                }
                if (*(s32 *)(rec + 0xA4) != 0) {
                    s32 o2 = 0x18;
                    if (*(s32 *)(rec + 0xA0) == 1) {
                        o2 = 0x1A;
                    }
                    s1->slot68 = popNpcSlotFromTail(*(u16 *)(o2 + b), arg0);
                } else {
                    s1->slot68 = 0xFFFF;
                }
                if (!(*(s32 *)(s1->rec + 0x4C) & 0x40000000)) {
                    sp[2] = 0.0f;
                    sp[0] = 0.0f;
                    sp[1] = s1->scale * -20.0f;
                    s1->sE0 = spawnInheritedNpcVariantC(*(u16 *)(arg0 + 0x16), D_mission_overlay_800A6DCC, sp);
                    sp[1] = s1->scale * -5.0f;
                    s1->sE2 = spawnInheritedNpcVariantC(*(u16 *)(arg0 + 0x16), D_mission_overlay_800A6DD0, sp);
                } else {
                    s1->sE0 = 0xFFFF;
                    s1->sE2 = 0xFFFF;
                }
                if (!(*(s32 *)(s1->rec + 0x4C) & 0xC0000000)) {
                    u8 *b2 = (u8 *)D_main_bss_80139560;
                    o = 0x2C;
                    if (*(s32 *)(rec + 0xA0) == 1) {
                        o = 0x2E;
                    }
                    s1->slot62 = popNpcSlotFromTail(*(u16 *)(o + b2), arg0);
                } else {
                    s1->slot62 = 0xFFFF;
                }
            } else {
                u8 *b = (u8 *)D_main_bss_80139560;
                s1->slot60 = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
                popNpcSlotFromTail(D_main_bss_80139560[0x14 / 2], arg0);
                s1->n3C = lookupHmtMaterialByName(s1->mesh, "joint_4", &s1->m44);
                s1->n40 = lookupHmtMaterialByName(s1->mesh, "head", &s1->m48);
                s1->sE0 = 0xFFFF;
                s1->sE2 = 0xFFFF;
            }
            s1->radius = *(f32 *)(*(u8 **)s1->mesh + 0x44) * s1->scale;
            s1->f58 = 0.0f;
            s1->f5C = 0.0f;
            s1->b91 = 0;
            s1->b6C = 0;
            s1->b92 = 0;
            s1->b6E = 0;
            s1->sE4 = 0;
            s1->b93 = 0;
            s1->ctx = allocateAndInitCraftNpcContext(s1->scale * 12.0f, s1->scale * 32.0f, 0xB);
            *(f32 *)(s1->ctx + 0x14) = 7.0f;
            *(f32 *)(s1->ctx + 4) = s1->scale * 0.0f;
            *(f32 *)(s1->ctx + 0x10) = 0.0f;
            *(f32 *)(s1->ctx + 0x18) = 0.6f;
            createAndInitObject(&s1->obj, 0, arg0, initActorFromSpawnTemplate, (action != 1) ? a1c : NULL);
            s1->fFC = 0.0f;
            if (hp > 0) {
                s1->iD8 = 0;
                if (*(s32 *)(s1->rec + 0x4C) >= 0 && *name != '-') {
                    s32 item = getLevelDatItemByName(name);
                    u8 *r = s1->rec;
                    initActorAsType1(s1->obj, item, *(s32 *)(r + 0x90), *(s32 *)(r + 0x9C), *(f32 *)(r + 0x94), *(f32 *)(s1->rec + 0x98), 0);
                    updateObjectFlags110(s1->obj, 0x24, 0);
                }
            }
            s1->b90 = 0;
            s1->anim[0] = load_model_animation("imp_stuff/atat_walk");
            s1->anim[1] = load_model_animation("imp_stuff/atat_die");
            if (hp > 0 && *(s32 *)(s1->rec + 0x4C) >= 0) {
                s1->b6F = 0;
                s1->fF0 = 0.0f;
                s1->rate88 = 0.0379575f / s1->scale;
                s1->fF4 = D_A630arr[0];
                s1->sE7 = 0;
                s1->t80 = ATABSF(((f32)(rand() & 0x7F) - 64.0f) * 0.015625f);
                s1->slot6A = popNpcSlotFromTail(D_main_bss_80139580[0], arg0);
            } else {
                s1->b6F = 1;
                s1->rate88 = 0.101220004f / s1->scale;
                s1->fF0 = 2.0f;
                s1->fF4 = D_A630arr[0];
                s1->sE7 = 0;
                s1->t80 = 1.0f;
                *(u16 *)(s1->mesh + 8) |= 0x40;
                s1->b91 = 1;
                s1->slot6A = 0xFFFF;
                clearPendingChildNpc(s1->obj);
                setObjectFlagBit4(arg0);
            }
            s1->animSlot = flattenAnimTreeAndAllocateSlot(*(s32 *)(s1->mesh + 0x18), s1->anim[s1->b6F]);
            s1->chan = markModelAnimChannelEntryActive(s1->animSlot, 0);
            {
                f32 d = 1.0f / (*(f32 *)(s1->rec + 0x90) * s1->rate88);
                s1->dur84 = d;
                if (s1->state != 4 && !(*(s32 *)(s1->rec + 0x4C) & 0x40000000)) {
                    setModelAnimSlotCycleDuration(s1->animSlot, d);
                    seekAllModelAnimChannelsInSlotToTime(s1->animSlot, s1->t80);
                    return 1;
                }
            }
            setModelAnimSlotCycleDuration(s1->animSlot, 1.0f);
            seekAllModelAnimChannelsInSlotToTime(s1->animSlot, 1.0f);
            spawnNpcWithRandomRotation(&sp[4]);
            ((s32 *)sp)[10] = 0;
            spawnHeavyMechSubEffect(&sp[4], arg0, "joint_4");
            return 1;
        }
    case 2:
        if (s1->anim[0] != 0) {
            s1->anim[0] = 0;
            clearModelAnimChannelEntry(s1->chan);
            releaseModelAnimSlot(s1->animSlot);
        }
        if (s1->b93 == 1) {
            s1->b93 = 0;
            factor5RemoveListNode(s1->audio);
        }
        rs_free(s1->ctx);
        if (s1->sE0 != 0xFFFF) {
            destroyNpcSlotByIndex(s1->sE0);
            s1->sE0 = 0xFFFF;
        }
        if (s1->sE2 != 0xFFFF) {
            destroyNpcSlotByIndex(s1->sE2);
            s1->sE2 = 0xFFFF;
        }
        initActorRenderDescriptorIfUninit(s1->obj, s1->b92, s1->rec, 0, s1->rec + 0x70);
        clearPendingAndDestroyChildNpc(&s1->obj);
        releaseMeshAsset(s1->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        switch (s1->state) {
        case 0:
            s1->state = 1;
        case 1:
            if (s1->b6F == 0) {
                func_mission_overlay_800AA6D0(s1, dt, s1->rec + 0x34);
                dispatchEffectByActorType(s1->obj, dt);
                s1->t80 += dt / s1->dur84;
                if (s1->b6C == 1) {
                    s1->t80 = 1.0f;
                }
                if (s1->t80 >= 1.0f) {
                    s32 f = s1->b91;
                    s1->t80 -= 1.0f;
                    if (f == 1) {
                        if (s1->b6C != 0) {
                            ((AtMsg *)sp)->type = 0xE;
                            ((AtMsg *)sp)->id = *(u16 *)(arg0 + 0x16);
                            ((AtMsg *)sp)->val = s1->iEC;
                            slotDispatcherIter(s1->sE8, 9, (SndArgs *)sp);
                        }
                        s1->b90 = f;
                        s1->state = 2;
                        *(u16 *)(s1->mesh + 8) |= 0x40;
                    }
                    if (s1->b90 != 0) {
                        tickAtAtAudioAndWeaponState((u8 *)s1);
                    }
                }
                if (s1->b6F == 0) {
                    f32 *tbl = D_A630arr;
                    u8 *snd = D_mission_overlay_8010A654;
                    s1->fF0 += dt / s1->dur84;
                    if (s1->fF0 > 1.0f) {
                        s1->sE7 = 0;
                        s1->fF0 = s1->t80;
                        s1->fF4 = D_A630arr[0];
                    } else if (s1->fF4 <= s1->fF0) {
                        if (snd[s1->sE7++] == 0) {
                            play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.5f, 0, 8, 0x7F, 0x5A);
                        } else {
                            play3DSoundEvent(0, s1, &s1->vel, 15.0f, 0.6f, 0, 9, 0x78, 0x28);
                        }
                        s1->fF4 = tbl[s1->sE7];
                    }
                }
            }
            {
                s32 hit = 0;
                seekAllModelAnimChannelsInSlotToTime(s1->animSlot, s1->t80 * s1->dur84);
                func_mission_overlay_800EFDE0(s1->obj, *(s32 *)(s1->rec + 0xA8), *(s32 *)(s1->rec + 0xAC), dt);
                tickAtAtBodyTransform(s1, dt);
                if ((u8)isPendingChildNpcActive(s1->obj) == 1) {
                    *(AtBlk *)&sp[16] = *(AtBlk *)s1;
                    lookupHmtTextureByName((s32)s1->mesh, D_mission_overlay_800A6D60, 0, (u8 *)s1, 0, 0);
                    if ((u8)validateActorTargetLOS(s1->obj) == 1) {
                        hit = 1;
                    }
                    *(AtBlk *)s1 = *(AtBlk *)&sp[16];
                }
                if (hit == 1) {
                    applyToObjectSubstructByFlag(s1->obj, dt, 0, 0.0f);
                }
            }
            processAtAtSubFeatureSlot((u8 *)s1);
            break;
        case 2:
            s1->t80 += dt / s1->dur84;
            switch (s1->step6D) {
            case 0:
                if (s1->t80 > 0.42f) {
                    s1->step6D++;
                    play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.8f, 0, 0x61, 0x7F, 0x7F);
                }
                break;
            case 1:
                if (s1->t80 > 0.68f) {
                    s1->step6D++;
                    play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.8f, 0, 0x61, 0x7F, 0x7F);
                }
                break;
            case 2:
                if (s1->t80 > 0.75f) {
                    s1->step6D++;
                    updateAtAtLegArticulation((struct Obj *)s1);
                }
            case 3:
                if (s1->t80 > 0.92f) {
                    s1->step6D++;
                    play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.6f, 0, 0x77, 0x7D, 0x7D);
                }
                break;
            }
            if (s1->t80 > 1.0f) {
                s32 hp;
                f32 f;
                if (s1->b6C != 0) {
                    D_mission_overlay_8010C9E0 |= 0x80;
                }
                s1->t80 = 1.0f;
                s1->state = 3;
                hp = getNpcCurrentHealth(s1->obj);
                f = *(f32 *)(s1->rec + 0xDC);
                if (f > 0.0f && f < 1.0f) {
                    dealDamageToNpc(s1->obj, (s32)((f32)hp * f));
                } else if (*(f32 *)(s1->rec + 0xDC) == 0.0f) {
                    dealDamageToNpc(s1->obj, hp + 0xA);
                    npcAtAtHandleDestruction(s1, 0);
                    s1->state = 5;
                    D_mission_overlay_8010C9E0 &= ~0x80;
                    s1->fF8 = 1.0f;
                    s1->b92 = 1;
                    return 1;
                } else {
                    s32 d = (s32)*(f32 *)(s1->rec + 0xDC);
                    if (d < hp) {
                        dealDamageToNpc(s1->obj, hp - d);
                    }
                }
                {
                    u8 *r = s1->rec;
                    datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s1->rec + 0x84));
                }
                tallyMidDetailObject(arg0);
                unregisterAndFreeNpcSlot(s1->slot62, arg0);
            }
            seekAllModelAnimChannelsInSlotToTime(s1->animSlot, s1->t80 * s1->dur84);
            func_mission_overlay_800EFDE0(s1->obj, 6, 6, dt);
            tickAtAtBodyTransform(s1, dt);
            break;
        case 3:
            setModelAnimSlotCycleDuration(s1->animSlot, 1.0f);
            seekAllModelAnimChannelsInSlotToTime(s1->animSlot, 1.0f);
            if (getNpcCurrentHealth(s1->obj) <= 0) {
                npcAtAtHandleDestruction(s1, 0);
                goto destroy;
            }
            break;
        case 5:
            s1->fF8 -= dt;
            if (s1->fF8 <= 0.0f) {
                D_mission_overlay_8010C9E0 |= 0x80;
                s1->b92 = 1;
            destroy:
                destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                return 1;
            }
            return 1;
        }
        if (s1->fFC != 0.0f) {
            s1->fFC -= dt;
            if (s1->fFC <= 0.0f) {
                s1->fFC = 0.0f;
                *(s32 **)(s1->mesh + 4) = D_mission_overlay_8010A610;
            }
        }
        if (*(s32 *)(s1->rec + 0x88) == 0) {
            s1->sE4 = 0;
        } else if (isNpcWithinActiveReferenceRange(s1) != 0) {
            s1->sE4 = 0;
        } else {
            s1->sE4++;
            if (s1->sE4 >= 0x15) {
                goto destroy;
            }
        }
        destroyObjectOwnedNpcSlot(s1->obj);
        return 1;
    case 4:
        {
            u8 *a4 = arg2;
            if (s1->state == 5) {
                return 1;
            }
            if (checkAndReturnByteFlagAsU8(*(s32 *)arg2, s1->mesh, s1, s1->radius) != 0) {
                if (s1->state != 4) {
                    u8 *cam;
                    u8 *m;
                    sp[24] = s1->pos.x;
                    sp[25] = s1->pos.y - s1->scale * 80.0f;
                    sp[26] = s1->pos.z;
                    cam = (u8 *)D_main_bss_80138D1C + 0x28;
                    sp[28] = *(f32 *)(cam + 0x24);
                    sp[29] = *(f32 *)(cam + 0x28);
                    sp[30] = *(f32 *)(cam + 0x2C);
                    sp[32] = sp[24] - sp[28];
                    sp[33] = sp[25] - sp[29];
                    sp[34] = sp[26] - sp[30];
                    if (sampleTerrainAtNpcPosition(&sp[28], &sp[32], D_main_bss_80138058, 0) == 0) {
                        parseModelAnimType2Entry(s1->animSlot);
                    }
                    {
                        u8 *n;
                        m = s1->m44;
                        n = cam = s1->n3C + 0x1C;
                        addVec3At0x24(n, -*(f32 *)(m + 0x50), -*(f32 *)(m + 0x54), -*(f32 *)(m + 0x58));
                        composeRotationMatrixSlot0(n, s1->f5C * 0.5f);
                        addVec3At0x24(n, *(f32 *)(m + 0x50), *(f32 *)(m + 0x54), *(f32 *)(m + 0x58));
                        buildRotationMatrixSlot1(sp, s1->f58 * 0.25f);
                        zmemcpy(&sp[12], n, 0x30);
                        mat3x4Multiply(&sp[12], sp, n);
                    }
                    {
                        u8 *m = s1->m48;
                        u8 *n = s1->n40 + 0x1C;
                        s32 fl;
                        clearVec4QuadStruct(n);
                        if (*(s32 *)(m + 0x4C) & 1) {
                            addVec3At0x24(n, -*(f32 *)(m + 0x50), -*(f32 *)(m + 0x54), -*(f32 *)(m + 0x58));
                        }
                        if (*(s32 *)(m + 0x4C) & 2) {
                            applyScaleToMat3x4(n, *(f32 *)(m + 0x5C), *(f32 *)(m + 0x60), *(f32 *)(m + 0x64));
                        }
                        if (*(s32 *)(m + 0x4C) & 4) {
                            composeQuatToMat3x4(n, m + 0x68);
                        }
                        composeRotationMatrixSlot0(n, s1->f5C * 0.5f);
                        composeRotationMatrixSlot1(n, s1->f58);
                        fl = *(s32 *)(m + 0x4C);
                        if ((fl & 9) == 9) {
                            addVec3At0x24(n, *(f32 *)(m + 0x78) + *(f32 *)(m + 0x50), *(f32 *)(m + 0x7C) + *(f32 *)(m + 0x54), *(f32 *)(m + 0x80) + *(f32 *)(m + 0x58));
                        } else if ((fl & 9) == 8) {
                            addVec3At0x24(n, *(f32 *)(m + 0x78), *(f32 *)(m + 0x7C), *(f32 *)(m + 0x80));
                        } else if (fl & 1) {
                            addVec3At0x24(n, *(f32 *)(m + 0x50), *(f32 *)(m + 0x54), *(f32 *)(m + 0x58));
                        }
                    }
                }
                mat34CrossRowsAndCopyPos(s1->mesh + 0x28, s1, s1->scale);
                addNpcToVisibilityBucket(*(s32 *)a4, s1->mesh, s1, s1->radius);
            } else {
                enqueueMeshTypeForCleanup(s1->mesh);
                mat34CrossRowsAndCopyPos(s1->mesh + 0x28, s1, s1->scale);
            }
            if (s1->b93 != 0) {
                updateActive3DAudioSource(s1->audio, s1, &s1->vel, 0x64);
            }
            if (s1->ctx != NULL) {
                lookupHmtTextureByName((s32)s1->mesh, D_mission_overlay_800A6DCC, 0, (u8 *)&sp[36], 0, 0);
                advanceNpcOnCurvedPath(*(s32 *)(a4 + 8), *(s32 *)a4, &sp[36], s1->ctx);
                return 1;
            }
            return 1;
        }
    case 5:
        {
            u8 *a5 = arg2;
            extrapolateNpcPositionForCurrentMode(arg2);
            play3DSoundEvent(0, s1, &s1->vel, 20.0f, 0.5f, 0, 0x2A, 0x78, 0x50);
            if (getNpcCurrentHealth(s1->obj) > 0) {
                u8 part = 0;
                s32 front;
                f32 mul;
                if (*(u8 **)(arg2 + 8) != NULL && *(char **)(*(u8 **)(arg2 + 8) + 0x24) != NULL && rs_strcmp(*(char **)(*(u8 **)(arg2 + 8) + 0x24), "body") != 0) {
                    if (rs_strcmp(*(char **)(*(u8 **)(arg2 + 8) + 0x24), "head") == 0) {
                        mul = 0.6f;
                        part = 1;
                    } else if (rs_strcmp(*(char **)(*(u8 **)(arg2 + 8) + 0x24), "neck") == 0) {
                        mul = 1.0f;
                        part = 1;
                    } else {
                        goto deflt;
                    }
                } else {
                deflt:
                    mul = 0.2f;
                    if (s1->state < 2) {
                        mul = 0.1f;
                    }
                }
                front = 0;
                switch (s1->state) {
                case 0:
                case 1:
                    front = 1;
                case 2:
                case 3:
                    *(u16 *)(a5 + 6) = (u32)((f32)*(u16 *)(a5 + 6) * mul);
                    break;
                }
                if (dealDamageToNpc(s1->obj, *(u16 *)(a5 + 6)) <= 0) {
                    if (front == 1 || part == 0) {
                        if (s1->b91 == 0) {
                            u8 *r = s1->rec;
                            datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s1->rec + 0x84));
                        }
                        npcAtAtHandleDestruction(s1, 0);
                        s1->b92 = 1;
                        destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                    } else {
                        if (s1->b93 == 1) {
                            s1->b93 = 0;
                            factor5RemoveListNode(s1->audio);
                        }
                        npcAtAtHandleDestruction(s1, 1);
                        spawnNpcWithRandomRotation(&sp[36]);
                        ((s32 *)sp)[42] = 0;
                        spawnHeavyMechSubEffect(&sp[36], arg0, "joint_4");
                        s1->state = 4;
                        *(u16 *)(s1->mesh + 8) &= ~0x40;
                        if (s1->sE2 != 0xFFFF) {
                            destroyNpcSlotByIndex(s1->sE2);
                            s1->sE2 = 0xFFFF;
                        }
                        dealDamageToNpc(s1->obj, dealDamageToNpc(s1->obj, 0) - 0x1F4);
                    }
                    clearPendingChildNpc(s1->obj);
                    setObjectFlagBit4(arg0);
                }
            }
            if (*(u16 *)a5 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)a5);
                return 1;
            }
            return 1;
        }
    case 9:
        {
            u8 *a9 = arg2;
            switch (arg2[0x18]) {
            case 0xC:
                s1->fDC = getActorCurrentValueByType(s1->obj);
                updateType1AnimRamp(s1->obj, 0.0f, 0.0f, 0.0f, 0);
                *(s32 **)(s1->mesh + 4) = D_mission_overlay_8010A614;
                s1->fFC = 0.0f;
                break;
            case 0xD:
                updateType1AnimRamp(s1->obj, s1->fDC, 0.0f, 0.0f, 0);
                s1->fFC = 3.0f;
                break;
            case 0xE:
                s1->b91 = 1;
                *(u32 *)(s1->rec + 0x4C) |= 0x80000000;
                s1->iEC = *(s32 *)(a9 + 4);
                s1->sE8 = *(u16 *)a9;
                s1->b6C = 1;
                s1->fFC = 3.0f;
                if (s1->slot6A != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s1->slot6A, arg0);
                    s1->slot6A = 0xFFFF;
                }
                clearPendingChildNpc(s1->obj);
                setObjectFlagBit4(arg0);
                return 1;
            case 8:
                if (getNpcCurrentHealth(s1->obj) > 0) {
                    u8 *b;
                    s32 o;
                    unregisterAndFreeNpcSlot(s1->slot62, arg0);
                    b = (u8 *)D_main_bss_80139560;
                    o = 0x2C;
                    if (*(s32 *)arg2 == 1) {
                        o = 0x2E;
                    }
                    s1->slot62 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    unregisterAndFreeNpcSlot(s1->slot66, arg0);
                    o = 0x12;
                    if (*(s32 *)arg2 == 1) {
                        o = 0xE;
                    }
                    s1->slot66 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    if (s1->slot68 != 0xFFFF) {
                        unregisterAndFreeNpcSlot(s1->slot68, arg0);
                        if (*(s32 *)(s1->rec + 0xA4) != 0) {
                            o = 0x18;
                            if (*(s32 *)arg2 == 1) {
                                o = 0x1A;
                            }
                            s1->slot68 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                        }
                    }
                    setObjectDetailLevel(s1->obj, *(s32 *)a9);
                    return 1;
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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", fake_func_800CEF1C);
