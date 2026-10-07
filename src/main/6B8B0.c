#include "common.h"
#include "common_types.h"
#include "common_variables.h"

#include "crafts.h"
#include "levels.h"
#include "game_settings.h"

#include "main/6B8B0.h"

struct D_main_800A05D0_type D_main_800A05D0[] = {
    {0x00000000,
    0x01D6,
    0x0226,
    0x0064,
    0x0000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0.0f,
    2.0f,
    {0xCE, 0xC0, 0xA4, 0xFF},
    {0xC8, 0xC0, 0xA0, 0xFF},
    0x0008,
    0x0000},

    {0x00000000,
    0x01C2,
    0x0230,
    0x0040,
    0x0000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    1.0f,
    2.0f,
    {0x82, 0xB6, 0xD3, 0xFF},
    {0x80, 0xB8, 0xD0, 0xFF},
    0x0008,
    0x0000},

    {0x00000001,
    0x01C7,
    0x01B8,
    0x0040,
    0x0000,
    0x01000000,
    0x01000000,
    0x00000000,
    0x00000000,
    -2.0f,
    2.0f,
    {0x78, 0x80, 0x60, 0xFF},
    {0x78, 0x80, 0x60, 0xFF},
    0x0008,
    0x0000},

    {0x000000C1,
    0x01EF,
    0x01C0,
    0x0040,
    0x0000,
    0x01000000,
    0x01000000,
    0x00000000,
    0x01000000,
    0.0f,
    3.0f,
    {0x0D, 0x0F, 0x13, 0xFF},
    {0x10, 0x10, 0x10, 0xFF},
    0x0008,
    0x0000},

    {0x00000001,
    0x0190,
    0x01CC,
    0x0040,
    0x0000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0.0f,
    2.0f,
    {0x9D, 0x6B, 0x63, 0xFF},
    {0xA0, 0x68, 0x60, 0xFF},
    0x0008,
    0x0000},

    {0x00000000,
    0x01D6,
    0x01F4,
    0x0040,
    0x0000,
    0x00000000,
    0x00000000,
    0x00400000,
    0x00400000,
    4.0f,
    2.0f,
    {0x08, 0x08, 0x08, 0xFF},
    {0x08, 0x08, 0x08, 0xFF},
    0x0008,
    0x0000},

    {0x00000019,
    0x01EA,
    0x01E0,
    0x0038,
    0x0000,
    0x01000000,
    0x01000000,
    0x00000000,
    0x00000000,
    0.0f,
    1.5f,
    {0xA8, 0x98, 0x80, 0xFF},
    {0xA8, 0x98, 0x80, 0xFF},
    0x0000,
    0x0000},

    {0x00000001,
    0x01A9,
    0x01C2,
    0x0040,
    0x0000,
    0x00400000,
    0x00400000,
    0x00000000,
    0x00000000,
    0.0f,
    1.5f,
    {0x4A, 0x59, 0x72, 0xFF},
    {0x48, 0x58, 0x70, 0xFF},
    0x0008,
    0x0000},

    {0x00000001,
    0x01F4,
    0x0208,
    0x0040,
    0x0000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0.0f,
    2.0f,
    {0x88, 0x30, 0x08, 0xFF},
    {0x88, 0x30, 0x08, 0xFF},
    0x0008,
    0x0000},

    {0x00000019,
    0x01C7,
    0x01CC,
    0x0038,
    0x0000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0.0f,
    1.2f,
    {0x88, 0x30, 0x08, 0xFF},
    {0x88, 0x30, 0x08, 0xFF},
    0x0008,
    0x0000},

    {0x00000000,
    0x0212,
    0x0226,
    0x0080,
    0x0000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0.0f,
    1.0f,
    {0xB3, 0x8A, 0x5C, 0xFF},
    {0xB0, 0x88, 0x58, 0xFF},
    0x0008,
    0x0000},

    {0x00000001,
    0x01C2,
    0x01DB,
    0x0040,
    0x0000,
    0x01000000,
    0x01000000,
    0x00000000,
    0x00000000,
    0.0f,
    1.8f,
    {0x60, 0x60, 0x68, 0xFF},
    {0x60, 0x60, 0x68, 0xFF},
    0x0008,
    0x0000},

