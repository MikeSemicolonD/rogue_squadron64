#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main/463D0", initGridLayerFromLevelData);

INCLUDE_ASM("asm/nonmatchings/main/463D0", updateGridLayerScroll);

INCLUDE_ASM("asm/nonmatchings/main/463D0", selectGridCellTileVariant);

INCLUDE_ASM("asm/nonmatchings/main/463D0", buildGridCellLabel);

INCLUDE_ASM("asm/nonmatchings/main/463D0", populateCraftSelectGrid);
__asm__(".section .rodata\n.globl D_main_8003A604\nD_main_8003A604:\n.word 0x40000000\n.word 0x1440000C\n.word 0x00AA5006\n.section .text");


#include "common_types.h"
typedef struct {
    u8 pad0[4];
    u16 u4;
    u16 u6;
    u16 u8;
    u8 padA[2];
    f32 fC;
    f32 f10;
} GridLayerRec;
typedef struct { u16 v; u16 w; } GridCell;
typedef struct {
    u8 pad0[0xC];
    GridCell *tbl;
} GridDesc;
extern GridDesc D_main_bss_80136DC0;
extern GridLayerRec D_main_bss_80136FF0[];
extern u8 D_main_bss_80137130[];
extern s32 D_main_bss_80137140;

void loadGridCellTilesByDistance(f32 arg0) {
    u8 sel[4];
    s32 n = 0;
    s32 i = 0;
    s16 v;
    GridLayerRec *r;
    u8 first;
    s32 j;
    if (D_main_bss_80137140 > 0) {
        do {
            r = &D_main_bss_80136FF0[D_main_bss_80137130[i]];
            r->fC = r->fC + r->f10 * arg0;
            v = (r->u4 + ((s32)r->fC % r->u6)) | 0x8000;
            if (n < 4) {
                if (D_main_bss_80136DC0.tbl[r->u8].v & 0x4000) {
                    if ((D_main_bss_80136DC0.tbl[r->u8].v & ~0x4000) != (u16)v) {
                        sel[n++] = i;
                        D_main_bss_80136DC0.tbl[r->u8].v = v;
                    }
                }
            }
            i++;
        } while (i < D_main_bss_80137140);
    }
    i = 0;
    if (n > 0) {
        do {
            first = D_main_bss_80137130[sel[i]];
            j = sel[i];
            while (j < D_main_bss_80137140 - 1) {
                D_main_bss_80137130[j] = D_main_bss_80137130[j + 1];
                j++;
            }
            D_main_bss_80137130[j] = first;
            i++;
        } while (i < n);
    }
}

INCLUDE_ASM("asm/nonmatchings/main/463D0", fake_func_8004661C);
