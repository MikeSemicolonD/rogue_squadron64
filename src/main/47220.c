#include "common.h"
#include "common_types.h"

#include "main/47220.h"

typedef struct {
    s32 pad0;
    f32 originX;
    f32 originZ;
    u8 padC[8];
    s32 width;
    s32 depth;
    u16 *cells;
} DatGridInfo;

typedef struct {
    u16 prev;
    u16 next;
    u16 type;
    s16 cell;
    s32 item;
} DatNode;

extern s32 D_main_bss_801375D8;
extern s32 gDoublyLinkedNodePool12;
extern u16 D_main_bss_80136FC0;

void parseDatItemCommon(s32 arg0, u8 *arg1) {
    s32 x;
    s32 z;
    u16 head;
    s32 idx;
    s32 cell;
    s32 off;
    DatNode *node;
    u16 v;

    x = (s32)((*(f32 *)arg1 - ((DatGridInfo *)&D_main_bss_801375D8)->originX) * 0.25f);
    if (x < 0) {
        x = 0;
    } else if (x >= ((DatGridInfo *)&D_main_bss_801375D8)->width) {
        x = ((DatGridInfo *)&D_main_bss_801375D8)->width - 1;
    }
    z = (s32)((*(f32 *)(arg1 + 8) - ((DatGridInfo *)&D_main_bss_801375D8)->originZ) * 0.25f);
    if (z < 0) {
        z = 0;
    } else if (z >= ((DatGridInfo *)&D_main_bss_801375D8)->depth) {
        z = ((DatGridInfo *)&D_main_bss_801375D8)->depth - 1;
    }
    head = D_main_bss_80136FC0;
    idx = head & 0xFFFF;
    cell = x + z * ((DatGridInfo *)&D_main_bss_801375D8)->width;
    if (idx != 0xFFFF) {
        node = (DatNode *)(gDoublyLinkedNodePool12 + idx * 12);
        v = node->next;
        D_main_bss_80136FC0 = v;
        if (v != 0xFFFF) {
            *(u16 *)(D_main_bss_80136FC0 * 12 + gDoublyLinkedNodePool12) = 0xFFFF;
        }
        off = cell * 2;
        v = *(u16 *)(off + (s32)((DatGridInfo *)&D_main_bss_801375D8)->cells);
        node->next = v;
        if (v != 0xFFFF) {
            *(u16 *)(node->next * 12 + gDoublyLinkedNodePool12) = head;
        }
        node->prev = 0xFFFF;
        node->cell = cell;
        node->type = 3;
        node->item = arg0;
        *(u16 *)(off + (s32)((DatGridInfo *)&D_main_bss_801375D8)->cells) = head;
    }
}

typedef struct {
    u16 type;
    u8 pad2[4];
    u16 id;
    u8 pad8[4];
    void *ptrC;
    f32 pos[3];
    u8 pad1C[0x18];
    u16 f34;
    u8 pad36[0x16];
    s32 flags;
    u8 pad50[4];
    s32 f54;
    u8 pad58[4];
    void *name;
} DatObjA;

typedef struct {
    u8 pad0[0xC];
    void *ptrC;
    f32 pos[3];
} DatObjB;

typedef struct {
    u8 pad0[0xC];
    void *ptrC;
    u8 pad10[0x10];
    void *ptr20;
    u8 pad24[4];
    s32 f28;
    void *ptr2C;
} DatObjC;

typedef struct {
    u16 type;
    u8 pad2[4];
    u16 id;
    u8 pad8[4];
    void *ptrC;
    f32 x;
    u8 pad14[4];
    f32 z;
    u8 pad1C[0xC];
    f32 w;
    u8 pad2C[4];
    f32 d;
    s32 flags;
} DatObjD;

typedef struct {
    u8 pad0[6];
    u16 id;
    u8 pad8[4];
    void *ptrC;
    u8 pad10[0x10];
    s32 flags;
} DatObjE;

typedef struct {
    u32 numObjs;
    void **objs;
    u32 pad8;
    u32 padC;
    u32 numB;
    void **b;
    u32 numC;
    void **c;
    u8 pad20[0x10];
    u32 numD;
    void **d;
    u32 numE;
    void **e;
    u32 pad40;
    void *refs;
} DatFile;

