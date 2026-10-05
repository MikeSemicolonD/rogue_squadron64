#include "common.h"
#include "common_types.h"

#include "PR/os.h"

#include "hud.h"
#include "textures.h"

#include "main/02420.h"
#include "main/08120.h"
#include "main/1EE30.h"
#include "main/55AF0.h"
#include "main/64EA0.h"
#include "menu_overlay/115E00.h"
#include "menu_overlay/12CA40.h"

// Interim BSS externs
extern struct ui_element bridgeShipBlueprints[9];
extern u16 bridgeShipBlueprintTextureIds[8]; // This would make it undersized by 1, what gives?
extern struct xy_offset D_menu_overlay_800CDF80[9];

struct rgba bridgeYellowColor = {
    0xE1, 0xAF, 0x00, 0xFF
};
struct rgba bridgeWhiteColor = {
    0xD7, 0xD8, 0xD7, 0xFF
};
struct rgba bridgeGreenColor = {
    0x91, 0xFF, 0x91, 0x00
};
struct rgba bridgeRedColor = {
    0xFF, 0x6E, 0x6E, 0x00
};

s32 D_menu_overlay_800CC700 = -1;

f32 bridgeShipBlueprintWidthScales[9] = {
    1.0f, 1.0f, 0.9f,
    1.1f, 0.9f, 1.1f,
    0.9f, 1.0f, 1.0f,
};
f32 bridgeShipBlueprintHeightScales[9] = {
    1.0f, 1.0f, 0.9f,
    0.9f, 0.9f, 1.1f,
    0.7f, 0.9f, 1.0f,
};

struct xy_offset bridgeShipBlueprintScreenPositions[8][8] = {
    {{   0, -16}, {  0,   0}, {   0,   0}, {   0,   0}, {   0,  0}, {  0,  0}, {  0,  0}, {  0,  0}},
    {{   0, -64}, {  0,  64}, {   0,   0}, {   0,   0}, {   0,  0}, {  0,  0}, {  0,  0}, {  0,  0}},
    {{   0, -64}, {-64,  64}, {  64,  64}, {   0,   0}, {   0,  0}, {  0,  0}, {  0,  0}, {  0,  0}},
    {{ -64, -64}, { 64, -64}, { -64,  64}, {  64,  64}, {   0,  0}, {  0,  0}, {  0,  0}, {  0,  0}},
    {{ -64, -64}, { 64, -64}, {-128,  64}, {   0,  64}, { 128, 64}, {  0,  0}, {  0,  0}, {  0,  0}},
    {{-128, -64}, {  0, -64}, { 128, -64}, {-128,  64}, {   0, 64}, {128, 64}, {  0,  0}, {  0,  0}},
    {{-128, -64}, {  0, -64}, { 128, -64}, {-192,  64}, { -64, 64}, { 64, 64}, {192, 64}, {  0,  0}},
    {{-192, -64}, {-64, -64}, {  64, -64}, { 192, -64}, {-192, 64}, {-64, 64}, { 64, 64}, {192, 64}},
};

// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
u32 data_pad_115E00 = 0x27C30020;

INCLUDE_ASM("asm/nonmatchings/menu_overlay/115E00", initCraftSelectScreen);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58BC);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58C4);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58C8);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58CC);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58D0);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58D4);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58D8);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58DC);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58E0);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58E4);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58E8);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58EC);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58F0);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58F4);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58F8);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/115E00", tickCraftSelectScreen);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/115E00", handleCraftSelectInput);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A5994);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", bridgeOuterBlueLightPositions);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A59C4);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/115E00", spawnOrientedEffectWithEasedSpin);

extern u8 D_menu_overlay_800CDABB;
extern s8 D_menu_overlay_800CDABC;
extern u8 D_menu_overlay_800CDABE;
extern s8 D_menu_overlay_800CDAC0;
extern u8 D_menu_overlay_800CDAC7;
extern u8 D_menu_overlay_800CDAC8;
extern s32 D_menu_overlay_800CDACC;
extern s32 D_menu_overlay_800CDFA8;
extern s32 D_menu_overlay_800CDFAC;
extern f32 D_menu_overlay_800CE6A8;
extern u8 bridgeMenuState;
extern u8 bridgeTransitionState;
extern s32 getControllerNewButtonsPressed(u8);
extern s32 getGameOrFrontText(s32);
extern s32 isAnimInstanceActive(s32);
extern s32 isPlayerShipActive();
extern void markStructInitializedOnce(s32);
extern void startPlayerSlotAnimationChannel(s32, s32);
extern void stopVoiceByHandleLocked(s32);
extern s32 bsearchFactor5TableByU16Key(s32, s32, s32);

