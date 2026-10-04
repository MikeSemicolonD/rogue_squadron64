#include "common.h"
#include "common_types.h"

typedef struct RsHeapBlock {
    struct RsHeapBlock *next;
    struct RsHeapBlock *prev;
    s32 size;
    s32 used;
} RsHeapBlock;

extern RsHeapBlock *gRsHeapBase;
extern RsHeapBlock *gRsHeapTail;
extern s32 gRsHeapTotalFree;
extern s32 gRsHeapMaxAlloc;

s32 initRsMallocHeap(RsHeapBlock *base, s32 size) {
    RsHeapBlock *tail;
    s32 avail;

    if (base != NULL) {
        avail = size - 0x10;
        gRsHeapBase = base;
        gRsHeapTail = tail = (RsHeapBlock *)((u8 *)base + avail);
        gRsHeapTotalFree = avail;
        gRsHeapMaxAlloc = size - 0x36;
        base->next = tail;
        base->prev = NULL;
        base->size = avail;
        base->used = 0;
        tail->next = NULL;
        tail->prev = base;
        tail->size = 0;
        tail->used = 0;
        return 1;
    }
    gRsHeapBase = NULL;
    return 0;
}

s32 getRsHeapMaxAllocSize(void) {
    if (gRsHeapBase != NULL) {
        return gRsHeapMaxAlloc - 0x23;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/05F80", allocRsHeapBlock);

INCLUDE_ASM("asm/nonmatchings/main/05F80", freeRsHeapBlock);

void noopHandler_80005560(void) {
}

INCLUDE_ASM("asm/nonmatchings/main/05F80", fake_func_80005568);
