#include "common.h"

#include "PR/os.h"
#include "main/02420.h"

OSMesgQueue D_main_8010FEE0;
OSMesg D_main_bss_8010FEF8;
struct heapBlockHeader *D_main_bss_8010FEFC;
struct heapBlockHeader *D_main_bss_8010FF00;
u32 bss_pad_02420;
struct D_main_bss_8010FF08_type *D_main_bss_8010FF08;
u32 D_main_bss_8010FF0C;
struct heapBlockHeader *D_main_bss_8010FF10;
struct heapBlockHeader *D_main_bss_8010FF14;
struct heapBlockHeader *D_main_bss_8010FF18;

s32 queueDeferredClearRequest(struct heapBlockHeader *arg0, s32 arg1) {
    if ((arg0 != 0) & (arg1 != 0)) {
        buildHeapFreeList(&D_main_bss_8010FF00, 0, NULL, arg0, (u32)arg0 + arg1, 1);
    } else {
        D_main_bss_8010FF00 = NULL;
    }
    return 1;
}

void clearFrameReadyFlag(void) {
    D_main_bss_8010FEFC = NULL;
}

extern u8 D_main_bss_8011A89A;
extern u8 *D_main_bss_8010FCB0;
extern u32 D_main_bss_801163E4;
struct heapBlockHeader *acquireFreeBufferSlot(void);
s32 computeFramebufferByteSize(void);
void ensureHeapInitialized(void) {
    struct heapBlockHeader *base;
    struct D_main_bss_8010FF08_type region;

    if (D_main_bss_8010FEFC == NULL && D_main_bss_8011A89A == 0 && !(*(u32 *)(D_main_bss_8010FCB0 + 0x44) & 0x80)) {
        base = acquireFreeBufferSlot();
        if (*(u32 *)(D_main_bss_8010FCB0 + 0x44) & 0x200) {
            buildHeapFreeList(&D_main_bss_8010FEFC, 0, NULL, base, (struct heapBlockHeader *)((u32)base + computeFramebufferByteSize()), 1);
        } else {
            u32 *end;

            region.dataAddress = (u32)base + computeFramebufferByteSize();
            end = &D_main_bss_801163E4;
            region.dataSize = *end - region.dataAddress;
            if (region.dataSize == 0) {
                buildHeapFreeList(&D_main_bss_8010FEFC, 0, NULL, base, (struct heapBlockHeader *)((u32)base + computeFramebufferByteSize()), 1);
            } else {
                buildHeapFreeList(&D_main_bss_8010FEFC, 1, &region, base, (struct heapBlockHeader *)(*end + computeFramebufferByteSize()), 1);
            }
        }
    }
}

u32 getTotalFreeHeapSize(void) {
    u32 var_a1;
    struct heapBlockHeader *var_a0;
    u32 var_a2;

    var_a0 = D_main_bss_8010FF18;
    var_a1 = 0;
    var_a2 = 0;
    while ((var_a2 < 2) & (var_a0 != NULL)) {
        while (!(var_a0->unk00 & 8)) {
            if (var_a0->unk00 & 1) var_a1 += var_a0->size;
            var_a0 = (struct heapBlockHeader*)((u32)var_a0 + var_a0->size + sizeof(struct heapBlockHeader));
        }
        var_a0 = D_main_bss_8010FF00;
        var_a2++;
    }
    return var_a1;
}

u32 findLargestFreeHeapChunk(void) {
    s32 var_a1;
    struct heapBlockHeader *var_a0;
    u32 var_a2;

    var_a0 = D_main_bss_8010FF18;
    var_a1 = 0;
    var_a2 = 0;
    while ((var_a2 < 2) & (var_a0 != NULL)) {
        while (!(var_a0->unk00 & 8)) {
            if ((var_a0->unk00 & 1) && (var_a1 < var_a0->size)) var_a1 = var_a0->size;
            var_a0 = (struct heapBlockHeader*)((u32)var_a0 + var_a0->size + sizeof(struct heapBlockHeader));
        }
        var_a0 = D_main_bss_8010FF00;
        var_a2++;
    }
    return var_a1;
}

