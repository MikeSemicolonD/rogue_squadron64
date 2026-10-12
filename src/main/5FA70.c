#include "common.h"
#include "common_types.h"

typedef struct { f32 x, y, z; } SoV3;
extern f32 soLen(f32 *) __asm__("vec3Length");
extern f32 soDot(f32 *, f32 *) __asm__("vec3Dot");
extern void soCross(f32 *, f32 *, f32 *) __asm__("vec3Cross");
extern f32 soAsin(f32) __asm__("constMinusSinfApprox");
extern void soQuat(f32 *, f32 *, f32) __asm__("quatFromAxisAngleSafe");
extern void soRot(f32 *, f32 *, f32 *) __asm__("rotateVec3ByQuat");
extern void soOrtho(f32 *) __asm__("orthonormalizeFrame");
extern void soNormInto(f32 *, f32 *) __asm__("vec3NormalizeInto");
extern void soNorm(f32 *) __asm__("normalize_vector");
extern void soRemove(void *) __asm__("factor5RemoveListNode");
extern void soPlay(s32, void *, void *, f32, f32, s32, s32, s32, s32) __asm__("play3DSoundEvent");
extern void soPlayV(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32) __asm__("play3DSoundEventVariant");
extern f32 soWrap(f32, f32, void *, s32) __asm__("wrapAngleToCyclicRange");
extern u8 D_main_bss_80138058[];

static __inline__ f32 soLenI(f32 *v) { return soLen(v); }

void steerOrientationTowardTarget(f32 *p, f32 *tgt, f32 dt) {
    f32 d[3];
    f32 n[3];
    f32 c[3];
    f32 q[4];
    f32 pr[3];
    f32 q2[4];
    f32 v[3];
    f32 up[3];
    f32 c2[3];
    f32 len;
    f32 lim;
    f32 ang;
    f32 t;

    lim = 0.0f;
    p[24] = p[24] - dt;
    if (p[24] <= lim) {
        p[24] = p[25];
        d[0] = tgt[0] - p[1];
        d[1] = tgt[1] - p[2];
        d[2] = tgt[2] - p[3];
        if (((u8 *)p)[0x7A] != 0) {
            len = soLenI(d);
            p[29] = p[29] - dt;
            if (len > 6.0f) {
                if (p[29] <= lim) {
                    if (((u8 *)p)[0x7B] == 1) {
                        ((u8 *)p)[0x7B] = 0;
                        soRemove((u8 *)p + 0x7C);
                    }
                    p[29] = len / 25.0f;
                    soPlay(0, p + 1, p + 10, 24.0f, 0.1f, 0, 0x40, 0x7F, 0x28);
                }
            } else {
                p[29] = lim;
                if (((u8 *)p)[0x7B] == 0) {
                    ((u8 *)p)[0x7B] = 1;
                    soPlayV((u8 *)p + 0x7C, p + 1, p + 10, 24.0f, 0.1f, 7, 0x41, 1, 0x7F, 0x28);
                }
            }
        }
        if (soLen(d) < 4.0f) {
            ((u8 *)p)[0x53] = 0;
        }
        soNormInto(n, d);
        soCross(c, p + 4, n);
        if (soLen(c) > 0.00001f) {
            lim = p[26] * 30.0f * dt;
            ang = soAsin(soDot(n, p + 4)) * 57.29578f;
            if (ang > lim) {
                ang = lim;
            } else if (ang < -lim) {
                ang = -lim;
            }
            soQuat(q, c, ang);
            soRot(q, p + 4, n);
            *(SoV3 *)(p + 4) = *(SoV3 *)n;
            soRot(q, p + 7, n);
            *(SoV3 *)(p + 7) = *(SoV3 *)n;
            soOrtho(p + 1);
        }
        if (((u8 *)p)[0x53] == 1) {
            pr[0] = p[1] + ((p[10] == 0.0f) ? 0.0f : 1.0f / p[10] * 4.0f) * (dt * 30.0f);
            pr[1] = p[2] + ((p[11] == 0.0f) ? 0.0f : 1.0f / p[11] * 4.0f) * (dt * 30.0f);
            pr[2] = p[3] + ((p[12] == 0.0f) ? 0.0f : 1.0f / p[12] * 4.0f) * (dt * 30.0f);
            if (soWrap(pr[0], pr[2], D_main_bss_80138058, 0) - p[2] < 0.1f) {
                lim = (p[26] + 2.0f) * p[22] * (dt * 30.0f);
                v[0] = p[4];
                v[1] = 0.0f;
                v[2] = p[6];
                up[0] = 0.0f;
                up[1] = 1.0f;
                up[2] = 0.0f;
                soNorm(v);
                soCross(c2, up, v);
                if (soLen(c2) > 0.000001f) {
                    if (lim < 0.0f) {
                        { register f32 k asm("$f0") = -15.0f; soQuat(q2, c2, (lim < k) ? k : lim); }
                        soRot(q2, p + 4, n);
                        *(SoV3 *)(p + 4) = *(SoV3 *)n;
                        soRot(q2, p + 7, n);
                        *(SoV3 *)(p + 7) = *(SoV3 *)n;
                        soOrtho(p + 1);
                    } else if (lim > 0.0f) {
                        { register f32 k asm("$f0") = 15.0f; soQuat(q2, c2, (lim > k) ? k : lim); }
                        soRot(q2, p + 4, n);
                        *(SoV3 *)(p + 4) = *(SoV3 *)n;
                        soRot(q2, p + 7, n);
                        *(SoV3 *)(p + 7) = *(SoV3 *)n;
                        soOrtho(p + 1);
                    }
                }
            }
        }
    }
    p[23] = p[23] + 0.4f;
    p[22] = p[22] + p[23];
    if (p[22] > p[27]) {
        p[22] = p[27];
    }
    p[10] = p[4] * p[22];
    p[11] = p[5] * p[22];
    p[12] = p[6] * p[22];
    p[1] = p[1] + p[10] * dt;
    p[2] = p[2] + p[11] * dt;
    p[3] = p[3] + p[12] * dt;
}

