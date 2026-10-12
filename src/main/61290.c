#include "common.h"
#include "common_types.h"
#include "rs_math.h"

typedef struct { f32 x, y, z; } RseV3;
typedef struct RseCtx {
    struct RseCtx *next;
    struct RseCtx *prev;
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[2];
    u16 f10;
    u16 f12;
    u8 pad14[0xC];
    f32 f20;
    f32 f24;
    u8 pad28[8];
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
} RseCtx;
typedef struct {
    u8 pad0[4];
    RseCtx *ctx;
    u8 pad8[0xE];
    u16 f16;
} RseNpc;
typedef struct {
    f32 *pos;
    u8 pad4[4];
    f32 f8;
} RseParams;
typedef struct {
    s32 f0;
    u8 pad4[0x14];
    f32 f18;
    f32 f1C;
    f32 f20;
    u8 pad24[0x24];
    struct { u8 pad[0x20]; RseCtx *head; } *f48;
} RseUpdate;
extern u16 D_main_bss_80139574;
extern u16 rseTblA[] __asm__("D_main_bss_80139870");
extern u16 rseTblB[] __asm__("D_main_bss_80139898");
extern u8 D_main_bss_80130B63;
extern s32 rand();
extern void popNpcSlotFromTail(u16, void *);
extern void destroyNpcSlotByIndex(u16);
extern u8 transformVec3ToNpcLocalWithScale(s32, s32, void *, f32, s32);

s32 rseImpl(RseNpc *npc, u16 cmd, void *arg) __asm__("randomlyScaledEffectNpcHandler");
s32 rseImpl(RseNpc *npc, u16 cmd, void *arg) {
    RseCtx *c = npc->ctx;

    switch (cmd) {
    case 1: {
        RseParams *p = arg;
        f32 s;
        c->f10 = 0x100;
        c->f10 |= rand() & 0x1C00;
        s = ((f32)(rand() & 0xFF) / 255.0f + 2.5f) * (p->f8 * 0.25f);
        c->f20 = c->f24 = s;
        *(RseV3 *)&c->f30 = *(RseV3 *)p->pos;
        *(f32 *)((u8 *)c + 0x3C) = 0.0f;
        popNpcSlotFromTail(D_main_bss_80139574, npc);
        return 1;
    }
    case 2:
        break;
    case 3: {
        f32 *dt = arg;
        c->f3C = c->f3C + *dt * 20.0f;
        if ((s32)c->f3C >= 20) {
            destroyNpcSlotByIndex(npc->f16);
            return 1;
        }
        break;
    }
    case 4: {
        RseUpdate *q = arg;
        if (transformVec3ToNpcLocalWithScale(q->f0, 0, &c->f30, 1.0f, 0)) {
            *(u16 *)((u8 *)c + 0x12) = rseTblA[(s32)c->f3C];
            if (D_main_bss_80130B63 != 0) {
                s32 t = (s32)c->f3C;
                if (t < 19) {
                    if (0.5f < c->f3C - (f32)t) {
                        c->f12 = rseTblB[t];
                    }
                }
            }
            c->f8 = (s32)((c->f30 - q->f18) * 256.0f);
            c->fA = (s32)((c->f34 - q->f1C) * 256.0f);
            c->fC = (s32)((c->f38 - q->f20) * 256.0f);
            c->next = q->f48->head;
            if (c->next != 0) {
                c->next->prev = c;
            }
            c->prev = 0;
            q->f48->head = c;
        }
        break;
    }
    }
    return 1;
}

typedef struct { f32 x, y, z; } V3;
typedef struct ColorFxCtx {
    struct ColorFxCtx *next;
    struct ColorFxCtx *prev;
    s16 f8;
    s16 fA;
    s16 fC;
    u8 padE[2];
    u16 f10;
    u16 f12;
    u8 pad14[0xC];
    f32 f20;
    f32 f24;
    u8 pad28[4];
    u8 c2C;
    u8 c2D;
    u8 c2E;
    u8 c2F;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    u8 f50;
} ColorFxCtx;

