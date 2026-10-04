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

void spawnNpcType0xAFromTemplate(s32 arg0, f32 scale) {
    RandomScaleEffectParams params;

    params.unk0 = arg0;
    params.unk8 = scale;
    params.unkC = scale;
    spawnNpcOfType(randomlyScaledEffectNpcHandler, &params, 1, 0xA);
}

void spawnRandomScaleColoredEffectAltVariant(s32 arg0, f32 scale) {
    RandomScaleEffectParams params;

    params.unk0 = arg0;
    params.unk10 = 0;
    params.unk4 = 0;
    params.unk8 = scale * 0.4f;
    params.unkC = scale * 0.85f;
    spawnNpcOfType(randomlyScaledColoredEffectNpcHandler, &params, 1, 0xA);
}

void spawnRandomScaleColoredEffectFromCaller(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct {
        s32 unk0;
        s32 unk4;
        s32 unk8;
        s32 unkC;
        u8 unk10;
    } params;

    params.unk0 = arg0;
    params.unk8 = arg1;
    params.unkC = arg2;
    params.unk4 = arg3;
    params.unk10 = 1;
    spawnNpcOfType(randomlyScaledColoredEffectNpcHandler, &params, 1, 0xA);
}

void spawnMinimalRandomNpc(s32 arg0, s32 arg1, s32 arg2) {
    s32 params[3];

    params[0] = arg0;
    params[1] = arg1;
    params[2] = arg2;
    spawnNpcOfType(minimalRandomNpcHandler, params, 1, 0xA);
}

INCLUDE_ASM("asm/nonmatchings/main/61290", fake_func_800613B8);

INCLUDE_RODATA("asm/nonmatchings/main/61290", strLoTx);

INCLUDE_RODATA("asm/nonmatchings/main/61290", junk_8003B40C);
