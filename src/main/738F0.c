#include "common.h"
#include "common_types.h"

extern u16 spawnNpcOfType(void *, void *, u32, u8);

typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s16 unk24;
} HeavyBurstArgs;

extern void heavyRandomBurstNpcHandler(void);

INCLUDE_ASM("asm/nonmatchings/main/738F0", initWaterSprayParticles);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF04);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF10);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF20);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF38);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF3C);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF40);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF44);

INCLUDE_ASM("asm/nonmatchings/main/738F0", npcWaterSprayUpdate);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnDestructionEffectBurst);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnDistanceScaledDebrisBurst);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnDirectionalDebrisBurst);

INCLUDE_ASM("asm/nonmatchings/main/738F0", distanceAndDopplerNpcHelper);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D088);

INCLUDE_ASM("asm/nonmatchings/main/738F0", explosionEffectNpcHandler);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D0C8);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D0CC);

INCLUDE_ASM("asm/nonmatchings/main/738F0", triggerDistanceScaledExplosion);

INCLUDE_ASM("asm/nonmatchings/main/738F0", triggerObjectDestructionEffects);

INCLUDE_ASM("asm/nonmatchings/main/738F0", transformLimbStrideAnchorsLocal);

INCLUDE_ASM("asm/nonmatchings/main/738F0", randomParticleWithParentNpcHandler);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D15C);

INCLUDE_ASM("asm/nonmatchings/main/738F0", buildRandomCameraFacingOrientation);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D170);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnScaledOrientedEffectTriple);

INCLUDE_ASM("asm/nonmatchings/main/738F0", heavyRandomBurstNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/738F0", buildNpcAnchoredCameraEffectTransform);

INCLUDE_ASM("asm/nonmatchings/main/738F0", computeWalkerLimbStrideTargets);

INCLUDE_ASM("asm/nonmatchings/main/738F0", extrapolateNpcPositionForCurrentMode);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D220);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D224);

INCLUDE_ASM("asm/nonmatchings/main/738F0", npcPowerGeneratorHandleDestruction);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnDirectionalDebrisBurstAnchored);

INCLUDE_ASM("asm/nonmatchings/main/738F0", npcWakeUpdate);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D2D4);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnGatedDistanceEffectPair);

typedef struct {
    f32 unk0;
    f32 unk4;
    s16 unk8;
} RandomParticleArgs;

extern void spawnRandomScaleColoredEffectFromCaller(void *, f32, f32, s32);
extern void randomParticleWithParentNpcHandler(void);

void spawnRandomParticleWithParent(void *arg0, s32 arg1, f32 arg2, u8 arg3) {
    RandomParticleArgs args;

    if (arg0 != NULL) {
        spawnRandomScaleColoredEffectFromCaller(arg0, arg2, arg2 + arg2, 0);
    }
    if (arg3) {
        args.unk8 = arg1;
        args.unk4 = arg2;
        args.unk0 = 0.6f;
        spawnNpcOfType(randomParticleWithParentNpcHandler, &args, 4, 10);
    }
}

extern f32 vec3Length(Vec3f);
extern u8 *D_main_bss_80138D1C;

f32 distanceFromCameraToPoint(f32 *arg0) {
    Vec3f d;
    u8 *cam = D_main_bss_80138D1C + 0x28;

    d[0] = arg0[0] - *(f32 *)(cam + 0x24);
    d[1] = arg0[1] - *(f32 *)(cam + 0x28);
    d[2] = arg0[2] - *(f32 *)(cam + 0x2C);
    return vec3Length(d);
}

static __inline__ u16 spawnHeavyBurstInline(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    HeavyBurstArgs args;

    args.unk0 = arg0;
    args.unkC = 1.0f;
    if (arg9 > 0.0f) {
        args.unkC = 1.0f / arg9;
    }
    args.unk10 = arg4;
    args.unk24 = arg1;
    args.unk4 = arg2;
    args.unk8 = arg3;
    args.unk14 = arg5;
    args.unk18 = arg6;
    args.unk1C = arg7;
    args.unk20 = arg8;
    return spawnNpcOfType(heavyRandomBurstNpcHandler, &args, 1, 100);
}

u16 spawnEffectNpcWithRampedScale(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    return spawnHeavyBurstInline(arg0, arg1, arg2, arg3, 1.3333334f, 1.0f, 1.0f, 3.0f, 0.5f, arg4);
}

