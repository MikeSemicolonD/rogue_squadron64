#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/42AF0", allocAndInitDoublyLinkedNodePool12);

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
extern s32 gDoublyLinkedNodePool12;
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
        rs_free(gDoublyLinkedNodePool12);
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
