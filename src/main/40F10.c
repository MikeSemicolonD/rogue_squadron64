#include "common.h"
#include "common_types.h"

#include "main/3F160.h"
#include "main/40F10.h"

INCLUDE_ASM("asm/nonmatchings/main/40F10", allocAndInitParticlePool);

INCLUDE_ASM("asm/nonmatchings/main/40F10", randomBurstNpcHandlerVariant);

INCLUDE_ASM("asm/nonmatchings/main/40F10", spawnNpcFormationWithRandomOrientation);

INCLUDE_ASM("asm/nonmatchings/main/40F10", computeNpcGroupCentroidAndCull);

INCLUDE_ASM("asm/nonmatchings/main/40F10", spawnRandomBurstNpc);

INCLUDE_ASM("asm/nonmatchings/main/40F10", freeNpcBurstSpawnerTables);

INCLUDE_ASM("asm/nonmatchings/main/40F10", initNpcContextFromTransform);

s32 randomBurstNpcHandlerVariant(struct D_80130BB8_type *self, u16 arg1, void *arg2);

s32 spawnRandomBurstNpcVariantWrapper(void *arg0) {
    return spawnNpcOfType(randomBurstNpcHandlerVariant, arg0, 4U, 0xFU) & 0xFFFF;
}

void destroyNpcSlotByIndexU16(s32 arg0) {
    destroyNpcSlotByIndex(arg0);
}

INCLUDE_ASM("asm/nonmatchings/main/40F10", attachChildNpcByIndex);

INCLUDE_ASM("asm/nonmatchings/main/40F10", assignNpcTargetAndPosition);

INCLUDE_ASM("asm/nonmatchings/main/40F10", setNpcForwardVectorByIndex);

INCLUDE_ASM("asm/nonmatchings/main/40F10", resolveNpcContextByIndex);

INCLUDE_ASM("asm/nonmatchings/main/40F10", fake_func_80041EEC);
