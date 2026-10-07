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

typedef struct {
    s32 size;
    void *dev;
    void *ram;
} SdrbReq;
extern void sendServiceMessage(s32, s32, void *, s32);
extern s32 sdrbB8 __asm__("D_main_bss_801126B8");

static __inline__ u8 sdrbDispatch(void) {
    u8 msg[0x18];

    if (D_main_bss_801126B0 != D_main_bss_801126B4) {
        if (sdrbB8 == 0) {
            sendServiceMessage(D_main_bss_801126BC, D_main_bss_801126BC, msg, 0);
        }
        return 1;
    }
    return 0;
}

s32 submitDmaRequestBatch(SdrbReq *reqs, s32 n, OSMesgQueue *mq) {
    s32 d;
    s32 i;
    PiDmaRequest *e;

    if (D_main_bss_801126B0 >= D_main_bss_801126B4) {
        d = D_main_bss_801126B0 - D_main_bss_801126B4;
    } else {
        d = D_main_bss_801126B4 - D_main_bss_801126B0;
    }
    if (d + n + 1 >= 0x100) {
        return 0;
    }
    if (getDmaSlotMutex() == 2) {
        return 0;
    }
    for (i = 0; i < n; reqs++, i++) {
        D_main_801112B0[D_main_bss_801126B4].size = reqs->size;
        D_main_801112B0[D_main_bss_801126B4].devAddr = (u32)reqs->dev;
        D_main_801112B0[D_main_bss_801126B4].vAddr = reqs->ram;
        D_main_801112B0[D_main_bss_801126B4].skip = 0;
        D_main_bss_801126B4 = (D_main_bss_801126B4 + 1) % 256;
    }
    D_main_801112B0[D_main_bss_801126B4].skip = 1;
    D_main_801112B0[D_main_bss_801126B4].mq = mq;
    D_main_bss_801126B4 = (D_main_bss_801126B4 + 1) % 256;
    if (getDmaSlotMutex() == 0) {
        sdrbDispatch();
    }
    return 1;
}

extern OSMesg D_main_80111288[];
extern OSMesgQueue D_main_80111290;
extern s32 D_main_bss_801126B4;
extern s32 D_main_bss_801126BC;
extern s32 registerServiceWorker(s32, s32, s32, void *);
extern s32 startServiceWorker(s32);

s32 initPiDmaWorker(void) {
    osCreateMesgQueue(&D_main_80111290, D_main_80111288, 1);
    D_main_bss_801126B4 = 0;
    D_main_bss_801126B0 = 0;
    D_main_bss_801126B8 = 0;
    D_main_bss_801126BC = registerServiceWorker(4, 0x200, 0x78, piDmaWorker);
    startServiceWorker(D_main_bss_801126BC);
    return 1;
}

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
