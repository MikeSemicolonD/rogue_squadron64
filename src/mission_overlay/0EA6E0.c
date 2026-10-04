#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EA6E0", func_mission_overlay_800E9AE0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EA6E0", initObjectAnimAndDetail);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EA6E0", playStateGatedDestroySound);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EA6E0", func_mission_overlay_800EA470);

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
