#include "common.h"
#include "common_types.h"
#include "common_variables.h"

#include "crafts.h"
#include "levels.h"
#include "secondary_weapons.h"
#include "medals.h"
#include "game_settings.h"
#include "mission_state.h"

#include "menu_overlay/12CA40.h"

#include "game_config.h"
typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 f6;
    u8 f8;
    u8 f9;
    u8 fA;
    u8 pB;
    u16 fC;
    u16 fE;
    u16 f10;
    u16 f12;
    u16 f14;
    u16 f16;
    u8 f18;
    u8 p19;
} MenuOvlEnt;
extern MenuOvlEnt D_menu_overlay_800CD2B0[];
extern u16 D_menu_overlay_800CFF50;
extern u8 D_menu_overlay_800CFF60[];
extern u8 D_main_bss_80130B3A;
extern s32 D_main_bss_80137CFC;
extern u8 dLevelByDemoId[];
extern u8 missionStats[];
void zmemcpy(u8 *, u8 *, u32);
void initNewAndPreviousButtonsPressed(void);
void tickMusyXIfActive(void);
u8 anyAudioSlotActive(void);
void runVideoFrameTick(void *, void *, void *);
void clearSceneBssRegion(s32);
s32 findManifestEntryByName(char *);
void loadSndFiles(void);
void loadGameOrFrontTxtFile(u8 *);
void registerSaveService(s32);
void initTextTextureTarget(void);
u8 moRunHangarMenuFromOverlay(u8 *, s32, s32) __asm__("runHangarMenuFromOverlay");
u8 moDrawRadarIcon(u8 *, s32) __asm__("drawRadarIcon");
u8 getLevelIntroCrawlId(u8);
u8 runResultsTextScreenLoop(s32, char *);
void menuControllerInput(s32, u8);
void runModelViewerLoop(s32, u8);
void runMenuRandomBackdropScreen(s32, void *, u8, u8);
void runMenuShipSelectScreen(s32);
void runMenuModelViewerScreen(s32);
void menuSubtype02Handler(s32);
void bufferArbiterProducerScanWait(void);
void waitForAnyAudioSlot(void);
void freeTxtFile(void);
s32 freeManifestSegmentAssets(s32);
void stopSaveServiceWorker(void);
void clearDeferredClearRequest(void);
u8 getSecondaryWeaponForLevelAndCraft(u8, u8, u8);
#define bc ((MOBoot *)&gBootConfig)
typedef struct {
    u8 p0[0x12];
    u16 f12;
    u16 f14;
    u16 f16;
    u8 f18;
    u8 p19[3];
    s32 f1C;
    u8 f20;
    u8 f21;
    u8 f22;
    u8 p23;
    u16 f24;
    u8 p26[0xA];
    s32 f30;
    s32 f34;
    s32 f38;
    u16 f3C;
    u16 f3E;
    u16 f40;
    u16 f42;
    s32 f44;
    u8 p48[8];
} MOBoot;

