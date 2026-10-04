#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/61290", randomlyScaledEffectNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/61290", randomlyScaledColoredEffectNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/61290", minimalRandomNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/61290", loadExplosionTextures);

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
} RandomScaleEffectParams;

u16 spawnNpcOfType(void *handler, void *params, u32 arg2, u8 arg3);
void randomlyScaledEffectNpcHandler(void);
void randomlyScaledColoredEffectNpcHandler(void);
void minimalRandomNpcHandler(void);

void spawnRandomScaleEffectDefault(s32 arg0) {
    RandomScaleEffectParams params;

    params.unk0 = arg0;
    params.unk8 = 1.0f;
    spawnNpcOfType(randomlyScaledEffectNpcHandler, &params, 1, 0xA);
}

INCLUDE_ASM("asm/nonmatchings/main/61290", spawnNpcType0xAFromTemplate);

INCLUDE_ASM("asm/nonmatchings/main/61290", spawnRandomScaleColoredEffectAltVariant);

INCLUDE_ASM("asm/nonmatchings/main/61290", spawnRandomScaleColoredEffectFromCaller);

INCLUDE_ASM("asm/nonmatchings/main/61290", spawnMinimalRandomNpc);

INCLUDE_ASM("asm/nonmatchings/main/61290", fake_func_800613B8);

INCLUDE_RODATA("asm/nonmatchings/main/61290", strLoTx);

INCLUDE_RODATA("asm/nonmatchings/main/61290", junk_8003B40C);
