#include "common.h"
#include "common_types.h"

typedef struct { u16 *data; u8 *tbl; u8 pad8[0x30]; u16 w; u16 h; } RadarGridC;
extern RadarGridC gRadarGridC __asm__("D_main_bss_80136DC0");
extern u16 D_main_bss_80136DF8;

s32 plotRadarBlipColumn(void *arg0v, s32 y) {
    u8 *arg0 = arg0v;
    s32 x;
    s32 xe;
    s32 h1;
    s32 off;
    s32 lo;
    u8 *col;
    u16 *p;
    u8 *tbl;
    u8 *a0;
    u8 *a1;

    x = *(s16 *)(arg0 + 0x85E) - 0x10;
    xe = *(s16 *)(arg0 + 0x85E) + 0x10;
    h1 = gRadarGridC.h - 1;
    col = arg0 + (y & 0x1F);
    if (y < 0) {
        p = gRadarGridC.data;
    } else {
        if (y >= gRadarGridC.w) {
            p = (u16 *)((u8 *)gRadarGridC.data + (gRadarGridC.w * 2 - 2));
        } else {
            p = (u16 *)((u8 *)gRadarGridC.data + y * 2);
        }
    }
    if (x > 0) {
        if (h1 >= x) {
            p += x * D_main_bss_80136DF8;
        } else {
            p += h1 * D_main_bss_80136DF8;
        }
    }
    tbl = gRadarGridC.tbl;
    if (x < xe) {
        do {
            a0 = tbl + (*p & 0x1FFF) * 0x1E;
            a1 = col + ((x & 0x1F) << 6);
            a1[0] = ((((s8)a0[5] + 0x80) * 0x10) / 22 & ~0xF) | ((u32)((a0[7] - 0x80) & 0xFF) / 22);
            x++;
            a1[0x20] = ((((s8)a0[0xF] + 0x80) * 0x10) / 22 & ~0xF) | ((u32)((a0[0x11] - 0x80) & 0xFF) / 22);
            if (x > 0 && x < h1) {
                p += gRadarGridC.w;
            }
        } while (x < xe);
    }
}

typedef struct { u16 *data; u8 pad4[0x34]; u16 w; u16 h; } RadarGridR;
extern RadarGridR D_main_bss_80136DC0;
extern u8 *D_main_bss_80136DC4;

void plotRadarBlipRow(u8 *arg0, s32 y) {
    s32 x;
    s32 xe;
    s32 w1;
    s32 lo;
    s32 off;
    u8 *row;
    u16 *p;
    u8 *tbl;
    u8 *a0;
    u8 *a1;

    x = *(s16 *)(arg0 + 0x85C) - 0x10;
    xe = *(s16 *)(arg0 + 0x85C) + 0x10;
    w1 = D_main_bss_80136DC0.w - 1;
    row = arg0 + ((y & 0x1F) << 6);
    if (y < 0) {
        p = D_main_bss_80136DC0.data;
    } else {
        if (y < D_main_bss_80136DC0.h) {
            p = D_main_bss_80136DC0.data + y * D_main_bss_80136DC0.w;
        } else {
            p = D_main_bss_80136DC0.data + (D_main_bss_80136DC0.h - 1) * D_main_bss_80136DC0.w;
        }
    }
    if (x > 0) {
        if (w1 >= x) {
            p += x;
        } else {
            p += w1;
        }
    }
    tbl = D_main_bss_80136DC4;
    if (x < xe) {
        do {
            a0 = tbl + (*p & 0x1FFF) * 0x1E;
            a1 = row + (x & 0x1F);
            a1[0] = ((((s8)a0[5] + 0x80) * 0x10) / 22 & ~0xF) | ((u32)((a0[7] - 0x80) & 0xFF) / 22);
            x++;
            a1[0x20] = ((((s8)a0[0xF] + 0x80) * 0x10) / 22 & ~0xF) | ((u32)((a0[0x11] - 0x80) & 0xFF) / 22);
            if (x > 0 && x < w1) {
                p++;
            }
        } while (x < xe);
    }
}

