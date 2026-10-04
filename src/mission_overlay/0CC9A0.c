#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", findNearestNpcWithinRange);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", initActorFromSpawnTemplate);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", updateAtAtLegArticulation);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CC9A0", D_mission_overlay_800A6ECC);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", npcAtAtUpdate);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CC9A0", fake_func_800CEF1C);
