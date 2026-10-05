#include "common.h"
#include "common_types.h"

#include "main/562A0.h"

struct text_header {
    u16 language_count;      /* 0x00 */
    u16 string_count;        /* 0x02 */
    u32 language_offsets[6]; /* 0x04 */
    // u32 filesize;         /* 0x18 The game treats this as part of the language_offsets */
}; // size 0x1C

struct text_header txtFileHeader;
u16 languageStringcount;
u16 bss_pad0_562A0;
u32 voiceTxtLanguageOffset;
u32 bss_pad1_562A0[2];
u8  voiceTxtString[0x180];

// This variable is weird.
// The data it points to is first an array of u16's, then an array of u8's (the actual string data)
// This is relevannt for matching certain functions (namely, `getGameOrFrontText`)
union {
    u16 *offsets;
    u8  *data;
} languageData = {NULL};
s32  D_main_8009ECA4 = -1;
u16 *languageStringOffsets = NULL;
// DO NOT DELETE ME I AM REQURIED FOR MATCHING
u32 data_pad_562A0 = 0x00431021;

#include "game_settings.h"
extern s32 D_main_bss_80138920;
extern s32 D_main_bss_80137CFC;
extern s32 findAssetAcrossSegments(s32, s32, s32, u8 *, s32);
extern void setupAssetDma(s32, s32, s32, u32, s32, void *);
extern s32 teardownAssetDma(s32, s32);
extern void *rs_malloc(u32, u16);

s32 loadTxtFile(u8 *arg0, u8 arg1) {
    s32 handle;
    s32 size;
    u8 *p;
    s32 key;
    s32 c;

    handle = findAssetAcrossSegments(D_main_bss_80138920, 0, D_main_bss_80137CFC, arg0, 1);
    setupAssetDma(D_main_bss_80138920, 0, handle, 0, 0x1C, &txtFileHeader);
    languageStringcount = txtFileHeader.string_count;
    if (gGameSettings.languageSelect >= txtFileHeader.language_count) {
        gGameSettings.languageSelect = 0;
    }
    if (arg1 == 0) {
        size = txtFileHeader.language_offsets[gGameSettings.languageSelect + 1] - txtFileHeader.language_offsets[gGameSettings.languageSelect];
        setupAssetDma(D_main_bss_80138920, 0, handle, txtFileHeader.language_offsets[gGameSettings.languageSelect], size, *(void **)&languageData.offsets = rs_malloc(size, 0));
        teardownAssetDma(D_main_bss_80138920, handle);
        key = 0xF5;
        size -= languageStringcount * 2;
        p = (u8 *)languageData.offsets + languageStringcount * 2;
        while (size != 0) {
            size--;
            c = *p ^ key;
            key ^= c;
            *p = c;
            p++;
        }
    } else {
        D_main_8009ECA4 = handle;
        size = txtFileHeader.string_count * 2;
        setupAssetDma(D_main_bss_80138920, 0, handle, txtFileHeader.language_offsets[gGameSettings.languageSelect], size, languageStringOffsets = rs_malloc(size, 0));
        voiceTxtLanguageOffset = txtFileHeader.language_offsets[gGameSettings.languageSelect];
    }
    return 1;
}

void loadGameOrFrontTxtFile(u8 *arg0) {
    loadTxtFile(arg0, 0);
}

char *getGameOrFrontText(s32 textId) {
    if ((textId >= 0) && (textId < languageStringcount)) {
        return &languageData.data[languageData.offsets[textId]];
    }
    return NULL;
}

s32 rs_free(u16 *);
s32 teardownAssetDma(s32, s32);
extern s32 D_main_bss_80138920;

void freeTxtFile(void) {
    if (languageData.offsets != NULL) {
        rs_free(languageData.offsets);
    }
    if (languageStringOffsets != NULL) {
        rs_free(languageStringOffsets);
    }
    if (D_main_8009ECA4 != -1) {
        teardownAssetDma(D_main_bss_80138920, D_main_8009ECA4);
        D_main_8009ECA4 = -1;
    }
    languageData.offsets = NULL;
    languageStringOffsets = NULL;
}

void loadVoiceTxtFile(u8 *arg0) {
    loadTxtFile(arg0, 1);
}

void setupAssetDma(s32, s32, s32, u32, s32, void *);

void getVoiceText(s32 id) {
    u8 *p;
    s32 key;
    s32 c;
    u8 out;
    s32 size;

    size = languageStringOffsets[id + 1] - languageStringOffsets[id];
    setupAssetDma(D_main_bss_80138920, 0, D_main_8009ECA4, voiceTxtLanguageOffset + languageStringOffsets[id], size, voiceTxtString);
    p = voiceTxtString;
    key = 0xF5;
    for (;;) {
        c = *p ^ key;
        out = c;
        key ^= c;
        if ((u8)(c - 'a') < 26) {
            out = c - 0x20;
        }
        *p = out;
        if (out == 0) {
            break;
        }
        p++;
    }
}

char *getVoiceTxtStringPtr(void) {
    return voiceTxtString;
}

INCLUDE_ASM("asm/nonmatchings/main/562A0", fake_func_80055A2C);
