#include "common.h"
#include "common_types.h"

#include "secondary_weapons.h"
#include "crafts.h"
#include "levels.h"
#include "game_settings.h"
#include "mission_state.h"
#include "medals.h"
#include "save.h"

#include "main/08120.h"
#include "main/6E500.h"
#include "main/82E70.h"

/*BSS definitions, for when BSS mathcing is possible
u8 D_main_bss_8013A5B0;
*/


// Interim BSS externs
extern u8 D_main_bss_8013A5B0;

s32 D_main_800A0A60 = -1;

INCLUDE_ASM("asm/nonmatchings/main/6E500", runIdleFramesAndLoadSaveData);

INCLUDE_ASM("asm/nonmatchings/main/6E500", applySaveSlotToMissionState);

void loadDefaultHighScores(void) {
    s8 var_a3;

    for (var_a3 = 0; var_a3 < 10; var_a3++) {
        gSaveDataBody.highscores[var_a3].name[0] = defaultHighscoreNames[var_a3][0];
        gSaveDataBody.highscores[var_a3].name[1] = defaultHighscoreNames[var_a3][1];
        gSaveDataBody.highscores[var_a3].name[2] = defaultHighscoreNames[var_a3][2];
        gSaveDataBody.highscores[var_a3].medals.as_short = 9 - var_a3;
        gSaveDataBody.highscores[var_a3].current_level = 9 - var_a3;
    }
}

// The placement of this array is EXTERMELY precise
// The short story is that, seemingly, the pointers of this array end up in the .text
// section of the output, even though small .data has (ostensibly) disabled via -G0
char *defaultHighscoreNames[0xA] = { "FLO", "HOL", "TOM", "JUE", "THG", "SIR", "MAR", "BST", "RFH", "CHR" };

void highScoreBubbleSort(u8 arg0) {
    u8 medalCounts[3];
    struct EliteRogueData temp_account_data;
    s32 var_a2;
    s32 var_s1;
    s32 var_s3;
    s32 medals;

    gGameSettings.unk24 = 0;
    medalCounts[2] = 0;
    medalCounts[1] = 0;
    medalCounts[0] = 0;
    for (var_s3 = 0; var_s3 < NUM_LEVELS; var_s3++) {
        if (gMissionState.medalPerLevel[var_s3] == MEDAL_NONE) continue;
        medalCounts[gMissionState.medalPerLevel[var_s3] - 1]++;
    }
    medals = (medalCounts[0] | (medalCounts[1] << 5) | (medalCounts[2] << 10));

    var_a2 = -1;
    for (var_s3 = 0; var_s3 < 10; var_s3++) {
        if (gSaveDataBody.highscores[var_s3].accountNumber == gMissionState.accountNumber) {
            var_a2 = var_s3;
            break;
        }
    }

    if (var_a2 != -1) {
        setAccountHighscore(var_a2, medalCounts[0] | (medalCounts[1] << 5) | (medalCounts[2] << 10), arg0);
    } else {
        for (var_s3 = 0; var_s3 < 10; var_s3++) {
            if (medals < getAccountHighscore(var_s3)) continue;
            for (var_s1 = 8; var_s1 >= var_s3; var_s1--) {
                gSaveDataBody.highscores[var_s1 + 1] = gSaveDataBody.highscores[var_s1];
            }
            setAccountHighscore(var_s3, medalCounts[0] | (medalCounts[1] << 5) | (medalCounts[2] << 10), arg0);
            break;
        }
    }

    for (var_s3 = 0; var_s3 < 10; var_s3++) {
        for (var_s1 = var_s3 + 1; var_s1 < 10; var_s1++) {
            if (getAccountHighscore(var_s3) < getAccountHighscore(var_s1)) {
                temp_account_data = gSaveDataBody.highscores[var_s3];
                gSaveDataBody.highscores[var_s3] = gSaveDataBody.highscores[var_s1];
                gSaveDataBody.highscores[var_s1] = temp_account_data;
            }
        }
    }

    gGameSettings.unk24 = 0;
    for (var_s3 = 0; var_s3 < 10; var_s3++) {
        if (gSaveDataBody.highscores[var_s3].accountNumber == gMissionState.accountNumber) {
            gGameSettings.unk24 = var_s3 + 1;
            break;
        }
    }
}

