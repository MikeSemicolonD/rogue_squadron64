#include "common.h"
#include "common_types.h"

typedef struct RsHeapBlock {
    struct RsHeapBlock *next;
    struct RsHeapBlock *prev;
    s32 size;
    s32 *owner;
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
        base->owner = NULL;
        tail->next = NULL;
        tail->prev = base;
        tail->size = 0;
        tail->owner = NULL;
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

void *allocRsHeapBlock(s32 size, s32 *owner) {
    RsHeapBlock *b;
    RsHeapBlock *n;
    u32 need;
    void *ret;

    if (gRsHeapBase != NULL) {
        b = gRsHeapBase;
        need = ((size + 15) & ~15) + 16;
        while (b->next != NULL) {
            if ((u32)b->size >= need && b->owner == NULL) {
                n = (RsHeapBlock *)((u8 *)b + need);
                ret = (u8 *)b + 0x10;
                n->size = b->size - need;
                n->prev = b;
                n->next = b->next;
                n->owner = NULL;
                gRsHeapMaxAlloc -= need;
                b->next->prev = b;
                b->size = need;
                b->owner = owner;
                b->next = n;
                goto done;
            }
            b = b->next;
        }
        ret = NULL;
done:
        return ret;
    }
    return NULL;
}

void freeRsHeapBlock(void *ptr) {
    RsHeapBlock *b = (RsHeapBlock *)((u8 *)ptr - 0x10);

    if (ptr != NULL) {
        gRsHeapMaxAlloc += b->size;
        *b->owner = 0;
        b->owner = NULL;
        if (b->next->owner == NULL) {
            b->size += b->next->size;
            if (b->next->next != NULL) {
                b->next = b->next->next;
            } else {
                b->next->prev = b;
            }
        }
        if (b->prev != NULL && b->prev->owner == NULL) {
            b->prev->size += b->size;
            b->prev->next = b->next;
        }
    }
}

void noopHandler_80005560(void) {
}

INCLUDE_ASM("asm/nonmatchings/main/05F80", fake_func_80005568);
