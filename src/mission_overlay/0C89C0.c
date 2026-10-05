#include "common.h"
#include "common_types.h"

struct NiObj { u8 pad0[0x34]; u8 *f34; s32 f38; u8 pad3C[0x34]; s16 f70; s16 f72; s16 f74; u8 pad76[2]; f32 f78; f32 f7C; s32 f80; s32 f84; };
typedef struct { u8 pad0[4]; struct NiObj *obj; } NiActor;
extern s32 D_main_bss_80137CE4;
s32 spawnNpcDestructionEffect();
s32 playNpcAmbientEffect();
s32 spawnNpcImpactEffectVariant();
s32 playNpcStateChangeEffect();
s32 setNpcHealth(s32, u8 *, u8 *);
void setObjectDetailLevel(s32, s32);
void initActorMotionParams(s32, f32, f32, f32, f32);
void initObjectAnimSubstruct(s32, f32, f32, f32, f32, s32 (*)(), s32, f32, f32, f32);

void initNpcActorFromSpawnMessage(NiActor *arg0)
{
  struct NiObj *o = arg0->obj;
  u8 *e;
  if (setNpcHealth(o->f38, o->f34 + 0x6C, o->f34) > 0)
  {
    o->f72 = 0;
  }
  else
  {
    o->f72 = 3;
  }
  o->f84 = 0;
  o->f80 = 0;
  o->f74 = 0;
  o->f7C = 1.0f;
  o->f78 = *((f32 *) (((D_main_bss_80137CE4 * 4) + o->f34) + 0x9C));
  ;
  initActorMotionParams(o->f38, *((f32 *) ((o->f34 + (D_main_bss_80137CE4 * 4)) + 0x98)), *((f32 *) ((o->f34 + (D_main_bss_80137CE4 * 4)) + 0xA0)), *((f32 *) ((o->f34 + (D_main_bss_80137CE4 * 4)) + 0xA4)), *((f32 *) ((o->f34 + (D_main_bss_80137CE4 * 4)) + 0xA8)));
  setObjectDetailLevel(o->f38, *((s32 *) (o->f34 + 0x8C)));
  switch (o->f70)
  {
    case 1:
      e = o->f34;
      initObjectAnimSubstruct(o->f38, *((f32 *) (e + 0xAC)), *((f32 *) (e + 0xB0)), *((f32 *) (e + 0xB4)), *((f32 *) (e + 0xB8)), spawnNpcDestructionEffect, 0, 5.0f, 50.0f, *((f32 *) (((D_main_bss_80137CE4 * 4) + e) + 0xBC)));
      break;

    case 3:
      e = o->f34;
      initObjectAnimSubstruct(o->f38, *((f32 *) (e + 0xAC)), *((f32 *) (e + 0xB0)), *((f32 *) (e + 0xB4)), *((f32 *) (e + 0xB8)), playNpcAmbientEffect, 0, 10.0f, 15.0f, *((f32 *) (((D_main_bss_80137CE4 * 4) + e) + 0xBC)));
      break;

    case 4:
      e = o->f34;
      initObjectAnimSubstruct(o->f38, *((f32 *) (e + 0xAC)), *((f32 *) (e + 0xB0)), *((f32 *) (e + 0xB4)), *((f32 *) (e + 0xB8)), spawnNpcImpactEffectVariant, 0, 10.0f, 50.0f, *((f32 *) (((D_main_bss_80137CE4 * 4) + e) + 0xBC)));
      break;

    default:
      e = o->f34;
      initObjectAnimSubstruct(o->f38, *((f32 *) (e + 0xAC)), *((f32 *) (e + 0xB0)), *((f32 *) (e + 0xB4)), *((f32 *) (e + 0xB8)), playNpcStateChangeEffect, 0, 10.0f, 15.0f, *((f32 *) (((D_main_bss_80137CE4 * 4) + e) + 0xBC)));
      break;

  }

}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A6994);

