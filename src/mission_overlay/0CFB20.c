#include "common.h"
#include "common_types.h"

extern f32 D_mission_overlay_8010A6A4[];
extern u8 D_mission_overlay_8010A6B8[];
extern f32 D_mission_overlay_8010A6BC[];
extern u8 D_mission_overlay_8010A6C4[];
extern f32 D_mission_overlay_8010A6C8[];
extern u8 D_mission_overlay_8010A6D8[];
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void advanceAtStEffectPhaseSound(u8 *arg0, f32 arg1, u8 arg2) {
    f32 *tab;
    u8 *flags;
    f32 t;
    u8 idx;
    switch (*(s16 *)(arg0 + 0x7E)) {
    case 0:
        tab = D_mission_overlay_8010A6A4;
        flags = D_mission_overlay_8010A6B8;
        break;
    case 1:
        tab = D_mission_overlay_8010A6BC;
        flags = D_mission_overlay_8010A6C4;
        break;
    case 2:
        tab = D_mission_overlay_8010A6C8;
        flags = D_mission_overlay_8010A6D8;
        break;
    default:
        return;
    }
    t = *(f32 *)(arg0 + 0xAC) + (arg1 / *(f32 *)(arg0 + 0x98));
    *(f32 *)(arg0 + 0xAC) = t;
    if (t > 1.0f) {
        arg0[0xFB] = 0;
        *(f32 *)(arg0 + 0xAC) = *(f32 *)(arg0 + 0x94);
        *(f32 *)(arg0 + 0xB0) = tab[0];
    }
    if (!arg2 && *(f32 *)(arg0 + 0xAC) >= *(f32 *)(arg0 + 0xB0)) {
        idx = arg0[0xFB];
        arg0[0xFB] = idx + 1;
        if (flags[idx] == 0) {
            play3DSoundEvent(0, arg0, arg0 + 0x24, 18.0f, 0.6f, 0, 5, 0x78, 0x32);
        } else {
            play3DSoundEvent(0, arg0, arg0 + 0x24, 16.0f, 0.5f, 0, 6, 0x78, 0x32);
        }
        *(f32 *)(arg0 + 0xB0) = tab[arg0[0xFB]];
    }
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A700C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A7010);

struct CfObj { u8 pad0[4]; f32 f4; u8 pad8[0x1C]; u8 pos[0xC]; s32 f30; u8 *f34; s32 f38; u8 pad3C[0x28]; s32 f64; u8 pad68[4]; f32 f6C; };
typedef struct { u8 pad0[4]; struct CfObj *obj; } CfActor;
extern u8 D_mission_overlay_800A700C[];
extern u8 D_mission_overlay_800A7010[];
extern u8 D_mission_overlay_8010A698[];
extern s32 D_main_bss_80137CE4;
s32 lookupHmtTextureByName(s32, u8 *, s32, u8 *, s32, s32);
s32 setObjectSubstructF10IfReady(s32, f32, s32);
s32 tickProgressChannel(s32, u8 *, s32, f32 *);
s32 resolveNpcAttachmentPos(s32, u8 *, f32, f32);
s32 generatePerpEmitDirectionWithJitter(s32, u8 *, s32);
s32 triggerCueWithSlotEffect(s32, s32, u8 *, u8 *, s32, f32, f32);
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
s32 tickAtStCannonFireEffect(CfActor *arg0, s32 arg1) {
    u8 buf[0x30];
    f32 sp58;
    struct CfObj *o = arg0->obj;
    f32 fv;
    s32 r;
    if (arg1 == 0) {
        lookupHmtTextureByName(o->f30, D_mission_overlay_800A700C, 0, buf, 0, 0);
        setObjectSubstructF10IfReady(o->f38, 0.06666667f, 0);
        o->f6C = ((f32 *)buf)[1] - o->f4;
        o->f64 = 0;
    } else {
        lookupHmtTextureByName(o->f30, D_mission_overlay_800A7010, 0, buf, 0, 0);
    }
    fv = *(f32 *)(o->f34 + D_main_bss_80137CE4 * 4 + 0xD8);
    if (fv != 0.0f) {
        resolveNpcAttachmentPos(o->f38, buf, 10.0f, fv);
    }
    generatePerpEmitDirectionWithJitter(o->f38, buf, 0);
    r = tickProgressChannel(o->f38, buf, 0, &sp58) & 0xFF;
    if (r == 1) {
        triggerCueWithSlotEffect(o->f38, 3, buf, D_mission_overlay_8010A698, r, 10.0f, sp58);
        play3DSoundEvent(0, o, o->pos, 20.0f, 0.4f, 0, 0xD, 0x78, 0x28);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", updateAtStBodyKinematics);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A705C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A7060);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", npcAtStHandleDestruction);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", advanceAtStDeathAnimPhase);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70DC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70E0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70E8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70F4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A7100);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", npcAtStUpdate);

