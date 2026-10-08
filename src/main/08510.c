#include "common.h"
#include "common_types.h"

#include "main/08510.h"
#include "main/1EE30.h"

// Interim BSS externs
extern struct DisplayListBuffer *D_main_bss_801163B0;

extern s32 D_main_bss_8011A8A4[];

s32 registerSiCallback(void (*cb)(void)) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_main_bss_8011A8A4[i] == 0) {
            D_main_bss_8011A8A4[i] = (s32)cb;
            return 1;
        }
    }
    return 0;
}

extern s32 D_main_bss_8011A8A4[];

void findAndZeroTableSlotMatching(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_main_bss_8011A8A4[i] == arg0) {
            D_main_bss_8011A8A4[i] = 0;
            return;
        }
    }
}

extern s32 D_main_bss_8011A8B0;

void clearFourWordTable(void) {
    s32 i;
    s32 *p;

    i = 3;
    p = &D_main_bss_8011A8B0;
    do {
        *p-- = 0;
    } while (--i >= 0);
}

#if 0
// I strongly suspect this file is compiled with O3, and that this function gets inlined
void heapFreeListInsert(struct DisplayListBuffer *arg0) {
    struct DisplayListBuffer *var_v1;

    if (arg0 != NULL) {
        var_v1 = arg0;
        if (arg0->next != NULL) {
            do {
                var_v1 = var_v1->next;
            } while (var_v1->next != NULL);
        }
        var_v1->next = D_main_bss_801163B0;
        if (D_main_bss_801163B0 != NULL) {
            D_main_bss_801163B0->prev = var_v1;
        }
        D_main_bss_801163B0 = arg0;
        D_main_bss_801163B0->prev = NULL;
    }
}
#else
void heapFreeListInsert(struct DisplayListBuffer *arg0) {
    struct DisplayListBuffer *var_v1;

    if (arg0 != NULL) {
        var_v1 = arg0;
        if (arg0->next != NULL) {
            do {
                var_v1 = var_v1->next;
            } while (var_v1->next != NULL);
        }
        var_v1->next = D_main_bss_801163B0;
        if (D_main_bss_801163B0 != NULL) {
            D_main_bss_801163B0->prev = var_v1;
        }
        D_main_bss_801163B0 = arg0;
        arg0->prev = NULL;
    }
}
#endif

extern u8 D_main_bss_8011A899;
extern struct DisplayListBuffer *hwListA[] __asm__("D_main_bss_801163C8");
extern struct DisplayListBuffer *D_main_bss_8011A4B0[];
extern struct DisplayListBuffer *D_main_bss_8011A458[];
extern struct DisplayListBuffer *hwListD[] __asm__("D_main_bss_8011A4A0");
extern struct DisplayListBuffer *hwListE[] __asm__("D_main_bss_8011A468");
extern struct DisplayListBuffer *hwTail[] __asm__("D_main_bss_8011A7E0");
extern struct DisplayListBuffer **D_main_bss_801163FC;
extern struct DisplayListBuffer **D_main_bss_8011A7DC;
extern struct DisplayListBuffer **D_main_bss_8011A4C4;
extern struct DisplayListBuffer **D_main_bss_8011A4AC;
extern struct DisplayListBuffer **D_main_bss_8011A4BC;
extern struct DisplayListBuffer **D_main_bss_8011A4B8;

static __inline__ void hwInsert(struct DisplayListBuffer *arg0) {
    struct DisplayListBuffer *var_v1;

    if (arg0 != NULL) {
        var_v1 = arg0;
        if (arg0->next != NULL) {
            do {
                var_v1 = var_v1->next;
            } while (var_v1->next != NULL);
        }
        var_v1->next = D_main_bss_801163B0;
        if (D_main_bss_801163B0 != NULL) {
            D_main_bss_801163B0->prev = var_v1;
        }
        D_main_bss_801163B0 = arg0;
        arg0->prev = NULL;
    }
}

void heapWalker(void) {
    u8 *ip;

    hwInsert(hwListA[D_main_bss_8011A899]);
    hwInsert(D_main_bss_8011A4B0[D_main_bss_8011A899]);
    hwInsert(D_main_bss_8011A458[D_main_bss_8011A899]);
    hwInsert(hwListD[D_main_bss_8011A899]);
    hwInsert(hwListE[D_main_bss_8011A899]);
    ip = &D_main_bss_8011A899;
    *(int *)((s32)hwListA + *ip * 4) = 0;
    *(int *)((s32)D_main_bss_8011A4B0 + *ip * 4) = 0;
    *(int *)((s32)D_main_bss_8011A458 + *ip * 4) = 0;
    *(int *)((s32)hwListD + *ip * 4) = 0;
    *(int *)((s32)hwListE + *ip * 4) = 0;
    D_main_bss_801163FC = &hwListA[D_main_bss_8011A899];
    D_main_bss_8011A7DC = &hwTail[D_main_bss_8011A899];
    D_main_bss_8011A4C4 = &D_main_bss_8011A4B0[D_main_bss_8011A899];
    D_main_bss_8011A4AC = &D_main_bss_8011A458[D_main_bss_8011A899];
    D_main_bss_8011A4BC = &hwListD[D_main_bss_8011A899];
    D_main_bss_8011A4B8 = &hwListE[D_main_bss_8011A899];
}

#if 0
s32 countDisplayListChunks(void) {
    s32 blah;
    struct DisplayListBuffer *var_v1;

    blah = 0;
    var_v1 = D_main_bss_801163B0;
    while (var_v1 != NULL) {
        var_v1 = var_v1->next;
        blah += sizeof(struct DisplayListBuffer);
    }
    return blah;
}
#else
s32 countDisplayListChunks(void) {
    s32 var_v0;
    struct DisplayListBuffer *var_v1;

    var_v1 = D_main_bss_801163B0;
    var_v0 = 0;
    if (var_v1 != NULL) {
        do {
            var_v1 = var_v1->next;
            var_v0 += 0x108;
        } while (var_v1 != NULL);
    }
    return var_v0;
}
#endif

#if 0
struct DisplayListBuffer *reclaimDisplayListChunk(void) {
    struct DisplayListBuffer *temp_a0;
    struct DisplayListBuffer *temp_v0;
    struct DisplayListBuffer *temp_v0_2;
    struct DisplayListBuffer *var_v1;

    temp_a0 = D_main_bss_801163B0;
    if (temp_a0 == NULL) {
        temp_v0 = findAndUnlinkSmallestEntry();
        heapFreeListInsert(temp_v0);
        // if (temp_v0 != NULL) {
        //     var_v1 = temp_v0;
        //     if (temp_v0->next != NULL) {
        //         do {
        //             var_v1 = var_v1->next;
        //         } while (var_v1->next != NULL);
        //     }
        //     var_v1->next = D_main_bss_801163B0;
        //     if (D_main_bss_801163B0 != NULL) {
        //         D_main_bss_801163B0->prev = var_v1;
        //     }
        //     D_main_bss_801163B0 = temp_v0;
        //     temp_v0->prev = NULL;
        // }
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    return temp_a0;
}
#else
struct DisplayListBuffer *reclaimDisplayListChunk(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    return chunk;
}
#endif

extern Gfx *D_main_bss_801163D4;
extern struct DisplayListBuffer **D_main_bss_801163FC;
extern struct DisplayListBuffer **D_main_bss_8011A7DC;

Gfx *allocateDisplayListBuffer(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;
    struct DisplayListBuffer *buf;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    buf = chunk;
    if (*D_main_bss_801163FC == NULL) {
        *D_main_bss_801163FC = buf;
    } else {
        (*D_main_bss_8011A7DC)->next = buf;
        buf->prev = *D_main_bss_8011A7DC;
    }
    buf->next = NULL;
    *D_main_bss_8011A7DC = buf;
    D_main_bss_801163D4 = &buf->displayList[0x1F];
    return buf->displayList;
}

extern struct DisplayListBuffer **D_main_bss_8011A4C4;

Gfx *allocDLBlockToFillRectList(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    if (*D_main_bss_8011A4C4 != NULL) {
        (*D_main_bss_8011A4C4)->prev = chunk;
    }
    chunk->next = *D_main_bss_8011A4C4;
    *D_main_bss_8011A4C4 = chunk;
    return chunk->displayList;
}

extern struct DisplayListBuffer **D_main_bss_8011A4AC;

Gfx *allocDLBlockToListB(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    if (*D_main_bss_8011A4AC != NULL) {
        (*D_main_bss_8011A4AC)->prev = chunk;
    }
    chunk->next = *D_main_bss_8011A4AC;
    *D_main_bss_8011A4AC = chunk;
    return chunk->displayList;
}

extern struct DisplayListBuffer **D_main_bss_8011A4B8;

Gfx *allocDLBlockToListC(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    if (*D_main_bss_8011A4B8 != NULL) {
        (*D_main_bss_8011A4B8)->prev = chunk;
    }
    chunk->next = *D_main_bss_8011A4B8;
    *D_main_bss_8011A4B8 = chunk;
    return chunk->displayList;
}

extern struct DisplayListBuffer **D_main_bss_8011A4BC;

Gfx *allocDLBlockToListD(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    if (*D_main_bss_8011A4BC != NULL) {
        (*D_main_bss_8011A4BC)->prev = chunk;
    }
    chunk->next = *D_main_bss_8011A4BC;
    *D_main_bss_8011A4BC = chunk;
    return chunk->displayList;
}

static __inline__ void freeListInsert(struct DisplayListBuffer *arg0) {
    struct DisplayListBuffer *var_v1;

    if (arg0 != NULL) {
        var_v1 = arg0;
        if (arg0->next != NULL) {
            do {
                var_v1 = var_v1->next;
            } while (var_v1->next != NULL);
        }
        var_v1->next = D_main_bss_801163B0;
        if (D_main_bss_801163B0 != NULL) {
            D_main_bss_801163B0->prev = var_v1;
        }
        D_main_bss_801163B0 = arg0;
        arg0->prev = NULL;
    }
}

typedef struct {
    s32 v[7];
} MeshReleaseEntry;

extern u16 D_main_bss_80113230;
extern MeshReleaseEntry D_main_bss_80112B30[];

void drainMeshReleaseQueue(void) {
    s32 i;
    s32 j;
    s32 *pb;
    s32 *pc;

    for (i = 0; i < D_main_bss_80113230; i++) {
        freeListInsert((struct DisplayListBuffer *)D_main_bss_80112B30[i].v[0]);
        pb = &D_main_bss_80112B30[i].v[1];
        pc = &D_main_bss_80112B30[i].v[3];
        for (j = 0; j < 2; j++) {
            freeListInsert((struct DisplayListBuffer *)pb[j]);
            freeListInsert((struct DisplayListBuffer *)pc[j]);
        }
        freeListInsert((struct DisplayListBuffer *)D_main_bss_80112B30[i].v[6]);
        freeListInsert((struct DisplayListBuffer *)D_main_bss_80112B30[i].v[5]);
    }
    D_main_bss_80113230 = 0;
}

s32 enqueueMeshForDeferredRelease(struct meshdef1 *arg0) {
    struct meshdef1 *mesh = arg0;
    MeshReleaseEntry *e;
    u16 idx;

    if (!(mesh->unk0C & 0x10)) {
        return 0;
    }
    idx = D_main_bss_80113230;
    if (idx < 0x40) {
        D_main_bss_80113230 = idx + 1;
        e = &D_main_bss_80112B30[idx];
    } else {
        e = NULL;
    }
    if (e == NULL) {
        return 0;
    }
    e->v[0] = *(s32 *)&mesh->unk2C[4];
    e->v[1] = *(s32 *)&mesh->unk2C[6];
    e->v[2] = *(s32 *)&mesh->unk2C[7];
    e->v[3] = *(s32 *)&mesh->unk2C[8];
    e->v[4] = *(s32 *)&mesh->unk2C[9];
    e->v[5] = *(s32 *)&mesh->unk2C[10];
    e->v[6] = *(s32 *)&mesh->unk2C[11];
    mesh->unk0C &= ~0x18;
    return 1;
}

extern Gfx *D_main_bss_8011D090;
extern u8 D_main_bss_8011D094;
void recordDeferredDrawRefVariant(s32 ref, s32 flags, s32 kind) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;
    u8 *cnt;

    if (flags & 0x40000000) {
        if (D_main_bss_8011D094 >= 0x40) {
            chunk = D_main_bss_801163B0;
            if (chunk == NULL) {
                chunk = findAndUnlinkSmallestEntry();
                if (chunk != NULL) {
                    tail = chunk;
                    while (tail->next != NULL) {
                        tail = tail->next;
                    }
                    tail->next = D_main_bss_801163B0;
                    if (D_main_bss_801163B0 != NULL) {
                        D_main_bss_801163B0->prev = tail;
                    }
                    D_main_bss_801163B0 = chunk;
                    chunk->prev = NULL;
                }
                chunk = D_main_bss_801163B0;
            }
            D_main_bss_801163B0 = D_main_bss_801163B0->next;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = NULL;
            }
            if (*D_main_bss_8011A4BC != NULL) {
                (*D_main_bss_8011A4BC)->prev = chunk;
            }
            chunk->next = *D_main_bss_8011A4BC;
            *D_main_bss_8011A4BC = chunk;
            D_main_bss_8011D090 = chunk->displayList;
            D_main_bss_8011D094 = 0;
        }
        cnt = &D_main_bss_8011D094;
        ((s32 *)D_main_bss_8011D090)[(*cnt)++] = (ref & 0xFFFFFF) | (kind << 24);
    }
}

void commitMeshDrawBatchRefs(struct meshdef1 *mesh) {
    struct DisplayListBuffer *p;
    struct DisplayListBuffer *q;
    struct DisplayListBuffer *t;
    struct DisplayListBuffer **hp;
    struct DisplayListBuffer **hq;
    s32 sel;
    s32 n;
    u32 w;
    u32 addr;

    if ((mesh->unk0C & 0x10) && (mesh->unk0C & 0x60)) {
        t = *(struct DisplayListBuffer **)((u8 *)mesh + 0x58);
        mesh->unk0C &= ~0x60;
        sel = *(u32 *)&mesh->unk2C[0] & 0x80000000;
        hp = (struct DisplayListBuffer **)((u8 *)mesh + 0x44);
        if (sel == 0) {
            hp = (struct DisplayListBuffer **)((u8 *)mesh + 0x48);
        }
        p = *hp;
        hq = (struct DisplayListBuffer **)((u8 *)mesh + 0x4C);
        if (sel == 0) {
            hq = (struct DisplayListBuffer **)((u8 *)mesh + 0x50);
        }
        q = *hq;
        while (p->next != NULL) {
            p = p->next;
        }
        while (q->next != NULL) {
            q = q->next;
        }
        while (t->next != NULL) {
            t = t->next;
        }
        n = 0;
        if (p != NULL || q != NULL) {
            do {
                w = ((u32 *)((u8 *)t + 8))[n];
                n++;
                addr = (w & 0xFFFFFF) | 0x80000000;
                switch (w >> 24) {
                case 0:
                    *(void **)(addr + 4) = (u8 *)p + 8;
                    p = p->prev;
                    break;
                case 1:
                    *(void **)(addr + 4) = (u8 *)q + 8;
                    q = q->prev;
                    break;
                }
                if (n == 0x40) {
                    t = t->prev;
                    n = 0;
                }
            } while (p != NULL || q != NULL);
        }
    }
}

extern Gfx *D_main_bss_8011A448;
extern Gfx *D_main_bss_8011A44C;
extern u8 D_main_bss_8011A450;

