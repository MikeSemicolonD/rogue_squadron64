#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/5FA70", steerOrientationTowardTarget);

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

INCLUDE_RODATA("asm/nonmatchings/main/5FA70", D_main_8003B248);

INCLUDE_ASM("asm/nonmatchings/main/5FA70", emitTrailPuffAndCue);

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

INCLUDE_RODATA("asm/nonmatchings/main/5FA70", D_main_8003B2F4);
