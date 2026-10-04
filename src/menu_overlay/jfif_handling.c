#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/jfif_handling", D_menu_overlay_800A76E0);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/jfif_handling", D_menu_overlay_800A7730);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", loadJfifAsset);

void zmemcpy(void *, void *, u32);
void rs_free(void *);
void cloneCellBufferWithAlloc(u8 *);
void allocCellGeometryBuffer(u8 *);

s32 resetJfifDecodeState(u8 *arg0, void *arg1) {
    s32 temp;
    void *q;

    zmemcpy(arg0, arg1, 0x30);
    if ((*(u16 *)(arg0 + 4) & 1) && (u16)(*(u16 *)(arg0 + 0x10) + 0x100) > 0x200) {
        return 0x12;
    }
    if ((*(u16 *)(arg0 + 4) & 2) && (u16)(*(u16 *)(arg0 + 0x12) + 0x100) > 0x200) {
        return 0x12;
    }
    if ((*(u16 *)(arg0 + 4) & 4) && (u16)(*(u16 *)(arg0 + 0x14) + 0x100) > 0x200) {
        return 0x12;
    }
    temp = *(s32 *)(arg0 + 0xC);
    if (temp != 0 && temp != 4) {
        return 0x12;
    }
    q = *(void **)(arg0 + 0x50);
    if (q != NULL) {
        *(u8 **)(arg0 + 0x50) = (u8 *)q - 0x100;
        rs_free((u8 *)q - 0x100);
    }
    q = *(void **)(arg0 + 0x54);
    if (q != NULL) {
        *(u8 **)(arg0 + 0x54) = (u8 *)q - 0x100;
        rs_free((u8 *)q - 0x100);
    }
    cloneCellBufferWithAlloc(arg0);
    q = *(void **)(arg0 + 0x7D8);
    if (q != NULL) {
        rs_free(q);
    }
    q = *(void **)(arg0 + 0x7DC);
    if (q != NULL) {
        rs_free(q);
    }
    q = *(void **)(arg0 + 0x7E0);
    if (q != NULL) {
        rs_free(q);
    }
    q = *(void **)(arg0 + 0x7E4);
    if (q != NULL) {
        rs_free(q);
    }
    allocCellGeometryBuffer(arg0);
    if (!((u32)(*(s32 *)(arg0 + 8) - 2) < 4)) {
        return 0x16;
    }
    *(u16 *)(arg0 + 0x46) = 0;
    *(u16 *)(arg0 + 0x7EC) = 0;
    *(u16 *)(arg0 + 0x7EE) = 0;
    *(u16 *)(arg0 + 0x7D2) = 0;
    *(u16 *)(arg0 + 0x7E8) = 0;
    *(u16 *)(arg0 + 0x7EA) = 0;
    *(arg0 + 0x4D) = 0;
    *(s32 *)(arg0 + 0x34) = *(s32 *)(arg0 + 0x38);
    return 0;
}

void rs_free(void *);

void freeJfifDecodeState(u8 *arg0) {
    u8 i;
    u8 *p;
    u8 *p2;
    void *q;

    if (arg0 != NULL) {
        i = 0;
        do {
            if ((arg0[0x48] >> i) & 1) {
                p = arg0 + i * 0xA8;
                rs_free(*(void **)(p + 0x5C));
                rs_free(*(void **)(p + 0x60));
            }
            i++;
        } while (i < 4);
        i = 0;
        do {
            p2 = arg0 + i * 0x2C;
            q = *(void **)(p2 + 0x708);
            i++;
            if (q != NULL) {
                rs_free(q);
            }
        } while (i < 3);
        q = *(void **)(arg0 + 0x77C);
        if (q != NULL) {
            rs_free(q);
        }
        q = *(void **)(arg0 + 0x50);
        if (q != NULL) {
            *(void **)(arg0 + 0x50) = (u8 *)q - 0x100;
            rs_free((u8 *)q - 0x100);
        }
        q = *(void **)(arg0 + 0x7D8);
        if (q != NULL) {
            rs_free(q);
        }
        q = *(void **)(arg0 + 0x7DC);
        if (q != NULL) {
            rs_free(q);
        }
        q = *(void **)(arg0 + 0x7E0);
        if (q != NULL) {
            rs_free(q);
        }
        q = *(void **)(arg0 + 0x7E4);
        if (q != NULL) {
            rs_free(q);
        }
        q = *(void **)(arg0 + 0x30);
        if (q != NULL) {
            rs_free(q);
        }
    }
    rs_free(arg0);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", parseJfifSOIMarker);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", parseJfifSOF0Marker);