static __inline__ Gfx *eadAllocBuf(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;
    struct DisplayListBuffer *buf;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    buf = chunk;
    if (*D_main_bss_801163FC == NULL) {
        *D_main_bss_801163FC = buf;
    } else {
        (*D_main_bss_8011A7DC)->next = buf;
        buf->prev = *D_main_bss_8011A7DC;
    }
    buf->next = NULL;
    *D_main_bss_8011A7DC = buf;
    D_main_bss_801163D4 = &buf->displayList[0x1F];
    return buf->displayList;
}

static __inline__ void eadRecord(s32 ref, s32 flags, s32 kind) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;
    u8 *cnt;

    if (flags & 0x40000000) {
        if (D_main_bss_8011D094 >= 0x40) {
            chunk = D_main_bss_801163B0;
            if (chunk == NULL) {
                chunk = findAndUnlinkSmallestEntry();
                if (chunk != NULL) {
                    tail = chunk;
                    while (tail->next != NULL) {
                        tail = tail->next;
                    }
                    tail->next = D_main_bss_801163B0;
                    if (D_main_bss_801163B0 != NULL) {
                        D_main_bss_801163B0->prev = tail;
                    }
                    D_main_bss_801163B0 = chunk;
                    chunk->prev = NULL;
                }
                chunk = D_main_bss_801163B0;
            }
            D_main_bss_801163B0 = D_main_bss_801163B0->next;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = NULL;
            }
            if (*D_main_bss_8011A4BC != NULL) {
                (*D_main_bss_8011A4BC)->prev = chunk;
            }
            chunk->next = *D_main_bss_8011A4BC;
            *D_main_bss_8011A4BC = chunk;
            D_main_bss_8011D090 = chunk->displayList;
            D_main_bss_8011D094 = 0;
        }
        cnt = &D_main_bss_8011D094;
        ((s32 *)D_main_bss_8011D090)[(*cnt)++] = (ref & 0xFFFFFF) | (kind << 24);
    }
}

static __inline__ Gfx *eadAllocFill(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    if (*D_main_bss_8011A4C4 != NULL) {
        (*D_main_bss_8011A4C4)->prev = chunk;
    }
    chunk->next = *D_main_bss_8011A4C4;
    *D_main_bss_8011A4C4 = chunk;
    return chunk->displayList;
}

Gfx *emitAllocatedDLCommand(Gfx *dl, s32 flags) {
    if (dl >= D_main_bss_801163D4) {
        dl->words.w0 = 0xB5000000;
        dl->words.w1 = 0;
        dl = eadAllocBuf();
    }
    eadRecord((s32)dl, flags, 0);
    D_main_bss_8011A448 = dl;
    D_main_bss_8011A450 = 0;
    dl++;
    D_main_bss_8011A44C = eadAllocFill();
    return dl;
}

typedef struct {
    u16 idx;
    u16 stamp;
} EfSlot;

extern u8 efSlotOf[] __asm__("D_main_801132C0");
extern EfSlot efCache[] __asm__("D_main_bss_80113240");
extern u16 efStamp __asm__("D_main_bss_801142C0");
extern struct { Gfx *dl; Gfx *vtx; u8 cnt; } efG __asm__("D_main_bss_8011A448");

Gfx *emitFaceDLCommands(Gfx *dl, Gfx **out, u8 *outIdx, u8 n, u16 *vt, s32 flags) {
    u8 buf[8];
    u8 i;
    u8 cnt;
    u16 vi;
    u8 slot;
    u8 *bp;

    bp = buf;
    cnt = 0;
    for (i = 0; i < n; i++) {
        vi = vt[i];
        __asm__("" :: "r"(dl));
        slot = efSlotOf[vi];
        if (efCache[slot].stamp == efStamp && efCache[slot].idx == vi) {
            bp[i] = slot;
        } else {
            bp[i] = 0xFF;
            cnt++;
        }
    }
    if (cnt != 0) {
        if (0x20 - efG.cnt < cnt) {
            D_main_bss_8011A448->words.w0 = 0x04000000 | (((D_main_bss_8011A450 << 10) | (((D_main_bss_8011A450 * 8 + 0xF) & 0xFFF0) - 1)) & 0xFFFF);
            D_main_bss_8011A448->words.w1 = (u32)efG.vtx;
            efStamp++;
            if (efStamp == 0) {
                efStamp = 1;
            }
            dl = emitAllocatedDLCommand(dl, flags);
            for (i = 0; i < n; i++) {
                efSlotOf[vt[i]] = efG.cnt;
                efCache[efG.cnt].idx = vt[i];
                efCache[efG.cnt].stamp = efStamp;
                out[i] = efG.vtx + efG.cnt;
                outIdx[i] = efG.cnt;
                efG.cnt++;
            }
        } else {
            for (i = 0; i < n; i++) {
                if (buf[i] == 0xFF) {
                    efSlotOf[vt[i]] = efG.cnt;
                    efCache[efG.cnt].idx = vt[i];
                    efCache[efG.cnt].stamp = efStamp;
                    out[i] = efG.vtx + efG.cnt;
                    outIdx[i] = efG.cnt;
                    efG.cnt++;
                } else {
                    outIdx[i] = buf[i];
                    out[i] = efG.vtx + buf[i];
                }
            }
        }
    } else {
        for (i = 0; i < n; i++) {
            outIdx[i] = buf[i];
            out[i] = efG.vtx + buf[i];
        }
    }
    return dl;
}

INCLUDE_ASM("asm/nonmatchings/main/08510", emitFrameRdpInitDl);

extern s32 D_main_bss_801142C4;

s32 setActiveRenderListPtr(s32 arg0) {
    D_main_bss_801142C4 = arg0;
    return 1;
}

extern Gfx *D_main_bss_8011DC58;
extern s16 D_main_bss_8011A848;
extern s32 D_main_bss_8011A838;
extern s32 D_main_bss_8011A83C;
extern u16 D_A880u __asm__("D_main_bss_8011A880");
extern u16 D_A882u __asm__("D_main_bss_8011A882");
extern u16 D_A884u __asm__("D_main_bss_8011A884");
extern u16 D_main_bss_8011A886;
extern u8 D_main_bss_8011A888;
extern u8 D_main_bss_8011A889;
extern u8 D_main_bss_8011A88A;

#define CFR_ENSURE()                                                                 \
    if (D_main_bss_8011DC58 >= D_main_bss_801163D4) {                                \
        struct DisplayListBuffer *chunk;                                             \
        struct DisplayListBuffer *tail;                                              \
        struct DisplayListBuffer *buf;                                               \
        D_main_bss_8011DC58->words.w0 = 0xB5000000;                                  \
        D_main_bss_8011DC58->words.w1 = 0;                                           \
        chunk = D_main_bss_801163B0;                                                 \
        if (chunk == NULL) {                                                         \
            chunk = findAndUnlinkSmallestEntry();                                    \
            if (chunk != NULL) {                                                     \
                tail = chunk;                                                        \
                while (tail->next != NULL) {                                         \
                    tail = tail->next;                                               \
                }                                                                    \
                tail->next = D_main_bss_801163B0;                                    \
                if (D_main_bss_801163B0 != NULL) {                                   \
                    D_main_bss_801163B0->prev = tail;                                \
                }                                                                    \
                D_main_bss_801163B0 = chunk;                                         \
                chunk->prev = NULL;                                                  \
            }                                                                        \
            chunk = D_main_bss_801163B0;                                             \
        }                                                                            \
        D_main_bss_801163B0 = D_main_bss_801163B0->next;                             \
        if (D_main_bss_801163B0 != NULL) {                                           \
            D_main_bss_801163B0->prev = NULL;                                        \
        }                                                                            \
        buf = chunk;                                                                 \
        if (*D_main_bss_801163FC == NULL) {                                          \
            *D_main_bss_801163FC = buf;                                              \
        } else {                                                                     \
            (*D_main_bss_8011A7DC)->next = buf;                                      \
            buf->prev = *D_main_bss_8011A7DC;                                        \
        }                                                                            \
        buf->next = NULL;                                                            \
        *D_main_bss_8011A7DC = buf;                                                  \
        D_main_bss_801163D4 = &buf->displayList[0x1F];                               \
        D_main_bss_8011DC58 = buf->displayList;                                      \
    }

void emitColorFillRect(void) {
    u8 r = D_main_bss_8011A888;
    u8 gr = D_main_bss_8011A889;
    u8 b = D_main_bss_8011A88A;

    CFR_ENSURE();
    {
        Gfx *g = D_main_bss_8011DC58++;
        g->words.w0 = 0xE7000000;
        g->words.w1 = 0;
    }
    CFR_ENSURE();
    {
        Gfx *g = D_main_bss_8011DC58++;
        g->words.w0 = 0xB900031D;
        g->words.w1 = 0x0F0A4000;
    }
    CFR_ENSURE();
    {
        Gfx *g = D_main_bss_8011DC58++;
        g->words.w0 = 0xBA001402;
        g->words.w1 = 0x300000;
    }
    CFR_ENSURE();
    if (D_main_bss_8011A848 >= 0x18) {
        Gfx *g = D_main_bss_8011DC58++;
        g->words.w0 = 0xF7000000;
        g->words.w1 = (r << 24) | (gr << 16) | (b << 8) | 0xFF;
    } else {
        Gfx *g = D_main_bss_8011DC58++;
        s32 c;
        g->words.w0 = 0xF7000000;
        c = ((r << 8) & 0xF800) | ((gr << 3) & 0x7C0) | ((b >> 2) & 0x3E);
        g->words.w1 = ((c | 1) << 16) | (c | 1);
    }
    if (D_A882u != 0) {
        CFR_ENSURE();
        {
            Gfx *g = D_main_bss_8011DC58++;
            g->words.w0 = 0xF6000000 | ((D_main_bss_8011A838 & 0x3FF) << 14) | ((D_A882u & 0x3FF) << 2);
            g->words.w1 = 0;
        }
    }
    if (D_main_bss_8011A886 < (u32)D_main_bss_8011A83C) {
        CFR_ENSURE();
        {
            Gfx *g = D_main_bss_8011DC58;
            ((u32 *)g)[0] = 0xF6000000 | ((D_main_bss_8011A838 & 0x3FF) << 14) | ((D_main_bss_8011A83C & 0x3FF) << 2);
            D_main_bss_8011DC58 = g + 1;
            g->words.w1 = (D_main_bss_8011A886 & 0x3FF) << 2;
        }
    }
    if (D_A880u != 0) {
        CFR_ENSURE();
        {
            Gfx *g = D_main_bss_8011DC58;
            ((u32 *)g)[0] = 0xF6000000 | ((D_A880u & 0x3FF) << 14) | ((D_main_bss_8011A886 & 0x3FF) << 2);
            D_main_bss_8011DC58 = g + 1;
            g->words.w1 = (D_A882u & 0x3FF) << 2;
        }
    }
    if (D_A884u < (u32)D_main_bss_8011A838) {
        CFR_ENSURE();
        {
            Gfx *g = D_main_bss_8011DC58;
            ((u32 *)g)[0] = 0xF6000000 | ((D_main_bss_8011A838 & 0x3FF) << 14) | ((D_main_bss_8011A886 & 0x3FF) << 2);
            D_main_bss_8011DC58 = g + 1;
            g->words.w1 = ((D_A884u & 0x3FF) << 14) | ((D_A882u & 0x3FF) << 2);
        }
    }
}

extern s8 D_main_bss_8011A88C;
extern s16 D_main_bss_8011A880;
extern s16 D_main_bss_8011A882;
extern s16 D_main_bss_8011A884;
extern u16 D_main_bss_8011A886;
extern u8 D_main_bss_8011A888;
extern u8 D_main_bss_8011A889;
extern u8 D_main_bss_8011A88A;
extern s8 D_main_bss_8011A88D;
extern s8 D_main_bss_8011A88E;

s32 setScreenColorOverlay(s8 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4, u8 arg5, u8 arg6, u8 arg7) {
    D_main_bss_8011A88C = 1;
    D_main_bss_8011A880 = arg1;
    D_main_bss_8011A882 = arg2;
    D_main_bss_8011A884 = arg3;
    D_main_bss_8011A88D = arg0;
    D_main_bss_8011A88E = 0;
    D_main_bss_8011A888 = arg5;
    D_main_bss_8011A889 = arg6;
    D_main_bss_8011A88A = arg7;
    D_main_bss_8011A886 = arg4;
    return 1;
}

extern s8 D_main_bss_8011A88C;

s32 disableScreenColorOverlay(void) {
    D_main_bss_8011A88C = 0;
    return 1;
}

typedef struct {
    s32 a[64];
    s32 b[32];
} RenderStateRow;

s32 beginFrameDLChunk(void);
extern RenderStateRow D_main_bss_8011D498[4];
extern s32 D_main_bss_80128C6C;
extern s32 D_main_bss_801143A0;
extern s32 D_main_bss_8011A460;
extern s32 D_main_bss_8011A4A8;
extern s32 D_main_bss_80117C00;

extern s8 D_main_80037650;
extern s16 D_main_bss_8010D59C;
extern s16 D_main_bss_8010DFD4;
extern s16 D_main_bss_8010DFD6;
extern s32 D_main_bss_8011A838;
extern s32 D_main_bss_8011A83C;
extern u8 D_main_bss_8011A899;
extern s32 D_main_bss_8011A8C0[];
extern s16 D_main_bss_8011A90A;
extern s16 D_main_bss_8011A90C;
extern s16 D_main_bss_8011A90E;
extern s16 D_main_bss_8011A910;
extern s32 D_main_bss_8011DC50;
extern s32 D_main_bss_8011DC5C;
extern u8 D_main_bss_80128EAD;
void heapWalker(void);
void tickTextureMaterialExpiry(void);

s32 frameStartReset(void) {
    s32 i;
    s32 j;
    u8 t;

    D_main_bss_8011A90A = 0;
    D_main_bss_8011A90C = 0;
    D_main_bss_8011DC50 = 0;
    D_main_bss_8011A90E = D_main_bss_8011A838 - 1;
    D_main_bss_8011A910 = D_main_bss_8011A83C - 1;
    heapWalker();
    D_main_bss_80128C6C = 0;
    D_main_bss_801143A0 = 0;
    D_main_bss_8011DC5C = D_main_bss_8011A8C0[D_main_bss_8011A899];
    for (i = 0; i < 4; i++) {
        for (j = 63; j >= 0; j--) {
            D_main_bss_8011D498[i].a[j] = 0;
        }
        for (j = 31; j >= 0; j--) {
            D_main_bss_8011D498[i].b[j] = 0;
        }
    }
    D_main_bss_8011A460 = 0;
    D_main_bss_8011A4A8 = 0;
    D_main_bss_80117C00 = 0;
    D_main_bss_8010DFD4 = 0;
    D_main_bss_8010DFD6 = 0;
    D_main_bss_8010D59C = 0;
    if (*(u8 *)&D_main_bss_8011A88C != 0) {
        if (*(u8 *)&D_main_bss_8011A88D == 1) {
            t = *(u8 *)&D_main_bss_8011A88E;
            if (t < D_main_bss_80128EAD) {
                D_main_80037650 = 1;
                D_main_bss_8011A88E = ++t;
            } else {
                D_main_80037650 = 0;
            }
        } else {
            D_main_80037650 = 1;
        }
    }
    tickTextureMaterialExpiry();
    return 1;
}

s32 clearStructPair2C30(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + 0x2C)) = 0;
    (*(s32 *)((u8 *)(arg0) + 0x30)) = 0;
    return 1;
}

s32 clearFrameReadyFlag();
s32 waitForPostSwapAck();
extern s8 D_main_bss_8011A89A;

s32 waitForPrevFrameDone(void) {
    waitForPostSwapAck();
    D_main_bss_8011A89A = 1;
    clearFrameReadyFlag();
    return 1;
}

