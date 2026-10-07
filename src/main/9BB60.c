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

extern volatile SpeechVoiceSlot gVSlots[] __asm__("D_main_bss_80154620");

void stopVoiceSlotSynced(s32 index) {
    switch (gVSlots[index].active) {
    case 1:
        gVSlots[index].active = 0;
        break;
    case 2:
        lockSpeechVoices();
        stopVoice(D_main_80153420[index].data);
        gVSlots[index].active = 3;
        gVSlots[index].unk18 = 4;
        unlockSpeechVoices();
        break;
    }
}

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

s32 isVoiceHandleActive(s32 handle) {
    u32 i;
    register s32 h asm("$5") = handle;

    if (speechFileLoaded) {
        for (i = 0; i < 1; i++) {
            if (D_main_bss_80154620[i].active != 0 && D_main_bss_80154620[i].handle == h) {
                goto found;
            }
        }
        i = -1;
    found:
        h = i;
        __asm__("" : "=r"(h) : "0"(h));
        if (h != -1) {
            return D_main_bss_80154620[h].active != 0;
        }
    }
    return 0;
}

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

extern u64 osGetTime(void);
extern void svpStream(void *) __asm__("serviceStreamingVoice");
extern void advanceVoiceStateToPlaying(void *);
extern s32 startStreamedSampleVoice(s32, s32, s32, s32, s32, s32, s32, s32, void *, s32);
extern void stopStreamedVoice(s32);
extern s32 accumulateVoiceSampleOffset(s32, s32, s32, s32, s32);
extern f32 D_main_8003DF00;
extern f64 D_main_8003DF08;
extern u32 D_main_bss_8015466C;
extern u32 D_main_bss_80154678;
extern u32 D_main_bss_80154680;
extern u8 D_main_bss_80154621[];
extern u8 D_main_bss_80154622[];
extern u8 D_main_bss_80154623[];
extern u8 D_main_bss_80154624[];
extern u8 D_main_bss_80154639[];
extern s32 D_main_bss_80154630[];
extern s32 D_main_bss_80154634[];
extern s32 D_main_bss_8015463C[];
extern f32 D_main_bss_80154640[];
extern u16 D_main_bss_801545C0[];

#define SVA(T, K) (*(T *)((u8 *)D_main_80153420 + (K) + off))
void serviceVoicePoolFrame(void) {
    s32 i;
    s32 off;
    u8 *v;

    if (speechFileLoaded) {
        lockSpeechVoices();
        i = 0;
        D_main_bss_8015466C = osGetTime();
        for (; i < 1; i++) {
            off = i * 0x1228;
            if (*(volatile u8 *)((u8 *)D_main_bss_80154620 + off) == 0) {
                continue;
            }
            v = (u8 *)D_main_80153420 + off;
            svpStream(v);
            switch (*(volatile u8 *)((u8 *)D_main_bss_80154620 + off)) {
            case 1:
                if (SVA(u8, 0x11DD) == 2) {
                    s32 r = SVA(s32, 0x1208);
                    f64 d = r;
                    f32 x;
                    x = (f32)*(u16 *)((u8 *)D_main_bss_801545C0 + off) * D_main_8003DF00;
                    if (r < 0) {
                        d += D_main_8003DF08;
                    }
                    *(s32 *)((u8 *)D_main_bss_8015463C + off) = 0;
                    *(volatile u8 *)((u8 *)D_main_bss_80154620 + off) = 2;
                    *(f32 *)((u8 *)D_main_bss_80154640 + off) = x / (f32)d;
                    advanceVoiceStateToPlaying(v);
                    *(s32 *)&v[0x120C] = startStreamedSampleVoice(
                        D_main_bss_80154624[off], *(s32 *)((u8 *)D_main_bss_80154630 + off),
                        *(s32 *)((u8 *)D_main_bss_80154634 + off), SVA(s32, 0x1208),
                        D_main_bss_80154621[off], D_main_bss_80154622[off], D_main_bss_80154623[off],
                        D_main_bss_80154639[off], accumulateVoiceSampleOffset, i);
                    if (*(s32 *)&v[0x120C] == -1) {
                        stopVoice(v);
                        *(volatile u8 *)((u8 *)D_main_bss_80154620 + off) = 0;
                    }
                }
                break;
            case 2:
                if (SVA(u8, 0x11DD) == 4) {
                    *(volatile u8 *)((u8 *)D_main_bss_80154620 + off) = 3;
                    SVA(u8, 0x1218) = 4;
                }
                break;
            case 3:
                if (SVA(u8, 0x1218) == 0) {
                    *(volatile u8 *)((u8 *)D_main_bss_80154620 + off) = 0;
                } else {
                    if (SVA(u8, 0x1218) == 2) {
                        stopStreamedVoice(SVA(s32, 0x120C));
                        SVA(s32, 0x120C) = -1;
                    }
                    v[0x1218] = SVA(u8, 0x1218) - 1;
                }
                break;
            }
        }
        D_main_bss_80154680 = osGetTime();
        D_main_bss_80154678 = D_main_bss_80154680 - D_main_bss_8015466C;
        unlockSpeechVoices();
    }
}

