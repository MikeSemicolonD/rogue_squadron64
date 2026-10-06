#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/48A50", allocAndInitGridCellArray);

INCLUDE_ASM("asm/nonmatchings/main/48A50", loadLevelTextureCache);

typedef struct {
    u16 f0;
    u16 f2;
    u8 pad4[8];
} GridCellB2;
extern s32 D_main_bss_80137A44;
extern u16 D_main_bss_80137A46;
extern GridCellB2 *D_main_bss_80137614_b __asm__("D_main_bss_80137614");

void buildGridCellAdjacencyTable(void) {
    s32 i;
    GridCellB2 *c;

    for (i = 5; i < D_main_bss_80137A44; i++) {
        D_main_bss_80137614_b[i].f0 = i - 1;
        D_main_bss_80137614_b[i].f2 = i + 1;
    }
    c = D_main_bss_80137614_b;
    c[5].f0 = 3;
    c[D_main_bss_80137A44 - 1].f2 = 4;
    for (i = 0; i < 3; i++) {
        c[i].f2 = 0xFFFF;
        c[i].f0 = 0xFFFF;
    }
    D_main_bss_80137614_b[3].f0 = 0xFFFF;
    D_main_bss_80137614_b[3].f2 = 5;
    D_main_bss_80137614_b[4].f0 = D_main_bss_80137A46 - 1;
    D_main_bss_80137614_b[4].f2 = 0xFFFF;
}

typedef struct {
    u16 *tbl0;
    u8 *tbl4;
    u16 *tbl8;
    s32 padC;
    f32 f10;
    u8 pad14[0x24];
    u16 w;
    u16 h;
} GridDescG;

typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA[5];
    u16 f14;
    u16 f16;
    s16 f18;
    s16 f1A;
    u8 pad1C[2];
    u16 f1E;
    u8 pad20[0x30];
    f32 f50;
    u8 pad54[0x64];
} GridCellG;

typedef struct {
    u16 prev;
    u16 next;
    s32 f4;
    GridCellG *f8;
} PoolG;

extern GridDescG gGridG __asm__("D_main_bss_80136DC0");
extern GridCellG *gCellsG __asm__("D_main_bss_80137A5C");
extern PoolG *gPoolG __asm__("gDoublyLinkedNodePool12");
extern u16 gFreeHeadG __asm__("D_main_bss_80136FC0");
extern u16 gFreeCntG __asm__("D_main_bss_80137A58");
extern u16 *gFreeListG __asm__("D_main_bss_80137A4C");
extern GridCellG *clampGridCellLookup(s32, s32);

GridCellG *getGridCellValueAt(s32 x, s32 y, s32 flag)
{
  s32 idx;
  s32 v;
  GridCellG *c;
  GridCellG *base;
  u16 head;
  u16 a;
  u8 *t;
  GridCellG *r;
  if ((((x < 0) || (x >= gGridG.w)) || (y < 0)) || (y >= gGridG.h))
  {
    return clampGridCellLookup(x, y);
  }
  idx = x + (y * gGridG.w);
  head = gGridG.tbl8[idx];
  v = head;
  if (v != 0xFFFF)
  {
    if ((head & 0x8000) && flag)
    {
      return gPoolG[v & 0x7FFF].f8;
    }
  }
  if ((gGridG.tbl0[idx] & 0x1FFF) == 0xFFFF)
  {
    return 0;
  }
  base = gCellsG;
  c = &base[*((u16 *) (((u8 *) base) + 0x22A))];
  while (c->f6 != 0xFFFF)
  {
    if (c->f8 != 0xFFFF) break;
    c = &gCellsG[c->f2];
  }
  if ((c->f16 == 4) || (gFreeHeadG == 0xFFFF))
  {
    return 0;
  }
  head = c->f1E;
  if (head != 0xFFFF)
  {
    if (c->f14 & 0x20)
    {
      {
        s32 p = c->f4;
        if (p != 0xFFFF)
        {
          gCellsG[p].f6 = c->f6;
        }
      }
      {
        s32 p = c->f6;
        if (p != 0xFFFF)
        {
          gCellsG[p].f4 = c->f4;
        }
      }
      head = 0;
      do
      {
        c->fA[head] = 0;
        head++;
      }
      while ((head) < 5);
    }
    else
    {
      PoolG *pb = gPoolG;
      PoolG *n = (PoolG *)(head * sizeof(PoolG) + (s32)pb);
      if (n->prev != 0xFFFF)
      {
        gPoolG[n->prev].next = n->next;
      }
      else
      {
        gGridG.tbl8[c->f18 + (c->f1A * gGridG.w)] = n->next;
      }
      {
      s32 hh = head;
      PoolG *pb2 = gPoolG;
      PoolG *m = (PoolG *)(hh * sizeof(PoolG) + (s32)pb2);
      if (m->next != 0xFFFF)
      {
        gPoolG[m->next].prev = m->prev;
      }
      }
      gPoolG[gFreeHeadG].prev = head;
      gPoolG[head].next = gFreeHeadG;
      gFreeHeadG = head;
      if (!(c->f14 & 0x40))
      {
        head = 0;
        if (c->fA[0] != 0)
        {
          while (1)
          {
            if (head >= 5) break;
            gFreeListG[gFreeCntG++] = c->fA[head];
            c->fA[head] = 0;
            head++;
            if (c->fA[head] == 0) goto done;
          }
        }
      }
      else
      {
        head = 0;
        do
        {
          c->fA[head] = 0;
          head++;
        }
        while ((head) < 5);
      }
    }
    done:
    c->f1E = 0xFFFF;
  }
  c->f18 = x;
  c->f1A = y;
  t = gGridG.tbl4 + ((gGridG.tbl0[idx] & 0x1FFF) * 0x1E);
  {
    s32 lo = ((s8 *) t)[3];
    s32 hi = ((s8 *) t)[4];
    f32 fv = (((((f32) lo) + (((f32) (hi - lo)) * 0.5f)) * gGridG.f10) * 0.00390625f) * 0.5f;
    r = c;
    r->f14 = 3;
    r->f50 = fv;
  }
  return r;
}

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