typedef struct {
    u16 start;
    u16 end;
    u16 lo1;
    u16 hi1;
    u16 lo0;
    u16 hi0;
} BfRange;

typedef struct {
    s32 dl;
    s32 mtx;
    s32 pad;
} BfDlEntry;

typedef struct BfNode {
    struct BfNode *next;
    s32 dl;
    s32 mtx;
} BfNode;

extern BfRange D_main_bss_8011A470[];
extern BfDlEntry D_bf400[] __asm__("D_main_bss_80116400");
extern s32 D_main_bss_8011A4D0[];
extern Gfx *D_main_bss_8011A4C0;
extern u8 D_main_80037658[];

static __inline__ void bfAlloc(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;
    struct DisplayListBuffer *buf;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    buf = chunk;
    if (*D_main_bss_801163FC == NULL) {
        *D_main_bss_801163FC = buf;
    } else {
        (*D_main_bss_8011A7DC)->next = buf;
        buf->prev = *D_main_bss_8011A7DC;
    }
    buf->next = NULL;
    *D_main_bss_8011A7DC = buf;
    D_main_bss_801163D4 = &buf->displayList[0x1F];
    D_main_bss_8011DC58 = buf->displayList;
}

#define BF_G(g)     CFR_ENSURE();     g = D_main_bss_8011DC58;

static __inline__ void bfEnsure(void) {
    CFR_ENSURE();
}

s32 beginFrameDLChunk(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;
    struct DisplayListBuffer *buf;
    RenderStateRow *row;
    s32 *bl;
    s32 k;
    s32 i;
    s32 j;
    s32 *pp;
    BfNode *n;
    register Gfx *h asm("$2");
    register Gfx *g asm("$3");
    s32 st;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    buf = chunk;
    if (*D_main_bss_801163FC == NULL) {
        *D_main_bss_801163FC = buf;
    } else {
        (*D_main_bss_8011A7DC)->next = buf;
        buf->prev = *D_main_bss_8011A7DC;
    }
    buf->next = NULL;
    *D_main_bss_8011A7DC = buf;
    D_main_bss_801163D4 = &buf->displayList[0x1F];
    D_main_bss_8011DC58 = buf->displayList;
    if (D_main_bss_8011DC50 != 0) {
        ((Gfx *)D_main_bss_8011DC50)->words.w0 = 0x07000000;
        ((Gfx *)D_main_bss_8011DC50)->words.w1 = (u32)buf;
    } else {
        D_main_bss_8011A4C0 = D_main_bss_8011DC58;
        g = D_main_bss_8011DC58++;
        g->words.w0 = 0x06000000;
        g->words.w1 = (u32)D_main_80037658;
    }
    for (k = 0; k < D_main_bss_80117C00; k++) {
        st = D_main_bss_8011A470[k].start;
        BF_G(g);
        g->words.w0 = 0x06000000;
        g->words.w1 = D_bf400[st].dl - 8;
        D_main_bss_8011DC58 = g + 1;
        st++;
        for (j = D_main_bss_8011A470[k].lo0; j < D_main_bss_8011A470[k].hi0; j++) {
            CFR_ENSURE();
            h = D_main_bss_8011DC58;
            h->words.w0 = 0x06000000;
            h->words.w1 = D_main_bss_8011A4D0[j] - 8;
            D_main_bss_8011DC58 = h + 1;
        }
        for (; st < D_main_bss_8011A470[k].end; st++) {
            if (D_bf400[st].mtx != 0) {
                BF_G(g);
                g->words.w0 = 0x01020040;
                g->words.w1 = D_bf400[st].mtx;
                D_main_bss_8011DC58 = g + 1;
            }
            CFR_ENSURE();
            h = D_main_bss_8011DC58;
            h->words.w0 = 0x06000000;
            h->words.w1 = D_bf400[st].dl - 8;
            D_main_bss_8011DC58 = h + 1;
        }
        for (i = 0x3F; i >= 0; i--) {
            for (n = (BfNode *)D_main_bss_8011D498[k].a[i]; n != NULL; n = n->next) {
                if (n->mtx != 0) {
                    BF_G(g);
                    g->words.w0 = 0x01020040;
                    g->words.w1 = n->mtx;
                    D_main_bss_8011DC58 = g + 1;
                }
                BF_G(g);
                g->words.w0 = 0x06000000;
                g->words.w1 = n->dl - 8;
                D_main_bss_8011DC58 = g + 1;
            }
        }
        for (j = D_main_bss_8011A470[k].lo1; j < D_main_bss_8011A470[k].hi1; j++) {
            CFR_ENSURE();
            h = D_main_bss_8011DC58;
            h->words.w0 = 0x06000000;
            h->words.w1 = D_main_bss_8011A4D0[j] - 8;
            D_main_bss_8011DC58 = h + 1;
        }
        for (i = 0x1F; i >= 0; i--) {
            for (n = (BfNode *)D_main_bss_8011D498[k].b[i]; n != NULL; n = n->next) {
                BF_G(g);
                g->words.w0 = 0x06000000;
                g->words.w1 = n->dl - 8;
                D_main_bss_8011DC58 = g + 1;
            }
        }
    }
    CFR_ENSURE();
    D_main_bss_8011DC50 = (s32)D_main_bss_8011DC58++;
    return 1;
}

s32 initRenderStateArrays(void) {
    s32 i;
    s32 j;

    beginFrameDLChunk();
    D_main_bss_80128C6C = 0;
    D_main_bss_801143A0 = 0;
    for (i = 0; i < 4; i++) {
        for (j = 63; j >= 0; j--) {
            D_main_bss_8011D498[i].a[j] = 0;
        }
        for (j = 31; j >= 0; j--) {
            D_main_bss_8011D498[i].b[j] = 0;
        }
    }
    D_main_bss_8011A460 = 0;
    D_main_bss_8011A4A8 = 0;
    D_main_bss_80117C00 = 0;
    return 1;
}

extern s32 D_main_bss_8011A914;
extern s32 D_main_bss_8011A918;
extern s32 D_main_bss_8011A920;
extern s32 D_main_bss_8011DC4C;
extern s32 D_main_bss_8011DC54;
extern u32 D_8011DC58u __asm__("D_main_bss_8011DC58");
extern s32 D_main_bss_80128EDC;
extern s32 D_main_bss_80128EE0;
extern Gfx *D_main_bss_801163D4;
extern struct DisplayListBuffer **D_main_bss_801163FC;
extern struct DisplayListBuffer **D_main_bss_8011A7DC;
Gfx *emitProfilerBarSegment(Gfx *, u32, s16, u8, u8, u8);
Gfx *flushDebugTextOverlay(Gfx *);

#define PROF_CHUNK_WRAP(cur) \
    if ((u32)(cur) >= (u32)D_main_bss_801163D4) { \
        struct DisplayListBuffer *chunk; \
        struct DisplayListBuffer *tail; \
        ((Gfx *)(cur))->words.w0 = 0xB5000000; \
        ((Gfx *)(cur))->words.w1 = 0; \
        chunk = D_main_bss_801163B0; \
        if (chunk == NULL) { \
            chunk = findAndUnlinkSmallestEntry(); \
            if (chunk != NULL) { \
                tail = chunk; \
                while (tail->next != NULL) { \
                    tail = tail->next; \
                } \
                tail->next = D_main_bss_801163B0; \
                if (D_main_bss_801163B0 != NULL) { \
                    D_main_bss_801163B0->prev = tail; \
                } \
                D_main_bss_801163B0 = chunk; \
                chunk->prev = NULL; \
            } \
            chunk = D_main_bss_801163B0; \
        } \
        D_main_bss_801163B0 = D_main_bss_801163B0->next; \
        if (D_main_bss_801163B0 != NULL) { \
            D_main_bss_801163B0->prev = NULL; \
        } \
        if (*D_main_bss_801163FC == NULL) { \
            *D_main_bss_801163FC = chunk; \
        } else { \
            (*D_main_bss_8011A7DC)->next = chunk; \
            chunk->prev = *D_main_bss_8011A7DC; \
        } \
        chunk->next = NULL; \
        *D_main_bss_8011A7DC = chunk; \
        D_main_bss_801163D4 = &chunk->displayList[0x1F]; \
        D_8011DC58u = (u32)chunk->displayList; \
    }

#define PROF_CHUNK_WRAP2(cur) \
    if ((u32)(cur) >= (u32)D_main_bss_801163D4) { \
        struct DisplayListBuffer *chunk; \
        struct DisplayListBuffer *tail; \
        ((Gfx *)(cur))->words.w0 = 0xB5000000; \
        ((Gfx *)(cur))->words.w1 = 0; \
        chunk = D_main_bss_801163B0; \
        if (chunk == NULL) { \
            chunk = findAndUnlinkSmallestEntry(); \
            if (chunk != NULL) { \
                tail = chunk; \
                while (tail->next != NULL) { \
                    tail = tail->next; \
                } \
                tail->next = D_main_bss_801163B0; \
                if (D_main_bss_801163B0 != NULL) { \
                    D_main_bss_801163B0->prev = tail; \
                } \
                D_main_bss_801163B0 = chunk; \
                chunk->prev = NULL; \
            } \
            chunk = D_main_bss_801163B0; \
        } \
        D_main_bss_801163B0 = D_main_bss_801163B0->next; \
        if (D_main_bss_801163B0 != NULL) { \
            D_main_bss_801163B0->prev = NULL; \
        } \
        buf = chunk; \
        if (*D_main_bss_801163FC == NULL) { \
            *D_main_bss_801163FC = buf; \
        } else { \
            (*D_main_bss_8011A7DC)->next = buf; \
            buf->prev = *D_main_bss_8011A7DC; \
        } \
        buf->next = NULL; \
        *D_main_bss_8011A7DC = buf; \
        D_main_bss_801163D4 = &buf->displayList[0x1F]; \
        D_8011DC58u = (u32)buf->displayList; \
    }

s32 drawFrameProfilerBars(void) {
    u32 *cur;
    u32 *p;
    u32 *q;
    Gfx *gq;
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;
    struct DisplayListBuffer *buf;

    beginFrameDLChunk();
    D_8011DC58u = D_main_bss_8011DC50;
    D_8011DC58u = (u32)emitProfilerBarSegment((Gfx *)D_main_bss_8011DC50, D_main_bss_8011A914, D_main_bss_8011A910 - 0x28, 0xFF, 0xFF, 0);
    D_8011DC58u = (u32)emitProfilerBarSegment((Gfx *)D_8011DC58u, D_main_bss_80128EE0, D_main_bss_8011A910 - 0x23, 0, 0, 0xFF);
    D_8011DC58u = (u32)emitProfilerBarSegment((Gfx *)D_8011DC58u, D_main_bss_80128EDC, D_main_bss_8011A910 - 0x1E, 0xFF, 0, 0);
    D_8011DC58u = (u32)emitProfilerBarSegment((Gfx *)D_8011DC58u, D_main_bss_8011A920, D_main_bss_8011A910 - 0x19, 0xFF, 0, 0xFF);
    D_8011DC58u = (u32)emitProfilerBarSegment((Gfx *)D_8011DC58u, D_main_bss_8011DC54, D_main_bss_8011A910 - 0x14, 0xFF, 0xFF, 0xFF);
    D_8011DC58u = (u32)emitProfilerBarSegment((Gfx *)D_8011DC58u, D_main_bss_8011DC4C, D_main_bss_8011A910 - 0xF, 0, 0xFF, 0);
    D_8011DC58u = (u32)emitProfilerBarSegment((Gfx *)D_8011DC58u, D_main_bss_8011A918, D_main_bss_8011A910 - 0xA, 0, 0xFF, 0xFF);
    cur = (u32 *)flushDebugTextOverlay((Gfx *)D_8011DC58u);
    D_8011DC58u = (u32)cur;
    PROF_CHUNK_WRAP2(cur);
    p = (u32 *)D_8011DC58u;
    D_8011DC58u = (u32)(p + 2);
    ((Gfx *)p)->words.w0 = 0xE9000000;
    ((Gfx *)p)->words.w1 = 0;
    PROF_CHUNK_WRAP(p + 2);
    q = (u32 *)D_8011DC58u;
    D_8011DC58u = (u32)(q + 2);
    q[0] = 0xB8000000;
    q[1] = 0;
    return 1;
}

typedef struct { s32 w0; void *p4; } EcRefB;
typedef struct { s32 w0; u32 w4; } EcRefC;
extern u16 ecCountB __asm__("D_main_bss_8010DFD6");
extern u16 ecCountC __asm__("D_main_bss_8010D59C");
extern EcRefB *ecRefsB[] __asm__("D_main_bss_8010E010");
extern EcRefC *ecRefsC[] __asm__("D_main_bss_8010DF50");

void emitCombinerStateAndPatch(void *arg0, u8 arg1) {
    s32 i;
    u32 mode;

    for (i = 0; i < ecCountB; i++) {
        ecRefsB[i]->p4 = arg0;
    }
    mode = (arg1 != 0) ? 0x2000000 : 0x3000000;
    for (i = 0; i < ecCountC; i++) {
        ecRefsC[i]->w4 &= 0xFCFFFFFF;
        ecRefsC[i]->w4 |= mode;
    }
}

extern s32 D_main_bss_8011A900;
extern s32 D_main_bss_8011A904;
extern s32 D_main_bss_80128ED8;

void computeFrameDeltaTime(void) {
    if (D_main_bss_8011A900 == -1) {
        D_main_bss_8011A904 = 0;
    } else {
        D_main_bss_8011A904 = D_main_bss_80128ED8 - D_main_bss_8011A900;
    }
    D_main_bss_8011A900 = D_main_bss_80128ED8;
}

typedef struct {
    s32 w0;
    s32 w4;
    u8 b8[4];
    f32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
} TfSnap;

extern struct { f32 a; f32 b; } tfAcc __asm__("D_main_bss_8011A8F8");
extern struct { s32 v; } tfLast __asm__("D_main_bss_8011A8F0");
extern struct { s32 v; } tfFrames __asm__("D_main_bss_8011A890");
extern struct { u32 hi; u32 lo; } tfClkS __asm__("osClockRate");
extern f32 D_main_bss_8011A8F4;
typedef struct { f32 v; } TfF;
#define tfCnt (*(TfF *)&D_main_bss_8011A8F4)
typedef struct { f32 a; f32 b; } TfAcc;
extern u8 D_main_bss_8011A8C9;
extern u8 D_main_bss_8011A8C8;
extern u8 D_main_bss_80128EAF;
extern u8 D_main_bss_80128EAE;
void tfAwait(void) __asm__("awaitFrameSyncMesgBlock");
void tfSignal(void) __asm__("signalFrameSyncMesgNonblock");
void readBufferSwapState(void *, u32 *, u32 *);
f32 getViModePeriod(void);
u64 osGetTime(void);

