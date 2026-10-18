#include "common.h"
#include "common_types.h"

#include "main/1D000.h"
#include "mission_overlay/0F09E0.h"
#include "mission_stats.h"
#include "rs_math.h"

extern s32 D_main_bss_80137CE4;

typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    char *n14;
    s8 s18;
    s8 s19;
    u16 h1A;
    u16 h1C;
    u16 h1E;
    u8 b20;
    u8 b21;
    u8 b22;
    u8 b23;
} TgtSel;

s32 findActiveNpcInSlotChain(u16, s32);
void *getNpcContextByIndex(u16);
s32 unregisterAndFreeNpcSlot(u16, void *);
u16 popNpcSlotFromTail(u16, void *);
void *getLevelDatItemByName(char *);
s32 getPlayerField2(s32);
s16 getNpcDetailLevelByIndex(u16);
s32 tgtDetail(u16) __asm__("getNpcDetailLevelByIndex");
void *getNpcContextField8(u16);
s32 revalidateNpcSlotIterator(void *);
f32 vec3Dot(f32 *, f32 *);
f32 vec3Length(f32 *);
s16 tgtRand(void) __asm__("rand");
extern u16 D_main_bss_80139560[];
extern u16 D_main_bss_80139562;
extern s32 D_mission_overlay_8010B320[];
extern s32 D_mission_overlay_8010B330[];

static __inline__ void tgtClear(TgtSel *p) {
    if (p->b20 == 1 && p->h1A != 0xFFFF) {
        if ((findActiveNpcInSlotChain(p->h1C, 0) & 0xFFFF) != 0xFFFF) {
            unregisterAndFreeNpcSlot(p->h1E, getNpcContextByIndex(p->h1E));
        }
        p->h1A = 0xFFFF;
        p->h1E = 0xFFFF;
        p->b20 = 0;
    }
}

static __inline__ s32 tgtSet(TgtSel *p, u16 idx) {
    if (idx != 0xFFFF) {
        p->h1E = popNpcSlotFromTail(p->h1C, getNpcContextByIndex(idx));
        if (p->h1E != 0xFFFF) {
            p->h1A = idx;
            p->b20 = 1;
            return 1;
        }
        p->h1A = 0xFFFF;
        p->b20 = 0;
    }
    return 0;
}

static __inline__ s32 tgtLos(f32 *a, f32 r, f32 th, f32 *b, f32 *out) {
    Vec3f v;

    v[0] = b[0] - a[0];
    v[1] = b[1] - a[1];
    v[2] = b[2] - a[2];
    if ((r * r) < ((v[0] * v[0]) + (v[2] * v[2])) || (vec3Dot(a + 3, v) / (vec3Length(a + 3) * vec3Length(v))) < th) {
        return 0;
    }
    *out = vec3Length(v);
    return 1;
}

s32 func_mission_overlay_800EFDE0(u8 *obj, s32 mode, s32 alt, f32 dt) {
    u8 it[8];
    u16 ids[8];
    f32 d;
    TgtSel *p = (TgtSel *)(obj + 0x114);
    u8 *item;
    register s32 n asm("$23");
    s32 k;
    s32 idx;
    u16 cur;
    u16 best;
    f32 bestD;
    f32 r;
    f32 th;
    u8 fp;
    u8 s6;
    s32 s0;
    s32 s3;

    if (p->b21 != 0 && (p->f10 -= dt, !(p->f10 > 0.0f))) {
    p->f10 = 1.0f;
    if (p->n14 != NULL) {
        item = getLevelDatItemByName(p->n14);
        if (item != NULL && *(u16 *)(item + 6) != 0xFFFF && !(*(u16 *)((u8 *)getNpcContextByIndex(*(u16 *)(item + 6)) + 0x14) & 0x10)) {
            tgtClear(p);
            if (tgtSet(p, *(u16 *)(item + 6)) == 1) {
                return 1;
            }
        }
    }
    if (p->s18 != 6) {
        mode = p->s18;
    }
    if (p->s19 != 6) {
        alt = p->s19;
    }
retry:
    n = 1;
    fp = 0;
    s6 = 0;
    switch (mode) {
        case 7:
            s6 = 1;
        case 0:
            ids[0] = 1;
            fp = 1;
            break;
        case 8:
            fp = 1;
            s6 = 1;
        case 1:
            if (*(s16 *)(obj + 0x19A) == 1) {
                ids[0] = 9;
            } else {
                ids[0] = 7;
            }
            break;
        case 9:
            fp = 1;
            s6 = 1;
        case 2:
            if (*(s16 *)(obj + 0x19A) == 1) {
                ids[0] = 0;
            } else {
                ids[0] = 5;
            }
            break;
        case 10:
            fp = 1;
            s6 = 1;
        case 3:
            if (*(s16 *)(obj + 0x19A) == 1) {
                ids[0] = 8;
            } else {
                ids[0] = 6;
            }
            break;
        case 5:
            if (*(s16 *)(obj + 0x19A) == 1) {
                ids[0] = 0xC;
            } else {
                ids[0] = 0xD;
            }
            break;
        case 4:
            n = 4;
            if (*(s16 *)(obj + 0x19A) == 1) {
                ids[0] = 0xC;
                ids[2] = 9;
                ids[1] = 0;
                ids[3] = 8;
            } else {
                ids[0] = 0xD;
                ids[1] = 5;
                ids[2] = 7;
                ids[3] = 6;
            }
            break;
        case 6:
            tgtClear(p);
            return 0;
    }
    best = 0xFFFF;
    bestD = 0.0f;
    k = 0;
    if (n != 0) {
        do {
        for (idx = findActiveNpcInSlotChain(D_main_bss_80139560[ids[k]], (s32)it); (idx & 0xFFFF) != 0xFFFF; idx = revalidateNpcSlotIterator(it)) {
            cur = idx;
            if (*(u16 *)((u8 *)getNpcContextByIndex(cur) + 0x14) & 0x10) {
                break;
            }
            if (s6 && tgtDetail(cur) != 0) {
                continue;
            }
            if (tgtLos(getNpcContextField8(*(u16 *)(obj + 0x198)), p->f4, p->f0, getNpcContextField8(cur), &d) == 1) {
                if (best == 0xFFFF || d < bestD) {
                    bestD = d;
                    best = idx;
                }
            }
        }
            } while (++k < n);
    }
    if (best == 0xFFFF) {
        if (alt != 6) {
            mode = alt;
            alt = 6;
            goto retry;
        }
        mode = alt;
    }
    if (fp == 0 && *(s16 *)(obj + 0x19A) == 1) {
        s3 = 0;
        s0 = 0;
        if (best == 0xFFFF || (s16)(tgtRand() % 100) < D_mission_overlay_8010B320[D_main_bss_80137CE4]) {
            s0 = 1;
        }
        if ((s16)(tgtRand() % 100) < D_mission_overlay_8010B330[D_main_bss_80137CE4]) {
            s0 = 1;
            r = p->fC;
            th = p->f8;
            s3 = 1;
        } else {
            r = p->f4;
            th = p->f0;
        }
        if (s0 == 1) {
            for (idx = findActiveNpcInSlotChain(D_main_bss_80139562, (s32)it); (idx & 0xFFFF) != 0xFFFF; idx = revalidateNpcSlotIterator(it)) {
                cur = idx;
                if (*(u16 *)((u8 *)getNpcContextByIndex(cur) + 0x14) & 0x10) {
                    break;
                }
                if ((u8)tgtLos(getNpcContextField8(*(u16 *)(obj + 0x198)), r, th, getNpcContextField8(cur), &d) == 1) {
                    if (s3 == 1) {
                        s3 = 0;
                        best = 0xFFFF;
                    }
                    if (best == 0xFFFF || d < bestD) {
                        bestD = d;
                        best = idx;
                        s6 = 1;
                    }
                }
            }
        }
    }
    if (best == (getPlayerField2(0) & 0xFFFF) || p->b23 == 1) {
        p->b23 = (p->b23 == 0);
        p->f10 = 5.0f;
    }
    p->b22 = s6;
    tgtClear(p);
    if (best == 0xFFFF) {
        return 0;
    }
    return tgtSet(p, best);
    }
    return 0;
}

