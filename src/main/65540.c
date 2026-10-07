#include "common.h"
#include "common_types.h"

#include "level_objectives.h"

#include "main/65540.h"

INCLUDE_RODATA("asm/nonmatchings/main/65540", D_main_8003B830);

typedef struct {
    u16 id;
    u8 pad2;
    u8 hiDetailOnly;
    u8 pad4[0x6C];
    s32 unk70;
    u8 pad74[0x18];
    u32 unk8C;
} LdDatItem;

typedef struct {
    u32 count;
    LdDatItem **items;
} LdDatHeader;

typedef struct {
    u8 pad[0x23];
    u8 unk23;
} LdSettings;

extern LdDatHeader *D_main_bss_801375D8;
extern LdSettings gGameSettingsLd __asm__("gGameSettings");
extern s32 gCurrentLevelLd __asm__("gCurrentLevel");
extern u8 D_main_bss_80139990[];
extern u8 D_main_bss_801399F8[];
extern u16 D_main_bss_801399E8[];
extern u8 D_main_bss_801399C2;
extern u8 D_main_bss_801399CB;
extern u8 D_main_bss_801399CC;
extern u8 D_main_bss_801399CD;
extern u8 D_main_bss_801399E0;
extern u8 D_main_bss_80130B63;
extern u8 D_main_8009FC40[];
extern char D_main_8003B830[];
void rs_memset(u8 *, u8, u32);
s32 isCraftAvailableByIdx(s32);
s32 isHobObjectLoaded(char *);
u16 loadAssetIntoNewSlot(char *, char *);
void loadCraftShadowTextures(s32);
void loadShieldPalette(void);
void load_hmt_and_hob(char *, void *, s32, s32);
void load_model_animation(char *);
void setPoolEntryPhaseAndMarkActive(u16, f32, s32);
s32 sprintf(char *, const char *, ...);

