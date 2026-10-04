#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/48A50", allocAndInitGridCellArray);

INCLUDE_ASM("asm/nonmatchings/main/48A50", loadLevelTextureCache);

INCLUDE_ASM("asm/nonmatchings/main/48A50", buildGridCellAdjacencyTable);

INCLUDE_ASM("asm/nonmatchings/main/48A50", getGridCellValueAt);

INCLUDE_ASM("asm/nonmatchings/main/48A50", clampGridCellLookup);

INCLUDE_ASM("asm/nonmatchings/main/48A50", processGridCellByDistance);

INCLUDE_ASM("asm/nonmatchings/main/48A50", recycleGridCellToFreeList);

extern s32 D_main_bss_80137A4C;
extern s32 D_main_bss_80137A54;
extern s32 D_main_bss_80137A5C;
extern s32 D_main_bss_80137A68;

void freeGridCellBuffers(void) {
    rs_free(D_main_bss_80137A5C);
    rs_free(D_main_bss_80137A54);
    rs_free(D_main_bss_80137A4C);
    rs_free(D_main_bss_80137A68);
}

s32 rs_free(s32);
s32 teardownAssetDma(s32, s32);
s32 unregisterServiceWorker(s32);
extern s32 D_main_bss_80137614;
extern s32 D_main_bss_80137A40;
extern s32 D_main_bss_80137A48;
extern s32 D_main_bss_80138920;

void teardownGridLayerWorker(void) {
    rs_free(D_main_bss_80137614);
    unregisterServiceWorker(D_main_bss_80137A40);
    teardownAssetDma(D_main_bss_80138920, D_main_bss_80137A48);
}

INCLUDE_ASM("asm/nonmatchings/main/48A50", hudDisplayUpdateWorker);

INCLUDE_ASM("asm/nonmatchings/main/48A50", fake_func_800496F4);

INCLUDE_RODATA("asm/nonmatchings/main/48A50", D_main_8003A810);
