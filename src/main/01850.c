#include "common.h"

#include "PR/os.h"

#include "main/01850.h"

// Interim BSS externs
// This stuff very messy because I don't want to keep going back to 8010D200.bss.s
// to find all this

// D_main_bss_8010D200, 0x8
// D_main_bss_8010D208, 0x8
extern u8 D_main_bss_8010D210;
extern u8 D_main_bss_8010D211[7]; // I bet this is really padding
extern OSThread gIdleThread;
extern OSThread gVideoThread;
// D_main_8010D580, 0x18
// D_main_8010D598, 0x4
// D_main_bss_8010D59C, 0x804
// D_main_8010DDA0, 0x1B0
// D_main_bss_8010DF50, 0x80
// D_main_8010DFD0, 0x4
// D_main_bss_8010DFD4, 0x2
// D_main_bss_8010DFD6, 0x2
// D_main_8010DFD8, 0x30
// D_main_bss_8010E008, 0x8
// D_main_bss_8010E010, 0x80
// D_main_bss_8010E090, 0x818
// D_main_bss_8010E8A8, 0x4
// D_main_bss_8010E8AC, 0x4
// D_main_bss_8010E8B0, 0x1000
// D_main_bss_8010F8B0, 0x400
// D_main_bss_8010FCB0, 0x228
// D_main_bss_8010FED8, 0x08

// Externs that belong to other files
// Ideally tese get delete at some point
extern u8 D_main_bss_801143B0[0x2000]; // video thread stack

u8 isPreNmiPending(void) {
    return D_main_bss_8010D210;
}

s32 returnZeroStub(void) {
    return 0;
}

struct DmaReq {
    s32 size;
    void *dev;
    void *ram;
};

struct BootConfigBlock {
    u8 pad0[4];
    void (*unk4)(s32 *);
    s32 unk8;
    s32 unkC;
    u8 pad10[0xC];
    s32 unk1C;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 pad23;
    u16 unk24;
    u8 pad26[2];
    s32 unk28;
};

extern u8 D_main_bss_8010D211s __asm__("D_main_bss_8010D211");
extern u8 func_entry_80000400[];
extern u8 D_main_bss_8010D200[];
extern u8 D_B0101000[];
extern u8 D_80100400[];
extern s32 D_main_bss_8010E008;
extern struct BootConfigBlock *D_main_bss_8010FCB0;
extern void loadDebugAssets(s32);
extern void initSiQueue(void);
extern void installPeriodicCallback(s32, s32);
extern s32 setDisplayMode(s32, u8, u8, u8, s32, s32);
extern void submitDmaRequestBatch(struct DmaReq *, s32, OSMesgQueue *);

void mainBootstrapWorker(s32 *arg0) {
    struct DmaReq req;
    OSMesgQueue sp28;
    OSMesg sp40;
    s32 t;
    s32 size;

    osStopThread(&gVideoThread);
    t = *arg0;
    D_main_bss_8010E008 = t;
    loadDebugAssets(t);
    size = (s32)(D_main_bss_8010D200 - func_entry_80000400) - 0x100000;
    if (size > 0) {
        osCreateMesgQueue(&sp28, &sp40, 1);
        req.size = (size + 0xF) & ~0xF;
        req.dev = D_B0101000;
        req.ram = D_80100400;
        submitDmaRequestBatch(&req, 1, &sp28);
        osRecvMesg(&sp28, NULL, 1);
        osInvalICache(req.ram, req.size);
    }
    initSiQueue();
    if (D_main_bss_8010FCB0->unk8 != 0) {
        installPeriodicCallback(D_main_bss_8010FCB0->unk8, D_main_bss_8010FCB0->unkC);
    }
    D_main_bss_8010D211s = 0;
    if (D_main_bss_8010FCB0->unk20 != 0) {
        if (setDisplayMode(D_main_bss_8010FCB0->unk1C, D_main_bss_8010FCB0->unk20, D_main_bss_8010FCB0->unk21, D_main_bss_8010FCB0->unk22, D_main_bss_8010FCB0->unk24, D_main_bss_8010FCB0->unk28) == 0) {
            D_main_bss_8010D211s = 1;
        }
    }
    D_main_bss_8010FCB0->unk4(arg0);
}

typedef struct {
    u8 pad0[0x19];
    u8 tripleBuffer;
    u8 pad1A[0x12];
    u32 dlBlocks;
    u32 size30;
    u32 size34;
    u32 size38;
    u8 pad3C[8];
    u32 flags;
} BootMemConfig;

extern BootMemConfig *gBootMemConfig __asm__("D_main_bss_8010FCB0");
extern u32 gOsMemSize __asm__("D_80000318");
extern s32 gFramebuffers[3] __asm__("D_main_bss_801163D8");
extern s32 D_main_bss_801163E4;
extern s32 D_main_bss_801163E8;
extern s32 D_main_bss_801163EC;
extern s32 D_main_bss_801163F0;
extern s32 D_main_bss_801163F4;
extern s32 D_main_bss_801163F8;

