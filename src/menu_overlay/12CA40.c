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

INCLUDE_ASM("asm/nonmatchings/menu_overlay/12CA40", menuOverlayInit);

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