typedef struct {
    DatFile *dat;
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    s32 width;
    s32 depth;
    u16 *cells;
} DatGridFull;

extern u8 D_main_bss_80130B39;
extern s32 D_main_bss_801375D4;
extern s32 D_main_bss_801375D0;
extern u8 D_main_bss_80130B3A;
extern u8 D_main_bss_80130B63;
extern u8 D_main_bss_80130BA0;
extern s32 D_main_bss_80136DC0;
extern s32 D_main_bss_80136FB0;
extern s32 D_main_bss_80137CE4;
extern s32 gCurrentLevel;
extern s32 gGameSettings;
f32 floatModulo(f32, f32);
s32 getAssetNameForNpcType(s32);
void *load_asset(s32 *);
s32 load_dat_file_assets();
s32 load_hmt_and_hob(s32 *, s32 *, s32, s32);
s32 markHighLodCellsInGrid(f32, f32, f32, f32);
s32 markLowLodCellsInGrid(f32, f32, f32, f32);
s32 parseDatEventTriggers(void **, u32);
s32 parseDatSpawnPositions(void *, s32);
s32 rs_malloc(s32, s32);
s32 sprintf(s32 *, s32 *, s32);
void **walkMeshdef0List(s32 *);
void parseDatItemCommon(s32, u8 *);
void setupNpcUpdateFunctions(s32);
void releaseMeshAsset(void *);

#define GRID ((DatGridFull *)&D_main_bss_801375D8)

