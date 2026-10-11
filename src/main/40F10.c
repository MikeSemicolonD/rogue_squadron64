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

typedef struct { s32 a, b, c; } BurstV3w;

typedef struct BurstNode {
    struct BurstNode *a;
    struct BurstNode *b;
} BurstNode;

typedef struct {
    u32 w0;
    f32 f4;
    f32 f8;
    f32 fC;
    u8 pad10[0x10];
    s32 w20;
    s32 w24;
    s32 w28;
    u8 pad2C[0x14];
    f32 f40;
    f32 f44;
    f32 f48;
    u8 pad4C[0x28];
    u16 h74;
    u8 pad76[2];
    s32 w78;
    u16 h7C;
    u8 pad7E[2];
    BurstNode n80;
    s32 w88;
    s32 w8C;
    void *p90;
    s32 w94;
    u8 pad98[4];
    u8 v9C[0x30];
    s32 wCC;
    s32 wD0;
    s32 wD4;
    s32 wD8;
    s32 wDC;
    s32 wE0;
    s32 wE4;
    u8 padE8[4];
    s32 wEC;
    u8 padF0[0x38];
    f32 f128;
    f32 f12C;
    u16 h130;
    u8 pad132[2];
    s32 w134;
    u8 pad138[8];
    u16 h140;
    u8 pad142[2];
    f32 f144;
    f32 f148;
    f32 f14C;
    f32 f150;
    f32 f154;
    f32 f158;
    f32 f15C;
    u8 b160;
} BurstNpc;

void vec3Cross(void *, void *, void *);
extern void clearStructPair2C30(void *);
extern void computeNpcGroupCentroidAndCull(void *, f32, f32 *, void *, void *);
extern void initVec4TripletFromArgs(void *, f32, f32, f32);
extern void mat34CrossRowsAndCopyPos(void *, void *, f32);
extern void setVec3At0x24(void *, f32, f32, f32);
extern void spawnNpcFormationWithRandomOrientation(void *, void *, void *, f32 *);
extern void transformVec3ByMat34(void *, void *, f32 *);
extern s32 transformVec3ToNpcLocalWithScale(void *, s32, void *, s32, s32);
extern s16 rand(void);
extern u16 D_main_bss_80139574;

