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

typedef struct {
    s32 unk0;
    u8 pad4[0xE];
    u16 width;
    u16 height;
    u16 bpp;
    u8 viFlag;
    u8 pad19[0x17];
    u32 unk30;
    u32 unk34;
    u32 unk38;
    u16 unk3C;
    u16 unk3E;
    u16 unk40;
    u16 unk42;
    u32 flags;
} VideoBootConfig;

typedef struct {
    s32 fb[3];
    s32 z;
    s32 e8;
    s32 ec;
    s32 dl[2];
    s32 f8;
} VideoMem;

extern VideoMem gVideoMem __asm__("D_main_bss_801163D8");
extern OSMesgQueue D_main_8010D580;
extern OSMesg D_main_8010DFD0;
extern OSThread D_main_8010DDA0;
extern u8 sNmiThreadStackEnd[] __asm__("D_main_8010DDA0");
extern u8 D_47490[];
extern void preNmiResetThread(void *);
extern VideoBootConfig *getGameConfig(s32);
extern void initMainHeap(s32, void *, void *, s32);
extern u8 initServiceRegistry(void);
extern u8 initDmaSlots(s32, s32 (*)(void));
extern u8 setVideoReadyFlag(void);
extern void setViModeType(void);
extern void initVideoBootWrapper(s16, s16, u16, u16, s16, s32 *, s32, s32, u32, s32 *, s32, u32, s32, u32, u32, u8, u16, u16);
extern s32 registerServiceWorker(s32, s32, s32, void (*)(s32 *));
extern void startServiceWorker(s32);

void thread3_video_handle(void *arg) {
    VideoBootConfig *cfg;
    s32 top;
    u16 w;
    u16 h;
    s16 bpp;
    u16 a;
    u16 b;
    s32 n;
    u8 *base;
    s32 heapTop;

    osCreateMesgQueue(&D_main_8010D580, &D_main_8010DFD0, 1);
    osCreateThread(&D_main_8010DDA0, 0, preNmiResetThread, NULL, sNmiThreadStackEnd, 0x7F);
    osStartThread(&D_main_8010DDA0);
    cfg = getGameConfig(0);
    *(VideoBootConfig **)&D_main_bss_8010FCB0 = cfg;
    if (cfg->unk0 == 0) {
        w = cfg->width;
        h = cfg->height;
        bpp = cfg->bpp;
        a = cfg->unk40;
        b = cfg->unk42;
    }
    if (bpp == 24) {
        bpp = 32;
    }
    if ((u8)partitionFramebufferMemory((s32 *)D_main_bss_8010D200, &top, w, h, bpp, !(cfg->flags & 0x200))) {
        n = 1;
        base = D_main_bss_8010D200;
        heapTop = gVideoMem.z;
    } else {
        n = 0;
        base = NULL;
        heapTop = top;
    }
    { register u8 *e asm("$2") = D_main_bss_8010D200; initMainHeap(n, base, e + (s32)D_47490, heapTop); }
    if (!initServiceRegistry()) {
        while (1) {
        }
    }
    if (!initDmaSlots(0, returnZeroStub)) {
        while (1) {
        }
    }
    if (!setVideoReadyFlag()) {
        while (1) {
        }
    }
    setViModeType();
    initVideoBootWrapper(w, h, a, b, bpp, gVideoMem.fb, gVideoMem.z, gVideoMem.e8,
                         (((VideoBootConfig *)D_main_bss_8010FCB0)->unk30 + 0xF) & ~0xF, gVideoMem.dl, gVideoMem.f8,
                         (((VideoBootConfig *)D_main_bss_8010FCB0)->unk38 + 0xF) & ~0xF, gVideoMem.ec,
                         (((VideoBootConfig *)D_main_bss_8010FCB0)->unk34 + 0xF) & ~0xF,
                         ((VideoBootConfig *)D_main_bss_8010FCB0)->flags, ((VideoBootConfig *)D_main_bss_8010FCB0)->viFlag,
                         ((VideoBootConfig *)D_main_bss_8010FCB0)->unk3C, ((VideoBootConfig *)D_main_bss_8010FCB0)->unk3E);
    if (D_main_bss_8010FCB0->unk4 != NULL) {
        startServiceWorker(registerServiceWorker(8, 0x2000, 0xA, mainBootstrapWorker));
    }
    while (1) {
    }
}

