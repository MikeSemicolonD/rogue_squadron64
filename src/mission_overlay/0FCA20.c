#include "common.h"
#include "common_types.h"

#include "crafts.h"
#include "hud.h"
#include "secondary_weapons.h"

#include "mission_overlay/0B4EC0.h"
#include "mission_overlay/0FCA20.h"

static struct hud_struct D_mission_overlay_8010CA30[2];

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90B0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90C0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90D0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90DC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90E8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A90F4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A9100);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A910C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A9118);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", D_mission_overlay_800A9124);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", configurePlayerSecondaryWeaponHud);

void destroyNpcSlotChain(u16);
void factor5RemoveListNode(void *);

void resetHudInstancesAndUnbindNpcs(void) {
    s32 i;
    struct hud_struct *h;

    i = 0;
    do {
        if ((D_mission_overlay_8010CA30[i & 0xFF].secondaryWeapon == 3 || D_mission_overlay_8010CA30[i & 0xFF].secondaryWeapon == 8) && D_mission_overlay_8010CA30[i & 0xFF].unk210 != 0) {
            destroyNpcSlotChain(D_mission_overlay_8010CA30[i & 0xFF].unk212);
        }
        h = &D_mission_overlay_8010CA30[i & 0xFF];
        if (h->unk274 != 0) {
            factor5RemoveListNode(D_mission_overlay_8010CA30[i & 0xFF].listNode);
            h->unk274 = 0;
        }
        switch (h->secondaryWeapon) {
        case 3:
        case 8:
            h->secondaryWeaponState = 0;
            h->unk210 = 0;
            h->unk211 = 0;
            break;
        case 1:
        case 2:
        case 4:
        case 5:
            h->secondaryWeaponState = 0;
            break;
        }
        if (getPlayerVehicleId(0) == 0 && !isWeaponSlotReady(0)) {
            h->alpha_scaling = 0.0f;
        } else {
            h->alpha_scaling = 1.0f;
        }
        i++;
    } while ((u32)(i & 0xFF) < 2);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", findNearestTargetableNpcInRange);

typedef struct TerrainV3 {
    f32 x;
    f32 y;
    f32 z;
} TerrainV3;

extern u8 D_main_bss_80138058[];
extern void lookupHmtTextureByName(s32, char *, s32, void *, void *, s32);
extern s32 sampleTerrainAtNpcPosition(TerrainV3 *, TerrainV3 *, void *, TerrainV3 *);

s32 projectForwardTerrainImpactPoint(TerrainV3 *out, f32 *arg1, s32 arg2) {
    TerrainV3 hit;
    u8 pad[0x18];
    TerrainV3 pos;
    TerrainV3 next;
    TerrainV3 dir;
    TerrainV3 delta;
    u8 buf[0x30];
    TerrainV3 base;
    u8 pad2[0x20];
    f32 t;

    lookupHmtTextureByName(arg2, "a", 0, &base, buf, 0);
    pos = base;
    dir.x = arg1[3] * 4.0f + arg1[9];
    dir.y = arg1[4] * 4.0f + arg1[10] + 2.0f;
    t = 0.0f;
    dir.z = arg1[5] * 4.0f + arg1[11];
    do {
        next.x = pos.x + dir.x * 0.1f;
        next.y = pos.y + dir.y * 0.1f;
        next.z = pos.z + dir.z * 0.1f;
        dir.y += 1.2f;
        delta.x = next.x - pos.x;
        delta.y = next.y - pos.y;
        delta.z = next.z - pos.z;
        if (!sampleTerrainAtNpcPosition(&pos, &delta, &D_main_bss_80138058, &hit)) {
            t += 0.1f;
            pos = next;
        } else {
            *out = hit;
            return 1;
        }
    } while (t < 5.0f);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", tickHudInstanceTargetingAndSpawns);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", updatePlayerHudFrame);

void destroyNpcSlotChain(u16);
void factor5RemoveListNode(void *);
void releaseTextureLutEntry(u16);

void teardownHudInstancesAndUnbindNpcs(void) {
    u32 i;

    for (i = 0; i < 10; i++) {
        releaseTextureLutEntry(D_mission_overlay_8010CA30[0].texture_ids[i]);
    }
    for (i = 0; i < 2; i++) {
        if ((D_mission_overlay_8010CA30[i].secondaryWeapon == 3 || D_mission_overlay_8010CA30[i].secondaryWeapon == 8) && D_mission_overlay_8010CA30[i].unk210 != 0) {
            destroyNpcSlotChain(D_mission_overlay_8010CA30[i].unk212);
        }
        if (D_mission_overlay_8010CA30[i].unk274 != 0) {
            factor5RemoveListNode(D_mission_overlay_8010CA30[i].listNode);
        }
    }
}

typedef struct {
    s16 hB8;
    u16 hBA;
    s32 wBC;
    f32 fC0;
    f32 fC4;
    f32 fC8;
    u8 bCC;
    u8 padCD[0xB];
} DhSlotArgs;
typedef struct {
    u8 pad0[4];
    u8 *p4;
    u8 pad8[0x13C];
} DhCam;
extern DhCam D_main_bss_80138D18[];
extern u8 gPlayers[];
extern f32 D_mission_overlay_8010B44C[];
extern f32 D_mission_overlay_8010B454[];
extern f32 D_mission_overlay_8010B45C[];
extern f32 D_mission_overlay_8010B464[];
extern f32 D_mission_overlay_8010B46C[];
extern f32 D_mission_overlay_8010B474[];
extern f32 D_mission_overlay_8010B47C[];
extern f32 D_mission_overlay_8010B484[];
extern f32 D_mission_overlay_8010B48C[];
extern f32 D_mission_overlay_8010B494[];
extern f32 D_mission_overlay_8010B49C[];
extern f32 D_mission_overlay_8010B4A4[];
extern f32 D_mission_overlay_8010B4AC[];
extern f32 D_mission_overlay_8010B4C0[];
extern f32 D_mission_overlay_8010B4CC[];
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);
s32 slotDispatcherIter(u16, s32, void *);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void accumulateVectorInObjectFrame(void *, void *, void *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);