void menuOverlayInit(u8 *arg0, u8 arg1, s32 arg2) {
    MenuOvlEnt *tbl = D_menu_overlay_800CD2B0;
    MenuOvlEnt *e;
    u16 t;

    D_menu_overlay_800CFF50 = arg1;
    D_main_bss_80130B3A = 1;
    zmemcpy(D_menu_overlay_800CFF60, (u8 *)bc, 0x50);
    initNewAndPreviousButtonsPressed();
    do {
        tickMusyXIfActive();
        while (!anyAudioSlotActive()) {
        }
        e = (MenuOvlEnt *)(D_menu_overlay_800CFF50 * sizeof(MenuOvlEnt) + (s32)tbl);
        bc->f12 = e->f0;
        bc->f14 = e->f2;
        bc->f16 = 0x10;
        bc->f40 = e->f4;
        bc->f42 = e->f6;
        bc->f38 = e->f10 << 10;
        bc->f30 = e->f12 << 10;
        t = e->f14;
        bc->f34 = t << 10;
        bc->f44 = e->f16;
        bc->f20 = e->f8;
        bc->f21 = e->f9;
        bc->f22 = e->fA;
        bc->f1C = e->fC;
        bc->f18 = e->f18;
        bc->f24 = e->fE;
        bc->f3C = 0x400;
        bc->f3E = 0x200;
        if (arg0[0x23] == 1) {
            bc->f34 = t << 11;
        }
        runVideoFrameTick((u8 *)bc + 0x10, (u8 *)bc + 0x2C, (u8 *)bc + 0x1C);
        clearSceneBssRegion(1);
        D_main_bss_80137CFC = findManifestEntryByName("data");
        loadSndFiles();
        loadGameOrFrontTxtFile("front_TXT");
        registerSaveService(6);
        initTextTextureTarget();
        switch (D_menu_overlay_800CFF50) {
        case 0:
            if (!moRunHangarMenuFromOverlay(arg0, 0, arg0[0])) {
                D_menu_overlay_800CFF50 = 1;
            } else {
            crawl:
                if (getLevelIntroCrawlId(arg0[0]) != 0xFF) {
                    D_menu_overlay_800CFF50 = 6;
                    break;
                }
                D_menu_overlay_800CFF50 = 11;
            }
            break;
        case 1:
            if (!moDrawRadarIcon(arg0, 0)) {
                D_menu_overlay_800CFF50 = 2;
            } else if (arg0[0] == 0x10) {
                gGameSettings.vehicleId = 7;
                goto crawl;
            } else {
                D_menu_overlay_800CFF50 = 0;
            }
            break;
        case 4:
            arg0[2] = runResultsTextScreenLoop(3, "CHOOSE DIFFICULTY:");
            D_menu_overlay_800CFF50 = 5;
            break;
        case 5:
            arg0[5] = runResultsTextScreenLoop(4, "CHOOSE CONTROLLER STYLE:");
            D_menu_overlay_800CFF50 = 0;
            break;
        case 2:
            menuControllerInput(0, arg2);
            gGameSettings.unk24 = 0;
            if (arg2 == 11) {
                D_menu_overlay_800CFF50 = 12;
            } else if (gGameSettings.unlockAndSettingsFlags[1] & 0x20) {
                gGameSettings.currentLevel = dLevelByDemoId[gGameSettings.demoId];
                gGameSettings.vehicleId = dDefaultCraftForLevel[gGameSettings.currentLevel];
                gGameSettings.unk02 = 0;
                gMissionState.unk20 = 0;
                D_menu_overlay_800CFF50 = 12;
            } else if (gGameSettings.unlockAndSettingsFlags[1] & 0x200) {
                gGameSettings.unlockAndSettingsFlags[1] &= ~0x200;
                gMissionState.unk20 = 0;
                D_menu_overlay_800CFF50 = 10;
            } else if (gGameSettings.cheatCodeFlags[0] & 0x200000) {
                gMissionState.unk20 = 0;
                D_menu_overlay_800CFF50 = 8;
            } else if (gGameSettings.cheatCodeFlags[0] & 0x2000000) {
                gMissionState.unk20 = 0;
                D_menu_overlay_800CFF50 = 12;
            } else {
                gMissionState.unk20 = 0;
                gMissionState.unk22 = 0;
                gMissionState.unk23 = 0;
                D_menu_overlay_800CFF50 = 1;
            }
            arg2 = 0;
            break;
        case 6:
            runModelViewerLoop(0, getLevelIntroCrawlId(arg0[0]));
            D_menu_overlay_800CFF50 = 11;
            break;
        case 3:
            runMenuRandomBackdropScreen(0, missionStats, arg0[0], arg2);
            D_menu_overlay_800CFF50 = 12;
            break;
        case 8:
            runMenuShipSelectScreen(0);
            D_menu_overlay_800CFF50 = 12;
            if (gGameSettings.cheatCodeFlags[0] & 0x200000) {
                gGameSettings.cheatCodeFlags[0] &= ~0x200000;
                D_menu_overlay_800CFF50 = 2;
            }
            break;
        case 9:
            runMenuModelViewerScreen(0);
            D_menu_overlay_800CFF50 = 12;
            break;
        case 7:
            arg0[0x2D] = runResultsTextScreenLoop(5, "CHOOSE CUTSCENE TYPE:");
            D_menu_overlay_800CFF50 = 11;
            break;
        case 10:
            menuSubtype02Handler(0);
            D_menu_overlay_800CFF50 = 2;
            gGameSettings.cheatCodeFlags[0] &= ~0x20;
            if (gGameSettings.unlockAndSettingsFlags[1] & 0x400) {
                D_menu_overlay_800CFF50 = 12;
            }
            break;
        }
        bufferArbiterProducerScanWait();
        waitForAnyAudioSlot();
        freeTxtFile();
        freeManifestSegmentAssets(D_main_bss_80137CFC);
        stopSaveServiceWorker();
        clearDeferredClearRequest();
    } while (D_menu_overlay_800CFF50 != 11 && D_menu_overlay_800CFF50 != 12);
    arg0[3] = getSecondaryWeaponForLevelAndCraft(arg0[0], arg0[1], 0);
    zmemcpy((u8 *)&gBootConfig, D_menu_overlay_800CFF60, 0x50);
    D_main_bss_80130B3A = 0;
}

