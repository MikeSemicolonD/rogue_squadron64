#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanResetState);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", func_mission_overlay_800D7974);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanStateEffectShared);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A781C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7820);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7824);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanState0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7834);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanState1);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7844);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7848);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A784C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanBehaviorByMode);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanSpawnBurstEffects);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7954);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanSteerToward);

s32 buildRotationMatrixSlot2(s32, f32);
f32 cosf(f32);
u8 isAudioVoiceActive(void *);
s32 updateActive3DAudioSource(void *, void *, void *, u8);

void npcWingmanUpdateEngineAudio(void *arg0, f32 arg1) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    u8 temp_v0;
    void *temp_s1;

    temp_fv1 = (*(f32 *)((u8 *)(arg0) + 0xEC));
    if (temp_fv1 > 0.0f) {
        temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0xE8)) + (temp_fv1 * arg1);
        (*(f32 *)((u8 *)(arg0) + 0xE8)) = temp_fv0;
        if (temp_fv0 > 1.0f) {
            (*(f32 *)((u8 *)(arg0) + 0xE8)) = 1.0f;
            (*(f32 *)((u8 *)(arg0) + 0xEC)) = 0.0f;
        }
        (*(f32 *)((u8 *)(arg0) + 0xE4)) = (f32) ((1.0f - ((cosf((*(f32 *)((u8 *)(arg0) + 0xE8)) * 3.1415927f) + 1.0f) * 0.5f)) * 10.0f);
    } else if (temp_fv1 < 0.0f) {
        temp_fv0_2 = (*(f32 *)((u8 *)(arg0) + 0xE8)) + (temp_fv1 * arg1);
        (*(f32 *)((u8 *)(arg0) + 0xE8)) = temp_fv0_2;
        if (temp_fv0_2 < 0.0f) {
            (*(f32 *)((u8 *)(arg0) + 0xE8)) = 0.0f;
            (*(f32 *)((u8 *)(arg0) + 0xEC)) = 0.0f;
        }
        (*(f32 *)((u8 *)(arg0) + 0xE4)) = (f32) ((1.0f - ((cosf((*(f32 *)((u8 *)(arg0) + 0xE8)) * 3.1415927f) + 1.0f) * 0.5f)) * 10.0f);
    }
    buildRotationMatrixSlot2((*(s32 *)((u8 *)(arg0) + 0x98)) + 0x1C, (*(f32 *)((u8 *)(arg0) + 0xE4)));
    buildRotationMatrixSlot2((*(s32 *)((u8 *)(arg0) + 0x9C)) + 0x1C, -(*(f32 *)((u8 *)(arg0) + 0xE4)));
    temp_s1 = arg0 + 0xA0;
    if ((*(u8 *)((u8 *)(arg0) + 0xF0)) != 0) {
        temp_v0 = isAudioVoiceActive(temp_s1);
        (*(u8 *)((u8 *)(arg0) + 0xF0)) = temp_v0;
        if (temp_v0 & 0xFF) {
            updateActive3DAudioSource(temp_s1, arg0, arg0 + 0x24, (*(u8 *)((u8 *)(arg0) + 0xF1)));
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanUpdate);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanState2);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanState3);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanState4);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanState5);

s32 npcWingmanStateNoop(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanState6);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7B00);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcTieVariantTickEffects);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcTieVariantSteerToward);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcTieVariantTickAttachmentEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcTieVariantHandleDestruction);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcTieVariantUpdate);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C0C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", jtbl_mission_overlay_800A7C10);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C34);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C38);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C3C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C40);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C44);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", jtbl_mission_overlay_800A7C48);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C5C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C60);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C64);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C68);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C6C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C70);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C74);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C78);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C7C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", jtbl_mission_overlay_800A7C80);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C98);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7C9C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CA0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CA4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CA8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CAC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CB0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CB4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CB8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CBC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CC0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CC4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CC8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CCC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CD0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CD4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CD8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CDC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CE0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CE4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CE8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CEC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CF0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CF4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7CF8);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcRadarDishInit);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7D00);
