#include "common.h"

#include "common_types.h"

#include "main/01720.h"
#include "main/3F160.h"

struct D_80130BB0_type *gNpcSlotList;
u16 gNpcSlotListTail;
u16 pad; // necessary for matching, for some reason. Without this pointers beneath it end up misaligned which makes no sense to me
struct D_80130BB8_type *gNpcContextArray;
struct D_80130BB8_type **gNpcContextArrayPtrs;
UNIDENTIFIED_TYPE *D_main_bss_80130BC0;
UNIDENTIFIED_TYPE *D_main_bss_80130BC4;
s32   gNpcNextOpenSlot;

void initNpcSlotList(void) {
    s32 var_a1;

    gNpcSlotList = rs_malloc(sizeof(struct D_80130BB0_type) * 0x800, 0U);
    for (var_a1 = 0; var_a1 < 0x800; var_a1++) {
        gNpcSlotList[var_a1].unk00 = NULL;
        gNpcSlotList[var_a1].prev_idx = var_a1 - 1 ;
        gNpcSlotList[var_a1].next_idx = var_a1 + 1;
    }
    gNpcSlotListTail = 2;
    gNpcSlotList[0].prev_idx = 0xFFFF;
    gNpcSlotList[0].next_idx = 1;
    gNpcSlotList[1].prev_idx = 0;
    gNpcSlotList[1].next_idx = 0xFFFF;
    gNpcSlotList[1].prev_idx = 0xFFFF;
    gNpcSlotList[2].prev_idx = 0xFFFF;
    gNpcSlotList[0x7FF].next_idx = 0xFFFF;
}

s32 allocateNpcSlot(struct D_80130BB8_type *arg0) {
    u16 tail;

    tail = gNpcSlotListTail;
    if (tail == 0xFFFF) {
        return 0xFFFF;
    }
    gNpcSlotListTail = gNpcSlotList[tail].next_idx;
    if (gNpcSlotListTail != 0xFFFF) {
        gNpcSlotList[gNpcSlotListTail].prev_idx = 0xFFFF;
    }
    gNpcSlotList[tail].prev_idx = 0xFFFF;
    gNpcSlotList[tail].next_idx = 0xFFFF;
    gNpcSlotList[tail].unk00 = NULL;
    if (arg0 != NULL) {
        arg0->unk1C[arg0->unk1B++] = tail;
    }
    return tail;
}

#if 0
u16 popNpcSlotFromTail(u16 arg0, struct D_80130BB8_type *arg1) {
    u16 tail;
    u16 var_v1;
    u8 var_t2;
    s32 blah;

    struct D_80130BB8_type *new_var;

    var_t2 = 0;
    if (arg1 != NULL) {
        if (arg1->unk1B >= 0x10) return 0xFFFF;
        if (arg1) {
            var_t2 = arg1->unk19;
        } else {
            var_t2 = 0;
        }
    }
    tail = gNpcSlotListTail;
    if (tail == 0xFFFF) return 0xFFFF;
    gNpcSlotListTail = gNpcSlotList[tail].next_idx;
    if (gNpcSlotListTail != 0xFFFF) {
        gNpcSlotList[gNpcSlotListTail].prev_idx = 0xFFFF;
    }
    for (var_v1 = arg0; var_v1 != 0xFFFF; var_v1 = gNpcSlotList[var_v1].next_idx) {
        if (gNpcSlotList[var_v1].unk00 == NULL) continue;
        if (var_t2 >= gNpcSlotList[var_v1].unk00->unk19) break;
        arg0 = var_v1;
    }
    gNpcSlotList[tail].next_idx = gNpcSlotList[arg0].next_idx;
    if (gNpcSlotList[tail].next_idx != 0xFFFF) {
        gNpcSlotList[gNpcSlotList[tail].next_idx].prev_idx = tail;
    }
    gNpcSlotList[tail].prev_idx = arg0;
    gNpcSlotList[arg0].next_idx = tail;
    gNpcSlotList[tail].unk00 = arg1;
    if (arg1 != NULL) {
        arg1->unk1C[arg1->unk1B++] = tail;
    }
    return tail;
}
#else
INCLUDE_ASM("asm/nonmatchings/main/3F160", popNpcSlotFromTail);
#endif

