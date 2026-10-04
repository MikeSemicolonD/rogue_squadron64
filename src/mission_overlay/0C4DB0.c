#include "common.h"
#include "common_types.h"

typedef struct { u16 *data; u8 *tbl; u8 pad8[0x30]; u16 w; u16 h; } RadarGridC;
extern RadarGridC gRadarGridC __asm__("D_main_bss_80136DC0");
extern u16 D_main_bss_80136DF8;

s32 plotRadarBlipColumn(void *arg0v, s32 y) {
    u8 *arg0 = arg0v;
    s32 x;
    s32 xe;
    s32 h1;
    s32 off;
    s32 lo;
    u8 *col;
    u16 *p;
    u8 *tbl;
    u8 *a0;
    u8 *a1;

    x = *(s16 *)(arg0 + 0x85E) - 0x10;
    xe = *(s16 *)(arg0 + 0x85E) + 0x10;
    h1 = gRadarGridC.h - 1;
    col = arg0 + (y & 0x1F);
    if (y < 0) {
        p = gRadarGridC.data;
    } else {
        if (y >= gRadarGridC.w) {
            p = (u16 *)((u8 *)gRadarGridC.data + (gRadarGridC.w * 2 - 2));
        } else {
            p = (u16 *)((u8 *)gRadarGridC.data + y * 2);
        }
    }
    if (x > 0) {
        if (h1 >= x) {
            p += x * D_main_bss_80136DF8;
        } else {
            p += h1 * D_main_bss_80136DF8;
        }
    }
    tbl = gRadarGridC.tbl;
    if (x < xe) {
        do {
            a0 = tbl + (*p & 0x1FFF) * 0x1E;
            a1 = col + ((x & 0x1F) << 6);
            a1[0] = ((((s8)a0[5] + 0x80) * 0x10) / 22 & ~0xF) | ((u32)((a0[7] - 0x80) & 0xFF) / 22);
            x++;
            a1[0x20] = ((((s8)a0[0xF] + 0x80) * 0x10) / 22 & ~0xF) | ((u32)((a0[0x11] - 0x80) & 0xFF) / 22);
            if (x > 0 && x < h1) {
                p += gRadarGridC.w;
            }
        } while (x < xe);
    }
}

typedef struct { u16 *data; u8 pad4[0x34]; u16 w; u16 h; } RadarGridR;
extern RadarGridR D_main_bss_80136DC0;
extern u8 *D_main_bss_80136DC4;

void plotRadarBlipRow(u8 *arg0, s32 y) {
    s32 x;
    s32 xe;
    s32 w1;
    s32 lo;
    s32 off;
    u8 *row;
    u16 *p;
    u8 *tbl;
    u8 *a0;
    u8 *a1;

    x = *(s16 *)(arg0 + 0x85C) - 0x10;
    xe = *(s16 *)(arg0 + 0x85C) + 0x10;
    w1 = D_main_bss_80136DC0.w - 1;
    row = arg0 + ((y & 0x1F) << 6);
    if (y < 0) {
        p = D_main_bss_80136DC0.data;
    } else {
        if (y < D_main_bss_80136DC0.h) {
            p = D_main_bss_80136DC0.data + y * D_main_bss_80136DC0.w;
        } else {
            p = D_main_bss_80136DC0.data + (D_main_bss_80136DC0.h - 1) * D_main_bss_80136DC0.w;
        }
    }
    if (x > 0) {
        if (w1 >= x) {
            p += x;
        } else {
            p += w1;
        }
    }
    tbl = D_main_bss_80136DC4;
    if (x < xe) {
        do {
            a0 = tbl + (*p & 0x1FFF) * 0x1E;
            a1 = row + (x & 0x1F);
            a1[0] = ((((s8)a0[5] + 0x80) * 0x10) / 22 & ~0xF) | ((u32)((a0[7] - 0x80) & 0xFF) / 22);
            x++;
            a1[0x20] = ((((s8)a0[0xF] + 0x80) * 0x10) / 22 & ~0xF) | ((u32)((a0[0x11] - 0x80) & 0xFF) / 22);
            if (x > 0 && x < w1) {
                p++;
            }
        } while (x < xe);
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", initializeRadar);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", updateCraftSelectAnimState);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", placeRadarDots);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", findClosestRadarContactAndSetSweep);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", renderRadarSweep);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", renderRadarMinimap);

