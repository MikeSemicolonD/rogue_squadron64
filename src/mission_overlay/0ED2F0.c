#include "common.h"
#include "common_types.h"

typedef struct TcSrc {
    u8 pad0[4];
    u16 h4;
    u8 pad6[0x22];
    f32 f28;
    u8 pad2C[4];
    f32 f30;
    u8 pad34[0xA];
    u16 h3E;
    u8 pad40[2];
    u16 h42;
    u8 pad44[2];
    u16 h46;
    u8 pad48[2];
    u16 h4A;
    f32 f4C;
    f32 f50;
    f32 f54;
    f32 f58;
    f32 f5C;
    f32 f60;
    s32 w64;
    s32 w68;
    s32 w6C;
    f32 f70;
    u8 pad74[3];
    u8 b77;
    f32 f78;
    u8 pad7C[0x1B];
    u8 b97;
    u8 pad98[3];
    u8 b9B;
    u8 pad9C[3];
    u8 b9F;
    s32 wA0;
} TcSrc;

typedef struct TcData {
    s32 f0;
    TcSrc *src;
    f32 x;
    f32 y;
    f32 z;
    u8 pad14[0x24];
    f32 f38;
    f32 f3C;
    f32 f40;
    f32 f44;
    f32 f48;
    u8 b4C;
    u8 b4D;
    u8 b4E;
} TcData;

typedef struct TcCue {
    f32 f0;
    f32 f4;
    s32 w8;
    s32 wC;
    s32 w10;
    s32 w14;
    s32 w18;
    s32 w1C;
    u16 h20;
    u16 h22;
    u16 h24;
    s16 h26;
    s16 h28;
    s16 h2A;
    u16 h2C;
    u8 b2E;
    u8 b2F;
    u8 b30;
    u8 b31;
    u8 b32;
    u8 b33;
    u8 b34;
    u8 b35;
    s32 w38;
} TcCue;

extern u16 D_main_bss_80139562;
s32 findActiveNpcInSlotChain(u16, void *);
f32 *getNpcContextField8(s32);
s32 tickObjectSoundCueState(TcCue *);

u8 tcmaeV(TcData *p, f32 dt) __asm__("tickCraftMountedAnimationEffect");
u8 tcmaeV(TcData *p, f32 dt) {
    s32 out[2];
    f32 bx[3];
    f32 np[3];
    TcCue sc;
    f32 mn[3];
    u8 ret;
    s32 i;
    f32 *o;
    f32 *q;
    TcSrc *s;
    f32 k;
    f32 f;
    s32 v;

    ret = 0;
    if (p->b4C != 0) {
        p->f48 += dt;
        if (!(p->src->f70 <= p->f48)) {
            return 0;
        }
        p->f48 = 0.0f;
        p->b4C = 0;
    }
    q = &p->x;
    bx[0] = p->x + p->src->f28;
    bx[2] = q[2] + p->src->f30;
    i = findActiveNpcInSlotChain(D_main_bss_80139562, out) & 0xFFFF;
    if (i == 0xFFFF) {
        return ret;
    }
    o = getNpcContextField8(i);
    np[0] = o[0] + o[9] * dt;
    np[1] = o[1] + o[10] * dt;
    np[2] = o[2] + o[11] * dt;
    if (o[0] < p->x || bx[0] < o[0] || o[2] < q[2] || bx[2] < o[2]) {
        v = p->b4D;
        if (v != 1) {
            return ret;
        }
        p->b4D = 0;
        if (p->src->f70 != 0.0f) {
            p->b4C = v;
            p->f48 = 0.0f;
        }
        s = p->src;
        sc.h20 = s->h4A;
        sc.h24 = s->h42;
        sc.h26 = v;
        sc.h22 = s->h46;
        sc.h28 = (u32)(s->f58 * 1000.0f);
        sc.h2A = (u32)(s->f5C * 1000.0f);
        sc.f0 = 0.0f;
        sc.w8 = 1;
        sc.wC = 1;
        sc.b31 = 0;
        sc.b32 = 0;
        sc.b2F = 0;
        sc.b2E = 0;
        sc.h2C = s->h4;
        sc.w1C = sc.w18 = sc.w14 = sc.w10 = 0x7FFFFFFF;
        sc.f4 = s->f78;
        sc.b33 = s->b97;
        sc.b34 = s->b9B;
        sc.b35 = s->b9F;
        sc.w38 = s->wA0;
        sc.b30 = 0;
        s = p->src;
        if (s->w6C != 0) {
            if (--s->w6C == 0) {
                ret = 1;
                sc.b2F = 1;
            }
        }
        if ((u8)tickObjectSoundCueState(&sc) == 1) {
            ret = 1;
        }
    } else {
        if (p->b4E == 0) {
            k = p->src->f4C;
            mn[0] = p->x + (p->src->f28 - p->src->f28 * k) * 0.5f;
            mn[2] = q[2] + (p->src->f28 - p->src->f28 * k) * 0.5f;
            bx[0] = p->x + p->src->f28 * k;
            bx[2] = q[2] + p->src->f30 * k;
        } else {
            mn[0] = p->f38;
            mn[2] = p->f3C;
            bx[0] = p->f40;
            bx[2] = p->f44;
        }
        f = o[0];
        if (!(mn[0] <= f) || !(f <= bx[0])) {
            return ret;
        }
        f = o[2];
        if (!(mn[2] <= f) || !(f <= bx[2])) {
            return ret;
        }
        if (p->b4D != 0) {
            return ret;
        }
        s = p->src;
        p->b4D = 1;
        sc.h20 = s->h3E;
        sc.h24 = s->h42;
        sc.h26 = 1;
        sc.h22 = s->h46;
        sc.h28 = (u32)(s->f50 * 1000.0f);
        sc.h2A = (u32)(s->f54 * 1000.0f);
        sc.f0 = s->f60;
        sc.w8 = s->w64;
        sc.wC = s->w68;
        sc.b31 = s->b77;
        sc.b32 = 0;
        sc.b2F = 0;
        sc.b2E = 1;
        sc.h2C = s->h4;
        sc.f4 = s->f78;
        sc.b33 = s->b97;
        sc.b34 = s->b9B;
        sc.b35 = s->b9F;
        sc.w38 = s->wA0;
        sc.b30 = 1;
        if ((u8)tickObjectSoundCueState(&sc) == 1) {
            ret = 1;
        }
    }
    return ret;
}