void unregisterAndFreeNpcSlot(u16 arg0, struct D_80130BB8_type *arg1) {
    s32 var_a0;

    for (var_a0 = arg1->unk1B - 1; var_a0 >= 0; var_a0--) {
        if (arg1->unk1C[var_a0] != arg0) continue;

        arg1->unk1B--;
        for (; var_a0 < arg1->unk1B; var_a0++) {
            arg1->unk1C[var_a0] = arg1->unk1C[var_a0 + 1];
        }
        if (gNpcSlotList[arg0].next_idx != 0xFFFF) {
            gNpcSlotList[gNpcSlotList[arg0].next_idx].prev_idx =gNpcSlotList[arg0].prev_idx;
        }
        if (gNpcSlotList[arg0].prev_idx != 0xFFFF) {
            gNpcSlotList[gNpcSlotList[arg0].prev_idx].next_idx = gNpcSlotList[arg0].next_idx;
        }
        gNpcSlotList[arg0].next_idx = gNpcSlotListTail;
        if (gNpcSlotListTail != 0xFFFF) {
            gNpcSlotList[gNpcSlotListTail].prev_idx = arg0;
        }
        gNpcSlotListTail = arg0;
        gNpcSlotList[arg0].prev_idx = 0xFFFF;
        break;
    }
}

