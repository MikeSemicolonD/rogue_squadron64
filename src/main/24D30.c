#include "common.h"
#include "common_types.h"
#include "PR/os.h"

INCLUDE_ASM("asm/nonmatchings/main/24D30", flushDebugTextOverlay);

typedef struct { s16 x; s16 y; u8 c; u8 pad; } DbgGlyph;
extern DbgGlyph D_main_bss_80128F28[];
extern u8 D_main_bss_80128F20;
extern s16 D_main_bss_8012BF28;
void queueDebugTextGlyph(s32 x, s32 y, s32 c) {
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

INCLUDE_ASM("asm/nonmatchings/main/24D30", drawDebugTextString);

INCLUDE_ASM("asm/nonmatchings/main/24D30", loadDebugAssets);

INCLUDE_ASM("asm/nonmatchings/main/24D30", fake_func_80024878);