#include "level_objectives.h"

typedef struct CmSrc {
    f32 dt;
    u8 pad4[0xC];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[0x68];
    s32 bool_idx;
    s32 bool_val;
    s32 cnt_idx;
    s32 cnt_val;
    u8 pad94[0x10];
    s32 hasRef;
    s32 refOff;
} CmSrc;

typedef struct CmRef {
    u8 pad0[0x10];
    f32 x;
    u8 pad14[4];
    f32 z;
    u8 pad1C[0xC];
    f32 dx;
    u8 pad2C[4];
    f32 dz;
} CmRef;

typedef struct CmData {
    s32 f0;
    CmSrc *src;
    f32 x;
    f32 y;
    f32 z;
    u8 pad14[0x24];
    f32 rx;
    f32 rz;
    f32 tx;
    f32 tz;
    s32 f48;
    u8 b4C;
    u8 b4D;
    u8 b4E;
} CmData;

typedef struct CmNpc {
    u8 pad0[4];
    CmData *data;
    void *self;
    u8 pad[0xA];
    u16 slot;
} CmNpc;

typedef struct CmTable {
    u8 pad[0x34];
    CmRef **refs;
} CmTable;

extern CmTable *D_main_bss_801375D8;
extern u16 D_main_bss_8013959C;
extern void popNpcSlotFromTail(u16, void *);
extern void destroyNpcSlotByIndex(u16);
extern s32 tickCraftMountedAnimationEffect(void *, f32);

s32 craftMountedAnimationNpcHandler(CmNpc *arg0, s32 arg1, CmSrc *arg2) {
    s32 msg = arg1 & 0xFFFF;
    CmData *p = arg0->data;

    switch (msg) {
    case 1: {
        CmSrc *src;
        arg0->self = (void *)((u8 *)p + 8);
        p->src = arg2;
        p->x = arg2->x;
        p->y = arg2->y;
        p->z = arg2->z;
        p->b4D = 0;
        p->f48 = 0;
        p->b4C = 0;
        p->f0 = 0;
        src = p->src;
        if (src->hasRef != 0) {
            s32 idx = *(u16 *)(src->refOff + (s32)src + 0xA6);
            CmRef *t = D_main_bss_801375D8->refs[idx];
            p->rx = t->x;
            p->rz = t->z;
            p->tx = p->rx + t->dx;
            p->tz = p->rz + t->dz;
            p->b4E = msg;
        } else {
            p->b4E = 0;
        }
        popNpcSlotFromTail(D_main_bss_8013959C, arg0);
        return 1;
    }
    case 3: {
        CmSrc *q = p->src;
        s32 b = q->bool_idx;
        f32 dt = arg2->dt;
        s32 c;
        if (b == 0 || gObjectiveBooleans[b - 1] == q->bool_val) {
            c = q->cnt_idx;
            if (c == 0 || gObjectiveCounts[c - 1] >= q->cnt_val) {
                if ((tickCraftMountedAnimationEffect(p, dt) & 0xFF) == 1) {
                    destroyNpcSlotByIndex(arg0->slot);
                }
            }
        }
        return 1;
    }
    case 12:
        p->b4D = 0;
        p->f48 = 0;
        p->b4C = 0;
    case 2:
        break;
    default:
        return 1;
    }
    return 1;
}

s32 slotDispatcherIter(u16, s32, s32);
extern u16 D_main_bss_8013959C;

void dispatchSlotActionTwelveByGlobalId(void) {
    slotDispatcherIter(D_main_bss_8013959C, 0xC, 0);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ED2F0", fake_func_800ECE04);

static u32 D_mission_overlay_800A8924[] __attribute__((section(".rodata"))) = { 0x1043000B, 0, 0x0802A3CF };
