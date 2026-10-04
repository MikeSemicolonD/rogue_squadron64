#include "common.h"
#include "common_types.h"

#include "mission_overlay/0FAE50.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", func_mission_overlay_800FA250);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", func_mission_overlay_800FA6A4);

typedef struct {
    u8 pad0[0x1A];
    u16 mask;
    u8 pad1C[8];
} MissionObjectiveDef;

extern u8 D_main_bss_80137CF4;
extern u8 D_main_bss_80138838;
extern u8 D_main_bss_80138925;
extern u16 D_main_bss_80130B88[][3];
extern MissionObjectiveDef D_mission_overlay_8010BE18[];
extern u16 D_mission_overlay_8010BFA8[];
extern u32 D_main_bss_80130B4C;
extern char D_main_bss_80138840[];
typedef struct {
    u8 active;
    u8 pad1[0x277];
    f32 unk278;
    f32 unk27C;
    f32 unk280;
    u8 pad284[0x14];
    s32 unk298;
    s32 unk29C;
} EndMissionPlayer;

extern EndMissionPlayer gPlayers[];

void flashMissionAlertObjectsAndPrint(void) {
    s32 i;

    for (i = 0; i < 1; i++) {
        if (gPlayers[i].active != 0 && (D_main_bss_80130B88[i][0] & *(u16 *)D_mission_overlay_8010BE18[i].pad0) && D_main_bss_80137CF4 == 0 && D_main_bss_80138838 == 0) {
            gPlayers[i].unk298 = 0;
            D_mission_overlay_8010C9E0 |= 0x10;
            D_main_bss_80138925 = 1;
            gPlayers[i].unk29C = 0x1D;
            D_mission_overlay_8010BFA8[i] |= D_mission_overlay_8010BE18[i].mask;
        }
    }
    if (D_main_bss_80130B4C & 0x4000000) {
        sprintf(D_main_bss_80138840, "\nX %.3f Y %.3f Z %.3f\n", (f64)gPlayers[0].unk278, (f64)gPlayers[0].unk27C, (f64)gPlayers[0].unk280);
    }
}


s32 countDisplayListChunks(void);
void serviceRumblePakMotors(void);
void setAudioFaderRampLocked(s32, s32, s32);
void beginSpeechTimingWindow(void);
extern u32 D_mission_overlay_8010CA20;
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_8010C9F1;
extern u8 D_main_bss_80137CF4;
extern u8 D_main_bss_80138838;
extern u8 D_main_bss_80138925;
extern u8 D_main_bss_80139C8F;
extern u16 D_main_bss_80130B88[][3];
extern MissionObjectiveDef D_mission_overlay_8010BE18[];
extern u16 D_mission_overlay_8010BFA8[];


s32 beginMissionEndTransition(void) {
    s32 i;

    if (countDisplayListChunks() < 15000) {
        return 0;
    }
    if (D_mission_overlay_8010CA20 != 0) {
        return 1;
    }
    D_mission_overlay_8010CA20 = 5;
    D_main_bss_80137CF4 = 1;
    D_main_bss_80138925 = 1;
    D_mission_overlay_8010CA1C |= 1;
    D_mission_overlay_8010C9F1 = !(D_mission_overlay_8010CA1C & 0x100);
    D_mission_overlay_8010CA1C |= 0x100;
    serviceRumblePakMotors();
    setAudioFaderRampLocked(0x32, 500, 0xFD);
    setAudioFaderRampLocked(0, 500, 0xFE);
    beginSpeechTimingWindow();
    D_main_bss_80139C8F = 0;
    for (i = 0; i < 1; i++) {
        if (gPlayers[i].active != 0 && (D_main_bss_80130B88[i][0] & *(u16 *)D_mission_overlay_8010BE18[i].pad0) && D_main_bss_80137CF4 == 0 && D_main_bss_80138838 == 0) {
            gPlayers[i].unk298 = 0;
            gPlayers[i].unk29C = 0x1D;
            D_mission_overlay_8010BFA8[i] |= D_mission_overlay_8010BE18[i].mask;
        }
    }
    return 1;
}

