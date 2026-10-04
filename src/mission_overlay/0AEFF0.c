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

void playSpeechClip(s32, s32, f32, u16);
extern s32 D_mission_overlay_801096B4;
extern f32 D_mission_overlay_801096B0;

void playSpeechClipOncePerChange(s32 arg0, s32 arg1) {
    if (arg0 != D_mission_overlay_801096B4 && arg0 != 0x28C) {
        playSpeechClip(arg0, 0x73, 0, arg1);
        D_mission_overlay_801096B4 = arg0;
        D_mission_overlay_801096B0 = 5.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", playSpeechClipOncePerLevel);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", resetSpeechOncePerLevelFlag);

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} PlayerSlotVec3;

void setPlayerSlotPositionVec3(u8 idx, PlayerSlotVec3 *v) {
    struct player_struct *p = gPlayers;

    *(PlayerSlotVec3 *)&p[idx].inner.unk178[8] = *v;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", destroySceneNpcsAndUnlink);

extern f32 D_mission_overlay_801096B0;

void decayWeaponCooldownTimer(s32 arg0, f32 arg1) {
    if (D_mission_overlay_801096B0 > 0.0f) {
        D_mission_overlay_801096B0 -= arg1;
    }
}

extern f32 D_mission_overlay_8010B7A0;

f32 getWeaponChargeLevel(void) {
    return D_mission_overlay_8010B7A0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", advancePitchTowardTarget);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", fake_func_800B42BC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AEFF0", D_mission_overlay_800A5810);