extern u8 D_main_bss_80130B2F;
void initCraftSelectScreen(s32, s32, s32, s32);
s32 tickCraftSelectScreen(void);
void drainAudioAndFinalizeSpeechBuffer(void);
s32 drawRadarIcon(u8 *arg0, s32 arg1) {
    u32 a;
    u32 b;
    s32 r;
    a = D_main_bss_80130B2F;
    if (a >= 0x10) {
        a = 0xF;
    }
    if (gGameSettings.cheatCodeFlags[0] & 1) {
        a = 0xF;
    }
    if ((gGameSettings.unlockAndSettingsFlags[0] & 0x100000) || (gGameSettings.cheatCodeFlags[0] & 0x4000000)) {
        a = 0x10;
    }
    if ((gGameSettings.unlockAndSettingsFlags[0] & 0x200000) || (gGameSettings.cheatCodeFlags[0] & 0x8000000)) {
        a = 0x11;
    }
    if ((gGameSettings.unlockAndSettingsFlags[0] & 0x400000) || (gGameSettings.cheatCodeFlags[0] & 0x10000000)) {
        a = 0x12;
    }
    if (a < arg0[0]) {
        b = a;
    } else {
        b = arg0[0];
    }
    initCraftSelectScreen(arg1, 1 << b, (1 << (a + 1)) - 1, b);
    do {
        r = tickCraftSelectScreen();
    } while (r == 0xFFFFFF);
    drainAudioAndFinalizeSpeechBuffer();
    if (r != 0xFFFFFE) {
        arg0[0] = r;
        arg0[2] = 0;
        return 1;
    }
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/12CA40", strMenuALPHA);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/12CA40", strMenuBETA);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/12CA40", strMenuGAMMA);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/12CA40", strMenuDELTA);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/12CA40", D_menu_overlay_800A760C);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/12CA40", strMenuINTRO);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/12CA40", strMenuEXTRO);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/12CA40", strMenuSPECIAL);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/12CA40", D_menu_overlay_800A7644);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/12CA40", runResultsTextScreenLoop);

