#include "common.h"
#include "common_types.h"

#include "main/66FB0.h"

struct D_main_8009FCD4_type {
    u32 songId;
    char *songName;
};

void *D_main_8009FCD0 = NULL;

struct D_main_8009FCD4_type D_main_8009FCD4[] = {
    {0x00000006, "c1l1_theme"},
    {0x00000007, "c1l1_spc01"},
    {0x00000008, "c1l1_spc02"},
    {0x00000009, "c1l1_prob1"},
    {0x0000000A, "c1l1_prob2"},
    {0x0000000B, "c1l2_theme"},
    {0x0000000C, "c1l2_spc01"},
    {0x0000000D, "c1l3_theme"},
    {0x0000000E, "c1l3_spc01"},
    {0x0000000F, "c1l4_theme"},
    {0x00000010, "c1l4_spc01"},
    {0x00000011, "c1l5_theme"},
    {0x00000012, "c1l5_spc01"},
    {0x00000013, "c1l5_act01"},
    {0x00000014, "c1l5_act02"},
    {0x00000015, "c2l1_theme"},
    {0x00000016, "c2l1_spc01"},
    {0x00000018, "c2l2_theme"},
    {0x00000019, "c2l2_spc01"},
    {0x0000001A, "c2l3_theme"},
    {0x0000001B, "c2l3_spc01"},
    {0x0000001C, "c2l5_theme"},
    {0x0000001E, "c3l1_theme"},
    {0x0000001F, "c3l2_theme"},
    {0x00000020, "c3l4_theme"},
    {0x00000021, "c3l4_spc01"},
    {0x00000022, "c3l5_theme"},
    {0x00000023, "c3l5_spc01"},
    {0x00000024, "c4l1_theme"},
    {0x00000025, "c5l1_start"},
    {0x00000026, "c5l1_1"},
    {0x00000027, "c5l1_2"},
    {0x00000028, "c5l1_3"},
    {0x00000029, "c5l2_theme"},
    {0x0000002A, "c5l2_spc01"},
    {0x0000002B, "c5l3_theme"},
    {0x0000002F, "action01b"},
    {0x0000002E, "action01"},
    {0x00000030, "action02"},
    {0x00000031, "action04"},
    {0x00000032, "action05"},
    {0x00000033, "action06"},
    {0x00000034, "action07"},
    {0x0000002C, "silent01"},
    {0x0000002D, "silent02"},
    {0x00000060, "addtl"},
    {0x00000035, "jingle01"},
    {0x00000036, "jingle02"},
    {0x00000037, "jingle03"},
    {0x00000038, "jingle04"},
    {0x00000039, "jingle05"},
    {0x0000003A, "jingle06"},
    {0x0000003B, "jingle07"},
    {0x0000003C, "jingle08"},
    {0x00000061, "empty"},
    {0x0000003D, "c1l1_cut1"},
    {0x0000003E, "c1l2_cut1"},
    {0x0000003F, "c1l3_cut1"},
    {0x00000040, "c1l4_cut1"},
    {0x00000041, "c1l5_cut1"},
    {0x00000042, "c2l1_cut1"},
    {0x00000043, "c2l2_cut1"},
    {0x00000044, "c2l3_cut1"},
    {0x00000045, "c2l5_cut1"},
    {0x00000046, "c2l6_cut1"},
    {0x00000047, "c3l1_cut1"},
    {0x00000048, "c3l2_cut1"},
    {0x00000049, "c3l3_cut1"},
    {0x0000004A, "c3l4_cut1"},
    {0x0000004B, "c3l5_cut1"},
    {0x0000004C, "c4l1_cut1"},
    {0x0000004D, "c5l1_cut1"},
    {0x0000004E, "c5l2_cut1"},
    {0x0000004F, "c5l3_cut1"},
    {0x00000050, "extr_cut1"},
    {0x00000051, "cut_seq1"},
    {0x00000052, "cut_seq2"},
    {0x00000053, "cut_seq3"},
    {0x00000054, "cut_seq4"},
    {0x00000055, "cut_seq5"},
    {0x00000056, "cut_seq6"},
    {0x00000057, "cut_seq7"},
    {0x00000058, "cut_seq8"},
    {0x00000059, "cut_jing1"},
    {0x0000005A, "cut_jing2"},
    {0x0000005C, "roguetheme"},
    {0x00000001, "roguetitle"},
    {0x0000005F, "imperial"},
    {0x00000002, "title"},
    {0x00000003, "hangar1"},
    {0x00000004, "hangar2"},
    {0x00000005, "hangar3"},
    {0x00000000, "logo1"},
    {0x0000005E, "credits"},
    {0x0000005D, "outro"},
    {0x0000005B, "kasan1"},
    {0xFFFFFFFF, 0x00000000},
};

// DO NOT DELETE ME I AM REQUIRED FOR MATCHING
u32 data_pad_66FB0 = 0x8FC20040;

typedef struct {
    s32 id;
    s32 value;
} AudioChannelEntry;
extern AudioChannelEntry D_main_bss_80139A00[];


