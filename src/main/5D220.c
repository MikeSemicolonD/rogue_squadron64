#include "common.h"
#include "common_types.h"

#include "main/5D220.h"

u8 D_main_8009ECF0[] = {
    0x20,
    0x20,
    0x10,
    0x20,
    0x10,
    0x20,
    0x20,
    0x00,
    0x30,
    0x30,
    0x50,
    0x40,
    0x30,
    0x60,
    0x20,
    0x00,
};

char *D_main_8009ED00[] = {
    "red_laser",
    "red_laser",
    "green_laser",
    "red_laser",
    "green_laser",
    "red_laser",
    "red_laser",
    NULL,
    NULL,
    NULL,
    "i_missile",
    "i_missile",
    "ion_laser",
    "ph_torp",
    "i_missile",
};

f32 D_main_8009ED3C[] ={
    0.7f,
    1.2f,
    2.0f,
    4.0f,
    0.0f,
    1.0f,
    0.0f,
};

// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
u32 data_pad_5D220[] = {
    0xC4400000,
    0xC4620000,
};

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} PxV3;

typedef struct {
    f32 m[12];
} PxMat;

s32 findActiveNpcInSlotChain(u16, void *);
u8 *getNpcContextByIndex(u16);
void transformMeshPartIntoWorld(s32, f32 *);
void vec3Cross(void *, void *, void *);
f32 vec3Length(void *);
f32 vec3Dot(void *, void *);
void normalize_vector(void *);
f32 constMinusSinfApprox(f32);
void quatFromAxisAngleSafe(void *, void *, f32);
void rotateVec3ByQuat(void *, void *, void *);
void orthonormalizeFrame(void *);

