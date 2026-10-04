#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", allocObjectPoolNode);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", unlinkAndFreeChildNpcNode);

s32 clearObjectPoolStateFlag();
s32 resetCraftSubsystemGlobal();
s32 resetObjectPoolListHead();
extern s32 D_mission_overlay_8010C0D0;
extern s32 D_mission_overlay_8010C0D4;

void resetObjectContextPool(void) {
    D_mission_overlay_8010C0D0 = 0;
    D_mission_overlay_8010C0D4 = 0;
    D_mission_overlay_8010C0D0 = 0;
    resetCraftSubsystemGlobal();
    resetObjectPoolListHead();
    clearObjectPoolStateFlag();
}

s32 rs_free(s32);

void freeAllObjectContextPoolNodes(void) {
    s32 temp_a0;
    s32 temp_a0_2;

    if (D_mission_overlay_8010C0D0 != 0) {
        do {
            temp_a0 = D_mission_overlay_8010C0D0;
            D_mission_overlay_8010C0D0 = (*(s32 *)((u8 *)(temp_a0) + 0xC));
            rs_free(temp_a0);
        } while (D_mission_overlay_8010C0D0 != 0);
    }
    if (D_mission_overlay_8010C0D4 != 0) {
        do {
            temp_a0_2 = D_mission_overlay_8010C0D4;
            D_mission_overlay_8010C0D4 = (*(s32 *)((u8 *)(temp_a0_2) + 0xC));
            rs_free(temp_a0_2);
        } while (D_mission_overlay_8010C0D4 != 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", createAndInitObject);

s32 clearPendingChildNpc(s32);
s32 unlinkAndFreeChildNpcNode(s32);

s32 clearPendingAndDestroyChildNpc(s32 *arg0) {
    clearPendingChildNpc(*arg0);
    unlinkAndFreeChildNpcNode(*arg0);
    return 1;
}

s32 destroyNpcSlotByIndex(u16);

void destroyObjectOwnedNpcSlot(void *arg0) {
    if ((*(u8 *)((u8 *)(arg0) + 0x1A4)) != 0) {
        destroyNpcSlotByIndex((*(u16 *)((u8 *)(arg0) + 0x198)));
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", fake_func_800EC6EC);
