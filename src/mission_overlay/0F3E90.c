#include "common.h"
#include "common_types.h"

#include "level_objectives.h"
#include "mission_overlay/0F3E90.h"
#include "rs_math.h"

typedef struct { s32 unk0; u8 pad[0x20]; } ModelAnimSlot24;
extern ModelAnimSlot24 D_mission_overlay_8010C4A0[];

extern void copyPipeDelimitedField(u8 *, s32, char *);
extern void copyRandomPipeDelimitedField(u8 *, char *);
extern s32 returnZero_800F3258(u8 *, s32);
extern void *getLevelDatItemByName(char *);

typedef struct { s32 type; f32 a; f32 b; s32 name; } RsTok;

static __inline__ u8 rsObjBool(u8 *a0, s32 v) {
    if (v == 0) {
        return 1;
    }
    if (v < 0x81) {
        return gObjectiveBooleans[v - 1] != 0;
    }
    return returnZero_800F3258(a0, v);
}

s32 resolveScriptedNameTokenList(u8 *arg0, u8 *arg1) {
    char buf[0x40];
    s32 i;
    RsTok *t;
    s32 v;
    s32 r;
    u8 *name;
    u8 *item;

    t = (RsTok *)(*(u8 **)(arg1 + 0x24) + 0x54);
    for (i = 0; i < 8; i++) {
        name = *(u8 **)(arg1 + 0x24) + t->name;
        switch (t->type) {
        case 1:
            if ((s32)t->a < *(s32 *)(arg1 + 0x34)) {
                break;
            }
            goto done;
        case 2:
            r = rsObjBool(arg0, (s32)t->a);
            if ((u8)r == (s32)t->b) {
                copyPipeDelimitedField(name, 0, buf);
                *(void **)(arg1 + 0x28) = getLevelDatItemByName(buf);
                *(s32 *)(arg1 + 0x34) = 0;
                return 1;
            }
            break;
        case 3:
            {
            s32 v3 = (s32)t->a;
            if (v3 > 0) {
                if (gObjectiveCounts[v3 - 1] >= (s32)t->b) {
                    copyPipeDelimitedField(name, 0, buf);
                    *(void **)(arg1 + 0x28) = getLevelDatItemByName(buf);
                    *(s32 *)(arg1 + 0x34) = 0;
                    return 1;
                }
            }
            }
            break;
        case 4:
            copyRandomPipeDelimitedField(name, buf);
            *(void **)(arg1 + 0x28) = getLevelDatItemByName(buf);
            *(s32 *)(arg1 + 0x34) = 0;
            return 1;
        case 5:
            copyPipeDelimitedField(name, 0, buf);
            *(void **)(arg1 + 0x28) = getLevelDatItemByName(buf);
            *(s32 *)(arg1 + 0x34) = 0;
            return 1;
        case 6:
            __asm__("" :: "r"(arg1));
            __asm__("" :: "r"(arg1));
            if ((s32)t->a == 1) {
                arg0[0x1A5] = 1;
            }
            return 0;
        case 7:
            copyPipeDelimitedField(name, 0, buf);
            item = getLevelDatItemByName(buf);
            *(u8 **)(arg1 + 0x28) = item;
            *(s32 *)(arg1 + 0x34) = 0;
            *(f32 *)(arg1 + 0x104) = t->a;
            if (*(s32 *)(item + 0x50) == 1) {
                *(f32 *)(arg1 + 0x14) = *(f32 *)(arg1 + 0x14) + 180.0f;
            }
            return 1;
        default:
            *(u8 **)(arg1 + 0x28) = *(u8 **)(arg1 + 0x24);
            return 1;
        }
        t++;
    }
done:
    *(u8 **)(arg1 + 0x28) = *(u8 **)(arg1 + 0x24);
    return 1;
}

#include "main/1D000.h"
#include "main/5A750.h"

typedef struct {
    f32 v[3];
} RoV3;

typedef struct {
    f32 v[4];
} RoQ4;

typedef struct {
    u8 pad0[0x14];
    f32 f14;
    u8 pad18[0x30];
    f32 f48;
    u8 pad4C[0x14];
    f32 f60;
    f32 f64;
    f32 f68;
    f32 f6C;
    f32 f70;
    f32 f74;
    f32 f78;
    f32 f7C;
    f32 f80;
    f32 f84;
    f32 f88;
    f32 f8C;
    f32 f90;
    f32 f94;
    f32 f98;
    f32 f9C;
    f32 fA0;
    f32 fA4;
    f32 fA8;
    f32 fAC;
    f32 fB0;
    f32 fB4;
    f32 fB8;
    RoQ4 quat;
    f32 fCC;
} RandOrient;

f32 floatModulo(f32, f32);
void vec3Cross(f32 *, f32 *, f32 *);
u16 rand(void);

void computeRandomizedOrientationFrame(f32 *arg0, RandOrient *o, f32 (*m)[3], f32 dt) {
    f32 sp10[4];
    f32 sp20[4];
    f32 sp30[4];
    f32 sp40[4];
    f32 sp50[4];
    f32 sp60[4];
    RoQ4 sp70;
    RoQ4 sp80;
    f32 target;
    f32 t88;
    f32 t84;
    f32 f8c;
    f32 tA0;
    f32 tm;
    f32 c80;
    f32 c98;
    f32 fa4;
    f32 h;
    f32 r;
    f32 *axis;
    f32 x;

    if (o->f60 != 0.0f || (t88 = o->f64) != 0.0f || o->f68 != 0.0f) {
        t88 = o->f64;
        target = t88;
        if (target == 0.0f) {
            target = o->f60;
        }
        if (o->f68 != target) {
            f32 rate;
            f32 cur;
            f32 nv;
            if (o->f6C == 0.0f) {
                if (o->f70 != 0.0f) {
                    rate = fabsf(target - o->f68) / o->f70;
                } else {
                    rate = 100000.0f;
                }
                o->f6C = rate;
            }
            if (o->f68 < target) {
                o->f68 += o->f6C * dt;
                if ((target - 0.01f) < o->f68) {
                    o->f68 = target;
                    o->f6C = 0.0f;
                }
            } else {
                o->f68 -= o->f6C * dt;
                if (o->f68 < (target + 0.01f)) {
                    o->f68 = target;
                    o->f6C = 0.0f;
                }
            }
        }
        t88 = o->f88 - dt;
        o->f88 = t88;
        if (t88 <= 0.0f) {
            o->f88 = 120.0f;
            {
                f32 q = ((f32)(rand() & 0x7F) - 64.0f) / 160.0f;
                f32 ab;
                f32 k = 0.1f;
                FABSF(ab, q);
                r = ab + k;
            }
            if (o->f90 > 0.0f) {
                t84 = o->f84 - r;
                o->f84 = t84;
                if (t84 < 0.0f) {
                    o->f84 = 0.0f;
                }
            } else {
                t84 = o->f84 + r;
                o->f84 = t84;
                if (t84 > 1.0f) {
                    o->f84 = 1.0f;
                }
            }
            c80 = o->f80;
            o->f8C = 0.0f;
            o->f94 = c80;
            o->f90 = o->f84 - c80;
        }
        if (o->f80 != o->f84) {
            f8c = o->f8C + o->f74 * (o->f48 * 0.25f);
            o->f8C = f8c;
            if (f8c >= 1.0f) {
                o->f88 = 0.0f;
                o->f80 = o->f84;
            } else {
                o->f80 = o->f94 + (1.0f - cosf(f8c * 3.1415927f)) * 0.5f * o->f90;
            }
        } else {
            o->f88 = 0.0f;
        }
        tA0 = o->fA0 - dt;
        o->fA0 = tA0;
        if (tA0 <= 0.0f) {
            f32 d;
            f32 ten;
            o->fA0 = 120.0f;
            ten = 10.0f;
            if (o->fA8 < 0.0f) {
                d = fabsf(((f32)(rand() & 0x7F) - 64.0f) / 0.3764706f) + ten;
            } else {
                d = -(fabsf(((f32)(rand() & 0x7F) - 64.0f) / 0.3764706f) + ten);
            }
            d = d * (o->f48 * 0.25f);
            o->f9C = floatModulo(o->f98 + d + 360.0f, 360.0f);
            c98 = o->f98;
            o->fA4 = 0.0f;
            o->fAC = c98;
            x = o->f9C - c98;
            FABSF(d, x);
            if (d > 180.0f) {
                d = 360.0f - d;
            }
            tm = floatModulo(c98 + d, 360.0f);
            if ((tm < (o->f9C - 1.0f)) || ((o->f9C + 1.0f) < tm)) {
                d = -d;
            }
            o->fA8 = d;
        }
        if (o->f98 != o->f9C) {
            fa4 = o->fA4 + o->f78;
            o->fA4 = fa4;
            if (fa4 >= 1.0f) {
                o->fA0 = 0.0f;
                o->f98 = o->f9C;
            } else {
                o->f98 = o->fAC + (1.0f - cosf(fa4 * 3.1415927f)) * 0.5f * o->fA8;
            }
        } else {
            o->fA0 = 0.0f;
        }
        o->f98 = floatModulo(o->f98, 360.0f);
        sp30[0] = 0.0f;
        sp30[1] = cosf(o->f80 * 3.1415927f) * o->f68 * 0.25f;
        h = o->f14 * (o->f7C * (o->f48 * 0.25f));
        if (h < 90.0f) {
            sp30[1] *= cosf(h * 0.017453292f);
        } else {
            sp30[1] = 0.0f;
        }
        sp30[1] *= o->f48 * 0.25f;
        sp30[2] = 0.0f;
        axis = m[1];
        quatFromAxisAngle(sp10, axis, -o->f98);
        rotateVec3ByQuat(sp10, sp30, sp20);
        m[0][0] += sp20[0];
        m[0][1] += sp20[1];
        m[0][2] += sp20[2];
        sp50[0] = m[3][0] + sp20[0];
        sp50[1] = m[3][1] + sp20[1];
        sp50[2] = m[3][2] + sp20[2];
        sp40[0] = sp50[0] - o->fB0;
        sp40[1] = sp50[1] - o->fB4;
        sp40[2] = sp50[2] - o->fB8;
        o->fB0 = sp50[0];
        o->fB4 = sp50[1];
        o->fB8 = sp50[2];
        if ((vec3Length(sp50) > 0.00001f) && (vec3Length(sp40) > 0.00001f)) {
            f32 ang;
            normalize_vector(sp50);
            normalize_vector(sp40);
            vec3Cross(sp60, sp40, axis);
            ang = constMinusSinfApprox(vec3Dot(sp50, axis)) * 57.29578f;
            ang = ang * (o->f48 * 0.25f);
            quatFromAxisAngle((f32 *)&sp70, sp60, -ang);
            if (o->fCC < ang) {
                slerpQuaternions((f32 *)&o->quat, (f32 *)&sp70, o->fCC / ang, (f32 *)&sp80);
                sp70 = sp80;
            }
            o->quat = sp70;
            rotateVec3ByQuat((f32 *)&sp70, axis, sp40);
            *(RoV3 *)m[1] = *(RoV3 *)sp40;
            rotateVec3ByQuat((f32 *)&sp70, m[2], sp40);
            *(RoV3 *)m[2] = *(RoV3 *)sp40;
            orthonormalizeFrame(m);
        }
    } else {
        quatFromCardinalAxis((f32 *)&o->quat, 2, 0.0f);
        o->fB0 = 0.0f;
        o->fB4 = 0.0f;
        o->fB8 = 0.0f;
    }
}

extern void setEffectIntensity(u8 *, s32);
extern s32 slotDispatcherIter(u16, s32, void *);
typedef struct { u8 *p; u8 pad[0x14]; u8 b18; } UnFx;
extern UnFx D_mission_overlay_8010C480;