void *rs_malloc(u32 size, u16 flags) {
    struct heapBlockHeader *sp10[2];
    struct heapBlockHeader *var_a0;
    struct heapBlockHeader *var_a1;
    struct heapBlockHeader *var_s2;
    u32 blockSize;
    u32 var_a2;
    u32 var_t0;
    struct heapBlockHeader *temp_a0;

    var_s2 = NULL;
    if (size != 0) {
        osRecvMesg(&D_main_8010FEE0, NULL, 1);
        blockSize = (size + 0xF) & ~0xF;
        if (flags & 4) {
            ensureHeapInitialized();
            var_t0 = 1;
            if (D_main_bss_8010FEFC == NULL) goto why;
            sp10[0] = D_main_bss_8010FEFC;
        } else {
            if (D_main_bss_8010FF00 != NULL) {
                if (flags & 0x10) {
                    sp10[0] = D_main_bss_8010FF00;
                    sp10[1] = D_main_bss_8010FF18;
                } else {
                    sp10[0] = D_main_bss_8010FF18;
                    sp10[1] = D_main_bss_8010FF00;
                }
                var_t0 = 2;
            } else {
                var_t0 = 1;
                sp10[0] = D_main_bss_8010FF18;
            }
        }
        var_a1 = NULL;
        for (var_a2 = 0; var_a2 < var_t0; var_a2++) {
            var_a0 = sp10[var_a2];
            while(!(var_a0->unk00 & 8)) {
                // I hate this, but I can't get it to match any other way...
                if ((var_a0->unk00 & 1) && (var_a0->size >= blockSize) && (var_a1 = var_a0, ((flags & 0x88) != 8))) break;
                var_a0 = (u32)var_a0 + var_a0->size + sizeof(struct heapBlockHeader);
            }
            if (var_a1 == NULL) continue;
            var_s2 = var_a1 + 1;
            var_a1->unk00 = 2;
            var_a1->flags = flags;
            if (blockSize != var_a1->size) {
                temp_a0 = (u32)var_s2 + blockSize;
                if ((u32) (var_a1->size - blockSize) >= 0x20U) {
                    temp_a0->unk00 = 1;
                    temp_a0->size = (s32) ((var_a1->size - blockSize) - 0x10);
                    var_a1->size = blockSize;
                }
            }
            break;
        }
why:
        osSendMesg(&D_main_8010FEE0, NULL, 0);
    }
    return var_s2;
}

static __inline__ u8 rfFree(struct heapBlockHeader *p, struct heapBlockHeader *blk) {
    struct heapBlockHeader *prev;
    struct heapBlockHeader *next;

    prev = NULL;
    while (!(p->unk00 & 8)) {
        next = (struct heapBlockHeader *)((u32)p + p->size + sizeof(struct heapBlockHeader));
        if (p->unk00 & 2) {
            if (blk == p) {
                u8 ok = !(p->unk00 & 4);
                if (!ok) {
                    return 0;
                }
                blk->unk00 = 1;
                if ((next->unk00 & 1) && !(next->unk00 & 4)) {
                    blk->size += sizeof(struct heapBlockHeader) + next->size;
                }
                if (prev != NULL) {
                    if ((prev->unk00 & 1) && !(prev->unk00 & 4)) {
                        prev->size += sizeof(struct heapBlockHeader) + p->size;
                    }
                }
                return 1;
            }
        }
        prev = p;
        p = next;
    }
    return 0;
}

void rs_free(void *ptr) {
    struct heapBlockHeader *blk;

    if (ptr != NULL) {
        osRecvMesg(&D_main_8010FEE0, NULL, 1);
        blk = (struct heapBlockHeader *)ptr - 1;
        if (!rfFree(D_main_bss_8010FF18, blk)) {
            if (D_main_bss_8010FF00 == NULL || !rfFree(D_main_bss_8010FF00, blk)) {
                if (D_main_bss_8010FEFC != NULL) {
                    rfFree(D_main_bss_8010FEFC, blk);
                }
            }
        }
        osSendMesg(&D_main_8010FEE0, NULL, 0);
    }
}

