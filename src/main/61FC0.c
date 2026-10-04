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

void measurePlayerSlotTextLayout(s32, struct ui_element *, u16, s32, s32, s32);
void setLookupEntryField5ByKey(void *, struct ui_element *, s32);

void startPlayerSlotAnimationChannelFlagged(u8 *arg0, s32 arg1, s8 arg2) {
    struct someFontThing *font;
    struct ui_element *elem;
    struct ui_element *e2;
    u32 a0;
    u32 a1;
    u16 s5;
    u16 s4;
    u8 *s3;

    if (arg0[0x454] == 0) {
        a0 = arg0[0x3C];
        a1 = arg0[0x3D];
        s5 = *(u16 *)(arg0 + 0x40);
        *(u32 *)(arg0 + 0x30) = 0;
        *(u32 *)(arg0 + 0x34) = 0;
        arg0[0x47] = arg2;
        arg0[0x455] = 0;
        font = D_main_8009FC10[a0];
        s4 = *(u16 *)(arg0 + 0x42);
        font->unk030 |= 1 << a1;
        font->unk084[a1] = font->unk01F;
        s3 = (u8 *)font + a1 * 4;
        elem = font->unk034[a1];
        elem->xy_offset_pointer = (struct xy_offset *)((u8 *)font->unk0EC + *(u16 *)((u8 *)font + 0xE8) * a1 * 4);
        elem->texture_id_pointer = (u16 *)((u8 *)font->unk0F0 + *(u16 *)((u8 *)font + 0xE8) * a1 * 2);
        measurePlayerSlotTextLayout(a0, elem, *(u16 *)((u8 *)font + 0xE8), arg1, (s16)s5, (s16)s4);
        if (font->unk0F4 != NULL) {
            setLookupEntryField5ByKey(font->unk0F4, *(struct ui_element **)(s3 + 0x34), elem->texture_count != 0);
        }
        if (font->unk01F == 0) {
            elem->flags |= 1;
        }
        *(u16 *)(s3 + 0x98) = s5;
        *(u16 *)(s3 + 0x9A) = s4;
        e2 = D_main_8009FC10[arg0[0x3C]]->unk034[arg0[0x3D]];
        setLookupEntryField5ByKey(*(void **)(arg0 + 0x450), e2, 0);
        *(u16 *)(arg0 + 0x44) = e2->texture_count;
        arg0[0x456] = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/61FC0", startPlayerSlotAnimationChannelLooping);

INCLUDE_ASM("asm/nonmatchings/main/61FC0", buildPlayerCraftAssetTemplate);

extern u16 D_main_bss_80139970[];
extern s8 D_main_8009ED88[];
s16 resolvePlayerAnimChannelKeyValue(u16 font, u16 key) {
    struct someFontThing *t = D_main_8009FC10[font];
    u16 i;
    u16 j;

    for (i = 0; i < t->symbolCount; i++) {
        if (t->unk024[i] == key || t->unk028[i] == key) {
            if (*(u8 *)&t->unk014 != 0) {
                return t->unk002;
            }
            return t->unk018[i];
        }
    }
    for (j = 0; j < 6; j++) {
        if (D_main_bss_80139970[j] == key) {
            return D_main_8009ED88[j];
        }
    }
    return 0;
}

extern s8 D_main_bss_80139960;
extern s16 D_main_bss_80139962;
extern s16 D_main_bss_80139964;

void initAllPlayerSlots(void) {
    u32 i = 0;
    u32 j;
    struct someFontThing **pp = D_main_8009FC10;
    for (; i < 12; i++) {
        struct someFontThing *t = *pp;
        u8 *q = (u8 *)t;
        t->unk020 = NULL;
        t->unk024 = NULL;
        t->unk028 = NULL;
        *(u16 *)&t->unk02C = 0;
        t->unk030 = 0;
        for (j = 0; j < 0x14; j++) {
            *(s32 *)(q + 0x34) = 0;
            t->unk084[j] = 0;
            q += 4;
        }
        pp++;
        *(u8 *)&t->unk0F8 = i + 0x41;
        t->unk0EC = NULL;
        t->unk0F0 = NULL;
        t->unk0F4 = NULL;
        t->unk0FC = NULL;
    }
    D_main_bss_80139960 = 1;
    D_main_bss_80139962 = 0x140;
    D_main_bss_80139964 = 0x140;
}

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

void resetPlayerSlotAllChannels(u16 slot, u8 arg1) {
    struct someFontThing *t = D_main_8009FC10[slot];
    u32 i;

    if (t->unk0F4 != NULL) {
        for (i = 0; i < *(u16 *)&t->unk02C; i++) {
            insertLookupEntry(t->unk0F4, t->unk034[i], arg1);
        }
    }
}

void measurePlayerSlotTextLayout(s32, struct ui_element *, u16, s32, s32, s32);

struct ui_element *setPlayerSlotAnimationFlag(u16 slot, s32 arg1, u16 idx, s16 arg3, s16 arg4) {
    struct someFontThing *t;
    struct ui_element *e;
    u8 *s2;

    t = D_main_8009FC10[slot];
    t->unk030 |= 1 << idx;
    t->unk084[idx] = t->unk01F;
    s2 = (u8 *)t + (idx * 4);
    e = t->unk034[idx];
    e->xy_offset_pointer = (void *)((u8 *)t->unk0EC + (*(u16 *)&t->unk0E8 * idx * 4));
    e->texture_id_pointer = (void *)((u8 *)t->unk0F0 + (*(u16 *)&t->unk0E8 * idx * 2));
    measurePlayerSlotTextLayout(slot, e, *(u16 *)&t->unk0E8, arg1, arg3, arg4);
    if (t->unk0F4 != NULL) {
        setLookupEntryField5ByKey(t->unk0F4, t->unk034[idx], e->texture_count != 0);
    }
    if (t->unk01F == 0) {
        e->flags |= 1;
    }
    *(s16 *)(s2 + 0x98) = arg3;
    *(s16 *)(s2 + 0x9A) = arg4;
    return t->unk034[idx];
}

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

extern u16 D_main_bss_80139980[];
u16 findCharEntryAltValueByKey(u16 font, u8 ch) {
    struct someFontThing *t = D_main_8009FC10[font];
    u16 i;

    for (i = 0; i < t->symbolCount; i++) {
        if ((u8)t->symbolList[i] == ch) {
            return t->unk024[i];
        }
    }
    for (i = 0; i < 6; i++) {
        if (ch == (u8)(i + 1)) {
            return D_main_bss_80139980[i];
        }
    }
    return 0xFFFF;
}

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
