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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", initializeRadar);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", renderRadarSweep);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", renderRadarMinimap);

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