typedef struct {
    union { f32 f; s32 i; } w0;
    s32 w4;
    union { s32 i; u8 b[4]; } w8;
    f32 wC;
    s32 w10;
    f32 w14;
    u8 b18;
    u8 pad[3];
} UnMsg;

s32 updateNpcEffectIntensity(u8 *arg0, u8 *arg1) {
    UnMsg msg;
    u8 *a = arg1;
    s32 v;

    {
        s32 v1 = *(s32 *)(a + 0x28);
        if (v1 != 0 && !rsObjBool(arg0, v1)) {
            return 0;
        }
    }
    {
        s32 v2 = *(s32 *)(a + 0x2C);
        if (v2 != 0 && gObjectiveCounts[v2 - 1] < *(s32 *)(a + 0x30)) {
            return 0;
        }
    }
    {
        s32 v3 = *(s32 *)(a + 0x3C);
        if (v3 != 0) {
            gObjectiveBooleans[v3 - 1] = a[0x43];
        }
    }
    {
        s32 v4 = *(s32 *)(a + 0x34);
        if (v4 != 0) {
            gObjectiveCounts[v4 - 1] += *(s32 *)(a + 0x38);
        }
    }
    switch (*(u16 *)arg1) {
    case 0x1A:
        msg.b18 = 0;
        msg.w0.i = *(s32 *)(arg1 + 0x44);
        *(f32 *)&msg.w4 = *(f32 *)(arg1 + 0x48);
        *(f32 *)&msg.w8 = *(f32 *)(arg1 + 0x4C);
        msg.wC = *(f32 *)(arg1 + 0x50);
        *(f32 *)&msg.w10 = *(f32 *)(arg1 + 0x54);
        msg.w14 = *(f32 *)(arg1 + 0x58);
        slotDispatcherIter(*(u16 *)(arg0 + 0x198), 9, &msg);
        break;
    case 0x1B:
        {
            u8 *s;
            u8 *b = arg1;
            f32 d;
            if (*(u16 *)(arg0 + 0x110) & 0x20) {
                break;
            }
            s = arg0 + 8;
            if (*(s32 *)(arg1 + 0x48) != 0) {
                *(f32 *)(s + 0x50) = *(f32 *)(s + 0x48) * *(f32 *)(arg1 + 0x44);
            } else {
                *(f32 *)(s + 0x50) = *(f32 *)(arg1 + 0x44);
            }
            if (*(f32 *)(s + 0x50) <= 0.0f) {
                *(f32 *)(s + 0x50) = 0.1f;
            }
            *(f32 *)(s + 0x4C) = *(f32 *)(s + 0x48);
            d = *(f32 *)(s + 0x50) - *(f32 *)(s + 0x48);
            *(f32 *)(s + 0x54) = d;
            if (d != 0.0f) {
                *(f32 *)(s + 0x58) = 0.0f;
                if (*(f32 *)(b + 0x4C) > 0.0f) {
                    *(f32 *)(s + 0x5C) = 1.0f / *(f32 *)(b + 0x4C);
                } else {
                    *(f32 *)(s + 0x48) = *(f32 *)(s + 0x50);
                    *(f32 *)(s + 0x2C) = *(f32 *)(s + 0x50) / *(f32 *)(*(u8 **)(s + 0x24) + 0x24);
                }
            }
        }
        break;
    case 0x1C:
        if (*(u16 *)(arg0 + 0x110) & 0x20) {
            return 0;
        }
        {
            u8 *b = arg1;
            if (*(s32 *)(arg1 + 0x48) == 0) {
                *(f32 *)(arg0 + 0x68) = *(f32 *)(arg1 + 0x44) * 0.25f;
            } else {
                *(f32 *)(arg0 + 0x68) = *(f32 *)(arg0 + 0x68) * (*(f32 *)(arg1 + 0x44) * 0.25f);
            }
            *(f32 *)(arg0 + 0x78) = *(f32 *)(b + 0x4C);
        }
        break;
    case 0x1D:
        if (*(s32 *)(arg1 + 0x44) != 0) {
            arg0[0x1A5] = 1;
        }
        arg0[0x1A6] = 1;
        break;
    case 0x20:
        {
            u8 *str;
            arg0[0x12C] = arg1[0x47];
            arg0[0x12D] = arg1[0x4B];
            setEffectIntensity(arg0, *(s32 *)(arg1 + 0x54));
            str = (u8 *)(*(s32 *)(arg1 + 0x4C) + (s32)arg1);
            if (*str == 0 || *str == 0x2D) {
                *(u8 **)(arg0 + 0x128) = NULL;
            } else {
                *(u8 **)(arg0 + 0x128) = str;
            }
            *(s32 *)(arg0 + 0x124) = 0;
            msg.b18 = 4;
            msg.w0.i = *(s32 *)(arg1 + 0x50);
            *(f32 *)&msg.w4 = *(f32 *)(arg1 + 0x54);
            slotDispatcherIter(*(u16 *)(arg0 + 0x198), 9, &msg);
        }
        break;
    case 0x22:
        if (*(u16 *)(arg0 + 0x110) & 0x20) {
            return 0;
        }
        {
            u8 *b = arg1;
            msg.b18 = 1;
            msg.w0.f = *(f32 *)(b + 0x44);
            {
            s32 v5 = *(s32 *)(b + 0x48);
            if (v5 != 0 && gObjectiveBooleans[v5 - 1] == *(s32 *)(b + 0x4C)) {
                msg.w8.b[1] = 0;
                msg.w8.b[2] = 0;
            } else {
                msg.w8.b[1] = b[0x4B];
                msg.w8.b[2] = b[0x4F];
            }
            }
            {
            s32 v6 = *(s32 *)(b + 0x50);
            if (v6 != 0 && gObjectiveCounts[v6 - 1] >= *(s32 *)(b + 0x54)) {
                msg.w8.b[0] = 0;
                msg.w4 = 0;
            } else {
                msg.w8.b[0] = b[0x53];
                msg.w4 = *(s32 *)(b + 0x54);
            }
            }
            if (msg.w0.f == 0.0f && !(msg.w8.i & 0xFFFF0000)) {
                return 0;
            }
            slotDispatcherIter(*(u16 *)(arg0 + 0x198), 9, &msg);
        }
        break;
    case 0x23:
        if (*(s32 *)(arg1 + 0x44) != 0) {
            *(f32 *)(arg0 + 0xFC) = 1.0f / *(f32 *)(arg1 + 0x48);
            *(s32 *)(arg0 + 0x100) = 0;
        } else {
            *(f32 *)(arg0 + 0xFC) = -1.0f / *(f32 *)(arg1 + 0x48);
            *(f32 *)(arg0 + 0x100) = 1.0f;
        }
        break;
    case 0x4E:
        D_mission_overlay_8010C480.b18 = 7;
        D_mission_overlay_8010C480.p = (u8 *)(*(s32 *)(arg1 + 0x44) + (s32)arg1);
        return 1;
    }
    return 0;
}


typedef struct { f32 x, y, z; } T1aV3;
typedef struct { u16 a, b; } T1aPair;
typedef struct { f32 t; u16 h4, h6; } T1aEv;
extern u8 *D_main_bss_801375D8;
extern u8 D_main_bss_80138058[];
extern s32 slotDispatcherIter(u16, s32, void *);
void buildPositionAndCallTransformHelper(void *, void *, void *, void *, f32, f32, f32);
void setupActorAnchorTransformType1(void *, void *, void *, void *, f32);
f32 sinf(f32);
f32 cosf(f32);
f32 sinfApprox(f32);
f32 constMinusSinfApprox(f32);
f32 vec3Dot(f32 *, f32 *);
void vec3Cross(f32 *, f32 *, f32 *);
f32 normalize_vector(f32 *);
void quatFromAxisAngle(f32 *, f32 *, f32);
void quatFromAxisAngleSafe(f32 *, f32 *, f32);
void rotateVec3ByQuat(f32 *, f32 *, f32 *);
f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
f32 sampleTerrainSurfaceAtWorldXz(f32, f32, void *, void *);
s32 updateNpcEffectIntensityA(u8 *, u8 *) __asm__("updateNpcEffectIntensity");
void computeRandomizedOrientationFrameA(void *, void *, void *, f32) __asm__("computeRandomizedOrientationFrame");
s32 resolveScriptedNameTokenListA(u8 *, u8 *) __asm__("resolveScriptedNameTokenList");
extern UnFx D_mission_overlay_8010C480;

#define SF(o) (*(f32 *)(s + (o)))
#define SW(o) (*(s32 *)(s + (o)))
#define SP(o) (*(u8 **)(s + (o)))

s32 executeActorType1EffectS(u8 *arg0, f32 dt) __asm__("executeActorType1Effect");

