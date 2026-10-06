#include "common.h"
#include "common_types.h"

#include "level_objectives.h"
#include "mission_overlay/0F3E90.h"

typedef struct { s32 unk0; u8 pad[0x20]; } ModelAnimSlot24;
extern ModelAnimSlot24 D_mission_overlay_8010C4A0[];

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", resolveScriptedNameTokenList);

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
                register f32 k asm("$f4") = 0.1f;
                __asm__ volatile("abs.s %0, %1" : "=f"(r) : "f"(q));
                r = r + k;
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
            __asm__ volatile("abs.s %0, %1" : "=f"(d) : "f"(x));
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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", updateNpcEffectIntensity);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0F3E90", D_mission_overlay_800A8BB8);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", executeActorType1Effect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", executeActorType2Effect);

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
void normalize_vector(f32 *);
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
                f32 a;
                f32 ab;
                register f32 x asm("$f0");
                __asm__ volatile("abs.s %0, %1" : "=f"(ab) : "f"(((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->timeRange)));
                s->timer = s->timeBase + ab;
                __asm__ volatile("abs.s %0, %1" : "=f"(ab) : "f"(((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->angRange)));
                a = s->angBase + ab;
                if (rand() & 1) {
                    x = a;
                } else {
                    x = -a;
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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", initActorAsType4);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", buildSineWaveEffectGeometryA);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", renderNpcAnchoredProceduralEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", spawnAndUpdateEffectActors);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", initActorAsType1WithAnchor);

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

#if 0
// The major mismatch with this is that the original code accesses a bunch of information
// via negative offsets from the unk0D element. This is strange, I don't think you can tickle
// GCC into doing this through "normal" code.
s32 checkObjectiveHandles(f32 arg0) {
    s32 var_s2;
    s32 temp_a0;
    s32 temp_a1;
    struct simpleCheckHandle *var_s1;

    for (var_s2 = 0; var_s2 < 0x30; var_s2++) {
        var_s1 = &simpleCheckHandles[var_s2];
        if (var_s1->active != 1) continue;

        switch (var_s1->checkType) {
            case 0:
                temp_a0 = var_s1->checks.boolcount.objectiveBooleanIndex;
                if ((temp_a0 != 0) && (gObjectiveBooleans[temp_a0 - 1] != var_s1->checks.boolcount.objectiveBooleanValue)) continue;

                temp_a0 = var_s1->checks.boolcount.objectiveCountIndex;
                if (temp_a0 == 0) break;
                temp_a1 = var_s1->checks.boolcount.unk07;
                if ((temp_a1 == 0) && (gObjectiveCounts[temp_a0 - 1] < var_s1->objectiveCountValue)) continue;

                if (var_s1->checks.boolcount.unk07 != 1) break;
                if (gObjectiveCounts[var_s1->checks.boolcount.unk07 - 1] >= var_s1->objectiveCountValue) continue;
                break;
            case 1:
                var_s1->checks.timer.timer -= arg0;
                if (var_s1->checks.timer.timer > 0.0f) continue;
                break;
            default:
                continue;
        }
        var_s1->active = 0;
        if (var_s1->unk0D == 0) {
            var_s1->handle();
        }
    }
    return 1;

//         if (simpleCheckHandles[var_s2].checkType != 0) {
//             if (simpleCheckHandles[var_s2].checkType != 1) continue;
//             simpleCheckHandles[var_s2].checks.timer.timer -= arg0;
//             if (simpleCheckHandles[var_s2].checks.timer.timer <= 0.0f) {
//                 simpleCheckHandles[var_s2].active = 0;
//                 if (simpleCheckHandles[var_s2].unk0D == 0) {
//                     simpleCheckHandles[var_s2].handle();
//                 }
//             }
//         } else {
//             temp_a0 = simpleCheckHandles[var_s2].checks.boolcount.objectiveBooleanIndex;
//             if ((temp_a0 == 0) ||
//                 (gObjectiveBooleans[temp_a0 - 1] == simpleCheckHandles[var_s2].checks.boolcount.objectiveBooleanValue)) {
//                     temp_a0 = simpleCheckHandles[var_s2].checks.boolcount.objectiveCountIndex;
//                     if (temp_a0 == 0) {
//                         temp_a1 = simpleCheckHandles[var_s2].checks.boolcount.unk07;
//                         if((temp_a1 != 0) || (gObjectiveCounts[temp_a0 - 1] >= simpleCheckHandles[var_s2].objectiveCountValue)) {
//                             if (temp_a1 == 1)
//                         }
//                     } else {
//                         simpleCheckHandles[var_s2].active = 0;
//                         if (simpleCheckHandles[var_s2].unk0D == 0) {
//                             simpleCheckHandles[var_s2].handle();
//                         }
//                     }
//                 }
//         }
//     }
//     return 1;
//     var_s2 = 0;
//     var_s1 = simpleCheckHandles;
//     var_s0 = &simpleCheckHandles->unk0D;
//     do {
//         temp_a1 = var_s0->unk1;
//         if (temp_a1 == 1) {
//             temp_v0 = var_s0->unk-1;
//             if (temp_v0 != 0) {
//                 if (temp_v0 != temp_a1) {
//                     var_s2 += 1;
//                 } else {
//                     temp_fv0 = var_s0->unk-9 - arg0;
//                     var_s0->unk-9 = temp_fv0;
//                     if (!(temp_fv0 > 0.0f)) {
//                         goto block_14;
//                     }
//                     goto block_16;
//                 }
//             } else {
//                 temp_v0_2 = (bitwise u8) var_s0->unk-9;
//                 if ((temp_v0_2 == 0) || (gObjectiveBooleans[temp_v0_2].unk-1 == var_s0->unk-8)) {
//                     temp_v0_3 = var_s0->unk-7;
//                     if (temp_v0_3 != 0) {
//                         temp_a0 = var_s0->unk-6;
//                         if ((temp_a0 != 0) || ((s32) gObjectiveCounts[temp_v0_3 - 1] >= var_s0->unk-5)) {
//                             if (temp_a0 == temp_a1) {
//                                 if ((s32) gObjectiveCounts[var_s0->unk-7 - 1] < var_s0->unk-5) {
//                                     goto block_14;
//                                 }
//                             } else {
//                                 goto block_14;
//                             }
//                         }
//                     } else {
// block_14:
//                         var_s0->unk1 = 0U;
//                         if (var_s0->unk0 == 0) {
//                             var_s1->handle();
//                         }
//                     }
//                 }
//                 goto block_16;
//             }
//         } else {
// block_16:
//             var_s2 += 1;
//         }
//         var_s0 += 0x10;
//         var_s1 += 0x10;
//     } while (var_s2 < 0x30);
//     return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", checkObjectiveHandles);
#endif

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
