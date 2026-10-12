#include "common.h"

#include "common_types.h"
#include "rs_math.h"
extern s32 rand(void);
extern void setNpcHealth(s32, void *, void *);
extern void initActorMotionParams(s32, s32, s32, s32, f32);
extern void setObjectDetailLevel(s32, s32);
extern void initObjectAnimSubstruct(s32, s32, s32, s32, f32, void *, s32, f32, f32, f32);
extern void setEffectIntensity(s32, s32);
extern s32 D_main_bss_80137CE4;
extern s32 spawnProbeDroidGroundImpactEffect(void *);

typedef struct { u8 pad0[0x34]; u8 *p34; s32 h38; } NpcA;
void initNpcActorVariant(void *arg0) {
    NpcA *s1 = *(NpcA **)((u8 *)arg0 + 4);
    u8 *s0;
    f32 r;
    *(s16 *)((u8 *)s1 + 0xE2) = 0;
    *(s32 *)((u8 *)s1 + 0x54) = 0;
    { f32 x = ((f32)(rand() & 0x7F) - 64.0f) * 0.03125f; FABSF(r, x); }
    s0 = s1->p34;
    *(f32 *)((u8 *)s1 + 0x58) = r + 1.0f;
    setNpcHealth(s1->h38, s0 + 0x6C, s0);
    initActorMotionParams(s1->h38, *(s32 *)(s0 + D_main_bss_80137CE4 * 4 + 0xA0), *(s32 *)(s0 + D_main_bss_80137CE4 * 4 + 0xA4), *(s32 *)(s0 + D_main_bss_80137CE4 * 4 + 0xA8), *(f32 *)(s0 + D_main_bss_80137CE4 * 4 + 0xAC));
    setObjectDetailLevel(s1->h38, *(s32 *)(s0 + 0x90));
    initObjectAnimSubstruct(s1->h38, *(s32 *)(s0 + 0xB0), *(s32 *)(s0 + 0xB4), *(s32 *)(s0 + 0xB8), *(f32 *)(s0 + 0xBC), spawnProbeDroidGroundImpactEffect, 0, 10.0f, 15.0f, *(f32 *)(s0 + D_main_bss_80137CE4 * 4 + 0xC0));
    setEffectIntensity(s1->h38, *(s32 *)(s0 + 0xC4));
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6B94);

#include "common_types.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} V3i;

struct ProbeFrame {
    V3i pos;
    V3i a;
    V3i b;
    V3i c;
};

extern V3i D_mission_overlay_800A6B94;
extern void *getObjectMeshTransformOrLocal(s32, void *);
extern void vec3Cross(f32 *, f32 *, f32 *);
extern f32 normalize_vector(f32 *);
extern void generatePerpEmitDirectionWithJitter(s32, void *, s32);
extern s32 tickProgressChannel(s32, void *, s32, f32 *);
extern void triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 spawnProbeDroidGroundImpactEffect(void *arg0) {
    f32 sp28[3];
    f32 sp38[3];
    f32 sp48[3];
    u8 sp58[0x30];
    struct ProbeFrame sp88;
    f32 spB8;
    f32 *m;
    f32 *npc;
    s32 r;

    *(V3i *)sp28 = D_mission_overlay_800A6B94;
    npc = *(f32 **)((u8 *)arg0 + 4);
    m = getObjectMeshTransformOrLocal(*(s32 *)((u8 *)npc + 0x38), sp58);
    sp38[0] = m[0] - npc[0];
    sp38[1] = m[1] - npc[1];
    sp38[2] = m[2] - npc[2];
    vec3Cross(sp48, sp28, sp38);
    vec3Cross(sp28, sp38, sp48);
    normalize_vector(sp28);
    normalize_vector(sp48);
    normalize_vector(sp38);
    sp88.a = *(V3i *)sp38;
    sp88.b = *(V3i *)sp28;
    sp88.pos = *(V3i *)npc;
    generatePerpEmitDirectionWithJitter(*(s32 *)((u8 *)npc + 0x38), &sp88, 0);
    r = tickProgressChannel(*(s32 *)((u8 *)npc + 0x38), &sp88, 0, &spB8) & 0xFF;
    if (r == 1) {
        triggerCueWithSlotEffect(*(s32 *)((u8 *)npc + 0x38), 3, &sp88, 0, r, 10.0f, spB8);
        play3DSoundEvent(0, npc, (u8 *)npc + 0x24, 20.0f, 0.5f, 0, 0x1D, 0x73, 0);
    }
    return 0;
}

