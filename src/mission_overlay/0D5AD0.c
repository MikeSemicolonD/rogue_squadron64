#include "common.h"

#include "common_types.h"
#include "rs_math.h"
typedef struct {
    f32 x, y, z;
} ChildVec3;

typedef struct {
    u8 pad0[0x58];
    s32 f58;
    u8 pad5C[0x48];
    s32 fA4;
    u8 padA8[0x20];
    s32 fC8[4];
} ChildTmpl;

typedef struct {
    u8 pad0[0xC];
    ChildVec3 pos;
    ChildVec3 rot;
    u8 pad24[0x10];
    ChildTmpl *tmpl;
    s32 f38;
    u8 pad3C[0x14];
    s32 f50;
    s32 f54;
    s32 f58;
    s32 f5C;
    f32 f60;
    f32 f64;
    s32 f68;
    ChildVec3 pos0;
    ChildVec3 rot0;
    u8 pad84[0x44];
    u8 fC8;
    u8 fC9;
} ChildCtx;

typedef struct {
    u8 pad0[4];
    ChildCtx *ctx;
    u8 pad8[0xC];
    u16 f14;
} ChildNpc;

typedef struct {
    u8 pad0[0xC];
    ChildTmpl *tmpl;
} ParentNpc;

extern s32 D_main_bss_80137CE4;
s32 rand(void);
void setNpcHealth(s32, void *, void *);
void setObjectDetailLevel(s32, s32);

void npcInitChildLinkedToParent(ChildNpc *npc, s32 arg1, ParentNpc *parent) {
    ChildCtx *c;
    ChildTmpl *t;

    c = npc->ctx;
    t = c->tmpl;
    setNpcHealth(c->f38, (u8 *)t + 0x6C, t);
    setObjectDetailLevel(c->f38, c->tmpl->fA4);
    if (!(npc->f14 & 0x20)) {
        if ((c->f50 = t->f58) == 0) {
            if ((c->f50 = *(s32 *)(D_main_bss_80137CE4 * 4 + (s32)t + 0xC8)) == 0) {
                c->f50 = 1;
            }
        }
        c->f54 = *(s32 *)(D_main_bss_80137CE4 * 4 + (s32)t + 0xC8);
    } else {
        t = parent->tmpl;
        if ((c->f50 = *(s32 *)(D_main_bss_80137CE4 * 4 + (s32)t + 0xC8)) == 0) {
            c->f50 = 1;
        }
        c->f54 = c->f50;
    }
    if (c->f54 > 0) {
        c->fC9 = 0;
    } else {
        c->fC9 = 2;
    }
    c->f58 = 0;
    { f32 _x = ((f32)(rand() & 0x7F) - 64.0f) / 320.0f; f32 _r; FABSF(_r, _x); c->f60 = _r; }
    c->f5C = 0;
    { f32 _x = ((f32)(rand() & 0x7F) - 64.0f) / 320.0f; f32 _r; FABSF(_r, _x); c->f64 = _r; }
    c->f68 = 0;
    c->pos0 = c->pos;
    c->rot0 = c->rot;
    c->fC8 = 0;
}

typedef struct {
    f32 x, y, z;
} SpinVec3;

void quatFromCardinalAxis(f32 *, u8, f32);
void quatMultiply(f32 *, f32 *, f32 *);
void rotateVec3ByQuat(f32 *, f32 *, f32 *);
f32 sinf(f32);

void advanceNpcSpinOrientation(u8 *arg0, f32 arg1) {
    f32 q1[4];
    f32 q2[4];
    f32 q3[4];
    SpinVec3 out;

    *(f32 *)(arg0 + 0x58) = *(f32 *)(arg0 + 0x58) + arg1 * *(f32 *)(arg0 + 0x60);
    if (*(f32 *)(arg0 + 0x58) > 1.0f) {
        *(f32 *)(arg0 + 0x58) = *(f32 *)(arg0 + 0x58) - 2.0f;
    }
    *(f32 *)(arg0 + 0x5C) = *(f32 *)(arg0 + 0x5C) + arg1 * *(f32 *)(arg0 + 0x60);
    if (*(f32 *)(arg0 + 0x5C) > 1.0f) {
        *(f32 *)(arg0 + 0x5C) = *(f32 *)(arg0 + 0x5C) - 2.0f;
    }
    *(f32 *)(arg0 + 0x68) = *(f32 *)(arg0 + 0x68) + arg1 * 0.5f;
    if (*(f32 *)(arg0 + 0x68) > 1.0f) {
        *(f32 *)(arg0 + 0x68) = 1.0f;
    }
    quatFromCardinalAxis(q1, 0, sinf(*(f32 *)(arg0 + 0x58) * 3.1415927f) * *(f32 *)(arg0 + 0x68));
    quatFromCardinalAxis(q2, 2, sinf(*(f32 *)(arg0 + 0x5C) * 3.1415927f) * *(f32 *)(arg0 + 0x68));
    quatMultiply(q2, q1, q3);
    rotateVec3ByQuat(q3, (f32 *)(arg0 + 0x6C), (f32 *)&out);
    *(SpinVec3 *)(arg0 + 0xC) = out;
    rotateVec3ByQuat(q3, (f32 *)(arg0 + 0x78), (f32 *)&out);
    *(SpinVec3 *)(arg0 + 0x18) = out;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D5AD0", D_mission_overlay_800A760C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D5AD0", npcDebrisFieldUpdate);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D5AD0", D_mission_overlay_800A7680);