typedef struct {
    u8 pad0[0x1A];
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
    u8 unk20;
    u8 unk21;
} PendingChildNpc;

s32 findActiveNpcInSlotChain(u16, s32);
void *getNpcContextByIndex(u16);
s32 unregisterAndFreeNpcSlot(u16, void *);

static inline void clearPendingChildNpcInline(PendingChildNpc *p) {
    if (p->unk20 == 1 && p->unk1A != 0xFFFF) {
        if ((findActiveNpcInSlotChain(p->unk1C, 0) & 0xFFFF) != 0xFFFF) {
            unregisterAndFreeNpcSlot(p->unk1E, getNpcContextByIndex(p->unk1E));
        }
        p->unk1A = 0xFFFF;
        p->unk1E = 0xFFFF;
        p->unk20 = 0;
    }
}

s32 isPendingChildNpcActive(u8 *obj) {
    PendingChildNpc *p = (PendingChildNpc *)(obj + 0x114);
    u16 idx;

    if (p->unk21 == 0) {
        return 0;
    }
    if (p->unk20 != 0) {
        if (p->unk1C == 0xFFFF) {
            return 0;
        }
        if (p->unk1E == 0xFFFF) {
            return 0;
        }
        if (p->unk1A == 0xFFFF) {
            return 0;
        }
        idx = findActiveNpcInSlotChain(p->unk1C, 0) & 0xFFFF;
        if (idx == 0xFFFF) {
            clearPendingChildNpcInline(p);
            return 0;
        }
        if (*(u16 *)((u8 *)getNpcContextByIndex(idx) + 0x14) & 0x10) {
            clearPendingChildNpcInline(p);
            return 0;
        }
        return 1;
    }
    return 0;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} LosChild;
void *getNpcContextField8(u16);
f32 vec3Dot(f32 *, f32 *);
f32 vec3Length(f32 *);

s32 validateActorTargetLOS(u8 *obj) {
    PendingChildNpc *p = (PendingChildNpc *)(obj + 0x114);
    f32 v[3];
    f32 *a;
    f32 *b;
    f32 d2;
    f32 dot;
    f32 len;
    f32 c;
    f32 r;
    f32 th;
    u16 idx;

    if (p->unk21 == 0) {
        return 0;
    }
    if (p->unk20 == 0) {
        return 0;
    }
    if (p->unk1C == 0xFFFF) {
        return 0;
    }
    if (p->unk1E == 0xFFFF) {
        return 0;
    }
    if (p->unk1A == 0xFFFF) {
        return 0;
    }
    idx = findActiveNpcInSlotChain(p->unk1C, 0) & 0xFFFF;
    if (idx == 0xFFFF || (*(u16 *)((u8 *)getNpcContextByIndex(idx) + 0x14) & 0x10)) {
        clearPendingChildNpcInline(p);
        return 0;
    }
    a = getNpcContextField8(*(u16 *)(obj + 0x198));
    b = getNpcContextField8(idx);
    r = ((LosChild *)p)->unkC;
    th = ((LosChild *)p)->unk8;
    v[0] = b[0] - a[0];
    v[1] = b[1] - a[1];
    v[2] = b[2] - a[2];
    d2 = v[0] * v[0] + v[2] * v[2];
    if (!(r * r < d2)) {
        dot = vec3Dot(a + 3, v);
        len = vec3Length(a + 3);
        c = dot / (len * vec3Length(v));
        if (d2 < 1.0f) {
            if (0.0f <= c) {
                return 1;
            }
        }
        if (!(c < th)) {
            return 1;
        }
    }
    return 0;
}

s32 computeActorAnchorDeltaAfterLOS(u8 *obj) {
    PendingChildNpc *p = (PendingChildNpc *)(obj + 0x114);
    f32 v[3];
    f32 *a;
    f32 *b;
    f32 d2;
    f32 dot;
    f32 len;
    f32 c;
    f32 r;
    f32 th;
    u16 idx;

    if (p->unk21 == 0) {
        return 0;
    }
    if (p->unk20 == 0) {
        return 0;
    }
    if (p->unk1C == 0xFFFF) {
        return 0;
    }
    if (p->unk1E == 0xFFFF) {
        return 0;
    }
    if (p->unk1A == 0xFFFF) {
        return 0;
    }
    idx = findActiveNpcInSlotChain(p->unk1C, 0) & 0xFFFF;
    if (idx == 0xFFFF || (*(u16 *)((u8 *)getNpcContextByIndex(idx) + 0x14) & 0x10)) {
        clearPendingChildNpcInline(p);
        return 0;
    }
    a = getNpcContextField8(*(u16 *)(obj + 0x198));
    b = getNpcContextField8(idx);
    r = ((LosChild *)p)->unk4;
    th = *(f32 *)(obj + 0x114);
    v[0] = b[0] - a[0];
    v[1] = b[1] - a[1];
    v[2] = b[2] - a[2];
    d2 = v[0] * v[0] + v[2] * v[2];
    if (!(r * r < d2)) {
        dot = vec3Dot(a + 3, v);
        len = vec3Length(a + 3);
        c = dot / (len * vec3Length(v));
        if (d2 < 1.0f) {
            if (0.0f <= c) {
                return 1;
            }
        }
        if (!(c < th)) {
            return 1;
        }
    }
    return 0;
}

extern f32 cosf(f32);

