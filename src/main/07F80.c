#include "common.h"
#include "common_types.h"

extern u8 D_main_bss_80112910[];
extern void (*D_main_bss_801128E0)(void);
extern u8 *D_main_bss_801128E4;
extern u32 D_main_bss_801128E8;
void osCreateMesgQueue(void *, void *, s32);
void osCreateThread(void *, s32, void (*)(void *), void *, void *, s32);
void osStartThread(void *);
s32 osSetTimer(void *, u64, u64, void *, void *);
void *rs_malloc(u32, u16);
void periodicCallbackWorker(void *arg);
void installPeriodicCallback(void (*cb)(void), s32 ms) {
    osCreateMesgQueue(D_main_bss_80112910, D_main_bss_80112910 + 0x18, 2);
    D_main_bss_801128E4 = rs_malloc(0x2000, 0x80);
    osCreateThread(D_main_bss_80112910 + 0x20, 0, periodicCallbackWorker, 0, D_main_bss_801128E4 + 0x400, 20);
    osStartThread(D_main_bss_80112910 + 0x20);
    D_main_bss_801128E0 = cb;
    D_main_bss_801128E8 = ms * 46875;
    osSetTimer(D_main_bss_80112910 - 0x20, 0, D_main_bss_801128E8, D_main_bss_80112910, 0);
}

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