void dispatchHudInstanceWeaponEffect(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, u16 arg6) {
    f32 mtx[12];
    u8 buf[0x30];
    f32 mtx2[12];
    DhSlotArgs sa;
    f32 scale[3];
    struct hud_struct *h;
    register u8 *p2 asm("$19") = arg2;
    register s32 tex asm("$7") = arg3;
    u16 r;
    f32 one;
    f32 t;
    f32 u;

    switch (arg4) {
    case 3:
    case 8:
        {
            struct hud_struct *hb = D_mission_overlay_8010CA30;
            h = &hb[arg0 & 0xFF];
        }
        if (h->unk211 != 0) {
            h->unk211 = 0;
            goto case2;
        }
        lookupHmtTextureByName(tex, "scnd", arg5, mtx, buf, 0);
        if (arg4 == 3) {
            r = dispatchCueByCategory(0xA, arg1, mtx, D_mission_overlay_8010B4C0, 1, 4.0f, D_mission_overlay_8010B47C[h->secondaryWeaponIsAdvanced]);
            sa.fC4 = D_mission_overlay_8010B46C[h->secondaryWeaponIsAdvanced];
            sa.fC8 = D_mission_overlay_8010B474[h->secondaryWeaponIsAdvanced];
        } else {
            r = dispatchCueByCategory(0xD, arg1, mtx, D_mission_overlay_8010B4C0, 1, 4.0f, D_mission_overlay_8010B494[h->secondaryWeaponIsAdvanced]);
            sa.fC4 = D_mission_overlay_8010B484[h->secondaryWeaponIsAdvanced];
            sa.fC8 = D_mission_overlay_8010B48C[h->secondaryWeaponIsAdvanced];
        }
        sa.hB8 = 0;
        sa.hBA = arg6;
        sa.wBC = 0;
        sa.bCC = 0;
        sa.fC0 = 10.0f;
        slotDispatcherIter(r, 0xA, &sa);
        if (arg4 == 3) {
            play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x46, 0x78, 0);
        } else {
            play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x46, 0x78, 0);
        }
        break;
    case 4:
        lookupHmtTextureByName(tex, "zb", 0, mtx, buf, 0);
        mtx[9] = *(f32 *)(p2 + 0xC) * 4.0f + *(f32 *)(p2 + 0x24);
        mtx[10] = *(f32 *)(p2 + 0x10) * 4.0f + *(f32 *)(p2 + 0x28) + 2.0f;
        mtx[11] = *(f32 *)(p2 + 0x14) * 4.0f + *(f32 *)(p2 + 0x2C);
        dispatchCueByCategory(8, arg1, mtx, NULL, 0, 0.0f, D_mission_overlay_8010B4AC[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced]);
        play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x47, 0x78, 0);
        break;
    case 2:
    case 5:
    case2:
        lookupHmtTextureByName(tex, "scnd", arg5, mtx, buf, 0);
        if (arg4 == 2) {
            dispatchCueByCategory(0xA, arg1, mtx, D_mission_overlay_8010B4C0, 1, D_mission_overlay_8010B44C[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced], D_mission_overlay_8010B454[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced]);
            play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x46, 0x78, 0);
        } else {
            dispatchCueByCategory(0xD, arg1, mtx, D_mission_overlay_8010B4C0, 1, D_mission_overlay_8010B45C[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced], D_mission_overlay_8010B464[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced]);
            play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x46, 0x78, 0);
        }
        break;
    case 7:
    case 9:
        lookupHmtTextureByName(tex, "scnd", arg5, mtx, buf, 0);
        r = dispatchCueByCategory(0xE, arg1, mtx, D_mission_overlay_8010B4C0, 1, D_mission_overlay_8010B49C[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced], D_mission_overlay_8010B4A4[D_mission_overlay_8010CA30[arg0 & 0xFF].secondaryWeaponIsAdvanced]);
        if (arg4 == 9) {
            sa.hB8 = 0;
            slotDispatcherIter(r, 0xA, &sa);
        }
        play3DSoundEvent(0, p2, p2 + 0x24, 18.0f, 0.2f, 0, 0x46, 0x78, 0);
        break;
    case 1:
        lookupHmtTextureByName(tex, "scnd", arg5, mtx, buf, 0);
        {
            DhCam *cams = D_main_bss_80138D18;
            u8 *pl = (u8 *)gPlayers;
            if (*(u16 *)(cams[*(s32 *)(pl + 0xBC)].p4 + 4) == 3 && *(u16 *)(pl + 0xB8) == 1) {
                accumulateVectorInObjectFrame(mtx, D_mission_overlay_8010B4CC, pl + 4);
            }
        }
        one = 1.0f;
        mat34CrossRowsAndCopyPos(mtx2, mtx, one);
        { struct hud_struct *hh = D_mission_overlay_8010CA30; t = *(f32 *)&hh[arg0 & 0xFF].unknown_words214[6] / 3.0f; }
        if (one < t) {
            t = one;
        }
        u = t;
        if (t < 0.25f) {
            u = 0.25f;
        }
        scale[0] = u * 3.0f;
        scale[1] = u * 3.0f;
        scale[2] = u * 5.0f;
        t = t + 0.1f;
        if (one < t) {
            t = one;
        }
        dispatchCueByCategory(0xC, arg1, mtx, scale, 1, 10.0f, t * 4.0f);
        play3DSoundEvent(0, p2, p2 + 0x24, 20.0f, 0.2f, 0, 0x34, 0x78, 0x3C);
        break;
    }
}

