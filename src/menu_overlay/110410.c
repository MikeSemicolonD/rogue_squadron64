#include "common.h"
#include "common_types.h"

#include "PR/ultratypes.h"
#include "game_settings.h"
#include "secondary_weapons.h"
#include "textures.h"

#include "main/1EE30.h"
#include "main/55AF0.h"
#include "main/562A0.h"
#include "main/64EA0.h"
#include "main/6C310.h"
#include "menu_overlay/110410.h"
#include "menu_overlay/12CA40.h"

// Interim Data externs
extern u8 hangarActiveSecondaryWeaponString;

// Interim BSS externs
extern char hangarSecondaryWeaponStrings[4][0x30];
extern u8  D_menu_overlay_800CD520[0x20];
extern u8  D_menu_overlay_800CD6D0;

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", loadCutsceneAssetsByIndex);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", D_menu_overlay_800A5130);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEDread);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", D_menu_overlay_800A514C);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuECalamari);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEBacta);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEVolcano);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEChandrila);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEResearch);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuETaloraan);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEKessel);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEKile);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuECon);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEJade);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEKasan);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuECorellia);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEChorax);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEBarkesh);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuETatooine);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", hangarInitialize);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", runHangarSelectionFrame);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", composeNpcOrientationMatrix);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", updateHangarBayScene);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", hangarTickCameraOrbit);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", D_menu_overlay_800A5804);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", hangarInitializeShipShadowHob);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", craftSelectionVoiceLineHelper);

s32 lerpVec3(s32 *, s32 *, s32, f32);
f32 quadraticEaseInOut(f32);
extern f32 D_menu_overlay_800CD704;
extern f32 D_menu_overlay_800CD708;
extern s32 D_menu_overlay_800CD800;
extern s32 D_menu_overlay_800CD810;
extern s32 D_menu_overlay_800CDA60;
extern s32 D_menu_overlay_800CDA70;

s32 tickEasedCameraKeyframeBlend(s32 arg0, s32 arg1, f32 arg2) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    s32 var_v0;

    if (D_menu_overlay_800CD708 < 1.0f) {
        temp_fv0 = D_menu_overlay_800CD708 + (arg2 / 7.5f);
        D_menu_overlay_800CD708 = temp_fv0;
        if (temp_fv0 > 1.0f) {
            D_menu_overlay_800CD708 = 1.0f;
        }
    }
    if (D_menu_overlay_800CD704 < 1.0f) {
        temp_fv0_2 = D_menu_overlay_800CD704 + (arg2 / 5.0f);
        D_menu_overlay_800CD704 = temp_fv0_2;
        if (temp_fv0_2 >= 1.0f) {
            D_menu_overlay_800CD704 = 1.0f;
        }
    }
    lerpVec3(&D_menu_overlay_800CD810, &D_menu_overlay_800CDA60, arg0, quadraticEaseInOut(D_menu_overlay_800CD708));
    lerpVec3(&D_menu_overlay_800CD800, &D_menu_overlay_800CDA70, arg1, quadraticEaseInOut(D_menu_overlay_800CD704));
    var_v0 = 0;
    if ((D_menu_overlay_800CD704 >= 1.0f) && (D_menu_overlay_800CD708 >= 1.0f)) {
        var_v0 = 1;
    }
    return var_v0;
}

#if 0

/*
This function may prove to be a problem child.
The last format string in this function, "%s%s", is right before the bogus file padding.
While there is a way to get that bogus padding into the rodata section itself, there's 2 major problems.

1) For reasons I cannot comprehend, there's an extra 16 bytes of padding being added by the compiler.
2) Moving the string out of the function creates an unwinnable situation concerning bridgeSecondaryWeaponTextIds
2a) If the string and bridgeSecondaryWeaponTextIds are in the function, they will be appropriately ordered in the rodata section.
BUT the compiler will also add extraneous padding between them.
2b) If you pull the strings and bridgeSecondaryWeaponTextIds out of the function, the compiler will place them next to each other
as desired.
BUT, you then can't lose the memcpy like assignemt to bridgeSecondaryWeaponTextIds in the function body.

Because of this, this function may not be truly matchable.
If there was ever an indicator that I was using the wrong compiler for this project, this would be it.

Note that as currently writte the .text section for this matches 100%, its just the rodata handling that is screwy.
*/

// const u8 blah0[8] = {
//     "%s%s%s"
// };