    {0x00000001,
    0x01E0,
    0x01C2,
    0x0040,
    0x0000,
    0x01000000,
    0x01000000,
    0x00000000,
    0x00000000,
    0.0f,
    2.0f,
    {0x8F, 0xAF, 0xA5, 0xFF},
    {0x90, 0xB0, 0xA8, 0xFF},
    0x0008,
    0x0000},

    {0x00000099,
    0x01E5,
    0x01E0,
    0x0038,
    0x0000,
    0x00400000,
    0x00400000,
    0x01000000,
    0x01000000,
    0.0f,
    1.0f,
    {0x10, 0x08, 0x08, 0xFF},
    {0x10, 0x08, 0x08, 0xFF},
    0x0008,
    0x0000},

    {0x00000001,
    0x01C2,
    0x01E0,
    0x0040,
    0x0000,
    0x00400000,
    0x00400000,
    0x00000000,
    0x00000000,
    0.0f,
    2.0f,
    {0xC6, 0xCD, 0xD3, 0xFF},
    {0xC8, 0xD0, 0xD0, 0xFF},
    0x0008,
    0x0000},

    {0x00000081,
    0x01D6,
    0x0190,
    0x0040,
    0x0000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    4.0f,
    3.0f,
    {0xAB, 0xE2, 0xF9, 0xFF},
    {0xA8, 0xE0, 0xF8, 0xFF},
    0x0008,
    0x0000},

    {0x00000000,
    0x015E,
    0x01F4,
    0x0080,
    0x0000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0.0f,
    2.0f,
    {0xCE, 0xC0, 0xA4, 0xFF},
    {0xC8, 0xC0, 0xA0, 0xFF},
    0x0008,
    0x0000},

    {0x00000000,
    0x0190,
    0x01CC,
    0x0040,
    0x0000,
    0x00000000,
    0x00000000,
    0x00400000,
    0x00400000,
    10.0f,
    3.0f,
    {0x08, 0x08, 0x08, 0xFF},
    {0x08, 0x08, 0x08, 0xFF},
    0x0008,
    0x0000},

    {0x00000001,
    0x01E0,
    0x01F4,
    0x0040,
    0x0000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0.0f,
    2.0f,
    {0xD1, 0xE7, 0xF5, 0xFF},
    {0xD0, 0xE0, 0xF0, 0xFF},
    0x0008,
    0x0000},

    {0x00000000,
    0x0226,
    0x0258,
    0x0040,
    0x0000,
    0x00400000,
    0x00400000,
    0x00000000,
    0x00000000,
    0.0f,
    1.0f,
    {0xDB, 0xDD, 0xF1, 0xFF},
    {0xD8, 0xE0, 0xF0, 0xFF},
    0x0008,
    0x0000},

    {0x00000000,
    0x0190,
    0x01C2,
    0x0040,
    0x0000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    1.0f,
    1.0f,
    {0x82, 0xB6, 0xD3, 0xFF},
    {0x80, 0xB8, 0xD0, 0xFF},
    0x0008,
    0x0000},
};

