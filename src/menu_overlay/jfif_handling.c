#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/jfif_handling", D_menu_overlay_800A76E0);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/jfif_handling", D_menu_overlay_800A7730);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", loadJfifAsset);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", resetJfifDecodeState);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", freeJfifDecodeState);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", parseJfifSOIMarker);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", parseJfifSOF0Marker);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", parseJfifDQTMarker);

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

INCLUDE_ASM("asm/nonmatchings/menu_overlay/jfif_handling", allocCellGeometryBuffer);

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

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/jfif_handling", D_menu_overlay_800A78A8);
