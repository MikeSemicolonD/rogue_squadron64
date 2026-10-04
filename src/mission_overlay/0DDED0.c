#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7DE0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7DEC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7DF8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7E00);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7E0C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DDED0", npcInitFullModel);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7E28);

struct EffectRow {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
};

extern char D_mission_overlay_800A7E28[];
extern struct EffectRow D_mission_overlay_8010A9C4[];
extern s32 D_main_bss_80137CE4;
extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void resolveNpcAttachmentPos(s32, void *, s32, f32);
extern s32 tickProgressChannel(s32, void *, s32, f32 *);
extern void triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);

s32 npcTickEffectChannelC(void *arg0)
{
  u8 sp28[0x30];
  f32 sp58;
  f32 fv;
  s32 r;
  struct EffectRow *e;
  u8 *npc = *((u8 **) (((u8 *) arg0) + 4));
  lookupHmtTextureByName(*((s32 *) (npc + 0x30)), D_mission_overlay_800A7E28, 0, sp28, 0, 0);
  fv = ((f32 *) (*((u8 **) (npc + 0x34))))[D_main_bss_80137CE4 + 0x37];
  if (fv != 0.0f)
  {
    e = &D_mission_overlay_8010A9C4[npc[0xCF]];
    e++;
    e--;
    resolveNpcAttachmentPos(*((s32 *) (npc + 0x38)), sp28, *((s32 *) (&e->unkC)), fv);
  }
  r = tickProgressChannel(*((s32 *) (npc + 0x38)), sp28, 0, &sp58) & 0xFF;
  if (r == 1)
  {
    *((f32 *) (npc + 0xDC)) = 0.0f;
    triggerCueWithSlotEffect(*((s32 *) (npc + 0x38)), 0, sp28, &D_mission_overlay_8010A9C4[npc[0xCF]], r, D_mission_overlay_8010A9C4[npc[0xCF]].unkC, sp58);
    play3DSoundEvent(0, npc, npc + 0x24, 18.0f, 0.5f, 0, 0x48, 0x6E, 0x28);
  }
  return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DDED0", npcTickEffectChannelD);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DDED0", npcTickEffectChannelE);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DDED0", playAttachmentMaterialFadeSound);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DDED0", transformCraftDualAnchorsAndApplyMotion);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DDED0", tickEnemyCraftWithDestruction);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DDED0", func_mission_overlay_800DE4EC);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DDED0", npcGroundTransportUpdate);

extern s32 D_mission_overlay_8010C0A0;

void resetCraftSubsystemGlobal(void) {
    D_mission_overlay_8010C0A0 = 0;
}

void func_mission_overlay_800DFB84(void) {
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DDED0", fake_func_800DFB8C);
