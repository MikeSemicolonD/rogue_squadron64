#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/07F80", installPeriodicCallback);

extern u8 D_main_bss_80112910[];
extern void (*D_main_bss_801128E0)(void);
s32 osRecvMesg(void *, void *, s32);
void osYieldThread(void);
void periodicCallbackWorker(void *arg) {
    u8 *q = D_main_bss_80112910;

    while (1) {
        osRecvMesg(q, 0, 1);
        osYieldThread();
        D_main_bss_801128E0();
    }
}

INCLUDE_ASM("asm/nonmatchings/main/07F80", fake_func_800074D8);
