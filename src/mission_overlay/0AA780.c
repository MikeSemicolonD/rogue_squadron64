#include "common.h"

#include "PR/gu.h"

#include "rs_math.h"
#include "main/1D000.h"
#include "mission_overlay/0AA780.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AA780", D_mission_overlay_800A5130);

void computeAngleToTargetFromTransform(Mat4x3 m, Vec3f pos, Vec3f ang) {
    Vec3f c2;
    Vec3f c1;
    Vec3f c0;
    Vec3f h;
    Vec3f v;
    f32 len;
    f32 d;
    f32 z;
    f32 l2;

    pos[0] = m[3][0];
    pos[1] = m[3][1];
    pos[2] = m[3][2];
    c2[0] = m[0][2];
    c2[1] = m[1][2];
    c2[2] = m[2][2];
    c1[0] = m[0][1];
    c1[1] = m[1][1];
    c1[2] = m[2][1];
    c0[0] = m[0][0];
    c0[1] = m[1][0];
    c0[2] = m[2][0];
    h[0] = c2[0];
    h[1] = 0.0f;
    h[2] = c2[2];
    len = vec3Length(h);
    if (len < 0.001f) {
        d = 90.0f - sinfApprox(-c0[0]) * 57.29578f;
        if ((0.0f < c0[2]) == (0.0f < c2[1])) {
            d = -d;
        }
        ang[2] = d;
        ang[0] = 0.0f;
    } else {
        d = 90.0f - sinfApprox(h[2] / len) * 57.29578f;
        if (0.0f < c2[0]) {
            d = -d;
        }
        ang[0] = d;
    }
    if (len < 0.001f) {
        ang[1] = 90.0f;
    } else {
        d = vec3Dot(h, c2) / len;
        if (d >= 1.0f) {
            ang[1] = 0.0f;
        } else {
            d = 90.0f - sinfApprox(d) * 57.29578f;
            ang[1] = d;
        }
    }
    if (c2[1] < 0.0f) {
        ang[1] = -ang[1];
    }
    v[0] = h[2];
    v[1] = z = 0.0f;
    v[2] = -h[0];
    l2 = vec3Length(v);
    if (len >= 0.001) {
        d = vec3Dot(v, c0) / l2;
        if (d >= 1.0f) {
            ang[2] = z;
        } else if (d <= -1.0f) {
            ang[2] = 180.0f;
        } else {
            ang[2] = 90.0f - sinfApprox(d) * 57.29578f;
        }
        if (0.0f < c0[1]) {
            ang[2] = -ang[2];
        }
    }
}

void buildOrientationFromPosAndAngles(Mat4x3 m, Vec3f pos, Vec3f ang) {
    f32 t[6];
    f32 a, b, c;
    f32 p1, p2, p3, p4;
    f32 sx, cx, sy, cy, sz, cz;
    m[3][0] = pos[0];
    m[3][1] = pos[1];
    m[3][2] = pos[2];
    a = ang[0] * 0.017453292f;
    b = ang[1] * 0.017453292f;
    c = ang[2];
    t[1] = cosf(a);
    t[0] = sinf(a);
    t[3] = cosf(b);
    t[2] = sinf(b);
    t[5] = cosf(c * 0.017453292f);
    t[4] = sinf(c * 0.017453292f);
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
void stepAngleTowardTarget(f32 *cur, f32 *tgt, f32 t, f32 *out) {
    f32 a;
    f32 b;
    f32 sum, r, d;

    a = cur[0];
    b = tgt[0];
    if ((a >= 0.0f && b >= 0.0f) || (a <= 0.0f && b <= 0.0f)) {
        a += 180.0f;
        b += 180.0f;
        r = (a + (b - a) * t) - 180.0f;
    } else {
        sum = FABSF_VAL(a) + FABSF_VAL(b);
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
        a += 180.0f;
        b += 180.0f;
        r = (a + (b - a) * t) - 180.0f;
    } else {
        sum = FABSF_VAL(a) + FABSF_VAL(b);
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
        a += 180.0f;
        b += 180.0f;
        r = (a + (b - a) * t) - 180.0f;
    } else {
        sum = FABSF_VAL(a) + FABSF_VAL(b);
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

void buildRotationMatrixFromEulerAngles(f32 (*arg0)[3], f32 arg1, f32 arg2, f32 arg3) {
    f32 v[6];
    f32 t1;
    f32 t2;
    f32 t3;
    f32 s1, c1, c2, s3, c3;
    register f32 s2 asm("$f6");
    f32 a, b, c, d;

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
    c3 = v[5];
    s1 = v[0];
    c2 = v[3];
    s2 = v[2];
    s3 = v[4];
    b = c1 * c3;
    c = c1 * s3;
    d = s1 * c3;
    a = s1 * s3;
    arg0[1][2] = s2;
    arg0[1][0] = -s3 * c2;
    arg0[0][2] = -s1 * c2;
    arg0[2][2] = c1 * c2;
    arg0[1][1] = c3 * c2;
    { register f32 pa asm("$f26") = a * s2; register f32 pc asm("$f24") = c * s2; register f32 pd asm("$f22") = d * s2; register f32 pb asm("$f2") = b * s2;
    arg0[0][0] = b - pa;
    arg0[2][0] = d + pc;
    arg0[0][1] = c + pd;
    arg0[2][1] = a - pb; }
}

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
