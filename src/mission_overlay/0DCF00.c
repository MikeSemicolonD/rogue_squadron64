#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DCF00", npcRadarDishComputeAimMotion);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DCF00", npcRadarDishUpdate);

extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern void initActorMotionParams(s32, f32, f32, f32, f32);

void npcInitMinimalNoAnim(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);

    npc[0xB1] = 1;
    *(f32 *)(npc + 0x60) = *(f32 *)(*(u8 **)(npc + 0x34) + 0x94);
    setNpcHealth(*(s32 *)(npc + 0x38), *(u8 **)(npc + 0x34) + 0x6C, *(u8 **)(npc + 0x34));
    initActorMotionParams(*(s32 *)(npc + 0x38), *(f32 *)(*(u8 **)(npc + 0x34) + 0xA0), *(f32 *)(*(u8 **)(npc + 0x34) + 0xA4), 0.0f, 0.0f);
    setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(*(u8 **)(npc + 0x34) + 0x8C));
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DCF00", fake_func_800DD2C4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DCF00", D_mission_overlay_800A7DD0);
