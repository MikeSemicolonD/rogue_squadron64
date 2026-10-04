#include "common.h"
#include "common_types.h"

#include "mission_overlay/0FAE50.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", func_mission_overlay_800FA250);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", func_mission_overlay_800FA6A4);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", flashMissionAlertObjectsAndPrint);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", beginMissionEndTransition);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", endMissionEndTransition);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", requestMissionTransitionMode);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", setupMissionTransitionScreenOverlay);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", tickMissionTransitionAndTeardown);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FAE50", D_mission_overlay_800A8FE4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FAE50", D_mission_overlay_800A8FEC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FAE50", D_mission_overlay_800A8FF0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FAE50", D_mission_overlay_800A8FFC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FAE50", D_mission_overlay_800A9004);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FAE50", D_mission_overlay_800A9010);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FAE50", D_mission_overlay_800A9018);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FAE50", D_mission_overlay_800A9020);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FAE50", D_mission_overlay_800A9028);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", choosePlayerCraftAssets);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", endMissionCleanup);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", requestSpeechResponseMode2);

s32 isSpeechBusyOrQueued();
extern s8 D_main_bss_80130B14;
extern u8 D_mission_overlay_8010C9F0;

void requestSpeechResponseMode1(void) {
    if ((D_mission_overlay_8010C9F0 == 0) && (isSpeechBusyOrQueued() != 0)) {
        D_main_bss_80130B14 = 1;
        D_mission_overlay_8010C9E0 |= 1;
        D_mission_overlay_8010C9F0 += 1;
    }
}

void func_mission_overlay_800FBBA0(void) {
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", func_mission_overlay_800FBBA8);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", func_mission_overlay_800FBC4C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", clearMissionObjectiveFlagsAndEnterPhaseSix);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", advanceMissionObjectiveStageWhenModeOne);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", fake_func_800FBE14);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FAE50", D_mission_overlay_800A90A4);
