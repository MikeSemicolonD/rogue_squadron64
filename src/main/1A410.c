#include "common.h"
#include "common_types.h"
#include "PR/os.h"

extern OSMesgQueue D_main_bss_80128D10;
void awaitFrameSyncMesgBlock(void) {
    osRecvMesg(&D_main_bss_80128D10, NULL, OS_MESG_BLOCK);
}

extern OSMesgQueue D_main_bss_80128D10;
void signalFrameSyncMesgNonblock(void) {
    osSendMesg(&D_main_bss_80128D10, NULL, OS_MESG_NOBLOCK);
}

INCLUDE_ASM("asm/nonmatchings/main/1A410", viRetraceHandlerThread);

void osYieldThread(void);
void yieldCurrentThread(void) {
    osYieldThread();
}

extern u8 D_main_bss_80128D2C;
s32 getInactiveBufferIndex(void) {
    return D_main_bss_80128D2C ^ 1;
}

INCLUDE_ASM("asm/nonmatchings/main/1A410", spTaskSchedulerThread);

void osYieldThread(void);
void yieldFromSpThread(void) {
    osYieldThread();
}

void osYieldThread(void);
void yieldFromGfxFrame(void) {
    osYieldThread();
}

extern OSMesgQueue D_main_8011A420;
extern u8 D_main_80128C80;
extern s32 D_main_bss_80128C84;
void postViThreadCommand(s32 arg0) {
    u8 *m = &D_main_80128C80;
    *m = 2;
    D_main_bss_80128C84 = arg0;
    osSendMesg(&D_main_8011A420, m, OS_MESG_BLOCK);
}

INCLUDE_ASM("asm/nonmatchings/main/1A410", initVideoSubsystem);

extern s32 D_main_bss_80128E90;
s32 requestViFeatureChange(s32 arg0) {
    D_main_bss_80128E90 = arg0;
    return 1;
}

extern s32 D_main_bss_80128E94;
s32 beginSceneRenderFrame(s32 arg0) {
    D_main_bss_80128E94 = arg0;
    return 1;
}

extern s32 D_main_bss_80128E90;
extern s32 D_main_bss_80128E94;
void clearPendingViChanges(void) {
    D_main_bss_80128E90 = 0;
    D_main_bss_80128E94 = 0;
}

extern volatile s32 gViReqOn __asm__("D_main_bss_80128E90");
extern volatile s32 gViReqOff __asm__("D_main_bss_80128E94");
extern u8 D_main_bss_8011A862;
extern u8 D_main_bss_8011A864;
extern u8 D_main_bss_8011A865;
extern u8 D_main_bss_8011A866;
extern u8 D_main_bss_8011A867;
extern u8 D_main_bss_8011A868;
extern OSViMode D_main_bss_80128D50[4];
void applyPendingViChanges(void) {
    OSViMode *m;
    if (gViReqOff & 1) {
        D_main_bss_8011A862 = 0;
    }
    if (gViReqOff & 8) {
        D_main_bss_8011A865 = 0;
    }
    if (gViReqOn & 1) {
        D_main_bss_8011A862 = 1;
    }
    if (gViReqOn & 8) {
        D_main_bss_8011A865 = 1;
    }
    if ((gViReqOff | gViReqOn) & 9) {
        if (D_main_bss_8011A865 == 0 || D_main_bss_8011A864 != 0) {
            m = &D_main_bss_80128D50[0];
            if (D_main_bss_8011A862 == 0) {
                m = &D_main_bss_80128D50[1];
            }
        } else {
            m = &D_main_bss_80128D50[3];
            if (D_main_bss_8011A862 != 0) {
                m = &D_main_bss_80128D50[2];
            }
        }
        osViSetMode(m);
        if (!((gViReqOn | gViReqOff) & 2)) {
            osViSetSpecialFeatures(D_main_bss_8011A868 ? 1 : 2);
        }
        if (!((gViReqOn | gViReqOff) & 4)) {
            osViSetSpecialFeatures(D_main_bss_8011A866 ? 0x40 : 0x80);
        }
        if (!((gViReqOn | gViReqOff) & 0x10)) {
            osViSetSpecialFeatures(D_main_bss_8011A867 ? 0x10 : 0x20);
        }
    }
    if (gViReqOff & 2) {
        osViSetSpecialFeatures(2);
        D_main_bss_8011A868 = 0;
    }
    if (gViReqOff & 4) {
        osViSetSpecialFeatures(0x80);
        D_main_bss_8011A866 = 0;
    }
    if (gViReqOff & 0x10) {
        osViSetSpecialFeatures(0x20);
        D_main_bss_8011A867 = 0;
    }
    if (gViReqOn & 2) {
        osViSetSpecialFeatures(1);
        D_main_bss_8011A868 = 1;
    }
    if (gViReqOn & 4) {
        osViSetSpecialFeatures(0x40);
        D_main_bss_8011A866 = 1;
    }
    if (gViReqOn & 0x10) {
        osViSetSpecialFeatures(0x10);
        D_main_bss_8011A867 = 1;
    }
    gViReqOff = 0;
    gViReqOn = 0;
}