typedef struct {
    f32 x, y, z;
    u8 pad0C[0x38];
    f32 unk44;
    u8 pad48[0x14];
    f32 unk5C;
    f32 unk60;
    f32 unk64;
    f32 unk68;
    f32 unk6C;
    f32 unk70;
    f32 unk74;
    f32 unk78;
    u8 pad7C[0x66];
    s16 unkE2;
} ProbeScatter;
extern s32 rand();
extern f32 vec3Length(f32 *);

void initProbeDroidScatterLaunch(ProbeScatter *arg0) {
    f32 sp10[3];
    f32 len;
    f32 r;

    if (arg0->unk68 > 0.0f) {
        sp10[0] = ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / arg0->unk68);
        sp10[1] = ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / arg0->unk68);
        sp10[2] = ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / arg0->unk68);
        len = vec3Length(sp10);
        if ((arg0->unk68 - arg0->unk44) < len) {
            normalize_vector(sp10);
            sp10[0] *= arg0->unk68 - arg0->unk44;
            sp10[1] *= arg0->unk68 - arg0->unk44;
            sp10[2] *= arg0->unk68 - arg0->unk44;
        }
        arg0->unk6C = arg0->unk5C + sp10[0];
        arg0->unk70 = arg0->unk60 + sp10[1];
        arg0->unk74 = arg0->unk64 + sp10[2];
    } else {
        arg0->unk6C = arg0->x;
        arg0->unk70 = arg0->y;
        arg0->unk74 = arg0->z;
    }
    { f32 x = ((f32)(rand() & 0x7F) - 64.0f) * 0.0078125f; f32 a; FABSF(a, x); r = a + 0.25f; }
    arg0->unkE2 = 1;
    arg0->unk78 = r;
}

#define FREEH if (*(s32 *)(o + 0x3C) != 0) { rs_free(*(s32 *)(o + 0x3C)); *(s32 *)(o + 0x3C) = 0; }
extern f32 vec3Dot(f32 *, f32 *);
extern f32 vec3Length(f32 *);
extern void vec3NormalizeInto(void *, f32 *);
extern f32 sinfApprox(f32);
extern void quatFromAxisAngle(f32 *, void *, f32);
extern void rotateVec3ByQuat(f32 *, void *, void *);
extern void orthonormalizeFrame(void *);
extern u8 spawnNpcAnchoredEffectSlot(s32, f32, s32);
extern f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
extern s32 isTerrainCellBlockedAtWorldXz(f32, f32, void *);
extern void rs_free(s32);
extern u8 D_main_bss_80138058[];

#define F(o, off) (*(f32 *)((u8 *)(o) + (off)))

