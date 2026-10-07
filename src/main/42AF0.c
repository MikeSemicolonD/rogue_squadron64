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

extern s16 D_main_bss_80130D10[];

s32 rasterizeEdgeXSpansDescending(f32 *a, f32 *b, s32 n)
{
  f32 slope;
  s32 y0;
  s32 y1;
  s32 t;
  s32 ret;
  ret = n;
  if (b[2] > a[2])
  {
    y0 = (s32) a[2];
    y1 = (s32) b[2];
    slope = (b[0] - a[0]) / (b[2] - a[2]);
    if (slope < 0.0f)
    {
      if ((n == 0) || (((f32) D_main_bss_80130D10[n]) < a[0]))
      {
        D_main_bss_80130D10[n] = (s32) a[0];
      }
      y0++;
      ret = n;
      if (y1 >= y0)
      {
        do
        {
          n++;
          D_main_bss_80130D10[n] = (s32) (a[0] + ((((f32) y0) - a[2]) * slope));
          y0++;
        }
        while (y1 >= y0);
      }
    }
    else
    {
      if (y0 < y1)
      {
        do
        {
          t = y0 + 1;
          D_main_bss_80130D10[n] = (s32) (a[0] + ((((f32) t) - a[2]) * slope));
          n++;
          y0 = t;
        }
        while (y0 < y1);
      }
      D_main_bss_80130D10[n] = (s32) b[0];
      ret = n;
    }
  }
  return n;
  return ret;
}

INCLUDE_ASM("asm/nonmatchings/main/42AF0", scanConvertTriangleToSpanTable);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", binPolygonIntoTerrainGrid);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", streamTerrainGridCellsByDistance);

typedef struct BgFace {
    struct BgFace *prev;
    struct BgFace *next;
    u8 pad8[8];
    u8 b10;
    u8 b11;
    u8 b12;
    u8 b13;
    u8 b14;
    u8 pad15;
    u16 s16;
    u16 s18;
    u16 s1A;
    u16 s1C;
    u16 s1E;
} BgFace;

typedef struct {
    u8 pad0[0x14];
    u16 flags;
    u8 pad16[0xA];
    BgFace face;
    u8 pad40[0x14];
    u8 c54;
    u8 c55;
    u8 c56;
    u8 pad57[0xD];
    u8 c64;
    u8 c65;
    u8 c66;
    u8 pad67[0x3D];
    u8 cA4;
    u8 cA5;
    u8 cA6;
    u8 padA7[0xD];
    u8 cB4;
    u8 cB5;
    u8 cB6;
} BgCell;

typedef struct BgNode {
    struct BgNode *a;
    struct BgNode *b;
    f32 dist;
    s32 col;
    s32 row;
    BgCell *cell;
} BgNode;

extern f32 D_main_8009DE94[];
extern f32 D_main_8009DEB4;
extern s32 bgSettings[] __asm__("gGameSettings");
extern BgNode *D_main_bss_80132DC0[][64];
extern s32 D_main_bss_80132DB4;
extern s32 D_main_bss_80132DBC;
extern void selectGridCellTileVariant(BgCell *, BgFace *, s32, s32);
extern void buildGridCellMesh(BgCell *);