#define CARVE(size, dst)        \
    if ((size) < hole) {        \
        dst = lo;               \
        lo += (size);           \
        hole -= (size);         \
    } else {                    \
        top -= (size);          \
        dst = top;              \
    }

s32 partitionFramebufferMemory(s32 *range, s32 *outTop, s16 w, s16 h, s16 bpp, u8 hasZ) {
    u32 fbSize;
    u32 zSize;
    u32 dlSize;
    u32 s30;
    u32 s34;
    u32 s38;
    s32 memTop;
    s32 top;
    s32 lo;
    u32 hole;
    u32 holeSize;

    if (bpp >= 24) {
        fbSize = w * h * 4;
    } else {
        fbSize = w * h * 2;
    }
    if (hasZ) {
        zSize = w * h * 2;
    } else {
        zSize = 0;
    }
    zSize = (zSize + 0x3F) & ~0x3F;
    fbSize = (fbSize + 0x3F) & ~0x3F;
    dlSize = gBootMemConfig->dlBlocks << 6;
    s30 = (gBootMemConfig->size30 + 0xF) & ~0xF;
    s34 = (gBootMemConfig->size34 + 0xF) & ~0xF;
    s38 = (gBootMemConfig->size38 + 0xF) & ~0xF;
    if (gBootMemConfig->flags & 0x2000) {
        memTop = 0x80400000;
    } else {
        memTop = gOsMemSize | 0x80000000;
    }
    D_main_bss_801163E4 = memTop - zSize;
    if ((*(u32 *)((u8 *)gBootMemConfig + 0x44) & 0x400) || zSize == 0) {
        gFramebuffers[0] = memTop - zSize - fbSize;
        hole = 0;
        lo = 0;
    } else {
        holeSize = 0x100000;
        gFramebuffers[0] = memTop - (fbSize + holeSize);
        hole = holeSize - zSize;
        lo = memTop - holeSize;
    }
    gFramebuffers[1] = gFramebuffers[0] - fbSize;
    if (gBootMemConfig->tripleBuffer != 0) {
        gFramebuffers[2] = gFramebuffers[1] - fbSize;
    } else {
        gFramebuffers[2] = 0;
    }
    if (gBootMemConfig->flags & 0x80) {
        top = gFramebuffers[0];
    } else {
        top = gFramebuffers[2];
        if (top == 0) {
            top = gFramebuffers[1];
        }
    }
    CARVE(dlSize, D_main_bss_801163F0)
    CARVE(dlSize, D_main_bss_801163F4)
    CARVE(s30, D_main_bss_801163E8)
    CARVE(s38, D_main_bss_801163F8)
    CARVE(s34, D_main_bss_801163EC)
    if (lo != 0) {
        range[0] = top;
        range[1] = lo - top;
        return 1;
    }
    *outTop = top;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/01850", thread3_video_handle);

INCLUDE_ASM("asm/nonmatchings/main/01850", runVideoFrameTick);

extern void func_entry_8000040C(void *, void *);
extern u8 D_main_bss_8010D200[];
extern u8 D_main_bss_8010D200b[] __asm__("D_main_bss_8010D200");
extern u8 D_main_bss_8010FED8[];
extern u8 D_238C2[];
extern u8 D_47490[];
void realMain(void) __asm__("main");
void realMain(void) {
    func_entry_8000040C(D_main_bss_8010D200, D_238C2);
    func_entry_8000040C(D_main_bss_8010D200b, D_47490);
    osInitialize();
    osCreateThread(&gIdleThread, 0, idle_thread_handle, NULL, D_main_bss_8010FED8, 0xA);
    osStartThread(&gIdleThread);
}

extern OSMesgQueue D_main_8010DFD8;
extern OSMesg D_main_8010D598;
extern OSViMode osViModeTable[];
void noopHandler_80004FD0(void);
void initRumblePakSlots(void);
void preNmiResetThread(void *arg) {
    osCreateMesgQueue(&D_main_8010DFD8, &D_main_8010D598, 1);
    osSetEventMesg(OS_EVENT_PRENMI, &D_main_8010DFD8, NULL);
    osRecvMesg(&D_main_8010DFD8, NULL, OS_MESG_BLOCK);
    D_main_bss_8010D210 = 1;
    switch (osTvType) {
        case 0:
            osViSetMode(&osViModeTable[14]);
            break;
        case 1:
            osViSetMode(&osViModeTable[0]);
            break;
        case 2:
            osViSetMode(&osViModeTable[28]);
            break;
    }
    osViBlack(1);
    noopHandler_80004FD0();
    initRumblePakSlots();
    while (1) {
    }
}

void idle_thread_handle(void) {
    osCreateViManager(0xFE);
    osViBlack(1U);
    osCreateThread(&gVideoThread, 0, thread3_video_handle, NULL, (u32)&D_main_bss_801143B0 + sizeof(D_main_bss_801143B0), 9);
    osStartThread(&gVideoThread);
    osSetThreadPri(NULL, 0);
    while(1);
}