s32 load_dat_file_assets(void) {
    char buf[0x28];
    u32 i;
    void *anim;
    char *name;
    char *prefix;
    u8 full;
    s32 id;
    s32 n;
    f32 phase;

    anim = NULL;
    rs_memset(D_main_bss_801399F8, 1, 6);
    rs_memset(D_main_bss_80139990, 0, 0x53);
    rs_memset((u8 *)D_main_bss_801399E8, 0xFF, 0x10);
    name = NULL;
    for (i = 0; i < D_main_bss_801375D8->count; i++) {
        {
            if (D_main_bss_801375D8->items[i]->hiDetailOnly == 0 || gGameSettingsLd.unk23 != 0) {
                anim = NULL;
                id = D_main_bss_801375D8->items[i]->id;
                prefix = D_main_8003B830;
                full = 1;
                if (D_main_bss_80139990[id] == 0) {
                    D_main_bss_80139990[id] = 1;
                    switch (id) {
                        case 0xC:
                            prefix = "imp_stuff/";
                            name = "tiefighter";
                            break;
                        case 0x12:
                            prefix = "imp_stuff/";
                            name = "tieinter";
                            break;
                        case 0x13:
                            loadCraftShadowTextures(0xD);
                            prefix = "imp_stuff/";
                            name = "tiebomber";
                            break;
                        case 0x29:
                            prefix = "imp_stuff/";
                            if (gGameSettingsLd.unk23 != 0) {
                                name = "tie_d";
                            } else {
                                name = "tie_dl";
                            }
                            break;
                        case 0xD:
                            prefix = "imp_stuff/";
                            if (isCraftAvailableByIdx(4) != 0) {
                                name = "gun_turretl";
                            } else {
                                name = "gun_turret";
                            }
                            break;
                        case 0xE:
                            prefix = "imp_stuff/";
                            name = "prbdroid";
                            break;
                        case 0x1E:
                            prefix = "imp_stuff/";
                            if (isCraftAvailableByIdx(4) != 0) {
                                name = "mis_turret";
                            } else {
                                name = "mis_turretl";
                            }
                            break;
                        case 0x14:
                            prefix = "gnrc_stuff/";
                            name = "destbuild";
                            break;
                        case 0x2A:
                            prefix = "gnrc_stuff/";
                            name = "radardish";
                            break;
                        case 0x24:
                            prefix = "imp_stuff/";
                            name = "shuttle";
                            break;
                        case 0x25:
                            prefix = "imp_stuff/";
                            name = "tankdroid";
                            break;
                        case 0x2B:
                            prefix = "reb_stuff/";
                            name = "r_transp";
                            break;
                        case 0x2D:
                            prefix = "imp_stuff/";
                            name = "cargo01";
                            break;
                        case 0x3E:
                            prefix = "imp_stuff/";
                            name = "assboat";
                            break;
                        case 0x40:
                            prefix = "imp_stuff/";
                            name = "wskimmer";
                            break;
                        case 0x2E:
                            prefix = "reb_stuff/";
                            name = "r_combat";
                            break;
                        case 0x32:
                            prefix = "gnrc_stuff/";
                            if (D_main_bss_801375D8->items[i]->unk70 != 0) {
                                name = "shield_h";
                            } else {
                                name = "shield";
                            }
                            full = 0;
                            break;
                        case 0x37:
                            load_hmt_and_hob("imp_stuff/wrld_dvfx", anim, 0, 0);
                            prefix = "imp_stuff/";
                            name = "wrld_dvstr";
                            break;
                        case 0x3B:
                            prefix = "imp_stuff/";
                            name = "trooper";
                            break;
                        case 0x50:
                            prefix = "imp_stuff/";
                            name = "bsoldier";
                            break;
                        case 0x3C:
                            prefix = "reb_stuff/";
                            name = "r_pilot";
                            break;
                        case 0x3D:
                            prefix = "gnrc_stuff/";
                            name = "civilian";
                            break;
                        case 0x41:
                            prefix = "reb_stuff/";
                            name = "r_turret";
                            break;
                        case 0x42:
                            prefix = "imp_stuff/";
                            name = "tal_turret";
                            break;
                        case 0x43:
                            prefix = "gnrc_stuff/";
                            name = "cloudcar";
                            break;
                        case 0x44:
                            load_hmt_and_hob(isCraftAvailableByIdx(3) != 0 ? "imp_stuff/lplatformlo" : "imp_stuff/lplatform", anim, 1, 0x10000);
                            continue;
                        case 0x4A:
                            prefix = "imp_stuff/";
                            name = "pwrgen";
                            break;
                        case 0x4C:
                            prefix = "gnrc_stuff/";
                            name = "powerup";
                            full = 0;
                            break;
                        case 0x4D:
                            prefix = "imp_stuff/";
                            name = "raptor";
                            break;
                        case 0x2C:
                            prefix = "imp_stuff/";
                            name = "hvyshut";
                            break;
                        case 0x48:
                            prefix = "imp_stuff/";
                            name = "bosshut";
                            break;
                        case 0xF:
                            prefix = "imp_stuff/";
                            if (gGameSettingsLd.unk23 != 0) {
                                name = "atat";
                            } else {
                                name = "atat_lo";
                            }
                            if (gCurrentLevelLd == 6) {
                                anim = D_main_8009FC40;
                            }
                            load_model_animation("imp_stuff/atat_walk");
                            load_model_animation("imp_stuff/atat_die");
                            break;
                        case 0x1F:
                            prefix = "imp_stuff/";
                            if (isCraftAvailableByIdx(1) != 0) {
                                name = "atst_hi";
                            } else {
                                name = "atst";
                            }
                            if (gCurrentLevelLd == 6) {
                                anim = D_main_8009FC40;
                            }
                            load_model_animation("imp_stuff/atst_walk");
                            load_model_animation("imp_stuff/atst_start");
                            load_model_animation("imp_stuff/atst_stop");
                            break;
                        case 0x47:
                            prefix = "reb_stuff/";
                            if (gGameSettingsLd.unk23 != 0) {
                                name = "atpt_i_hi";
                            } else {
                                name = "atpt_i";
                            }
                            load_model_animation("reb_stuff/atpt_walk");
                            load_model_animation("reb_stuff/atpt_start");
                            load_model_animation("reb_stuff/atpt_stop");
                            break;
                        case 0x28:
                            prefix = "imp_stuff/";
                            switch (gCurrentLevelLd) {
                                case 4:
                                    name = "g5turret";
                                    break;
                                case 0x11:
                                    name = "dsturret";
                                    break;
                                default:
                                    name = "megaturret";
                                    break;
                            }
                            break;
                        case 0x2F:
                        case 0x30:
                        case 0x31:
                            prefix = "imp_stuff/";
                            name = "train";
                            D_main_bss_80139990[0x31] = 1;
                            D_main_bss_80139990[0x30] = 1;
                            D_main_bss_80139990[0x2F] = 1;
                            break;
                        case 0x33:
                            prefix = "imp_stuff/";
                            name = "train_pil";
                            break;
                        case 0x34:
                        case 0x35:
                            prefix = "reb_stuff/";
                            name = "r_train";
                            D_main_bss_80139990[0x35] = 1;
                            D_main_bss_80139990[0x34] = 1;
                            break;
                        case 0x36:
                            prefix = "reb_stuff/";
                            name = "r_tr_pil";
                            break;
                        case 0x27:
                            D_main_bss_80139990[id] = 0;
                            switch (D_main_bss_801375D8->items[i]->unk8C) {
                                default:
                                case 0:
                                    name = "wmxwng";
                                    n = 2;
                                    break;
                                case 1:
                                    name = "wmywng";
                                    n = 3;
                                    break;
                                case 2:
                                    name = "wmawng";
                                    n = 0;
                                    break;
                                case 3:
                                    name = "wmvwng";
                                    n = 1;
                                    break;
                                case 4:
                                    name = "wmspdr";
                                    n = 4;
                                    break;
                                case 5:
                                    name = "wmfalc";
                                    n = 5;
                                    break;
                                case 6:
                                    name = "tie";
                                    n = 7;
                                    break;
                                case 7:
                                    name = "t16";
                                    n = 6;
                                    break;
                            }
                            if (!(isHobObjectLoaded(name) & 0xFF)) {
                                sprintf(buf, "pl_crafts/%s", name);
                                load_hmt_and_hob(buf, anim, 1, 0);
                            }
                            loadCraftShadowTextures(n);
                            continue;
                        case 0x45:
                            break;
                        default:
                            name = NULL;
                            break;
                    }
                    if (name != NULL) {
                        sprintf(buf, "%s%s", prefix, name);
                        if (full) {
                            load_hmt_and_hob(buf, anim, 1, 0);
                        } else {
                            load_hmt_and_hob(buf, anim, 0, 0);
                        }
                    }
                }
            }
        }
    }
    switch (gCurrentLevelLd) {
        case 5:
        case 6:
        case 9:
        case 11:
        case 13:
        case 14:
            load_hmt_and_hob("gnrc_stuff/lamps", anim, 1, 0x10000);
            break;
    }
    name = NULL;
    if (D_main_bss_801399C2 != 0 || gCurrentLevelLd == 0xF) {
        loadShieldPalette();
    }
    if (D_main_bss_801399CB != 0) {
        prefix = "imp_stuff/";
        if (D_main_bss_80130B63 != 0) {
            sprintf(buf, "%strp_anm_run", prefix);
            D_main_bss_801399E8[0] = loadAssetIntoNewSlot("st_run", buf);
            sprintf(buf, "%strp_anm_sht", prefix);
            D_main_bss_801399E8[1] = loadAssetIntoNewSlot("st_sht", buf);
            phase = 12.0f;
            setPoolEntryPhaseAndMarkActive(D_main_bss_801399E8[0], phase, 0);
            setPoolEntryPhaseAndMarkActive(D_main_bss_801399E8[1], phase, 0);
        } else {
            sprintf(buf, "%strp_anm_run_lo", prefix);
            D_main_bss_801399E8[0] = loadAssetIntoNewSlot("st_run", buf);
            setPoolEntryPhaseAndMarkActive(D_main_bss_801399E8[0], 2.4f, 0);
            D_main_bss_801399E8[1] = 0xFFFF;
        }
    }
    if (D_main_bss_801399CC != 0) {
        prefix = "reb_stuff/";
        if (D_main_bss_80130B63 != 0) {
            sprintf(buf, "%sr_pilot_anm", prefix);
            D_main_bss_801399E8[2] = loadAssetIntoNewSlot("rp_run", buf);
            setPoolEntryPhaseAndMarkActive(D_main_bss_801399E8[2], 12.0f, 0);
        } else {
            sprintf(buf, "%sr_pilot_anm_lo", prefix);
            D_main_bss_801399E8[2] = loadAssetIntoNewSlot("rp_run", buf);
            setPoolEntryPhaseAndMarkActive(D_main_bss_801399E8[2], 2.4f, 0);
        }
    }
    if (D_main_bss_801399CD != 0) {
        prefix = "gnrc_stuff/";
        if (D_main_bss_80130B63 != 0) {
            sprintf(buf, "%sciv_anm_run", prefix);
            D_main_bss_801399E8[4] = loadAssetIntoNewSlot("civ_run", buf);
            setPoolEntryPhaseAndMarkActive(D_main_bss_801399E8[4], 12.0f, 0);
        } else {
            sprintf(buf, "%sciv_anm_run_lo", prefix);
            D_main_bss_801399E8[4] = loadAssetIntoNewSlot("civ_run", buf);
            setPoolEntryPhaseAndMarkActive(D_main_bss_801399E8[4], 2.4f, 0);
        }
    }
    if (D_main_bss_801399E0 != 0) {
        prefix = "imp_stuff/";
        if (D_main_bss_80130B63 != 0) {
            sprintf(buf, "%sblk_anm_run", prefix);
            D_main_bss_801399E8[6] = loadAssetIntoNewSlot("ibu_run", buf);
            setPoolEntryPhaseAndMarkActive(D_main_bss_801399E8[6], 12.0f, 0);
        } else {
            sprintf(buf, "%sblk_anm_run_lo", prefix);
            D_main_bss_801399E8[6] = loadAssetIntoNewSlot("ibu_run", buf);
            setPoolEntryPhaseAndMarkActive(D_main_bss_801399E8[6], 2.4f, 0);
        }
    }
    return 1;
}

