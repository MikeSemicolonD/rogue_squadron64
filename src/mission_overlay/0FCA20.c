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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", dispatchHudInstanceWeaponEffect);

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
