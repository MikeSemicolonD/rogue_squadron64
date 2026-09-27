#include "common.h"

#include "level_objectives.h"
#include "mission_state.h"
#include "mission_stats.h"

#include "main/04030.h"
#include "main/6C310.h"
#include "mission_overlay/0C7EB0.h"
#include "mission_overlay/0F3E90.h"
#include "mission_overlay/level_objective_handling/all_levels.h"

struct D_8010A450_type gMissionObjectiveVtable[0x15] = {
    {lv0_initializeObjectTracking,
    lv0_objectiveSlot1,
    lv0_calculateFriendliesSaved,
    lv0_checkComplexObjectives,},

    {lv1_initializeObjectTracking,
    lv1_objectiveSlot1,
    lv1_calculateFriendliesSaved,
    lv1_checkComplexObjectives,},

    {lv2_initializeObjectTracking,
    lv2_objectiveSlot1,
    lv2_calculateFriendliesSaved,
    lv2_checkComplexObjectives,},

    {lv3_initializeObjectTracking,
    lv3_objectiveSlot1,
    lv3_calculateFriendliesSaved,
    lv3_checkComplexObjectives,},

    {lv4_initializeObjectTracking,
    lv4_objectiveSlot1,
    lv4_calculateFriendliesSaved,
    lv4_checkComplexObjectives,},

    {lv5_initializeObjectTracking,
    lv5_objectiveSlot1,
    lv5_calculateFriendliesSaved,
    lv5_checkComplexObjectives,},

    {lv6_initializeObjectTracking,
    lv6_objectiveSlot1,
    lv6_calculateFriendliesSaved,
    lv6_checkComplexObjectives,},

    {lv7_initializeObjectTracking,
    lv7_objectiveSlot1,
    lv7_calculateFriendliesSaved,
    lv7_checkComplexObjectives,},

    {lv8_initializeObjectTracking,
    lv8_objectiveSlot1,
    lv8_calculateFriendliesSaved,
    lv8_checkComplexObjectives,},

    {lv9_initializeObjectTracking,
    lv9_objectiveSlot1,
    lv9_calculateFriendliesSaved,
    lv9_checkComplexObjectives,},

    {lva_initializeObjectTracking,
    lva_objectiveSlot1,
    lva_calculateFriendliesSaved,
    lva_checkComplexObjectives,},

    {lvb_initializeObjectTracking,
    lvb_objectiveSlot1,
    lvb_calculateFriendliesSaved,
    lvb_checkComplexObjectives,},

    {lvc_initializeObjectTracking,
    lvc_objectiveSlot1,
    lvc_calculateFriendliesSaved,
    lvc_checkComplexObjectives,},

    {lvd_initializeObjectTracking,
    lvd_objectiveSlot1,
    lvd_calculateFriendliesSaved,
    lvd_checkComplexObjectives,},

    {lve_initializeObjectTracking,
    lve_objectiveSlot1,
    lve_calculateFriendliesSaved,
    lve_checkComplexObjectives,},

    {lvf_initializeObjectTracking,
    lvf_objectiveSlot1,
    lvf_calculateFriendliesSaved,
    lvf_checkComplexObjectives,},

    {lvg_initializeObjectTracking,
    lvg_objectiveSlot1,
    lvg_calculateFriendliesSaved,
    lvg_checkComplexObjectives,},

    {lvh_initializeObjectTracking,
    lvh_objectiveSlot1,
    lvh_calculateFriendliesSaved,
    lvh_checkComplexObjectives,},

    {lvi_initializeObjectTracking,
    lvi_objectiveSlot1,
    lvi_calculateFriendliesSaved,
    lvi_checkComplexObjectives,},

    {lvj_initializeObjectTracking,
    lvj_objectiveSlot1,
    lvj_calculateFriendliesSaved,
    lvj_checkComplexObjectives,},

    {lvk_initializeObjectTracking,
    lvk_objectiveSlot1,
    lvk_calculateFriendliesSaved,
    lvk_checkComplexObjectives,},
};

void initializeObjectiveTracking(void) {
    gMissionObjectiveVtable[gCurrentLevel].initializeObjectiveTracking();
}

void dispatchObjectiveSlot1(void) {
    gMissionObjectiveVtable[gCurrentLevel].unk4();
}

