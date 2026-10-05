#include "common.h"
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


INCLUDE_ASM("asm/nonmatchings/main/463D0", initGridLayerFromLevelData);

INCLUDE_ASM("asm/nonmatchings/main/463D0", updateGridLayerScroll);

INCLUDE_ASM("asm/nonmatchings/main/463D0", selectGridCellTileVariant);

INCLUDE_ASM("asm/nonmatchings/main/463D0", buildGridCellLabel);

typedef struct { u16 *cell; s16 off; u16 cnt; u16 id; f32 pos; f32 w; } CraftGridEnt;
s32 isCraftAvailableByIdx(s32);

void populateCraftSelectGrid(s32 arg0) {
    f32 pos = 0.0f;
    u16 *p;
    s32 i;
    s32 j;
    s16 off;
    CraftGridEnt *e;
    u8 *q;
    f32 w;

    if (isCraftAvailableByIdx(7) != 0) {
        D_main_bss_80137140 = 0;
        return;
    }
    i = 15;
    q = D_main_bss_80137130 + i;
    do {
        *q-- = i;
    } while (--i >= 0);
    i = 0;
    off = arg0 + 3;
    e = (CraftGridEnt *)D_main_bss_80136FF0;
    p = (u16 *)(((u8 *)D_main_bss_80136DC0.tbl) + arg0 * 4);
    while (1) {
        if (p[0] == 0xFFFF) break;
        e[i].cell = p;
        e[i].pos = pos;
        w = 2.0f;
        if (p[4] != 0) w = (f32)p[4];
        e[i].w = w;
        if (8.0f < w) e[i].w = 8.0f;
        e[i].off = off;
        e[i].cnt = p[2];
        e[i].id = p[0];
        *(u16 *)(((u8 *)D_main_bss_80136DC0.tbl) + p[0] * 4) = off | 0x8000;
        j = 0;
        if (p[2] != 0) {
            do {
                *(u16 *)((((j * 4) | 2) + (u8 *)p + 0xC)) = 0xFFFF;
                j++;
            } while (j < p[2]);
        }
        off = off + 3;
        off = off + j;
        p = (u16 *)((u8 *)p + (j * 4 + 0xC));
        i++;
        pos += 0.06666667f;
        if (i >= 16) break;
    }
    D_main_bss_80137140 = i;
}
__asm__(".section .rodata\n.word 0x1440000C\n.word 0x00AA5006\n.section .text");


#include "common_types.h"
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
