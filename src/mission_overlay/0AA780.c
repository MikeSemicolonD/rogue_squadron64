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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AA780", stepAngleTowardTarget);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AA780", buildTransformMatrixFromEulerAngles);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AA780", fake_func_800AA6CC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AA780", D_mission_overlay_800A51D8);
