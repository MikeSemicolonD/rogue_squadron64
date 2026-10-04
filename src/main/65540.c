#include "common.h"
#include "common_types.h"

#include "level_objectives.h"

#include "main/65540.h"

INCLUDE_RODATA("asm/nonmatchings/main/65540", D_main_8003B830);

INCLUDE_ASM("asm/nonmatchings/main/65540", load_dat_file_assets);

INCLUDE_ASM("asm/nonmatchings/main/65540", setupNpcUpdateFunctions);

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
