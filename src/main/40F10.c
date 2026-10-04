#include "common.h"
#include "common_types.h"

#include "main/3F160.h"
#include "main/40F10.h"

INCLUDE_ASM("asm/nonmatchings/main/40F10", allocAndInitParticlePool);

INCLUDE_ASM("asm/nonmatchings/main/40F10", randomBurstNpcHandlerVariant);

INCLUDE_ASM("asm/nonmatchings/main/40F10", spawnNpcFormationWithRandomOrientation);

INCLUDE_ASM("asm/nonmatchings/main/40F10", computeNpcGroupCentroidAndCull);

INCLUDE_ASM("asm/nonmatchings/main/40F10", spawnRandomBurstNpc);

s32 rs_free(s32);
extern s32 D_main_bss_80130BD0;
extern s32 D_main_bss_80130C04;
extern s32 D_main_bss_80130C08;

void freeNpcBurstSpawnerTables(void) {
    rs_free(D_main_bss_80130BD0);
    rs_free(D_main_bss_80130C08);
    rs_free(D_main_bss_80130C04);
}

INCLUDE_ASM("asm/nonmatchings/main/40F10", initNpcContextFromTransform);

s32 randomBurstNpcHandlerVariant(struct D_80130BB8_type *self, u16 arg1, void *arg2);

s32 spawnRandomBurstNpcVariantWrapper(void *arg0) {
    return spawnNpcOfType(randomBurstNpcHandlerVariant, arg0, 4U, 0xFU) & 0xFFFF;
}

void destroyNpcSlotByIndexU16(s32 arg0) {
    destroyNpcSlotByIndex(arg0);
}

typedef struct {
    u8 pad0[0x134];
    s32 children[3];
} AttachNpcCtx;
void attachChildNpcByIndex(u16 idx, s32 child) {
    AttachNpcCtx *ctx = NULL;
    s32 i;

    if (idx != 0xFFFF) {
        slotDispatcherIter(idx, 0x1000, &ctx);
        if (ctx != NULL) {
            for (i = 0; i < 2; i++) {
                if (ctx->children[i] == 0) {
                    ctx->children[i] = child;
                    ctx->children[i + 1] = 0;
                    break;
                }
            }
        }
    }
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} NpcTargetVec3;
void assignNpcTargetAndPosition(u16 idx, u16 key, NpcTargetVec3 *pos, f32 arg3) {
    u8 *ctx = NULL;

    if (idx != 0xFFFF && key != 0xFFFF) {
        slotDispatcherIter(idx, 0x1000, &ctx);
        if (ctx != NULL) {
            if (*(u16 *)(ctx + 0x140) == 0xFFFF) {
                *(u16 *)(ctx + 0x140) = findFreeNpcSlotByKey((struct D_80130BB8_type *)(u32)idx, key);
            }
            if (pos != NULL) {
                *(NpcTargetVec3 *)(ctx + 0x144) = *pos;
            }
            *(f32 *)(ctx + 0x15C) = arg3;
        }
    }
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} NpcFwdVec3;
void setNpcForwardVectorByIndex(u16 idx, NpcFwdVec3 *v) {
    u8 *ctx = NULL;

    if (idx != 0xFFFF) {
        slotDispatcherIter(idx, 0x1000, &ctx);
        if (ctx != NULL) {
            *(NpcFwdVec3 *)(ctx + 4) = *v;
        }
    }
}

void *resolveNpcContextByIndex(u16 idx) {
    void *ctx = NULL;

    if (idx != 0xFFFF) {
        slotDispatcherIter(idx, 0x1000, &ctx);
        if (ctx != NULL) {
            return ctx;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/main/40F10", fake_func_80041EEC);
