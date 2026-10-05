#include "common.h"

#include "mission_overlay/0C7EB0.h"
#include "mission_overlay/0C84A0.h"
#include "mission_overlay/level_objective_handling/lv_0.h"

s32 D_mission_overlay_8010B690 = 0;
s32 D_mission_overlay_8010B694 = 0;
s32 D_mission_overlay_8010B698 = 0;
s32 D_mission_overlay_8010B69C = 0;
s32 D_mission_overlay_8010B6A0 = 0;
s32 D_mission_overlay_8010B6A4 = 0;
s32 D_mission_overlay_8010B6A8 = 0;
// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
u32 data_pad_lv_0 = 0x8FC50050;

s32 lv0_initializeObjectTracking(void) {
    D_mission_overlay_8010B690 = 0;
    D_mission_overlay_8010B694 = 0;
    D_mission_overlay_8010B698 = 0;
    D_mission_overlay_8010B69C = 0;
    D_mission_overlay_8010B6A0 = 0;
    D_mission_overlay_8010B6A4 = 0;
    D_mission_overlay_8010B6A8 = 0;
    setObjectiveBoolean(0x61, 1U);
    setObjectiveBoolean(0x62, 1U);
    setObjectiveBoolean(5, 1U);
    addBooleanCountHandleWrapper(func_mission_overlay_80101934, 0, 0, 1, 0x15);
    addBooleanCountHandleWrapper(func_mission_overlay_801018EC, 0, 0, 0x14, 1);
    setLevelObjectTrackingScalar(7.5f);
    setObjectiveBoolean(0x3C, 1U);
    setObjectiveTimer(2, 0.0f);
    setObjectiveHiddenFlag(1, 1);
    setObjectiveHiddenFlag(1, 2);
    setObjectiveHiddenFlag(1, 3);
    setObjectiveHiddenFlag(1, 4);
    return 0;
}

