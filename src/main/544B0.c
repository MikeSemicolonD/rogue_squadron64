#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/544B0", trackResourceListWithMappingTables);

INCLUDE_ASM("asm/nonmatchings/main/544B0", dispatchOverlaySetupByParentAssetName);

INCLUDE_ASM("asm/nonmatchings/main/544B0", updateAnimatedTextureStreaming);

INCLUDE_ASM("asm/nonmatchings/main/544B0", attachedMeshOverlayNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/544B0", load_full_header_image);

s32 dispatchOverlaySetupByParentAssetName(s32, s32, s32);
s32 rs_malloc(s32, s32);

s32 allocAndSetupModelInstance(s32 arg0) {
    s32 temp_v0;

    temp_v0 = rs_malloc(0x34, 0);
    if (temp_v0 != 0) {
        dispatchOverlaySetupByParentAssetName(arg0, temp_v0, 0xFFFF);
    }
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main/544B0", randomizeListEntrySpacing);

s32 rs_free(s32);

void freeListEntryPointers(void *arg0) {
    s32 temp_a0;
    s32 var_s1;
    void *var_s0;

    var_s1 = 0;
    var_s0 = arg0;
    do {
        temp_a0 = (*(s32 *)((u8 *)(var_s0) + 0x1C));
        var_s0 += 4;
        var_s1 += 1;
        rs_free(temp_a0);
    } while (var_s1 < 2);
}

INCLUDE_ASM("asm/nonmatchings/main/544B0", fake_func_80054648);