void checkTrackedNpcProximityForCue(u8 *o, f32 dt) {
    PxMat m;
    PxV3 d;
    PxV3 axis;
    f32 q[4];
    u16 idx;
    u8 *ctx;
    f32 lim;
    f32 a;

    if (o[0x11C] == 1) {
        idx = findActiveNpcInSlotChain(*(u16 *)(o + 0x118), NULL);
        if (idx != 0xFFFF) {
            ctx = getNpcContextByIndex(idx);
            m = **(PxMat **)(ctx + 8);
            if (*(void **)(ctx + 0xC) != NULL) {
                transformMeshPartIntoWorld(*(s32 *)(ctx + 0xC), m.m);
            }
            d.x = m.m[0] - *(f32 *)(o + 0xB4);
            d.y = m.m[1] - *(f32 *)(o + 0xB8);
            d.z = m.m[2] - *(f32 *)(o + 0xBC);
            vec3Cross(&axis, o + 0xC0, &d);
            if (vec3Length(&axis) > 1e-5f) {
                lim = *(f32 *)(o + 0x114) * 30.0f * dt;
                normalize_vector(&d);
                a = constMinusSinfApprox(vec3Dot(&d, o + 0xC0)) * 57.29578f;
                if (lim < a) {
                    a = lim;
                } else if (a < -lim) {
                    a = -lim;
                }
                quatFromAxisAngleSafe(q, &axis, a);
                rotateVec3ByQuat(q, o + 0xC0, &d);
                *(PxV3 *)(o + 0xC0) = d;
                rotateVec3ByQuat(q, o + 0xCC, &d);
                *(PxV3 *)(o + 0xCC) = d;
                orthonormalizeFrame(o + 0xB4);
                if (vec3Dot(o + 0x100, o + 0xC0) <= *(f32 *)(o + 0x110)) {
                    o[0x11C] = 0;
                }
            }
            *(f32 *)(o + 0xD8) = *(f32 *)(o + 0xC0) * *(f32 *)(o + 0x10C);
            *(f32 *)(o + 0xDC) = *(f32 *)(o + 0xC4) * *(f32 *)(o + 0x10C);
            *(f32 *)(o + 0xE0) = *(f32 *)(o + 0xC8) * *(f32 *)(o + 0x10C);
        } else {
            o[0x11C] = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/5D220", audioCueDispatcherNpcHandler);

extern u16 D_main_bss_8013957C;
s32 findActiveNpcInSlotChain(u16, void *);
u8 *getNpcContextByIndex(u16);
s32 revalidateNpcSlotIterator(void *);
void slotDispatcherIter(u16, s32, void *);
void transformMeshPartIntoWorld(s32, f32 *);

void collectNearbyNpcsForEffect(u8 *arg0, u16 arg1) {
    u8 sp10[8];
    struct {
        u16 a;
        u16 b;
        s16 c;
        s16 d;
        s32 e;
    } ev;
    f32 v[3];
    s32 idx;
    s32 mesh;
    u32 cur;
    f32 dist2;
    f32 r;
    f32 t;
    f32 sq;
    f32 sq2;
    f32 val;
    f32 two31;
    u32 sign;
    s32 w;

    ev.a = 0xFFFF;
    ev.b = 0xFFFF;
    ev.c = 9;
    ev.e = 0;
    idx = findActiveNpcInSlotChain(D_main_bss_8013957C, sp10);
    if ((idx & 0xFFFF) != 0xFFFF) {
        sign = 0x80000000;
        two31 = 2147483648.0f;
        do {
            cur = idx & 0xFFFF;
            if (cur != (arg1 & 0xFFFF)) {
                mesh = *(s32 *)(getNpcContextByIndex(cur) + 0xC);
                if (mesh != 0) {
                    transformMeshPartIntoWorld(mesh, v);
                    v[0] = v[0] - *(f32 *)(arg0 + 0x90);
                    v[1] = v[1] - *(f32 *)(arg0 + 0x94);
                    v[2] = v[2] - *(f32 *)(arg0 + 0x98);
                    r = *(f32 *)(arg0 + 0xD0);
                    dist2 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
                    if (dist2 <= r * r) {
                        __asm__("sqrt.s %0, %1" : "=f"(sq) : "f"(dist2));
                        t = (r - sq) / r;
                        __asm__ volatile("sqrt.s %0, %1" : "=f"(sq2) : "f"(t));
                        val = (f32)*(u16 *)(arg0 + 0xD6) * sq2;
                        if (!(two31 <= val)) {
                            ev.d = (s32)val;
                        } else {
                            w = (s32)(val - two31);
                            __asm__("or %0, %1, %2" : "=r"(w) : "r"(w), "r"(sign));
                            ev.d = w;
                        }
                        slotDispatcherIter(idx & 0xFFFF, 5, &ev);
                    }
                }
            }
            idx = revalidateNpcSlotIterator(sp10);
        } while ((idx & 0xFFFF) != 0xFFFF);
    }
}

typedef struct SpBlk {
    struct SpBlk *next;
    struct SpBlk *prev;
    s16 x, y, z;
    u8 padE[0x22];
} SpBlk;

typedef struct {
    SpBlk blk[3];
    PxV3 pos;
    PxV3 pt[2];
    PxV3 vel;
    f32 C0;
    f32 C4;
    f32 C8;
    f32 CC;
    f32 D0;
    u16 D4;
    u16 D6;
    u8 D8;
    u8 D9;
} SpObj;

typedef struct {
    u16 a;
    u16 b;
    s16 c;
    u16 d;
    void *e;
} SpEv;

s32 rs_malloc(s32, s32);
void rs_memset(void *, s32, s32);
u16 popNpcSlotFromTail(u16, void *);
void destroyNpcSlotByIndex(u16);
void spawnScaledOrientedEffectTriple(void *, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
s32 findSegmentObjectSphereHit(s32, void *, void *, void *);
s32 getPlayerField2(s32);
f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
s32 isTerrainCellBlockedAtWorldXz(f32, f32, void *);
void spawnWaterSprayDebrisAndBurst(void *, f32, f32, f32, f32, f32);
u8 transformVec3ToNpcLocalWithScale(s32, s32, void *, f32, s32);
extern s16 D_main_bss_80139738;
extern u16 D_main_bss_80139568;
extern u8 D_main_bss_80130B39;
extern u8 D_main_bss_80138058[];
extern s32 missionStats[];

s32 sprayEffectEmitterNpcHandler(u8 *arg0, s32 action, u8 *arg2) {
    f32 hit[10];
    f32 v[3];
    f32 seg[12];
    union {
        struct {
            u8 it[8];
            f32 d[3];
        } s;
        SpEv ev;
    } u;
    SpObj *o = *(SpObj **)(arg0 + 4);

    switch ((u16)action) {
    case 1:
        {
        u8 *rec = arg2;
        o = (SpObj *)rs_malloc(0xDC, 0);
        *(SpObj **)(arg0 + 4) = o;
        *(u16 *)((u8 *)o + 0x10) = 0x300;
        *((u8 *)o + 0x2C) = 0xFF;
        *((u8 *)o + 0x2D) = 0xFF;
        *((u8 *)o + 0x2E) = 0xFF;
        *((u8 *)o + 0x2F) = 0xFF;
        *(s16 *)((u8 *)o + 0x8) = *(s16 *)((u8 *)o + 0xA) = *(s16 *)((u8 *)o + 0xC) = 0;
        *(s16 *)((u8 *)o + 0x28) = *(s16 *)((u8 *)o + 0x2A) = 0;
        *(u16 *)((u8 *)o + 0x12) = D_main_bss_80139738;
        *(f32 *)((u8 *)o + 0x20) = *(f32 *)((u8 *)o + 0x24) = *(f32 *)rec;
        o->vel = *(PxV3 *)(*(u8 **)(rec + 0xC) + 0x24);
        o->C0 = *(f32 *)rec;
        o->pos.x = *(f32 *)(*(u8 **)(rec + 0xC) + 0) + o->vel.x / 30.0f;
        o->pos.y = *(f32 *)(*(u8 **)(rec + 0xC) + 4) + o->vel.y / 30.0f;
        o->pos.z = *(f32 *)(*(u8 **)(rec + 0xC) + 8) + o->vel.z / 30.0f;
        o->blk[1] = o->blk[0];
        o->blk[2] = o->blk[0];
        o->pt[0] = o->pos;
        o->pt[1] = o->pos;
        *(f32 *)((u8 *)o + 0x50) = *(f32 *)((u8 *)o + 0x20) * 1.1f;
        *(f32 *)((u8 *)o + 0x54) = *(f32 *)((u8 *)o + 0x24) * 1.1f;
        *((u8 *)o + 0x5F) = 0xC0;
        o->C4 = o->C0;
        *(f32 *)((u8 *)o + 0x80) = *(f32 *)((u8 *)o + 0x20) * 1.2f;
        *(f32 *)((u8 *)o + 0x84) = *(f32 *)((u8 *)o + 0x24) * 1.2f;
        *((u8 *)o + 0x8F) = 0x60;
        o->C8 = o->C0;
        o->D6 = *(u16 *)(rec + 0x1C);
        o->D4 = *(u16 *)(rec + 0x18);
        o->CC = 0.0f;
        o->D8 = rec[0x17];
        *(volatile f32 *)&o->D0 = 2.5f;
        o->D9 = 0;
        popNpcSlotFromTail(D_main_bss_80139568, arg0);
        return 1;
        }
    case 2:
        if (o->D9 != 0) {
            rs_memset(v, 0, 0xC);
            spawnScaledOrientedEffectTriple(&o->pos, 1.0f);
            if (o->D8 == 8) {
                play3DSoundEvent(0, &o->pos, v, 24.0f, 0.4f, 0, 0x21, 0x78, 0x50);
            } else {
                play3DSoundEvent(0, &o->pos, v, 24.0f, 0.4f, 0, 0x6E, 0x78, 0x50);
            }
            return 1;
        }
        break;
    case 3:
        {
        f32 dt = *(f32 *)arg2;
        s16 ex;
        u16 best;
        u16 ch;
        u16 idx;
        f32 bestd;
        f32 *hp;
        o->pos.x += o->vel.x * dt;
        o->pos.y += o->vel.y * dt;
        o->pos.z += o->vel.z * dt;
        v[0] = o->pt[0].x - o->pos.x;
        v[1] = o->pt[0].y - o->pos.y;
        v[2] = o->pt[0].z - o->pos.z;
        o->pt[0].x = o->pos.x + v[0] * 0.1f;
        o->pt[0].y = o->pos.y + v[1] * 0.1f;
        o->pt[0].z = o->pos.z + v[2] * 0.1f;
        v[0] = o->pt[1].x - o->pt[0].x;
        v[1] = o->pt[1].y - o->pt[0].y;
        v[2] = o->pt[1].z - o->pt[0].z;
        o->pt[1].x = o->pt[0].x + v[0] * 0.1f;
        o->pt[1].y = o->pt[0].y + v[1] * 0.1f;
        o->pt[1].z = o->pt[0].z + v[2] * 0.1f;
        o->vel.y += dt * 12.0f;
        *(PxV3 *)&seg[0] = o->pos;
        *(PxV3 *)&seg[9] = o->vel;
        seg[6] = 0.0f;
        seg[7] = 0.0f;
        seg[8] = 0.0f;
        seg[3] = 0.0f;
        seg[4] = 0.0f;
        seg[5] = 1.0f;
        ex = -1;
        if (o->CC < 1.0f) {
            ex = o->D4;
        }
        best = 0xFFFF;
        bestd = 2.0f;
        hp = hit;
        ch = D_main_bss_8013957C;
        {
        f32 dt2 = *(f32 *)arg2;
        u.s.d[0] = seg[9] * dt2;
        u.s.d[1] = seg[10] * dt2;
        u.s.d[2] = seg[11] * dt2;
        }
        idx = findActiveNpcInSlotChain(ch, u.s.it);
        if ((idx & 0xFFFF) != 0xFFFF) {
            do {
                if ((u16)ex == 0xFFFF || (u16)ex != idx) {
                    s32 mesh = *(s32 *)(getNpcContextByIndex(idx & 0xFFFF) + 0xC);
                    if (mesh != 0 && findSegmentObjectSphereHit(mesh, seg, u.s.d, hp) != 0) {
                        if (hp[6] < bestd) {
                            bestd = hp[6];
                            best = idx;
                        }
                    }
                }
                idx = revalidateNpcSlotIterator(u.s.it);
            } while ((idx & 0xFFFF) != 0xFFFF);
        }
        idx = best;
        if ((idx & 0xFFFF) != 0xFFFF) {
            if (D_main_bss_80130B39 == 0 && o->D4 == (u16)getPlayerField2(0)) {
                missionStats[2]++;
            }
            u.ev.a = *(u16 *)(arg0 + 0x16);
            u.ev.b = o->D4;
            u.ev.c = o->D8;
            u.ev.d = o->D6;
            u.ev.e = hit;
            slotDispatcherIter(idx & 0xFFFF, 5, &u.ev);
            o->D9 = 1;
            goto tail;
        }
        {
            f32 h = wrapAngleToCyclicRange(o->pos.x, o->pos.z, D_main_bss_80138058, 0);
            if (h <= o->pos.y) {
                o->pos.y = h;
                if (isTerrainCellBlockedAtWorldXz(o->pos.x, o->pos.z, D_main_bss_80138058) == 1) {
                    spawnWaterSprayDebrisAndBurst(&o->pos, 0.6f, 1.2f, 1.0f, 2.0f, 0.5f);
                }
            tail:
                if (o->D0 > 0.0f) {
                    collectNearbyNpcsForEffect((u8 *)o, idx);
                }
                o->D9 = 1;
                destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                return 1;
            }
        }
        }
        break;
    case 4:
        {
        u8 *rec = arg2;
        s32 j;
        if (transformVec3ToNpcLocalWithScale(*(s32 *)arg2, 0, &o->pos, 0.5f, 0)) {
            *(s16 *)((u8 *)o + 0x8) = (o->pos.x - *(f32 *)(rec + 0x18)) * 256.0f;
            *(s16 *)((u8 *)o + 0xA) = (o->pos.y - *(f32 *)(rec + 0x1C)) * 256.0f;
            *(s16 *)((u8 *)o + 0xC) = (o->pos.z - *(f32 *)(rec + 0x20)) * 256.0f;
            *(u8 **)o = *(u8 **)(*(u8 **)(rec + 0x48) + 0x20);
            if (*(u8 **)o != NULL) {
                *(SpObj **)(*(u8 **)o + 4) = o;
            }
            *(s32 *)((u8 *)o + 4) = 0;
            *(SpObj **)(*(u8 **)(rec + 0x48) + 0x20) = o;
            for (j = 0; j < 2; j++) {
                SpBlk *nx;
                SpBlk *b = &o->blk[j];
                SpObj *p = (SpObj *)((u8 *)o + j * 12);
                b[1].x = (p->pt[0].x - *(f32 *)(rec + 0x18)) * 256.0f;
                b[1].y = (p->pt[0].y - *(f32 *)(rec + 0x1C)) * 256.0f;
                b[1].z = (p->pt[0].z - *(f32 *)(rec + 0x20)) * 256.0f;
                nx = *(SpBlk **)(*(u8 **)(rec + 0x48) + 0x20);
                b[1].next = nx;
                if (nx != NULL) {
                    nx->prev = (SpBlk *)((u8 *)o + (j * 0x30 + 0x30));
                }
                b[1].prev = NULL;
                *(SpBlk **)(*(u8 **)(rec + 0x48) + 0x20) = (SpBlk *)((u8 *)o + (j * 0x30 + 0x30));
            }
        }
        return 1;
        }
    case 10:
        switch (*(s16 *)arg2) {
        case 1:
            {
            f32 f = (f32)o->D6 * *(f32 *)(arg2 + 0x18);
            if (f > 65535.0f) {
                f = 65535.0f;
            }
            o->D6 = (u32)f;
            }
            break;
        case 6:
            o->D0 = *(f32 *)(arg2 + 0x18);
            break;
        default:
            return 1;
        }
        break;
    case 11:
        *(u16 *)(arg2 + 2) = 0x1005;
        break;
    }
    return 1;
}

extern s32 D_main_bss_80137CE4;
extern s32 D_main_bss_8013961C;
extern struct { s32 t; s32 shots; } msStats __asm__("missionStats");
u16 spawnNpcOfType(void *, void *, u32, u8);
void noopHandler(s32);
s32 audioCueDispatcherNpcHandler();
s32 guidedEffectNpcHandler();

typedef struct {
    f32 v[3];
    s32 a2;
    f32 a5;
    s32 a0;
    s16 a1;
    s16 a4;
    u16 val;
} CueArgs;

#define CUE_TBL(o) (((u16 *)D_main_bss_8013961C)[D_main_bss_80137CE4 + (o)])

u16 dispatchCueByCategory(s32 arg0, s32 arg1, s32 arg2, f32 *arg3, s32 arg4, f32 arg5, f32 arg6) {
    CueArgs st;
    s32 who = arg1;
    f32 k;

    if (D_main_bss_80130B39 == 0 && (u16)who == (u16)getPlayerField2(0)) {
        msStats.shots++;
    }
    st.a5 = arg5;
    st.a4 = arg4;
    st.a2 = arg2;
    st.a0 = arg0;
    st.a1 = who;
    switch (arg0) {
    case 9:
        if (D_main_bss_80130B39 == 0) {
            noopHandler(0xFA);
        }
    case 8:
        st.val = CUE_TBL(8);
        st.v[0] = st.v[1] = st.v[2] = 0.1f;
        break;
    case 6:
        if (D_main_bss_80130B39 == 0) {
            noopHandler(0xFA);
        }
        st.v[0] = arg3[0] * 0.25f;
        st.v[1] = arg3[1] * 0.25f;
        st.v[2] = arg3[2] * 0.25f;
        st.val = CUE_TBL(4);
        break;
    case 11:
        if (D_main_bss_80130B39 == 0) {
            noopHandler(0xFA);
        }
    case 10:
        st.val = CUE_TBL(12);
        st.v[0] = st.v[1] = st.v[2] = 0.25f;
        break;
    case 14:
        st.val = CUE_TBL(12);
        st.v[0] = arg3[0] * 0.25f;
        st.v[1] = arg3[1] * 0.25f;
        st.v[2] = arg3[2] * 0.25f;
        break;
    case 13:
        st.val = CUE_TBL(20);
        st.v[0] = st.v[1] = st.v[2] = 0.25f;
        break;
    case 12:
        st.val = CUE_TBL(16);
        goto vec;
    case 2:
    case 3:
    case 4:
    case 5:
        if (D_main_bss_80130B39 == 0) {
            noopHandler(0xFA);
        }
    default:
        if ((u16)who == (u16)getPlayerField2(0)) {
            st.val = CUE_TBL(28);
        } else {
            st.val = CUE_TBL(0);
        }
    vec:
        if (arg3 != NULL) {
            st.v[0] = arg3[0] * 0.25f;
            st.v[1] = arg3[1] * 0.25f;
            st.v[2] = arg3[2] * 0.25f;
        } else {
            k = 0.25f;
            st.v[2] = k;
            st.v[1] = k;
            st.v[0] = k;
        }
        break;
    }
    st.val = (u32)((f32)st.val * arg6);
    { u16 r;
    switch (arg0) {
    case 11:
        r = spawnNpcOfType(guidedEffectNpcHandler, &st, 2, 0xC); break;
    case 10:
    case 13:
    case 14:
        r = spawnNpcOfType(guidedEffectNpcHandler, &st, 2, 0x23); break;
    case 9:
        r = spawnNpcOfType(sprayEffectEmitterNpcHandler, &st, 4, 0xC); break;
    case 8:
        r = spawnNpcOfType(sprayEffectEmitterNpcHandler, &st, 4, 0x23); break;
    case 12:
        r = spawnNpcOfType(audioCueDispatcherNpcHandler, &st, 2, 0x23); break;
    case 4:
    case 5:
        r = spawnNpcOfType(audioCueDispatcherNpcHandler, &st, 4, 0xC); break;
    case 1:
        r = spawnNpcOfType(audioCueDispatcherNpcHandler, &st, 4, 0x23); break;
    default:
        r = spawnNpcOfType(audioCueDispatcherNpcHandler, &st, 2, arg0 == 0 ? 0x23 : 0xC); break;
    }
    return r;
    }
}

INCLUDE_RODATA("asm/nonmatchings/main/5D220", D_main_8003B168);

extern s32 D_main_8003B168;
extern s32 D_main_bss_80137CFC;
extern s32 D_main_bss_80138920;
extern s32 D_main_bss_8013961C;
extern s32 D_main_bss_80139740;
extern u8 *D_main_bss_801395E0[];
extern s16 D_main_bss_80139738;
extern s8 D_main_bss_80139730;
extern s8 D_main_bss_80139734[];
extern s8 D_main_bss_8013973A;
extern f32 D_main_bss_8013973C;
void load_hmt_and_hob(char *, s32, s32, s32);
u8 *getHobObjectByName(char *);
s16 loadAndRelocateAsset(s32 *, s32, s32);
void loadExplosionTextures(void);
s32 rs_malloc(s32, s32);
s32 findAssetAcrossSegments(s32, s32, s32, char *, s32);
void setupAssetDma(s32, s32, s32, s32, s32, s32);
void teardownAssetDma(s32, s32);
void initWeaponSlotIndexTable(void);
s32 load_asset(char *);

void loadWeaponsHobObjects(void) {
    s32 i;
    u8 **s0;
    char **s1;
    u8 *obj;
    char *name;
    u8 *p;
    s8 *q;
    s32 h;
    u32 flag;

    load_hmt_and_hob("weapons", 0, 0, 0);
    i = 0;
    flag = 0x10000;
    s0 = D_main_bss_801395E0;
    s1 = D_main_8009ED00;
    do {
        name = *s1;
        if (name != NULL) {
            obj = getHobObjectByName(name);
            *s0 = obj;
            p = *(u8 **)(*(u8 **)(obj + 0x10) + 0x10);
            *(u32 *)(p + 0xC) |= flag;
        } else {
            *s0 = NULL;
        }
        s0++;
        i++;
        s1++;
    } while (i < 0xF);
    D_main_bss_80139738 = loadAndRelocateAsset(&D_main_8003B168, 0, 0);
    loadExplosionTextures();
    D_main_bss_80139740 = rs_malloc(0x400, 0);
    h = findAssetAcrossSegments(D_main_bss_80138920, 0, D_main_bss_80137CFC, "lights_PAL", 1);
    i = 3;
    setupAssetDma(D_main_bss_80138920, 0, h, 0, 0x400, D_main_bss_80139740);
    teardownAssetDma(D_main_bss_80138920, h);
    q = D_main_bss_80139734 + i;
    do {
        *q = i;
        i -= 1;
        q -= 1;
    } while (i >= 0);
    i = 4;
    D_main_bss_80139730 = i;
    initWeaponSlotIndexTable();
    D_main_bss_8013961C = load_asset("weapon_info");
    D_main_bss_8013973A = 0;
    D_main_bss_8013973C = 0.5f;
}

s32 findSegmentObjectSphereHit(s32, void *, void *, void *);
s32 findNpcInScaledBoxRegion(u8 *arg0, f32 scale, u16 ex, u16 slot, f32 *out) {
    u8 it[8];
    f32 box[3];
    s32 idx;
    s32 mesh;
    u16 best;
    f32 bestDist;

    box[0] = *(f32 *)(arg0 + 0x24) * scale;
    box[1] = *(f32 *)(arg0 + 0x28) * scale;
    best = 0xFFFF;
    (void)0;
    bestDist = 2.0f;
    box[2] = *(f32 *)(arg0 + 0x2C) * scale;
    idx = findActiveNpcInSlotChain(slot, it);
    if ((idx & 0xFFFF) != 0xFFFF) {
        do {
            if (ex == 0xFFFF || ex != (idx & 0xFFFF)) {
                mesh = *(s32 *)(getNpcContextByIndex(idx & 0xFFFF) + 0xC);
                if (mesh != 0) {
                    if (findSegmentObjectSphereHit(mesh, arg0, box, out) != 0) {
                        if (out[6] < bestDist) {
                            bestDist = out[6];
                            best = idx;
                        }
                    }
                }
            }
            idx = revalidateNpcSlotIterator(it);
        } while ((idx & 0xFFFF) != 0xFFFF);
    }
    return best;
}

s32 findSegmentObjectSphereHit(s32, void *, void *, void *);

u16 findNpcInScaledBoxRegionExcludingPair(u8 *arg0, u16 ex1, f32 scale, u16 ex2, u16 slot, void *out) {
    u8 it[8];
    f32 box[3];
    u16 cur;
    s32 idx;
    s32 mesh;

    box[0] = *(f32 *)(arg0 + 0x24) * scale;
    box[1] = *(f32 *)(arg0 + 0x28) * scale;
    box[2] = *(f32 *)(arg0 + 0x2C) * scale;
    idx = findActiveNpcInSlotChain(slot, it);
    if ((idx & 0xFFFF) != 0xFFFF) {
        do {
            cur = idx & 0xFFFF;
            if (cur != ex1) {
                if (ex2 == 0xFFFF || ex2 != cur) {
                    mesh = *(s32 *)(getNpcContextByIndex(cur) + 0xC);
                    if (mesh != 0) {
                        if (findSegmentObjectSphereHit(mesh, arg0, box, out) != 0) {
                            return cur;
                        }
                    }
                }
            }
            idx = revalidateNpcSlotIterator(it);
        } while ((idx & 0xFFFF) != 0xFFFF);
    }
    return 0xFFFF;
}

s32 rs_free(s32);
extern s32 D_main_bss_8013961C;
extern s32 D_main_bss_80139740;

void freeEffectAssetBuffers(void) {
    rs_free(D_main_bss_8013961C);
    rs_free(D_main_bss_80139740);
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 unk1C;
    s16 unk20;
    s32 unk24;
    u8 unk28;
    u8 unk29;
    f32 unk2C;
} ByteAnimDebrisArgs;
void byteAnimatedDebrisNpcHandler();
u16 spawnNpcOfType(void *, void *, u32, u8);
void spawnByteAnimDebrisDefault(f32 *pos) {
    ByteAnimDebrisArgs args;

    args.x = pos[0];
    args.y = pos[1] - 1.0f;
    args.z = pos[2];
    args.unk28 = 0;
    args.unk24 = D_main_bss_80139740;
    args.unk29 = 0x10;
    args.unk1C = 6.0f;
    args.unk20 = 0x300;
    args.unk2C = 20.0f;
    spawnNpcOfType(byteAnimatedDebrisNpcHandler, &args, 2, 15);
}

void spawnByteAnimDebrisWithParam(f32 *pos, u8 arg1) {
    ByteAnimDebrisArgs args;

    args.x = pos[0];
    args.y = pos[1] - 1.0f;
    args.z = pos[2];
    args.unk28 = arg1;
    args.unk24 = D_main_bss_80139740;
    args.unk29 = arg1 + 0x10;
    args.unk1C = 6.0f;
    args.unk20 = 0x300;
    args.unk2C = 20.0f;
    spawnNpcOfType(byteAnimatedDebrisNpcHandler, &args, 2, 15);
}

s16 loadAndRelocateAsset(s32 *, s32, s32);
extern s32 D_main_8003B168;
extern s16 D_main_bss_80139738;

void loadTieBomberSprite(void) {
    D_main_bss_80139738 = loadAndRelocateAsset(&D_main_8003B168, 0, 0);
}

typedef struct {
    f32 x, y, z;
} NpcRayDir;

typedef struct {
    u8 pad0[0xC];
    f32 hx, hy, hz;
} NpcRayHit;

extern NpcRayDir D_main_bss_801395A0;
extern NpcRayHit D_main_bss_801395B0;
s32 findActiveNpcInSlotChain(u16, void *);
u8 *getNpcContextByIndex(u16);
s32 findSegmentObjectSphereHit(s32, void *, void *, void *);
s32 revalidateNpcSlotIterator(void *);

s32 findNpcAlongDirectionRay(u8 *arg0, s32 arg1, f32 *arg2, u16 arg3) {
    u8 sp10[8];
    f32 x;
    f32 y;
    f32 z;
    s32 idx;
    s32 ctx;

    x = *(f32 *)(arg0 + 0x10) * 0.5f;
    D_main_bss_801395A0.x = x;
    y = *(f32 *)(arg0 + 0x14) * 0.5f;
    D_main_bss_801395A0.y = y;
    z = *(f32 *)(arg0 + 0x18) * 0.5f;
    D_main_bss_801395A0.z = z;
    if (x == 0.0f && y == 0.0f && z == 0.0f) {
        return 0;
    }
    idx = findActiveNpcInSlotChain(arg3, sp10);
    if ((idx & 0xFFFF) != 0xFFFF) {
        do {
            idx &= 0xFFFF;
            if (*(u16 *)(arg0 + 0xB6) != idx) {
                ctx = *(s32 *)(getNpcContextByIndex(idx) + 0xC);
                if (ctx != 0) {
                    if (findSegmentObjectSphereHit(ctx, arg0 + 4, &D_main_bss_801395A0, &D_main_bss_801395B0) != 0) {
                        arg2[0] = D_main_bss_801395B0.hx;
                        arg2[1] = D_main_bss_801395B0.hy;
                        arg2[2] = D_main_bss_801395B0.hz;
                        return 1;
                    }
                }
            }
            idx = revalidateNpcSlotIterator(sp10);
        } while ((idx & 0xFFFF) != 0xFFFF);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/5D220", fake_func_8005EE64);
