#include "common.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BD840", D_mission_overlay_800A5FE0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BD840", D_mission_overlay_800A5FE8);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BD840", playerT16Init);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BD840", computeT16Transform);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BD840", D_mission_overlay_800A6074);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BD840", playerT16MainUpdate);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BD840", playerT16Update);

#include "common_types.h"
#include "player.h"
extern char D_mission_overlay_800A6074[];
extern u8 D_mission_overlay_80109A48[];
extern u8 D_main_bss_80137DBC[][0x2A0];
void lookupHmtTextureByName(void *, char *, s32, void *, s32, s32);
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);
s32 slotDispatcherIter(u16, s32, void *);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
typedef struct {
    s16 unk0;
    u8 pad2[0x16];
    f32 unk18;
    u8 pad1C[4];
} T16SlotArgs;
void triggerT16Effect(s32 *arg0, s32 arg1) {
    u8 tex[0x30];
    T16SlotArgs args;
    struct inner_player_struct *p = (struct inner_player_struct *)D_main_bss_80137DBC[*arg0];
    u16 cue;

    lookupHmtTextureByName(p->object, D_mission_overlay_800A6074, arg1 & 1, tex, 0, 0);
    cue = dispatchCueByCategory(0, p->unk0B6, tex, D_mission_overlay_80109A48, 1, 12.5f, p->blasterDamageMultiplier);
    args.unk0 = 1;
    args.unk18 = 0.7f;
    slotDispatcherIter(cue, 10, &args);
    play3DSoundEvent(0, tex, &p->unk028, 20.0f, 0.2f, 0, 0x31, 0x64, 0x32);
}

const u32 rodata_pad_0BD840 = 0x8FBE0030;