s32 evaluateTargetTrackingVisibility(u8 *obj, f32 arg1, f32 arg2) {
    PendingChildNpc *p = (PendingChildNpc *)(obj + 0x114);
    f32 v[3];
    f32 *a;
    f32 *b;
    f32 d2;
    f32 dot;
    f32 len;
    f32 c;
    f32 r;
    f32 th;
    f32 cs;
    u16 idx;

    if (p->unk21 == 0) {
        return 0;
    }
    if (p->unk20 == 0) {
        return 0;
    }
    if (p->unk1C == 0xFFFF) {
        return 0;
    }
    if (p->unk1E == 0xFFFF) {
        return 0;
    }
    if (p->unk1A == 0xFFFF) {
        return 0;
    }
    idx = findActiveNpcInSlotChain(p->unk1C, 0) & 0xFFFF;
    if (idx == 0xFFFF || (*(u16 *)((u8 *)getNpcContextByIndex(idx) + 0x14) & 0x10)) {
        clearPendingChildNpcInline(p);
        return 0;
    }
    a = getNpcContextField8(*(u16 *)(obj + 0x198));
    r = arg1 * 0.25f;
    cs = cosf(arg2 * 0.017453292f);
    b = getNpcContextField8(idx);
    v[0] = b[0] - a[0];
    v[1] = b[1] - a[1];
    v[2] = b[2] - a[2];
    d2 = v[0] * v[0] + v[2] * v[2];
    th = cs;
    if (!(r * r < d2)) {
        dot = vec3Dot(a + 3, v);
        len = vec3Length(a + 3);
        c = dot / (len * vec3Length(v));
        if (d2 < 1.0f) {
            if (0.0f <= c) {
                return 1;
            }
        }
        if (!(c < th)) {
            return 1;
        }
    }
    return 0;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s32 (*fn)(void *, s32);
    s16 unk1C;
    s16 unk1E;
    s32 unk20;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    u8 unk29;
    s8 unk2A;
    u8 unk2B;
} TickSub;
extern s32 rand(void);
void tickObjectAnimSubstruct(u8 *obj, TickSub *sub, f32 arg2, f32 arg3) {

    if (sub->fn == NULL) return;
    sub->unkC = sub->unkC - arg2;
    if (!(sub->unkC <= 0.0f) && !(0.0f < sub->unk10)) return;
    if (0.0f < sub->unk10) {
        sub->unk10 = sub->unk10 - arg2;
        if (sub->unk10 <= 0.0f && sub->unk2B != 0) {
            sub->unk10 = 0.0f;
            sub->unk28 = sub->unk28 + 1;
            if (sub->fn(getNpcContextByIndex(*(u16 *)(obj + 0x198)), (s8)sub->unk28) != 0) {
                sub->fn = NULL;
            }
        }
    } else if (sub->unk2B != 0) {
        sub->unk10 = 0.0f;
        sub->unk28 = 0;
        if (sub->fn(getNpcContextByIndex(*(u16 *)(obj + 0x198)), 0) != 0) {
            sub->fn = NULL;
        }
        sub->unk1E++;
        if (sub->unk1E >= sub->unk1C) {
            if (sub->unk4 == 0.0f) {
                sub->unk1E = 0;
            } else {
                sub->unk2B = 0;
                sub->unkC = sub->unk4;
                return;
            }
        }
        sub->unkC = sub->unk0 / (f32)sub->unk1C;
        if (sub->unk8 != 0.0f) {
            f32 r;
            f32 x = ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / sub->unk8);
            FABSF(r, x);
            sub->unkC = sub->unkC + r;
        }
    } else {
        sub->unkC = 0.0f;
        sub->unk2B = 1;
        sub->unk1E = 0;
        sub->unk10 = 0.0f;
        sub->unk28 = 0;
    }
}

s32 transformMeshPartIntoWorld(s32, s32);
s32 zmemcpy(s32, s32, s32);
void vec3Cross(f32 *, f32 *, f32 *);

static __inline__ s32 rnapMeshInl(void *arg0, s32 arg1) {
    void *temp_s0;

    temp_s0 = getNpcContextByIndex(findActiveNpcInSlotChain((*(u16 *)((u8 *)(arg0) + 0x130)), 0) & 0xFFFF);
    if ((arg1 == 0) || ((*(s32 *)((u8 *)(temp_s0) + 0xC)) == 0)) {
        return (*(s32 *)((u8 *)(temp_s0) + 8));
    }
    zmemcpy(arg1, (*(s32 *)((u8 *)(temp_s0) + 8)), 0x30);
    transformMeshPartIntoWorld((*(s32 *)((u8 *)(temp_s0) + 0xC)), arg1);
    return arg1;
}

static __inline__ f32 rnapTurnInl(Mat4x3 arg0, Vec3f arg1, struct Struct3f *arg2) {
    Vec3f sp10;
    struct Struct3f sp20;
    f32 temp_fs0;

    sp10[0] = arg1[0] - arg0[0][0];
    sp10[1] = arg1[1] - arg0[0][1];
    sp10[2] = arg1[2] - arg0[0][2];
    temp_fs0 = constMinusSinfApprox(vec3Dot(arg0[1], sp10) / (vec3Length(arg0[1]) * vec3Length(sp10))) * 57.29578f;
    vec3Cross((f32 *)&sp20, arg0[1], sp10);
    if (vec3Length((f32 *)&sp20) != 0.0f) {
        normalize_vector((f32 *)&sp20);
    }
    *arg2 = sp20;
    return temp_fs0;
}

void resolveNpcAttachmentPos(u8 *arg0, f32 *arg1, f32 arg2, f32 arg3) {
    Mat4x3 sp10;
    Vec3f sp40;
    f32 ang;
    f32 r;

    computeAnchorRelativePositionByDistanceRatio(arg1, (void *)rnapMeshInl(arg0, (s32)sp10), arg2, sp40);
    *(struct Struct3f *)sp10 = *(struct Struct3f *)sp40;
    ang = rnapTurnInl((void *)arg1, sp10[0], (struct Struct3f *)sp40);
    FABSF(r, ang);
    if (r > 0.1f) {
        Vec4f q;
        if (arg3 < ang) {
            ang = arg3;
        } else if (ang < -arg3) {
            ang = -arg3;
        }
        quatFromAxisAngleSafe(q, sp40, ang);
        rotateVec3ByQuat(q, arg1 + 3, arg1 + 3);
        rotateVec3ByQuat(q, arg1 + 6, arg1 + 6);
    }
}

static __inline__ void swapKV(f32 *keys, u16 *vals, s32 a, s32 b) {
    f32 tf = keys[a];
    u16 tu;

    keys[a] = keys[b];
    keys[b] = tf;
    tu = vals[a];
    vals[a] = vals[b];
    vals[b] = tu;
}

void quicksortFloatKeysWithValues(f32 *keys, u16 *vals, s32 lo, s32 hi) {
    s32 last;
    s32 i;

    if (lo < hi) {
        swapKV(keys, vals, lo, (lo + hi) / 2);
        last = lo;
        for (i = lo + 1; i <= hi; i++) {
            if (keys[i] < keys[lo]) {
                last++;
                swapKV(keys, vals, last, i);
            }
        }
        swapKV(keys, vals, lo, last);
        quicksortFloatKeysWithValues(keys, vals, lo, last - 1);
        quicksortFloatKeysWithValues(keys, vals, last + 1, hi);
    }
}

typedef struct { f32 x, y, z; } GsV3;
typedef struct {
    GsV3 pos;
    GsV3 n;
    f32 d;
    f32 e;
    u8 pad20[8];
} GsHit;
typedef struct {
    s16 cnt;
    u16 ids[8];
    u8 pad12[2];
    f32 range;
    s16 done;
    u8 pad1A[2];
    f32 dist;
    f32 keys[8];
    u8 it[8];
    GsV3 dir;
    GsV3 org;
} GsState;
extern u8 D_main_bss_80138058[];
s32 gsSample(GsV3 *, GsV3 *, void *, GsHit *) __asm__("sampleTerrainAtNpcPosition");
s32 gsFindActive(u16, void *) __asm__("findActiveNpcInSlotChain");
u8 *gsCtx(u16) __asm__("getNpcContextByIndex");
s32 gsHitTest(s32, void *, void *, void *) __asm__("findSegmentObjectSphereHit");
s32 gsRevalidate(void *) __asm__("revalidateNpcSlotIterator");
void gsSort(f32 *, u16 *, s32, s32) __asm__("quicksortFloatKeysWithValues");