#include "game_settings.h"
typedef struct {
    u8 p00[0xB4];
    s16 fB4;
    u8 pB6[0xC0 - 0xB6];
    f32 fC0;
    f32 fC4;
    u8 pC8[0xD8 - 0xC8];
    s32 fD8;
    s32 fDC;
    s32 fE0;
    u8 pE4[4];
    f32 fE8;
    f32 fEC;
    f32 fF0;
    f32 fF4;
    f32 fF8;
    f32 fFC;
    u8 p100[4];
    f32 f104;
    f32 f108;
    f32 f10C;
    f32 f110;
    f32 f114;
    f32 f118;
    s32 f11C;
    f32 f120;
    f32 f124;
    f32 f128;
    f32 f12C;
    f32 f130;
    f32 f134;
    f32 f138;
    s32 f13C;
    f32 f140;
    f32 f144;
    f32 f148;
    s32 f14C;
    f32 f150;
    f32 f154;
    s16 f158;
    u8 p15A[6];
    s32 f160;
    s32 f164;
    s32 f168;
    u8 p16C[4];
    s32 f170;
    s32 f174;
    s32 f178;
    u8 p17C[4];
    s16 f180;
    u8 p182[0x194 - 0x182];
    s32 f194;
} AtStPlayer;

extern AtStPlayer D_main_bss_80137DBC;
void initPlayerCraftMovementMode(AtStPlayer *);
s32 refreshPlayerSecondaryWeaponHud(s32, void *, s32);

void playerAtStInit(s32 arg0, s16 arg1)
{
  AtStPlayer *p = &D_main_bss_80137DBC;
  register u32 mask asm("$6");
  p->f180 = arg1;
  p->fB4 = 0;
  initPlayerCraftMovementMode(p);
  mask = 0xFEFFFFFF;
  p->f11C = (p->f14C = (p->f13C = 0));
  p->fE0 = (p->fDC = (p->fD8 = 0));
  p->f158 = 0;
  p->fC0 = 150.0f;
  p->fC4 = 150.0f;
  p->fE8 = 2.625f;
  p->fEC = 2.625f;
  p->fF0 = 0.11875f;
  p->fF4 = 0.11875f;
  p->fF8 = 1.4f;
  p->fFC = 1.8f;
  p->f104 = 15.0f;
  p->f108 = 10.0f;
  p->f10C = 1.0f;
  p->f110 = -40.0f;
  p->f114 = -40.0f;
  p->f118 = 35.0f;
  p->f120 = 35.0f;
  p->f124 = 35.0f;
  p->f130 = 0.75f;
  p->f134 = 3.0f;
  p->f138 = 20.0f;
  p->f140 = 10.0f;
  p->f144 = 60.0f;
  p->f148 = 10.0f;
  p->f150 = 5.0f;
  p->f154 = 40.0f;
  p->f128 = 0.2f;
  p->f12C = 0.15f;
  p->f174 = (p->f168 = (p->f164 = (p->f170 = (p->f160 = 0))));
  p->f194 = 4;
  gGameSettings.unlockAndSettingsFlags[0] &= mask;
  p->f178 = refreshPlayerSecondaryWeaponHud(0, &gGameSettings, 0xFEFFFFFF) & 0xFF;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A721C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", spawnPlayerAtStCannonFire);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", advancePlayerAtStLocomotion);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", updatePlayerAtStBehavior);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", playerAtStUpdate);

s32 setNpcHealth(s32, void *, void *);
void initActorMotionParams(s32, s32, s32, s32, f32);
void initObjectAnimSubstruct(s32, s32, s32, s32, f32, void *, s32, f32, f32, s32);
void setObjectDetailLevel(s32, s32);
s32 tickAtStCannonFireEffect();
extern s32 D_main_bss_80137CE4;

void npcInitFromTemplate(u8 *arg0) {
    u8 *npc;
    u8 *tmpl;

    npc = *(u8 **)(arg0 + 4);
    tmpl = *(u8 **)(npc + 0x34);
    *(f32 *)(npc + 0x64) = 1.0f;
    *(s32 *)(npc + 0x68) = 0;
    if (setNpcHealth(*(s32 *)(npc + 0x38), tmpl + 0x6C, tmpl) > 0) {
        npc[0xFA] = 0;
        npc[0x7C] = 0;
        *(f32 *)(npc + 0x60) = ((f32 *)(tmpl + 0xBC))[D_main_bss_80137CE4];
        initActorMotionParams(*(s32 *)(npc + 0x38), ((s32 *)(tmpl + 0xB4))[D_main_bss_80137CE4], ((s32 *)(tmpl + 0xB8))[D_main_bss_80137CE4], ((s32 *)(tmpl + 0xC0))[D_main_bss_80137CE4], ((f32 *)(tmpl + 0xC4))[D_main_bss_80137CE4]);
        initObjectAnimSubstruct(*(s32 *)(npc + 0x38), *(s32 *)(tmpl + 0xC8), *(s32 *)(tmpl + 0xCC), *(s32 *)(tmpl + 0xD0), *(f32 *)(tmpl + 0xD4), tickAtStCannonFireEffect, 0, 10.0f, 15.0f, 0);
        setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(tmpl + 0xA0));
    } else {
        npc[0xFA] = 2;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", spawnScaledBootVec4Effect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", fake_func_800D2C98);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A73B8);
