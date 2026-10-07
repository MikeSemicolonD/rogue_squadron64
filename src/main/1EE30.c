#include "common.h"
#include "common_types.h"

#include "compiler/gcc/memory.h"

#include "main/01720.h"
#include "main/08510.h"
#include "main/1EE30.h"

u16 D_main_bss_80128EF0;
u16 bass_pad0_1EE30;
struct MaterialPoolEntry   *D_main_bss_80128EF4;
struct MaterialPoolEntry   *D_main_bss_80128EF8;
u16 **D_main_bss_80128EFC;
struct MaterialPoolEntry  **D_main_bss_80128F00;
u16 D_main_bss_80128F04;
u16 bass_pad1_1EE30;
struct D_main_bss_80128F08 *D_main_bss_80128F08;

extern s32 D_main_bss_8011A850;
extern s32 D_main_bss_8011A854;
extern s32 D_main_bss_8011A7D0;
extern s32 D_main_bss_8011A7D8;

void initTextureLUTAndAllocBuffers(u16 arg0, u16 arg1) {
    s32 i;

    D_main_bss_80128F04 = arg1;
    D_main_bss_80128EF0 = arg0;
    D_main_bss_80128F08 = rs_malloc(arg0 * 0x24, 0);
    D_main_bss_80128EFC = rs_malloc(D_main_bss_80128F04 << 2, 0);
    D_main_bss_80128F00 = rs_malloc(D_main_bss_80128EF0 << 2, 0);
    for (i = 0; i < D_main_bss_80128EF0; i++) {
        D_main_bss_80128F08[i].unk00 = 0;
    }
    for (i = 0; i < D_main_bss_80128F04; i++) {
        D_main_bss_80128EFC[i] = 0;
    }
    D_main_bss_8011A7D8 = D_main_bss_8011A850;
    D_main_bss_8011A7D0 = D_main_bss_8011A854;
}

void destroyTextureLUTs(void) {
    rs_free(D_main_bss_80128F08);
    rs_free(D_main_bss_80128EFC);
}

#define RGBA5551(r, g, b) ((((r) << 8) & 0xF800) | (((g) << 3) & 0x7C0) | (((b) >> 2) & 0x3E))

u16 *packTlutEntriesRgba5551(u16 *dst, s32 flags, u8 *src, s16 count, u8 *key) {
    s16 i;
    u8 kr;
    u8 kg;
    u8 kb;

    if (flags & 0x8000) {
        for (i = 0; i < count; i++, dst++, src += 4) {
            if (src[3] != 0) {
                *dst = RGBA5551(src[0], src[1], src[2]) | 1;
            } else {
                *dst = RGBA5551(src[0], src[1], src[2]);
            }
        }
    } else if (flags & 0x4000) {
        kr = key[0];
        kg = key[1];
        kb = key[2];
        for (i = 0; i < count; i++, dst++, src += 3) {
            if (kr != src[0] || kg != src[1] || kb != src[2]) {
                *dst = RGBA5551(src[0], src[1], src[2]) | 1;
            } else {
                *dst = RGBA5551(src[0], src[1], src[2]);
            }
        }
    } else {
        for (i = 0; i < count; i++, dst++, src += 3) {
            *dst = RGBA5551(src[0], src[1], src[2]) | 1;
        }
    }
    return dst;
}

u16 allocTextureTlutBlock(u16 tl, u32 arg0, u16 fl, u32 *key) {
    u16 n;

    switch (fl & 0xF) {
    case 0:
        n = 0x10;
        break;
    case 1:
        n = 0x100;
        break;
    default:
        return 0xFFFF;
    }
    if ((arg0 & 0xFF000000) != 0x80000000) {
        return arg0;
    }
    if (tl == 0xFFFF) {
        for (tl = 0; tl < D_main_bss_80128F04; tl++) {
            if (D_main_bss_80128EFC[tl] == NULL) {
                break;
            }
        }
        if (tl == D_main_bss_80128F04) {
            return 0xFFFF;
        }
        D_main_bss_8011A7D0 -= n * 2;
        D_main_bss_80128EFC[tl] = (u16 *)D_main_bss_8011A7D0;
        packTlutEntriesRgba5551((u16 *)D_main_bss_8011A7D0, fl, (u8 *)arg0, n, (u8 *)key);
    } else {
        packTlutEntriesRgba5551(D_main_bss_80128EFC[tl], fl, (u8 *)arg0, n, (u8 *)key);
    }
    return tl;
}

void ftlbImpl(u16 idx, u8 fmt) __asm__("freeTextureTlutBlock");

void ftlbImpl(u16 idx, u8 fmt) {
    s32 size;
    u16 *blk;
    u32 *src;
    u32 *dst;
    s32 i;
    u16 *p;

    size = 0x100;
    if ((fmt & 0x3F) == 1) {
        size = 0x10;
    }
    blk = D_main_bss_80128EFC[idx];
    src = (u32 *)blk;
    dst = (u32 *)(blk + size);
    while ((s32)src != D_main_bss_8011A7D0) {
        src--;
        dst--;
        *dst = *src;
    }
    D_main_bss_80128EFC[idx] = NULL;
    D_main_bss_8011A7D0 += size * 2;
    i = 0;
    if (D_main_bss_80128F04 != 0) {
        do {
            p = D_main_bss_80128EFC[i & 0xFFFF];
            if (p != NULL) {
                if (p < blk) {
                    D_main_bss_80128EFC[i & 0xFFFF] = (u16 *)((u8 *)p + size * 2);
                }
            }
            i++;
        } while ((u16)i < D_main_bss_80128F04);
    }
}

void freeTextureDataSlot(u16 arg0) {
    u8 *data;
    u8 *end;
    u8 *dst;
    s32 n;
    s32 i;
    u16 tlut;

    unlinkTextureMaterialList(arg0);
    end = D_main_bss_80128F08[arg0].texture_size + D_main_bss_80128F08[arg0].texture_data;
    data = D_main_bss_80128F08[arg0].texture_data;
    n = D_main_bss_8011A7D8 - (s32)end;
    D_main_bss_80128F08[arg0].unk00 = 0;
    if (n != 0) {
        dst = data;
        i = n;
        while (i > 0) {
            *(u32 *)dst = *(u32 *)end;
            end += 4;
            dst += 4;
            i -= 4;
        }
    }
    D_main_bss_8011A7D8 = (s32)(D_main_bss_80128F08[arg0].texture_data + n);
    for (i = 0; i < D_main_bss_80128EF0; i++) {
        if (D_main_bss_80128F08[i].unk00 != 0) {
            u8 *d2 = D_main_bss_80128F08[i].texture_data;
            if (D_main_bss_80128F08[arg0].texture_data < d2) {
                D_main_bss_80128F08[i].texture_data = d2 - D_main_bss_80128F08[arg0].texture_size;
            }
        }
    }
    tlut = D_main_bss_80128F08[arg0].unk0E;
    if (tlut != 0xFFFF) {
        for (i = 0; i < D_main_bss_80128EF0; i++) {
            if (D_main_bss_80128F08[i].unk00 != 0 && D_main_bss_80128F08[i].unk0E == tlut) {
                return;
            }
        }
        freeTextureTlutBlock(tlut, D_main_bss_80128F08[i].unk00);
    }
}

