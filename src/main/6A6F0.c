#include "common.h"
#include "common_types.h"
#include "rs_math.h"

INCLUDE_ASM("asm/nonmatchings/main/6A6F0", collideSegmentAgainstObjectNodes);

f32 *intersectSegmentWithObjectSphere(void *, void *, f32 *, f32 *);
s32 collideSegmentAgainstObjectNodes(void *, f32 *, f32 *, f32 *);
f32 normalize_vector(void *);

s32 findSegmentObjectSphereHit(u8 **obj, f32 *p, f32 *d, f32 *out) {
    f32 *s;
    f32 dx, dy, dz;
    f32 b2, b, aa, r, dd, t, q;
    f32 len;

    s = intersectSegmentWithObjectSphere(obj, *obj + 0x48, p, d);
    if (s != NULL) {
        if (*(s32 *)(*obj + 0x58) == 0) {
            if (out != NULL) {
                dx = s[0] - p[0];
                dy = s[1] - p[1];
                dz = s[2] - p[2];
                b = dx * d[0] + dy * d[1] + dz * d[2];
                dd = dx * dx + dy * dy + dz * dz;
                aa = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
                b2 = b * b;
                dd = s[3] - dd + b2 / aa;
                len = sqrtfInline(aa);
                q = sqrtfInline(dd);
                b = b / len - q;
                out[6] = b / len;
                out[0] = p[0] + d[0] * out[6];
                out[1] = p[1] + d[1] * out[6];
                out[2] = p[2] + d[2] * out[6];
                out[3] = s[0] - out[0];
                out[4] = s[1] - out[1];
                out[5] = s[2] - out[2];
                normalize_vector(&out[3]);
                out[7] = sqrtfInline((d[0] * d[0] + d[1] * d[1] + d[2] * d[2]) * out[6] * out[6]);
                t = sqrtfInline(s[3]);
                out[8] = s[3] * 4.1887903f * t;
                ((s32 *)out)[9] = 0;
            }
            return 1;
        }
        if (collideSegmentAgainstObjectNodes(obj, p, d, out) != 0) {
            return 1;
        }
    }
    return 0;
}

f32 *intersectSegmentWithObjectSphere(void *, void *, f32 *, f32 *);

f32 projectPointOntoObjectSphereHit(u8 **obj, f32 *p, f32 *d) {
    f32 *s;
    f32 dx, dy, dz;
    f32 b2, b, aa, dd, t, q;
    f32 len;

    s = intersectSegmentWithObjectSphere(obj, *obj + 0x48, p, d);
    if (s != NULL) {
        dx = s[0] - p[0];
        dy = s[1] - p[1];
        dz = s[2] - p[2];
        b = dx * d[0] + dy * d[1] + dz * d[2];
        dd = dx * dx + dy * dy + dz * dz;
        aa = d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
        b2 = b * b;
        dd = s[3] - dd + b2 / aa;
        len = sqrtfInline(aa);
        q = sqrtfInline(dd);
        b = b / len - q;
        return b / len;
    }
    return -1.0f;
}

void transformVec3ByMat34(void *, void *, void *);
void transformMeshPartIntoWorld(unsigned char **arg0, void *arg1) {
    transformVec3ByMat34((unsigned char *)arg0 + 0x28, *arg0 + 0x4C, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main/6A6F0", fake_func_8006ACA4);

static u32 D_main_8003C8FC[] __attribute__((section(".rodata"))) = { 0x46327180 };
