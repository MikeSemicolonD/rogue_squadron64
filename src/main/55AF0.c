#include "common.h"

#include "main/55AF0.h"

extern s32 D_main_bss_80137CFC;
extern s32 D_main_bss_80138920;
s32 get_asset_size_extra(s32, s32);
s32 get_asset_size_simple(s32, s32);
s32 findAssetAcrossSegments(s32, s32, s32, s32, s32);
void setupAssetDma(s32, s32, s32, s32, s32, void *);
void teardownAssetDma(s32, s32);
void *rs_malloc(s32, s32);
s32 rs_free(s32);
void sprintf(char *, const char *, ...);
void rs_strncpy(char *, char *, s32);
s32 registerHmtTextureInTable(struct material_entry *, struct texture_entry *, u32);

u16 *loadAssetAndIterateSubchunks(s32 assetId, char *prefix, u16 *out, s32 flags, s32 every) {
    struct material_entry mat;
    struct full_image_header *file;
    struct full_image_header *hdr;
    struct texture_entry *tex;
    u16 *list;
    u16 *p;
    s32 size;
    s32 handle;
    u32 off;
    s32 count;
    s32 i;
    s32 j;
    u32 base;
    s32 rem;

    size = get_asset_size_extra(D_main_bss_80137CFC, assetId);
    file = rs_malloc(size, 4);
    if (file == NULL) {
        file = rs_malloc(size, 0);
    }
    size = get_asset_size_simple(D_main_bss_80137CFC, assetId);
    hdr = file;
    off = 0;
    count = 0;
    handle = findAssetAcrossSegments(D_main_bss_80138920, 0, D_main_bss_80137CFC, assetId, 0);
    setupAssetDma(D_main_bss_80138920, 0, handle, 0, size, file);
    teardownAssetDma(D_main_bss_80138920, handle);
    while (off < (u32)(size - 0x10)) {
        count++;
        off += (hdr->image_size + 7) & ~3;
        hdr = (struct full_image_header *)((u8 *)file + off);
    }
    list = out;
    if (list == NULL) {
        list = rs_malloc((count + 1) * 2, 0);
    }
    hdr = file;
    off = 0;
    i = 0;
    mat.material_type = 1;
    mat.zero = 0;
    *(u8 *)&mat.alwaysa = 1;
    mat.misc_float = 0.2f;
    mat.one = 1.0f;
    if (count > 0) {
        do {
        tex = &hdr->ent;
        base = (u32)tex;
        for (j = 0; j < 8; j++) {
            if (tex->pixel_offsets[j] != 0) {
                tex->pixel_offsets[j] += base;
            }
        }
        if (tex->plte_offset != 0) {
            tex->plte_offset += base;
        }
        if (tex->texture_name_offset != 0) {
            tex->texture_name_offset += base;
        }
        if (every == 0 || (rem = i % every) == 0) {
            hdr->ent.flags_type |= flags;
            if (prefix != NULL) {
                sprintf(mat.material_name, "%s%d", prefix, i);
                hdr->ent.texture_name_offset = (u32)mat.material_name;
            } else {
                rs_strncpy(mat.material_name, (char *)hdr->ent.texture_name_offset, 0x10);
            }
            list[i] = registerHmtTextureInTable(&mat, &hdr->ent, 0);
        } else {
            list[i] = list[i - rem];
        }
        i++;
        off += (hdr->image_size + 7) & ~3;
        hdr = (struct full_image_header *)((u8 *)file + off);
        } while (i < count);
    }
    if (out == NULL) {
        list[i] = 0xFFFF;
    }
    rs_free((s32)file);
    return list;
}

typedef struct {
    u32 size;
    u32 px[8];
    u32 plte;
    char *name;
    s16 w;
    s16 h;
    u8 one;
    u8 bd;
    u16 fl;
} SsFile;
u8 *rs_strcpy(u8 *, u8 *);
typedef struct {
    u16 material_type;
    u16 texture_index;
    f32 misc_float;
    f32 one;
    u32 zero;
    u8 alwaysa;
    u8 pad11[3];
    char material_name[16];
} SsMat;

