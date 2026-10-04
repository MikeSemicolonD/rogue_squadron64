#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main/4A300", flushPendingGridCellTiles);

INCLUDE_ASM("asm/nonmatchings/main/4A300", emitGridCellTileStrip);

INCLUDE_ASM("asm/nonmatchings/main/4A300", emitGridCellTileStripAdjacent);

INCLUDE_ASM("asm/nonmatchings/main/4A300", emitGridCellTileStripDiagonal);

INCLUDE_ASM("asm/nonmatchings/main/4A300", transformWorldPosToGridSpace);

INCLUDE_ASM("asm/nonmatchings/main/4A300", mapCellGeometryToGridSpace);

INCLUDE_ASM("asm/nonmatchings/main/4A300", scaleObjectPosToGridUnits);

INCLUDE_ASM("asm/nonmatchings/main/4A300", unpackGridVertexBytes);

INCLUDE_ASM("asm/nonmatchings/main/4A300", buildGridCellMesh);

INCLUDE_ASM("asm/nonmatchings/main/4A300", getGridCellFromWorldPos);

INCLUDE_ASM("asm/nonmatchings/main/4A300", byteAnimatedDebrisNpcHandler);

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
void mapCellGeometryToGridSpace(void *);

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