s32 buildGridCellMeshForFace(BgNode *head, BgFace **out) {
    BgFace *found = NULL;
    BgNode *n;
    BgNode *stop;
    BgNode *o;
    BgFace *face;
    BgFace *of;
    BgCell *c;
    s32 lod;
    s32 count;
    s32 mode;
    s32 row;
    s32 flags;
    f32 t;
    f32 dist;
    f32 f;

    if (head == NULL) {
        return 0;
    }
    lod = 0;
    stop = NULL;
    while (head->dist < D_main_8009DE94[lod + 1]) {
        lod++;
    }
    n = head;
    count = 0;
    while (1) {
        flags = n->cell->flags;
        dist = n->dist;
        face = &n->cell->face;
        while (dist < D_main_8009DE94[lod + 1]) {
            lod++;
            if (lod == 3) {
                stop = n->a;
            }
        }
        switch (lod) {
        case 0:
            count += 1;
            mode = 2;
            t = 0.0f;
            break;
        case 1:
            count += 2;
            mode = 1;
            t = (n->dist - D_main_8009DE94[2]) / (D_main_8009DE94[1] - D_main_8009DE94[2]);
            break;
        case 2:
            count += 2;
            mode = 1;
            t = 0.0f;
            break;
        case 3:
            count += 3;
            mode = 0;
            t = (n->dist - D_main_8009DE94[4]) / (D_main_8009DE94[3] - D_main_8009DE94[4]);
            break;
        default:
            count += 3;
            mode = 0;
            t = 0.0f;
            break;
        }
        if (flags & 8) {
            t = 0.0f;
            mode = 1;
            if (bgSettings[3] & 0x08000000) {
                c = n->cell;
                c->c55 = c->c56 = c->c64 = c->c66 = c->cA4 = c->cA6 = c->cB5 = c->cB6 = 0;
            }
        } else if (flags & 4) {
            mode = 2;
            if (bgSettings[3] & 0x08000000) {
                n->cell->c54 = n->cell->c55 = n->cell->c56 = 0xFF;
                n->cell->c64 = n->cell->c65 = n->cell->c66 = 0;
                n->cell->cA4 = 0xFF;
                n->cell->cA5 = 0xFF;
                n->cell->cA6 = 0;
                n->cell->cB4 = 0xFF;
                n->cell->cB5 = 0;
                n->cell->cB6 = 0xFF;
            }
        }
        face->b14 = mode;
        if (mode == 2) {
            face->b10 = face->b11 = face->b12 = face->b13 = mode;
            face->s16 = face->s18 = face->s1A = face->s1C = face->s1E = 0;
        } else {
            f = t * 65535.0f;
            face->b10 = face->b11 = face->b12 = face->b13 = mode;
            face->s16 = face->s18 = face->s1A = face->s1C = face->s1E = (u32)f;
        }
        if (n->cell->flags & 0xC0) {
            selectGridCellTileVariant(n->cell, face, mode, flags);
        }
        buildGridCellMesh(n->cell);
        if (n->b == NULL) {
            n->cell->face.prev = NULL;
            break;
        }
        n->b->cell->face.next = &n->cell->face;
        n->cell->face.prev = &n->b->cell->face;
        if (found == NULL && n->dist < D_main_8009DEB4) {
            n->b->cell->face.next = NULL;
            n->cell->face.prev = NULL;
            found = &n->b->cell->face;
            *out = found;
        }
        n = n->b;
    }
    if (n != stop) {
        do {
            face = &n->cell->face;
            if (face->b10 == 0) {
                row = n->row;
                lod = n->col;
                if (row > 0 && (o = D_main_bss_80132DC0[row - 1][lod]) != NULL && o->cell->face.b10 == 2) {
                    face->b10 = face->b11 = face->b12 = face->b13 = face->b14 = 1;
                    face->s16 = face->s18 = face->s1A = face->s1C = face->s1E = 0;
                } else if (row < D_main_bss_80132DBC - 1 && (o = D_main_bss_80132DC0[row + 1][lod]) != NULL && o->cell->face.b10 == 2) {
                    face->b10 = face->b11 = face->b12 = face->b13 = face->b14 = 1;
                    face->s16 = face->s18 = face->s1A = face->s1C = face->s1E = 0;
                } else if (lod > 0 && (o = D_main_bss_80132DC0[row][lod - 1]) != NULL && o->cell->face.b10 == 2) {
                    face->b10 = face->b11 = face->b12 = face->b13 = face->b14 = 1;
                    face->s16 = face->s18 = face->s1A = face->s1C = face->s1E = 0;
                } else if (lod < D_main_bss_80132DB4 - 1 && (o = D_main_bss_80132DC0[row][lod + 1]) != NULL && o->cell->face.b10 == 2) {
                    face->b10 = face->b11 = face->b12 = face->b13 = face->b14 = 1;
                    face->s16 = face->s18 = face->s1A = face->s1C = face->s1E = 0;
                }
            }
            n = n->a;
        } while (n != stop);
    }
    n = head;
    if (n != NULL) {
        do {
            lod = n->col;
            face = &n->cell->face;
            row = n->row;
            if (row > 0 && (o = D_main_bss_80132DC0[row - 1][lod]) != NULL) {
                of = &o->cell->face;
                if (of->b10 < face->b10) {
                    of->b14 = face->b13;
                    of->s1E = face->s1C;
                } else {
                    face->b13 = of->b14;
                    face->s1C = of->s1E;
                }
            }
            if (lod > 0 && (o = D_main_bss_80132DC0[row][lod - 1]) != NULL) {
                of = &o->cell->face;
                if (of->b10 < face->b10) {
                    of->b12 = face->b11;
                    of->s1A = face->s18;
                } else {
                    face->b11 = of->b12;
                    face->s18 = of->s1A;
                }
            }
            n = n->b;
        } while (n != NULL);
    }
    head->cell->face.next = NULL;
    return count;
}

