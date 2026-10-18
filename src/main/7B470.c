#include "common.h"
#include "common_types.h"
#include "rs_math.h"

void *rs_malloc(s32, s32);

void allocateNpcMeshVertexBuffer(u8 *arg0, u8 *arg1)
{
  u8 *mesh;
  u8 *list;
  u8 *e;
  void **out;
  u32 vi;
  s32 j;
  u16 *ids;
  s32 k;
  u8 *p;
  mesh = *((u8 **) ((*((u8 **) (arg1 + 0x1C))) + 8));
  *((u8 **) (arg0 + 4)) = mesh;
  list = *((u8 **) ((*((u8 **) ((*((u8 **) (arg1 + 0x1C))) + 8))) + 0x20));
  out = rs_malloc(((*((s32 *) (mesh + 0x14))) + ((*((s32 *) (list + 0xC))) * 4)) * 4, 0);
  *((void ***) arg0) = out;
  vi = 0;
  if ((*((s32 *) (mesh + 0x14))) != 0)
  {
    do
    {
      k = *((s32 *) (list + 0xC));
      e = *((u8 **) (list + 8));
      if (k > 0)
      {
        do
        {
          if (((*((u32 *) e)) & 0x18) == 0x18)
          {
            j = 0;
            ids = (u16 *) (e + (((*((u32 *) (e + 4))) & 0xFC0000) >> 16));
            do
            {
              if ((*ids) == vi)
              {
                *out = (e + (((*((u32 *) (e + 4))) & 0x3F000) >> 10)) + (j * 4);
                out++;
              }
              j++;
              ids++;
            }
            while (j < 4);
          }
          k--;
          e += ((*((u32 *) (e + 4))) & 0x3F000000) >> 22;
        }
        while (k > 0);
      }
      *out = 0;
      out++;
      vi++;
    }
    while (vi < (*((u32 *) (mesh + 0x14))));
  }
  k = 3;
  p = arg0 + 0xB4;
  do
  {
    *((u16 *) (p + 0x28)) = 0;
    k--;
    p -= 0x3C;
  }
  while (k >= 0);
  *((u32 *) (mesh + 0xC)) |= 0x09010008;
}

typedef struct {
    u8 col[4];
    f32 k[4];
    f32 f14;
    s16 h18, h1A, h1C;
    u16 h1E;
    u16 fl;
    u8 pad22[0x1A];
} TmLight;
typedef struct {
    u8 pad0[0xC];
    u32 flags;
    u8 pad10[4];
    s32 count;
    u8 pad18[0xC];
    s16 *verts;
} TmMesh;
typedef struct {
    u32 **dst;
    TmMesh *mesh;
    TmLight lights[4];
} TmObj;

void tmImpl(TmObj *o) __asm__("transformMeshVerticesForNpc");
void tmImpl(TmObj *o) {
    u32 **dst;
    s32 n;
    s16 *v;
    s32 i;
    f32 r, g, b;
    register f32 a asm("$f12");
    f32 d;
    f32 c;
    u32 col;
    TmLight *L;

    dst = o->dst;
    n = o->mesh->count;
    v = o->mesh->verts;
    for (; n > 0; ) {
        a = 0.0f;
        b = a;
        g = a;
        r = a;
        for (i = 0, L = o->lights; i < 4; L++, i++) {
            if (L->fl == 0) {
                continue;
            }
            if (L->fl & 2) {
                s32 x = v[0];
                s32 z = v[2];
                d = sqrtfInline((f32)(x * x + z * z));
                if (0.0f < d) {
                    d = (f32)(L->h18 * x + L->h1C * z) * 256.0f / d;
                }
            } else if (L->fl & 4) {
                s32 y = v[1];
                s32 k = L->h1A;
                s32 t;
                if (y < k) {
                    t = k - y;
                } else {
                    t = y - k;
                }
                d = (256.0f - (f32)t) * 256.0f;
            } else {
                d = (f32)(L->h18 * v[0] + L->h1A * v[1] + L->h1C * v[2]);
            }
            d -= L->f14;
            if (d <= 0.0f) {
                continue;
            }
            d = d / (65536.0f - L->f14);
            r += L->col[0] + L->k[0] * d;
            g += L->col[1] + L->k[1] * d;
            b += L->col[2] + L->k[2] * d;
            a += L->col[3] + L->k[3] * d;
            __asm__("" :: "i"(0));
            __asm__("" :: "i"(0));
            __asm__("" :: "i"(0));
        }
        c = (r < 0.0f) ? 0.0f : ((255.0f < r) ? 255.0f : r);
        r = c;
        c = (g < 0.0f) ? 0.0f : ((255.0f < g) ? 255.0f : g);
        g = c;
        c = (b < 0.0f) ? 0.0f : ((255.0f < b) ? 255.0f : b);
        b = c;
        c = (a < 0.0f) ? 0.0f : ((255.0f < a) ? 255.0f : a);
        col = ((s32)r << 24) | ((s32)g << 16) | ((s32)b << 8) | (s32)c;
        while (*dst != NULL) {
            **dst = col;
            dst++;
        }
        n--;
        v += 4;
        dst++;
    }
    o->mesh->flags |= 0x20;
    o->mesh->flags &= ~0x180;
}