s32 slotDispatcherIter(u16 arg0, s32 arg1, void *arg2) {
    u16 temp_s3;
    u16 var_s0;
    struct D_80130BB8_type *temp_a0;

    while (arg0 != 0xFFFF) {
        if (gNpcSlotList[arg0].unk00 != NULL) {
            temp_a0 = gNpcSlotList[arg0].unk00;
            temp_a0->unk1A++;
            if (!(temp_a0->unk14 & 8)) {
                var_s0 = gNpcSlotList[arg0].next_idx;
                temp_s3 = gNpcSlotList[arg0].prev_idx;
                if (temp_a0->update_func(temp_a0, arg1, arg2) != 0) {
                    if (gNpcSlotList[arg0].prev_idx == temp_s3) {
                        var_s0 = gNpcSlotList[arg0].next_idx;
                    } else if ((var_s0 != 0xFFFF) && (gNpcSlotList[var_s0].prev_idx != temp_s3)) {
                        var_s0 = 0xFFFF;
                    }
                } else {
                    var_s0 = 0xFFFF;
                }
            } else {
                var_s0 = gNpcSlotList[arg0].next_idx;
            }
            temp_a0->unk1A--;
            if (!temp_a0->unk1A && (temp_a0->unk14 & 8)) {
                destroyNpcSlotByIndex(arg0);
            }
        } else {
            var_s0 = gNpcSlotList[arg0].next_idx;
        }
        arg0 = var_s0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/3F160", slotDispatcherInner);

struct FreeBlk {
    u8 cnt;
    u8 idx[0x43];
    struct FreeBlk *prev;
    struct FreeBlk *next;
};
void reinsertNpcIntoSortedFreeList(struct D_80130BB8_type *arg0) {
    struct FreeBlk **head;
    struct FreeBlk *b;
    struct FreeBlk *n;
    struct FreeBlk *x;
    void *base;
    s32 off;
    u8 t;

    if (arg0->unk14 & 4) {
        if (arg0->unk04 != NULL) {
            rs_free(arg0->unk04);
        }
        return;
    }
    if (arg0->unk14 & 1) {
        head = (struct FreeBlk **)&D_main_bss_80130BC0;
    } else {
        head = (struct FreeBlk **)&D_main_bss_80130BC4;
    }
    if (arg0->unk14 & 1) {
        base = arg0->unk04 - 0x4C;
        b = (struct FreeBlk *)(base - (arg0->unk18 << 7));
    } else {
        base = arg0->unk04 - 0x4C;
        b = (struct FreeBlk *)(base - (arg0->unk18 << 8));
    }
    t = b->cnt + 1;
    b->cnt = t;
    b->idx[(s8)t] = arg0->unk18;
    if (b->next == NULL) {
        if (b->prev == NULL && (s8)b->cnt == 0) {
            struct FreeBlk *h = *head;
            b->next = h;
            if (h != NULL) {
                h->prev = b;
            }
            *head = b;
        } else if (b->next != NULL) {
            goto sw;
        }
    } else {
sw:
        n = b->next;
        if ((s8)n->cnt < (s8)b->cnt) {
            if (b->prev != NULL) {
                b->prev->next = n;
            } else {
                *head = n;
            }
            b->next->prev = b->prev;
            if (b->next->next != NULL) {
                b->next->next->prev = b;
            }
            x = b->next;
            b->prev = x;
            b->next = x->next;
            b->prev->next = b;
        }
    }
    arg0->unk04 = NULL;
    arg0->unk14 &= 0xFFFC;
}

void destroyNpcSlotByIndex(u16 arg0) {
    s32 var_a2;
    struct D_80130BB8_type *temp_s0;

    temp_s0 = gNpcSlotList[arg0].unk00;
    if (temp_s0 == NULL) return;
    if (temp_s0->unk1A != 0) {
        temp_s0->unk14 |= 8;
    } else {
        temp_s0->unk08 = NULL;
        temp_s0->unk1A++;
        if (temp_s0->update_func != NULL) temp_s0->update_func(temp_s0, 2, NULL);
        temp_s0->unk1A--;
        reinsertNpcIntoSortedFreeList(temp_s0);
        for (var_a2 = temp_s0->unk1B - 1; var_a2 >= 0; var_a2--) {
            if (gNpcSlotList[temp_s0->unk1C[var_a2]].next_idx != 0xFFFF) {
                gNpcSlotList[gNpcSlotList[temp_s0->unk1C[var_a2]].next_idx].prev_idx = gNpcSlotList[temp_s0->unk1C[var_a2]].prev_idx;
            }
            if (gNpcSlotList[temp_s0->unk1C[var_a2]].prev_idx != 0xFFFF) {
                gNpcSlotList[gNpcSlotList[temp_s0->unk1C[var_a2]].prev_idx].next_idx = gNpcSlotList[temp_s0->unk1C[var_a2]].next_idx;
            }
            gNpcSlotList[temp_s0->unk1C[var_a2]].next_idx = gNpcSlotListTail;
            if (gNpcSlotListTail != 0xFFFF) {
                gNpcSlotList[gNpcSlotListTail].prev_idx = temp_s0->unk1C[var_a2];
            }
            gNpcSlotList[temp_s0->unk1C[var_a2]].prev_idx = 0xFFFF;
            gNpcSlotListTail = temp_s0->unk1C[var_a2];
        }
        gNpcNextOpenSlot++;
        gNpcContextArrayPtrs[gNpcNextOpenSlot] = temp_s0;
    }
}

typedef struct {
    u16 idx;
    u16 next;
    u16 nextNext;
} NpcSlotChainPos;

u16 revalidateNpcSlotIterator(NpcSlotChainPos *pos) {
    u16 idx;

    idx = pos->next;
    if (idx != gNpcSlotList[pos->idx].next_idx && (idx == 0xFFFF || pos->nextNext != gNpcSlotList[idx].next_idx || (pos->nextNext != 0xFFFF && idx != gNpcSlotList[pos->nextNext].prev_idx))) {
        return 0xFFFF;
    }
    while (idx != 0xFFFF) {
        if (gNpcSlotList[idx].unk00 != NULL) {
            pos->idx = idx;
            pos->next = gNpcSlotList[idx].next_idx;
            if (pos->next != 0xFFFF) {
                pos->nextNext = gNpcSlotList[pos->next].next_idx;
            } else {
                pos->nextNext = 0xFFFF;
            }
            return gNpcSlotList[idx].unk00->unk16;
        }
        idx = gNpcSlotList[idx].next_idx;
    }
    return 0xFFFF;
}

void *relinkNpcSlotToNewParentGroup(NpcSlotChainPos *pos) {
    struct D_80130BB8_type *npc;
    u16 idx;

    idx = pos->next;
    if (idx != gNpcSlotList[pos->idx].next_idx && (idx == 0xFFFF || pos->nextNext != gNpcSlotList[idx].next_idx || (pos->nextNext != 0xFFFF && idx != gNpcSlotList[pos->nextNext].prev_idx))) {
        return NULL;
    }
    while (idx != 0xFFFF) {
        npc = gNpcSlotList[idx].unk00;
        if (npc != NULL && npc->unk08 != NULL) {
            pos->idx = idx;
            pos->next = gNpcSlotList[idx].next_idx;
            if (pos->next != 0xFFFF) {
                pos->nextNext = gNpcSlotList[pos->next].next_idx;
            } else {
                pos->nextNext = 0xFFFF;
            }
            return npc->unk08;
        }
        idx = gNpcSlotList[idx].next_idx;
    }
    return NULL;
}

void destroyNpcSlotChain(u16 arg0) {
    u16 var_a0;

    while (arg0 != 0xFFFF) {
        var_a0 = gNpcSlotList[arg0].next_idx;
        if (gNpcSlotList[arg0].unk00 != NULL) {
            unregisterAndFreeNpcSlot(arg0, gNpcSlotList[arg0].unk00);
        } else {
            if (var_a0 != 0xFFFF) {
                gNpcSlotList[gNpcSlotList[arg0].next_idx].prev_idx = gNpcSlotList[arg0].prev_idx;
            }
            if (gNpcSlotList[arg0].prev_idx != 0xFFFF) {
                gNpcSlotList[gNpcSlotList[arg0].prev_idx].next_idx = gNpcSlotList[arg0].next_idx;
            }
            gNpcSlotList[arg0].next_idx = gNpcSlotListTail;
            if (gNpcSlotListTail != 0xFFFF) {
                gNpcSlotList[gNpcSlotListTail].prev_idx = arg0;
            }
            gNpcSlotListTail = arg0;
            gNpcSlotList[arg0].prev_idx = 0xFFFF;
        }
        arg0 = var_a0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/3F160", spawnChildNpcWithTransform);

INCLUDE_ASM("asm/nonmatchings/main/3F160", spawnInheritedNpcVariantA);

s32 spawnChildNpcWithTransform(struct D_80130BB8_type *self, u16 arg1, void *arg2);
u16 spawnInheritedNpcVariantB(s16 arg0, s32 arg1) {
    struct {
        s16 type;
        s16 parent;
        s32 arg;
        s32 pad[3];
        s16 unk14;
    } msg;
    f32 sp28;
    u16 var_a1;
    u16 ret;
    struct D_80130BB8_type *temp_s0;
    u8 temp_s1;
    npc_update fn;
    void *msgp;

    msg.parent = arg0;
    msg.type = 0;
    msg.arg = arg1;
    msg.unk14 = 0;
    temp_s1 = gNpcSlotList[(u16)arg0].unk00->unk19 + 1;
    fn = spawnChildNpcWithTransform;
    msgp = &msg;
    if (gNpcNextOpenSlot < 0) {
        for (var_a1 = gNpcSlotList[1].prev_idx; var_a1 != 0xFFFF; var_a1 = gNpcSlotList[var_a1].prev_idx) {
            if ((gNpcSlotList[var_a1].unk00 != NULL) && (gNpcSlotList[var_a1].unk00->unk1A == 0)) {
                destroyNpcSlotByIndex(var_a1);
                break;
            }
        }
    }
    temp_s0 = gNpcContextArrayPtrs[gNpcNextOpenSlot--];
    temp_s0->unk04 = NULL;
    temp_s0->unk08 = NULL;
    temp_s0->unk0C = 0;
    temp_s0->update_func = fn;
    temp_s0->unk10 = 0;
    temp_s0->unk14 = 1;
    temp_s0->unk1B = 0;
    temp_s0->unk1A = 0;
    temp_s0->unk19 = temp_s1;
    temp_s0->unk16 = allocateNpcSlot(temp_s0);
    gNpcSlotList[temp_s0->unk16].unk00 = temp_s0;
    popNpcSlotFromTail(0U, temp_s0);
    slotDispatcherInner(temp_s0);
    slotDispatcherIter(temp_s0->unk16, 1, msgp);
    ret = temp_s0->unk16;
    if (ret != 0xFFFF) {
        sp28 = 0.033333335f;
        slotDispatcherIter(ret, 3, &sp28);
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main/3F160", spawnInheritedNpcVariantC);

void freeNpcSlotArray(void) {
    rs_free(gNpcSlotList);
    gNpcSlotList = NULL;
}

u16 findActiveNpcInSlotChain(u16 idx, NpcSlotChainPos *out) {
    while (idx != 0xFFFF) {
        if (gNpcSlotList[idx].unk00 != NULL) {
            if (out != NULL) {
                out->idx = idx;
                out->next = gNpcSlotList[idx].next_idx;
                if (out->next != 0xFFFF) {
                    out->nextNext = gNpcSlotList[out->next].next_idx;
                } else {
                    out->nextNext = 0xFFFF;
                }
            }
            return gNpcSlotList[idx].unk00->unk16;
        }
        idx = gNpcSlotList[idx].next_idx;
    }
    return 0xFFFF;
}

void *findFirstActiveNpcChildInChain(u16 idx, NpcSlotChainPos *out) {
    struct D_80130BB8_type *npc;

    while (idx != 0xFFFF) {
        npc = gNpcSlotList[idx].unk00;
        if (npc != NULL && npc->unk08 != NULL) {
            if (out != NULL) {
                out->idx = idx;
                out->next = gNpcSlotList[idx].next_idx;
                if (out->next != 0xFFFF) {
                    out->nextNext = gNpcSlotList[out->next].next_idx;
                } else {
                    out->nextNext = 0xFFFF;
                }
            }
            return npc->unk08;
        }
        idx = gNpcSlotList[idx].next_idx;
    }
    return NULL;
}

void allocNpcContextArrays(void) {
    s32 var_a2;
    struct D_80130BB8_type **temp_v0;
    struct D_80130BB8_type **var_a1;
    struct D_80130BB8_type *var_a0;

    gNpcContextArray     = rs_malloc(sizeof(struct D_80130BB8_type)  * 0xC0, 0U);
    gNpcContextArrayPtrs = rs_malloc(sizeof(struct D_80130BB8_type*) * 0xC0, 0U);
    for (var_a2 = 0xBF; var_a2 >= 0; var_a2--) {
        gNpcContextArrayPtrs[var_a2] = &gNpcContextArray[var_a2];
    }
    gNpcNextOpenSlot = 0xBF;
    D_main_bss_80130BC4 = NULL;
    D_main_bss_80130BC0 = NULL;
}

void destroyTransientNpcSlots(void);

void destroyNpcContextArrays(void) {
    void *p;

    while (gNpcNextOpenSlot < 0xBF) {
        destroyTransientNpcSlots();
    }
    while ((p = D_main_bss_80130BC0) != NULL) {
        D_main_bss_80130BC0 = *(void **)((u8 *)p + 0x48);
        rs_free(p);
    }
    while ((p = D_main_bss_80130BC4) != NULL) {
        D_main_bss_80130BC4 = *(void **)((u8 *)p + 0x48);
        rs_free(p);
    }
    rs_free(gNpcContextArrayPtrs);
    rs_free(gNpcContextArray);
    gNpcContextArrayPtrs = NULL;
    gNpcContextArray = NULL;
}

u16 spawnNpcWithSubtype(npc_update arg0, void *arg1, u32 arg2, u8 arg3) {
    u16 var_a1;
    struct D_80130BB8_type *temp_s0;

    if (gNpcNextOpenSlot < 0) {
        for (var_a1 = gNpcSlotList[1].prev_idx; var_a1 != 0xFFFF; var_a1 = gNpcSlotList[var_a1].prev_idx) {
            if ((gNpcSlotList[var_a1].unk00 != NULL) && (gNpcSlotList[var_a1].unk00->unk1A == 0)) {
                destroyNpcSlotByIndex(var_a1);
                break;
            }
        }
    }
    temp_s0 = gNpcContextArrayPtrs[gNpcNextOpenSlot--];
    temp_s0->unk04 = NULL;
    temp_s0->unk08 = NULL;
    temp_s0->unk0C = 0;
    temp_s0->update_func = arg0;
    temp_s0->unk10 = 0;
    temp_s0->unk14 = arg2;
    temp_s0->unk1B = 0;
    temp_s0->unk1A = 0;
    temp_s0->unk19 = arg3;
    temp_s0->unk16 = allocateNpcSlot(temp_s0);
    gNpcSlotList[temp_s0->unk16].unk00 = temp_s0;
    popNpcSlotFromTail(0U, temp_s0);
    slotDispatcherInner(temp_s0);
    slotDispatcherIter(temp_s0->unk16, 8, arg1);
    return temp_s0->unk16;
}

u16 spawnNpcOfType(npc_update arg0, void *arg1, u32 arg2, u8 arg3) {
    u16 var_a1;
    struct D_80130BB8_type *temp_s0;

    if (gNpcNextOpenSlot < 0) {
        for (var_a1 = gNpcSlotList[1].prev_idx; var_a1 != 0xFFFF; var_a1 = gNpcSlotList[var_a1].prev_idx) {
            if ((gNpcSlotList[var_a1].unk00 != NULL) && (gNpcSlotList[var_a1].unk00->unk1A == 0)) {
                destroyNpcSlotByIndex(var_a1);
                break;
            }
        }
    }
    temp_s0 = gNpcContextArrayPtrs[gNpcNextOpenSlot--];
    temp_s0->unk04 = NULL;
    temp_s0->unk08 = NULL;
    temp_s0->unk0C = 0;
    temp_s0->update_func = arg0;
    temp_s0->unk10 = 0;
    temp_s0->unk14 = arg2;
    temp_s0->unk1B = 0;
    temp_s0->unk1A = 0;
    temp_s0->unk19 = arg3;
    temp_s0->unk16 = allocateNpcSlot(temp_s0);
    gNpcSlotList[temp_s0->unk16].unk00 = temp_s0;
    popNpcSlotFromTail(0U, temp_s0);
    slotDispatcherInner(temp_s0);
    slotDispatcherIter(temp_s0->unk16, 1, arg1);
    return temp_s0->unk16;
}

struct D_80130BB8_type *getNpcContextByIndex(u16 arg0) {
    return gNpcSlotList[arg0].unk00;
}

void *getNpcContextField8(u16 arg0) {
    if (gNpcSlotList[arg0].unk00 != NULL) {
        return gNpcSlotList[arg0].unk00->unk08;
    } else {
        return NULL;
    }
}

u16 findFreeNpcSlotByKey(struct D_80130BB8_type *arg0, u16 arg1) {
    u16 var_s0;

    var_s0 = 0xFFFF;
    if (arg1 != 0xFFFF) {
        if (gNpcSlotList[arg1].unk00 != NULL) {
            var_s0 = allocateNpcSlot(NULL);
            if (var_s0 != 0xFFFF) {
                popNpcSlotFromTail(var_s0, gNpcSlotList[arg1].unk00);
            }
        }
    }
    return var_s0;
}

u16 getNextSlotNpcTypeId(u16 arg0) {
    if ((arg0 == 0xFFFF) || (gNpcSlotList[arg0].next_idx == 0xFFFF)) {
        return 0xFFFF;
    } else {
        return gNpcSlotList[gNpcSlotList[arg0].next_idx].unk00->unk16;
    }
}

u16 getNpcNextSlotIndex(u16 arg0) {
    u16 ret;
    if (arg0 != 0xFFFF) {
        ret = gNpcSlotList[arg0].next_idx;
    } else {
        ret = 0xFFFF;
    }
    return ret;
}

void destroyTransientNpcSlots(void) {
    u16 var_a1;

    for (var_a1 = gNpcSlotList[1].prev_idx; var_a1 != 0xFFFF; var_a1 = gNpcSlotList[var_a1].prev_idx) {
        if ((gNpcSlotList[var_a1].unk00 != NULL) && (gNpcSlotList[var_a1].unk00->unk1A == 0)) {
            destroyNpcSlotByIndex(var_a1);
            break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/3F160", fake_func_80040304);