INCLUDE_RODATA("asm/nonmatchings/main/5FA70", D_main_8003B224);

typedef struct { f32 x, y, z; } LoV3;
extern LoV3 D_main_8003B224;
extern f32 constMinusSinfApprox(f32);
extern f32 vec3Dot(f32 *, f32 *);
extern f32 vec3Length(f32 *);
extern void vec3Cross(f32 *, f32 *, f32 *);
extern void quatFromAxisAngle(f32 *, f32 *, f32);
extern void rotateVec3ByQuat(f32 *, f32 *, f32 *);
extern void orthonormalizeFrame(f32 *);

void levelOrientationToReferenceAxis(f32 *p, f32 dt)
{
  LoV3 ref = D_main_8003B224;
  f32 q[4];
  f32 cr[3];
  f32 ang;
  f32 t;
  f32 x;
  f32 y;
  ang = constMinusSinfApprox(vec3Dot((f32 *) (&ref), p + 4)) * 57.29578f;
 do { if (1.0f < fabsf(ang)) { vec3Cross(cr, p + 4, (f32 *) (&ref)); if (vec3Length(cr) > 0.00001f) { if (ang < 0.0f) { quatFromAxisAngle(q, cr, (ang < -15.0f) ? -15.0f : ang); } else if (ang > 0.0f) { quatFromAxisAngle(q, cr, (ang > 15.0f) ? 15.0f : ang); } rotateVec3ByQuat(q, p + 4, cr); *((LoV3 *) (p + 4)) = *((LoV3 *) cr); rotateVec3ByQuat(q, p + 7, cr); *((LoV3 *) (p + 7)) = *((LoV3 *) cr); orthonormalizeFrame(p + 1); } } x = p[4] * p[22]; y = p[5] * p[22]; p[23] = p[23] + 0.4f; p[10] = x; p[11] = y + p[23]; p[12] = p[6] * p[22]; p[1] = p[1] + (p[10] * dt); p[2] = p[2] + (p[11] * dt); p[3] = p[3] + (p[12] * dt); } while (0);
}


typedef struct { f32 v[3]; } TpV3;
typedef struct {
    u8 pad0[4];
    TpV3 pos;
    TpV3 dir;
    TpV3 up;
    u8 pad28[0x1C];
    u16 cue;
    u8 pad46[0x12];
    f32 vol;
    u8 pad5C[0x67];
    u8 active;
} TpObj;
typedef struct { u8 b[5]; } TpTypes;
static const TpTypes kTrailTypes = { { 0x1F, 5, 6, 7, 0xFF } };
typedef struct {
    TpV3 pos;
    TpV3 dir;
    f32 range;
    f32 width;
    s32 zero;
    TpTypes *types;
    u16 self;
    s8 one;
    u16 hits[7];
} TpAim;
typedef struct {
    s16 cmd;
    u16 arg;
    s32 zero;
    f32 a;
    f32 b;
    f32 c;
    u8 flag;
} TpCmd;
typedef struct {
    TpV3 pos;
    TpV3 dir;
    TpV3 up;
    TpV3 fwd;
} TpCue;
typedef struct {
    TpCmd cmd;
    u8 pad18[8];
    f32 q0[4];
    f32 q1[4];
    f32 q2[4];
    f32 cr[3];
    u8 pad8C[0x1C];
} TpLoop;
typedef union {
    struct {
        TpTypes list;
        TpAim aim;
    } a;
    TpLoop l;
} TpBuf;
extern s32 acquireNpcTargetsInAimCone(TpAim *);
extern void zmemcpy(void *, void *, s32);
extern s32 dispatchCueByCategory(s32, u16, TpCue *, void *, s32, f32, f32);
extern s32 slotDispatcherIter(s32, s32, TpCmd *);
extern void quatMultiply(f32 *, f32 *, f32 *);
extern u8 D_main_8009ED60[];