typedef struct { f32 x, y, z; } BvV3;
typedef struct { BvV3 cam; BvV3 p[4]; } BvPoly;
typedef struct { f32 m[12]; } BvMat;
extern BvPoly bvPoly __asm__("D_main_bss_80130C10");
extern struct { u8 pad[0x14]; f32 x, y, z; } bvGrid __asm__("D_main_bss_80136DC0");
extern s32 D_main_bss_80137A68[];
extern s32 D_main_bss_8013889C;
extern s32 D_main_bss_80137A60;
extern s32 D_main_bss_80137A74;
extern s32 D_main_bss_80137A50;
extern f32 D_main_bss_80130C50;
extern f32 D_main_8009DEAC;
extern f32 D_main_8009DEB0;
extern void *D_main_bss_80138D1C;
void recycleGridCellToFreeList(void);
f32 sinf(f32);
f32 cosf(f32);
void bvNorm(void *) __asm__("normalize_vector");
void bvXform(void *, void *, void *) __asm__("transformVec3ByMat34");
void bvBin(void *) __asm__("binPolygonIntoTerrainGrid");
BgNode *bvStream(void *, void *) __asm__("streamTerrainGridCellsByDistance");

s32 bvImpl(BvV3 *out, BgFace **faces, f32 fov) __asm__("buildVisibleTerrainGridAroundCamera");
s32 bvImpl(BvV3 *out, BgFace **faces, f32 fov) {
    BvMat m;
    BvV3 d;
    u8 *cam;
    BvMat *cm;
    f32 half;
    f32 a;
    f32 s;
    f32 t;
    s32 sel;
    BgNode *n;

    cam = D_main_bss_80138D1C;
    recycleGridCellToFreeList();
    cm = (BvMat *)(cam + 0x28);
    sel = D_main_bss_80137A68[D_main_bss_8013889C & 1];
    bvPoly.cam.x = (cm->m[9] - bvGrid.x) * 0.5f;
    bvPoly.cam.y = (cm->m[10] - bvGrid.y) * 0.5f;
    D_main_bss_80137A74 = D_main_bss_80137A60;
    bvPoly.cam.z = (cm->m[11] - bvGrid.z) * 0.5f;
    d.x = D_main_bss_80130C50 * -4.0f;
    half = (fov + 4.0f) * 0.5f;
    D_main_bss_80137A50 = sel;
    a = half * 3.1415927f / 180.0f;
    d.y = -3.0f;
    a = sinf(a) / cosf(a);
    d.z = 3.0f / a;
    s = sinf((90.0f - half) * 3.1415927f / 180.0f);
    D_main_8009DEB0 = D_main_8009DEAC * D_main_bss_80130C50 / s;
    bvNorm(&d);
    d.x *= D_main_8009DEB0;
    d.y *= D_main_8009DEB0;
    d.z *= D_main_8009DEB0;
    m = *cm;
    m.m[9] = bvPoly.cam.x;
    m.m[10] = bvPoly.cam.y;
    m.m[11] = bvPoly.cam.z;
    bvXform(&m, &d, &bvPoly.p[0]);
    d.x = -d.x;
    bvXform(&m, &d, &bvPoly.p[1]);
    d.y = -d.y;
    bvXform(&m, &d, &bvPoly.p[2]);
    d.x = -d.x;
    bvXform(&m, &d, &bvPoly.p[3]);
    t = (f32)(s32)(bvPoly.cam.x + bvGrid.x * 0.5f);
    out->x = t + t;
    t = (f32)(s32)(bvPoly.cam.z + bvGrid.z * 0.5f);
    out->z = t + t;
    out->y = bvGrid.y;
    bvBin(&bvPoly);
    n = bvStream(&bvPoly, out);
    if (n == NULL) {
        return 0;
    }
    buildGridCellMeshForFace(n, faces);
    return (s32)&n->cell->face;
}

