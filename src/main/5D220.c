#include "common.h"
#include "common_types.h"

#include "main/5D220.h"

u8 D_main_8009ECF0[] = {
    0x20,
    0x20,
    0x10,
    0x20,
    0x10,
    0x20,
    0x20,
    0x00,
    0x30,
    0x30,
    0x50,
    0x40,
    0x30,
    0x60,
    0x20,
    0x00,
};

char *D_main_8009ED00[] = {
    "red_laser",
    "red_laser",
    "green_laser",
    "red_laser",
    "green_laser",
    "red_laser",
    "red_laser",
    NULL,
    NULL,
    NULL,
    "i_missile",
    "i_missile",
    "ion_laser",
    "ph_torp",
    "i_missile",
};

f32 D_main_8009ED3C[] ={
    0.7f,
    1.2f,
    2.0f,
    4.0f,
    0.0f,
    1.0f,
    0.0f,
};

// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
u32 data_pad_5D220[] = {
    0xC4400000,
    0xC4620000,
};

INCLUDE_ASM("asm/nonmatchings/main/5D220", checkTrackedNpcProximityForCue);

INCLUDE_ASM("asm/nonmatchings/main/5D220", audioCueDispatcherNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/5D220", collectNearbyNpcsForEffect);

INCLUDE_ASM("asm/nonmatchings/main/5D220", sprayEffectEmitterNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/5D220", dispatchCueByCategory);

INCLUDE_RODATA("asm/nonmatchings/main/5D220", D_main_8003B168);

INCLUDE_ASM("asm/nonmatchings/main/5D220", loadWeaponsHobObjects);

INCLUDE_ASM("asm/nonmatchings/main/5D220", findNpcInScaledBoxRegion);

INCLUDE_ASM("asm/nonmatchings/main/5D220", findNpcInScaledBoxRegionExcludingPair);

s32 rs_free(s32);
extern s32 D_main_bss_8013961C;
extern s32 D_main_bss_80139740;

void freeEffectAssetBuffers(void) {
    rs_free(D_main_bss_8013961C);
    rs_free(D_main_bss_80139740);
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 unk1C;
    s16 unk20;
    s32 unk24;
    u8 unk28;
    u8 unk29;
    f32 unk2C;
} ByteAnimDebrisArgs;
void byteAnimatedDebrisNpcHandler();
u16 spawnNpcOfType(void *, void *, u32, u8);
void spawnByteAnimDebrisDefault(f32 *pos) {
    ByteAnimDebrisArgs args;

    args.x = pos[0];
    args.y = pos[1] - 1.0f;
    args.z = pos[2];
    args.unk28 = 0;
    args.unk24 = D_main_bss_80139740;
    args.unk29 = 0x10;
    args.unk1C = 6.0f;
    args.unk20 = 0x300;
    args.unk2C = 20.0f;
    spawnNpcOfType(byteAnimatedDebrisNpcHandler, &args, 2, 15);
}

void spawnByteAnimDebrisWithParam(f32 *pos, u8 arg1) {
    ByteAnimDebrisArgs args;

    args.x = pos[0];
    args.y = pos[1] - 1.0f;
    args.z = pos[2];
    args.unk28 = arg1;
    args.unk24 = D_main_bss_80139740;
    args.unk29 = arg1 + 0x10;
    args.unk1C = 6.0f;
    args.unk20 = 0x300;
    args.unk2C = 20.0f;
    spawnNpcOfType(byteAnimatedDebrisNpcHandler, &args, 2, 15);
}

s16 loadAndRelocateAsset(s32 *, s32, s32);
extern s32 D_main_8003B168;
extern s16 D_main_bss_80139738;

void loadTieBomberSprite(void) {
    D_main_bss_80139738 = loadAndRelocateAsset(&D_main_8003B168, 0, 0);
}

typedef struct {
    f32 x, y, z;
} NpcRayDir;

typedef struct {
    u8 pad0[0xC];
    f32 hx, hy, hz;
} NpcRayHit;

extern NpcRayDir D_main_bss_801395A0;
extern NpcRayHit D_main_bss_801395B0;
s32 findActiveNpcInSlotChain(u16, void *);
u8 *getNpcContextByIndex(u16);
s32 findSegmentObjectSphereHit(s32, void *, void *, void *);
s32 revalidateNpcSlotIterator(void *);

s32 findNpcAlongDirectionRay(u8 *arg0, s32 arg1, f32 *arg2, u16 arg3) {
    u8 sp10[8];
    f32 x;
    f32 y;
    f32 z;
    s32 idx;
    s32 ctx;

    x = *(f32 *)(arg0 + 0x10) * 0.5f;
    D_main_bss_801395A0.x = x;
    y = *(f32 *)(arg0 + 0x14) * 0.5f;
    D_main_bss_801395A0.y = y;
    z = *(f32 *)(arg0 + 0x18) * 0.5f;
    D_main_bss_801395A0.z = z;
    if (x == 0.0f && y == 0.0f && z == 0.0f) {
        return 0;
    }
    idx = findActiveNpcInSlotChain(arg3, sp10);
    if ((idx & 0xFFFF) != 0xFFFF) {
        do {
            idx &= 0xFFFF;
            if (*(u16 *)(arg0 + 0xB6) != idx) {
                ctx = *(s32 *)(getNpcContextByIndex(idx) + 0xC);
                if (ctx != 0) {
                    if (findSegmentObjectSphereHit(ctx, arg0 + 4, &D_main_bss_801395A0, &D_main_bss_801395B0) != 0) {
                        arg2[0] = D_main_bss_801395B0.hx;
                        arg2[1] = D_main_bss_801395B0.hy;
                        arg2[2] = D_main_bss_801395B0.hz;
                        return 1;
                    }
                }
            }
            idx = revalidateNpcSlotIterator(sp10);
        } while ((idx & 0xFFFF) != 0xFFFF);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/5D220", fake_func_8005EE64);
