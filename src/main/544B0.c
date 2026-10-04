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

s16 rand();
typedef struct {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[2];
} ListSpacingEntry;
void randomizeListEntrySpacing(ListSpacingEntry *arg0, ListSpacingEntry *src, u16 range)
{
  u16 v = src->unk4;
  int r = range;
  ListSpacingEntry *p = src;
  ListSpacingEntry *dst = arg0;
  do
  {
    p++;
    dst->unk4 = v - (rand() % r);
    v = p->unk4;
    dst++;
  }
  while ((p->unk4 - src->unk4) < 16);
}

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
