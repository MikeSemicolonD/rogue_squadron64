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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB2D0", parseDatEventTriggers);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB2D0", fake_func_800AAADC);

static u32 D_mission_overlay_800A51E8[] __attribute__((section(".rodata"))) = { 0x3484FE00, 0x00641024 };
