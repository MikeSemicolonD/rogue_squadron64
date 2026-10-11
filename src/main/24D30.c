#include "common.h"
#include "common_types.h"
#include "PR/os.h"

INCLUDE_ASM("asm/nonmatchings/main/24D30", flushDebugTextOverlay);

typedef struct { s16 x; s16 y; u8 c; u8 pad; } DbgGlyph;
extern DbgGlyph D_main_bss_80128F28[];
extern u8 D_main_bss_80128F20;
extern s16 D_main_bss_8012BF28;
__inline__ void queueDebugTextGlyph(s32 x, s32 y, s32 c) {
    s32 i = D_main_bss_8012BF28;
    if (i < 0x800 && D_main_bss_80128F20 != 0) {
        D_main_bss_80128F28[i].c = c;
        D_main_bss_80128F28[i].x = x;
        D_main_bss_80128F28[i].y = y;
        D_main_bss_8012BF28 = (u16)D_main_bss_8012BF28 + 1;
    }
}

extern s16 D_main_bss_8012BF2A;
extern s16 D_main_bss_8012BF2C;
void setDebugTextCursor(s32 col, s32 row) {
    D_main_bss_8012BF2A = ((col << 16) >> 13) + 0x28;
    D_main_bss_8012BF2C = ((row << 16) >> 13) + 0x10;
}

extern u16 gDbgCurX __asm__("D_main_bss_8012BF2A");
extern u16 gDbgCurY __asm__("D_main_bss_8012BF2C");
void queueDebugTextGlyph(s32 x, s32 y, s32 c);
void drawDebugTextString(u8 *s) {
    while (*s != 0) {
        switch (*s) {
        case '\n':
            gDbgCurX = 0x28;
            gDbgCurY += 8;
            break;
        case '\t':
            gDbgCurX = (((gDbgCurX >> 3) & 0x1FF8) + 8) * 8;
            break;
        default:
            queueDebugTextGlyph(gDbgCurX, gDbgCurY, *s);
        case ' ':
            gDbgCurX += 8;
            break;
        }
        s++;
    }
    gDbgCurX = 0x28;
    gDbgCurY += 8;
}

#include "textures.h"
typedef struct { s32 w[3]; } DbgW3;
extern char strDbgData[];
extern char strDbgFont[];
extern char strDbgFonttex[];
extern DbgW3 strDbgFontmat;
extern u8 D_main_bss_80128F20;
extern s16 D_main_bss_80128F22;
extern s16 D_main_bss_8012BF28;
extern s16 D_main_bss_8012BF2A;
extern s16 D_main_bss_8012BF2C;
s32 findManifestEntryByName(char *);
s32 get_asset_size_extra(s32, char *);
void *rs_malloc(s32, s32);
void rs_free(void *);
s32 findAssetAcrossSegments(s32, s32, s32, char *, s32);
void setupAssetDma(s32, s32, s32, s32, s32, void *);
void teardownAssetDma(s32, s32);
s32 freeManifestSegmentAssets(s32);
s32 registerHmtTextureInTable(struct material_entry *, struct texture_entry *, u8);
void loadDebugAssets(s32 seg) {
    struct material_entry mat;
    struct texture_entry tex;
    s32 entry;
    s32 size;
    u8 *data;
    s32 asset;

    D_main_bss_80128F20 = 0;
    D_main_bss_8012BF28 = 0;
    entry = findManifestEntryByName(strDbgData);
    if (entry != -1) {
        size = get_asset_size_extra(entry, strDbgFont);
        data = rs_malloc(size, 8);
        asset = findAssetAcrossSegments(seg, 0, entry, strDbgFont, 0);
        setupAssetDma(seg, 0, asset, 0, size, data);
        teardownAssetDma(seg, asset);
        tex.pixel_offsets[0] = (u32)(data + 0x3C);
        tex.plte_offset = (u32)(data + 0xC);
        tex.texture_name_offset = (u32)strDbgFonttex;
        tex.width = *(u16 *)(data + 4);
        tex.height = *(u16 *)(data + 6);
        tex.one = 1;
        tex.flags_type = data[0] | 0x4000;
        ((u8 *)&tex.transparency_color)[0] = 0;
        ((u8 *)&tex.transparency_color)[1] = 0;
        ((u8 *)&tex.transparency_color)[2] = 0;
        *(DbgW3 *)mat.material_name = strDbgFontmat;
        D_main_bss_80128F22 = registerHmtTextureInTable(&mat, &tex, 1);
        rs_free(data);
        freeManifestSegmentAssets(entry);
        D_main_bss_8012BF2A = 0x28;
        D_main_bss_8012BF2C = 0x10;
        D_main_bss_80128F20 = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/24D30", fake_func_80024878);
