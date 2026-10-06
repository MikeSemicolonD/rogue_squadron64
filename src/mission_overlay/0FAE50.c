#include "common.h"
#include "common_types.h"

#include "mission_overlay/0FAE50.h"

typedef struct {
    u8 currentLevel; u8 vehicleId; u8 unk02; u8 pad3[9]; u32 flags0; u32 flags1;
} Fa250Settings;
extern Fa250Settings gGS250 __asm__("gGameSettings");
extern u32 gLevel250 __asm__("gCurrentLevel");
extern struct { u8 pad[0x16]; s16 unk16; } gBootConfig;
extern s32 gObjectiveCounts[0x80];
extern u8 gObjectiveBooleans[0x80];
extern f32 gObjectiveTimers[8];
typedef struct {
    u32 completion_time; u32 shots_fired; u32 shots_landed; u16 enemies_destroyed; u8 friendlies_saved; u8 bonus_collected;
} Fa250Stats;
void setRngSeed(s32);
void initNpcSlotList(void);
void allocNpcContextArrays(void);
void allocAllInitialNpcSlots(void);
void initNpcBookkeepingTables(void);
void setMissionLevelInitByte(s32);
void allocAnimationPhasePool(s32);
void resetTextureAnimSlots(void);
void loadSndFiles(void);
void reset_model_animations(void);
void resetObjectContextPool(void);
void initializeObjectiveHandles(void);
void allocAndInitParticlePool(void);
void clearTrackedNpcSlots(void);
void selectRenderPresetByIndex(s32);
void selectSecondaryPresetByIndex(s32);
void loadGameOrFrontTxtFile(char *);
void initVoiceSubtitleSystem(void);
void setSubtitleOverlayScreenPos(s32, s32);
void initPlayerMissionStateFromSettings(void);
void gatherActiveUnlockFlags(void);
void rs_memset(void *, s32, s32);
void initPlayerStructs(void);
void initAllPlayersHudTracking(void);
void resetSceneNodeShakeStateArray(void);
void initPlayerVehicleStateTables(void);
void initTransformNodeFromVectors(u8 *, void *, void *);
void loadWeaponsHobObjects(void);
s32 getLevelExpansionMemoryBudget(void);
void loadLevelAssets(s32);
void cutsceneActorNpcHandler(void);
s16 spawnNpcOfType(void *, s32, s32, s32);
void choosePlayerCraftAssets(s32 *);
void spawnHudNpc(void);
void initSpeechSubsystem(s32, u8);
void initAudioListenerFromCamera(void);
void initLevelMusicBank(void);
void preloadSceneSongsWrapper(void);
void playSimpleAudioCmd(s32, s32, s32);
void broadcastSceneShutdownAndCleanup(void);