s32 executeActorType1EffectS(u8 *arg0, f32 dt) {
    f32 rm[12];
    f32 prev[3];
    struct { f32 f0; u8 pad[0x14]; u8 type; u8 pad2[7]; } msg;
    u8 *s;
    f32 *m;
    u8 stop;
    u8 fired;
    f32 t;

    s = arg0 + 8;
    stop = 0;
    m = getNpcContextField8(*(u16 *)(arg0 + 0x198));
    *(T1aV3 *)prev = *(T1aV3 *)(s + 0xD0);
    fired = 0;
    t = SF(0x104);
    if (t != 0.0f || (SW(0xFC) & 0xFF00FF00) != 0) {
        if (t > 0.0f) {
            t -= dt;
            SF(0x104) = t;
            if (t > 0.0f) {
                goto stopped;
            }
            SF(0x104) = 0.0f;
        }
        if (s[0xFC] != 0 && gObjectiveBooleans[s[0xFC] - 1] != s[0xFD]) {
            stop = 1;
            goto anim;
        }
        if (s[0xFE] != 0 && gObjectiveCounts[s[0xFE] - 1] < SW(0x100)) {
        stopped:
            stop = 1;
            goto anim;
        }
        if (*(u16 *)(arg0 + 0x110) & 2) {
            s[0xFE] = 0;
            s[0xFC] = 0;
            msg.type = 3;
            slotDispatcherIter(*(u16 *)(arg0 + 0x198), 9, &msg);
        }
    }
    if (SF(0x48) != SF(0x50)) {
        SF(0x58) += SF(0x5C) * dt;
        if (SF(0x58) >= 1.0f) {
            SF(0x48) = SF(0x50);
        } else {
            SF(0x48) = SF(0x4C) + sinf(SF(0x58) * 3.1415927f * 0.5f) * SF(0x54);
        }
        SF(0x2C) = SF(0x48) / *(f32 *)(SP(0x24) + 0x24);
        if (*(u16 *)(arg0 + 0x110) & 1) {
            msg.type = 2;
            msg.f0 = SF(0x48);
            slotDispatcherIter(*(u16 *)(arg0 + 0x198), 9, &msg);
        }
    }
    SF(0x30) += SF(0x2C) * dt;
    if (SF(0x30) > 1.0f) {
        u8 *cur;
        u8 *nx;
        f32 saved;
        SW(0x34)++;
        cur = SP(0x24);
        if (*(s32 *)(cur + 0x40) != 0) {
            gObjectiveCounts[*(s32 *)(cur + 0x40) - 1] += *(s32 *)(cur + 0x44);
        }
        if (*(s32 *)(cur + 0x48) != 0) {
            gObjectiveBooleans[*(s32 *)(cur + 0x48) - 1] = cur[0x4F];
        }
        if (!(u8)resolveScriptedNameTokenListA(arg0, s)) {
            arg0[0x1A4] = 1;
            return 0;
        }
        nx = SP(0x28);
        SF(0x30) = (SF(0x30) - 1.0f) / SF(0x2C) * (SF(0x48) / *(f32 *)(nx + 0x24));
        saved = SF(0x14);
        {
            f32 dd = *(f32 *)(nx + 0x24);
            SF(0x2C) = SF(0x48) / dd;
        }
        SP(0x24) = nx;
        SP(0x28) = 0;
        SW(0x0) = *(s32 *)(nx + 0x1C);
        SW(0x4) = *(s32 *)(SP(0x24) + 0x20);
        SP(0x8) = *(u8 **)(SP(0x24) + 0x20) + SW(0x0) * 0xC;
        setupActorAnchorTransformType1(s, SP(0x24) + 0x10, s + 0xD0, s + 0xC, SF(0x30));
        SF(0x14) = saved;
        SW(0x3C) = 0;
        if (*(s32 *)(SP(0x24) + 0x28) != 0) {
            SF(0x40) = **(f32 **)(SP(0x24) + 0x2C);
        } else {
            SF(0x40) = 10.0f;
        }
    }
anim:
    buildPositionAndCallTransformHelper(s, SP(0x24) + 0x10, s + 0xD0, s + 0xC, SF(0x44), 1.0f, SF(0x30));
    m[9] = (SF(0xD0) - prev[0]) / dt;
    m[10] = (SF(0xD4) - prev[1]) / dt;
    m[11] = (SF(0xD8) - prev[2]) / dt;
    buildRotationMatrixSlot2((Vec3f *)rm, SF(0x14));
    composeRotationMatrixSlot0((Vec3f *)rm, SF(0xC));
    composeRotationMatrixSlot1((Vec3f *)rm, SF(0x10));
    m[6] = rm[1];
    m[7] = rm[4];
    m[8] = rm[7];
    m[3] = rm[2];
    m[4] = rm[5];
    m[5] = rm[8];
    if (*(u16 *)(arg0 + 0x110) & 8) {
        f32 up[3] = { 0.0f, 1.0f, 0.0f };
        f32 c1[3];
        f32 c2[3];
        f32 q[4];
        vec3Cross(c1, &m[6], &m[3]);
        vec3Cross(c2, up, c1);
        normalize_vector(c2);
        vec3Cross(up, c1, c2);
        normalize_vector(up);
        quatFromAxisAngle(q, c1, sinfApprox(vec3Dot(&m[3], up)) * 57.29578f);
        rotateVec3ByQuat(q, &m[6], up);
        *(T1aV3 *)&m[6] = *(T1aV3 *)up;
        rotateVec3ByQuat(q, &m[3], up);
        *(T1aV3 *)&m[3] = *(T1aV3 *)up;
    }
    if (SF(0x30) >= SF(0x40)) {
        u8 *p = SP(0x24);
        s32 idx;
        T1aPair *tb = (T1aPair *)(p + (*(s32 *)(p + 0xD8) + 0xD4));
        fired = updateNpcEffectIntensityA(arg0, ((u8 **)*(u8 **)(D_main_bss_801375D8 + 0x3C))[tb[((T1aEv *)*(u8 **)(p + 0x2C))[SW(0x3C)].h6].b]);
        idx = SW(0x3C) + 1;
        SW(0x3C) = idx;
        if (idx < *(s32 *)(SP(0x24) + 0x28)) {
            SF(0x40) = *(f32 *)(*(u8 **)(SP(0x24) + 0x2C) + idx * 8);
        } else {
            SF(0x40) = 10.0f;
        }
    }
    if (SF(0xDC) > 0.0f) {
        f32 off[3];
        f32 v[3];
        f32 q[4];
        v[0] = 0.0f;
        v[1] = SF(0xDC) * 0.25f;
        v[2] = 0.0f;
        quatFromAxisAngle(q, &m[3], -SF(0xE0));
        rotateVec3ByQuat(q, v, off);
        m[0] = SF(0xD0) + off[0];
        m[1] = SF(0xD4) + off[1];
        m[2] = SF(0xD8) + off[2];
    } else {
        *(T1aV3 *)m = *(T1aV3 *)(s + 0xD0);
    }
    if (SF(0xE8) > 0.0f) {
        SF(0xEC) += dt * SF(0xF0);
        if (SF(0xEC) < 1.0f) {
            f32 w[3];
            f32 q[4];
            f32 k;
            w[2] = 0.0f;
            w[0] = 0.0f;
            k = 1.0f - (cosf((SF(0xEC) + SF(0xEC)) * 3.1415927f) + 1.0f) * 0.5f;
            w[1] = -SF(0xE8) * k;
            quatFromAxisAngle(q, &m[3], SF(0xE4));
            rotateVec3ByQuat(q, w, w);
            m[0] += w[0];
            m[1] += w[1];
            m[2] += w[2];
            if (wrapAngleToCyclicRange(m[0], m[2], D_main_bss_80138058, 0) < m[1]) {
                struct { u16 a, b, c, d; s32 e; } msg2;
                msg2.a = 0xFFFF;
                msg2.b = 0xFFFF;
                msg2.c = 7;
                msg2.d = 0xFFFF;
                msg2.e = 0;
                slotDispatcherIter(*(u16 *)(arg0 + 0x198), 5, &msg2);
            }
        } else {
            SF(0xE8) = 0.0f;
        }
    }
    if (!stop) {
        computeRandomizedOrientationFrameA(arg0, s, m, dt);
    }
    if (SF(0xF8) != 0.0f || SF(0xF4) != 0.0f) {
        f32 w[3];
        f32 q[4];
        f32 ang;
        f32 *ax;
        if (SF(0xF4) > 0.0f) {
            SF(0xF8) += SF(0xF4) * dt;
            if (SF(0xF8) > 1.0f) {
                SF(0xF8) = 1.0f;
                SF(0xF4) = 0.0f;
            }
        } else if (SF(0xF4) < 0.0f) {
            SF(0xF8) += SF(0xF4) * dt;
            if (SF(0xF8) < 0.0f) {
                SF(0xF8) = 0.0f;
                SF(0xF4) = 0.0f;
            }
        }
        ax = w;
        vec3Cross(ax, &m[6], &m[3]);
        if (*(s32 *)(SP(0x24) + 0x50) == 0) {
            quatFromAxisAngle(q, ax, constMinusSinfApprox(cosf(SF(0xF8) * 3.1415927f)) * 57.29578f * 0.5f);
        } else {
            quatFromAxisAngle(q, ax, -constMinusSinfApprox(cosf(SF(0xF8) * 3.1415927f)) * 57.29578f * 0.5f);
        }
        rotateVec3ByQuat(q, &m[3], w);
        *(T1aV3 *)&m[3] = *(T1aV3 *)w;
        rotateVec3ByQuat(q, &m[6], w);
        *(T1aV3 *)&m[6] = *(T1aV3 *)w;
    }
    if (fired) {
        slotDispatcherIter(*(u16 *)(arg0 + 0x198), 9, &D_mission_overlay_8010C480);
        return 1;
    }
    if (*(u16 *)(arg0 + 0x110) & 4) {
        if (!(*(u16 *)(arg0 + 0x110) & 0x10)) {
            m[1] = wrapAngleToCyclicRange(m[0], m[2], D_main_bss_80138058, 0) - SF(0x38) * 0.25f;
        } else {
            f32 terr[10];
            f32 c[3];
            f32 q[4];
            f32 ang;
            m[1] = sampleTerrainSurfaceAtWorldXz(m[0], m[2], D_main_bss_80138058, terr) - SF(0x38) * 0.25f;
            ang = constMinusSinfApprox(vec3Dot((f32 *)(s + 0x18), &terr[3])) * 57.29578f;
            if (ang > 0.0001f) {
                if (dt * 30.0f < ang) {
                    ang = dt * 30.0f;
                }
                vec3Cross(c, (f32 *)(s + 0x18), &terr[3]);
                quatFromAxisAngleSafe(q, c, ang);
                rotateVec3ByQuat(q, (f32 *)(s + 0x18), c);
                *(T1aV3 *)(s + 0x18) = *(T1aV3 *)c;
            } else {
                *(T1aV3 *)(s + 0x18) = *(T1aV3 *)&terr[3];
            }
            ang = constMinusSinfApprox(vec3Dot((f32 *)(s + 0x18), &m[6])) * 57.29578f;
            if (ang > 0.0001f) {
                vec3Cross(c, &m[6], (f32 *)(s + 0x18));
                quatFromAxisAngleSafe(q, c, ang);
                rotateVec3ByQuat(q, &m[3], c);
                *(T1aV3 *)&m[3] = *(T1aV3 *)c;
                rotateVec3ByQuat(q, &m[6], c);
                *(T1aV3 *)&m[6] = *(T1aV3 *)c;
            }
        }
    } else if (*(u16 *)(arg0 + 0x110) & 0x10) {
        f32 terr[10];
        f32 c[3];
        f32 q[4];
        f32 ang;
        sampleTerrainSurfaceAtWorldXz(m[0], m[2], D_main_bss_80138058, terr);
        ang = constMinusSinfApprox(vec3Dot((f32 *)(s + 0x18), &terr[3])) * 57.29578f;
        if (ang > 0.0001f) {
            if (dt * 30.0f < ang) {
                ang = dt * 30.0f;
            }
            vec3Cross(c, (f32 *)(s + 0x18), &terr[3]);
            quatFromAxisAngleSafe(q, c, ang);
            rotateVec3ByQuat(q, (f32 *)(s + 0x18), c);
            *(T1aV3 *)(s + 0x18) = *(T1aV3 *)c;
        } else {
            *(T1aV3 *)(s + 0x18) = *(T1aV3 *)&terr[3];
        }
        ang = constMinusSinfApprox(vec3Dot((f32 *)(s + 0x18), &m[6])) * 57.29578f;
        if (ang > 0.0001f) {
            vec3Cross(c, &m[6], (f32 *)(s + 0x18));
            quatFromAxisAngleSafe(q, c, ang);
            rotateVec3ByQuat(q, &m[3], c);
            *(T1aV3 *)&m[3] = *(T1aV3 *)c;
            rotateVec3ByQuat(q, &m[6], c);
            *(T1aV3 *)&m[6] = *(T1aV3 *)c;
        }
    }
    return 0;
}

void *getNpcContextField8(u16);
typedef struct {
    f32 x, y, z;
} T2V3;

typedef struct {
    T2V3 dir;
    f32 rate0;
    f32 rate;
    f32 speed;
    f32 timer;
    f32 angBase;
    f32 angRange;
    f32 timeBase;
    f32 timeRange;
    f32 rate1;
    u8 *box;
    u8 active;
    u8 hold;
} T2State;

void vec3Cross(f32 *, f32 *, f32 *);
f32 constMinusSinfApprox(f32);
f32 normalize_vector(f32 *);
f32 vec3Dot(f32 *, f32 *);
f32 vec3Length(f32 *);
void quatFromAxisAngleSafe(f32 *, f32 *, f32);
void quatFromAxisAngle(f32 *, f32 *, f32);
void rotateVec3ByQuat(f32 *, f32 *, f32 *);
void orthonormalizeFrameF(f32 *) __asm__("orthonormalizeFrame");
f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
u16 rand(void);
f32 fabsf(f32);
extern u8 D_main_bss_80138058[];