void *loadDatFile(s32 arg0) {
    s32 path[10];
    f32 mn[4];
    f32 mx[4];
    DatFile *dat;
    u32 i;
    f32 *bnd;

    sprintf(path, "%s/dat", arg0);
    dat = load_asset(path);
    bnd = (f32 *)&D_main_bss_80136DC0;
    mn[0] = bnd[8];
    mn[2] = bnd[11];
    mx[0] = bnd[9];
    mx[2] = bnd[12];
    mn[1] = mx[1] = 0.0f;

    i = 0;
    if (dat->numObjs != 0) {
        void **list = (void **)((u8 *)dat + (s32)dat->objs);
        dat->objs = list;
        if (dat->numObjs != 0) {
            s32 ff = 0xFFFF;
            do {
                DatObjA *a;
                f32 v;
                u8 *gs;
                a = (DatObjA *)((u8 *)list + (s32)list[i]);
                list[i] = a;
                if (a->ptrC != NULL) {
                    a->ptrC = (u8 *)a + (s32)a->ptrC;
                    a->f34 = ff;
                    a->id = ff;
                    __asm__("" :: "r"(ff));
                    a->f54 = 0x80000000;
                }
                if (!(a->flags & 2)) {
                    if (a->name != NULL) {
                        a->name = (u8 *)a + (s32)a->name;
                    }
                }
                if (D_main_bss_80130B39 != 0) {
                    switch (a->type) {
                    case 0:
                    case 0xD:
                    case 0x14:
                    case 0x21:
                    case 0x28:
                    case 0x2A:
                    case 0x2B:
                    case 0x2E:
                    case 0x33:
                    case 0x41:
                    case 0x42:
                    case 0x44:
                    case 0x4A:
                    case 0x4B:
                        break;
                    case 0x32:
                        if (D_main_bss_80130BA0 == 0) {
                            break;
                        }
                    default:
                        a->type = ff;
                        break;
                    }
                } else if (gCurrentLevel == 3 && (gs = (u8 *)&gGameSettings, gs[0x23] == 0) && a->type == 0xC) {
                    a->type = 0x13;
                }
                v = a->pos[0];
                if (v < mn[0]) {
                    mn[0] = v;
                } else if (mx[0] < v) {
                    mx[0] = v;
                }
                v = a->pos[1];
                if (v < mn[1]) {
                    mn[1] = v;
                } else if (mx[1] < v) {
                    mx[1] = v;
                }
                v = a->pos[2];
                if (v < mn[2]) {
                    mn[2] = v;
                } else if (mx[2] < v) {
                    mx[2] = v;
                }
                i++;
            } while (i < dat->numObjs);
        }
    } else {
        dat->objs = NULL;
    }

    i = 0;
    if (dat->numB != 0) {
        void **list = (void **)((u8 *)dat + (s32)dat->b);
        dat->b = list;
        if (dat->numB != 0) {
            do {
                f32 v;
                DatObjB *b = (DatObjB *)((u8 *)list + (s32)list[i]);
                list[i] = b;
                if (b->ptrC != NULL) {
                    b->ptrC = (u8 *)b + (s32)b->ptrC;
                }
                v = b->pos[0];
                if (v < mn[0]) {
                    mn[0] = v;
                } else if (mx[0] < v) {
                    mx[0] = v;
                }
                v = b->pos[1];
                if (v < mn[1]) {
                    mn[1] = v;
                } else if (mx[1] < v) {
                    mx[1] = v;
                }
                v = b->pos[2];
                if (v < mn[2]) {
                    mn[2] = v;
                } else if (mx[2] < v) {
                    mx[2] = v;
                }
                i++;
            } while (i < dat->numB);
        }
    } else {
        dat->b = NULL;
    }

    i = 0;
    if (dat->numC != 0) {
        void **list = (void **)((u8 *)dat + (s32)dat->c);
        dat->c = list;
        if (dat->numC != 0) {
            do {
                DatObjC *c = (DatObjC *)((u8 *)list + (s32)list[i]);
                list[i] = c;
                if (c->ptrC != NULL) {
                    c->ptrC = (u8 *)c + (s32)c->ptrC;
                }
                if (c->ptr20 != NULL) {
                    c->ptr20 = (u8 *)c + (s32)c->ptr20;
                }
                if (c->f28 != 0) {
                    c->ptr2C = (u8 *)c + (s32)c->ptr2C;
                }
                i++;
            } while (i < dat->numC);
        }
    } else {
        dat->c = NULL;
    }

    i = 0;
    if (dat->numD != 0) {
        void **list = (void **)((u8 *)dat + (s32)dat->d);
        dat->d = list;
        if (dat->numD != 0) {
            do {
                DatObjD *d = (DatObjD *)((u8 *)list + (s32)list[i]);
                list[i] = d;
                if (d->ptrC != NULL) {
                    d->ptrC = (u8 *)d + (s32)d->ptrC;
                    d->id = 0xFFFF;
                }
                switch (d->type) {
                case 4:
                    markHighLodCellsInGrid(d->x, d->x + d->w, d->z, d->z + d->d);
                    break;
                case 5:
                    markLowLodCellsInGrid(d->x, d->x + d->w, d->z, d->z + d->d);
                    break;
                }
                i++;
            } while (i < dat->numD);
        }
    } else {
        dat->d = NULL;
    }

    i = 0;
    if (dat->numE != 0) {
        void **list = (void **)((u8 *)dat + (s32)dat->e);
        dat->e = list;
        if (dat->numE != 0) {
            do {
                DatObjE *e = (DatObjE *)((u8 *)list + (s32)list[i]);
                list[i] = e;
                if (e->ptrC != NULL) {
                    e->ptrC = (u8 *)e + (s32)e->ptrC;
                    e->id = 0xFFFF;
                }
                i++;
            } while (i < dat->numE);
        }
    } else {
        dat->e = NULL;
    }

    if (dat->refs != NULL) {
        dat->refs = (u8 *)dat->refs + (s32)dat;
        for (i = 0; (s32)i < 0x100; i++) {
            u32 *ent;
            void **list;
            s32 off;
            void **slot = (void **)(i * 4 + (s32)dat->refs);
            if (*slot != NULL) {
                ent = (u32 *)((u8 *)*slot + (s32)dat->refs);
                *slot = ent;
                while (*ent != -1) {
                    switch (*ent) {
                    case 0:
                        list = dat->objs;
                        off = ent[1] * 4;
                        break;
                    case 2:
                        list = dat->b;
                        off = ent[1] * 4;
                        break;
                    case 3:
                        list = dat->c;
                        off = ent[1] * 4;
                        break;
                    case 6:
                        list = dat->d;
                        off = ent[1] * 4;
                        break;
                    case 7:
                        list = dat->e;
                        off = ent[1] * 4;
                        break;
                    default:
                        goto clear;
                    }
                    *ent = *(u32 *)(off + (s32)list);
                    ent[1] = ((DatObjB *)*ent)->ptrC;
                    goto adv;
                clear:
                    *ent = 0;
                    ent[1] = 0;
                adv:
                    ent += 2;
                }
            }
        }
    }

    if (D_main_bss_80130B3A == 1) {
        return dat;
    }
    GRID->dat = dat;

    {
    register f32 v asm("$f2");
    f32 r;
    if (mn[0] < 0.0f) {
        r = floatModulo(mn[0], 4.0f);
        v = mn[0] - 4.0f;
        v = v - r;
    } else {
        r = floatModulo(mn[0], 4.0f);
        v = mn[0];
        v = v - r;
    }
    mn[0] = v;
    if (mn[2] < 0.0f) {
        r = floatModulo(mn[2], 4.0f);
        v = mn[2] - 4.0f;
        v = v - r;
    } else {
        r = floatModulo(mn[2], 4.0f);
        v = mn[2];
        v = v - r;
    }
    mn[2] = v;
    if (mx[0] < 0.0f) {
        r = floatModulo(mx[0], 4.0f);
        v = mx[0] - r;
    } else {
        r = floatModulo(mx[0], 4.0f);
        v = mx[0] + 4.0f - r;
    }
    mx[0] = v;
    if (mx[2] < 0.0f) {
        r = floatModulo(mx[2], 4.0f);
        v = mx[2] - r;
    } else {
        r = floatModulo(mx[2], 4.0f);
        v = mx[2] + 4.0f - r;
    }
    mx[2] = v;
    }

    GRID->width = (s32)((mx[0] - mn[0]) * 0.25f);
    if (GRID->width <= 0) {
        GRID->width = 1;
    }
    GRID->depth = (s32)((mx[2] - mn[2]) * 0.25f);
    if (GRID->depth <= 0) {
        GRID->depth = 1;
    }
    GRID->minX = mn[0];
    GRID->minZ = mn[2];
    GRID->maxX = mx[0];
    GRID->maxZ = mx[2];

    if (D_main_bss_80130B39 == 0) {
        parseDatEventTriggers(dat->e, dat->numE);
    }
    load_dat_file_assets();

    if (D_main_bss_80130B39 != 0) {
        i = 0;
        if (GRID->dat->numObjs != 0) {
            do {
                DatObjA *a = (DatObjA *)GRID->dat->objs[i];
                u16 n = a->type;
                if (n != 0xFFFF && n != 0x14 && n != 0x32 && n != 0x4A) {
                    if (a->name == NULL) {
                        a->name = (void *)getAssetNameForNpcType(n & 0xFF);
                    }
                    a->type = 0;
                }
                i++;
            } while (i < GRID->dat->numObjs);
        }
    }

    i = 0;
    GRID->cells = (u16 *)rs_malloc(GRID->width * GRID->depth * 2, 0);
    if (GRID->width * GRID->depth > 0) {
        do {
            GRID->cells[i] = 0xFFFF;
            i++;
        } while ((s32)i < GRID->width * GRID->depth);
        i = 0;
    }

    i = 0;
    D_main_bss_801375D4 = 0;
    if (dat->numObjs != 0) {
        do {
            DatObjA *a = dat->objs[i];
            s32 n;
            if (!(a->flags & 4)) {
                if (D_main_bss_80130B39 == 0) {
                    n = parseDatSpawnPositions(a, D_main_bss_80137CE4);
                } else {
                    n = 1;
                }
                if (n == 1) {
                    a = dat->objs[i];
                    parseDatItemCommon((s32)a, (u8 *)a + 0x10);
                } else if (n == 2) {
                    D_main_bss_801375D4++;
                }
            }
            i++;
        } while (i < dat->numObjs);
    }

    if (D_main_bss_801375D4 != 0) {
        s32 n;
        s32 *p = &D_main_bss_801375D0;
        *p = rs_malloc(D_main_bss_801375D4 * 4, 0);
        n = 0;
        i = 0;
        if (dat->numObjs != 0) {
            do {
                DatObjA *a = dat->objs[i];
                if (!(a->flags & 4)) {
                    if (parseDatSpawnPositions(a, D_main_bss_80137CE4) == 2) {
                        *(void **)(n++ * 4 + D_main_bss_801375D0) = dat->objs[i];
                    }
                }
                i++;
            } while (i < dat->numObjs);
        }
    } else {
        D_main_bss_801375D0 = 0;
    }

    if (D_main_bss_80130B39 == 0) {
        i = 0;
        if (dat->numE != 0) {
            do {
                DatObjE *e = dat->e[i];
                if (!(e->flags & 4)) {
                    parseDatItemCommon((s32)e, (u8 *)e + 0x10);
                }
                i++;
            } while (i < dat->numE);
        }
        i = 0;
        if (dat->numD != 0) {
            do {
                DatObjD *d = dat->d[i];
                if (d->flags & 0x80) {
                    setupNpcUpdateFunctions((s32)d);
                }
                i++;
            } while (i < dat->numD);
        }
    }

    sprintf(path, "%s/opkg", arg0);
    load_hmt_and_hob(path, &D_main_bss_80136FB0, 1, 0);
    if (D_main_bss_80130B63 != 0) {
        sprintf(path, "%s/opkg2", arg0);
        load_hmt_and_hob(path, &D_main_bss_80136FB0, 1, 0);
    }
    if (gCurrentLevel == 0xA) {
        void **m = walkMeshdef0List("b_tsp_hi");
        if (m != NULL) {
            u8 *mesh = *m;
            *(f32 *)(mesh + 0x44) = *(f32 *)(mesh + 0x44) * 1.5f;
            releaseMeshAsset(m);
        }
    }
    return NULL;
}