typedef struct {
    u16 f0;
    u16 w;
    u16 h;
    s16 bpp;
    u8 vi;
    u8 pad9;
} VidMode;

typedef struct {
    s32 mode;
    u8 a;
    u8 b;
    u8 c;
    u8 pad7;
    u16 d;
    u8 padA[2];
    s32 e;
} VidParams;

typedef struct {
    u32 dlBlocks;
    u32 s30;
    u32 s34;
    u32 s38;
    u16 f10;
    u16 f12;
    u16 f14;
    u16 f16;
    u32 flags;
} VidMem;

typedef struct {
    u8 pad0[0x10];
    VidMode mode;
    VidParams params;
    VidMem mem;
} VidBootCfg;

typedef struct {
    s32 fb[3];
    s32 z;
    s32 e8;
    s32 ec;
    s32 dl[2];
    s32 f8;
} VidMemMap;

extern VidMemMap sVidMemMap __asm__("D_main_bss_801163D8");
extern VidBootCfg *sVidBootCfg __asm__("D_main_bss_8010FCB0");
extern u8 sHeapBase208[] __asm__("D_main_bss_8010D208");
extern u8 D_47490[];
extern void musyxNoopStub(void);
extern void coalesceFreeHeapBlocks(s32, void *, void *, s32);
extern u8 advanceVideoFrame(s16, s16, u16, u16, s16, s32 *, s32, s32, u32, s32 *, s32, u32, s32, u32, u32, u8, u16, u16);
extern s32 reapplyDisplayMode(s32, u8, u8, u8, u16, s32);

s32 runVideoFrameTick(VidMode *mode, VidMem *mem, VidParams *params) {
    s32 top;
    u16 w;
    u16 h;
    u16 bpp;
    u16 a;
    u16 b;
    s32 n;
    u8 *base;
    s32 heapTop;
    musyxNoopStub();
    bpp = mode->bpp;
    w = mode->w;
    h = mode->h;
    a = mem->f14;
    b = mem->f16;
    if (mode->bpp == 24) {
        bpp = 32;
    }
    if ((u8)partitionFramebufferMemory((s32 *)sHeapBase208, &top, w, h, bpp, !(mem->flags & 0x200))) {
        n = 1;
        base = sHeapBase208;
        heapTop = sVidMemMap.z;
    } else {
        n = 0;
        base = NULL;
        heapTop = top;
    }
    coalesceFreeHeapBlocks(n, base, (u8 *)((s32)D_main_bss_8010D200 + (s32)D_47490), heapTop);
    if (!advanceVideoFrame(w, h, a, b, bpp, sVidMemMap.fb, sVidMemMap.z, sVidMemMap.e8, (mem->s30 + 0xF) & ~0xF, sVidMemMap.dl, sVidMemMap.f8,
                           (mem->s38 + 0xF) & ~0xF, sVidMemMap.ec, (mem->s34 + 0xF) & ~0xF, mem->flags, mode->vi, mem->f10, mem->f12)) {
        return 0;
    }
    if (D_main_bss_8010D211s == 0) {
        return 1;
    }
    if (params->a == 0) {
        return 1;
    }
    if (reapplyDisplayMode(params->mode, params->a, params->b, params->c, params->d, params->e) != 0) {
        return 0;
    }
    sVidBootCfg->mode = *mode;
    sVidBootCfg->mem = *mem;
    sVidBootCfg->params = *params;
    return 1;
}

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