s32 timeSnapshotFiller(TfSnap *s) {
    u32 r0;
    u32 r1;
    u32 now;
    f32 v;
    f32 cnt;
    f32 avg;
    TfAcc *acc;
    u32 *clk;

    tfAwait();
    now = osGetTime();
    if (tfLast.v == -1) {
        s->f24 = 0.0f;
        s->w4 = 0;
        s->w0 = 0;
    } else {
        s->w4 = tfFrames.v - 1;
        s->w0 = tfFrames.v;
        s->f24 = (f32)(u32)(now - tfLast.v) / (f32)tfClkS.lo;
    }
    readBufferSwapState(s->b8, &r0, &r1);
    acc = (TfAcc *)&tfAcc;
    __asm__("" : "=r"(acc) : "0"(acc));
    {
        f32 fr = (f32)r0;
        clk = &tfClkS.lo;
        __asm__("" : "=r"(clk) : "0"(clk));
        s->fC = fr / (f32)*clk;
    }
    acc->a += s->fC;
    { f32 *p10 = &s->f10; *p10 = (f32)r1 / (f32)*clk; }
    cnt = D_main_bss_8011A8F4 + 1.0f;
    avg = acc->a / cnt;
    { f32 *pb = &acc->b; *pb += s->f10; }
    D_main_bss_8011A8F4 = cnt;
    s->f14 = avg;
    s->f18 = acc->b / tfCnt.v;
    { f32 *p1C = &s->f1C; *p1C = getViModePeriod() / 1000.0f; }
    tfLast.v = now;
    if (D_main_bss_8011A8C9 != 0 && D_main_bss_8011A8C8 != 0) {
        if (D_main_bss_8011A900 == -1) {
            v = 0.0f;
        } else {
            f32 t = (f32)(u32)(D_main_bss_80128ED8 - D_main_bss_8011A900) / (f32)tfClkS.lo;
            if (D_main_bss_80128EAF - D_main_bss_80128EAE >= 2) {
                t += getViModePeriod() * 0.001f * (D_main_bss_80128EAF - D_main_bss_80128EAE);
            } else {
                t += getViModePeriod() * 0.001f;
            }
            v = t;
        }
    } else {
        v = (f32)(u32)D_main_bss_8011A904 / (f32)tfClkS.lo;
    }
    s->f20 = v;
    tfSignal();
    return 1;
}

s32 osRecvMesg(void *, void *, s32);
void osYieldThread(void);
void bufferArbiterMarkSlotReady(void);
void bufferArbiterProducerMark(void);
void waitOnVideoQueue(void);
void awaitFrameSyncMesgBlock(void);
void signalFrameSyncMesgNonblock(void);
extern u8 D_main_bss_8011A818[];
extern u8 D_main_8011A7E8[];
extern u8 D_main_bss_8011A89E;
extern u8 D_main_bss_8011A89D;
extern s8 D_main_bss_8011A89A;
extern u8 D_main_bss_80128EAA[];
extern u8 D_main_bss_80128EAD;

void bufferArbiterProducerScanWait(void) {
    u32 i;
    volatile u8 *pending = &D_main_bss_8011A89E;
    s32 stateA;
    s32 stateB;
    u8 *count;

    if (*pending != 0) {
        osRecvMesg(D_main_bss_8011A818, NULL, 1);
        *pending = 0;
        osYieldThread();
    }
    bufferArbiterMarkSlotReady();
    if (D_main_bss_8011A89D != 0) {
        osRecvMesg(D_main_8011A7E8, NULL, 1);
        D_main_bss_8011A89D = 0;
        osYieldThread();
    }
    D_main_bss_8011A89A = 0;
    bufferArbiterProducerMark();
    stateA = 3;
    count = &D_main_bss_80128EAD;
    stateB = 4;
    do {
        i = 0;
        waitOnVideoQueue();
        awaitFrameSyncMesgBlock();
        for (i = 0; i < *count; i++) {
            if (D_main_bss_80128EAA[i] == stateA || D_main_bss_80128EAA[i] == stateB) {
                break;
            }
        }
        signalFrameSyncMesgNonblock();
    } while (i != D_main_bss_80128EAD);
}

u32 getTimeSinceLastFrame(void);
void yieldFromSpThread(void);
void yieldFromGfxFrame(void);
void bufferArbiterMarkSlotReady(void);


void *bufferArbiterAllocSlot(s32);
u8 getInactiveBufferIndex(void);
void osWritebackDCacheAll(void);
s32 osSendMesg(void *, void *, s32);
void osDpGetCounters(u32 *);
void osDpSetStatus(u32);
void setPostSwapPendingFlags(void);
u8 isPreNmiPending(void);
void recordFrameTimestamp(void);
extern u16 sgCountA __asm__("D_main_bss_8010DFD4");
extern u16 sgCountB __asm__("D_main_bss_8010DFD6");
extern u16 sgCountC __asm__("D_main_bss_8010D59C");
extern struct meshdef1 *sgMeshes[] __asm__("D_main_bss_8010E090");
typedef struct { s32 w0; void *p4; } SgRefB;
typedef struct { s32 w0; u32 w4; } SgRefC;
extern SgRefB *sgRefsB[] __asm__("D_main_bss_8010E010");
extern SgRefC *sgRefsC[] __asm__("D_main_bss_8010DF50");
extern void *sgSlots[] __asm__("D_main_bss_801163C8");
extern u8 sgBufIdx __asm__("D_main_bss_8011A899");
extern s32 sgFrameCount __asm__("D_main_bss_8011A890");
extern volatile s32 sgFrameCountV __asm__("D_main_bss_8011A890");
extern u8 sgStamp2 __asm__("D_main_bss_801142C0+2");
typedef struct { u16 a; u16 stamp; } SgVs;
extern SgVs sgVtxSlots[] __asm__("D_main_bss_80113240");
typedef struct { u32 type, flags; u8 *ucode_boot; u32 ucode_boot_size; u32 ucode, ucode_size, ucode_data, ucode_data_size, dram_stack, dram_stack_size, output_buff, output_buff_size; Gfx *data_ptr; u32 data_size, yield_data_ptr, yield_data_size; } SgTask;
extern SgTask gspTaskS __asm__("gspTask");
extern u8 rspbootTextStart[];
extern u8 findModelAnimKeyframeByPhase[];
extern u32 D_main_800377C0;
extern u32 D_main_800377C4;
extern Gfx *D_main_bss_8011A4C0;
extern u8 D_main_8011A420[];
typedef struct { u8 type; void *task; } SgMsg;
extern SgMsg sgMsg __asm__("D_main_80112AE0");

#define SG_DP_COUNTERS() \
    if (wait != 0) { \
        osRecvMesg(D_main_8011A7E8, NULL, 1); \
        yieldFromGfxFrame(); \
    } \
    osDpGetCounters(cnt); \
    D_main_bss_8011A920 = (u32)((f32)cnt[1] * 0.77034); \
    D_main_bss_8011DC54 = (u32)((f32)cnt[2] * 0.77034) - D_main_bss_8011A920; \
    D_main_bss_8011DC4C = (u32)((f32)cnt[3] * 0.77034);

s32 submitGfxFrame(void) {
    u32 cnt[4];
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    u8 wait;
    void *slot;
    u8 idx;
    u32 mode;
    volatile u8 *pend;
    volatile s32 *fc;
    u8 m;

    D_main_bss_8011A914 = getTimeSinceLastFrame();
    if (*(volatile u8 *)&D_main_bss_8011A89E != 0) {
        osRecvMesg(D_main_bss_8011A818, NULL, 1);
        yieldFromSpThread();
    }
    bufferArbiterMarkSlotReady();
    drainMeshReleaseQueue();
    for (i = 0; i < sgCountA; i++) {
        commitMeshDrawBatchRefs(sgMeshes[i]);
    }
    pend = &D_main_bss_8011A89D;
    wait = *pend;
    if (sgSlots[sgBufIdx] != NULL) {
        slot = bufferArbiterAllocSlot(1);
        if (slot != NULL) {
            idx = getInactiveBufferIndex();
            for (j = 0; j < sgCountB; j++) {
                sgRefsB[j]->p4 = slot;
            }
            mode = (idx != 0) ? 0x2000000 : 0x3000000;
            for (j = 0; j < sgCountC; j++) {
                sgRefsC[j]->w4 &= 0xFCFFFFFF;
                sgRefsC[j]->w4 |= mode;
            }
            osWritebackDCacheAll();
            gspTaskS.data_ptr = D_main_bss_8011A4C0 - 1;
            gspTaskS.data_size = 0;
            gspTaskS.ucode_boot = rspbootTextStart;
            gspTaskS.ucode_boot_size = findModelAnimKeyframeByPhase - rspbootTextStart;
            D_main_bss_8011A89E = 1;
            D_main_bss_8011A89D = 1;
            sgMsg.type = 1;
            sgMsg.task = &gspTaskS;
            gspTaskS.ucode = D_main_800377C0;
            gspTaskS.ucode_data = D_main_800377C4;
            osSendMesg(D_main_8011A420, &sgMsg, 0);
            SG_DP_COUNTERS();
            osDpSetStatus(0x1C0);
            bufferArbiterProducerMark();
            if (D_main_bss_8011A900 == -1) {
                D_main_bss_8011A904 = 0;
            } else {
                D_main_bss_8011A904 = D_main_bss_80128ED8 - D_main_bss_8011A900;
            }
            D_main_bss_8011A900 = D_main_bss_80128ED8;
        } else {
            SG_DP_COUNTERS();
            bufferArbiterProducerMark();
            setPostSwapPendingFlags();
        }
    } else {
        *pend = 0;
        D_main_bss_8011A89E = 0;
        bufferArbiterProducerMark();
    }
    while (isPreNmiPending()) {
    }
    fc = &sgFrameCount;
    *fc += 1;
    sgBufIdx ^= 1;
    sgVtxSlots[sgStamp2++].stamp = 0;
    if (sgStamp2 == 0x20) {
        sgStamp2 = 0;
    }
    recordFrameTimestamp();
    return 1;
}

extern Gfx *D_main_bss_801163B8;
extern u8 D_main_bss_801163BC;
void recordDeferredDrawRefA(s32 flags, s32 ref) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;
    u8 *cnt;

    if (flags & 0x40000000) {
        if (D_main_bss_801163BC >= 0x40) {
            chunk = D_main_bss_801163B0;
            if (chunk == NULL) {
                chunk = findAndUnlinkSmallestEntry();
                if (chunk != NULL) {
                    tail = chunk;
                    while (tail->next != NULL) {
                        tail = tail->next;
                    }
                    tail->next = D_main_bss_801163B0;
                    if (D_main_bss_801163B0 != NULL) {
                        D_main_bss_801163B0->prev = tail;
                    }
                    D_main_bss_801163B0 = chunk;
                    chunk->prev = NULL;
                }
                chunk = D_main_bss_801163B0;
            }
            D_main_bss_801163B0 = D_main_bss_801163B0->next;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = NULL;
            }
            if (*D_main_bss_8011A4B8 != NULL) {
                (*D_main_bss_8011A4B8)->prev = chunk;
            }
            chunk->next = *D_main_bss_8011A4B8;
            *D_main_bss_8011A4B8 = chunk;
            D_main_bss_801163B8 = chunk->displayList;
            D_main_bss_801163BC = 0;
        }
        cnt = &D_main_bss_801163BC;
        ((s32 *)D_main_bss_801163B8)[(*cnt)++] = ref;
    }
}

void recordDeferredDrawRefB(s32 flags) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;
    u8 *cnt;

    if (flags & 0x40000000) {
        if (D_main_bss_801163BC >= 0x40) {
            chunk = D_main_bss_801163B0;
            if (chunk == NULL) {
                chunk = findAndUnlinkSmallestEntry();
                if (chunk != NULL) {
                    tail = chunk;
                    while (tail->next != NULL) {
                        tail = tail->next;
                    }
                    tail->next = D_main_bss_801163B0;
                    if (D_main_bss_801163B0 != NULL) {
                        D_main_bss_801163B0->prev = tail;
                    }
                    D_main_bss_801163B0 = chunk;
                    chunk->prev = NULL;
                }
                chunk = D_main_bss_801163B0;
            }
            D_main_bss_801163B0 = D_main_bss_801163B0->next;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = NULL;
            }
            if (*D_main_bss_8011A4B8 != NULL) {
                (*D_main_bss_8011A4B8)->prev = chunk;
            }
            chunk->next = *D_main_bss_8011A4B8;
            *D_main_bss_8011A4B8 = chunk;
            D_main_bss_801163B8 = chunk->displayList;
            D_main_bss_801163BC = 0;
        }
        cnt = &D_main_bss_801163BC;
        ((s32 *)D_main_bss_801163B8)[(*cnt)++] = 0;
    }
}

void recordDeferredDrawRefC(s32 flags, s32 ref) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;


    if (flags & 0x40000000) {
        if (D_main_bss_801163BC >= 0x40) {
            chunk = D_main_bss_801163B0;
            if (chunk == NULL) {
                chunk = findAndUnlinkSmallestEntry();
                if (chunk != NULL) {
                    tail = chunk;
                    while (tail->next != NULL) {
                        tail = tail->next;
                    }
                    tail->next = D_main_bss_801163B0;
                    if (D_main_bss_801163B0 != NULL) {
                        D_main_bss_801163B0->prev = tail;
                    }
                    D_main_bss_801163B0 = chunk;
                    chunk->prev = NULL;
                }
                chunk = D_main_bss_801163B0;
            }
            D_main_bss_801163B0 = D_main_bss_801163B0->next;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = NULL;
            }
            if (*D_main_bss_8011A4B8 != NULL) {
                (*D_main_bss_8011A4B8)->prev = chunk;
            }
            chunk->next = *D_main_bss_8011A4B8;
            *D_main_bss_8011A4B8 = chunk;
            D_main_bss_801163B8 = chunk->displayList;
            D_main_bss_801163BC = 0;
        }
        ((s32 *)D_main_bss_801163B8)[D_main_bss_801163BC++] = ref;
    }
}

void recordDeferredDrawRefD(s32 flags) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;


    if (flags & 0x40000000) {
        if (D_main_bss_801163BC >= 0x40) {
            chunk = D_main_bss_801163B0;
            if (chunk == NULL) {
                chunk = findAndUnlinkSmallestEntry();
                if (chunk != NULL) {
                    tail = chunk;
                    while (tail->next != NULL) {
                        tail = tail->next;
                    }
                    tail->next = D_main_bss_801163B0;
                    if (D_main_bss_801163B0 != NULL) {
                        D_main_bss_801163B0->prev = tail;
                    }
                    D_main_bss_801163B0 = chunk;
                    chunk->prev = NULL;
                }
                chunk = D_main_bss_801163B0;
            }
            D_main_bss_801163B0 = D_main_bss_801163B0->next;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = NULL;
            }
            if (*D_main_bss_8011A4B8 != NULL) {
                (*D_main_bss_8011A4B8)->prev = chunk;
            }
            chunk->next = *D_main_bss_8011A4B8;
            *D_main_bss_8011A4B8 = chunk;
            D_main_bss_801163B8 = chunk->displayList;
            D_main_bss_801163BC = 0;
        }
        ((s32 *)D_main_bss_801163B8)[D_main_bss_801163BC++] = 0;
    }
}

extern s32 *D_main_bss_8011A438;
extern s32 D_main_bss_8011A43C;
extern u8 D_main_bss_8011A440;

static __inline__ Gfx *raeAllocBuf(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;
    struct DisplayListBuffer *buf;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    buf = chunk;
    if (*D_main_bss_801163FC == NULL) {
        *D_main_bss_801163FC = buf;
    } else {
        (*D_main_bss_8011A7DC)->next = buf;
        buf->prev = *D_main_bss_8011A7DC;
    }
    buf->next = NULL;
    *D_main_bss_8011A7DC = buf;
    D_main_bss_801163D4 = &buf->displayList[0x1F];
    return buf->displayList;
}

