#include "common.h"

#include "common_types.h"
extern void composeEulerRotationXYZ(void *, s32, s32, s32);
extern void *walkMeshdef0List(s32);
extern void mat34CrossRowsAndCopyPosPtr(void *, void *, void *);
extern void popNpcSlotFromTail(u16, void *);
extern void dispatchDatSubtypeByRandomIndex(void *, void *);
extern void parseDatItemCommon(void *, void *);
extern void walkDatTreeAndCollectSubtypes(void *, void *);
extern void releaseMeshAsset(void *);
extern s32 isNpcWithinActiveReferenceRange(void *);
extern void destroyNpcSlotByIndex(u16);
extern void walkDatTreeAndScaleLeafByFloat(void *, void *, s32);
extern u8 addNpcToVisibilityBucket(s32, void *, void *, f32);
extern void walkDatTreeAndVisitChildren(void *, void *, void *);
extern void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
extern void extrapolateNpcPositionForCurrentMode(void *);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern s32 getPlayerField2(s32);
extern void playSpeechClip(s32, s32, s32, s32);
extern u16 D_main_bss_80139560[];

typedef struct {
    u8 *mesh;
    f32 x, y;
    f32 f0C;
    u8 pad[0x18];
    f32 f28, f2C, f30;
    u8 *rec;
    f32 f38;
    u8 b3C, b3D, b3E, b3F;
    u8 tree[1];
} NpcA;

s32 func_mission_overlay_800E4070(u8 *arg0, u16 arg1, u8 *arg2) {
    NpcA *s1 = *(NpcA **)(arg0 + 4);
    u8 *s0;
    u32 a0;

    switch (arg1) {
    case 1:
        s0 = (u8 *)s1 + 4;
        *(u8 **)(arg0 + 8) = s0;
        composeEulerRotationXYZ(s0, *(s32 *)(arg2 + 0x1C), *(s32 *)(arg2 + 0x20), *(s32 *)(arg2 + 0x24));
        s1->x = *(f32 *)(arg2 + 0x10);
        s1->y = *(f32 *)(arg2 + 0x14);
        {
            f32 zf = 0.0f;
            f32 t = *(f32 *)(arg2 + 0x18);
            s1->b3C = 0;
            s1->rec = arg2;
            s1->f30 = zf;
            s1->f2C = zf;
            s1->f28 = zf;
            s1->f0C = t;
        }
        {
            u8 *m = walkMeshdef0List(*(s32 *)(arg2 + 0x5C));
            *(u8 **)s1 = m;
            *(u16 *)(m + 8) |= 0x20;
        }
        mat34CrossRowsAndCopyPosPtr(s1->mesh + 0x28, s0, arg2 + 0x28);
        *(u8 **)(arg0 + 0xC) = s1->mesh;
        {
            f32 v;
            if (*(f32 *)(s1->rec + 0x2C) > *(f32 *)(s1->rec + 0x28)) {
                if (*(f32 *)(s1->rec + 0x30) < *(f32 *)(s1->rec + 0x2C)) {
                    *(u16 *)(s1->mesh + 8) |= 0x400;
                    v = *(f32 *)(s1->rec + 0x2C);
                } else goto l800;
            } else if (*(f32 *)(s1->rec + 0x28) < *(f32 *)(s1->rec + 0x30)) {
l800:
                *(u16 *)(s1->mesh + 8) |= 0x800;
                v = *(f32 *)(s1->rec + 0x30);
            } else {
                v = *(f32 *)(s1->rec + 0x28);
            }
            s1->f38 = *(f32 *)(*(u8 **)s1->mesh + 0x44) * v;
        }
        popNpcSlotFromTail(D_main_bss_80139560[0xE], arg0);
        if (*(u16 *)arg2 != 0x4F) {
            *(u16 *)(arg0 + 0x14) |= 0x100;
            s1->b3E = 0;
            if (*(s32 *)(arg2 + 0x70) == 0) {
                popNpcSlotFromTail(D_main_bss_80139560[0x15], arg0);
            }
            a0 = D_main_bss_80139560[0xA];
        } else {
            s1->b3E = 1;
            if (*(s32 *)(arg2 + 0x70) == 0) {
                popNpcSlotFromTail(D_main_bss_80139560[0x13], arg0);
            }
            a0 = D_main_bss_80139560[6];
        }
        popNpcSlotFromTail(a0, arg0);
        dispatchDatSubtypeByRandomIndex((u8 *)s1 + 0x40, s1->mesh);
        s1->b3F = 1;
        s1->b3D = 0;
        break;
    case 2:
        *(u16 *)(s1->rec + 6) = 0xFFFF;
        parseDatItemCommon(s1->rec, (u8 *)s1 + 4);
        walkDatTreeAndCollectSubtypes((u8 *)s1 + 0x40, s1->mesh);
        releaseMeshAsset(s1->mesh);
        return 1;
    case 3:
        if (isNpcWithinActiveReferenceRange((u8 *)s1 + 4) != 0) {
            s1->b3C = 0;
        } else {
            s1->b3C++;
            if (s1->b3C >= 0x15) {
                destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                break;
            }
        }
        if (s1->b3F != 0) {
            if (s1->tree[0] != 0xFF) {
                walkDatTreeAndScaleLeafByFloat((u8 *)s1 + 0x40, s1->mesh, *(s32 *)arg2);
                return 1;
            }
            return 1;
        }
        break;
    case 4:
        s1->b3F = addNpcToVisibilityBucket(*(s32 *)arg2, s1->mesh, (u8 *)s1 + 4, s1->f38);
        if (s1->b3F != 0 && s1->tree[0] != 0xFF) {
            walkDatTreeAndVisitChildren((u8 *)s1 + 0x40, s1->mesh, arg2);
            return 1;
        }
        break;
    case 5: {
        u8 *msg = arg2;

        if (*(u16 *)(msg + 4) != 7) {
            if (*(u16 *)(msg + 4) == 0xD && s1->b3E == 1) {
                u8 *r = s1->rec;
                datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x7C), *(s32 *)(r + 0x80), *(s32 *)(r + 0x74), *(s32 *)(r + 0x78), *(s32 *)(r + 0x84), *(s32 *)(r + 0x88));
            } else {
                extrapolateNpcPositionForCurrentMode(msg);
                play3DSoundEvent(0, (u8 *)s1 + 4, (u8 *)s1 + 0x28, 24.0f, 0.8f, 0, 0xC, 0x7F, 0x50);
                if (*(u16 *)s1->rec == 0x33 && *(u16 *)(msg + 2) == (u16)getPlayerField2(0) && s1->b3D == 0) {
                    s1->b3D = 1;
                    playSpeechClip(0x15B, 0x73, 0, 8);
                }
            }
        }
        if (*(u16 *)msg != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)msg);
        }
        break;
    }
    }
    return 1;
}

static u32 D_mission_overlay_800A8288[] __attribute__((section(".rodata"))) = { 0x8FC2001C, 0x8FC3001C };

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E4C70", fake_func_800E447C);