static __inline__ u16 gsNext(GsState *st, s32 idx) {
    GsHit hit;
    u16 cur;

    while ((idx & 0xFFFF) != 0xFFFF) {
        cur = idx;
        if (gsHitTest(*(s32 *)(gsCtx(cur) + 0xC), &st->org, &st->dir, &hit) != 0) {
            st->dist = hit.d;
            return cur;
        }
        idx = gsRevalidate(st->it);
    }
    st->done = 1;
    return 0xFFFF;
}

s16 gatherAndSortNearbyNpcViewPoints(f32 *src, u16 chain, GsState *st) {
    u16 n;
    f32 k;
    u16 v;
    s16 one;

    st->done = 0;
    st->org = *(GsV3 *)src;
    st->dist = 0.0f;
    st->cnt = 0;
    st->dir.x = src[3] * st->range;
    st->dir.y = src[4] * st->range;
    st->dir.z = src[5] * st->range;
    {
        GsHit hit;
        if (gsSample(&st->org, &st->dir, D_main_bss_80138058, &hit) != 0) {
            st->dir.x = hit.pos.x - st->org.x;
            st->dir.y = hit.pos.y - st->org.y;
            st->dir.z = hit.pos.z - st->org.z;
            st->range = hit.e;
        }
    }
    n = gsNext(st, gsFindActive(chain, st->it));
    while (st->cnt < 8) {
        s32 ff = 0xFFFF;
        one = 1;
        if (n == ff) {
            break;
        }
        st->keys[st->cnt] = st->dist;
        st->ids[st->cnt] = n;
        st->cnt++;
        if (st->done == 0) {
            s32 idx = gsRevalidate(st->it);
            while ((idx & 0xFFFF) != 0xFFFF) {
                s32 cur = idx & 0xFFFF;
                GsHit hit;
                if (gsHitTest(*(s32 *)(gsCtx(cur) + 0xC), &st->org, &st->dir, &hit) != 0) {
                    st->dist = hit.d;
                    n = cur;
                    goto next;
                }
                idx = gsRevalidate(st->it);
            }
            st->done = one;
        }
        n = 0xFFFF;
    next:;
    }
    if (st->cnt >= 3) {
        gsSort(st->keys, st->ids, 0, st->cnt - 1);
    } else if (st->cnt == 2) {
        if (st->keys[0] > st->keys[1]) {
            k = st->keys[0];
            st->keys[0] = st->keys[1];
            st->keys[1] = k;
            v = st->ids[0];
            st->ids[0] = st->ids[1];
            st->ids[1] = v;
        }
    }
    return st->cnt;
}

typedef struct {
    f32 pos[3];
    f32 dir[3];
    f32 ang;
    f32 maxr;
    f32 minr;
    u8 *list;
    u16 ignore;
    u8 flag;
    u8 pad2B;
    u16 ids[32];
} AcState;
typedef struct {
    u8 pad0[8];
    f32 *pos;
    s32 mesh;
    u8 pad10[4];
    u16 h14;
} AcCtx;
extern f32 cosf(f32);
AcCtx *acCtx(u16) __asm__("getNpcContextByIndex");
s32 acFind(u16, void *) __asm__("findActiveNpcInSlotChain");
void acXform(s32, f32 *) __asm__("transformMeshPartIntoWorld");
void acSort(f32 *, u16 *, s32, s32) __asm__("quicksortFloatKeysWithValues");

s32 acquireNpcTargetsInAimCone(AcState *p) {
    u8 it[8];
    f32 v[3];
    f32 keys[32];
    s32 n;
    s32 k;
    f32 cs;
    u16 idx;
    f32 d2;
    f32 dot;
    f32 *q;
    AcCtx *ctx;

    n = 0;
    k = n;
    cs = cosf(p->ang * 0.017453292f);
    p->ids[0] = 0xFFFF;
    while (p->list[k] != 0xFF) {
        for (idx = acFind(D_main_bss_80139560[p->list[k]], it); idx != 0xFFFF; idx = revalidateNpcSlotIterator(it)) {
            if (idx == p->ignore) {
                continue;
            }
            ctx = acCtx(idx);
            if (p->flag && (ctx->h14 & 0x100)) {
                continue;
            }
            if (ctx->mesh != 0) {
                acXform(ctx->mesh, v);
                q = v;
            } else {
                q = ctx->pos;
                if (q == NULL) {
                    continue;
                }
            }
            v[0] = q[0] - p->pos[0];
            v[1] = q[1] - p->pos[1];
            v[2] = q[2] - p->pos[2];
            d2 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
            if (d2 <= p->maxr * p->maxr && p->minr * p->minr <= d2) {
                dot = vec3Dot(p->dir, v) / vec3Length(v);
                if (cs <= dot) {
                    f32 sq;
                    p->ids[n] = idx;
                    SQRTF(sq, d2);
                    keys[n] = (1.0f - dot) * 100.0f + sq;
                    n++;
                    if (n == 32) {
                        goto done;
                    }
                }
            }
        }
        k++;
    }
done:
    if (n >= 3) {
        acSort(keys, p->ids, 0, n - 1);
    } else if (n == 2) {
        if (keys[0] > keys[1]) {
            f32 t = keys[0];
            u16 u = p->ids[0];
            keys[0] = keys[1];
            p->ids[0] = p->ids[1];
            keys[1] = t;
            p->ids[1] = u;
        }
    }
    return n;
}

typedef struct { f32 x, y, z; } TpV3;
typedef struct {
    s16 cnt;
    u16 ids[8];
    u8 pad12[2];
    f32 range;
    s16 done;
    u8 pad1A[2];
    f32 dist;
    f32 keys[8];
    u8 it[8];
    TpV3 dir;
    TpV3 org;
} TpState;
typedef struct {
    u8 pad0[0x20];
    f32 f20;
    s16 h24;
    u8 pad26[3];
    u8 b29;
} TpCh;
typedef struct {
    u8 pad0[0x10];
    u8 *p10;
    u8 pad14;
    u8 b15;
} TpCtx;
extern u16 D_main_bss_8013957C;
s32 tpGather(f32 *, u16, TpState *) __asm__("gatherAndSortNearbyNpcViewPoints");
TpCtx *tpCtx(u16) __asm__("getNpcContextByIndex");

#define TP_TEAM(id) ({ TpCtx *c_ = tpCtx(id); c_->p10 != NULL ? *(s16 *)(c_->p10 + 0x19A) : 3 - (c_->b15 >> 6); })

