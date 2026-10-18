#include "common.h"

#include "main/66660.h"
#include "rs_math.h"

#define VABS(x) ({ f32 _x = (x); f32 _r; FABSF(_r, _x); _r; })
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3;
extern void evalCubicSplineAtTimeF(void *, f32, V3 *) __asm__("evalCubicSplineAtTime");
f32 sinfApprox(f32);
void buildRotationMatrixSlot1(Mat4x3, f32);
f32 normalize_vector(Vec3f);
void transformVec3ByMat34(Mat4x3, Vec3f, Vec3f);

void buildPositionAndCallTransformHelper(void *spline, void *offv, void *outv, void *rotv, f32 arg4, f32 arg5, f32 t) {
#define off ((f32 *)offv)
#define out ((f32 *)outv)
#define rot ((f32 *)rotv)
    V3 p0;
    V3 p1;
    V3 d;
    V3 n;
    f32 m[12];
    f32 prevYaw;
    f32 diff;

    t = (t * 0.999f) + 0.001f;
    prevYaw = rot[1];
    evalCubicSplineAtTimeF(spline, t - 0.0009f, &p0);
    p0.x += off[0];
    p0.y += off[1];
    p0.z += off[2];
    evalCubicSplineAtTimeF(spline, t, &p1);
    p1.x += off[0];
    p1.y += off[1];
    p1.z += off[2];
    d.x = p1.x - p0.x;
    d.y = p1.y - p0.y;
    d.z = p1.z - p0.z;
    *(V3 *)out = p1;
    n = d;
    n.y = 0.0f;
    normalize_vector((f32 *)&n);
    if (n.x < 0.0f && n.z < 0.0f) {
        rot[1] = FABSF_SELF(sinfApprox(-n.x) * 57.29578f) - 180.0f;
    } else if (n.x >= 0.0f && n.z < 0.0f) {
        rot[1] = -FABSF_SELF(sinfApprox(n.x) * 57.29578f) - 180.0f;
    } else if (n.x < 0.0f && n.z >= 0.0f) {
        rot[1] = -FABSF_SELF(sinfApprox(-n.x) * 57.29578f);
    } else {
        rot[1] = VABS(sinfApprox(n.x) * 57.29578f);
    }
    buildRotationMatrixSlot1((f32 *)m, -rot[1]);
    transformVec3ByMat34((f32 *)m, (f32 *)&d, (f32 *)&n);
    n.x = 0.0f;
    normalize_vector((f32 *)&n);
    if (n.y < 0.0f && n.z < 0.0f) {
        rot[0] = FABSF_SELF(sinfApprox(-n.z) * 57.29578f) - 270.0f;
    } else if (n.y >= 0.0f && n.z < 0.0f) {
        rot[0] = -FABSF_SELF(sinfApprox(-n.z) * 57.29578f) - 90.0f;
    } else if (n.y < 0.0f && n.z >= 0.0f) {
        rot[0] = -FABSF_SELF(sinfApprox(n.z) * 57.29578f) - 270.0f;
    } else {
        rot[0] = FABSF_SELF(sinfApprox(n.z) * 57.29578f) - 90.0f;
    }
    diff = rot[1] - prevYaw;
    if (diff > 180.0f) {
        diff -= 360.0f;
    }
    if (diff < -180.0f) {
        diff += 360.0f;
    }
    diff = rot[2] + (diff * arg4);
    rot[2] = diff * 0.9375f;
}
#undef off
#undef out
#undef rot

typedef struct {
    u8 pad0[0x24];
    f32 nearZ;
} BoundsView;
#define VABS(x) ({ f32 _x = (x); f32 _r; FABSF(_r, _x); _r; })
extern Vec3f D_main_8009FC50[8];
extern u8 D_main_8009FCB0[12][2];
extern void mat3x4Multiply(void *, void *, void *);

