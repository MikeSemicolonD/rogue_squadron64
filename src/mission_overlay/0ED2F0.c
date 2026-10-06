#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ED2F0", tickCraftMountedAnimationEffect);

#include "level_objectives.h"

typedef struct CmSrc {
    f32 dt;
    u8 pad4[0xC];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[0x68];
    s32 bool_idx;
    s32 bool_val;
    s32 cnt_idx;
    s32 cnt_val;
    u8 pad94[0x10];
    s32 hasRef;
    s32 refOff;
} CmSrc;

typedef struct CmRef {
    u8 pad0[0x10];
    f32 x;
    u8 pad14[4];
    f32 z;
    u8 pad1C[0xC];
    f32 dx;
    u8 pad2C[4];
    f32 dz;
} CmRef;

typedef struct CmData {
    s32 f0;
    CmSrc *src;
    f32 x;
    f32 y;
    f32 z;
    u8 pad14[0x24];
    f32 rx;
    f32 rz;
    f32 tx;
    f32 tz;
    s32 f48;
    u8 b4C;
    u8 b4D;
    u8 b4E;
} CmData;

typedef struct CmNpc {
    u8 pad0[4];
    CmData *data;
    void *self;
    u8 pad[0xA];
    u16 slot;
} CmNpc;

typedef struct CmTable {
    u8 pad[0x34];
    CmRef **refs;
} CmTable;

extern CmTable *D_main_bss_801375D8;
extern u16 D_main_bss_8013959C;
extern void popNpcSlotFromTail(u16, void *);
extern void destroyNpcSlotByIndex(u16);
extern s32 tickCraftMountedAnimationEffect(void *, f32);

s32 craftMountedAnimationNpcHandler(CmNpc *arg0, s32 arg1, CmSrc *arg2) {
    s32 msg = arg1 & 0xFFFF;
    CmData *p = arg0->data;

    switch (msg) {
    case 1: {
        CmSrc *src;
        arg0->self = (void *)((u8 *)p + 8);
        p->src = arg2;
        p->x = arg2->x;
        p->y = arg2->y;
        p->z = arg2->z;
        p->b4D = 0;
        p->f48 = 0;
        p->b4C = 0;
        p->f0 = 0;
        src = p->src;
        if (src->hasRef != 0) {
            s32 idx = *(u16 *)(src->refOff + (s32)src + 0xA6);
            CmRef *t = D_main_bss_801375D8->refs[idx];
            p->rx = t->x;
            p->rz = t->z;
            p->tx = p->rx + t->dx;
            p->tz = p->rz + t->dz;
            p->b4E = msg;
        } else {
            p->b4E = 0;
        }
        popNpcSlotFromTail(D_main_bss_8013959C, arg0);
        return 1;
    }
    case 3: {
        CmSrc *q = p->src;
        s32 b = q->bool_idx;
        f32 dt = arg2->dt;
        s32 c;
        if (b == 0 || gObjectiveBooleans[b - 1] == q->bool_val) {
            c = q->cnt_idx;
            if (c == 0 || gObjectiveCounts[c - 1] >= q->cnt_val) {
                if ((tickCraftMountedAnimationEffect(p, dt) & 0xFF) == 1) {
                    destroyNpcSlotByIndex(arg0->slot);
                }
            }
        }
        return 1;
    }
    case 12:
        p->b4D = 0;
        p->f48 = 0;
        p->b4C = 0;
    case 2:
        break;
    default:
        return 1;
    }
    return 1;
}

s32 slotDispatcherIter(u16, s32, s32);
extern u16 D_main_bss_8013959C;

void dispatchSlotActionTwelveByGlobalId(void) {
    slotDispatcherIter(D_main_bss_8013959C, 0xC, 0);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ED2F0", fake_func_800ECE04);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0ED2F0", D_mission_overlay_800A8920);
