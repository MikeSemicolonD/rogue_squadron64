#include "common.h"

#include "common_types.h"
#include "rs_math.h"
typedef struct {
    u16 *grid;
    u8 *cells;
    u8 pad8[8];
    f32 scale;
    u8 pad14[4];
    f32 baseY;
    u8 pad1C[4];
    f32 x0;
    f32 x1;
    u8 pad28[4];
    f32 z0;
    f32 z1;
    u8 pad34[4];
    u16 w;
    u16 h;
} TerrainGridWA;
typedef struct { u8 pad[5]; s8 h[5][5]; } TerrainCellWA;
typedef struct { f32 x; f32 y; f32 z; f32 nx; f32 ny; f32 nz; } TerrainHitWA;
extern TerrainGridWA gGridWA __asm__("D_main_bss_80136DC0");

f32 wrapAngleToCyclicRange(f32 x, f32 z, void *unused, TerrainHitWA *out) {
    f32 fx;
    f32 fz;
    s32 ix;
    s32 iz;
    s32 tx;
    s32 tz;
    s32 sx;
    s32 sz;
    TerrainCellWA *cell;
    s32 a;
    s32 db;
    s32 dc;
    f32 scale;
    f32 y;
    f32 len;
    f32 sq;
    f32 d;

    fx = x - gGridWA.x0;
    if (fx < 0.0f) {
        fx = (fx - 2.0f * (f32)(s32)(fx * 0.5f)) + 2.0f;
    } else if (gGridWA.x1 <= fx) {
        fx -= 2.0f * (f32)(s32)(fx * 0.5f);
    }
    fx = 2.0f * fx;
    ix = fx;
    fx -= (f32)ix;
    sx = ix / 4;
    tx = sx;
    sx = ix - tx * 4;
    ix = tx;
    fz = z - gGridWA.z0;
    if (fz < 0.0f) {
        fz = (fz - 2.0f * (f32)(s32)(fz * 0.5f)) + 2.0f;
    } else if (gGridWA.z1 <= fz) {
        fz -= 2.0f * (f32)(s32)(fz * 0.5f);
    }
    fz = 2.0f * fz;
    iz = fz;
    fz -= (f32)iz;
    sz = iz / 4;
    tz = sz;
    sz = iz - tz * 4;
    __asm__("" : : : "$5");
    iz = tz;
    if (ix < 0 || ix >= gGridWA.w || iz < 0 || iz >= gGridWA.h) {
        if (out != NULL) {
            out->x = x;
            out->y = 0.0f;
            out->z = z;
            out->nx = 0.0f;
            out->nz = 0.0f;
            out->ny = 1.0f;
        }
        return 0.0f;
    }
    scale = gGridWA.scale * 0.00390625f;
    d = fx - fz;
    cell = (TerrainCellWA *)(gGridWA.cells + (gGridWA.grid[ix + iz * gGridWA.w] & 0x1FFF) * 0x1E);
    if (d >= 0.0f) {
        __asm__("" : : "r"(cell));
        a = cell->h[sz][sx + 1];
        db = cell->h[sz][sx] - a;
        dc = cell->h[sz + 1][sx + 1] - a;
        y = (1.0f - fx) * (f32)db;
        y += fz * (f32)dc;
        __asm__("" : "+r"(dc) : : "$2", "$3");
        __asm__("" : : "r"(db));
        y += (f32)a;
        if (out != NULL) {
            out->ny = 1.0f;
            out->nx = (f32)db * scale;
            out->nz = (f32)-dc * scale;
        }
    } else {
        a = cell->h[sz + 1][sx];
        db = cell->h[sz + 1][sx + 1] - a;
        y = fx * (f32)db;
        dc = cell->h[sz][sx] - a;
        y += (1.0f - fz) * (f32)dc;
        y += (f32)a;
        if (out != NULL) {
            out->ny = 1.0f;
            out->nx = (f32)-db * scale;
            out->nz = (f32)dc * scale;
        }
    }
    y *= scale;
    y += gGridWA.baseY;
    if (out != NULL) {
        sq = out->nx * out->nx + 1.0f + out->nz * out->nz;
        SQRTF(scale, sq);
        out->nx /= scale;
        out->x = x;
        out->y = y;
        out->z = z;
        out->ny /= scale;
        out->nz /= scale;
    }
    return y;
}

INCLUDE_ASM("asm/nonmatchings/main/68990", sampleTerrainSurfaceAtWorldXz);

