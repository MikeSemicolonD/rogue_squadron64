#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", plotRadarBlipColumn);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", plotRadarBlipRow);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", initializeRadar);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", updateCraftSelectAnimState);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", placeRadarDots);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", findClosestRadarContactAndSetSweep);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", renderRadarSweep);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", renderRadarMinimap);

extern u8 D_mission_overlay_80109FE4[];
extern u16 D_mission_overlay_8010BFF0[];
u16 lookupCraftValueByLevelKey(s32 key) {
    s32 i;

    for (i = 0; D_mission_overlay_80109FE4[i] != 0xFF; i += 2) {
        if (D_mission_overlay_80109FE4[i] == key) {
            break;
        }
    }
    if (D_mission_overlay_80109FE4[i] != 0xFF) {
        return D_mission_overlay_8010BFF0[i >> 1];
    }
    return 0;
}

extern s16 D_mission_overlay_8010C080;

void resetCraftSelectionCounter(void) {
    D_mission_overlay_8010C080 = 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", registerObjectAndResolveDatItem);

s32 findMatchingTextureRecursive(u16, void *, void *, s32);
void *getCraftRecordByIdx(s32);
s32 plotRadarBlipColumn(void *, s32);
extern void *D_mission_overlay_8010BFE0;

void getAvailableShipsForLevel(void) {
    s32 var_s0;
    void *temp_s1;
    void *temp_v0;

    temp_s1 = D_mission_overlay_8010BFE0;
    temp_v0 = getCraftRecordByIdx(0);
    (*(s16 *)((u8 *)(temp_s1) + 0x85C)) = (s16) (s32) ((*(f32 *)((u8 *)(temp_v0) + 0)) * 0.5f);
    var_s0 = -0x10;
    (*(s16 *)((u8 *)(temp_s1) + 0x85E)) = (s16) (s32) ((*(f32 *)((u8 *)(temp_v0) + 8)) * 0.5f);
    do {
        plotRadarBlipColumn(temp_s1, (*(s16 *)((u8 *)(temp_s1) + 0x85C)) + var_s0);
        var_s0 += 1;
    } while (var_s0 < 0x10);
    (*(s16 *)((u8 *)(temp_s1) + 0xDB8)) = 0;
    findMatchingTextureRecursive((*(u16 *)((u8 *)(temp_s1) + 0x858)), temp_s1 + 0x800, temp_s1 + 0x824, 0);
    (*(s16 *)((u8 *)(temp_s1) + 0xDC8)) = -1;
    (*(s32 *)((u8 *)(temp_s1) + 0xDCC)) = 0;
}

void accumulateClampedFloatField(u8 *arg0, f32 arg1) {
    if (*(f32 *)(arg0 + 0xDCC) < 1.0f) {
        *(f32 *)(arg0 + 0xDCC) += arg1;
    }
}

u8 getDisplayItemStateByte(void *arg0) {
    return (*(u8 *)((u8 *)(arg0) + 0xDD0));
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", fake_func_800C64A4);

const u32 rodata_pad_0C4DB0[3] = { 0x93C30004, 0x3C01801D, 0x00220821 };