extern char D_mission_overlay_800A6994[];
extern u8 D_mission_overlay_8010A5AC[];
void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
void generatePerpEmitDirectionWithJitter(s32, void *, s32);
u8 tickProgressChannel(s32, void *, s32, f32 *);
void triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 playNpcStateChangeEffect(u8 *arg0) {
    u8 sp28[0x30];
    u8 sp58[0x30];
    u8 sp88[0x30];
    f32 spB8;
    f32 spBC;
    s32 temp_s1;
    s32 temp_v0;
    u8 *temp_s2;

    temp_s2 = *(u8 **)(arg0 + 4);
    lookupHmtTextureByName(*(s32 *)(temp_s2 + 0x30), D_mission_overlay_800A6994, 0, sp28, (s32)sp88, 0);
    lookupHmtTextureByName(*(s32 *)(temp_s2 + 0x30), D_mission_overlay_800A6994, 1, sp58, (s32)sp88, 1);
    generatePerpEmitDirectionWithJitter(*(s32 *)(temp_s2 + 0x38), sp28, 0);
    generatePerpEmitDirectionWithJitter(*(s32 *)(temp_s2 + 0x38), sp58, 1);
    temp_s1 = tickProgressChannel(*(s32 *)(temp_s2 + 0x38), sp28, 0, &spB8) & 0xFF;
    if (temp_s1 == 1) {
        temp_v0 = tickProgressChannel(*(s32 *)(temp_s2 + 0x38), sp58, 0, &spBC) & 0xFF;
        if (temp_v0 == temp_s1) {
            triggerCueWithSlotEffect(*(s32 *)(temp_s2 + 0x38), 2, sp28, D_mission_overlay_8010A5AC, temp_v0, 10.0f, spB8);
            triggerCueWithSlotEffect(*(s32 *)(temp_s2 + 0x38), 2, sp58, D_mission_overlay_8010A5AC, 0, 10.0f, spBC);
            *(s32 *)(temp_s2 + 0x7C) = 0;
            play3DSoundEvent(0, temp_s2, temp_s2 + 0x24, 18.0f, 0.5f, 0, 0x16, 0x7F, 0x28);
        }
    }
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A69A0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", spawnNpcDestructionEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", spawnNpcImpactEffectVariant);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", updateNpcOrientationFromMotion);

void releaseMeshAsset(void *);
void *walkMeshdef0List(char *);
void initVec4TripletFromArgs(void *, s32, s32, s32);
void composeRotationMatrixSlot0(void *, s32);
void composeRotationMatrixSlot1(void *, s32);
void composeRotationMatrixSlot2(void *, s32);
void addVec3At0x24(void *, s32, s32, s32);
extern char D_mission_overlay_800A6A0C[];
extern char D_mission_overlay_800A6A18[];
extern char D_mission_overlay_800A6A24[];
extern char D_mission_overlay_800A6A30[];

typedef struct {
    u8 pad0[0x1C];
    s32 rot[3];
    s32 scale[3];
} NpcModelTemplate;

typedef struct {
    s32 pos[3];
    u8 padC[0x24];
    u8 *mesh;
    NpcModelTemplate *tmpl;
    u8 pad38[0x38];
    s16 state;
} NpcModelOwner;

void setupNpcModelForState(NpcModelOwner *npc) {
    NpcModelTemplate *tmpl;

    releaseMeshAsset(npc->mesh);
    switch (npc->state) {
        case 2:
            npc->mesh = walkMeshdef0List(D_mission_overlay_800A6A0C);
            break;
        case 3:
            npc->mesh = walkMeshdef0List(D_mission_overlay_800A6A18);
            break;
        case 4:
            npc->mesh = walkMeshdef0List(D_mission_overlay_800A6A24);
            break;
        default:
            npc->mesh = walkMeshdef0List(D_mission_overlay_800A6A30);
            break;
    }
    tmpl = npc->tmpl;
    initVec4TripletFromArgs(npc->mesh + 0x28, tmpl->scale[0], tmpl->scale[1], tmpl->scale[2]);
    composeRotationMatrixSlot0(npc->mesh + 0x28, tmpl->rot[0]);
    composeRotationMatrixSlot1(npc->mesh + 0x28, tmpl->rot[1]);
    composeRotationMatrixSlot2(npc->mesh + 0x28, tmpl->rot[2]);
    addVec3At0x24(npc->mesh + 0x28, npc->pos[0], npc->pos[1], npc->pos[2]);
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A6A0C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A6A18);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A6A24);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A6A30);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", npcTurretUpdate);

void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
void generatePerpEmitDirectionWithJitter(s32, void *, s32);
u8 tickProgressChannel(s32, void *, s32, f32 *);
void triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern char D_mission_overlay_800A69A0[];
extern u8 D_mission_overlay_8010A5AC[];

s32 playNpcAmbientEffect(u8 *arg0) {
    u8 *npc;
    u8 emit[0x30];
    f32 progress;
    u8 state;

    npc = *(u8 **)(arg0 + 4);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A69A0, 0, emit, 0, 0);
    generatePerpEmitDirectionWithJitter(*(s32 *)(npc + 0x38), emit, 0);
    state = tickProgressChannel(*(s32 *)(npc + 0x38), emit, 0, &progress);
    if (state == 1) {
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 0, emit, D_mission_overlay_8010A5AC, state, 10.0f, progress);
        play3DSoundEvent(0, npc, npc + 0x24, 15.0f, 0.5f, 0, 0x16, 0x7F, 0x28);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", fake_func_800CA26C);

__asm__(".section .rodata\n.word 0x3C02801C\n.word 0x8C423BBC\n.word 0x3043008B\n.section .text");
