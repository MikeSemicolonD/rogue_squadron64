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

typedef struct TexEffTemplate {
    u8 pad00[0x60];
    u8 health[0x24];
    u32 u84;
    u32 pad88;
} TexEffTemplate;

s32 setNpcHealth(void *, void *, s32);
extern s32 D_main_bss_80137CE4;
extern void initActorMotionParams(void *, f32, f32, f32, f32);
extern void initObjectAnimSubstruct(void *, s32, s32, s32, f32, void *, s32, f32, f32, s32);
void setObjectDetailLevel(void *, s16);
extern s32 npcTexturedEffectUpdate(void *);
extern s32 npcTexturedEffectUpdateVariant(void *);
extern s32 npcTexturedEffectUpdateConditional(void *, s32);
extern s32 npcTexturedEffectUpdateConditionalAlt(void *, s32);
extern s32 npcTexturedEffectUpdateWithSlotChain(void *, s32);

void initNpcTexturedEffectFromTemplate(void *arg0) {
    register u8 *eff asm("$17") = *(u8 **)((u8 *)arg0 + 4);
    register u8 *tpl asm("$16") = *(u8 **)(eff + 0x34);
    u8 *row;
    f32 b, a, c, d;
    void *fn;

    *(s16 *)(eff + 0xAC) = 0;
    *(u8 *)(*(u8 **)(eff + 0x38) + 0x1A7) = 1;
    setNpcHealth(*(void **)(eff + 0x38), tpl + 0x60, 0);
    row = (u8 *)(D_main_bss_80137CE4 * 4 + (s32)tpl);
    *(f32 *)(eff + 0x94) = *(f32 *)(row + 0x88) * 30.0f;
    *(s32 *)(eff + 0x9C) = 0;
    *(s16 *)(eff + 0xAE) = 0;
    *(f32 *)(eff + 0x98) = 1.0f;
    a = *(f32 *)(row + 0x84);
    b = *(f32 *)(row + 0x8C);
    c = *(f32 *)(row + 0x90);
    d = *(f32 *)(row + 0x94);
    if (*(s16 *)(eff + 0xA4) != 4) {
        if (b > 50.0f) {
            b = 50.0f;
        }
        if (d > 50.0f) {
            d = 50.0f;
        }
        if (a > 70.0f) {
            a = 70.0f;
        }
        if (c > 70.0f) {
            c = 70.0f;
        }
    }
    initActorMotionParams(*(void **)(eff + 0x38), a, b, c, d);
    switch (*(s16 *)(eff + 0xA4)) {
    case 0:
        fn = npcTexturedEffectUpdate;
        goto common;
    case 1:
        fn = npcTexturedEffectUpdateConditionalAlt;
        goto common;
    case 2:
        fn = npcTexturedEffectUpdateVariant;
        goto common;
    case 3:
        fn = npcTexturedEffectUpdateConditional;
    common:
        initObjectAnimSubstruct(*(void **)(eff + 0x38), *(s32 *)(tpl + 0x98), *(s32 *)(tpl + 0x9C), *(s32 *)(tpl + 0xA0), *(f32 *)(tpl + 0xA4), fn, 0, D_main_800A0D9C[*(s16 *)(eff + 0xA4)].block_o_floats[6], 15.0f, 0);
        break;
    case 4:
        initObjectAnimSubstruct(*(void **)(eff + 0x38), *(s32 *)(tpl + 0x98), *(s32 *)(tpl + 0x9C), *(s32 *)(tpl + 0xA0), *(f32 *)(tpl + 0xA4), npcTexturedEffectUpdateWithSlotChain, 0, D_main_800A0D9C[*(s16 *)(eff + 0xA4)].block_o_floats[6], 50.0f, 0);
        *(s32 *)(eff + 0xA0) = *(s32 *)(tpl + D_main_bss_80137CE4 * 4 + 0xA8);
        break;
    }
    setObjectDetailLevel(*(void **)(eff + 0x38), 1);
}

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

typedef struct {
    u16 h0;
    u16 type;
    f32 f4;
    s32 w8;
    s32 wC;
    f32 f10;
    u8 b14;
    u8 pad15[3];
    f32 f18;
    u8 pad1C[4];
} NtCtx;
extern s32 gObjectiveCounts[0x80];
extern u8 gObjectiveBooleans[0x80];
extern s32 D_main_bss_80137CE4;
f32 *ntMesh(s32, void *) __asm__("getObjectMeshTransformOrLocal");
u16 getObjectNpcTypeId(s32);
s32 ntCue(s32, s32, void *, void *, s32, f32, f32) __asm__("triggerCueWithSlotEffect");
s32 ntIter(u16, s32, void *) __asm__("slotDispatcherIter");

s32 npcTexturedEffectUpdateWithSlotChain(void *arg0, s32 arg1) {
    u8 sp28[0x30];
    NtCtx ctx;
    f32 sp78;
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 *def;
    u8 ret;
    u16 h;
    f32 *m;

    ret = 0;
    def = *(u8 **)(npc + 0x34);
    if (*(s32 *)(def + 0xBC) != 0) {
        if (gObjectiveBooleans[*(s32 *)(def + 0xBC) - 1] == 0) {
            return 0;
        }
    }
    if (*(s32 *)(def + 0xC0) != 0) {
        if (gObjectiveCounts[*(s32 *)(def + 0xC0) - 1] < *(s32 *)(def + 0xC4)) {
            return 0;
        }
    }
    m = ntMesh(*(s32 *)(npc + 0x38), sp28);
    if (*(f32 *)(*(u8 **)(npc + 0x34) + 0xB4) * 0.25f < m[1]) {
        return 0;
    }
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), (*(s16 *)(npc + 0xAE) < 2) ? D_main_8003D69C : "c_d", *(s16 *)(npc + 0xAE) & 1, sp28, 0, 0);
    *(s16 *)(npc + 0xAE) = (*(s16 *)(npc + 0xAE) + 1) % 4;
    if ((stepAndTickProgressChannel(*(s32 *)(npc + 0x38), sp28, 0.5f, 0, &sp78) & 0xFF) == 1) {
        ctx.h0 = 0;
        ctx.type = getObjectNpcTypeId(*(s32 *)(npc + 0x38));
        ctx.f4 = 0.0f;
        ctx.f4 = (f32)((s32 *)(*(u8 **)(npc + 0x34) + 0xB0))[D_main_bss_80137CE4] * 0.033333335f;
        ctx.w8 = 0;
        ctx.wC = 0;
        ctx.f10 = -1.0f;
        ctx.b14 = 0;
        h = ntCue(*(s32 *)(npc + 0x38), 0xB, sp28, (u8 *)&D_main_800A0D9C[0].block_o_floats[3] + *(s16 *)(npc + 0xA4) * 0x3C, 0, ((f32 *)((u8 *)&D_main_800A0D9C[0].block_o_floats[3] + *(s16 *)(npc + 0xA4) * 0x3C))[3], sp78);
        if (*(s32 *)(*(u8 **)(npc + 0x34) + 0xAC) != 0) {
            ntIter(h, 0xA, &ctx);
            ctx.h0 = 4;
            ctx.f18 = *(f32 *)(*(u8 **)(npc + 0x34) + 0xB8);
            ntIter(h, 0xA, &ctx);
        }
        play3DSoundEvent(0, npc, npc + 0x24, 12.0f, 0.3f, 0, 0x16, 0x6E, 0x3C);
        if (--*(s32 *)(npc + 0xA0) == 0) {
            ret = 1;
        }
    }
    return ret;
}

#include "main/1D000.h"
#include "main/192E0.h"
#include "main/5A750.h"
typedef struct { f32 x, y, z; } AimV3;
u8 aimIsPendingChildNpcActive(s32) __asm__("isPendingChildNpcActive");
u8 computeActorAnchorDeltaAfterLOS(s32);
f32 *getObjectMeshTransformOrLocal(s32, void *);
void computeAnchorRelativePositionByDistanceRatio(Vec3f, Mat4x3, f32, Vec3f);
void aimClearPendingChildNpc(s32) __asm__("clearPendingChildNpc");

