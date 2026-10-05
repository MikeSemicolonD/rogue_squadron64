#include "common.h"

#include "common_types.h"
#include "mission_overlay/0BAFF0.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BAFF0", playerFalconInit);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BAFF0", computeFalconFlightTransform);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BAFF0", D_mission_overlay_800A5E00);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BAFF0", D_mission_overlay_800A5E04);

typedef struct {
    s32 unk0;
    u8 pad4[0x28 - 4];
    u8 unk28[4];
    u8 pad2C[0xB6 - 0x2C];
    u16 unkB6;
    u8 padB8[0x16C - 0xB8];
    f32 unk16C;
    u8 pad170[0x2A0 - 0x170];
} FalconEngPlayer;

extern FalconEngPlayer D_main_bss_80137DBC[];
extern s32 D_mission_overlay_80109998[];
extern u8 D_mission_overlay_801099A0[];
extern u8 gGameSettings;
void lookupHmtTextureByName(s32, s32, s32, void *, void *, s32);
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void playSpeechClipOncePerLevel(s32, s32);

void triggerFalconEngineEffect(s32 *arg0, s32 arg1) {
    u8 sp28[0x30];
    u8 sp58[0x30];
    s32 *s3;
    s32 *tbl;
    FalconEngPlayer *s0;
    s32 a0;

    tbl = D_mission_overlay_80109998;
    s3 = tbl + (arg1 & 0xFF);
    s0 = &D_main_bss_80137DBC[*arg0];
    lookupHmtTextureByName(s0->unk0, *s3, 0, sp28, sp58, 0);
    dispatchCueByCategory(0, s0->unkB6, sp28, D_mission_overlay_801099A0, 1, 12.5f, s0->unk16C);
    lookupHmtTextureByName(s0->unk0, *s3, 1, sp28, sp58, 1);
    dispatchCueByCategory(0, s0->unkB6, sp28, D_mission_overlay_801099A0, 1, 12.5f, s0->unk16C);
    play3DSoundEvent(0, sp28, s0->unk28, 20.0f, 0.2f, 0, 0x2F, 0x6E, 0x3C);
    a0 = 0x28C;
    if (gGameSettings != 0xF) {
        a0 = 0x133;
    }
    playSpeechClipOncePerLevel(a0, 9);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BAFF0", bindFalconSubmodelMaterials);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BAFF0", playerFalconMainUpdate);

typedef struct {
    u8 pad0[0x1A];
    u16 mask1A;
    u8 pad1C;
    u8 mask1D;
    u16 mask1E;
    u8 pad20[4];
} HudDef;

typedef struct {
    s32 unk0;
    u8 pad4[0xB6 - 4];
    u16 unkB6;
    s32 unkB8;
    u8 padBC[0x158 - 0xBC];
    u16 unk158;
    u8 pad15A[2];
    s32 unk15C;
    f32 unk160;
    f32 unk164;
    u8 pad168[0x178 - 0x168];
    s32 unk178;
    u8 pad17C[4];
    u16 unk180;
    u8 pad182[0x2A0 - 0x182];
} FalconSpawnPlayer;

#define FSP ((FalconSpawnPlayer *)D_main_bss_80137DBC)
extern u16 D_main_bss_80130B88[][3];
extern HudDef D_mission_overlay_8010BE18[];
extern void triggerFalconEngineEffect(s32 *, s32);
extern void playerFalconMainUpdate(void *, s32 *, f32);
extern void tickCraftAnimationSlot(s32, f32);
extern u8 tickHudInstanceTargetingAndSpawns(s32, f32, void *, s32, s32, void *, s32);
extern void dispatchHudInstanceWeaponEffect(s32, s32, void *, s32, s32, s32, s32);

void spawnFalconEngineParticles(s32 *arg0, f32 dt) {
    u16 out[2];
    FalconSpawnPlayer *p;

    p = &FSP[*arg0];
    if (*(u16 *)((u8 *)D_main_bss_80137DBC + p->unkB8 * 0x2A0 + 0x180) & 1) {
        if (0.0f < p->unk160) {
            p->unk160 = p->unk160 - dt;
        } else if (D_main_bss_80130B88[*arg0][0] & D_mission_overlay_8010BE18[*arg0].mask1A) {
            p->unk160 = p->unk160 + p->unk164;
            triggerFalconEngineEffect(arg0, *((u8 *)&p->unk158 + 1));
            p->unk158 ^= 1;
        }
        if (tickHudInstanceTargetingAndSpawns(0, dt, (u8 *)p + 4, p->unk0, (D_main_bss_80130B88[*arg0][0] & 0xFF) & D_mission_overlay_8010BE18[*arg0].mask1D, out, p->unkB6)) {
            dispatchHudInstanceWeaponEffect(0, p->unkB6, (u8 *)p + 4, p->unk0, p->unk178, p->unk158, out[0]);
        }
        if (D_main_bss_80130B88[*arg0][0] & D_mission_overlay_8010BE18[*arg0].mask1E) {
            p->unk158 = 0;
            p->unk15C = (p->unk15C + 1) & 3;
        }
    }
    playerFalconMainUpdate(p, arg0, dt);
    tickCraftAnimationSlot(0, dt);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BAFF0", playerFalconUpdate);

#if 0
// https://decomp.me/scratch/yyxM0
f32 integrateFalconFlightPhysics(f32 arg0, f32 arg1, f32 arg2) {
    f32 temp_fa0;
    f32 var_fv0;

    if (!(fabsf(arg1 - arg0) > 0.35f)) {
        return arg1;
    }
    if (!(arg0 < arg1)) {
        if (!((arg0 - arg1) > 180.0f)) {
            var_fv0 = -70.0f;
        } else {
            var_fv0 = 70.0f;
        }
    } else {
        if (!(arg1 - arg0 > 180.0f)) {
            var_fv0 = 70.0f;
        } else {
            var_fv0 = -70.0f;
        }
    }
    arg0 += (arg2 * var_fv0);
    if (arg0 < 0.0f) {
        arg0 += 360.0f;
    } else if (360.0f < arg0) {
        arg0 -= 360.0f;
    }
    return arg0;
}

// DO NOT DELETE ME I AM REQUIRED FOR MATCHING
const u32 rodata_pad_0BAFF0[2] = {
    0x03A0F021,
    0x24040014,
};
#else
INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BAFF0", integrateFalconFlightPhysics);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BAFF0", D_mission_overlay_800A5ED4);
#endif
