#include "common.h"
#include "common_types.h"

extern void rs_memset(void *, s32, s32);
extern s32 setNpcHealth(s32, void *, void *);
extern void initActorMotionParams(s32, f32, f32, f32, f32);
extern void setObjectDetailLevel(s32, s32);
extern void *lookupHmtMaterialByName(s32, char *, s32 *);
extern s32 D_main_bss_80137CE4;

void npcWingmanResetState(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 *def = *(u8 **)(npc + 0x34);

    rs_memset(npc + 0x68, 0, 0x30);
    if (setNpcHealth(*(s32 *)(npc + 0x38), def + 0x6C, def) > 0) {
        initActorMotionParams(*(s32 *)(npc + 0x38), ((f32 *)(def + 0xC0))[D_main_bss_80137CE4], ((f32 *)(def + 0xC4))[D_main_bss_80137CE4], ((f32 *)(def + 0xC8))[D_main_bss_80137CE4], ((f32 *)(def + 0xCC))[D_main_bss_80137CE4]);
        setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(def + 0xAC));
        npc[0x5C] = 0;
    } else {
        npc[0x5C] = 4;
        npc[0x84] = 1;
    }
    npc[0x53] = 0;
    npc[0xF4] = 0;
    if (*(s32 *)(def + 0x8C) == 0) {
        if (*(s32 *)(def + 0xB4) == 0) {
            *(f32 *)(npc + 0xE4) = 0.0f;
            *(f32 *)(npc + 0xE8) = 0.0f;
        } else {
            *(f32 *)(npc + 0xE4) = 10.0f;
            *(f32 *)(npc + 0xE8) = 1.0f;
        }
        *(s32 *)(npc + 0xEC) = 0;
        *(void **)(npc + 0x98) = lookupHmtMaterialByName(*(s32 *)(npc + 0x30), "wngrot_a", NULL);
        *(void **)(npc + 0x9C) = lookupHmtMaterialByName(*(s32 *)(npc + 0x30), "wngrot_b", NULL);
        npc[0xF0] = 0;
    }
}

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

extern char D_mission_overlay_800A781C[];
extern char D_mission_overlay_800A7820[];
extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern u8 npcWingmanStateEffectShared(void *, void *, f32, u8);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 npcWingmanState2(void *arg0) {
    u8 tex[0x30];
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    char *name = NULL;

    switch (npc[0x5E]) {
    case 0:
        name = D_mission_overlay_800A781C;
        break;
    case 1:
        name = D_mission_overlay_800A7820;
        break;
    }
    npc[0x5E] ^= 1;
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), name, 0, tex, 0, 0);
    if (npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]) == 1) {
        play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 2, 90, 40);
    }
    return 0;
}

extern char D_mission_overlay_800A7844[];

s32 npcWingmanState3(void *arg0) {
    u8 tex[0x30];
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    char *name = NULL;
    s32 variant = 0;

    switch (npc[0x5E]) {
    case 0:
        name = D_mission_overlay_800A7844;
        break;
    case 1:
        name = D_mission_overlay_800A7844;
        variant = 1;
        break;
    }
    npc[0x5E] ^= 1;
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), name, variant, tex, 0, 0);
    if (npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]) == 1) {
        play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 2, 90, 40);
    }
    return 0;
}

extern char D_mission_overlay_800A7848[];

s32 npcWingmanState4(void *arg0) {
    u8 tex[0x30];
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 hit;

    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A7848, 0, tex, 0, 0);
    hit = npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A7848, 1, tex, 0, 0);
    hit |= npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]);
    if (hit == 1) {
        play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 2, 90, 40);
    }
    return 0;
}

extern char D_mission_overlay_800A784C[];

s32 npcWingmanState5(void *arg0) {
    u8 tex[0x30];
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    char *name = NULL;
    u8 hit;

    switch (npc[0x5E]) {
    case 0:
        name = D_mission_overlay_800A7844;
        break;
    case 1:
        name = D_mission_overlay_800A784C;
        break;
    }
    npc[0x5E] ^= 1;
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), name, 0, tex, 0, 0);
    hit = npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), name, 1, tex, 0, 0);
    hit |= npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]);
    if (hit == 1) {
        play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 0x2F, 0x6E, 0x3C);
    }
    return 0;
}

s32 npcWingmanStateNoop(void) {
    return 1;
}

s32 npcWingmanState6(void *arg0) {
    u8 tex[0x30];
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    char *name = NULL;
    s32 variant = 0;

    switch (npc[0x5E]) {
    case 0:
        name = D_mission_overlay_800A7844;
        break;
    case 1:
        name = D_mission_overlay_800A7844;
        variant = 1;
        break;
    }
    npc[0x5E] ^= 1;
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), name, variant, tex, 0, 0);
    if (npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]) == 1) {
        play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 0x31, 100, 50);
    }
    return 0;
}

static u32 D_mission_overlay_800A7B04[] __attribute__((section(".rodata"))) = { 0x10600001, 0x00000000, 0x8FC2001C };

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

extern s32 setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern void initActorMotionParams(s32, f32, f32, f32, f32);
extern void initObjectAnimSubstruct(s32, f32, f32, f32, f32, void *, s32, f32, f32, s32);
extern void npcTieVariantTickEffects(void);
extern s32 D_main_bss_80137CE4;

void npcRadarDishInit(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 *def = *(u8 **)(npc + 0x34);

    npc[0x87] = 0;
    npc[0xBA] = 0;
    *(s16 *)(npc + 0x88) = 0;
    setNpcHealth(*(s32 *)(npc + 0x38), *(u8 **)(npc + 0x34) + 0x6C, *(u8 **)(npc + 0x34));
    initActorMotionParams(*(s32 *)(npc + 0x38), ((f32 *)(def + 0xC0))[D_main_bss_80137CE4], ((f32 *)(def + 0xC4))[D_main_bss_80137CE4], ((f32 *)(def + 0xC8))[D_main_bss_80137CE4], ((f32 *)(def + 0xCC))[D_main_bss_80137CE4]);
    setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(*(u8 **)(npc + 0x34) + 0xB4));
    initObjectAnimSubstruct(*(s32 *)(npc + 0x38), *(f32 *)(def + 0xD0), *(f32 *)(def + 0xD4), *(f32 *)(def + 0xD8), *(f32 *)(def + 0xDC), npcTieVariantTickEffects, 0, 10.0f, 15.0f, 0);
}

static u32 D_mission_overlay_800A7D04[] __attribute__((section(".rodata"))) = { 0x8FC2001C, 0x3C018005, 0xC420FE44 };
