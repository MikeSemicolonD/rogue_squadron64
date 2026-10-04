#include "common.h"
#include "common_types.h"

#include "font.h"
#include "main/61FC0.h"

INCLUDE_ASM("asm/nonmatchings/main/61FC0", loadCharTextureSet);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", loadFontAsset);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", activateAnimationKeyframe);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", samplePlayerAnimChannel);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", measurePlayerSlotTextLayout);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", startPlayerSlotAnimationChannelExt);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", startPlayerSlotAnimationChannel);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", advancePlayerAnimationPhase);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", initPlayerSlotAnimationChannelFull);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", startPlayerSlotAnimationChannelFlagged);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", startPlayerSlotAnimationChannelLooping);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", buildPlayerCraftAssetTemplate);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", resolvePlayerAnimChannelKeyValue);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", initAllPlayerSlots);

void resetPlayerSlotChannelTransform(s32 arg0) {
    struct someFontThing *temp_v0;

    temp_v0 = D_main_8009FC10[arg0 & 0xFFFF];
    temp_v0->unk028 = NULL;
    temp_v0->unk024 = NULL;
    temp_v0->unk020 = NULL;
    temp_v0->unk030 = 0;
}

void *getPlayerSlotLookupBase(s32 arg0) {
    return D_main_8009FC10[arg0 & 0xFF]->unk020;
}

struct ui_element *getPlayerSlotFieldAt34(u16 arg0, u16 arg1) {
    return D_main_8009FC10[arg0]->unk034[arg1];
}

INCLUDE_ASM("asm/nonmatchings/main/61FC0", resetPlayerSlotAllChannels);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", setPlayerSlotAnimationFlag);

extern s8 D_main_bss_80139960;
extern s16 D_main_bss_80139962;
extern s16 D_main_bss_80139964;

void setMenuOverlayHeaderState(s8 arg0, s16 arg1, s16 arg2) {
    D_main_bss_80139960 = arg0;
    D_main_bss_80139962 = arg1;
    D_main_bss_80139964 = arg2;
}

extern s32 D_main_bss_80139968;

void setMenuOverlayHeaderCallback(s32 arg0) {
    D_main_bss_80139968 = arg0;
}

void setPlayerSlotEntryRGB(u16 arg0, u16 arg1, struct rgba *arg2) {
    struct ui_element *temp_v1;

    temp_v1 = D_main_8009FC10[arg0]->unk034[arg1];
    temp_v1->rgba.r = arg2->r;
    temp_v1->rgba.g = arg2->g;
    temp_v1->rgba.b = arg2->b;
}

void setPlayerSlotPointerAndFlag(s32 arg0, void *arg1, s32 arg2) {
    struct someFontThing *temp_v0;

    temp_v0 = D_main_8009FC10[arg0 & 0xFFFF];
    temp_v0->unk0FC = arg1;
    temp_v0->unk100 = arg2 & 0xFF;
}

void clearPlayerSlotPointerAndFlag(u16 arg0) {
    struct someFontThing *temp_v0;

    temp_v0 = D_main_8009FC10[arg0];
    temp_v0->unk0FC = NULL;
    temp_v0->unk100 = 0;
}

s32 isAnimInstanceActive(void *arg0) {
    return (*(s8 *)((u8 *)(arg0) + 1)) != 0;
}

struct ui_element *getPlayerAnimChannelEntryByIds(void *arg0) {
    return D_main_8009FC10[(*(u8 *)((u8 *)(arg0) + 8))]->unk034[(*(u8 *)((u8 *)(arg0) + 0)) + (*(u8 *)((u8 *)(arg0) + 9))];
}

struct ui_element *getPlayerAnimChannelEntryReversed(u8 *arg0) {
    s32 t = arg0[0] - 1;
    u16 idx = arg0[9] - t;
    return D_main_8009FC10[arg0[8]]->unk034[idx];
}

s32 identityReturnArg(s32 arg0) {
    return arg0;
}

s32 getPlayerSlotAnimChannelCount(void *arg0) {
    return (*(s32 *)((u8 *)(arg0) + 0x44C));
}

void markStructInitializedOnce(void *arg0) {
    if ((*(u8 *)((u8 *)(arg0) + 0x454)) == 0) {
        (*(s8 *)((u8 *)(arg0) + 0x456)) = 0;
        (*(u8 *)((u8 *)(arg0) + 0x454)) = 1U;
        (*(s32 *)((u8 *)(arg0) + 0x30)) = 0;
    }
}

s32 isStructUninitialized(void *arg0) {
    return ((*(s32 *)((u8 *)(arg0) + 0x454)) & 0xFF00FF00) == 0;
}

u16 findCharEntryValueByKey(u16 arg0, u8 arg1) {
    s32 var_a2;
    u16 var_v1;
    struct someFontThing *temp_a0;

    temp_a0 = D_main_8009FC10[arg0];
    for (var_v1 = 0; var_v1 < temp_a0->symbolCount; var_v1++) {
        if (temp_a0->symbolList[var_v1] == arg1) return temp_a0->unk028[var_v1];
    }
    return 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/main/61FC0", findCharEntryAltValueByKey);

u8 findCharEntryByteByKey(u16 arg0, u8 arg1) {
    s32 var_a2;
    u16 var_v1;
    struct someFontThing *temp_a0;

    temp_a0 = D_main_8009FC10[arg0];
    for (var_v1 = 0; var_v1 < temp_a0->symbolCount; var_v1++) {
        if (temp_a0->symbolList[var_v1] == arg1) return temp_a0->unk018[var_v1];
    }
    return 0;
}

s16 getPlayerSlotEntryBaseShort(u16 arg0) {
    return D_main_8009FC10[arg0]->unk006;
}

s16 samplePlayerSlotChannelScaledShort(u16 arg0, u16 arg1) {
    struct someFontThing *temp_a2;
    struct ui_element *temp_a1;
    struct xy_offset *temp_a0;
    s16 temp;

    temp_a2 = D_main_8009FC10[arg0];
    temp_a1 = temp_a2->unk034[arg1];
    temp_a0 = temp_a1->xy_offset_pointer;
    temp = temp_a2->unk006 + (temp_a0[temp_a1->texture_count - 1].y - temp_a0[0].y);
    return temp * temp_a1->height_scale;
}

s16 getPlayerSlotSpanShort(u16 arg0) {
    struct someFontThing *temp_v1;

    temp_v1 = D_main_8009FC10[arg0];
    return temp_v1->unk004 + temp_v1->unk00A;
}

void setPlayerSlotEnabledFlag(u16 arg0, u8 arg1) {
    D_main_8009FC10[arg0]->unk102 = arg1 == 0;
}

s16 invokeMenuOverlayHeaderCallback(s16 arg0) {
    s16 ret;

    if (D_main_bss_80139960 & 8) {
        ret = ((s16 (*)(s16))D_main_bss_80139968)(arg0);
    } else {
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main/61FC0", fake_func_80064294);
