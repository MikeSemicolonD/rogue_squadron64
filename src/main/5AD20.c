#include "common.h"

#include "hob.h"

#include "main/5AD20.h"

struct vertex D_main_8009ECC0[] = {
    {0xFF80, 0x0000, 0xFF80, 0x0000},
    {0x0080, 0x0000, 0xFF80, 0x0000},
    {0x0080, 0x0000, 0x0080, 0x0000},
    {0xFF80, 0x0000, 0x0080, 0x0000},
};

f32 D_main_8009ECE0[] = {
    5.0f,
    -5.0f,
    21.0f,
    -21.0f,
};

INCLUDE_ASM("asm/nonmatchings/main/5AD20", loadTopCloudsAsset);

INCLUDE_ASM("asm/nonmatchings/main/5AD20", updateWalkerParticlePositions);

INCLUDE_RODATA("asm/nonmatchings/main/5AD20", D_main_8003AE10);

INCLUDE_ASM("asm/nonmatchings/main/5AD20", loadSkyHorizonHob);

f32 atan2Approx(f32, f32);
void linkDirectionalTrailSegments(f32 *arg0, u8 *arg1) {
    u8 *base = arg1 + 0x1C;
    s32 lo;
    s32 hi;
    s32 i;
    s32 t;
    u8 *n;
    u8 *m;

    f32 ab;
    __asm__ volatile("abs.s %0, %1" : "=f"(ab) : "f"(arg0[4]));
    if (0.7f < ab) {
        lo = 0;
        hi = 7;
    } else {
        t = (s32)(atan2Approx(arg0[3], arg0[5]) / 0.7853982f) & 7;
        lo = t - 2;
        hi = t + 2;
    }
    i = lo;
    if (hi >= lo) {
        do {
            n = (u8 *)((i & 7) * 0x5C + (s32)base);
            if (i != lo) {
                *(u8 **)(n + 4) = base + (((i - 1) & 7) * 0x5C + 0x2E0);
            } else {
                *(u8 **)(n + 4) = 0;
            }
            m = (u8 *)((i & 7) * 0x5C + (s32)base);
            *(u8 **)m = base + ((i & 7) * 0x5C + 0x2E0);
            *(u8 **)(m + 0x2E4) = m;
            if (i != hi) {
                *(u8 **)(m + 0x2E0) = base + ((i + 1) & 7) * 0x5C;
            } else {
                *(u8 **)(m + 0x2E0) = 0;
            }
            i++;
        } while (hi >= i);
    }
    *(u8 **)(*(u8 **)(arg1 + 0x18) + 0x1C) = arg1 + ((lo & 7) * 0x5C + 0x1C);
}

INCLUDE_ASM("asm/nonmatchings/main/5AD20", setupWalkerSpriteTileQuad);

INCLUDE_ASM("asm/nonmatchings/main/5AD20", cinematicSplineWalkerNpcHandler);

extern s16 D_main_bss_80139560[];

s16 allocateNpcSlot(void *);

void allocAllInitialNpcSlots(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        D_main_bss_80139560[i] = allocateNpcSlot(NULL);
    }
}

INCLUDE_ASM("asm/nonmatchings/main/5AD20", fake_func_8005C61C);
