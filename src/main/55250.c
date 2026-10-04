#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/55250", tickWrappingTimerAccumulatorList);

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

INCLUDE_ASM("asm/nonmatchings/main/55250", setPoolEntryPhaseAndMarkActive);

INCLUDE_ASM("asm/nonmatchings/main/55250", setPoolEntryPhase);

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

INCLUDE_ASM("asm/nonmatchings/main/55250", registerTextureAnimSlot);

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
    __asm__("lwc1 %0, D_main_8003AD14" : "=f"(wrap));
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
