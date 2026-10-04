#include "common.h"
#include "common_types.h"

#include "main/7CEA0.h"

Vec3f D_main_800A0D90 = {0.0f, 0.0f, 1.0f};

struct D_main_800A0D9C_type {
    char *unk00[3];
    f32 block_o_floats[12];
};

struct D_main_800A0D9C_type D_main_800A0D9C[] = {
    {{"top_tran", "barrel_t", "rohr_tra"},
     {0.064567f, 7.99805f, -0.1937f,
      1.0f, 1.0f, 1.0f,
      10.0f, -181.0f, 181.0f,
      0.0f, 60.0f, -2.0f}},
    {{"top_tran", "barrel_t", "rohr_tra"},
     {1.74563f, 6.63377f, 0.0f,
      1.0f, 1.0f, 1.0f,
      10.0f, -181.0f, 181.0f,
      -10.0f, 181.0f, -2.0f}},
    {{"top_tran", "barrel_t", "rohr_tra"},
     {0.0f, 0.0f, 0.802509f,
      1.0f, 1.0f, 1.0f,
      10.0f, -25.0f, 25.0f,
      -7.0f, 7.0f, -2.0f}},
    {{"top_tran", "barrel_t", "rohr_tra"}, 
     {-3.30829f, 13.6873f, 0.0f,
      1.0f, 1.0f, 1.0f,
      10.0f, -181.0f, 181.0f,
      -20.0f, 70.0f, -2.0f}},
    {{"top_tran", "larm_tra", "rarm_tra"},
     {-3.27379f, 5.40009f, 0.0f,
      1.0f, 1.0f, 1.0f,
      5.0f, -181.0f, 181.0f,
      0.0f, 70.0f, 0.0f}},
};

u32 data_pad_7CEA0[] = {
    0x00000000,
    0x24020271,
};

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", initNpcTexturedEffectFromTemplate);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D69C);

extern char D_main_8003D69C[];
extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern s32 stepAndTickProgressChannel(s32, void *, f32, s32, f32 *);
extern void triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);

s32 npcTexturedEffectUpdate(void *arg0) {
    u8 sp28[0x30];
    u8 sp58[0x30];
    u8 sp88[0x30];
    f32 spB8;
    f32 spBC;
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    s32 r;
    struct D_main_800A0D9C_type *e;

    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_main_8003D69C, 0, sp28, (s32)sp88, 0);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_main_8003D69C, 1, sp58, (s32)sp88, 1);
    r = stepAndTickProgressChannel(*(s32 *)(npc + 0x38), sp28, 0.5f, 0, &spB8) & 0xFF;
    if (r == 1) {
        if ((stepAndTickProgressChannel(*(s32 *)(npc + 0x38), sp58, 0.5f, 0, &spBC) & 0xFF) == r) {
            triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, sp28, (u8 *)&D_main_800A0D9C[0].block_o_floats[3] + *(s16 *)(npc + 0xA4) * 0x3C, 0, (e = &D_main_800A0D9C[*(s16 *)(npc + 0xA4)], e->block_o_floats[6]), spB8);
            triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, sp58, (u8 *)&D_main_800A0D9C[0].block_o_floats[3] + *(s16 *)(npc + 0xA4) * 0x3C, 0, (e = &D_main_800A0D9C[*(s16 *)(npc + 0xA4)], e->block_o_floats[6]), spBC);
            play3DSoundEvent(0, npc, npc + 0x24, 12.0f, 0.3f, 0, 0x16, 0x6E, 0x3C);
            *(s32 *)(npc + 0x98) = 0;
        }
    }
    return 0;
}

s32 npcTexturedEffectUpdateVariant(void *arg0) {
    u8 sp28[0x30];
    u8 sp58[0x30];
    u8 sp88[0x30];
    f32 spB8;
    f32 spBC;
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    s32 r;
    struct D_main_800A0D9C_type *e;

    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_main_8003D69C, 0, sp28, (s32)sp88, 0);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_main_8003D69C, 1, sp58, (s32)sp88, 1);
    r = stepAndTickProgressChannel(*(s32 *)(npc + 0x38), sp28, 0.5f, 0, &spB8) & 0xFF;
    if (r == 1) {
        if ((stepAndTickProgressChannel(*(s32 *)(npc + 0x38), sp58, 0.5f, 0, &spBC) & 0xFF) == r) {
            triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, sp28, (u8 *)&D_main_800A0D9C[0].block_o_floats[3] + *(s16 *)(npc + 0xA4) * 0x3C, 0, (e = &D_main_800A0D9C[*(s16 *)(npc + 0xA4)], e->block_o_floats[6]), spB8);
            triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, sp58, (u8 *)&D_main_800A0D9C[0].block_o_floats[3] + *(s16 *)(npc + 0xA4) * 0x3C, 0, (e = &D_main_800A0D9C[*(s16 *)(npc + 0xA4)], e->block_o_floats[6]), spBC);
            play3DSoundEvent(0, npc, npc + 0x24, 12.0f, 0.3f, 0, 0x16, 0x6E, 0x3C);
            *(s32 *)(npc + 0x98) = 0;
        }
    }
    return 0;
}

extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void setObjectSubstructF10IfReady(s32, f32, s32);
extern s32 stepAndTickProgressChannel(s32, void *, f32, s32, f32 *);
extern void triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);