void aimOrientNpcTowardTarget(void *arg0, f32 dt) {
    u8 *npc = arg0;
    f32 m[12];
    f32 inv[12];
    AimV3 dir;
    AimV3 loc;
    AimV3 rel;
    f32 meshBuf[12];
    AimV3 axis;
    f32 q[4];
    AimV3 cr;
    AimV3 a;
    AimV3 b;
    f32 ang;
    f32 lim;
    f32 d;
    f32 l1;

    if (aimIsPendingChildNpcActive(*(s32 *)(npc + 0x38)) == 1 && computeActorAnchorDeltaAfterLOS(*(s32 *)(npc + 0x38)) == 1) {
        computeAnchorRelativePositionByDistanceRatio((f32 *)npc, (void *)getObjectMeshTransformOrLocal(*(s32 *)(npc + 0x38), meshBuf), D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[6], (f32 *)&rel);
        mat34CrossRowsAndCopyPos((void *)m, (void *)npc, 1.0f);
        mat3x3InverseInto((void *)inv, (void *)m);
        transformVec3ByMat34((void *)inv, (f32 *)&rel, (f32 *)&loc);
        loc.x += D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[0] * *(f32 *)(npc + 0x84);
        loc.y += D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[1] * *(f32 *)(npc + 0x84);
        loc.z += D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[2] * *(f32 *)(npc + 0x84);
        vec3NormalizeInto((f32 *)&dir, (f32 *)&loc);
        buildRotationMatrixSlot0((void *)m, *(f32 *)(npc + 0x90));
        composeRotationMatrixSlot1((void *)m, *(f32 *)(npc + 0x8C));
        transformVec3ByMat34((void *)m, D_main_800A0D90, (f32 *)&loc);
        ang = constMinusSinfApprox(vec3Dot((f32 *)&loc, (f32 *)&dir)) * 57.29578f;
        if (ang > 0.001f) {
            lim = *(f32 *)(npc + 0x94) * dt;
            if (lim < ang) {
                ang = lim;
            }
            vec3Cross((f32 *)&axis, (f32 *)&loc, (f32 *)&dir);
            normalize_vector((f32 *)&axis);
            quatFromAxisAngle(q, (f32 *)&axis, ang);
            rotateVec3ByQuat(q, (f32 *)&loc, (f32 *)&dir);
            axis.y = 0.0f;
            axis.x = dir.x;
            axis.z = dir.z;
            d = vec3Dot(D_main_800A0D90, (f32 *)&axis);
            l1 = vec3Length(D_main_800A0D90) * vec3Length((f32 *)&axis);
            ang = constMinusSinfApprox(d / l1) * 57.29578f;
            a = *(AimV3 *)D_main_800A0D90;
            a.y = 0.0f;
            b = axis;
            b.y = 0.0f;
            vec3Cross((f32 *)&cr, (f32 *)&a, (f32 *)&b);
            if (!(0.0f <= cr.y)) {
                ang = -ang;
            }
            buildRotationMatrixSlot1((void *)m, -ang);
            transformVec3ByMat34((void *)m, (f32 *)&dir, (f32 *)&axis);
            axis.x = 0.0f;
            *(f32 *)(npc + 0x8C) = ang;
            {
                f32 d2 = vec3Dot(D_main_800A0D90, (f32 *)&axis);
                f32 l2 = vec3Length(D_main_800A0D90) * vec3Length((f32 *)&axis);
                f32 r;
                r = constMinusSinfApprox(d2 / l2) * 57.29578f;
                if (!(axis.y <= 0.0f)) {
                    r = -r;
                }
                *(f32 *)(npc + 0x90) = r;
            }
            if (D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[8] < *(f32 *)(npc + 0x8C)) {
                *(f32 *)(npc + 0x8C) = D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[8];
            } else if (*(f32 *)(npc + 0x8C) < D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[7]) {
                *(f32 *)(npc + 0x8C) = D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[7];
            }
            if (D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[10] < *(f32 *)(npc + 0x90)) {
                *(f32 *)(npc + 0x90) = D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[10];
            } else if (*(f32 *)(npc + 0x90) < D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[9]) {
                *(f32 *)(npc + 0x90) = D_main_800A0D9C[*(s16 *)(npc + 0xA4)].block_o_floats[9];
            }
        }
    } else {
        aimClearPendingChildNpc(*(s32 *)(npc + 0x38));
    }
}

typedef struct {
    void *item;
    f32 m[12];
    f32 scale;
    u16 ctx;
    s16 kind;
    s32 pad3C;
} SdA;

typedef struct {
    f32 m[12];
    f32 scale;
    u8 v34[16];
    u16 ctx;
    u16 pad46;
} SdB;

void *getLevelDatItemByName(u8 *);
u8 readFirstNameTreeEntry(s32, char *);
u8 readFirstNameTreeEntryFromNode(char *);
u8 *sdGetCtx(u16) __asm__("getNpcContextByIndex");
u16 sdSpawn(void *, void *, s32, u8) __asm__("spawnNpcOfType");
s32 sdIter(s32, s32, void *) __asm__("slotDispatcherIter");
void sdCopy(void *, void *, u32) __asm__("zmemcpy");
extern u8 sdAv[] __asm__("attachedAudioVisualEmitterNpcHandler");
extern u8 sdSg[] __asm__("npcShieldGeneratorUpdate");

void spawnDatDrivenAudioVisualEmitters(u8 *npc) {
    char it[16];
    SdA a;
    SdB b;
    void *items[5];
    f32 dt;
    s32 i;
    u16 h;
    u8 r;

    dt = 0.033333335f;
    a.scale = *(f32 *)(*(u8 **)(npc + 0x34) + 0x28);
    items[0] = getLevelDatItemByName((u8 *)(*(s32 *)(*(s32 *)(npc + 0x34) + 0xE4) + *(s32 *)(npc + 0x34)));
    items[1] = getLevelDatItemByName((u8 *)(*(s32 *)(*(s32 *)(npc + 0x34) + 0xE8) + *(s32 *)(npc + 0x34)));
    items[2] = getLevelDatItemByName((u8 *)(*(s32 *)(*(s32 *)(npc + 0x34) + 0xEC) + *(s32 *)(npc + 0x34)));
    items[3] = getLevelDatItemByName((u8 *)(*(s32 *)(*(s32 *)(npc + 0x34) + 0xF0) + *(s32 *)(npc + 0x34)));
    items[4] = getLevelDatItemByName((u8 *)(*(s32 *)(*(s32 *)(npc + 0x34) + 0xF4) + *(s32 *)(npc + 0x34)));
    a.ctx = *(u16 *)(*(u8 **)(npc + 0x38) + 0x198);
    for (i = 0; i < 5; i++) {
        if (items[i] == NULL) {
            return;
        }
    }
    *(s16 *)(npc + 0x1B4) = 0;
    for (r = readFirstNameTreeEntry(*(s32 *)(npc + 0x30), it); r; r = readFirstNameTreeEntryFromNode(it)) {
        {
            s32 w;
            lookupHmtTextureByName(*(s32 *)(npc + 0x30), it, 0, a.m, 0, 0);
            w = *(s32 *)it & ~0xFF;
#define SDSPAWN(K, I)                 a.kind = K;                 a.item = items[I];                 h = sdSpawn(sdAv, &a, 2, sdGetCtx(*(u16 *)(*(u8 **)(npc + 0x38) + 0x198))[0x19] + 1);
            if (w == 0x73707400) {
                SDSPAWN(3, 4)
            } else if (w == 0x62746D00) {
                SDSPAWN(4, 3)
            } else if (w == 0x73646800) {
                SDSPAWN(2, 1)
            } else if (w == 0x74707400) {
                SDSPAWN(0, 0)
            } else if (w == 0x62746700) {
                SDSPAWN(1, 2)
            } else {
                continue;
            }
            if (h != 0xFFFF) {
                sdIter(h, 3, &dt);
                *(u16 *)((s32)npc + ((*(s16 *)(npc + 0x1B4))++ << 1) + 0x1B6) = h;
            }
        }
    }
    sdCopy(b.v34, *(u8 **)(npc + 0x34) + 0xBC, 0x10);
    b.scale = *(f32 *)(*(u8 **)(npc + 0x34) + 0x28);
    b.ctx = *(u16 *)(*(u8 **)(npc + 0x38) + 0x198);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), "shld", 0, &b, 0, 0);
    *(u16 *)(npc + 0x1F6) = sdSpawn(sdSg, &b, 2, sdGetCtx(*(u16 *)(*(u8 **)(npc + 0x38) + 0x198))[0x19] + 1);
    sdIter(*(u16 *)(npc + 0x1F6), 3, &dt);
}

typedef struct { f32 m[12]; } SnMat;
typedef struct {
    SnMat m;
    f32 scale[3];
    u16 ctx;
    u16 idx;
    void *name;
    s32 pad44;
} SnArgs;

typedef struct {
    u8 pad0[0xFC];
    u16 hFC[4];
    u16 h104[4];
    u16 h10C[4];
    u16 h114[4];
    u16 h11C[4];
} SnNpc;

extern u8 D_main_bss_80130B39;
extern u8 snVortex[] __asm__("npcVortexUpdate");
extern u8 snHeavy[] __asm__("heavyAttachedAudioEmitterNpcHandler");
u8 *snGetCtx(u16) __asm__("getNpcContextByIndex");
u16 spawnNpcOfType(void *, void *, s32, u8);
s32 slotDispatcherIter(s32, s32, void *);
u16 spawnInheritedNpcVariantB(u16, void *);
s32 sprintf(char *, const char *, ...);

