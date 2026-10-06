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

INCLUDE_ASM("asm/nonmatchings/main/42AF0", buildGridCellMeshForFace);

INCLUDE_ASM("asm/nonmatchings/main/42AF0", buildVisibleTerrainGridAroundCamera);

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
