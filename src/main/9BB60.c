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

typedef struct {
    u8 active;
    u8 pad[0x1227];
} SpeechVoiceSlot;

extern SpeechVoiceSlot D_main_bss_80154620[];

void findFreeSpeechVoiceSlot(void) {
    s32 i;

    do {
        for (i = 0; i < 1; i++) {
            if (D_main_bss_80154620[i].active != 0) {
                break;
            }
        }
    } while (i != 1);
}

INCLUDE_ASM("asm/nonmatchings/main/9BB60", shutdownMusyXVoices);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", accumulateVoiceSampleOffset);

void synchronousDmaTransfer(s32 arg0, s32 arg1, s32 arg2);
s32 osSendMesg(void *mq, void *msg, s32 flag);

void dmaVoiceSampleAndSignal(s32 arg0, s32 arg1, s32 arg2, void *mq) {
    synchronousDmaTransfer(arg0, arg1, arg2);
    osSendMesg(mq, 0, 1);
}

void bzero(void *, s32);
void osCreateMesgQueue(void *, void *, s32);

void initMusyXVoiceSlot(u8 *voice, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    bzero(voice, 0x190);
    *(s16 *)(voice + 0x166) = 0x28;
    *(s32 *)(voice + 0x194) = arg1;
    *(s32 *)(voice + 0x198) = arg2;
    *(s32 *)(voice + 0x19C) = arg3;
    *(s32 *)(voice + 0x11A8) = 0;
    *(s32 *)(voice + 0x190) = arg4;
    osCreateMesgQueue(voice + 0x11AC, voice + 0x11C4, 1);
    if (arg1 == 0 || arg4 == 0) {
        voice[0x11DD] = 0;
    } else {
        voice[0x11DD] = 1;
    }
    voice[0x11DC] = 0;
    *(s16 *)(voice + 0x11A2) = 0;
    *(s32 *)(voice + 0x11A4) = 0;
    *(s16 *)(voice + 0x11A0) = 0;
    *(s32 *)(voice + 0x11C8) = 0;
    *(s32 *)(voice + 0x11D0) = 0;
    *(s32 *)(voice + 0x11CC) = 0;
    *(s32 *)(voice + 0x11D8) = 0;
    *(s32 *)(voice + 0x11D4) = 0;
    voice[0x11DE] = 2;
}

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
