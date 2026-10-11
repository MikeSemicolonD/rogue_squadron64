#include "common.h"
#include "common_types.h"
#include "PR/os.h"

INCLUDE_ASM("asm/nonmatchings/main/832A0", findModelAnimKeyframeByPhase);

typedef struct { s32 a; s32 b; s32 c; u8 *ch; u8 state; u8 pad[3]; } MaSlot;
extern MaSlot gActiveModelAnimSlots[];
s32 resetModelAnimSlotTable(void) {
    u16 i;
    for (i = 0; i < 0x20; i++) {
        gActiveModelAnimSlots[i].a = 0;
        gActiveModelAnimSlots[i].b = 0;
        gActiveModelAnimSlots[i].c = 0;
        gActiveModelAnimSlots[i].state = 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", allocateModelAnimSlot);

INCLUDE_ASM("asm/nonmatchings/main/832A0", appendAnimHandleAndDescendantsToBuffer);

void *rs_malloc(u32, u16);
s32 allocateModelAnimSlot(void *, void *, u16);
void appendAnimHandleAndDescendantsToBuffer(s32);
extern s32 D_main_bss_8013AC10;
extern u8 D_main_bss_8013A9A1[];
s32 flattenAnimTreeAndAllocateSlot(u8 *a, u8 *b) {
    u16 n = *(u16 *)(*(u8 **)(b + 4) + 0xE);
    s32 *buf = rs_malloc(n * 4, 0);
    s32 slot;
    D_main_bss_8013AC10 = (s32)(buf + 1);
    *buf = (s32)(a + 0x1C);
    if (*(s32 *)(a + 0xC) != 0) {
        appendAnimHandleAndDescendantsToBuffer(*(s32 *)(a + 0xC));
    }
    if (*(s32 *)a != 0) {
        appendAnimHandleAndDescendantsToBuffer(*(s32 *)a);
    }
    slot = allocateModelAnimSlot(buf, b, n);
    if (slot != 0) {
        s32 idx = slot - 1;
        *(u8 *)((s32)D_main_bss_8013A9A1 + idx * 0x14) = 1;
    }
    return slot;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", model_animation_offset_convert);

INCLUDE_ASM("asm/nonmatchings/main/832A0", releaseModelAnimSlot);

INCLUDE_ASM("asm/nonmatchings/main/832A0", markModelAnimChannelEntryActive);

INCLUDE_ASM("asm/nonmatchings/main/832A0", clearModelAnimChannelEntry);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seekModelAnimChannelToTime);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seekAllModelAnimChannelsInSlotToTime);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setModelAnimChannelEntryDuration);

INCLUDE_ASM("asm/nonmatchings/main/832A0", getModelAnimChannelEntryDuration);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setModelAnimSlotCycleDuration);

INCLUDE_ASM("asm/nonmatchings/main/832A0", sampleModelAnimKeyframeVec3);

INCLUDE_ASM("asm/nonmatchings/main/832A0", parseModelAnimType2Entry);

INCLUDE_ASM("asm/nonmatchings/main/832A0", audioSeqMallocZero);

void rs_free(void *);
void audioSeqFree(void *p) {
    rs_free(p);
}

extern u32 D_main_800A0F54;
u16 unusedRand(void) {
    D_main_800A0F54 *= 0xA8351D63;
    return D_main_800A0F54 >> 6;
}

extern s16 D_main_800A0F58[];
s16 lookupSineFromAngleTable(s32 a) {
    u32 q = a & 0xFFF;
    if (q < 0x400) {
        return D_main_800A0F58[q];
    }
    if (q < 0x800) {
        return D_main_800A0F58[~a & 0x3FF];
    }
    if (q < 0xC00) {
        return -D_main_800A0F58[a & 0x3FF];
    }
    return -D_main_800A0F58[~a & 0x3FF];
}

extern s32 D_main_bss_8013ACD0[];
void setTrackVoiceTickBudget(u32 tempo, u8 t) {
    if (t == 0xFF) {
        t = 8;
    }
    D_main_bss_8013ACD0[t] = (tempo * 0x600) / 240;
}