u8 configurePlayerSecondaryWeaponHud(u8, u8, u8, s32);
extern u8 D_main_bss_80130B12;
extern u32 D_main_bss_80130B4C;
extern u8 gMissionState[];

u8 refreshPlayerSecondaryWeaponHud(u8 arg0) {
    s32 flag;

    if (arg0 == 0) {
        switch (D_main_bss_80130B12) {
            case 2:
            case 3:
                flag = (D_main_bss_80130B4C >> 10) & 1;
                break;
            case 5:
            case 8:
                flag = (D_main_bss_80130B4C >> 12) & 1;
                break;
            case 4:
                flag = (D_main_bss_80130B4C >> 15) & 1;
                break;
            default:
                flag = 0;
                break;
        }
    } else {
        flag = 0;
    }
    return configurePlayerSecondaryWeaponHud(arg0, gMissionState[2], gMissionState[3], flag);
}

void resetTransientPlayerStateFlags(void) {
    u8 var_s1;
    struct hud_struct *temp_s0;

    for (var_s1 = 0; var_s1 < 2;  var_s1++) {
        temp_s0 = &D_mission_overlay_8010CA30[var_s1];
        switch (temp_s0->secondaryWeapon) {
        case SECONDARY_WEAPON_SEEKER_MISSILES:
        case SECONDARY_WEAPON_SEEKER_TORPEDOS:
            temp_s0->secondaryWeaponState = 0;
            temp_s0->unk210 = 0;
            temp_s0->unk211 = 0;
            break;
        case SECONDARY_WEAPON_ION_CANNON:
        case SECONDARY_WEAPON_MISSLES:
        case SECONDARY_WEAPON_BOMBS:
        case SECONDARY_WEAPON_PROTON_TORPEDOS:
            temp_s0->secondaryWeaponState = 0;
            break;
        }
        if (getPlayerVehicleId(0) != CRAFT_XWING) {
            temp_s0->alpha_scaling = 1.0f;
        } else if (!isWeaponSlotReady(0U)) {
            temp_s0->alpha_scaling = 0.0f;
        } else {
            temp_s0->alpha_scaling = 1.0f;
        }
    }
}

void resetSecondaryWeaponCount(void) {
    u8 var_a0;

    for (var_a0 = 0; var_a0 < 2; var_a0++) {
        D_mission_overlay_8010CA30[var_a0].secondaryWeaponCount = D_mission_overlay_8010CA30[var_a0].secondaryWeaponReset;
    }
}

typedef struct {
    u32 x;
    u32 y;
    u32 z;
} HudTargetPos;

s32 getActiveHudInstanceTargetPosition(HudTargetPos *arg0) {
    if (D_mission_overlay_8010CA30[0].secondaryWeapon == 4 && D_mission_overlay_8010CA30[0].secondaryWeaponState != 0 && *(u8 *)&D_mission_overlay_8010CA30[0].unknown_words214[5] != 0) {
        *arg0 = *(HudTargetPos *)&D_mission_overlay_8010CA30[0].unknown_words214[2];
        return 1;
    }
    return 0;
}

s32 func_mission_overlay_800FEECC(void) {
    s32 var_a0;

    var_a0 = 0;
    if (D_mission_overlay_8010CA30[0].secondaryWeapon == SECONDARY_WEAPON_BOMBS) {
        var_a0 = D_mission_overlay_8010CA30[0].secondaryWeaponState > 0U;
    }
    return var_a0;
}

u8 getHudSecondaryWeponCount(void) {
    return D_mission_overlay_8010CA30[0].secondaryWeaponCount;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", fake_func_800FEF04);

// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
const u32 rodata_pad_0FCA20[] = {
    0x00000000,
    0x8FC20024,
};