extern u8 D_main_bss_8011A862;
extern u8 D_main_bss_8011A864;
extern u8 D_main_bss_8011A865;
extern OSViMode D_main_bss_80128D50[4];
extern OSViMode D_main_bss_80128C90;
extern u16 D_main_bss_80128CC0;
extern u16 D_main_bss_80128CC2;
extern u16 D_main_bss_80128CD4;
extern u16 D_main_bss_80128CD6;
void waitOnVideoQueue(void);
void swapBufferWithViMode(void) {
    OSViMode *m = D_main_bss_80128D50;
    if (D_main_bss_8011A865 == 0 || D_main_bss_8011A864 != 0) {
        if (D_main_bss_8011A862 == 0) {
            m += 1;
        }
    } else {
        if (D_main_bss_8011A862 != 0) {
            m += 2;
        } else {
            m += 3;
        }
    }
    D_main_bss_80128C90 = *m;
    {
        u16 *p = &D_main_bss_80128CC0;
        D_main_bss_80128CC2 = *p;
        p += 10;
        D_main_bss_80128CD6 = *p;
        osViSetMode((OSViMode *)(p - 0x22));
    }
}

extern u8 D_main_bss_8011A862;
extern u8 D_main_bss_8011A864;
extern u8 D_main_bss_8011A865;
extern OSViMode D_main_bss_80128D50[4];
extern OSViMode D_main_bss_80128C90;
extern u16 D_main_bss_80128CC0;
extern u16 D_main_bss_80128CC2;
extern u16 D_main_bss_80128CD4;
extern u16 D_main_bss_80128CD6;
void waitOnVideoQueue(void);
void selectAndApplyViMode(void) {
    OSViMode *m = D_main_bss_80128D50;
    if (D_main_bss_8011A865 == 0 || D_main_bss_8011A864 != 0) {
        if (D_main_bss_8011A862 == 0) {
            m += 1;
        }
    } else {
        if (D_main_bss_8011A862 != 0) {
            m += 2;
        } else {
            m += 3;
        }
    }
    D_main_bss_80128C90 = *m;
    D_main_bss_80128CC2 = D_main_bss_80128CC0;
    D_main_bss_80128CD6 = D_main_bss_80128CD4;
    osViSetMode(&D_main_bss_80128C90);
    waitOnVideoQueue();
}

extern s32 D_main_bss_8011A838;
extern s32 D_main_bss_8011A83C;
extern s16 D_main_bss_8011A848;
s32 computeFramebufferByteSize(void) {
    if (D_main_bss_8011A848 >= 0x18) {
        return D_main_bss_8011A838 * D_main_bss_8011A83C * 4;
    }
    return D_main_bss_8011A838 * D_main_bss_8011A83C * 2;
}

