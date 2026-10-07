#include "common.h"
#include "common_types.h"

#include "level_objectives.h"

#include "main/65540.h"

INCLUDE_RODATA("asm/nonmatchings/main/65540", D_main_8003B830);

INCLUDE_ASM("asm/nonmatchings/main/65540", load_dat_file_assets);

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