typedef struct { s16 x, y, z, w; } RdPt;
typedef RdPt RdPt8[8];
typedef struct { u8 pad[8]; u32 *p8; u32 nC; } RdHdr;
typedef struct { u8 pad[0x20]; RdHdr *hdr; RdPt *pts; } RdNode;
typedef struct {
    u32 w0;
    s32 w4;
    s32 w8;
    s16 hC;
    s16 hE;
    s16 h10;
    s16 h12;
    s16 h14;
    s16 h16;
    s16 h18;
    s16 h1A;
    s16 h1C;
    s16 h1E;
    u8 b20, b21, b22, b23;
} RdEnt;
typedef struct { u8 pad[0x9F8]; RdEnt ents[16]; } RdState;
extern void *D_mission_overlay_8010BFE0;
extern u32 D_mission_overlay_8010CA1C;
extern s32 rdLevel __asm__("gCurrentLevel");
extern u8 D_mission_overlay_80109FF8[];
extern u8 D_mission_overlay_8010A028[];
extern u8 D_mission_overlay_8010A058[];
u8 *rdMalloc(u32, u16) __asm__("rs_malloc");
s32 plotRadarBlipColumn(void *, s32);
u16 rdRegTex(void *, void *, s32) __asm__("registerHmtTextureInTable");
u16 rdLoad(char *, s32, s32) __asm__("loadAndRelocateAsset");
void rdClear(void *) __asm__("clearStructPair2C30");
RdNode **rdFind(char *) __asm__("findNamedEntryInCurrentObject");
void rdNorm(f32 *) __asm__("normalize_vector");
f32 rdAtan2(f32, f32) __asm__("atan2Approx");
f32 sinf(f32);
f32 cosf(f32);
void rdInit4(void *, f32, f32, f32) __asm__("initVec4TripletFromArgs");
void rdAdd24(void *, f32, f32, f32) __asm__("addVec3At0x24");

