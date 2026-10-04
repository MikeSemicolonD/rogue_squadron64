#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", calculateDatItemDistanceToPlayer);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", getScaledPlayerCraftSpeed);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", playObjectiveVoiceLine1);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", playObjectiveVoiceLine2);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", dispatchHudEffectUpdate);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", delegateToLevelStageTick);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", triggerNamedAssetCue);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", triggerSoundCueByType);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", fake_func_800C7DB4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C84A0", D_mission_overlay_800A6968);