static __inline__ void raeRecord(s32 ref, s32 flags, s32 kind) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;
    u8 *cnt;

    if (flags & 0x40000000) {
        if (D_main_bss_8011D094 >= 0x40) {
            chunk = D_main_bss_801163B0;
            if (chunk == NULL) {
                chunk = findAndUnlinkSmallestEntry();
                if (chunk != NULL) {
                    tail = chunk;
                    while (tail->next != NULL) {
                        tail = tail->next;
                    }
                    tail->next = D_main_bss_801163B0;
                    if (D_main_bss_801163B0 != NULL) {
                        D_main_bss_801163B0->prev = tail;
                    }
                    D_main_bss_801163B0 = chunk;
                    chunk->prev = NULL;
                }
                chunk = D_main_bss_801163B0;
            }
            D_main_bss_801163B0 = D_main_bss_801163B0->next;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = NULL;
            }
            if (*D_main_bss_8011A4BC != NULL) {
                (*D_main_bss_8011A4BC)->prev = chunk;
            }
            chunk->next = *D_main_bss_8011A4BC;
            *D_main_bss_8011A4BC = chunk;
            D_main_bss_8011D090 = chunk->displayList;
            D_main_bss_8011D094 = 0;
        }
        cnt = &D_main_bss_8011D094;
        ((s32 *)D_main_bss_8011D090)[(*cnt)++] = (ref & 0xFFFFFF) | (kind << 24);
    }
}

static __inline__ Gfx *raeAllocB(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    if (*D_main_bss_8011A4AC != NULL) {
        (*D_main_bss_8011A4AC)->prev = chunk;
    }
    chunk->next = *D_main_bss_8011A4AC;
    *D_main_bss_8011A4AC = chunk;
    return chunk->displayList;
}

Gfx *raeImpl(Gfx *dl, s32 flags) __asm__("reserveAndEmitDLEntry");
Gfx *raeImpl(Gfx *dl, s32 flags) {
    if (dl >= D_main_bss_801163D4) {
        dl->words.w0 = 0xB5000000;
        dl->words.w1 = 0;
        dl = raeAllocBuf();
    }
    raeRecord((s32)dl, flags, 1);
    D_main_bss_8011A438 = (s32 *)dl;
    D_main_bss_8011A440 = 0;
    dl++;
    D_main_bss_8011A43C = (s32)raeAllocB();
    return dl;
}

s32 reserveAndEmitDLEntry(s32, s32);
extern s32 *D_main_bss_8011A438;
extern s32 D_main_bss_8011A43C;
extern u8 D_main_bss_8011A440;

s32 reserveAlignedDLSpace(s32 gfx, u8 *out, u8 n, s32 *ptr, s32 arg4) {
    u8 *used = &D_main_bss_8011A440;
    s32 base;
    s32 *g;

    if (*used + n > 0x40) {
        g = D_main_bss_8011A438;
        g[0] = ((((D_main_bss_8011A440 * 4) + 0xF) & 0xFFF0) - 1) & 0xFFFF | 0x02000000;
        g[1] = D_main_bss_8011A43C;
        gfx = reserveAndEmitDLEntry(gfx, arg4);
    }
    base = *used * 4;
    out[1] = base;
    if (n == 1) {
        out[2] = out[3] = out[0] = base;
    } else {
        out[2] = base + 4;
        out[3] = base + 8;
        if (n == 3) {
            out[0] = out[1];
        } else {
            out[0] = base + 0xC;
        }
    }
    *ptr = D_main_bss_8011A43C + D_main_bss_8011A440 * 4;
    D_main_bss_8011A440 += n;
    return gfx;
}















INCLUDE_ASM("asm/nonmatchings/main/08510", heapFreeListDequeue);

typedef struct { s16 x, y, z, w; } EtfVtx;
typedef struct { u8 pad0[0xC]; u32 flags; u8 pad10[0x14]; void *p24; } EtfMesh;
extern u8 *etfB4 __asm__("D_main_bss_801163B4");
extern u8 D_main_80037640[];
extern void transformAndEmitFaceVertices(u32 *, u16 *, u32 *, void *, u32, void *, s32, EtfMesh *);

void emitTexturedFaceGeometry(u32 *face, u32 *out, u32 *col, EtfVtx *dst, EtfVtx *src, s32 arg5, EtfMesh *m, u8 mask, u8 count) {
    u32 fl;
    u16 *idx;
    u32 *t6;
    s32 n;
    s32 bit;
    s32 i;

    idx = (u16 *)((u8 *)face + ((face[1] >> 16) & 0xFC));
    fl = face[0];
    t6 = (u32 *)((u8 *)face + ((face[1] >> 10) & 0xFC));
    if (m->flags & 0x40) {
        n = 3;
        if (fl & 8) {
            n = 4;
        }
        bit = 1;
        if (m->flags & 1) {
            f32 *pos = m->p24;
            for (i = 0; i < n; i++, bit <<= 1) {
                if (mask & bit) {
                    f32 *v = &pos[idx[i] * 3];
                    dst->x = v[0] * 256.0f;
                    dst->y = v[1] * 256.0f;
                    dst->z = v[2] * 256.0f;
                    dst = (EtfVtx *)((s16 *)dst + 2);
                    dst = (EtfVtx *)((s16 *)dst + 2);
                }
            }
        } else {
            EtfVtx *tb = m->p24;
            for (i = 0; i < n; i++, bit <<= 1) {
                if (mask & bit) {
                    *dst = tb[idx[i]];
                    dst++;
                }
            }
        }
    } else if (src != NULL) {
        for (i = 0; i < count; i++) {
            dst[i] = src[i];
        }
    }
    if (m->flags & 0x20) {
        if ((fl & 0x40) && !(m->flags & 0x100000)) {
            transformAndEmitFaceVertices(out, idx, t6, (u8 *)face + ((face[1] & 0xFC0) >> 4), fl,
                                         etfB4 != NULL ? etfB4 + ((u16 *)face)[4] * 16 : D_main_80037640, ({ __asm__ volatile(""); arg5; }), m);
        } else {
            out[0] = t6[0];
            if (fl & 0x10) {
                out[1] = t6[1];
                out[2] = t6[2];
                if (fl & 8) {
                    out[3] = t6[3];
                }
            } else if (fl & 0x20) {
                out[1] = t6[0];
                out[2] = t6[0];
                if (fl & 8) {
                    out[3] = t6[0];
                }
            }
        }
    } else if (col != NULL) {
        if (fl & 0x30) {
            i = (fl & 8) ? 3 : 2;
        } else {
            i = 0;
        }
        for (; i >= 0; i--) {
            out[i] = col[i];
        }
    }
}

f32 cosf(f32);
f32 vec3Length(f32 *);
void normalize_vector(f32 *);
void transformVec3ByMat34(f32 *, f32 *, f32 *);
void rotateVec3ByMat3x3(f32 *, f32 *, f32 *);

void transformLightByType(u8 *light, f32 *mat) {
    f32 v[3];
    f32 out[3];
    f32 *p;
    f32 len;

    switch (light[8]) {
    case 1:
        rotateVec3ByMat3x3(mat, (f32 *)(light + 0x18), (f32 *)(light + 0x44));
        normalize_vector((f32 *)(light + 0x44));
        break;
    case 2:
        transformVec3ByMat34(mat, (f32 *)(light + 0xC), (f32 *)(light + 0x38));
        if (*(f32 *)(light + 0x30) != 0.0f) {
            v[0] = *(f32 *)(light + 0x30);
            v[2] = 0.0f;
            v[1] = 0.0f;
            rotateVec3ByMat3x3(mat, v, out);
            *(f32 *)(light + 0x50) = vec3Length(out);
        }
        break;
    case 3:
        transformVec3ByMat34(mat, (f32 *)(light + 0xC), (f32 *)(light + 0x38));
        rotateVec3ByMat3x3(mat, (f32 *)(light + 0x18), (f32 *)(light + 0x44));
        normalize_vector((f32 *)(light + 0x44));
        if (*(f32 *)(light + 0x30) != 0.0f) {
            v[0] = *(f32 *)(light + 0x30);
            v[2] = 0.0f;
            v[1] = 0.0f;
            rotateVec3ByMat3x3(mat, v, out);
            *(f32 *)(light + 0x50) = vec3Length(out);
        }
        *(f32 *)(light + 0x54) = cosf(*(f32 *)(light + 0x34) * 0.017453292f / 2.0f);
        break;
    }
}

typedef struct {
    u32 w0;
    u32 w1;
} RdpWord;

extern f32 D_main_bss_8011D088;
extern s32 D_main_8003775C[];
extern s32 D_main_8003776C[];
extern s32 D_main_bss_8011A858;
extern s32 D_main_bss_8011A85C;
extern u8 D_main_bss_8011A860;
extern u8 D_main_bss_8011A861;
extern u8 D_main_bss_8011A908;
extern u8 D_main_bss_8011A898;

RdpWord *appendRdpStateDl(RdpWord *dl, u32 flags, u8 *outA, u8 *outB) {
    u32 om;
    u32 geomSet;
    u32 geomClr;
    RdpWord *p;
    RdpWord *q;
    u8 v;

    p = dl++;
    p->w0 = 0xE7000000;
    p->w1 = 0;
    if (flags & 0x200000) {
        om = 0;
        geomSet = 0x1000;
        geomClr = 0;
    } else {
        om = 0x80000;
        geomSet = 0;
        geomClr = 0x1000;
    }
    if (!(flags & 0x8000)) {
        om |= 0x2000;
    }
    if (flags & 0x80000) {
        p = dl++;
        p->w0 = 0xB9000201;
        p->w1 = 4;
        q = dl++;
        q->w0 = 0xEE000000;
        q->w1 = (u32)D_main_bss_8011D088 << 16;
        geomClr |= 1;
    } else {
        p = dl++;
        p->w0 = 0xB9000201;
        p->w1 = 0;
        geomSet |= 1;
    }
    if (flags & 0x1C00000) {
        om |= D_main_8003775C[(flags & 0x1C00000) >> 22];
    } else {
        om |= D_main_bss_8011A858;
    }
    if (flags & 0xE000000) {
        om |= D_main_8003776C[(flags & 0xE000000) >> 25];
    } else {
        om |= D_main_bss_8011A85C;
    }
    if (!(flags & 0x10000) && D_main_bss_8011A898 != 0) {
        geomSet |= 0x10000;
        v = 0x82;
    } else {
        geomClr |= 0x10000;
        v = 1;
    }
    D_main_bss_8011A908 = v;
    if (geomSet != 0) {
        p = dl++;
        p->w0 = 0xB7000000;
        p->w1 = geomSet;
    }
    if (geomClr != 0) {
        p = dl++;
        p->w0 = 0xB6000000;
        p->w1 = geomClr;
    }
    dl[0].w0 = 0xBE000000;
    dl[0].w1 = om;
    dl[1].w0 = 0xFFF7CF0F;
    dl[1].w1 = 0;
    dl += 2;
    flags &= 0x30000000;
    if (flags != 0) {
        switch (flags) {
        case 0x30000000:
            D_main_bss_8011A861 = 1;
            break;
        case 0x10000000:
            D_main_bss_8011A861 = 0;
            break;
        case 0x20000000:
            D_main_bss_8011A861 = 2;
            break;
        }
    } else {
        D_main_bss_8011A861 = D_main_bss_8011A860;
    }
    *outB = 0x7F;
    *outA = 0xFF;
    return dl;
}

extern s32 D_main_80037760[];
extern s32 D_main_bss_8011A858;

s32 selectRenderPresetByIndex(u8 arg0) {
    D_main_bss_8011A858 = D_main_80037760[arg0];
    return 1;
}

extern s32 D_main_80037770[];
extern s32 D_main_bss_8011A85C;

s32 selectSecondaryPresetByIndex(u8 arg0) {
    D_main_bss_8011A85C = D_main_80037770[arg0];
    return 1;
}

extern Gfx *D_main_bss_8011DC58;
extern Gfx *D_main_bss_801163D4;
extern struct DisplayListBuffer **D_main_bss_801163FC;
extern struct DisplayListBuffer **D_main_bss_8011A7DC;
extern u8 D_main_bss_8011A908;
extern u8 D_main_bss_801143A8;
struct DisplayListBuffer *findAndUnlinkSmallestEntry(void);
Gfx *findOrCreateMaterial(Gfx *, u16, s32);
Gfx *emitMaterialRenderModeDL(Gfx *, s32, s32);

#define DL_ENSURE()                                                                  \
    if (D_main_bss_8011DC58 >= D_main_bss_801163D4) {                                \
        struct DisplayListBuffer *chunk;                                             \
        struct DisplayListBuffer *tail;                                              \
        struct DisplayListBuffer *buf;                                               \
        D_main_bss_8011DC58->words.w0 = 0xB5000000;                                  \
        D_main_bss_8011DC58->words.w1 = 0;                                           \
        chunk = D_main_bss_801163B0;                                                 \
        if (chunk == NULL) {                                                         \
            chunk = findAndUnlinkSmallestEntry();                                    \
            if (chunk != NULL) {                                                     \
                tail = chunk;                                                        \
                while (tail->next != NULL) {                                         \
                    tail = tail->next;                                               \
                }                                                                    \
                tail->next = D_main_bss_801163B0;                                    \
                if (D_main_bss_801163B0 != NULL) {                                   \
                    D_main_bss_801163B0->prev = tail;                                \
                }                                                                    \
                D_main_bss_801163B0 = chunk;                                         \
                chunk->prev = NULL;                                                  \
            }                                                                        \
            chunk = D_main_bss_801163B0;                                             \
        }                                                                            \
        D_main_bss_801163B0 = D_main_bss_801163B0->next;                             \
        if (D_main_bss_801163B0 != NULL) {                                           \
            D_main_bss_801163B0->prev = NULL;                                        \
        }                                                                            \
        buf = chunk;                                                                 \
        if (*D_main_bss_801163FC == NULL) {                                          \
            *D_main_bss_801163FC = buf;                                              \
        } else {                                                                     \
            (*D_main_bss_8011A7DC)->next = buf;                                      \
            buf->prev = *D_main_bss_8011A7DC;                                        \
        }                                                                            \
        buf->next = NULL;                                                            \
        *D_main_bss_8011A7DC = buf;                                                  \
        D_main_bss_801163D4 = &buf->displayList[0x1F];                               \
        D_main_bss_8011DC58 = buf->displayList;                                      \
    }

void emitMaterialTexturedDL(u16 id, s32 arg1, s32 flags, u8 *p3, u8 *p4) {
    if ((D_main_bss_8011A444[id].material_type & 1) && !(flags & 8)) {
        DL_ENSURE();
        {
            Gfx *g = D_main_bss_8011DC58++;
            g->words.w0 = 0xE7000000;
            g->words.w1 = 0;
        }
        D_main_bss_8011DC58 = findOrCreateMaterial(D_main_bss_8011DC58, D_main_bss_8011A444[id].D_80128F08_index, flags);
        if (*p3 != D_main_bss_8011A908 || *p4 != D_main_bss_801143A8) {
            D_main_bss_8011DC58 = emitMaterialRenderModeDL(D_main_bss_8011DC58, arg1, flags);
            *p3 = D_main_bss_8011A908;
            *p4 = D_main_bss_801143A8;
        }
    } else {
        DL_ENSURE();
        D_main_bss_801143A8 = 0;
        {
            Gfx *g = D_main_bss_8011DC58++;
            g->words.w0 = 0xE7000000;
            g->words.w1 = 0;
        }
        if (*p3 != D_main_bss_8011A908 || *p4 != 0) {
            DL_ENSURE();
            {
                Gfx *g = D_main_bss_8011DC58++;
                g->words.w0 = 0xB9000002;
                g->words.w1 = 0;
            }
            D_main_bss_8011DC58 = emitMaterialRenderModeDL(D_main_bss_8011DC58, arg1, flags);
            *p3 = D_main_bss_8011A908;
            *p4 = D_main_bss_801143A8;
        }
        DL_ENSURE();
        {
            Gfx *g = D_main_bss_8011DC58++;
            g->words.w0 = 0xFCFFFFFF;
            g->words.w1 = 0xFFFE793C;
        }
        DL_ENSURE();
        {
            Gfx *g = D_main_bss_8011DC58++;
            g->words.w0 = 0xBB000000;
            g->words.w1 = 0;
        }
    }
}

