#include "common.h"

#include "common_types.h"

typedef struct {
    u16 h0;
    u16 next;
    u8 pad4[2];
    u16 h6;
    u16 h8;
    u16 tiles[5];
    u16 flags;
    u16 state;
    u8 pad18[0xA0];
} FpCell;
extern FpCell *fpCells __asm__("D_main_bss_80137A5C");
extern u16 fpCnt __asm__("D_main_bss_80137A58");
extern u16 *fpList __asm__("D_main_bss_80137A4C");

s32 flushPendingGridCellTiles(void) {
    FpCell *c = &fpCells[fpCells[3].next];
    s32 i;

    while (fpCnt < 10) {
        {
            if (c->state == 4) {
                return 0;
            }
            if ((c->h6 == 0xFFFF || c->h8 != 0xFFFF) && !(c->flags & 0x40) && c->tiles[0] != 0) {
                i = 0;
                do {
                    u16 t;
                    if (i >= 5) {
                        break;
                    }
                    t = c->tiles[i];
                    fpList[fpCnt++] = t;
                    c->tiles[i] = 0;
                    i++;
                } while (c->tiles[i] != 0);
                c->flags |= 3;
            }
            c = &fpCells[c->next];
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/4A300", emitGridCellTileStrip);

INCLUDE_ASM("asm/nonmatchings/main/4A300", emitGridCellTileStripAdjacent);

INCLUDE_ASM("asm/nonmatchings/main/4A300", emitGridCellTileStripDiagonal);

INCLUDE_ASM("asm/nonmatchings/main/4A300", transformWorldPosToGridSpace);

#include "common_types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} McgVtx;

typedef struct {
    u16 unk0;
    u16 next;
    u16 type;
    u16 pad6;
    s32 val;
} McgNode;

typedef struct {
    u8 pad0[0xA];
    u16 vA;
    u16 vC;
    u16 vE;
    u16 v10;
    u16 v12;
    u8 pad14[4];
    s16 gx;
    s16 gz;
    u8 pad1C[0x30 - 0x1C];
    u8 lod;
    u8 pad31[0x44 - 0x31];
    s8 *heights;
    u8 pad48[0x54 - 0x48];
    s32 out[25];
} McgCell;

typedef struct {
    u8 pad0[8];
    u16 *cells;
    u8 padC[0x38 - 0xC];
    u16 stride;
} McgGrid;

extern McgGrid sMcgGrid __asm__("D_main_bss_80136DC0");
extern f32 D_main_bss_80136DD0;
extern McgVtx *D_main_bss_80137A54;
extern McgNode *gDoublyLinkedNodePool12;
void transformWorldPosToGridSpace(void *, McgVtx *, s32 *, f32, f32, f32);

void mapCellGeometryToGridSpace(McgCell *a) {
    s32 list[10];
    s32 n;
    u16 v;
    McgNode *e;
    McgNode *pool;
    s8 *h;
    McgVtx *p;
    f32 scale;
    f32 x;
    f32 z;
    f32 x0;
    f32 z0;
    f32 x1;
    f32 z1;
    f32 x5;
    f32 z5;
    f32 x25;
    f32 z25;
    f32 x75;
    f32 z75;

    n = 0;
    if (sMcgGrid.cells != NULL) {
        v = sMcgGrid.cells[a->gx + a->gz * sMcgGrid.stride];
        if (v != 0xFFFF) {
            v = gDoublyLinkedNodePool12[v & 0x7FFF].next;
            if (v != 0xFFFF) {
                pool = gDoublyLinkedNodePool12;
                do {
                    e = (McgNode *)(v * sizeof(McgNode) + (s32)pool);
                    if (e->type == 2) {
                        list[n++] = e->val;
                    }
                    if (n >= 9) {
                        break;
                    }
                    v = e->next;
                } while (v != 0xFFFF);
            }
        }
    }
    *(s32 *)((s32)list + (n << 2)) = 0;
    h = a->heights;
    x = (f32)a->gx;
    scale = D_main_bss_80136DD0 * 0.00390625f * 0.5f;
    x0 = x + 0.0f;
    p = &D_main_bss_80137A54[a->vA];
    z = (f32)a->gz;
    z0 = z + 0.0f;
    transformWorldPosToGridSpace(&a->out[0], p++, list, x0, h[0] * scale, z0);
    x1 = x + 1.0f;
    transformWorldPosToGridSpace(&a->out[4], p++, list, x1, h[4] * scale, z0);
    z1 = z + 1.0f;
    transformWorldPosToGridSpace(&a->out[20], p++, list, x0, h[20] * scale, z1);
    transformWorldPosToGridSpace(&a->out[24], p, list, x1, h[24] * scale, z1);
    if (a->lod < 2) {
        x5 = x + 0.5f;
        p = &D_main_bss_80137A54[a->vC];
        transformWorldPosToGridSpace(&a->out[2], p++, list, x5, h[2] * scale, z0);
        z5 = z + 0.5f;
        transformWorldPosToGridSpace(&a->out[10], p++, list, x0, h[10] * scale, z5);
        transformWorldPosToGridSpace(&a->out[12], p++, list, x5, h[12] * scale, z5);
        transformWorldPosToGridSpace(&a->out[14], p++, list, x1, h[14] * scale, z5);
        transformWorldPosToGridSpace(&a->out[22], p, list, x5, h[22] * scale, z1);
        if (a->lod == 0) {
            z25 = z + 0.25f;
            p = &D_main_bss_80137A54[a->vE];
            transformWorldPosToGridSpace(&a->out[5], p++, list, x0, h[5] * scale, z25);
            x25 = x + 0.25f;
            transformWorldPosToGridSpace(&a->out[6], p++, list, x25, h[6] * scale, z25);
            transformWorldPosToGridSpace(&a->out[7], p++, list, x5, h[7] * scale, z25);
            x75 = x + 0.75f;
            transformWorldPosToGridSpace(&a->out[8], p++, list, x75, h[8] * scale, z25);
            transformWorldPosToGridSpace(&a->out[9], p, list, x1, h[9] * scale, z25);
            z75 = z + 0.75f;
            p = &D_main_bss_80137A54[a->v10];
            transformWorldPosToGridSpace(&a->out[15], p++, list, x0, h[15] * scale, z75);
            transformWorldPosToGridSpace(&a->out[16], p++, list, x25, h[16] * scale, z75);
            transformWorldPosToGridSpace(&a->out[17], p++, list, x5, h[17] * scale, z75);
            transformWorldPosToGridSpace(&a->out[18], p++, list, x75, h[18] * scale, z75);
            transformWorldPosToGridSpace(&a->out[19], p, list, x1, h[19] * scale, z75);
            p = &D_main_bss_80137A54[a->v12];
            transformWorldPosToGridSpace(&a->out[1], p++, list, x25, h[1] * scale, z0);
            transformWorldPosToGridSpace(&a->out[3], p++, list, x75, h[3] * scale, z0);
            transformWorldPosToGridSpace(&a->out[11], p++, list, x25, h[11] * scale, z5);
            transformWorldPosToGridSpace(&a->out[13], p++, list, x75, h[13] * scale, z5);
            transformWorldPosToGridSpace(&a->out[21], p, list, x25, h[21] * scale, z1);
            p = &D_main_bss_80137A54[a->vA];
            transformWorldPosToGridSpace(&a->out[23], p + 4, list, x75, h[23] * scale, z1);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/4A300", scaleObjectPosToGridUnits);

INCLUDE_ASM("asm/nonmatchings/main/4A300", unpackGridVertexBytes);

#include "common_types.h"
typedef struct {
    u8 pad0[8];
    u16 i8;
    u16 iA;
    u16 iC;
    u16 iE;
    u16 i10;
    u16 i12;
    u16 flags;
    u8 pad16[2];
    s16 x18;
    s16 y1A;
    u8 pad1C[2];
    u16 i1E;
    u8 pad20[0x10];
    u8 f30;
    u8 pad31[0x13];
    s8 *p44;
    u8 *p48;
    u8 pad4C[8];
    u8 body54[4];
} GCell;

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[0x1A];
    u8 f30;
    u8 pad31[0x87];
} GCellEntry;

typedef struct {
    u8 pad0[2];
    u16 next;
    u16 kind;
    u8 pad6[2];
    u32 val;
} GNode;

extern GCellEntry *gCellArr __asm__("D_main_bss_80137A5C");
extern u8 D_main_bss_80136DC0[];
extern s32 D_main_bss_80137A74;
extern u8 *D_main_bss_80137A50;
extern f32 D_main_bss_80136DD0;
u8 *buildGridCellLabel(void *);
void emitGridCellTileStrip(void *, void *);
void emitGridCellTileStripAdjacent(void *, void *);
void emitGridCellTileStripDiagonal(void *, void *);
extern void unpackGridVertexBytes(u8 *, u8 *, u32 *, u8 *, f32, f32, f32);

typedef struct { u8 b[12]; } V12;
void buildGridCellMesh(GCell *c) {
    u32 list[9];
    f32 fy;
    f32 sp48;
    f32 sp4C;
    f32 sp50;
    f32 sp54;
    f32 sp58;
    f32 sp5C;
    GCellEntry *cell;
    u8 *dst;
    u8 *lbl;
    V12 *src;
    s8 *vt;
    f32 fx;
    f32 sc;
    f32 xh;
    f32 yh;
    f32 xq;
    f32 yq;
    f32 xt;
    f32 yt;
    u16 flags;
    s32 idx;
    GNode *pool;
    GNode *p2;
    s32 n;
    u32 *lp;
    s32 cnt;

    flags = c->flags;
    if (flags & 0x20) {
        if (flags & 0x40) {
            c->p48 = buildGridCellLabel(c);
            return;
        } else {
            cell = &gCellArr[c->i8];
            flags = cell->flags;
            if (!(flags & 0x40)) {
                if ((flags & 3) == 0) {
                    c->p48 = (u8 *)cell + 0x54;
                    return;
                }
                if (cell->f30 < 3 && (flags & 3) == 3) {
                    emitGridCellTileStrip(cell, D_main_bss_80136DC0);
                }
                if (cell->f30 < 2 && (cell->flags & 3) == 2) {
                    emitGridCellTileStripAdjacent(cell, D_main_bss_80136DC0);
                }
                if (cell->f30 == 0) {
                    emitGridCellTileStripDiagonal(cell, D_main_bss_80136DC0);
                }
                mapCellGeometryToGridSpace((void*)cell);
            }
            c->p48 = (u8 *)cell + 0x54;
            return;
        }
    }
    if (!(flags & 0x40)) {
        if (c->f30 < (flags & 3)) {
            if (c->f30 < 3 && (flags & 3) == 3) {
                emitGridCellTileStrip(c, D_main_bss_80136DC0);
            }
            if (c->f30 < 2 && (c->flags & 3) == 2) {
                emitGridCellTileStripAdjacent(c, D_main_bss_80136DC0);
            }
            if (c->f30 == 0) {
                emitGridCellTileStripDiagonal(c, D_main_bss_80136DC0);
            }
            mapCellGeometryToGridSpace(c);
            ((u8 *)c)[0x57] = 1;
        }
    }
    lbl = (u8 *)c + 0x54;
    if (c->flags & 0xC0) {
        lbl = buildGridCellLabel(c);
    }
    pool = (GNode *)gDoublyLinkedNodePool12;
    idx = pool[c->i1E].next;
    if (idx == 0xFFFF || pool[idx].kind != 1) {
        c->p48 = lbl;
        return;
    }
    n = 0;
    if (D_main_bss_80137A74 <= 0) {
        c->p48 = (u8 *)c + 0x54;
        return;
    }
    p2 = pool;
    D_main_bss_80137A74 = D_main_bss_80137A74 - 1;
    dst = D_main_bss_80137A50 + D_main_bss_80137A74 * 0x64;
    c->p48 = dst;
    do {
        list[n] = p2[idx].val;
        n++;
        idx = p2[idx].next;
    } while (idx != 0xFFFF && p2[idx].kind == 1 && n < 8);
    list[n] = 0;
    fx = (f32)c->x18;
    sp4C = fx + 0.0f;
    vt = c->p44;
    sc = D_main_bss_80136DD0 * 0.00390625f * 0.5f;
    fy = (f32)c->y1A;
    sp48 = fy;
    sp50 = fy + 0.0f;
    sp54 = fx + 1.0f;
    src = (V12 *)D_main_bss_80137A54 + c->iA;
    unpackGridVertexBytes(dst, (u8 *)src++, list, lbl, sp4C, (f32)vt[0] * sc, sp50);
    unpackGridVertexBytes(dst + 0x10, (u8 *)src++, list, lbl + 0x10, sp54, (f32)vt[4] * sc, sp50);
    sp58 = sp48 + 1.0f;
    unpackGridVertexBytes(dst + 0x50, (u8 *)src++, list, lbl + 0x50, sp4C, (f32)vt[0x14] * sc, sp58);
    unpackGridVertexBytes(dst + 0x60, (u8 *)src++, list, lbl + 0x60, sp54, (f32)vt[0x18] * sc, sp58);
    if (c->f30 < 2) {
        xh = fx + 0.5f;
        src = (V12 *)D_main_bss_80137A54 + c->iC;
        unpackGridVertexBytes(dst + 8, (u8 *)src++, list, lbl + 8, xh, (f32)vt[2] * sc, sp50);
        sp5C = sp48 + 0.5f;
        unpackGridVertexBytes(dst + 0x28, (u8 *)src++, list, lbl + 0x28, sp4C, (f32)vt[0xA] * sc, sp5C);
        unpackGridVertexBytes(dst + 0x30, (u8 *)src++, list, lbl + 0x30, xh, (f32)vt[0xC] * sc, sp5C);
        unpackGridVertexBytes(dst + 0x38, (u8 *)src++, list, lbl + 0x38, sp54, (f32)vt[0xE] * sc, sp5C);
        unpackGridVertexBytes(dst + 0x58, (u8 *)src++, list, lbl + 0x58, xh, (f32)vt[0x16] * sc, sp58);
        if (c->f30 == 0) {
            yq = sp48 + 0.25f;
            src = (V12 *)D_main_bss_80137A54 + c->iE;
            unpackGridVertexBytes(dst + 0x14, (u8 *)src++, list, lbl + 0x14, sp4C, (f32)vt[5] * sc, yq);
            xq = fx + 0.25f;
            unpackGridVertexBytes(dst + 0x18, (u8 *)src++, list, lbl + 0x18, xq, (f32)vt[6] * sc, yq);
            unpackGridVertexBytes(dst + 0x1C, (u8 *)src++, list, lbl + 0x1C, xh, (f32)vt[7] * sc, yq);
            xt = fx + 0.75f;
            unpackGridVertexBytes(dst + 0x20, (u8 *)src++, list, lbl + 0x20, xt, (f32)vt[8] * sc, yq);
            unpackGridVertexBytes(dst + 0x24, (u8 *)src++, list, lbl + 0x24, sp54, (f32)vt[9] * sc, yq);
            src = (V12 *)D_main_bss_80137A54 + c->i10;
            yt = sp48 + 0.75f;
            unpackGridVertexBytes(dst + 0x3C, (u8 *)src++, list, lbl + 0x3C, sp4C, (f32)vt[0xF] * sc, yt);
            unpackGridVertexBytes(dst + 0x40, (u8 *)src++, list, lbl + 0x40, xq, (f32)vt[0x10] * sc, yt);
            unpackGridVertexBytes(dst + 0x44, (u8 *)src++, list, lbl + 0x44, xh, (f32)vt[0x11] * sc, yt);
            unpackGridVertexBytes(dst + 0x48, (u8 *)src++, list, lbl + 0x48, xt, (f32)vt[0x12] * sc, yt);
            unpackGridVertexBytes(dst + 0x4C, (u8 *)src++, list, lbl + 0x4C, sp54, (f32)vt[0x13] * sc, yt);
            src = (V12 *)D_main_bss_80137A54 + c->i12;
            unpackGridVertexBytes(dst + 4, (u8 *)src++, list, lbl + 4, xq, (f32)vt[1] * sc, sp50);
            unpackGridVertexBytes(dst + 0xC, (u8 *)src++, list, lbl + 0xC, xt, (f32)vt[3] * sc, sp50);
            unpackGridVertexBytes(dst + 0x2C, (u8 *)src++, list, lbl + 0x2C, xq, (f32)vt[0xB] * sc, sp5C);
            unpackGridVertexBytes(dst + 0x34, (u8 *)src++, list, lbl + 0x34, xt, (f32)vt[0xD] * sc, sp5C);
            unpackGridVertexBytes(dst + 0x54, (u8 *)src++, list, lbl + 0x54, xq, (f32)vt[0x15] * sc, sp58);
            src = (V12 *)D_main_bss_80137A54 + c->iA;
            unpackGridVertexBytes(dst + 0x5C, (u8 *)(src + 4), list, lbl + 0x5C, xt, (f32)vt[0x17] * sc, sp58);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/4A300", getGridCellFromWorldPos);

typedef struct {
    f32 pos[3];
    u8 unkC;
    u8 padD;
    u8 unkE;
    u8 padF;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    u16 links[64];
    s32 flags;
    u8 *frames;
    u8 frameStart;
    u8 frameEnd;
    u8 padAA[2];
    f32 rate;
    f32 frame;
} BadObj;

typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    u16 flags;
    u8 pad12[2];
    union {
        u8 *frames;
        u8 rgb[3];
    } u14;
    u8 frameStart;
    u8 frameEnd;
    u8 pad1A[2];
    f32 rate;
} BadArg;

typedef struct {
    u8 pad0[4];
    BadObj *obj;
    u8 pad8[0xE];
    u16 slot;
} BadNpc;

typedef struct {
    u8 pad0[8];
    u16 *heads;
    u8 padC[8];
    f32 x;
    f32 y;
    f32 z;
} BadGrid;

extern BadGrid sBadGrid __asm__("D_main_bss_80136DC0");
extern u16 D_main_bss_80136FC0;
extern u16 D_main_bss_80139596;
void getGridCellFromWorldPos(BadObj *, u16 *);
u16 popNpcSlotFromTail(u16, void *);
void destroyNpcSlotByIndex(u16);

#define BAD_UNLINK_ALL(obj)                                             for (i = 0; i < 64; i++) {                                              n = (obj)->links[i];                                                if (n == 0xFFFF) {                                                      break;                                                          }                                                                   nx = gDoublyLinkedNodePool12[n].next;                               pv = gDoublyLinkedNodePool12[n].unk0;                               if (nx != 0xFFFF) {                                                     gDoublyLinkedNodePool12[nx].unk0 = pv;                          }                                                                   if (pv != 0xFFFF) {                                                     gDoublyLinkedNodePool12[pv].next = nx;                          } else {                                                                sBadGrid.heads[gDoublyLinkedNodePool12[n].pad6] = nx;           }                                                                   fh = D_main_bss_80136FC0; gDoublyLinkedNodePool12[n].next = fh; nx = fh; if (nx != 0xFFFF) { gDoublyLinkedNodePool12[nx].unk0 = n; }                                                                   D_main_bss_80136FC0 = n;                                        }                                                                   gDoublyLinkedNodePool12[D_main_bss_80136FC0].unk0 = 0xFFFF;

s32 byteAnimatedDebrisNpcHandler(BadNpc *arg0, u16 a1, BadArg *arg2) {
    s32 arg1 = a1;
    BadObj *obj = arg0->obj;
    f32 scale;
    f32 f;
    f32 g;
    s32 i;
    s32 n;
    s32 nx;
    s32 pv;
    u16 fh;
    u8 *tbl;

    switch (arg1) {
    case 1:
        popNpcSlotFromTail(D_main_bss_80139596, arg0);
        obj->flags = 0;
        obj->links[0] = 0xFFFF;
        obj->unkC = arg1;
        obj->unkE = 0;
        if (arg2 != NULL) {
            arg2->flags |= 3;
            byteAnimatedDebrisNpcHandler(arg0, 0x1000, arg2);
            return 1;
        }
        obj->flags = 0x10000;
        break;
    case 0x1000:
        if (arg2 != NULL) {
            if (arg2->flags & 1) {
                scale = 0.5f;
                obj->f10 = (arg2->f0 - sBadGrid.x) * scale;
                obj->f14 = (arg2->f4 - sBadGrid.y) * scale;
                obj->f18 = (arg2->f8 - sBadGrid.z) * scale;
                obj->f1C = arg2->fC * scale;
                obj->flags |= 1;
            }
            if (arg2->flags & 2) {
                if (arg2->flags & 0x100) {
                    obj->frames = arg2->u14.frames;
                    obj->frameStart = arg2->frameStart;
                    obj->frameEnd = arg2->frameEnd;
                    obj->rate = arg2->rate;
                    obj->frame = obj->frameStart;
                    obj->pos[0] = obj->frames[obj->frameStart * 4 + 0];
                    obj->pos[1] = obj->frames[obj->frameStart * 4 + 1];
                    obj->pos[2] = obj->frames[obj->frameStart * 4 + 2];
                    obj->flags |= arg2->flags & 0x300;
                } else {
                    obj->pos[0] = arg2->u14.rgb[0];
                    obj->pos[1] = arg2->u14.rgb[1];
                    obj->pos[2] = arg2->u14.rgb[2];
                }
            }
        }
        break;
    case 2:
        BAD_UNLINK_ALL(obj);
        break;
    case 3:
        if (obj->flags & 0x100) {
            f = obj->frame + arg2->f0 * obj->rate;
            i = f;
            obj->frame = f;
            if (i >= obj->frameEnd) {
                if (obj->flags & 0x200) {
                    destroyNpcSlotByIndex(arg0->slot);
                    return 1;
                }
                g = f - (f32)i + (f32)obj->frameStart;
                i = g;
                obj->frame = g;
            }
            obj->pos[0] = obj->frames[i * 4 + 0];
            obj->pos[1] = obj->frames[i * 4 + 1];
            obj->pos[2] = obj->frames[i * 4 + 2];
        }
        if (obj->flags & 1) {
            obj->flags &= ~1;
            BAD_UNLINK_ALL(obj);
            getGridCellFromWorldPos(obj, obj->links);
        }
        break;
    case 4:
        break;
    default:
        return 1;
    }
    return 1;
}
__asm__(".section .rodata
.word 0x2E020010
.word 0x1440FFFA
.section .text");


#include "common_types.h"

typedef struct {
    u8 pad0[8];
    u16 unk8;
    u8 padA[0xA];
    u16 unk14;
    u8 pad16[0x32];
    u8 *unk48;
} GridCellRef;

typedef struct {
    u8 pad0[0x14];
    u16 unk14;
    u8 pad16[0x1A];
    u8 unk30;
    u8 pad31[0x87];
} GridCellEntry;

extern GridCellEntry *D_main_bss_80137A5C;
extern u8 D_main_bss_80136DC0[];
u8 *buildGridCellLabel(void *);
void emitGridCellTileStrip(void *, void *);
void emitGridCellTileStripAdjacent(void *, void *);
void emitGridCellTileStripDiagonal(void *, void *);
void mapCellGeometryToGridSpace(McgCell *);

void buildGridCellMeshNoLabel(GridCellRef *arg0) {
    GridCellEntry *cell;
    u16 flags;

    if (arg0->unk14 & 0x40) {
        arg0->unk48 = buildGridCellLabel(arg0);
    } else {
        cell = &D_main_bss_80137A5C[arg0->unk8];
        flags = cell->unk14;
        if (!(flags & 0x40) && (flags & 3) != 0) {
            if (cell->unk30 < 3 && (flags & 3) == 3) {
                emitGridCellTileStrip(cell, D_main_bss_80136DC0);
            }
            if (cell->unk30 < 2 && (cell->unk14 & 3) == 2) {
                emitGridCellTileStripAdjacent(cell, D_main_bss_80136DC0);
            }
            if (cell->unk30 == 0) {
                emitGridCellTileStripDiagonal(cell, D_main_bss_80136DC0);
            }
            mapCellGeometryToGridSpace(cell);
        }
        arg0->unk48 = (u8 *)cell + 0x54;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/4A300", fake_func_8004CCF8);