void executeActorType2Effect(void *arg0, f32 dt) {
    f32 d[3];
    f32 v[3];
    f32 q[4];
    f32 c[3];
    T2State *s = (T2State *)((u8 *)arg0 + 8);
    f32 *m = getNpcContextField8(*(u16 *)((u8 *)arg0 + 0x198));
    f32 ang;
    f32 len;
    f32 turn;
    f32 *fw;

    {
        f32 vx = m[9];
        d[0] = m[0] + vx - *(f32 *)(s->box + 0x10);
    }
    {
        f32 vx = m[10];
        d[1] = m[1] + vx - *(f32 *)(s->box + 0x14);
    }
    {
        f32 vx = m[11];
        d[2] = m[2] + vx - *(f32 *)(s->box + 0x18);
    }
    len = vec3Length(d);
    if (len == 0.0f) {
        len = 1.0f;
    }
    v[0] = d[0] / len;
    v[1] = d[1] / len;
    v[2] = d[2] / len;
    fw = &m[3];
    ang = constMinusSinfApprox(vec3Dot(v, fw)) * 57.29578f;
    len = vec3Length(d);
    if (*(f32 *)(s->box + 0x1C) <= len) {
        if (s->active == 0) {
            if (s->hold == 0) {
                quatFromAxisAngle(q, v, 180.0f);
                rotateVec3ByQuat(q, fw, v);
                *(f32 *)((u8 *)arg0 + 8) = -v[0];
                s->dir.y = -v[1];
                s->dir.z = -v[2];
                s->active = 1;
                s->hold = 0;
                s->rate = s->rate0;
            } else if (ang < 112.5f) {
                vec3Cross(c, v, fw);
                quatFromAxisAngleSafe(q, c, 180.0f - ang);
                rotateVec3ByQuat(q, fw, (f32 *)s);
                s->active = 1;
                s->hold = 0;
                s->rate = s->rate0;
            }
        } else if (*(f32 *)(s->box + 0x1C) + 0.25f <= len) {
            s->active = 0;
            s->hold = 0;
        }
    } else {
        if (s->timeBase != 0.0f) {
            s->timer -= dt;
            if (s->active == 0 && s->timer <= 0.0f) {
                f32 ab;
                f32 x;
                FABSF(ab, ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->timeRange));
                s->timer = s->timeBase + ab;
                FABSF(ab, ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->angRange));
                ang = s->angBase + ab;
                if (rand() & 1) {
                    x = ang;
                } else {
                    x = -ang;
                }
                quatFromAxisAngle(q, &m[6], x);
                rotateVec3ByQuat(q, fw, (f32 *)s);
                s->active = 1;
                s->rate = s->rate1;
            }
        }
        s->hold = 0;
    }
    turn = s->rate * 30.0f * dt;
    if (*(u16 *)((u8 *)arg0 + 0x110) & 4) {
        s->dir.y = 0.0f;
        normalize_vector((f32 *)s);
    }
    if (s->active != 0) {
        ang = constMinusSinfApprox(vec3Dot((f32 *)s, &m[3])) * 57.29578f;
        if (ang > 0.01f) {
            vec3Cross(c, &m[3], (f32 *)s);
            if (turn < ang) {
                ang = turn;
            }
            quatFromAxisAngleSafe(q, c, ang);
            rotateVec3ByQuat(q, &m[3], v);
            *(T2V3 *)&m[3] = *(T2V3 *)v;
            rotateVec3ByQuat(q, &m[6], v);
            *(T2V3 *)&m[6] = *(T2V3 *)v;
            orthonormalizeFrameF(m);
        } else {
            *(T2V3 *)&m[3] = s->dir;
            s->active = 0;
            s->hold = 1;
        }
    }
    m[9] = m[3] * s->speed;
    m[10] = m[4] * s->speed;
    m[11] = m[5] * s->speed;
    m[0] += m[9] * dt;
    m[1] += m[10] * dt;
    m[2] += m[11] * dt;
    if (*(u16 *)((u8 *)arg0 + 0x110) & 4) {
        m[1] = wrapAngleToCyclicRange(m[0], m[2], D_main_bss_80138058, 0);
    }
}

void *getNpcContextField8(u16);
typedef struct {
    f32 x, y, z;
} T3V3;

typedef struct {
    T3V3 dir;
    f32 rate0;
    f32 rate;
    f32 speed;
    f32 timer;
    f32 angBase;
    f32 angRange;
    f32 timeBase;
    f32 timeRange;
    f32 rate1;
    u8 *box;
    u8 active;
    u8 hold;
} T3State;

void vec3Cross(f32 *, f32 *, f32 *);
f32 constMinusSinfApprox(f32);
f32 normalize_vector(f32 *);
f32 vec3Dot(f32 *, f32 *);
void quatFromAxisAngleSafe(f32 *, f32 *, f32);
void quatFromAxisAngle(f32 *, f32 *, f32);
void rotateVec3ByQuat(f32 *, f32 *, f32 *);
void orthonormalizeFrameF(f32 *) __asm__("orthonormalizeFrame");
f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
u16 rand(void);
f32 fabsf(f32);
extern u8 D_main_bss_80138058[];

void executeActorType3Effect(void *arg0, f32 dt) {
    f32 d[3];
    f32 v[3];
    f32 axis[3];
    f32 q[4];
    f32 c[3];
    T3State *s = (T3State *)((u8 *)arg0 + 8);
    f32 *m = getNpcContextField8(*(u16 *)((u8 *)arg0 + 0x198));
    s32 f;
    f32 ang;
    f32 turn;

    {
        f32 vx = m[9];
        d[0] = m[0] + vx - *(f32 *)(s->box + 0x10);
    }
    {
        f32 vx = m[10];
        d[1] = m[1] + vx - *(f32 *)(s->box + 0x14);
    }
    {
        f32 vx = m[11];
        d[2] = m[2] + vx - *(f32 *)(s->box + 0x18);
    }
    v[0] = m[0] - (*(f32 *)(s->box + 0x10) + *(f32 *)(s->box + 0x28) * 0.5f);
    v[1] = m[1] - (*(f32 *)(s->box + 0x14) + *(f32 *)(s->box + 0x2C) * 0.5f);
    v[2] = m[2] - (*(f32 *)(s->box + 0x18) + *(f32 *)(s->box + 0x30) * 0.5f);
    normalize_vector(v);
    f = 0;
    if (d[0] < 0.0f) {
        f = 1;
    } else if (*(f32 *)(s->box + 0x28) < d[0]) {
        f = 2;
    }
    if (d[2] < 0.0f) {
        f |= 4;
    } else if (*(f32 *)(s->box + 0x30) < d[2]) {
        f |= 8;
    }
    if (f != 0) {
        axis[1] = 0.0f;
        switch (f) {
        case 1:
            axis[2] = 0.0f;
            axis[0] = 1.0f;
            break;
        case 2:
            axis[2] = 0.0f;
            axis[0] = -1.0f;
            break;
        case 5:
            axis[0] = axis[2] = 0.70710677f;
            break;
        case 6:
            axis[0] = -0.70710677f;
            axis[2] = 0.70710677f;
            break;
        case 4:
            axis[0] = 0.0f;
            axis[2] = 1.0f;
            break;
        case 8:
            axis[0] = 0.0f;
            axis[2] = -1.0f;
            break;
        case 9:
            axis[0] = 0.70710677f;
            axis[2] = -0.70710677f;
            break;
        case 10:
            axis[0] = axis[2] = -0.70710677f;
            break;
        }
        ang = constMinusSinfApprox(vec3Dot(v, &m[3])) * 57.29578f;
        if (s->active == 0) {
            if (s->hold == 0) {
                quatFromAxisAngle(q, axis, 180.0f);
                rotateVec3ByQuat(q, &m[3], v);
                s->dir.x = -v[0];
                s->dir.y = -v[1];
                s->dir.z = -v[2];
                s->active = 1;
                s->hold = 0;
                s->rate = s->rate0;
            } else if (ang < 112.5f) {
            turn:
                vec3Cross(c, v, &m[3]);
                quatFromAxisAngleSafe(q, c, 180.0f - ang);
                rotateVec3ByQuat(q, &m[3], (f32 *)s);
                s->active = 1;
                s->hold = 0;
                s->rate = s->rate0;
            }
        } else if (d[0] < -0.25f || *(f32 *)(s->box + 0x28) + 0.25f < d[0] || d[2] < -0.25f || *(f32 *)(s->box + 0x30) + 0.25f < d[2]) {
            goto turn;
        }
    } else {
        if (s->timeBase != 0.0f) {
            s->timer -= dt;
            if (s->active == 0 && s->timer <= 0.0f) {
                f32 ab;
                f32 x;
                FABSF(ab, ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->timeRange));
                s->timer = s->timeBase + ab;
                FABSF(ab, ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->angRange));
                ang = s->angBase + ab;
                if (rand() & 1) {
                    x = ang;
                } else {
                    x = -ang;
                }

                quatFromAxisAngle(q, &m[6], x);
                rotateVec3ByQuat(q, &m[3], (f32 *)s);
                s->active = 1;
                s->rate = s->rate1;
            }
        }
        s->hold = 0;
    }
    turn = s->rate * 30.0f * dt;
    if (*(u16 *)((u8 *)arg0 + 0x110) & 4) {
        s->dir.y = 0.0f;
        normalize_vector((f32 *)s);
    }
    if (s->active != 0) {
        ang = constMinusSinfApprox(vec3Dot((f32 *)s, &m[3])) * 57.29578f;
        if (ang > 0.01f) {
            vec3Cross(c, &m[3], (f32 *)s);
            if (turn < ang) {
                ang = turn;
            }
            quatFromAxisAngleSafe(q, c, ang);
            rotateVec3ByQuat(q, &m[3], v);
            *(T3V3 *)&m[3] = *(T3V3 *)v;
            rotateVec3ByQuat(q, &m[6], v);
            *(T3V3 *)&m[6] = *(T3V3 *)v;
            orthonormalizeFrameF(m);
        } else {
            *(T3V3 *)&m[3] = s->dir;
            s->active = 0;
            s->hold = 1;
        }
    }
    m[9] = m[3] * s->speed;
    m[10] = m[4] * s->speed;
    m[11] = m[5] * s->speed;
    m[0] += m[9] * dt;
    m[1] += m[10] * dt;
    m[2] += m[11] * dt;
    if (*(u16 *)((u8 *)arg0 + 0x110) & 4) {
        m[1] = wrapAngleToCyclicRange(m[0], m[2], D_main_bss_80138058, 0);
    }
}

typedef struct { f32 x, y, z; } T4V3;
extern void t4Memset(void *, s32, s32) __asm__("rs_memset");