static __inline__ void hfInit(void) {
    OSMesg pad[2];
    osCreateMesgQueue(&D_main_8010FEE0, &D_main_bss_8010FEF8, 1);
    osSendMesg(&D_main_8010FEE0, NULL, 0);
}
void buildHeapFreeList(struct heapBlockHeader **arg0, u32 arg1, struct D_main_bss_8010FF08_type *arg2, struct heapBlockHeader *arg3, struct heapBlockHeader *arg4, u8 arg5) {
    struct heapBlockHeader *a3;
    struct heapBlockHeader *a1;
    struct heapBlockHeader *a0;
    struct heapBlockHeader *t0;
    struct D_main_bss_8010FF08_type *a2;
    u32 pa1;
    s32 t1;
    s32 v1;
    u32 diff;
    u32 t2;

    hfInit();
    if (arg5 != 0) {
        *arg0 = arg3;
        arg3->unk00 = 1;
        (*arg0)->flags = 0;
        (*arg0)->size = (u32)arg4 - (u32)arg3 - 0x20;
    } else {
        a3 = arg3;
        do {
            a1 = a3;
            a3 = (struct heapBlockHeader *)((u8 *)a3 + a3->size + 0x10);
        } while (!(a3->unk00 & 8));
        a1->size = (u32)arg4 - (u32)a1 - 0x20;
    }
    t2 = 0;
    arg4[-1].unk00 = 8;
    arg4[-1].flags = 0;
    arg4[-1].size = 0;
    if (arg1 != 0) {
        do {
            a2 = &arg2[t2];
            a3 = *arg0;
            a1 = (struct heapBlockHeader *)(a2->dataAddress - 0x10);
            t1 = (a2->dataSize + 0xF) & ~0xF;
            if (!(a3->unk00 & 8)) {
                do {
                    a0 = (struct heapBlockHeader *)((u8 *)a3 + a3->size);
                    t0 = a0 + 1;
                    __asm__("" :: "r"(a0));
                    if (((u32)a1 >= (u32)a3) & ((u32)a1 < (u32)t0)) {
                        a1->unk00 = 6;
                        a1->flags = 0;
                        if (a1 != a3) {
                            a3->size = (u32)a1 - (u32)a3 - 0x10;
                        }
                        v1 = (u32)t0 - (u32)a1 - 0x10;
                        diff = v1 - t1;
                        if (v1 != t1) {
                            if (diff >= 0x21) {
                                struct heapBlockHeader *n = (struct heapBlockHeader *)((u8 *)a1 + t1);
                                n[1].unk00 = 1;
                                n[1].flags = 0;
                                n[1].size = diff - 0x10;
                            } else {
                                t1 = v1;
                            }
                        }
                        a1->size = t1;
                        break;
                    }
                    a3 = t0;
                } while (!(a0[1].unk00 & 8));
            }
            t2++;
        } while (t2 < arg1);
    }
}

static __inline__ void imhInit(void) {
    OSMesg pad[4];
    osCreateMesgQueue(&D_main_8010FEE0, &D_main_bss_8010FEF8, 1);
    osSendMesg(&D_main_8010FEE0, NULL, 0);
}
static __inline__ void imhBuild(struct heapBlockHeader **arg0, u32 arg1, struct D_main_bss_8010FF08_type *arg2, struct heapBlockHeader *arg3, struct heapBlockHeader *arg4, u8 arg5) {
    struct heapBlockHeader *a3;
    struct heapBlockHeader *a1;
    struct heapBlockHeader *a0;
    struct heapBlockHeader *t0;
    struct D_main_bss_8010FF08_type *a2;
    u32 pa1;
    s32 t1;
    s32 v1;
    u32 diff;
    u32 t2;

    imhInit();
    if (arg5 != 0) {
        *arg0 = arg3;
        arg3->unk00 = 1;
        (*arg0)->flags = 0;
        (*arg0)->size = (u32)arg4 - (u32)arg3 - 0x20;
    } else {
        a3 = arg3;
        do {
            a1 = a3;
            a3 = (struct heapBlockHeader *)((u8 *)a3 + a3->size + 0x10);
        } while (!(a3->unk00 & 8));
        a1->size = (u32)arg4 - (u32)a1 - 0x20;
    }
    t2 = 0;
    arg4[-1].unk00 = 8;
    arg4[-1].flags = 0;
    arg4[-1].size = 0;
    if (arg1 != 0) {
        do {
            a2 = &arg2[t2];
            a3 = *arg0;
            a1 = (struct heapBlockHeader *)(a2->dataAddress - 0x10);
            t1 = (a2->dataSize + 0xF) & ~0xF;
            if (!(a3->unk00 & 8)) {
                do {
                    a0 = (struct heapBlockHeader *)((u8 *)a3 + a3->size);
                    t0 = a0 + 1;
                    if (((u32)a1 >= (u32)a3) & ((u32)a1 < (u32)t0)) {
                        a1->unk00 = 6;
                        a1->flags = 0;
                        if (a1 != a3) {
                            a3->size = (u32)a1 - (u32)a3 - 0x10;
                        }
                        v1 = (u32)t0 - (u32)a1 - 0x10;
                        diff = v1 - t1;
                        if (v1 != t1) {
                            if (diff >= 0x21) {
                                struct heapBlockHeader *n = (struct heapBlockHeader *)((u8 *)a1 + t1);
                                n[1].unk00 = 1;
                                n[1].flags = 0;
                                n[1].size = diff - 0x10;
                            } else {
                                t1 = v1;
                            }
                        }
                        a1->size = t1;
                        break;
                    }
                    a3 = t0;
                } while (!(a0[1].unk00 & 8));
            }
            t2++;
        } while (t2 < arg1);
    }
}


void initMainHeap(u32 arg0, struct D_main_bss_8010FF08_type *arg1, struct heapBlockHeader *arg2, struct heapBlockHeader *arg3) {
    D_main_bss_8010FF08 = arg1;
    D_main_bss_8010FF0C = arg0;
    D_main_bss_8010FF10 = arg2;
    D_main_bss_8010FF14 = arg3;
    imhBuild(&D_main_bss_8010FF18, arg0, arg1, arg2, arg3, 1);
    D_main_bss_8010FF00 = NULL;
    D_main_bss_8010FEFC = NULL;
}

