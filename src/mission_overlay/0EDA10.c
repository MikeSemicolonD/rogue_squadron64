#include "common.h"

#include "common_types.h"

typedef struct {
    u8 pad0[2];
    u8 type;
    u8 pad3[3];
    u16 f6;
    u8 pad8[8];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[0xC];
    s32 f28;
    s32 spawned;
    s32 f30;
    s32 boolIdx;
    s32 countIdx;
    s32 countMin;
    u8 pad40[0x2C];
    s32 f6C;
    s32 maxSpawned;
    f32 interval;
    s32 namesOff;
    s32 randomName;
    s32 targetOff;
} DatSpawnItem;

typedef struct {
    DatSpawnItem *item;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    u8 pad1C[0xC];
    f32 f28;
    f32 f2C;
    f32 f30;
    f32 timer;
    s32 outOfRange;
} DatSpawnCtx;

typedef struct {
    u8 pad0[4];
    DatSpawnCtx *ctx;
    void *pos;
    u8 padC[0xA];
    u16 slot;
} DatSpawnNpc;

typedef struct {
    char *name;
    DatSpawnItem *item;
    void *pos;
    void *target;
    s32 *f30;
    s32 *spawned;
} DatSpawnParams;

extern s32 gObjectiveCounts[0x80];
extern u8 gObjectiveBooleans[0x80];
extern u16 D_main_bss_80139574[];
u16 popNpcSlotFromTail(u16, DatSpawnNpc *);
void destroyNpcSlotByIndex(u16);
void parseDatItemCommon(DatSpawnItem *, void *);
void copyRandomPipeDelimitedField(char *, char *);
s32 copyPipeDelimitedField(char *, s32, char *);
void *getLevelDatItemByName(char *);
u8 isPointInsideTriggerVolume(void *, f32);
void spawnDatStructureNpcByType(DatSpawnParams *);
s32 isNpcWithinActiveReferenceRange(void *);
void dispatchSlotAction5IfActive(DatSpawnNpc *, void *);

s32 datItemActorNpcHandler(DatSpawnNpc *npc, u16 action, void *arg) {
    char buf[0x100];
    DatSpawnParams p;
    DatSpawnCtx *c;
    DatSpawnItem *it;
    DatSpawnItem *found;
    f32 dt;
    char *names;

    c = npc->ctx;
    switch (action) {
    case 1:
        c->item = arg;
        c->f4 = ((DatSpawnItem *)arg)->x;
        c->f8 = ((DatSpawnItem *)arg)->y;
        c->fC = ((DatSpawnItem *)arg)->z;
        c->f10 = c->f14 = c->f18 = 0.0f;
        c->f28 = c->f2C = c->f30 = 0.0f;
        npc->pos = &c->f4;
        popNpcSlotFromTail(D_main_bss_80139574[0], npc);
        c->outOfRange = 0;
        c->timer = 0.0f;
        break;
    case 2:
        c->item->f6 = 0xFFFF;
        if (c->item->f30 < c->item->f6C || c->item->f6C <= 0) {
            parseDatItemCommon(c->item, &c->item->x);
        }
        return 1;
    case 3:
        dt = *(f32 *)arg;
        if (c->item->boolIdx != 0 && gObjectiveBooleans[c->item->boolIdx - 1] == 0) {
            return 1;
        }
        if (c->item->countIdx != 0 && gObjectiveCounts[c->item->countIdx - 1] < c->item->countMin) {
            return 1;
        }
        if (c->item->f30 >= c->item->f6C && c->item->f6C > 0) {
        destroy:
            destroyNpcSlotByIndex(npc->slot);
            return 1;
        }
        it = c->item;
        if (it->spawned < it->maxSpawned && (it->spawned + it->f30 < it->f6C || it->f6C <= 0)) {
            if (c->timer <= 0.0f) {
                names = (char *)(it->namesOff + (s32)it);
                if (it->randomName != 0) {
                    copyRandomPipeDelimitedField(names, buf);
                } else {
                    c->item->f28 = copyPipeDelimitedField(names, it->f28, buf);
                }
                found = getLevelDatItemByName(buf);
                switch (found->type) {
                case 3:
                    p.item = found;
                    p.pos = &found->x;
                    break;
                case 6:
                    p.item = found;
                    p.pos = &found->x;
                    break;
                case 7:
                    p.item = found;
                    p.pos = &found->x;
                    break;
                default:
                    p.item = NULL;
                    break;
                }
                if (p.item != NULL && !isPointInsideTriggerVolume(p.pos, 2.0f)) {
                    p.name = buf;
                    p.target = getLevelDatItemByName((char *)(c->item->targetOff + (s32)c->item));
                    p.f30 = &c->item->f30;
                    p.spawned = &c->item->spawned;
                    c->item->spawned++;
                    spawnDatStructureNpcByType(&p);
                    c->timer = c->item->interval;
                }
            } else {
                c->timer = c->timer - dt;
            }
        }
        if (isNpcWithinActiveReferenceRange(&c->f4)) {
            c->outOfRange = 0;
            break;
        }
        if (++c->outOfRange < 0x15) {
            break;
        }
        goto destroy;
    case 7:
        dispatchSlotAction5IfActive(npc, arg);
        break;
    default:
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDA10", fake_func_800ED148);
