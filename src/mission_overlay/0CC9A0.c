#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", findNearestNpcWithinRange);

struct IaObj { u8 pad0[0x34]; u8 *f34; s32 f38; u8 pad3C[0xAA]; u8 fE6; u8 padE7[0x10]; f32 fF8; };
typedef struct { u8 pad0[4]; struct IaObj *obj; } IaActor;
extern s32 D_main_bss_80137CE4;
s32 setNpcHealth(s32, u8 *, u8 *);
void setObjectDetailLevel(s32, s32);
void initActorMotionParams(s32, s32, s32, s32, f32);
void initObjectAnimSubstruct(s32, s32, s32, s32, f32, s32 (*)(), s32, f32, f32, s32);
void setEffectIntensity(s32, s32);
s32 tickActorTexturedSoundEffect();

void initActorFromSpawnTemplate(IaActor *arg0) {
    struct IaObj *o = arg0->obj;
    u8 *e = o->f34;
    s32 h;
    u8 *e2;
    u8 *t;
    s32 off;
    s8 st;

    h = setNpcHealth(o->f38, e + 0x6C, e);
    setObjectDetailLevel(o->f38, *(s32 *)(o->f34 + 0xA0));
    st = 4;
    if (h > 0) {
        e2 = o->f34;
        if (*(s32 *)(e2 + 0x4C) >= 0) {
            o->fE6 = 0;
            off = D_main_bss_80137CE4 * 4;
            o->fF8 = *(f32 *)((u8 *)(off + (s32)o->f34) + 0xB8) * 3.0f;
            t = (u8 *)(off + (s32)e2);
            initActorMotionParams(o->f38, *(s32 *)(t + 0xB0), *(s32 *)(t + 0xB4), *(s32 *)(t + 0xBC), *(f32 *)(t + 0xC0));
            initObjectAnimSubstruct(o->f38, *(s32 *)(e2 + 0xC4), *(s32 *)(e2 + 0xC8), *(s32 *)(e2 + 0xCC), *(f32 *)(e2 + 0xD0), tickActorTexturedSoundEffect, 0, 10.0f, 15.0f, 0);
            setEffectIntensity(o->f38, *(s32 *)(e2 + 0xD8));
            return;
        }
        st = 3;
    }
    o->fE6 = st;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CC9A0", D_mission_overlay_800A6D60);

typedef struct { s16 a; s16 b; u8 pad4[8]; f32 c; f32 d; u8 pad[0xC]; } SndArgs;
typedef struct { u8 pad0[4]; struct Obj *obj; } SndActor;
struct Obj { u8 pad0[0x24]; u8 pos[0xC]; s32 f30; s32 pad34; s32 f38; };
extern u8 D_mission_overlay_800A6D60[];
extern u8 D_mission_overlay_8010A624[];
s32 lookupHmtTextureByName(s32, u8 *, s32, u8 *, s32, s32);
s32 setObjectSubstructF10IfReady(s32, f32, s32);
s32 tickProgressChannel(s32, u8 *, s32, s32);
s16 getObjectNpcTypeId(s32);
s32 triggerCueWithSlotEffect(s32, s32, u8 *, u8 *, s32, f32, f32);
s32 slotDispatcherIter(s32, s32, SndArgs *);
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
s32 tickActorTexturedSoundEffect(u8 *arg0, s32 arg1) {
    u8 buf[0x30];
    SndArgs args;
    struct Obj *o = ((SndActor *)arg0)->obj;
    s32 r;
    if (arg1 == 0) {
        lookupHmtTextureByName(o->f30, D_mission_overlay_800A6D60, 0, buf, 0, 0);
        setObjectSubstructF10IfReady(o->f38, 0.06666667f, 0);
    } else {
        lookupHmtTextureByName(o->f30, "b", 0, buf, 0, 0);
    }
    r = tickProgressChannel(o->f38, buf, 0, 0) & 0xFF;
    if (r == 1) {
        args.a = 0;
        args.b = getObjectNpcTypeId(o->f38);
        args.c = 5.0f;
        args.d = 10.0f;
        slotDispatcherIter(triggerCueWithSlotEffect(o->f38, 5, buf, D_mission_overlay_8010A624, r, 10.0f, -1.0f) & 0xFFFF, 0xA, &args);
        play3DSoundEvent(0, o, o->pos, 20.0f, 0.4f, 0, 0xD, 0x78, 0x28);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", tickAtAtBodyTransform);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", tickAtAtAudioAndWeaponState);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CC9A0", D_mission_overlay_800A6DCC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CC9A0", D_mission_overlay_800A6DD0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", processAtAtSubFeatureSlot);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CC9A0", D_mission_overlay_800A6DE0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", npcAtAtHandleDestruction);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", spawnAtAtFootstepDustBurst);

extern u8 D_mission_overlay_800A6DCC[];
extern u8 D_main_bss_80138058[];
extern void computeWalkerLimbStrideTargets(u16, f32 *, f32 *, f32 *, f32);
extern f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
extern void spawnAtAtFootstepDustBurst(f32 *);

void updateAtAtLegArticulation(struct Obj *arg0) {
    Vec3f sp18;
    Vec3f sp28;
    Vec3f sp38;
    Vec3f sp48;
    f32 sp58[12];
    s32 j;
    f32 s;

    lookupHmtTextureByName(arg0->f30, D_mission_overlay_800A6DCC, 0, (u8 *)sp58, 0, 0);
    computeWalkerLimbStrideTargets(*(u16 *)((u8 *)arg0->f38 + 0x198), sp18, sp28, sp38, 0.7f);
    sp18[0] = sp58[0] - sp28[0] * 0.5f - sp38[0] * 0.5f;
    sp18[1] = sp58[1] - sp28[1] * 0.5f - sp38[1] * 0.5f;
    sp18[2] = sp58[2] - sp28[2] * 0.5f - sp38[2] * 0.5f;
    j = 0;
    do {
        s = (f32)j;
        sp48[0] = sp18[0] + sp38[0] * 0.5f * s;
        sp48[2] = sp18[2] + sp38[2] * 0.5f * s;
        sp48[1] = wrapAngleToCyclicRange(sp48[0], sp48[2], D_main_bss_80138058, 0);
        spawnAtAtFootstepDustBurst(sp48);
        sp48[0] = sp18[0] + sp28[0] + sp38[0] * 0.5f * s;
        sp48[2] = sp18[2] + sp28[2] + sp38[2] * 0.5f * s;
        j++;
        sp48[1] = wrapAngleToCyclicRange(sp48[0], sp48[2], D_main_bss_80138058, 0);
        spawnAtAtFootstepDustBurst(sp48);
    } while (j < 3);
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CC9A0", D_mission_overlay_800A6ECC);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", npcAtAtUpdate);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", fake_func_800CEF1C);