void spawnNamedTexturedEmitterNpc(u8 *npc, s32 model) {
    char name[8];
    f32 d[3];
    f32 m1[12];
    f32 m2[12];
    SnArgs a;
    SnArgs b;
    f32 dt;
    s32 i;

    dt = 0.033333335f;
    if (D_main_bss_80130B39 == 0) {
        a.scale[0] = *(f32 *)(*(u8 **)(npc + 0x34) + 0x28) * 100.0f;
        a.scale[1] = *(f32 *)(*(u8 **)(npc + 0x34) + 0x28) * 100.0f;
        a.scale[2] = *(f32 *)(*(u8 **)(npc + 0x34) + 0x28) * 100.0f;
        a.ctx = *(u16 *)(*(u8 **)(npc + 0x38) + 0x198);
    } else {
        a.ctx = 0xFFFF;
        a.name = (void *)model;
        a.scale[0] = 5.0f;
        a.scale[1] = 5.0f;
        a.scale[2] = 5.0f;
    }
    for (i = 0; i < 4; i++) {
        name[0] = '0';
        name[1] = i + '1';
        name[2] = 0;
        lookupHmtTextureByName(D_main_bss_80130B39 ? model : *(s32 *)(npc + 0x30), name, 0, &a, 0, 0);
        a.idx = i;
        a.m.m[6] = -a.m.m[6];
        a.m.m[7] = -a.m.m[7];
        a.m.m[8] = -a.m.m[8];
        if (D_main_bss_80130B39 == 0) {
            ((SnNpc *)npc)->hFC[i] = spawnNpcOfType(snVortex, &a, 4, snGetCtx(*(u16 *)(*(u8 **)(npc + 0x38) + 0x198))[0x19] + 1);
            slotDispatcherIter(((SnNpc *)npc)->hFC[i], 3, &dt);
            ((SnNpc *)npc)->h104[i] = 0xFFFF;
        } else {
            slotDispatcherIter(spawnNpcOfType(snVortex, &a, 4, 0x56), 3, &dt);
        }
        if (D_main_bss_80130B39 == 0) {
            a.m.m[1] -= a.scale[1] * 0.25f;
            ((SnNpc *)npc)->h114[i] = spawnInheritedNpcVariantB(*(u16 *)(*(u8 **)(npc + 0x38) + 0x198), &a);
            mat34CrossRowsAndCopyPos(m1, npc, 1.0f);
            m1[9] = m1[10] = m1[11] = 0.0f;
            mat3x3InverseInto(m2, m1);
            d[0] = a.m.m[0] - ((f32 *)npc)[0];
            d[1] = a.m.m[1] - ((f32 *)npc)[1];
            d[2] = a.m.m[2] - ((f32 *)npc)[2];
            transformVec3ByMat34(m2, d, (f32 *)&npc[i * 12 + 0xA8]);
            b.scale[0] = *(f32 *)(*(u8 **)(npc + 0x34) + 0x28) * 100.0f;
            b.scale[1] = *(f32 *)(*(u8 **)(npc + 0x34) + 0x2C) * 100.0f;
            b.scale[2] = *(f32 *)(*(u8 **)(npc + 0x34) + 0x30) * 100.0f;
            b.ctx = *(u16 *)(*(u8 **)(npc + 0x38) + 0x198);
            b.name = name;
            sprintf(name, "wshld%d", i + 1);
            b.m = a.m;
            b.m.m[1] += b.scale[1] * 0.08f;
            ((SnNpc *)npc)->h10C[i] = spawnNpcOfType(snHeavy, &b, 4, snGetCtx(*(u16 *)(*(u8 **)(npc + 0x38) + 0x198))[0x19] + 1);
            slotDispatcherIter(((SnNpc *)npc)->h10C[i], 3, &dt);
            ((SnNpc *)npc)->h11C[i] = 0xFFFF;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/main/7CEA0", D_main_8003D708);

typedef struct { f32 x, y, z; } NqV3;
f32 sinf(f32);

void npcQuatOrientedMultiPhaseUpdate(u8 *npc, f32 dt) {
    f32 m[12];
    f32 qt[4];
    NqV3 tmp;
    NqV3 a;
    NqV3 b;
    register f32 *q asm("$16");
    f32 x;
    f32 ang;
    u8 v;

    mat34CrossRowsAndCopyPos((void *)m, (void *)npc, 1.0f);
    switch (*(s16 *)(npc + 0xFA)) {
    case 0:
        break;
    case 1:
        npc[0xD8] = npc[0xF9];
        v = npc[0xF9];
        if (v & 5) {
            if (v & 1) {
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xB4), (f32 *)&a);
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xCC), (f32 *)&b);
            } else {
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xB4), (f32 *)&b);
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xCC), (f32 *)&a);
            }
        } else {
            if (v & 2) {
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xA8), (f32 *)&b);
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xC0), (f32 *)&a);
            } else {
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xA8), (f32 *)&a);
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xC0), (f32 *)&b);
            }
        }
        *(f32 *)(npc + 0x90) = b.x - a.x;
        *(f32 *)(npc + 0x94) = b.y - a.y;
        *(f32 *)(npc + 0x98) = b.z - a.z;
        *(f32 *)(npc + 0x60) += dt * *(f32 *)(npc + 0x64);
        if (*(f32 *)(npc + 0x60) > 0.5f) {
            *(f32 *)(npc + 0x60) = 0.5f;
        }
        q = (f32 *)(npc + 0x70);
        *(f32 *)(npc + 0x5C) = sinf(*(f32 *)(npc + 0x60) * 3.1415927f) * *(f32 *)(npc + 0x68);
        quatFromAxisAngleSafe(q, (f32 *)(npc + 0x90), *(f32 *)(npc + 0x5C));
        rotateVec3ByQuat(q, (f32 *)(npc + 0xC), (f32 *)&tmp);
        *(NqV3 *)(npc + 0xC) = tmp;
        rotateVec3ByQuat(q, (f32 *)(npc + 0x18), (f32 *)&tmp);
        *(NqV3 *)(npc + 0x18) = tmp;
        break;
    case 2:
        switch (npc[0xF9]) {
        case 3:
            transformVec3ByMat34((void *)m, (f32 *)(npc + 0xA8), (f32 *)&b);
            transformVec3ByMat34((void *)m, (f32 *)(npc + 0xB4), (f32 *)&a);
            npc[0xD9] = 1;
            break;
        case 12:
            transformVec3ByMat34((void *)m, (f32 *)(npc + 0xA8), (f32 *)&a);
            transformVec3ByMat34((void *)m, (f32 *)(npc + 0xB4), (f32 *)&b);
            npc[0xD9] = 1;
            break;
        case 6:
            transformVec3ByMat34((void *)m, (f32 *)(npc + 0xB4), (f32 *)&a);
            transformVec3ByMat34((void *)m, (f32 *)(npc + 0xC0), (f32 *)&b);
            npc[0xD9] = 1;
            break;
        case 9:
            transformVec3ByMat34((void *)m, (f32 *)(npc + 0xB4), (f32 *)&b);
            transformVec3ByMat34((void *)m, (f32 *)(npc + 0xC0), (f32 *)&a);
            npc[0xD9] = 1;
            break;
        case 5:
            if (npc[0xD8] & 1) {
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xA8), (f32 *)&a);
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xC0), (f32 *)&b);
            } else {
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xA8), (f32 *)&b);
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xC0), (f32 *)&a);
            }
            break;
        case 10:
            if (npc[0xD8] & 2) {
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xB4), (f32 *)&b);
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xCC), (f32 *)&a);
            } else {
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xB4), (f32 *)&a);
                transformVec3ByMat34((void *)m, (f32 *)(npc + 0xCC), (f32 *)&b);
            }
            break;
        }
        *(f32 *)(npc + 0x90) = b.x - a.x;
        *(f32 *)(npc + 0x94) = b.y - a.y;
        *(f32 *)(npc + 0x98) = b.z - a.z;
        *(f32 *)(npc + 0x60) += dt * *(f32 *)(npc + 0x64);
        if (*(f32 *)(npc + 0x60) > 0.5f) {
            if (npc[0xD9] != 0) {
                *(f32 *)(npc + 0x60) = 0.5f;
            } else {
                *(f32 *)(npc + 0x60) -= 2.0f;
            }
        }
        ang = sinf(*(f32 *)(npc + 0x60) * 3.1415927f) * *(f32 *)(npc + 0x68);
        *(f32 *)(npc + 0x5C) = ang;
        *(f32 *)(npc + 0x6C) += dt * *(f32 *)(npc + 0x64);
        if (*(f32 *)(npc + 0x6C) < 1.0f) {
            q = (f32 *)(npc + 0x80);
            quatFromAxisAngleSafe(q, (f32 *)(npc + 0x90), ang);
            slerpQuaternions((f32 *)(npc + 0x70), q, *(f32 *)(npc + 0x6C), qt);
            q = qt;
        } else {
            q = (f32 *)(npc + 0x70);
            quatFromAxisAngleSafe(q, (f32 *)(npc + 0x90), *(f32 *)(npc + 0x5C));
        }
        rotateVec3ByQuat(q, (f32 *)(npc + 0xC), (f32 *)&tmp);
        *(NqV3 *)(npc + 0xC) = tmp;
        rotateVec3ByQuat(q, (f32 *)(npc + 0x18), (f32 *)&tmp);
        *(NqV3 *)(npc + 0x18) = tmp;
        break;
    case 3:
    case 4:
        npc[0xD9] = 1;
        *(f32 *)(npc + 0x60) += dt * *(f32 *)(npc + 0x64);
        if (*(f32 *)(npc + 0x60) > 0.5f) {
            *(f32 *)(npc + 0x60) = 0.5f;
        }
        ang = sinf(*(f32 *)(npc + 0x60) * 3.1415927f) * *(f32 *)(npc + 0x68);
        *(f32 *)(npc + 0x5C) = ang;
        *(f32 *)(npc + 0x6C) += dt * *(f32 *)(npc + 0x64);
        if (*(f32 *)(npc + 0x6C) < 1.0f) {
            q = (f32 *)(npc + 0x80);
            quatFromAxisAngleSafe(q, (f32 *)(npc + 0x90), ang);
            slerpQuaternions((f32 *)(npc + 0x70), q, *(f32 *)(npc + 0x6C), qt);
            q = qt;
        } else {
            q = (f32 *)(npc + 0x70);
            quatFromAxisAngleSafe(q, (f32 *)(npc + 0x90), *(f32 *)(npc + 0x5C));
        }
        rotateVec3ByQuat(q, (f32 *)(npc + 0xC), (f32 *)&tmp);
        *(NqV3 *)(npc + 0xC) = tmp;
        rotateVec3ByQuat(q, (f32 *)(npc + 0x18), (f32 *)&tmp);
        *(NqV3 *)(npc + 0x18) = tmp;
        orthonormalizeFrame((void *)npc);
        break;
    }
}