extern s32 D_main_bss_8013ACD0[];
s32 getTrackVoiceTickBudget(u8 *t) {
    s32 *base = D_main_bss_8013ACD0;
    s32 *p;
    u8 idx = t[0x4F];
    if (idx != 0xFF) {
        p = base + idx;
    } else {
        p = base + 8;
    }
    return *p;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", setChannelNoteCell);

extern u8 D_main_bss_8013C460[];
extern u8 D_main_bss_80142040[][16];
void setChannelByteParam(u8 a, u8 b, u8 v) {
    if (b != 0xFF) {
        D_main_bss_80142040[b][a] = v;
        return;
    }
    D_main_bss_8013C460[a] = v;
}

extern u8 D_main_bss_8013C460[];
extern u8 D_main_bss_80142040[][16];
u8 getChannelByteParam(u8 a, u8 b) {
    if (b != 0xFF) {
        return D_main_bss_80142040[b][a];
    }
    return D_main_bss_8013C460[a];
}

extern u8 D_main_bss_80142018[];
extern u8 D_main_bss_801483D0[][16];
void setChannelByteParamAlt(u8 a, u8 b, u8 v) {
    if (b != 0xFF) {
        D_main_bss_801483D0[b][a] = v;
        return;
    }
    D_main_bss_80142018[a] = v;
}

extern u8 D_main_bss_80142018[];
extern u8 D_main_bss_801483D0[][16];
u8 getChannelByteParamAlt(u8 a, u8 b) {
    if (b != 0xFF) {
        return D_main_bss_801483D0[b][a];
    }
    return D_main_bss_80142018[a];
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", resetChannelStateRecord);

INCLUDE_ASM("asm/nonmatchings/main/832A0", getChannelControllerValue);

INCLUDE_ASM("asm/nonmatchings/main/832A0", initVoiceModulatorRecords);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateVoiceModulatorRecord);

u16 evaluateVoiceModulatorRecord(u8 *, u8 *);
u16 evaluateVoiceModulatorRecordZero(u8 *v) {
    return evaluateVoiceModulatorRecord(v, v + 0xC0);
}

u16 evaluateVoiceModulatorRecord(u8 *, u8 *);
u16 evaluateVoiceModulatorRecordOne(u8 *v) {
    return evaluateVoiceModulatorRecord(v, v + 0xD2);
}

u16 evaluateVoiceModulatorRecord(u8 *, u8 *);
u16 evaluateVoiceModulatorRecordTwo(u8 *v) {
    return evaluateVoiceModulatorRecord(v, v + 0xE4);
}

u16 evaluateVoiceModulatorRecord(u8 *, u8 *);
u16 evaluateVoiceModulatorRecordThree(u8 *v) {
    return evaluateVoiceModulatorRecord(v, v + 0xF6);
}

u16 evaluateVoiceModulatorRecord(u8 *, u8 *);
u16 evaluateVoiceModulatorRecordFour(u8 *v) {
    return evaluateVoiceModulatorRecord(v, v + 0x108);
}

u16 evaluateVoiceModulatorRecord(u8 *, u8 *);
u16 evaluateVoiceModulatorRecordFive(u8 *v) {
    return evaluateVoiceModulatorRecord(v, v + 0x11A);
}

u16 evaluateVoiceModulatorRecord(u8 *, u8 *);
u16 evaluateVoiceModulatorRecordSix(u8 *v) {
    return evaluateVoiceModulatorRecord(v, v + 0x12C);
}

u16 evaluateVoiceModulatorRecord(u8 *, u8 *);
u16 evaluateVoiceModulatorRecordSeven(u8 *v) {
    return evaluateVoiceModulatorRecord(v, v + 0x13E);
}

u16 evaluateVoiceModulatorRecord(u8 *, u8 *);
u16 evaluateVoiceModulatorRecordEight(u8 *v) {
    return evaluateVoiceModulatorRecord(v, v + 0x150);
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableInsertValue);

typedef struct { s32 a; s32 b; } TblE8a;
extern s32 D_main_bss_8013C450;
extern u8 D_main_bss_8013BC4C[];
extern TblE8a D_main_bss_8013BC40[];
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5SortedTableRemoveValue(s32 v) {
    s32 i;
    s32 j;
    s32 off;
    factor5MutexAcquire();
    for (i = 0; i < D_main_bss_8013C450; i++) {
        off = i * 8;
        if (*(u16 *)(D_main_bss_8013BC4C + off) == (v & 0xFFFF)) {
            break;
        }
    }
    if (i != D_main_bss_8013C450) {
        j = i + 1;
        if (j < D_main_bss_8013C450) {
            do {
                D_main_bss_8013BC40[j] = D_main_bss_8013BC40[j + 1];
                j++;
            } while (j < D_main_bss_8013C450);
        }
        D_main_bss_8013C450 = D_main_bss_8013C450 - 1;
        factor5MutexRelease();
        return 1;
    }
    factor5MutexRelease();
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableInsertTaggedValue);

typedef struct { s32 a; s32 b; } TblE8c;
extern s32 D_main_bss_8013AF08;
extern u8 D_main_bss_80148454[];
extern TblE8c D_main_bss_80148448[];
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5SortedTableRemoveTaggedValue(s32 v) {
    s32 i;
    s32 j;
    s32 off;
    factor5MutexAcquire();
    for (i = 0; i < D_main_bss_8013AF08; i++) {
        off = i * 8;
        if (*(u16 *)(D_main_bss_80148454 + off) == (v & 0xFFFF)) {
            break;
        }
    }
    if (i != D_main_bss_8013AF08) {
        j = i + 1;
        if (j < D_main_bss_8013AF08) {
            do {
                D_main_bss_80148448[j] = D_main_bss_80148448[j + 1];
                j++;
            } while (j < D_main_bss_8013AF08);
        }
        D_main_bss_8013AF08 = D_main_bss_8013AF08 - 1;
        factor5MutexRelease();
        return 1;
    }
    factor5MutexRelease();
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SecondSortedTableInsertValue);

typedef struct { s32 a; s32 b; } TblE8b;
extern s32 D_main_bss_8013AF0C;
extern u8 D_main_bss_80148C6C[];
extern TblE8b D_main_bss_80148C60[];
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5SecondSortedTableRemoveValue(s32 v) {
    s32 i;
    s32 j;
    s32 off;
    factor5MutexAcquire();
    for (i = 0; i < D_main_bss_8013AF0C; i++) {
        off = i * 8;
        if (*(u16 *)(D_main_bss_80148C6C + off) == (v & 0xFFFF)) {
            break;
        }
    }
    if (i != D_main_bss_8013AF0C) {
        j = i + 1;
        if (j < D_main_bss_8013AF0C) {
            do {
                D_main_bss_80148C60[j] = D_main_bss_80148C60[j + 1];
                j++;
            } while (j < D_main_bss_8013AF0C);
        }
        D_main_bss_8013AF0C = D_main_bss_8013AF0C - 1;
        factor5MutexRelease();
        return 1;
    }
    factor5MutexRelease();
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableInsertWidePair);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableRemoveWidePair);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableInsertVoiceRecord);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableRemoveVoiceRecord);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5BucketedTableInsertEntry);

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5BucketedTableRemoveEntry);

s32 binarySearchWithComparator(s32 arg0, u8 *base, s32 n, s32 size, s32 (*cmp)(s32, u8 *)) {
    s32 lo, hi, mid, r;
    u8 *p;
    if (n != 0) {
        lo = 1;
        hi = n;
        do {
            mid = (lo + hi) >> 1;
            p = base + size * (mid - 1);
            r = cmp(arg0, p);
            if (r == 0) {
                return (s32)p;
            }
            if (r < 0) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } while (hi >= lo);
    }
    return 0;
}