extern u8 D_main_bss_80130B39;
extern s32 D_main_bss_801375D0;
extern s32 D_main_bss_801375D4;
s32 isDatItemConditionMet(s32);
void setupNpcUpdateFunctions(s32);

void ugcsV(f32 *pos) __asm__("updateActiveGridCellState");
void ugcsV(f32 *pos) {
    s32 x0;
    s32 x1;
    s32 z1;
    s32 z;
    s32 x;
    s32 cell;
    s32 off;
    s32 o;
    s32 i;
    f32 fx;
    f32 fz;
    f32 q = 0.25f;
    f32 ten = 10.0f;
    u16 n;
    u16 nx;
    u16 pv;
    s32 kind;
    s32 o12;
    s32 item;
    u8 hit;
    DatNode *node;

    fx = (pos[0] - ((DatGridInfo *)&D_main_bss_801375D8)->originX) * q;
    x0 = fx - ten;
    fz = (pos[2] - ((DatGridInfo *)&D_main_bss_801375D8)->originZ) * q;
    if (x0 < 0) {
        x0 = 0;
    } else if (x0 >= ((DatGridInfo *)&D_main_bss_801375D8)->width) {
        x0 = ((DatGridInfo *)&D_main_bss_801375D8)->width - 1;
    }
    z = fz - ten;
    __asm__("" :: "r"(z));
    if (z < 0) {
        z = 0;
    } else if (z >= ((DatGridInfo *)&D_main_bss_801375D8)->depth) {
        z = ((DatGridInfo *)&D_main_bss_801375D8)->depth - 1;
    }
    x1 = fx + ten;
    if (x1 < 0) {
        x1 = 0;
    } else if (x1 >= ((DatGridInfo *)&D_main_bss_801375D8)->width) {
        x1 = ((DatGridInfo *)&D_main_bss_801375D8)->width - 1;
    }
    z1 = fz + ten;
    if (z1 < 0) {
        z1 = 0;
    } else if (z1 >= ((DatGridInfo *)&D_main_bss_801375D8)->depth) {
        z1 = ((DatGridInfo *)&D_main_bss_801375D8)->depth - 1;
    }
    for (; z < z1; z++) {
        x = x0;
        cell = x + z * ((DatGridInfo *)&D_main_bss_801375D8)->width;
        for (; x < x1; x++, cell++) {
            o = (u16)cell * 2;
            n = *(u16 *)(o + (s32)((DatGridInfo *)&D_main_bss_801375D8)->cells);
            if (n != 0xFFFF) {
                off = o;
                do {
                    o12 = n * 12;
                    item = ((DatNode *)(o12 + gDoublyLinkedNodePool12))->item;
                    kind = *(u16 *)item;
                    if (D_main_bss_80130B39 == 0) {
                        hit = 0;
                        if (((DatNode *)(o12 + gDoublyLinkedNodePool12))->type == 3) {
                            if (isPointXzWithinRangeOfRef(pos, (f32 *)(item + 0x10))) {
                                hit = isDatItemConditionMet(((DatNode *)(o12 + gDoublyLinkedNodePool12))->item) != 0;
                            }
                        }
                    } else {
                        hit = 0;
                        if (((DatNode *)(o12 + gDoublyLinkedNodePool12))->type == 3) {
                            hit = isPointXzWithinRangeOfRef(pos, (f32 *)(item + 0x10)) != 0;
                        }
                    }
                    if (hit) {
                        nx = ((DatNode *)(n * 12 + gDoublyLinkedNodePool12))->next;
                        pv = ((DatNode *)(n * 12 + gDoublyLinkedNodePool12))->prev;
                        if (nx != 0xFFFF) {
                            ((DatNode *)(nx * 12 + gDoublyLinkedNodePool12))->prev = pv;
                        }
                        if (pv != 0xFFFF) {
                            ((DatNode *)(pv * 12 + gDoublyLinkedNodePool12))->next = nx;
                        } else {
                            *(u16 *)(off + (s32)((DatGridInfo *)&D_main_bss_801375D8)->cells) = nx;
                        }
                        if (kind != 0xFFFF) {
                            setupNpcUpdateFunctions(((DatNode *)(n * 12 + gDoublyLinkedNodePool12))->item);
                        }
                        ((DatNode *)(n * 12 + gDoublyLinkedNodePool12))->next = D_main_bss_80136FC0;
                        if (D_main_bss_80136FC0 != 0xFFFF) {
                            ((DatNode *)(D_main_bss_80136FC0 * 12 + gDoublyLinkedNodePool12))->prev = n;
                        }
                        D_main_bss_80136FC0 = n;
                        ((DatNode *)(n * 12 + gDoublyLinkedNodePool12))->prev = 0xFFFF;
                        n = nx;
                    } else {
                        n = ((DatNode *)(n * 12 + gDoublyLinkedNodePool12))->next;
                    }
                } while (n != 0xFFFF);
            }
        }
    }
    for (i = 0; i < D_main_bss_801375D4; i++) {
        if (*(s32 *)(i * 4 + D_main_bss_801375D0) != 0 && isDatItemConditionMet(*(s32 *)(i * 4 + D_main_bss_801375D0))) {
            setupNpcUpdateFunctions(*(s32 *)(i * 4 + D_main_bss_801375D0));
            *(s32 *)(i * 4 + D_main_bss_801375D0) = 0;
        }
    }
}

