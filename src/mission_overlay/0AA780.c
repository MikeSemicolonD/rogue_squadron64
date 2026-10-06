#include "common.h"

#include "PR/gu.h"

#include "rs_math.h"
#include "main/1D000.h"
#include "mission_overlay/0AA780.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AA780", D_mission_overlay_800A5130);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AA780", computeAngleToTargetFromTransform);

void buildOrientationFromPosAndAngles(Mat4x3 m, Vec3f pos, Vec3f ang) {
    f32 t[6];
    register f32 k asm("$f24") = 0.017453292f;
    f32 a, b, c;
    f32 p1, p2, p3, p4;
    f32 sx, cx, sy, cy, sz, cz;
    m[3][0] = pos[0];
    m[3][1] = pos[1];
    m[3][2] = pos[2];
    a = ang[0] * k;
    b = ang[1] * k;
    c = ang[2];
    t[1] = cosf(a);
    t[0] = sinf(a);
    t[3] = cosf(b);
    t[2] = sinf(b);
    t[5] = cosf(c * k);
    t[4] = sinf(c * k);
    cx = t[1];
    cz = t[5];
    p1 = cx * cz;
    sz = t[4];
    p2 = cx * sz;
    cy = t[3];
    sx = t[0];
    p3 = sx * cz;
    sy = t[2];
    p4 = sx * sz;
    m[0][0] = p1 - p4 * sy;
    m[1][0] = -sz * cy;
    m[2][0] = p3 + p2 * sy;
    m[1][2] = sy;
    m[0][2] = -sx * cy;
    m[2][2] = cx * cy;
    m[0][1] = p2 + p3 * sy;
    m[1][1] = cz * cy;
    m[2][1] = p4 - p1 * sy;
}

extern f32 floatModulo(f32, f32);
#define VABS(x) ({ f32 _x = (x); f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(_x)); _r; })
void stepAngleTowardTarget(f32 *cur, f32 *tgt, f32 t, f32 *out) {
    register f32 a asm("$f12");
    register f32 b asm("$f4");
    register f32 b1 asm("$f4");
    register f32 q asm("$f0");
    f32 a1, sum, r, d;

    a = cur[0];
    b = tgt[0];
    if ((a >= 0.0f && b >= 0.0f) || (a <= 0.0f && b <= 0.0f)) {
        a1 = a + 180.0f;
        b1 = b + 180.0f;
        q = (b1 - a1) * t;
        r = (a1 + q) - 180.0f;
    } else {
        sum = VABS(a) + VABS(b);
        if (sum < 180.0f) {
            d = sum * t;
        } else {
            d = (360.0f - sum) * t;
        }
        if (a > 0.0f) {
            if (sum <= 180.0f) {
                r = a - d;
            } else {
                r = a + d;
            }
        } else if (sum <= 180.0f) {
            r = a + d;
        } else {
            r = a - d;
        }
    }
    floatModulo(r, 180.0f);
    out[0] = r;
    a = cur[1];
    b = tgt[1];
    if ((a >= 0.0f && b >= 0.0f) || (a <= 0.0f && b <= 0.0f)) {
        a1 = a + 180.0f;
        b1 = b + 180.0f;
        q = (b1 - a1) * t;
        r = (a1 + q) - 180.0f;
    } else {
        sum = VABS(a) + VABS(b);
        if (sum < 180.0f) {
            d = sum * t;
        } else {
            d = (360.0f - sum) * t;
        }
        if (a > 0.0f) {
            if (sum <= 180.0f) {
                r = a - d;
            } else {
                r = a + d;
            }
        } else if (sum <= 180.0f) {
            r = a + d;
        } else {
            r = a - d;
        }
    }
    floatModulo(r, 180.0f);
    out[1] = r;
    a = cur[2];
    b = tgt[2];
    if ((a >= 0.0f && b >= 0.0f) || (a <= 0.0f && b <= 0.0f)) {
        a1 = a + 180.0f;
        b1 = b + 180.0f;
        q = (b1 - a1) * t;
        r = (a1 + q) - 180.0f;
    } else {
        sum = VABS(a) + VABS(b);
        if (sum < 180.0f) {
            d = sum * t;
        } else {
            d = (360.0f - sum) * t;
        }
        if (a > 0.0f) {
            if (sum <= 180.0f) {
                r = a - d;
            } else {
                r = a + d;
            }
        } else if (sum <= 180.0f) {
            r = a + d;
        } else {
            r = a - d;
        }
    }
    floatModulo(r, 180.0f);
    out[2] = r;
}

void clampVec3ToUnitIfLongerThan(Vec3f arg0) {
    f32 temp_fv0;

    temp_fv0 = vec3Length(arg0);
    if (temp_fv0 >= 0.0001f) {
        arg0[0] /= temp_fv0;
        arg0[1] /= temp_fv0;
        arg0[2] /= temp_fv0;
    }
}

void scaleVec3ByScalar(Vec3f arg0, f32 arg1, Vec3f arg2) {
    arg0[0] = arg2[0] * arg1;
    arg0[1] = arg2[1] * arg1;
    arg0[2] = arg2[2] * arg1;
}

void addScaledVec3ToVec3(Vec3f arg0, Vec3f arg1, f32 arg2, Vec3f arg3) {
    arg0[0] = arg1[0] + (arg3[0] * arg2);
    arg0[1] = arg1[1] + (arg3[1] * arg2);
    arg0[2] = arg1[2] + (arg3[2] * arg2);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AA780", buildRotationMatrixFromEulerAngles);

void buildTransformMatrixFromEulerAngles(f32 (*arg0)[3], f32 arg1, f32 arg2, f32 arg3) {
    f32 v[6];
    f32 t1;
    f32 t2;
    f32 t3;
    f32 s1, c1, s2, c2, s3, c3;
    f32 a, b, c, d;

    arg0[3][0] = 0.0f;
    arg0[3][1] = 0.0f;
    arg0[3][2] = 0.0f;
    t1 = arg1 * 0.017453292f;
    v[1] = cosf(t1);
    v[0] = sinf(t1);
    t2 = arg2 * 0.017453292f;
    v[3] = cosf(t2);
    v[2] = sinf(t2);
    t3 = arg3 * 0.017453292f;
    v[5] = cosf(t3);
    v[4] = sinf(t3);
    c1 = v[1];
    s3 = v[4];
    c2 = v[3];
    s2 = v[2];
    s1 = v[0];
    c3 = v[5];
    b = c1 * c3;
    c = c1 * s3;
    d = s1 * c3;
    a = s1 * s3;
    arg0[0][0] = b - (a * s2);
    arg0[1][0] = -s3 * c2;
    arg0[2][0] = d + (c * s2);
    arg0[0][2] = -s1 * c2;
    arg0[2][2] = c1 * c2;
    arg0[1][2] = s2;
    arg0[0][1] = c + (d * s2);
    arg0[1][1] = c3 * c2;
    arg0[2][1] = a - (b * s2);
}

__asm__(".word 0");

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AA780", fake_func_800AA6CC);

static u32 D_mission_overlay_800A51DC[] __attribute__((section(".rodata"))) = { 0x8FC20038 };
