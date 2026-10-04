#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/61290", randomlyScaledEffectNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/61290", randomlyScaledColoredEffectNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/61290", minimalRandomNpcHandler);

extern u8 D_main_bss_80130B63;
extern u8 D_main_bss_80139870[];
extern u8 D_main_bss_80139898[];
extern u8 D_main_bss_80139900[];
extern u8 D_main_bss_80139910[];
extern u8 D_main_bss_8013990C[];
extern u8 D_main_bss_801398C0[16][4];
extern u8 D_main_bss_80139920[16][4];
extern s32 gCurrentLevel;
extern s32 isCraftAvailableByIdx(s32);
extern void loadAssetAndIterateSubchunks(char *, char *, u8 *, s32, s32);
extern u8 *load_asset(char *);
extern void rs_free(void *);

void loadExplosionTextures(void) {
    u8 *pal;
    s32 i;
    s8 alpha;
    u8 t;

    if (D_main_bss_80130B63 == 0) {
        loadAssetAndIterateSubchunks("explo2_IMGS", "explo_tex", D_main_bss_80139870, 0, isCraftAvailableByIdx(5) ? 0 : 3);
    } else {
        loadAssetAndIterateSubchunks("explo2_IMGS", "explo_tex", D_main_bss_80139870, 0, 0);
        loadAssetAndIterateSubchunks("explo2hi_IMGS", "explh_tex", D_main_bss_80139898, 0, 0);
    }
    loadAssetAndIterateSubchunks("ionexp_IMGS", "iexplo_tx", D_main_bss_80139900, 0, 0);
    loadAssetAndIterateSubchunks("ionex2_IMGS", "iexpl2_tx", D_main_bss_80139910, 0, 0);
    loadAssetAndIterateSubchunks("smkexp_IMGS", "sexplo_tx", D_main_bss_8013990C, 0, 0);
    pal = load_asset("smkexp_PAL");
    for (i = 0; i < 16; i++) {
        D_main_bss_80139920[i][0] = pal[gCurrentLevel * 4 + 0];
        D_main_bss_80139920[i][1] = pal[gCurrentLevel * 4 + 1];
        t = pal[gCurrentLevel * 4 + 2];
        D_main_bss_80139920[i][3] = -1 - i * 16;
        D_main_bss_80139920[i][2] = t;
        D_main_bss_801398C0[i][0] = pal[gCurrentLevel * 4 + 0x80];
        D_main_bss_801398C0[i][1] = pal[gCurrentLevel * 4 + 0x81];
        t = pal[gCurrentLevel * 4 + 0x82];
        D_main_bss_801398C0[i][3] = -1 - i * 16;
                D_main_bss_801398C0[i][2] = t;
    }
    rs_free(pal);
}

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