s32 tpImpl(u8 *obj, f32 *src, TpCh *ch, f32 *out) __asm__("tickProgressChannel");
s32 tpImpl(u8 *obj, f32 *src, TpCh *ch, f32 *out) {
    TpState st;
    f32 r;
    u8 hit;
    s32 n;
    s32 i;
    u16 id;

    switch ((s32)ch) {
    case 0:
        r = *(s16 *)(obj + 0x15C) / 100.0f;
        break;
    case 1:
        r = *(s16 *)(obj + 0x188) / 100.0f;
        break;
    default:
        r = ch->h24 / 100.0f;
        break;
    }
    hit = 0;
    st.range = r;
    n = tpGather(src, D_main_bss_8013957C, &st);
    if (st.range != r) {
        hit = 1;
        if (out != NULL) {
            *out = st.range;
        }
    } else if (out != NULL) {
        *out = 0.0f;
    }
    switch ((s32)ch) {
    case 0:
        obj[0x161] = hit;
        *(f32 *)(obj + 0x158) = st.range;
        break;
    case 1:
        obj[0x18D] = hit;
        *(f32 *)(obj + 0x184) = st.range;
        break;
    default:
        ch->b29 = hit;
        ch->f20 = st.range;
        break;
    }
    if (n == 0) {
        return 1;
    }
    if (*(s16 *)(obj + 0x19A) == 1) {
        if (obj[0x136] == 0) {
            for (i = 0; i < n; i++) {
                id = st.ids[i];
                if (id == *(u16 *)(obj + 0x198)) {
                    if (i + 1 == n) {
                        return 1;
                    }
                } else {
                    if (TP_TEAM(id) == 1) {
                        goto ret0;
                    }
                    return 1;
                }
            }
        } else {
            for (i = 0; i < n; i++) {
                id = st.ids[i];
                if (id == *(u16 *)(obj + 0x198)) {
                    if (i + 1 == n) {
                        return 1;
                    }
                } else {
                    if (TP_TEAM(id) != 0) {
                        goto ret0;
                    }
                    return 1;
                }
            }
        }
    } else {
        for (i = 0; i < n; i++) {
            id = st.ids[i];
            if (id == *(u16 *)(obj + 0x198)) {
                if (i + 1 == n) {
                    return 1;
                }
            } else {
                if (TP_TEAM(id) != 1) {
                    goto ret0;
                }
                return 1;
            }
        }
    }
ret0:
    return 0;
}

typedef struct { f32 x, y, z; } RcV3;
typedef struct { u8 a, b; } RcPair;
typedef struct { RcV3 pos; RcV3 n; f32 u; f32 d; f32 e; f32 g; } RcHit;
extern u8 D_main_bss_80138058[];
extern u16 D_main_bss_80139560[];
extern u8 D_mission_overlay_8010B340[];
extern s32 sampleTerrainAtNpcPosition(f32 *, RcV3 *, void *, RcHit *);
extern void sampleTerrainSurfaceAtWorldXz(f32, f32, void *, RcHit *);
extern s32 revalidateNpcSlotIterator(void *);
extern s32 findSegmentObjectSphereHit(s32, void *, void *, void *);
extern f32 projectPointOntoObjectSphereHit(s32, void *, void *);

