#include "common.h"

#include "main/080E0.h"

// Hand-written in assembly: packs the 32-bit halves and divides with no zero check.
__asm__(
    ".set push\n"
    ".set noreorder\n"
    ".globl u64DivU64\n"
    ".type u64DivU64, @function\n"
    ".ent u64DivU64\n"
    "u64DivU64:\n"
    "    dsll32 $2, $4, 0\n"
    "    dsll32 $3, $5, 0\n"
    "    dsrl32 $3, $3, 0\n"
    "    or $2, $2, $3\n"
    "    dsll32 $3, $6, 0\n"
    "    dsll32 $8, $7, 0\n"
    "    dsrl32 $8, $8, 0\n"
    "    or $3, $3, $8\n"
    "    ddivu $0, $2, $3\n"
    "    mflo $3\n"
    "    jr $31\n"
    "    dsrl32 $2, $3, 0\n"
    ".end u64DivU64\n"
    ".size u64DivU64, . - u64DivU64\n"
    ".set pop\n"
);

// Hand-written in assembly; no GCC 2.7.2/2.8.1 output uses $f4 here.
__asm__(
    ".set push\n"
    ".set noreorder\n"
    ".globl floatToInt\n"
    ".type floatToInt, @function\n"
    ".ent floatToInt\n"
    "floatToInt:\n"
    "    trunc.w.s $f4, $f12\n"
    "    jr $31\n"
    "    mfc1 $2, $f4\n"
    ".end floatToInt\n"
    ".size floatToInt, . - floatToInt\n"
    ".set pop\n"
);

INCLUDE_ASM("asm/nonmatchings/main/080E0", fake_func_8000751C);