typedef struct { s32 x, y, z; } SpV3;
typedef struct {
    f32 f0;
    SpV3 v4;
    f32 f10, f14, f18, f1C;
    s32 w20, w24;
    f32 f28, f2C;
    s32 w30, w34;
    f32 f38;
    s16 h3C, h3E;
    f32 f40, f44, f48, f4C, f50, f54, f58, f5C;
    s32 w60;
    s32 w64;
    void *w68;
    u8 b6C, b6D;
    u8 pad6E[2];
    s16 h70, h72, h74, h76;
    s32 w78;
    u16 h7C;
} SparkCtx;
extern s32 D_main_bss_80130C08;
extern u8 D_main_bss_801398C0[];
extern u8 D_main_bss_80139920[];
extern u8 D_main_bss_80138058[];
extern s32 isTerrainCellBlockedAtWorldXz(f32, f32, void *);
extern s32 spawnRandomBurstNpcVariantWrapper(void *);

void emitPresetSparkBurst(f32 *arg0) {
    SparkCtx c;
    u8 *p;
    f32 a = 10.0f;
    f32 d = 15.0f;

    c.f0 = 5.0f;
    c.v4 = *(SpV3 *)arg0;
    c.f10 = 0.0f;
    c.f14 = -3.0f;
    c.f18 = 0.0f;
    c.f1C = 0.0f;
    c.w20 = 0;
    c.w24 = 0;
    c.f28 = 1.0f;
    c.f2C = 1.0f;
    c.w30 = 0;
    c.w34 = 0;
    c.f38 = 0.1f;
    c.h3C = 0;
    c.h3E = 0;
    c.f40 = 2.0f;
    c.f44 = 0.0f;
    c.f48 = 0.0f;
    c.f4C = 3.0f;
    c.f50 = 0.0f;
    c.f54 = 0.8f;
    c.w64 = D_main_bss_80130C08 + 0x1C;
    c.f58 = 1.0f;
    c.f5C = 0.0f;
    c.b6C = 1;
    if (isTerrainCellBlockedAtWorldXz(arg0[0], arg0[2], D_main_bss_80138058) == 0) {
        p = D_main_bss_80139920;
    } else {
        p = D_main_bss_801398C0;
    }
    c.w68 = p;
    c.b6D = 0x10;
    c.h70 = (u32)(a * 256.0f);
    c.h72 = (u32)(d * 256.0f);
    c.h74 = 4;
    c.w78 = 0x09000000;
    c.h7C = 1;
    spawnRandomBurstNpcVariantWrapper(&c);
}

extern void computeWalkerLimbStrideTargets(u16, f32 *, f32 *, f32 *, f32);
extern void emitPresetSparkBurst(f32 *);
extern f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
extern u8 D_main_bss_80138058[];

void updateWalkerLegStrideAndDust(u8 *arg0) {
    f32 a[3];
    f32 b[3];
    f32 c[3];
    f32 p[3];
    s32 i;
    f32 t;

    computeWalkerLimbStrideTargets(*(u16 *)(*(u8 **)(arg0 + 0x38) + 0x198), a, b, c, 1.05f);
    i = 0;
    do {
        t = i;
        p[0] = a[0] + (b[0] / 3.0f) * t;
        p[2] = a[2] + (b[2] / 3.0f) * t;
        p[1] = wrapAngleToCyclicRange(p[0], p[2], D_main_bss_80138058, 0);
        emitPresetSparkBurst(p);
        i++;
        p[0] = a[0] + c[0] + (b[0] / 3.0f) * t;
        p[2] = a[2] + c[2] + (b[2] / 3.0f) * t;
        p[1] = wrapAngleToCyclicRange(p[0], p[2], D_main_bss_80138058, 0);
        emitPresetSparkBurst(p);
    } while (i < 3);
    i = 1;
    do {
        t = i;
        p[0] = a[0] + (c[0] / 5.0f) * t;
        p[2] = a[2] + (c[2] / 5.0f) * t;
        p[1] = wrapAngleToCyclicRange(p[0], p[2], D_main_bss_80138058, 0);
        emitPresetSparkBurst(p);
        i++;
        p[0] = a[0] + b[0] + (c[0] / 5.0f) * t;
        p[2] = a[2] + b[2] + (c[2] / 5.0f) * t;
        p[1] = wrapAngleToCyclicRange(p[0], p[2], D_main_bss_80138058, 0);
        emitPresetSparkBurst(p);
    } while (i < 4);
}

void zmemcpy(u8 *, u8 *, u32);
extern void destroyNpcSlotByIndex(u16);
s32 slotDispatcherIter(s32, s32, void *);
extern void updateWalkerLegStrideAndDust(u8 *);
extern f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
extern u8 D_main_bss_80138058[];

void play3DSoundEventF(s32, void *, void *, f32, f32, s32, s32, s32, s32) __asm__("play3DSoundEvent");

typedef struct { f32 x, y, z; u8 pad0C[0x18]; f32 vx, vy, vz; } WalkerPhys;

void npcWalkerUpdate(u8 *arg0, f32 dt) {
    struct { u16 h[4]; s32 w; } ev;
    WalkerPhys *w = (WalkerPhys *)arg0;
    s32 i;
    f32 h;

    zmemcpy(arg0, arg0 + 0x1F8, 0x30);
    w->vy += dt * 0.7f;
    w->x += w->vx * dt;
    w->y += w->vy * dt;
    w->z += w->vz * dt;
    h = wrapAngleToCyclicRange(w->x, w->z, D_main_bss_80138058, 0);
    if (h <= *(f32 *)(arg0 + 0x4)) {
        *(f32 *)(arg0 + 0x4) = h;
        *(s16 *)(arg0 + 0x1B2) = 3;
        *(f32 *)(arg0 + 0x44) = *(f32 *)(arg0 + 0x40);
        *(f32 *)(arg0 + 0x48) = *(f32 *)(arg0 + 0x40) * 0.9f;
        for (i = 0; i < 4; i++) {
            if (((u16 *)(arg0 + 0x114))[i] != 0xFFFF) {
                destroyNpcSlotByIndex(((u16 *)(arg0 + 0x114))[i]);
                ((u16 *)(arg0 + 0x114))[i] = 0xFFFF;
            }
        }
        ev.h[0] = 0xFFFF;
        ev.h[1] = 0xFFFF;
        ev.h[2] = 7;
        ev.h[3] = 0xFFFF;
        ev.w = 0;
        for (i = 0; i < *(s16 *)(arg0 + 0x1B4); i++) {
            if (((u16 *)(arg0 + 0x1B6))[i] != 0xFFFF) {
                slotDispatcherIter(((u16 *)(arg0 + 0x1B6))[i], 5, &ev);
                ((u16 *)(arg0 + 0x1B6))[i] = 0xFFFF;
            }
        }
        updateWalkerLegStrideAndDust(arg0);
        { union { s32 i; f32 f; } u; u.i = 0x41C80000;
        play3DSoundEventF(0, arg0, arg0 + 0x24, u.f, 0.8f, 0, 0x75, 0x7F, 0x64);
        play3DSoundEventF(0, arg0, arg0 + 0x24, u.f, 0.8f, 0, 0x77, 0x7F, 0x64); }
    }
    zmemcpy(arg0 + 0x1F8, arg0, 0x30);
}

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