#include "common_types.h"
typedef struct { u8 pad[5]; s8 h[25]; } HbGrid;

f32 sampleHmpTileHeightBicubic(f32 x0, f32 y0, f32 z0, f32 dx, f32 dy, f32 dz, HbGrid *g) {
    s32 i;
    s32 j;
    f32 best;
    f32 t;
    f32 num;
    f32 den;
    f32 r;
    s32 a;
    s32 e1;
    s32 e2;
    s32 e3, e4, b;
    s32 r0, r1, r5, r6;

    if (x0 + dx < -0.001f) {
        x0 += 4.0f;
    }
    if (z0 + dz < -0.001f) {
        z0 += 4.0f;
    }
    best = 1.0f;
    for (j = 0; j < 4; j++) {
        t = ((f32)j + 1.0f) - z0;
        r5 = j * 5 + 5;
        r6 = j * 5 + 6;
        r0 = j * 5;
        r1 = j * 5 + 1;
        for (i = 0; i < 4; i++) {
            a = g->h[i + r6];
            e1 = g->h[i + r1];
            {
                register HbGrid *p asm("$3") = (HbGrid *)((s32)g + (i + r5));
                e2 = p->h[0];
            }
            e1 -= a;
            e2 -= a;
            den = e1;
            num = (((f32)i + 1.0f) - x0) * e2 + ((f32)a - y0) + t * den;
            den = e2 * dx + dy + den * dz;
            if (0.0f <= num && num < den) {
                r = num / den;
                if (r < best) {
                    if ((s32)(x0 + dx * r) == i && (s32)(z0 + dz * r) == j) {
                        best = r;
                    }
                }
            }
            b = g->h[i + r0];
            e3 = b - g->h[i + r1];
            e4 = b - g->h[i + r5];
            den = e4;
            num = ((f32)i - x0) * e3 + ((f32)b - y0) + ((f32)j - z0) * den;
            den = e3 * dx + dy + den * dz;
            if (0.0f <= num && num < den) {
                r = num / den;
                if (r < best) {
                    if ((s32)(x0 + dx * r) == i && (s32)(z0 + dz * r) == j) {
                        best = r;
                    }
                }
            }
        }
    }
    return best;
}

INCLUDE_ASM("asm/nonmatchings/main/68990", sampleTerrainAtNpcPosition);

#include "common_types.h"

typedef struct {
    u16 *grid;
    u8 *cells;
    u8 pad8[0x18];
    f32 x0;
    f32 x1;
    u8 pad28[4];
    f32 z0;
    f32 z1;
    u8 pad34[4];
    u16 stride;
} TerrainGridInfo;

extern TerrainGridInfo D_main_bss_80136DC0;
extern s32 D_main_bss_801375C0;

s32 isTerrainCellBlockedAtWorldXz(f32 x, f32 z) {
    s32 ix;
    s32 iz;
    s32 tx;
    s32 tz;
    s32 fx;
    s32 fz;
    u8 *cell;
    u8 flags;

    x -= D_main_bss_80136DC0.x0;
    if (x < 0.0f) {
        x = (x - 2.0f * (f32)(s32)(x * 0.5f)) + 2.0f;
    } else if (D_main_bss_80136DC0.x1 <= x) {
        x -= 2.0f * (f32)(s32)(x * 0.5f);
    }
    x = 2.0f * x;
    ix = x;
    fx = ix / 4;
    tx = fx;
    fx = ix - tx * 4;
    ix = tx;
    z -= D_main_bss_80136DC0.z0;
    if (z < 0.0f) {
        z = (z - 2.0f * (f32)(s32)(z * 0.5f)) + 2.0f;
    } else if (D_main_bss_80136DC0.z1 <= z) {
        z -= 2.0f * (f32)(s32)(z * 0.5f);
    }
    z = 2.0f * z;
    iz = z;
    fz = iz / 4;
    tz = fz;
    fz = iz - tz * 4;
    cell = D_main_bss_80136DC0.cells + (D_main_bss_80136DC0.grid[ix + tz * D_main_bss_80136DC0.stride] & 0x1FFF) * 0x1E;
    flags = cell[2];
    if ((flags & 8) || ((flags & 0x10) && (((s8 *)(cell + (fx + ((fz << 2) + fz))))[5] >= D_main_bss_801375C0))) {
        return 1;
    }
    return 0;
}


INCLUDE_ASM("asm/nonmatchings/main/68990", fake_func_80069AEC);

__asm__(".section .rodata\n.word 0x46003006\n.word 0x46000007\n.section .text");
