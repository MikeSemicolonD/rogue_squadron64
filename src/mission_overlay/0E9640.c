#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E9640", runDestructionPhaseSequence);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E9640", tickCraftWithPhasedDestruction);

extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);

void initNpcHealthAndDetailFromChild(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 *def = *(u8 **)(npc + 0x34);

    *(s16 *)(npc + 0x3E) = 0;
    *(f32 *)(npc + 0x50) = *(f32 *)(def + 0x94);
    setNpcHealth(*(s32 *)(npc + 0x38), *(u8 **)(npc + 0x34) + 0x6C, *(u8 **)(npc + 0x34));
    setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(*(u8 **)(npc + 0x34) + 0xAC));
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E9640", fake_func_800E9AD8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E9640", D_mission_overlay_800A86C8);