void initializeObjectiveTracking(void);
void initWaterSprayEffectAndSfx(void);
void loadLevelTextureCache(s32);
extern s32 D_mission_overlay_8010CA1C;
extern s32 D_mission_overlay_8010C9E8;
extern s32 D_mission_overlay_8010C9E4;
extern s32 D_main_bss_80137CE4;
extern u8 D_main_bss_80137CF4;
extern u8 D_main_bss_80138890;
extern u8 D_main_bss_80138925;
extern u8 D_main_bss_80138838;
extern u8 D_main_bss_80138839;
extern u8 D_main_bss_80138927;
extern u8 D_main_bss_80138924;
extern s32 D_main_bss_80138D10;
extern s32 D_main_bss_8013889C;
extern s16 D_main_bss_80130BA2;
extern u8 gVecs250[] __asm__("D_main_8009EC10");
extern u8 D_main_bss_80130B62;
extern f32 D_main_bss_80130BA4;
typedef struct { u16 unk0; u16 unk2; u16 unk4; u8 pad6[0x18]; u16 unk1E; u16 pad20; u16 unk22; } Fa250Hud;
extern Fa250Hud gHud250[] __asm__("D_mission_overlay_8010BE18");
extern u16 D_mission_overlay_8010BFA8[];
typedef struct { u8 b[0x2A0]; } Fa250Mat;
typedef struct { u16 unk0; u16 unk2; u8 pad4[0x70]; void *unk74; u8 pad78[0x5D0 - 0x78]; } Fa250Cam;
typedef struct { u8 unk0; u8 pad[0x143]; } Fa250Pl;
extern Fa250Mat D_main_bss_8013800C[];
extern Fa250Cam D_main_bss_80138268[];
extern Fa250Pl D_main_bss_80138D18[];
extern Fa250Stats missionStatsS __asm__("missionStats");
void func_mission_overlay_800FA250(void) {
    s32 pad[20];
    s32 craft[2];
    s32 i;
    u16 v;

    if (gGS250.flags1 & 0x60) {
        setRngSeed(1);
    }
    initNpcSlotList();
    allocNpcContextArrays();
    allocAllInitialNpcSlots();
    initNpcBookkeepingTables();
    setMissionLevelInitByte(1);
    allocAnimationPhasePool(0x10);
    resetTextureAnimSlots();
    loadSndFiles();
    reset_model_animations();
    resetObjectContextPool();
    initializeObjectiveHandles();
    allocAndInitParticlePool();
    clearTrackedNpcSlots();
    selectRenderPresetByIndex(1);
    if (gBootConfig.unk16 >= 0x11) {
        selectRenderPresetByIndex(0);
        selectSecondaryPresetByIndex(0);
    }
    loadGameOrFrontTxtFile("game_TXT");
    initVoiceSubtitleSystem();
    setSubtitleOverlayScreenPos(gGS250.vehicleId == 4 ? 0 : 0x24, -0xA);
    D_mission_overlay_8010CA20 = 0;
    D_mission_overlay_8010CA1C = 0;
    D_mission_overlay_8010C9E0 = 0;
    D_mission_overlay_8010C9E8 = 0;
    D_main_bss_80137CE4 = gGS250.unk02;
    gLevel250 = gGS250.currentLevel;
    initPlayerMissionStateFromSettings();
    gatherActiveUnlockFlags();
    if (gLevel250 == 0xA) {
        D_mission_overlay_8010CA1C |= 0x200;
    }
    if (gLevel250 == 0x14) {
        D_mission_overlay_8010CA1C |= 0x800;
    }
    if (gGS250.flags0 & 8) {
        D_mission_overlay_8010CA1C &= ~0x80;
    } else {
        D_mission_overlay_8010CA1C |= 0x80;
    }
    D_main_bss_80137CF4 = 0;
    D_main_bss_80138890 = 0;
    D_main_bss_80138925 = 0;
    D_main_bss_80138838 = 0;
    D_main_bss_80138839 = 0;
    D_main_bss_80138927 = 0;
    D_main_bss_80138924 = 0;
    D_main_bss_80138D10 = 0;
    D_main_bss_8013889C = 0;
    rs_memset(gObjectiveCounts, 0, 0x200);
    rs_memset(gObjectiveBooleans, 0, 0x80);
    initPlayerStructs();
    initAllPlayersHudTracking();
    for (i = 0; i < 1; i++) {
        D_mission_overlay_8010BFA8[i] |= gHud250[i].unk0;
        D_mission_overlay_8010BFA8[i] |= gHud250[i].unk4;
        D_mission_overlay_8010BFA8[i] |= gHud250[i].unk2;
        D_mission_overlay_8010BFA8[i] |= gHud250[i].unk1E;
        if (gGS250.vehicleId != 1) {
            D_mission_overlay_8010BFA8[i] |= gHud250[i].unk22;
        }
    }
    resetSceneNodeShakeStateArray();
    initPlayerVehicleStateTables();
    for (i = 0; i < 1; i++) {
        if (D_main_bss_80138D18[i].unk0 != 0) {
            D_main_bss_80138268[i].unk0 &= 0xFFFE;
            D_main_bss_80138268[i].unk74 = &D_main_bss_8013800C[i];
            initTransformNodeFromVectors((u8 *)&D_main_bss_80138268[i], gVecs250 + 0x34, gVecs250 + 0x34);
            D_main_bss_80138268[i].unk2 = 2;
        }
    }
    loadWeaponsHobObjects();
    loadLevelAssets(getLevelExpansionMemoryBudget());
    D_main_bss_80130BA2 = spawnNpcOfType(cutsceneActorNpcHandler, 0, 4, 0x64);
    i = 0;
    do {
        craft[i] = gGS250.vehicleId;
    } while (--i >= 0);
    choosePlayerCraftAssets(craft);
    spawnHudNpc();
    initSpeechSubsystem(0, D_main_bss_80130B62);
    initAudioListenerFromCamera();
    initLevelMusicBank();
    preloadSceneSongsWrapper();
    playSimpleAudioCmd(0x7A, 0x3E8, 0xFE);
    D_main_bss_80130BA4 = 0.0f;
    D_mission_overlay_8010C9E4 = 0;
    i = 7;
    do {
        gObjectiveTimers[i] = 0.0f;
    } while (--i >= 0);
    missionStatsS.completion_time = 0;
    missionStatsS.shots_fired = 0;
    missionStatsS.shots_landed = 0;
    missionStatsS.enemies_destroyed = 0;
    missionStatsS.friendlies_saved = 0;
    missionStatsS.bonus_collected = 0;
    broadcastSceneShutdownAndCleanup();
    getLevelDatItemByName("player_StartPosition");
    initializeObjectiveTracking();
    initWaterSprayEffectAndSfx();
    if (gLevel250 != 0xA) {
        loadLevelTextureCache(0x1000);
    }
}

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