static __inline__ void cpV3(f32 *d, f32 *s) { d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; }

s32 emitTrailPuffAndCue(TpObj *arg0) {
    u16 hits[7];
    s32 n;
    s32 i;
    s32 slot;
    TpBuf u;
    u8 *lb;
    TpCue cue;
    register u16 *hp __asm__("$17");

    if (arg0->active == 0) {
        goto clear;
    }
    {
        u.a.list = kTrailTypes;
        {
            f32 *s_ = arg0->pos.v;
            u.a.aim.pos.v[0] = s_[0];
            u.a.aim.pos.v[1] = s_[1];
            u.a.aim.pos.v[2] = s_[2];
        }
        lb = (u8 *)&u.a.list;
        u.a.aim.dir = arg0->dir;
        *(f32 *)(lb + 0x20) = 35.0f;
        *(f32 *)(lb + 0x24) = 35.0f;
        u.a.aim.zero = 0;
        *(u8 **)(lb + 0x2C) = lb;
        *(u16 *)(lb + 0x30) = 0xFFFF;
        *(s8 *)(lb + 0x32) = 1;
        {
            TpAim *cp = &u.a.aim;
            n = acquireNpcTargetsInAimCone(cp);
            cp = 0;
        }
        hp = hits;
        if (n > 0) {
            TpAim *ap = &u.a.aim;
            for (i = 0; n < 7; i++, n++) {
                ap->hits[n] = ap->hits[i];
            }
        }
        zmemcpy(hp, u.a.aim.hits, 0xE);
    }
    if (n == 0) {
    clear:
        arg0->active = 0;
    }
        u.l.cmd.zero = 0;
        u.l.cmd.flag = 1;
        u.l.cmd.a = 15.0f;
        u.l.cmd.b = 10.0f;
        u.l.cmd.c = 7.5f;
        cue.pos = arg0->pos;
        for (i = 0; i < 7; i++) {
            if (i == 0) {
                cue.dir = arg0->dir;
                cue.up = arg0->up;
                cue.fwd = cue.dir;
                vec3Cross(u.l.cr, arg0->up.v, arg0->dir.v);
                quatFromAxisAngle(u.l.q0, u.l.cr, 6.25f);
            } else {
                quatFromAxisAngle(u.l.q1, arg0->dir.v, i * 60.0f);
                quatMultiply(u.l.q1, u.l.q0, u.l.q2);
                rotateVec3ByQuat(u.l.q2, arg0->dir.v, cue.dir.v);
                rotateVec3ByQuat(u.l.q2, arg0->up.v, cue.up.v);
                cue.fwd = cue.dir;
            }
            slot = dispatchCueByCategory(0xA, arg0->cue, &cue, D_main_8009ED60 + 4, 0, arg0->vol, 1.0f);
            if (arg0->active != 0) {
                u.l.cmd.cmd = 0;
                u.l.cmd.arg = hits[i];
                slotDispatcherIter(slot & 0xFFFF, 0xA, &u.l.cmd);
            }
            u.l.cmd.cmd = 5;
            slotDispatcherIter(slot & 0xFFFF, 0xA, &u.l.cmd);
        }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/5FA70", guidedEffectNpcHandler);

extern s8 D_main_bss_80139860;
extern s8 D_main_bss_80139864[];

void initWeaponSlotIndexTable(void) {
    s32 i;
    s8 *p;

    i = 3;
    p = D_main_bss_80139864 + i;
    do {
        *p-- = i;
    } while (--i >= 0);
    D_main_bss_80139860 = 4;
}

INCLUDE_RODATA("asm/nonmatchings/main/5FA70", D_main_8003B2F8);