void handleLevelSelectStartConfirm(void) {
    u8 start = 0;
    if ((u8)(bridgeMenuState - 2) < 2U) {
        if (bridgeTransitionState == 0 && D_menu_overlay_800CDAC0 == 0) {
            if (getControllerNewButtonsPressed(D_menu_overlay_800CDAC8) & 0x4000) {
                start = D_menu_overlay_800CDABE == 0;
            }
        }
    }
    if ((start != 0) || (D_menu_overlay_800CDABE != 0)) {
        if (!(isAnimInstanceActive(D_menu_overlay_800CDFA8) & 0xFF)) {
            if (D_menu_overlay_800CDABB != 0) {
                markStructInitializedOnce(D_menu_overlay_800CDFAC);
                if (D_menu_overlay_800CC700 != -1) {
                    stopVoiceByHandleLocked(D_menu_overlay_800CC700);
                    D_menu_overlay_800CC700 = -1;
                }
                D_menu_overlay_800CDABB = 0;
                D_menu_overlay_800CDABC = 1;
            }
            if (D_menu_overlay_800CDAC7 == 1) {
                startPlayerSlotAnimationChannel(D_menu_overlay_800CDFA8, getGameOrFrontText(0x39));
                bsearchFactor5TableByU16Key(0x19, 0x5F, 0x40);
                bridgeMenuState = 2;
                D_menu_overlay_800CDAC7 = 0;
                D_menu_overlay_800CE6A8 = 1.0f;
            } else if (!(isPlayerShipActive() & 0xFF)) {
                playExitSoundAndToggleScreenMeshes();
                bridgeMenuState = 4;
                bridgeTransitionState = 0;
                D_menu_overlay_800CDACC = 0xFFFFFE;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/115E00", tickMenuTransitionState);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/115E00", runScriptedCraftCinematicEvent);

struct HobBlk { u8 b[0xFC]; };
extern struct HobBlk bridgeBlueLightHobs[7];
extern void clearStructPair2C30(u8 *);

void initMenuWidgetArray(void) {
    u32 i;
    u32 j;
    u8 *p;
    u8 *q;
    u8 v;
    f32 *vtx;

    for (i = 0; i < 7; i++) {
        p = bridgeBlueLightHobs[i].b;
        q = p + 0x4C;
        *(s32 *)(p + 0x58) = 0x09000009;
        *(s32 *)(p + 0xC) = 0;
        *(s32 *)(p + 0x8) = 0;
        *(s32 *)(p + 0x4) = 0;
        *(s32 *)(p + 0x0) = 0;
        *(u8 **)(p + 0x10) = q;
        *(s32 *)(p + 0x60) = 3;
        *(u8 **)(p + 0x6C) = p + 0xA8;
        *(s32 *)(p + 0x14) = 0;
        *(s32 *)(p + 0x50) = 0;
        *(s32 *)(p + 0x4C) = 0;
        *(s32 *)(p + 0x54) = 0;
        *(s32 *)(p + 0x68) = 0;
        *(s32 *)(p + 0x5C) = 0;
        *(s32 *)(p + 0x64) = 0;
        *(u8 **)(p + 0x70) = p + 0xD8;
        *(s32 *)(p + 0x74) = 0;
        clearStructPair2C30(q);
        *(u8 **)(p + 0xB0) = p + 0xB8;
        *(s32 *)(p + 0xB8) = 0x10;
        *(s32 *)(p + 0xAC) = 0;
        *(s32 *)(p + 0xA8) = 0;
        *(s32 *)(p + 0xB4) = 1;
        *(s32 *)(p + 0xBC) = 0x080C5000;
        *(s32 *)(p + 0xC0) = 0;
        *(f32 *)(p + 0xC0) = 0;
        *(s32 *)(p + 0xB8) |= 0x82;
        for (j = 0; j < 3; j++) {
            *(u16 *)(p + 0xC4 + j * 2) = j;
        }
        if (i == 0) {
            p[0xCC] = 0xB4;
            p[0xCD] = 0xB4;
            p[0xCE] = 0xF5;
            p[0xCF] = 0;
            p[0xD0] = 0xB4;
            p[0xD1] = 0xB4;
            p[0xD2] = 0xF5;
            p[0xD3] = 0;
            p[0xD4] = 0;
            p[0xD5] = 0;
            p[0xD6] = 0xA0;
            p[0xD7] = 0;
        } else {
            if (i < 4) {
                p[0xD4] = 0x50;
                p[0xD5] = 0x50;
                p[0xCC] = 0xFF;
                p[0xCD] = 0xFF;
                p[0xCE] = 0xFF;
                p[0xCF] = 0;
                p[0xD0] = 0xFF;
                p[0xD1] = 0xFF;
                p[0xD2] = 0xFF;
                p[0xD3] = 0;
                p[0xD6] = 0xFF;
                p[0xD7] = 0xC8;
            } else {
                p[0xD4] = 0x1E;
                p[0xD5] = 0x1E;
                p[0xD6] = 0xE1;
                p[0xCC] = 0;
                p[0xCD] = 0;
                p[0xCE] = 0x37;
                p[0xCF] = 0;
                p[0xD0] = 0;
                p[0xD1] = 0;
                p[0xD2] = 0x37;
                p[0xD3] = 0;
                p[0xD7] = 0x9B;
            }
        }
        vtx = *(f32 **)(p + 0x70);
        vtx[0] = 1.0f;
        vtx[1] = -2.0f;
        vtx[2] = 0;
        vtx[3] = -1.0f;
        vtx[4] = -2.0f;
        vtx[5] = 0;
        vtx[6] = 0;
        vtx[7] = 0;
        vtx[8] = 0;
    }
}

void bridgeLoadShipBlueprints(struct some_ui_list_root *arg0) {
    char sp10[0x20];
    char *bridgeShipBlueprintNames[9] = {
        "xwing",
        "ywing",
        "awing",
        "vwing",
        "speeder",
        "falcon",
        "interceptor",
        "t16",
        "xwing",
    };
    struct material_entry sp58;
    u32 var_s4;
    struct full_image_header *temp_v0;
    struct texture_entry *temp_s0;

    for (var_s4 = 0; var_s4 < 9; var_s4++) {
        sprintf(sp10, "blueprints/%s", bridgeShipBlueprintNames[var_s4]);
        temp_v0 = load_asset(sp10);
        temp_s0 = &temp_v0->ent;
        full_header_image_offset_convert(temp_s0, (u32)temp_s0);
        sp58.material_type = 1;
        rs_strcpy(sp58.material_name, (u8 *) temp_s0->texture_name_offset);
        temp_s0->flags_type = 0x2004;
        bridgeShipBlueprintTextureIds[var_s4] = registerHmtTextureInTable(&sp58, temp_s0, 1U);
        rs_memset(&bridgeShipBlueprints[var_s4], 0U, 0x30U);
        bridgeShipBlueprints[var_s4].texture_id_pointer = &bridgeShipBlueprintTextureIds[var_s4];
        bridgeShipBlueprints[var_s4].unknown0A = 1;
        bridgeShipBlueprints[var_s4].texture_count = 1;
        bridgeShipBlueprints[var_s4].width_scale = bridgeShipBlueprintWidthScales[var_s4];
        bridgeShipBlueprints[var_s4].height_scale = bridgeShipBlueprintHeightScales[var_s4];
        bridgeShipBlueprints[var_s4].flags = 3;
        bridgeShipBlueprints[var_s4].rgba.r = 0;
        bridgeShipBlueprints[var_s4].rgba.g = 0;
        bridgeShipBlueprints[var_s4].rgba.b = 0;
        bridgeShipBlueprints[var_s4].rgba.a = 0xFF;
        insertLookupEntry(arg0, &bridgeShipBlueprints[var_s4], 0xAU);
        rs_free(temp_v0);
    }
}

#if 0
// Really close, permuter hasn't turned anything up yet
// Functionally identical though, which is a good sign
// https://decomp.me/scratch/mkgBu
void layoutMenuTextRow(struct some_ui_list_root *arg0, u8 arg1) {
    f32 temp_fv0;
    s32 temp_s4;
    s32 temp_s6;
    s32 var_v1;
    u32 var_s0;

    temp_s6 = getAvailablePlayerCraftFlagsConsiderUnlocks(arg1);
    temp_s4 = getAvailablePlayerCraftFlagsIgnoreUnlocks(arg1);
    var_v1 = 0;
    for (var_s0 = 0; var_s0 < 9; var_s0++) {
        if (temp_s4 & (1 << var_s0)) var_v1++;
    }
    for (var_s0 = 0; var_s0 < 9; var_s0++) {
        if (temp_s4 & (1 << var_s0)) {
            temp_fv0 = (((bridgeShipBlueprintScreenPositions[var_v1 - 1][var_s0].x / 1.5f) - 32.0f) * 512.0f) / 512.0f;
            bridgeShipBlueprints[var_s0].xpos = temp_fv0;
            D_menu_overlay_800CDF80[var_s0].x = temp_fv0;
            temp_fv0 = (((bridgeShipBlueprintScreenPositions[var_v1 - 1][var_s0].y / 1.1f) - 75.0f) * 340.0f) / 340.0f;
            bridgeShipBlueprints[var_s0].ypos = temp_fv0;
            D_menu_overlay_800CDF80[var_s0].y = temp_fv0;
        }
        if (temp_s6 & (1 << var_s0)) {
            bridgeShipBlueprints[var_s0].rgba = bridgeGreenColor;
        } else {
            bridgeShipBlueprints[var_s0].rgba = bridgeRedColor;
        }
        setLookupEntryField5ByKey(arg0, &bridgeShipBlueprints[var_s0], (temp_s4 & (1 << var_s0)) != 0);
    }
}
#else
void layoutMenuTextRow(struct some_ui_list_root *arg0, u8 arg1) {
    f32 temp_fv0;
    s32 temp_s4;
    s32 temp_s6;
    s32 var_v1;
    u32 var_s0;
    s32 j;

    temp_s6 = getAvailablePlayerCraftFlagsConsiderUnlocks(arg1);
    temp_s4 = getAvailablePlayerCraftFlagsIgnoreUnlocks(arg1);
    var_v1 = 0;
    var_s0 = 0;
    do {
        if (temp_s4 & (1 << var_s0)) var_v1++;
        var_s0++;
    } while (var_s0 < 9);
    j = 0;
    for (var_s0 = 0; var_s0 < 9; var_s0++) {
        if (temp_s4 & (1 << var_s0)) {
            temp_fv0 = (((bridgeShipBlueprintScreenPositions[var_v1 - 1][j].x / 1.5f) - 32.0f) * 512.0f) * 0.001953125f;
            bridgeShipBlueprints[var_s0].xpos = temp_fv0;
            D_menu_overlay_800CDF80[var_s0].x = temp_fv0;
            temp_fv0 = (((bridgeShipBlueprintScreenPositions[var_v1 - 1][j].y / 1.1f) - 75.0f) * 340.0f) / 340.0f;
            bridgeShipBlueprints[var_s0].ypos = temp_fv0;
            D_menu_overlay_800CDF80[var_s0].y = temp_fv0;
            j++;
        }
        if (temp_s6 & (1 << var_s0)) {
            bridgeShipBlueprints[var_s0].rgba = bridgeGreenColor;
        } else {
            bridgeShipBlueprints[var_s0].rgba = bridgeRedColor;
        }
        setLookupEntryField5ByKey(arg0, &bridgeShipBlueprints[var_s0], (temp_s4 & (1 << var_s0)) != 0);
    }
}
#endif

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A5BA4);

extern u32 D_main_bss_80130B4C;
extern char D_menu_overlay_800A5BA4[];
void setPlayerSlotAnimationFlag(s32, char *, s32, s32, s16);

void printLevelSelectWeaponText(u8 arg0) {
    char buf[0x100];
    char *a;
    char *b;
    char *c;
    char *d;
    char *e;
    s32 flags;
    s32 n;
    s32 i;
    u16 y;

    n = 0;
    flags = getAvailablePlayerCraftFlagsIgnoreUnlocks(arg0);
    i = 0;
    do {
        if (flags & (1 << i)) {
            n++;
        }
        i++;
    } while ((u8)i < 9U);
    a = getGameOrFrontText(0x48);
    if (D_main_bss_80130B4C & 0x200) {
        b = getGameOrFrontText(0x4B);
    } else {
        b = D_menu_overlay_800A5BA4;
    }
    c = getGameOrFrontText(0x4D);
    d = getGameOrFrontText(0x4A);
    if (D_main_bss_80130B4C & 0x10000) {
        e = getGameOrFrontText(0x4B);
    } else {
        e = D_menu_overlay_800A5BA4;
    }
    sprintf(buf, "%s%s%s\n%s%s%s", a, b, c, d, e, getGameOrFrontText(0x4C));
    y = 0xFFD0;
    if (n == 1) {
        y = 0xFFFD;
    }
    setPlayerSlotAnimationFlag(2, buf, 1, -0x100, y);
    setPlayerSlotEntryRGB(2, 1, &bridgeWhiteColor);
}

extern s32 D_menu_overlay_800CDFB0;
extern u8 bridgeMenuDesiredLevel;
extern u8 D_menu_overlay_800CDABF;
extern f32 D_menu_overlay_800CDB0C;
extern void setVoiceLineLoopFlag(s32);
s32 mallocVoiceLineStruct(u16 *, f32, s32);
s32 startPlayerSlotAnimationChannelLooping(s32, f32);

void startSlotLoopAnimWithVoiceSync(f32 arg0) {
    u16 sp10[2] = {0, 0xFFFF};
    s32 r;

    r = startPlayerSlotAnimationChannelLooping(D_menu_overlay_800CDFAC, arg0) & 0xFF;
    switch (r) {
    case 1:
        if (D_menu_overlay_800CDFB0 == 0) {
            sp10[0] = bridgeMenuDesiredLevel + 0x279;
            D_menu_overlay_800CDFB0 = mallocVoiceLineStruct(sp10, 0.7f, 0x6E);
            D_menu_overlay_800CDABF = r;
            D_menu_overlay_800CDB0C = -10.0f;
        }
        D_menu_overlay_800CC700 = bsearchFactor5TableByU16Key(0x43, 0x32, 0x40);
        break;
    case 2:
        stopVoiceByHandleLocked(D_menu_overlay_800CC700);
        D_menu_overlay_800CC700 = -1;
        break;
    case 3:
        if (D_menu_overlay_800CDFB0 != 0) {
            setVoiceLineLoopFlag(D_menu_overlay_800CDFB0);
        }
        stopVoiceByHandleLocked(D_menu_overlay_800CC700);
    case 4:
        bsearchFactor5TableByU16Key(0x42, 0x55, 0x40);
        break;
    }
    if (bridgeTransitionState == 0) {
        D_menu_overlay_800CDB0C = D_menu_overlay_800CDB0C - arg0;
        if (D_menu_overlay_800CDB0C > -5.0f && D_menu_overlay_800CDB0C < 0.0f && D_menu_overlay_800CDABF == 0 && D_menu_overlay_800CDFB0 == 0 && bridgeMenuState != 4) {
            sp10[0] = bridgeMenuDesiredLevel + 0x279;
            D_menu_overlay_800CDFB0 = mallocVoiceLineStruct(sp10, 0.7f, 0x6E);
            D_menu_overlay_800CDABF = 1;
            D_menu_overlay_800CDB0C = -10.0f;
        }
    }
}

void samplePlayerAnimChannel(s32, s32, f32);
void activateAnimationKeyframe(s32, s32, u8);
struct ui_element *getPlayerSlotFieldAt34(u16, u16);
void setPlayerSlotEntryRGB(u16, u16, struct rgba *);
extern s32 D_menu_overlay_800CDCDC;

void setupPlayerCraftDisplayAnim(void) {
    u8 i;
    s32 k;

    setPlayerSlotAnimationFlag(0, "XX", 6, -0x100, 0x72);
    setPlayerSlotAnimationFlag(0, "XX", 9, -0x100, 0x72);
    samplePlayerAnimChannel(0, 6, 1.0f);
    i = 4;
    samplePlayerAnimChannel(0, 9, 1.0f);
    relocateLookupEntryToNewKey((struct some_ui_list_root *)D_menu_overlay_800CDCDC, getPlayerSlotFieldAt34(0, 6), 0x19);
    relocateLookupEntryToNewKey((struct some_ui_list_root *)D_menu_overlay_800CDCDC, getPlayerSlotFieldAt34(0, 9), 0x19);
    setPlayerSlotAnimationFlag(0, "{", 4, -0x100, 0x76);
    setPlayerSlotAnimationFlag(0, "{", 7, -0x100, 0x76);
    setPlayerSlotAnimationFlag(0, "}", 5, -0x100, 0x76);
    setPlayerSlotAnimationFlag(0, "}", 8, -0x100, 0x76);
    do {
        k = i;
        activateAnimationKeyframe(0, k, 0);
        setPlayerSlotEntryRGB(0, k, &bridgeWhiteColor);
        samplePlayerAnimChannel(0, k, 1.0f);
        i++;
    } while (i < 10);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/115E00", applyPlayerSlotAnimChannelKeyframe);

s32 anyAudioSlotActive();
s32 bufferArbiterProducerScanWait();
s32 destroyPlayerShipRecord(s32, s32 *);
s32 finalizeCurrentSpeechBuffer();
s32 shutdownFormatMessageWorker();
s32 tickMusyXIfActive();
extern s32 D_menu_overlay_800CDC80;
extern s32 D_menu_overlay_800CDCDC;

void drainAudioAndFinalizeSpeechBuffer(void) {
    tickMusyXIfActive();
    do {

    } while (!(anyAudioSlotActive() & 0xFF));
    bufferArbiterProducerScanWait();
    destroyPlayerShipRecord(D_menu_overlay_800CDCDC, &D_menu_overlay_800CDC80);
    shutdownFormatMessageWorker();
    finalizeCurrentSpeechBuffer();
}

s32 tickMultiPartVoiceLine(s32, f32);
extern s32 D_menu_overlay_800CDFB0;

void tickTimedScreenFadeFloat(f32 arg0) {
    if ((D_menu_overlay_800CDFB0 != 0) && ((tickMultiPartVoiceLine(D_menu_overlay_800CDFB0, arg0) & 0xFF) == 1)) {
        D_menu_overlay_800CDFB0 = 0;
    }
}

extern void queueAudioVoiceCmd(s32, s32, s32, s32);
extern void playSimpleAudioCmd(s32, s32, s32);
extern void setVoiceLineLoopFlag(s32);
extern void applyFlagsToMeshTreeOrList(s32, s32, s32, s32);
extern void releaseSceneObjectMeshTree(s32);
extern void beginSceneRenderFrame(s32);
extern void updateTextOverlayLookupEntry(s32, s32 *, f32);
extern s32 D_menu_overlay_800CDCE0;
typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x18];
} MenuScreenMeshSlot;

extern MenuScreenMeshSlot D_menu_overlay_800CDCF0[];

void playExitSoundAndToggleScreenMeshes(void) {
    queueAudioVoiceCmd(0, 400, D_menu_overlay_800CDCE0, 1);
    playSimpleAudioCmd(0, 400, 0xFE);
    if (D_menu_overlay_800CDFB0 != 0) {
        setVoiceLineLoopFlag(D_menu_overlay_800CDFB0);
    }
    applyFlagsToMeshTreeOrList(D_menu_overlay_800CDCF0[2].unk4, 0, 0x10000000, 0);
    applyFlagsToMeshTreeOrList(D_menu_overlay_800CDCF0[3].unk4, 0, 0x10000000, 0);
    releaseSceneObjectMeshTree(D_menu_overlay_800CDCF0[2].unk4);
    releaseSceneObjectMeshTree(D_menu_overlay_800CDCF0[3].unk4);
    beginSceneRenderFrame(1);
    updateTextOverlayLookupEntry(D_menu_overlay_800CDCDC, &D_menu_overlay_800CDC80, 24.0f);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/115E00", fake_func_800B2628);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A5C18);