typedef struct { u8 pad0[8]; u16 h8; u8 padA[0x1E]; u8 mtx[0x30]; } PdMesh;
typedef struct { s32 w0; u8 pad4[0xC]; f32 f10, f14, f18; s32 w1C, w20, w24; f32 f28, f2C, f30; u8 pad34[0x28]; s32 p5C; } PdRec;
typedef struct { PdMesh *mesh; PdRec *rec; f32 x, y, z; u8 pad14[0x24]; s32 w38; f32 f3C; u8 tree; } PdSelf;
typedef struct { u8 pad0[4]; PdSelf *self; void *p8; void *pC; u8 pad10[6]; u16 h16; } PdNpc;
extern u8 D_main_bss_80130B39;
extern u16 D_main_bss_80139574;
extern s32 D_main_bss_801375F8;
extern s32 D_8010CA1C;
u8 applyNamedEffectParameterDefault(s32, void *, void *, s32);
PdMesh *pdWalk(s32) __asm__("walkMeshdef0List");
void destroyNpcSlotByIndex(u16);
void buildRotationMatrixSlot0(void *, s32);
void composeRotationMatrixSlot1(void *, s32);
void composeRotationMatrixSlot2(void *, s32);
void applyScaleToMat3x4(void *, f32, f32, f32);
void addVec3At0x24(void *, f32, f32, f32);
void popNpcSlotFromTail(u16, void *);
void dispatchDatSubtypeByRandomIndex(void *, void *);
void pdCommon(void *, void *) __asm__("parseDatItemCommon");
void walkDatTreeAndCollectSubtypes(void *, void *);
void releaseMeshAsset(void *);
s32 *getCraftRecordByIdx(s32);
f32 *getCutsceneRuntimeContext();
void walkDatTreeAndScaleLeafByFloat(void *, void *, s32);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
void walkDatTreeAndVisitChildren(void *, void *, void *);