extern u8 D_main_bss_8011A898;
Gfx *emitMaterialRenderModeDLAlt(Gfx *, s32, s32);

void emitMaterialTexturedDLAlt(u16 id, s32 arg1, s32 flags, u8 *p3) {
    flags |= 1;
    if ((D_main_bss_8011A444[id].material_type & 1) && !(flags & 8)) {
        DL_ENSURE();
        {
            Gfx *g = D_main_bss_8011DC58++;
            g->words.w0 = 0xE7000000;
            g->words.w1 = 0;
        }
        D_main_bss_8011DC58 = findOrCreateMaterial(D_main_bss_8011DC58, D_main_bss_8011A444[id].D_80128F08_index, flags);
        if (*p3 != D_main_bss_8011A908) {
            D_main_bss_8011DC58 = emitMaterialRenderModeDLAlt(D_main_bss_8011DC58, arg1, flags);
            *p3 = D_main_bss_8011A908;
        }
    } else {
        if (!(D_main_bss_8011A908 & 0x80)) {
            D_main_bss_8011A908 = 1;
        }
        DL_ENSURE();
        {
            Gfx *g = D_main_bss_8011DC58++;
            g->words.w0 = 0xB9000002;
            g->words.w1 = 0;
        }
        if (*p3 != D_main_bss_8011A908) {
            DL_ENSURE();
            {
                Gfx *g = D_main_bss_8011DC58++;
                g->words.w0 = 0xE7000000;
                g->words.w1 = 0;
            }
            D_main_bss_8011DC58 = emitMaterialRenderModeDLAlt(D_main_bss_8011DC58, arg1, flags);
            *p3 = D_main_bss_8011A908;
        }
        DL_ENSURE();
        {
            if (!(arg1 & 0x10000) && D_main_bss_8011A898) {
                Gfx *g = D_main_bss_8011DC58++;
                g->words.w0 = 0xFCFFFFFF;
                g->words.w1 = 0xFFFE7638;
            } else {
                Gfx *g = D_main_bss_8011DC58++;
                g->words.w0 = 0xFCFFFFFF;
                g->words.w1 = 0xFFFE793C;
            }
        }
        DL_ENSURE();
        {
            Gfx *g = D_main_bss_8011DC58++;
            g->words.w0 = 0xBB000000;
            g->words.w1 = 0;
        }
    }
}

extern u32 D_main_bss_8011A8B8;
extern struct D_main_bss_8011A444 *D_main_bss_8010E8AC;
extern s32 D_main_bss_80114380;
extern u8 D_main_bss_8010F8B0[];
extern s32 D_main_bss_801143A4;
extern u8 D_main_bss_8011A454;

void resetSceneLightsAndMaterials(void) {
    u32 i;
    u32 *count = &D_main_bss_8011A8B8;

    D_main_bss_8011A454 = 1;
    for (i = 0; i < *count; i++) {
        ((u8 *)D_main_bss_8010E8AC)[i] = 0;
    }
    D_main_bss_80114380 = 0;
    for (i = 0; i < 0x400; i++) {
        D_main_bss_8010F8B0[i] = 0;
    }
    D_main_bss_801143A4 = 0;
}

struct TSLEnt {
    /* 0x0 */ void *p0;
    /* 0x4 */ void *p4;
};

struct TSLItem {
    /* 0x0 */ u32 flags;
    /* 0x4 */ u16 h4;
    /* 0x6 */ u16 h6;
    /* 0x8 */ u16 mat;
};

struct TSLGroup {
    /* 0x00 */ struct TSLGroup *next;
    /* 0x04 */ u32 pad4;
    /* 0x08 */ struct TSLItem *items;
    /* 0x0C */ u32 count;
};

struct TSLScene {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ u32 flags;
    /* 0x10 */ u8 **lights;
    /* 0x14 */ u8 pad14[0xC];
    /* 0x20 */ struct TSLGroup *groups;
    /* 0x24 */ u8 *verts;
};

extern s32 D_main_bss_8011437C;
extern u32 D_main_bss_8011A8BC;
extern u32 D_main_bss_8011A8B8;
extern s32 D_main_bss_80114380;
extern u8 D_main_bss_8010F8B0[];
extern s32 D_main_bss_801143A4;
extern u8 D_main_bss_8011A454;
extern struct D_main_bss_8011A444 *D_main_bss_8010E8A8;
extern struct D_main_bss_8011A444 *D_main_bss_8010E8AC;
extern void *D_main_bss_8010E8B0[];
extern struct TSLEnt D_main_bss_801143B0[];

void transformSceneLights(struct TSLScene *scene, f32 *m, f32 *light_mat, s8 *out_a, s8 *out_b) {
    s32 i;
    s32 *p;
    u8 *l;
    u32 n;
    register struct TSLEnt *ent asm("$9");
    struct TSLEnt *e;
    struct TSLGroup *g;
    struct TSLItem *it;
    u32 j;
    s32 idx;
    s32 t;
    s32 q;
    s32 c;
    u16 vi;
    u8 tag;
    void **pp;
    u8 *arr;
    struct D_main_bss_8011A444 *mt;
    struct { f32 x; f32 y; f32 z; f32 pad[4]; } vec;

    idx = 0x1F;
    p = &D_main_bss_8011437C;
    do {
        *p-- = 0;
    } while (--idx >= 0);
    l = scene->lights;
    if (l != NULL) {
        do {
            transformLightByType(l, light_mat);
            l = *(u8 **)l;
        } while (l != NULL);
    }
    D_main_bss_8011A454++;
    if (D_main_bss_8011A454 == 0) {
        D_main_bss_8011A454 = 1;
    }
    n = 0;
    if (D_main_bss_8011A8BC != 0) {
        do {
            ((u8 *)D_main_bss_8010E8AC)[D_main_bss_80114380++] = 0;
            if (D_main_bss_80114380 == D_main_bss_8011A8B8) {
                D_main_bss_80114380 = 0;
            }
            D_main_bss_8010F8B0[D_main_bss_801143A4++] = 0;
            if (D_main_bss_801143A4 == 0x400) {
                D_main_bss_801143A4 = 0;
            }
            n++;
        } while (n < D_main_bss_8011A8BC);
    }
    *out_a = 0;
    *out_b = 0;
    g = scene->groups;
    ent = D_main_bss_801143B0;
    if (g != NULL) {
        do {
            it = g->items;
            j = 0;
            if (g->count != 0) {
                do {
                    if (!(it->flags & 0x100)) {
                        if (it->flags & 2) {
                            *out_b = 1;
                            vi = *(u16 *)((it->h4 & 0xFC) + (s32)it);
                            if (scene->flags & 1) {
                                f32 *v = (f32 *)(vi * 12 + (s32)scene->verts);
                                t = (s32)(m[6] * v[0] + m[7] * v[1] + m[8] * v[2] + m[11]);
                            } else {
                                vec.x = (f32)*(s16 *)(scene->verts + vi * 8) * 0.00390625f;
                                vec.y = (f32)*(s16 *)(scene->verts + vi * 8 + 2) * 0.00390625f;
                                vec.z = (f32)*(s16 *)(scene->verts + vi * 8 + 4) * 0.00390625f;
                                t = (s32)(m[6] * vec.x + m[7] * vec.y + m[8] * vec.z + m[11]);
                            }
                            idx = (s32)((f32)t * 256.0f / 64.0f);
                            if (idx >= 0) {
                                c = 0x1FF;
                                if (idx < 0x200) {
                                    c = idx;
                                }
                            } else {
                                c = 0;
                            }
                            idx = c;
                            if ((it->flags & 0x10) || (it->flags & 0x60) == 0x60) {
                                idx |= 0x200;
                            }
                            tag = D_main_bss_8011A454;
                            e = ent;
                            ent = e + 1;
                            e->p4 = it;
                            if (D_main_bss_8010F8B0[idx] == tag) {
                                e->p0 = D_main_bss_8010E8B0[idx];
                            } else {
                                e->p0 = NULL;
                                D_main_bss_8010F8B0[idx] = tag;
                            }
                            D_main_bss_8010E8B0[idx] = e;
                        } else {
                            *out_a = 1;
                            idx = it->mat;
                            if ((D_main_bss_8011A444[idx].material_type & 1) && (it->flags & 4)) {
                                idx = (D_main_bss_8011A444[idx].D_80128F08_index + 1) * 2;
                            } else {
                                idx = 0;
                            }
                            if ((it->flags & 0x10) || (it->flags & 0x60) == 0x60) {
                                idx |= 1;
                            }
                            e = ent;
                            ent = e + 1;
                            pp = (void **)&e->p4;
                            *pp = it;
                            arr = (u8 *)D_main_bss_8010E8AC;
                            tag = D_main_bss_8011A454;
                            if (arr[idx] == tag) {
                                ((void **)e)[0] = ((void **)D_main_bss_8010E8A8)[idx];
                            } else {
                                ((void **)e)[0] = NULL;
                                ((u8 *)D_main_bss_8010E8AC)[idx] = tag;
                            }
                            ((void **)D_main_bss_8010E8A8)[idx] = e;
                        }
                    }
                    j++;
                    it = (struct TSLItem *)((u8 *)it + (*(u8 *)&it->h4 & 0x3F) * 4);
                } while (j < g->count);
            }
            g = g->next;
        } while (g != NULL);
    }
}

typedef struct {
    u16 idx;
    u16 stamp;
} VtxCacheSlot;

extern u8 D_main_801132C0[];
extern VtxCacheSlot D_main_bss_80113240[];
extern u16 D_main_bss_801142C0;

u8 bindFaceVerticesToCache(u32 *face, u8 *mask, u8 base) {
    u8 buf[8];
    u8 n;
    u8 found;
    u8 i;
    u8 j;
    u8 slot;
    u16 vi;
    u16 *vt;
    u8 bit;
    u16 ret;
    s32 cnt;
    u8 *bp;

    n = (face[0] & 8) ? 4 : 3;
    vt = (u16 *)((u8 *)face + (*(u16 *)((u8 *)face + 4) & 0xFC));
    bp = buf;
    found = 0;
    for (j = 0; j < n; j++) {
        vi = vt[j];
        slot = D_main_801132C0[vi];
        if (D_main_bss_80113240[slot].stamp == D_main_bss_801142C0 && D_main_bss_80113240[slot].idx == vi) {
            bp[j] = slot;
        } else {
            bp[j] = 0xFF;
            found++;
        }
    }
    cnt = found;
    ret = cnt;
    if (cnt == 0) {
        return 0;
    }
    if (base + cnt >= 0x21) {
        D_main_bss_801142C0++;
        if (D_main_bss_801142C0 == 0) {
            D_main_bss_801142C0 = 1;
        }
        for (i = 0; i < n; i++) {
            D_main_801132C0[vt[i]] = i;
            D_main_bss_80113240[i].idx = vt[i];
            D_main_bss_80113240[i].stamp = D_main_bss_801142C0;
        }
        *mask = 0xF;
        return n;
    }
    *mask = 0;
    i = 0;
    bit = 1;
    for (; i < n; i++) {
        if (buf[i] == 0xFF) {
            D_main_801132C0[vt[i]] = base;
            D_main_bss_80113240[base].idx = vt[i];
            D_main_bss_80113240[base++].stamp = D_main_bss_801142C0;
            *mask |= bit;
        }
        bit <<= 1;
    }
    return ret;
}

typedef struct LFNode {
    struct LFNode *link;
    struct LFNode *next;
    u32 *face[64];
} LFNode;

typedef struct {
    u8 p0[0xC];
    u32 flags;
    u8 *lights;
    u8 p14[0x2C - 0x14];
    u32 unk2C;
    s32 unk30;
    u8 p34[0x44 - 0x34];
    struct DisplayListBuffer *list44[2];
    struct DisplayListBuffer *list4C[2];
    LFNode *faces;
} LitMesh;

extern u16 D_main_bss_801142C0;
extern s32 D_main_bss_80114300[];
extern s32 D_main_bss_8011A894;
extern u8 D_main_bss_8011A899;
extern struct DisplayListBuffer *D_main_bss_8011A458[];
extern struct DisplayListBuffer *D_main_bss_8011A4B0[];
s32 bfvcS(u32 *, u8 *, s32) __asm__("bindFaceVerticesToCache");
void rltEmit(u32 *, void *, void *, void *, void *, s32, void *, s32, u8) __asm__("emitTexturedFaceGeometry");

static __inline__ Gfx *rltAllocA(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    if (*D_main_bss_8011A4C4 != NULL) {
        (*D_main_bss_8011A4C4)->prev = chunk;
    }
    chunk->next = *D_main_bss_8011A4C4;
    *D_main_bss_8011A4C4 = chunk;
    return chunk->displayList;
}

static __inline__ Gfx *rltAllocB(void) {
    struct DisplayListBuffer *chunk;
    struct DisplayListBuffer *tail;

    chunk = D_main_bss_801163B0;
    if (chunk == NULL) {
        chunk = findAndUnlinkSmallestEntry();
        if (chunk != NULL) {
            tail = chunk;
            while (tail->next != NULL) {
                tail = tail->next;
            }
            tail->next = D_main_bss_801163B0;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = tail;
            }
            D_main_bss_801163B0 = chunk;
            chunk->prev = NULL;
        }
        chunk = D_main_bss_801163B0;
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    if (*D_main_bss_8011A4AC != NULL) {
        (*D_main_bss_8011A4AC)->prev = chunk;
    }
    chunk->next = *D_main_bss_8011A4AC;
    *D_main_bss_8011A4AC = chunk;
    return chunk->displayList;
}

#define LIT_BUMP() \
    D_main_bss_801142C0++; \
    if (D_main_bss_801142C0 == 0) { \
        D_main_bss_801142C0 = 1; \
    }

