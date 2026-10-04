#include "common.h"
#include "common_types.h"

typedef struct {
    u8 active;
    u8 pad1[0x17];
    u8 unk18;
    u8 pad19[3];
    s32 sampleOffset;
    u8 pad20[4];
    s32 handle;
    u8 pad28[0x1228 - 0x28];
} SpeechVoiceSlot;

typedef struct {
    u8 data[0x1228];
} SpeechVoice;

extern SpeechVoice D_main_80153420[];
extern SpeechVoiceSlot D_main_bss_80154620[];
extern u8 D_main_bss_80154650[];
extern u8 speechFileLoaded;

s32 osSendMesg(void *mq, void *msg, s32 flag);
s32 osRecvMesg(void *mq, void *msg, s32 flag);
void stopVoice(void *arg0);
void stopVoiceSlotSynced(s32 index);
u32 consumeVoiceSamples(void *voice, u32 count);

extern s32 D_main_bss_80154648;

s32 findVoiceSlotByAge(s32 index) {
    u32 i;

    for (;;) {
        for (i = 0; i < 1; i++) {
            if (D_main_bss_80154620[i].active != 0) {
                if (i != index) {
                    if (D_main_bss_80154620[i].handle == D_main_bss_80154648) {
                        break;
                    }
                }
            }
        }
        if (i == 1) {
            break;
        }
        if (++D_main_bss_80154648 == -1) {
            D_main_bss_80154648 = 0;
        }
    }
    D_main_bss_80154620[index].handle = D_main_bss_80154648;
    if (++D_main_bss_80154648 == -1) {
        D_main_bss_80154648 = 0;
    }
    return D_main_bss_80154620[index].handle;
}

INCLUDE_ASM("asm/nonmatchings/main/9BB60", allocAndConfigureNewVoice);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", stopVoiceSlotSynced);

static inline s32 findVoiceSlotByHandle(s32 handle) {
    u32 i;

    for (i = 0; i < 1; i++) {
        if (D_main_bss_80154620[i].active != 0 && D_main_bss_80154620[i].handle == handle) {
            return i;
        }
    }
    return -1;
}

s32 stopVoiceByHandle(s32 handle) {
    s32 index;

    if (handle == -1 || !speechFileLoaded) {
        return 0;
    }
    index = findVoiceSlotByHandle(handle);
    if (index == -1) {
        return 0;
    }
    stopVoiceSlotSynced(index);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/9BB60", isVoiceHandleActive);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", setVoiceMixByKey);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", serviceVoicePoolFrame);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", getVoicePlaybackProgressByKey);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", loadSpeechFile);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", initMusyXVoiceTable);

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

extern void *speechSampleOffsets;
extern u8 speechSampleOffsetsLoaded;
extern void *D_main_bss_80154674;

void findAndZeroTableSlotMatching(void (*)(void));
void serviceVoicePoolFrame(void);
void rs_free(void *);

void shutdownMusyXVoices(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 1; i++) {
        stopVoiceSlotSynced(i);
    }
    do {
        for (j = 0; j < 1; j++) {
            if (D_main_bss_80154620[j].active != 0) {
                break;
            }
        }
    } while (j != 1);
    speechFileLoaded = 0;
    findAndZeroTableSlotMatching(serviceVoicePoolFrame);
    if (speechSampleOffsets != NULL && speechSampleOffsetsLoaded) {
        rs_free(speechSampleOffsets);
    }
    rs_free(D_main_bss_80154674);
}

s32 accumulateVoiceSampleOffset(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 index) {
    if (speechFileLoaded) {
        consumeVoiceSamples(D_main_80153420[index].data, arg1 + arg3);
        D_main_bss_80154620[index].sampleOffset += arg1 + arg3;
    }
    return 0;
}

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