void updateProbeDroidHopState(u8 *o, f32 dt) {
    f32 sp10[3];
    f32 sp20[3];
    f32 sp30[4];
    f32 sp40[4];
    f32 ang;
    f32 lim;
    f32 s;
    s16 v;
    f32 a, b, c;

    switch (*(s16 *)(o + 0xE2)) {
    case 1:
        sp10[0] = F(o, 0x6C) - F(o, 0);
        sp10[1] = F(o, 0x70) - F(o, 4);
        sp10[2] = F(o, 0x74) - F(o, 8);
        vec3NormalizeInto(o + 0x24, sp10);
        if (vec3Length(sp10) > 0.5f) {
            sp10[1] = 0.0f;
            normalize_vector(sp10);
            sp20[0] = F(o, 0xC);
            sp20[1] = 0.0f;
            sp20[2] = F(o, 0x14);
            normalize_vector(sp20);
            ang = -sinfApprox(vec3Dot(sp20, sp10)) * 57.29578f;
            lim = FABSF_VAL(ang);
            if (dt * 15.0f < lim) {
                ang = ang < 0.0f ? dt * -15.0f : dt * 15.0f;
            }
            lim = FABSF_VAL(ang);
            if (0.0001f < lim) {
                quatFromAxisAngle(sp30, o + 0x18, ang);
                rotateVec3ByQuat(sp30, o + 0xC, o + 0xC);
                orthonormalizeFrame(o);
            }
            F(o, 0x24) = F(o, 0x24) * F(o, 0x78);
            F(o, 0x28) = F(o, 0x28) * F(o, 0x78);
            F(o, 0x2C) = F(o, 0x2C) * F(o, 0x78);
            F(o, 0) = F(o, 0) + F(o, 0x24) * dt;
            F(o, 4) = F(o, 4) + F(o, 0x28) * dt;
            F(o, 8) = F(o, 8) + F(o, 0x2C) * dt;
        } else {
            *(s16 *)(o + 0xE2) = 0;
            F(o, 0x54) = 0;
            F(o, 0x58) = FABSF_VAL(((f32)(((s32 (*)())rand)(sp10) & 0x7F) - 64.0f) * 0.03125f) + 1.0f;
            F(o, 0x24) = 0;
            F(o, 0x28) = 0;
            F(o, 0x2C) = 0;
        }
    case 0:
        if (F(o, 0x4C) > 0.0f) {
            if (F(o, 0x48) > 0.5f) {
                F(o, 0x50) = F(o, 0x50) * 0.98f;
                if (F(o, 0x50) < 1.0f) {
                    F(o, 0x50) = 1.0f;
                }
            }
            a = F(o, 0x4C) * F(o, 0x50);
            F(o, 0x4C) = a;
            F(o, 0x48) = a;
            if (F(o, 0x50) == 1.0f || 1.0f <= a) {
                F(o, 0x4C) = 0.0f;
            }
        } else {
            F(o, 0x48) = F(o, 0x48) * 0.9f;
            if (F(o, 0x48) < 0.05f) {
                F(o, 0x4C) = 0.05f;
                F(o, 0x50) = 1.1f;
            }
        }
        break;
    case 2:
    case 3:
        quatFromAxisAngle(sp40, o + 0x7C, F(o, 0x88) * dt * 5.0f);
        rotateVec3ByQuat(sp40, o + 0xC, o + 0xC);
        rotateVec3ByQuat(sp40, o + 0x18, o + 0x18);
        if (*(s16 *)(o + 0xE2) == 3) {
            F(o, 0x28) = F(o, 0x28) + dt * 1.2f;
            F(o, 0x58) = F(o, 0x58) - dt;
            if (F(o, 0x58) <= 0.0f) {
                o[0xE1] = 1;
                goto done;
            }
        } else {
            F(o, 0x28) = F(o, 0x28) + dt * 2.2f;
        }
        F(o, 4) = F(o, 4) + F(o, 0x28) * dt;
        F(o, 0) = F(o, 0) + F(o, 0x24) * dt;
        F(o, 8) = F(o, 8) + F(o, 0x2C) * dt;
        if (spawnNpcAnchoredEffectSlot(*(s32 *)(o + 0x38), dt, 10) == 1) {
        done:
            *(s16 *)(o + 0xE2) = 4;
            FREEH;
            break;
        }
        ang = wrapAngleToCyclicRange(F(o, 0), F(o, 8), D_main_bss_80138058, 0);
        if (ang < F(o, 4)) {
            o[0xE1] = 2;
            F(o, 4) = ang;
            *(s16 *)(o + 0xE2) = !isTerrainCellBlockedAtWorldXz(F(o, 0), F(o, 8), D_main_bss_80138058) ? 4 : 5;
            FREEH;
        }
        break;
    }
}

