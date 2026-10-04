#include "common.h"
#include "common_types.h"

typedef struct DoublyLinkedNode12_s {
    u16 prev;
    u16 next;
    s32 unk4;
    s32 unk8;
} DoublyLinkedNode12;

typedef struct {
    u16 *unk0;
    u8 *unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x10];
    f32 unk20;
    u8 pad24[8];
    f32 unk2C;
    u8 pad30[8];
    u16 unk38;
    u16 unk3A;
} GridDesc;

extern GridDesc D_main_bss_80136DC0;

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

extern s16 D_main_bss_80130C70[];

s32 rasterizeEdgeXSpansAscending(f32 *a, f32 *b, s32 n) {
    f32 slope;
    s32 y0;
    s32 y1;
    s16 *p;
    s32 t;

    if (b[2] > a[2]) {
        y0 = (s32)a[2];
        y1 = (s32)b[2];
        slope = (b[0] - a[0]) / (b[2] - a[2]);
        if (slope < 0.0f) {
            if (y0 < y1) {
                do {
                    t = y0 + 1;
                    D_main_bss_80130C70[n] = (s32)(a[0] + (((f32)t - a[2]) * slope));
                    n++;
                    y0 = t;
                } while (y0 < y1);
            }
            D_main_bss_80130C70[n] = (s32)b[0];
        } else {
            if (n == 0 || a[0] < (f32)D_main_bss_80130C70[n]) {
                D_main_bss_80130C70[n] = (s32)a[0];
            }
            y0++;
            if (y1 >= y0) {
                do {
                    n++;
                    D_main_bss_80130C70[n] = (s32)(a[0] + (((f32)y0 - a[2]) * slope));
                    y0++;
                } while (y1 >= y0);
            }
        }
    }
    return n;
}

INCLUDE_ASM("asm/nonmatchings/main/42AF0", rasterizeEdgeXSpansDescending);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", scanConvertTriangleToSpanTable);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", binPolygonIntoTerrainGrid);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", streamTerrainGridCellsByDistance);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", buildGridCellMeshForFace);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", buildVisibleTerrainGridAroundCamera);

extern f32 D_main_8003A53C;
void markLowLodCellsInGrid(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 x;
    u16 *cell;
    u8 *info;
    f32 o;
    f32 sc;

    o = D_main_bss_80136DC0.unk20;
    __asm__("lwc1 %0, D_main_8003A53C" : "=f"(sc));
    x0 = (s32)((arg0 - o) * sc);
    if (x0 < 0) {
        x0 = 0;
    }
    x1 = (s32)((arg1 - o) * sc);
    if (x1 >= (s32)D_main_bss_80136DC0.unk38) {
        x1 = D_main_bss_80136DC0.unk38 - 1;
    }
    o = D_main_bss_80136DC0.unk2C;
    y0 = (s32)((arg2 - o) * sc);
    if (y0 < 0) {
        y0 = 0;
    }
    y1 = (s32)((arg3 - o) * sc);
    if (y1 >= (s32)D_main_bss_80136DC0.unk3A) {
        y1 = D_main_bss_80136DC0.unk3A - 1;
    }
    if (y1 >= y0) {
        do {
            x = x0;
            if (x1 >= x) {
                do {
                    cell = (u16 *)(((x + y0 * D_main_bss_80136DC0.unk38) * 2) + (s32)D_main_bss_80136DC0.unk0);
                    *cell |= 0x8000;
                    info = (u8 *)((*(u16 *)(((x + y0 * D_main_bss_80136DC0.unk38) * 2) + (s32)D_main_bss_80136DC0.unk0) & 0x1FFF) * 0x1E + (s32)D_main_bss_80136DC0.unk4);
                    info[2] |= 1;
                    x++;
                } while (x1 >= x);
            }
            y0++;
        } while (y1 >= y0);
    }
}

extern f32 D_main_8003A540;

void markHighLodCellsInGrid(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    s32 x0;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 x;
    u16 *cell;
    u8 *info;
    f32 o;
    f32 sc;

    o = D_main_bss_80136DC0.unk20;
    __asm__("lwc1 %0, D_main_8003A540" : "=f"(sc));
    x0 = (s32)((arg0 - o) * sc);
    if (x0 < 0) {
        x0 = 0;
    }
    x1 = (s32)((arg1 - o) * sc);
    if (x1 >= (s32)D_main_bss_80136DC0.unk38) {
        x1 = D_main_bss_80136DC0.unk38 - 1;
    }
    o = D_main_bss_80136DC0.unk2C;
    y0 = (s32)((arg2 - o) * sc);
    if (y0 < 0) {
        y0 = 0;
    }
    y1 = (s32)((arg3 - o) * sc);
    if (y1 >= (s32)D_main_bss_80136DC0.unk3A) {
        y1 = D_main_bss_80136DC0.unk3A - 1;
    }
    if (y1 >= y0) {
        do {
            x = x0;
            if (x1 >= x) {
                do {
                    cell = (u16 *)(((x + y0 * D_main_bss_80136DC0.unk38) * 2) + (s32)D_main_bss_80136DC0.unk0);
                    *cell |= 0x4000;
                    info = (u8 *)((*(u16 *)(((x + y0 * D_main_bss_80136DC0.unk38) * 2) + (s32)D_main_bss_80136DC0.unk0) & 0x1FFF) * 0x1E + (s32)D_main_bss_80136DC0.unk4);
                    info[2] |= 2;
                    x++;
                } while (x1 >= x);
            }
            y0++;
        } while (y1 >= y0);
    }
}

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

void teardownAnimatedMapGridLayer(void) {
    if (hmpFile != 0) {
        rs_free(D_main_bss_80136DC0.unk8);
        rs_free(D_main_bss_80136DC0.unkC);
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