f32 raycastTerrainAndNpcs(f32 *org, f32 *dir, u16 ignore, u16 *outIdx, f32 maxd, f32 stop, f32 *outDist, RcV3 *outN, u32 flags, u8 *outFlag) {
    RcHit hit;
    u8 it[8];
    RcV3 v;
    s32 k;
    s32 idx;
    f32 d;
    s32 mesh;
    u8 fl;
    u16 cur;

    *outIdx = ignore;
    fl = flags;
    *outFlag = 0;
    if (maxd == 0.0f) {
        return 0.0f;
    }
    v.x = dir[0] * maxd;
    v.y = dir[1] * maxd;
    v.z = dir[2] * maxd;
    if (flags & 1) {
        if (sampleTerrainAtNpcPosition(org, &v, D_main_bss_80138058, &hit)) {
            v.x = hit.pos.x - org[0];
            v.y = hit.pos.y - org[1];
            v.z = hit.pos.z - org[2];
            *outIdx = 0xFFFF;
            sampleTerrainSurfaceAtWorldXz(hit.pos.x, hit.pos.z, D_main_bss_80138058, &hit);
            *outN = hit.n;
            *outFlag |= 1;
            if (outDist != NULL) {
                *outDist = hit.d;
            }
            maxd = hit.d;
            if (maxd <= stop) {
                return maxd;
            }
        }
    }
    if ((fl & 2) && D_mission_overlay_8010B340[0] != 0xFF) {
        k = 0;
        do {
            if (((RcPair *)D_mission_overlay_8010B340)[k].b == 0) {
                for (idx = findActiveNpcInSlotChain(D_main_bss_80139560[((RcPair *)D_mission_overlay_8010B340)[k].a], (s32)it); (idx & 0xFFFF) != 0xFFFF && (cur = idx) != ignore; idx = revalidateNpcSlotIterator(it)) {
                    {
                        mesh = *(s32 *)((u8 *)getNpcContextByIndex(cur) + 0xC);
                        if (mesh != 0) {
                            if (findSegmentObjectSphereHit(mesh, org, &v, &hit) != 0) {
                                if (hit.d < maxd) {
                                    maxd = hit.d;
                                    *outIdx = idx;
                                    *outFlag |= 2;
                                    if (maxd <= stop) {
                                        return maxd;
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                for (idx = findActiveNpcInSlotChain(D_main_bss_80139560[((RcPair *)D_mission_overlay_8010B340)[k].a], (s32)it); (idx & 0xFFFF) != 0xFFFF && (cur = idx) != ignore; idx = revalidateNpcSlotIterator(it)) {
                    {
                        mesh = *(s32 *)((u8 *)getNpcContextByIndex(cur) + 0xC);
                        if (mesh != 0) {
                            d = projectPointOntoObjectSphereHit(mesh, org, &v);
                            if (0.0f < d && d < maxd) {
                                maxd = d;
                                *outIdx = idx;
                                *outFlag |= 2;
                                if (maxd <= stop) {
                                    return maxd;
                                }
                            }
                        }
                    }
                }
            }
k++;
        } while (((RcPair *)D_mission_overlay_8010B340)[k].a != 0xFF);
    }
    return maxd;
}

typedef struct { f32 x, y, z; } Vec3Cp2;

void *getNpcContextField8(u16);
void parseDatItemCommon(void *, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);

s32 initActorRenderDescriptorIfUninit(u8 *arg0, u8 arg1, u8 *arg2, u8 arg3, s32 *arg4) {
    s32 *p;
    s32 *q = arg4;
    Vec3Cp2 *npc;

    if (arg0[0x1A7] == 0) {
        *(u16 *)(arg2 + 6) = 0xFFFF;
        if (arg1 == 0 && !(*(u32 *)(arg0 + 0x1A4) & 0xFF00FF00)) {
            if (arg3 == 1) {
                npc = getNpcContextField8(*(u16 *)(arg0 + 0x198));
                *(Vec3Cp2 *)(arg2 + 0x10) = *npc;
            }
            parseDatItemCommon(arg2, arg2 + 0x10);
        }
    } else {
        if (*(u16 *)(arg2 + 6) == *(u16 *)(arg0 + 0x198)) {
            *(u16 *)(arg2 + 6) = 0xFFFF;
        }
        if (arg1 == 0 && !(*(u32 *)(arg0 + 0x1A4) & 0xFF00FF00)) {
            p = *(s32 **)(arg0 + 0x19C);
            if (p != NULL) {
                *p = *p - 1;
            }
        } else {
            p = *(s32 **)(arg0 + 0x19C);
            if (p != NULL) {
                *p = *p - 1;
            }
            p = *(s32 **)(arg0 + 0x1A0);
            if (p != NULL) {
                *p = *p + 1;
            }
        }
    }
    if (arg0[0x1A5] != 0 && arg4 != NULL) {
        datItemSetObjectiveBooleanCount(q[0], q[1], q[2], q[3], q[4], q[5]);
    }
    return 1;
}

void *getNpcContextField8(u16);
void computeBillboardFacingVector(void *, void *);

typedef struct { f32 x, y, z; } Vec3Cp;

void initActorRenderDescriptorWithNpcVelocity(u8 *arg0, u8 *arg1) {
    Vec3Cp sp10;
    Vec3Cp *npc;

    if (arg0[0x1A7] == 0) {
        npc = getNpcContextField8(*(u16 *)(arg0 + 0x198));
        computeBillboardFacingVector(npc, &sp10);
        *(Vec3Cp *)(arg1 + 0x10) = *npc;
        *(Vec3Cp *)(arg1 + 0x1C) = sp10;
    }
}

s32 setNpcHealth(u8* npc, s32* health, u8* record) {
    u8* rec = record;

    if (npc[0x1A7] == 0) {
        *(s32**)(npc + 0x190) = health;
        if (*(s32*)(record + 0x54) == (s32)0x80000000) {
            *(s32*)(record + 0x54) = health[D_main_bss_80137CE4];
        }
        *(s32*)(npc + 0x194) = *(s32*)(rec + 0x54);
    } else {
        *(s32*)(npc + 0x190) = health[D_main_bss_80137CE4];
        *(s32*)(npc + 0x194) = health[D_main_bss_80137CE4];
    }
    return health[D_main_bss_80137CE4];
}

s32 getNpcCurrentHealth(u8* npc) {
    if (npc[0x1A7] != 0) {
        return *(s32*)(npc + 0x190);
    }
    return (*(s32**)(npc + 0x190))[D_main_bss_80137CE4];
}

void dealDamageToNpc(u8* npc, s32 damage) {
    if (npc[0x1A7] == 0) {
        (*(s32**)(npc + 0x190))[D_main_bss_80137CE4] -= damage;
    } else {
        *(s32*)(npc + 0x190) -= damage;
    }
}

s32 getNpcMissingHealth(u8* npc) {
    if (npc[0x1A7] != 0) {
        return *(s32*)(npc + 0x194) - *(s32*)(npc + 0x190);
    }
    return *(s32*)(npc + 0x194) - (*(s32**)(npc + 0x190))[D_main_bss_80137CE4];
}

f32 getNpcHealthPercentage(u8* npc) {
    if (npc[0x1A7] != 0) {
        return ((f32)*(s32*)(npc + 0x190) / (f32)*(s32*)(npc + 0x194)) * 100.0f;
    }
    return ((f32)(*(s32**)(npc + 0x190))[D_main_bss_80137CE4] / (f32)*(s32*)(npc + 0x194)) * 100.0f;
}

s32 isVectorWithinConeAndRange(Mat4x3 arg0, f32 arg1, f32 arg2, Vec3f arg3) {
    Vec3f sp10;
    f32 temp_fs1_2;
    f32 temp_fs2;
    s32 var_v0;

    sp10[0] = arg3[0] - arg0[0][0];
    sp10[1] = arg3[1] - arg0[0][1];
    sp10[2] = arg3[2] - arg0[0][2];
    temp_fs2 = ((sp10[0] * sp10[0]) + (sp10[2] * sp10[2]));
    if ((arg1 * arg1) < temp_fs2) {
        return 0;
    }
    temp_fs1_2 = vec3Dot(arg0[1], sp10) / (vec3Length(arg0[1]) * vec3Length(sp10));
    // I hate that this matches :(
    if (!(temp_fs2 < 1.0f) || (var_v0 = 1, !(temp_fs1_2 >= 0.0f))) {
        if (!(temp_fs1_2 < arg2)) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
    }
    return var_v0;
}

s32 isVectorInConeWriteDistance(Mat4x3 arg0, f32 arg1, f32 arg2, Vec3f arg3, f32 *arg4) {
    Vec3f sp10;

    sp10[0] = arg3[0] - arg0[0][0];
    sp10[1] = arg3[1] - arg0[0][1];
    sp10[2] = arg3[2] - arg0[0][2];
    if (!((arg1 * arg1) < ((sp10[0] * sp10[0]) + (sp10[2] * sp10[2])))) {
        if (!((vec3Dot(arg0[1], sp10) / (vec3Length(arg0[1]) * vec3Length(sp10))) < arg2)) {
            *arg4 = vec3Length(sp10);
            return 1;
        }
    }
    return 0;
}

s32 computeTurnAxisTowardTarget(Mat4x3 arg0, f32 arg1, f32 arg2, Vec3f arg3, UNIDENTIFIED_TYPE *arg4, struct Struct3f *arg5) {
    Vec3f sp10;
    struct Struct3f sp20;
    f32 *temp_s1;
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_ft0;
    f32 temp_fv0;

    sp10[0] = arg3[0] - arg0[0][0];
    sp10[1] = arg3[1] - arg0[0][1];
    sp10[2] = arg3[2] - arg0[0][2];
    if (((arg1 * arg1) < ((sp10[0] * sp10[0]) + (sp10[2] * sp10[2])))) return 0;

    normalize_vector(sp10);
    temp_fa0 = vec3Dot(arg0[1], sp10) / (vec3Length(arg0[1]) * vec3Length(sp10));
    if (temp_fa0 < arg2) return 0;

    constMinusSinfApprox(temp_fa0);
    vec3Cross(&sp20, arg0[1], sp10);
    if (vec3Length(&sp20) != 0.0f) {
        normalize_vector(&sp20);
    }
    *arg5 = sp20;
    return 1;
}

f32 computeTurnVectorTowardTarget(Mat4x3 arg0, Vec3f arg1, struct Struct3f *arg2, f32 *arg3) {
    Vec3f sp10;
    struct Struct3f sp20;
    f32 temp_fs0;

    sp10[0] = arg1[0] - arg0[0][0];
    sp10[1] = arg1[1] - arg0[0][1];
    sp10[2] = arg1[2] - arg0[0][2];
    temp_fs0 = constMinusSinfApprox(vec3Dot(arg0[1], sp10) / (vec3Length(arg0[1]) * vec3Length(sp10))) * 57.29578f;
    vec3Cross(&sp20, arg0[1], sp10);
    if (vec3Length(&sp20) != 0.0f) {
        normalize_vector(&sp20);
    }
    *arg2 = sp20;
    return temp_fs0;
}

// https://decomp.me/scratch/D6Lx1
f32 computeTurnVectorAndDistanceToTarget(Mat4x3 arg0, Vec3f arg1, struct Struct3f *arg2, f32 *arg3) {
    Vec3f sp10;
    struct Struct3f sp20;
    f32 temp_fs0;

    sp10[0] = arg1[0] - arg0[0][0];
    sp10[1] = arg1[1] - arg0[0][1];
    sp10[2] = arg1[2] - arg0[0][2];
    *arg3 = vec3Length(sp10);
    temp_fs0 = constMinusSinfApprox(vec3Dot(arg0[1], sp10) / (vec3Length(arg0[1]) * vec3Length(sp10))) * 57.29578f;
    vec3Cross(&sp20, arg0[1], sp10);
    if (vec3Length(&sp20) != 0.0f) {
        normalize_vector(&sp20);
    }
    *arg2 = sp20;
    return temp_fs0;
}

typedef struct {
    u8 active;
    u8 pad1[7];
    Mat4x3 matrix;
    u8 pad38[0x144 - 0x38];
} TriggerVolume;

extern TriggerVolume D_main_bss_80138D18[];

u8 transformVec3ToNpcLocalWithScale(Mat4x3, s32, f32 *, f32, f32 *);

s32 isPointInsideTriggerVolume(f32 *point, f32 scale) {
    s32 i;
    f32 local[2];

    TriggerVolume *tv;

    for (i = 0; i < 1; i++) {
        tv = &D_main_bss_80138D18[i];
        if (tv->active != 0 && transformVec3ToNpcLocalWithScale(tv->matrix, 0, point, scale, local)) {
            return 1;
        }
    }
    return 0;
}

void *getNpcContextByIndex(u16);

s16 getNpcDetailLevelByIndex(u16 index) {
    u8 *ctx = getNpcContextByIndex(index);
    u8 *npc = *(u8 **)(ctx + 0x10);

    if (npc != NULL) {
        return *(s16 *)(npc + 0x19A);
    }
    return 3 - (ctx[0x15] >> 6);
}

void *getNpcContextByIndex(u16);

void setObjectDetailLevel(void *arg0, s16 arg1) {
    void *temp_v0;

    (*(s16 *)((u8 *)(arg0) + 0x19A)) = arg1;
    temp_v0 = getNpcContextByIndex((*(u16 *)((u8 *)(arg0) + 0x198)));
    (*(u16 *)((u8 *)(temp_v0) + 0x14)) = (u16) (((*(u16 *)((u8 *)(temp_v0) + 0x14)) & 0xFF3F) | ((3 - arg1) << 6));
}

s16 getObjectDetailLevel(void *arg0) {
    return (*(s16 *)((u8 *)(arg0) + 0x19A));
}

f32 cosf(f32);
s32 rand(void);

void initActorMotionParams(u8 *actor, f32 angleA, f32 speedA, f32 angleB, f32 speedB) {
    *(f32 *)(actor + 0x114) = cosf(angleA * 0.017453292f);
    *(f32 *)(actor + 0x118) = speedA * 0.25f;
    *(f32 *)(actor + 0x11C) = cosf(angleB * 0.017453292f);
    *(f32 *)(actor + 0x120) = speedB * 0.25f;
    *(f32 *)(actor + 0x124) = (s16)((s16)rand() % 30) * 0.033333335f;
    actor[0x136] = 0;
    actor[0x137] = 0;
    actor[0x135] = 1;
}

s32 transformMeshPartIntoWorld(s32, s32);
s32 zmemcpy(s32, s32, s32);

s32 getObjectMeshTransformOrLocal(void *arg0, s32 arg1) {
    void *temp_s0;

    temp_s0 = getNpcContextByIndex(findActiveNpcInSlotChain((*(u16 *)((u8 *)(arg0) + 0x130)), 0) & 0xFFFF);
    if ((arg1 == 0) || ((*(s32 *)((u8 *)(temp_s0) + 0xC)) == 0)) {
        return (*(s32 *)((u8 *)(temp_s0) + 8));
    }
    zmemcpy(arg1, (*(s32 *)((u8 *)(temp_s0) + 8)), 0x30);
    transformMeshPartIntoWorld((*(s32 *)((u8 *)(temp_s0) + 0xC)), arg1);
    return arg1;
}

s32 findActiveNpcInSlotChain(u16, s32);

s32 getObjectNpcTypeId(void *arg0) {
    return findActiveNpcInSlotChain((*(u16 *)((u8 *)(arg0) + 0x130)), 0) & 0xFFFF;
}

s32 unregisterAndFreeNpcSlot(u16, void *);

void clearPendingChildNpc(s32 arg0) {
    void *temp_s0;

    temp_s0 = arg0 + 0x114;
    if (((*(u8 *)((u8 *)(temp_s0) + 0x20)) == 1) && ((*(u16 *)((u8 *)(temp_s0) + 0x1A)) != 0xFFFF)) {
        if ((findActiveNpcInSlotChain((*(u16 *)((u8 *)(temp_s0) + 0x1C)), 0) & 0xFFFF) != 0xFFFF) {
            unregisterAndFreeNpcSlot((*(u16 *)((u8 *)(temp_s0) + 0x1E)), getNpcContextByIndex((*(u16 *)((u8 *)(temp_s0) + 0x1E))));
        }
        (*(u16 *)((u8 *)(temp_s0) + 0x1A)) = 0xFFFFU;
        (*(u16 *)((u8 *)(temp_s0) + 0x1E)) = 0xFFFFU;
        (*(u8 *)((u8 *)(temp_s0) + 0x20)) = 0U;
    }
}

void setObjectFlagBit4(void *arg0) {
    (*(u16 *)((u8 *)(arg0) + 0x14)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x14)) | 0x10);
}

void clearObjectFlagBit4(void *arg0) {
    (*(u16 *)((u8 *)(arg0) + 0x14)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x14)) & 0xFFEF);
}

void computeAnchorRelativePositionByDistanceRatio(Vec3f arg0, Mat4x3 arg1, f32 arg2, Vec3f arg3) {
    Vec3f sp10;
    f32 temp_fv0;
    f32 var_ft0;

    sp10[0] = arg1[0][0] - arg0[0];
    sp10[1] = arg1[0][1] - arg0[1];
    sp10[2] = arg1[0][2] - arg0[2];
    temp_fv0 = vec3Length(sp10);
    if (arg2 > 0.0f) {
        var_ft0 = temp_fv0 / arg2;
    } else {
        var_ft0 = 0.0f;
    }
    arg3[0] = (f32) (arg1[0][0] + (arg1[3][0] * var_ft0));
    arg3[1] = (f32) (arg1[0][1] + (arg1[3][1] * var_ft0));
    arg3[2] = (f32) (arg1[0][2] + (arg1[3][2] * var_ft0));
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    s32 unk10;
    f32 unk14;
    s32 unk18;
    s16 unk1C;
    s16 unk1E;
    s32 unk20;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    u8 unk29;
    s8 unk2A;
    u8 unk2B;
} ObjectAnimSubstruct;

void initObjectAnimSubstruct(u8 *obj, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 useAlt, f32 arg7, f32 arg8, f32 arg9) {
    ObjectAnimSubstruct *sub;
    f32 angle;

    if (useAlt == 0) {
        sub = (ObjectAnimSubstruct *)(obj + 0x138);
    } else {
        sub = (ObjectAnimSubstruct *)(obj + 0x164);
    }
    angle = arg9;
    sub->unk0 = arg1;
    sub->unk4 = arg2;
    sub->unk1C = arg3;
    if (sub->unk1C == 0) {
        sub->unk1C++;
    }
    sub->unk8 = arg4;
    sub->unk18 = arg5;
    sub->unkC = 0;
    sub->unk2B = 1;
    sub->unk1E = 0;
    sub->unk10 = 0;
    sub->unk28 = 0;
    sub->unk14 = 1.0f;
    sub->unk24 = arg8 * 100.0f;
    sub->unk26 = arg7 * 100.0f;
    if (angle > 45.0f) {
        angle = 45.0f;
    }
    sub->unk29 = 0;
    sub->unk20 = 0;
    sub->unk2A = angle * 2.8222222f;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    s32 unkC;
    s32 unk10;
    f32 unk14;
    s32 unk18;
    s16 unk1C;
    s16 unk1E;
    s32 unk20;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    u8 unk29;
    s8 unk2A;
    u8 unk2B;
} AnimSubstruct;

void initAnimSubstructFromParams(AnimSubstruct *sub, s32 arg1, s32 arg2, f32 arg3, f32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    sub->unk0 = arg1;
    sub->unk4 = arg2;
    sub->unk1C = arg3;
    if (sub->unk1C == 0) {
        sub->unk1C++;
    }
    sub->unk8 = arg4;
    sub->unk18 = arg5;
    sub->unkC = 0;
    sub->unk2B = 1;
    sub->unk1E = 0;
    sub->unk10 = 0;
    sub->unk28 = 0;
    sub->unk14 = 1.0f;
    sub->unk24 = arg7 * 100.0f;
    sub->unk26 = arg6 * 100.0f;
    if (arg8 > 45.0f) {
        arg8 = 45.0f;
    }
    sub->unk29 = 0;
    sub->unk20 = 0;
    sub->unk2A = arg8 * 2.8222222f;
}

void tickObjectAnimSubstruct(u8 *obj, TickSub *sub, f32 arg2, f32 arg3);

void applyToObjectSubstructByFlag(u8 *obj, f32 arg1, f32 arg2, s32 useAlt) {
    u8 *sub;

    if (useAlt == 0) {
        sub = obj + 0x138;
    } else {
        sub = obj + 0x164;
    }
    tickObjectAnimSubstruct(obj, sub, arg1, arg2);
}

void setObjectSubstructF10IfReady(u8 *obj, f32 value, s32 useAlt) {
    u8 *sub;

    if (useAlt == 0) {
        sub = obj + 0x138;
    } else {
        sub = obj + 0x164;
    }
    if (*(s32 *)(sub + 0x18) != 0 && sub[0x2B] != 0) {
        *(f32 *)(sub + 0x10) = value;
    }
}

void setAnimSubstructValueIfActive(void *arg0, f32 arg1) {
    if (((*(s32 *)((u8 *)(arg0) + 0x18)) != 0) && ((*(u8 *)((u8 *)(arg0) + 0x2B)) != 0)) {
        (*(f32 *)((u8 *)(arg0) + 0x10)) = arg1;
    }
}

void vec3Cross(f32 *, f32 *, f32 *);
s32 rand();
extern f32 D_mission_overlay_8010C470;
extern f32 D_mission_overlay_8010C474;

void generatePerpEmitDirectionWithJitter(s8 *arg0, f32 *arg1, s32 arg2) {
    u8 flag = arg2;
    f32 sp10[4];
    f32 sp20[4];
    f32 sp30[4];
    f32 sp40[4];
    f32 *a;
    f32 *b;
    f32 f0;

    if (arg0[0x162] != 0) {
        a = arg1 + 6;
        b = arg1 + 3;
        vec3Cross(sp10, a, b);
        if (!flag) {
            f0 = (f32)arg0[0x162] * 0.35433072f;
            D_mission_overlay_8010C470 = ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / f0);
            D_mission_overlay_8010C474 = ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / f0);
        }
        quatFromAxisAngle(sp30, sp10, D_mission_overlay_8010C470);
        quatFromAxisAngle(sp40, a, D_mission_overlay_8010C474);
        quatMultiply(sp40, sp30, sp20);
        rotateVec3ByQuat(sp20, b, b);
        rotateVec3ByQuat(sp20, a, a);
    }
}