#define RF(T, o) (((struct { u8 p[o]; T v; } *)r)->v)
typedef struct { s32 w[2]; s16 h; s8 b; } RdStr;
u8 *initializeRadar(void **out, void **out2) {
    f32 v[3];
    f32 c[3];
    f32 d[3];
    RdPt tmp;
    f32 angs[8];
    u8 *r;
    s32 i;
    RdEnt *e;
    RdNode **obj;
    u32 k;
    u32 sel;
    u32 cnt;
    u32 m2;
    u32 j;
    f32 best;
    f32 dist;
    f32 a;
    f32 ang;
    u8 *m;

    D_mission_overlay_8010BFE0 = r = rdMalloc(0xDD4, 0);
    RF(s16, 0x85E) = 0;
    RF(s16, 0x85C) = 0;
    for (i = 0; i < 0x20; i++) {
        plotRadarBlipColumn(r, i);
    }
    RF(u16, 0x800) = 1;
    RF(u8, 0x810) = 1;
    RF(f32, 0x804) = 0.2f;
    RF(f32, 0x808) = 1.0f;
    RF(s32, 0x80C) = 0;
    { RdStr *dd = (RdStr *)(r + 0x814); const RdStr *ss = (const RdStr *)"radar_disp"; __builtin_memcpy(dd, ss, 11); }
    RF(u8 *, 0x824) = r;
    if (D_mission_overlay_8010CA1C & 0x200) {
        RF(u8 *, 0x844) = D_mission_overlay_8010A028;
    } else {
        RF(u8 *, 0x844) = D_mission_overlay_80109FF8;
    }
    if (rdLevel == 0x14) {
        RF(u8 *, 0x844) = D_mission_overlay_8010A058;
    }
    RF(u8, 0x850) = 1;
    RF(s16, 0x84E) = 0x40;
    RF(s16, 0x84C) = 0x40;
    RF(s16, 0x852) = 0x300;
    RF(u8 *, 0x848) = r + 0x814;
    RF(u16, 0x858) = rdRegTex(r + 0x800, r + 0x824, 0);
    RF(u16, 0x85A) = rdLoad("ov/ov_rdir", 0, 0);
    RF(s32, 0x8E8) = 0x02770000;
    RF(s32, 0x8F0) = 0xB;
    RF(u8 *, 0x8FC) = r + 0x938;
    RF(s32, 0x89C) = 0;
    RF(s32, 0x898) = 0;
    RF(s32, 0x894) = 0;
    RF(s32, 0x890) = 0;
    RF(u8 *, 0x8A0) = r + 0x8DC;
    RF(s32, 0x8A4) = 0;
    RF(s32, 0x8E0) = 0;
    RF(s32, 0x8DC) = 0;
    RF(s32, 0x8E4) = 0;
    RF(s32, 0x8F8) = 0;
    RF(s32, 0x8EC) = 0;
    RF(s32, 0x8F4) = 0;
    RF(u8 *, 0x900) = r + 0x948;
    RF(s32, 0x904) = 0;
    rdClear(r + 0x8DC);
    RF(s32, 0x93C) = 0;
    RF(s32, 0x938) = 0;
    RF(RdEnt *, 0x940) = (RdEnt *)(r + 0x9F8);
    e = RF(RdEnt *, 0x940);
    RF(s32, 0x944) = 8;
    for (i = 0; i < 16; e++, i++) {
        e->w0 = 4;
        e->w4 = 0x090C8005;
        e->w8 = 0;
        e->w0 |= 0x82;
        e->hC = 0xA;
        e->hE = i % 8;
        e->h10 = (i + 1) % 8;
        e->h14 = 0x800;
        e->h16 = 0x1000;
        e->h18 = 0;
        e->h1A = 0;
        e->h1C = 0x1000;
        e->h1E = 0;
        if (i >= 8) {
            e->w8 = RF(u16, 0x858) << 16;
            e->b20 = 0xFF;
            e->b21 = 0xFF;
            e->b22 = 0xFF;
            e->b23 = 0xD2;
        } else {
            e->w8 = RF(u16, 0x85A) << 16;
            e->b20 = 0xFF;
            e->b21 = 0x8F;
            e->b22 = 0x20;
            e->b23 = 0xFF;
        }
    }
    for (i = 0; i < 8; i++) {
        ang = (f32)i * 3.1415927f * 2.0f * 0.125f - 0.3926991f;
        *(s16 *)(r + i * 8 + 0x948) = sinf(ang) * 256.0f;
        *(s16 *)(r + i * 8 + 0x94A) = -cosf(ang) * 256.0f;
        *(s16 *)(r + i * 8 + 0x94C) = 0;
    }
    RF(s16, 0x998) = 0;
    RF(s16, 0x99A) = 0;
    RF(s16, 0x99C) = 0;
    obj = rdFind("ckp_ra");
    if (obj != NULL) {
        RF(u8, 0xDD0) = 1;
        c[0] = c[1] = c[2] = 0.0f;
        for (k = 0; k < 9; k++) {
            c[0] += (*obj)->pts[k].x;
            c[1] += (*obj)->pts[k].y;
            c[2] += (*obj)->pts[k].z;
        }
        c[0] /= 9.0f;
        c[1] /= 9.0f;
        c[2] /= 9.0f;
        RF(u16, 0x9F0) = (*obj)->pts[0].x;
        RF(u16, 0x9F2) = (*obj)->pts[0].y;
        RF(u16, 0x9F4) = (*obj)->pts[0].z;
        d[0] = (*obj)->pts[0].x - c[0];
        d[1] = (*obj)->pts[0].y - c[1];
        d[2] = (*obj)->pts[0].z - c[2];
        best = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
        sel = 0;
        for (k = 1; k < 9; k++) {
            d[0] = (*obj)->pts[k].x - c[0];
            d[1] = (*obj)->pts[k].y - c[1];
            d[2] = (*obj)->pts[k].z - c[2];
            dist = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
            if (dist < best) {
                RF(u16, 0x9F0) = (*obj)->pts[k].x;
                RF(u16, 0x9F2) = (*obj)->pts[k].y;
                RF(u16, 0x9F4) = (*obj)->pts[k].z;
                best = dist;
                sel = k;
            }
        }
        cnt = 0;
        for (k = 0; k < 9; k++) {
            if (k == sel) {
                continue;
            }
            v[0] = (*obj)->pts[k].x - (*obj)->pts[sel].x;
            v[1] = (*obj)->pts[k].y - (*obj)->pts[sel].y;
            v[2] = 0.0f;
            rdNorm(v);
            a = rdAtan2(v[0], -v[1]);
            for (j = 0; j < cnt; j++) {
                if (a < angs[j]) {
                    break;
                }
            }
            for (m2 = cnt; m2 != j; m2--) {
                RF(RdPt8, 0x9A0)[m2] = RF(RdPt8, 0x9A0)[m2 - 1];
                angs[m2] = angs[m2 - 1];
            }
            cnt++;
            RF(RdPt8, 0x9A0)[j] = (*obj)->pts[k];
            angs[j] = a;
        }
        tmp = RF(RdPt8, 0x9A0)[cnt - 1];
        for (i = cnt - 1; i != 0; i--) {
            RF(RdPt8, 0x9A0)[i] = RF(RdPt8, 0x9A0)[i - 1];
        }
        RF(RdPt8, 0x9A0)[0] = tmp;
        {
            RdHdr *h = (*obj)->hdr;
            u32 *p = h->p8;
            for (k = 0; k < h->nC; k++) {
                p[0] |= 0x100;
                p = (u32 *)((u8 *)p + ((p[1] & 0x3F000000) >> 22));
            }
        }
    } else {
        RF(u8, 0xDD0) = 0;
    }
    m = r + 0x860;
    *out = r + 0x890;
    *out2 = m;
    rdInit4(m, 0.2f, 0.2f, 0.2f);
    rdAdd24(m, 0.0f, -0.25f, 1.0f);
    RF(s16, 0xDB8) = 0;
    RF(s16, 0xDC8) = -1;
    RF(f32, 0xDCC) = 2.0f;
    return r;
}

