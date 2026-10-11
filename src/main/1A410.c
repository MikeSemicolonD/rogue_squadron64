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

INCLUDE_ASM("asm/nonmatchings/main/1A410", postViThreadCommand);

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

INCLUDE_ASM("asm/nonmatchings/main/1A410", computeFramebufferByteSize);

INCLUDE_ASM("asm/nonmatchings/main/1A410", readBufferSwapState);

INCLUDE_ASM("asm/nonmatchings/main/1A410", bufferArbiterProducerMark);

INCLUDE_ASM("asm/nonmatchings/main/1A410", waitOnVideoQueue);

INCLUDE_ASM("asm/nonmatchings/main/1A410", bufferArbiterMarkSlotReady);

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
