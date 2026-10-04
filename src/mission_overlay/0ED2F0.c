#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ED2F0", tickCraftMountedAnimationEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ED2F0", craftMountedAnimationNpcHandler);

s32 slotDispatcherIter(u16, s32, s32);
extern u16 D_main_bss_8013959C;

void dispatchSlotActionTwelveByGlobalId(void) {
    slotDispatcherIter(D_main_bss_8013959C, 0xC, 0);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ED2F0", fake_func_800ECE04);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0ED2F0", D_mission_overlay_800A8920);
