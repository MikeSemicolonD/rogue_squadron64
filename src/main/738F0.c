#include "common.h"
#include "common_types.h"

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

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnRandomParticleWithParent);

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

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnEffectNpcWithRampedScale);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnEffectNpcWithRampedScaleExt);

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
extern u16 spawnNpcOfType(void *, void *, u32, u8);
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

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnSpeedGatedTrailEffect);

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