// Hand-written assembly.
__asm__(
    ".section .text\n.set push\n.set noat\n.set noreorder\n"
    "glabel transformObjectColliderCenter\n"
    "    lbu        $t0, 0xB($a0)\n"
    "    lui        $v0, (0x80139C80 >> 16)\n"
    "    ori        $v0, $v0, (0x80139C80 & 0xFFFF)\n"
    "    beqz       $t0, .Lmain_8006ACCC\n"
    "    sll       $t0, $t0, 4\n"
    "    jr         $ra\n"
    "    addu      $v0, $v0, $t0\n"
    "  .Lmain_8006ACCC:\n"
    "    lui        $t1, (0x8013A490 >> 16)\n"
    "    ori        $t1, $t1, (0x8013A490 & 0xFFFF)\n"
    "    lh         $t0, 0x0($t1)\n"
    "    lui        $t2, (0x8013A498 >> 16)\n"
    "    ori        $t2, $t2, (0x8013A498 & 0xFFFF)\n"
    "    bltz       $t0, .Lmain_8006AE3C\n"
    "    addu      $t2, $t2, $t0\n"
    "    lbu        $at, 0x0($t2)\n"
    "    addiu      $t0, $t0, -0x1\n"
    "    sh         $t0, 0x0($t1)\n"
    "    sb         $at, 0xB($a0)\n"
    "    sll        $t0, $at, 4\n"
    "    addu       $v0, $v0, $t0\n"
    "  .Lmain_8006AD00:\n"
    "    mfc1       $t4, $fs0\n"
    "    mfc1       $t5, $fs1\n"
    "    mfc1       $t6, $fs2\n"
    "    mfc1       $t7, $fs3\n"
    "    lwc1       $ft0, 0x4($a1)\n"
    "    lwc1       $ft3, 0x28($a0)\n"
    "    lwc1       $ft4, 0x34($a0)\n"
    "    lwc1       $ft5, 0x40($a0)\n"
    "    mul.s      $fs0, $ft3, $ft0\n"
    "    lwc1       $ft3, 0x2C($a0)\n"
    "    mul.s      $fs1, $ft4, $ft0\n"
    "    lwc1       $ft4, 0x38($a0)\n"
    "    mul.s      $fs2, $ft5, $ft0\n"
    "    lwc1       $ft0, 0x8($a1)\n"
    "    lwc1       $ft5, 0x44($a0)\n"
    "    mul.s      $ft1, $ft3, $ft0\n"
    "    nop\n"
    "    mul.s      $ft2, $ft4, $ft0\n"
    "    add.s      $fs0, $fs0, $ft1\n"
    "    add.s      $fs1, $fs1, $ft2\n"
    "    mul.s      $ft1, $ft5, $ft0\n"
    "    nop\n"
    "    add.s      $fs2, $fs2, $ft1\n"
    "    lwc1       $ft3, 0x30($a0)\n"
    "    lwc1       $ft4, 0x3C($a0)\n"
    "    lwc1       $ft0, 0xC($a1)\n"
    "    lwc1       $ft5, 0x48($a0)\n"
    "    mul.s      $ft1, $ft3, $ft0\n"
    "    lwc1       $ft3, 0x4C($a0)\n"
    "    mul.s      $ft2, $ft4, $ft0\n"
    "    add.s      $fs0, $fs0, $ft1\n"
    "    add.s      $fs1, $fs1, $ft2\n"
    "    mul.s      $ft1, $ft5, $ft0\n"
    "    lwc1       $ft4, 0x50($a0)\n"
    "    add.s      $fs2, $fs2, $ft1\n"
    "    lwc1       $ft5, 0x54($a0)\n"
    "    add.s      $fs0, $fs0, $ft3\n"
    "    add.s      $fs1, $fs1, $ft4\n"
    "    add.s      $fs2, $fs2, $ft5\n"
    "    swc1       $fs0, 0x0($v0)\n"
    "    swc1       $fs1, 0x4($v0)\n"
    "    swc1       $fs2, 0x8($v0)\n"
    "    lhu        $t0, 0x8($a0)\n"
    "    lwc1       $ft3, 0x0($a1)\n"
    "    andi       $at, $t0, 0x400\n"
    "    beqz       $at, .Lmain_8006ADC8\n"
    "    addiu     $t1, $a0, 0x28\n"
    "    addiu      $t1, $t1, 0x4\n"
    "    j          .Lmain_8006ADD8\n"
    "    andi      $at, $t0, 0x40\n"
    "  .Lmain_8006ADC8:\n"
    "    andi       $at, $t0, 0x800\n"
    "    beqz       $at, .Lmain_8006ADD8\n"
    "    andi      $at, $t0, 0x40\n"
    "    addiu      $t1, $t1, 0x8\n"
    "  .Lmain_8006ADD8:\n"
    "    beqz       $at, .Lmain_8006ADF8\n"
    "    lwc1      $ft0, 0x0($t1)\n"
    "    ori        $t0, $zero, 0x4\n"
    "    mtc1       $t0, $ft4\n"
    "    nop\n"
    "    cvt.s.w    $ft4, $ft4\n"
    "    mul.s      $ft3, $ft3, $ft4\n"
    "    nop\n"
    "  .Lmain_8006ADF8:\n"
    "    lwc1       $ft1, 0xC($t1)\n"
    "    mul.s      $ft0, $ft0, $ft0\n"
    "    lwc1       $ft2, 0x18($t1)\n"
    "    mul.s      $ft1, $ft1, $ft1\n"
    "    nop\n"
    "    mul.s      $ft2, $ft2, $ft2\n"
    "    add.s      $ft0, $ft0, $ft1\n"
    "    add.s      $ft0, $ft0, $ft2\n"
    "    mul.s      $ft3, $ft3, $ft0\n"
    "    nop\n"
    "    swc1       $ft3, 0xC($v0)\n"
    "    mtc1       $t4, $fs0\n"
    "    mtc1       $t5, $fs1\n"
    "    mtc1       $t6, $fs2\n"
    "    mtc1       $t7, $fs3\n"
    "    jr         $ra\n"
    "    nop\n"
    "  .Lmain_8006AE3C:\n"
    "    lui        $v0, (0x8006AE48 >> 16)\n"
    "    j          .Lmain_8006AD00\n"
    "    ori       $v0, $v0, (0x8006AE48 & 0xFFFF)\n"
    "endlabel transformObjectColliderCenter\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    ".set pop\n"
);

