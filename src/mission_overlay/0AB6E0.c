#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", playerSnowSpeederInit);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", composeEffectObjectTransformMatrix);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", tickEffectObjectMotionAndOrientation);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AB6E0", D_mission_overlay_800A536C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", tickCinematicEffectObject);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", playerSnowSpeederUpdate);

s32 getPlayerVehicleId(s32);
s32 slotDispatcherIter(u16, s32, void *);
extern u8 *D_mission_overlay_8010B6D0;
typedef struct {
    u8 pad0[0x18];
    u8 cmd;
    u8 pad19[7];
} SpecialSlotEffectArgs;
void triggerPlayerVehicleSpecialSlotEffect(void) {
    SpecialSlotEffectArgs args;

    if (getPlayerVehicleId(0) == 4 && D_mission_overlay_8010B6D0[0x2C] != 0 && D_mission_overlay_8010B6D0[0x2D] != 0) {
        args.cmd = 0xD;
        slotDispatcherIter(*(u16 *)(D_mission_overlay_8010B6D0 + 0xF0), 9, &args);
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", fake_func_800AD378);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AB6E0", D_mission_overlay_800A53D4);
