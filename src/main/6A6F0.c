#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/6A6F0", collideSegmentAgainstObjectNodes);

INCLUDE_ASM("asm/nonmatchings/main/6A6F0", findSegmentObjectSphereHit);

static __inline__ f32 ppSqrt(f32 x) { f32 r; __asm__ volatile("sqrt.s %0, %1" : "=f"(r) : "f"(x)); return r; }
f32 *intersectSegmentWithObjectSphere(void *, void *, f32 *, f32 *);

f32 projectPointOntoObjectSphereHit(u8 **obj, f32 *p, f32 *d) {
    f32 *s;
    f32 dx, dy, dz;
    f32 b2, b, aa, r, dd, t, q;
    register f32 len asm("$f0");

    s = intersectSegmentWithObjectSphere(obj, *obj + 0x48, p, d);
    if (s == NULL) {
        r = -1.0f;
    } else {
        dx = s[0] - p[0];
        dy = s[1] - p[1];
        dz = s[2] - p[2];
        b = dx * d[0] + dy * d[1] + dz * d[2];
        dd = dx * dx + dy * dy + dz * dz;
        aa = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
        b2 = b * b;
        dd = s[3] - dd + b2 / aa;
        len = ppSqrt(aa);
        q = ppSqrt(dd);
        b = b / len - q;
        r = b / len;
    }
    return r;
}

void transformVec3ByMat34(void *, void *, void *);
void transformMeshPartIntoWorld(unsigned char **arg0, void *arg1) {
    transformVec3ByMat34((unsigned char *)arg0 + 0x28, *arg0 + 0x4C, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main/6A6F0", fake_func_8006ACA4);

static u32 D_main_8003C8FC[] __attribute__((section(".rodata"))) = { 0x46327180 };
