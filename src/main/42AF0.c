#include "common.h"
#include "common_types.h"

typedef struct DoublyLinkedNode12_s {
    u16 prev;
    u16 next;
    s32 unk4;
    s32 unk8;
} DoublyLinkedNode12;

s32 rs_malloc(s32, s32);
extern DoublyLinkedNode12 *gDoublyLinkedNodePool12;
extern s16 D_main_bss_80136FC0;
extern u16 D_main_bss_80136FC8;

void allocAndInitDoublyLinkedNodePool12(s32 count) {
    s32 i;
    u16 none;

    gDoublyLinkedNodePool12 = (DoublyLinkedNode12 *)rs_malloc(count * sizeof(DoublyLinkedNode12), 0);
    for (i = 0; i < count; i++) {
        gDoublyLinkedNodePool12[i].prev = i - 1;
        gDoublyLinkedNodePool12[i].next = i + 1;
        gDoublyLinkedNodePool12[i].unk8 = 0;
    }
    none = 0xFFFF;
    D_main_bss_80136FC8 = none;
    D_main_bss_80136FC0 = 0;
    gDoublyLinkedNodePool12[count - 1].next = none;
    gDoublyLinkedNodePool12[0].prev = none;
}

INCLUDE_ASM("asm/nonmatchings/main/42AF0", rasterizeEdgeXSpansAscending);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", rasterizeEdgeXSpansDescending);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", scanConvertTriangleToSpanTable);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", binPolygonIntoTerrainGrid);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", streamTerrainGridCellsByDistance);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", buildGridCellMeshForFace);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", buildVisibleTerrainGridAroundCamera);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", markLowLodCellsInGrid);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", markHighLodCellsInGrid);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", load_level_hmp);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", cutsceneActorNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", computeGridTileEdgeAdjacencyMasks);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", loadLevelAssets);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", computeGridLayerScrollOffset);

s32 rs_free(s32);
void teardownGridLayerWorker(void);
void freeGridCellBuffers(void);
extern s32 hmpFile;
extern s32 gCurrentLevel;
extern struct DoublyLinkedNode12_s *gDoublyLinkedNodePool12;
extern s32 D_main_bss_80136E1C;
extern s32 D_main_bss_80136DC0[];

void teardownAnimatedMapGridLayer(void) {
    if (hmpFile != 0) {
        rs_free(D_main_bss_80136DC0[2]);
        rs_free(D_main_bss_80136DC0[3]);
        rs_free(hmpFile);
        hmpFile = 0;
    }
    if (gCurrentLevel != 0xA) {
        teardownGridLayerWorker();
        freeGridCellBuffers();
        rs_free((s32)gDoublyLinkedNodePool12);
        rs_free(D_main_bss_80136E1C);
    }
}

extern f32 D_main_bss_80130C50;

void setGridLayerScrollX(f32 arg0) {
    D_main_bss_80130C50 = arg0;
}

extern f32 D_main_bss_80130C54;
extern f32 D_main_bss_80130C58;

void setGridLayerScrollBounds(f32 arg0, f32 arg1) {
    D_main_bss_80130C54 = arg0;
    D_main_bss_80130C58 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/main/42AF0", fake_func_800457CC);