#if 0
// Mostly matches, but there's some really dumb register allocation nonsense going on
void applyAccountUnlocksToSettings(void) {
    u8 var_s0;
    u8 var_s1;

    gGameSettings.unlockAndSettingsFlags[1] = gSaveDataBody.unk00;
    for (var_s0 = 0; var_s0 < 1; var_s0++) {
        gGameSettings.unlockAndSettingsFlags[var_s0] = (gGameSettings.unlockAndSettingsFlags[var_s0] & ~0x8B) | (gSaveDataBody.unk04 & 0x8B);
    }
    gGameSettings.cheatCodeFlags[0] = 0;
    gGameSettings.cheatCodeFlags[1] = 0;
    gGameSettings.musicVolume = gSaveDataBody.musicVolume;
    gGameSettings.soundFxVolume = gSaveDataBody.soundFxVolume;
    gGameSettings.speechVolume = gSaveDataBody.speechVolume;
    gGameSettings.controllerSetting = gSaveDataBody.controllerSetting;
    gGameSettings.languageSelect = gSaveDataBody.unkA3[5];
    for (var_s0 = 0; var_s0 < 0x1D; var_s0++) {
        if ((gSaveDataBody.cheatCodeFlags[var_s0 / 32] & (1 << (var_s0 % 32))) && isCheatCodeIndexAllowed(var_s0)) {
            gGameSettings.cheatCodeFlags[var_s0 / 32] = gGameSettings.cheatCodeFlags[var_s0 / 32] | (1 << (var_s0 % 32));
        }
    }
    if (gGameSettings.unk23 == 0) {
        gGameSettings.unlockAndSettingsFlags[1] &= ~1;
        if (gSaveDataBody.unkA3[6] == 1) {
            serializeSettingsToSaveAndPersist();
        }
    } else {
        var_s0 = gSaveDataBody.unkA3[6];
        if (var_s0 == 0) {
            gGameSettings.unlockAndSettingsFlags[1] |= 1;
            serializeSettingsToSaveAndPersist();
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/main/6E500", applyAccountUnlocksToSettings);
#endif

INCLUDE_ASM("asm/nonmatchings/main/6E500", serializeSettingsToSaveAndPersist);

INCLUDE_ASM("asm/nonmatchings/main/6E500", setUnlockBitAndPersist);

void applyMusicOrSfxVolume(u8, s32, s32, s32);
void setMusyXVoiceTickGate(s32);
void setSpeechVolume(u8);
void applyVolumeSettingsToMixer(void) {
    u8 music;
    u8 sfx;
    u8 speech;

    music = gGameSettings.musicVolume;
    sfx = gGameSettings.soundFxVolume;
    speech = gGameSettings.speechVolume;
    gGameSettings.unlockAndSettingsFlags[1] &= ~2;
    gGameSettings.unlockAndSettingsFlags[1] &= ~4;
    gGameSettings.unlockAndSettingsFlags[1] &= ~8;
    if (music == 0) {
        gGameSettings.unlockAndSettingsFlags[1] |= 2;
    }
    if (sfx == 0) {
        gGameSettings.unlockAndSettingsFlags[1] |= 4;
    }
    if (speech == 0) {
        gGameSettings.unlockAndSettingsFlags[1] |= 8;
    }
    applyMusicOrSfxVolume(music, 0, 1, 0);
    applyMusicOrSfxVolume(sfx, 0, 0, 1);
    setSpeechVolume(speech);
    setMusyXVoiceTickGate(((u8 *)&gGameSettings.unlockAndSettingsFlags[1])[3] & 0x80);
}

INCLUDE_ASM("asm/nonmatchings/main/6E500", resetGameSettingsAndMissionStats);

INCLUDE_ASM("asm/nonmatchings/main/6E500", generateUnlockString);

s32 getActiveAccountsBitmask(void) {
    return gSaveDataBody.unk50;
}

s32 getAccountUnk51(void) {
    return gSaveDataBody.unk51;
}

INCLUDE_ASM("asm/nonmatchings/main/6E500", createAccountProfile);

extern u8 missionStats;

void initPlayerMissionStateFromSettings(void) {
    s32 var_s1;
    u8 *temp_s0;

    var_s1 = 0;
    do {
        temp_s0 = &gMissionState.numLives[var_s1];
        (*(u8 *)((u8 *)(temp_s0) + 2)) = (u8) gGameSettings.secondaryWeapon;
        var_s1 += 1;
        (*(s8 *)((u8 *)(temp_s0) + 3)) = getSecondaryWeaponCount(gGameSettings.vehicleId, gGameSettings.secondaryWeapon);
    } while (var_s1 == 0);
    gMissionState.completedObjectiveFlags = 0;
    gMissionState.hiddenObjectiveFlags = 0;
    gMissionState.numMissionObjectives = 0;
    rs_memset(&missionStats, 0U, 0x10U);
}

void initializeNumLives(void) {
    u8 var_v1;

    for (var_v1 = 0; var_v1 < 1; var_v1++) {
        gMissionState.numLives[var_v1] = 3;
    }
}

extern struct account_data D_main_bss_8013A550;
void packAccountProgressBits(struct account_data *, u8 *, s32);
struct account_data *loadAccountDataIntoStruct(u8 arg0) {
    s32 lvl;

    rs_strcpy((u8 *)D_main_bss_8013A550.name, (u8 *)gGameSettings.name);
    D_main_bss_8013A550.unk04 = gMissionState.playerRank;
    lvl = gMissionState.maxUnlockedLevel;
    D_main_bss_8013A550.unk05 = lvl;
    D_main_bss_8013A550.unk0C = gGameSettings.unlockAndSettingsFlags[0] & 0x7FFE00;
    D_main_bss_8013A550.accountNumber = gMissionState.accountNumber;
    packAccountProgressBits(&D_main_bss_8013A550, gMissionState.medalPerLevel, lvl);
    copyAccountRecordAndMarkActive(&D_main_bss_8013A550, arg0);
    return &D_main_bss_8013A550;
}

void parseAccountDataBytes(u8 *src, u8 *dst) {
    u8 i;

    for (i = 0; i < 19; i++) {
        dst[i] = (*((i >> 2) + src + 6) >> ((i & 3) * 2)) & 3;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/6E500", packAccountProgressBits);

struct EliteRogueData *getSaveScratchBufferPtr(void) {
    return gSaveDataBody.highscores;
}

u8 findUnusedAccountId(void) {
    u8 var_a0;
    u8 found;
    u8 var_v1;

    for (var_a0 = 1; var_a0 < 0xFF; var_a0++) {
        found = 0;
        for (var_v1 = 0; var_v1 < 10; var_v1++) {
            if (gSaveDataBody.highscores[var_v1].accountNumber == var_a0) {
                found = 1;
                break;
            }
        }
        if (found == 0) break;
    }
    return var_a0;
}

s32 resetGameSettingsAndMissionStats();

void resetSettingsClearSaveAndReload(void) {
    resetGameSettingsAndMissionStats();
    rs_memset((u8 *) &gSaveDataBody, 0U, 0xB0U);
    loadDefaultHighScores();
    persistSaveDataBody();
    serializeSettingsToSaveAndPersist();
}

u32 getUsableRdramSize(void);
void initIdleDemoTimersAndSave(void) {
    u8 i;

    for (i = 0; i < 1; i++) {
        gGameSettings.unlockAndSettingsFlags[i] = 0x19B;
    }
    gGameSettings.unk23 = getUsableRdramSize() > 0x400000;
    gGameSettings.unlockAndSettingsFlags[1] &= ~1;
    if (gGameSettings.unk23) {
        gGameSettings.unlockAndSettingsFlags[1] |= 1;
    }
}

void resetMixerVolumesAndFlags(void) {
    gGameSettings.musicVolume   = 0x7F;
    gGameSettings.soundFxVolume = 0x7F;
    gGameSettings.speechVolume  = 0x7F;
    GAME_SETTING_UNSET(1, GAME_SETTINGS_MONO_STEREO);
    GAME_SETTING_UNSET(1, GAME_SETTINGS_MUTE_SFX);
    GAME_SETTING_UNSET(1, GAME_SETTINGS_MUTE_SPEECH);
    GAME_SETTING_SET(1, GAME_SETTINGS_DISABLE_SUBTITLES);
}

s32 isUnlockBitSet(u8 arg0) {
    u16 huh;
    huh = arg0;
    huh = gSaveDataBody.unkA3[arg0 / 8] >> (huh % 8);
    return huh & 1;
}

void gatherActiveUnlockFlags(void) {
    gMissionState.activeUnlockFlags = gGameSettings.unlockAndSettingsFlags[0] & ~0xFF8001FF;
}

void syncMissionUnlockBitsToSettings(void) {
    u32 bitmask = ~0xFF8001FF;
    gGameSettings.unlockAndSettingsFlags[0] = (gGameSettings.unlockAndSettingsFlags[0] & bitmask & gMissionState.activeUnlockFlags) | (gGameSettings.unlockAndSettingsFlags[0] & ~bitmask);
}

void unlockMissleUpgradeOnLevelCompletion(u8 levelId) {
    if (levelId == LEVEL_GERRARDV) {
        gGameSettings.unlockAndSettingsFlags[0] |= GAME_SETTING_MASK(GAME_SETTINGS_ADVANCED_TORPEDOS);
    }
    if (levelId == LEVEL_KESSEL_PRISON) {
        gGameSettings.unlockAndSettingsFlags[0] |= GAME_SETTING_MASK(GAME_SETTINGS_ADVANCED_MISSILES);
    }
}

struct account_data *getAccountDataPtr(u8 arg0) {
    struct account_data *temp_v1;

    temp_v1 = &gSaveDataBody.accounts[arg0];
    if (temp_v1->unk05 >= 0x11) {
        temp_v1->unk05 = 0x10;
    }
    return temp_v1;
}

void copyAccountRecordAndMarkActive(struct account_data *arg0, u8 arg1) {
    struct account_data *temp_a0;

    if (arg0->unk05 >= 0x11) {
        arg0->unk05 = 0x10;
    }
    temp_a0 = &gSaveDataBody.accounts[arg1];
    if (arg0 != temp_a0) {
        zmemcpy(temp_a0, arg0, sizeof(struct account_data));
    }
    gSaveDataBody.unk51 = arg1;
    gSaveDataBody.unk50 |= (1 << arg1);
    persistSaveDataBody();
}

void clearAccountRecordAndMarkInactive(u8 arg0) {
    rs_memset(&gSaveDataBody.accounts[arg0], 0, sizeof(struct account_data));
    gSaveDataBody.unk50 &= ~(1 << arg0);
    persistSaveDataBody();
}

s32 registerServiceWorker(s32, s32, s32, s32 *);
s32 startServiceWorker(s32);
extern s8 D_main_bss_8013A5B1;
extern s32 saveServiceWorker;

void registerSaveService(s32 arg0) {
    s32 temp_v0;

    temp_v0 = registerServiceWorker(4, 0x800, arg0 & 0xFF, &saveServiceWorker);
    D_main_800A0A60 = temp_v0;
    startServiceWorker(temp_v0);
    D_main_bss_8013A5B1 = 0;
}

s32 unregisterServiceWorker(s32);

void stopSaveServiceWorker(void) {
    if (D_main_800A0A60 != -1) {
        unregisterServiceWorker(D_main_800A0A60);
    }
    D_main_800A0A60 = -1;
}

s32 getViModeType();

s32 isViModeTypePal(void) {
    return (getViModeType() & 0xFF) == 1;
}

void cycleIdleDemoId(void) {
    gGameSettings.demoId = (gGameSettings.demoId + 1) % 6;
    if (gGameSettings.demoId == 5) {
        if (gGameSettings.unk15 < 4) {
            gGameSettings.unk15 += 1;
            gGameSettings.demoId = 0;
        } else {
            gGameSettings.unk15 = 0;
        }
    }
}

s32 classifySaveStateFromInput(s32 arg0) {
    switch (arg0) {
        case 6:
            return 1;
        case 8:
            D_main_bss_8013A5B0 = 1;
            return 2;
        case 9:
            return 1;
        default:
            return 0;
    }
}

u8 loadOrSaveEepromRecord(s32, s32, s32, void *, s32);
s32 loadSaveDataIfNotLoaded(void) {
    struct GameSettings *gs = &gGameSettings;
    u8 r;

    if (*(u8 *)&gs->unk2C != 0) {
        return 0;
    }
    r = loadOrSaveEepromRecord(1, 0, 0, &gSaveDataBody, 0xB0);
    if (r) {
        r = loadOrSaveEepromRecord(1, 0, 1, &gSaveDataBody, 0xB0);
    }
    gs->nabooStarfighterCheatHash = gSaveDataBody.unkAC;
    return r == 0;
}

u8 saveLoadDispatcher(s32, s32, s32, void *, void *, s32);
void triggerSaveMessage(void);
void persistSaveDataBody(void) {
    u8 buf[0x10];

    gSaveDataBody.unkA2 = 0x3A;
    gSaveDataBody.unkA3[6] = gGameSettings.unk23;
    gSaveDataBody.unkAC = gGameSettings.nabooStarfighterCheatHash;
    if (D_main_800A0A60 == -1) {
        if (!saveLoadDispatcher(1, 0, 0, buf, &gSaveDataBody, 0xB0)) {
            *(u8 *)&gGameSettings.unk2C = 1;
        }
        if (!saveLoadDispatcher(1, 0, 1, buf, &gSaveDataBody, 0xB0)) {
            *(u8 *)&gGameSettings.unk2C = 1;
        }
    } else {
        triggerSaveMessage();
    }
}

u8 *rs_malloc(s32, s32);
s32 sendServiceMessage(s32, s32, u8 *, s32);
extern s32 D_main_bss_80138920;

void triggerSaveMessage(void) {
    u8 *temp_v0;

    temp_v0 = rs_malloc(0x14, 0);
    rs_memset(temp_v0, 0U, 0x14U);
    sendServiceMessage(D_main_bss_80138920, D_main_800A0A60, temp_v0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main/6E500", saveServiceWorker);

s32 isSaveStateNotPending(void) {
    return gSaveDataBody.unkA2 != 0x3A;
}

void setAccountHighscore(u8 arg0, u16 arg1, u8 levelId) {
    gSaveDataBody.highscores[arg0].name[0] = gGameSettings.name[0];
    gSaveDataBody.highscores[arg0].name[1] = gGameSettings.name[1];
    gSaveDataBody.highscores[arg0].name[2] = gGameSettings.name[2];
    gSaveDataBody.highscores[arg0].current_level = levelId;
    gSaveDataBody.highscores[arg0].medals.as_short = arg1;
    gSaveDataBody.highscores[arg0].accountNumber = gMissionState.accountNumber;
}

s32 getAccountHighscore(u8 arg0) {
    s32 medals;

    medals = gSaveDataBody.highscores[arg0].medals.as_short;
    medals = ((medals & 0x1F) + 2*((medals >> 5) & 0x1F) + 4*((medals >> 10) & 0x1F)) * 2;
    if (gSaveDataBody.highscores[arg0].accountNumber == gMissionState.accountNumber) {
        medals += 1;
    }
    return medals;
}

s32 getSecondaryWeaponCount(u8 craftId, u8 arg1) {
    s32 count;

    count = 0;
    switch (craftId) {
    case CRAFT_XWING:
        count = 6;
        if (arg1 == SECONDARY_WEAPON_ION_CANNON) {
            count = 0xFF;
        }
        break;
    case CRAFT_YWING:
        count = 0x14;
        break;
    case CRAFT_VWING:
    case CRAFT_SNOWSPEEDER:
        count = 6;
        break;
    case CRAFT_FALCON:
        count = 0xF;
        break;
    case CRAFT_AWING:
    case CRAFT_TIEINTER:
        count = 8;
        break;
    case CRAFT_T16:
        count = 0xFF;
        break;
    case CRAFT_KOELSCH:
        count = 0xA;
        break;
    }
    return count;
}

INCLUDE_ASM("asm/nonmatchings/main/6E500", fake_func_8006F4AC);

// DO NOT DELTE ME, I'M REQUIRED FOR MATCHING
u32 data_junk = 0x03A0F021;
