#include "common.h"

#include "main/04080.h"
#include "main/06170.h"

typedef struct {
    u32 size;
    u32 devAddr;
    void *vAddr;
    OSMesgQueue *mq;
    u8 skip;
    u8 pad11[3];
} PiDmaRequest;

extern PiDmaRequest D_main_801112B0[];
extern OSIoMesg D_main_bss_80111270;
extern OSMesgQueue D_main_80111290;
extern s32 D_main_bss_801126B0;
extern s32 D_main_bss_801126B4;
extern volatile s32 D_main_bss_801126B8;
extern s32 D_main_bss_801126BC;
extern OSMesg recvServiceMessage(OSId);
extern s32 yieldThreadRet1(s32);

void piDmaWorker(void *arg) {
    PiDmaRequest *req;

    while (TRUE) {
        recvServiceMessage(D_main_bss_801126BC);
        D_main_bss_801126B8 = 1;
        while (D_main_bss_801126B0 != D_main_bss_801126B4) {
            req = &D_main_801112B0[D_main_bss_801126B0];
            D_main_bss_801126B0 = (D_main_bss_801126B0 + 1) % 256;
            if (req->skip == 0) {
                osPiStartDma(&D_main_bss_80111270, 1, 0, req->devAddr, req->vAddr, req->size, &D_main_80111290);
                osRecvMesg(&D_main_80111290, NULL, 1);
                yieldThreadRet1(D_main_bss_801126BC);
            } else {
                if (D_main_bss_801126B0 == D_main_bss_801126B4) {
                    D_main_bss_801126B8 = 0;
                }
                osSendMesg(req->mq, (OSMesg)1, 0);
            }
        }
        D_main_bss_801126B8 = 0;
    }
}

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
