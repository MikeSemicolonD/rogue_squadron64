#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/79E80", heavyMechSubEffectNpcHandler);

extern void mat3x4Multiply(void *, void *, void *);
extern void zmemcpy(void *, void *, s32);

void concatChildTransformAlongChain(u8 *node, u8 *arg1) {
    u8 *out = arg1;
    u8 buf[2][0x30];
    s32 n = 0;
    u8 *src;
    u8 *dst;

    if (*(u8 **)(node + 8) == NULL) {
        zmemcpy(arg1, node + 0x1C, 0x30);
        return;
    }
    src = node + 0x1C;
    node = *(u8 **)(node + 8);
    do {
        dst = out;
        if (*(u8 **)(node + 8) != NULL) {
            n++;
            dst = buf[n & 1];
        }
        mat3x4Multiply(node + 0x1C, src, dst);
        node = *(u8 **)(node + 8);
        src = dst;
    } while (node != NULL);
}

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
