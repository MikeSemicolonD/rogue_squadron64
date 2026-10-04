#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/9BB60", findVoiceSlotByAge);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", allocAndConfigureNewVoice);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", stopVoiceSlotSynced);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", stopVoiceByHandle);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", isVoiceHandleActive);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", setVoiceMixByKey);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", serviceVoicePoolFrame);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", getVoicePlaybackProgressByKey);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", loadSpeechFile);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", initMusyXVoiceTable);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", findFreeSpeechVoiceSlot);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", shutdownMusyXVoices);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", accumulateVoiceSampleOffset);

void synchronousDmaTransfer(s32 arg0, s32 arg1, s32 arg2);
s32 osSendMesg(void *mq, void *msg, s32 flag);

void dmaVoiceSampleAndSignal(s32 arg0, s32 arg1, s32 arg2, void *mq) {
    synchronousDmaTransfer(arg0, arg1, arg2);
    osSendMesg(mq, 0, 1);
}

INCLUDE_ASM("asm/nonmatchings/main/9BB60", initMusyXVoiceSlot);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", serviceStreamingVoice);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", consumeVoiceSamples);

void advanceVoiceStateToPlaying(void *arg0) {
    if ((*(u8 *)((u8 *)(arg0) + 0x11DD)) == 2) {
        (*(u8 *)((u8 *)(arg0) + 0x11DD)) = 3U;
    }
}

void stopVoice(void *arg0) {
    (*(s8 *)((u8 *)(arg0) + 0x11DD)) = 4;
}

INCLUDE_ASM("asm/nonmatchings/main/9BB60", fake_func_8009C2C8);
