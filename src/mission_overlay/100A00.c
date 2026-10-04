#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", resolveCraftAnimationNodeHandles);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", applyCraftAnimationKeyframePose);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", despawnCraftAnimationSlotNpcs);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", despawnCraftAnimationSlotNpcsAndMarkStopping);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", allocateCraftAnimationStateForSlot);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", tickCraftAnimationSlot);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", freePlayerAuxBuffersIfActive);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", resetCraftAnimationStateForSlot);

typedef struct {
    u8 unk0[0x12];
    u8 unk12;
    u8 unk13;
    f32 unk14;
} CraftAnimSlot;

extern CraftAnimSlot D_mission_overlay_8010CF20[];

void setCraftAnimationSlotParams(u8 slot, u8 flag, f32 value) {
    D_mission_overlay_8010CF20[slot].unk12 = flag;
    D_mission_overlay_8010CF20[slot].unk14 = value;
}

u8 getCraftAnimationSlotFlag(u8 slot) {
    return D_mission_overlay_8010CF20[slot].unk13;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", getCraftAnimationSlotValue);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/100A00", D_mission_overlay_800A9548);