extern f32 D_mission_overlay_8010C9EC;
extern u8 D_mission_overlay_8010C9F0;
extern u8 D_mission_overlay_8010CA18;
extern struct { u8 pad0[0x10]; u32 f10; u32 pad14; u32 f18; } gGameSettings;
extern u8 gMissionState[];
extern u32 gCurrentLevel;
extern u32 D_mission_overlay_8010C9E0;
extern s8 D_main_bss_80130B14;
void resetSecondaryWeaponCount(void);
void stageSoundCueRequestByIdAndParam(s32, s32, s32, s32);

s32 requestMissionTransitionMode(s32 arg0) {
    u8 *p;
    s8 t;

    if (D_mission_overlay_8010CA20 != 0) {
        return 0;
    }
    if (arg0 == 3) {
        D_mission_overlay_8010CA20 = 3;
        goto done;
    }
    if (arg0 == 2) {
        D_mission_overlay_8010CA20 = 4;
        goto done;
    }
    if (gGameSettings.f10 & 0x20) {
        D_mission_overlay_8010C9E0 |= 1;
        D_main_bss_80130B14 = 4;
        return 1;
    }
    resetSecondaryWeaponCount();
    if (gCurrentLevel == 0x10) {
        D_mission_overlay_8010C9E0 |= 4;
        return 1;
    }
    if (gGameSettings.f18 & 0x400000) {
        gMissionState[D_mission_overlay_8010CA18] += 1;
    }
    t = gMissionState[D_mission_overlay_8010CA18] - 1;
    gMissionState[D_mission_overlay_8010CA18] = t;
    if (t == 0) {
        gMissionState[4] = 3;
        D_mission_overlay_8010C9E0 |= 1;
        goto done;
    }
    stageSoundCueRequestByIdAndParam(0x1D, 0x37, 0, 1);
    D_mission_overlay_8010CA20 = 1;
done:
    D_mission_overlay_8010C9F0 = 0;
    D_mission_overlay_8010C9EC = 0.0f;
    return 1;
}

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

extern s32 D_main_bss_80137F3C;
extern u8 D_main_bss_80130B41;
extern struct {
    u8 pad0[0x180];
    u32 f180;
} D_main_bss_80137DBC;
void resetTransientPlayerStateFlags(u32);
void loadPlayerStartPosition(void *, void *);
void deactivateEffectObject(s32);
void disableScreenColorOverlay(void);

s32 tickMissionTransitionAndTeardown(void) {
    s8 t;
    u32 flags;
    u32 mode;
    s32 x;
    Bss80138D20 *p;

    if (D_main_bss_80137F3C & 0x380000) {
        t = gMissionState[D_mission_overlay_8010CA18] - 1;
        gMissionState[D_mission_overlay_8010CA18] = t;
        if (t == 0) {
            gMissionState[4] = 3;
            D_mission_overlay_8010C9E0 |= 1;
            return 1;
        }
    }
    flags = D_mission_overlay_8010C9E0;
    if (flags & 0xC) {
        mode = 3;
        if (flags & 4) {
            mode = 4;
        }
        D_mission_overlay_8010CA20 = mode;
{ s32 y = flags; y &= ~4; D_mission_overlay_8010C9E0 = y & ~8; }
        D_mission_overlay_8010C9F0 = 0;
        D_mission_overlay_8010C9EC = 0.0f;
        return 1;
    }
    D_mission_overlay_8010CA1C &= ~8;
    resetTransientPlayerStateFlags(flags);
    despawnCraftAnimationSlotNpcs(0);
    loadPlayerStartPosition(&D_main_bss_80137DBC, (u8 *)&D_main_bss_80137DBC + 4);
    deactivateEffectObject(0);
    p = &D_main_bss_80138D20;
    setGridLayerScrollX(1.0f);
    p->f14 = getBootConfigField14() & 0xFFFF;
    p->f20 = 65.0f;
    disableScreenColorOverlay();
    x = 0;
    if (D_main_bss_80130B41 != 4) {
        x = 0x24;
    }
    setSubtitleOverlayScreenPos(x, -10);
    D_mission_overlay_8010CA20 = 0;
    D_mission_overlay_8010C9F0 = 0;
    { s32 y = D_mission_overlay_8010CA1C & ~4; D_mission_overlay_8010CA1C = y & ~0x100; }
    D_mission_overlay_8010C9EC = 0.0f;
    D_mission_overlay_8010C9E8 = 3;
    buildGridCellAdjacencyTable();
    releaseFlaggedMeshInstanceMeshes(0);
    if (D_main_bss_80137DBC.f180 & 0x780000) {
        resetSecondaryWeaponCount();
        D_mission_overlay_8010CA20 = 1;
        D_mission_overlay_8010C9F0 = 1;
        D_mission_overlay_8010C9EC = 0.0f;
        D_mission_overlay_8010C9E0 &= ~2;
    }
    return 1;
}

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
