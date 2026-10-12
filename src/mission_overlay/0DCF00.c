#include "common.h"
#include "common_types.h"
#include "rs_math.h"

typedef struct { f32 x, y, z; } RdV3;
typedef union { RdV3 v; f32 w[4]; } RdV4;
extern RdV3 D_mission_overlay_8010A950;
extern u8 isPendingChildNpcActive(s32);
extern u8 computeActorAnchorDeltaAfterLOS(s32);
extern f32 *getObjectMeshTransformOrLocal(s32, void *);
extern void mat3x3InverseInto(void *, void *);
extern void transformVec3ByMat34(void *, void *, void *);
extern f32 vec3NormalizeInto(void *, void *);
extern void buildRotationMatrixSlot0(void *, f32);
extern void buildRotationMatrixSlot1(void *, f32);
extern f32 vec3Dot(void *, void *);
extern f32 vec3Length(void *);
extern f32 constMinusSinfApprox(f32);
extern void vec3Cross(void *, void *, void *);
extern f32 normalize_vector(void *);
extern void quatFromAxisAngle(void *, void *, f32);
extern void rotateVec3ByQuat(void *, void *, void *);
extern void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void composeRotationMatrixSlot1(void *, f32);
void factor5RemoveListNode(void *);
f32 floatModulo(f32, f32);

void rdImpl(u8 *npc, f32 dt) __asm__("npcRadarDishComputeAimMotion");
void rdImpl(u8 *npc, f32 dt) {
    f32 m1[12];
    f32 m2[12];
    RdV4 tgt;
    RdV4 dir;
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
        pos = getObjectMeshTransformOrLocal(*(s32 *)(npc + 0x38), NULL);
        mat34CrossRowsAndCopyPos(m1, npc, 1.0f);
        mat3x3InverseInto(m2, m1);
        transformVec3ByMat34(m2, pos, &dir);
        dir.v.y -= *(f32 *)(npc + 0x5C);
        vec3NormalizeInto(&tgt, &dir);
        buildRotationMatrixSlot0(m1, *(f32 *)(npc + 0x58));
        composeRotationMatrixSlot1(m1, *(f32 *)(npc + 0x54));
        transformVec3ByMat34(m1, &D_mission_overlay_8010A950, &dir);
        ang = constMinusSinfApprox(vec3Dot(&dir, &tgt)) * 57.29578f;
        if (ang > 0.001f) {
            RdV4 axis;
            f32 q[4];
            RdV4 c;
            RdV4 a;
            RdV4 b;
            if (ang > 10.0f && npc[0xB0] == 0) {
                npc[0xB0] = los;
                play3DSoundEventVariant(npc + 0x6C, npc, npc + 0x24, 8.0f, 0.1f, 7, 0x4B, los, 0x64, 0x28);
            }
            if (*(f32 *)(npc + 0x60) * (dt * 30.0f) < ang) {
                ang = *(f32 *)(npc + 0x60) * (dt * 30.0f);
            }
            vec3Cross(&axis, &dir, &tgt);
            normalize_vector(&axis);
            quatFromAxisAngle(q, &axis, ang);
            rotateVec3ByQuat(q, &dir, &tgt);
            axis.v.x = tgt.v.x;
            axis.v.y = 0.0f;
            axis.v.z = tgt.v.z;
            ang = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010A950, &axis) / (vec3Length(&D_mission_overlay_8010A950) * vec3Length(&axis))) * 57.29578f;
            a.v = D_mission_overlay_8010A950;
            a.v.y = 0.0f;
            b.v = axis.v;
            b.v.y = 0.0f;
            vec3Cross(&c, &a, &b);
            if (!(c.v.y >= 0.0f)) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(m1, -ang);
            transformVec3ByMat34(m1, &tgt, &axis);
            axis.v.x = 0.0f;
            *(f32 *)(npc + 0x54) = ang;
            ang2 = constMinusSinfApprox(vec3Dot(&D_mission_overlay_8010A950, &axis) / (vec3Length(&D_mission_overlay_8010A950) * vec3Length(&axis))) * 57.29578f;
            if (!(axis.v.y <= 0.0f)) {
                ang2 = -ang2;
            }
            lim = -ang2;
            *(f32 *)(npc + 0x58) = lim;
            if (lim > 24.0f) {
                *(f32 *)(npc + 0x58) = 24.0f;
            } else if (lim < -50.0f) {
                *(f32 *)(npc + 0x58) = -50.0f;
            }
        } else if (npc[0xB0] == los) {
            npc[0xB0] = 0;
            factor5RemoveListNode(npc + 0x6C);
        }
    } else {
other:
        *(f32 *)(npc + 0x54) = floatModulo(*(f32 *)(npc + 0x54) + *(f32 *)(npc + 0x60) * (dt * 30.0f), 360.0f);
    }
}

