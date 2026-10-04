#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D38A0", npcInitWithMotionParams);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D38A0", npcTickEffectChannelA);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D38A0", npcTickEffectChannelB);

struct TsObj { u8 pad0[0x24]; u8 pos[0xC]; s32 f30; u8 *f34; s32 f38; u8 pad3C[0x20]; f32 f5C_pad; };
struct TsObj2 { u8 pad0[0x24]; u8 pos[0xC]; s32 f30; u8 *f34; s32 f38; u8 pad3C[0x20]; s16 f5C; u8 pad5E[2]; f32 f60; };
typedef struct { u8 pad0[4]; struct TsObj2 *obj; } TsActor;
typedef struct { s16 a; s16 b; f32 x; f32 y; f32 z; f32 w; u8 flag; u8 pad[0xB]; } TsEvent;
extern s32 D_main_bss_80137CE4;
extern u8 D_mission_overlay_8010A868[];
s32 lookupHmtTextureByName(s32, char *, s32, u8 *, s32, s32);
s32 resolveNpcAttachmentPos(s32, u8 *, f32, f32);
s32 tickProgressChannel(s32, u8 *, s32, f32 *);
s32 triggerCueWithSlotEffect(s32, s32, u8 *, u8 *, s32, f32, f32);
s16 getObjectNpcTypeId(s32);
s32 slotDispatcherIter(s32, s32, TsEvent *);
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 npcTickEffectChannelWithSlotDispatch(TsActor *arg0) {
    u8 buf[0x30];
    TsEvent ev;
    f32 sp78;
    struct TsObj2 *o = arg0->obj;
    f32 fv;
    s32 r;
    s32 cue;

    if (o->f60 < 70.0f) {
        return 0;
    }
    lookupHmtTextureByName(o->f30, "scnd", o->f5C, buf, 0, 0);
    o->f5C ^= 1;
    fv = *(f32 *)(o->f34 + D_main_bss_80137CE4 * 4 + 0x100);
    if (fv != 0.0f) {
        resolveNpcAttachmentPos(o->f38, buf, 5.0f, fv);
    }
    r = tickProgressChannel(o->f38, buf, 1, &sp78) & 0xFF;
    if (r != 1) {
        return 0;
    }
    cue = triggerCueWithSlotEffect(o->f38, 0xB, buf, D_mission_overlay_8010A868, 0, 5.0f, sp78);
    ev.a = 0;
    ev.x = 0.0f;
    ev.y = 0.0f;
    ev.z = 0.0f;
    ev.flag = r;
    ev.w = -1.0f;
    ev.b = getObjectNpcTypeId(o->f38);
    slotDispatcherIter(cue & 0xFFFF, 0xA, &ev);
    play3DSoundEvent(0, o, o->pos, 18.0f, 0.3f, 0, 0x30, 0x78, 0x50);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D38A0", npcShuttleHandleDestruction);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D38A0", D_mission_overlay_800A747C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D38A0", npcShuttleUpdate);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D38A0", fake_func_800D4EC4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D38A0", D_mission_overlay_800A75E4);