s32 getAvailablePlayerCraftFlagsConsiderUnlocks(enum Level levelId) {
    s32 availableCraftFlags;

    availableCraftFlags = CRAFT_FLAG(dDefaultCraftForLevel[levelId]);
    if ((gMissionState.maxUnlockedLevel >= LEVEL_JADEMOON) && (levelId < gMissionState.maxUnlockedLevel) && (availableCraftFlags & 0xD)) {
        availableCraftFlags |= CRAFT_FLAG(CRAFT_AWING);
    }
    if ((gMissionState.maxUnlockedLevel >= LEVEL_TALORAAN) && (levelId < gMissionState.maxUnlockedLevel) && (availableCraftFlags & 0xD)) {
        availableCraftFlags |= CRAFT_FLAG(CRAFT_VWING);
    }
    if ((gMissionState.maxUnlockedLevel >= LEVEL_CALAMARI) && (levelId < gMissionState.maxUnlockedLevel) && (availableCraftFlags & 0xD)) {
        availableCraftFlags |= CRAFT_FLAG(CRAFT_XWING);
    }
    if (ALL_CRAFT_UNLOCKED) {
        availableCraftFlags |= 0x7F;
    }
    if ((gGameSettings.cheatCodeFlags[0] & 4) || MELLINIUM_FALCON_UNLOCKED) {
        availableCraftFlags |= CRAFT_FLAG(CRAFT_FALCON);
    }
    if ((gGameSettings.cheatCodeFlags[0] & 8) || TIE_INTERCEPTOR_UNLOCKED) {
        availableCraftFlags |= CRAFT_FLAG(CRAFT_TIEINTER);
    }
    if (levelId == LEVEL_TALORAAN) {
        availableCraftFlags &= ~CRAFT_FLAG(CRAFT_VWING);
        availableCraftFlags &= ~CRAFT_FLAG(CRAFT_SNOWSPEEDER);
    }
    if (levelId == LEVEL_TRENCH_RUN) {
        availableCraftFlags &= CRAFT_FLAG(CRAFT_XWING);
    }
    if (levelId == LEVEL_KESSEL_RESCUE) {
        availableCraftFlags &= CRAFT_FLAG(CRAFT_XWING) | CRAFT_FLAG(CRAFT_YWING);
    }
    if ((levelId == LEVEL_CORELLIA) || (levelId == LEVEL_CONST_YARD) || (levelId == LEVEL_FEST) || (levelId == LEVEL_HOTH)) {
        availableCraftFlags &= CRAFT_FLAG(CRAFT_SNOWSPEEDER);
    }
    if (levelId == LEVEL_BEGGARS_CANYON) {
        availableCraftFlags &= CRAFT_FLAG(CRAFT_T16);
    }
    return availableCraftFlags;
}

s32 getAvailablePlayerCraftFlagsIgnoreUnlocks(enum Level levelId) {
    s32 availableCraftFlags;

    availableCraftFlags = CRAFT_FLAG(dDefaultCraftForLevel[levelId]);
    if (availableCraftFlags & 0xD) {
        availableCraftFlags |= CRAFT_FLAG(CRAFT_XWING) | CRAFT_FLAG(CRAFT_AWING) | CRAFT_FLAG(CRAFT_VWING);
    }
    if (ALL_CRAFT_UNLOCKED) {
        availableCraftFlags |= 0x7F;
    }
    if ((gGameSettings.cheatCodeFlags[0] & 4) || MELLINIUM_FALCON_UNLOCKED) {
        availableCraftFlags |= CRAFT_FLAG(CRAFT_FALCON);
    }
    if ((gGameSettings.cheatCodeFlags[0] & 8) || TIE_INTERCEPTOR_UNLOCKED) {
        availableCraftFlags |= CRAFT_FLAG(CRAFT_TIEINTER);
    }
    if (levelId == LEVEL_TALORAAN) {
        availableCraftFlags &= ~CRAFT_FLAG(CRAFT_VWING);
        availableCraftFlags &= ~CRAFT_FLAG(CRAFT_SNOWSPEEDER);
    }
    if (levelId == LEVEL_TRENCH_RUN) {
        availableCraftFlags &= CRAFT_FLAG(CRAFT_XWING);
    }
    if (levelId == LEVEL_KESSEL_RESCUE) {
        availableCraftFlags &= CRAFT_FLAG(CRAFT_XWING) | CRAFT_FLAG(CRAFT_YWING);
    }
    if ((levelId == LEVEL_CORELLIA) || (levelId == LEVEL_CONST_YARD) || (levelId == LEVEL_FEST) || (levelId == LEVEL_HOTH)) {
        availableCraftFlags &= CRAFT_FLAG(CRAFT_SNOWSPEEDER);
    }
    if (levelId == LEVEL_BEGGARS_CANYON) {
        availableCraftFlags &= CRAFT_FLAG(CRAFT_T16);
    }
    return availableCraftFlags;
}