s32 initActorAsType4(u8 *a0, char *name, f32 a2, f32 a3, s32 a4) {
    u8 *p = a0 + 8;
    f32 *q = (f32 *)(a0 + 0x50);
    u8 *item;
    f32 t;
    f32 x;

    a0[0x112] = 4;
    if (name[0] != 0) {
        item = getLevelDatItemByName(name);
        if (item != NULL) {
            switch (item[2]) {
            case 6:
                *(s16 *)(p + 0xEC) = 1;
                *(T4V3 *)(a0 + 0xD0) = *(T4V3 *)(item + 0x10);
                *(T4V3 *)(a0 + 0xE8) = *(T4V3 *)(item + 0x28);
                *(f32 *)(p + 0xD4) = *(f32 *)(item + 0x10) + *(f32 *)(item + 0x28) * 0.5f;
                *(f32 *)(p + 0xD8) = *(f32 *)(item + 0x14) + *(f32 *)(item + 0x2C) * 0.5f;
                *(f32 *)(p + 0xDC) = *(f32 *)(item + 0x18) + *(f32 *)(item + 0x30) * 0.5f;
                goto common;
            case 7:
                *(s16 *)(p + 0xEC) = 2;
                *(T4V3 *)(a0 + 0xD0) = *(T4V3 *)(item + 0x10);
                *(f32 *)(p + 0xE0) = *(f32 *)(item + 0x1C);
                *(f32 *)(p + 0xD4) = *(f32 *)(p + 0xC8);
                *(f32 *)(p + 0xDC) = *(f32 *)(p + 0xD0);
                *(f32 *)(p + 0xD8) = *(f32 *)(p + 0xCC) - *(f32 *)(p + 0xE0) * 0.5f;
                goto common;
            }
        }
    }
    {
        T4V3 *v = getNpcContextField8(*(u16 *)(a0 + 0x198));
        *(T4V3 *)(p + 0xD4) = *v;
        *(T4V3 *)(p + 0xC8) = *(T4V3 *)(p + 0xD4);
        *(s16 *)(p + 0xEC) = 0;
    }
common:
    *(T4V3 *)(p + 0x98) = *(T4V3 *)(p + 0xD4);
    *(f32 *)(p + 0xA4) = 0.0f;
    *(f32 *)(p + 0xA8) = 0.0f;
    *(f32 *)(p + 0xB0) = 0.0f;
    *(f32 *)(p + 0xB8) = 0.0f;
    *(f32 *)(p + 0xBC) = 0.0f;
    *(f32 *)(p + 0xC0) = 0.0f;
    *(f32 *)(p + 0xC4) = 0.0f;
    p[0x96] = 0;
    *(f32 *)(p + 0x18) = a2;
    *(f32 *)(p + 0x20) = a2;
    *(f32 *)(p + 0x3C) = a2;
    *(f32 *)(p + 0x2C) = 0.0f;
    *(f32 *)(p + 0x30) = 0.0f;
    *(f32 *)(p + 0xAC) = 1.0f;
    *(f32 *)(p + 0xB4) = 1.0f;
    if (a3 < 10.0f) {
        a3 = 10.0f;
    }
    if (180.0f < a3) {
        a3 = 180.0f;
    }
    t = (f32)a4 / 10.0f;
    *(f32 *)(p + 0x1C) = a3;
    *(f32 *)(p + 0x24) = a3;
    x = 1.0f - t;
    *(f32 *)(p + 0x34) = x;
    if (x < 0.1f) {
        *(f32 *)(p + 0x34) = 0.1f;
    }
    *(f32 *)(p + 0x28) = *(f32 *)(p + 0xF8) = 10000000.0f;
    *(s32 *)(p + 0xF4) = 0;
    *(s16 *)(p + 0xF2) = 0;
    *(f32 *)(p + 0x38) = t + 1.0f;
    q[0] = 11.25f;
    q[1] = 22.5f;
    q[2] = *(f32 *)(p + 0x34) * 5.0f;
    if (q[2] < 1.8f) {
        q[2] = 1.0f;
    }
    q[3] = *(f32 *)(p + 0x34) + *(f32 *)(p + 0x34);
    if (q[3] < 1.0f) {
        q[3] = 0.4f;
    }
    *(s32 *)(p + 0x100) = 0;
    t4Memset(q + 4, 0xFF, 0x15);
    return 1;
}

f32 sinfApprox(f32);
typedef struct { f32 f0; u8 pad4[4]; f32 f8; } SwIn;
typedef struct { u8 pad0[8]; f32 f8; } SwOut;
void buildSineWaveEffectGeometryA(s32 mode, void *inp, f32 base, void *outp) {
    SwIn *in = inp;
    SwOut *out = outp;
    f32 a[4];
    f32 b[4];
    f32 max;
    f32 scale;
    f32 amp;
    u8 *o = (u8 *)out;

    max = out->f8;
    scale = 255.0f / max;
    amp = (1.0f - (sinfApprox(in->f8) / 1.5707964f)) * base;
    a[0] = base + amp;
    if (a[0] < 0.0f) {
        a[0] = 0.0f;
    }
    if (max < a[0]) {
        a[0] = max;
    }
    b[0] = base - amp;
    if (b[0] < 0.0f) {
        b[0] = 0.0f;
    }
    if (max < b[0]) {
        b[0] = max;
    }
    amp = (sinfApprox(in->f0) / 1.5707964f) * (max - base);
    b[2] = base + amp;
    a[2] = base - amp;
    switch (mode) {
    case 0:
        o[0x19] = (u32)(a[0] * scale);
        o[0x1B] = (u32)(b[0] * scale);
        if (o[0x14] == 0xFF) {
            o[0x17] = (u32)(b[2] * scale);
        } else {
            o[0x17] = (u32)(((f32)o[0x14] + (f32)o[0x1A]) * 0.5f);
        }
        if (o[0x20] == 0xFF) {
            o[0x1D] = (u32)(a[2] * scale);
        } else {
            o[0x1D] = (u32)(((f32)o[0x20] + (f32)o[0x1A]) * 0.5f);
        }
        b[3] = a[0] * (b[2] / base);
        if (max < b[3]) {
            b[3] = max;
        }
        o[0x16] = (u32)(b[3] * scale);
        a[1] = a[0] * (a[2] / base);
        if (max < a[1]) {
            a[1] = max;
        }
        o[0x1C] = (u32)(a[1] * scale);
        b[1] = b[0] * (b[2] / base);
        if (max < b[1]) {
            b[1] = max;
        }
        o[0x18] = (u32)(b[1] * scale);
        a[3] = b[0] * (a[2] / base);
        if (max < a[3]) {
            a[3] = max;
        }
        o[0x1E] = (u32)(a[3] * scale);
        break;
    case 1:
        o[0x13] = (u32)(a[0] * scale);
        o[0x15] = (u32)(b[0] * scale);
        if (o[0x1A] == 0xFF) {
            o[0x17] = (u32)(a[2] * scale);
        } else {
            o[0x17] = (u32)(((f32)o[0x1A] + (f32)o[0x14]) * 0.5f);
        }
        o[0x11] = (u32)(b[2] * scale);
        if (o[0x16] == 0xFF) {
            a[1] = a[0] * (a[2] / base);
            if (max < a[1]) {
                a[1] = max;
            }
            o[0x16] = (u32)(a[1] * scale);
        } else {
            o[0x16] = (u32)(((f32)o[0x13] + (f32)o[0x19]) * 0.5f);
        }
        if (o[0x18] == 0xFF) {
            a[3] = b[0] * (a[2] / base);
            if (max < a[3]) {
                a[3] = max;
            }
            o[0x18] = (u32)(a[3] * scale);
        } else {
            o[0x18] = (u32)(((f32)o[0x15] + (f32)o[0x1B]) * 0.5f);
        }
        b[3] = a[0] * (b[2] / base);
        if (max < b[3]) {
            b[3] = max;
        }
        o[0x10] = (u32)(b[3] * scale);
        b[1] = b[0] * (b[2] / base);
        if (max < b[1]) {
            b[1] = max;
        }
        o[0x12] = (u32)(b[1] * scale);
        break;
    case 2:
        o[0x1F] = (u32)(a[0] * scale);
        o[0x21] = (u32)(b[0] * scale);
        if (o[0x1A] == 0xFF) {
            o[0x1D] = (u32)(b[2] * scale);
        } else {
            o[0x1D] = (u32)(((f32)o[0x1A] + (f32)o[0x20]) * 0.5f);
        }
        o[0x23] = (u32)(a[2] * scale);
        if (o[0x1C] == 0xFF) {
            b[3] = a[0] * (b[2] / base);
            if (max < b[3]) {
                b[3] = max;
            }
            o[0x1C] = (u32)(b[3] * scale);
        } else {
            o[0x1C] = (u32)(((f32)o[0x1F] + (f32)o[0x19]) * 0.5f);
        }
        if (o[0x1E] == 0xFF) {
            b[1] = b[0] * (b[2] / base);
            if (max < b[1]) {
                b[1] = max;
            }
            o[0x1E] = (u32)(b[1] * scale);
        } else {
            o[0x1E] = (u32)(((f32)o[0x21] + (f32)o[0x1B]) * 0.5f);
        }
        a[1] = a[0] * (a[2] / base);
        if (max < a[1]) {
            a[1] = max;
        }
        o[0x22] = (u32)(a[1] * scale);
        a[3] = b[0] * (a[2] / base);
        if (max < a[3]) {
            a[3] = max;
        }
        o[0x24] = (u32)(a[3] * scale);
        break;
    }
}

typedef struct {
    f32 f0;
    u8 pad4[4];
    f32 f8;
} SineWaveIn;

typedef struct {
    u8 pad0[8];
    f32 f8;
    u8 padC[5];
    u8 b11;
    u8 b12;
    u8 pad13;
    u8 b14;
    u8 b15;
    u8 pad16;
    u8 b17;
    u8 b18;
    u8 pad19;
    u8 b1A;
    u8 b1B;
    u8 pad1C;
    u8 b1D;
    u8 b1E;
    u8 pad1F;
    u8 b20;
    u8 b21;
    u8 pad22;
    u8 b23;
    u8 b24;
} SineWaveOut;

f32 sinfApprox(f32);

void buildSineWaveEffectGeometryB(s32 mode, SineWaveIn *in, f32 base, SineWaveOut *out) {
    f32 a[4];
    f32 b[4];
    f32 max;
    f32 scale;
    f32 amp;

    max = out->f8;
    scale = 255.0f / max;
    amp = (1.0f - (sinfApprox(in->f8) / 1.5707964f)) * base;
    a[0] = base + amp;
    if (a[0] < 0.0f) {
        a[0] = 0.0f;
    }
    if (max < a[0]) {
        a[0] = max;
    }
    b[0] = base - amp;
    if (b[0] < 0.0f) {
        b[0] = 0.0f;
    }
    if (max < b[0]) {
        b[0] = max;
    }
    amp = (sinfApprox(in->f0) / 1.5707964f) * (max - base);
    b[2] = base + amp;
    a[2] = base - amp;
    switch (mode) {
    case 0:
        out->b1A = (u32)(a[0] * scale);
        out->b18 = (u32)(b[2] * scale);
        out->b1E = (u32)(a[2] * scale);
        b[3] = a[0] * (b[2] / base);
        if (max < b[3]) {
            b[3] = max;
        }
        out->b17 = (u32)(b[3] * scale);
        a[1] = a[0] * (a[2] / base);
        if (max < a[1]) {
            a[1] = max;
        }
        out->b1D = (u32)(a[1] * scale);
        break;
    case 1:
        out->b14 = (u32)(a[0] * scale);
        if (out->b1A == 0xFF) {
            out->b18 = (u32)(a[2] * scale);
            a[1] = a[0] * (a[2] / base);
            if (max < a[1]) {
                a[1] = max;
            }
            out->b17 = (u32)(a[1] * scale);
        } else {
            out->b17 = (u32)(((f32)out->b1A + (f32)out->b14) * 0.5f);
            out->b18 = (u32)(((f32)out->b1B + (f32)out->b15) * 0.5f);
        }
        out->b12 = (u32)(b[2] * scale);
        b[3] = a[0] * (b[2] / base);
        if (max < b[3]) {
            b[3] = max;
        }
        out->b11 = (u32)(b[3] * scale);
        break;
    case 2:
        out->b20 = (u32)(a[0] * scale);
        if (out->b1A == 0xFF) {
            out->b1E = (u32)(b[2] * scale);
            b[3] = a[0] * (b[2] / base);
            if (max < b[3]) {
                b[3] = max;
            }
            out->b1D = (u32)(b[3] * scale);
        } else {
            out->b1D = (u32)(((f32)out->b1A + (f32)out->b20) * 0.5f);
            out->b1E = (u32)(((f32)out->b1B + (f32)out->b21) * 0.5f);
        }
        out->b24 = (u32)(a[2] * scale);
        a[1] = a[0] * (a[2] / base);
        if (max < a[1]) {
            a[1] = max;
        }
        out->b23 = (u32)(a[1] * scale);
        break;
    }
}

void rs_memset(u8 *, u8, u32);
void rotateVec3ByMat3x3(Mat4x3, Vec3f, Vec3f);
void buildSineWaveEffectGeometryA(s32, void *, f32, void *);
f32 raycastTerrainAndNpcs(f32 *, f32 *, u16, u16 *, f32, s32, f32 *, f32 *, s32, u8 *);

typedef struct { f32 m[12]; } RnMat;
typedef struct {
    f32 ang;
    f32 ang2;
    f32 range;
    f32 padC;
    u8 b[0x18];
} RnFx;