// Hand-written assembly.
__asm__(
    ".section .text\n.set push\n.set noat\n.set noreorder\n"
    "glabel intersectSegmentWithObjectSphere\n"
    "    addiu      $sp, $sp, -0x4\n"
    "    sw         $ra, 0x0($sp)\n"
    "    jal        transformObjectColliderCenter\n"
    "    nop\n"
    "    mfc1       $t0, $fs0\n"
    "    mfc1       $t1, $fs1\n"
    "    mfc1       $t2, $fs2\n"
    "    mfc1       $t3, $fs3\n"
    "    lwc1       $ft0, 0x0($v0)\n"
    "    lwc1       $ft3, 0x0($a2)\n"
    "    lwc1       $ft1, 0x4($v0)\n"
    "    sub.s      $ft0, $ft0, $ft3\n"
    "    lwc1       $ft3, 0x4($a2)\n"
    "    lwc1       $ft2, 0x8($v0)\n"
    "    sub.s      $ft1, $ft1, $ft3\n"
    "    lwc1       $ft3, 0x8($a2)\n"
    "    nop\n"
    "    sub.s      $ft2, $ft2, $ft3\n"
    "    lwc1       $fs0, 0x0($a3)\n"
    "    lwc1       $fs1, 0x4($a3)\n"
    "    mul.s      $ft4, $fs0, $ft0\n"
    "    lwc1       $fs2, 0x8($a3)\n"
    "    mul.s      $ft3, $fs1, $ft1\n"
    "    nop\n"
    "    mul.s      $ft5, $fs2, $ft2\n"
    "    add.s      $ft4, $ft4, $ft3\n"
    "    add.s      $ft4, $ft4, $ft5\n"
    "    mul.s      $ft5, $ft0, $ft0\n"
    "    nop\n"
    "    mul.s      $ft1, $ft1, $ft1\n"
    "    nop\n"
    "    mul.s      $ft2, $ft2, $ft2\n"
    "    add.s      $ft5, $ft5, $ft1\n"
    "    add.s      $ft5, $ft5, $ft2\n"
    "    lwc1       $ft0, 0xC($v0)\n"
    "    mtc1       $zero, $ft1\n"
    "    nop\n"
    "    cvt.s.w    $ft1, $ft1\n"
    "    nop\n"
    "    c.lt.s     $ft4, $ft1\n"
    "    nop\n"
    "    bc1f       .Lmain_8006AF14\n"
    "    nop\n"
    "    c.le.s     $ft5, $ft0\n"
    "    nop\n"
    "    bc1f       .Lmain_8006AFA0\n"
    "    nop\n"
    "  .Lmain_8006AF14:\n"
    "    mul.s      $fs0, $fs0, $fs0\n"
    "    nop\n"
    "    mul.s      $fs1, $fs1, $fs1\n"
    "    nop\n"
    "    mul.s      $fs2, $fs2, $fs2\n"
    "    add.s      $fs0, $fs0, $fs1\n"
    "    add.s      $fs0, $fs0, $fs2\n"
    "    mul.s      $fs1, $ft4, $ft4\n"
    "    sub.s      $ft5, $ft0, $ft5\n"
    "    div.s      $fs2, $fs1, $fs0\n"
    "    nop\n"
    "    add.s      $ft5, $ft5, $fs2\n"
    "    c.le.s     $ft5, $ft1\n"
    "    nop\n"
    "    bc1t       .Lmain_8006AFA0\n"
    "    nop\n"
    "    sqrt.s     $fs0, $fs0\n"
    "    nop\n"
    "    sqrt.s     $ft5, $ft5\n"
    "    nop\n"
    "    div.s      $ft4, $ft4, $fs0\n"
    "    nop\n"
    "    sub.s      $ft4, $ft4, $ft5\n"
    "    c.le.s     $ft4, $fs0\n"
    "    nop\n"
    "    bc1f       .Lmain_8006AFA0\n"
    "    nop\n"
    "    mtc1       $t0, $fs0\n"
    "    mtc1       $t1, $fs1\n"
    "    mtc1       $t2, $fs2\n"
    "    mtc1       $t3, $fs3\n"
    "    lw         $ra, 0x0($sp)\n"
    "    addiu      $sp, $sp, 0x4\n"
    "    jr         $ra\n"
    "    nop\n"
    "  .Lmain_8006AFA0:\n"
    "    mtc1       $t0, $fs0\n"
    "    mtc1       $t1, $fs1\n"
    "    mtc1       $t2, $fs2\n"
    "    mtc1       $t3, $fs3\n"
    "    lw         $ra, 0x0($sp)\n"
    "    addiu      $sp, $sp, 0x4\n"
    "    jr         $ra\n"
    "    addu      $v0, $zero, $zero\n"
    "endlabel intersectSegmentWithObjectSphere\n"
    ".set pop\n"
);

