#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/79E80", heavyMechSubEffectNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/79E80", concatChildTransformAlongChain);

s32 initWaterSprayParticles();
s32 loadSfxAsset();

void initWaterSprayEffectAndSfx(void) {
    loadSfxAsset();
    initWaterSprayParticles();
}

INCLUDE_ASM("asm/nonmatchings/main/79E80", spawnNpcWithRandomRotation);

extern u16 spawnNpcOfType(void *, void *, u32, u8);
extern void heavyMechSubEffectNpcHandler(void);

u16 spawnHeavyMechSubEffect(u8 *args, u8 *parent, s32 arg2) {
    *(u16 *)args = *(u16 *)(parent + 0x16);
    *(s32 *)(args + 4) = arg2;
    return spawnNpcOfType(heavyMechSubEffectNpcHandler, args, 2, parent[0x19] + 1);
}

INCLUDE_ASM("asm/nonmatchings/main/79E80", setRandomFacingDirection);

INCLUDE_ASM("asm/nonmatchings/main/79E80", fake_func_80079CD8);