typedef struct { u8 pad[0x14]; s16 x0; s16 y0; s16 x1; s16 y1; s16 x2; s16 y2; u8 pad20[3]; s8 a; } Seg;
extern f32 sinf(f32);
extern f32 cosf(f32);

void updateCraftSelectAnimState(u8 *arg0, f32 *arg1, f32 arg2, f32 arg3, f32 arg4)
{
  f32 t;
  f32 d;
  f32 fr;
  f32 sn;
  f32 cs;
  f32 ang;
  s16 px;
  s16 py;
  s32 i;
  s32 s4;
  s32 s2;
  u8 *p;
  Seg *e;
  u32 u0;
  u32 u1;
  p = arg0 + 0xB18;
  t = arg1[0] * 0.5f;
  fr = t - (f32)(s32)t;
  d = fr + fr;
  u0 = (u32)(d * 4096.0f * 0.015625f);
  s4 = ((u0 + ((s16)(*(s16 *)(arg0 + 0x85C) % 32) << 7)) & 0xFFF) | 0x1000;
  t = arg1[2] * 0.5f;
  fr = t - (f32)(s32)t;
  d = fr + fr;
  u1 = (u32)(d * 4096.0f * 0.015625f);
  s2 = ((u1 + ((s16)(*(s16 *)(arg0 + 0x85E) % 32) << 7)) & 0xFFF) | 0x1000;
  ang = -0.3926991f;
  sn = sinf(ang);
  cs = cosf(ang);
  px = (u32)((f32)s4 + (sn * arg3 + cs * arg2) * 0.45f * 4096.0f);
  py = (u32)((f32)s2 - -(cs * arg3 - sn * arg2) * 0.45f * 4096.0f);
  e = (Seg *)p;
  i = 0;
  do
  {
    e->x0 = s4;
    e->y0 = s2;
    ang = (f32)(i + 1);
    ang = ang * 3.1415927f;
    ang = ang + ang;
    ang = ang * 0.125f;
    ang = ang - 0.3926991f;
    e->x1 = px;
    e->y1 = py;
    sn = sinf(ang);
    cs = cosf(ang);
    px = (u32)((f32)s4 + (sn * arg3 + cs * arg2) * 0.45f * 4096.0f);
    e->x2 = px;
    py = (u32)((f32)s2 - -(cs * arg3 - sn * arg2) * 0.45f * 4096.0f);
    e->y2 = py;
    e->a = (u32)(arg4 * 210.0f);
    i++;
    e++;
  }
  while (i < 8);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", placeRadarDots);

extern s32 gObjectiveCounts[];
extern u8 gObjectiveBooleans[];
typedef struct {
    s32 a, b, c;
} Raw3;

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    u8 pad1C[0x2C - 0x1C];
    u8 *src;
    s32 boolA;
    s32 cntB;
    s32 cntBLim;
    s32 boolC;
    s32 cntD;
    s32 cntDLim;
} RadarContact;