u16 decodeRdpFormatFlags(u16 arg0) {
    u32 ret;
    switch (arg0 & 0x3F) {
        case 1:
            ret = 0;
            break;
        case 2:
            ret = 1;
            break;
        case 3:
            ret = 2;
            break;
        case 4:
            ret = 3;
            break;
        case 5:
            ret = 4;
            break;
        case 6:
            ret = 5;
            break;
    }
    if (arg0 & 0x8000) {
        ret |= 0x8000;
    }
    if (arg0 & 0x4000) {
        ret |= 0x4000;
    }
    if (arg0 & 0x2000) {
        ret |= 0x2000;
    }
    if (arg0 & 0x1000) {
        ret |= 0x1000;
    }
    if (arg0 & 0x800) {
        ret |= 0x800;
    }
    if (arg0 & 0x400) {
        ret |= 0x400;
    }
    if (arg0 & 0x200) {
        ret |= 0x200;
    }
    if (arg0 & 0x100) {
        ret |= 0x100;
    }
    if (arg0 & 0x80) {
        ret |= 0x80;
    }
    if (arg0 & 0x40) {
        ret |= 0x40;
    }
    return ret;
}

u16 decodeRdpSizeFlags(u16 arg0) {
    u32 ret;
    switch (arg0 & 0xF) {
        case 4:
            ret = 5;
            break;
        case 0:
            ret = 1;
            break;
        case 5:
            ret = 6;
            break;
        case 1:
            ret = 2;
            break;
        case 2:
            ret = 3;
            break;
        case 3:
            ret = 4;
            break;
    }
    if (arg0 & 0x8000) {
        ret |= 0x8000;
    }
    if (arg0 & 0x4000) {
        ret |= 0x4000;
    }
    if (arg0 & 0x2000) {
        ret |= 0x2000;
    }
    if (arg0 & 0x1000) {
        ret |= 0x1000;
    }
    if (arg0 & 0x800) {
        ret |= 0x800;
    }
    if (arg0 & 0x400) {
        ret |= 0x400;
    }
    if (arg0 & 0x200) {
        ret |= 0x200;
    }
    if (arg0 & 0x100) {
        ret |= 0x100;
    }
    if (arg0 & 0x80) {
        ret |= 0x80;
    }
    if (arg0 & 0x40) {
        ret |= 0x40;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main/1EE30", parseImageFile);

typedef struct { u8 b[4]; } LtC4;
void *parseImageFile(void *, s32, s32, s32, s32, s32, void *);

static __inline__ u16 lttTlut(u16 tl, u32 arg0, u16 fl, u32 *key) {
    u16 n;
    u16 ret;

    switch (fl & 0xF) {
    case 0:
        n = 0x10;
        break;
    case 1:
        n = 0x100;
        break;
    default:
        ret = 0xFFFF;
        goto done;
    }
    if ((arg0 & 0xFF000000) != 0x80000000) {
        ret = arg0;
        goto done;
    }
    if (tl == 0xFFFF) {
        for (tl = 0; tl < D_main_bss_80128F04; tl++) {
            if (D_main_bss_80128EFC[tl] == NULL) {
                break;
            }
        }
        if (tl == D_main_bss_80128F04) {
            ret = 0xFFFF;
            goto done;
        }
        D_main_bss_8011A7D0 -= n * 2;
        D_main_bss_80128EFC[tl] = (u16 *)D_main_bss_8011A7D0;
        packTlutEntriesRgba5551((u16 *)D_main_bss_8011A7D0, fl, (u8 *)arg0, n, (u8 *)key);
    } else {
        packTlutEntriesRgba5551(D_main_bss_80128EFC[tl], fl, (u8 *)arg0, n, (u8 *)key);
    }
    ret = tl;
done:
    return ret;
}

u16 lttImpl(void *tex, u32 plte, u16 w, u16 h, u16 flags, u8 one, u8 depth, u16 idx, u32 *transp, u8 *name) __asm__("loadTextureToMemory");
u16 lttImpl(void *tex, u32 plte, u16 w, u16 h, u16 flags, u8 one, u8 depth, u16 idx, u32 *transp, u8 *name) {
    s32 i;
    u8 *end;
    u8 *data;
    struct D_main_bss_80128F08 *e;

    if (idx == 0xFFFF) {
        for (i = 0; i < D_main_bss_80128EF0; i++) {
            if (D_main_bss_80128F08[i].unk00 != 0) {
                if (rs_strncmp(D_main_bss_80128F08[i].texture_name, name, 0x10) == 0) {
                    return i;
                }
            }
        }
        for (i = 0; i < D_main_bss_80128EF0; i++) {
            if (D_main_bss_80128F08[i].unk00 == 0) {
                break;
            }
        }
        data = (u8 *)D_main_bss_8011A7D8;
    } else {
        i = idx;
        data = D_main_bss_80128F08[i].texture_data;
    }
    if (i != D_main_bss_80128EF0) {
    rs_strncpy(D_main_bss_80128F08[i].texture_name, name, 0x10);
    D_main_bss_80128F08[i].unk02 = one;
    D_main_bss_80128F08[i].unk00 = decodeRdpSizeFlags(flags);
    D_main_bss_80128F08[i].width = w;
    D_main_bss_80128F08[i].height = h;
    D_main_bss_80128F08[i].texture_data = data;
    D_main_bss_80128F08[i].unk03 = depth;
    if (transp != NULL) {
        *(LtC4 *)&D_main_bss_80128F08[i].unk04 = *(LtC4 *)transp;
    }
    end = parseImageFile(data, flags, w, h, one, (s32)tex, transp);
    if (flags & 0x800) {
        end = parseImageFile(end, 4, (u16)(w >> depth), (u16)(h >> depth), 1, (s32)tex + 4, NULL);
    } else if (flags & 0x400) {
        end = parseImageFile(end, 5, (u16)(w >> depth), (u16)(h >> depth), 1, (s32)tex + 4, NULL);
    }
    data = (u8 *)(((u32)end + 0xF) & ~0xF);
    if (flags & 0x20) {
        switch (flags & 0xF) {
        case 0:
            data += 0x20;
            break;
        case 1:
            data += 0x200;
            break;
        }
    }
    {
        struct D_main_bss_80128F08 *b = D_main_bss_80128F08;
        e = (struct D_main_bss_80128F08 *)(i * sizeof(struct D_main_bss_80128F08) + (s32)b);
    }
    e->texture_size = data - e->texture_data;
    if (idx == 0xFFFF) {
        D_main_bss_8011A7D8 = (s32)data;
        D_main_bss_80128F08[i].unk0E = lttTlut(0xFFFF, plte, flags, transp);
    } else {
        lttTlut(e->unk0E, plte, flags, transp);
    }
    return i;
    }
    return 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/main/1EE30", loadTextureTile);

extern u8 D_main_bss_8011A908;
extern u8 D_main_bss_801143A8;
extern u32 D_main_bss_801163D4;
extern u8 D_main_80038860[];
extern u32 D_main_80037860[][2];
extern Gfx *loadTextureTile(Gfx *, struct D_main_bss_80128F08 *, s32, s32, s32, u16 *, s32 *);

#define EMR_CHECK(d) \
    if ((u32)(d) >= D_main_bss_801163D4) { \
        (d)->words.w0 = 0xB5000000; \
        (d)->words.w1 = 0; \
        (d) = allocateDisplayListBuffer(); \
    }

Gfx *emitMaterialRenderStateDL(Gfx *dl, u16 idx, u32 arg2, u8 *out) {
    struct D_main_bss_80128F08 *e;
    u16 sp20;
    s32 sp24;
    u32 flags;
    Gfx *g;
    Gfx *g2;
    u8 v;

    e = &D_main_bss_80128F08[idx];
    sp20 = 0;
    sp24 = (s32)e->texture_data;
    dl = loadTextureTile(dl, e, 0, 0, 1, &sp20, &sp24);
    if (e->unk00 & 0x1C00) {
        dl = loadTextureTile(dl, e, e->unk03, 1, 0, &sp20, &sp24);
    }
    EMR_CHECK(dl);
    if (e->unk02 >= 2) {
        g = dl++;
        g->words.w0 = 0xBA001001;
        flags = 4;
        g->words.w1 = 0x10000;
    } else {
        g = dl++;
        g->words.w0 = 0xBA001001;
        flags = 0;
        g->words.w1 = 0;
    }
    if (arg2 & 1) {
        flags |= 1;
    }
    if (e->unk00 & 0xA000) {
        flags |= 2;
    }
    if (e->unk00 & 0xC00) {
        flags |= 0x12;
    }
    if (arg2 & 2) {
        flags |= 8;
    }
    if (arg2 & 4) {
        flags |= 0x100;
    }
    EMR_CHECK(dl);
    if (e->unk00 & 0x4000) {
        g = dl++;
        g->words.w0 = 0xB9000002;
        g->words.w1 = 1;
        D_main_bss_801143A8 = 1;
        flags |= 0x40;
    } else {
        g = dl++;
        g->words.w0 = 0xB9000002;
        g->words.w1 = 0;
        D_main_bss_801143A8 = 0;
    }
    v = D_main_80038860[flags & 0x7F];
    *out = v;
    if (D_main_bss_8011A908 & 0x80) {
        flags |= 0x80;
    } else {
        D_main_bss_8011A908 = v;
        if ((v & 0x7F) != 2) {
            if (e->unk00 & 0x1C00) {
                flags |= 0x80;
                D_main_bss_8011A908 = 2;
                *out = 2;
            }
        } else {
            flags |= 0x80;
        }
    }
    EMR_CHECK(dl);
    *dl = ((Gfx *)D_main_80037860)[(u16)flags];
    dl++;
    EMR_CHECK(dl);
    g2 = dl++;
    g2->words.w0 = (((e->unk02 - 1) & 7) << 11) | 0xBB000001;
    g2->words.w1 = 0;
    if ((u32)(dl + 2) >= D_main_bss_801163D4) {
        dl->words.w0 = 0xB5000000;
        dl->words.w1 = 0;
        dl = allocateDisplayListBuffer();
    }
    dl->words.w0 = 0x03820000;
    dl->words.w1 = 0;
    (dl + 1)->words.w0 = ((u32)((e->width - 1) << 9) >> 16 << 16) | ((u32)((e->height - 1) << 9) >> 16);
    (dl + 1)->words.w1 = ((u32)((e->width - 1) << 9) >> 16 << 16) | ((u32)((e->height - 1) << 9) >> 16);
    (dl + 2)->words.w0 = ((e->width - 1) << 25) | (((e->height - 1) << 9) & 0xFFFF);
    (dl + 2)->words.w1 = ((e->width - 1) << 25) | (((e->height - 1) << 9) & 0xFFFF);
    return dl + 3;
}

void resetMaterialPool(void) {
    u32 var_a0;

    for (var_a0 = 0; var_a0 < D_main_bss_80128EF0; var_a0++) {
        D_main_bss_80128F00[var_a0] = NULL;
    }

    D_main_bss_80128EF8 = D_main_bss_80128EF4;
    D_main_bss_80128EF4[0].prev = NULL;
    for (var_a0 = 1; var_a0 < 0x200; var_a0++) {
        D_main_bss_80128EF4[var_a0 - 1].next = &D_main_bss_80128EF4[var_a0];
        D_main_bss_80128EF4[var_a0].prev = &D_main_bss_80128EF4[var_a0 - 1];
    }
    D_main_bss_80128EF4[var_a0 - 1].next = NULL;
}

u8 buildMaterialFreeList(void) {
    u32 var_a0;

    for (var_a0 = 0; var_a0 < D_main_bss_80128EF0; var_a0++) {
        D_main_bss_80128F00[var_a0] = NULL;
    }

    D_main_bss_80128EF8 = D_main_bss_80128EF4;
    D_main_bss_80128EF4[0].prev = NULL;
    for (var_a0 = 1; var_a0 < 0x200; var_a0++) {
        D_main_bss_80128EF4[var_a0 - 1].next = &D_main_bss_80128EF4[var_a0];
        D_main_bss_80128EF4[var_a0].prev = &D_main_bss_80128EF4[var_a0 - 1];
    }
    D_main_bss_80128EF4[var_a0 - 1].next = NULL;
    return 1;
}

s32 createMaterialPool(void) {
    D_main_bss_80128EF4 = rs_malloc(sizeof(struct MaterialPoolEntry) * 0x200, 0x80U);
    if (D_main_bss_80128EF4 != NULL) {
        return buildMaterialFreeList();
    } else {
        return 0;
    }
}

s32 unlinkTextureMaterialList(u16 arg0) {
    struct MaterialPoolEntry *temp_s1;
    struct MaterialPoolEntry *var_s0;

    var_s0 = D_main_bss_80128F00[arg0];
    while (var_s0 != NULL) {
        temp_s1 = var_s0->next;
        heapFreeListInsert(var_s0->unk14);
        if (var_s0->prev != NULL) {
            var_s0->prev->next = var_s0->next;
        } else {
            D_main_bss_80128F00[arg0] = var_s0->next;
        }
        if (var_s0->next != NULL) {
            var_s0->next->prev = var_s0->prev;
        }
        var_s0->next = D_main_bss_80128EF8;
        if (D_main_bss_80128EF8 != NULL) {
            D_main_bss_80128EF8->prev = var_s0;
        }
        var_s0->prev = NULL;
        D_main_bss_80128EF8 = var_s0;
        var_s0 = temp_s1;
    }
    return 1;
}

void tickTextureMaterialExpiry(void) {
    u32 var_s2;
    struct MaterialPoolEntry *temp_s3;
    struct MaterialPoolEntry *var_s0;

    for(var_s2 = 0; var_s2 < D_main_bss_80128EF0; var_s2++) {
        var_s0 = D_main_bss_80128F00[var_s2];
        while (var_s0 != NULL) {
            temp_s3 = var_s0->next;
            if (var_s0->unk08 < 0x708U) {
                var_s0->unk08++;
            } else {
                heapFreeListInsert(var_s0->unk14);
                if (var_s0->prev != NULL) {
                    var_s0->prev->next = var_s0->next;
                } else {
                    D_main_bss_80128F00[var_s2] = var_s0->next;
                }
                if (var_s0->next != NULL) {
                    var_s0->next->prev = var_s0->prev;
                }
                var_s0->next = D_main_bss_80128EF8;
                if (D_main_bss_80128EF8 != NULL) {
                    D_main_bss_80128EF8->prev = var_s0;
                }
                var_s0->prev = NULL;
                D_main_bss_80128EF8 = var_s0;
            }
            var_s0 = temp_s3;
        }
    }
}

extern void *D_main_bss_801163C8[];
extern void **D_main_bss_801163FC;
extern u8 D_main_bss_8011A899;
extern u8 D_main_bss_8011A908;

struct MaterialPoolEntry *resetMaterialExpiryById(u16 id, u32 kind) {
    struct MaterialPoolEntry *entry;
    s32 flag;
    u8 c;

    if (D_main_bss_801163FC == &D_main_bss_801163C8[D_main_bss_8011A899]) {
        entry = D_main_bss_80128F00[id];
        if (entry != NULL) {
            flag = D_main_bss_8011A908 & 0x80;
            do {
                if (entry->unk10 == (kind & 7)) {
                    c = entry->unk0C;
                    if ((c & 0x7F) == 2) {
                        if (flag != 0) {
                            goto hit;
                        }
                    }
                    if (c == entry->unk0E) {
                        if (flag == 0) {
                        hit:
                            entry->unk08 = 0;
                            return entry;
                        }
                    }
                }
                entry = entry->next;
            } while (entry != NULL);
        }
    }
    return NULL;
}

struct DisplayListBuffer *findAndUnlinkSmallestEntry(void) {
    u32 var_a3;
    struct MaterialPoolEntry *var_a1;
    struct MaterialPoolEntry *var_v1;

    var_a1 = NULL;
    for (var_a3 = 0; var_a3 < D_main_bss_80128EF0; var_a3++) {
        var_v1 = D_main_bss_80128F00[var_a3];
        while (var_v1 != NULL) {
            if ((var_v1->unk08 != 0) && ((var_a1 == NULL) || (var_v1->unk08 >= var_a1->unk08))) {
                var_a1 = var_v1;
            }
            var_v1 = var_v1->next;
        }
    }
    if (var_a1 != NULL) {
        if (var_a1->prev != NULL) {
            var_a1->prev->next = var_a1->next;
        } else {
            D_main_bss_80128F00[var_a1->unk0A] = var_a1->next;
        }
        if (var_a1->next != NULL) {
            var_a1->next->prev = var_a1->prev;
        }
        var_a1->prev = NULL;
        var_a1->next = D_main_bss_80128EF8;
        if (D_main_bss_80128EF8 != NULL) {
            D_main_bss_80128EF8->prev = var_a1;
        }
        D_main_bss_80128EF8 = var_a1;
        return var_a1->unk14;
    } else {
        return NULL;
    }
}

struct MaterialPoolEntry *popMaterialNodeIntoBucket(u16 arg0) {
    struct MaterialPoolEntry *temp_a1;

    temp_a1 = D_main_bss_80128EF8;
    if (D_main_bss_80128EF8 != NULL) {
        D_main_bss_80128EF8 = D_main_bss_80128EF8->next;
        if (D_main_bss_80128EF8 != NULL) {
            D_main_bss_80128EF8->prev = NULL;
        }
        temp_a1->next = D_main_bss_80128F00[arg0];
        if (temp_a1->next != NULL) {
            temp_a1->next->prev = temp_a1;
        }
        D_main_bss_80128F00[arg0] = temp_a1;
    }
    return temp_a1;
}

extern void *D_main_bss_8011A7DC;
extern u32 D_main_bss_8011A7E0[];

static __inline__ struct MaterialPoolEntry *aoPop(u16 arg0) {
    struct MaterialPoolEntry *temp_a1;

    temp_a1 = D_main_bss_80128EF8;
    if (D_main_bss_80128EF8 != NULL) {
        D_main_bss_80128EF8 = D_main_bss_80128EF8->next;
        if (D_main_bss_80128EF8 != NULL) {
            D_main_bss_80128EF8->prev = NULL;
        }
        temp_a1->next = D_main_bss_80128F00[arg0];
        if (temp_a1->next != NULL) {
            temp_a1->next->prev = temp_a1;
        }
        D_main_bss_80128F00[arg0] = temp_a1;
    }
    return temp_a1;
}

s32 aoImpl(u32 arg0, u16 arg1, s32 arg2) __asm__("allocOrEvictMaterialNode");
s32 aoImpl(u32 arg0, u16 arg1, s32 arg2) {
    u32 sp10;
    u8 sp14;
    struct MaterialPoolEntry *n;
    struct DisplayListBuffer *f;
    u32 end;
    Gfx *buf;
    Gfx *d;
    u32 *dl;

    if (D_main_bss_801163FC == &D_main_bss_801163C8[D_main_bss_8011A899]) {
        n = aoPop(arg1);
        if (n == NULL) {
            f = findAndUnlinkSmallestEntry();
            if (f != NULL) {
                heapFreeListInsert(f);
                n = aoPop(arg1);
            }
        }
        if (n != NULL) {
            end = D_main_bss_801163D4;
            D_main_bss_801163FC = (void **)&n->unk14;
            n->unk14 = NULL;
            D_main_bss_8011A7DC = &sp10;
            buf = allocateDisplayListBuffer();
            d = emitMaterialRenderStateDL(buf, arg1, arg2, &n->unk0E);
            if ((u32)d >= D_main_bss_801163D4) {
                d->words.w0 = 0xB5000000;
                d->words.w1 = 0;
                d = allocateDisplayListBuffer();
            }
            ((u32 *)d)[0] = 0xB8000000;
            *(int *)((u32 *)d + 1) = 0;
            D_main_bss_801163D4 = end;
            D_main_bss_801163FC = &D_main_bss_801163C8[D_main_bss_8011A899];
            D_main_bss_8011A7DC = &D_main_bss_8011A7E0[D_main_bss_8011A899];
            n->unk0C = D_main_bss_8011A908;
            n->unk0D = D_main_bss_801143A8;
            n->unk08 = 0;
            n->unk0A = arg1;
            n->unk10 = arg2 & 7;
            if (arg0 >= D_main_bss_801163D4) {
                ((u32 *)arg0)[0] = 0xB5000000;
                ((u32 *)arg0)[1] = 0;
                arg0 = (u32)allocateDisplayListBuffer();
            }
            dl = (u32 *)arg0;
            arg0 += 8;
            dl[0] = 0x06000000;
            dl[1] = (u32)buf - 8;
            return arg0;
        }
    }
    return (s32)emitMaterialRenderStateDL((Gfx *)arg0, arg1, arg2, &sp14);
}

extern u8 D_main_bss_801143A8;
extern u32 D_main_bss_801163D4;
s32 allocOrEvictMaterialNode(u32, s32, s32);

s32 findOrCreateMaterial(u32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct MaterialPoolEntry *entry;
    struct MaterialPoolEntry *hit;
    s32 flag;
    u8 c;
    u32 *dl;

    if (D_main_bss_801163FC == &D_main_bss_801163C8[D_main_bss_8011A899]) {
        entry = D_main_bss_80128F00[arg1 & 0xFFFF];
        hit = NULL;
        if (entry != NULL) {
            flag = D_main_bss_8011A908 & 0x80;
            do {
                if (entry->unk10 == (arg2 & 7)) {
                    c = entry->unk0C;
                    if ((c & 0x7F) == 2) {
                        if (flag != 0) {
                            goto found;
                        }
                    }
                    if (c == entry->unk0E) {
                        if (flag == 0) {
found:
                            entry->unk08 = 0;
                            hit = entry;
                            goto done;
                        }
                    }
                }
                entry = entry->next;
                if (entry == NULL) {
                    goto none;
                }
            } while (1);
        }
    } else {
none:
        hit = NULL;
    }
done:
    if (hit == NULL) {
        arg0 = allocOrEvictMaterialNode(arg0, arg1 & 0xFFFF, arg2);
    } else {
        dl = (u32 *)arg0;
        if (arg0 >= D_main_bss_801163D4) {
            dl[0] = 0xB5000000;
            dl[1] = 0;
            arg0 = (u32)allocateDisplayListBuffer();
            dl = (u32 *)arg0;
        }
        dl[0] = 0x06000000;
        dl[1] = (u32)hit->unk14 - 8;
        D_main_bss_8011A908 = hit->unk0C;
        arg0 += 8;
        D_main_bss_801143A8 = hit->unk0D;
    }
    return arg0;
}

u16 getTextureLUTFieldAt8(u16 arg0) {
    return D_main_bss_80128F08[arg0].width;
}

u16 getTextureLUTFieldAtA(u16 arg0) {
    return D_main_bss_80128F08[arg0].height;
}

extern u16 D_main_bss_8011A8B4;

s32 releaseTextureLutEntry(u16 arg0) {
    struct D_main_bss_8011A444 *e;
    u16 tex;
    u16 t;
    s32 i;

    if (arg0 != 0) {
        e = (struct D_main_bss_8011A444 *)(arg0 * 4 + (s32)D_main_bss_8011A444);
        t = e->material_type;
        if (t != 0) {
            e->material_type = 0;
            if (t & 1) {
                tex = e->D_80128F08_index;
                i = 0;
                if (D_main_bss_8011A8B4 != 0) {
                    do {
                        struct D_main_bss_8011A444 *e2 = (struct D_main_bss_8011A444 *)((i & 0xFFFF) * 4 + (s32)D_main_bss_8011A444);
                        if (e2->material_type != 0 && e2->D_80128F08_index == tex) {
                            return 1;
                        }
                        i++;
                    } while ((u16)i < D_main_bss_8011A8B4);
                }
                freeTextureDataSlot(tex);
                return 1;
            }
            __asm__("");
            return 1;
        }
    }
    return 0;
}

extern s32 D_main_bss_8011A850;
extern s32 D_main_bss_8011A854;
extern s32 D_main_bss_8011A7D0;
extern s32 D_main_bss_8011A7D8;
extern u16 D_main_bss_8011A8B4;

s32 initTextureMaterialPools(void) {
    s32 i;
    u16 a;
    u16 b;
    struct D_main_bss_8011A444 *p;
    u16 *pc;

    a = D_main_bss_80128EF0;
    b = D_main_bss_80128F04;
    D_main_bss_80128EF0 = a;
    D_main_bss_80128F04 = b;
    D_main_bss_80128F08 = rs_malloc(a * 0x24, 0);
    D_main_bss_80128EFC = rs_malloc(D_main_bss_80128F04 << 2, 0);
    D_main_bss_80128F00 = rs_malloc(D_main_bss_80128EF0 << 2, 0);
    for (i = 0; i < D_main_bss_80128EF0; i++) {
        D_main_bss_80128F08[i].unk00 = 0;
    }
    for (i = 0; i < D_main_bss_80128F04; i++) {
        D_main_bss_80128EFC[i] = 0;
    }
    D_main_bss_8011A7D8 = D_main_bss_8011A850;
    D_main_bss_8011A7D0 = D_main_bss_8011A854;
    buildMaterialFreeList();
    pc = &D_main_bss_8011A8B4;
    i = 1;
    if (i < *pc) {
        p = D_main_bss_8011A444 + 1;
        do {
            *(u16 *)p = 0;
            i++;
            p++;
        } while (i < *pc);
    }
    return 1;
}

s32 getTextureDimsBySlot(u16 arg0, u16 *arg1, u16 *arg2) {
    u32 temp_a0_2;

    if (D_main_bss_8011A444[arg0].material_type & 1) {
        temp_a0_2 = D_main_bss_8011A444[arg0].D_80128F08_index;
        *arg1 = D_main_bss_80128F08[temp_a0_2].width;
        *arg2 = D_main_bss_80128F08[temp_a0_2].height;
        return 1;
    } else {
        return 0;
    }
}

/* remaining: arg4 (stack u8) is loaded into a1 at function entry and 0xFFFF const hoisted into t0 in target; sb zero,0x10 ordering */
typedef struct { u32 a; u32 b; u32 c; u32 d; } HmtCopy16;
extern u16 D_main_bss_8011A8B4;
extern f32 D_main_800009F0;
extern u8 *D_main_bss_801163B4;
extern u8 *D_main_bss_801143AC;
extern u16 loadTextureToMemory(struct texture_entry *, u32, u16, u16, u16, u8, u8, s32, u32 *, u32);
extern u8 *rs_strncpy(u8 *, u8 *, s32);

u16 parseHmtMaterials(s32 arg0, struct material_entry *arg1, struct texture_entry *arg2, u8 arg3, s32 arg4) {
    u16 tm;
    u8 *dst;
    u8 flag = arg4;

    if ((arg0 != D_main_bss_8011A8B4) & (arg0 != 0xFFFF)) {
        if (arg3) {
            arg1->zero = 0;
            arg1->misc_float = D_main_800009F0;
            arg1->one = D_main_800009F0;
            *((u8 *)arg1 + 0x10) = 0;
            arg1->material_type = 2;
        }
        if (arg2 != NULL) {
            tm = loadTextureToMemory(arg2, arg2->plte_offset, arg2->width, arg2->height, arg2->flags_type, arg2->one, arg2->bit_depth, flag ? D_main_bss_8011A444[arg0].D_80128F08_index : 0xFFFF, &arg2->transparency_color, arg2->texture_name_offset);
            if (tm == 0xFFFF) {
                return 0xFFFF;
            }
            arg1->texture_index = tm;
            arg1->material_type |= 1;
        }
        if (D_main_bss_801163B4 != NULL) {
            dst = (u8 *)(arg0 * 16) + (s32)D_main_bss_801163B4;
            *(HmtCopy16 *)dst = *(HmtCopy16 *)((u8 *)arg1 + 4);
        }
        if (D_main_bss_801143AC != NULL) {
            rs_strncpy(D_main_bss_801143AC + arg0 * 16, (u8 *)arg1->material_name, 0x10);
        }
        D_main_bss_8011A444[arg0].material_type = arg1->material_type;
        D_main_bss_8011A444[arg0].D_80128F08_index = arg1->texture_index;
        return arg0;
    }
    return 0xFFFF;
}

extern u16 D_main_bss_8011A8B4;

u16 parseHmtMaterials(s32, struct material_entry *, struct texture_entry *, u8, s32);

s32 registerHmtTextureInTable(struct material_entry *materials, struct texture_entry *textures, u8 flag) {
    s32 i;
    struct D_main_bss_8011A444 *entry;

    for (i = 0; i < D_main_bss_8011A8B4; i++) {
        entry = &D_main_bss_8011A444[i];
        if (entry->material_type == 0) {
            break;
        }
    }
    return parseHmtMaterials(i, materials, textures, flag, 0);
}

typedef struct { s16 w; s16 h; } TexDimsTmp;
extern s32 releaseTextureLutEntry(u16);

s32 findMatchingTextureRecursive(u16 arg0, struct material_entry *arg1, struct texture_entry *arg2, u8 arg3) {
    struct D_main_bss_8011A444 *e;
    struct D_main_bss_80128F08 *ent;
    TexDimsTmp dims;
    s16 w, h;
    s32 flags;

    e = (struct D_main_bss_8011A444 *)(arg0 * 4 + (s32)D_main_bss_8011A444);
    if (e->material_type != 0) {
        if (e->material_type & 1) {
            if (arg2 != NULL) {
                ent = (struct D_main_bss_80128F08 *)(e->D_80128F08_index * 0x24 + (s32)D_main_bss_80128F08);
                w = ent->width;
                h = ent->height;
                dims.w = w;
                dims.h = h;
                if (dims.w == (s16)arg2->width && dims.h == (s16)arg2->height) {
                    flags = arg2->flags_type;
                    if (flags == (decodeRdpFormatFlags(D_main_bss_80128F08[e->D_80128F08_index].unk00) & 0xFFFF)) {
                        return parseHmtMaterials(arg0, arg1, arg2, arg3, 1) & 0xFFFF;
                    }
                }
            }
        } else {
            if (arg2 == NULL) {
                return parseHmtMaterials(arg0, arg1, NULL, arg3, 0) & 0xFFFF;
            }
        }
        if (releaseTextureLutEntry(arg0) & 0xFF) {
            return parseHmtMaterials(arg0, arg1, arg2, arg3, 0) & 0xFFFF;
        }
    }
    return 0xFFFF;
}

extern u8 *D_main_bss_801143AC;

s32 findTextureByName(u8 *name) {
    s32 i;
    s32 idx;
    u16 type;
    register struct D_main_bss_8011A444 *e asm("$3");
    s32 base;

    i = 0;
    if (D_main_bss_8011A8B4 != 0) {
        do {
            idx = i & 0xFFFF;
            { register s32 o asm("$2") = idx * 4; e = (struct D_main_bss_8011A444 *)(o + (s32)D_main_bss_8011A444); }
            type = e->material_type;
            if (type != 0) {
                if (D_main_bss_801143AC != 0) {
                    if (type & 2) {
                        if (rs_strncmp(D_main_bss_801143AC + idx * 16, name, 16) == 0) {
                            return idx;
                        }
                        goto next;
                    }
                } else if (!(type & 1)) {
                    goto next;
                }
                if (rs_strncmp(D_main_bss_80128F08[e->D_80128F08_index].texture_name, name, 16) == 0) {
                    return idx;
                }
            }
next:
            i++;
        } while ((u16)i < D_main_bss_8011A8B4);
    }
    return 0xFFFF;
}

typedef struct {
    u8 b[4];
} Bytes4;

typedef struct {
    u16 id;
    u8 unk2;
    u8 pad3;
    u16 format;
    Bytes4 unk6;
    u8 padA[2];
    s32 size;
    u8 *data;
} TextureDescriptor;

void *rs_malloc(u32, u16);
void *memcpy(void *, const void *, u32);

s32 copyTextureDescriptorWithData(u16 id, TextureDescriptor *desc, void **buf) {
    u16 index;

    if (D_main_bss_8011A444[id].material_type & 1) {
        index = D_main_bss_8011A444[id].D_80128F08_index;
        desc->id = id;
        desc->size = D_main_bss_80128F08[index].texture_size;
        desc->data = D_main_bss_80128F08[index].texture_data;
        desc->unk6 = *(Bytes4 *)&D_main_bss_80128F08[index].unk04;
        desc->format = decodeRdpFormatFlags(*(u16 *)&D_main_bss_80128F08[index].unk00);
        if (*buf == NULL) {
            *buf = rs_malloc(desc->size, 0);
            if (*buf == NULL) {
                return 0;
            }
            desc->unk2 = 1;
        } else {
            desc->unk2 = 0;
        }
        memcpy(buf, desc->data, desc->size);
        return 1;
    }
    return 0;
}

s32 fillTextureDescriptorNoCopy(u16 id, TextureDescriptor *desc) {
    u16 index;

    if (D_main_bss_8011A444[id].material_type & 1) {
        index = D_main_bss_8011A444[id].D_80128F08_index;
        desc->id = id;
        desc->size = D_main_bss_80128F08[index].texture_size;
        desc->data = D_main_bss_80128F08[index].texture_data;
        desc->unk6 = *(Bytes4 *)&D_main_bss_80128F08[index].unk04;
        desc->format = decodeRdpFormatFlags(*(u16 *)&D_main_bss_80128F08[index].unk00);
        desc->unk2 = 0;
        return 1;
    }
    return 0;
}

typedef struct {
    u16 matIdx;
    u8 allocated;
    u8 pad3;
    u16 flags;
    u8 name[6];
    s32 size;
} TexLoadDesc;

extern s32 D_main_bss_8011A7D0;
void *parseImageFile(void *, s32, s32, s32, s32, s32, void *);
u16 *packTlutEntriesRgba5551(u16 *, s32, u8 *, s16, u8 *);

s32 loadAndDecodeTexture(TexLoadDesc *d, void **out, s32 arg2, u32 tlutSrc) {
    register u16 i asm("$4");
    s16 t;
    u16 flags;
    u8 shift;
    u16 w;
    u16 h;
    void *img;
    u16 tl;
    u16 n;
    u16 fl;
    u8 *nm;

    if (*out == NULL) {
        *out = rs_malloc(d->size, 0);
        if (*out == NULL) {
            return 0;
        }
        d->allocated = 1;
    } else {
        d->allocated = 0;
    }
    img = *out;
    flags = d->flags;
    t = D_main_bss_8011A444[d->matIdx].D_80128F08_index;
    shift = D_main_bss_80128F08[t].unk03;
    w = D_main_bss_80128F08[t].width;
    h = D_main_bss_80128F08[t].height;
    img = parseImageFile(img, flags, w, h, D_main_bss_80128F08[t].unk02, arg2, d->name);
    if (flags & 0x800) {
        parseImageFile(img, 4, (u16)(w >> shift), (u16)(h >> shift), 1, arg2 + 4, NULL);
    } else if (flags & 0x400) {
        parseImageFile(img, 5, (u16)(w >> shift), (u16)(h >> shift), 1, arg2 + 4, NULL);
    }
    tl = D_main_bss_80128F08[t].unk0E;
    fl = d->flags;
    nm = d->name;
    switch (fl & 0xF) {
    case 0:
        n = 0x10;
        break;
    case 1:
        n = 0x100;
        break;
    default:
        return;
    }
    if ((tlutSrc & 0xFF000000) != 0x80000000) {
        return 1;
    }
    if (tl == 0xFFFF) {
        for (i = 0; i < D_main_bss_80128F04; i++) {
            if (D_main_bss_80128EFC[i] == NULL) {
                break;
            }
        }
        if (i != D_main_bss_80128F04) {
            D_main_bss_8011A7D0 -= n * 2;
            D_main_bss_80128EFC[i] = (u16 *)D_main_bss_8011A7D0;
            packTlutEntriesRgba5551((u16 *)D_main_bss_8011A7D0, fl, (u8 *)tlutSrc, n, nm);
        }
    } else {
        packTlutEntriesRgba5551(D_main_bss_80128EFC[tl], fl, (u8 *)tlutSrc, n, nm);
    }
    return 1;
}

s32 rs_free(void *);

s32 uploadTextureDescriptorData(void *arg0, void *arg1) {
    s32 var_v0;

    if (D_main_bss_8011A444[(*(u16 *)((u8 *)(arg0) + 0))].material_type & 1) {
        memcpy((*(void **)((u8 *)(arg0) + 0x10)), arg1, (*(u32 *)((u8 *)(arg0) + 0xC)));
        var_v0 = 1;
        if ((*(u8 *)((u8 *)(arg0) + 2)) & 1) {
            rs_free(arg1);
            return 1;
        }
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_v0;
    }
    var_v0 = 0;
    return var_v0;
}

u8 *getTextureDataByMaterialId(u16 arg0) {
    return D_main_bss_80128F08[D_main_bss_8011A444[arg0].D_80128F08_index].texture_data;
}

s32 returnOne_80023334(void) {
    return 1;
}

u16 *getTextureTlutEntry(u16 arg0) {
    return D_main_bss_80128EFC[arg0];
}

s32 returnOne_8002335C(void) {
    return 1;
}

u16 getTextureAttrBySlot(u16 arg0) {
    if (D_main_bss_8011A444[arg0].material_type & 1) {
        return D_main_bss_80128F08[D_main_bss_8011A444[arg0].D_80128F08_index].unk0E;
    } else {
        return 0xFFFF;
    }
}

u16 texPackTlutAtAllocSlot(u32 arg0, u8 arg1, u8 arg2, u8 *key) {
    u16 fl;
    u16 n;
    register u16 ret asm("$2");
    u16 tl;

    fl = arg1 != 0x10;
    if (key != 0) {
        fl |= 0x4000;
    }
    if (arg2 != 0) {
        fl |= 0x8000;
    }
    tl = 0xFFFF;
    switch (fl & 0xF) {
    case 0:
        n = 0x10;
        break;
    case 1:
        n = 0x100;
        break;
    default:
        ret = 0xFFFF;
        goto done;
    }
    if ((arg0 & 0xFF000000) != 0x80000000) {
        ret = arg0;
        goto done;
    }
    if (tl == 0xFFFF) {
        for (tl = 0; tl < D_main_bss_80128F04; tl++) {
            if (D_main_bss_80128EFC[tl] == NULL) {
                break;
            }
        }
        if (tl == D_main_bss_80128F04) {
            ret = 0xFFFF;
            goto done;
        }
        D_main_bss_8011A7D0 -= n * 2;
        D_main_bss_80128EFC[tl] = (u16 *)D_main_bss_8011A7D0;
        packTlutEntriesRgba5551((u16 *)D_main_bss_8011A7D0, fl, (u8 *)arg0, n, key);
    } else {
        packTlutEntriesRgba5551(D_main_bss_80128EFC[tl], fl, (u8 *)arg0, n, key);
    }
    ret = tl;
done:
    return ret;
}

u16 texPackTlutSlotOrAlloc(u16 slot, u8 *src, u8 sz, u8 fb, u8 *e) {
    u16 flags;
    s32 t;
    u16 cnt;
    u16 ret;
    u16 i;
    u16 *dst;

    t = sz != 0x10;
    flags = t;
    if (e != 0) {
        flags = t | 0x4000;
    }
    if (fb != 0) {
        flags |= 0x8000;
    }
    i = slot;
    switch (flags & 0xF) {
    case 0:
        cnt = 0x10;
        break;
    case 1:
        cnt = 0x100;
        break;
    default:
        ret = 0xFFFF;
        goto out;
    }
    ret = (u32)src;
    if (((u32)src & 0xFF000000) == 0x80000000) {
        if (i == 0xFFFF) {
            for (i = 0; i < D_main_bss_80128F04; i++) {
                if (D_main_bss_80128EFC[i] == 0) {
                    break;
                }
            }
            if (i == D_main_bss_80128F04) {
                ret = 0xFFFF;
                goto out;
            }
            dst = (u16 *)(D_main_bss_8011A7D0 - cnt * 2);
            D_main_bss_8011A7D0 = (s32)dst;
            D_main_bss_80128EFC[i] = dst;
            packTlutEntriesRgba5551(dst, flags, src, cnt, e);
        } else {
            packTlutEntriesRgba5551(D_main_bss_80128EFC[i], flags, src, cnt, e);
        }
        ret = i;
    }
out:
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main/1EE30", texPackTlutAtIndex);

s32 unpackTlutToRgbaBytes(u16 arg0, u8 *arg1, u8 arg2, u8 arg3, u8 arg4) {
    s32 var_a2;
    u16 *temp_v0;
    u32 temp_a0;
    u8 temp_v0_2;
    u8 *why;
    u16 huh, wtf;

    temp_v0 = &D_main_bss_80128EFC[arg0][arg2];
    if (arg4 != 0) {
        for (var_a2 =0; var_a2 < arg3; var_a2++) {
            temp_a0 = temp_v0[var_a2];
            temp_v0_2 = temp_a0 >> 0xB;
            *arg1++ = (temp_v0_2 << 3) | (temp_v0_2 >> 2);

            temp_v0_2 = (temp_a0 >> 6) & 0x1F;
            *arg1++ = (temp_v0_2 << 3) | (temp_v0_2 >> 2);

            temp_a0 >>= 1;
            temp_a0 &= 0x1F;
            temp_v0_2 = temp_a0 << 3;
            temp_a0 >>= 2;
            *arg1++ = temp_v0_2 | temp_a0;

            why = arg1++;
            huh = temp_v0[var_a2];
            wtf = huh;
            wtf &= 1;
            *why = -wtf;
        }
    } else {
        for (var_a2 =0; var_a2 < arg3; var_a2++) {
            temp_a0 = temp_v0[var_a2];
            temp_v0_2 = temp_a0 >> 0xB;
            *arg1++ = (temp_v0_2 << 3) | (temp_v0_2 >> 2);

            temp_v0_2 = (temp_a0 >> 6) & 0x1F;
            *arg1++ = (temp_v0_2 << 3) | (temp_v0_2 >> 2);

            temp_a0 >>= 1;
            temp_a0 &= 0x1F;
            temp_v0_2 = temp_a0 << 3;
            temp_a0 >>= 2;
            *arg1++ = temp_v0_2 | temp_a0;
        }
    }
    return 1;
}

s32 shiftTlutEntryWithinChunk(u16 arg0, u8 arg1, u8 arg2, s8 arg3) {
    u16 blah;
    u16 var_a3;
    u16 *temp_a0;

    temp_a0 = D_main_bss_80128EFC[arg0];
    if (arg3 < 0) {
        blah = temp_a0[arg1];
        for (var_a3 = arg1 + 1; var_a3 < arg1 + arg2; var_a3++) {
            temp_a0[var_a3 - 1] = temp_a0[var_a3];
        }
        temp_a0[var_a3 - 1] = blah;
    } else {
        // ???
        blah = temp_a0[var_a3 = (arg1 + arg2) - 1];
        for (; var_a3 > arg1; var_a3--) {
            temp_a0[var_a3] = temp_a0[var_a3 - 1];
        }
        temp_a0[var_a3] = blah;
    }
    return 1;
}

extern s32 D_main_bss_8011A7D0;
extern s32 D_main_bss_8011A7D8;

s32 getLoadedTextureCount(void) {
    return D_main_bss_8011A7D0 - D_main_bss_8011A7D8;
}

INCLUDE_ASM("asm/nonmatchings/main/1EE30", fake_func_80023968);

INCLUDE_RODATA("asm/nonmatchings/main/1EE30", D_main_800009F0);