INCLUDE_ASM("asm/nonmatchings/main/9BB60", getVoicePlaybackProgressByKey);

extern void *speechSampleOffsets;
extern u8 speechSampleOffsetsLoaded;
void *rs_malloc(u32, u16);
void rs_free(void *);
extern void setupAssetDma(s32, s32, s32, s32, s32, void *);
extern s32 getAssetRamAddress(s32);

s32 loadSpeechFile(s32 arg0, s32 arg1) {
    u32 *buf;
    u32 *offs;

    if (speechFileLoaded) {
        if (speechSampleOffsets != NULL && speechSampleOffsetsLoaded) {
            rs_free(speechSampleOffsets);
        }
        if ((arg0 & 0xF0000000) != 0x80000000) {
            speechFile = getAssetRamAddress(arg0);
            buf = rs_malloc(4, 8);
            if (buf == NULL) {
                return 0;
            }
            setupAssetDma(arg1, 0, arg0, 0, 4, buf);
            numSpeechSamples = *buf;
            rs_free(buf);
            offs = rs_malloc(numSpeechSamples * 4, 0);
            speechSampleOffsets = offs;
            if (offs == NULL) {
                return 0;
            }
            setupAssetDma(arg1, 0, arg0, 4, numSpeechSamples * 4, offs);
            { register u8 one asm("$2") = 1; speechSampleOffsetsLoaded = one; }
            return 1;
        }
        speechFile = arg0;
        speechSampleOffsets = (void *)(arg0 + 4);
        { register u32 n asm("$2") = *(u32 *)arg0; numSpeechSamples = n; }
        speechSampleOffsetsLoaded = 0;
        return 1;
    }
    return 0;
}

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

typedef struct {
    u8 pad0[0x190];
    void (*readFn)(u32, void *, s32, void *);
    u32 srcBase;
    u32 bufBase;
    u32 bufSize;
    u8 pad1A0[0x4];
    u32 hdrA;
    u32 hdrB;
    u8 pad1AC[0x11A0 - 0x1AC];
    u16 blocksLeft;
    u16 blocksLeftLo;
    u32 remain;
    u32 endMark;
    u8 mq[0x1C];
    u32 unk11C8;
    u32 unk11CC;
    s32 unk11D0;
    u32 unk11D4;
    u32 unk11D8;
    u8 pending;
    u8 state;
    u8 budget;
} StreamVoice;
extern void decodeAndFillVoiceBlock(void *, u32);

