#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", advanceAtStEffectPhaseSound);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", playerAtStInit);

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