typedef struct {
    u8 pad0[4];
    ColorFxCtx *ctx;
    u8 pad8[0xE];
    u16 f16;
} ColorFxNpc;

typedef struct {
    f32 *pos;
    u8 *color;
    f32 f8;
    f32 fC;
    u8 f10;
} ColorFxParams;

typedef struct {
    s32 f0;
    u8 pad4[0x14];
    f32 f18;
    f32 f1C;
    f32 f20;
    u8 pad24[0x24];
    struct { u8 pad[0x20]; ColorFxCtx *head; } *f48;
} ColorFxUpdate;

extern u8 D_main_bss_80139900[];
extern u8 D_main_bss_80139910[];
extern u16 D_main_bss_80139574;
extern s32 rand();
extern void popNpcSlotFromTail(u16, void *);
extern void destroyNpcSlotByIndex(u16);
extern u8 transformVec3ToNpcLocalWithScale(s32, s32, void *, f32, s32);

s32 randomlyScaledColoredEffectNpcHandler(ColorFxNpc *npc, u16 cmd, void *arg) {
    ColorFxCtx *c = npc->ctx;

    switch (cmd) {
    case 1: {
        ColorFxParams *p = arg;
        f32 s;
        f32 s2;
        u8 t;
        c->f10 = 0x300;
        c->f10 |= rand() & 0x1C00;
        c->c2E = 0xFF;
        c->c2D = 0xFF;
        c->c2C = 0xFF;
        c->c2F = 0xFF;
        c->f44 = 255.0f;
        c->f50 = p->f10;
        switch (c->f50) {
        case 0:
        default:
            c->f12 = *(u16 *)D_main_bss_80139900;
            break;
        case 1:
            c->f12 = *(u16 *)D_main_bss_80139910;
            break;
        }
        s = (FABSF_VAL(((f32)(rand() & 0x7F) - 64.0f) * 0.00390625f) + 0.625f) * p->f8;
        c->f48 = s;
        c->f4C = p->fC * 0.875f - c->f48;
        c->f20 = c->f24 = c->f48;
        if (p->color != 0) {
            c->c2C = p->color[0];
            c->c2D = p->color[1];
            c->c2E = p->color[2];
        }
        *(V3 *)&c->f30 = *(V3 *)p->pos;
        *(volatile f32 *)&c->f3C = 0.0f;
        *(volatile f32 *)&c->f40 = 0.0f;
        popNpcSlotFromTail(D_main_bss_80139574, npc);
        return 1;
    }
    case 2:
        break;
    case 3: {
        f32 *dt = arg;
        c->f40 = c->f40 + *dt;
        switch (c->f50) {
        case 0:
        default:
            c->f3C = c->f3C + *dt * 20.0f;
            c->f48 = c->f48 + c->f4C * *dt;
            c->f20 = c->f24 = c->f48;
            if (c->f40 >= 0.5f) {
                c->f44 = c->f44 - *dt * 512.0f;
                if (c->f44 > 0.0f) {
                    c->c2F = (u32)c->f44;
                } else {
                    destroyNpcSlotByIndex(npc->f16);
                    return 1;
                }
            }
            break;
        case 1:
            c->f3C = 2.0f * (c->f40 * 8.0f);
            c->f44 = 255.0f - 2.0f * (c->f40 * 255.0f);
            c->f48 = c->f48 + 2.0f * (c->f4C * *dt);
            c->f20 = c->f24 = c->f48;
            if (c->f40 <= 0.5f) {
                c->c2F = (u32)c->f44;
            } else {
                destroyNpcSlotByIndex(npc->f16);
                return 1;
            }
            break;
        }
        break;
    }
    case 4: {
        ColorFxUpdate *q = arg;
        if (transformVec3ToNpcLocalWithScale(q->f0, 0, &c->f30, 1.0f, 0)) {
            switch (c->f50) {
            case 0:
            default: {
                u16 *tb = (u16 *)D_main_bss_80139900;
                c->f12 = tb[(s32)c->f3C % 6];
                break;
            }
            case 1: {
                u16 *tb = (u16 *)D_main_bss_80139910;
                c->f12 = tb[(s32)c->f3C % 8];
                break;
            }
            }
            c->f8 = (s32)((c->f30 - q->f18) * 256.0f);
            c->fA = (s32)((c->f34 - q->f1C) * 256.0f);
            c->fC = (s32)((c->f38 - q->f20) * 256.0f);
            c->next = q->f48->head;
            if (c->next != 0) {
                c->next->prev = c;
            }
            c->prev = 0;
            q->f48->head = c;
        }
        break;
    }
    }
    return 1;
}