s32 tickProgressChannel(s32, f32 *, s32, s32);

s32 stepAndTickProgressChannel(s32 arg0, u8 *arg1, f32 arg2, s32 arg3, s32 arg4) {
    f32 sp[12];

    zmemcpy((s32)sp, (s32)arg1, 0x30);
    sp[0] += sp[3] * arg2;
    sp[1] += sp[4] * arg2;
    sp[2] += sp[5] * arg2;
    return tickProgressChannel(arg0, sp, arg3, arg4) & 0xFF;
}

f32 getEffectIntensity(void *arg0) {
    return (*(f32 *)((u8 *)(arg0) + 0x14C));
}

s32 setEffectIntensity(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)(arg0) + 0x14C)) = arg1;
    return 1;
}

typedef struct {
    s16 type;
    u8 pad2[0x16];
    f32 value;
    u8 mode;
} CueSlotMessage;

f32 getEffectIntensity(void *);
s32 dispatchCueByCategory(s32, u16, s32, s32, u8, f32, f32);
s32 slotDispatcherIter(u16, s32, void *);

u16 triggerCueWithSlotEffect(u8 *npc, s32 arg1, s32 arg2, s32 arg3, u8 arg4, f32 arg5, f32 arg6) {
    CueSlotMessage msg;
    s32 id;

    id = dispatchCueByCategory(arg1, *(u16 *)(npc + 0x198), arg2, arg3, arg4, arg5, getEffectIntensity(npc));
    if (arg6 >= 0.0f) {
        msg.value = arg6;
        if (arg6 == 0.0f) {
            msg.mode = 2;
        } else {
            msg.mode = 1;
        }
        msg.type = 2;
        slotDispatcherIter(id, 10, &msg);
    }
    return id;
}

