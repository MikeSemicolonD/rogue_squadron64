#include "common.h"
#include "common_types.h"

s32 slotDispatcherIter(u16, s32, void *);

typedef struct {
    u16 unk0;
    s16 pad2;
    s16 unk4;
    u16 unk6;
    s32 unk8;
} SlotAction5Args;

typedef struct {
    u16 unk0;
    u16 slot;
    s32 active;
    u16 *unk8;
} SlotAction5Src;

s32 dispatchSlotAction5IfActive(s32 arg0, SlotAction5Src *arg1) {
    SlotAction5Args args;
    u16 *p;

    if (arg1->active != 1) {
        return 0;
    }
    p = arg1->unk8;
    args.unk0 = 0xFFFF;
    args.unk4 = 7;
    args.unk6 = *p;
    args.unk8 = 0;
    slotDispatcherIter(arg1->slot, 5, &args);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F0980", fake_func_800EFDDC);