typedef struct {
    u8 pad0[0x34];
    u8 *cur;
    u8 pad1[0x11];
    u8 mask;
    u8 pad2[0x2AE];
    f32 qt[256];
} JfifDQT;

extern u8 D_menu_overlay_800A76E0[];
extern f64 D_menu_overlay_800A7730[];

s32 parseJfifDQTMarker(JfifDQT *arg0) {
    f32 q[64];
    s32 len;
    u32 id;
    u16 i;
    u16 j;
    u16 k;
    f64 cj;

    {
        u8 *p = arg0->cur;
        s32 hi = p[0] << 8;
        len = (p[1] | hi) - 2;
    }
    arg0->cur += 2;
    do {
        id = *arg0->cur;
        arg0->cur++;
        if (id >= 4) {
            return 9;
        }
        i = 0;
        do {
            q[D_menu_overlay_800A76E0[i]] = *arg0->cur++;
            i++;
        } while (i < 0x40);
        i = 0;
        j = 0;
        arg0->mask |= 1 << (u16)id;
        do {
            k = 0;
            cj = D_menu_overlay_800A7730[j];
            do {
                *(f32 *)((u8 *)arg0 + (i * 4 + ((u16)id << 8)) + 0x2F8) = q[i] * cj * D_menu_overlay_800A7730[k];
                i++;
                k++;
            } while (k < 8);
            j++;
        } while (j < 8);
        len -= 0x41;
    } while ((u16)len != 0);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", parseJfifDHTMarker);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", paserJfifSOSMarker);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", rebuildDebrisCellGeometry);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", emitDebrisCellFaces);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", computeCellGridIndices);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", buildDebrisCellBitfield);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", decodeDeltaCellCounts);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", allocDebrisCellTable);

typedef struct {
    u8 *bits;
    u8 pad4[4];
    s32 *codes;
    u8 padC[4];
    u8 *vals;
    s32 maxcode[18];
    s32 valptr[18];
    u32 count;
} HuffTable;

typedef struct {
    u8 pad0[0x58];
    HuffTable tables[4];
} JfifHuffState;

s32 buildCellSlotTableAndFindFree(JfifHuffState *state, u8 index) {
    s32 code = 0;
    s32 k;
    HuffTable *tbl = &state->tables[index];
    u32 i;

    for (k = 1; k < 17; k++) {
        if (tbl->bits[k - 1] != 0) {
            tbl->valptr[k] = code - tbl->codes[code];
            code += tbl->bits[k - 1];
            tbl->maxcode[k] = tbl->codes[code - 1];
        } else {
            tbl->maxcode[k] = -1;
            tbl->valptr[k] = -1;
        }
    }
    tbl->maxcode[17] = 0xFFFFF;
    if (!(index & 1)) {
        for (i = 0; i <= tbl->count; i++) {
            if (tbl->vals[i] >= 16) {
                return 16;
            }
        }
    }
    return 0;
}

typedef struct {
    u8 pad0[0x34];
    u8 *cur;
    u8 pad38[0xC];
    u16 bitbuf;
    u16 bitcnt;
    u8 pad48[5];
    u8 eof;
} JfifBitReader;

