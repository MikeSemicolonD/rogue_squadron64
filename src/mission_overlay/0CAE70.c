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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CAE70", updateProbeDroidHopState);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CAE70", npcProbeDriod);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D10);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D18);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D20);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D28);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D30);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D38);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D40);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CAE70", D_mission_overlay_800A6D48);
