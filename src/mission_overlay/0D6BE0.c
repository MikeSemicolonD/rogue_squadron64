#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D6BE0", npcInitSimpleModel);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D6BE0", npcTickEffectChannelShared);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D6BE0", npcTankDroidComputeAimMotion);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D6BE0", npcTankDroidUpdate);

void npcTickEffectChannelShared(s32, s32, s32);

void npcTickEffectChannelSharedMode0(s32 arg0, s32 arg1) {
    npcTickEffectChannelShared(arg0, arg1, 0);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D6BE0", npcTickEffectChannelSharedMode1);