// Looking at the assembly for this, I'm forced to wonder if it was hand-written...
// Hand-written assembly.
__asm__(
    ".set push\n.set noat\n.set noreorder\n"
    "glabel decrypt_ns_hmt\n"
    "    addu       $t0, $a0, $zero\n"
    "    addu       $t1, $a1, $zero\n"
    "    addu       $t2, $a2, $zero\n"
    "  .Lmain_8006AFCC:\n"
    "    lbu        $t3, 0x0($t0)\n"
    "    andi       $t4, $t2, 0xFF\n"
    "    xor        $t5, $t3, $t4\n"
    "    sb         $t5, 0x0($t0)\n"
    "    srl        $t4, $t2, 8\n"
    "    sll        $t2, $t2, 24\n"
    "    or         $t2, $t2, $t4\n"
    "    addu       $t2, $t2, $t3\n"
    "    addiu      $t1, $t1, -0x1\n"
    "    bnez       $t1, .Lmain_8006AFCC\n"
    "    addiu     $t0, $t0, 0x1\n"
    "    jr         $ra\n"
    "    nop\n"
    "endlabel decrypt_ns_hmt\n"
    ".set pop\n"
);

INCLUDE_ASM("asm/nonmatchings/main/6B8B0", applyLevelScreenAndCameraSettings);

s32 isCraftAvailableByIdx(s32 craftId) {
    switch (craftId) {
    case CRAFT_XWING:
        if ((gGameSettings.unk23 == 0) && (D_main_bss_80130B39 == 0)) {
            return D_main_800A05D0[gGameSettings.currentLevel].craftAvailabiltyFlags & CRAFT_FLAG(CRAFT_XWING);
        }
        return 0;
    case CRAFT_YWING:
        if ((gGameSettings.unk23 == 0) && (D_main_bss_80130B39 == 0)) {
            return D_main_800A05D0[gGameSettings.currentLevel].craftAvailabiltyFlags & CRAFT_FLAG(CRAFT_YWING);
        }
        return 1;
    case CRAFT_AWING:
        if (gGameSettings.unk23 == 0) {
            return D_main_800A05D0[gGameSettings.currentLevel].craftAvailabiltyFlags & CRAFT_FLAG(CRAFT_AWING);
        }
        return 1;
    case CRAFT_FALCON:
        if ((gGameSettings.unk23 == 0) && (D_main_bss_80130B39 == 0)) {
            return D_main_800A05D0[gGameSettings.currentLevel].craftAvailabiltyFlags & CRAFT_FLAG(CRAFT_FALCON);
        }
        return 1;
    case CRAFT_TIEINTER:
        if ((gGameSettings.unk23 == 0) && (D_main_bss_80130B39 == 0)) {
            return D_main_800A05D0[gGameSettings.currentLevel].craftAvailabiltyFlags & CRAFT_FLAG(CRAFT_TIEINTER);
        }
        return 0;
    case CRAFT_T16:
        if ((gGameSettings.unk23 == 0) && (D_main_bss_80130B39 == 0)) {
            return D_main_800A05D0[gGameSettings.currentLevel].craftAvailabiltyFlags & CRAFT_FLAG(CRAFT_T16);
        }
        return 0;
    case CRAFT_VWING:
        if ((gGameSettings.unk23 == 0) && (D_main_bss_80130B39 == 0)) {
            return D_main_800A05D0[gGameSettings.currentLevel].craftAvailabiltyFlags & CRAFT_FLAG(CRAFT_VWING);
        }
        return 0;
    case CRAFT_SNOWSPEEDER:
        if ((gGameSettings.unk23 == 0) && (D_main_bss_80130B39 == 0)) {
            return D_main_800A05D0[gGameSettings.currentLevel].craftAvailabiltyFlags & CRAFT_FLAG(CRAFT_SNOWSPEEDER);
        }
        return 0;
    default:
        return 0;
    }
}

