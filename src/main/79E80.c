#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/79E80", heavyMechSubEffectNpcHandler);

void zmemcpy(void *, void *, u32);
void mat3x4Multiply(void *, void *, void *);
typedef struct TransformChainNode {
    u8 pad0[8];
    struct TransformChainNode *child;
    u8 padC[0x10];
    f32 mtx[12];
} TransformChainNode;
void concatChildTransformAlongChain(TransformChainNode *node, f32 *arg1) {
    f32 *out = arg1;
    f32 tmp[2][12];
    s32 n = 0;
    f32 *src;
    f32 *dst;

    if (node->child == NULL) {
        zmemcpy(out, node->mtx, 0x30);
        return;
    }
    src = node->mtx;
    node = node->child;
    do {
        dst = out;
        if (node->child != NULL) {
            n++;
            dst = tmp[n & 1];
        }
        mat3x4Multiply(node->mtx, src, dst);
        node = node->child;
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