typedef struct {
    f32 x, y, z;
    f32 f0C, f10, f14, f18, f1C, f20;
    u8 pad24[0xC];
    u8 *mesh;
    f32 f34;
    f32 f38;
    f32 ax[3];
    f32 f48;
} TpState;

typedef struct {
    u8 pad0[4];
    f32 x, y, z;
    u8 pad10[0xC];
    f32 f1C;
    u8 pad20[0x50];
    u16 h70;
    u16 h72;
} TpPt;

typedef struct {
    TpPt *p0;
    TpPt *p1;
    f32 dt;
    s32 *pC;
} TpArg;

s16 rand(void);
u8 *walkMeshdef0List(char *);
void releaseMeshAsset(void *);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
extern void tpQuat(f32 *, f32 *, f32) __asm__("quatFromAxisAngle");
extern void tpRot(f32 *, f32 *, f32 *) __asm__("rotateVec3ByQuat");
extern void tpMat(void *, void *, f32) __asm__("mat34CrossRowsAndCopyPos");
extern f32 tpLen(f32 *) __asm__("vec3Length");
extern void tpNorm(f32 *) __asm__("normalize_vector");

s32 twoPointPositionedNpcHandler(u8 *npc, u16 cmd, TpArg *a) {
    TpState *s = *(TpState **)(npc + 4);
    f32 q[4];
    f32 t;
    f32 dt;

    switch (cmd) {
    case 1:
        s->mesh = walkMeshdef0List("debris1");
        s->x = a->p0->x + a->p1->x;
        s->y = a->p0->y + a->p1->y;
        s->z = a->p0->z + a->p1->z;
        s->f0C = 0.0f;
        s->f10 = 0.0f;
        s->f14 = 1.0f;
        s->f18 = 0.0f;
        s->f1C = 1.0f;
        s->f20 = 0.0f;
        s->f34 = (f32)a->p0->h70 * 0.00390625f * 0.2f;
        t = (f32)a->p0->h72 * 0.00390625f * 0.2f - s->f34;
        if (a->p1->f1C != 0.0f) {
            s->f38 = t / a->p1->f1C;
        } else {
            s->f38 = 0.0f;
        }
        do {
            s->ax[0] = ((f32)(rand() & 0x7F) - 64.0f) * 0.015625f;
            s->ax[1] = ((f32)(rand() & 0x7F) - 64.0f) * 0.015625f;
            s->ax[2] = ((f32)(rand() & 0x7F) - 64.0f) * 0.015625f;
        } while (tpLen(s->ax) == 0.0f);
        tpNorm(s->ax);
        s->f48 = ((f32)(rand() & 0x7F) - 64.0f) / 0.35555556f;
        break;
    case 2:
        releaseMeshAsset(s->mesh);
        break;
    case 4:
        dt = a->dt;
        s->x = a->p0->x + a->p1->x;
        s->y = a->p0->y + a->p1->y;
        s->z = a->p0->z + a->p1->z;
        tpQuat(q, s->ax, s->f48 * dt);
        tpRot(q, &s->f0C, &s->f0C);
        tpRot(q, &s->f18, &s->f18);
        t = s->f34 + s->f38 * dt;
        if (t != 0.0f) {
            tpMat(s->mesh + 0x28, s, t);
            addNpcToVisibilityBucket(*a->pC, s->mesh, s, 1.0f);
        }
        break;
    }
    return 1;
}

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

typedef struct { f32 x, y, z; } AvVec3;
typedef struct { s32 w[12]; } AvBlk;
typedef struct {
    AvVec3 pos;
    AvVec3 fwd;
    AvVec3 up;
    AvVec3 vel;
    u8 *mesh;
    u8 *rec;
    s32 obj;
    u8 *n[3];
    u8 *m[3];
    f32 mat[12];
    f32 scale;
    f32 radius;
    f32 f8C;
    f32 f90;
    f32 f94;
    f32 f98;
    f32 f9C;
    f32 fA0;
    s16 type;
    u16 link;
    u16 slotA8;
    u16 slotAA;
    s16 state;
    s16 padAE;
    f32 timer;
    s16 count;
} AvObj;
typedef struct { u16 id; s16 zero; u8 pad4[0x14]; u8 type; } AvMsg;
extern u16 D_main_bss_80139560[];
extern u16 D_main_bss_80139574;
s16 rand(void);
u8 *walkMeshdef0List(char *);
u16 popNpcSlotFromTail(u16, void *);
u8 *lookupHmtMaterialByName(void *, char *, void *);
void createAndInitObject(void *, s32, void *, void *, s32);
u8 *getNpcContextField8(u16);
void clearPendingAndDestroyChildNpc(void *);
void releaseMeshAsset(void *);
s32 func_mission_overlay_800EFDE0(s32, s32, s32, f32);
void aimOrientNpcTowardTarget(void *, f32);
s32 isPendingChildNpcActive(s32);
s32 validateActorTargetLOS(s32);
void applyToObjectSubstructByFlag(s32, f32, s32, f32);
void destroyObjectOwnedNpcSlot(s32);
void spawnNpcType0xAFromTemplate(void *, f32);
void destroyNpcSlotByIndex(u16);
void spawnRandomScaleEffectDefault(void *);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
s32 getNpcCurrentHealth(s32);
void extrapolateNpcPositionForCurrentMode(void *);
s32 dealDamageToNpc(s32, s32);
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void clearPendingChildNpc(s32);
void setObjectFlagBit4(void *);
s32 slotDispatcherIter(s32, s32, void *);
void dispatchSlotAction5IfActive(void *, void *);
#define AVABSF(x) ({ f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(x)); _r; })
#define AV_JOINT_HEAD(k) \
    m = s2->m[k]; \
    n = s2->n[k] + 0x1C; \
    clearVec4QuadStruct(n); \
    if (*(s32 *)(m + 0x4C) & 1) { \
        addVec3At0x24(n, -*(f32 *)(m + 0x50), -*(f32 *)(m + 0x54), -*(f32 *)(m + 0x58)); \
    } \
    if (*(s32 *)(m + 0x4C) & 2) { \
        applyScaleToMat3x4(n, *(f32 *)(m + 0x5C), *(f32 *)(m + 0x60), *(f32 *)(m + 0x64)); \
    } \
    if (*(s32 *)(m + 0x4C) & 4) { \
        composeQuatToMat3x4(n, m + 0x68); \
    }
#define AV_JOINT_TAIL() \
    { s32 fl = *(s32 *)(m + 0x4C); \
    if ((fl & 9) == 9) { \
        addVec3At0x24(n, *(f32 *)(m + 0x78) + *(f32 *)(m + 0x50), *(f32 *)(m + 0x7C) + *(f32 *)(m + 0x54), *(f32 *)(m + 0x80) + *(f32 *)(m + 0x58)); \
    } else if ((fl & 9) == 8) { \
        addVec3At0x24(n, *(f32 *)(m + 0x78), *(f32 *)(m + 0x7C), *(f32 *)(m + 0x80)); \
    } else if (fl & 1) { \
        addVec3At0x24(n, *(f32 *)(m + 0x50), *(f32 *)(m + 0x54), *(f32 *)(m + 0x58)); \
    } }

static __inline__ void avRotateSaved(AvObj *o, f32 *sp) {
    f32 rm[12];
    buildRotationMatrixSlot0(rm, o->f90);
    composeRotationMatrixSlot1(rm, o->f8C);
    transformVec3ByMat34(rm, &sp[67], &o->fwd);
    transformVec3ByMat34(rm, &sp[70], &o->up);
}