void serviceStreamingVoice(StreamVoice *v) {
    s32 n;
    s32 budget;
    u32 t;
    u8 st;
    u32 t2;
    u32 t3;
    u32 t4;
    u32 t5;
    u32 t6;
    u16 bl;

    budget = v->budget;
    if (v->pending != 0) {
        if (osRecvMesg(v->mq, NULL, 0) >= 0) {
            if (v->unk11D0 == 0) {
                v->unk11C8 = 0x60;
                v->blocksLeft = *(u16 *)&v->hdrA;
                v->blocksLeftLo = v->hdrA;
                v->remain = v->hdrB & 0xFFFFFF;
            }
            t2 = v->remain;
            v->unk11D0 += 0x400;
            v->remain = (t2 < 0x101) ? 0 : t2 - 0x100;
            v->pending = 0;
        }
        if (v->pending != 0) {
            goto skip;
        }
    }
    st = v->state;
    if (st == 1 || st == 2 || (st & 0xFF) == 3) {
        t3 = v->unk11D0;
        if (t3 - v->unk11CC < 0xC01) {
            if (t3 == 0) {
                n = 0x400;
            } else {
                t4 = v->remain;
                n = 0x400;
                if (t4 < 0x101) {
                    n = t4 * 4;
                }
            }
            if (n > 0) {
                v->pending = 1;
                v->readFn(v->srcBase + v->unk11D0, (u8 *)v + ((v->unk11D0 & 0xFF8) + 0x1A0), n, v->mq);
            }
        }
    }
skip:
    if (v->unk11D8 - v->unk11D4 < v->bufSize - 0xA0) {
        do {
            if (!((v->state == 1 || v->blocksLeft != 0) && ((t5 = v->unk11D0, t5 != 0) && v->remain == 0 || t5 - v->unk11CC >= 0x25) && budget > 0)) {
                break;
            }
            decodeAndFillVoiceBlock(v, v->bufBase + ((v->unk11D8 % v->bufSize) >> 2) * 8);
            bl = v->blocksLeft - 1;
            v->blocksLeft = bl;
            v->unk11CC = (v->unk11C8 >> 3) & ~3;
            v->unk11D8 += 0xA0;
            if (!(bl & 0xFFFF)) {
                v->endMark = v->bufSize;
            }
            budget -= 1;
        } while (v->unk11D8 - v->unk11D4 < v->bufSize - 0xA0);
    }
    if ((u32)(v->state - 3) < 2 && v->blocksLeft == 0) {
        t6 = v->unk11D8;
        while ((t6 - v->unk11D4 < v->bufSize - 0xA0) & (budget > 0)) {
            bzero((void *)(v->bufBase + ((t6 % v->bufSize) >> 2) * 8), 0x140);
            budget -= 1;
            v->unk11D8 += 0xA0;
            t6 = v->unk11D8;
        }
    }
    if (v->state == 1 && v->unk11D8 - v->unk11D4 >= v->bufSize - 0x140) {
        v->state = 2;
    }
}

u32 consumeVoiceSamples(void *v, u32 count)
{
  u8 *voice = v;
  u32 n = 0;
  s32 rem;
  s32 avail;
  u32 w;
  if (voice[0x11DD] == 3)
  {
    rem = *((s32 *) (voice + 0x11A8));
    if (rem > 0)
    {
      rem -= count;
      *((s32 *) (voice + 0x11A8)) = rem;
      if (rem <= 0)
      {
        n = 0x11DD;
        voice[n] = 4;
        *((s32 *) (voice + 0x11A8)) = 0;
      }
    }
    avail = (*((u32 *) (voice + 0x11D8))) - (*((u32 *) (voice + 0x11D4)));
    w = avail;
    if (count < w)
    {
      w = count;
    }
    n = w;
    *((u32 *) (voice + 0x11D4)) += w;
    return n;
  }
  if (w || avail)
  {
    return n;
  }
  else
  {
    return n;
  }
}

void advanceVoiceStateToPlaying(void *arg0) {
    if ((*(u8 *)((u8 *)(arg0) + 0x11DD)) == 2) {
        (*(u8 *)((u8 *)(arg0) + 0x11DD)) = 3U;
    }
}

void stopVoice(void *arg0) {
    (*(s8 *)((u8 *)(arg0) + 0x11DD)) = 4;
}

INCLUDE_ASM("asm/nonmatchings/main/9BB60", fake_func_8009C2C8);
