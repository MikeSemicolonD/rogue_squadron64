#include "common.h"
#include "common_types.h"

#include "main/3F160.h"
#include "main/40F10.h"

extern s32 D_main_bss_80130BD0;
extern s16 D_main_bss_80130BD4;
extern s32 D_main_bss_80130C04;
extern s32 D_main_bss_80130C08;
s32 loadAssetAndIterateSubchunks(char *, char *, u8 *, s32, s32);
s32 load_asset(char *);

typedef struct { s16 prev; s16 next; u8 pad[0x68]; } PartCell;

void allocAndInitParticlePool(void) {
    PartCell *p;
    s32 i;
    u8 *pal;

    p = rs_malloc(0x3600, 0);
    D_main_bss_80130BD0 = (s32)p;
    i = 0;
    do {
        p[i].prev = i != 0 ? i - 1 : -1;
        p[i].next = i != 0x7f ? i + 1 : -1;
        i++;
    } while (i < 0x80);
    D_main_bss_80130BD4 = 0;
    D_main_bss_80130C08 = loadAssetAndIterateSubchunks("part_spr", 0, 0, 0, 0);
    D_main_bss_80130C04 = load_asset("part_pal");
    i = 0;
    do {
        pal = (u8 *)(i * 4 + D_main_bss_80130C04);
        i++;
        pal[3] = pal[0x200];
    } while (i < 0x80);
}

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

void vec3Cross(void *, void *, void *);

typedef struct {
    s32 a, b, c;
} NpcV3w;

typedef struct {
    f32 f0;
    NpcV3w v4;
    f32 f10, f14, f18, f1C;
    s32 w20, w24;
    f32 f28, f2C;
    s32 w30, w34;
    f32 f38;
    s16 h3C, h3E;
    f32 f40, f44, f48, f4C, f50, f54, f58, f5C;
    s32 w60;
    s32 w64;
    s32 w68;
    u8 b6C, b6D;
    u8 pad6E[2];
    s16 h70, h72, h74, h76;
    s32 w78;
    s16 h7C;
} NpcCtxInit;

__asm__(".section .rodata\n.globl D_main_8003A4B0\nD_main_8003A4B0:\n.word 0x3F800000\n.globl D_main_8003A4B4\nD_main_8003A4B4:\n.word 0x41200000\n.globl D_main_8003A4B8\nD_main_8003A4B8:\n.word 0x40000000\n.globl D_main_8003A4BC\nD_main_8003A4BC:\n.word 0x3F800000\n.globl D_main_8003A4C0\nD_main_8003A4C0:\n.word 0x3F333333\n.globl D_main_8003A4C4\nD_main_8003A4C4:\n.word 0x40A00000\n.word 0x00220821\n.word 0x8C30A770\n.section .text");

void initNpcContextFromTransform(NpcCtxInit *self, u8 *tf) {
    f32 one;
    f32 c10;
    f32 c2;
    f32 c1;
    f32 c07;
    f32 c5;
    f32 zero;
    s32 g;

    if (tf != NULL) {
        self->v4 = *(NpcV3w *)tf;
        *(NpcV3w *)&self->w20 = *(NpcV3w *)(tf + 0xC);
        vec3Cross(&self->f2C, tf + 0xC, tf + 0x18);
    } else {
        __asm__ volatile("lwc1 %0, D_main_8003A4B0" : "=f"(one));
        self->w20 = 0;
        self->w24 = 0;
        self->w30 = 0;
        self->w34 = 0;
        self->f28 = one;
        self->f2C = one;
    }
    g = D_main_bss_80130C08;
    __asm__ volatile("mtc1 $zero, %0" : "=f"(zero));
    __asm__ volatile("lwc1 %0, D_main_8003A4B4" : "=f"(c10));
    __asm__ volatile("lwc1 %0, D_main_8003A4B8" : "=f"(c2));
    __asm__ volatile("lwc1 %0, D_main_8003A4BC" : "=f"(c1));
    __asm__ volatile("lwc1 %0, D_main_8003A4C0" : "=f"(c07));
    __asm__ volatile("lwc1 %0, D_main_8003A4C4" : "=f"(c5));
    self->h70 = 0xC;
    self->h3E = 0;
    self->h3C = 0;
    self->w68 = 0;
    self->b6C = 0;
    self->b6D = 0;
    self->h72 = 0;
    self->h74 = 0;
    self->h7C = 1;
    self->w78 = 0;
    self->f18 = zero;
    self->f14 = zero;
    self->f10 = zero;
    self->f1C = zero;
    self->f38 = zero;
    self->f40 = c10;
    self->f44 = zero;
    self->f48 = zero;
    self->f4C = c2;
    self->f50 = zero;
    self->f54 = zero;
    self->f58 = c1;
    self->f5C = c07;
    *(volatile s32 *)&self->w64 = g;
    *(volatile f32 *)&self->f0 = c5;
}

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
