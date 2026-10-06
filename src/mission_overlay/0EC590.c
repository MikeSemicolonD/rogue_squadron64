#include "common.h"

#include "common_types.h"
#include "game_settings.h"
#include "mission_stats.h"

typedef struct {
    /* 0x00 */ u8 *mesh;
    /* 0x04 */ u8 *dat;
    /* 0x08 */ f32 m[12];
    /* 0x38 */ u8 *node;
    /* 0x3C */ u8 *mat;
    /* 0x40 */ f32 radius;
    /* 0x44 */ f32 scale;
    /* 0x48 */ f32 f48;
    /* 0x4C */ f32 f4C;
    /* 0x50 */ f32 f50;
    /* 0x54 */ f32 f54;
    /* 0x58 */ f32 f58;
    /* 0x5C */ f32 f5C;
    /* 0x60 */ f32 f60;
    /* 0x64 */ f32 f64;
    /* 0x68 */ f32 f68;
    /* 0x6C */ s8 timer;
    /* 0x6D */ u8 taken;
} PowerUp;

extern u16 D_pu_slot[] __asm__("D_main_bss_80139574");
void composeEulerRotationXYZ(void *, f32, f32, f32);
u8 *walkMeshdef0List(const char *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void mat34CrossRowsAndCopyPosI(void *, void *, s32) __asm__("mat34CrossRowsAndCopyPos");
void popNpcSlotFromTail(u16, void *);
u8 *lookupHmtMaterialByName(void *, const char *, void *);
void parseDatItemCommon(void *, void *);
void releaseMeshAsset(void *);
f32 cosf(f32);
f32 sinf(f32);
f32 *getCraftRecordByIdx(s32);
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void destroyNpcSlotByIndex(u16);
f32 floatModulo(f32, f32);
s32 isNpcWithinActiveReferenceRange(void *);
void clearVec4QuadStruct(void *);
void addVec3At0x24(void *, f32, f32, f32);
void applyScaleToMat3x4(void *, f32, f32, f32);
void composeQuatToMat3x4(void *, void *);
void composeRotationMatrixSlot1(void *, f32);
void addNpcToVisibilityBucket(s32, void *, void *, f32);

s32 npcPowerUpUpdate(u8 *arg0, u16 action, u8 *arg2) {
    PowerUp *s1 = *(PowerUp **)(arg0 + 4);
    u8 *dat;
    f32 lo;
    f32 mid;
    f32 dt;
    f32 off;
    f32 z;
    f32 one;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 d[3];
    f32 *craft;

    switch (action) {
    case 1:
        *(f32 **)(arg0 + 8) = s1->m;
        *(u16 *)(arg0 + 0x14) |= 0x110;
        composeEulerRotationXYZ(s1->m, *(f32 *)(arg2 + 0x1C), *(f32 *)(arg2 + 0x20), *(f32 *)(arg2 + 0x24));
        s1->m[0] = *(f32 *)(arg2 + 0x10);
        s1->m[1] = *(f32 *)(arg2 + 0x14);
        z = 0.0f;
        s1->m[2] = *(f32 *)(arg2 + 0x18);
        s1->m[11] = z;
        s1->m[10] = z;
        s1->m[9] = z;
        s1->timer = 0;
        s1->dat = arg2;
        s1->mesh = walkMeshdef0List("r_pow");
        s1->scale = *(f32 *)(arg2 + 0x28);
        s1->f48 = *(f32 *)(arg2 + 0x70) * 0.25f;
        s1->f4C = z;
        s1->f50 = *(f32 *)(arg2 + 0x74);
        s1->f54 = z;
        s1->f58 = z;
        s1->f5C = z;
        s1->f60 = z;
        s1->f64 = z;
        s1->taken = 0;
        mat34CrossRowsAndCopyPosI(s1->mesh + 0x28, s1->m, *(s32 *)&s1->scale);
        *(u8 **)(arg0 + 0xC) = s1->mesh;
        mid = *(volatile f32 *)(s1->dat + 0x2C);
        lo = *(volatile f32 *)(s1->dat + 0x28);
        if (lo < mid) {
            if (*(f32 *)(s1->dat + 0x30) < mid) {
                *(u16 *)(s1->mesh + 8) |= 0x400;
                lo = *(f32 *)(s1->dat + 0x2C);
            } else {
                goto big;
            }
        } else if (lo < *(f32 *)(s1->dat + 0x30)) {
        big:
            *(u16 *)(s1->mesh + 8) |= 0x800;
            lo = *(f32 *)(s1->dat + 0x30);
        }
        s1->radius = *(f32 *)(*(u8 **)s1->mesh + 0x44) * lo;
        popNpcSlotFromTail(D_pu_slot[0], arg0);
        s1->node = lookupHmtMaterialByName(s1->mesh, "rot_a", &s1->mat);
        break;
    case 2:
        *(u16 *)(s1->dat + 6) = 0xFFFF;
        if (s1->taken == 0) {
            parseDatItemCommon(s1->dat, s1->dat + 0x10);
        }
        releaseMeshAsset(s1->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        if (s1->taken == 0) {
            off = 0.0f;
            if (s1->f48 != off) {
                s1->f4C += dt * s1->f50;
                one = 1.0f;
                if (s1->f4C > one) {
                    s1->f4C = one;
                    s1->f5C = *(f32 *)(s1->dat + 0x7C);
                }
                s1->f54 = (one - cosf(s1->f4C * 3.1415927f * 0.5f)) * s1->f48;
                off = s1->f54 + off;
            }
            s1->f58 += dt * s1->f5C;
            if (s1->f58 > 1.0f) {
                s1->f58 = s1->f58 - 2.0f;
            }
            off += sinf(s1->f58 * 3.1415927f) * (*(f32 *)(s1->dat + 0x78) * 0.25f);
            s1->m[1] = *(f32 *)(s1->dat + 0x14) - off;
            craft = getCraftRecordByIdx(0);
            d[0] = craft[0] - s1->m[0];
            d[1] = craft[1] - s1->m[1];
            d[2] = craft[2] - s1->m[2];
            if (d[0] * d[0] + d[1] * d[1] + d[2] * d[2] <= s1->radius * s1->radius) {
                missionStats.bonus_collected++;
                play3DSoundEvent(0, s1->m, &s1->m[9], 18.0f, 0.5f, 0, 0x18, 0x50, 0x14);
                switch (*(u32 *)(s1->dat + 0x6C)) {
                case 0:
                    gGameSettings.unlockAndSettingsFlags[0] |= 0x200;
                    break;
                case 1:
                    gGameSettings.unlockAndSettingsFlags[0] |= 0x800;
                    break;
                case 2:
                    gGameSettings.unlockAndSettingsFlags[0] |= 0x2000;
                    break;
                case 3:
                    gGameSettings.unlockAndSettingsFlags[0] |= 0x4000;
                    break;
                case 4:
                    gGameSettings.unlockAndSettingsFlags[0] |= 0x10000;
                    break;
                case 5:
                    gGameSettings.unlockAndSettingsFlags[0] |= 0x400;
                    break;
                case 6:
                    gGameSettings.unlockAndSettingsFlags[0] |= 0x1000;
                    break;
                case 7:
                    gGameSettings.unlockAndSettingsFlags[0] |= 0x8000;
                    break;
                }
                s1->taken = 1;
                s1->f68 = s1->scale * 0.5f;
                datItemSetObjectiveBooleanCount(*(s32 *)(s1->dat + 0x88), *(s32 *)(s1->dat + 0x8C), *(s32 *)(s1->dat + 0x80), *(s32 *)(s1->dat + 0x84), 0, 0);
            }
        } else {
            s1->scale = s1->scale - s1->f68;
            if (s1->scale <= 0.0f) {
                destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                return 1;
            }
        }
        s1->f60 += dt * 90.0f;
        s1->f60 = floatModulo(s1->f60, 360.0f);
        s1->f64 += dt;
        if (s1->f64 >= 1.0f) {
            s1->f64 = 0.0f;
        }
        if (isNpcWithinActiveReferenceRange(s1->m) != 0) {
            s1->timer = 0;
        } else if (++s1->timer >= 0x15) {
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        break;
    case 4:
        {
            u8 *mp = s1->mat;
            u8 *m = s1->node + 0x1C;

            clearVec4QuadStruct(m);
            if (*(s32 *)(mp + 0x4C) & 1) {
                addVec3At0x24(m, -*(f32 *)(mp + 0x50), -*(f32 *)(mp + 0x54), -*(f32 *)(mp + 0x58));
            }
            if (*(s32 *)(mp + 0x4C) & 2) {
                applyScaleToMat3x4(m, *(f32 *)(mp + 0x5C), *(f32 *)(mp + 0x60), *(f32 *)(mp + 0x64));
            }
            if (*(s32 *)(mp + 0x4C) & 4) {
                composeQuatToMat3x4(m, mp + 0x68);
            }
            composeRotationMatrixSlot1(m, s1->f60);
            addVec3At0x24(m, 0.0f, sinf(2.0f * s1->f64 * 3.1415927f) * 0.5f, 0.0f);
            if ((*(s32 *)(mp + 0x4C) & 9) == 9) {
                addVec3At0x24(m, *(f32 *)(mp + 0x78) + *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x7C) + *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x80) + *(f32 *)(mp + 0x58));
            } else if ((*(s32 *)(mp + 0x4C) & 9) == 8) {
                addVec3At0x24(m, *(f32 *)(mp + 0x78), *(f32 *)(mp + 0x7C), *(f32 *)(mp + 0x80));
            } else if (*(s32 *)(mp + 0x4C) & 1) {
                addVec3At0x24(m, *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x58));
            }
            mat34CrossRowsAndCopyPos(s1->mesh + 0x28, s1->m, s1->scale);
            addNpcToVisibilityBucket(*(s32 *)arg2, s1->mesh, s1->m, s1->radius);
        }
        break;
    default:
        return 1;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EC590", fake_func_800EC10C);