typedef struct { f32 x, y, z; } PVec3;
typedef struct {
    PVec3 pos;
    f32 fwd[3];
    f32 up[3];
    PVec3 vel;
    u8 *mesh;
    u8 *rec;
    s32 obj;
    u8 *ctx;
    f32 scale;
    f32 radius;
    f32 f48;
    s32 i4C;
    f32 f50;
    f32 timer;
    f32 f58;
    PVec3 home;
    f32 range;
    f32 f6C[4];
    f32 axis[3];
    f32 spin;
    u16 slot8C;
    u16 slot8E;
    u16 slot90;
    u16 slot92;
    s32 outCount;
    u8 audio[0x44];
    f32 soundTimer;
    u8 audioOn;
    u8 deathKind;
    s16 state;
    u8 tree[0x38];
} Probe;

extern void *rs_malloc(s32, s32);

extern void *walkMeshdef0List(char *);
extern void composeEulerRotationXYZ(void *, s32, s32, s32);
extern void mat34CrossRowsAndCopyPos(void *, void *, f32);
extern u16 popNpcSlotFromTail(u16, void *);
extern void createAndInitObject(void *, s32, void *, void *, s32);
extern void *getLevelDatItemByName(char *);
extern void *allocateAndInitCraftNpcContext(f32, f32, s32);
extern void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
extern void dispatchDatSubtypeByRandomIndex(void *, void *);
extern void factor5RemoveListNode(void *);
extern void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
extern void walkDatTreeAndCollectSubtypes(void *, void *);
extern void clearPendingAndDestroyChildNpc(void *);
extern void releaseMeshAsset(void *);
extern void func_mission_overlay_800AA6D0(void *, f32, void *);
extern void func_mission_overlay_800EFDE0(s32, s32, s32, f32);
extern u8 validateActorTargetLOS(s32);
extern void applyToObjectSubstructByFlag(s32, f32, f32, s32);
extern s32 findActiveNpcInSlotChain(u16, s32);
extern void *getNpcContextField8(u16);
extern void composeRandomRotationMatrix(void *, void *, f32, s32, s32, s32);
extern void scaleVec3ByRandomRange(void *, f32, f32);
extern void spawnDebris1Npc(void *, void *, f32, f32, f32);
extern void spawnOrientedEffectIfBudgetOk(void *, s32, s32, f32, f32);
extern void spawnNpcType0xAFromTemplate(void *, f32);
extern void spawnByteAnimDebrisDefault(void *);
extern void distanceAndDopplerNpcHelper(void *, f32, f32);
extern void spawnWaterSprayDebrisAndBurst(void *, f32, f32, f32, f32, f32);
extern s32 isNpcWithinActiveReferenceRange(void *);
extern void destroyNpcSlotByIndex(u16);
extern void destroyObjectOwnedNpcSlot(s32);
extern void walkDatTreeAndScaleLeafByFloat(void *, void *, s32);
extern s32 selectMeshLodAndSubmitForRender(s32, void *, void *, s32, f32);
extern void walkDatTreeAndVisitChildren(void *, void *, void *);
extern void advanceNpcOnCurvedPath(s32, s32, void *, void *);
extern s32 updateActive3DAudioSource(void *, void *, void *, u8);
extern void unregisterAndFreeNpcSlot(u16, void *);
extern void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
extern void tallyMidDetailObject(void *);
extern void setObjectFlagBit4(void *);
extern void slotDispatcherIter(u16, s32, void *);
extern s32 getNpcCurrentHealth(s32);
extern void extrapolateNpcPositionForCurrentMode(void *);
extern s32 dealDamageToNpc(s32, u16);
extern void buildRandomCameraFacingOrientation(s32, void *, f32, s32, s32, s32);
extern void spawnOrientedNpc(s32, void *, void *, s32, f32, f32, f32, f32);
extern void spawnRandomScaleEffectDefault(void *);
extern void spawnDestructionEffectBurst(void *, u16, f32, f32, f32, f32);
extern void spawnDirectionalDebrisBurst(void *, u16, f32, f32, f32, f32);
extern u16 D_main_bss_80139560[];
extern u16 D_main_bss_80139562;
extern u16 D_main_bss_80139574;
extern u8 D_mission_overlay_8010A600[];

typedef struct {
    u16 a, b;
    u16 c, d;
    f32 e;
} SlotMsg;

