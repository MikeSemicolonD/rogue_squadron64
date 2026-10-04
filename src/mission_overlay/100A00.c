#include "common.h"
#include "common_types.h"

typedef struct {
    u8 *unk0;
    u8 *unk4;
    void *unk8;
    void *unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
} CraftAnimSlot;

extern CraftAnimSlot D_mission_overlay_8010CF20[];

void despawnCraftAnimationSlotNpcs(u8);
void rs_free(void *);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", resolveCraftAnimationNodeHandles);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", applyCraftAnimationKeyframePose);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", despawnCraftAnimationSlotNpcs);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", despawnCraftAnimationSlotNpcsAndMarkStopping);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", allocateCraftAnimationStateForSlot);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/100A00", tickCraftAnimationSlot);

void freePlayerAuxBuffersIfActive(u8 index) {
    if (*D_mission_overlay_8010CF20[index].unk4 != 0) {
        despawnCraftAnimationSlotNpcs(index);
        rs_free(D_mission_overlay_8010CF20[index].unk8);
        rs_free(D_mission_overlay_8010CF20[index].unkC);
    }
}

typedef struct {
    u8 pad[0xF4];
    f32 unkF4;
    f32 unkF8;
} CraftAnimCamera;

extern CraftAnimCamera D_mission_overlay_8010CF38;

void resetCraftAnimationStateForSlot(u8 index) {
    u8 *obj;

    despawnCraftAnimationSlotNpcs(index);
    obj = D_mission_overlay_8010CF20[index].unk0;
    D_mission_overlay_8010CF20[index].unk10 = 0;
    D_mission_overlay_8010CF20[index].unk11 = 0;
    D_mission_overlay_8010CF20[index].unk12 = 0;
    D_mission_overlay_8010CF20[index].unk13 = 0;
    D_mission_overlay_8010CF38.unkF4 = *(f32 *)(obj + 0xE8);
    D_mission_overlay_8010CF38.unkF8 = 1.0f;
}

void setCraftAnimationSlotParams(u8 slot, u8 flag, f32 value) {
    D_mission_overlay_8010CF20[slot].unk12 = flag;
    D_mission_overlay_8010CF20[slot].unk14 = value;
}

u8 getCraftAnimationSlotFlag(u8 slot) {
    return D_mission_overlay_8010CF20[slot].unk13;
}

f32 getCraftAnimationSlotValue(u8 slot) {
    return D_mission_overlay_8010CF20[slot].unk14;
}

__asm__(".section .rodata
    .word 0xB8480003
.section .text");