s32 func_main_80085CD8(u8 *a, u8 *b) {
    return *(u16 *)(a + 4) - *(u16 *)(b + 4);
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5BucketedTableLookupValue);

s32 compareHalfwordAtOffset8(u8 *a, u8 *b) {
    return *(u16 *)(a + 8) - *(u16 *)(b + 8);
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableLookupWidePairRecord);

s32 compareHalfwordAtOffset4_v2(u8 *a, u8 *b) {
    return *(u16 *)(a + 4) - *(u16 *)(b + 4);
}

extern s32 D_main_bss_8013AF0C;
extern u8 D_main_bss_8013AC58[];
extern s16 D_main_bss_8013AC5C;
extern u8 *D_main_bss_8013AC60;
extern u8 D_main_bss_80148C68[];
s32 compareHalfwordAtOffset4_v2(u8 *a, u8 *b);
static __inline__ u8 *bsrchLV2(u8 *key, u8 *base, s32 n, s32 size, s32 (*cmp)(u8 *, u8 *)) {
    s32 lo, hi, mid, r;
    u8 *p;
    if (n != 0) {
        lo = 1;
        hi = n;
        do {
            mid = (lo + hi) >> 1;
            p = base + size * (mid - 1);
            r = cmp(key, p);
            if (r == 0) {
                return p;
            }
            if (r < 0) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } while (hi >= lo);
    }
    return 0;
}
s32 factor5SecondSortedTableLookupValue(s16 key) {
    u8 *p;
    D_main_bss_8013AC5C = key;
    p = bsrchLV2(D_main_bss_8013AC58, D_main_bss_80148C68, D_main_bss_8013AF0C, 8, compareHalfwordAtOffset4_v2);
    D_main_bss_8013AC60 = p;
    if (p != 0) {
        return *(s32 *)p;
    }
    return 0;
}

extern s32 D_main_bss_8013C450;
extern u8 D_main_bss_8013AC68[];
extern s16 D_main_bss_8013AC6C;
extern u8 *D_main_bss_8013AC70;
extern u8 D_main_bss_8013BC48[];
s32 compareHalfwordAtOffset4_v2(u8 *a, u8 *b);
static __inline__ u8 *bsrchLV1(u8 *key, u8 *base, s32 n, s32 size, s32 (*cmp)(u8 *, u8 *)) {
    s32 lo, hi, mid, r;
    u8 *p;
    if (n != 0) {
        lo = 1;
        hi = n;
        do {
            mid = (lo + hi) >> 1;
            p = base + size * (mid - 1);
            r = cmp(key, p);
            if (r == 0) {
                return p;
            }
            if (r < 0) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } while (hi >= lo);
    }
    return 0;
}
s32 factor5SortedTableLookupValue(s16 key) {
    u8 *p;
    D_main_bss_8013AC6C = key;
    p = bsrchLV1(D_main_bss_8013AC68, D_main_bss_8013BC48, D_main_bss_8013C450, 8, compareHalfwordAtOffset4_v2);
    D_main_bss_8013AC70 = p;
    if (p != 0) {
        return *(s32 *)p;
    }
    return 0;
}

