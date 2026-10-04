#include "common.h"
#include "common_types.h"

#include "main/47220.h"

INCLUDE_ASM("asm/nonmatchings/main/47220", parseDatItemCommon);

INCLUDE_ASM("asm/nonmatchings/main/47220", loadDatFile);

INCLUDE_ASM("asm/nonmatchings/main/47220", updateActiveGridCellState);

INCLUDE_ASM("asm/nonmatchings/main/47220", parseDatItemSubtypes1To5);

s32 rs_free(s32);
extern s32 D_main_bss_801375D0;
extern s32 D_main_bss_801375D8;

void freeLevelDatBuffers(void) {
    rs_free(D_main_bss_801375D0);
    D_main_bss_801375D0 = 0;
    rs_free((*(s32 *)((u8 *)(&D_main_bss_801375D8) + 0)));
    rs_free((*(s32 *)((u8 *)(&D_main_bss_801375D8) + 0x1C)));
}

void *getLevelDatItemByName(char *name) {
    return getDatItemByName((struct dat_file_header *)D_main_bss_801375D8, name);
}

INCLUDE_ASM("asm/nonmatchings/main/47220", getDatItemByName);

INCLUDE_ASM("asm/nonmatchings/main/47220", findDatItemInTableByName);

extern s32 D_main_bss_801375F8;
extern s32 D_8010CA1C;
f32 *getCutsceneRuntimeContext();
extern u8 D_main_bss_80130B39;

void isNpcWithinActiveReferenceRange(f32 *arg0) {
    s32 *var_a0;
    s32 *var_v0;

    if (D_main_bss_80130B39 == 0) {
        if (!(D_8010CA1C & 8)) {
            var_a0 = getCraftRecordByIdx(0);
        } else {
            var_v0 = &D_main_bss_801375F8;
            goto block_5;
        }
    } else {
        var_v0 = getCutsceneRuntimeContext();
block_5:
        var_a0 = var_v0;
    }
    isPointXzWithinRangeOfRef((f32 *) var_a0, arg0);
}

s32 isPointXzWithinRangeOfRef(Vec3f arg0, Vec3f arg1) {
    f32 xdist;
    f32 zdist;

    xdist = (arg0[0] - arg1[0]) * 0.25f;
    zdist = (arg0[2] - arg1[2]) * 0.25f;
    if (144.0f < ((xdist * xdist) + (zdist * zdist))) {
        return 0;
    } else {
        return 1;
    }
}

static const u32 rodata_padding = 0x8FA605E8;

s32 *getCraftRecordByIdx(s32);
s32 updateActiveGridCellState(s32 *);
extern s32 D_8010CA1C;
extern s32 D_main_bss_801375F8;

void lookupActivePlayerCraftGridCell(void) {
    s32 *var_v0;

    if (!(D_8010CA1C & 8)) {
        var_v0 = getCraftRecordByIdx(0);
    } else {
        var_v0 = &D_main_bss_801375F8;
    }
    updateActiveGridCellState(var_v0);
}