s32 attachedAudioVisualEmitterNpcHandler(u8 *arg0, u16 action, u8 *arg2) {
    AvObj *s2 = *(AvObj **)(arg0 + 4);
    f32 sp[76];
    f32 dt;

    switch (action) {
    case 1:
        {
            u8 *a1c = arg2;
            char *name = NULL;
            s2->rec = *(u8 **)arg2;
            switch (*(s16 *)(arg2 + 0x3A)) {
            case 0:
                name = "tpt";
                break;
            case 1:
                name = "btg";
                break;
            case 2:
                name = "sdh";
                break;
            case 3:
                name = "spt";
                break;
            case 4:
                name = "btm";
                break;
            }
            s2->mesh = walkMeshdef0List(name);
            s2->type = *(s16 *)(a1c + 0x3A);
            *(AvBlk *)s2 = *(AvBlk *)(a1c + 4);
            s2->vel.x = s2->vel.y = s2->vel.z = 0.0f;
            {
                f32 sc = (1.0f / *(f32 *)(*(u8 **)s2->mesh + 0x34)) * *(f32 *)(a1c + 0x34);
                s2->scale = sc;
                mat34CrossRowsAndCopyPos(s2->mesh + 0x28, s2, sc);
            }
            *(AvObj **)(arg0 + 8) = s2;
            *(u8 **)(arg0 + 0xC) = s2->mesh;
            {
                u8 *b = (u8 *)D_main_bss_80139560;
                s2->slotA8 = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
                s2->slotAA = popNpcSlotFromTail(D_main_bss_80139560[0xC / 2], arg0);
            }
            {
                struct D_main_800A0D9C_type *t = D_main_800A0D9C;
                s2->n[0] = lookupHmtMaterialByName(s2->mesh, t[s2->type].unk00[0], &s2->m[0]);
                s2->n[1] = lookupHmtMaterialByName(s2->mesh, t[s2->type].unk00[1], &s2->m[1]);
                s2->n[2] = lookupHmtMaterialByName(s2->mesh, t[s2->type].unk00[2], &s2->m[2]);
            }
            s2->f8C = 0.0f;
            s2->f90 = 0.0f;
            s2->radius = *(f32 *)(*(u8 **)s2->mesh + 0x44) * s2->scale;
            createAndInitObject(&s2->obj, 0, arg0, initNpcTexturedEffectFromTemplate, 0);
            s2->link = *(u16 *)(a1c + 0x38);
            {
                u8 *p = getNpcContextField8(*(u16 *)(a1c + 0x38));
                mat34CrossRowsAndCopyPos(sp, p, 1.0f);
                sp[11] = 0.0f;
                sp[10] = 0.0f;
                sp[9] = 0.0f;
                mat3x3InverseInto(&sp[12], sp);
                sp[24] = s2->pos.x - *(f32 *)(p + 0);
                sp[25] = s2->pos.y - *(f32 *)(p + 4);
                sp[26] = s2->pos.z - *(f32 *)(p + 8);
                transformVec3ByMat34(&sp[12], &sp[24], &sp[28]);
                transformVec3ByMat34(&sp[12], &s2->fwd, &sp[31]);
                transformVec3ByMat34(&sp[12], &s2->up, &sp[34]);
                mat34CrossRowsAndCopyPos(s2->mat, &sp[28], 1.0f);
            }
            return 1;
        }
    case 2:
        clearPendingAndDestroyChildNpc(&s2->obj);
        releaseMeshAsset(s2->mesh);
        return 1;
    case 3:
        {
            u8 *p;
            dt = *(f32 *)arg2;
            p = getNpcContextField8(s2->link);
            mat34CrossRowsAndCopyPos(&sp[40], p, 1.0f);
            mat3x4Multiply(&sp[40], s2->mat, &sp[52]);
            extractOrthonormalFrameFromStruct(s2, &sp[52]);
            s2->vel = *(AvVec3 *)(p + 0x24);
            switch (s2->state) {
            case 0:
                {
                f32 inc = dt * 4.0f;
                if (s2->f98 < 1.0f) {
                    s2->f98 += inc;
                    if (1.0f < s2->f98) {
                        s2->f98 = 1.0f;
                        s2->f9C = 0.0f;
                    } else if (s2->f98 < 0.2f) {
                        s2->f9C = s2->f98 * 5.0f;
                    } else {
                        s2->f9C = 1.0f - (s2->f98 - 0.2f) * 1.25f;
                    }
                }
                {
                    register s32 hit asm("$16") = 0;
                    func_mission_overlay_800EFDE0(s2->obj, *(s32 *)(s2->rec + 0x7C), *(s32 *)(s2->rec + 0x80), dt);
                    aimOrientNpcTowardTarget(s2, dt);
                    if ((u8)isPendingChildNpcActive(s2->obj) == 1) {
                        *(AvBlk *)&sp[64] = *(AvBlk *)s2;
                        avRotateSaved(s2, sp);
                        if ((u8)validateActorTargetLOS(s2->obj) == 1) {
                            hit = 1;
                        }
                        *(AvBlk *)s2 = *(AvBlk *)&sp[64];
                    }
                    if (hit == 1) {
                        applyToObjectSubstructByFlag(s2->obj, dt, 0, 0.0f);
                    }
                }
                }
                break;
            case 1:
                {
                f32 inc = dt * 4.0f;
                if (s2->f98 < 1.0f) {
                    s2->f98 += inc;
                    if (1.0f < s2->f98) {
                        s2->f98 = 1.0f;
                        s2->f9C = 0.0f;
                    } else if (s2->f98 < 0.2f) {
                        s2->f9C = s2->f98 * 5.0f;
                    } else {
                        s2->f9C = 1.0f - (s2->f98 - 0.2f) * 1.25f;
                    }
                }
                s2->timer -= dt;
                if (s2->timer <= 0.0f) {
                    if (--s2->count <= 0) {
                        spawnNpcType0xAFromTemplate(s2, s2->radius * 5.0f);
                        play3DSoundEvent(0, s2, &s2->vel, 24.0f, 0.6f, 0, 0x22, 0x7D, 0x50);
                        destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                        return 1;
                    }
                    s2->timer = (s16)(rand() % 3) * 0.033333335f;
                    play3DSoundEvent(0, s2, &s2->vel, 24.0f, 0.4f, 0, 0x2A, 0x7E, 0x3C);
                    sp[64] = s2->pos.x + ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / (s2->radius * 0.5f));
                    sp[65] = s2->pos.y - AVABSF(((f32)(rand() & 0x7F) - 64.0f) / (64.0f / (s2->radius * 0.5f)));
                    sp[66] = s2->pos.z + ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / (s2->radius * 0.5f));
                    spawnRandomScaleEffectDefault(&sp[64]);
                }
                }
                break;
            }
            destroyObjectOwnedNpcSlot(s2->obj);
            return 1;
        }
    case 4:
        {
            u8 *a4 = arg2;
            u8 *m;
            u8 *n;
            mat34CrossRowsAndCopyPos(s2->mesh + 0x28, s2, s2->scale);
            switch (s2->type) {
            default:
                AV_JOINT_HEAD(0)
                composeRotationMatrixSlot1(n, s2->f8C);
                AV_JOINT_TAIL()
                AV_JOINT_HEAD(1)
                composeRotationMatrixSlot0(n, s2->f90);
                AV_JOINT_TAIL()
                AV_JOINT_HEAD(2)
                addVec3At0x24(n, 0.0f, 0.0f, s2->f9C * D_main_800A0D9C[s2->type].block_o_floats[11]);
                AV_JOINT_TAIL()
                break;
            case 4:
                AV_JOINT_HEAD(0)
                composeRotationMatrixSlot1(n, s2->f8C);
                AV_JOINT_TAIL()
                AV_JOINT_HEAD(1)
                composeRotationMatrixSlot0(n, s2->f90);
                AV_JOINT_TAIL()
                AV_JOINT_HEAD(2)
                composeRotationMatrixSlot0(n, s2->f90);
                AV_JOINT_TAIL()
                break;
            case 2:
                AV_JOINT_HEAD(1)
                composeRotationMatrixSlot0(n, s2->f90);
                composeRotationMatrixSlot1(n, s2->f8C);
                AV_JOINT_TAIL()
                AV_JOINT_HEAD(2)
                addVec3At0x24(n, 0.0f, 0.0f, s2->f9C * D_main_800A0D9C[s2->type].block_o_floats[11]);
                AV_JOINT_TAIL()
                break;
            }
            addNpcToVisibilityBucket(*(s32 *)a4, s2->mesh, s2, s2->radius);
            return 1;
        }
    case 5:
        {
            u8 *a5 = arg2;
            if (getNpcCurrentHealth(s2->obj) > 0) {
                extrapolateNpcPositionForCurrentMode(arg2);
                play3DSoundEvent(0, s2, &s2->vel, 24.0f, 0.4f, 0, 0x2A, 0x7E, 0x3C);
                if (dealDamageToNpc(s2->obj, *(u16 *)(arg2 + 6)) <= 0) {
                    s2->state = 1;
                    s2->count = 3;
                    s2->timer = 0.0f;
                    unregisterAndFreeNpcSlot(s2->slotA8, arg0);
                    unregisterAndFreeNpcSlot(s2->slotAA, arg0);
                    popNpcSlotFromTail(D_main_bss_80139574, arg0);
                    {
                        u8 *r = s2->rec;
                        datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x6C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x64), *(s32 *)(r + 0x68), *(s32 *)(r + 0x74), *(s32 *)(s2->rec + 0x78));
                    }
                    clearPendingChildNpc(s2->obj);
                    setObjectFlagBit4(arg0);
                    ((AvMsg *)&sp[64])->type = 0xF;
                    ((AvMsg *)&sp[64])->id = *(u16 *)(arg0 + 0x16);
                    ((AvMsg *)&sp[64])->zero = 0;
                    slotDispatcherIter(s2->link, 9, &sp[64]);
                }
            }
            if (*(u16 *)a5 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)a5);
                return 1;
            }
            return 1;
        }
    case 7:
        dispatchSlotAction5IfActive(arg0, arg2);
        break;
    }
    return 1;
}