// const u8 blah1[20] = {
//     "%s%s\x00\x04\x18\x80\x00\x62\x18\x21\x00\x03\x21\x00\x00\x82\x20\x21"
// };

char *hangarGenerateSecondaryWeaponString(enum Level level, enum PlayerCraft craft) {
    u16 bridgeSecondaryWeaponTextIds[10] = {
        0x0000, 0x004E, 0x0050, 0x0051, 0x0052, 0x0053, 0x004F, 0x0054, 0x0055, 0x0056
    };
    u8 isAdvanced;
    char *temp_s3;
    char *var_s1_2;
    u8 temp_s0;
    u8 temp_s2;
    u8 why;

    isAdvanced = 0;
    temp_s2 = hangarActiveSecondaryWeaponString;
    temp_s0 = getSecondaryWeaponForLevelAndCraft(level, craft, D_menu_overlay_800CD6D0);
    if (temp_s0 != SECONDARY_WEAPON_NONE) {
        why = temp_s0 - 2;
        if ((why < 2U) && (ADVANCED_MISSILES_UNLOCKED)) isAdvanced = 1;
        if ((temp_s0 == SECONDARY_WEAPON_BOMBS) && (ADVANCED_BOMBS_UNLOCKED)) isAdvanced = 1;
        if ((temp_s0 == SECONDARY_WEAPON_PROTON_TORPEDOS) && (ADVANCED_TORPEDOS_UNLOCKED)) isAdvanced = 1;
        temp_s0 = bridgeSecondaryWeaponTextIds[temp_s0];
        temp_s3 = getGameOrFrontText(0x49);
        if (isAdvanced) {
            var_s1_2 = getGameOrFrontText(0x4B);
        } else {
            var_s1_2 = "";
        }
        sprintf(hangarSecondaryWeaponStrings[temp_s2], "%s%s%s", temp_s3, var_s1_2, getGameOrFrontText(temp_s0));
    } else {
        sprintf(hangarSecondaryWeaponStrings[temp_s2], "%s%s", getGameOrFrontText(0x49), getGameOrFrontText(0x57));
    }
    hangarActiveSecondaryWeaponString++;
    hangarActiveSecondaryWeaponString &= 3; // the really ought to be %= 4, but that leads to a ton of intruction reordering
    return hangarSecondaryWeaponStrings[temp_s2];
}
#else

const u16 bridgeSecondaryWeaponTextIds[] = {
    0x0000, 0x004E, 0x0050, 0x0051, 0x0052, 0x0053, 0x004F, 0x0054, 0x0055, 0x0056
};

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", hangarGenerateSecondaryWeaponString);
#endif