s32 compareHalfwordAtOffset4_v3(u8 *a, u8 *b) {
    return *(u16 *)(a + 4) - *(u16 *)(b + 4);
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", factor5SortedTableLookupTaggedValue);

s32 cmpU16ByValue(u8 *a, u8 *b) {
    return *(u16 *)(a + 0) - *(u16 *)(b + 0);
}

extern u16 D_main_bss_8013AC90;
extern u8 D_main_bss_8013CC80[];
extern s32 D_main_bss_80140800;
s32 cmpU16ByValue(u8 *a, u8 *b);
static __inline__ u8 *bsrch(u8 *key, u8 *base, s32 n, s32 size, s32 (*cmp)(u8 *, u8 *)) {
    s32 lo, hi, mid, r;
    u8 *p;
    if (n != 0) {
        lo = 1;
        hi = n;
        do {
            mid = (lo + hi) >> 1;
            p = base + size * (mid - 1);
            r = cmp(key, p);
            if (r == 0) {
                return p;
            }
            if (r < 0) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        } while (hi >= lo);
    }
    return 0;
}
u8 *musyxSortedInsertByU16(s16 key) {
    D_main_bss_8013AC90 = key;
    return bsrch((u8 *)&D_main_bss_8013AC90, D_main_bss_8013CC80, D_main_bss_80140800, 0xC, cmpU16ByValue);
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", freeSynthVoiceFromActiveList);

INCLUDE_ASM("asm/nonmatchings/main/832A0", allocVoiceHandleNode);

INCLUDE_ASM("asm/nonmatchings/main/832A0", resolveVoiceSlotByHandle);

INCLUDE_ASM("asm/nonmatchings/main/832A0", allocateSynthVoice);

s32 allocateSynthVoice(u8, u8, u16, s32);
void freeSynthVoiceFromActiveList();
s32 isAudioSlotActive(s32);
void stopVoiceMarkRetrigger(s32);
extern u8 D_main_8013D880[];
extern u8 D_main_bss_8013D8AE[];
extern s32 D_main_bss_8013D8E4[];
extern u8 D_main_bss_8013D939[];
s32 stopVoiceByKey(u8 key) {
    s32 v = allocateSynthVoice(key, 0xFF, 0xFFFF, 1);
    s32 off;
    if (v != -1) {
        off = (v * 0x5F) << 2;
        D_main_bss_8013D939[off] = 1;
        freeSynthVoiceFromActiveList(off + (s32)D_main_8013D880);
        *(s32 *)((s32)D_main_bss_8013D8E4 + off) = -1;
        if ((u8)isAudioSlotActive(v)) {
            stopVoiceMarkRetrigger(v);
        }
        *(s32 *)((s32)D_main_8013D880 + off) = 0;
        D_main_bss_8013D8AE[off] = 0;
    }
    return v;
}

extern u8 D_main_bss_8013D939[];
s32 isAudioSlotActive(s32);
void stopVoiceMarkRetrigger(s32);
void silenceVoiceSlot(s32 i) {
    if (i != -1) {
        if ((u8)isAudioSlotActive(i)) {
            stopVoiceMarkRetrigger(i);
        }
        D_main_bss_8013D939[i * 0x17C] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", computeVoiceGlidePitch);

extern u8 *D_main_bss_8013AF00;
extern u32 D_main_bss_8013D8A4[];
extern s32 D_main_bss_8013D8E4[];
extern u16 D_main_bss_8013D93E[];
static __inline__ u8 *findVoiceNodeInlQ(u32 h) {
    u8 *n = D_main_bss_8013AF00;
    if (n != 0) {
        do {
            if (*(u32 *)(n + 8) == h) {
                return n;
            }
            if (h < *(u32 *)(n + 8)) {
                return 0;
            }
            n = *(u8 **)n;
        } while (n != 0);
    }
    return 0;
}
u16 queryVoicePlayPositionByHandle(u32 h) {
    s32 id;
    u8 *r;
    s32 off;
    if (h != -1 && (r = findVoiceNodeInlQ(h)) != 0) {
        id = *(s32 *)(r + 0xC);
    } else {
        id = -1;
    }
    if (id != -1) {
        off = (id & 0xFF) * 0x17C;
        if (*(u32 *)((s32)D_main_bss_8013D8E4 + off) == id && !(*(u32 *)((s32)D_main_bss_8013D8A4 + off) & 2)) {
            return *(u16 *)((s32)D_main_bss_8013D93E + off);
        }
        return 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", findActiveVoiceByKeyPair);

INCLUDE_ASM("asm/nonmatchings/main/832A0", findVoiceForNote);

INCLUDE_ASM("asm/nonmatchings/main/832A0", startNoteOnVoice);

INCLUDE_ASM("asm/nonmatchings/main/832A0", applyNoteEventToGroup);

INCLUDE_ASM("asm/nonmatchings/main/832A0", dispatchSequencerNoteEvent);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxNoteEventLockedDispatch);

INCLUDE_ASM("asm/nonmatchings/main/832A0", bsearchFactor5TableByU16Key);

INCLUDE_ASM("asm/nonmatchings/main/832A0", validateVoiceHandle);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxSetSequenceParamLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxQuerySequenceLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setVoiceParamByHandle);

extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 setVoiceParamByHandle(s32, u8);
s32 setVoiceParamByHandleLocked(s32 h, u8 v) {
    s32 r = -1;
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        r = setVoiceParamByHandle(h, v);
        factor5MutexRelease();
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", applyVoiceCmdByHandle);

extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 applyVoiceCmdByHandle(s32, u8);
s32 applyVoiceCmdByHandleLocked(s32 h, u8 v) {
    s32 r = -1;
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        r = applyVoiceCmdByHandle(h, v);
        factor5MutexRelease();
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoiceKeyTransposeAcrossChain);

extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 spreadVoiceKeyTransposeAcrossChain(s32, u16);
s32 spreadVoiceKeyTransposeLocked(s32 h, u16 v) {
    s32 r = -1;
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        r = spreadVoiceKeyTransposeAcrossChain(h, v);
        factor5MutexRelease();
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoicePanVolumeAcrossChain);

extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 spreadVoicePanVolumeAcrossChain(s32, u16);
s32 safeLookup3DSoundEntry(s32 h, u16 v) {
    s32 r = -1;
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        r = spreadVoicePanVolumeAcrossChain(h, v);
        factor5MutexRelease();
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoiceParamPairLocked);

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoiceByteParamAcrossChain);

extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 spreadVoiceByteParamAcrossChain(s32, u8);
s32 spreadVoiceByteParamLocked(s32 h, u8 v) {
    s32 r = -1;
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        r = spreadVoiceByteParamAcrossChain(h, v);
        factor5MutexRelease();
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", spreadVoiceParamLockedVariant);

INCLUDE_ASM("asm/nonmatchings/main/832A0", flagVoiceChainForStop);

extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 flagVoiceChainForStop(s32);
s32 stopVoiceByHandleLocked(s32 h) {
    s32 r = -1;
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        r = flagVoiceChainForStop(h);
        factor5MutexRelease();
    }
    return r;
}

void shiftChannelStreamLeft8(u32 *p) {
    *p <<= 8;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", computeChannelTempoStepFromTable);

INCLUDE_ASM("asm/nonmatchings/main/832A0", computeChannelWaitDuration);

u8 computeChannelWaitDuration();
s32 soundMacroOpWaitTicks(u8 *ch, u8 *cmd) {
    cmd[5] = 1;
    return computeChannelWaitDuration();
}

void freeSynthVoiceFromActiveList();
s32 soundMacroOpStopVoice(u8 *ch) {
    *(s32 *)ch = 0;
    ch[0x2E] = 0;
    freeSynthVoiceFromActiveList();
    *(s32 *)(ch + 0x64) = -1;
    return 1;
}

void freeSynthVoiceFromActiveList();
s32 soundMacroOpReturnFromGosub(u8 *ch, u8 *cmd) {
    if (cmd[2] == 0 || *(s32 *)(ch + 8) == 0) {
        *(s32 *)ch = 0;
        ch[0x2E] = 0;
        freeSynthVoiceFromActiveList(ch);
        *(s32 *)(ch + 0x64) = -1;
        return 1;
    }
    *(s32 *)ch = *(s32 *)(ch + 8);
    *(s32 *)(ch + 4) = *(s32 *)(ch + 0xC);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpGosubLoopCounterFiftyFour);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpGosubLoopCounterThirty);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpGosubModulatorLoop);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpGosubRandomLoop);

s32 factor5BucketedTableLookupValue(u16);
void freeSynthVoiceFromActiveList();
s32 soundMacroOpGosub(u8 *ch, u16 *cmd) {
    s32 v = factor5BucketedTableLookupValue(cmd[0]);
    s32 old;
    if (v != 0) {
        old = *(s32 *)ch;
        *(s32 *)ch = v;
        *(s32 *)(ch + 8) = old;
        *(s32 *)(ch + 0xC) = *(s32 *)(ch + 4);
        *(s32 *)(ch + 4) = v + cmd[3] * 8;
        return 0;
    }
    *(s32 *)ch = 0;
    ch[0x2E] = 0;
    freeSynthVoiceFromActiveList(ch);
    *(s32 *)(ch + 0x64) = -1;
    return 1;
}

s32 factor5BucketedTableLookupValue(u16);
s32 soundMacroOpGosubAltReturnFrame(u8 *ch, u16 *cmd) {
    s32 v = factor5BucketedTableLookupValue(cmd[0]);
    if (v != 0) {
        *(s32 *)(ch + 0x1C) = v;
        *(s32 *)(ch + 0x20) = v + cmd[3] * 8;
    }
    return 0;
}

s32 clearChannelFieldsAt1Cand20(u8 *ch) {
    *(s32 *)(ch + 0x20) = 0;
    *(s32 *)(ch + 0x1C) = 0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpLoopRandomCount);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpKeyOnNote);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpKeyOffByNote);