s32 copyPipeDelimitedField(u8 *s, s32 field, u8 *out) {
    s32 count = 0;

    s++;
    while (*s != 0) {
        if (*s == '|') {
            s++;
            count++;
        } else if (s[1] == 0) {
            count++;
        }
        if (count == field) {
            while (*s != 0 && *s != '|') {
                *out++ = *s++;
            }
            *out = 0;
            if (*s != 0) {
                return field + 1;
            }
            return 0;
        }
        s++;
    }
    return 0;
}

s32 copyRandomPipeDelimitedField(u8 *arg0, u8 *arg1) {
    s32 field;
    s32 count;
    s32 ret;
    u8 *s;
    u8 *o;
    u8 c;

    if (arg0[0] != 0) {
        field = (s16)rand() % *arg0++;
        o = arg1;
        s = arg0;
        c = *s;
        count = 0;
        while (c != 0) {
            if (c == '|') {
                s++;
                count++;
            } else if (s[1] == 0) {
                count++;
            }
            if (count == field) {
                while (*s != 0 && *s != 0x7C) {
                    *o++ = *s++;
                }
                *o = 0;
                ret = 0;
                if (*s != 0) {
                    ret = field + 1;
                }
                goto done;
            }
            s++;
            c = *s;
        }
        ret = 0;
done:
        return ret;
    }
    *arg1 = 0;
    return 0;
}

s32 returnZero_800F3258(void) {
    return 0;
}

void tallyMidDetailObject(u8 *obj) {
    if ((obj[0x15] >> 6) == 2) {
        missionStats.enemies_destroyed++;
    }
}