s32 lv0_checkComplexObjectives(void) {
    char *name;
    s32 a;
    s32 t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24, t25;

    if (getObjectiveCount(2) >= 3) {
        setHudEnableBit4();
        playObjectiveVoiceLine2(0x229, 0.3f);
        return 0;
    }
    if (getObjectiveCount(3) >= 9) {
        setHudEnableBit4();
        playObjectiveVoiceLine2(0x22A, 0.3f);
        return 0;
    }
    if (getObjectiveCount(0xA) >= 6) {
        activateObjectiveCompleteFlag(3);
        activateObjectiveCompleteFlag(4);
        setHudEnableBit8();
        return 0;
    }
    if (getObjectiveTimer(2) >= 29.0f && calculateDatItemDistanceToPlayer(name = "ROGUE_10") >= 32.0f && getDatItemHealth(name) > 0) {
        dealDamagetoDatItem((u8 *)name, 0x1E);
    }
    if (getObjectiveTimer(6) >= 6.0f) {
        t1 = getObjectiveBoolean(0x3C);
        if (t1 == 1 && D_mission_overlay_8010B6A4 == t1) {
            setObjectiveBoolean(0x3C, 0);
            setObjectiveBoolean(0x3D, 1);
        }
    }
    t2 = getObjectiveBoolean(0x1F);
    if (t2 == 1) {
        t3 = getObjectiveBoolean(0x18);
        if (t3 == t2 && getObjectiveBoolean(0x19) == t3 && getObjectiveBoolean(0x33) == 0) {
            setObjectiveBoolean(0x33, 1);
        }
    }
    t4 = getObjectiveBoolean(0x26);
    if (t4 == 1) {
        t5 = getObjectiveBoolean(0x27);
        if (t5 == t4) {
            t6 = getObjectiveBoolean(0x1B);
            if (t6 == t5) {
                t7 = getObjectiveBoolean(0x1C);
                if (t7 == t6 && getObjectiveBoolean(0x1D) == t7 && getObjectiveBoolean(0x34) == 0) {
                    setObjectiveBoolean(0x34, 1);
                }
            }
        }
    }
    t8 = getObjectiveBoolean(0x20);
    if (t8 == 1) {
        t9 = getObjectiveBoolean(0x21);
        if (t9 == t8) {
            t10 = getObjectiveBoolean(0x28);
            if (t10 == t9) {
                t11 = getObjectiveBoolean(0x29);
                if (t11 == t10) {
                    t12 = getObjectiveBoolean(0x2A);
                    if (t12 == t11 && getObjectiveBoolean(0x2B) == t12 && getObjectiveBoolean(0x35) == 0) {
                        setObjectiveBoolean(0x35, 1);
                    }
                }
            }
        }
    }
    t13 = getObjectiveBoolean(0x22);
    if (t13 == 1) {
        t14 = getObjectiveBoolean(0x23);
        if (t14 == t13) {
            t15 = getObjectiveBoolean(0x2D);
            if (t15 == t14) {
                t16 = getObjectiveBoolean(0x2E);
                if (t16 == t15 && getObjectiveBoolean(0x2F) == t16 && getObjectiveBoolean(0x36) == 0) {
                    setObjectiveBoolean(0x36, 1);
                }
            }
        }
    }
    t17 = getObjectiveBoolean(0x24);
    if (t17 == 1 && getObjectiveBoolean(0x25) == t17 && getObjectiveBoolean(0x37) == 0) {
        setObjectiveBoolean(0x37, 1);
    }
    t18 = getObjectiveBoolean(0x18);
    if (t18 == 1 && getObjectiveBoolean(0x19) == t18 && getObjectiveBoolean(0x1A) == 0) {
        setObjectiveBoolean(0x1A, 1);
    }
    t19 = getObjectiveBoolean(0x1B);
    if (t19 == 1) {
        t20 = getObjectiveBoolean(0x1C);
        if (t20 == t19 && getObjectiveBoolean(0x1D) == t20 && getObjectiveBoolean(0x1E) == 0) {
            setObjectiveBoolean(0x1E, 1);
        }
    }
    t21 = getObjectiveBoolean(0x28);
    if (t21 == 1) {
        t22 = getObjectiveBoolean(0x29);
        if (t22 == t21) {
            t23 = getObjectiveBoolean(0x2A);
            if (t23 == t22 && getObjectiveBoolean(0x2B) == t23 && getObjectiveBoolean(0x2C) == 0) {
                setObjectiveBoolean(0x2C, 1);
            }
        }
    }
    t24 = getObjectiveBoolean(0x2D);
    if (t24 == 1) {
        t25 = getObjectiveBoolean(0x2E);
        if (t25 == t24 && getObjectiveBoolean(0x2F) == t25 && getObjectiveBoolean(0x30) == 0) {
            setObjectiveBoolean(0x30, 1);
        }
    }
    if (D_mission_overlay_8010B6A8 == 1) {
        if (getObjectiveTimer(7) >= 6.0f) {
            D_mission_overlay_8010B6A8 = 0;
        }
    }
    if (D_mission_overlay_8010B6A8 == 0) {
        if (D_mission_overlay_8010B690 == 0) {
            D_mission_overlay_8010B690 = 1;
            D_mission_overlay_8010B6A8 = 1;
            setObjectiveTimer(7, 5.0f);
            return 0;
        }
        if (D_mission_overlay_8010B690 == 1 && D_mission_overlay_8010B694 == 0) {
            D_mission_overlay_8010B694 = D_mission_overlay_8010B690;
            D_mission_overlay_8010B6A8 = D_mission_overlay_8010B690;
            setObjectiveTimer(7, 0.0f);
            playObjectiveVoiceLine2(0x224, 0.3f);
            return 0;
        }
        if (D_mission_overlay_8010B694 == 1 && D_mission_overlay_8010B698 == 0) {
            D_mission_overlay_8010B698 = D_mission_overlay_8010B694;
            D_mission_overlay_8010B6A8 = D_mission_overlay_8010B694;
            setObjectiveTimer(7, 5.0f);
            setObjectiveHiddenFlag(0, 1);
            setObjectiveHiddenFlag(0, 2);
            return 0;
        }
        if (getObjectiveBoolean(0x1F) == 0 && getObjectiveBoolean(5) == 0 && getObjectiveBoolean(0x1A) == 0 && D_mission_overlay_8010B69C == 0) {
            D_mission_overlay_8010B69C = 1;
            D_mission_overlay_8010B6A8 = 1;
            setObjectiveTimer(7, 1.0f);
            playObjectiveVoiceLine2(0x225, 0.3f);
            return 0;
        }
        a = getObjectiveBoolean(0x16);
        if (a == 1 && D_mission_overlay_8010B6A0 == 0) {
            D_mission_overlay_8010B6A0 = a;
            D_mission_overlay_8010B6A8 = a;
            setObjectiveTimer(7, 0.0f);
            playObjectiveVoiceLine2(0x1F0, 0.3f);
            return 0;
        }
        if (getObjectiveCount(1) >= 0x15 && D_mission_overlay_8010B6A4 == 0) {
            D_mission_overlay_8010B6A4 = 1;
            D_mission_overlay_8010B6A8 = 1;
            activateObjectiveCompleteFlag(1);
            activateObjectiveCompleteFlag(2);
            setHudFlagBit40AndStoreArg("CameraPosition_01");
            setObjectiveTimer(6, 0.0f);
            setObjectiveTimer(7, 0.0f);
            playObjectiveVoiceLine2(0x228, 2.0f);
            setObjectiveHiddenFlag(0, 3);
            setObjectiveHiddenFlag(0, 4);
            triggerSoundCueByType(4);
        }
        return 0;
    }
    return 0;
}

void func_mission_overlay_801018EC(void) {
    playObjectiveVoiceLine2(0x26E, 0.3f);
    playObjectiveVoiceLine2(0x148, 0.3f);
    playObjectiveVoiceLine2(0x270, 0.3f);
}


void func_mission_overlay_80101934(void) {
    setObjectiveCount(0x73, 6U);
}

s32 lv0_80101954(void) {
    return 0;
}

s32 lv0_calculateFriendliesSaved(void) {
    setFriendliesSaved(0x33 - (getObjectiveCount(2) + getObjectiveCount(3)));
    return 0;
}

// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
const u32 rodata_pad_lv_0[] = {
    0xA8480000,
    0xB8480003,
};