extern s32 D_main_bss_80137CFC;
extern s32 D_main_bss_80138920;
extern s32 D_main_bss_80139B4C;
extern s32 D_main_bss_80139B50;
extern s32 D_main_bss_80139B54;
extern void *D_main_8009FCD0;
s32 load_asset_with_malloc_flags(char *, s32);
void *findAssetAcrossSegments(s32, s32, s32, char *, s32);
s32 parseSndFiles(s32, s32, void *, s32, s32);
void playSimpleAudioCmd(s32, s32, s32);
void applyVolumeSettingsToMixer(void);

void loadSndFiles(void) {
    s32 i;
    s32 m1 = -1;

    i = 15;
    do {
        D_main_bss_80139A00[i].id = m1;
        i--;
    } while (i >= 0);
    D_main_bss_80139B54 = load_asset_with_malloc_flags("sound/proj_SND", 0);
    D_main_bss_80139B50 = load_asset_with_malloc_flags("sound/pool_SND", 0);
    D_main_bss_80139B4C = load_asset_with_malloc_flags("sound/sdir_SND", 0);
    D_main_8009FCD0 = findAssetAcrossSegments(D_main_bss_80138920, 0, D_main_bss_80137CFC, "sound/samp_SND", 0);
    parseSndFiles(D_main_bss_80139B54, 0x24, D_main_8009FCD0, D_main_bss_80139B4C, D_main_bss_80139B50);
    playSimpleAudioCmd(0, 0, 0xFE);
    playSimpleAudioCmd(0, 0, 0xFD);
    applyVolumeSettingsToMixer();
}

extern void *D_main_bss_80138D1C;
extern s32 D_main_bss_80139A80;
extern f32 D_main_bss_80139B30[3];
extern f32 D_main_bss_80139B40[3];
extern f32 D_main_bss_80139B58[3];
void register3DAudioListenerNode(void *, void *, void *, void *, void *, f32, f32, f32, s32, s32);

void initAudioListenerFromCamera(void) {
    f32 *cam = D_main_bss_80138D1C;

    D_main_bss_80139B58[0] = cam[0x4C / 4];
    D_main_bss_80139B58[1] = cam[0x50 / 4];
    D_main_bss_80139B58[2] = cam[0x54 / 4];
    D_main_bss_80139B30[0] = cam[0x30 / 4];
    D_main_bss_80139B30[1] = cam[0x3C / 4];
    D_main_bss_80139B30[2] = cam[0x48 / 4];
    D_main_bss_80139B40[0] = -cam[0x2C / 4];
    D_main_bss_80139B40[1] = -cam[0x38 / 4];
    D_main_bss_80139B40[2] = -cam[0x44 / 4];
    register3DAudioListenerNode(&D_main_bss_80139A80, D_main_bss_80139B58, D_main_bss_80139B30, D_main_bss_80139B30, D_main_bss_80139B40, 2.0f, 2.0f, 50.0f, 0, 0x7F);
}

extern int sprintf(char *, const char *, ...);
s32 get_asset_size_extra(s32, char *);
s32 rs_malloc(s32, s32);
void setupAssetDma(s32, s32, void *, s32, s32, s32);
void teardownAssetDma(s32, void *);

s32 loadSongAssetByName(s32 arg0, s32 arg1) {
    char sp18[0x28];
    AudioChannelEntry *slot;
    AudioChannelEntry *e;
    AudioChannelEntry *p;
    s32 i;
    s32 j;
    s32 k;
    struct D_main_8009FCD4_type *s;
    s32 size;
    void *seg;

    i = 0;
    p = D_main_bss_80139A00;
    do {
        if (p->id == arg1) {
            return 1;
        }
        i++;
        p++;
    } while (i < 0x10);
    i = 0;
    do {
        if (D_main_bss_80139A00[i].id == -1) {
            for (j = 0; D_main_8009FCD4[j].songId != -1; j++) {
                if (D_main_8009FCD4[j].songId == arg1) {
                    sprintf(sp18, "sound/%s_SNG", D_main_8009FCD4[j].songName);
                    size = get_asset_size_extra(D_main_bss_80137CFC, sp18);
                    D_main_bss_80139A00[i].value = rs_malloc(size, 0);
                    seg = findAssetAcrossSegments(arg0, 0, D_main_bss_80137CFC, sp18, 0);
                    setupAssetDma(arg0, 0, seg, 0, size, D_main_bss_80139A00[i].value);
                    teardownAssetDma(arg0, seg);
                    D_main_bss_80139A00[i].id = arg1;
                    return 1;
                }
            }
        }
        i++;
    } while (i < 0x10);
    return 0;
}

typedef struct AudioListenerVec3 {
    f32 v[3];
} AudioListenerVec3;

extern f32 D_main_bss_80139B10[3];
extern f32 D_main_bss_80139B20[3];
extern f32 vec3Length(Vec3f);
extern s32 setMusyX3DProperties(void *, void *, void *, void *, void *, s32);

