#include "common.h"
#include "common_types.h"
#include "rs_math.h"

typedef struct {
    u16 vol;
    u8 b2;
    u8 b3;
    f32 f4;
    f32 f8;
    f32 minDist;
    f32 maxDist;
    u16 range;
    u16 falloff;
} Emitter3DDesc;

typedef struct {
    u16 type;
    u16 slot;
    u16 descIdx;
    u8 b6;
    u8 pad7;
    u8 source[0x44];
    Emitter3DDesc *desc;
} Emitter3DCtx;

typedef struct {
    u8 pad0[4];
    Emitter3DCtx *ctx;
    u8 pad8[0xE];
    u16 slot;
} Emitter3DNpc;

typedef struct {
    u16 type;
    u16 descIdx;
} Emitter3DSpawn;

typedef struct {
    u8 pad0[0x10];
    f32 f10;
    u8 pad14[0x10];
    f32 x;
    f32 y;
    f32 z;
} Emitter3DTarget;

extern Emitter3DDesc D_mission_overlay_80109B00[];
extern s32 D_main_bss_80130B58[];
extern u16 D_main_bss_80137F3C;
extern u16 D_main_bss_80139598;
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void *getNpcContextField8(u16);
u16 findFreeNpcSlotByKey(u16, u16);
s32 getPlayerField2(s32);
u16 popNpcSlotFromTail(u16, Emitter3DNpc *);
void destroyNpcSlotByIndex(u16);
void destroyNpcSlotChain(u16);
void factor5RemoveListNode(void *);
u16 getNextSlotNpcTypeId(u16);
s32 updateActive3DAudioSource(void *, void *, void *, u8);
s32 mostlyMusyxFlagGatedHelper(void *);
void safeLookup3DSoundEntry(s32, u16);

s32 attached3DSoundEmitterNpcHandler(Emitter3DNpc *npc, u16 action, Emitter3DSpawn *spawn) {
    Emitter3DCtx *c;
    Emitter3DDesc *d;
    Emitter3DTarget *t;
    u16 vol;
    u16 id;
    s32 v;
    s32 r;
    f32 dist;
    c = npc->ctx;
    d = c->desc;
    switch (action) {
    case 1:
        c->type = spawn->type;
        c->descIdx = spawn->descIdx;
        c->b6 = 0;
        d = &D_mission_overlay_80109B00[c->descIdx];
        c->desc = d;
        t = getNpcContextField8(c->type);
        if (t == NULL) {
        destroy:
            destroyNpcSlotByIndex(npc->slot);
            return 1;
        }
        c->slot = findFreeNpcSlotByKey(npc->slot, c->type);
        if (!(D_main_bss_80130B58[0] & 2) || c->descIdx != 3 || c->type != (u16)getPlayerField2(0)) {
            vol = d->vol;
        } else {
            vol = 0x78;
        }
        play3DSoundEvent((s32)c->source, t, &t->x, d->f8, d->f4, 0xF, vol, d->b3, d->b2);
        popNpcSlotFromTail(D_main_bss_80139598, npc);
        return 1;
    case 2:
        destroyNpcSlotChain(c->slot);
        factor5RemoveListNode(c->source);
        return 1;
    case 3:
        id = getNextSlotNpcTypeId(c->slot);
        if (id == 0xFFFF) {
            goto destroy;
        }
        t = getNpcContextField8(id);
        if (t == NULL) {
            goto destroy;
        }
        if (id == (u16)getPlayerField2(0) && (D_main_bss_80137F3C & 0x100)) {
            updateActive3DAudioSource(c->source, t, &t->x, 0);
            return 1;
        }
        updateActive3DAudioSource(c->source, t, &t->x, d->b3);
        v = (s32)(-t->f10 * d->falloff + 8192.0f);
        SQRTF(dist, t->x * t->x + t->y * t->y + t->z * t->z);
        v = v + (dist + 0.5f - d->minDist) / (d->maxDist - d->minDist) * d->range;
        if (v >= 0) {
            r = 0x3FFF;
            if (v < 0x4000) {
                r = v;
            }
        } else {
            r = 0;
        }
        v = r;
        safeLookup3DSoundEntry(mostlyMusyxFlagGatedHelper(c->source), v);
        return 1;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C00A0", fake_func_800BF784);

static u32 D_mission_overlay_800A6248[] __attribute__((section(".rodata"))) = { 0x03A0F021, 0x00801021 };