s32 renderLitTexturedMeshFaces(s32 arg0, f32 *arg1, LitMesh *arg2, s32 arg3) {
    u8 sp28;
    LFNode *faceList;
    struct DisplayListBuffer *s2;
    struct DisplayListBuffer *s4;
    struct DisplayListBuffer *tmp;
    Gfx *sp44;
    Gfx *sp4C;
    s32 s1;
    s32 s3;
    s32 s5;
    s32 fp;
    u32 s7;
    u32 sign;
    u32 v;
    u8 *l;
    u8 hasA;
    u8 hasB;
    register u32 **s0 asm("$16");
    u32 *f;
    u32 w;

    arg2->unk30 = D_main_bss_8011A894;
    s7 = 0;
    do {
        D_main_bss_80114300[s7] = 0;
        s7++;
    } while (s7 < 0x20);
    l = arg2->lights;
    while (l != NULL) {
        transformLightByType(l, arg1);
        l = *(u8 **)l;
    }
    v = arg2->unk2C;
    sign = v >> 31;
    faceList = arg2->faces;
    v ^= 0x80000000;
    arg2->unk2C = v;
    if (faceList != NULL) {
    while (faceList->link != NULL) {
        faceList = faceList->link;
    }
    tmp = arg2->list44[sign];
    if (tmp != NULL) {
        if (arg2->flags & 0x40) {
            s4 = tmp;
            while (s4->next != NULL) {
                s4 = s4->next;
            }
        }
        if (arg2->flags & 0x20) {
            s2 = arg2->list4C[sign];
            while (s2->next != NULL) {
                s2 = s2->next;
            }
        }
        s3 = 0;
        s1 = 0;
        hasA = (arg2->flags >> 8) & 1;
        hasB = (arg2->flags >> 7) & 1;
        while (faceList != NULL) {
            s0 = &faceList->face[0];
            for (s7 = 0; s7 < 0x40; s7++) {
                f = *s0;
                if (f == NULL) {
                    break;
                }
                if (f != (u32 *)-1) {
                    if (arg2->flags & 0x20) {
                        w = *f;
                        if (w & 0x30) {
                            s5 = 3;
                            if (w & 8) {
                                s5 = 4;
                            }
                        } else {
                            s5 = 1;
                        }
                    }
                    if (arg2->flags & 0x40) {
                        fp = bfvcS(*s0, &sp28, s1 & 0xFF);
                    }
                    if ((arg2->flags & 0x20) && ((s3 & 0xFFFF) + (s5 & 0xFFFF)) >= 0x41) {
                        s3 = 0;
                        s2 = s2->prev;
                    }
                    if ((arg2->flags & 0x40) && ((s1 & 0xFFFF) + (fp & 0xFF)) >= 0x21) {
                        s1 = 0;
                        s4 = s4->prev;
                    }
                    if ((hasA && (**s0 & 0x200)) || (hasB && (**s0 & 0x400)) || hasA == hasB) {
                        rltEmit(*s0, &s2->displayList[0].words.w0 + (s3 & 0xFFFF), NULL, &s4->displayList[s1 & 0xFFFF], NULL, arg3, arg2, sp28, fp);
                    }
                    s3 += s5;
                    s1 += fp & 0xFF;
                } else {
                    if (arg2->flags & 0x20) {
                        s3 = 0;
                        s2 = s2->prev;
                    }
                    if (arg2->flags & 0x40) {
                        s4 = s4->prev;
                        LIT_BUMP();
                        s1 = 0;
                    }
                }
                s0++;
            }
            faceList = faceList->next;
        }
        return 1;
    }
    D_main_bss_8011A4C4 = &arg2->list44[sign];
    D_main_bss_8011A4AC = &arg2->list4C[sign];
    sp4C = rltAllocA();
    sp44 = rltAllocB();
    s4 = arg2->list44[sign ^ 1];
    while (s4->next != NULL) {
        s4 = s4->next;
    }
    s2 = arg2->list4C[sign ^ 1];
    while (s2->next != NULL) {
        s2 = s2->next;
    }
    s3 = 0;
    s1 = 0;
    while (faceList != NULL) {
        s0 = &faceList->face[0];
        for (s7 = 0; s7 < 0x40; s7++) {
            f = *s0;
            if (f == NULL) {
                break;
            }
            if (f != (u32 *)-1) {
                w = *f;
                if (w & 0x30) {
                    s5 = 3;
                    if (w & 8) {
                        s5 = 4;
                    }
                } else {
                    s5 = 1;
                }
                fp = bfvcS(*s0, &sp28, s1 & 0xFF);
                if (((s3 & 0xFFFF) + (s5 & 0xFFFF)) >= 0x41) {
                    s3 = 0;
                    sp44 = rltAllocB();
                    s2 = s2->prev;
                }
                if (((s1 & 0xFFFF) + (fp & 0xFF)) >= 0x21) {
                    s1 = 0;
                    sp4C = rltAllocA();
                    s4 = s4->prev;
                }
                rltEmit(*s0, &sp44->words.w0 + (s3 & 0xFFFF), &s2->displayList[0].words.w0 + (s3 & 0xFFFF), &sp4C[s1 & 0xFFFF], &s4->displayList[s1 & 0xFFFF], arg3, arg2, sp28, fp);
                s3 += s5;
                s1 += fp & 0xFF;
            } else {
                s3 = 0;
                sp44 = rltAllocB();
                s2 = s2->prev;
                s1 = 0;
                sp4C = rltAllocA();
                s4 = s4->prev;
                LIT_BUMP();
            }
            s0++;
        }
        faceList = faceList->next;
    }
    LIT_BUMP();
    D_main_bss_8011A4C4 = &D_main_bss_8011A4B0[D_main_bss_8011A899];
    D_main_bss_8011A4AC = &D_main_bss_8011A458[D_main_bss_8011A899];
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/08510", submitSceneNodeRender);

INCLUDE_ASM("asm/nonmatchings/main/08510", renderFlatMeshFaceGroup);

INCLUDE_ASM("asm/nonmatchings/main/08510", renderUnlitMeshFaces);

struct RvItem {
    /* 0x00 */ struct RvItem *next;
    /* 0x04 */ u32 pad4;
    /* 0x08 */ s16 x, y, z;
    /* 0x0E */ u16 padE;
    /* 0x10 */ u16 flags;
    /* 0x12 */ u16 mat;
};
struct RvScene {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ struct RvItem *items;
};

void resetVertexCacheSlot(struct RvScene *scene, f32 *m, s8 *a2, s8 *a3, s8 *a4, s8 *a5, u16 *lo, u16 *hi) {
    u32 n;
    register struct TSLEnt *ent asm("$10");
    struct TSLEnt *e;
    struct RvItem *it;
    s32 idx;
    s32 t;
    s32 c;
    u8 tag;
    void **pp;
    u8 *arr;
    struct { f32 x; f32 y; f32 z; f32 pad[3]; } vec;

    D_main_bss_8011A454++;
    if (D_main_bss_8011A454 == 0) {
        D_main_bss_8011A454 = 1;
    }
    n = 0;
    if (D_main_bss_8011A8BC != 0) {
        do {
            ((u8 *)D_main_bss_8010E8AC)[D_main_bss_80114380++] = 0;
            if (D_main_bss_80114380 == D_main_bss_8011A8B8) {
                D_main_bss_80114380 = 0;
            }
            D_main_bss_8010F8B0[D_main_bss_801143A4++] = 0;
            if (D_main_bss_801143A4 == 0x400) {
                D_main_bss_801143A4 = 0;
            }
            n++;
        } while (n < D_main_bss_8011A8BC);
    }
    *a2 = 0;
    *a3 = 0;
    *a4 = 0;
    *a5 = 0;
    *lo = 0xFFFF;
    *hi = 0;
    it = scene->items;
    ent = D_main_bss_801143B0;
    if (it != NULL) {
        do {
            if (it->flags & 0x100) {
                if ((it->flags & 3) != 0) {
                    *a5 = 1;
                } else {
                    *a4 = 1;
                }
                vec.x = (f32)it->x * 0.00390625f;
                vec.y = (f32)it->y * 0.00390625f;
                vec.z = (f32)it->z * 0.00390625f;
                t = (s32)(m[6] * vec.x + m[7] * vec.y + m[8] * vec.z + m[11]);
                idx = (s32)((f32)t * 256.0f / 64.0f);
                if (idx >= 0) {
                    c = 0x1FF;
                    if (idx < 0x200) {
                        c = idx;
                    }
                } else {
                    c = 0;
                }
                idx = c;
                if (idx < *lo) {
                    *lo = idx;
                }
                if (*hi < idx) {
                    *hi = idx;
                }
                tag = D_main_bss_8011A454;
                e = ent;
                ent = e + 1;
                e->p4 = it;
                if (D_main_bss_8010F8B0[idx] == tag) {
                    e->p0 = D_main_bss_8010E8B0[idx];
                } else {
                    e->p0 = NULL;
                    D_main_bss_8010F8B0[idx] = tag;
                }
                D_main_bss_8010E8B0[idx] = e;
            } else {
                if ((it->flags & 3) != 0) {
                    *a3 = 1;
                } else {
                    *a2 = 1;
                }
                idx = it->mat;
                if (D_main_bss_8011A444[idx].material_type & 1) {
                    idx = (D_main_bss_8011A444[idx].D_80128F08_index + 1) * 2;
                } else {
                    idx = 0;
                }
                e = ent;
                ent = e + 1;
                pp = (void **)&e->p4;
                *pp = it;
                arr = (u8 *)D_main_bss_8010E8AC;
                tag = D_main_bss_8011A454;
                if (arr[idx] == tag) {
                    ((void **)e)[0] = ((void **)D_main_bss_8010E8A8)[idx];
                } else {
                    ((void **)e)[0] = NULL;
                    ((u8 *)D_main_bss_8010E8AC)[idx] = tag;
                }
                ((void **)D_main_bss_8010E8A8)[idx] = e;
            }
            it = it->next;
        } while (it != NULL);
    }
}

INCLUDE_ASM("asm/nonmatchings/main/08510", buildOrientedFaceGeometry);

INCLUDE_ASM("asm/nonmatchings/main/08510", renderLitMeshFaceGroup);

extern f32 D_main_bss_801163C0;
extern f32 D_main_bss_8011A7D4;
extern f32 D_main_bss_8011A8CC;
extern f32 D_main_bss_8011D088;
extern void clearVec4QuadStruct(f32 *);
extern void mat3x3InverseInto(f32 *, void *);
extern void mat3x4Multiply(f32 *, void *, f32 *);
extern void submitSceneNodeRender(f32 *, f32 *, void *, void *, s32);

s32 processMeshdef1ForLod(u8 *arg0, u8 *arg1, u8 *arg2) {
    f32 sp18[12];
    f32 sp48[12];
    f32 t;
    f32 v;
    u32 flags;
    u8 *l;

    if (*(u32 *)(arg0 + 0xC) & 0x80000) {
        t = *(f32 *)(arg0 + 0x1C);
        if (t <= D_main_bss_8011A8CC) {
            t = D_main_bss_8011A8CC * 256.0f;
        } else {
            t = t * 256.0f;
        }
        v = (((D_main_bss_8011A7D4 * t + D_main_bss_801163C0) / t) * 511.0f + 511.0f) * 32.0f;
        D_main_bss_8011D088 = (f32)(u16)(u32)v;
    }
    flags = *(u32 *)(arg0 + 0xC);
    if (flags & 0xC0000000) {
        return 0;
    }
    *(u32 *)(arg0 + 0xC) = (flags | 8) & ~0x10;
    if (arg1 == 0) {
        clearVec4QuadStruct(sp18);
        submitSceneNodeRender(sp18, 0, arg0, 0, 0);
    } else {
        mat3x3InverseInto(sp48, arg1);
        mat3x3InverseInto(sp18, arg2 + 0x2C);
        mat3x4Multiply(sp18, arg1, sp18);
        l = *(u8 **)(arg2 + 4);
        if (l != 0) {
            do {
                transformLightByType(l, sp48);
                l = *(u8 **)l;
            } while (l != 0);
        }
        submitSceneNodeRender(sp18, sp48, arg0, arg2, 0);
    }
    return 1;
}

typedef struct {
    s32 a;
    s32 b;
    u8 *c;
} PsnDlEntry;

typedef struct PsnSortEntry {
    struct PsnSortEntry *next;
    s32 dl;
    s32 mtx;
    u8 *node;
    u8 flag;
} PsnSortEntry;

extern s32 D_main_bss_8011A894;
extern u8 *D_main_bss_8010E090[];
extern PsnDlEntry D_main_bss_80116400[];
extern PsnSortEntry D_main_bss_80117C08[];
s32 renderUnlitMeshFaces(f32 *, f32 *, u8 *);
s32 renderLitTexturedMeshFacesCall(f32 *, f32 *, u8 *) __asm__("renderLitTexturedMeshFaces");
s32 renderFlatMeshFaceGroup(f32 *, f32 *, u8 *);
s32 renderLitMeshFaceGroup(f32 *, f32 *, u8 *);
s32 submitSceneNodeRenderR(f32 *, f32 *, void *, void *, s32) __asm__("submitSceneNodeRender");

static __inline__ void psnLod(u8 *n) {
    f32 t;
    f32 v;

    t = *(f32 *)(n + 0x1C);
    if (t <= D_main_bss_8011A8CC) {
        t = D_main_bss_8011A8CC * 256.0f;
    } else {
        t = t * 256.0f;
    }
    v = (((D_main_bss_8011A7D4 * t + D_main_bss_801163C0) / t) * 511.0f + 511.0f) * 32.0f;
    D_main_bss_8011D088 = (f32)(u16)(u32)v;
}

static __inline__ void psnComputeLod(u8 *n) {
    f32 t;
    f32 v;

    if (*(u32 *)(n + 0xC) & 0x80000) {
        t = *(f32 *)(n + 0x1C);
        if (t <= D_main_bss_8011A8CC) {
            t = D_main_bss_8011A8CC * 256.0f;
        } else {
            t = t * 256.0f;
        }
        v = (((D_main_bss_8011A7D4 * t + D_main_bss_801163C0) / t) * 511.0f + 511.0f) * 32.0f;
        D_main_bss_8011D088 = (f32)(u16)(u32)v;
    }
}

static __inline__ void psnAddDl(s32 a, u8 *node) {
    s32 i = D_main_bss_80128C6C;

    D_main_bss_80116400[i].a = a;
    D_main_bss_80116400[i].b = D_main_bss_8011DC5C;
    D_main_bss_80128C6C = i + 1;
    D_main_bss_80116400[i].c = node;
}

static __inline__ void psnAddSort(u8 *m, u8 *node, s32 c) {
    s32 i;
    s32 *slot;
    s32 dl;

    i = D_main_bss_801143A0;
    D_main_bss_80117C08[i].next = (PsnSortEntry *)D_main_bss_8011D498[D_main_bss_80117C00].a[c];
    D_main_bss_8011D498[D_main_bss_80117C00].a[c] = (s32)&D_main_bss_80117C08[i];
    dl = *(s32 *)(m + 0x38);
    D_main_bss_80117C08[i].mtx = D_main_bss_8011DC5C;
    D_main_bss_80117C08[i].node = node;
    D_main_bss_80117C08[i].dl = dl;
    dl = *(s32 *)(m + 0x34) == 0;
    D_main_bss_801143A0 = i + 1;
    D_main_bss_80117C08[i].flag = dl;
}

static __inline__ void psnQueue(f32 *mtx, u8 *m, u8 *node) {
    s32 a;
    s32 c;
    s32 i;
    s32 lod;
    s32 *slot;

    if (*(s32 *)(m + 0x34) != 0) {
        psnAddDl(*(s32 *)(m + 0x34), node);
    }
    if (*(s32 *)(m + 0x38) == 0) {
        return;
    }
    lod = (s32)(mtx[0x2C / 4] * 256.0f) / 512;
    if (lod >= 0) {
        c = 0x3F;
        if (lod < 0x40) {
            c = lod;
        }
    } else {
        c = 0;
    }
    psnAddSort(m, node, c);
}

s32 processSceneNode(f32 *arg0, f32 *arg1, u8 *arg2, u8 *arg3) {
    u8 *s0;
    s32 ret;
    s32 flags;
    s32 r;
    s32 lod;
    s32 *slot;
    s32 i;
    s32 a;
    s32 c;
    u16 idx;

    flags = *(s32 *)(arg2 + 0xC);
    ret = 1;
    if (flags & 4) {
        s0 = *(u8 **)(arg2 + 8);
        if (D_main_bss_8011A894 == *(s32 *)(s0 + 0x30)) {
        queue:
            psnQueue(arg0, s0, arg2);
            return ret;
        }
        idx = D_main_bss_8010DFD4;
        D_main_bss_8010E090[idx] = s0;
        flags = *(s32 *)(s0 + 0xC);
        D_main_bss_8010DFD4 = idx + 1;
        if (flags & 0x10) {
            if (flags & 0x260) {
                *(u32 *)(s0 + 0x2C) &= ~0x40000000;
                if (*(u32 *)(s0 + 0xC) & 0xC0000000) {
                    if (*(s32 *)(arg2 + 0xC) >= 0) {
                        goto set;
                    }
                    r = renderUnlitMeshFaces(arg0, arg1, arg2) & 0xFF;
                } else {
                    r = renderLitTexturedMeshFacesCall(arg0, arg1, s0) & 0xFF;
                }
                if (r == 0) {
                    return 0;
                }
            set:
                *(u32 *)(s0 + 0x2C) |= 0x20000000;
            }
            goto queue;
        }
        if (flags & 0x80000) {
            psnLod(s0);
        }
        flags = *(s32 *)(s0 + 0xC);
        if (flags < 0) {
            ret = renderFlatMeshFaceGroup(arg0, arg1, s0);
        } else if (flags & 0x40000000) {
            ret = renderLitMeshFaceGroup(arg0, arg1, s0);
        } else {
            ret = submitSceneNodeRenderR(arg0, arg1, s0, arg3, 1);
        }
        if (ret & 0xFF) {
            *(u32 *)(s0 + 0x2C) |= 0x20000000;
        }
        return ret & 0xFF;
    }
    if (!(flags & 8)) {
        goto p3;
    }
    if (flags & 0x10) {
        if (flags & 0x260) {
            u32 v = *(u32 *)(arg2 + 0x2C);
            if (v & 0x20000000) {
                *(u32 *)(arg2 + 0x2C) = v & ~0x20000000;
                return 1;
            }
            *(u32 *)(arg2 + 0x2C) = v & ~0x40000000;
            if (*(u32 *)(arg2 + 0xC) & 0xC0000000) {
                s0 = arg2;
                if (*(s32 *)(arg2 + 0xC) >= 0) {
                    goto queue;
                }
                r = renderUnlitMeshFaces(arg0, arg1, arg2) & 0xFF;
            } else {
                r = renderLitTexturedMeshFacesCall(arg0, arg1, arg2) & 0xFF;
            }
            s0 = arg2;
            if (r != 0) {
                goto queue;
            }
            return 0;
        }
        s0 = arg2;
        goto queue;
    }
p3:
    {
        u32 v = *(u32 *)(arg2 + 0x2C);
        if (v & 0x20000000) {
            *(u32 *)(arg2 + 0x2C) = v & ~0x20000000;
            if (D_main_bss_8011A894 == *(s32 *)(arg2 + 0x30)) {
                s0 = *(u8 **)(arg2 + 8);
                goto queue;
            }
        }
    }
    psnComputeLod(arg2);
    flags = *(s32 *)(arg2 + 0xC);
    if (flags < 0) {
        r = renderFlatMeshFaceGroup(arg0, arg1, arg2) & 0xFF;
    } else if (flags & 0x40000000) {
        r = renderLitMeshFaceGroup(arg0, arg1, arg2) & 0xFF;
    } else {
        r = submitSceneNodeRenderR(arg0, arg1, arg2, arg3, 1) & 0xFF;
    }
    return r;
}

extern f32 D_main_bss_80112AF0[12];
extern u8 *D_main_bss_80112B20;
extern u8 *D_main_bss_80112B24;
extern s32 D_main_bss_8011DC5C;
extern void mat3x4Multiply(f32 *, void *, f32 *);
extern void mat3x3InverseInto(f32 *, void *);
extern void convertMat3x4ToN64Mtx(s32, f32 *);
extern s32 processSceneNode(f32 *, f32 *, u8 *, u8 *);

s32 traverseSceneGraphRecursive(u8 *arg0, f32 *arg1, f32 *arg2, u8 *arg3) {
    f32 sp10[12];
    f32 sp40[12];
    s32 s1 = 1;
    u8 *v1;
    u8 *c0;
    u8 *s0;

    do {
        s0 = arg0 + 0x1C;
        mat3x4Multiply(arg1, s0, sp10);
        if (arg2 != 0) {
            mat3x3InverseInto(D_main_bss_80112AF0, s0);
            mat3x4Multiply(D_main_bss_80112AF0, arg2, sp40);
        } else {
            mat3x3InverseInto(sp40, s0);
        }
        if (*(u8 **)(arg0 + 0x10) != 0) {
            convertMat3x4ToN64Mtx(D_main_bss_8011DC5C, sp10);
            D_main_bss_80112B24 = *(u8 **)(arg3 + 4);
            if (D_main_bss_80112B24 != 0) {
                do {
                    transformLightByType(D_main_bss_80112B24, sp40);
                    D_main_bss_80112B24 = *(u8 **)D_main_bss_80112B24;
                } while (D_main_bss_80112B24 != 0);
            }
            v1 = *(u8 **)(arg0 + 0x10);
            while (((D_main_bss_80112B20 = v1) != 0) & ((s1 & 0xFF) != 0)) {
                s1 = processSceneNode(sp10, sp40, D_main_bss_80112B20, arg3);
                v1 = *(u8 **)D_main_bss_80112B20;
            }
            D_main_bss_8011DC5C += 0x40;
        }
        c0 = *(u8 **)(arg0 + 0xC);
        if ((c0 != 0) & ((s1 & 0xFF) != 0)) {
            s1 = traverseSceneGraphRecursive(c0, sp10, sp40, arg3);
        }
        arg0 = *(u8 **)arg0;
    } while ((arg0 != 0) & ((s1 & 0xFF) != 0));
    return s1 & 0xFF;
}

extern u32 dtgW __asm__("D_main_bss_8011A838");
extern u32 dtgH __asm__("D_main_bss_8011A83C");
void drawTextGlyphRect(s32 tex, s16 x0, s16 y0, s16 x1, s16 y1, u16 dsdx, u16 dtdy) {
    u32 s;
    u32 t;

    if ((y1 < 0) | (x1 < 0)) {
        return;
    }
    if (y0 < (s16)(D_main_bss_8011A83C * 4) && x0 < (s16)(D_main_bss_8011A838 * 4)) {
        if (y0 < 0) {
            t = (u32)-y0 >> 1;
            y0 = 0;
        } else {
            t = 0;
        }
        if (x0 < 0) {
            s = (u32)-x0 >> 1;
            x0 = 0;
        } else {
            s = 0;
        }
        if (y1 > dtgH * 4) {
            y1 = dtgH * 4;
        }
        if (x1 > dtgW * 4) {
            x1 = dtgW * 4;
        }
        if (D_main_bss_8011DC58 + 1 >= D_main_bss_801163D4) {
            struct DisplayListBuffer *chunk;
            struct DisplayListBuffer *tail;
            struct DisplayListBuffer *buf;
            D_main_bss_8011DC58->words.w0 = 0xB5000000;
            D_main_bss_8011DC58->words.w1 = 0;
            chunk = D_main_bss_801163B0;
            if (chunk == NULL) {
                chunk = findAndUnlinkSmallestEntry();
                if (chunk != NULL) {
                    tail = chunk;
                    while (tail->next != NULL) {
                        tail = tail->next;
                    }
                    tail->next = D_main_bss_801163B0;
                    if (D_main_bss_801163B0 != NULL) {
                        D_main_bss_801163B0->prev = tail;
                    }
                    D_main_bss_801163B0 = chunk;
                    chunk->prev = NULL;
                }
                chunk = D_main_bss_801163B0;
            }
            D_main_bss_801163B0 = D_main_bss_801163B0->next;
            if (D_main_bss_801163B0 != NULL) {
                D_main_bss_801163B0->prev = NULL;
            }
            buf = chunk;
            if (*D_main_bss_801163FC == NULL) {
                *D_main_bss_801163FC = buf;
            } else {
                (*D_main_bss_8011A7DC)->next = buf;
                buf->prev = *D_main_bss_8011A7DC;
            }
            buf->next = NULL;
            *D_main_bss_8011A7DC = buf;
            D_main_bss_801163D4 = &buf->displayList[0x1F];
            D_main_bss_8011DC58 = buf->displayList;
        }
        {
            Gfx *g = D_main_bss_8011DC58;
            g[0].words.w0 = 0xE4000000 | ((x1 & 0xFFF) << 12) | (y1 & 0xFFF);
            g[0].words.w1 = ((x0 & 0xFFF) << 12) | (y0 & 0xFFF);
            g[1].words.w0 = (s << 21) | ((t << 5) & 0xFFE0);
            g[1].words.w1 = (dsdx << 16) | dtdy;
            D_main_bss_8011DC58 = g + 2;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/08510", drawSubtitleText);

INCLUDE_ASM("asm/nonmatchings/main/08510", setupCameraMatrices);

extern s8 D_main_bss_8011A86C;
extern s8 D_main_bss_8011A86D;
extern s8 D_main_bss_8011A86E;

s32 setFrameLevelStateBytes(s8 arg0, s8 arg1, s8 arg2) {
    D_main_bss_8011A86C = arg0;
    D_main_bss_8011A86D = arg1;
    D_main_bss_8011A86E = arg2;
    return 1;
}

extern s8 D_main_bss_8011A870;

s32 setRenderStateFlagByteOne(s8 arg0) {
    D_main_bss_8011A870 = arg0;
    return 1;
}

extern s8 D_main_bss_8011A871;

s32 setRenderStateFlagByteTwo(s8 arg0) {
    D_main_bss_8011A871 = arg0;
    return 1;
}

extern s8 D_main_bss_8011A872;

s32 setRenderStateFlagByteThree(s8 arg0) {
    D_main_bss_8011A872 = arg0;
    return 1;
}

extern s8 D_main_bss_8011A875;
extern s8 D_main_bss_8011A874;
extern s8 D_main_bss_8011A873;
extern f32 D_main_bss_8011A878;
extern f32 D_main_bss_8011A87C;

s32 setViewStateBytesAndFadeScale(s8 arg0, s8 arg1, s8 arg2, f32 arg3, f32 arg4) {
    D_main_bss_8011A873 = arg0;
    D_main_bss_8011A874 = arg1;
    D_main_bss_8011A875 = arg2;
    D_main_bss_8011A878 = arg3;
    D_main_bss_8011A87C = (32.0f / arg4) + arg3;
    return 1;
}

extern s8 D_main_bss_8011A873;
extern s8 D_main_bss_8011A874;
extern s8 D_main_bss_8011A875;

s32 setViewStateTripletBytes(s8 arg0, s8 arg1, s8 arg2) {
    D_main_bss_8011A873 = arg0;
    D_main_bss_8011A874 = arg1;
    D_main_bss_8011A875 = arg2;
    return 1;
}



s32 setMissionLevelInitByte(s8 arg0) {
    D_main_bss_8011A898 = arg0;
    return 1;
}

s32 resetMaterialPoolWrapper(void) {
    resetMaterialPool();
    return 1;
}

extern f32 D_main_bss_8011A840;

void setRenderViewScaleFloat(f32 arg0) {
    D_main_bss_8011A840 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/main/08510", buildAndRegisterDefaultMaterial);

extern void clearPendingViChanges(void);
extern void clearPostSwapPendingFlags(void);
extern void initVideoSubsystem(s16, s16, u16, u16, s16, s32, s32, s32, s32, s32, s32, s32, s32, s32 *, u8, s32);
extern u8 buildAndRegisterDefaultMaterial(s16, s16, s16, s16, s16, s32 *, s32, s32, u32, s32 *, s32, u32, s32, u32, u32, u8, u16, u16);
void swapBufferWithViMode(void);
u8 buildMaterialFreeList(void);
extern void loadDebugAssets(s32);
extern s32 D_main_bss_8010E008;

static __inline__ void avScanWait(void) {
    u32 i;
    volatile u8 *pending = &D_main_bss_8011A89E;
    s32 stateA;
    s32 stateB;

    if (*pending != 0) {
        osRecvMesg(D_main_bss_8011A818, NULL, 1);
        *pending = 0;
        osYieldThread();
    }
    bufferArbiterMarkSlotReady();
    if (D_main_bss_8011A89D != 0) {
        osRecvMesg(D_main_8011A7E8, NULL, 1);
        D_main_bss_8011A89D = 0;
        osYieldThread();
    }
    D_main_bss_8011A89A = 0;
    bufferArbiterProducerMark();
    stateA = 3;
    stateB = 4;
    do {
        i = 0;
        waitOnVideoQueue();
        awaitFrameSyncMesgBlock();
        for (i = 0; i < D_main_bss_80128EAD; i++) {
            if (D_main_bss_80128EAA[i] == stateA || D_main_bss_80128EAA[i] == stateB) {
                break;
            }
        }
        signalFrameSyncMesgNonblock();
    } while (i != D_main_bss_80128EAD);
}

u8 advanceVideoFrame(s16 w, s16 h, u16 a, u16 b, s16 bpp, s32 *fb, s32 z, s32 e8, u32 p8, s32 *p9, s32 p10, u32 p11, s32 p12, u32 p13, u32 flags, u8 p15, u16 p16, u16 p17) {
    avScanWait();
    swapBufferWithViMode();
    waitOnVideoQueue();
    clearPendingViChanges();
    clearPostSwapPendingFlags();
    initVideoSubsystem(w, h, a, b, bpp, (flags >> 2) & 1, (flags >> 3) & 1, (flags >> 4) & 1, (flags >> 5) & 1, (flags >> 6) & 1, (flags >> 7) & 1, (flags >> 8) & 1, bpp >= 0x18, fb, p15, 1);
    if (buildAndRegisterDefaultMaterial(w, h, a, b, bpp, fb, z, e8, p8, p9, p10, p11, p12, p13, flags, p15, p16, p17) == 0) {
        return 0;
    }
    if (buildMaterialFreeList() == 0) {
        return 0;
    }
    loadDebugAssets(D_main_bss_8010E008);
    return 1;
}

extern void clearPendingViChanges(void);
extern void clearPostSwapPendingFlags(void);
extern void initVideoSubsystem(s16, s16, u16, u16, s16, s32, s32, s32, s32, s32, s32, s32, s32, s32 *, u8, s32);
extern u8 buildAndRegisterDefaultMaterial(s16, s16, s16, s16, s16, s32 *, s32, s32, u32, s32 *, s32, u32, s32, u32, u32, u8, u16, u16);
extern s32 createMaterialPool(void);
extern void *rs_malloc(u32, u16);
extern SgTask gspTaskI __asm__("gspTask");

s32 initVideoBootWrapper(s16 w, s16 h, u16 a, u16 b, s16 bpp, s32 *fb, s32 z, s32 e8, u32 p8, s32 *p9, s32 p10, u32 p11, s32 p12, u32 p13, u32 flags, u8 p15, u16 p16, u16 p17) {
    s32 r;
    clearPendingViChanges();
    clearPostSwapPendingFlags();
    initVideoSubsystem(w, h, a, b, bpp, (flags >> 2) & 1, (flags >> 3) & 1, (flags >> 4) & 1, (flags >> 5) & 1, (flags >> 6) & 1, (flags >> 7) & 1, (flags >> 8) & 1, bpp >= 0x18, fb, p15, 0);
    if (buildAndRegisterDefaultMaterial(w, h, a, b, bpp, fb, z, e8, p8, p9, p10, p11, p12, p13, flags, p15, p16, p17) != 0) {
        createMaterialPool();
        gspTaskI.yield_data_ptr = (u32)rs_malloc(0x1000, 0x80);
        gspTaskI.yield_data_size = 0xC00;
        return 1;
    }
    return 0;
}

s32 destroyTextureLUTs();
s32 rs_free(struct D_main_bss_8011A444 *);
s32 selectAndApplyViMode();
extern struct D_main_bss_8011A444 *D_main_bss_8010E8A8;
extern struct D_main_bss_8011A444 *D_main_bss_8010E8AC;
extern struct D_main_bss_8011A444 *D_main_bss_801143AC;
extern struct D_main_bss_8011A444 *D_main_bss_801163B4;

s32 freeRenderSubsystemResources(void) {
    destroyTextureLUTs();
    rs_free(D_main_bss_8011A444);
    if (D_main_bss_801163B4 != NULL) {
        rs_free(D_main_bss_801163B4);
    }
    if (D_main_bss_801143AC != NULL) {
        rs_free(D_main_bss_801143AC);
    }
    rs_free(D_main_bss_8010E8A8);
    rs_free(D_main_bss_8010E8AC);
    selectAndApplyViMode();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/08510", fake_func_800186D8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", junk_800007E8);