s32 slotDispatcherIter(u16, s32, void *);
s32 spawnNpcOfType();
void updateDestructionDebrisNpc();
void npcTieVariantUpdate();
void npcTurretUpdate();
void npcProbeDriod();
void npcAtAtUpdate();
void npcAtStUpdate();
void npcAtPtUpdate();
void npcDebrisFieldUpdate();
void npcShuttleUpdate();
void npcTankDroidUpdate();
void npcGroundTroopUpdate();
void npcWingmanUpdate();
void npcRadarDishUpdate();
void npcGroundTransportUpdate();
void craftMountedAnimationNpcHandler();
void datItemActorNpcHandler();
void npcTrainCarUpdate();
void npcShieldUpdate();
void func_mission_overlay_800E4070();
void npcWaterCraftUpdate();
void npcWordDevastatorUpdate();
void tickCraftWithPhasedDestruction();
void func_main_80077AF0();
void npcPowerUpUpdate();
void parseDatItemSubtypes1To5();

u16 setupNpcUpdateFunctions(u8 *item) {
    s32 slot;
    u16 id;
    f32 dt;

    switch (*(u16 *)item) {
    case 20:
        slot = spawnNpcOfType(updateDestructionDebrisNpc, item, (((3 - *(u16 *)(item + 0x8A)) << 6) | 1) & 0xFFC1, 0x28);
        break;
    case 12: case 18: case 19: case 41: case 67:
        slot = spawnNpcOfType(npcTieVariantUpdate, item, 2, 0x55);
        break;
    case 13: case 30: case 40: case 65: case 66:
        slot = spawnNpcOfType(npcTurretUpdate, item, 2, 0x50);
        break;
    case 14:
        slot = spawnNpcOfType(npcProbeDriod, item, 4, 0x55);
        break;
    case 15:
        slot = spawnNpcOfType(npcAtAtUpdate, item, 2, 0x55);
        break;
    case 31:
        slot = spawnNpcOfType(npcAtStUpdate, item, 2, 0x55);
        break;
    case 71:
        slot = spawnNpcOfType(npcAtPtUpdate, item, 2, 0x55);
        break;
    case 33:
        slot = spawnNpcOfType(npcDebrisFieldUpdate, item, 4, 0x55);
        break;
    case 36: case 44: case 72: case 77:
        slot = spawnNpcOfType(npcShuttleUpdate, item, 2, 0x55);
        break;
    case 37:
        slot = spawnNpcOfType(npcTankDroidUpdate, item, 2, 0x55);
        break;
    case 59: case 60: case 61: case 80:
        slot = spawnNpcOfType(npcGroundTroopUpdate, item, 2, 0x55);
        break;
    case 39:
        slot = spawnNpcOfType(npcWingmanUpdate, item, 2, 0x5A);
        break;
    case 42:
        slot = spawnNpcOfType(npcRadarDishUpdate, item, 2, 0x5A);
        break;
    case 43: case 45: case 46:
        slot = spawnNpcOfType(npcGroundTransportUpdate, item, 2, 0x5A);
        break;
    case 16:
        slot = spawnNpcOfType(craftMountedAnimationNpcHandler, item, 1, 0x64);
        break;
    case 25:
        slot = spawnNpcOfType(datItemActorNpcHandler, item, 1, 0x64);
        break;
    case 47: case 48: case 49: case 52: case 53:
        slot = spawnNpcOfType(npcTrainCarUpdate, item, 2, 0x64);
        break;
    case 50:
        slot = spawnNpcOfType(npcShieldUpdate, item, 4, 0x64);
        break;
    case 51: case 54: case 68: case 75: case 79:
        slot = spawnNpcOfType(func_mission_overlay_800E4070, item, 1, 0x28);
        break;
    case 62:
        slot = spawnNpcOfType(npcWaterCraftUpdate, item, 4, 0x55);
        break;
    case 64:
        slot = spawnNpcOfType(npcWaterCraftUpdate, item, 4, 0x5A);
        break;
    case 55:
        slot = spawnNpcOfType(npcWordDevastatorUpdate, item, 4, 0x55);
        break;
    case 70:
        slot = spawnNpcOfType(tickCraftWithPhasedDestruction, item, 2, 0x28);
        break;
    case 74:
        slot = spawnNpcOfType(func_main_80077AF0, item, 4, 0x64);
        break;
    case 76:
        slot = spawnNpcOfType(npcPowerUpUpdate, item, 1, 0x64);
        break;
    case 81: case 82:
    default:
        slot = spawnNpcOfType(parseDatItemSubtypes1To5, item, 1, 0x28);
        break;
    }
    id = slot;
    dt = 1.0f / 30.0f;
    if (id != 0xFFFF) {
        *(u16 *)(item + 6) = slot;
        slotDispatcherIter(id, 3, &dt);
    }
    return id;
}

