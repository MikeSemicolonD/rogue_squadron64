#include "common.h"

#include "main/66660.h"

#define VABS(x) ({ f32 _x = (x); f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(_x)); _r; })
#define ABSF(x) ({ f32 _r = (x); __asm__ volatile("abs.s %0, %0" : "+f"(_r)); _r; })
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} V3;
extern void evalCubicSplineAtTimeF(void *, f32, V3 *) __asm__("evalCubicSplineAtTime");
f32 sinfApprox(f32);
void buildRotationMatrixSlot1(Mat4x3, f32);
void normalize_vector(Vec3f);
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
        rot[1] = ABSF(sinfApprox(-n.x) * 57.29578f) - 180.0f;
    } else if (n.x >= 0.0f && n.z < 0.0f) {
        rot[1] = -ABSF(sinfApprox(n.x) * 57.29578f) - 180.0f;
    } else if (n.x < 0.0f && n.z >= 0.0f) {
        rot[1] = -ABSF(sinfApprox(-n.x) * 57.29578f);
    } else {
        rot[1] = VABS(sinfApprox(n.x) * 57.29578f);
    }
    buildRotationMatrixSlot1((f32 *)m, -rot[1]);
    transformVec3ByMat34((f32 *)m, (f32 *)&d, (f32 *)&n);
    n.x = 0.0f;
    normalize_vector((f32 *)&n);
    if (n.y < 0.0f && n.z < 0.0f) {
        rot[0] = ABSF(sinfApprox(-n.z) * 57.29578f) - 270.0f;
    } else if (n.y >= 0.0f && n.z < 0.0f) {
        rot[0] = -ABSF(sinfApprox(-n.z) * 57.29578f) - 90.0f;
    } else if (n.y < 0.0f && n.z >= 0.0f) {
        rot[0] = -ABSF(sinfApprox(n.z) * 57.29578f) - 270.0f;
    } else {
        rot[0] = ABSF(sinfApprox(n.z) * 57.29578f) - 90.0f;
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

INCLUDE_ASM("asm/nonmatchings/main/66660", projectModelBoundsToScreen);

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