extern f32 D_main_8003A53C;
__asm__(".section .rodata\n.globl D_main_8003A53C\nD_main_8003A53C:\n.word 0x3F000000\n.section .text");

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

__asm__(".section .rodata\n.globl D_main_8003A540\nD_main_8003A540:\n.word 0x3F000000\n.section .text");

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

typedef struct CaNode {
    struct CaNode *next;
    struct CaNode *prev;
    s32 unk8;
    s32 cb;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad1C[4];
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 pad2C[0x30];
} CaNode;

typedef struct { f32 x, y, z; } CaVec3;

typedef struct CaActor {
    struct CaActor *next;
    struct CaActor *prev;
    s32 unk8;
    s32 unkC;
    CaNode *head;
    s32 unk14;
    u8 pad18[4];
    u8 mat[0x30];
    CaNode a;
    CaNode b;
    s16 npc;
    u8 pad106[2];
    s32 frames;
    CaVec3 dir;
} CaActor;

typedef struct {
    u8 *grid;
    u8 pad4[4];
    CaActor **list;
} CaCtx;

typedef struct {
    s32 unk0;
    u8 *cam;
} CaCam;

extern s32 getLevelCutsceneActorCallbackPrimary(void);
extern s32 getLevelCutsceneActorCallbackSecondary(void);
extern void clearStructPair2C30(CaNode *);
extern void clearVec4QuadStruct(void *);
extern void applyScaleToMat3x4(void *, f32, f32, f32);
extern void initVec4TripletFromArgs(void *, f32, f32, f32);
extern void addVec3At0x24(void *, CaVec3);
extern s32 buildVisibleTerrainGridAroundCamera(CaVec3 *, s32 *, s32);
extern void computeGridLayerScrollOffset(void *);
extern void setViewStateBytesAndFadeScale(u8, u8, u8, f32, f32);
extern void setMissionLevelInitByte(s32);
extern void normalize_vector(CaVec3 *);
extern f32 vec3Dot(CaVec3 *, CaVec3 *);
extern u8 isCameraTransitionIdle();
extern void slotDispatcherIter(u16, s32, void *);
extern void requestViFeatureChange(s32);
extern void beginSceneRenderFrame(s32);
extern s16 spawnNpcOfType(void *, s32, s32, s32);
extern s32 cinematicSplineWalkerNpcHandler;
extern s32 D_8010CA1C;
extern s32 D_main_bss_80130B50;
extern f32 D_main_bss_80136DD0;
extern u8 D_main_bss_80138838;
extern CaCam D_main_bss_80138D18;
extern void *D_main_bss_80138D1C;
extern s32 gCurrentLevel;
extern f32 D_main_8009DEAC;
extern f32 D_main_bss_80136FBC;
extern u8 D_main_bss_80136E18[];
extern u8 D_main_bss_80130B39;
extern s32 D_main_bss_80138898;
extern s32 D_main_bss_80138928;

