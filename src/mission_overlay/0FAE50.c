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

extern s8 D_main_bss_80130B14;
extern u8 D_mission_overlay_8010C9F0;
void requestSpeechResponseMode2(void) {
    if ((D_mission_overlay_8010C9F0 == 0) && (isSpeechBusyOrQueued() != 0)) {
        D_main_bss_80130B14 = 2;
        D_mission_overlay_8010C9E0 |= 1;
        D_mission_overlay_8010C9F0 += 1;
    }
}

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

void rs_memset(void *, s32, s32);
void broadcastSceneEventWithPayload(void *, f32);
extern f32 D_mission_overlay_8010C9EC;
extern s32 D_mission_overlay_8010CA1C;

void func_mission_overlay_800FBBA8(f32 arg0) {
    u8 payload[4];

    rs_memset(payload, 0, 4);
    payload[3] = 0xFF;
    if (D_mission_overlay_8010C9EC > 0.5f && D_mission_overlay_8010C9EC - arg0 <= 0.5f) {
        broadcastSceneEventWithPayload(payload, 2.0f);
    }
    D_mission_overlay_8010C9EC -= arg0;
    if (D_mission_overlay_8010C9EC < 0.0f) {
        D_mission_overlay_8010CA1C |= 0x40;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", func_mission_overlay_800FBC4C);

typedef struct {
    u8 pad0[0x1A];
    u16 mask;
    u8 pad1C[8];
} MissionObjectiveDef;

void playSimpleAudioCmd(s32, s32, s32);
extern MissionObjectiveDef D_mission_overlay_8010BE18[];
extern u16 D_mission_overlay_8010BFA8[];
extern f32 D_mission_overlay_8010C9EC;

s32 clearMissionObjectiveFlagsAndEnterPhaseSix(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        D_mission_overlay_8010BFA8[i] &= ~D_mission_overlay_8010BE18[i].mask;
    }
    if (D_mission_overlay_8010CA20 != 6) {
        D_mission_overlay_8010CA20 = 6;
        playSimpleAudioCmd(0, 0x3E8, 0xFF);
        D_mission_overlay_8010C9EC = 1.1f;
    }
    return 1;
}

void stopAllMusicWithFade(f32);

s32 advanceMissionObjectiveStageWhenModeOne(void) {
    if (D_mission_overlay_8010CA20 == 1) {
        stopAllMusicWithFade(0.75f);
        D_mission_overlay_8010C9F0 += 1;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", fake_func_800FBE14);

__asm__(".section .rodata\n.word 0x3C018005\n.word 0xC420FED0\n.section .text");
