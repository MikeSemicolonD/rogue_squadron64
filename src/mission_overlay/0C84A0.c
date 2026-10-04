#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", calculateDatItemDistanceToPlayer);

void *getCraftRecordByIdx(s32);

f32 getScaledPlayerCraftSpeed(void) {
    return (*(f32 *)((u8 *)(getCraftRecordByIdx(0)) + 4)) * 4.0f;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", spawnEffectOnNamedDatItem);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", initActorTowardNamedDatItem);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", initAnchoredActorTowardNamedDatItem);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", getDatItemHealth);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", getDatItemHealthPercentage);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", despawnEffectOnNamedDatItem);

extern f32 D_main_bss_8013973C;

void setLevelObjectTrackingScalar(f32 arg0) {
    D_main_bss_8013973C = arg0;
}

void playSpeechClip(s32, s32, f32, s32);

void playObjectiveVoiceLine1(s32 arg0) {
    playSpeechClip(arg0, 0x73, 0, 0x43);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", playObjectiveVoiceLine2);

s32 initSpeechPlaybackState();

void dispatchHudEffectUpdate(void) {
    initSpeechPlaybackState();
}

s32 triggerStageMusicForNamedDatItem();

void delegateToLevelStageTick(void) {
    triggerStageMusicForNamedDatItem();
}

s32 triggerStageAmbientForNamedDatItem();

void triggerNamedAssetCue(void) {
    triggerStageAmbientForNamedDatItem();
}

s32 initSoundCueRequest();

void triggerSoundCueByType(void) {
    initSoundCueRequest();
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", fake_func_800C7DB4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C84A0", D_mission_overlay_800A6968);