u16 spawnEffectNpcWithRampedScaleExt(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    HeavyBurstArgs args;

    args.unk0 = arg0;
    args.unkC = 1.0f;
    if (arg9 > 0.0f) {
        args.unkC = 1.0f / arg9;
    }
    args.unk10 = arg4;
    args.unk24 = arg1;
    args.unk14 = arg5;
    args.unk18 = arg6;
    args.unk1C = arg7;
    args.unk4 = arg2;
    args.unk8 = arg3;
    args.unk20 = arg8;
    return spawnNpcOfType(heavyRandomBurstNpcHandler, &args, 1, 100);
}

void vec3ExtrapolateFirstOrder(f32 *arg0, s32 arg1, f32 *arg2, f32 arg3) {
    arg2[0] = arg0[0] - arg0[3] * arg3;
    arg2[1] = arg0[1] - arg0[4] * arg3;
    arg2[2] = arg0[2] - arg0[5] * arg3;
}

extern void buildNpcAnchoredCameraEffectTransform(u16, void *, s32, f32);

void buildNpcAnchoredCameraEffectTransformWrapper(u16 arg0, void *arg1, f32 arg2) {
    buildNpcAnchoredCameraEffectTransform(arg0, arg1, 0, arg2);
}

typedef struct {
    s32 unk0;
    u8 pad4[0x18];
    s16 unk1C;
    s16 unk1E;
} WaterSprayArgs;

extern u8 *getNpcContextByIndex(u16);
extern u8 D_main_bss_8013A944;
extern void npcWaterSprayUpdate(void);

u16 spawnWaterSprayNpc(s32 arg0, s32 arg1) {
    WaterSprayArgs args;
    u16 id = arg0;

    if (D_main_bss_8013A944 != 0) {
        args.unk1C = id;
        args.unk0 = arg1;
        args.unk1E = 0;
        return spawnNpcOfType(npcWaterSprayUpdate, &args, 1, getNpcContextByIndex(id)[0x19] + 1);
    }
    return 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnWaterSprayDebrisAndBurst);

typedef struct {
    u8 *parent;
    s32 unk4;
    void *unk8;
    s32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
} WakeTrailArgs;

extern u8 D_main_800A0D70[];
extern void npcWakeUpdate(void);

void spawnSpeedGatedTrailEffect(s16 arg0, u8 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7, f32 arg8) {
    WakeTrailArgs args;

    if (D_main_bss_8013A944 != 0 && arg5 > 0.0f && vec3Length((f32 *)(arg1 + 0x24)) > 0.0f) {
        args.parent = arg1;
        args.unk14 = arg5;
        args.unk18 = arg3;
        args.unk2C = arg0;
        args.unkC = 0;
        args.unk1C = arg4;
        args.unk4 = arg7;
        args.unk24 = arg8;
        args.unk8 = D_main_800A0D70;
        args.unk20 = 1.0f / arg6;
        args.unk28 = 0.3f;
        args.unk10 = arg2 * 0.5f;
        spawnNpcOfType(npcWakeUpdate, &args, 2, 15);
    }
}

void forwardToNpcGeneratorSpawn(u16 arg0, s32 arg1, f32 arg2) {
    Vec3f out;

    buildNpcAnchoredCameraEffectTransform(arg0, out, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/main/738F0", func_main_80077AF0);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D448);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D454);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnDebrisBurstFromTemplate);

typedef struct {
    u8 pad0[0x6C];
    s32 health[8];
    u8 pad8C_[0x8C - 0x6C - 0x20];
} NpcDefHealth;

extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern s32 D_main_bss_80137CE4;

void initSpawnedNpcHealthAndDetail(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    s32 i;

    *(u8 *)(npc + 0x125) = 0;
    for (i = 0; i < 8; i++) {
        ((s32 *)(npc + 0xD4))[i] = D_main_bss_80137CE4[(*(NpcDefHealth **)(npc + 0x68))->health];
    }
    setNpcHealth(*(s32 *)(npc + 0x6C), (*(NpcDefHealth **)(npc + 0x68))->health, *(NpcDefHealth **)(npc + 0x68));
    setObjectDetailLevel(*(s32 *)(npc + 0x6C), *(s32 *)(*(u8 **)(npc + 0x68) + 0x8C));
}

INCLUDE_ASM("asm/nonmatchings/main/738F0", fake_func_80079278);