typedef struct {
    u8 pad0[0xDBC];
    f32 sweepAngle;
    f32 sweepA;
    f32 sweepB;
    s16 sel;
    s16 padDCA;
    s32 selTimer;
} RadarState;

extern RadarContact *gRadarContacts[] __asm__("D_mission_overlay_8010C000");
extern s16 D_mission_overlay_8010C080;
extern f32 atan2Approx(f32, f32);
extern u8 *getNpcContextField8(u16);

void findClosestRadarContactAndSetSweep(RadarState *st, f32 *pos, f32 unused, f32 range) {
    f32 d[3];
    f32 fs0;
    f32 fs1;
    f32 t;
    RadarContact *c;
    u8 *s0;
    u8 *np;
    s32 ok;
    s32 i;
    s32 best;

    best = -1;
    i = 0;
    if (D_mission_overlay_8010C080 > 0) {
        do {
            c = gRadarContacts[i];
            ok = 1;
            if (c->boolA > 0) {
                ok = gObjectiveBooleans[c->boolA - 1] != 0;
            }
            if (c->cntB > 0 && gObjectiveCounts[c->cntB - 1] < c->cntBLim) {
                ok = 0;
            }
            if (c->boolC > 0 && gObjectiveBooleans[c->boolC - 1] != 0) {
                ok = 0;
            }
            if (c->cntD > 0 && gObjectiveCounts[c->cntD - 1] >= c->cntDLim) {
                ok = 0;
            }
            if (ok != 0) {
                s0 = c->src;
                if (s0 != NULL) {
                    u16 nid = *(u16 *)(s0 + 6);
                    if (nid != 0xFFFF && (np = getNpcContextField8(*(u16 *)(s0 + 6))) != NULL) {
                        *(Raw3 *)c->pos = *(Raw3 *)np;
                    } else {
                        *(Raw3 *)c->pos = *(Raw3 *)(s0 + 0x10);
                    }
                }
                d[0] = c->pos[0] - pos[0];
                d[2] = c->pos[2] - pos[2];
                fs1 = d[0] * d[0] + d[2] * d[2];
                if (best < 0 || fs1 < fs0) {
                    best = i;
                    fs0 = fs1;
                }
            } else if (i == st->sel) {
                st->sel = -1;
            }
            i += 1;
        } while (i < D_mission_overlay_8010C080);
    }
    if (st->sel >= 0) {
        if (best != st->sel) {
            d[0] = gRadarContacts[st->sel]->pos[0] - pos[0];
            d[2] = gRadarContacts[st->sel]->pos[2] - pos[2];
            fs1 = d[0] * d[0] + d[2] * d[2];
            fs1 = fs1 * 1.5625f;
            if (best >= 0 && fs0 < fs1) {
                st->sel = best;
                goto clear;
            }
            goto after;
        }
        if (best < 0) {
            goto setsel;
        }
        goto compute;
    }
setsel:
    st->sel = best;
clear:
    st->selTimer = 0;
after:
    if (st->sel >= 0) {
compute:
        d[0] = gRadarContacts[st->sel]->pos[0] - pos[0];
        d[2] = gRadarContacts[st->sel]->pos[2] - pos[2];
        __asm__ volatile("sqrt.s %0, %1" : "=f"(fs1) : "f"(d[0] * d[0] + d[2] * d[2]));
        if (fs1 > 8.0f) {
            if (fs1 > 20.0f) {
                fs1 = 20.0f;
            }
            fs1 = 1.0f - (fs1 - 8.0f) / 12.0f;
            st->sweepAngle = atan2Approx(d[0], d[2]) * 57.29578f;
            st->sweepA = fs1 * 145.0f + 15.0f;
            st->sweepB = (1.0f - fs1) * range;
            return;
        }
    }
    st->sweepB = 0.0f;
}

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} RadarRgba;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 w;
} RadarPt;

