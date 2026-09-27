#include "common.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BF800", strMissC5L2);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BF800", strMissC3L2);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BF800", strMissC3L1);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BF800", strMissC2L3);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BF800", strMissC2L1);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BF800", strMissC1L1);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", initDemoPlayState);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", applyDemoRecordedHudEvents);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", clearPlayerSlotHudTracking);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", initAllPlayersHudTracking);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BF800", D_mission_overlay_800A6214);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", tickPlayerHudIndicators);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", loadPlayerSlotHudPreset);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", countTrailingZeros16);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", func_mission_overlay_800BF358);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", func_mission_overlay_800BF3A4);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", func_mission_overlay_800BF408);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", getDemoRecordedTimestep);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BF800", fake_func_800BF498);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BF800", D_mission_overlay_800A6230);
