#include "common.h"

#include "main/66660.h"

INCLUDE_ASM("asm/nonmatchings/main/66660", buildPositionAndCallTransformHelper);

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