s32 slotDispatcherIter(u16, s32, void *);
s16 spawnNpcWithSubtype(void *, void *, s32, s32);
void npcTieVariantUpdate();
void npcShuttleUpdate();
void npcDebrisFieldUpdate();
void npcAtStUpdate();
void npcGroundTroopUpdate();

u16 spawnDatStructureNpcByType(u8 *item) {
    u16 slot;
    u16 id;
    f32 dt;

    slot = 0xFFFF;
    switch (**(u16 **)(item + 0xC)) {
        case 0xC:
        case 0x12:
        case 0x13:
        case 0x29:
        case 0x43:
            slot = spawnNpcWithSubtype(npcTieVariantUpdate, item, 0x22, 0x55);
            break;
        case 0x24:
        case 0x2C:
        case 0x48:
        case 0x4D:
            slot = spawnNpcWithSubtype(npcShuttleUpdate, item, 0x22, 0x55);
            break;
        case 0x21:
            slot = spawnNpcWithSubtype(npcDebrisFieldUpdate, item, 0x22, 0x55);
            break;
        case 0x1F:
            slot = spawnNpcWithSubtype(npcAtStUpdate, item, 0x22, 0x55);
            break;
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x50:
            slot = spawnNpcWithSubtype(npcGroundTroopUpdate, item, 0x22, 0x55);
            break;
    }
    id = slot;
    dt = 1.0f / 30.0f;
    if (id != 0xFFFF) {
        (*(s16 **)(item + 0xC))[3] = slot;
        slotDispatcherIter(id, 3, &dt);
    }
    return id;
}