void renderNpcAnchoredProceduralEffect(u8 *arg0) {
    f32 m28[12];
    f32 inv[12];
    f32 q0[4];
    f32 q1[4];
    f32 qa[4];
    f32 qb[4];
    f32 hit[3][3];
    f32 dir[4];
    f32 axis[4];
    f32 m[12];
    f32 dist[4];
    u8 fl[8];
    u16 id;
    u8 *s;
    u8 crossed;
    RnFx *e;
    s32 i;
    f32 d;
    f32 *p;
    RnMat *src;
    u8 one;

    crossed = 0;
    s = arg0 + 8;
    e = (RnFx *)(arg0 + 0x50);
    src = getNpcContextField8(*(u16 *)(arg0 + 0x198));
    p = m;
    *(RnMat *)p = *src;
    mat34CrossRowsAndCopyPos((Vec3f *)m28, (Vec3f *)p, 1.0f);
    mat3x3InverseInto((Vec3f *)inv, (Vec3f *)m28);
    rs_memset(&e->b[0], 0xFF, 0x15);
    if (!(*(u16 *)(arg0 + 0x110) & 0x40)) {
        d = raycastTerrainAndNpcs(p, &p[3], *(u16 *)(arg0 + 0x198), &id, e->range, 0, &dist[0], hit[0], 1, &fl[0]);
        one = 1;
        e->b[0xA] = (u32)(d * (255.0f / e->range));
        quatFromAxisAngle(q0, &p[6], e->ang * -0.6666667f);
        rotateVec3ByQuat(q0, &p[3], dir);
        d = raycastTerrainAndNpcs(p, dir, *(u16 *)(arg0 + 0x198), &id, e->range, 0, &dist[1], hit[1], one, &fl[1]);
        e->b[0x4] = (u32)(d * (255.0f / e->range));
        quatFromAxisAngle(q1, &p[6], e->ang * 0.6666667f);
        rotateVec3ByQuat(q1, &p[3], dir);
        d = raycastTerrainAndNpcs(p, dir, *(u16 *)(arg0 + 0x198), &id, e->range, 0, &dist[2], hit[2], one, &fl[2]);
        e->b[0x10] = (u32)(d * (255.0f / e->range));
        for (i = 0; i < 3; i++) {
            if (fl[i] & 1) {
                rotateVec3ByMat3x3((Vec3f *)inv, hit[i], hit[i]);
                buildSineWaveEffectGeometryA(i, (SineWaveIn *)hit[i], dist[i], (SineWaveOut *)e);
                continue;
            }
            switch (i) {
            case 0:
                if (!crossed) {
                    crossed = 1;
                    vec3Cross(axis, &p[6], &p[3]);
                    quatFromAxisAngle(qa, axis, -e->ang2);
                }
                rotateVec3ByQuat(qa, &p[3], dir);
                d = raycastTerrainAndNpcs(p, dir, *(u16 *)(arg0 + 0x198), &id, e->range, 0, &dist[0], hit[0], one, &fl[0]);
                e->b[0xB] = (u32)(d * (255.0f / e->range));
                if (fl[i] & 1) {
                    rotateVec3ByMat3x3((Vec3f *)inv, hit[i], hit[i]);
                    buildSineWaveEffectGeometryB(i, (SineWaveIn *)hit[i], dist[i], (SineWaveOut *)e);
                }
                break;
            case 1:
                if (!crossed) {
                    crossed = 1;
                    vec3Cross(axis, &p[6], &p[3]);
                    quatFromAxisAngle(qa, axis, -e->ang2);
                }
                quatMultiply(q0, qa, qb);
                rotateVec3ByQuat(qb, &p[3], dir);
                d = raycastTerrainAndNpcs(p, dir, *(u16 *)(arg0 + 0x198), &id, e->range, 0, &dist[1], hit[1], one, &fl[1]);
                e->b[0x5] = (u32)(d * (255.0f / e->range));
                if (fl[i] & 1) {
                    rotateVec3ByMat3x3((Vec3f *)inv, hit[i], hit[i]);
                    buildSineWaveEffectGeometryB(i, (SineWaveIn *)hit[i], dist[i], (SineWaveOut *)e);
                }
                break;
            case 2:
                if (!crossed) {
                    crossed = 1;
                    vec3Cross(axis, &p[6], &p[3]);
                    quatFromAxisAngle(qa, axis, -e->ang2);
                }
                quatMultiply(q1, qa, qb);
                rotateVec3ByQuat(qb, &p[3], dir);
                d = raycastTerrainAndNpcs(p, dir, *(u16 *)(arg0 + 0x198), &id, e->range, 0, &dist[2], hit[2], one, &fl[2]);
                e->b[0x11] = (u32)(d * (255.0f / e->range));
                if (fl[i] & 1) {
                    rotateVec3ByMat3x3((Vec3f *)inv, hit[i], hit[i]);
                    buildSineWaveEffectGeometryB(i, (SineWaveIn *)hit[i], dist[i], (SineWaveOut *)e);
                }
                break;
            default:
                continue;
            }
        }
    }
    if (*(u16 *)(arg0 + 0x110) & 0x80) {
        return;
    }
    if (!crossed) {
        vec3Cross(axis, &p[6], &p[3]);
    }
    d = raycastTerrainAndNpcs(p, &p[3], *(u16 *)(arg0 + 0x198), &id, e->b[0xA] * (e->range / 255.0f), 0, NULL, NULL, 2, &fl[0]);
    if (fl[0] & 2) {
        e->b[0xA] = (u32)(d * (255.0f / e->range));
        *(u16 *)(s + 0xF0) = id;
    } else {
        *(u16 *)(s + 0xF0) = 0xFFFF;
    }
    quatFromAxisAngle(qb, axis, e->ang2);
    rotateVec3ByQuat(qb, &p[3], dir);
    d = raycastTerrainAndNpcs(p, dir, *(u16 *)(arg0 + 0x198), &id, e->b[0x9] * (e->range / 255.0f), 0, NULL, NULL, 2, &fl[0]);
    if (fl[0] & 2) {
        e->b[0x9] = (u32)(d * (255.0f / e->range));
    }
    quatFromAxisAngle(qb, axis, -e->ang2);
    rotateVec3ByQuat(qb, &p[3], dir);
    d = raycastTerrainAndNpcs(p, dir, *(u16 *)(arg0 + 0x198), &id, e->b[0xB] * (e->range / 255.0f), 0, NULL, NULL, 2, &fl[0]);
    if (fl[0] & 2) {
        e->b[0xB] = (u32)(d * (255.0f / e->range));
    }
    quatFromAxisAngle(qb, &p[6], e->ang * -0.33333334f);
    rotateVec3ByQuat(qb, &p[3], dir);
    d = raycastTerrainAndNpcs(p, dir, *(u16 *)(arg0 + 0x198), &id, e->b[0x7] * (e->range / 255.0f), 0, NULL, NULL, 2, &fl[0]);
    if (fl[0] & 2) {
        e->b[0x7] = (u32)(d * (255.0f / e->range));
    }
    quatFromAxisAngle(qb, &p[6], e->ang * 0.33333334f);
    rotateVec3ByQuat(qb, &p[3], dir);
    d = raycastTerrainAndNpcs(p, dir, *(u16 *)(arg0 + 0x198), &id, e->b[0xD] * (e->range / 255.0f), 0, NULL, NULL, 2, &fl[0]);
    if (fl[0] & 2) {
        e->b[0xD] = (u32)(d * (255.0f / e->range));
    }
}

typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    u8 grid[0x15];
} SaGrid;