static __inline__ s32 pdInRange(f32 *arg0) {
    s32 *var_a0;
    s32 *var_v0;

    if (D_main_bss_80130B39 == 0) {
        if (!(D_8010CA1C & 8)) {
            var_a0 = getCraftRecordByIdx(0);
        } else {
            var_v0 = &D_main_bss_801375F8;
            goto block_5;
        }
    } else {
        var_v0 = (s32 *)getCutsceneRuntimeContext();
block_5:
        var_a0 = var_v0;
    }
    return isPointXzWithinRangeOfRef((f32 *) var_a0, arg0);
}

s32 parseDatItemSubtypes1To5(PdNpc *arg0, u16 arg1, PdRec *arg2) {
    PdSelf *self = arg0->self;
    PdRec *r;
    s32 nm;
    PdMesh *m;
    f32 v;
    u8 buf[0x10];

    switch (arg1) {
    case 1:
        r = arg2;
        nm = arg2->p5C;
        if (D_main_bss_80130B39 == 1 && applyNamedEffectParameterDefault(nm, buf, &arg2->f10, 0) != 0) {
            nm = (s32)buf;
        }
        m = pdWalk(nm);
        self->mesh = m;
        if (m == NULL) {
            destroyNpcSlotByIndex(arg0->h16);
            return 0;
        }
        m->h8 |= 0x20;
        self->x = r->f10;
        self->y = r->f14;
        self->z = r->f18;
        buildRotationMatrixSlot0(self->mesh->mtx, r->w1C);
        composeRotationMatrixSlot1(self->mesh->mtx, r->w20);
        composeRotationMatrixSlot2(self->mesh->mtx, r->w24);
        applyScaleToMat3x4(self->mesh->mtx, r->f28, r->f2C, r->f30);
        addVec3At0x24(self->mesh->mtx, self->x, self->y, self->z);
        arg0->p8 = &self->x;
        *(void **)((u8 *)arg0 + 0xC) = self->mesh;
        popNpcSlotFromTail(D_main_bss_80139574, arg0);
        self->w38 = 0;
        self->rec = r;
        if (r->f2C > r->f28) {
            if (r->f30 < r->f2C) {
                self->mesh->h8 |= 0x400;
                v = self->rec->f2C;
            } else {
                goto l800;
            }
        } else if (r->f28 < r->f30) {
l800:
            self->mesh->h8 |= 0x800;
            v = self->rec->f30;
        } else {
            v = r->f28;
        }
        self->f3C = (*(f32 **)self->mesh)[0x44 / 4] * v;
        dispatchDatSubtypeByRandomIndex(&self->tree, self->mesh);
        return 1;
    case 2:
        if (self->mesh != NULL) {
            pdCommon(self->rec, &self->rec->f10);
            walkDatTreeAndCollectSubtypes(&self->tree, self->mesh);
            releaseMeshAsset(self->mesh);
        }
        arg0->h16 = 0xFFFF;
        break;
    case 3:
        if (pdInRange(&self->x) != 0) {
            self->w38 = 0;
        } else if (++self->w38 >= 0x15) {
            destroyNpcSlotByIndex(arg0->h16);
            return 1;
        }
        if (self->tree != 0xFF) {
            walkDatTreeAndScaleLeafByFloat(&self->tree, self->mesh, arg2->w0);
            return 1;
        }
        return 1;
    case 5:
        if (*(u16 *)arg2 != 0xFFFF) {
            *(u16 *)arg2 = 0xFFFF;
            break;
        }
        return 1;
    case 4:
        if (addNpcToVisibilityBucket(arg2->w0, self->mesh, &self->x, self->f3C) != 0 && self->tree != 0xFF) {
            walkDatTreeAndVisitChildren(&self->tree, self->mesh, arg2);
        }
        break;
    }
    return 1;
}

