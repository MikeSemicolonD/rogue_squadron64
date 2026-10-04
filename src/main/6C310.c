#include "common.h"
#include "common_types.h"

#include "player.h"

#include "main/6C310.h"

// Interim BSS externs
extern u16 D_main_bss_8013A528[14];

#include "textures.h"
#include "main/1EE30.h"
#include "main/55AF0.h"
#include "main/64EA0.h"
extern char D_main_8003C960[];
void rs_free(void *);

void loadCraftShadowTextures(s32 arg0) {
    struct material_entry sp10;
    struct full_image_header *temp_s4;
    struct full_image_header *var_s1;
    s32 var_s2;
    s32 var_v1;

    var_s2 = arg0;
    if (D_main_bss_8013A528[var_s2] == 0xFFFF) {
        temp_s4 = load_asset(D_main_8003C960);
        do {
loop_2:
            var_s1 = temp_s4;
            for (var_v1 = 0; var_v1 < var_s2; var_v1++) {
                var_s1 = (struct full_image_header *)(((u32)var_s1 + var_s1->image_size + 7) & ~3);
            }
            full_header_image_offset_convert(&var_s1->ent, (u32)&var_s1->ent);
            var_s1->ent.flags_type |= 0x2000;
            sp10.material_type = 1;
            sp10.material_name[0] = 0;
            D_main_bss_8013A528[var_s2] = registerHmtTextureInTable(&sp10, &var_s1->ent, 1U);
            var_s2 = 9;
            if (D_main_bss_8013A528[9] == 0xFFFF) {
                goto loop_2;
            }
            var_s2 = 0xA;
            if (D_main_bss_8013A528[0xA] == 0xFFFF) {
                goto loop_2;
            }
            var_s2 = 0xB;
            if (D_main_bss_8013A528[0xB] == 0xFFFF) {
                goto loop_2;
            }
            var_s2 = 0xC;
        } while (D_main_bss_8013A528[0xC] == 0xFFFF);
        rs_free(temp_s4);
    }
}

INCLUDE_ASM("asm/nonmatchings/main/6C310", applyCentripetalBankingToNpcCorners);

INCLUDE_ASM("asm/nonmatchings/main/6C310", allocateAndInitCraftNpcContext);

INCLUDE_ASM("asm/nonmatchings/main/6C310", advanceNpcOnCurvedPath);

INCLUDE_ASM("asm/nonmatchings/main/6C310", splineWalkerCraftNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/6C310", stubNpcHandler);

void clearTrackedNpcSlots(void) {
    s32 i;
    u16 v = 0xFFFF;

    for (i = 13; i >= 0; i--) {
        D_main_bss_8013A528[i] = v;
    }
}

void splineWalkerCraftNpcHandler();
u16 spawnNpcOfType(void *, void *, u32, u8);
typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s16 d;
} SplineWalkerSpawnArgs;
void spawnSplineWalkerCraft(s32 arg0, s32 arg1, s32 arg2, s16 arg3) {
    SplineWalkerSpawnArgs args;

    args.a = arg0;
    args.b = arg1;
    args.c = arg2;
    args.d = arg3;
    spawnNpcOfType(splineWalkerCraftNpcHandler, &args, 1, 10);
}

void stubNpcHandler();
typedef struct {
    f32 x;
    f32 y;
    s32 a;
    s32 b;
    s16 c;
} StubMarkerArgs;
u16 spawnStubMarkerNpc(f32 x, f32 y, s32 a, s32 b, s16 c) {
    StubMarkerArgs args;

    args.a = a;
    args.b = b;
    args.x = x;
    args.y = y;
    args.c = c;
    return spawnNpcOfType(stubNpcHandler, &args, 1, 10);
}

extern u32 get_asset_size_extra(s32, char *);
extern s32 findAssetAcrossSegments(s32, s32, s32, char *, s32);
extern void setupAssetDma(s32, s32, s32, s32, u32, void *);
extern void teardownAssetDma(s32, s32);
extern char D_main_8003C9B0[];
extern s32 D_main_bss_80137CFC;
extern s32 D_main_bss_80138920;

u32 load_naboo_starfighter(u32 arg0) {
    u32 buf;
    u32 size;
    u32 off;
    u32 ret;
    u32 v;
    s32 idx;
    u16 count;
    u16 i;
    u32 *q;

    size = get_asset_size_extra(D_main_bss_80137CFC, D_main_8003C9B0);
    buf = (u32)rs_malloc(size, 0);
    idx = findAssetAcrossSegments(D_main_bss_80138920, 0, D_main_bss_80137CFC, D_main_8003C9B0, 0);
    setupAssetDma(D_main_bss_80138920, 0, idx, 0, size, (void *)buf);
    teardownAssetDma(D_main_bss_80138920, idx);
    decrypt_ns_hmt((u8 *)buf, size, arg0);
    off = *(u32 *)(buf + 4);
    ret = 0;
    if (size >= off && (off & 3) == 0) {
        count = *(u16 *)(buf + off);
        if (count < 0x29) {
            i = 0;
            for (; i < count; i++, off += 0x34) {
                if (off >= size) {
                    break;
                }
                q = (u32 *)(off + buf) + 1;
                v = *q;
                if (v == 0 || (v & 3) != 0 || v > size) {
                    break;
                }
                v = q[9];
                if (v == 0 || (v & 3) != 0 || v > size) {
                    break;
                }
            }
            if (i == count) {
                ret = arg0;
            }
        }
    }
    rs_free((void *)buf);
    return ret;
}

#if 0
void *getCraftRecordByIdx(s32 arg0) {
    return &gPlayers[arg0].inner.posX; // While this matches its obviously wrong, there's another struct inside player.inner (most likely)
}
#else
extern u8 D_main_bss_80137DBC[][0x2A0];
void *getCraftRecordByIdx(s32 i) {
    u8 *p = D_main_bss_80137DBC[i];
    return p + 4;
}
#endif

void *getPlayerCraftRecordByIdx(s32 i) {
    u8 *p = D_main_bss_80137DBC[i];
    return p + 4;
}

enum PlayerCraft getPlayerVehicleId(s32 playerId) {
    return gPlayers[playerId].inner.vehicleId;
}

void *getPlayerRecordTargetBuffer(s32 i) {
    u8 *p = D_main_bss_80137DBC[i];
    return p + 0x34;
}

u16 getPlayerField2(s32 arg0) {
    return gPlayers[arg0].unk002;
}

INCLUDE_ASM("asm/nonmatchings/main/6C310", attachDebrisModelVariant);

INCLUDE_ASM("asm/nonmatchings/main/6C310", updateDestructionDebrisNpc);

INCLUDE_ASM("asm/nonmatchings/main/6C310", fake_func_8006D8FC);
