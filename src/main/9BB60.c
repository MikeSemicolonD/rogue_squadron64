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
void osCreateMesgQueue(void *, void *, s32);

extern u8 D_main_bss_80154668[];

static inline void createSpeechLock(void) {
    osCreateMesgQueue(D_main_bss_80154650, D_main_bss_80154668, 1);
}

static inline void lockSpeechVoices(void) {
    osRecvMesg(D_main_bss_80154650, NULL, 1);
}

static inline void unlockSpeechVoices(void) {
    osSendMesg(D_main_bss_80154650, NULL, 0);
}

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

extern u32 numSpeechSamples;
extern s32 speechFile;
extern u32 *gSpeechOffs __asm__("speechSampleOffsets");
extern void *gSpeechBuf __asm__("D_main_bss_80154674");
extern void dmaVoiceSampleAndSignal(s32, s32, s32, void *);
extern void initMusyXVoiceSlot(u8 *voice, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 findVoiceSlotByAge(s32);

s32 allocAndConfigureNewVoice(u32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6) {
    SpeechVoice *v;
    s32 i;
    if (speechFileLoaded != 0 && arg0 < numSpeechSamples) {
        for (i = 0; i < 1; i++) {
            if (D_main_bss_80154620[i].active == 0) break;
        }
        if (i != 1) {
            v = &D_main_80153420[i];
            osCreateMesgQueue(&v->data[0x11E0], &v->data[0x11F8], 2);
            if (arg1 == 0) {
                arg1 = 0x3E80;
                if (*(u8 *)&gSpeechOffs[arg0] == 0) {
                    arg1 = 0x1F40;
                }
            }
            v->data[0x1204] = arg2;
            v->data[0x1201] = arg3;
            v->data[0x1202] = arg4;
            v->data[0x1203] = arg5;
            v->data[0x1219] = arg6;
            *(void **)&v->data[0x1210] = gSpeechBuf;
            *(s32 *)&v->data[0x1208] = arg1;
            *(s32 *)&v->data[0x1214] = (((u32)arg1 * 8 / 30 + 0x9F) / 160) * 0xA0;
            lockSpeechVoices();
            initMusyXVoiceSlot(v->data, (gSpeechOffs[arg0] & 0xFFFFFF) + speechFile, *(s32 *)&v->data[0x1210], *(s32 *)&v->data[0x1214], (s32)dmaVoiceSampleAndSignal);
            *(s32 *)&v->data[0x120C] = -1;
            *(volatile u8 *)&v->data[0x1200] = 1;
            unlockSpeechVoices();
            return findVoiceSlotByAge(i);
        }
    }
    return -1;
}

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

extern u8 D_main_bss_80154621[];
extern u8 D_main_bss_80154622[];
extern u8 D_main_bss_80154623[];
extern s32 D_main_bss_8015462C[];
extern void setVoiceVolumePanLocked(s32, s32, s32, s32, s32);

s32 setVoiceMixByKey(s32 arg0, s8 arg1, s8 arg2, s8 arg3, u8 arg4) {
    s32 index;
    s32 off;
    s32 h;

    if (speechFileLoaded) {
        index = findVoiceSlotByHandle(arg0);
        if (index != -1) {
            lockSpeechVoices();
            index = index * 0x1228;
            h = *(s32 *)((u8 *)D_main_bss_8015462C + index);
            if (h != -1) {
                setVoiceVolumePanLocked(h, arg1 & 0xFF, arg2 & 0xFF, arg3 & 0xFF, arg4);
            }
            D_main_bss_80154622[index] = arg2;
            D_main_bss_80154623[index] = arg3;
            D_main_bss_80154621[index] = arg1;
            unlockSpeechVoices();
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/9BB60", serviceVoicePoolFrame);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", getVoicePlaybackProgressByKey);

INCLUDE_ASM("asm/nonmatchings/main/9BB60", loadSpeechFile);

extern void *speechSampleOffsets;
extern void *D_main_bss_80154674;


void initMusyXVoiceSlot(u8 *voice, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 streamSampleCountToByteSize(s32);
void *rs_malloc(u32, u16);
void registerSiCallback(void (*)(void));
void serviceVoicePoolFrame(void);
void osCreateMesgQueue(void *, void *, s32);

void initMusyXVoiceTable(void) {
    s32 i;

    speechSampleOffsets = 0;
    for (i = 0; i < 1; i++) {
        initMusyXVoiceSlot(D_main_80153420[i].data, 0, 0, 0, 0);
        D_main_bss_80154620[i].active = 0;
    }
    createSpeechLock();
    unlockSpeechVoices();
    D_main_bss_80154674 = rs_malloc(streamSampleCountToByteSize(0x10E0), 0);
    registerSiCallback(serviceVoicePoolFrame);
    speechFileLoaded = 1;
    D_main_bss_80154648 = 0;
}

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
