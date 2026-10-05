#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7DE0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7DEC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7DF8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7E00);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7E0C);

typedef struct { u8 pad0[4]; u8 *obj; } NiActor;
typedef struct { u8 pad0[0x64]; s32 a64[2]; s32 a6C[2]; u8 pad74[0x68]; f32 aDC[2]; s32 aE4[2]; } NiVecs;
struct EffectRow {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
};
extern struct EffectRow D_mission_overlay_8010A9C4[];
extern f32 D_mission_overlay_8010AA00;
extern s32 D_main_bss_80137CE4;
extern s32 npcTickEffectChannelC();
extern s32 npcTickEffectChannelD();
extern s32 npcTickEffectChannelE();
extern s32 playAttachmentMaterialFadeSound();
extern void setNpcHealth(s32, u8 *, u8 *);
extern void setObjectDetailLevel(s32, s32);
extern void initActorMotionParams(s32, s32, s32, s32, f32);
extern void initObjectAnimSubstruct(s32, s32, s32, s32, f32, s32 (*)(), s32, f32, f32, s32);

void npcInitFullModel(NiActor *arg0) {
    u8 *o = arg0->obj;
    u8 *e = *(u8 **)(o + 0x34);
    s32 i;
    u8 *p;
    u8 *t;
    f32 fs;

    o[0xD1] = 0;
    for (i = 0; i < 2; i++) {
        ((NiVecs *)o)->a64[i] = 0;
        ((NiVecs *)o)->a6C[i] = 0;
        ((NiVecs *)o)->aDC[i] = 1.0f;
        ((NiVecs *)o)->aE4[i] = 0;
    }
    *(u16 *)(o + 0xD2) = 0;
    *(f32 *)(o + 0xD8) = *(f32 *)(*(u8 **)(o + 0x34) + 0x90);
    setNpcHealth(*(s32 *)(o + 0x38), *(u8 **)(o + 0x34) + 0x6C, *(u8 **)(o + 0x34));
    setObjectDetailLevel(*(s32 *)(o + 0x38), *(s32 *)(*(u8 **)(o + 0x34) + 0xA8));
    *(f32 *)(o + 0xD4) = *(f32 *)((u8 *)(D_main_bss_80137CE4 * 4) + (s32)*(u8 **)(o + 0x34) + 0xC0);
    t = (u8 *)(D_main_bss_80137CE4 * 4) + (s32)*(u8 **)(o + 0x34);
    initActorMotionParams(*(s32 *)(o + 0x38), *(s32 *)(t + 0xB8), *(s32 *)(t + 0xBC), *(s32 *)(t + 0xC4), *(f32 *)(t + 0xC8));
    switch (o[0xCF]) {
    case 0:
        initObjectAnimSubstruct(*(s32 *)(o + 0x38), *(s32 *)(e + 0xCC), *(s32 *)(e + 0xD0), *(s32 *)(e + 0xD4), *(f32 *)(e + 0xD8), npcTickEffectChannelC, 0, D_mission_overlay_8010A9C4[o[0xCF]].unkC, 15.0f, 0);
        break;
    case 1:
        initObjectAnimSubstruct(*(s32 *)(o + 0x38), *(s32 *)(e + 0xCC), *(s32 *)(e + 0xD0), *(s32 *)(e + 0xD4), *(f32 *)(e + 0xD8), npcTickEffectChannelD, 0, D_mission_overlay_8010A9C4[o[0xCF]].unkC, 15.0f, 0);
        break;
    case 2:
        fs = 15.0f;
        initObjectAnimSubstruct(*(s32 *)(o + 0x38), *(s32 *)(e + 0xCC), *(s32 *)(e + 0xD0), *(s32 *)(e + 0xD4), *(f32 *)(e + 0xD8), playAttachmentMaterialFadeSound, 0, D_mission_overlay_8010A9C4[o[0xCF]].unkC, fs, 0);
        initObjectAnimSubstruct(*(s32 *)(o + 0x38), *(s32 *)(e + 0xCC), *(s32 *)(e + 0xD0), *(s32 *)(e + 0xD4), *(f32 *)(e + 0xD8), npcTickEffectChannelE, 1, D_mission_overlay_8010AA00, fs, 0);
        break;
    }
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7E28);


extern char D_mission_overlay_800A7E28[];
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

s32 npcTickEffectChannelD(void *arg0)
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
    triggerCueWithSlotEffect(*((s32 *) (npc + 0x38)), 2, sp28, &D_mission_overlay_8010A9C4[npc[0xCF]], r, D_mission_overlay_8010A9C4[npc[0xCF]].unkC, sp58);
    play3DSoundEvent(0, npc, npc + 0x24, 18.0f, 0.4f, 0, 0x48, 0x6E, 0x28);
  }
  return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DDED0", npcTickEffectChannelE);

s32 playAttachmentMaterialFadeSound(void *arg0)
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
    play3DSoundEvent(0, npc, npc + 0x24, 19.0f, 0.5f, 0, 0x48, 0x78, 0x28);
  }
  return 0;
}

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