extern s32 gBootConfig;

u16 getBootConfigField12(void) {
    return (*(u16 *)((u8 *)(&gBootConfig) + 0x12));
}

u16 getBootConfigField14(void) {
    return (*(u16 *)((u8 *)(&gBootConfig) + 0x14));
}

s32 getLevelCutsceneActorCallbackPrimary(void) {
    if ((gGameSettings.unlockAndSettingsFlags[1] & 1) &&
        ((gGameSettings.currentLevel == LEVEL_SULLUST) ||
         (gGameSettings.currentLevel == LEVEL_CONST_YARD) ||
         (gGameSettings.currentLevel == LEVEL_KILEII)
        )
    ) {
        return 0;
    }
    return D_main_800A05D0[gGameSettings.currentLevel].unk0C;
}

s32 getLevelCutsceneActorCallbackSecondary(void) {
    if ((gGameSettings.unlockAndSettingsFlags[1] & 1) &&
        ((gGameSettings.currentLevel == LEVEL_SULLUST) ||
         (gGameSettings.currentLevel == LEVEL_CONST_YARD)
        )
    ) {
        return 0;
    }
    return D_main_800A05D0[gGameSettings.currentLevel].unk0C;
}

s32 getLevelConfigWordA(void) {
    return D_main_800A05D0[gGameSettings.currentLevel].unk14;
}

s32 getLevelConfigWordB(void) {
    return D_main_800A05D0[gGameSettings.currentLevel].unk18;
}

f32 getLevelConfigFloatA(void) {
    return D_main_800A05D0[gGameSettings.currentLevel].unk1C;
}

f32 getLevelConfigFloatB(void) {
    return D_main_800A05D0[gGameSettings.currentLevel].unk20;
}

void copyLevelConfigColorTriple(void *arg0) {
    (*(u8 *)((u8 *)(arg0) + 0)) = (u8) D_main_800A05D0[gGameSettings.currentLevel].unk28.r;
    (*(u8 *)((u8 *)(arg0) + 1)) = (u8) D_main_800A05D0[gGameSettings.currentLevel].unk28.g;
    (*(u8 *)((u8 *)(arg0) + 2)) = (u8) D_main_800A05D0[gGameSettings.currentLevel].unk28.b;
}

void copyLevelConfigPackedWord(struct rgba *dst) {
    *dst = D_main_800A05D0[gGameSettings.currentLevel].unk24;
}

s16 getLevelConfigHalfword(void) {
    return D_main_800A05D0[gGameSettings.currentLevel].unk2C;
}

s32 getLevelExpansionMemoryBudget(void) {
    if (gGameSettings.unk23 != 0) return 0x800;
    if (gGameSettings.currentLevel == LEVEL_CORELLIA) {
        return 0x190;
    } else if (gGameSettings.currentLevel == LEVEL_KILEII) {
        return 0x271;
    } else if (gGameSettings.currentLevel == LEVEL_JADEMOON) {
        return 0x258;
    } else if (gGameSettings.currentLevel == LEVEL_THYFERRA) {
        return 0x258;
    } else {
        return 0x1F4;
    }
}

s32 getLevelTimeLimit(void) {
    if (gGameSettings.unk23 != 0) return 0x7D0;

    switch (gGameSettings.currentLevel) {
        case LEVEL_GERRARDV:
        case LEVEL_KESSEL_PRISON:
        case LEVEL_SULLUST:
            return 0x190;
        case LEVEL_KILEII:
            return 0x1F4;
        case LEVEL_THYFERRA:
            return 0x258;
        case LEVEL_TRENCH_RUN:
            return 0x3E8;
        default:
            return 0x12C;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/6B8B0", fake_func_8006B704);

static const u32 padding_junk[] = {0x46246081, 0x46281081};