s32 randomBurstNpcHandlerVariant(struct D_80130BB8_type *self, u16 arg1, void *arg2) {
    BurstNpc *s = self->unk04;
    f32 v[3];
    f32 sp28[3];
    u8 mtx[0x30];
    BurstNpc *a;
    u8 *ctx;
    u16 id;
    f32 one;
    f32 i;
    void *a2;
    f32 t;
    BurstNode **p;
    BurstNode *head;

    switch (arg1) {
    case 1:
        s = rs_malloc(0x164, 0);
        self->unk04 = s;
        zmemcpy(s, arg2, 0x80);
        s->h130 = 0xFFFF;
        s->h140 = 0xFFFF;
        *(s32 *)&s->f128 = 0;
        *(s32 *)&s->f12C = 0;
        s->w134 = 0;
        s->b160 = 0;
        s->w8C = 0;
        s->w88 = 0;
        s->n80.b = 0;
        s->n80.a = 0;
        s->p90 = &s->wCC;
        s->w94 = 0;
        s->wD4 = 0;
        s->wD0 = 0;
        s->wCC = 0;
        s->wDC = 0;
        s->wE4 = 0;
        s->wE0 = 0;
        s->wEC = 0;
        s->f150 = s->f154 = s->f158 = s->f144 = s->f148 = s->f14C = 0.0f;
        s->wD8 = s->w78 | 0x40000000;
        clearStructPair2C30(&s->wCC);
        popNpcSlotFromTail(D_main_bss_80139574, self);
        break;
    case 2:
        destroyNpcSlotChain(s->h140);
        if (s->h130 != 0xFFFF) {
            v[0] = v[1] = v[2] = 0.0f;
            computeNpcGroupCentroidAndCull(s, 10000.0f, v, NULL, NULL);
        }
        break;
    case 3:
        if (s->b160 != 0) {
            s->f128 = 0.0f;
            if (s->h130 == 0xFFFF) {
                destroyNpcSlotByIndex(self->unk16);
            }
        } else {
            s->f128 = s->f128 + *(f32 *)arg2 * (s->f40 + s->f44 * (f32)(rand() % 100) / 100.0f);
        }
        s->f12C = s->f12C + *(f32 *)arg2;
        break;
    case 4:
        a2 = arg2;
        v[0] = v[1] = v[2] = 0.0f;
        if (s->h140 != 0xFFFF && 0.0f < s->f12C) {
            id = getNextSlotNpcTypeId(s->h140);
            if (id != 0xFFFF) {
                ctx = getNpcContextField8(id);
                one = 1.0f;
                mat34CrossRowsAndCopyPos(mtx, ctx, one);
                transformVec3ByMat34(mtx, &s->f144, v);
                v[0] = v[0] - s->f4;
                s->f4 = s->f4 + v[0];
                v[1] = v[1] - s->f8;
                s->f8 = s->f8 + v[1];
                v[2] = v[2] - s->fC;
                s->fC = s->fC + v[2];
                s->f150 = v[0] / s->f12C * s->f15C;
                s->f154 = v[1] / s->f12C * s->f15C;
                s->f158 = v[2] / s->f12C * s->f15C;
                if ((s->h7C & 2) && one < s->f128) {
                    *(BurstV3w *)&s->w20 = *(BurstV3w *)(ctx + 0xC);
                    vec3Cross(s->pad2C, ctx + 0xC, ctx + 0x18);
                }
            } else {
                s->b160 = 1;
            }
        }
        v[0] = -v[0] * 0.25f;
        v[1] = -v[1] * 0.25f;
        v[2] = -v[2] * 0.25f;
        if (1.0f <= s->f128) {
            for (i = 1.0f; i <= s->f128; i += 1.0f) {
                t = i / s->f128 + -1.0f;
                sp28[0] = v[0] * t;
                sp28[1] = v[1] * t;
                sp28[2] = v[2] * t;
                spawnNpcFormationWithRandomOrientation(s, &s->f150, &s->h130, sp28);
                if (s->h74 != 0) {
                    s->h74 = s->h74 - 1;
                    if (s->h74 == 0) {
                        s->b160 = 1;
                        break;
                    }
                }
            }
            s->f128 = s->f128 - (i - 1.0f);
        }
        s->f40 = s->f40 - s->f48 * s->f12C;
        if (s->f40 < 0.0f) {
            s->b160 = 1;
        }
        s->wEC = 0;
        computeNpcGroupCentroidAndCull(s, s->f12C, v, &s->wEC, a2);
        s->f12C = 0.0f;
        if (s->wEC != 0) {
            initVec4TripletFromArgs(s->v9C, 0.25f, 0.25f, 0.25f);
            setVec3At0x24(s->v9C, s->f4, s->f8, s->fC);
            if (transformVec3ToNpcLocalWithScale(*(void **)a2, 0, &s->f4, s->w0, 0) & 0xFF) {
                head = **(BurstNode ***)a2;
                s->n80.a = head;
                if (head != NULL) {
                    head->b = &s->n80;
                }
                s->n80.b = NULL;
                **(BurstNode ***)a2 = &s->n80;
            }
        }
        break;
    case 0x1000:
        *(void **)arg2 = s;
        break;
    }
    return 1;
}

extern s32 gNpcNextOpenSlot;
extern s16 D_main_bss_80130BD4_b __asm__("D_main_bss_80130BD4");
extern s16 rand(void);
extern void quatFromAxisAngleSafe(void *, void *, f32);
extern void quatFromAxisAngle(void *, void *, f32);
extern void quatFromCardinalAxis(void *, u8, f32);
extern void quatMultiply(void *, void *, void *);
extern void rotateVec3ByQuat(void *, void *, void *);
typedef struct { u8 b0, b1, b2, b3; } SfW4;
typedef struct { s32 a, b, c; } SfV3;