s32 soundMacroOpAddPitchBend(u8 *ch, s16 *cmd) {
    s32 v = *(u16 *)(ch + 0x28) + *cmd;
    if (v < 0) {
        *(s32 *)(ch + 0x28) = 0;
    } else if (v > 0xFFFF) {
        *(s32 *)(ch + 0x28) = 0xFFFF0000;
    } else {
        *(s32 *)(ch + 0x28) = v << 16;
    }
    return 0;
}

s32 setChannelProgHalfwordAt28(u8 *ch, u16 *cmd) {
    *(u32 *)(ch + 0x28) = *cmd << 16;
    return 0;
}

s32 soundMacroOpSetPitchBendGlide(u8 *ch, u8 *cmd) {
    u32 d = *(u32 *)(cmd + 4);
    if (d != 0) {
        *(s16 *)(ch + 0x2C) = (*(u32 *)(ch + 0x28) >> 8) / d;
    } else {
        *(s16 *)(ch + 0x2C) = 0;
    }
    return 0;
}

s32 soundMacroOpAddKeyByte(u8 *ch, u16 *cmd) {
    u16 c = *cmd;
    s16 k = ch[0x2E] + c;
    if (k < 0) {
        ch[0x2E] = 0;
    } else if (k >= 0x100) {
        ch[0x2E] = 0xFF;
    } else {
        ch[0x2E] = k;
    }
    return 0;
}

s32 setChannelProgByteAt2E(u8 *ch, u32 *cmd) {
    ch[0x2E] = *cmd >> 8;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpStoreGlobalRegister);

s32 setChannelKeyOffsetAt6E(u8 *ch, u16 *cmd) {
    ch[0x6E] = *cmd;
    ch[0x6F] = *(u32 *)cmd >> 8;
    return 0;
}

u8 computeChannelWaitDuration();
s32 soundMacroOpPortamentoStartWait(u8 *ch, s32 *out) {
    *(s32 *)(ch + 0x70) <<= 16;
    *out = 4;
    return computeChannelWaitDuration();
}

s32 scaleFixedPointByRatioA(u16);
s32 scaleFixedPointByRatioB(u16);
s32 computeChannelPitchSweepStep(u8 *a) {
    s32 r;
    if (*(s8 *)(a + 0xBC) != 0) {
        if (*(s8 *)(a + 0xBC) > 0) {
            r = (((scaleFixedPointByRatioA(*(u16 *)(a + 0x72)) & 0xFFFF) - *(s32 *)(a + 0x70)) * *(s8 *)(a + 0xBC)) / 100;
        } else {
            r = ((*(s32 *)(a + 0x70) - (scaleFixedPointByRatioB(*(u16 *)(a + 0x72)) & 0xFFFF)) * *(s8 *)(a + 0xBC)) / 100;
        }
    } else {
        r = 0;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpStartNoteAbsoluteSweep);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpStartNoteRelativeSweep);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpStartNoteTransposedSweep);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpPlaySampleKeymap);

void musyxStartVoiceRelease(u8, u8);
s32 soundMacroOpKeyOff(u8 *ch) {
    musyxStartVoiceRelease(ch[0x67], 1);
    return 0;
}

s32 setChannelFlag24Bit80(u8 *ch) {
    *(u32 *)(ch + 0x24) |= 0x80;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpSetPanSweep);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpSetProgramTableValue);

s32 divideByMixerBaseFrequency(u16);
s32 soundMacroOpStartPitchEnvelope(u8 *ch, u32 *cmd) {
    *(u32 *)(ch + 0x24) |= 0x100;
    *(s32 *)(ch + 0x70) = divideByMixerBaseFrequency(*cmd >> 8) << 16;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxSetVoiceAdsrFromTable);

s32 divideByMixerBaseFrequency(u16);
u8 computeChannelWaitDuration();
s32 soundMacroOpStartVibrato(u8 *ch, u32 *cmd, s32 i) {
    u8 *p = (u8 *)(i * 4 + (s32)ch);
    u8 *q;
    u8 b;
    *(s32 *)(p + 0x44) = 0;
    q = ch + i;
    b = *cmd >> 8;
    q[0x4C] = b;
    q[0xAC] = b;
    *(s32 *)(p + 0x84) = divideByMixerBaseFrequency(*cmd >> 16) << 16;
    *cmd = 0;
    return computeChannelWaitDuration(ch, cmd);
}

