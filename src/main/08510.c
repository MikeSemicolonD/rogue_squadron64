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

INCLUDE_ASM("asm/nonmatchings/main/08510", heapWalker);

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

INCLUDE_ASM("asm/nonmatchings/main/08510", emitAllocatedDLCommand);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitFaceDLCommands);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitFrameRdpInitDl);

extern s32 D_main_bss_801142C4;

s32 setActiveRenderListPtr(s32 arg0) {
    D_main_bss_801142C4 = arg0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/08510", emitColorFillRect);

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

INCLUDE_ASM("asm/nonmatchings/main/08510", beginFrameDLChunk);

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

INCLUDE_ASM("asm/nonmatchings/main/08510", drawFrameProfilerBars);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitCombinerStateAndPatch);

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

INCLUDE_ASM("asm/nonmatchings/main/08510", timeSnapshotFiller);

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

INCLUDE_ASM("asm/nonmatchings/main/08510", submitGfxFrame);

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

INCLUDE_ASM("asm/nonmatchings/main/08510", reserveAndEmitDLEntry);

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

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005A0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005A8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005B0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005B8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005C0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005C8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005D0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005D8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005E0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005E8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005F0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005F8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_80000600);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_80000608);

INCLUDE_ASM("asm/nonmatchings/main/08510", heapFreeListDequeue);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitTexturedFaceGeometry);

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

INCLUDE_ASM("asm/nonmatchings/main/08510", appendRdpStateDl);

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

INCLUDE_ASM("asm/nonmatchings/main/08510", emitMaterialTexturedDL);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitMaterialTexturedDLAlt);

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

INCLUDE_ASM("asm/nonmatchings/main/08510", transformSceneLights);

INCLUDE_ASM("asm/nonmatchings/main/08510", bindFaceVerticesToCache);

INCLUDE_ASM("asm/nonmatchings/main/08510", renderLitTexturedMeshFaces);

INCLUDE_ASM("asm/nonmatchings/main/08510", submitSceneNodeRender);

INCLUDE_ASM("asm/nonmatchings/main/08510", renderFlatMeshFaceGroup);

INCLUDE_ASM("asm/nonmatchings/main/08510", renderUnlitMeshFaces);

INCLUDE_ASM("asm/nonmatchings/main/08510", resetVertexCacheSlot);

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

INCLUDE_ASM("asm/nonmatchings/main/08510", processSceneNode);

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

INCLUDE_ASM("asm/nonmatchings/main/08510", drawTextGlyphRect);

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

extern s8 D_main_bss_8011A898;

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

INCLUDE_ASM("asm/nonmatchings/main/08510", advanceVideoFrame);

INCLUDE_ASM("asm/nonmatchings/main/08510", initVideoBootWrapper);

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