typedef struct {
    f32 *pos;
    f32 scale;
    u8 *color;
} MinFxParams;

extern u8 D_main_bss_8013990C[];

s32 mrnImpl(ColorFxNpc *npc, u16 cmd, void *arg) __asm__("minimalRandomNpcHandler");
s32 mrnImpl(ColorFxNpc *npc, u16 cmd, void *arg) {
    ColorFxCtx *c = npc->ctx;

    switch (cmd) {
    case 1: {
        MinFxParams *p = arg;
        f32 s;
        c->f10 = 0x300;
        c->f10 |= rand() & 0x1C00;
        *(s32 *)((u8 *)c + 0x1C) = 0;
        c->c2C = p->color[0];
        c->c2D = p->color[1];
        c->c2E = p->color[2];
        c->f44 = p->color[3];
        c->c2F = (u32)c->f44;
        c->f12 = *(u16 *)D_main_bss_8013990C;
        c->f20 = c->f24 = ((f32)(rand() & 0xFF) / 255.0f + 2.5f) * (p->scale * 0.25f);
        *(V3 *)&c->f30 = *(V3 *)p->pos;
        *(s32 *)&c->f3C = 0;
        *(s32 *)&c->f40 = 0;
        popNpcSlotFromTail(D_main_bss_80139574, npc);
        return 1;
    }
    case 2:
        break;
    case 3: {
        f32 *dt = arg;
        c->f40 = c->f40 + *dt;
        c->f44 = c->f44 - *dt * 512.0f;
        c->f20 = c->f20 * 1.1f;
        c->f24 = c->f24 * 1.1f;
        c->f34 = c->f34 - *dt;
        if (c->f44 > 0.0f) {
            c->c2F = (u32)c->f44;
        } else {
            destroyNpcSlotByIndex(npc->f16);
            return 1;
        }
        break;
    }
    case 4: {
        ColorFxUpdate *q = arg;
        if (transformVec3ToNpcLocalWithScale(q->f0, 0, &c->f30, 1.0f, 0)) {
            c->f8 = (s32)((c->f30 - q->f18) * 256.0f);
            c->fA = (s32)((c->f34 - q->f1C) * 256.0f);
            c->fC = (s32)((c->f38 - q->f20) * 256.0f);
            c->next = q->f48->head;
            if (c->next != 0) {
                c->next->prev = c;
            }
            c->prev = 0;
            q->f48->head = c;
        }
        break;
    }
    }
    return 1;
}

extern u8 D_main_bss_80130B63;
extern u8 D_main_bss_80139870[];
extern u8 D_main_bss_80139898[];
extern u8 D_main_bss_80139900[];
extern u8 D_main_bss_80139910[];
extern u8 D_main_bss_8013990C[];
extern u8 D_main_bss_801398C0[16][4];
extern u8 D_main_bss_80139920[16][4];
extern s32 gCurrentLevel;
extern s32 isCraftAvailableByIdx(s32);
extern void loadAssetAndIterateSubchunks(char *, char *, u8 *, s32, s32);
extern u8 *load_asset(char *);
extern void rs_free(void *);