typedef struct {
    u8 pad0[0xE];
    s16 i0;
    s16 i1;
    u8 pad12[6];
    s16 u0;
    u8 pad1A[2];
    s16 u1;
    u8 pad1E[2];
    RadarRgba col;
} RadarEntry;

f32 sinf(f32);
f32 sinfApprox(f32);
f32 floatModulo(f32, f32);

void renderRadarSweep(void *arg0v, f32 *arg1, f32 arg2, f32 arg3)
{
  u8 *arg0 = arg0v;
  RadarRgba col;
  RadarEntry *e = (RadarEntry *) (arg0 + 0xAF4);
  RadarPt *tbl = *((RadarPt **) (arg0 + 0x900));
  s32 n = 0;
  f32 f;
  f32 lo;
  f32 hi;
  f32 acc;
  f32 span;
  f32 x;
  register f32 y asm("$f0");
  f32 half;
  f32 frac;
  s32 idx;
  s32 i0;
  s32 i1;
  RadarPt *a;
  RadarPt *b;
  if ((*((f32 *) (arg0 + 0xDC4))) > 0.0f)
  {
    if ((*((f32 *) (arg0 + 0xDCC))) < 1.0f)
    {
      f = (sinf(((2.0f * ((*((f32 *) (arg0 + 0xDCC))) * 3.0f)) * 3.1415927f) - 1.5707964f) + 1.0f) * 0.5f;
      col.r = (u32) ((f * 0.0f) + 255.0f);
      col.g = (u32) ((f * 77.0f) + 143.0f);
      col.b = (u32) ((f * 188.0f) + 32.0f);
      f = (*((f32 *) (arg0 + 0xDCC))) / 0.33333334f;
      if (f < 1.0f)
      {
        col.a = (u32) (f * 255.0f);
      }
      else
      {
        col.a = 0xFF;
      }
    }
    else
    {
      col.r = 0xFF;
      col.g = 0x8F;
      col.b = 0x20;
      col.a = 0xFF;
    }
    col.a = (u32) (((f32) col.a) * (*((f32 *) (arg0 + 0xDC4))));
    if (arg3 > 0.0f)
    {
      f = sinfApprox(arg2);
    }
    else
    {
      f = 3.1415927f - sinfApprox(arg2);
    }
    lo = floatModulo(((((*((f32 *) (arg0 + 0xDBC))) - (*((f32 *) (arg0 + 0xDC0)))) * 0.017453292f) + 12.566371f) - f, 6.2831855f);
    hi = floatModulo(((((*((f32 *) (arg0 + 0xDBC))) + (*((f32 *) (arg0 + 0xDC0)))) * 0.017453292f) + 12.566371f) - f, 6.2831855f);
    if (hi < lo)
    {
      hi += 6.2831855f;
    }
    acc = 0.0f;
    lo = lo / 0.7853982f;
    hi = hi / 0.7853982f;
    span = hi;
    span = span - lo;
    if (lo < hi)
    {
      half = 0.5f;
      do
      {
        y = lo + half;
        frac = y;
        asm("" : "+f"(y));
        idx = (s32) y;
        frac = frac - ((f32) ((s32) frac));
        i0 = idx % 8;
        e->i0 = i0;
        i1 = i0 + 1;
        i1 %= 8;
        e->i1 = i1;
        if (n == 0)
        {
          tbl[8].x = tbl[i0].x + (tbl[i1].x - tbl[i0].x) * frac;
          tbl[8].y = tbl[i0].y + (tbl[i1].y - tbl[i0].y) * frac;
          tbl[8].z = tbl[i0].z + (tbl[i1].z - tbl[i0].z) * frac;
          e->i0 = 8;
        }
        e->u0 = (u32) ((acc / span) * 4096.0f);
        acc += 1.0f - frac;
        if (span < acc)
        {
          acc = span;
        }
        e->u1 = (u32) ((acc / span) * 4096.0f);
        lo += 1.0f - frac;
        if (hi < lo)
        {
          frac = hi + half;
          i1 = i0 + 1;
          frac = frac - ((f32) ((s32) frac));
          a = (RadarPt *)(i0 * 8 + (s32)tbl);
          tbl[9].x = a->x + ((&tbl[i1 % 8])->x - a->x) * frac;
          tbl[9].y = a->y + ((&tbl[i1 % 8])->y - a->y) * frac;
          tbl[9].z = a->z + ((&tbl[i1 % 8])->z - a->z) * frac;
          lo = hi;
          e->i1 = 9;
        }
        asm("" :: "f"(half));
        e->col = col;
        e--;
        n++;
      }
      while ((n < 8) && (lo < hi));
    }
  }
  asm("" : "+r"(n));
  asm("" : "+r"(n));
  *((RadarEntry **) (arg0 + 0x940)) = e + 1;
  *((s32 *) (arg0 + 0x944)) = n + 8;
}