s32 soundMacroOpSetVolumeRamp(u8 *ch, u8 *cmd) {
    u16 t;
    s32 a;
    s32 b;
    *(u32 *)(ch + 0x24) |= 0x8000;
    t = *(u16 *)cmd;
    *(s32 *)(ch + 0xA4) = t << 8;
    a = cmd[2] << 16;
    b = (s8)cmd[7] << 16;
    *(s32 *)(ch + 0x38) = a;
    *(s32 *)(ch + 0xA8) = b + a;
    if (*(s32 *)(ch + 0xA4) != 0) {
        *(u32 *)(ch + 0x3C) = (u32)b / t;
    } else {
        *(u32 *)(ch + 0x3C) = b;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroOpSetPitchRelativeToNote);

INCLUDE_ASM("asm/nonmatchings/main/832A0", evaluateSoundMacroCurveTable);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroSetVoiceVolume);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroSetupVolumeRamp);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroPlayRandomKeyNote);

s32 soundMacroSetFlagBitVibrato(u8 *ch) {
    *(u32 *)(ch + 0x24) |= 0x20000;
    return 0;
}

s32 soundMacroSetFlagBitTremolo(u8 *ch) {
    *(u32 *)(ch + 0x24) |= 0x40000;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroPushEffectEvent);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler40);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler41);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler42);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler43);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler44);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler45);

INCLUDE_ASM("asm/nonmatchings/main/832A0", seqCmdHandler46);

INCLUDE_ASM("asm/nonmatchings/main/832A0", refreshVoicePlaybackRate);

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroSetPitchTarget);

INCLUDE_ASM("asm/nonmatchings/main/832A0", tickAudioChannel);

INCLUDE_ASM("asm/nonmatchings/main/832A0", tickAllAudioChannels);

extern s32 D_main_bss_8013ACC8;
extern s32 D_main_bss_8013B03C;
extern s32 D_main_bss_8013C448;
extern s32 D_main_bss_8013C454;
extern s32 D_main_bss_8013C458;
extern s32 D_main_bss_80142038;
extern s32 D_main_bss_801440C0;
void tickAllAudioChannels(s32);
void tickAudioSequencerFrame(void) {
    D_main_bss_8013C448 = 0;
    D_main_bss_8013C458 = 0;
    D_main_bss_8013B03C = 0;
    D_main_bss_8013C454 = 0;
    if (D_main_bss_80142038 != 0) {
        D_main_bss_8013ACC8 = (D_main_bss_80142038 * 0x7D00) / D_main_bss_801440C0 * 8;
        tickAllAudioChannels(D_main_bss_80142038);
    }
}

extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
void tickActiveSongs(void);
void tickAndReap3DAudioVoices(void);
void stopAllSynthVoices(s32);
void tickMusyXIfActive(void) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        tickActiveSongs();
        tickAndReap3DAudioVoices();
        stopAllSynthVoices(0);
        factor5MutexRelease();
    }
}

void freeSynthVoiceFromActiveList();
void releaseSynthVoice(u8 *ch) {
    freeSynthVoiceFromActiveList();
    *(s32 *)(ch + 0x64) = -1;
    *(s32 *)ch = 0;
    ch[0x2E] = 0;
    *(s32 *)(ch + 0x28) = 0;
    *(u32 *)(ch + 0x24) &= ~3;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", stopVoicesByHandle);

INCLUDE_ASM("asm/nonmatchings/main/832A0", stopAllSynthVoices);

extern u8 D_main_bss_80148C58[];
u8 getMusyXChannelSlotByte(s32 i) {
    return D_main_bss_80148C58[i & 0xF];
}

extern u8 D_main_bss_80148C58[];
void setMusyXChannelSlotByte(s32 i, u8 v) {
    D_main_bss_80148C58[i & 0xF] = v;
}

extern u8 D_main_bss_801483C8;
void setMusyXVoiceTickGate(u8 arg0) {
    D_main_bss_801483C8 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", dispatchAudioCommand);

extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
void dispatchAudioCommand(u8, u16, u8, s32, s32);
void playSimpleAudioCmd(u8 a, u16 b, u8 c) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        dispatchAudioCommand(a, b, c, 0, 0);
        factor5MutexRelease();
    }
}

extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
void dispatchAudioCommand(u8, u16, u8, s32, s32);
void applyMusicOrSfxVolume(u8 a, u16 b, u8 music, u8 sfx) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        if (music) {
            dispatchAudioCommand(a, b, 0x15, 0, 0);
        }
        if (sfx) {
            dispatchAudioCommand(a, b, 0x16, 0, 0);
        }
        factor5MutexRelease();
    }
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", isAudioFaderRampActive);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setupAudioFaderRamp);

extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
void setupAudioFaderRamp(u8, u16, u8);
void setAudioFaderRampLocked(u8 a, u16 b, u8 c) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        setupAudioFaderRamp(a, b, c);
        factor5MutexRelease();
    }
}