s32 findFreeCellBitSlot(JfifBitReader *arg0, u8 arg1) {
    u8 var_t0 = 0;
    u8 temp_a1 = arg1;
    s32 var_a3;
    s32 temp_a3;
    u16 temp_v0;
    u16 temp_v0_4;
    u16 temp_v1;
    u8 *temp_v0_2;
    u8 var_v1;
    u8 t;

    var_a3 = 0;
    if (temp_a1 != 0) {
        do {
            temp_v0 = arg0->bitcnt;
            temp_a3 = var_a3 * 2;
            if (temp_v0 == 0) {
                arg0->bitcnt = 8;
                if (arg0->eof == 0) {
                    temp_v0_2 = arg0->cur;
                    var_v1 = *temp_v0_2;
                    arg0->cur = temp_v0_2 + 1;
                } else {
                    var_v1 = 0;
                }
                arg0->bitbuf = var_v1;
                if (var_v1 == 0xFF) {
                    t = *arg0->cur++;
                    if (t == 0xD9) {
                        arg0->eof = 1;
                    }
                }
                temp_v0_4 = arg0->bitbuf;
                var_a3 = temp_a3 + ((temp_v0_4 >> 7) & 1);
                arg0->bitcnt = arg0->bitcnt - 1;
                arg0->bitbuf = temp_v0_4 * 2;
            } else {
                arg0->bitcnt = temp_v0 - 1;
                temp_v1 = arg0->bitbuf * 2;
                var_a3 = temp_a3 + ((temp_v1 >> 8) & 1);
                arg0->bitbuf = temp_v1;
            }
            var_t0++;
        } while (var_t0 < temp_a1);
    }
    return var_a3;
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", allocCellBitGroup);

void allocCellGeometryBuffer(u8 *arg0) {
    f32 sp[4];
    f32 *dst;
    u8 *src;
    s32 i;
    s32 j;
    s32 off;

    i = 0;
    if (*(u16 *)(arg0 + 4) & 0x20) {
        dst = sp;
        src = arg0;
        do {
            f32 t = *(f32 *)(src + 0x18);
            src += 4;
            i += 1;
            *dst = t;
            dst += 1;
        } while (i < 4);
    } else {
        sp[0] = 1.402f;
        sp[1] = 1.772f;
        sp[2] = 0.71414f;
        sp[3] = 0.34414f;
    }
    *(void **)(arg0 + 0x7D8) = rs_malloc(0x400, *(u16 *)(arg0 + 0xE));
    *(void **)(arg0 + 0x7DC) = rs_malloc(0x400, *(u16 *)(arg0 + 0xE));
    *(void **)(arg0 + 0x7E0) = rs_malloc(0x400, *(u16 *)(arg0 + 0xE));
    *(void **)(arg0 + 0x7E4) = rs_malloc(0x400, *(u16 *)(arg0 + 0xE));
    i = 0;
    j = -0x80;
    do {
        off = i * 4;
        *(s32 *)(off + *(s32 *)(arg0 + 0x7D8)) = (((s32)(sp[0] * 65536.0f + 0.5f) * j) + 0x8000) >> 16;
        *(s32 *)(off + *(s32 *)(arg0 + 0x7DC)) = (((s32)(sp[1] * 65536.0f + 0.5f) * j) + 0x8000) >> 16;
        *(s32 *)(off + *(s32 *)(arg0 + 0x7E0)) = -(s32)(sp[2] * 65536.0f + 0.5f) * j;
        i += 1;
        *(s32 *)(off + *(s32 *)(arg0 + 0x7E4)) = (-(s32)(sp[3] * 65536.0f + 0.5f) * j) + 0x8000;
        j += 1;
    } while (i < 0x100);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", buildDebrisMeshFromCells);

void *rs_malloc(u32, u16);
void rs_memset(u8 *, u8, u32);
void zmemcpy(void *, void *, u32);

void cloneCellBufferWithAlloc(u8 *state) {
    s32 size = 0x580;
    u8 *buf;
    u8 *tbl;
    s32 i;

    buf = rs_malloc(size, *(u16 *)(state + 0xE));
    rs_memset(buf, 0, size);
    tbl = buf + 0x100;
    *(u8 **)(state + 0x50) = tbl;
    for (i = 0; i < 0x100; i++) {
        (*(u8 **)(state + 0x50))[i] = i;
    }
    tbl += 0x80;
    for (i = 0x80; i < 0x200; i++) {
        tbl[i] = 0xFF;
    }
    zmemcpy(tbl + 0x380, *(u8 **)(state + 0x50), 0x80);
    *(u8 **)(state + 0x54) = rs_malloc(size, *(u16 *)(state + 0xE));
    zmemcpy(*(u8 **)(state + 0x54), buf, size);
    for (i = 0; i < size; i++) {
        (*(u8 **)(state + 0x54))[i] >>= 3;
    }
    *(u8 **)(state + 0x54) += 0x100;
}

typedef struct {
    u8 pad0[0xE];
    u16 heapTag;
    u8 pad10[0x77C - 0x10];
    u8 *cells[16];
} CellRecord;

void *rs_malloc(u32, u16);

void allocZeroedCellRecord(CellRecord *rec) {
    u8 *buf = rs_malloc(0x800, rec->heapTag);
    u8 i;

    for (i = 0; i < 16; i++) {
        rec->cells[i] = buf + i * 0x80;
    }
}

static u32 D_menu_overlay_800A78AC[] __attribute__((section(".rodata"))) = { 0x0C020B28 };