typedef struct { u16 idx; u8 a, b, c, d; } RmBlip;
typedef struct { s32 w[12]; } RmMat;
typedef struct {
    u8 grid[0x800];
    u8 pad800[0x58];
    u16 h858;
    u8 pad85A[2];
    s16 h85C;
    s16 h85E;
    RmMat m860;
    u8 pad890[0x1C];
    RmMat m8AC;
    u8 pad8DC[0x24];
    void *p900;
    u8 pad904[0x44];
    u8 b948[0x58];
    u8 b9A0[0x298];
    RmBlip blips[0x2A];
    u8 padD34[0x84];
    u16 hDB8;
    u8 padDBA[0x16];
    u8 bDD0;
} RmState;
typedef struct { u8 pad[4]; u16 h4; } RmCam;
extern RmCam *D_main_bss_80138D1C;
extern struct { u8 pad[0xC]; u32 wC; } rmGS __asm__("gGameSettings");
extern u16 D_main_bss_80137F3C;
extern f32 D_mission_overlay_8010BFDC;
f32 *rmCraft(s32) __asm__("getPlayerCraftRecordByIdx");
void plotRadarBlipRow(u8 *, s32);
void rmCopyMat(void *) __asm__("copyCurrentObjectMatrix");
f32 getConfigFloatValue(void);
u8 rmFunc(void) __asm__("func_mission_overlay_800FEECC");
u8 rmSecCnt(void) __asm__("getHudSecondaryWeponCount");
void rmUpdAnim(void *, f32 *, f32, f32, f32) __asm__("updateCraftSelectAnimState");
void rmFind(void *, f32 *, f32 *, f32) __asm__("findClosestRadarContactAndSetSweep");
void renderRadarSweep(void *, f32 *, f32, f32);
void placeRadarDots(void *, f32 *);
s32 findMatchingTextureRecursive(u16, void *, void *, s32);

void renderRadarMinimap(RmState *r) {
    f32 *c;
    s32 i;
    s32 x;
    s32 z;
    u16 idx;
    f32 len;
    f32 range;

    c = rmCraft(0);
    for (i = r->hDB8 - 1; i >= 0; i--) {
        idx = r->blips[i].idx;
        r->grid[idx] = r->blips[i].a;
        r->grid[(idx + 1) & 0x7FF] = r->blips[i].b;
        r->grid[(idx + 0x20) & 0x7FF] = r->blips[i].c;
        r->grid[(idx + 0x21) & 0x7FF] = r->blips[i].d;
    }
    r->hDB8 = 0;
    x = c[0] * 0.5f;
    z = c[2] * 0.5f;
    if (x != r->h85C || z != r->h85E) {
        if (z < r->h85E) {
            plotRadarBlipRow((u8 *)r, r->h85E - 16);
            r->h85E--;
        } else if (r->h85E < z) {
            plotRadarBlipRow((u8 *)r, r->h85E + 16);
            r->h85E++;
        }
        if (x < r->h85C) {
            plotRadarBlipColumn(r, r->h85C - 16);
            r->h85C--;
        } else if (r->h85C < x) {
            plotRadarBlipColumn(r, r->h85C + 16);
            r->h85C++;
        }
    }
    __asm__ volatile("sqrt.s %0, %1" : "=f"(len) : "f"(c[3] * c[3] + c[5] * c[5]));
    if (D_main_bss_80138D1C->h4 != 3 || !(rmGS.wC & 0x10) || r->bDD0 == 0) {
        r->p900 = r->b948;
        r->m8AC = r->m860;
        range = D_mission_overlay_8010BFDC;
    } else {
        rmCopyMat(&r->m8AC);
        r->p900 = r->b9A0;
        if ((rmGS.wC & 0x10) && !(D_main_bss_80137F3C & 0x100) && getConfigFloatValue() == 0.0f
            && (!rmFunc() || !rmSecCnt())) {
            range = 1.0f;
        } else {
            range = 0.0f;
        }
    }
    rmUpdAnim(r, c, c[3] / len, c[5] / len, range);
    rmFind(r, c, c + 3, range);
    renderRadarSweep(r, c, c[3] / len, c[5] / len);
    placeRadarDots(r, c);
    findMatchingTextureRecursive(r->h858, r->grid + 0x800, r->grid + 0x824, 0);
}