extern u8 gMusyXActiveFlag;
extern u8 D_main_bss_80141B2C[][0x28];
void setAudioFaderState(u8 i, u8 v) {
    if (gMusyXActiveFlag != 0) {
        D_main_bss_80141B2C[i][0] = v;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", anyAudioSlotActive);

INCLUDE_ASM("asm/nonmatchings/main/832A0", resetMusyXEngineState);

extern s32 D_main_bss_8013AF08;
extern s32 D_main_bss_8013AF0C;
extern s32 D_main_bss_8013C44C;
extern s32 D_main_bss_8013C450;
extern s16 D_main_bss_8013C480[][2];
extern s32 D_main_bss_80148C50;
void clearMusyXSequencerState(void) {
    s32 i;
    D_main_bss_8013C44C = 0;
    D_main_bss_8013AF0C = 0;
    D_main_bss_8013C450 = 0;
    D_main_bss_8013AF08 = 0;
    D_main_bss_80148C50 = 0;
    for (i = 0; i < 0x200; i++) {
        D_main_bss_8013C480[i][0] = 0;
        D_main_bss_8013C480[i][1] = 0;
    }
}

extern u8 gMusyXActiveFlag;
extern u8 D_main_bss_80140808[];
u8 *getMusyXStateTableIfActive(void) {
    if (gMusyXActiveFlag != 0) {
        return D_main_bss_80140808;
    }
    return NULL;
}

extern u8 gMusyXActiveFlag;
void tickAudioBufferUpdate(void);
void syncMusyXIfActive(void) {
    if (gMusyXActiveFlag != 0) {
        tickAudioBufferUpdate();
    }
}

extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
void freeAudioScratchBuffer(void);
void runMusyXTaskLocked(void) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        freeAudioScratchBuffer();
        factor5MutexRelease();
    }
}

void resetSongSubsystemCounter(void);
void initSongSequencerPools(void);
void resetMusyXEngineState(s32);
void clearStreamedVoiceFlags(void);
void reset3DAudioLists(void);
extern s8 D_main_bss_80148C67;
extern s32 D_main_bss_8013AF08;
extern s32 D_main_bss_8013AF0C;
extern s32 D_main_bss_8013C44C;
extern s32 D_main_bss_8013C450;
extern s16 D_main_bss_8013C480[][2];
extern s32 D_main_bss_80148C50;
extern volatile u8 D_main_bss_8013ACF4;
extern u8 gMusyXActiveFlag;
s32 initMusyXEngine(s32 arg0) {
    s32 i;
    s8 *p;
    resetSongSubsystemCounter();
    i = 0xF;
    p = &D_main_bss_80148C67;
    do {
        *p = 0;
        i--;
        p--;
    } while (i >= 0);
    D_main_bss_8013C44C = 0;
    D_main_bss_8013AF0C = 0;
    D_main_bss_8013C450 = 0;
    D_main_bss_8013AF08 = 0;
    D_main_bss_80148C50 = 0;
    for (i = 0; i < 0x200; i++) {
        D_main_bss_8013C480[i][0] = 0;
        D_main_bss_8013C480[i][1] = 0;
    }
    initSongSequencerPools();
    D_main_bss_8013ACF4 = 0;
    resetMusyXEngineState(arg0);
    clearStreamedVoiceFlags();
    reset3DAudioLists();
    gMusyXActiveFlag = 1;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", setDisplayMode);

INCLUDE_ASM("asm/nonmatchings/main/832A0", reapplyDisplayMode);

extern u8 gMusyXActiveFlag;
extern void * volatile D_main_bss_8013AF14;
void shutdownAudioEngine(void);
void noopHandler_80099C44(void);
void rs_free(void *);
void shutdownMusyXEngine(void) {
    if (gMusyXActiveFlag != 0) {
        shutdownAudioEngine();
        if (D_main_bss_8013AF14 != NULL) {
            rs_free(D_main_bss_8013AF14);
        }
        noopHandler_80099C44();
        gMusyXActiveFlag = 0;
    }
}

extern u8 gMusyXActiveFlag;
extern void * volatile D_main_bss_8013AF14;
void waitForMusyXAudioTaskDone(void);
void noopHandler_80099C44(void);
void rs_free(void *);
void musyxNoopStub(void) {
    if (gMusyXActiveFlag != 0) {
        waitForMusyXAudioTaskDone();
        if (D_main_bss_8013AF14 != NULL) {
            rs_free(D_main_bss_8013AF14);
        }
        noopHandler_80099C44();
        gMusyXActiveFlag = 0;
    }
}

extern u8 gMusyXActiveFlag;
u8 isMusyXActive(void) {
    return gMusyXActiveFlag;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", serviceAudioOutputBuffers);

INCLUDE_ASM("asm/nonmatchings/main/832A0", runAiAudioStreamPlaybackLoop);

INCLUDE_ASM("asm/nonmatchings/main/832A0", buildSongTempoSchedule);

INCLUDE_ASM("asm/nonmatchings/main/832A0", allocateSongChannelArray);

INCLUDE_ASM("asm/nonmatchings/main/832A0", setupSongRenderBuffers);

INCLUDE_ASM("asm/nonmatchings/main/832A0", advanceVolumeFadeEnvelope);

INCLUDE_ASM("asm/nonmatchings/main/832A0", buildSongDecodeBufferRing);

INCLUDE_ASM("asm/nonmatchings/main/832A0", acquireSampleStreamBlock);

INCLUDE_ASM("asm/nonmatchings/main/832A0", initSampleStreamBlockCache);

INCLUDE_ASM("asm/nonmatchings/main/832A0", moveSampleBlockToFront);

INCLUDE_ASM("asm/nonmatchings/main/832A0", recycleSampleStreamBlock);

INCLUDE_ASM("asm/nonmatchings/main/832A0", fillSampleStreamRange);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxRenderVoiceSamples);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxKeyOnVoice);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxMixActiveVoices);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxBuildVoiceCommandList);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxSynthFrame);

INCLUDE_ASM("asm/nonmatchings/main/832A0", initN64RspMixer);

INCLUDE_ASM("asm/nonmatchings/main/832A0", initAudioSubsystem);

INCLUDE_ASM("asm/nonmatchings/main/832A0", reapplyAudioConfig);

INCLUDE_ASM("asm/nonmatchings/main/832A0", shutdownAudioEngine);

INCLUDE_ASM("asm/nonmatchings/main/832A0", waitForMusyXAudioTaskDone);

