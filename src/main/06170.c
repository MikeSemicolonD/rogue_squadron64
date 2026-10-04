#include "common.h"

#include "main/04080.h"
#include "main/06170.h"

INCLUDE_ASM("asm/nonmatchings/main/06170", piDmaWorker);

INCLUDE_ASM("asm/nonmatchings/main/06170", submitDmaRequestBatch);

INCLUDE_ASM("asm/nonmatchings/main/06170", initPiDmaWorker);

extern s32 D_main_bss_801126B0;
extern s32 D_main_bss_801126B4;
extern s32 D_main_bss_801126B8;
extern s32 D_main_bss_801126BC;
extern void sendServiceMessage(s32, s32, void *, s32);

u8 dispatchPendingPiDmaToWorker(s32 arg0) {
    u8 msg[0x18];

    if (D_main_bss_801126B0 != D_main_bss_801126B4) {
        if (D_main_bss_801126B8 == 0) {
            sendServiceMessage(D_main_bss_801126BC, D_main_bss_801126BC, msg, 0);
        }
        return 1;
    }
    return 0;
}

void getAssetRamAddress(s32 arg0) {
    resolveAssetRamAddress(arg0);
}

s32 setDmaSlotMaxTxStepSize(s32 arg0) {
    s32 temp_v0;
    s32 var_a0;

    var_a0 = (arg0 + 0xF) & ~0xF;
    temp_v0 = dmaSlotMaxTxStepSize;
    if (var_a0 == 0) {
        var_a0 = 0x10;
    }
    dmaSlotMaxTxStepSize = var_a0;
    return temp_v0;
}

INCLUDE_ASM("asm/nonmatchings/main/06170", fake_func_8000595C);
