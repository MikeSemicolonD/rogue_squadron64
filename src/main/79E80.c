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

void heavyMechSubEffectNpcHandler();
u16 spawnNpcOfType(void *, void *, u32, u8);
typedef struct {
    u16 unk0;
    s32 unk4;
} HeavyMechSubEffectArgs;
u16 spawnHeavyMechSubEffect(HeavyMechSubEffectArgs *args, u8 *parent, s32 arg2) {
    args->unk0 = *(u16 *)(parent + 0x16);
    args->unk4 = arg2;
    return spawnNpcOfType(heavyMechSubEffectNpcHandler, args, 2, parent[0x19] + 1);
}

INCLUDE_ASM("asm/nonmatchings/main/79E80", setRandomFacingDirection);

INCLUDE_ASM("asm/nonmatchings/main/79E80", fake_func_80079CD8);
