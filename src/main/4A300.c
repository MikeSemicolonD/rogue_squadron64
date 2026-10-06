#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main/4A300", flushPendingGridCellTiles);

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

INCLUDE_ASM("asm/nonmatchings/main/4A300", buildGridCellMesh);

INCLUDE_ASM("asm/nonmatchings/main/4A300", getGridCellFromWorldPos);

INCLUDE_ASM("asm/nonmatchings/main/4A300", byteAnimatedDebrisNpcHandler);
__asm__(".section .rodata\n.globl D_main_8003A8B4\nD_main_8003A8B4:\n.word 0x3F000000\n.word 0x2E020010\n.word 0x1440FFFA\n.section .text");


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
