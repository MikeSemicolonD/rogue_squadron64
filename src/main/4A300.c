#include "common.h"

#include "common_types.h"
#include "rs_math.h"

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

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} EsV3;
typedef struct {
    u8 pad0[0xA];
    u16 vert;
    u8 pad0C[8];
    u16 flags;
    u8 pad16[2];
    s16 gx;
    s16 gz;
} EsCell;
typedef struct {
    u16 *cells;
    u8 *tiles;
    u8 pad8[8];
    f32 scale;
    u8 pad14[0x24];
    u16 w;
    u16 h;
} EsGrid;
extern EsV3 *esVerts __asm__("D_main_bss_80137A54");

void emitGridCellTileStrip_impl(EsCell *a, EsGrid *g) __asm__("emitGridCellTileStrip");
void emitGridCellTileStrip_impl(EsCell *a, EsGrid *g) {
    s32 idx;
    u8 *c;
    u8 *l;
    u8 *r;
    u8 *u;
    u8 *d;
    EsV3 *o;
    f32 y;
    f32 yy;
    f32 dx;
    f32 dz;
    register f32 len asm("$f0");

    idx = a->gx + a->gz * g->w;
    c = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    y = 256.0f / g->scale;
    if (a->vert == 0) {
        if (fpCnt == 0 && flushPendingGridCellTiles() == 0) {
            return;
        }
        a->vert = fpList[--fpCnt];
    }
    o = &esVerts[a->vert];
    if (a->gx > 0) {
        l = g->tiles + (g->cells[idx - 1] & 0x1FFF) * 0x1E + 5;
    } else {
        l = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gx < g->w - 1) {
        r = g->tiles + (g->cells[idx + 1] & 0x1FFF) * 0x1E + 5;
    } else {
        r = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gz > 0) {
        u = g->tiles + (g->cells[idx - g->w] & 0x1FFF) * 0x1E + 5;
    } else {
        u = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gz < g->h - 1) {
        d = g->tiles + (g->cells[idx + g->w] & 0x1FFF) * 0x1E + 5;
    } else {
        d = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    yy = y * y;
    dx = (f32)(((s8 *)l)[3] - ((s8 *)c)[1]);
    dz = (f32)(((s8 *)u)[0xF] - ((s8 *)c)[5]);
    SQRTF(len, dx * dx + yy + dz * dz);
    o[0].x = dx / len;
    o[0].y = y / len;
    o[0].z = dz / len;
    dx = (f32)(((s8 *)c)[3] - ((s8 *)r)[1]);
    dz = (f32)(((s8 *)u)[0x13] - ((s8 *)c)[9]);
    SQRTF(len, dx * dx + yy + dz * dz);
    o[1].x = dx / len;
    o[1].y = y / len;
    o[1].z = dz / len;
    dx = (f32)(((s8 *)l)[0x17] - ((s8 *)c)[0x15]);
    dz = (f32)(((s8 *)c)[0xF] - ((s8 *)d)[5]);
    SQRTF(len, dx * dx + yy + dz * dz);
    o[2].x = dx / len;
    o[2].y = y / len;
    o[2].z = dz / len;
    dx = (f32)(((s8 *)c)[0x17] - ((s8 *)r)[0x15]);
    dz = (f32)(((s8 *)c)[0x13] - ((s8 *)d)[9]);
    SQRTF(len, dx * dx + yy + dz * dz);
    o[3].x = dx / len;
    o[3].y = y / len;
    o[3].z = dz / len;
    a->flags = (a->flags & 0xFFFC) | 2;
}

typedef struct {
    u8 pad0[0xC];
    u16 vert;
    u8 pad0E[6];
    u16 flags;
    u8 pad16[2];
    s16 gx;
    s16 gz;
} EaCell;

void emitGridCellTileStripAdjacent_impl(EaCell *a, EsGrid *g) __asm__("emitGridCellTileStripAdjacent");
void emitGridCellTileStripAdjacent_impl(EaCell *a, EsGrid *g) {
    s32 idx;
    u8 *c;
    u8 *l;
    u8 *r;
    u8 *u;
    u8 *d;
    EsV3 *o;
    f32 y;
    f32 yy;
    f32 dx;
    f32 dz;
    register f32 len asm("$f0");

    idx = a->gx + a->gz * g->w;
    c = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    y = 256.0f / g->scale;
    if (a->vert == 0) {
        if (fpCnt == 0 && flushPendingGridCellTiles() == 0) {
            return;
        }
        a->vert = fpList[--fpCnt];
    }
    o = &esVerts[a->vert];
    if (a->gx > 0) {
        l = g->tiles + (g->cells[idx - 1] & 0x1FFF) * 0x1E + 5;
    } else {
        l = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gx < g->w - 1) {
        r = g->tiles + (g->cells[idx + 1] & 0x1FFF) * 0x1E + 5;
    } else {
        r = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gz > 0) {
        u = g->tiles + (g->cells[idx - g->w] & 0x1FFF) * 0x1E + 5;
    } else {
        u = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gz < g->h - 1) {
        d = g->tiles + (g->cells[idx + g->w] & 0x1FFF) * 0x1E + 5;
    } else {
        d = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    yy = y * y;
    dx = (f32)(((s8 *)c)[1] - ((s8 *)c)[3]);
    dz = (f32)(((s8 *)u)[0x11] - ((s8 *)c)[7]);
    SQRTF(len, dx * dx + yy + dz * dz);
    o[0].x = dx / len;
    o[0].y = y / len;
    o[0].z = dz / len;
    dx = (f32)(((s8 *)l)[0xD] - ((s8 *)c)[0xB]);
    dz = (f32)(((s8 *)c)[5] - ((s8 *)c)[0xF]);
    SQRTF(len, dx * dx + yy + dz * dz);
    o[1].x = dx / len;
    o[1].y = y / len;
    o[1].z = dz / len;
    dx = (f32)(((s8 *)c)[0xB] - ((s8 *)c)[0xD]);
    dz = (f32)(((s8 *)c)[7] - ((s8 *)c)[0x11]);
    SQRTF(len, dx * dx + yy + dz * dz);
    o[2].x = dx / len;
    o[2].y = y / len;
    o[2].z = dz / len;
    dx = (f32)(((s8 *)c)[0xD] - ((s8 *)r)[0xB]);
    dz = (f32)(((s8 *)c)[9] - ((s8 *)c)[0x13]);
    SQRTF(len, dx * dx + yy + dz * dz);
    o[3].x = dx / len;
    o[3].y = y / len;
    o[3].z = dz / len;
    dx = (f32)(((s8 *)c)[0x15] - ((s8 *)c)[0x17]);
    dz = (f32)(((s8 *)c)[0x11] - ((s8 *)d)[7]);
    SQRTF(len, dx * dx + yy + dz * dz);
    o[4].x = dx / len;
    o[4].y = y / len;
    o[4].z = dz / len;
    a->flags = (a->flags & 0xFFFC) | 1;
}

typedef struct {
    u8 pad0[0xA];
    u16 vA;
    u8 pad0C[2];
    u16 vE;
    u16 v10;
    u16 v12;
    u16 flags;
    u8 pad16[2];
    s16 gx;
    s16 gz;
} EdCell;

#define ES_VEC(o, dxe, dze)     dx = (f32)(dxe);     dz = (f32)(dze);     SQRTF(len, dx * dx + y * y + dz * dz);     (o)->x = dx / len;     (o)->y = y / len;     (o)->z = dz / len;
#define B(p, i) (((s8 *)(p))[i])

void emitGridCellTileStripDiagonal_impl(EdCell *a, EsGrid *g) __asm__("emitGridCellTileStripDiagonal");
void emitGridCellTileStripDiagonal_impl(EdCell *a, EsGrid *g) {
    s32 idx;
    s32 k;
    u8 *c;
    u8 *l;
    u8 *r;
    u8 *u;
    u8 *d;
    u8 *p;
    EsV3 *o;
    f32 y;
    f32 dx;
    f32 dz;
    f32 len;

    idx = a->gx + a->gz * g->w;
    c = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    y = 256.0f / g->scale;
    if (a->vE == 0) {
        if (fpCnt < 3 && flushPendingGridCellTiles() == 0) {
            return;
        }
        a->vE = fpList[--fpCnt];
        a->v10 = fpList[--fpCnt];
        a->v12 = fpList[--fpCnt];
    }
    __asm__("" :: "r"(idx));
    if (a->gx > 0) {
        l = g->tiles + (g->cells[idx - 1] & 0x1FFF) * 0x1E + 5;
    } else {
        l = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gx < g->w - 1) {
        r = g->tiles + (g->cells[idx + 1] & 0x1FFF) * 0x1E + 5;
    } else {
        r = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gz > 0) {
        u = g->tiles + (g->cells[idx - g->w] & 0x1FFF) * 0x1E + 5;
    } else {
        u = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gz < g->h - 1) {
        d = g->tiles + (g->cells[idx + g->w] & 0x1FFF) * 0x1E + 5;
    } else {
        d = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gx > 0) {
        l = g->tiles + (g->cells[idx - 1] & 0x1FFF) * 0x1E + 5;
    } else {
        l = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gx < g->w - 1) {
        r = g->tiles + (g->cells[idx + 1] & 0x1FFF) * 0x1E + 5;
    } else {
        r = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gz > 0) {
        u = g->tiles + (g->cells[idx - g->w] & 0x1FFF) * 0x1E + 5;
    } else {
        u = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    if (a->gz < g->h - 1) {
        d = g->tiles + (g->cells[idx + g->w] & 0x1FFF) * 0x1E + 5;
    } else {
        d = g->tiles + (g->cells[idx] & 0x1FFF) * 0x1E + 5;
    }
    o = &esVerts[a->vE];
    ES_VEC(o, B(l, 8) - B(c, 6), B(c, 0) - B(c, 0xA))
    for (k = 1; k < 4; k++) {
        p = (u8 *)(k + (s32)c);
        ES_VEC(&o[k], B(p, 4) - B(p, 6), B(p, 0) - B(p, 0xA))
    }
    ES_VEC(&o[4], B(c, 8) - B(r, 6), B(c, 4) - B(c, 0xE))
    o = &esVerts[a->v10];
    ES_VEC(o, B(l, 0x12) - B(c, 0x10), B(c, 0xA) - B(c, 0x14))
    for (k = 1; k < 4; k++) {
        p = (u8 *)(k + (s32)c);
        ES_VEC(&o[k], B(p, 0xE) - B(p, 0x10), B(p, 0xA) - B(p, 0x14))
    }
    ES_VEC(&o[4], B(c, 0x12) - B(r, 0x10), B(c, 0xE) - B(c, 0x18))
    o = &esVerts[a->v12];
    ES_VEC(&o[0], B(c, 0) - B(c, 2), B(u, 0x10) - B(c, 6))
    ES_VEC(&o[1], B(c, 2) - B(c, 4), B(u, 0x12) - B(c, 8))
    ES_VEC(&o[2], B(c, 0xA) - B(c, 0xC), B(c, 6) - B(c, 0x10))
    ES_VEC(&o[3], B(c, 0xC) - B(c, 0xE), B(c, 8) - B(c, 0x12))
    ES_VEC(&o[4], B(c, 0x14) - B(c, 0x16), B(c, 0x10) - B(d, 6))
    o = &esVerts[a->vA];
    ES_VEC(&o[4], B(c, 0x16) - B(c, 0x18), B(c, 0x12) - B(d, 8))
    a->flags = a->flags & 0xFFFC;
}

extern u8 D_main_bss_80136DC0[];
static inline f32 m2cSqrt(f32 x)
{
    f32 r;
    SQRTF(r, x);
    return r;
}
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} McgVtx_l;
typedef struct {
    McgVtx_l col;
    u8 pad0C[2];
    u8 flat;
    u8 pad0F;
    McgVtx_l pos;
    f32 radius;
} TwLight;
typedef struct {
    u8 pad[0x3C];
    McgVtx_l org;
    f32 *axis;
} TwDesc;
void transformWorldPosToGridSpace_impl(void *arg0, McgVtx_l *arg1, TwLight **list, f32 arg3, f32 arg4, f32 arg5) __asm__("transformWorldPosToGridSpace");
void transformWorldPosToGridSpace_impl(void *arg0, McgVtx_l *arg1, TwLight **list, f32 arg3, f32 arg4, f32 arg5) {
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft4;
    f32 w;
    TwDesc *g;
    TwLight *l;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 r;

    g = (TwDesc *) D_main_bss_80136DC0;
    w = (arg1->x * g->axis[4]) + (arg1->y * g->axis[5]) + (arg1->z * g->axis[6]);
    if (w > 0.0f) {
        var_fa0 = g->org.x + (g->axis[0] * w);
        var_fa1 = g->org.y + (g->axis[1] * w);
        var_ft4 = g->org.z + (g->axis[2] * w);
    } else {
        var_fa0 = g->org.x;
        var_fa1 = g->org.y;
        var_ft4 = g->org.z;
    }
    while ((l = *list++) != NULL) {
        if (l->flat != 0) {
            dx = arg3 - l->pos.x;
            if (dx < 0.0f) {
                dx = -dx;
            }
            w = arg5 - l->pos.z;
            if (w < 0.0f) {
                w = -w;
            }
            r = l->radius;
            if (r <= dx || r <= w) {
                continue;
            }
            w = m2cSqrt(1.0f - ((w < dx) ? dx / r : w / r));
        } else {
            dx = arg3 - l->pos.x;
            w = arg1->x * dx;
            dx = dx * dx;
            dy = arg4 - l->pos.y;
            w += arg1->y * dy;
            dx += dy * dy;
            dy = arg5 - l->pos.z;
            w += arg1->z * dy;
            dx += dy * dy;
            if (!(w > 0.01f)) {
                continue;
            }
            r = l->radius;
            if (!(dx < r * r)) {
                continue;
            }
            if (dx < 0.0001f) {
                var_fa0 += l->col.x;
                var_fa1 += l->col.y;
                var_ft4 += l->col.z;
                continue;
            }
            w *= (1.0f / m2cSqrt(dx)) - (1.0f / r);
        }
        var_fa0 += l->col.x * w;
        var_fa1 += l->col.y * w;
        var_ft4 += l->col.z * w;
    }
    if (var_fa0 >= 256.0f) {
        ((u8 *) arg0)[0] = 0xFF;
    } else if (var_fa0 < 0.0f) {
        ((u8 *) arg0)[0] = 0;
    } else {
        ((u8 *) arg0)[0] = (u32) var_fa0;
    }
    if (var_fa1 >= 256.0f) {
        ((u8 *) arg0)[1] = 0xFF;
    } else if (var_fa1 < 0.0f) {
        ((u8 *) arg0)[1] = 0;
    } else {
        ((u8 *) arg0)[1] = (u32) var_fa1;
    }
    if (var_ft4 >= 256.0f) {
        ((u8 *) arg0)[2] = 0xFF;
    } else if (var_ft4 < 0.0f) {
        ((u8 *) arg0)[2] = 0;
    } else {
        ((u8 *) arg0)[2] = (u32) var_ft4;
    }
}

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

typedef struct { u16 next; u16 prev; u16 kind; u16 idx; void *obj; } PoolNode;
typedef struct { u8 pad[3]; s8 lo; s8 hi; u8 pad2[25]; } GridCell30;
typedef struct {
    u16 *cells;
    GridCell30 *tbl;
    u16 *heads;
    u32 pad0;
    f32 f10;
    u8 pad14[0x24];
    u16 w;
    u16 h;
} GridDesc;
typedef struct {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    f32 z;
    f32 r;
} ObjPos;

extern u8 D_main_bss_80136DC0[];
#define GD (*(GridDesc *)D_main_bss_80136DC0)
extern u16 D_main_bss_80136FC0;
extern PoolNode *sopPool __asm__("gDoublyLinkedNodePool12");

s32 scaleObjectPosToGridUnits(ObjPos *o, s32 insert) {
    s32 count = 0;
    s32 two;
    s32 row;
    s32 col;
    s32 rowEnd;
    s32 colEnd;
    s32 idx;
    f32 r;
    f32 rr;
    f32 sc;

    o->x = o->x * 0.5f;
    o->y = o->y * 0.5f;
    o->z = o->z * 0.5f;
    r = o->r * 0.5f;
    o->r = r;
    rr = r * r;
    sc = GD.f10 * 0.00390625f * 0.5f;
    row = (s32)(o->z - r);
    if (row < 0) {
        row = count;
    }
    rowEnd = (s32)(o->z + r);
    if (rowEnd >= GD.h) {
        rowEnd = GD.h - 1;
    }
    colEnd = (s32)(o->x + r);
    if (colEnd >= GD.w) {
        colEnd = GD.w - 1;
    }
    if (row <= rowEnd) {
    for (; row <= rowEnd; row++) {
        col = (s32)(o->x - o->r);
        if (col < 0) {
            col = 0;
        }
        idx = col + row * GD.w;
        for (; col <= colEnd; col++) {
            GridCell30 *cell = &GD.tbl[GD.cells[idx] & 0x1FFF];
            f32 dz = o->z - (f32)row;
            f32 dx;
            f32 dy;
            f32 dd;
            two = 2;
            if (dz > 0.0f) {
                dz -= 1.0f;
            }
            dx = o->x - (f32)col;
            if (dx > 0.0f) {
                dx -= 1.0f;
            }
            dy = (f32)cell->lo * sc - o->y;
            if (dy < 0.0f) {
                dy = o->y - (f32)cell->hi * sc;
                if (dy < 0.0f) {
                    dy = 0.0f;
                }
            }
            dd = dx * dx + dy * dy + dz * dz;
            if (o->pad0[0xE] != 0 || dd < rr) {
            count++;
            if (insert == 0) {
                continue;
            }
            {
                s32 n = D_main_bss_80136FC0;
                s32 a;
                if (n == 0xFFFF) {
                    return count;
                }
                a = sopPool[n].prev;
                if (a != 0xFFFF) {
                    sopPool[a].next = sopPool[n].next;
                }
                {
                PoolNode *q = &sopPool[n];
                a = q->next;
                if (a != 0xFFFF) {
                    sopPool[a].prev = q->prev;
                } else {
                    D_main_bss_80136FC0 = sopPool[n].prev;
                }
                }
                a = GD.heads[idx];
                if (a != 0xFFFF) {
                    a &= 0x7FFF;
                    while (sopPool[a].kind != 2) {
                        register s32 b asm("$2") = sopPool[a].prev;
                        if (b == 0xFFFF) {
                            sopPool[a].prev = n;
                            sopPool[n].next = a;
                            a = 0xFFFF;
                            sopPool[n].prev = a;
                            break;
                        }
                        a = b;
                    }
                    if (a != 0xFFFF) {
                        sopPool[n].next = sopPool[a].next;
                        if (sopPool[n].next != 0xFFFF) {
                            sopPool[sopPool[a].next].prev = n;
                        } else {
                            GD.heads[idx] = n;
                        }
                        sopPool[n].prev = a;
                        sopPool[a].next = n;
                    }
                } else {
                    sopPool[n].next = a;
                    sopPool[n].prev = a;
                    GD.heads[idx] = n;
                }
                sopPool[n].kind = two;
                sopPool[n].idx = idx;
                sopPool[n].obj = o;
            }
            }
            idx++;
        }
    }
    }
    if (insert == 0) {
    o->x = o->x + o->x;
    o->y = o->y + o->y;
    o->z = o->z + o->z;
    o->r = o->r + o->r;
    }
    return count;
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} UgV3;
typedef struct {
    UgV3 col;
    u8 pad0C[4];
    UgV3 pos;
    f32 radius;
} UgLight;
void unpackGridVertexBytes_impl(u8 *arg0, UgV3 *arg1, UgLight **list, u8 *arg3, f32 arg4, f32 arg5, f32 arg6) __asm__("unpackGridVertexBytes");
void unpackGridVertexBytes_impl(u8 *arg0, UgV3 *arg1, UgLight **list, u8 *arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 var_fa0;
    f32 var_fa1;
    f32 var_ft4;
    f32 w;
    UgLight *l;
    f32 dx;
    f32 dy;
    f32 r;

    var_fa0 = arg3[0];
    var_fa1 = arg3[1];
    var_ft4 = arg3[2];
    while ((l = *list++) != NULL) {
        dx = arg4 - l->pos.x;
        w = arg1->x * dx;
        dx = dx * dx;
        dy = arg5 - l->pos.y;
        w += arg1->y * dy;
        dx += dy * dy;
        dy = arg6 - l->pos.z;
        w += arg1->z * dy;
        dx += dy * dy;
        if (!(w > 0.01f)) {
            continue;
        }
        r = l->radius;
        if (!(dx < r * r)) {
            continue;
        }
        if (dx < 0.0001f) {
            var_fa0 += l->col.x;
            var_fa1 += l->col.y;
            var_ft4 += l->col.z;
            continue;
        }
        w *= (1.0f / m2cSqrt(dx)) - (1.0f / r);
        var_fa0 += l->col.x * w;
        var_fa1 += l->col.y * w;
        var_ft4 += l->col.z * w;
    }
    if (var_fa0 >= 256.0f) {
        arg0[0] = 0xFF;
    } else if (var_fa0 < 0.0f) {
        arg0[0] = 0;
    } else {
        arg0[0] = (u32) var_fa0;
    }
    if (var_fa1 >= 256.0f) {
        arg0[1] = 0xFF;
    } else if (var_fa1 < 0.0f) {
        arg0[1] = 0;
    } else {
        arg0[1] = (u32) var_fa1;
    }
    if (var_ft4 >= 256.0f) {
        arg0[2] = 0xFF;
    } else if (var_ft4 < 0.0f) {
        arg0[2] = 0;
    } else {
        arg0[2] = (u32) var_ft4;
    }
}

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
__asm__(".section .rodata\n.word 0x2E020010\n.word 0x1440FFFA\n.section .text");


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
