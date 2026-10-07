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

INCLUDE_ASM("asm/nonmatchings/main/47220", loadDatFile);

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