void tickMusyXIfActive(void);
u8 anyAudioSlotActive(void);
void bufferArbiterProducerScanWait(void);
void destroyPlayerShipRecord(s32, void *);
s32 finalizeCurrentSpeechBuffer();
extern s32 D_menu_overlay_800CD668;
extern u8 D_menu_overlay_800CD670[];
void gracefulMenuShutdown(void) {
    s32 i;

    tickMusyXIfActive();
    while (!anyAudioSlotActive()) {
    }
    bufferArbiterProducerScanWait();
    destroyPlayerShipRecord(D_menu_overlay_800CD668, D_menu_overlay_800CD670);
    for (i = 7; i >= 0; i--) {
    }
    finalizeCurrentSpeechBuffer();
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", extractTextBeforeFmtChar);

typedef struct {
    u8 pad[0x4C];
    u32 flags;
    f32 pos[3];
    f32 scale[3];
    f32 quat[4];
    f32 offs[3];
} NodeXform;
void clearVec4QuadStruct(void *);
void addVec3At0x24(void *, f32, f32, f32);
void applyScaleToMat3x4(void *, f32, f32, f32);
void composeQuatToMat3x4(void *, void *);
void composeRotationMatrixSlot2(void *, f32);

void composeInterpolatedNodeMatrices(u8 *arg0, u8 *arg1, NodeXform *arg2, NodeXform *arg3, f32 arg4) {
    s32 i;
    u16 j;
    u8 *dst;
    NodeXform *s;
    f32 ang;
    s32 fl;

    if (arg0 != NULL) {
        if (arg1 != NULL) {
            for (i = 0; (u16)i < 2; i++) {
                dst = arg1 + 0x1C;
                if ((u16)i == 0) {
                    dst = arg0 + 0x1C;
                }
                j = i & 0xFFFF;
                s = arg3;
                if (j == 0) {
                    s = arg2;
                }
                clearVec4QuadStruct(dst);
                if (s->flags & 1) {
                    addVec3At0x24(dst, -s->pos[0], -s->pos[1], -s->pos[2]);
                }
                if (s->flags & 2) {
                    applyScaleToMat3x4(dst, s->scale[0], s->scale[1], s->scale[2]);
                }
                if (s->flags & 4) {
                    composeQuatToMat3x4(dst, s->quat);
                }
                ang = arg4;
                if (j != 0) {
                    ang = -ang;
                }
                composeRotationMatrixSlot2(dst, ang);
                fl = s->flags;
                if ((fl & 9) == 9) {
                    addVec3At0x24(dst, s->offs[0] + s->pos[0], s->offs[1] + s->pos[1], s->offs[2] + s->pos[2]);
                } else if ((fl & 9) == 8) {
                    addVec3At0x24(dst, s->offs[0], s->offs[1], s->offs[2]);
                } else if (fl & 1) {
                    addVec3At0x24(dst, s->pos[0], s->pos[1], s->pos[2]);
                }
            }
        }
    }
}

extern char D_menu_overlay_800A5804[];
void hangarLoadShadows(void) {
    struct material_entry sp10;
    struct full_image_header *temp_s4;
    struct full_image_header *var_s1;
    s32 var_s2;
    s32 var_v1;

    temp_s4 = load_asset(D_menu_overlay_800A5804);
    for (var_s2 = 0; var_s2 < 14; var_s2++) {
        var_s1 = temp_s4;
        for (var_v1 = 0; var_v1 < var_s2; var_v1++) {
            var_s1 = (struct full_image_header *)(((u32)var_s1 + var_s1->image_size + 7) & ~3);
        }
        full_header_image_offset_convert(&var_s1->ent, (u32)&var_s1->ent);
        var_s1->ent.flags_type |= 0x2000;
        sp10.material_type = 1;
        D_main_bss_8013A528[var_s2] = registerHmtTextureInTable(&sp10, &var_s1->ent, 1U);
    }
    rs_free(temp_s4);
}

typedef struct {
    u8 pad[0x27];
    u8 b;
} SetByteEntry;
void setByteAcrossEntryList(u8 *arg0, u8 arg1) {
    u32 i;
    SetByteEntry *e = *(SetByteEntry **)(arg0 + 8);

    for (i = 0; i < *(u32 *)(arg0 + 0xC); i++) {
        e->b = arg1;
        e++;
    }
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} CraftSelectVec3;
void initCraftSelectVectors(CraftSelectVec3 *arg0, CraftSelectVec3 *arg1) {
    D_menu_overlay_800CD704 = 0.0f;
    D_menu_overlay_800CD708 = 0.0f;
    *(CraftSelectVec3 *)&D_menu_overlay_800CDA60 = *arg0;
    *(CraftSelectVec3 *)&D_menu_overlay_800CDA70 = *arg1;
}

s32 setPlayerSlotEntryRGB(s32, s32, s32 *);
s32 startPlayerSlotAnimationChannelExt(s32, s8 *, s32, s32, s32, s32);
extern s32 D_menu_overlay_800CDA7C;
extern s8 D_menu_overlay_800CDA80;
extern s32 hangarWhiteColor;

void hangarSetSecondaryWeaponDisplay(s32 arg0, s8 arg1) {
    D_menu_overlay_800CDA7C = startPlayerSlotAnimationChannelExt(2, hangarGenerateSecondaryWeaponString(arg0 & 0xFF, arg1 & 0xFF), 0x10, 1, -0x100, 0x97);
    setPlayerSlotEntryRGB(2, 1, &hangarWhiteColor);
    setPlayerSlotEntryRGB(2, 2, &hangarWhiteColor);
    D_menu_overlay_800CDA80 = arg1;
}

void startPlayerSlotAnimationChannel(s32, char *);
void advancePlayerAnimationPhase(s32, s32, f32);
extern s32 D_menu_overlay_800CD6DC;
void hangarUpdateSecWeaponIfChanged(u8 arg0, u8 arg1, f32 arg2) {
    if (arg1 != (u8)D_menu_overlay_800CDA80) {
        startPlayerSlotAnimationChannel(D_menu_overlay_800CDA7C, hangarGenerateSecondaryWeaponString(arg0, arg1));
        D_menu_overlay_800CDA80 = arg1;
    }
    advancePlayerAnimationPhase(D_menu_overlay_800CDA7C, D_menu_overlay_800CD6DC, arg2);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", fake_func_800AEC54);
