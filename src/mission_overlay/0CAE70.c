#include "common.h"

#include "common_types.h"
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
    { f32 x = ((f32)(rand() & 0x7F) - 64.0f) * 0.03125f; __asm__ volatile("abs.s %0, %1" : "=f"(r) : "f"(x)); }
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
extern void normalize_vector(f32 *);
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
    { f32 x = ((f32)(rand() & 0x7F) - 64.0f) * 0.0078125f; f32 a; __asm__ volatile("abs.s %0, %1" : "=f"(a) : "f"(x)); r = a + 0.25f; }
    arg0->unkE2 = 1;
    arg0->unk78 = r;
}

#define FREEH if (*(s32 *)(o + 0x3C) != 0) { rs_free(*(s32 *)(o + 0x3C)); *(s32 *)(o + 0x3C) = 0; }
#define ABSF(x) ({ f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(x)); _r; })
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
            lim = ABSF(ang);
            if (dt * 15.0f < lim) {
                ang = ang < 0.0f ? dt * -15.0f : dt * 15.0f;
            }
            lim = ABSF(ang);
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
            F(o, 0x58) = ABSF(((f32)(((s32 (*)())rand)(sp10) & 0x7F) - 64.0f) * 0.03125f) + 1.0f;
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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CAE70", npcProbeDriod);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D10);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D18);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D20);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D28);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D30);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D38);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D40);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D48);
