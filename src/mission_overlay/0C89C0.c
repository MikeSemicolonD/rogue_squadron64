#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", initNpcActorFromSpawnMessage);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A6994);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", playNpcStateChangeEffect);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A69A0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", spawnNpcDestructionEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", spawnNpcImpactEffectVariant);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", updateNpcOrientationFromMotion);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", setupNpcModelForState);

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