s32 rs_free(s32);
extern s32 D_main_bss_801375D0;
extern s32 D_main_bss_801375D8;

void freeLevelDatBuffers(void) {
    rs_free(D_main_bss_801375D0);
    D_main_bss_801375D0 = 0;
    rs_free((*(s32 *)((u8 *)(&D_main_bss_801375D8) + 0)));
    rs_free((*(s32 *)((u8 *)(&D_main_bss_801375D8) + 0x1C)));
}

void *getLevelDatItemByName(char *name) {
    return getDatItemByName((struct dat_file_header *)D_main_bss_801375D8, name);
}

static inline void *getDatItemInline(struct dat_file_header *hdr, char *name) {
    u8 *s;
    u8 *t;
    u32 hash = 0xFFFF;
    struct data_hashmap_bucket *b;

    s = (u8 *)name;
    while (*s != 0) {
        hash = *s++ + (u16)hash * 33;
    }
    b = hdr->buckets[hash & 0xFF];
    if (b == NULL) {
        return NULL;
    }
    for (; b->dat_entry != (void *)-1; b++) {
        s = (u8 *)name;
        t = (u8 *)b->entry_name;
        while (*s == *t) {
            if (*s == 0) {
                break;
            }
            s++;
            t++;
        }
        if (*s == 0 && *t == 0) {
            return b->dat_entry;
        }
    }
    return NULL;
}