void loadSpriteSheetTextureFrames(s32 assetId, char *prefix, u16 frameH, u16 *out, s32 maxFrames, s32 flags) {
    SsMat mat;
    SsFile *file;
    struct texture_entry *tex;
    u32 base;
    s32 size;
    s32 handle;
    s32 i;
    s32 j;
    s32 n;
    s32 row;

    size = get_asset_size_extra(D_main_bss_80137CFC, assetId);
    file = rs_malloc(size, 0);
    handle = findAssetAcrossSegments(D_main_bss_80138920, 0, D_main_bss_80137CFC, assetId, 0);
    setupAssetDma(D_main_bss_80138920, 0, handle, 0, size, file);
    teardownAssetDma(D_main_bss_80138920, handle);
    tex = (struct texture_entry *)&file->px;
    base = (u32)tex;
    for (j = 0; j < 8; j++) {
        if (tex->pixel_offsets[j] != 0) {
            tex->pixel_offsets[j] += base;
        }
    }
    if (tex->plte_offset != 0) {
        tex->plte_offset += base;
    }
    if (tex->texture_name_offset != 0) {
        tex->texture_name_offset += base;
    }
    n = file->h / frameH;
    if (maxFrames < n) {
        n = maxFrames;
    }
    file->h = frameH;
    switch (file->fl & 0xF) {
    case 2:
        row = file->w * 2;
        break;
    case 3:
        if (file->fl & 0x8000) {
            row = file->w * 4;
        } else {
            row = file->w * 3;
        }
        break;
    case 4:
        if (file->fl & 0x8000) {
            row = file->w;
        } else {
            row = (file->w + 1) >> 1;
        }
        break;
    case 1:
    case 5:
        row = file->w;
        break;
    case 0:
        row = (file->w + 1) >> 1;
        break;
    default:
        row = 0;
        break;
    }
    row = row * frameH;
    mat.material_type = 1;
    mat.zero = 0;
    mat.alwaysa = 1;
    mat.misc_float = 0.2f;
    mat.one = 1.0f;
    file->fl |= flags;
    for (i = 0; i < n; i++) {
        sprintf(mat.material_name, "%s_%d", prefix, i);
        rs_strcpy((u8 *)file->name, (u8 *)mat.material_name);
        *out = registerHmtTextureInTable((struct material_entry *)&mat, (struct texture_entry *)&file->px, 0);
        file->px[0] += row;
        out++;
    }
    rs_free((s32)file);
}

void full_header_image_offset_convert(struct texture_entry *texture_entry, u32 file_base_addr) {
    s32 var_a2;

    for (var_a2 = 0; var_a2 < 8; var_a2++) {
        if (texture_entry->pixel_offsets[var_a2] != NULL) {
            texture_entry->pixel_offsets[var_a2] += file_base_addr;
        }
    }
    if (texture_entry->plte_offset != NULL) {
        texture_entry->plte_offset += file_base_addr;
    }
    if (texture_entry->texture_name_offset != NULL) {
        texture_entry->texture_name_offset += file_base_addr;
    }
}

void *load_asset(char *);
s32 registerHmtTextureInTable(struct material_entry *, struct texture_entry *, u32);
void rs_strncpy(char *, char *, s32);
u16 loadAndRelocateAsset(char *path, char *name, u16 flags) {
    struct material_entry mat;
    u8 *asset = load_asset(path);
    struct texture_entry *tex = (struct texture_entry *)(asset + 4);
    u32 base = (u32)tex;
    s32 i;
    u16 ret;

    for (i = 0; i < 8; i++) {
        if (tex->pixel_offsets[i] != 0) {
            tex->pixel_offsets[i] += base;
        }
    }
    if (tex->plte_offset != 0) {
        tex->plte_offset += base;
    }
    if (*(u32 *)((u8 *)tex + 0x24) != 0) {
        *(u32 *)((u8 *)tex + 0x24) += base;
    }
    mat.material_type = 1;
    mat.zero = 0;
    *(u8 *)&mat.alwaysa = 1;
    mat.misc_float = 0.2f;
    mat.one = 1.0f;
    *(u16 *)(asset + 0x32) |= flags;
    if (name != NULL) {
        rs_strncpy(mat.material_name, name, 0x10);
        *(char **)(asset + 0x28) = mat.material_name;
    } else {
        rs_strncpy(mat.material_name, *(char **)(asset + 0x28), 0x10);
    }
    ret = registerHmtTextureInTable(&mat, (struct texture_entry *)(asset + 4), 0);
    rs_free(asset);
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main/55AF0", fake_func_800555E8);
