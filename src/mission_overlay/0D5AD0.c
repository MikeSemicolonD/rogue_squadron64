#include "common.h"

#include "common_types.h"
INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D5AD0", npcInitChildLinkedToParent);

typedef struct {
    f32 x, y, z;
} SpinVec3;

void quatFromCardinalAxis(f32 *, u8, f32);
void quatMultiply(f32 *, f32 *, f32 *);
void rotateVec3ByQuat(f32 *, f32 *, f32 *);
f32 sinf(f32);

void advanceNpcSpinOrientation(u8 *arg0, f32 arg1) {
    f32 q1[4];
    f32 q2[4];
    f32 q3[4];
    SpinVec3 out;

    *(f32 *)(arg0 + 0x58) = *(f32 *)(arg0 + 0x58) + arg1 * *(f32 *)(arg0 + 0x60);
    if (*(f32 *)(arg0 + 0x58) > 1.0f) {
        *(f32 *)(arg0 + 0x58) = *(f32 *)(arg0 + 0x58) - 2.0f;
    }
    *(f32 *)(arg0 + 0x5C) = *(f32 *)(arg0 + 0x5C) + arg1 * *(f32 *)(arg0 + 0x60);
    if (*(f32 *)(arg0 + 0x5C) > 1.0f) {
        *(f32 *)(arg0 + 0x5C) = *(f32 *)(arg0 + 0x5C) - 2.0f;
    }
    *(f32 *)(arg0 + 0x68) = *(f32 *)(arg0 + 0x68) + arg1 * 0.5f;
    if (*(f32 *)(arg0 + 0x68) > 1.0f) {
        *(f32 *)(arg0 + 0x68) = 1.0f;
    }
    quatFromCardinalAxis(q1, 0, sinf(*(f32 *)(arg0 + 0x58) * 3.1415927f) * *(f32 *)(arg0 + 0x68));
    quatFromCardinalAxis(q2, 2, sinf(*(f32 *)(arg0 + 0x5C) * 3.1415927f) * *(f32 *)(arg0 + 0x68));
    quatMultiply(q2, q1, q3);
    rotateVec3ByQuat(q3, (f32 *)(arg0 + 0x6C), (f32 *)&out);
    *(SpinVec3 *)(arg0 + 0xC) = out;
    rotateVec3ByQuat(q3, (f32 *)(arg0 + 0x78), (f32 *)&out);
    *(SpinVec3 *)(arg0 + 0x18) = out;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D5AD0", D_mission_overlay_800A760C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D5AD0", npcDebrisFieldUpdate);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D5AD0", D_mission_overlay_800A7680);