extern u8 D_mission_overlay_80109FE4[];
extern u16 D_mission_overlay_8010BFF0[];
u16 lookupCraftValueByLevelKey(s32 key) {
    s32 i;

    for (i = 0; D_mission_overlay_80109FE4[i] != 0xFF; i += 2) {
        if (D_mission_overlay_80109FE4[i] == key) {
            break;
        }
    }
    if (D_mission_overlay_80109FE4[i] != 0xFF) {
        return D_mission_overlay_8010BFF0[i >> 1];
    }
    return 0;
}

extern s16 D_mission_overlay_8010C080;

void resetCraftSelectionCounter(void) {
    D_mission_overlay_8010C080 = 0;
}

s32 getLevelDatItemByName(char *);
extern void *D_mission_overlay_8010C000[];
typedef struct { u8 pad[0x2C]; s32 nameOffset; } RegisteredObject;
void registerObjectAndResolveDatItem(RegisteredObject *obj) {
    s32 item;

    if (D_mission_overlay_8010C080 < 0x20) {
        D_mission_overlay_8010C000[D_mission_overlay_8010C080++] = obj;
        if (obj->nameOffset != 0) {
            char *name = (char *)(obj->nameOffset + (s32)obj);
            if (*name == 0x2D) {
                obj->nameOffset = 0;
            } else {
                item = getLevelDatItemByName(name);
                if (item != 0) {
                    obj->nameOffset = item;
                } else {
                    obj->nameOffset = 0;
                }
            }
        }
    }
}

s32 findMatchingTextureRecursive(u16, void *, void *, s32);
void *getCraftRecordByIdx(s32);
s32 plotRadarBlipColumn(void *, s32);
extern void *D_mission_overlay_8010BFE0;

void getAvailableShipsForLevel(void) {
    s32 var_s0;
    void *temp_s1;
    void *temp_v0;

    temp_s1 = D_mission_overlay_8010BFE0;
    temp_v0 = getCraftRecordByIdx(0);
    (*(s16 *)((u8 *)(temp_s1) + 0x85C)) = (s16) (s32) ((*(f32 *)((u8 *)(temp_v0) + 0)) * 0.5f);
    var_s0 = -0x10;
    (*(s16 *)((u8 *)(temp_s1) + 0x85E)) = (s16) (s32) ((*(f32 *)((u8 *)(temp_v0) + 8)) * 0.5f);
    do {
        plotRadarBlipColumn(temp_s1, (*(s16 *)((u8 *)(temp_s1) + 0x85C)) + var_s0);
        var_s0 += 1;
    } while (var_s0 < 0x10);
    (*(s16 *)((u8 *)(temp_s1) + 0xDB8)) = 0;
    findMatchingTextureRecursive((*(u16 *)((u8 *)(temp_s1) + 0x858)), temp_s1 + 0x800, temp_s1 + 0x824, 0);
    (*(s16 *)((u8 *)(temp_s1) + 0xDC8)) = -1;
    (*(s32 *)((u8 *)(temp_s1) + 0xDCC)) = 0;
}

void accumulateClampedFloatField(u8 *arg0, f32 arg1) {
    if (*(f32 *)(arg0 + 0xDCC) < 1.0f) {
        *(f32 *)(arg0 + 0xDCC) += arg1;
    }
}

u8 getDisplayItemStateByte(void *arg0) {
    return (*(u8 *)((u8 *)(arg0) + 0xDD0));
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", fake_func_800C64A4);

const u32 rodata_pad_0C4DB0[3] = { 0x93C30004, 0x3C01801D, 0x00220821 };
