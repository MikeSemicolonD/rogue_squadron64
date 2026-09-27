#include "common.h"

#include "crafts.h"
#include "hud.h"
#include "secondary_weapons.h"

#include "mission_overlay/0B4EC0.h"
#include "mission_overlay/0FCA20.h"

static struct hud_struct D_mission_overlay_8010CA30[2];

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", strMissOvOvMtrack);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", strMissOvOvMtarget);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", strMissOvOvLockb);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", strMissOvOvLockt);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", strMissOvOvLockr);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", strMissOvOvLockl);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", strMissOvOvLockc);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", strMissOvOvBomb);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", strMissOvOvTrack);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0FCA20", strMissOvOvTarget);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", configurePlayerSecondaryWeaponHud);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", resetHudInstancesAndUnbindNpcs);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", findNearestTargetableNpcInRange);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", projectForwardTerrainImpactPoint);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", tickHudInstanceTargetingAndSpawns);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", updatePlayerHudFrame);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", teardownHudInstancesAndUnbindNpcs);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", dispatchHudInstanceWeaponEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", refreshPlayerSecondaryWeaponHud);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0FCA20", getActiveHudInstanceTargetPosition);

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
