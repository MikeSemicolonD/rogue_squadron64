#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/48A50", allocAndInitGridCellArray);

INCLUDE_ASM("asm/nonmatchings/main/48A50", loadLevelTextureCache);

INCLUDE_ASM("asm/nonmatchings/main/48A50", buildGridCellAdjacencyTable);

INCLUDE_ASM("asm/nonmatchings/main/48A50", getGridCellValueAt);

INCLUDE_ASM("asm/nonmatchings/main/48A50", clampGridCellLookup);

INCLUDE_ASM("asm/nonmatchings/main/48A50", processGridCellByDistance);

typedef struct {
    u16 f0;
    u16 f2;
    u8 pad4[0xB4];
} GridCellA;

typedef struct {
    u16 f0;
    u16 f2;
    u8 pad4[8];
} GridCellB;

extern GridCellA *D_main_bss_80137A5C;
extern GridCellB *D_main_bss_80137614;

void recycleGridCellToFreeList(void) {
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;
    s32 var_a1_2;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 var_a2;
    u16 var_a2_2;
    GridCellA *var_v1;
    GridCellB *var_v1_2;
    GridCellA *temp_a1;
    GridCellB *temp_a1_2;
    GridCellA *temp_v1;
    GridCellB *temp_v1_2;
    GridCellA *pa;
    GridCellB *pb;

    var_a2 = D_main_bss_80137A5C[2].f2;
    var_a1 = var_a2 & 0xFFFF;
    if (var_a1 != 0xFFFF) {
        temp_v1 = (GridCellA *)(var_a1 * 0xB8 + (s32)D_main_bss_80137A5C);
        temp_v1->f0 = D_main_bss_80137A5C[4].f0;
        D_main_bss_80137A5C[D_main_bss_80137A5C[4].f0].f2 = var_a2;
        if (temp_v1->f2 != 0xFFFF) {
            do {
                var_a2 = D_main_bss_80137A5C[var_a1].f2;
                var_a1 = var_a2 & 0xFFFF;
            } while (D_main_bss_80137A5C[var_a1].f2 != 0xFFFF);
        }
        D_main_bss_80137A5C[var_a2 & 0xFFFF].f2 = 4;
        D_main_bss_80137A5C[4].f0 = var_a2;
    }
    var_a0 = 2;
    pa = D_main_bss_80137A5C;
    var_v1 = &pa[2];
    do {
        temp_a1 = var_v1 - 1;
        temp_v0 = temp_a1->f2;
        var_v1->f2 = temp_v0;
        if ((temp_v0 & 0xFFFF) != 0xFFFF) {
            pa[var_v1->f2].f0 = var_a0;
        }
        var_a0 -= 1;
        var_v1 = temp_a1;
    } while (var_a0 > 0);
    D_main_bss_80137A5C[0].f2 = 0xFFFF;
    var_a2_2 = D_main_bss_80137614[2].f2;
    var_a1_2 = var_a2_2 & 0xFFFF;
    if (var_a1_2 != 0xFFFF) {
        temp_v1_2 = (GridCellB *)(var_a1_2 * 0xC + (s32)D_main_bss_80137614);
        temp_v1_2->f0 = D_main_bss_80137614[4].f0;
        D_main_bss_80137614[D_main_bss_80137614[4].f0].f2 = var_a2_2;
        if (temp_v1_2->f2 != 0xFFFF) {
            do {
                var_a2_2 = D_main_bss_80137614[var_a1_2].f2;
                var_a1_2 = var_a2_2 & 0xFFFF;
            } while (D_main_bss_80137614[var_a1_2].f2 != 0xFFFF);
        }
        D_main_bss_80137614[var_a2_2].f2 = 4;
        D_main_bss_80137614[4].f0 = var_a2_2;
    }
    var_a0_2 = 2;
    pb = D_main_bss_80137614;
    var_v1_2 = &pb[2];
    do {
        temp_a1_2 = var_v1_2 - 1;
        temp_v0_2 = temp_a1_2->f2;
        var_v1_2->f2 = temp_v0_2;
        if ((temp_v0_2 & 0xFFFF) != 0xFFFF) {
            pb[var_v1_2->f2].f0 = var_a0_2;
        }
        var_a0_2 -= 1;
        var_v1_2 = temp_a1_2;
    } while (var_a0_2 > 0);
    D_main_bss_80137614[0].f2 = 0xFFFF;
}

extern s32 D_main_bss_80137A4C;
extern s32 D_main_bss_80137A54;
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
