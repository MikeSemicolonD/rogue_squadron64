#include "common.h"
#include "common_types.h"
#include "PR/os.h"

typedef struct { s16 x; s16 y; u8 c; u8 pad; } DbgGlyphF;
extern DbgGlyphF gDbgGlyphsF[] __asm__("D_main_bss_80128F28");
extern s16 D_main_bss_8012BF28;
extern s16 D_main_bss_8012BF2A;
extern s16 D_main_bss_8012BF2C;
extern s16 D_main_bss_80128F22;
typedef struct { u32 w0; u32 w1; } DbgDL;
#define DBG_DL_CHECK(dl) if ((u32)(dl) >= D_main_bss_801163D4) { (dl)->w0 = 0xB5000000; (dl)->w1 = 0; (dl) = (DbgDL *)allocateDisplayListBuffer(); }
extern u32 D_main_bss_801163D4;
extern u16 *D_main_bss_8011A444;
extern char *D_main_80038CF0;
DbgDL *allocateDisplayListBuffer();
DbgDL *findOrCreateMaterial(DbgDL *, u16, s32);
char *strchr(const char *, s32);
DbgDL *flushDebugTextOverlay(DbgDL *dl) {
    DbgDL *p;
    s16 i;
    u8 c;
    register char *s asm("$3");
    register u8 idx asm("$4");
    s32 col; u8 row; s32 t;

    if (D_main_bss_8012BF28 != 0) {
        DBG_DL_CHECK(dl);
        { DbgDL *_g = dl++; _g->w0 = 0xE7000000; _g->w1 = 0; }
        dl = findOrCreateMaterial(dl, D_main_bss_8011A444[(u16)D_main_bss_80128F22 * 2 + 1], 2);
        DBG_DL_CHECK(dl);
        { DbgDL *_g = dl++; _g->w0 = 0xB900031D; _g->w1 = 0; }
        DBG_DL_CHECK(dl);
        { DbgDL *_g = dl++; _g->w0 = 0xBA001402; _g->w1 = 0x200000; }
        DBG_DL_CHECK(dl);
        { DbgDL *_g = dl++; _g->w0 = 0xBA000C02; _g->w1 = 0; }
        DBG_DL_CHECK(dl);
        { DbgDL *_g = dl++; _g->w0 = 0xBA001301; _g->w1 = 0; }
        DBG_DL_CHECK(dl);
        { DbgDL *_g = dl++; _g->w0 = 0xB9000002; _g->w1 = 1; }
        DBG_DL_CHECK(dl);
        { DbgDL *_g = dl++; _g->w0 = 0xF9000000; _g->w1 = 0; }
        for (i = 0; i < D_main_bss_8012BF28; i++) {
            c = gDbgGlyphsF[i].c;
            if ((u32)(c - 'a') < 26) {
                c -= 0x20;
            }
            s = strchr(D_main_80038CF0, c);
            if (s != NULL) {
                { register char *b asm("$2") = D_main_80038CF0; register s32 d asm("$5") = s - b; idx = (u8)d; __asm__("" : : "r"(d)); }
                col = (u8)(idx % 21);
                row = idx / 21;
                t = row * 7;
                if ((u32)(dl + 1) >= D_main_bss_801163D4) {
                    dl->w0 = 0xB5000000;
                    dl->w1 = 0;
                    dl = (DbgDL *)allocateDisplayListBuffer();
                }
                {
                    DbgDL *_g = dl;
                    _g->w0 = 0xE4000000 | ((((gDbgGlyphsF[i].x + 7) * 4) & 0xFFF) << 12) | (((gDbgGlyphsF[i].y + 6) * 4) & 0xFFF);
                    _g->w1 = (((gDbgGlyphsF[i].x * 4) & 0xFFF) << 12) | ((gDbgGlyphsF[i].y * 4) & 0xFFF);
                    _g[1].w0 = ((((col << 3) << 5) & 0xFFFF) << 16) | ((t << 5) & 0xFFFF);
                    _g[1].w1 = 0x10000400;
                }
                dl += 2;
            }
        }
        D_main_bss_8012BF28 = 0;
    }
    D_main_bss_8012BF2A = 0x28;
    D_main_bss_8012BF2C = 0x10;
    return dl;
}

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