void setAudioFaderRampLocked(s32, s32, s32);
void endSpeechTimingWindow(void);
void clearControllerPakPresence(u8);
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_8010C9F1;
extern u8 D_main_bss_80137CF4;
extern u8 D_main_bss_80138838;
extern u8 D_main_bss_80138925;
extern MissionObjectiveDef D_mission_overlay_8010BE18[];
extern u16 D_mission_overlay_8010BFA8[];
extern EndMissionPlayer gPlayers[];

s32 endMissionEndTransition(void) {
    s32 i;

    if (D_mission_overlay_8010CA20 == 5) {
        D_mission_overlay_8010CA20 = 0;
        D_mission_overlay_8010CA1C &= ~1;
        if (D_mission_overlay_8010C9F1 != 0) {
            D_mission_overlay_8010CA1C &= ~0x100;
        }
        D_main_bss_80137CF4 = 0;
        D_main_bss_80138925 = 0;
        setAudioFaderRampLocked(0x7F, 500, 0xFD);
        setAudioFaderRampLocked(0x7F, 500, 0xFE);
        endSpeechTimingWindow();
        for (i = 0; i < 1; i++) {
            if (gPlayers[i].active != 0 && D_main_bss_80137CF4 == 0 && D_main_bss_80138838 == 0) {
                D_mission_overlay_8010BFA8[i] &= ~D_mission_overlay_8010BE18[i].mask;
            }
            clearControllerPakPresence(i);
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FAE50", requestMissionTransitionMode);

typedef struct {
    u8 pad0[0x14];
    s32 f14;
    u8 pad18[8];
    f32 f20;
} Bss80138D20;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Vec3i;

void buildGridCellAdjacencyTable(void);
void despawnCraftAnimationSlotNpcs(u8);
s32 getBootConfigField12(void);
s32 getBootConfigField14(void);
void initEffectObjectFromLevelData(s32, s32);
void lookupActivePlayerCraftGridCell(void);
void releaseFlaggedMeshInstanceMeshes(s32);
void setGridLayerScrollX(f32);
void setScreenColorOverlay(s32, s32, s32, s32, s32, s32, s32, s32);
void setSubtitleOverlayScreenPos(s32, s32);
extern s32 D_main_8009EBC0;
extern s32 D_main_8009EC10;
extern Vec3i D_main_bss_801375F8;
extern Bss80138D20 D_main_bss_80138D20;
extern s32 D_mission_overlay_8010BFDC;
extern s32 D_mission_overlay_8010C9E8;
extern f32 D_mission_overlay_8010C9EC;
extern u8 D_mission_overlay_8010C9F0;

s32 setupMissionTransitionScreenOverlay(void) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    Bss80138D20 *p;
    Vec3i *temp_v0;

    if (D_mission_overlay_8010CA20 != 7 && D_mission_overlay_8010CA20 != 0) {
        return 0;
    }
    {
        if (D_main_8009EC10 != D_main_8009EBC0) {
            temp_v0 = getLevelDatItemByName(D_main_8009EC10);
            D_main_bss_801375F8 = *(Vec3i *)((u8 *)temp_v0 + 0x10);
            D_mission_overlay_8010CA1C |= 8;
            lookupActivePlayerCraftGridCell();
        }
        initEffectObjectFromLevelData(0, D_main_8009EC10);
        p = &D_main_bss_80138D20;
        setGridLayerScrollX(1.3176471f);
        p->f20 = 49.330357f;
        p->f14 = ((getBootConfigField14() & 0xFFFF) * 0xAA) / 224;
        temp_s0 = (getBootConfigField14() & 0xFFFF) - p->f14;
        temp_s0 = temp_s0 / 2;
        temp_s2 = temp_s0 + 1;
        temp_s1 = getBootConfigField12() & 0xFFFF;
        setScreenColorOverlay(0, 0, temp_s0 & 0xFFFF, temp_s1, (getBootConfigField14() - temp_s2) & 0xFFFF, 0, 0, 0);
        setSubtitleOverlayScreenPos(0, -4);
        D_mission_overlay_8010BFDC = 0;
        D_mission_overlay_8010CA20 = 7;
        D_mission_overlay_8010C9F0 = 0;
        D_mission_overlay_8010C9EC = 0.0f;
        D_mission_overlay_8010CA1C |= 0x104;
        D_mission_overlay_8010C9E8 = 3;
        buildGridCellAdjacencyTable();
        releaseFlaggedMeshInstanceMeshes(0);
        despawnCraftAnimationSlotNpcs(0);
    }
    return 1;
}

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

void stopAllMusicWithFade(f32);
void resetSpeechSubsystem(void);
void finalizeCurrentSpeechBuffer(void);
void freeSubtitleOverlay(void);
void freeEffectAssetBuffers(void);
void missionCleanupNoopHook(void);
void freeTxtFile(void);
void destroyNpcContextArrays(void);
void freeNpcBurstSpawnerTables(void);
void teardownAudioListenerNode(void);
void waitForAnyAudioSlot(void);
void freeAnimationPhasePool(void);
void freeAllHobFiles(void);
void freeNpcSlotArray(void);
void freeLevelDatBuffers(void);
void teardownAnimatedMapGridLayer(void);
void stopMusicAndResetAudio(void);
void reset_and_free_model_animations(void);
void calculateFriendliesSaved(void);
void freeAllObjectContextPoolNodes(void);
extern f32 D_main_bss_80130BA4;
extern u32 missionStats;

void endMissionCleanup(void) {
    missionStats = D_main_bss_80130BA4;
    stopAllMusicWithFade(0.8f);
    resetSpeechSubsystem();
    finalizeCurrentSpeechBuffer();
    freeSubtitleOverlay();
    freeEffectAssetBuffers();
    missionCleanupNoopHook();
    freeTxtFile();
    destroyNpcContextArrays();
    freeNpcBurstSpawnerTables();
    teardownAudioListenerNode();
    waitForAnyAudioSlot();
    freeAnimationPhasePool();
    freeAllHobFiles();
    freeNpcSlotArray();
    freeLevelDatBuffers();
    teardownAnimatedMapGridLayer();
    stopMusicAndResetAudio();
    reset_and_free_model_animations();
    calculateFriendliesSaved();
    freeAllObjectContextPoolNodes();
}

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

u16 getPlayerField2(u8);
s32 slotDispatcherIter(u16, s32, void *);
void broadcastSceneShutdownAndCleanup(void);
void func_mission_overlay_800C72E8(void);
void commitStagedSongAndPlay(void);
void dispatchSlotActionTwelveByGlobalId(void);
void resetSpeechSubsystem(void);
void clearSpeechActiveFlags(void);
extern u8 D_mission_overlay_8010CA18;

void func_mission_overlay_800FBC4C(f32 dt) {
    D_mission_overlay_8010C9EC += dt;
    if (D_mission_overlay_8010C9F0 == 0 && D_mission_overlay_8010C9EC > 7.0f) {
        D_mission_overlay_8010C9F0 = 1;
    } else if (D_mission_overlay_8010C9F0 == 1) {
        slotDispatcherIter(getPlayerField2(D_mission_overlay_8010CA18), 0xC, NULL);
        D_mission_overlay_8010C9EC = 0.0f;
        D_mission_overlay_8010C9F0 = 2;
    } else if (D_mission_overlay_8010C9F0 == 2 && D_mission_overlay_8010C9EC >= 1.0f) {
        broadcastSceneShutdownAndCleanup();
        func_mission_overlay_800C72E8();
        commitStagedSongAndPlay();
        dispatchSlotActionTwelveByGlobalId();
        resetSpeechSubsystem();
        clearSpeechActiveFlags();
        D_mission_overlay_8010CA20 = 0;
    }
}

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