s32 cutsceneActorNpcHandler(CaActor **self, u16 msg, CaCtx *ctx) {
    CaVec3 ofs;
    CaVec3 v;
    CaActor *s = *(self + 1);
    s32 cnt;
    CaCtx *c;
    u8 go;
    f32 far;
    f32 near;
    CaActor *t;

    switch (msg) {
    case 2:
        break;
    case 1:
        s = (CaActor *)rs_malloc(0x118, 0);
        self[1] = s;
        s->a.next = &s->b;
        s->a.prev = (CaNode *)(s->a.unk8 = 0);
        s->a.cb = getLevelCutsceneActorCallbackPrimary() | 0x80040000;
        s->a.unk14 = s->a.unk18 = s->a.unk10 = 0;
        s->a.unk24 = s->a.unk28 = s->a.unk20 = 0;
        clearStructPair2C30(&s->a);
        s->b.next = 0;
        s->b.prev = &s->a;
        s->b.unk8 = 0;
        s->b.cb = getLevelCutsceneActorCallbackSecondary() | 0x80050000;
        s->b.unk14 = s->b.unk18 = s->b.unk10 = 0;
        s->b.unk24 = s->b.unk28 = s->b.unk20 = 0;
        clearStructPair2C30(&s->b);
        s->next = (CaActor *)(s->prev = (CaActor *)(s->unk8 = s->unkC = 0));
        s->head = &s->a;
        s->unk14 = 0;
        clearVec4QuadStruct(s->mat);
        applyScaleToMat3x4(s->mat, 1.0f, D_main_bss_80136DD0 * 0.0625f, 1.0f);
        s->frames = 0;
        s->npc = spawnNpcOfType(&cinematicSplineWalkerNpcHandler, 0, 4, 100);
        break;
    case 4:
        c = ctx;
        s->b.unk20 = 0;
        if (gCurrentLevel == 0xA) {
            cnt = 0;
            D_main_8009DEAC = 22.0f;
        } else {
            cnt = buildVisibleTerrainGridAroundCamera(&ofs, &s->b.unk20, *(s32 *)(c->grid + 0x20));
        }
        computeGridLayerScrollOffset(c->grid);
        far = *(f32 *)(c->grid + 0x28);
        near = far * D_main_bss_80136FBC;
        setViewStateBytesAndFadeScale(D_main_bss_80136E18[0], D_main_bss_80136E18[1], D_main_bss_80136E18[2], near, 32.0f / (far - near));
        setMissionLevelInitByte(1);
        go = 0;
        if (D_main_bss_80130B39 != 1) {
            if (++s->frames >= 5 && !(D_main_bss_80130B50 & 1) && !(D_8010CA1C & 1)) {
                go = (u8)D_main_bss_80138838 == 0;
            }
        }
        if (go == 1) {
            v.x = *(f32 *)((u8 *)D_main_bss_80138D1C + 0x30);
            v.y = *(f32 *)((u8 *)D_main_bss_80138D1C + 0x3C);
            v.z = *(f32 *)((u8 *)D_main_bss_80138D1C + 0x48);
            normalize_vector(&v);
            if (vec3Dot(&v, &s->dir) >= 0.9999f) {
                D_main_bss_80138898 |= 0x11;
                D_main_bss_80138928 &= ~0x11;
                s->a.cb = (s->a.cb & 0xCFFFFFFF) | 0x30000000;
                s->b.cb = (s->a.cb & 0xCFFFFFFF) | 0x30000000;
            } else {
                D_main_bss_80138928 |= 0x11;
                D_main_bss_80138898 &= ~0x11;
                s->a.cb &= 0xCFFFFFFF;
                s->b.cb &= 0xCFFFFFFF;
            }
            if (D_main_bss_80130B39 == 0 && !(D_main_bss_80138898 & 1) && !isCameraTransitionIdle()) {
                D_main_bss_80138898 |= 0x11;
                D_main_bss_80138928 &= ~0x11;
            }
        }
        s->dir.x = *(f32 *)(D_main_bss_80138D18.cam + 0x30);
        s->dir.y = *(f32 *)(D_main_bss_80138D18.cam + 0x3C);
        s->dir.z = *(f32 *)(D_main_bss_80138D18.cam + 0x48);
        normalize_vector(&s->dir);
        if (cnt != 0) {
            *(s32 *)((u8 *)s + 0x6C) = cnt;
            initVec4TripletFromArgs(s->mat, 1.0f, D_main_bss_80136DD0 * 0.0625f, 1.0f);
            addVec3At0x24(s->mat, ofs);
            t = *c->list;
            s->next = t;
            if (t != 0) {
                t->prev = s;
            }
            *c->list = s;
            s->prev = 0;
        }
        if (D_main_bss_80130B39 != 1 || gCurrentLevel != 0x13) {
            slotDispatcherIter(s->npc, 4, c);
        }
        requestViFeatureChange(D_main_bss_80138898);
        beginSceneRenderFrame(D_main_bss_80138928);
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/42AF0", computeGridTileEdgeAdjacencyMasks);

extern f32 D_main_8009DEAC;
extern u8 D_main_bss_80130B39;
extern s16 D_main_bss_80130C4C;
extern f32 D_main_bss_80130C50;
extern f32 D_main_bss_80130C54;
extern f32 D_main_bss_80130C58;
extern f32 D_main_bss_80130C5C;
extern f32 D_main_bss_80130C60;
extern u8 D_main_bss_80136E18[];
extern u8 D_main_bss_80136F80[];
extern f32 D_main_bss_80136FAC;
extern f32 D_main_bss_80136FBC;
extern s32 D_main_bss_80138898;
extern s32 D_main_bss_80138928;
extern s32 hmpFile;
extern s32 gCurrentLevel;
extern s32 D_main_bss_80136E1C;
void sprintf(char *, void *, ...);
void allocAndInitGridCellArray(s32);
void load_level_hmp(s32, void *, void *);
void loadDatFile(void *);
void load_full_header_image(void *);
void initGridLayerFromLevelData(void *, u16);
void copyLevelConfigColorTriple(void *);
void setFrameLevelStateBytes(u8, u8, u8);
void setMissionLevelInitByte(s32);
void computeGridTileEdgeAdjacencyMasks(s32);

void loadLevelAssets(s32 arg0) {
    char sp10[0x28];
    f32 fa;
    f32 fb;

    D_main_bss_80130C4C = arg0;
    sprintf((char *)D_main_bss_80136F80, "level/lv_%c", gCurrentLevel < 0xA ? gCurrentLevel + 0x30 : gCurrentLevel + 0x57);
    hmpFile = 0;
    if (gCurrentLevel != 0xA) {
        allocAndInitGridCellArray(arg0);
        D_main_bss_80136E1C = rs_malloc(arg0 * 0x18, 0);
    }
    load_level_hmp(0, D_main_bss_80136F80, D_main_bss_80136F80);
    loadDatFile(D_main_bss_80136F80);
    sprintf(sp10, "%s/ref_TM", D_main_bss_80136F80);
    load_full_header_image(sp10);
    initGridLayerFromLevelData(&D_main_bss_80136DC0, *(u16 *)(hmpFile + 0x18));
    D_main_bss_80136FBC = 0.9f;
    if (gCurrentLevel == 2) {
        D_main_bss_80136FBC = 0.3f;
    }
    D_main_bss_80136FAC = 5.0f;
    copyLevelConfigColorTriple(D_main_bss_80136E18);
    setFrameLevelStateBytes(D_main_bss_80136E18[0], D_main_bss_80136E18[1], D_main_bss_80136E18[2]);
    setMissionLevelInitByte(1);
    fa = 2.0f;
    D_main_bss_80130C54 = 16.0f;
    D_main_bss_80130C58 = 24.0f;
    D_main_8009DEAC = 16.0f;
    if (gCurrentLevel == 0xC) {
        fa = -2.0f;
    }
    fb = -8.0f;
    D_main_bss_80130C5C = fa;
    if (gCurrentLevel == 0xC) {
        fb = -20.0f;
    }
    D_main_bss_80130C60 = fb;
    D_main_bss_80130C50 = 1.0f;
    if (D_main_bss_80130B39 == 0 && gCurrentLevel != 0x11) {
        computeGridTileEdgeAdjacencyMasks(gCurrentLevel);
    }
    D_main_bss_80138928 = 0;
    D_main_bss_80138898 = 0;
}

extern f32 D_main_8009DEB4;
extern void *D_main_bss_80138D1C;

void computeGridLayerScrollOffset(void *arg0) {
    f32 temp_ft0;
    f32 temp_fv1;
    f32 var_fv0;

    temp_fv1 = (*(f32 *)((u8 *)(D_main_bss_80138D1C) + 0x50));
    if ((D_main_bss_80130C5C < temp_fv1) || (D_main_bss_80130C5C <= D_main_bss_80130C60)) {
        var_fv0 = D_main_bss_80130C54;
        goto block_5;
    }
    if (temp_fv1 < D_main_bss_80130C60) {
        var_fv0 = D_main_bss_80130C58;
block_5:
        D_main_8009DEAC = var_fv0;
    } else {
        D_main_8009DEAC = D_main_bss_80130C54 + (((D_main_bss_80130C58 - D_main_bss_80130C54) * (temp_fv1 - D_main_bss_80130C5C)) / (D_main_bss_80130C60 - D_main_bss_80130C5C));
    }
    if (gCurrentLevel == 0xA) {
        D_main_8009DEAC = 22.0f;
    }
    if ((gCurrentLevel == 2) || (gCurrentLevel == 0x13)) {
        D_main_8009DEB4 = 0.0f;
    } else {
        temp_ft0 = D_main_bss_80136FBC * 0.7f;
        D_main_8009DEB4 = temp_ft0;
        D_main_8009DEB4 = temp_ft0 * temp_ft0 * D_main_8009DEAC * D_main_8009DEAC;
    }
    (*(f32 *)((u8 *)(arg0) + 0x28)) = (f32) (2.0f * ((D_main_8009DEAC - (D_main_8009DEAC * 0.25f)) + 1.0f));
}

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