void unlockLevelsAndCraftsBasedOnMedalsEarned(u8 *medalsPerLevel) {
    u8 var_a1;
    u8 normalAllBronze;
    u8 unlockableAllBronze;
    u8 normalAllSilver;
    u8 unlockableAllSilver;
    u8 normalAllGold;
    u8 unlockableAllGold;
    u8 anyLevelsUnlocked;
    u8 temp_v1;
    u8 temp_v1_2;

    anyLevelsUnlocked = 0;
    normalAllBronze = 1;
    normalAllSilver = 1;
    normalAllGold   = 1;
    // Check the medals for all "normal" levels
    for (var_a1 = 0; var_a1 < LEVEL_BEGGARS_CANYON; var_a1++) {
        temp_v1 = medalsPerLevel[var_a1];
        if (temp_v1 < MEDAL_GOLD) {
            normalAllGold = 0;
        }
        if (temp_v1 < MEDAL_SILVER) {
            normalAllSilver = 0;
        }
        if (temp_v1 < MEDAL_BRONZE) {
            normalAllBronze = 0;
        }
    }
    if (normalAllBronze == 1) {
        if (!BEGGARS_CANYON_UNLOCKED) {
            anyLevelsUnlocked = 1;
        }
        GAME_SETTING_SET(0, GAME_SETTINGS_BEGGARS_CANYON);
    }
    if (normalAllSilver == 1) {
        if (!DEATH_STAR_UNLOCKED) {
            anyLevelsUnlocked = 1;
        }
        GAME_SETTING_SET(0, GAME_SETTINGS_DEATH_STAR);
    }
    if (normalAllGold == 1) {
        if (!HOTH_UNLOCKED) {
            anyLevelsUnlocked = 1;
        }
        GAME_SETTING_SET(0, GAME_SETTINGS_HOTH);
    }
    gMissionState.anyExtraLevelsUnlocked = anyLevelsUnlocked;
    unlockableAllBronze = 1;
    unlockableAllSilver = 1;
    unlockableAllGold   = 1;
    // Check the medals for all unlockable levels
    for (var_a1 = LEVEL_BEGGARS_CANYON; var_a1 < NUM_LEVELS; var_a1++) {
        temp_v1 = medalsPerLevel[var_a1];
        if (temp_v1 < MEDAL_GOLD) {
            unlockableAllGold = 0;
        }
        if (temp_v1 < MEDAL_SILVER) {
            unlockableAllSilver = 0;
        }
        if (temp_v1 < MEDAL_BRONZE) {
            unlockableAllBronze = 0;
        }
    }
    if (unlockableAllBronze == 1) {
        GAME_SETTING_SET(0, GAME_SETTINGS_MELLINIUM_FALCON);
    }
    if (unlockableAllSilver == 1) {
        GAME_SETTING_SET(0, GAME_SETTINGS_TIE_INTERCEPTOR);
    }
    if (unlockableAllGold == 1) {
        GAME_SETTING_SET(0, GAME_SETTINGS_ALL_CRAFT);
    }
}

typedef struct {
    u8 pad[0x1C];
    f32 unk1C;
    f32 unk20;
} TimeSnapshot;
void timeSnapshotFiller(TimeSnapshot *);
f32 floatModulo(f32, f32);
extern s32 D_main_bss_8013889C;

f32 advanceWrappingPhaseAccumulator(void) {
    TimeSnapshot snap;
    f32 var_fs0;
    f32 m;

    timeSnapshotFiller(&snap);
    var_fs0 = snap.unk20;
    D_main_bss_8013889C += 1;
    m = floatModulo(var_fs0, snap.unk1C);
    if (m > 0.0f) {
        if ((m / snap.unk1C) < 0.5f) {
            var_fs0 -= m;
        } else {
            var_fs0 = (var_fs0 + snap.unk1C) - m;
        }
    }
    if (var_fs0 <= 0.0f) {
        var_fs0 = 0.016666668f;
    }
    if (var_fs0 > 0.16666667f) {
        var_fs0 = 0.16666667f;
    }
    return var_fs0;
}

