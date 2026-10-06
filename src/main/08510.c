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