typedef struct {
    AvVec3 pos;
    AvVec3 fwd;
    AvVec3 up;
    AvVec3 vel;
    u8 *mesh;
    s32 obj;
    f32 radius;
    f32 scale;
    f32 mat[12];
    u16 link;
    u16 pad72[3];
    u16 slot78;
    u16 slot7A;
    s16 state;
    u16 pad7E;
    u8 audio[0x44];
    u8 flagC4;
} SgObj;
void npcSpawnInitMarkActive(u8 *, s32, u8 *);
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
void factor5RemoveListNode(void *);
void updateActive3DAudioSource(void *, void *, void *, s32);
void composeRandomRotationMatrix(f32 *, f32 *, f32, s32, s32, s32);
void scaleVec3ByRandomRange(f32 *, f32, f32);
void spawnDebris1Npc(f32 *, f32 *, f32, f32, f32);
void distanceAndDopplerNpcHelper(f32 *, f32, f32);
void spawnOrientedNpc(s32, void *, s32, s32, f32, f32, f32, f32);

s32 npcShieldGeneratorUpdate(u8 *arg0, u16 action, u8 *arg2) {
    SgObj *s2 = *(SgObj **)(arg0 + 4);
    f32 sp[80];

    switch (action) {
    case 1:
        {
            u8 *a1c = arg2;
            s2->mesh = walkMeshdef0List("shldgen");
            *(AvBlk *)s2 = *(AvBlk *)a1c;
            s2->vel.x = s2->vel.y = s2->vel.z = 0.0f;
            {
                f32 sc = (1.0f / *(f32 *)(*(u8 **)s2->mesh + 0x34)) * *(f32 *)(a1c + 0x30);
                s2->scale = sc;
                mat34CrossRowsAndCopyPos(s2->mesh + 0x28, s2, sc);
            }
            *(SgObj **)(arg0 + 8) = s2;
            *(u8 **)(arg0 + 0xC) = s2->mesh;
            {
                u8 *b = (u8 *)D_main_bss_80139560;
                s2->slot78 = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
                s2->slot7A = popNpcSlotFromTail(D_main_bss_80139560[0xC / 2], arg0);
            }
            s2->radius = *(f32 *)(*(u8 **)s2->mesh + 0x44) * s2->scale;
            createAndInitObject(&s2->obj, 0, arg0, npcSpawnInitMarkActive, (s32)a1c);
            s2->link = *(u16 *)(a1c + 0x44);
            {
                u8 *p = getNpcContextField8(*(u16 *)(a1c + 0x44));
                mat34CrossRowsAndCopyPos(sp, p, 1.0f);
                sp[11] = 0.0f;
                sp[10] = 0.0f;
                sp[9] = 0.0f;
                mat3x3InverseInto(&sp[12], sp);
                sp[24] = s2->pos.x - *(f32 *)(p + 0);
                sp[25] = s2->pos.y - *(f32 *)(p + 4);
                sp[26] = s2->pos.z - *(f32 *)(p + 8);
                transformVec3ByMat34(&sp[12], &sp[24], &sp[28]);
                transformVec3ByMat34(&sp[12], &s2->fwd, &sp[31]);
                transformVec3ByMat34(&sp[12], &s2->up, &sp[34]);
                mat34CrossRowsAndCopyPos(s2->mat, &sp[28], 1.0f);
            }
            s2->flagC4 = 1;
            play3DSoundEventVariant(s2->audio, s2, &s2->vel, 18.0f, 0.6f, 7, 0x66, 1, 0x7D, 0x50);
            return 1;
        }
    case 2:
        if (s2->flagC4 == 1) {
            factor5RemoveListNode(s2->audio);
        }
        clearPendingAndDestroyChildNpc(&s2->obj);
        releaseMeshAsset(s2->mesh);
        return 1;
    case 3:
        {
            u8 *p = getNpcContextField8(s2->link);
            mat34CrossRowsAndCopyPos(&sp[40], p, 1.0f);
            mat3x4Multiply(&sp[40], s2->mat, &sp[52]);
            extractOrthonormalFrameFromStruct(s2, &sp[52]);
            s2->vel = *(AvVec3 *)(p + 0x24);
            switch (s2->state) {
            case 0:
                break;
            case 1:
                {
                    s32 i;
                    s32 n = (s16)(rand() % 3) + 7;
                    for (i = 0; i < n; i++) {
                        f32 a;
                        f32 b;
                        f32 c;
                        composeRandomRotationMatrix(&sp[64], &sp[68], s2->radius / 3.0f, 0x3C, 0, 0);
                        sp[64] += s2->pos.x;
                        sp[65] += s2->pos.y;
                        sp[66] += s2->pos.z;
                        scaleVec3ByRandomRange(&sp[68], 1.5f, 3.0f);
                        a = AVABSF(((f32)(rand() & 0x7F) - 64.0f) / 12.8f) + 12.0f;
                        b = AVABSF(((f32)(rand() & 0x7F) - 64.0f) * 0.015625f) + 1.5f;
                        c = AVABSF(((f32)(rand() & 0x7F) - 64.0f) / 320.0f) + 0.2f;
                        spawnDebris1Npc(&sp[64], &sp[68], a, b, c);
                        distanceAndDopplerNpcHelper(&sp[64], 0.1f, 2.0f);
                    }
                    spawnOrientedNpc(2, s2, 0, 0, s2->scale * 25.0f, s2->scale * 30.0f, 1.0f, 1.0f);
                    spawnOrientedNpc(3, s2, 0, 0, s2->scale * 22.0f, s2->scale * 34.0f, 1.0f, 0.8f);
                    spawnNpcType0xAFromTemplate(s2, s2->radius * 4.0f);
                    play3DSoundEvent(0, s2, &s2->vel, 24.0f, 0.7f, 0, 0x22, 0x7F, 0x50);
                    destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                    return 1;
                }
            }
            destroyObjectOwnedNpcSlot(s2->obj);
            return 1;
        }
    case 4:
        mat34CrossRowsAndCopyPos(s2->mesh + 0x28, s2, s2->scale);
        addNpcToVisibilityBucket(*(s32 *)arg2, s2->mesh, s2, s2->radius);
        if (s2->flagC4) {
            updateActive3DAudioSource(s2->audio, s2, &s2->vel, 0x7D);
            return 1;
        }
        break;
    case 5:
        {
            u8 *a5 = arg2;
            if (*(u16 *)(arg2 + 4) != 7 || getNpcCurrentHealth(s2->obj) >= 0) {
                extrapolateNpcPositionForCurrentMode(arg2);
                play3DSoundEvent(0, s2, &s2->vel, 20.0f, 0.4f, 0, 0x2A, 0x78, 0x3C);
                if (dealDamageToNpc(s2->obj, *(u16 *)(arg2 + 6)) <= 0) {
                    s2->state = 1;
                    unregisterAndFreeNpcSlot(s2->slot78, arg0);
                    unregisterAndFreeNpcSlot(s2->slot7A, arg0);
                    popNpcSlotFromTail(D_main_bss_80139574, arg0);
                    setObjectFlagBit4(arg0);
                    ((AvMsg *)&sp[72])->type = 0xF;
                    ((AvMsg *)&sp[72])->id = *(u16 *)(arg0 + 0x16);
                    ((AvMsg *)&sp[72])->zero = 1;
                    slotDispatcherIter(s2->link, 9, &sp[72]);
                    if (s2->flagC4 == 1) {
                        factor5RemoveListNode(s2->audio);
                    }
                    s2->flagC4 = 0;
                }
            }
            if (*(u16 *)a5 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)a5);
                return 1;
            }
            return 1;
        }
    case 7:
        dispatchSlotAction5IfActive(arg0, arg2);
        break;
    }
    return 1;
}

typedef struct { s32 w[12]; } VxBlk;
typedef struct { s32 a, b, c; } VxBlk3;
typedef struct {
    f32 pos[3];
    f32 fwd[3];
    f32 up[3];
    f32 vel[3];
    u8 *mesh;
    f32 scale;
    f32 sv[3];
    f32 f44;
    f32 ang;
    u16 link;
    u16 slot4E;
    u16 slot50;
    u16 f52;
    u8 audio[0x44];
    u8 f98;
    u8 f99;
    u16 spray;
    s32 f9C;
} VxObj;
typedef struct { u16 id; s16 zero; u8 pad4[0x14]; u8 type; } VxMsg;
extern u8 D_main_bss_80130B39;
extern f32 D_main_bss_80130BA4;
void *rs_malloc(s32, s32);
void applyFlagsToMeshTreeOrList(void *, s32, s32, s32);
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
u16 spawnWaterSprayNpc(u16, f32 *);
void factor5RemoveListNode(void *);
u8 *getNpcContextByIndex(u16);
f32 floatModulo(f32, f32);
void updateActive3DAudioSource(void *, void *, void *, s32);
void spawnRandomScaleColoredEffectAltVariant(s32, f32);