extern u8 D_main_bss_80130B63;

s32 parseDatSpawnPositions(u8 *arg0) {
    if (D_main_bss_80130B63 == 0 && arg0[3] != 0) {
        return 0;
    }
    switch (*(u16 *)arg0) {
        case 0x0:
        case 0x14:
        case 0x18:
        case 0x4C:
        case 0x52:
            return 1;
        case 0xC:
        case 0xD:
        case 0xE:
        case 0xF:
        case 0x12:
        case 0x13:
        case 0x1E:
        case 0x1F:
        case 0x21:
        case 0x24:
        case 0x25:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x2F:
        case 0x30:
        case 0x31:
        case 0x34:
        case 0x35:
        case 0x37:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x46:
        case 0x47:
        case 0x48:
        case 0x4A:
        case 0x4D:
        case 0x50:
            return (*(s32 *)(arg0 + 0x88) != 0) ? 1 : 2;
        case 0x33:
        case 0x36:
        case 0x44:
        case 0x4B:
        case 0x4F:
            return (*(s32 *)(arg0 + 0x6C) != 0) ? 1 : 2;
        case 0x32:
            return (*(s32 *)(arg0 + 0x6C) != 0) ? 1 : 2;
        case 0x19:
            return (*(s32 *)(arg0 + 0x40) != 0) ? 1 : 2;
        default:
            return 0;
    }
}