s32 getLevelHardwiredDifficulty(u8 levelId) {
    return 0;
}

u8 getSecondaryWeaponForLevelAndCraft(u8 levelId, u8 craftId, u8 arg2) {
    s32 secondaryWeaponType;

    secondaryWeaponType = SECONDARY_WEAPON_NONE;
    switch (craftId) {
    case CRAFT_XWING:
        secondaryWeaponType = SECONDARY_WEAPON_PROTON_TORPEDOS;
        break;
    case CRAFT_YWING:
        secondaryWeaponType = SECONDARY_WEAPON_BOMBS;
        break;
    case CRAFT_AWING:
        secondaryWeaponType = SECONDARY_WEAPON_MISSLES;
        break;
    case CRAFT_VWING:
        secondaryWeaponType = SECONDARY_WEAPON_CLUSTER_MISSILES;
        break;
    case CRAFT_SNOWSPEEDER:
        secondaryWeaponType = SECONDARY_WEAPON_TOW_CABLE;
        break;
    case CRAFT_TIEINTER:
    case CRAFT_T16:
        secondaryWeaponType = SECONDARY_WEAPON_NONE;
        break;
    case CRAFT_FALCON:
    case CRAFT_KOELSCH:
        secondaryWeaponType = SECONDARY_WEAPON_SEEKER_TORPEDOS;
        break;
    }
    if (levelId == LEVEL_KESSEL_RESCUE) {
        if (craftId == CRAFT_XWING) {
            secondaryWeaponType = SECONDARY_WEAPON_ION_CANNON;
        }
    }
    if ((secondaryWeaponType == SECONDARY_WEAPON_MISSLES) && GAME_SETTING_IS_SET(arg2, GAME_SETTINGS_SEEKER_MISSILES)) {
        secondaryWeaponType = SECONDARY_WEAPON_SEEKER_MISSILES;
    }
    if ((secondaryWeaponType == SECONDARY_WEAPON_PROTON_TORPEDOS) && GAME_SETTING_IS_SET(arg2, GAME_SETTINGS_SEEKER_TORPEDOS)) {
        secondaryWeaponType = SECONDARY_WEAPON_SEEKER_TORPEDOS;
    }
    if ((secondaryWeaponType == SECONDARY_WEAPON_CLUSTER_MISSILES) && GAME_SETTING_IS_SET(arg2, GAME_SETTINGS_SEEKER_CLUSTER_MISSILES)) {
        secondaryWeaponType = SECONDARY_WEAPON_SEEKER_CLUSTER_MISSILES;
    }
    return secondaryWeaponType;
}

s32 hasKasanMoorDefected(u8 levelId) {
    return levelId < LEVEL_JADEMOON ? 4 : 5;
}

void hangarInitialize(u8, u8, s32, u8);
s32 runHangarSelectionFrame(u8);
void gracefulMenuShutdown(void);

s32 runHangarMenuFromOverlay(u8 *out, s32 arg1, enum Level level) {
    s32 result;

    hangarInitialize(arg1, dDefaultCraftForLevel[level], getAvailablePlayerCraftFlagsConsiderUnlocks(level), level);
    do {
        result = runHangarSelectionFrame(level);
    } while (result == 0xFFFFFF);
    gracefulMenuShutdown();
    if (result != 0xFFFFFE) {
        out[1] = result;
        return 1;
    }
    return 0;
}

u8 getLevelIntroCrawlId(u8 levelId) {
    switch (levelId) {
        case LEVEL_MOSEISLEY:
            return 0;
            break;
        case LEVEL_JADEMOON:
            return 1;
            break;
        case LEVEL_TALORAAN:
            return 2;
            break;
        case LEVEL_CALAMARI:
            return 3;
            break;
        default:
            return 0xFF;
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/12CA40", fake_func_800C6968);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/12CA40", junk_800A76D4);