u16 snImpl(u8 *d, void *arg1, void *arg2, f32 *arg3) __asm__("spawnNpcFormationWithRandomOrientation");
u16 snImpl(u8 *d, void *arg1, void *arg2, f32 *arg3) {
    u8 *s;
    u16 id;
    f32 sp10[3];
    f32 sp20[4];
    f32 sp30[4];
    f32 sp40[4];
    s32 sp50[4];
    u16 tmp;
    f32 ft;
    f32 fs;
    f32 fs2;
    s16 ri;
    u16 t28;

    id = (u16)D_main_bss_80130BD4_b;
    if (id == 0xFFFF) {
        return 0xFFFF;
    }
    if ((*(u16 *)(d + 0x7C) & 0x40) && gNpcNextOpenSlot < 4) {
        return 0xFFFF;
    }
    {
        s = (u8 *)D_main_bss_80130BD0 + (u16)id * 0x6C;
        tmp = *(u16 *)(s + 2);
        D_main_bss_80130BD4 = tmp;
        if (tmp != 0xFFFF) {
            *(u16 *)((u8 *)D_main_bss_80130BD0 + (u16)D_main_bss_80130BD4 * 0x6C) = 0xFFFF;
        }
        if (arg2 != 0) {
            *(u16 *)(s + 2) = *(u16 *)arg2;
            if (*(u16 *)(s + 2) != 0xFFFF) {
                *(u16 *)((u8 *)D_main_bss_80130BD0 + *(u16 *)(s + 2) * 0x6C) = id;
            }
            *(u16 *)(s + 0) = 0xFFFF;
            *(u16 *)arg2 = id;
        }
        *(u16 *)(s + 0x20) = *(u16 *)(d + 0x7C);
        if (*(f32 *)(d + 0x38) != 0.0f) {
            vec3Cross(sp10, d + 0x20, d + 0x2C);
            quatFromAxisAngleSafe(sp20, sp10, (f32)(s16)(rand() % 360));
            rotateVec3ByQuat(sp20, d + 0x20, sp10);
            ri = rand() % 100;
            ft = *(f32 *)(d + 0x38);
            ft *= (f32)ri;
            ft /= 100.0f;
            *(f32 *)(s + 4) = ft * sp10[0] + arg3[0];
            *(f32 *)(s + 8) = ft * sp10[1] + arg3[1];
            ft *= sp10[2];
            ft += arg3[2];
            *(f32 *)(s + 0xC) = ft;
        } else {
            *(SfV3 *)(s + 4) = *(SfV3 *)arg3;
        }
        if (*(s16 *)(d + 0x3C) != 0) {
            quatFromAxisAngle(sp20, d + 0x20, (f32)((s16)((rand() & 0xFFFF) % (s16)*(u16 *)(d + 0x3C)) - (s16)*(u16 *)(d + 0x3C) / 2));
        } else {
            quatFromCardinalAxis(sp20, 0, 0);
        }
        if (*(s16 *)(d + 0x3E) != 0) {
            quatFromAxisAngle(sp30, d + 0x2C, (f32)((s16)((rand() & 0xFFFF) % (s16)*(u16 *)(d + 0x3E)) - (s16)*(u16 *)(d + 0x3E) / 2));
        } else {
            quatFromCardinalAxis(sp30, 0, 0);
        }
        quatMultiply(sp20, sp30, sp40);
        if (*(f32 *)(d + 0x1C) != 0.0f) {
            fs = ((*(f32 *)(d + 0x1C) * (f32)(s16)(rand() % 100)) / 100.0f + 1.0f) - *(f32 *)(d + 0x1C) * 0.5f;
            rotateVec3ByQuat(sp40, d + 0x10, sp10);
            *(f32 *)(s + 0x10) = sp10[0] * fs;
            *(f32 *)(s + 0x14) = sp10[1] * fs;
            *(f32 *)(s + 0x18) = sp10[2] * fs;
        } else {
            rotateVec3ByQuat(sp40, d + 0x10, (f32 *)(s + 0x10));
        }
        if (arg1 != 0) {
            *(f32 *)(s + 0x10) = *(f32 *)(s + 0x10) + ((f32 *)arg1)[0];
        }
        *(f32 *)(s + 0x14) = *(f32 *)(s + 0x14) + ((f32 *)arg1)[1];
        *(f32 *)(s + 0x18) = *(f32 *)(s + 0x18) + ((f32 *)arg1)[2];
        ft = *(f32 *)(d + 0x4C) + (*(f32 *)(d + 0x50) * (f32)(s16)(rand() % 100)) / 100.0f;
        *(f32 *)(s + 0x1C) = ft;
        if (*(u16 *)(d + 0x7C) & 0x40) {
            *(f32 *)(s + 0x28) = ft;
            sp50[0] = (s32)d;
            sp50[1] = (s32)s;
            sp50[2] = 0;
            sp50[3] = 0;
            *(u16 *)(s + 0x24) = spawnNpcOfType(*(npc_update *)(d + 0x60), sp50, (*(u16 *)(d + 0x7C) & 0x80) ? 2 : 1, 0xF);
            *(u16 *)(s + 0x26) = findFreeNpcSlotByKey((struct D_80130BB8_type *)0xFFFF, *(u16 *)(s + 0x24));
        } else {
            *(u16 *)(s + 0x44) = 0;
            if (*(u16 *)(d + 0x7C) & 8) {
                *(u16 *)(s + 0x44) |= rand() & 0x1C00;
            }
            *(s32 *)(s + 0x64) = *(s32 *)(d + 0x64);
            if (*(u8 *)(d + 0x6C) >= 2) {
                *(u16 *)(s + 0x24) = *(u8 *)(d + 0x6C) << 8;
                if (*(u16 *)(d + 0x7C) & 0x30) {
                    t28 = (u32)(f32)*(u16 *)(d + 0x6E);
                } else {
                    t28 = (u32)((f32)*(u16 *)(s + 0x24) / *(f32 *)(s + 0x1C));
                }
                *(u16 *)(s + 0x28) = t28;
            } else {
                *(u16 *)(s + 0x24) = 0x100;
                *(u16 *)(s + 0x28) = 0;
            }
            *(u16 *)(s + 0x26) = 0;
            *(u16 *)(s + 0x46) = **(u16 **)(s + 0x64);
            *(s32 *)(s + 0x68) = *(s32 *)(d + 0x68);
            if (*(u8 *)(d + 0x6D) != 0) {
                *(u16 *)(s + 0x2A) = *(u8 *)(d + 0x6D) << 8;
                *(s16 *)(s + 0x2E) = (u32)((f32)*(u16 *)(s + 0x2A) / *(f32 *)(s + 0x1C));
                *(u16 *)(s + 0x44) |= 0x200;
                *(SfW4 *)(s + 0x60) = **(SfW4 **)(s + 0x68);
                *(u16 *)(s + 0x2C) = 0;
            } else {
                *(u16 *)(s + 0x2A) = 0x100;
                *(u16 *)(s + 0x2E) = 0;
                *(u16 *)(s + 0x2C) = 0;
            }
            fs2 = (f32)*(u16 *)(d + 0x70) * 0.00390625f;
            *(f32 *)(s + 0x58) = fs2;
            *(f32 *)(s + 0x54) = fs2;
            if (*(u16 *)(d + 0x72) != 0 && *(u16 *)(d + 0x72) != *(u16 *)(d + 0x70)) {
                *(s16 *)(s + 0x30) = (s32)((f32)(*(u16 *)(d + 0x72) - *(u16 *)(d + 0x70)) / *(f32 *)(s + 0x1C));
            } else {
                *(s16 *)(s + 0x30) = 0;
            }
            if (*(u16 *)(d + 0x7C) & 1) {
                *(u16 *)(s + 0x44) |= 0x100;
            }
        }
        return id;
    }
    return 0xFFFF;
}

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