s32 spawnAndUpdateEffectActors(u8 *arg0, s32 arg1, f32 *arg2, f32 *arg3) {
    f32 maxLo[3];
    f32 maxHi[3];
    f32 firstLo[3];
    f32 firstHi[3];
    s32 maxLoIdx[3];
    s32 maxHiIdx[3];
    s32 firstLoIdx[3];
    s32 firstHiIdx[3];
    SaGrid *s;
    s32 i;
    s32 j;
    s32 k;
    s32 row;
    s32 col;
    f32 v;
    f32 w;
    f32 best;
    f32 x;
    f32 y;
    s32 r;

    row = 0;
    col = 0;
    r = 8;
    s = (SaGrid *)(arg0 + 0x50);
    x = 0.0f;
    y = 0.0f;
    if (s->grid[0xA] != 0xFF) {
        v = ((f32)s->grid[0xA] / 255.0f) * s->f8;
        if (v < s->fC) {
            for (i = 0; i < 3; i++) {
                maxHiIdx[i] = 3;
                maxLoIdx[i] = 3;
                firstHiIdx[i] = -1;
                firstLoIdx[i] = -1;
            }
            firstHi[1] = v;
            firstLo[1] = v;
            maxHi[1] = v;
            maxLo[1] = v;
            w = ((f32)s->grid[9] / 255.0f) * s->f8;
            firstHi[0] = w;
            firstLo[0] = w;
            maxHi[0] = w;
            maxLo[0] = w;
            w = ((f32)s->grid[0xB] / 255.0f) * s->f8;
            firstHi[2] = w;
            firstLo[2] = w;
            maxHi[2] = w;
            maxLo[2] = w;
            for (i = 2; i >= 0; i--) {
                for (j = 0; j < 3; j++) {
                    v = ((f32)s->grid[j + i * 3] / 255.0f) * s->f8;
                    if (s->fC < v && firstLoIdx[j] == -1) {
                        firstLoIdx[j] = i;
                        firstLo[j] = v;
                    }
                    if (maxLo[j] < v) {
                        maxLo[j] = v;
                        maxLoIdx[j] = i;
                    }
                    v = ((f32)s->grid[j + (6 - i) * 3] / 255.0f) * s->f8;
                    if (s->fC < v && firstHiIdx[j] == -1) {
                        firstHiIdx[j] = 6 - i;
                        firstHi[j] = v;
                    }
                    if (maxHi[j] < v) {
                        maxHi[j] = v;
                        maxHiIdx[j] = 6 - i;
                    }
                }
            }
            if (firstLoIdx[1] != -1 || firstHiIdx[1] != -1 || firstLoIdx[0] != -1 || firstHiIdx[0] != -1) {
                best = -1.0f;
                if (firstLoIdx[1] != -1 && best < firstLo[1]) {
                    row = firstLoIdx[1];
                    best = firstLo[1];
                    col = 0;
                }
                if (firstHiIdx[1] != -1 && (best < firstHi[1] || (firstHi[1] == best && (rand() & 1)))) {
                    col = 0;
                    row = firstHiIdx[1];
                    best = firstHi[1];
                }
                if (firstLoIdx[0] != -1 && (best < firstLo[0] || (firstLo[0] == best && (rand() & 1)))) {
                    col = 1;
                    row = firstLoIdx[0];
                    best = firstLo[0];
                }
                if (firstHiIdx[0] != -1 && (best < firstHi[0] || (firstHi[0] == best && (rand() & 1)))) {
                    row = firstHiIdx[0];
                    col = 1;
                }
            } else {
                best = -1.0f;
                if (best < maxLo[1]) {
                    row = maxLoIdx[1];
                    best = maxLo[1];
                    col = 0;
                }
                if (best < maxHi[1] || (maxHi[1] == best && (rand() & 1))) {
                    col = 0;
                    row = maxHiIdx[1];
                    best = maxHi[1];
                }
                if (best < maxLo[0] || (maxLo[0] == best && (rand() & 1))) {
                    col = 1;
                    row = maxLoIdx[0];
                    best = maxLo[0];
                }
                if (best < maxHi[0] || (maxHi[0] == best && (rand() & 1))) {
                    col = 1;
                    row = maxHiIdx[0];
                    best = maxHi[0];
                }
                if (best < s->fC) {
                    if (firstLoIdx[2] != -1 && best < firstLo[2]) {
                        row = firstLoIdx[2];
                        best = firstLo[2];
                        col = -1;
                    }
                    if (firstHiIdx[2] != -1 && (best < firstHi[2] || (firstHi[2] == best && (rand() & 1)))) {
                        col = -1;
                        row = firstHiIdx[2];
                        best = firstHi[2];
                    }
                    if (best < s->fC) {
                        if (best < maxLo[2] || (maxLo[2] == best && (rand() & 1))) {
                            col = -1;
                            row = maxLoIdx[2];
                            best = maxLo[2];
                        }
                        if (best < maxHi[2] || (maxHi[2] == best && (rand() & 1))) {
                            row = maxHiIdx[2];
                            col = -1;
                        }
                    }
                }
            }
            x = (s->f0 / 3.0f) * (f32)(row - 3);
            y = s->f4 * (f32)col;
            if (y == 0.0f) {
                if (x == 0.0f) {
                    r = 8;
                } else if (x < 0.0f) {
                    r = 6;
                } else {
                    r = 2;
                }
            } else if (y > 0.0f) {
                if (x == 0.0f) {
                    r = 0;
                } else if (x < 0.0f) {
                    r = 7;
                } else {
                    r = 1;
                }
            } else {
                if (x == 0.0f) {
                    r = 4;
                } else if (x < 0.0f) {
                    r = 5;
                } else {
                    r = 3;
                }
            }
        }
    }
    *arg2 = y;
    *arg3 = x;
    return r;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", executeActorType4Effect);

void clearObjectField112(void *arg0) {
    (*(s8 *)((u8 *)(arg0) + 0x112)) = 0;
}

typedef struct { s32 x, y, z; } T1V3;
struct T1Src {
    u8 pad0[0x1C];
    s32 unk1C;
    u8 *unk20;
    f32 unk24;
    s32 unk28;
    f32 *unk2C;
};

struct T1State {
    s32 unk0;
    u8 *unk4;
    u8 *unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    f32 unk1C;
    s32 unk20;
    struct T1Src *unk24;
    s32 unk28;
    f32 unk2C;
    f32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 pad4C[4];
    f32 unk50;
    u8 pad54[0xC];
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    f32 unk70;
    f32 unk74;
    f32 unk78;
    s32 unk7C;
    f32 unk80;
    f32 unk84;
    s32 unk88;
    u8 pad8C[4];
    s32 unk90;
    u8 pad94[4];
    s32 unk98;
    s32 unk9C;
    s32 unkA0;
    u8 padA4[4];
    f32 unkA8;
    u8 padAC[4];
    s32 unkB0;
    s32 unkB4;
    s32 unkB8;
    u8 quat[0x10];
    f32 unkCC;
    s32 unkD0;
    s32 unkD4;
    s32 unkD8;
    f32 unkDC;
    f32 unkE0;
    u8 padE4[4];
    s32 unkE8;
    u8 padEC[8];
    s32 unkF4;
    s32 unkF8;
    u8 unkFC;
    u8 padFD;
    u8 unkFE;
    u8 padFF[5];
    s32 unk104;
};

extern void *getNpcContextField8(u16);
extern void setupActorAnchorTransformType1(void *, void *, void *, void *, f32);
extern void quatFromCardinalAxis(f32 *, u8, f32);

s32 initActorAsType1(u8 *arg0, struct T1Src *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    u8 *obj = arg0;
    struct T1State *s = (struct T1State *)(obj + 8);
    s32 *ctx;
    u8 *end;

    obj[0x112] = 1;
    s->unk24 = arg1;
    s->unk28 = 0;
    s->unk0 = arg1->unk1C;
    s->unk4 = arg1->unk20;
    end = arg1->unk20 + arg1->unk1C * 0xC;
    s->unk14 = 0;
    s->unk10 = 0;
    s->unkC = 0;
    s->unk34 = 0;
    s->unk20 = 0;
    s->unk18 = 0;
    s->unk1C = 1.0f;
    s->unk48 = arg2;
    s->unk50 = arg2;
    s->unk8 = end;
    s->unk2C = arg2 / arg1->unk24;
    s->unk104 = 0;
    s->unkFC = 0;
    s->unkFE = 0;
    s->unk30 = arg3 * s->unk2C;
    if (s->unk30 > 1.0f) {
        s->unk30 = 0.0f;
    }
    if (arg1->unk28 != 0) {
        s->unk40 = *arg1->unk2C;
    } else {
        s->unk40 = 10.0f;
    }
    s->unk3C = 0;
    s->unk44 = arg6;
    s->unk38 = 0;
    ctx = (s32 *)getNpcContextField8(*(u16 *)(arg0 + 0x198));
    setupActorAnchorTransformType1(s, (u8 *)arg1 + 0x10, ctx, &s->unkC, s->unk30);
    s->unkA8 = 0.0f;
    s->unk60 = 0;
    s->unk64 = 0;
    s->unk68 = 0;
    s->unk6C = 0;
    s->unk88 = 0;
    s->unk98 = 0;
    s->unk9C = 0;
    s->unkA0 = 0;
    s->unk90 = 0;
    s->unk70 = 2.0f;
    s->unk74 = 0.05f;
    s->unk78 = 0.022f;
    s->unk80 = 0.5f;
    s->unk84 = 0.5f;
    quatFromCardinalAxis((f32 *)s->quat, 2, s->unkA8);
    s->unkB0 = 0;
    s->unkB4 = 0;
    s->unkB8 = 0;
    s->unk7C = 0;
    s->unkDC = arg4;
    s->unkCC = 360.0f;
    s->unkE0 = arg5;
    *(T1V3 *)&s->unkD0 = *(T1V3 *)ctx;
    s->unkE8 = 0;
    s->unkF4 = 0;
    s->unkF8 = 0;
    return 1;
}

extern void *getNpcContextField8(u16);
extern void setupActorAnchorTransformType1(void *, void *, void *, void *, f32);

u8 initActorAsType1WithAnchor(u8 *a0, u8 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    u8 *p = a0 + 8;

    *(u8 *)(a0 + 0x112) = 1;
    *(u8 **)(p + 0x24) = arg1;
    *(s32 *)(p + 0x28) = 0;
    *(s32 *)(a0 + 8) = *(s32 *)(arg1 + 0x1C);
    *(s32 *)(p + 4) = *(s32 *)(arg1 + 0x20);
    *(s32 *)(p + 8) = *(s32 *)(arg1 + 0x20) + *(s32 *)(arg1 + 0x1C) * 12;
    *(s32 *)(p + 0x14) = 0;
    *(s32 *)(p + 0x10) = 0;
    *(s32 *)(p + 0xC) = 0;
    *(s32 *)(p + 0x34) = 0;
    *(s32 *)(p + 0x20) = 0;
    *(s32 *)(p + 0x18) = 0;
    *(f32 *)(p + 0x1C) = 1.0f;
    *(f32 *)(p + 0x48) = arg2;
    *(f32 *)(p + 0x50) = arg2;
    *(f32 *)(p + 0x2C) = arg2 / *(f32 *)(arg1 + 0x24);
    *(s32 *)(p + 0x104) = 0;
    *(u8 *)(p + 0xFC) = 0;
    *(u8 *)(p + 0xFE) = 0;
    *(f32 *)(p + 0x30) = arg3 * *(f32 *)(p + 0x2C);
    if (*(f32 *)(p + 0x30) > 1.0f) {
        *(s32 *)(p + 0x30) = 0;
    }
    if (*(s32 *)(arg1 + 0x28) != 0) {
        *(f32 *)(p + 0x40) = **(f32 **)(arg1 + 0x2C);
    } else {
        *(f32 *)(p + 0x40) = 10.0f;
    }
    *(s32 *)(p + 0x3C) = 0;
    *(f32 *)(p + 0x44) = arg6;
    *(s32 *)(p + 0x38) = 0;
    setupActorAnchorTransformType1(p, arg1 + 0x10, getNpcContextField8(*(u16 *)(a0 + 0x198)), p + 0xC, *(f32 *)(p + 0x30));
    *(s32 *)(p + 0xF4) = 0;
    *(s32 *)(p + 0xF8) = 0;
    return 1;
}

s32 setType1ActorVelocity(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    u8 *p;
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 1) {
        p = (u8 *)arg0 + 8;
        *(f32 *)(p + 0x7C) = arg2;
        *(f32 *)(p + 0xCC) = arg3;
        *(f32 *)(p + 0x60) = arg1 * 0.25f;
        return 1;
    }
    return 0;
}

f32 setType1ActorField40(void *arg0, f32 arg1) {
    f32 var_fv0;

    var_fv0 = 0.0f;
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 1) {
        var_fv0 = (*(f32 *)((u8 *)(arg0) + 0x40));
        (*(f32 *)((u8 *)(arg0) + 0x40)) = arg1;
    }
    return var_fv0;
}

typedef struct { f32 x, y, z; } Vec3Struct_2;
extern void *getNpcContextField8(u16);

s32 initActorAsType2(void *arg0, s32 arg1, f32 arg2, f32 arg3) {
    u8 *p = (u8 *)arg0 + 8;
    void *ctx;

    *(u8 *)((u8 *)arg0 + 0x112) = 2;
    ctx = getNpcContextField8(*(u16 *)((u8 *)arg0 + 0x198));
    *(Vec3Struct_2 *)((u8 *)arg0 + 8) = *(Vec3Struct_2 *)((u8 *)ctx + 0xC);
    *(f32 *)(p + 0x18) = 0.0f;
    *(f32 *)(p + 0xC) = *(f32 *)(p + 0x10) = arg3;
    *(f32 *)(p + 0x14) = arg2;
    *(s32 *)(p + 0x30) = arg1;
    *(u8 *)(p + 0x34) = *(u8 *)(p + 0x35) = 0;
    *(f32 *)(p + 0x2C) = *(f32 *)(p + 0x1C) = *(f32 *)(p + 0x20) = *(f32 *)(p + 0x24) = *(f32 *)(p + 0x28) = *(f32 *)(p + 0x18);
    return 1;
}

s32 setType2ActorVelocity(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    u8 *p;
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 2) {
        p = (u8 *)arg0 + 8;
        *(s32 *)(p + 0x18) = 0;
        *(f32 *)(p + 0x24) = arg1;
        *(f32 *)(p + 0x28) = arg2;
        *(f32 *)(p + 0x1C) = arg3;
        *(f32 *)(p + 0x20) = arg4;
        *(f32 *)(p + 0x2C) = arg5;
        return 1;
    }
    return 0;
}

typedef struct { f32 x, y, z; } Vec3Struct_3;
extern void *getNpcContextField8(u16);

s32 initActorAsType3(void *arg0, s32 arg1, f32 arg2, f32 arg3) {
    u8 *p = (u8 *)arg0 + 8;
    void *ctx;

    *(u8 *)((u8 *)arg0 + 0x112) = 3;
    ctx = getNpcContextField8(*(u16 *)((u8 *)arg0 + 0x198));
    *(Vec3Struct_3 *)((u8 *)arg0 + 8) = *(Vec3Struct_3 *)((u8 *)ctx + 0xC);
    *(f32 *)(p + 0x18) = 0.0f;
    *(f32 *)(p + 0xC) = *(f32 *)(p + 0x10) = arg3;
    *(f32 *)(p + 0x14) = arg2;
    *(s32 *)(p + 0x30) = arg1;
    *(u8 *)(p + 0x34) = *(u8 *)(p + 0x35) = 0;
    *(f32 *)(p + 0x2C) = *(f32 *)(p + 0x1C) = *(f32 *)(p + 0x20) = *(f32 *)(p + 0x24) = *(f32 *)(p + 0x28) = *(f32 *)(p + 0x18);
    return 1;
}

