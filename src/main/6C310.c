#include "common.h"
#include "common_types.h"

#include "player.h"

#include "main/6C310.h"

// Interim BSS externs
extern u16 D_main_bss_8013A528[14];

INCLUDE_ASM("asm/nonmatchings/main/6C310", loadCraftShadowTextures);

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

INCLUDE_ASM("asm/nonmatchings/main/6C310", spawnStubMarkerNpc);

INCLUDE_ASM("asm/nonmatchings/main/6C310", load_naboo_starfighter);

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
