#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", allocObjectPoolNode);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", unlinkAndFreeChildNpcNode);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", resetObjectContextPool);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", freeAllObjectContextPoolNodes);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", createAndInitObject);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", clearPendingAndDestroyChildNpc);

s32 destroyNpcSlotByIndex(u16);

void destroyObjectOwnedNpcSlot(void *arg0) {
    if ((*(u8 *)((u8 *)(arg0) + 0x1A4)) != 0) {
        destroyNpcSlotByIndex((*(u16 *)((u8 *)(arg0) + 0x198)));
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", fake_func_800EC6EC);
