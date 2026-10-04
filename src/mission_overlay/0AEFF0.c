#include "common.h"
#include "common_types.h"

#include "mission_overlay/0AEFF0.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", initPlayerCraftTrailBuffers);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", computeCraftSelectTurnFromInput);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", populateCutsceneSubtitleTextIds);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", playRandomCutsceneVoiceLine);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", integrateCraftVelocityAndCollide);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", playCutsceneObjectImpactSound);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", tickCutsceneObject);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", findNearestSceneObjectToPoint);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", loadPlayerStartPosition);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AEFF0", D_mission_overlay_800A55C0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", spawnSceneDebrisAndEffectCluster);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", spawnNpcDestructionDebris);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", updateSplineCraftTransform);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", computeOrientedTransformFromQuat);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", tickCinematicObjectStateMachine);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", updatePlayerCraftPhysics);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", applyCraftCapabilityFlags);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", initPlayerCraftMovementMode);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", tryPlaySpatialSoundWithGates);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", scheduleSceneFormatMessageTimed);

s32 stopRumbleEffect(s32);

void cancelSceneQueueHandle(void *arg0) {
    s32 temp_a0;

    temp_a0 = (*(s32 *)((u8 *)(arg0) + 0x1C0));
    if (temp_a0 != -1) {
        stopRumbleEffect(temp_a0);
        (*(s32 *)((u8 *)(arg0) + 0x1C0)) = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", playSpeechClipOncePerChange);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", playSpeechClipOncePerLevel);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", resetSpeechOncePerLevelFlag);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", setPlayerSlotPositionVec3);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", destroySceneNpcsAndUnlink);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", decayWeaponCooldownTimer);

extern f32 D_mission_overlay_8010B7A0;

f32 getWeaponChargeLevel(void) {
    return D_mission_overlay_8010B7A0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", advancePitchTowardTarget);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", fake_func_800B42BC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AEFF0", D_mission_overlay_800A5810);