s32 npcTexturedEffectUpdateConditional(void *arg0, s32 arg1) {
    u8 sp28[0x30];
    f32 sp58;
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);

    if (arg1 != 2) {
        setObjectSubstructF10IfReady(*(s32 *)(npc + 0x38), 0.06666667f, 0);
        lookupHmtTextureByName(*(s32 *)(npc + 0x30), "a_b_c", arg1, sp28, 0, 0);
    } else {
        lookupHmtTextureByName(*(s32 *)(npc + 0x30), "a_b_c", 2, sp28, 0, 0);
    }
    if ((stepAndTickProgressChannel(*(s32 *)(npc + 0x38), sp28, 0.5f, 0, &sp58) & 0xFF) == 1) {
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, sp28, (u8 *)&D_main_800A0D9C[0].block_o_floats[3] + *(s16 *)(npc + 0xA4) * 0x3C, 0, ((f32 *)((u8 *)&D_main_800A0D9C[0].block_o_floats[3] + *(s16 *)(npc + 0xA4) * 0x3C))[3], sp58);
        play3DSoundEvent(0, npc, npc + 0x24, 12.0f, 0.3f, 0, 0x16, 0x6E, 0x3C);
        *(s32 *)(npc + 0x98) = 0;
    }
    return 0;
}

extern char D_main_8003D69C[];

s32 npcTexturedEffectUpdateConditionalAlt(void *arg0, s32 arg1) {
    u8 sp28[0x30];
    f32 sp58;
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);

    switch (arg1) {
    case 0:
        setObjectSubstructF10IfReady(*(s32 *)(npc + 0x38), 0.033333335f, 0);
    case 1:
        lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_main_8003D69C, arg1, sp28, 0, 0);
        break;
    }
    if ((stepAndTickProgressChannel(*(s32 *)(npc + 0x38), sp28, 0.5f, 0, &sp58) & 0xFF) == 1) {
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 2, sp28, (u8 *)&D_main_800A0D9C[0].block_o_floats[3] + *(s16 *)(npc + 0xA4) * 0x3C, 0, ((f32 *)((u8 *)&D_main_800A0D9C[0].block_o_floats[3] + *(s16 *)(npc + 0xA4) * 0x3C))[3], sp58);
        play3DSoundEvent(0, npc, npc + 0x24, 12.0f, 0.3f, 0, 0x16, 0x6E, 0x3C);
        *(s32 *)(npc + 0x98) = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", npcTexturedEffectUpdateWithSlotChain);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", aimOrientNpcTowardTarget);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", spawnDatDrivenAudioVisualEmitters);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", spawnNamedTexturedEmitterNpc);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D708);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", npcQuatOrientedMultiPhaseUpdate);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", emitPresetSparkBurst);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", updateWalkerLegStrideAndDust);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", npcWalkerUpdate);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D7C0);

#include "main/1D000.h"
#include "main/192E0.h"
#include "main/5A750.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} V3i;

extern V3i D_main_8003D7C0;

void submitOrientedEffectMesh(u8 *arg0, f32 arg1) {
    V3i sp10;
    V3i sp20;
    f32 ang;
    f32 lim;
    f32 v;
    f32 *s3 = (f32 *)(arg0 + 0x18);
    f32 *s2;
    f32 *s0;

    sp20 = D_main_8003D7C0;
    ang = vec3Dot((f32 *)&sp20, s3);
    if (ang < 0.9996f) {
        s2 = (f32 *)(arg0 + 0x90);
        vec3Cross(s2, s3, (f32 *)&sp20);
        if (vec3Length(s2) > 0.00001f) {
            ang = constMinusSinfApprox(ang) * 57.29578f;
            lim = arg1 * 3.0f;
            if (lim < ang) {
                ang = lim;
            }
            s0 = (f32 *)(arg0 + 0x70);
            quatFromAxisAngleSafe(s0, s2, ang);
            rotateVec3ByQuat(s0, (f32 *)(arg0 + 0xC), (f32 *)&sp10);
            *(V3i *)(arg0 + 0xC) = sp10;
            rotateVec3ByQuat(s0, s3, (f32 *)&sp10);
            *(V3i *)(arg0 + 0x18) = sp10;
            orthonormalizeFrame((f32 *)arg0);
            v = *(f32 *)(arg0 + 0x44) - ((*(f32 *)(arg0 + 0x40) - *(f32 *)(arg0 + 0x48)) * arg1 * 0.33f);
            *(f32 *)(arg0 + 0x44) = v;
            if (v < *(f32 *)(arg0 + 0x48)) {
                *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x48);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", twoPointPositionedNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", spawnWorldDevastatorVacuumDebris);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", npcWordDevastatorUpdate);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D8C0);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", jtbl_main_8003D8C8);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D904);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D908);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D90C);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D910);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", jtbl_main_8003D918);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D92C);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D930);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D934);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D938);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D93C);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D940);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D944);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D948);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D94C);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D950);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D954);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D958);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D95C);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D960);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D964);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D968);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D96C);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D970);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D974);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D978);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D97C);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D980);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D984);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D988);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D98C);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D990);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D994);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D998);

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D99C);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", attachedAudioVisualEmitterNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", npcShieldGeneratorUpdate);

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", npcVortexUpdate);

extern s8 D_main_bss_8013A980;

void clearObjectPoolStateFlag(void) {
    D_main_bss_8013A980 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", npcSpawnInitTimedEffect);

s32 setNpcHealth(void *, void *, s32);
void setObjectDetailLevel(void *, s16);
void npcSpawnInitMarkActive(u8 *arg0, s32 arg1, u8 *arg2) {
    u8 *s = *(u8 **)(arg0 + 4);

    (*(u8 **)(s + 0x34))[0x1A7] = 1;
    setNpcHealth(*(u8 **)(s + 0x34), arg2 + 0x34, 0);
    setObjectDetailLevel(*(u8 **)(s + 0x34), 1);
    *(s16 *)(s + 0x7C) = 0;
}

INCLUDE_ASM("asm/nonmatchings/main/7CEA0", fake_func_80082268);