extern OSMesgQueue D_main_bss_80149990;
extern OSMesg D_main_bss_801499A8;
void initFactor5Mutex(void) {
    osCreateMesgQueue(&D_main_bss_80149990, &D_main_bss_801499A8, 1);
    osSendMesg(&D_main_bss_80149990, NULL, OS_MESG_NOBLOCK);
}

extern s32 D_main_800A1780;
extern OSMesgQueue D_main_bss_80149990;
void factor5MutexAcquire(void) {
    if (D_main_800A1780 == 0) {
        osRecvMesg(&D_main_bss_80149990, NULL, OS_MESG_BLOCK);
    }
    D_main_800A1780++;
}

extern s32 D_main_800A1780;
extern OSMesgQueue D_main_bss_80149990;
void factor5MutexRelease(void) {
    if (D_main_800A1780 > 0) {
        if (--D_main_800A1780 == 0) {
            osSendMesg(&D_main_bss_80149990, NULL, OS_MESG_NOBLOCK);
        }
    }
}

extern OSMesgQueue D_main_bss_80149990;
void factor5QueueBlock(void) {
    osRecvMesg(&D_main_bss_80149990, NULL, OS_MESG_BLOCK);
}

extern OSMesgQueue D_main_bss_80149990;
void factor5QueueSignal(void) {
    osSendMesg(&D_main_bss_80149990, NULL, OS_MESG_NOBLOCK);
}

extern u8 *D_main_bss_801496F8;
s32 isAudioSlotActive(s32 i) {
    return D_main_bss_801496F8[i * 0x88] != 0;
}

s32 audioStubReturnZero(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxInitVoiceFromSample);

extern u8 *D_main_bss_801496F8;
void msvrImpl(s32 i, u8 flag) __asm__("musyxStartVoiceRelease");
void msvrImpl(s32 i, u8 flag) {
    s32 b = (s32)D_main_bss_801496F8;
    u8 *v = (u8 *)(i * 0x88 + b);
    *(u16 *)(v + 0x30) = 0x14;
    if (flag) {
        v[0x6C] = 3;
        *(s32 *)(v + 0x64) = 0;
        *(s32 *)(v + 0x60) = 0;
        *(f32 *)(v + 0x68) = *(f32 *)(v + 0x5C);
        *(u16 *)(v + 0x58) = *(u16 *)(v + 0x30);
    }
}

extern u8 *D_main_bss_801496F8;
extern f64 D_main_8003DE58;
void musyxStoreVoiceAdsrParams(s32 i, u16 *p) {
    s32 b = (s32)D_main_bss_801496F8;
    u8 *v = (u8 *)(i * 0x88 + b);
    *(u16 *)(v + 0x28) = p[0];
    *(u16 *)(v + 0x2A) = p[1];
    *(f32 *)(v + 0x2C) = (f32)p[2] / D_main_8003DE58;
    *(u16 *)(v + 0x30) = p[3];
}

extern u8 *D_main_bss_801496F8;
extern f32 D_main_8003DE60;
void musyxTriggerVoiceAttack(u16 i) {
    u8 *v = D_main_bss_801496F8 + i * 0x88;
    f32 f = D_main_8003DE60;
    u16 h = *(u16 *)(v + 0x28);
    v[0x6C] = 0;
    *(s32 *)(v + 0x60) = 0;
    *(s32 *)(v + 0x68) = 0;
    *(s32 *)(v + 0x5C) = 0;
    *(f32 *)(v + 0x64) = f;
    v[0] = 1;
    *(u16 *)(v + 0x58) = h;
}

extern u8 *D_main_bss_801496F8;
void musyxStopVoice(s32 i) {
    D_main_bss_801496F8[i * 0x88 + 1] = 0;
}

void noopHandler_80092388(void) {
}

extern u8 *D_main_bss_801496F8;
void musyxSetVoicePitchBend(s32 i, u16 b) {
    if (b <= 0x2000) {
        *(u16 *)(D_main_bss_801496F8 + i * 0x88 + 4) = b;
        return;
    }
    *(u16 *)(D_main_bss_801496F8 + i * 0x88 + 4) = 0x2000;
}

extern u8 *D_main_bss_801496F8;
void computeVoiceVolumePanCoefficients(void *, void *, s32, s32, s32, void *, s32, void *);
void setVoiceModulationParams(s32 i, s32 a, s32 b, s32 c, s32 d) {
    u8 *v = D_main_bss_801496F8 + i * 0x88;
    computeVoiceVolumePanCoefficients(v + 0x46, v + 0x44, a, b, c, v + 0x48, d, v + 0x4A);
}

extern u8 *D_main_bss_801496F8;
void stopVoiceMarkRetrigger(s32 i) {
    if (D_main_bss_801496F8[i * 0x88] != 0) {
        D_main_bss_801496F8[i * 0x88] = 0;
        D_main_bss_801496F8[i * 0x88 + 0x85] = 1;
    }
}

extern u8 *D_main_bss_801496F8;
void beginVoiceFadeRelease(s32 i) {
    s32 b = (s32)D_main_bss_801496F8;
    u8 *v = (u8 *)(i * 0x88 + b);
    if (v[0] != 0) {
        *(u16 *)(v + 0x30) = 0x14;
        if (v[1] != 0) {
            v[1] = 0;
            return;
        }
        v[0x6C] = 3;
        *(s32 *)(v + 0x64) = 0;
        *(s32 *)(v + 0x60) = 0;
        *(f32 *)(v + 0x68) = *(f32 *)(v + 0x5C);
        *(u16 *)(v + 0x58) = *(u16 *)(v + 0x30);
    }
}

extern u8 *D_main_bss_801496F8;
void deactivateVoice(s32 i) {
    D_main_bss_801496F8[i * 0x88] = 0;
}

void buildSongTempoSchedule(void);
void tickAudioBufferUpdate(void) {
    buildSongTempoSchedule();
}