extern s32 D_main_bss_80128EB4;
extern s32 D_main_bss_80128EB8;
extern s32 D_main_bss_80128EBC;
void readBufferSwapState(s32 *arg0, s32 *arg1, s32 *arg2) {
    if (D_main_bss_80128EB4 == -1) {
        *arg0 = 0;
        *arg1 = 0;
        *arg2 = 0;
    } else {
        *arg1 = D_main_bss_80128EB4;
        *arg2 = D_main_bss_80128EB8;
        *arg0 = D_main_bss_80128EBC;
    }
}

typedef struct {
    s32 buf[3];
    s16 h[3];
    u8 st[3];
    u8 n;
    u8 viCount;
    u8 minVi;
    u8 pad18[0x1C];
    s32 time[3];
} BufArbFull;
extern BufArbFull gBufArb __asm__("D_main_bss_80128E98");
extern OSMesgQueue D_main_bss_80128D10;
extern s32 D_main_bss_80128D34;
void bufferArbiterProducerMark(void) {
    s32 i;
    s32 j;
    osRecvMesg(&D_main_bss_80128D10, NULL, OS_MESG_BLOCK);
    for (i = 0; i < gBufArb.n; i++) {
        if (gBufArb.st[i] == 2) {
            gBufArb.time[i] = (D_main_bss_80128D34 != -1) ? D_main_bss_80128D34 : 0;
            for (j = 0; j < gBufArb.n; j++) {
                if (gBufArb.st[j] == 4) {
                    gBufArb.st[i] = 3;
                    gBufArb.h[i] = 0;
                    goto done;
                }
            }
            for (j = 0; j < gBufArb.n; j++) {
                if (gBufArb.st[j] == 5) {
                    if (gBufArb.viCount < gBufArb.minVi - 1) {
                        gBufArb.st[i] = 3;
                        gBufArb.h[i] = 0;
                        goto done;
                    }
                    break;
                }
            }
            osViSwapBuffer((void *)gBufArb.buf[i]);
            gBufArb.st[i] = 4;
            goto done;
        }
    }
done:
    osSendMesg(&D_main_bss_80128D10, NULL, OS_MESG_NOBLOCK);
}

extern volatile u8 D_main_80037808;
extern OSMesgQueue D_main_bss_80128CF0;
void osYieldThread(void);
void waitOnVideoQueue(void) {
    D_main_80037808 = 1;
    osRecvMesg(&D_main_bss_80128CF0, NULL, OS_MESG_BLOCK);
    D_main_80037808 = 0;
    osYieldThread();
}

