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


typedef struct {
    u8 *f0;
    u8 *f4;
    s32 f8;
    u8 padC[0x2C];
    u16 f38;
    u16 f3A;
    u8 pad3C[0x14];
    f32 f10;
} IgRaw;
typedef struct {
    u8 pad0[2];
    u8 flags;
    s8 lo;
    s8 hi;
    u8 pad5[0x19];
} IgElem;
typedef struct {
    u16 *cells;
    IgElem *elems;
    u8 pad8[8];
    f32 f10;
    u8 pad14[0x24];
    u16 w;
    u16 h;
} IgLvl;
typedef struct {
    u8 pad0[0xA];
    u16 hA;
    u16 hC;
    u16 hE;
    u16 h10;
    u16 h12;
    u16 h14;
    u8 pad16[2];
    u16 h18;
    u16 h1A;
    u8 pad1C[2];
    u16 h1E;
    u8 pad20[0x10];
    u8 b30;
    u8 pad31[0x87];
} IgSlot;
typedef struct {
    u8 pad0[0x60];
    s32 i60;
    s32 i64;
    f32 f68;
    f32 f6C;
} IgDat;
typedef struct {
    u8 *f0;
    u8 *f4;
    s32 f8;
    u8 padC[0x2C];
    u16 f38;
    u16 f3A;
    u8 pad3C[0x1C];
} IgHdr;
extern u8 ig37150 __asm__("D_main_bss_80137150");
extern u8 ig37151 __asm__("D_main_bss_80137151");
extern s32 ig375C0 __asm__("D_main_bss_801375C0");
extern f32 ig37164 __asm__("D_main_bss_80137164");
extern f32 ig3715C __asm__("D_main_bss_8013715C");
extern f32 ig37160 __asm__("D_main_bss_80137160");
extern f32 ig37158 __asm__("D_main_bss_80137158");
extern f32 ig37154 __asm__("D_main_bss_80137154");
extern s32 ig37168 __asm__("D_main_bss_80137168");
extern f32 ig36FA8 __asm__("D_main_bss_80136FA8");
extern void *ig37148[2] __asm__("D_main_bss_80137148");
extern IgHdr ig37450 __asm__("D_main_bss_80137450");
extern IgSlot ig37170[] __asm__("D_main_bss_80137170");
extern u16 ig374B0[16] __asm__("D_main_bss_801374B0");
extern u8 ig374D0[] __asm__("D_main_bss_801374D0");
extern void *getLevelDatItemByNameI(char *) __asm__("getLevelDatItemByName");
extern void *rs_mallocI(u32, u16) __asm__("rs_malloc");