static __inline__ void cfInit(void) {
    OSMesg pad[2];
    osCreateMesgQueue(&D_main_8010FEE0, &D_main_bss_8010FEF8, 1);
    osSendMesg(&D_main_8010FEE0, NULL, 0);
}
static __inline__ void cfBuild(struct heapBlockHeader **arg0, u32 arg1, struct D_main_bss_8010FF08_type *arg2, struct heapBlockHeader *arg3, struct heapBlockHeader *arg4, u8 arg5) {
    struct heapBlockHeader *a3;
    struct heapBlockHeader *a1;
    struct heapBlockHeader *a0;
    struct heapBlockHeader *t0;
    struct D_main_bss_8010FF08_type *a2;
    u32 pa1;
    s32 t1;
    s32 v1;
    u32 diff;
    u32 t2;

    cfInit();
    if (arg5 != 0) {
        *arg0 = arg3;
        arg3->unk00 = 1;
        (*arg0)->flags = 0;
        (*arg0)->size = (u32)arg4 - (u32)arg3 - 0x20;
    } else {
        a3 = arg3;
        do {
            a1 = a3;
            a3 = (struct heapBlockHeader *)((u8 *)a3 + a3->size + 0x10);
        } while (!(a3->unk00 & 8));
        a1->size = (u32)arg4 - (u32)a1 - 0x20;
    }
    arg4[-1].unk00 = 8;
    arg4[-1].flags = 0;
    arg4[-1].size = 0;
    for (t2 = 0; t2 < arg1; t2++) {
        {
            a2 = &arg2[t2];
            a3 = *arg0;
            a1 = (struct heapBlockHeader *)(a2->dataAddress - 0x10);
            t1 = (a2->dataSize + 0xF) & ~0xF;
            if (!(a3->unk00 & 8)) {
                do {
                    a0 = (struct heapBlockHeader *)((u8 *)a3 + a3->size);
                    t0 = a0 + 1;
                    __asm__("" :: "r"(a0));
                    if (((u32)a1 >= (u32)a3) & ((u32)a1 < (u32)t0)) {
                        a1->unk00 = 6;
                        a1->flags = 0;
                        if (a1 != a3) {
                            a3->size = (u32)a1 - (u32)a3 - 0x10;
                        }
                        v1 = (u32)t0 - (u32)a1 - 0x10;
                        diff = v1 - t1;
                        if (v1 != t1) {
                            if (diff >= 0x21) {
                                struct heapBlockHeader *n = (struct heapBlockHeader *)((u8 *)a1 + t1);
                                n[1].unk00 = 1;
                                n[1].flags = 0;
                                n[1].size = diff - 0x10;
                            } else {
                                t1 = v1;
                            }
                        }
                        a1->size = t1;
                        break;
                    }
                    a3 = t0;
                } while (!(a0[1].unk00 & 8));
            }
        }
    }
}


static __inline__ void cfMerge(struct heapBlockHeader *p, struct heapBlockHeader *blk) {
    struct heapBlockHeader *prev;
    struct heapBlockHeader *next;

    prev = NULL;
    while (!(p->unk00 & 8)) {
        next = (struct heapBlockHeader *)((u32)p + p->size + sizeof(struct heapBlockHeader));
        if (p->unk00 & 2) {
            if (blk == p) {
                blk->unk00 = 1;
                if ((next->unk00 & 1) && !(next->unk00 & 4)) {
                    blk->size += sizeof(struct heapBlockHeader) + next->size;
                }
                if (prev != NULL) {
                    if ((prev->unk00 & 1) && !(prev->unk00 & 4)) {
                        prev->size += sizeof(struct heapBlockHeader) + p->size;
                    }
                }
                return;
            }
        }
        prev = p;
        p = next;
    }
}

void coalesceFreeHeapBlocks(u32 n, struct D_main_bss_8010FF08_type *regions, struct heapBlockHeader *start, struct heapBlockHeader *end) {
    struct heapBlockHeader *b;

    D_main_bss_8010FF08 = regions;
    D_main_bss_8010FF0C = n;
    D_main_bss_8010FF10 = start;
    D_main_bss_8010FF14 = end;
    b = D_main_bss_8010FF18;
    while (!(*(u16 *)b & 8)) {
        if ((b->unk00 & 6) && !(b->flags & 0x80)) {
            cfMerge(D_main_bss_8010FF18, b);
        }
        b = (struct heapBlockHeader *)((u32)b + b->size + sizeof(struct heapBlockHeader));
    }
    cfBuild(&D_main_bss_8010FF18, n, regions, start, end, 0);
    D_main_bss_8010FF00 = NULL;
    D_main_bss_8010FEFC = NULL;
}
