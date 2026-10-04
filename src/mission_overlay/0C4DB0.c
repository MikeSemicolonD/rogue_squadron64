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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", lookupCraftValueByLevelKey);

extern s16 D_mission_overlay_8010C080;

void resetCraftSelectionCounter(void) {
    D_mission_overlay_8010C080 = 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", registerObjectAndResolveDatItem);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", getAvailableShipsForLevel);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", accumulateClampedFloatField);

u8 getDisplayItemStateByte(void *arg0) {
    return (*(u8 *)((u8 *)(arg0) + 0xDD0));
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", fake_func_800C64A4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C4DB0", D_mission_overlay_800A6870);