f32 fabsf(f32);
extern u16 D_main_bss_80139560[] __asm__("D_main_bss_80139560");
extern u8 D_main_bss_801399FB;
extern u8 D_main_bss_80130B39;
extern u16 D_main_bss_80139574;
void npcInitMinimalNoAnim(void *);

void *walkMeshdef0List(char *);
void composeEulerRotationXYZ(void *, f32, f32, f32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
void composeRotationMatrixSlot2(void *, f32);
void addVec3At0x24(void *, f32, f32, f32);
u16 popNpcSlotFromTail(u16, void *);
s32 lookupHmtMaterialByName(void *, char *, void *);
void createAndInitObject(void *, s32, void *, void *, s32);
void dispatchDatSubtypeByRandomIndex(void *, void *);
void factor5RemoveListNode(void *);
s32 getNpcCurrentHealth(s32);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void walkDatTreeAndCollectSubtypes(void *, void *);
void releaseMeshAsset(void *);
f32 floatModulo(f32, f32);
void func_mission_overlay_800EFDE0(s32, s32, s32, f32);
void npcRadarDishComputeAimMotion(void *, f32);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyObjectOwnedNpcSlot(s32);
void walkDatTreeAndScaleLeafByFloat(void *, void *, f32);
void destroyNpcSlotByIndex(u16);
void transformMeshPartIntoWorld(void *, f32 *);
void spawnNpcType0xAFromTemplate(f32 *, f32);
void spawnByteAnimDebrisDefault(void *);
void spawnOrientedNpc(s32, f32 *, s32, s32, f32, f32, f32, f32);
void spawnDestructionEffectBurst(f32 *, s32, f32, f32, f32, f32);
void composeRandomRotationMatrix(f32 *, f32 *, f32, s32, s32, s32);
void scaleVec3ByRandomRange(f32 *, f32, f32);
void spawnDebris1Npc(f32 *, f32 *, f32, f32, f32);
void spawnSplineWalkerCraft(void *, f32, f32, s32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void clearVec4QuadStruct(void *);
void applyScaleToMat3x4(void *, s32, s32, s32);
void composeQuatToMat3x4(void *, void *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
void walkDatTreeAndVisitChildren(void *, void *, void *);
void updateActive3DAudioSource(void *, void *, void *, s32);
void extrapolateNpcPositionForCurrentMode(void *);
s32 getObjectDetailLevel(s32);
void func_mission_overlay_800EFD6C(s32);
s32 dealDamageToNpc(s32, u16);
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
void clearPendingChildNpc(s32);
void setObjectFlagBit4(void *);
void dispatchSlotAction5IfActive(void *, void *);
s32 rand(void);

typedef struct {
    u8 pad0[0x4C];
    u32 flags;
    f32 f50, f54, f58;
    s32 w5C, w60, w64;
    u8 q68[0x10];
    f32 f78, f7C, f80;
} RdDef;

typedef struct {
    u8 pad0[0x1C];
    u8 mat[1];
} RdObj;

s32 npcRadarDishUpdate(u8 *arg0, s32 arg1, u8 *arg2) {
    u8 *n;
    u8 *d;
    u8 *m;
    s32 act;
    s32 i;
    s32 cnt;
    f32 sp28[3];
    f32 sp38[3];
    f32 sp48[4];
    f32 dt;
    f32 kk;
    u8 *a2;
    f32 a;
    f32 b;
    f32 c;
    f32 d3;
    f32 sc;
    s32 off;
    s16 r16;
    f32 sc2;
    register u16 *tb asm("$16");
    u16 *tb2;
    u32 fl;
    register s32 one asm("$16");
    u8 *q;

    act = arg1 & 0xFFFF;
    n = *(u8 **)(arg0 + 4);
    switch (act) {
    case 1:
        a2 = arg2;
        *(u8 **)(n + 0x34) = arg2;
        *(void **)(n + 0x30) = walkMeshdef0List("b_lrsp");
        *(f32 *)(n + 0) = *(f32 *)(a2 + 0x10);
        *(f32 *)(n + 4) = *(f32 *)(a2 + 0x14);
        *(f32 *)(n + 8) = *(f32 *)(a2 + 0x18);
        composeEulerRotationXYZ(n, *(f32 *)(a2 + 0x1C), *(f32 *)(a2 + 0x20) + 180.0f, *(f32 *)(a2 + 0x24));
        *(f32 *)(n + 0x24) = *(f32 *)(n + 0x28) = *(f32 *)(n + 0x2C) = 0.0f;
        kk = 1.0f / *(f32 *)(**(u8 ***)(n + 0x30) + 0x34);
        *(f32 *)(n + 0x50) = kk * *(f32 *)(a2 + 0x28);
        initVec4TripletFromArgs(*(u8 **)(n + 0x30) + 0x28, kk * *(f32 *)(a2 + 0x28), kk * *(f32 *)(a2 + 0x2C), kk * *(f32 *)(a2 + 0x30));
        composeRotationMatrixSlot0(*(u8 **)(n + 0x30) + 0x28, *(f32 *)(a2 + 0x1C));
        composeRotationMatrixSlot1(*(u8 **)(n + 0x30) + 0x28, *(f32 *)(a2 + 0x20) + 180.0f);
        composeRotationMatrixSlot2(*(u8 **)(n + 0x30) + 0x28, *(f32 *)(a2 + 0x24));
        addVec3At0x24(*(u8 **)(n + 0x30) + 0x28, *(f32 *)(n + 0), *(f32 *)(n + 4), *(f32 *)(n + 8));
        *(u8 **)(arg0 + 8) = n;
        *(void **)(arg0 + 0xC) = *(void **)(n + 0x30);
        tb = D_main_bss_80139560;
        *(u16 *)(n + 0x64) = popNpcSlotFromTail(tb[14], arg0);
        {
        s32 o1;
        if (*(s32 *)(a2 + 0x8C) != 1) {
            o1 = 0x2A;
            if (*(s32 *)(a2 + 0x8C) == 0) {
                o1 = 0x28;
            }
        } else {
            o1 = 0x26;
        }
        *(u16 *)(n + 0x66) = popNpcSlotFromTail(*(u16 *)((u8 *)tb + o1), arg0);
        }
        *(f32 *)(n + 0x5C) = (*(f32 *)(n + 0x50) / 0.05f) * -4.0f;
        *(s32 *)(n + 0x3C) = lookupHmtMaterialByName(*(void **)(n + 0x30), "top_tran", n + 0x44);
        *(s32 *)(n + 0x40) = lookupHmtMaterialByName(*(void **)(n + 0x30), "dish", n + 0x48);
        tb2 = D_main_bss_80139560;
        __asm__ volatile("" : "+r"(one));
        off = 0x12;
        one = 1;
        if (*(s32 *)(a2 + 0x8C) == one) {
            off = 0xE;
        }
        *(u16 *)(n + 0x68) = popNpcSlotFromTail(*(u16 *)(off + (u8 *)tb2), arg0);
        if (*(s32 *)(a2 + 0x90) != 0) {
            off = 0x18;
            if (*(s32 *)(a2 + 0x8C) == one) {
                off = 0x1A;
            }
            *(u16 *)(n + 0x6A) = popNpcSlotFromTail(*(u16 *)(off + (u8 *)tb2), arg0);
        } else {
            *(u16 *)(n + 0x6A) = 0xFFFF;
        }
        *(f32 *)(n + 0x4C) = *(f32 *)(**(u8 ***)(n + 0x30) + 0x44) * *(f32 *)(n + 0x50);
        *(s32 *)(n + 0x54) = 0;
        *(s32 *)(n + 0x58) = 0;
        *(u16 *)(n + 0xB2) = 0;
        n[0xB0] = 0;
        createAndInitObject(n + 0x38, 0, arg0, npcInitMinimalNoAnim, 0);
        dispatchDatSubtypeByRandomIndex(n + 0xB4, *(void **)(n + 0x30));
        return 1;
    case 2:
        if (n[0xB0] == 1) {
            n[0xB0] = 0;
            factor5RemoveListNode(n + 0x6C);
        }
        initActorRenderDescriptorIfUninit(*(s32 *)(n + 0x38), getNpcCurrentHealth(*(s32 *)(n + 0x38)) < 1, *(void **)(n + 0x34), 0, *(u8 **)(n + 0x34) + 0x70);
        clearPendingAndDestroyChildNpc(n + 0x38);
        walkDatTreeAndCollectSubtypes(n + 0xB4, *(void **)(n + 0x30));
        releaseMeshAsset(*(void **)(n + 0x30));
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        switch (n[0xB1]) {
        case 1:
            if (D_main_bss_801399FB == 1) {
                if (*(s32 *)(*(u8 **)(n + 0x34) + 0x98) != 0) {
                    *(f32 *)(n + 0x54) = floatModulo(*(f32 *)(n + 0x54) + *(f32 *)(n + 0x60) * (dt * 30.0f), 360.0f);
                } else {
                    func_mission_overlay_800EFDE0(*(s32 *)(n + 0x38), *(s32 *)(*(u8 **)(n + 0x34) + 0x9C), 6, dt);
                    npcRadarDishComputeAimMotion(n, dt);
                }
            }
            goto dflt;
        case 2:
            transformMeshPartIntoWorld(*(void **)(n + 0x30), sp28);
            sc = *(f32 *)(n + 0x50) * 20.0f;
            spawnNpcType0xAFromTemplate(sp28, *(f32 *)(n + 0x4C) * 3.0f);
            spawnByteAnimDebrisDefault(n);
            spawnOrientedNpc(0x8002, sp28, 0, 0, sc * 0.75f, sc * 1.2f, 1.0f, 0.4f);
            spawnDestructionEffectBurst(sp28, 0xFFFF, 1.6f, sc * 2.5f, 1.5f, 1.0f);
            {
            register f32 *p48 asm("$18");
            f32 *p38;
            i = 0;
            r16 = rand();
            cnt = (s16)(r16 % 3) + 7;
            if (cnt > 0) {
                p38 = sp38;
                p48 = sp48;
                do {
                    composeRandomRotationMatrix(p38, p48, *(f32 *)(n + 0x4C) / 3.0f, 0x3C, 0, 0);
                    sp38[0] += sp28[0];
                    sp38[1] += sp28[1];
                    sp38[2] += sp28[2];
                    scaleVec3ByRandomRange(p48, 1.5f, 3.0f);
                    c = ((f32)(rand() & 0x7F) - 64.0f) / 12.8f;
                    FABSF(a, c);
                    a += 12.0f;
                    c = ((f32)(rand() & 0x7F) - 64.0f) / 42.666668f;
                    FABSF(b, c);
                    b += 2.5f;
                    c = ((f32)(rand() & 0x7F) - 64.0f) / 320.0f;
                    FABSF(d3, c);
                    spawnDebris1Npc(p38, p48, a, b, d3 + 0.2f);
                    i++;
                } while (i < cnt);
            }
            }
            sc2 = *(f32 *)(n + 0x50) * 35.0f;
            spawnSplineWalkerCraft(n, sc2, sc2, 0xC);
            play3DSoundEvent(0, n, n + 0x24, 24.0f, 0.5f, 0, 0x26, 0x7F, 0x50);
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        case 0:
        default:
dflt:
            if (isNpcWithinActiveReferenceRange(n) != 0) {
                *(u16 *)(n + 0xB2) = 0;
            } else {
                *(u16 *)(n + 0xB2) = *(u16 *)(n + 0xB2) + 1;
                if (*(s16 *)(n + 0xB2) >= 0x15) {
                    destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                    return 1;
                }
            }
            destroyObjectOwnedNpcSlot(*(s32 *)(n + 0x38));
            if (n[0xB4] != 0xFF) {
                walkDatTreeAndScaleLeafByFloat(n + 0xB4, *(void **)(n + 0x30), *(f32 *)arg2);
            }
            return 1;
        }
    case 4:
        {
        u8 *d;
        u8 *m;
        d = *(u8 **)(n + 0x44);
        m = *(u8 **)(n + 0x3C) + 0x1C;
        clearVec4QuadStruct(m);
        if (((RdDef *)d)->flags & 1) {
            addVec3At0x24(m, -((RdDef *)d)->f50, -((RdDef *)d)->f54, -((RdDef *)d)->f58);
        }
        if (((RdDef *)d)->flags & 2) {
            applyScaleToMat3x4(m, ((RdDef *)d)->w5C, ((RdDef *)d)->w60, ((RdDef *)d)->w64);
        }
        if (((RdDef *)d)->flags & 4) {
            composeQuatToMat3x4(m, ((RdDef *)d)->q68);
        }
        composeRotationMatrixSlot1(m, *(f32 *)(n + 0x54));
        {
        u32 fl = ((RdDef *)d)->flags;
        if ((fl & 9) == 9) {
            addVec3At0x24(m, ((RdDef *)d)->f78 + ((RdDef *)d)->f50, ((RdDef *)d)->f7C + ((RdDef *)d)->f54, ((RdDef *)d)->f80 + ((RdDef *)d)->f58);
        } else if ((fl & 9) == 8) {
            addVec3At0x24(m, ((RdDef *)d)->f78, ((RdDef *)d)->f7C, ((RdDef *)d)->f80);
        } else if (fl & 1) {
            addVec3At0x24(m, ((RdDef *)d)->f50, ((RdDef *)d)->f54, ((RdDef *)d)->f58);
        }
        }
        d = *(u8 **)(n + 0x48);
        m = *(u8 **)(n + 0x40) + 0x1C;
        clearVec4QuadStruct(m);
        if (((RdDef *)d)->flags & 1) {
            addVec3At0x24(m, -((RdDef *)d)->f50, -((RdDef *)d)->f54, -((RdDef *)d)->f58);
        }
        if (((RdDef *)d)->flags & 2) {
            applyScaleToMat3x4(m, ((RdDef *)d)->w5C, ((RdDef *)d)->w60, ((RdDef *)d)->w64);
        }
        if (((RdDef *)d)->flags & 4) {
            composeQuatToMat3x4(m, ((RdDef *)d)->q68);
        }
        composeRotationMatrixSlot0(m, *(f32 *)(n + 0x58));
        {
        u32 fl = ((RdDef *)d)->flags;
        if ((fl & 9) == 9) {
            addVec3At0x24(m, ((RdDef *)d)->f78 + ((RdDef *)d)->f50, ((RdDef *)d)->f7C + ((RdDef *)d)->f54, ((RdDef *)d)->f80 + ((RdDef *)d)->f58);
        } else if ((fl & 9) == 8) {
            addVec3At0x24(m, ((RdDef *)d)->f78, ((RdDef *)d)->f7C, ((RdDef *)d)->f80);
        } else if (fl & 1) {
            addVec3At0x24(m, ((RdDef *)d)->f50, ((RdDef *)d)->f54, ((RdDef *)d)->f58);
        }
        }
        mat34CrossRowsAndCopyPos(*(u8 **)(n + 0x30) + 0x28, n, *(f32 *)(n + 0x50));
        if (addNpcToVisibilityBucket(*(s32 *)arg2, *(void **)(n + 0x30), n, *(f32 *)(n + 0x4C)) != 0 && n[0xB4] != 0xFF) {
            walkDatTreeAndVisitChildren(n + 0xB4, *(void **)(n + 0x30), arg2);
        }
        if (n[0xB0] != 0) {
            updateActive3DAudioSource(n + 0x6C, n, n + 0x24, 0x64);
        }
        }
        return 1;
    case 5:
        q = arg2;
        if (getNpcCurrentHealth(*(s32 *)(n + 0x38)) > 0) {
            extrapolateNpcPositionForCurrentMode(q);
            play3DSoundEvent(0, n, n + 0x24, 20.0f, 0.5f, 0, 0x2A, 0x7F, 0x50);
            if (getObjectDetailLevel(*(s32 *)(n + 0x38)) == 1 && D_main_bss_80130B39 == 0) {
                func_mission_overlay_800EFD6C(0x1F4);
            }
            if (dealDamageToNpc(*(s32 *)(n + 0x38), *(u16 *)(q + 6)) <= 0) {
                n[0xB1] = 2;
                unregisterAndFreeNpcSlot(*(u16 *)(n + 0x64), arg0);
                unregisterAndFreeNpcSlot(*(u16 *)(n + 0x66), arg0);
                unregisterAndFreeNpcSlot(*(u16 *)(n + 0x68), arg0);
                if (*(u16 *)(n + 0x6A) != 0xFFFF) {
                    unregisterAndFreeNpcSlot(*(u16 *)(n + 0x6A), arg0);
                }
                popNpcSlotFromTail(D_main_bss_80139574, arg0);
                datItemSetObjectiveBooleanCount(*(s32 *)(*(u8 **)(n + 0x34) + 0x78), *(s32 *)(*(u8 **)(n + 0x34) + 0x7C), *(s32 *)(*(u8 **)(n + 0x34) + 0x70), *(s32 *)(*(u8 **)(n + 0x34) + 0x74), *(s32 *)(*(u8 **)(n + 0x34) + 0x80), *(s32 *)(*(u8 **)(n + 0x34) + 0x84));
                tallyMidDetailObject(arg0);
                clearPendingChildNpc(*(s32 *)(n + 0x38));
                setObjectFlagBit4(arg0);
                if (n[0xB0] == 1) {
                    n[0xB0] = 0;
                    factor5RemoveListNode(n + 0x6C);
                }
            }
        }
        if (*(u16 *)q != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)q);
        }
        return 1;
    case 7:
        dispatchSlotAction5IfActive(arg0, arg2);
        return 1;
    default:
        return 1;
    }
}

extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern void initActorMotionParams(s32, f32, f32, f32, f32);

void npcInitMinimalNoAnim(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);

    npc[0xB1] = 1;
    *(f32 *)(npc + 0x60) = *(f32 *)(*(u8 **)(npc + 0x34) + 0x94);
    setNpcHealth(*(s32 *)(npc + 0x38), *(u8 **)(npc + 0x34) + 0x6C, *(u8 **)(npc + 0x34));
    initActorMotionParams(*(s32 *)(npc + 0x38), *(f32 *)(*(u8 **)(npc + 0x34) + 0xA0), *(f32 *)(*(u8 **)(npc + 0x34) + 0xA4), 0.0f, 0.0f);
    setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(*(u8 **)(npc + 0x34) + 0x8C));
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DCF00", fake_func_800DD2C4);

static u32 D_mission_overlay_800A7DD4[] __attribute__((section(".rodata"))) = { 0x3C018005, 0xC422FE50, 0x46020003 };