void *getDatItemByName(struct dat_file_header *hdr, char *name) {
    return getDatItemInline(hdr, name);
}

void *findDatItemInTableByName(struct dat_file_header *hdr, u32 *out, char *name) {
    u8 *item = getDatItemInline(hdr, name);

    if (item != NULL && out != NULL) {
        out[0] = *(u32 *)(item + 0x1C);
        out[1] = *(u32 *)(item + 0x20);
        out[2] = *(u32 *)(item + 0x20) + *(u32 *)(item + 0x1C) * 12;
    }
    return item;
}

extern s32 D_main_bss_801375F8;
extern s32 D_8010CA1C;
f32 *getCutsceneRuntimeContext();
extern u8 D_main_bss_80130B39;

void isNpcWithinActiveReferenceRange(f32 *arg0) {
    s32 *var_a0;
    s32 *var_v0;

    if (D_main_bss_80130B39 == 0) {
        if (!(D_8010CA1C & 8)) {
            var_a0 = getCraftRecordByIdx(0);
        } else {
            var_v0 = &D_main_bss_801375F8;
            goto block_5;
        }
    } else {
        var_v0 = getCutsceneRuntimeContext();
block_5:
        var_a0 = var_v0;
    }
    isPointXzWithinRangeOfRef((f32 *) var_a0, arg0);
}

s32 isPointXzWithinRangeOfRef(Vec3f arg0, Vec3f arg1) {
    f32 xdist;
    f32 zdist;

    xdist = (arg0[0] - arg1[0]) * 0.25f;
    zdist = (arg0[2] - arg1[2]) * 0.25f;
    if (144.0f < ((xdist * xdist) + (zdist * zdist))) {
        return 0;
    } else {
        return 1;
    }
}

static const u32 rodata_padding = 0x8FA605E8;

s32 *getCraftRecordByIdx(s32);
s32 updateActiveGridCellState(s32 *);
extern s32 D_8010CA1C;
extern s32 D_main_bss_801375F8;

void lookupActivePlayerCraftGridCell(void) {
    s32 *var_v0;

    if (!(D_8010CA1C & 8)) {
        var_v0 = getCraftRecordByIdx(0);
    } else {
        var_v0 = &D_main_bss_801375F8;
    }
    updateActiveGridCellState(var_v0);
}
