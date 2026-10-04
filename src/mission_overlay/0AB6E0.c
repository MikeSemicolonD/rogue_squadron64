#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", playerSnowSpeederInit);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", composeEffectObjectTransformMatrix);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", tickEffectObjectMotionAndOrientation);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AB6E0", D_mission_overlay_800A536C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", tickCinematicEffectObject);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", playerSnowSpeederUpdate);

typedef struct {
    u8 pad0[0x18];
    u8 type;
} SpecialSlotMsg;

extern s32 getPlayerVehicleId(s32);
extern s32 slotDispatcherIter(u16, s32, void *);
extern u8 *D_mission_overlay_8010B6D0;

void triggerPlayerVehicleSpecialSlotEffect(void) {
    SpecialSlotMsg msg;

    if (getPlayerVehicleId(0) == 4 && D_mission_overlay_8010B6D0[0x2C] != 0 && D_mission_overlay_8010B6D0[0x2D] != 0) {
        msg.type = 0xD;
        slotDispatcherIter(*(u16 *)(D_mission_overlay_8010B6D0 + 0xF0), 9, &msg);
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", fake_func_800AD378);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AB6E0", D_mission_overlay_800A53D4);
