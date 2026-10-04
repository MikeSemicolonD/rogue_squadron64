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

INCLUDE_ASM("asm/nonmatchings/main/1EE30", packTlutEntriesRgba5551);

INCLUDE_ASM("asm/nonmatchings/main/1EE30", allocTextureTlutBlock);

INCLUDE_ASM("asm/nonmatchings/main/1EE30", freeTextureTlutBlock);

INCLUDE_ASM("asm/nonmatchings/main/1EE30", freeTextureDataSlot);

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

INCLUDE_ASM("asm/nonmatchings/main/1EE30", loadTextureToMemory);

INCLUDE_ASM("asm/nonmatchings/main/1EE30", loadTextureTile);

INCLUDE_ASM("asm/nonmatchings/main/1EE30", emitMaterialRenderStateDL);

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

INCLUDE_ASM("asm/nonmatchings/main/1EE30", allocOrEvictMaterialNode);

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

INCLUDE_ASM("asm/nonmatchings/main/1EE30", releaseTextureLutEntry);

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

INCLUDE_ASM("asm/nonmatchings/main/1EE30", parseHmtMaterials);

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

INCLUDE_ASM("asm/nonmatchings/main/1EE30", findMatchingTextureRecursive);

INCLUDE_ASM("asm/nonmatchings/main/1EE30", findTextureByName);

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

INCLUDE_ASM("asm/nonmatchings/main/1EE30", loadAndDecodeTexture);

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

INCLUDE_ASM("asm/nonmatchings/main/1EE30", texPackTlutAtAllocSlot);

INCLUDE_ASM("asm/nonmatchings/main/1EE30", texPackTlutSlotOrAlloc);

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