extern void buildRotationMatrixSlot0(f32 *, f32);
extern void composeRotationMatrixSlot1(f32 *, f32);
extern void composeRotationMatrixSlot2(f32 *, f32);
extern void rotateVec3ByMat3x3(f32 *, f32 *, f32 *);
extern f32 sinf(f32);

#define F32(p, o) (*(f32 *)((p) + (o)))
#define S16(p, o) (*(s16 *)((p) + (o)))

void npcDeformingMeshUpdate(u8 *arg0, f32 dt) {
    f32 m[12];
    f32 v[3];
    f32 o[3];
    f32 len;
    f32 zero = 0.0f;
    u8 *p;
    u8 *base;
    s32 i;

    base = arg0 + 0x28;
    for (i = 0; i < 4; i++) {
        p = base + i * 0x3C;
        if (*(u16 *)p != 0) {
            F32(p, 0x10) += F32(p, 0x14) * dt;
            if (F32(p, 0x10) < 1.0f) {
                buildRotationMatrixSlot0(m, F32(p, 4) * dt);
                if (F32(p, 8) != zero) {
                    composeRotationMatrixSlot1(m, F32(p, 8) * dt);
                }
                if (F32(p, 0xC) != zero) {
                    composeRotationMatrixSlot2(m, F32(p, 0xC) * dt);
                }
                v[0] = S16(p, -8);
                v[1] = S16(p, -6);
                v[2] = S16(p, -4);
                rotateVec3ByMat3x3(m, v, o);
                {
                    f32 a = o[0];
                    SQRTF(len, a * a + o[1] * o[1] + o[2] * o[2]);
                    len = len * 0.00390625f;
                    if (zero < len) {
                        S16(p, -8) = a / len;
                        S16(p, -6) = o[1] / len;
                        S16(p, -4) = o[2] / len;
                    }
                }
                F32(p, -0x10) = F32(p, 0x18) * sinf(F32(p, 0x10) * 3.1415927f);
            } else {
                *(u16 *)p = 0;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/7B470", npcShieldUpdate);

typedef struct {
    u8 r, g, b, a;
    f32 dr;
    f32 dg;
    f32 db;
    f32 unk10;
    f32 unk14;
    s16 v[3];
    u16 pad1E;
    u16 active;
    u16 pad22;
    f32 rx;
    f32 ry;
    f32 rz;
    f32 t;
    f32 speed;
    f32 amp;
} HaSlot;

typedef struct { u32 w[12]; } HaBlk48;
typedef struct { f32 x, y, z; } HaV3;
typedef struct { u8 pad0[0xC]; u8 *next; u8 *prev; } HaMesh;

typedef struct {
    u8 pad0[0xC];
    u16 listA;
    u8 padE[0x1C - 0xE];
    u16 listB;
} HaLists;

extern HaLists D_main_bss_80139560;
extern f32 D_main_800A0D80;
extern u8 D_main_800A0D84[];
extern u8 D_main_800A0D88[];
extern void *D_main_bss_8013A970;

extern void rs_free(void *);
extern void releaseMeshAsset(void *);
extern void *getNpcContextField8(u16);
extern void mat34CrossRowsAndCopyPos(void *, void *, f32);
extern void mat3x3InverseInto(void *, void *);
extern void transformVec3ByMat34(void *, void *, void *);
extern void popNpcSlotFromTail(u16, void *);
extern u8 *walkMeshdef0List(s32);
extern void mat3x4Multiply(void *, void *, void *);
extern void extractOrthonormalFrameFromStruct(void *, void *);
extern void mat34CrossRowsAndCopyPosPtr(void *, void *, void *);
extern f32 normalize_vector(void *);
extern s16 rand(void);
extern void buildRotationMatrixSlot1(void *, f32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void destroyNpcSlotByIndex(u16);
extern void spawnRandomScaleColoredEffectFromCaller(void *, f32, f32, void *);
extern s32 checkAndReturnByteFlagAsU8(void *, void *, void *, f32);
extern void transformMeshVerticesForNpc(void *);

s32 heavyAttachedAudioEmitterNpcHandler(u8 *npc, u16 msg, u8 *arg) {
    f32 m28[12];
    f32 inv58[12];
    f32 rel[3];
    f32 mm[12];
    f32 mC8[12];
    f32 mF8[12];
    f32 m128[12];
    f32 v158[3];
    f32 m168[12];
    u8 *d;

    d = *(u8 **)(npc + 4);
    switch (msg) {
    case 1: {
        u8 *a = arg;
        f32 one;
        f32 inv;
        f32 c;
        f32 m;
        u8 *ctx;

        d = rs_malloc(0x180, 0);
        *(u8 **)(npc + 4) = d;
        *(u8 **)(npc + 8) = d + 8;
        *(HaBlk48 *)(d + 8) = *(HaBlk48 *)a;
        d[0x17C] = 0;
        *(u8 **)d = walkMeshdef0List(*(s32 *)(a + 0x40));
        *(u8 **)(npc + 0xC) = *(u8 **)d;
        allocateNpcMeshVertexBuffer(d + 0x38, *(u8 **)d);
        *(s32 *)(**(u8 ***)d + 0x58) = 0;
        one = 1.0f;
        inv = one / *(f32 *)(**(u8 ***)d + 0x34);
        *(f32 *)(d + 0x13C) = inv * *(f32 *)(a + 0x30);
        *(f32 *)(d + 0x140) = inv * *(f32 *)(a + 0x34);
        *(f32 *)(d + 0x144) = inv * *(f32 *)(a + 0x38);
        inv = *(f32 *)(d + 0x13C);
        if (inv < *(f32 *)(d + 0x140)) {
            inv = *(f32 *)(d + 0x140);
        }
        if (inv < *(f32 *)(d + 0x144)) {
            inv = *(f32 *)(d + 0x144);
        }
        *(f32 *)(d + 0x138) = *(f32 *)(**(u8 ***)d + 0x44) * inv;
        popNpcSlotFromTail(D_main_bss_80139560.listA, npc);
        popNpcSlotFromTail(D_main_bss_80139560.listB, npc);
        *(u16 *)(d + 0x178) = *(u16 *)(a + 0x3C);
        ctx = getNpcContextField8(*(u16 *)(a + 0x3C));
        mat34CrossRowsAndCopyPos(m28, ctx, one);
        m28[9] = m28[10] = m28[11] = 0.0f;
        mat3x3InverseInto(inv58, m28);
        rel[0] = *(f32 *)(d + 8) - *(f32 *)(ctx + 0);
        rel[1] = *(f32 *)(d + 0xC) - *(f32 *)(ctx + 4);
        rel[2] = *(f32 *)(d + 0x10) - *(f32 *)(ctx + 8);
        transformVec3ByMat34(inv58, rel, &mm[0]);
        transformVec3ByMat34(inv58, d + 0x14, &mm[3]);
        transformVec3ByMat34(inv58, d + 0x20, &mm[6]);
        mat34CrossRowsAndCopyPos(d + 0x148, mm, one);
        break;
    }
    case 2:
        rs_free(*(void **)(d + 0x38));
        releaseMeshAsset(*(void **)d);
        break;
    case 3: {
        f32 dt = *(f32 *)arg;
        u8 *ctx = getNpcContextField8(*(u16 *)(d + 0x178));

        mat34CrossRowsAndCopyPos(mC8, ctx, 1.0f);
        mat3x4Multiply(mC8, d + 0x148, mF8);
        extractOrthonormalFrameFromStruct(d + 8, mF8);
        *(HaV3 *)(d + 0x2C) = *(HaV3 *)(ctx + 0x24);
        npcDeformingMeshUpdate(d + 0x38, dt);
        break;
    }
    case 4: {
        u8 *a = arg;
        s32 i;
        u8 *p;
        HaMesh *mesh;

        for (i = 0, p = d; i < 4; i++, p += 0x3C) {
            if (*(u16 *)(p + 0x60) != 0) {
                break;
            }
        }
        if (i < 4 && checkAndReturnByteFlagAsU8(*(void **)a, *(void **)d, d + 8, *(f32 *)(d + 0x138))) {
            mat34CrossRowsAndCopyPosPtr(*(u8 **)d + 0x28, d + 8, d + 0x13C);
            transformMeshVerticesForNpc(d + 0x38);
            mesh = *(HaMesh **)d;
            do {
                if ((mesh->next = **(u8 ***)a) != NULL) {
                    *(u8 **)(*(u8 **)(*(u8 **)d + 0xC) + 4) = *(u8 **)d + 0xC;
                }
                *(s32 *)(*(u8 **)d + 0x10) = 0;
                **(u8 ***)a = *(u8 **)d + 0xC;
            } while (0);
        }
        break;
    }
    case 5: {
        u8 *a = arg;
        s32 ci;

        if (*(u16 *)(a + 4) != 7 && (ci = 0xC, *(void **)(a + 8) != NULL)) {
            u8 *col;
            HaSlot *s;
            u8 *base;
            s32 i;

            switch (*(u16 *)(a + 4)) {
            case 0:
            case 1:
            case 3:
            case 5:
            case 6:
                col = D_main_800A0D84;
                break;
            case 2:
            case 4:
                col = D_main_800A0D88;
                ci = 0xE;
                break;
            default:
                col = NULL;
                break;
            }
            spawnRandomScaleColoredEffectFromCaller(*(void **)(a + 8), 0.2f, 1.4f, col);
            play3DSoundEvent(0, d + 8, d + 0x2C, 16.0f, 0.8f, 0, 0xC, 0x7F, 0x50);
            base = d + 0x38;
            for (i = 0; i < 4; i++) {
                if (*(u16 *)(base + i * 0x3C + 0x28) == 0) {
                    s = (HaSlot *)&base[i * 0x3C + 8];
                    goto found;
                }
            }
            s = NULL;
        found:
            if (s != NULL) {
                u8 *pal;

                mat3x3InverseInto(m128, *(u8 **)d + 0x28);
                rotateVec3ByMat3x3(m128, *(u8 **)(a + 8) + 0xC, v158);
                normalize_vector(v158);
                pal = (u8 *)(ci * 4 + (s32)D_main_bss_8013A970);
                buildRotationMatrixSlot1(m168, rand());
                rand();
                s->v[0] = m168[0] * 256.0f;
                s->v[0] = m168[3] * 256.0f;
                s->v[0] = m168[6] * 256.0f;
                s->r = pal[0];
                s->g = pal[1];
                s->b = pal[2];
                s->a = 0;
                s->dr = pal[4] - pal[0];
                s->dg = pal[5] - pal[1];
                s->db = pal[6] - pal[2];
                s->unk10 = 255.0f;
                s->unk14 = 0.0f;
                s->active = 1;
                s->rx = 0.0f;
                s->speed = 1.0f;
                s->ry = 0.0f;
                s->amp = 128.0f;
                s->rz = 0.0f;
                s->t = 0.0f;
                s->unk14 = D_main_800A0D80;
                s->v[0] = v158[0] * -256.0f;
                s->v[1] = v158[1] * -256.0f;
                s->v[2] = v158[2] * -256.0f;
                /*E*/
            }
        }
        if (*(u16 *)a != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)a);
        }
        break;
    }
    }
    return 1;
}

extern void *D_main_bss_8013A970;
static const char D_main_8003D624[12] = "shield_PAL\0000";
void loadShieldPalette(void) {
    D_main_bss_8013A970 = load_asset((char *)D_main_8003D624);
}

INCLUDE_ASM("asm/nonmatchings/main/7B470", fake_func_8007C298);
