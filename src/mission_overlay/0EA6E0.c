#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EA6E0", func_mission_overlay_800E9AE0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EA6E0", initObjectAnimAndDetail);

extern f32 D_mission_overlay_8010B184[];
extern u8 D_mission_overlay_8010B198[];
extern f32 D_mission_overlay_8010B19C[];
extern u8 D_mission_overlay_8010B1AC[];
extern f32 D_mission_overlay_8010B1B0[];
extern u8 D_mission_overlay_8010B1B8[];
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

void playStateGatedDestroySound(u8 *o, f32 dt, u8 arg2) {
    f32 *tbl;
    u8 *flags;
    f32 t;
    u16 idx;

    switch (*(s16 *)(o + 0x84)) {
    case 0:
        tbl = D_mission_overlay_8010B184;
        flags = D_mission_overlay_8010B198;
        break;
    case 1:
        tbl = D_mission_overlay_8010B19C;
        flags = D_mission_overlay_8010B1AC;
        break;
    case 2:
        tbl = D_mission_overlay_8010B1B0;
        flags = D_mission_overlay_8010B1B8;
        break;
    default:
        return;
    }
    t = *(f32 *)(o + 0x70) + dt / *(f32 *)(o + 0xA0);
    *(f32 *)(o + 0x70) = t;
    if (t > 1.0f) {
        *(u16 *)(o + 0x78) = 0;
        *(f32 *)(o + 0x70) = *(f32 *)(o + 0x9C);
        *(f32 *)(o + 0x74) = tbl[0];
        return;
    }
    if (arg2 == 0 && *(f32 *)(o + 0x74) <= t) {
        idx = *(u16 *)(o + 0x78);
        *(u16 *)(o + 0x78) = idx + 1;
        if (flags[(s16)idx] == 0) {
            play3DSoundEvent(0, o, o + 0x24, 12.0f, 0.3f, 0, 0x62, 0x78, 0x28);
        } else {
            play3DSoundEvent(0, o, o + 0x24, 12.0f, 0.3f, 0, 0x63, 0x78, 0x28);
        }
        *(f32 *)(o + 0x74) = tbl[*(s16 *)(o + 0x78)];
    }
}

s16 getObjectNpcTypeId(s32);
s32 lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
s32 setObjectSubstructF10IfReady(s32, f32, s32);
s32 slotDispatcherIter(s32, s32, void *);
s32 tickProgressChannel(s32, void *, s32, s32);
s32 triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);
extern s32 D_main_bss_80137CE4;
extern u8 D_mission_overlay_8010B178[];

s32 spawnObjectImpactEffectWithSound(u8 *arg0, s32 arg1) {
    u8 sp28[0x30];
    struct {
        s16 a;
        s16 b;
        s32 pad4[2];
        f32 c;
        f32 d;
        s32 pad[2];
    } sp58;
    s32 temp_s0;
    u8 *temp_s1;

    temp_s1 = *(u8 **)(arg0 + 4);
    lookupHmtTextureByName(*(s32 *)(temp_s1 + 0x30), "a_b", arg1, sp28, 0, 0);
    if (arg1 == 0) {
        setObjectSubstructF10IfReady(*(s32 *)(temp_s1 + 0x38), 0.06666667f, 0);
        *(s32 *)(temp_s1 + 0x5C) = 0;
    }
    temp_s0 = tickProgressChannel(*(s32 *)(temp_s1 + 0x38), sp28, 0, 0) & 0xFF;
    if (temp_s0 == 1) {
        sp58.a = 0;
        sp58.b = getObjectNpcTypeId(*(s32 *)(temp_s1 + 0x38));
        sp58.c = 5.0f;
        sp58.d = *(f32 *)(*(u8 **)(temp_s1 + 0x34) + D_main_bss_80137CE4 * 4 + 0xD8);
        slotDispatcherIter(triggerCueWithSlotEffect(*(s32 *)(temp_s1 + 0x38), 4, sp28, D_mission_overlay_8010B178, temp_s0, 10.0f, -1.0f) & 0xFFFF, 0xA, &sp58);
        play3DSoundEvent(0, temp_s1, temp_s1 + 0x24, 20.0f, 0.4f, 0, 0xD, 0x78, 0x28);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EA6E0", computeNpcOrientationFromAimVectors);

#include "common_types.h"
extern void clearModelAnimChannelEntry(s32);
extern void releaseModelAnimSlot(s32);
extern s32 flattenAnimTreeAndAllocateSlot(s32, s32);
extern s32 markModelAnimChannelEntryActive(s32, s32);
extern void setModelAnimSlotCycleDuration(s32, f32);
extern void playStateGatedDestroySound(u8 *, f32, u8);

typedef struct {
    u8 pad0[0x30];
    s32 *p30;
    u8 pad34[0x20];
    f32 f54;
    u8 pad58[0x2C];
    s16 s84;
    u8 pad86[2];
    s32 a88[2];
    u8 pad90[4];
    s32 i94;
    s32 i98;
    s32 i9C;
    f32 fA0;
    f32 fA4;
    u8 padA8[0xB];
    u8 bB3;
} AnimObj;

void func_mission_overlay_800EA470(AnimObj *arg0) {
    f32 t;
    clearModelAnimChannelEntry(arg0->i98);
    releaseModelAnimSlot(arg0->i94);
    switch (arg0->bB3) {
    case 1:
        arg0->s84 = 2;
        arg0->fA0 = 1.0f / (arg0->fA0 * arg0->fA4);
        arg0->fA4 = 0.14400001f / arg0->f54;
        break;
    case 2:
        arg0->i9C = 0;
        arg0->s84 = 1;
        arg0->fA0 = 1.0f / (arg0->fA0 * arg0->fA4);
        arg0->fA4 = 0.074999996f / arg0->f54;
        break;
    case 3:
        arg0->s84 = 0;
        arg0->fA0 = 1.0f / (arg0->fA0 * arg0->fA4);
        arg0->fA4 = 0.06f / arg0->f54;
        break;
    default:
        return;
    }
    arg0->fA0 = 1.0f / (arg0->fA0 * arg0->fA4);
    arg0->i94 = flattenAnimTreeAndAllocateSlot(arg0->p30[6], arg0->a88[arg0->s84]);
    arg0->i98 = markModelAnimChannelEntryActive(arg0->i94, 0);
    setModelAnimSlotCycleDuration(arg0->i94, arg0->fA0);
    playStateGatedDestroySound((u8 *)arg0, 10.0f, 1);
    arg0->bB3 = 0;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8748);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EA6E0", npcAtPtUpdate);

extern s32 D_mission_overlay_8010C0C0;

void resetObjectPoolListHead(void) {
    D_mission_overlay_8010C0C0 = 0;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A87B0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", jtbl_mission_overlay_800A87B8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A87DC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A87E0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A87E4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A87E8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A87EC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A87F0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A87F4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A87F8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A87FC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8800);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8804);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8808);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A880C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8810);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8814);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8818);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A881C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8820);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8824);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8828);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A882C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8830);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8834);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8838);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A883C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8840);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8844);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8848);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A884C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8850);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8854);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8858);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A885C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8860);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8864);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8868);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A886C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8870);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8874);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8878);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A887C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8880);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EA6E0", D_mission_overlay_800A8884);
