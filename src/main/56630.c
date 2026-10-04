#include "common.h"
#include "common_types.h"

typedef struct {
    u8 r, g, b, a;
} SubtitleRGBA;
static const SubtitleRGBA subtitleColor = { 0xE1, 0xAF, 0x00, 0xFF };

extern s32 D_main_bss_80139010;
extern u16 D_main_bss_80139014;
extern s32 D_main_bss_80130B50;
void loadVoiceTxtFile(char *);
s32 rs_malloc(s32, s32);
void setSubtitleOverlayScreenPos(s16, s16);
void loadCharTextureSet(s32, u16, s32, s32);
void setMenuOverlayHeaderState(s32, s32, s32);
void setPlayerSlotEntryRGB(u16, s32, SubtitleRGBA *);
void setPlayerSlotAnimationFlag(u16, char *, s32, s32, s32);
u8 *getPlayerSlotFieldAt34(u16, s32);

void initVoiceSubtitleSystem(void) {
    SubtitleRGBA sp18;
    s32 temp_s0;
    s32 temp_v0;
    u16 var_v1;
    u8 *slot;

    sp18 = subtitleColor;
    loadVoiceTxtFile("voice_TXT");
    temp_v0 = rs_malloc(0x20, 0);
    D_main_bss_80139010 = temp_v0;
    *(u16 *)temp_v0 = 0xFFFF;
    setSubtitleOverlayScreenPos(0, 0);
    temp_s0 = getBootConfigField14();
    if (((f32)(temp_s0 & 0xFFFF) / (f32)(getBootConfigField12() & 0xFFFF)) < 0.5f) {
        D_main_bss_80139014 = 0xA;
    } else {
        var_v1 = 4;
        if (D_main_bss_80130B50 & 1) {
            var_v1 = 0xB;
        }
        D_main_bss_80139014 = var_v1;
    }
    loadCharTextureSet(0, D_main_bss_80139014, 1, 0x12C);
    setMenuOverlayHeaderState(1, 0, 0);
    setPlayerSlotEntryRGB(D_main_bss_80139014, 0, &sp18);
    setPlayerSlotAnimationFlag(D_main_bss_80139014, "A\nA", 0, -0x64, 0xA);
    slot = getPlayerSlotFieldAt34(D_main_bss_80139014, 0);
    *(u32 *)(slot + 0x14) |= 0x20;
    *(u8 *)(D_main_bss_80139010 + 5) = *(u8 *)(*(s32 *)(slot + 0x10) + 7);
}

typedef struct {
    u16 unk0;
    u8 pad2;
    u8 unk3;
    u8 pad4[8];
    s16 unkC;
    u8 padE[4];
    s16 unk12;
    s16 unk14;
} HudOverlayInfo;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 *unk4_s16;
} HudNodeMeshInfo;

typedef struct HudNode {
    struct HudNode *next;
    struct HudNode *prev;
    u16 unk8;
    u8 padA[6];
    HudNodeMeshInfo *mesh;
    u8 pad14[4];
    f32 unk18;
    f32 unk1C;
} HudNode;

typedef struct {
    u8 pad0[8];
    HudNode *unk8;
    u8 padC[4];
    s32 unk10;
    s32 unk14;
} HudOwner;

extern s32 D_main_bss_80139010;
#define HUD_INFO ((HudOverlayInfo *)D_main_bss_80139010)
extern u16 D_main_bss_80139014;

void linkHudNodeAndComputeScreenPos(HudOwner *arg0) {
    HudNode *node;
    HudNode *old;

    if ((HUD_INFO->unk0 != 0xFFFF) && (HUD_INFO->unk3 != 0)) {
        node = (HudNode *)getPlayerSlotFieldAt34(D_main_bss_80139014, 0);
        old = arg0->unk8;
        node->next = old;
        if (old != NULL) {
            old->prev = node;
        }
        node->prev = NULL;
        arg0->unk8 = node;
        node->unk18 = (f32)((-arg0->unk10 / 2) + HUD_INFO->unk12);
        node->unk1C = (f32)((arg0->unk14 / 2) + HUD_INFO->unk14 + HUD_INFO->unkC);
        if ((u32)(HUD_INFO->unk0 - 0x222) < 2U) {
            node->unk18 = (f32)(((arg0->unk10 / 2) - ((s16 *)node->mesh)[node->unk8 * 2 - 2]) - (((s16 *)node->mesh)[2] * 5));
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/56630", tickVoiceSubtitleDisplay);

extern s32 D_main_bss_80139010;
s32 getBootConfigField12();
s32 getBootConfigField14();

void setSubtitleOverlayScreenPos(s16 arg0, s16 arg1) {
    (*(u16 *)((u8 *)(D_main_bss_80139010) + 0x12)) = (u16) (((arg0 + 0x18) * (getBootConfigField12() & 0xFFFF)) / 320);
    (*(s16 *)((u8 *)(D_main_bss_80139010) + 0x14)) = (s16) ((arg1 * (getBootConfigField14() & 0xFFFF)) / 224);
    (*(s16 *)((u8 *)(D_main_bss_80139010) + 0x16)) = (s16) ((((getBootConfigField12() & 0xFFFF) * 0x128) / 320) - (*(u16 *)((u8 *)(D_main_bss_80139010) + 0x12)));
}

s32 resetPlayerSlotChannelTransform(u16);
s32 rs_free(s32);
extern s32 D_main_bss_80139010;
extern u16 D_main_bss_80139014;

void freeSubtitleOverlay(void) {
    resetPlayerSlotChannelTransform(D_main_bss_80139014);
    rs_free(D_main_bss_80139010);
}

s32 getVoiceText(u16);

typedef struct {
    s16 id;
    u8 unk2;
    u8 unk3;
    s32 unk4;
    s32 unk8;
} ActiveVoiceLine;

void setActiveVoiceLine(s32 arg0, s32 arg1) {
    ActiveVoiceLine *p;

    ((ActiveVoiceLine *)D_main_bss_80139010)->id = arg0;
    getVoiceText(arg0);
    p = (ActiveVoiceLine *)D_main_bss_80139010;
    ((u8 *)p)[3] = 0;
    p->unk8 = arg1;
    ((ActiveVoiceLine *)D_main_bss_80139010)->unk2 = 0;
}

void clearActiveVoiceLine(void) {
    *(u16 *)D_main_bss_80139010 = 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/main/56630", fake_func_80056344);
