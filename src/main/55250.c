#include "common.h"
#include "common_types.h"

typedef struct {
    u8 *mat;
    s16 frameCount;
    u16 flags;
    u32 frame;
    u32 phase;
} PoolEntryT;
u8 *getTextureDataByMaterialId(u16);
void uploadTextureDescriptorData(void *, void *);
extern s32 D_main_bss_80137C80;
extern s32 D_main_bss_80137C84;

void tickWrappingTimerAccumulatorList(f32 dt) {
    s32 n;
    PoolEntryT *p;
    PoolEntryT *e;
    s32 i;
    u16 idx;

    n = D_main_bss_80137C80;
    p = (PoolEntryT *)D_main_bss_80137C84;
    e = p;
    for (i = n; i > 0; i--, e++) {
        if (e->flags & 0x4000) {
            idx = e->frame >> 8;
            e->frame = e->frame + e->phase * dt;
            if (idx != (e->frame >> 8)) {
                idx = (e->frame >> 8) % e->frameCount;
                *(u8 **)(e->mat + 0x10) = getTextureDataByMaterialId(*(u16 *)e->mat);
                uploadTextureDescriptorData(e->mat, e->mat + 0x14 + *(s32 *)(e->mat + 0xC) * idx);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/55250", loadAssetIntoNewSlot);

INCLUDE_ASM("asm/nonmatchings/main/55250", allocAnimationPhasePool);

s32 rs_free(s32);
extern s32 D_main_bss_80137C80;
extern s32 D_main_bss_80137C84;

void freeAnimationPhasePool(void) {
    s32 var_s0;
    void *temp_a0;

    var_s0 = 0;
    if (D_main_bss_80137C80 > 0) {
        do {
            temp_a0 = (var_s0 * 0x10) + D_main_bss_80137C84;
            if ((*(u16 *)((u8 *)(temp_a0) + 6)) & 0x8000) {
                rs_free((*(s32 *)((u8 *)(temp_a0) + 0)));
            }
            var_s0 += 1;
        } while (var_s0 < D_main_bss_80137C80);
    }
    rs_free(D_main_bss_80137C84);
}

typedef struct { s32 unk0; s16 frameCount; u16 flags; u32 frame; u32 phase; } PoolEntryP;

void setPoolEntryPhaseAndMarkActive(u16 idx, f32 phase, s32 flags) {
    if (idx < D_main_bss_80137C80) {
        ((PoolEntryP *)D_main_bss_80137C84)[idx].phase = phase * 256.0f;
        ((PoolEntryP *)D_main_bss_80137C84)[idx].flags = flags | 0xC000;
    }
}

void setPoolEntryPhase(u16 idx, f32 phase) {
    if (idx < D_main_bss_80137C80) {
        ((PoolEntryP *)D_main_bss_80137C84)[idx].phase = phase * 256.0f;
    }
}

typedef struct {
    s32 unk0;
    s16 frameCount;
    u16 flags;
    u32 frame;
    u32 phase;
} PoolEntry;

u32 getPoolEntryFrameIndex(u16 index) {
    return (((PoolEntry *)D_main_bss_80137C84)[index].frame >> 8) % ((PoolEntry *)D_main_bss_80137C84)[index].frameCount;
}

typedef struct {
    u8 unk0[4];
    u16 unk4;
    u8 unk6[4];
} TextureAnimSlot;

extern TextureAnimSlot D_main_bss_80137C90[];

void resetTextureAnimSlots(void) {
    s32 i;

    for (i = 7; i >= 0; i--) {
        D_main_bss_80137C90[i].unk4 = 0;
    }
}

typedef struct {
    u16 chunk;
    u8 a;
    u8 b;
    u16 flags;
    u16 speed;
    u16 phase;
} RegAnimSlot;

s32 findTextureByName(s32);
s32 getTextureAttrBySlot(s32);

s32 registerTextureAnimSlot(s32 arg0, s8 arg1, s8 arg2, f32 arg3, u16 arg4) {
    f32 scale;
    f32 wrap;
    f32 v;
    u32 val;
    u16 tex;
    s32 attr;
    RegAnimSlot *s;
    s32 i;

    scale = 256.0f;
    i = 0;
    wrap = 2147483648.0f;
    s = (RegAnimSlot *)D_main_bss_80137C90;
    do {
        if (s->flags != 0) {
            i++, s++;
        } else {
            tex = findTextureByName(arg0);
            if (tex == 0xFFFF) {
                i++, s++;
            } else {
                attr = getTextureAttrBySlot(tex);
                if ((attr & 0xFFFF) != 0xFFFF) {
                    v = arg3 * scale;
                    s->chunk = attr;
                    s->a = arg1;
                    s->b = arg2;
                    if (!(wrap <= v)) {
                        val = (s32)v;
                    } else {
                        val = (s32)(v - wrap);
                        val |= 0x80000000;
                    }
                    s->speed = val;
                    s->phase = 0;
                    s->flags = arg4;
                    return i & 0xFFFF;
                }
                i++, s++;
            }
        }
    } while (i < 8);
    return 0xFFFF;
}

typedef struct {
    u16 chunk;
    u8 a;
    u8 b;
    u16 flags;
    u16 speed;
    u16 phase;
} TlutAnimSlot;

void shiftTlutEntryWithinChunk(u16, u8, u8, s32);

void tickTextureAnimSlots(f32 dt) {
    s32 i;
    f32 wrap;
    f32 v;
    u32 val;
    TlutAnimSlot *s;

    i = 0;
    wrap = 2147483648.0f;
    s = (TlutAnimSlot *)D_main_bss_80137C90;
    do {
        if (s->flags != 0) {
            v = (f32)s->phase + dt * (f32)s->speed;
            if (!(wrap <= v)) {
                val = (s32)v;
                s->phase = val;
            } else {
                val = (s32)(v - wrap) | 0x80000000;
                s->phase = val;
            }
            if (val & 0xFF00) {
                do {
                    s->phase -= 0x100;
                    shiftTlutEntryWithinChunk(s->chunk, s->a, s->b, (s->flags & 1) ? 1 : -1);
                } while (s->phase & 0xFF00);
            }
        }
        i++;
        s++;
    } while (i < 8);
}

__asm__(".section .rodata
.word 0x025E1821, 0x8FAF05A4
.section .text");