s32 npcVortexUpdate(u8 *arg0, u16 action, u8 *arg2) {
    VxObj *s1 = *(VxObj **)(arg0 + 4);
    f32 spray[3];
    char buf[4];
    f32 q[4];
    VxMsg msg;
    f32 dt;

    switch (action) {
    case 1:
        {
            u8 *a1c = arg2;
            f32 f;
            s1 = rs_malloc(0xA0, 0);
            *(VxObj **)(arg0 + 4) = s1;
            *(u16 *)(arg0 + 0x14) |= 0x100;
            s1->mesh = walkMeshdef0List("vortex");
            applyFlagsToMeshTreeOrList(s1->mesh, 0, 0x10000, 0);
            *(VxBlk *)s1 = *(VxBlk *)a1c;
            s1->vel[0] = s1->vel[1] = s1->vel[2] = 0.0f;
            f = *(f32 *)(*(u8 **)s1->mesh + 0x34);
            s1->scale = f * *(f32 *)(a1c + 0x30);
            s1->sv[0] = f * *(f32 *)(a1c + 0x30);
            s1->sv[1] = f * *(f32 *)(a1c + 0x34);
            s1->sv[2] = f * *(f32 *)(a1c + 0x38);
            mat34CrossRowsAndCopyPosPtr((void *)(s1->mesh + 0x28), (void *)s1, s1->sv);
            *(VxObj **)(arg0 + 8) = s1;
            *(u8 **)(arg0 + 0xC) = s1->mesh;
            {
                u8 *b = (u8 *)D_main_bss_80139560;
                s1->slot4E = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
                s1->slot50 = popNpcSlotFromTail(D_main_bss_80139560[0xC / 2], arg0);
            }
            s1->f44 = *(f32 *)(*(u8 **)s1->mesh + 0x44) * f * *(f32 *)(a1c + 0x34) * 100.0f;
            s1->f99 = 0;
            s1->link = *(u16 *)(a1c + 0x3C);
            s1->f9C = *(s32 *)(a1c + 0x40);
            s1->f52 = *(u16 *)(a1c + 0x3E);
            s1->f98 = 1;
            s1->ang = 0.0f;
            play3DSoundEventVariant(s1->audio, s1, s1->vel, 10.0f, 0.6f, 0xF, 0x66, 1, 0x78, 0x28);
            spray[0] = s1->scale * 0.9f;
            spray[1] = s1->scale * 0.6f;
            spray[2] = s1->scale * 0.9f;
            s1->spray = spawnWaterSprayNpc(*(u16 *)(arg0 + 0x16), spray);
        }
        break;
    case 2:
        if (s1->f98 == 1) {
            factor5RemoveListNode(s1->audio);
        }
        releaseMeshAsset(s1->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        buf[0] = '0';
        buf[1] = ((u8 *)&s1->f52)[1] + '1';
        buf[2] = 0;
        lookupHmtTextureByName(D_main_bss_80130B39 ? s1->f9C : *(s32 *)(getNpcContextByIndex(s1->link) + 0xC), buf, 0, s1, 0, 0);
        s1->up[0] = -s1->up[0];
        s1->up[1] = -s1->up[1];
        s1->up[2] = -s1->up[2];
        if (!D_main_bss_80130B39) {
            *(VxBlk3 *)s1->vel = *(VxBlk3 *)(getNpcContextField8(s1->link) + 0x24);
        } else {
            s1->vel[0] = 0.0f;
            s1->vel[1] = 0.0f;
            s1->vel[2] = 0.0f;
        }
        s1->ang = floatModulo(s1->ang + 2.0f, 360.0f);
        quatFromAxisAngle(q, s1->up, s1->ang);
        rotateVec3ByQuat(q, s1->fwd, s1->fwd);
        if (s1->f99 == 0) {
            s1->sv[1] = (wrapAngleToCyclicRange(s1->pos[0], s1->pos[2], D_main_bss_80138058, 0) - s1->pos[1] + 0.7f) / s1->scale;
            if (D_main_bss_80130B39) {
                s1->sv[1] *= sinf(D_main_bss_80130BA4 * 3.0f) * 0.3f + 2.5f;
            }
            if (s1->sv[1] <= 0.0f) {
                s1->sv[1] = 0.001f;
            }
        } else {
            if (s1->spray != 0xFFFF) {
                destroyNpcSlotByIndex(s1->spray);
                s1->spray = 0xFFFF;
            }
            s1->sv[1] -= dt * 3.0f;
            if (s1->sv[1] <= 0.0f) {
                if (!D_main_bss_80130B39) {
                    msg.type = 0xF;
                    msg.id = *(u16 *)(arg0 + 0x16);
                    msg.zero = 2;
                    slotDispatcherIter(s1->link, 9, &msg);
                }
                destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                return 1;
            }
        }
        s1->f44 = *(f32 *)(*(u8 **)s1->mesh + 0x44) * s1->sv[1];
        break;
    case 4:
        mat34CrossRowsAndCopyPosPtr((void *)(s1->mesh + 0x28), (void *)s1, s1->sv);
        if (D_main_bss_80130B39) {
            if ((*(u8 **)(s1->mesh + 0xC) = **(u8 ***)arg2) != NULL) {
                *(u8 **)(*(u8 **)(s1->mesh + 0xC) + 4) = s1->mesh + 0xC;
            }
            *(u8 **)(s1->mesh + 0x10) = NULL;
            **(u8 ***)arg2 = s1->mesh + 0xC;
        } else {
            addNpcToVisibilityBucket(*(s32 *)arg2, s1->mesh, s1, 100.0f);
        }
        if (s1->f98) {
            updateActive3DAudioSource(s1->audio, s1, s1->vel, 0x78);
            return 1;
        }
        break;
    case 5:
        if (*(s32 *)(arg2 + 8) != 0) {
            spawnRandomScaleColoredEffectAltVariant(*(s32 *)(arg2 + 8), 0.4f);
        }
        play3DSoundEvent(0, s1, s1->vel, 20.0f, 0.4f, 0, 0x2A, 0x78, 0x50);
        if (*(u16 *)arg2 != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)arg2);
            return 1;
        }
        return 1;
    case 9:
        if (arg2[0x18] == 0x10) {
            s1->f99 = 1;
        }
        break;
    }
    return 1;
}

extern s8 D_main_bss_8013A980;

void clearObjectPoolStateFlag(void) {
    D_main_bss_8013A980 = 0;
}

s32 nsSetHealth(void *, void *, void *) __asm__("setNpcHealth");
void nsSetDetail(void *, s32) __asm__("setObjectDetailLevel");
s16 rand(void);
f32 cosf(f32);
extern s32 D_main_bss_80137CE4;

void npcSpawnInitTimedEffect(u8 *arg0) {
    u8 *s0 = *(u8 **)(arg0 + 4);
    u8 *def;
    register u8 *t asm("$6");
    s32 hp;
    f32 *row;
    f32 v;

    *(s16 *)(s0 + 0x1B2) = 0;
    t = *(u8 **)(s0 + 0x34);
    def = t;
    hp = nsSetHealth(*(void **)(s0 + 0x38), t + 0x6C, t);
    *(s32 *)(s0 + 0xE8) = *(s32 *)(s0 + 0xEC) = *(s32 *)(s0 + 0xF0) = *(s32 *)(s0 + 0xF4) = hp;
    *(u8 *)(s0 + 0xF9) = 0;
    *(s16 *)(s0 + 0xFA) = 0;
    *(u8 *)(s0 + 0xF8) = 1;
    *(f32 *)(s0 + 0x54) = ((f32)(rand() & 0x7F) - 64.0f) / 64.064064f;
    *(f32 *)(s0 + 0x58) = *(f32 *)(def + 0xA8);
    *(s32 *)(s0 + 0x5C) = 0;
    *(s32 *)(s0 + 0x60) = 0;
    *(f32 *)(s0 + 0x64) = 1.0f / *(f32 *)(def + 0xB0);
    v = *(f32 *)(def + 0xAC);
    *(u8 *)(s0 + 0xD8) = 0;
    *(u8 *)(s0 + 0xD9) = 0;
    row = (f32 *)(D_main_bss_80137CE4 * 4 + (s32)def);
    *(s32 *)(s0 + 0x6C) = 0;
    *(s32 *)(s0 + 0x2B8) = 0;
    *(f32 *)(s0 + 0x68) = v;
    { f32 c = cosf(row[0xDC/4] * 0.017453292f);
    s32 i = D_main_bss_80137CE4;
    *(f32 *)(s0 + 0xDC) = c;
    *(f32 *)(s0 + 0xE0) = *(f32 *)(i * 4 + (s32)def + 0xD8);
    *(f32 *)(s0 + 0xE4) = *(f32 *)(i * 4 + (s32)def + 0xE0);
    nsSetDetail(*(void **)(s0 + 0x38), *(s32 *)(*(u8 **)(s0 + 0x34) + 0xB4)); }
}

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