extern u8 D_mission_overlay_80109FE4[];
extern u16 D_mission_overlay_8010BFF0[];
u16 lookupCraftValueByLevelKey(s32 key) {
    s32 i;

    for (i = 0; D_mission_overlay_80109FE4[i] != 0xFF; i += 2) {
        if (D_mission_overlay_80109FE4[i] == key) {
            break;
        }
    }
    if (D_mission_overlay_80109FE4[i] != 0xFF) {
        return D_mission_overlay_8010BFF0[i >> 1];
    }
    return 0;
}

extern s16 D_mission_overlay_8010C080;

void resetCraftSelectionCounter(void) {
    D_mission_overlay_8010C080 = 0;
}

s32 getLevelDatItemByName(char *);
extern void *D_mission_overlay_8010C000[];
typedef struct { u8 pad[0x2C]; s32 nameOffset; } RegisteredObject;
void registerObjectAndResolveDatItem(RegisteredObject *obj) {
    s32 item;

    if (D_mission_overlay_8010C080 < 0x20) {
        D_mission_overlay_8010C000[D_mission_overlay_8010C080++] = obj;
        if (obj->nameOffset != 0) {
            char *name = (char *)(obj->nameOffset + (s32)obj);
            if (*name == 0x2D) {
                obj->nameOffset = 0;
            } else {
                item = getLevelDatItemByName(name);
                if (item != 0) {
                    obj->nameOffset = item;
                } else {
                    obj->nameOffset = 0;
                }
            }
        }
    }
}

s32 findMatchingTextureRecursive(u16, void *, void *, s32);
void *getCraftRecordByIdx(s32);
s32 plotRadarBlipColumn(void *, s32);
extern void *D_mission_overlay_8010BFE0;

void getAvailableShipsForLevel(void) {
    s32 var_s0;
    void *temp_s1;
    void *temp_v0;

    temp_s1 = D_mission_overlay_8010BFE0;
    temp_v0 = getCraftRecordByIdx(0);
    (*(s16 *)((u8 *)(temp_s1) + 0x85C)) = (s16) (s32) ((*(f32 *)((u8 *)(temp_v0) + 0)) * 0.5f);
    var_s0 = -0x10;
    (*(s16 *)((u8 *)(temp_s1) + 0x85E)) = (s16) (s32) ((*(f32 *)((u8 *)(temp_v0) + 8)) * 0.5f);
    do {
        plotRadarBlipColumn(temp_s1, (*(s16 *)((u8 *)(temp_s1) + 0x85C)) + var_s0);
        var_s0 += 1;
    } while (var_s0 < 0x10);
    (*(s16 *)((u8 *)(temp_s1) + 0xDB8)) = 0;
    findMatchingTextureRecursive((*(u16 *)((u8 *)(temp_s1) + 0x858)), temp_s1 + 0x800, temp_s1 + 0x824, 0);
    (*(s16 *)((u8 *)(temp_s1) + 0xDC8)) = -1;
    (*(s32 *)((u8 *)(temp_s1) + 0xDCC)) = 0;
}

void accumulateClampedFloatField(u8 *arg0, f32 arg1) {
    if (*(f32 *)(arg0 + 0xDCC) < 1.0f) {
        *(f32 *)(arg0 + 0xDCC) += arg1;
    }
}

u8 getDisplayItemStateByte(void *arg0) {
    return (*(u8 *)((u8 *)(arg0) + 0xDD0));
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C4DB0", fake_func_800C64A4);

const u32 rodata_pad_0C4DB0[3] = { 0x93C30004, 0x3C01801D, 0x00220821 };