s32 npcProbeDriod(u8 *arg0, u16 action, u8 *arg2) {
    Probe *s1 = *(Probe **)(arg0 + 4);
    PVec3 sp28;
    f32 sp38[4];
    f32 sp48[4];
    f32 sp58[4];
    f32 dt;
    s32 n;
    s32 i;
    u8 *rec;
    u8 *m;
    u8 *m6;
    u8 *m4;
    s32 n4;

    switch (action) {
    case 1:
        rec = arg2;
        s1 = rs_malloc(0x11C, 0);
        *(Probe **)(arg0 + 4) = s1;
        s1->rec = arg2;
        s1->mesh = walkMeshdef0List("probe_droid");
        *(u8 **)(s1->mesh + 4) = D_mission_overlay_8010A600;
        composeEulerRotationXYZ(s1, *(s32 *)(arg2 + 0x1C), *(s32 *)(arg2 + 0x20), *(s32 *)(arg2 + 0x24));
        s1->pos = *(PVec3 *)(arg2 + 0x10);
        s1->vel.x = s1->vel.y = s1->vel.z = 0.0001f;
        s1->scale = *(f32 *)(arg2 + 0x28);
        if (s1->scale < *(f32 *)(arg2 + 0x2C)) {
            s1->scale = *(f32 *)(arg2 + 0x2C);
        }
        if (*(f32 *)(arg2 + 0x30) > s1->scale) {
            s1->scale = *(f32 *)(arg2 + 0x30);
        }
        mat34CrossRowsAndCopyPos(s1->mesh + 0x28, s1, s1->scale);
        *(Probe **)(arg0 + 8) = s1;
        *(u8 **)(arg0 + 0xC) = s1->mesh;
        {
            u8 *b = (u8 *)D_main_bss_80139560;
            register s32 one asm("$16") = 1;
            s32 o;
            o = 0;
            if (*(s32 *)(arg2 + 0x90) == one) {
                o = 0xA;
            }
            s1->slot8E = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            if (*(s32 *)(arg2 + 0x94) != 0) {
                o = 0x18;
                if (*(s32 *)(arg2 + 0x90) == one) {
                    o = 0x1A;
                }
                s1->slot90 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            } else {
                s1->slot90 = 0xFFFF;
            }
        }
        {
            u8 *b = (u8 *)D_main_bss_80139560;
            s32 o;
            s1->slot8C = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
            o = 0x30;
            if (*(s32 *)(rec + 0x90) == 1) {
                o = 0x32;
            }
            s1->slot92 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
        }
        s1->i4C = 0;
        s1->outCount = 0;
        s1->f48 = 1.0f;
        s1->radius = *(f32 *)(*(u8 **)s1->mesh + 0x44) * s1->scale;
        createAndInitObject(&s1->obj, 0, arg0, initNpcActorVariant, 0);
        {
            char *name = (char *)(*(s32 *)(rec + 0x8C) + (s32)rec);
            u8 *item;
            if (*name != '-' && (item = getLevelDatItemByName(name)) != NULL) {
                s1->home = *(PVec3 *)(item + 0x10);
                s1->range = *(f32 *)(item + 0x1C) - s1->radius;
                if (s1->range < 0.0f) {
                    s1->range = 0.0f;
                }
            } else {
                s1->home = s1->pos;
                s1->range = 1.0f;
            }
        }
        s1->ctx = allocateAndInitCraftNpcContext(0.2f, 0.2f, 0xA);
        *(f32 *)(s1->ctx + 0x14) = 7.0f;
        *(f32 *)(s1->ctx + 0x10) = 0.2f;
        play3DSoundEventVariant(s1->audio, s1, &s1->vel, 15.0f, 0.8f, 0xF, 0x1E, 1, 0x6E, 0);
        s1->audioOn = 1;
        s1->soundTimer = 0;
        dispatchDatSubtypeByRandomIndex(s1->tree, s1->mesh);
        return 1;
    case 2:
        if (s1->audioOn == 1) {
            factor5RemoveListNode(s1->audio);
        }
        if (s1->ctx != NULL) {
            rs_free((s32)s1->ctx);
        }
        initActorRenderDescriptorIfUninit(s1->obj, s1->state >= 2, s1->rec, 0, s1->rec + 0x70);
        walkDatTreeAndCollectSubtypes(s1->tree, s1->mesh);
        clearPendingAndDestroyChildNpc(&s1->obj);
        releaseMeshAsset(s1->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        func_mission_overlay_800AA6D0(s1, dt, s1->rec + 0x34);
        switch (s1->state) {
        case 0:
            s1->timer += dt;
            if (s1->f58 <= s1->timer) {
                initProbeDroidScatterLaunch((ProbeScatter *)s1);
            }
            updateProbeDroidHopState((u8 *)s1, dt);
            goto common;
        case 1:
            updateProbeDroidHopState((u8 *)s1, dt);
            s1->soundTimer -= dt;
            if (s1->soundTimer <= 0.0f) {
                u16 id;
                *(f32 *)((u8 *)s1 + 0xDC) = 5.0f;
                id = findActiveNpcInSlotChain(D_main_bss_80139562, 0);
                if (id != 0xFFFF) {
                    f32 *p = getNpcContextField8(id);
                    sp28.x = p[0] - s1->pos.x;
                    sp28.y = p[1] - s1->pos.y;
                    sp28.z = p[2] - s1->pos.z;
                    if (vec3Length((f32 *)&sp28) <= 10.0f) {
                        play3DSoundEvent(0, s1, &s1->vel, 10.0f, 0.2f, 0, 0x1C, 0x78, 0x50);
                    }
                }
            }
        common:
            func_mission_overlay_800EFDE0(s1->obj, *(s32 *)(s1->rec + 0x98), *(s32 *)(s1->rec + 0x9C), dt);
            if (validateActorTargetLOS(s1->obj)) {
                applyToObjectSubstructByFlag(s1->obj, dt, 0.0f, 0);
            }
            break;
        case 2:
        case 3:
            updateProbeDroidHopState((u8 *)s1, dt);
            break;
        case 4:
            if (s1->deathKind != 0) {
                n4 = (s16)((s16)rand() % 3) + 2;
                for (i = 0; i < n4; i++) {
                    if (s1->deathKind == 2) {
                        composeRandomRotationMatrix(&sp28, sp38, s1->radius * 0.5f, 30, 0, 0);
                    } else {
                        composeRandomRotationMatrix(&sp28, sp38, s1->radius * 0.5f, 90, 0, 0);
                    }
                    sp28.x += s1->pos.x;
                    sp28.y += s1->pos.y;
                    sp28.z += s1->pos.z;
                    scaleVec3ByRandomRange(sp38, 3.0f, 4.0f);
                    spawnDebris1Npc(&sp28, sp38, 60.0f, 0.8f, 0.3f);
                }
                if (s1->deathKind == 2) {
                    spawnOrientedEffectIfBudgetOk(s1, 0, 0, 0.5f, 1.0f);
                }
            }
            spawnNpcType0xAFromTemplate(s1, s1->radius * 4.0f);
            spawnByteAnimDebrisDefault(s1);
            play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.4f, 0, 0x24, 0x7D, 0x28);
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        case 5:
            n = (s16)((s16)rand() % 3) + 3;
            for (i = 0; i < n; i++) {
                f32 a, b, c, x;
                composeRandomRotationMatrix(sp48, sp58, s1->radius * 0.5f, 80, 0, 0);
                sp48[0] += s1->pos.x;
                sp48[1] += s1->pos.y;
                sp48[2] += s1->pos.z;
                scaleVec3ByRandomRange(sp58, 1.0f, 2.5f);
                a = FABSF_VAL(((f32)(rand() & 0x7F) - 64.0f) / 12.8f) + 20.0f;
                b = FABSF_VAL(((f32)(rand() & 0x7F) - 64.0f) / 80.0f) + 0.5f;
                spawnDebris1Npc(sp48, sp58, a, b, FABSF_VAL(((f32)(rand() & 0x7F) - 64.0f) / 320.0f) + 0.2f);
                distanceAndDopplerNpcHelper(sp48, 0.05f, 0.2f);
            }
            spawnWaterSprayDebrisAndBurst(s1, 0.05f, 0.8f, 0.8f, 1.0f, 1.0f);
            spawnByteAnimDebrisDefault(s1);
            play3DSoundEvent(0, s1, &s1->vel, 20.0f, 0.4f, 0, 0x73, 0x7D, 0x28);
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        if (isNpcWithinActiveReferenceRange(s1) != 0) {
            s1->outCount = 0;
        } else {
            s1->outCount++;
            if (s1->outCount >= 0x15) {
                destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                return 1;
            }
        }
        destroyObjectOwnedNpcSlot(s1->obj);
        if (s1->tree[0] != 0xFF) {
            walkDatTreeAndScaleLeafByFloat(s1->tree, s1->mesh, *(s32 *)arg2);
            return 1;
        }
        return 1;
    case 4:
        m4 = arg2;
        sp28 = s1->pos;
        s1->pos.y += (s1->f48 - 0.5f) * -0.08f;
        if (selectMeshLodAndSubmitForRender(*(s32 *)arg2, s1->mesh, s1, *(s32 *)(s1->rec + 0x28), 0.02f) != 0 && s1->tree[0] != 0xFF) {
            walkDatTreeAndVisitChildren(s1->tree, s1->mesh, arg2);
        }
        s1->pos = sp28;
        if (s1->ctx != NULL) {
            advanceNpcOnCurvedPath(*(s32 *)(m4 + 8), *(s32 *)m4, s1, s1->ctx);
        }
        if (s1->audioOn == 1) {
            updateActive3DAudioSource(s1->audio, s1, &s1->vel, 0x6E);
            return 1;
        }
        return 1;
    case 6:
        m6 = arg2;
        if (s1->state != 2) {
            if (*(u16 *)arg2 != 0xFFFF) {
                f32 *p = getNpcContextField8(*(u16 *)arg2);
                s1->vel.x = s1->pos.x - p[0];
                s1->vel.y = s1->pos.y - p[1];
                s1->vel.z = s1->pos.z - p[2];
                normalize_vector((f32 *)&s1->vel);
                s1->state = 2;
                s1->vel.x *= 1.5f;
                s1->vel.y *= 1.5f;
                s1->vel.z *= 1.5f;
                do {
                    s1->axis[0] = ((f32)(rand() & 0x7F) - 64.0f) * 0.015625f;
                    s1->axis[1] = ((f32)(rand() & 0x7F) - 64.0f) * 0.015625f;
                    s1->axis[2] = ((f32)(rand() & 0x7F) - 64.0f) * 0.015625f;
                } while (vec3Length(s1->axis) == 0.0f);
                normalize_vector(s1->axis);
                s1->spin = ((f32)(rand() & 0x7F) - 64.0f) / 0.35555556f;
                spawnNpcType0xAFromTemplate(s1, 0.5f);
                play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.6f, 0, 0x4F, 0x7D, 0x50);
                {
                    s32 *h = (s32 *)(D_main_bss_80137CE4 * 4 + (s32)s1->rec);
                    if (h[0x6C / 4] > 0) {
                        u8 *r;
                        h[0x6C / 4] = 0;
                        unregisterAndFreeNpcSlot(s1->slot8C, arg0);
                        unregisterAndFreeNpcSlot(s1->slot92, arg0);
                        unregisterAndFreeNpcSlot(s1->slot8E, arg0);
                        if (s1->slot90 != 0xFFFF) {
                            unregisterAndFreeNpcSlot(s1->slot90, arg0);
                        }
                        popNpcSlotFromTail(D_main_bss_80139574, arg0);
                        r = s1->rec;
                        datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s1->rec + 0x84));
                        tallyMidDetailObject(arg0);
                        setObjectFlagBit4(arg0);
                    }
                }
                ((SlotMsg *)&sp28)->a = 0xFFFF;
                ((SlotMsg *)&sp28)->b = 0xFFFF;
                ((SlotMsg *)&sp28)->d = 0x32;
                ((SlotMsg *)&sp28)->e = 0.0f;
                ((SlotMsg *)&sp28)->c = 7;
                slotDispatcherIter(*(u16 *)m6, 5, &sp28);
            }
        }
        m6[2] = 1;
        break;
    case 5:
        m = arg2;
        if (getNpcCurrentHealth(s1->obj) > 0) {
            extrapolateNpcPositionForCurrentMode(m);
            play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.6f, 0, 0x2A, 0x7D, 0x50);
            if (dealDamageToNpc(s1->obj, *(u16 *)(m + 6)) <= 0) {
                if (*(u8 **)(m + 8) != NULL) {
                    s1->vel.x = *(f32 *)(*(u8 **)(m + 8) + 0xC) * 1.5f;
                    s1->vel.y = *(f32 *)(*(u8 **)(m + 8) + 0x10) * 1.5f;
                    s1->vel.z = *(f32 *)(*(u8 **)(m + 8) + 0x14) * 1.5f;
                }
                do {
                    s1->axis[0] = ((f32)(rand() & 0x7F) - 64.0f) * 0.015625f;
                    s1->axis[1] = ((f32)(rand() & 0x7F) - 64.0f) * 0.015625f;
                    s1->axis[2] = ((f32)(rand() & 0x7F) - 64.0f) * 0.015625f;
                } while (vec3Length(s1->axis) == 0.0f);
                normalize_vector(s1->axis);
                s1->spin = ((f32)(rand() & 0x7F) - 64.0f) / 0.35555556f;
                if (s1->audioOn == 1) {
                    s1->audioOn = 0;
                    factor5RemoveListNode(s1->audio);
                }
                if (*(u16 *)(m + 4) != 0xC) {
                    switch (rand() & 3) {
                    case 0:
                        s1->state = 4;
                        s1->deathKind = rand() & 1;
                        buildRandomCameraFacingOrientation(0, sp38, 0.0f, 0, 5, 1);
                        spawnOrientedNpc(1, s1, sp38, 0, 0.1f, 0.5f, 0.1f, 1.0f);
                        break;
                    case 1:
                        s1->state = 3;
                        s1->f58 = 0.5f;
                        s1->vel.x *= 1.5f;
                        s1->vel.y *= 1.5f;
                        s1->vel.z *= 1.5f;
                        spawnRandomScaleEffectDefault(s1);
                        play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.4f, 0, 0x24, 0x7D, 0x28);
                        break;
                    case 2:
                        s1->state = 2;
                        spawnRandomScaleEffectDefault(s1);
                        play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.4f, 0, 0x24, 0x7D, 0x28);
                        spawnDestructionEffectBurst(s1, *(u16 *)(arg0 + 0x16), 1.5f, 0.7f, 1.2f, 1.0f);
                        break;
                    case 3:
                        s1->state = 2;
                        spawnRandomScaleEffectDefault(s1);
                        play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.4f, 0, 0x24, 0x7D, 0x28);
                        spawnDirectionalDebrisBurst(s1, *(u16 *)(arg0 + 0x16), 1.5f, 0.4f, 1.2f, 1.0f);
                        break;
                    }
                } else {
                    s1->state = 2;
                    play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.4f, 0, 0x24, 0x7D, 0x28);
                }
                unregisterAndFreeNpcSlot(s1->slot8C, arg0);
                unregisterAndFreeNpcSlot(s1->slot92, arg0);
                unregisterAndFreeNpcSlot(s1->slot8E, arg0);
                if (s1->slot90 != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s1->slot90, arg0);
                }
                popNpcSlotFromTail(D_main_bss_80139574, arg0);
                {
                    u8 *r = s1->rec;
                    datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s1->rec + 0x84));
                }
                tallyMidDetailObject(arg0);
                setObjectFlagBit4(arg0);
            }
        }
        if (*(u16 *)m != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)m);
        }
        break;
    }
    return 1;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D10);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D18);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D20);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D28);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D30);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D38);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D40);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D48);
