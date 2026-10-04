#include "common.h"

#include "main/55AF0.h"

INCLUDE_ASM("asm/nonmatchings/main/55AF0", loadAssetAndIterateSubchunks);

INCLUDE_ASM("asm/nonmatchings/main/55AF0", loadSpriteSheetTextureFrames);

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
