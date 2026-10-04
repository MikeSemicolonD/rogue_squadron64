#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", computeTrackedObjectWorldAnchor);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0ADF80", D_mission_overlay_800A53E0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0ADF80", D_mission_overlay_800A53F8);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", updateCinematicCameraStateMachine);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", submitCameraTrackedObjectToRender);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", emitEffectParticlesAlongPath);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", loadEffectModelInstancePool);

extern s8 D_mission_overlay_8010B6E8;

void resetEffectSequenceState(void) {
    D_mission_overlay_8010B6E8 = 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", freeEffectModelInstancePool);

extern s32 D_mission_overlay_8010B738;

s32 getEffectModelPoolHandle(void) {
    return D_mission_overlay_8010B738;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", beginCameraViewTransition);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", requestCameraSnapToTrackedAnchor);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", beginCameraTrackedTransition);

void advanceCameraTransitionOnCue(s32 arg0) {
    if (((u8) (*(s8 *)((u8 *)(&D_mission_overlay_8010B6E8) + 0)) == 3) && ((*(s32 *)((u8 *)(&D_mission_overlay_8010B6E8) + 0x50)) == arg0)) {
        (*(s8 *)((u8 *)(&D_mission_overlay_8010B6E8) + 0)) = 4;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", isCameraTransitionIdle);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", fake_func_800AE3E4);