void loadExplosionTextures(void) {
    u8 *pal;
    s32 i;
    s8 alpha;
    u8 t;

    if (D_main_bss_80130B63 == 0) {
        loadAssetAndIterateSubchunks("explo2_IMGS", "explo_tex", D_main_bss_80139870, 0, isCraftAvailableByIdx(5) ? 0 : 3);
    } else {
        loadAssetAndIterateSubchunks("explo2_IMGS", "explo_tex", D_main_bss_80139870, 0, 0);
        loadAssetAndIterateSubchunks("explo2hi_IMGS", "explh_tex", D_main_bss_80139898, 0, 0);
    }
    loadAssetAndIterateSubchunks("ionexp_IMGS", "iexplo_tx", D_main_bss_80139900, 0, 0);
    loadAssetAndIterateSubchunks("ionex2_IMGS", "iexpl2_tx", D_main_bss_80139910, 0, 0);
    loadAssetAndIterateSubchunks("smkexp_IMGS", "sexplo_tx", D_main_bss_8013990C, 0, 0);
    pal = load_asset("smkexp_PAL");
    for (i = 0; i < 16; i++) {
        D_main_bss_80139920[i][0] = pal[gCurrentLevel * 4 + 0];
        D_main_bss_80139920[i][1] = pal[gCurrentLevel * 4 + 1];
        t = pal[gCurrentLevel * 4 + 2];
        D_main_bss_80139920[i][3] = -1 - i * 16;
        D_main_bss_80139920[i][2] = t;
        D_main_bss_801398C0[i][0] = pal[gCurrentLevel * 4 + 0x80];
        D_main_bss_801398C0[i][1] = pal[gCurrentLevel * 4 + 0x81];
        t = pal[gCurrentLevel * 4 + 0x82];
        D_main_bss_801398C0[i][3] = -1 - i * 16;
                D_main_bss_801398C0[i][2] = t;
    }
    rs_free(pal);
}

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
} RandomScaleEffectParams;

u16 spawnNpcOfType(void *handler, void *params, u32 arg2, u8 arg3);
void randomlyScaledEffectNpcHandler(void);
s32 randomlyScaledColoredEffectNpcHandler(ColorFxNpc *, u16, void *);
void minimalRandomNpcHandler(void);

void spawnRandomScaleEffectDefault(s32 arg0) {
    RandomScaleEffectParams params;

    params.unk0 = arg0;
    params.unk8 = 1.0f;
    spawnNpcOfType(randomlyScaledEffectNpcHandler, &params, 1, 0xA);
}

void spawnNpcType0xAFromTemplate(s32 arg0, f32 scale) {
    RandomScaleEffectParams params;

    params.unk0 = arg0;
    params.unk8 = scale;
    params.unkC = scale;
    spawnNpcOfType(randomlyScaledEffectNpcHandler, &params, 1, 0xA);
}

void spawnRandomScaleColoredEffectAltVariant(s32 arg0, f32 scale) {
    RandomScaleEffectParams params;

    params.unk0 = arg0;
    params.unk10 = 0;
    params.unk4 = 0;
    params.unk8 = scale * 0.4f;
    params.unkC = scale * 0.85f;
    spawnNpcOfType(randomlyScaledColoredEffectNpcHandler, &params, 1, 0xA);
}

void spawnRandomScaleColoredEffectFromCaller(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct {
        s32 unk0;
        s32 unk4;
        s32 unk8;
        s32 unkC;
        u8 unk10;
    } params;

    params.unk0 = arg0;
    params.unk8 = arg1;
    params.unkC = arg2;
    params.unk4 = arg3;
    params.unk10 = 1;
    spawnNpcOfType(randomlyScaledColoredEffectNpcHandler, &params, 1, 0xA);
}

void spawnMinimalRandomNpc(s32 arg0, s32 arg1, s32 arg2) {
    s32 params[3];

    params[0] = arg0;
    params[1] = arg1;
    params[2] = arg2;
    spawnNpcOfType(minimalRandomNpcHandler, params, 1, 0xA);
}

INCLUDE_ASM("asm/nonmatchings/main/61290", fake_func_800613B8);

INCLUDE_RODATA("asm/nonmatchings/main/61290", strLoTx);

INCLUDE_RODATA("asm/nonmatchings/main/61290", junk_8003B40C);