s32 setType3ActorParams(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    u8 *p;
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 3) {
        p = (u8 *)arg0 + 8;
        *(s32 *)(p + 0x18) = 0;
        *(f32 *)(p + 0x24) = arg1;
        *(f32 *)(p + 0x28) = arg2;
        *(f32 *)(p + 0x1C) = arg3;
        *(f32 *)(p + 0x20) = arg4;
        *(f32 *)(p + 0x2C) = arg5;
        return 1;
    }
    return 0;
}

extern void executeActorType1Effect(void *, f32);
extern void executeActorType2Effect(void *, f32);
extern void executeActorType3Effect(void *, f32);
extern void executeActorType4Effect(void *, f32);

void dispatchEffectByActorType(void *arg0, f32 arg1) {
    switch (*(u8 *)((u8 *)arg0 + 0x112)) {
    case 1:
        executeActorType1Effect(arg0, arg1);
        break;
    case 2:
        executeActorType2Effect(arg0, arg1);
        break;
    case 3:
        executeActorType3Effect(arg0, arg1);
        break;
    case 4:
        executeActorType4Effect(arg0, arg1);
        break;
    }
}

s32 setType1ActorParams(void *arg0, f32 arg1, s8 arg2, s8 arg3, s8 arg4, s32 arg5) {
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 1) {
        (*(f32 *)((u8 *)(arg0) + 0x10C)) = arg1;
        (*(s8 *)((u8 *)(arg0) + 0x104)) = arg2;
        (*(s8 *)((u8 *)(arg0) + 0x105)) = arg3;
        (*(s8 *)((u8 *)(arg0) + 0x106)) = arg4;
        (*(s32 *)((u8 *)(arg0) + 0x108)) = arg5;
        return 1;
    }
    return 0;
}

void updateObjectFlags110(void *arg0, s32 arg1, s32 arg2) {
    (*(u16 *)((u8 *)(arg0) + 0x110)) = (u16) (((*(u16 *)((u8 *)(arg0) + 0x110)) | arg1) & ~arg2);
}

void resetType1FxFields(void *arg0) {
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 1) {
        (*(s32 *)((u8 *)(arg0) + 0xFC)) = 0;
        (*(f32 *)((u8 *)(arg0) + 0x100)) = 1.0f;
    }
}

void updateType1AnimRamp(void *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4) {
    u8 *p;
    u8 type = *(u8 *)((u8 *)arg0 + 0x112);
    f32 delta;

    if (type == 1) {
        p = (u8 *)arg0 + 8;
        if (arg4 == type) {
            *(f32 *)(p + 0x50) = *(f32 *)(p + 0x48) * arg1;
        } else {
            *(f32 *)(p + 0x50) = arg1;
        }
        if (*(f32 *)(p + 0x50) < arg2) {
            *(f32 *)(p + 0x50) = arg2;
        }
        delta = *(f32 *)(p + 0x50) - *(f32 *)(p + 0x48);
        *(f32 *)(p + 0x4C) = *(f32 *)(p + 0x48);
        *(f32 *)(p + 0x54) = delta;
        if (delta != 0.0f) {
            *(f32 *)(p + 0x58) = 0.0f;
            if (arg3 > 0.0f) {
                *(f32 *)(p + 0x5C) = 1.0f / arg3;
                return;
            }
            *(f32 *)(p + 0x48) = *(f32 *)(p + 0x50);
            *(f32 *)(p + 0x2C) = *(f32 *)(p + 0x48) / *(f32 *)(*(u8 **)(p + 0x24) + 0x24);
        }
    }
}

f32 getActorCurrentValueByType(void *arg0) {
    u8 temp_v1;

    temp_v1 = (*(u8 *)((u8 *)(arg0) + 0x112));
    switch (temp_v1) {                              /* irregular */
    case 1:
        return (*(f32 *)((u8 *)(arg0) + 0x50));
    case 4:
        return (*(f32 *)((u8 *)(arg0) + 0x28));
    default:
        return 0.0f;
    }
}

#include "main/1D000.h"
#include "main/192E0.h"
#include "main/3F160.h"
#include "main/5A750.h"

f32 sinf(f32);

void syncType1ActorFrameToAnchorIfZeroGate(u8 *arg0, Vec3f arg1) {
    Mat4x3 sp10;
    Mat4x3 sp40;
    Vec3f sp70;
    f32 ang;
    f32 s;
    u8 *s1;

    if (arg0[0x112] == 1) {
        s1 = arg0 + 8;
        if (*(f32 *)(s1 + 0xE8) == 0.0f) {
            mat34CrossRowsAndCopyPos(sp10, getNpcContextField8(*(u16 *)(arg0 + 0x198)), 1.0f);
            mat3x3InverseInto(sp40, sp10);
            rotateVec3ByMat3x3(sp40, arg1, sp70);
            if (sp70[0] != 0.0f || sp70[1] != 0.0f) {
                normalize_vector(sp70);
                ang = atan2Approx(sp70[0], sp70[1]);
                s = sinf(2.0f * ang);
                *(f32 *)(s1 + 0xE4) = ang * 57.29578f;
                s = s * 45.0f;
                *(f32 *)(s1 + 0xE8) = vec3Length(arg1);
                *(f32 *)(s1 + 0xEC) = 0.0f;
                *(f32 *)(s1 + 0xF0) = 0.5f;
                *(f32 *)(s1 + 0x14) += s;
            }
        }
    }
}

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    s16 unk6;
    s32 unk8;
} SpawnSlotMsg;

extern u16 findNpcInScaledBoxRegionExcludingPair(void *, u16, f32, u16, u16, s32);
extern s32 slotDispatcherIter(u16, s32, void *);
extern void *getNpcContextField8(u16);
extern u16 D_main_bss_8013957C;

s32 spawnNpcAnchoredEffectSlot(void *arg0, f32 arg1, s32 arg2) {
    SpawnSlotMsg msg;
    u16 id;
    u16 slot;
    s32 ret;

    ret = 0;
    slot = findNpcInScaledBoxRegionExcludingPair(getNpcContextField8(*(u16 *)((u8 *)arg0 + 0x198)), *(u16 *)((u8 *)arg0 + 0x198), arg1, 0xFFFF, D_main_bss_8013957C, 0);
    if (slot != 0xFFFF) {
        id = *(u16 *)((u8 *)arg0 + 0x198);
        slotDispatcherIter(slot, 6, &id);
        if (arg2 != 0) {
            msg.unk0 = 0xFFFF;
            msg.unk2 = 0xFFFF;
            msg.unk4 = 7;
            msg.unk6 = arg2;
            msg.unk8 = 0;
            slotDispatcherIter(slot, 5, &msg);
        }
        ret = 1;
    }
    return ret;
}

extern s32 rs_strcmp(u8 *, u8 *);
extern u8 *rs_strcpy(u8 *, u8 *);
extern void *load_asset(char *);
extern void model_animation_offset_convert(void *);

void *load_model_animation(char *name) {
    s32 i;
    s32 freeSlot;

    i = 0;
    freeSlot = -1;
    for (; i < 16; i++) {
        if (D_mission_overlay_8010C4A0[i].unk0 != 0) {
            if (rs_strcmp(D_mission_overlay_8010C4A0[i].pad, (u8 *)name) == 0) {
                return (void *)D_mission_overlay_8010C4A0[i].unk0;
            }
        } else {
            freeSlot = i;
        }
    }
    if (freeSlot == -1) {
        return NULL;
    }
    rs_strcpy(D_mission_overlay_8010C4A0[freeSlot].pad, (u8 *)name);
    D_mission_overlay_8010C4A0[freeSlot].unk0 = (s32)load_asset(name);
    model_animation_offset_convert((void *)D_mission_overlay_8010C4A0[freeSlot].unk0);
    return (void *)D_mission_overlay_8010C4A0[freeSlot].unk0;
}

extern void resetModelAnimSlotTable(void);

s32 reset_model_animations(void) {
    s32 i;

    resetModelAnimSlotTable();
    for (i = 15; i >= 0; i--) {
        D_mission_overlay_8010C4A0[i].unk0 = 0;
    }
    return 1;
}

extern void rs_free(void *);

s32 reset_and_free_model_animations(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (*(void **)&D_mission_overlay_8010C4A0[i].unk0 != NULL) {
            rs_free(*(void **)&D_mission_overlay_8010C4A0[i].unk0);
        }
        D_mission_overlay_8010C4A0[i].unk0 = 0;
    }
    resetModelAnimSlotTable();
    return 1;
}

s32 checkObjectiveHandles(f32 arg0) {
    s32 i;
    struct simpleCheckHandle *e;

    for (i = 0, e = simpleCheckHandles; i < 0x30; i++, e++) {
        if (e->active != 1) continue;

        switch (e->checkType) {
            case 0:
                if ((e->checks.boolcount.objectiveBooleanIndex != 0) && (gObjectiveBooleans[e->checks.boolcount.objectiveBooleanIndex - 1] != e->checks.boolcount.objectiveBooleanValue)) continue;
                if (e->checks.boolcount.objectiveCountIndex == 0) break;
                if ((e->checks.boolcount.unk07 == 0) && (gObjectiveCounts[e->checks.boolcount.objectiveCountIndex - 1] < e->objectiveCountValue)) continue;
                if (e->checks.boolcount.unk07 != 1) break;
                if (gObjectiveCounts[e->checks.boolcount.objectiveCountIndex - 1] >= e->objectiveCountValue) continue;
                break;
            case 1:
                e->checks.timer.timer -= arg0;
                if (e->checks.timer.timer > 0.0f) continue;
                break;
            default:
                continue;
        }
        e->active = 0;
        if (e->unk0D == 0) {
            e->handle();
        }
    }
    return 1;
}

s32 initializeObjectiveHandles(void) {
    s32 var_v1;

    for (var_v1 = 0x2F; var_v1 >= 0; var_v1--) {
        simpleCheckHandles[var_v1].active = 0;
    }
    return 1;
}

s32 addBooleanCountHandle(void (*handle)(), u8 booleanIndex, u8 booleanValue, u8 checkIndex, u32 checkCount, u8 arg5) {
    s32 var_v1;

    for (var_v1 = 0; var_v1 < 0x30; var_v1++) {
        if (simpleCheckHandles[var_v1].active == 0) break;
    }

    if (var_v1 == 0x30) {
        return 0;
    } else { 
        simpleCheckHandles[var_v1].active = 1;
        simpleCheckHandles[var_v1].unk0D = 0;
        simpleCheckHandles[var_v1].checkType = 0;
        simpleCheckHandles[var_v1].handle = handle;
        simpleCheckHandles[var_v1].checks.boolcount.objectiveBooleanIndex = booleanIndex;
        simpleCheckHandles[var_v1].checks.boolcount.objectiveBooleanValue = booleanValue;
        simpleCheckHandles[var_v1].checks.boolcount.objectiveCountIndex = checkIndex;
        simpleCheckHandles[var_v1].objectiveCountValue = checkCount;
        simpleCheckHandles[var_v1].checks.boolcount.unk07 = arg5;
        return 1;
    }
}

s32 addTimerHandle(void (*handle)(), f32 timerValue) {
    s32 var_v1;

    for (var_v1 = 0; var_v1 < 0x30; var_v1++) {
        if (simpleCheckHandles[var_v1].active == 0) break;
    }

    if (var_v1 == 0x30) {
        return 0;
    } else {
        simpleCheckHandles[var_v1].active = 1;
        simpleCheckHandles[var_v1].unk0D = 0;
        simpleCheckHandles[var_v1].checkType = 1;
        simpleCheckHandles[var_v1].handle = handle;
        simpleCheckHandles[var_v1].checks.timer.timer = timerValue;
        return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", fake_func_800FA248);

static u32 D_mission_overlay_800A8F68[] __attribute__((section(".rodata"))) = { 0xAFBF002C, 0xAFBE0028 };
