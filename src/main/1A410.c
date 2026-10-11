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

INCLUDE_ASM("asm/nonmatchings/main/1A410", applyPendingViChanges);

INCLUDE_ASM("asm/nonmatchings/main/1A410", swapBufferWithViMode);

INCLUDE_ASM("asm/nonmatchings/main/1A410", selectAndApplyViMode);

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

INCLUDE_ASM("asm/nonmatchings/main/1A410", bufferArbiterProducerMark);

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

INCLUDE_ASM("asm/nonmatchings/main/1A410", acquireFreeBufferSlot);

INCLUDE_ASM("asm/nonmatchings/main/1A410", postSwapRdpReset);

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

INCLUDE_ASM("asm/nonmatchings/main/1A410", dpInterruptHandlerThread);

INCLUDE_ASM("asm/nonmatchings/main/1A410", fake_func_8001C3FC);
