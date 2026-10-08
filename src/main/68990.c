#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main/68990", wrapAngleToCyclicRange);

INCLUDE_ASM("asm/nonmatchings/main/68990", sampleTerrainSurfaceAtWorldXz);

INCLUDE_ASM("asm/nonmatchings/main/68990", sampleHmpTileHeightBicubic);

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
