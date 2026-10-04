#include "common.h"
#include "common_types.h"
#include "main/3F160.h"

INCLUDE_ASM("asm/nonmatchings/main/544B0", trackResourceListWithMappingTables);

INCLUDE_ASM("asm/nonmatchings/main/544B0", dispatchOverlaySetupByParentAssetName);

INCLUDE_ASM("asm/nonmatchings/main/544B0", updateAnimatedTextureStreaming);

s32 rs_free(s32);
void *getNpcContextField8(u16);
void updateAnimatedTextureStreaming(u16 *, f32 *, f32);
extern char D_main_8009EBD0[];
extern u8 *D_main_bss_80138D1C;
extern u16 D_main_bss_80139594;
typedef struct {
    u8 pad0[4];
    char *unk4;
} MeshOvl;
typedef struct {
    u8 pad0[0x24];
    f32 x;
    f32 y;
    f32 z;
} NpcVec;
s32 attachedMeshOverlayNpcHandler(struct D_80130BB8_type *arg0, s32 a1, u16 *arg2) {
    s32 arg1 = a1 & 0xFFFF;
    f32 sp10[3];
    f32 len;
    f32 sq;
    NpcVec *v;
    MeshOvl *ovl;
    u16 *data;
    s32 i;
    s32 *p;

    data = (u16 *)arg0->unk04;
    switch (arg1) {
    case 1:
        *data = *arg2;
        ovl = (MeshOvl *)getNpcContextByIndex(*data)->unk0C;
        if (ovl == NULL) {
            destroyNpcSlotByIndex(arg0->unk16);
            return 1;
        }
        dispatchOverlaySetupByParentAssetName((s32)ovl, (s32)data, *data);
        *(char **)((char *)ovl + 4) = D_main_8009EBD0;
        popNpcSlotFromTail(D_main_bss_80139594, arg0);
        return 1;
    case 2:
        i = 0;
        p = (s32 *)data;
        do {
            rs_free(p[7]);
            p++;
            i++;
        } while (i < 2);
        return 1;
    case 4:
        ovl = (MeshOvl *)getNpcContextByIndex(*data)->unk0C;
        if (ovl != NULL) {
            v = getNpcContextField8(*data);
            sq = v->x * v->x + v->y * v->y + v->z * v->z;
            __asm__ volatile("sqrt.s %0, %1" : "=f"(len) : "f"(sq));
            sp10[0] = *(f32 *)(D_main_bss_80138D1C + 0x4C);
            sp10[1] = *(f32 *)(D_main_bss_80138D1C + 0x50);
            sp10[2] = *(f32 *)(D_main_bss_80138D1C + 0x54);
            updateAnimatedTextureStreaming(data, sp10, len);
        }
        return 1;
    }
    return 1;
}

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