s32 projectModelBoundsToScreen(BoundsView *view, void *arg1, f32 *min, f32 *max, u8 mode) {
    Vec3f cube[8];
    Vec3f proj;
    Mat4x3 mat;
    u8 i;
    u8 c0;
    u8 c1;
    f32 *p;
    f32 *q;
    f32 *r;
    f32 nz;

    mat3x4Multiply((u8 *)view + 0x2C, arg1, mat);
    for (i = 0; i < 8; i++) {
        cube[i][0] = D_main_8009FC50[i][0] < 0.0f ? min[0] : max[0];
        cube[i][1] = D_main_8009FC50[i][1] < 0.0f ? min[1] : max[1];
        cube[i][2] = D_main_8009FC50[i][2] < 0.0f ? min[2] : max[2];
        p = cube[i];
        transformVec3ByMat34(mat, p, p);
        if (mode == 0) {
            if (p[2] == 0.0f) {
                return 1;
            }
            proj[0] = p[0] * (1.0f / p[2]);
            proj[1] = p[1] * (1.0f / p[2]);
            proj[2] = p[2] * (1.0f / p[2]);
            if (view->nearZ < proj[2] && VABS(proj[0]) < 1.0f && VABS(proj[1]) < 1.0f) {
                return 1;
            }
        }
        cube[i][0] *= 1.3333334f;
        cube[i][1] *= 1.3333334f;
    }
    for (i = 0; i < 12; i++) {
        r = cube[D_main_8009FCB0[i][0]];
        c1 = 0;
        c0 = 0;
        if (r[2] <= view->nearZ && cube[D_main_8009FCB0[i][1]][2] <= view->nearZ) {
            continue;
        }
        if (r[0] < -r[2]) {
            c0 = 1;
        }
        if (r[2] < r[0]) {
            c0 |= 2;
        }
        if (r[1] < -r[2]) {
            c0 |= 4;
        }
        if (r[2] < r[1]) {
            c0 |= 8;
        }
        q = cube[D_main_8009FCB0[i][1]];
        if (q[0] < -q[2]) {
            c1 = 1;
        }
        if (q[2] < q[0]) {
            c1 |= 2;
        }
        if (q[1] < -q[2]) {
            c1 |= 4;
        }
        if (q[2] < q[1]) {
            c1 |= 8;
        }
        if (!(c0 & c1)) {
            return 1;
        }
    }
    return 0;
}

extern void evalCubicSplineAtTime(void *, s32, f32 *);

void applyDatItemWorldOffset(void *spline, f32 *offset, f32 *out) {
    evalCubicSplineAtTime(spline, 0, out);
    out[0] += offset[0];
    out[1] += offset[1];
    out[2] += offset[2];
}

extern void buildPositionAndCallTransformHelper(void *, void *, void *, void *, f32, f32, f32);

void setupActorAnchorTransformType1(void *arg0, void *arg1, void *arg2, void *arg3, f32 arg4) {
    buildPositionAndCallTransformHelper(arg0, arg1, arg2, arg3, 1.0f, 1.0f, arg4);
    *(s32 *)((u8 *)arg3 + 8) = 0;
}

f32 quadraticEaseInOut(f32 arg0) {
    f32 temp_fv1;

    if (arg0 < 0.0f) {
        arg0 = 0.0f;
    } else if (arg0 > 1.0f) {
        arg0 = 1.0f;
    }
    if (!(arg0 <= 0.5f)) {
        temp_fv1 = 1.0f - arg0;
        return 1.0f - (2.0f * temp_fv1 * temp_fv1);
    } else {
        return 2.0f * arg0 * arg0;
    }
}

void lerpVec3(Vec3f arg0, Vec3f arg1, Vec3f arg2, f32 arg3) {
    arg0[0] = (arg1[0] * (1.0f - arg3)) + (arg2[0] * arg3);
    arg0[1] = (arg1[1] * (1.0f - arg3)) + (arg2[1] * arg3);
    arg0[2] = (arg1[2] * (1.0f - arg3)) + (arg2[2] * arg3);
}

// DO NOT DELTE ME I'M REQUIRED FOR MATCHING
static const u32 rodata_padding[] = {
    0xAFA2001C,
    0x0C011409,
    0xA02000C0,
};

INCLUDE_ASM("asm/nonmatchings/main/66660", fake_func_800663AC);
