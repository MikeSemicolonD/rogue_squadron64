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

INCLUDE_ASM("asm/nonmatchings/main/79E80", spawnHeavyMechSubEffect);

INCLUDE_ASM("asm/nonmatchings/main/79E80", setRandomFacingDirection);

INCLUDE_ASM("asm/nonmatchings/main/79E80", fake_func_80079CD8);
