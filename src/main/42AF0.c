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

INCLUDE_ASM("asm/nonmatchings/main/42AF0", teardownAnimatedMapGridLayer);

extern f32 D_main_bss_80130C50;

void setGridLayerScrollX(f32 arg0) {
    D_main_bss_80130C50 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/main/42AF0", setGridLayerScrollBounds);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", fake_func_800457CC);
