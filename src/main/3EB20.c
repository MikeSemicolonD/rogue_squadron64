#include "common.h"
#include "common_types.h"

extern u8 D_800B1EF0[];
extern u8 D_800D03E0[];
extern u8 D_main_bss_8010D200[];

s32 queueDeferredClearRequest(s32, s32);

void clearSceneBssRegion(u8 mode) {
    u8 *start = NULL;
    s32 size = 0;

    if (mode == 2) {
        start = D_800B1EF0;
        size = D_main_bss_8010D200 - start;
    } else if (mode == 1) {
        start = D_800D03E0;
        size = D_main_bss_8010D200 - start;
    }
    queueDeferredClearRequest((s32)start, size);
}

s32 queueDeferredClearRequest(s32, s32);

void clearDeferredClearRequest(void) {
    queueDeferredClearRequest(0, 0);
}

INCLUDE_ASM("asm/nonmatchings/main/3EB20", fake_func_8003DF98);
