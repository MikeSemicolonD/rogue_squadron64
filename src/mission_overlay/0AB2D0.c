#include "common.h"

#include "common_types.h"
typedef struct {
    u16 unk0;
    u8 pad2[0xE];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} DatObjective;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 pad0C[0x18];
    f32 vx;
    f32 vy;
    f32 vz;
} MovingPoint;
typedef struct {
    u8 pad[0x3C];
    DatObjective **objs;
} DatObjectList;
extern DatObjectList *D_main_bss_801375D8;
void applyDatObjectiveTriggerEffect(DatObjective *, s32);

s32 func_mission_overlay_800AA6D0(MovingPoint *arg0, f32 dt, u16 *arg2) {
    u16 *p;
    u16 v;
    f32 x;
    f32 y;
    f32 z;
    f32 d;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 r2;
    f32 s;
    DatObjective **objs;
    DatObjective *o;
    s32 t;

    p = arg2;
    v = *p;
    if (v == 0xFFFF) {
        return 0;
    }
    {
        x = arg0->x + arg0->vx * dt;
        y = arg0->y + arg0->vy * dt;
        z = arg0->z + arg0->vz * dt;
        objs = D_main_bss_801375D8->objs;
        do {
            o = objs[v & 0xFFF];
            if (v & 0x4000) {
                d = x - o->unk10;
                s = d * d;
                dz = z - o->unk18;
                dz = dz * dz;
                d = s + dz;
            } else {
                d = x - o->unk10;
                s = d * d;
                dy = y - o->unk14;
                d = dy * dy;
                s = s + d;
                dz = z - o->unk18;
                dz = dz * dz;
                d = s + dz;
            }
            r2 = o->unk1C * o->unk1C;
            if (v & 0x8000) {
                if ((f32)(r2 + 0.0100000000000000019) < d) {
                    *p = v & 0x7FFF;
                    t = o->unk0;
                    if (t < 0x1A) {
                        if (t >= 0x18) {
                            applyDatObjectiveTriggerEffect(o, 0);
                        }
                    }
                }
            } else if (d < r2) {
                *p = v | 0x8000;
                t = o->unk0;
                if (t < 0x1A) {
                    if (t >= 0x18) {
                        applyDatObjectiveTriggerEffect(o, 1);
                    }
                }
            }
            p++;
            v = *p;
        } while (v != 0xFFFF);
    }
    return 0;
}

// best: 7 ndiff rows (sd 10), right size. Left: ply-search loop p/np copy (target loads via a copy a0, stores via a1) and d+k*2 addu order, plus beqz vs beqzl on list==NULL
#include "common_types.h"

void resetCraftSelectionCounter(void);
u16 *getPlayerRecordTargetBuffer(s32);
void *getLevelDatItemByName(char *);
void registerObjectAndResolveDatItem(u8 *);
s32 parseDatSpawnPositions(u8 *, s32);
extern s32 D_main_bss_80137CE4;

void parseDatEventTriggers(u8 **items, s32 count) {
    u16 *ply;
    u8 *it;
    u8 *list;
    u8 *end;
    u8 *d;
    u8 *t;
    s32 flag;
    s32 k;
    u16 *p;
    u16 *np;
    register u8 *q asm("$4");
    u16 v;
    u16 id;
    u8 c;

    resetCraftSelectionCounter();
    ply = getPlayerRecordTargetBuffer(0);
    *ply = 0xFFFF;
    while (count > 0) {
        it = *items;
        flag = 0;
        switch (*(u16 *)it) {
        case 0x18:
            flag = *(s32 *)(it + 0x34);
            list = (u8 *)(*(s32 *)(it + 0x58) + (s32)it);
            break;
        case 0x19:
            flag = *(s32 *)(it + 0x44);
            list = (u8 *)(*(s32 *)(it + 0x68) + (s32)it);
            t = getLevelDatItemByName((char *)(*(s32 *)(it + 0x80) + (s32)it));
            if (t != NULL) {
                *(s32 *)(t + 0x4C) |= 4;
            }
            break;
        case 0x3A:
            registerObjectAndResolveDatItem(it);
            list = NULL;
            break;
        default:
            list = NULL;
            break;
        }
        if (list != NULL && parseDatSpawnPositions(it, D_main_bss_80137CE4) == 1) {
            id = *(u16 *)(it + 4);
            if (flag != 0) {
                id |= 0x4000;
            }
            if (*list != 0) {
                list++;
                if (*list != 0) {
                    do {
                        end = list;
                        c = *end;
                        while (c != 0 && (c = *end) != '|') {
                            end++;
                            c = *end;
                        }
                        if (c == 0) {
                            end--;
                        } else {
                            *end = 0;
                        }
                        if (list[0] == 'p' && list[1] == 'l' && list[2] == 'y' && list[3] == 0) {
                            for (k = 0, np = ply; k < 0x3F; np = p + 1) {
                                p = np;
__asm__("" : "+r"(p));
                                k++;
                                if (*p == 0xFFFF) {
                                    *np = id;
                                    ply[k] = 0xFFFF;
                                    break;
                                }
                            }
                        } else {
                            d = getLevelDatItemByName((char *)list);
                            if (d != NULL) {
                                k = 0;
                                q = d;
                                for (; k < 0xB; q += 2) {
                                    v = *(u16 *)(q + 0x34);
                                    k++;
                                    if (v == 0xFFFF) {
                                        *(u16 *)(q + 0x34) = id;
                                        *(u16 *)((s32)d + (k << 1) + 0x34) = v;
                                        break;
                                    }
                                }
                            }
                        }
                        list = end + 1;
                    } while (end[1] != 0);
                }
            }
        }
        count--;
        items++;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB2D0", fake_func_800AAADC);

static u32 D_mission_overlay_800A51E8[] __attribute__((section(".rodata"))) = { 0x3484FE00, 0x00641024 };
