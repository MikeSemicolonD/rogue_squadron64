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

INCLUDE_ASM("asm/nonmatchings/main/9BB60", dmaVoiceSampleAndSignal);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", initMusyXVoiceSlot);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", serviceStreamingVoice);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", consumeVoiceSamples);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", advanceVoiceStateToPlaying);

void stopVoice(void *arg0) {
    (*(s8 *)((u8 *)(arg0) + 0x11DD)) = 4;
}

INCLUDE_ASM("asm/nonmatchings/main/9BB60", fake_func_8009C2C8);