void updateAudioListenerVelocity(f32 dt) {
    f32 *cam = D_main_bss_80138D1C;
    f32 x = cam[0x4C / 4];
    f32 y;
    f32 z;
    f32 len;

    D_main_bss_80139B58[0] = x;
    y = cam[0x50 / 4];
    D_main_bss_80139B58[1] = y;
    z = cam[0x54 / 4];
    D_main_bss_80139B58[2] = z;
    if (dt > 0.0f) {
        D_main_bss_80139B20[0] = (x - D_main_bss_80139B10[0]) / dt;
        D_main_bss_80139B20[1] = (y - D_main_bss_80139B10[1]) / dt;
        D_main_bss_80139B20[2] = (z - D_main_bss_80139B10[2]) / dt;
    } else {
        D_main_bss_80139B20[2] = 0.0f;
        D_main_bss_80139B20[1] = 0.0f;
        D_main_bss_80139B20[0] = 0.0f;
    }
    len = vec3Length(D_main_bss_80139B20);
    if (len > 37.5f) {
        f32 s;
        len = len / 0.75f;
        s = 50.0f / len;
        D_main_bss_80139B20[0] = D_main_bss_80139B20[0] * s;
        D_main_bss_80139B20[1] = D_main_bss_80139B20[1] * s;
        D_main_bss_80139B20[2] = D_main_bss_80139B20[2] * s;
    }
    *(AudioListenerVec3 *)D_main_bss_80139B10 = *(AudioListenerVec3 *)D_main_bss_80139B58;
    D_main_bss_80139B30[0] = cam[0x30 / 4];
    D_main_bss_80139B30[1] = cam[0x3C / 4];
    D_main_bss_80139B30[2] = cam[0x48 / 4];
    D_main_bss_80139B40[0] = -cam[0x2C / 4];
    D_main_bss_80139B40[1] = -cam[0x38 / 4];
    D_main_bss_80139B40[2] = -cam[0x44 / 4];
    setMusyX3DProperties(&D_main_bss_80139A80, D_main_bss_80139B58, D_main_bss_80139B20, D_main_bss_80139B30, D_main_bss_80139B40, 0x7F);
}

s32 unlinkMusyXListNode(s32 *);
extern s32 D_main_bss_80139A80;

void teardownAudioListenerNode(void) {
    unlinkMusyXListNode(&D_main_bss_80139A80);
}

extern s32 D_main_bss_80139B4C;
extern s32 D_main_bss_80139B50;
extern s32 D_main_bss_80139B54;
s32 anyAudioSlotActive();
s32 rs_free(s32);
s32 tickMusyXIfActive();
extern u8 D_main_bss_80130B39;

void waitForAnyAudioSlot(void) {
    tickMusyXIfActive();
    do {

    } while (!(anyAudioSlotActive() & 0xFF));
    if (D_main_bss_80130B39 == 0) {
        rs_free(D_main_bss_80139B54);
        rs_free(D_main_bss_80139B50);
        rs_free(D_main_bss_80139B4C);
    }
}

s32 parseSndFiles(s32, s32, void *, s32, s32);
extern s32 D_main_bss_80139B4C;
extern s32 D_main_bss_80139B50;
extern s32 D_main_bss_80139B54;

s32 parseLoadedSndSection(s32 arg0) {
    parseSndFiles(D_main_bss_80139B54, arg0 & 0xFFFF, D_main_8009FCD0, D_main_bss_80139B4C, D_main_bss_80139B50);
    return 1;
}

s32 rs_free(s32);

void freeAudioCacheEntry(s32 id) {
    s32 i;

    if (id == -1) {
        for (i = 0; i < 16; i++) {
            if (D_main_bss_80139A00[i].id != -1) {
                rs_free(D_main_bss_80139A00[i].value);
                D_main_bss_80139A00[i].id = -1;
            }
        }
    } else {
        for (i = 0; i < 16; i++) {
            if (D_main_bss_80139A00[i].id == id) {
                rs_free(D_main_bss_80139A00[i].value);
                D_main_bss_80139A00[i].id = -1;
            }
        }
    }
}

s32 findAudioChannelById(s32 arg0) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (D_main_bss_80139A00[i].id == arg0) {
            return D_main_bss_80139A00[i].value;
        }
    }
    return 0;
}

extern void *D_main_bss_80138D1C;

void updateAudioListenerPosFromPlayer(void) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv0_3;

    temp_fv0 = (*(f32 *)((u8 *)(D_main_bss_80138D1C) + 0x4C));
    (*(f32 *)((u8 *)(&D_main_bss_80139B10) + 0)) = temp_fv0;
    (*(f32 *)((u8 *)(&D_main_bss_80139B58) + 0)) = temp_fv0;
    temp_fv0_2 = (*(f32 *)((u8 *)(D_main_bss_80138D1C) + 0x50));
    (*(f32 *)((u8 *)(&D_main_bss_80139B10) + 4)) = temp_fv0_2;
    (*(f32 *)((u8 *)(&D_main_bss_80139B58) + 4)) = temp_fv0_2;
    temp_fv0_3 = (*(f32 *)((u8 *)(D_main_bss_80138D1C) + 0x54));
    (*(f32 *)((u8 *)(&D_main_bss_80139B10) + 8)) = temp_fv0_3;
    (*(f32 *)((u8 *)(&D_main_bss_80139B58) + 8)) = temp_fv0_3;
}