void initGridLayerFromLevelData(IgLvl *arg0, s32 arg1) {
    IgDat *dat;
    s32 i;
    s32 j;
    s32 v;
    IgElem *p;
    IgElem *e;
    u16 *cp;

    ig37150 = 0;
    dat = getLevelDatItemByNameI("player_StartPosition");
    if (dat == 0) {
        return;
    }
    v = dat->i60;
    if (v == 0) {
        return;
    }
    ig375C0 = 0x7F - v;
    e = arg0->elems;
    ig37164 = (f32)dat->i64;
    ig3715C = dat->f68;
    ig37160 = dat->f6C;
    ig36FA8 = ig37164 * arg0->f10 * 0.00390625f;
    p = e;
    for (i = 0; i < arg1; i++, p++) {
        if (!(p->lo < ig375C0)) {
            p->flags |= 8;
            p->lo = (s32)((f32)ig375C0 - ig37164);
        } else {
            if (p->hi < ig375C0) {
                continue;
            }
            p->flags |= 0x10;
        }
        p->hi = (s32)((f32)ig375C0 + ig37164);
        ig37150 = 1;
    }
    i = 0;
    e = arg0->elems;
    v = 0;
    if (arg0->w * arg0->h > 0) {
    do {
        __asm__("" :: "r"(v));
        __asm__("" :: "r"(v));
        __asm__("" :: "r"(v));
        cp = (u16 *)(i * 2 + (s32)arg0->cells);
        if (e[*cp & 0x1FFF].flags & 0x18) {
            *cp |= 0x2000;
            arg0->cells[i] &= 0x3FFF;
            if (e[arg0->cells[i] & 0x1FFF].flags & 0x10) {
                v++;
            }
        }
        i++;
    } while (i < arg0->w * arg0->h);
    }
    if (v > 0) {
        ig37148[0] = rs_mallocI(v * 25, 0);
        ig37148[1] = rs_mallocI(v * 25, 0);
    }
    zmemcpy(&ig37450, arg0, 0x58);
    ig37450.f0 = (u8 *)ig374B0;
    ig37450.f3A = 4;
    ig37450.f38 = 4;
    ig37450.f4 = ig374D0;
    ig37450.f8 = 0;
    for (j = 0; j < 4; j++) {
        ig37170[j].h18 = j % 2 + 1;
        ig37170[j].h1A = j / 2 + 1;
        ig37170[j].b30 = 0;
        ig37170[j].h12 = 0;
        ig37170[j].h10 = 0;
        ig37170[j].hE = 0;
        ig37170[j].hC = 0;
        ig37170[j].hA = 0;
        ig37170[j].h14 = 0;
        ig37170[j].h1E = 0xFFFF;
    }
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            ig374B0[j * 4 + i] = (j + 1) % 2 * 2 + (i + 1) % 2;
        }
    }
    ig37151 = 0;
    ig37168 = 0;
    {
        f32 z = 0.0f;
        ig37158 = z;
        ig37154 = z;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/463D0", updateGridLayerScroll);

typedef struct { u8 pad[5]; u8 bytes[0x19]; } GridTileEnt;
typedef struct { GridTileEnt e[4]; } GridTileSet;
typedef struct {
    u16 *cells;
    GridTileEnt *tiles;
    u8 pad8[0x30];
    u16 width;
} TerrainGridHdr;
typedef struct {
    u8 pad0[0xA];
    u16 unkA;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    u16 flags;
    u8 pad16[2];
    s16 x;
    s16 y;
    u8 pad1C[0x28];
    u8 *tile;
} SelCell;
typedef struct { u8 pad[0xA]; u16 a; u16 b; u16 c; u16 d; u16 e; u8 pad2[0xB8 - 0x14]; } GridVariantSrc;
#define HDR ((TerrainGridHdr *)&D_main_bss_80136DC0)
extern u8 *D_main_bss_80137148[];
extern u8 D_main_bss_80137151;
extern s32 D_main_bss_80137168;
extern GridVariantSrc D_main_bss_80137170[];
extern GridTileSet D_main_bss_801374D0[];
extern s32 D_main_bss_801375C0;
extern s32 D_main_8009DEC0;

void selectGridCellTileVariant(SelCell *arg0) {
    s32 i = 0;
    s32 q;
    u8 *dst;
    s8 *src;
    s8 *p;
    u8 v;
    GridVariantSrc *vs;
    u8 *alt;

    if (arg0->flags & 0x40) {
        q = ((arg0->y & 1) * 2) + (arg0->x & 1);
        arg0->tile = D_main_bss_801374D0[D_main_bss_80137151].e[q].bytes;
        arg0->tile = D_main_bss_801374D0[D_main_bss_80137151].e[q].bytes;
        arg0->unkA = D_main_bss_80137170[q].a;
        arg0->unkC = D_main_bss_80137170[q].b;
        arg0->unkE = D_main_bss_80137170[q].c;
        arg0->unk10 = D_main_bss_80137170[q].d;
        arg0->unk12 = D_main_bss_80137170[q].e;
        return;
    }
    dst = D_main_bss_80137148[D_main_bss_80137151] + (D_main_bss_80137168 * 0x19);
    src = (s8 *)HDR->tiles[HDR->cells[arg0->x + (arg0->y * HDR->width)] & 0x1FFF].bytes;
    alt = D_main_bss_801374D0[D_main_bss_80137151].e[((arg0->y & 1) * 2) + (arg0->x & 1)].bytes;

    do {
        u8 *d = dst + i;
        if (src[i] < D_main_bss_801375C0) {
            v = src[i];
        } else {
            v = alt[i];
        }
        *d = v;
        i++;

    } while (i < 0x19);
    arg0->tile = dst;
    D_main_bss_80137168++;
    if (D_main_8009DEC0 < D_main_bss_80137168) {
        D_main_8009DEC0 = D_main_bss_80137168;
    }
}

typedef struct { u8 b[4]; } GcCol;
typedef struct { GcCol c[46]; } GcColSet;
extern GcColSet D_main_bss_801371C4[];
typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[2];
    s16 x;
    s16 y;
    u8 pad1C[0x38];
    GcCol label[25];
} LblCell;

u8 *buildGridCellLabel(LblCell *arg0) {
    GcCol *src = D_main_bss_801371C4[((arg0->y & 1) * 2) + (arg0->x & 1)].c;
    u16 w;
    u16 *p;
    u16 cell;
    s8 *h;
    s32 i;

    if (arg0->flags & 0x40) {
        return (u8 *)src;
    }
    w = HDR->width;
    p = HDR->cells;
    cell = p[arg0->x + (arg0->y * w)];
    p = (u16 *)&HDR->tiles[cell & 0x1FFF];
    h = (s8 *)((GridTileEnt *)p)->bytes;
    for (i = 0; i < 0x19; i++) {
        if (h[i] >= D_main_bss_801375C0) {
            arg0->label[i] = *src;
        }
        src++;
    }
    arg0->label[0].b[3] = 1;
    return arg0->label[0].b;
}

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
