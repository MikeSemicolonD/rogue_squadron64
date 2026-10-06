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

typedef struct {
    u16 x;
    s16 y;
} VsGlyph;

typedef struct {
    /* 0x00 */ u16 id;
    /* 0x02 */ u8 b2;
    /* 0x03 */ u8 b3;
    /* 0x04 */ u8 b4;
    /* 0x05 */ u8 b5;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ s32 key;
    /* 0x0C */ s16 hC;
    /* 0x0E */ u16 cur;
    /* 0x10 */ u16 count;
    /* 0x12 */ u8 pad12[4];
    /* 0x16 */ s16 h16;
    /* 0x18 */ f32 f18;
    /* 0x1C */ f32 f1C;
} VsHud;

typedef struct {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ u16 h8;
    /* 0x0A */ u8 padA[2];
    /* 0x0C */ s32 wC;
    /* 0x10 */ VsGlyph *glyphs;
} VsSlot;

typedef struct {
    u8 pad0[0x10];
    u32 w10;
    u8 pad14[2];
    u8 b16;
} VsSettings;

extern s32 D_main_bss_80139010;
extern u16 D_main_bss_80139014;
extern VsSettings gGameSettings;
#define VH ((VsHud *)D_main_bss_80139010)
s32 getBootConfigField12();
s32 getVoiceText(u16);
u8 *getVoiceTxtStringPtr(u16);
void setPlayerSlotAnimationFlag(u16, char *, s32, s32, s32);
u8 *getPlayerSlotLookupBase(u8);
f32 getVoicePlaybackProgressByKey(s32, f32 *);

#define SETV(K) { u16 vid = K; if (VH->id != vid) { VH->id = vid; getVoiceText(vid); { VsHud *h = VH; h->b3 = 0; h->key = -1; } VH->b2 = 0; } }

void tickVoiceSubtitleDisplay(f32 dt) {
    f32 sp18;
    s32 lim;
    u8 *str;
    VsSlot *slot;
    VsGlyph *gl2;
    VsGlyph *glyphs;
    s32 line;
    s32 i;
    s32 k;
    s32 brk;
    s32 sub;
    s32 j;
    s32 n;
    s32 cnt;
    s32 best;

    lim = VH->h16;
    if (gGameSettings.b16 != 0) {
        SETV(0x222)
    } else if (gGameSettings.w10 & 0x20) {
        SETV(0x223)
    }
    if (VH->id == 0xFFFF) return;
    str = getVoiceTxtStringPtr(VH->id);
    if (str == NULL) return;
    if (VH->b2 == 0) {
        setPlayerSlotAnimationFlag(D_main_bss_80139014, (char *)str, 0, (s16)(-((getBootConfigField12() & 0xFFFF) * 100) / 320), 10);
        slot = (VsSlot *)getPlayerSlotFieldAt34(D_main_bss_80139014, 0);
        if (slot->h8 == 0) {
            VH->id = 0xFFFF;
            return;
        }
        sub = 0;
        line = sub;
        brk = sub;
        VH->b2 = 1;
        VH->cur = 0;
        glyphs = slot->glyphs;
        i = sub;
        for (k = 0; str[k] != 0; k++) {
            if (str[k] == ' ') brk = i;
            if (getPlayerSlotLookupBase(D_main_bss_80139014)[str[k]] != 0xFF) {
                glyphs[i].x = glyphs[i].x - sub;
                if (lim < (s16)glyphs[i].x) {
                    line += VH->b5;
                    sub += (s16)glyphs[brk].x;
                    for (j = i; j >= brk; j--) {
                        glyphs[j].x = glyphs[j].x - glyphs[brk].x;
                        glyphs[j].y = line;
                    }
                }
                glyphs[i].y = line;
                i++;

            }
        }
        VH->b4 = line / VH->b5 + 1;
        {
            VsHud *h = VH;
            h->count = slot->h8;
            h->b3 = 0;
        }
    }
    {
        VsHud *h = VH;
        if (h->b3 == 0) {
            if ((u16)(h->id - 0x222) < 2) {
                h->f18 = 0.0f;
                h->b3 = 1;
                h->f1C = 2000000.0f;
            } else if (getVoicePlaybackProgressByKey(h->key, &sp18) > 0.0f) {
                VsHud *h2 = VH;
                h2->f18 = 0.0f;
                h2->f1C = sp18;
                h2->b3 = 1;
            }
            if (VH->b3 == 0) return;
        }
    }
    VH->f18 = VH->f18 - dt;
    if (VH->f18 <= 0.0f) {
        slot = (VsSlot *)getPlayerSlotFieldAt34(D_main_bss_80139014, 0);
        if (VH->cur >= VH->count) {
            VH->id = 0xFFFF;
            getPlayerSlotFieldAt34(D_main_bss_80139014, 0);
            return;
        }
        if (VH->b3 >= 2) {
            slot->wC = slot->wC + slot->h8 * 2;
            slot->glyphs = (VsGlyph *)((u8 *)slot->glyphs + slot->h8 * 4);
        }
        n = 1;
        gl2 = slot->glyphs;
        line = gl2[0].y;
        cnt = 1;
        for (; n + VH->cur < VH->count; n++) {
            if (line < gl2[n].y) {
                if (cnt >= 3) break;
                line = gl2[n].y;
                cnt++;
            }
        }
        {
            VsHud *h = VH;
            h->cur = h->cur + n;
            slot->h8 = n;
            h->hC = -(h->b5 + line);
            if (h->cur >= h->count) {
                h->f18 = h->f18 + 0.5f;
            } else {
                h->b3 = h->b3 + 1;
            }
        }
        VH->f18 = (VH->f1C * (f32)cnt) / (f32)VH->b4;
    }
}

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