void calculateFriendliesSaved(void) {
    gMissionObjectiveVtable[gCurrentLevel].calculateFriendliesSaved();
}

void checkComplexObjectives(void) {
    gMissionObjectiveVtable[gCurrentLevel].checkComplexObjectives();
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C7EB0", dealDamagetoDatItem);

enum Level getCurrentLevel(void) {
    return gCurrentLevel;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C7EB0", getSceneStatePtr);

enum PlayerCraft getLocalPlayerVehicleId(void) {
    return getPlayerVehicleId(0);
}

u32 setObjectiveBoolean(s32 booleanIndex, u8 booleanValue) {
    u32 blah;

    if (booleanIndex != 0) {
        blah = gObjectiveBooleans[booleanIndex - 1];
        gObjectiveBooleans[booleanIndex - 1] = booleanValue;
        return blah;
    } else {
        return 1;
    }
}

void setObjectiveBooleans(u8 *arg0, s8 arg1) {
    u8 *var_a0;
    u8 var_v0;

    while (*arg0 != 0) {
        gObjectiveBooleans[*arg0++ - 1] = arg1;
    }
}

s32 getObjectiveBoolean(s32 booleanIndex) {
    if (booleanIndex != 0) {
        return gObjectiveBooleans[booleanIndex - 1];
    } else {
        return 1U;
    }
}

u32 setObjectiveCount(s32 countIndex, u32 countValue) {
    u32 blah;

    if (countIndex != 0) {
        blah = gObjectiveCounts[countIndex - 1];
        gObjectiveCounts[countIndex - 1] = countValue;
        return blah;
    } else {
        return 0;
    }
}

u32 increaseObjectiveCount(s32 arg0, s32 arg1) {
    if (arg0 != 0) {
        gObjectiveCounts[arg0 - 1] += arg1;
        return gObjectiveCounts[arg0 - 1];
    } else {
        return 0;
    }
}

s32 getObjectiveCount(s32 countIndex) {
    if (countIndex != 0) {
        return gObjectiveCounts[countIndex - 1];
    } else {
        return 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C7EB0", getAndSetByteAtLevelStateTable);

void setObjectiveHiddenFlag(s32 arg0, s32 arg1) {
    u32 temp_a1;
    struct MissionState *why;

    temp_a1 = arg1 - 1;
    if (temp_a1 >= 8) return;

    why = &gMissionState;
    if (arg0 != 0) {
        why->hiddenObjectiveFlags |= 1 << temp_a1;
    } else {
        why->hiddenObjectiveFlags &= ~(1 << temp_a1);
    }
}

void activateObjectiveCompleteFlag(s32 arg0) {
    u32 temp_a1;

    temp_a1 = arg0 - 1;
    if (temp_a1 < 8U) {
        gMissionState.completedObjectiveFlags |= 1 << temp_a1;
    }
}

f32 getObjectiveTimer(s32 timerIndex) {
    return gObjectiveTimers[timerIndex];
}

f32 setObjectiveTimer(s32 timerIndex, f32 timerValue) {
    f32 blah;
    blah = gObjectiveTimers[timerIndex];
    gObjectiveTimers[timerIndex] = timerValue;
    return blah;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C7EB0", getGlobalFloatGameState);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C7EB0", getObjectiveGlobalFloat);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C7EB0", setHudEnableBit4);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C7EB0", setHudEnableBit8);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C7EB0", isLevelStateByteZero);

void setFriendliesSaved(s32 arg0) {
    if (arg0 < 0) {
        arg0 = 0;
    }
    if (arg0 >= 0x100) {
        arg0 = 0xFF;
    }
    missionStats.friendlies_saved = arg0;
}

s16 randMod(s32 arg0) {
    s16 thing = rand();
    return (thing % arg0);
}

u8 addBooleanCountHandleWrapper(void (*handle)(), s32 booleanIndex, s32 booleanValue, s32 countIndex, s32 countValue) {
    return addBooleanCountHandle(handle, booleanIndex, booleanValue, countIndex, (u32) countValue, 0U);
}

u8 addTimerHandleWrapper(void (*handle)(), f32 timerValue) {
    return addTimerHandle(handle, timerValue);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C7EB0", setHudFlagBit40AndStoreArg);
