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

INCLUDE_ASM("asm/nonmatchings/main/6B8B0", transformObjectColliderCenter);

INCLUDE_ASM("asm/nonmatchings/main/6B8B0", intersectSegmentWithObjectSphere);

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