typedef struct { u8 st[3]; u8 n; } BufArb;
extern BufArb D_main_bss_80128EAA;
void bufferArbiterMarkSlotReady(void) {
    s32 i;
    for (i = 0; i < D_main_bss_80128EAA.n; i++) {
        if (D_main_bss_80128EAA.st[i] == 1) {
            D_main_bss_80128EAA.st[i] = 2;
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/1A410", bufferArbiterAllocSlot);

typedef struct {
    s32 buf[3];
    s16 h[3];
    u8 st[3];
    u8 n;
    u8 viCount;
    u8 minVi;
    u8 pad18[0x10];
    s32 stamp[3];
    s32 time[3];
} BufArbX;
extern BufArbX gBufArbX __asm__("D_main_bss_80128E98");
extern volatile u8 D_main_80037808;
extern OSMesgQueue D_main_bss_80128CF0;
void osYieldThread(void);
s32 acquireFreeBufferSlot(void) {
    s32 i;
    while (1) {
        for (i = 0; i < gBufArbX.n; i++) {
            if (gBufArbX.st[i] == 0) {
                return gBufArbX.buf[i];
            }
        }
        D_main_80037808 = 1;
        osRecvMesg(&D_main_bss_80128CF0, NULL, OS_MESG_BLOCK);
        D_main_80037808 = 0;
        osYieldThread();
    }
}

#include "PR/sptask.h"
extern u8 D_main_bss_8011A8C8;
extern volatile u8 gBufIdxV __asm__("D_main_bss_80128D2C");
s32 bufferArbiterAllocSlot(s32);
void emitCombinerStateAndPatch(void *, u8);
void computeFrameDeltaTime(void);
extern u8 rspbootTextStart[];
extern u8 findModelAnimKeyframeByPhase[];
extern OSTask gspTask;
extern s32 D_main_bss_8011A4C0;
extern u32 D_main_800377C0;
extern u32 D_main_800377C4;
extern volatile u8 D_main_bss_8011A89E;
extern volatile u8 D_main_bss_8011A89D;
extern u8 D_main_80128CE0;
extern OSTask *D_main_bss_80128CE4;
extern OSMesgQueue D_main_8011A420;
void postSwapRdpReset(void) {
    s32 slot;
    u8 *m;
    volatile u8 *p = &D_main_bss_8011A8C8;
    if (*p != 0) {
        slot = bufferArbiterAllocSlot(1);
        if (slot != 0) {
            *p = 0;
            emitCombinerStateAndPatch((void *)slot, gBufIdxV ^ 1);
            computeFrameDeltaTime();
            osWritebackDCacheAll();
            gspTask.t.data_ptr = (u64 *)(D_main_bss_8011A4C0 - 8);
            {
                u8 *bt = rspbootTextStart;
                gspTask.t.ucode_boot_size = findModelAnimKeyframeByPhase - bt;
                gspTask.t.ucode_boot = (u64 *)bt;
            }
            gspTask.t.data_size = 0;
            gspTask.t.ucode = (u64 *)D_main_800377C0;
            gspTask.t.ucode_data = (u64 *)D_main_800377C4;
            osDpSetStatus(0x1C0);
            m = &D_main_80128CE0;
            D_main_bss_8011A89E = 1;
            D_main_bss_8011A89D = 1;
            *m = 1;
            D_main_bss_80128CE4 = &gspTask;
            osSendMesg(&D_main_8011A420, m, OS_MESG_NOBLOCK);
        }
    }
}

extern u8 D_main_bss_8011A8C8;
extern u8 D_main_bss_8011A8C9;
void setPostSwapPendingFlags(void) {
    D_main_bss_8011A8C8 = 1;
    D_main_bss_8011A8C9 = 1;
}

INCLUDE_ASM("asm/nonmatchings/main/1A410", waitForPostSwapAck);

extern u8 D_main_bss_8011A8C8;
extern u8 D_main_bss_8011A8C9;
void clearPostSwapPendingFlags(void) {
    D_main_bss_8011A8C8 = 0;
    D_main_bss_8011A8C9 = 0;
}

extern u32 D_main_800377C0;
extern u32 D_main_800377C4;
void setGfxTaskYieldParams(u32 arg0, u32 arg1) {
    D_main_800377C0 = arg0;
    D_main_800377C4 = arg1;
}

extern OSMesgQueue D_main_bss_8011A408;
extern OSMesg D_main_bss_8011A830;
extern OSMesgQueue D_main_8011A7E8;
extern OSMesg D_main_bss_8011DC64;
extern s32 D_main_bss_80128D30;
extern s32 D_main_bss_80128D34;
extern s32 D_main_bss_80128EDC;
extern volatile u8 D_main_bss_8011A89D;
u32 getTimeSinceLastFrame(void);
void dpInterruptHandlerThread(void *arg) {
    volatile u8 *p;
    osCreateMesgQueue(&D_main_bss_8011A408, &D_main_bss_8011A830, 1);
    osSetEventMesg(OS_EVENT_DP, &D_main_bss_8011A408, NULL);
    osCreateMesgQueue(&D_main_8011A7E8, &D_main_bss_8011DC64, 1);
    p = &D_main_bss_8011A89D;
    while (1) {
        osRecvMesg(&D_main_bss_8011A408, NULL, OS_MESG_BLOCK);
        D_main_bss_80128D34 = (u32)osGetTime() - D_main_bss_80128D30;
        D_main_bss_80128EDC = getTimeSinceLastFrame();
        if (*p != 0) {
            osSendMesg(&D_main_8011A7E8, NULL, OS_MESG_NOBLOCK);
        }
        p[-2] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/1A410", fake_func_8001C3FC);