s32 isDatItemConditionMet(u8 *item) {
    switch (*(u16 *)item) {
        case 0xC:
        case 0xD:
        case 0xE:
        case 0xF:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x1E:
        case 0x1F:
        case 0x21:
        case 0x24:
        case 0x25:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x2F:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x46:
        case 0x47:
        case 0x48:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4F:
        case 0x50:
        case 0x52:
            if (*(s32 *)(item + 0x60) != 0 && gObjectiveBooleans[*(s32 *)(item + 0x60) - 1] == 0) {
                return 0;
            }
            if (*(s32 *)(item + 0x64) != 0 && gObjectiveCounts[*(s32 *)(item + 0x64) - 1] < *(s32 *)(item + 0x68)) {
                return 0;
            }
            return 1;
        case 0x19:
            if (*(s32 *)(item + 0x34) != 0 && gObjectiveBooleans[*(s32 *)(item + 0x34) - 1] == 0) {
                return 0;
            }
            if (*(s32 *)(item + 0x38) != 0 && gObjectiveCounts[*(s32 *)(item + 0x38) - 1] < *(s32 *)(item + 0x3C)) {
                return 0;
            }
            return 1;
        default:
            return 1;
    }
}

s32 missionCleanupNoopHook(void) {
    return 1;
}

void datItemSetObjectiveBooleanCount(s32 booleanIndex, s32 booleanValue, s32 count1Index, s32 count1Value, s32 count2Index, s32 count2Value) {
    if (booleanIndex != 0) {
        gObjectiveBooleans[booleanIndex - 1] = booleanValue;
    }
    if (count1Index != 0) {
        gObjectiveCounts[count1Index - 1] += count1Value;
    }
    if (count2Index != 0) {
        gObjectiveCounts[count2Index - 1] += count2Value;
    }
}

typedef struct {
    s32 countIdx;
    s32 delta;
    s32 boolIdx;
    u8 pad0C[3];
    u8 value;
} DatTriggerEffect;

void applyDatObjectiveTriggerEffect(u8 *item, u8 which) {
    DatTriggerEffect *e;

    switch (*(u16 *)item) {
        case 0x18:
            e = (DatTriggerEffect *)(item + 0x38);
            if (*(s32 *)(item + 0x28) != 0 && gObjectiveBooleans[*(s32 *)(item + 0x28) - 1] == 0) {
                return;
            }
            if (*(s32 *)(item + 0x2C) != 0 && gObjectiveCounts[*(s32 *)(item + 0x2C) - 1] < *(s32 *)(item + 0x30)) {
                return;
            }
            break;
        case 0x19:
            e = (DatTriggerEffect *)(item + 0x48);
            break;
        default:
            return;
    }
    if (which != 1) {
        e++;
    }
    if (e->countIdx != 0) {
        gObjectiveCounts[e->countIdx - 1] += e->delta;
    }
    if (e->boolIdx != 0) {
        gObjectiveBooleans[e->boolIdx - 1] = e->value;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/65540", fake_func_80065A5C);

INCLUDE_RODATA("asm/nonmatchings/main/65540", D_main_8003C25C);
