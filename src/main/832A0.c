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

extern u8 gCcTblG[][0x86] __asm__("D_main_bss_80140A10");
extern u8 gCcTrkTblG[][16][0x86] __asm__("D_main_bss_801440C8");
s32 getChannelControllerValue(u8 ctrl, u8 slot, u8 trk) {
    if (trk != 0xFF) {
        if (ctrl < 0x40) {
            return (gCcTrkTblG[trk][slot][ctrl & 0x1F] << 7) | gCcTrkTblG[trk][slot][(ctrl & 0x1F) + 0x20];
        }
        if (ctrl == 0x80 || ctrl == 0x81) {
            return gCcTrkTblG[trk][slot][(ctrl & 0xFE) + 1] | (gCcTrkTblG[trk][slot][ctrl & 0xFE] << 7);
        }
        if (ctrl < 0x46) {
            return (gCcTrkTblG[trk][slot][ctrl] >= 0x40) ? 0x3FFF : 0;
        }
        if (ctrl >= 0x60 && ctrl < 0x66) {
            return 0;
        }
        return gCcTrkTblG[trk][slot][ctrl] << 7;
    }
    if (ctrl < 0x40) {
        return (gCcTblG[slot][ctrl & 0x1F] << 7) | gCcTblG[slot][(ctrl & 0x1F) + 0x20];
    }
    if (ctrl == 0x80 || ctrl == 0x81) {
        return gCcTblG[slot][(ctrl & 0xFE) + 1] | (gCcTblG[slot][ctrl & 0xFE] << 7);
    }
    if (ctrl < 0x46) {
        return (gCcTblG[slot][ctrl] >= 0x40) ? 0x3FFF : 0;
    }
    if (ctrl >= 0x60 && ctrl < 0x66) {
        return 0;
    }
    return gCcTblG[slot][ctrl] << 7;
}

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

typedef struct { s32 a; s32 b; s32 c; } TblE12a;
extern s32 D_main_bss_8013C44C;
extern u8 D_main_bss_8013B050[];
extern s32 D_main_bss_8013B03C;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5SortedTableRemoveWidePair(s32 v) {
    s32 i;
    s32 j;
    s32 off;
    factor5MutexAcquire();
    for (i = 0; i < D_main_bss_8013C44C; i++) {
        off = i * 0xC;
        if (*(u16 *)(D_main_bss_8013B050 + off) == (v & 0xFFFF)) {
            break;
        }
    }
    if (i != D_main_bss_8013C44C) {
        j = i + 1;
        if (j < D_main_bss_8013C44C) {
            do {
                ((TblE12a *)&D_main_bss_8013B03C)[j] = ((TblE12a *)&D_main_bss_8013B03C)[j + 1];
                j++;
            } while (j < D_main_bss_8013C44C);
        }
        D_main_bss_8013C44C = D_main_bss_8013C44C - 1;
        factor5MutexRelease();
        return 1;
    }
    factor5MutexRelease();
    return 0;
}

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

extern s32 D_main_bss_8013AC20;
extern u32 D_main_bss_8013AC24;
extern u8 D_main_bss_8013AC28[];
extern u16 D_main_bss_8013AC2C;
extern u8 *D_main_bss_8013AC30;
extern s16 D_main_bss_8013C480[][2];
extern u8 D_main_bss_801420C0[];
s32 func_main_80085CD8(u8 *a, u8 *b);
static __inline__ u8 *bsrchLV4(u8 *key, u8 *base, s32 n, s32 size, s32 (*cmp)(u8 *, u8 *)) {
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
s32 factor5BucketedTableLookupValue(u16 h) {
    u32 v;
    s32 second;
    u8 *p;
    v = (u16)h >> 6;
    D_main_bss_8013AC24 = v;
    if ((u16)D_main_bss_8013C480[v][0] != 0) {
        second = (u16)D_main_bss_8013C480[v][1];
        D_main_bss_8013AC2C = h;
        D_main_bss_8013AC20 = second;
        p = bsrchLV4(D_main_bss_8013AC28, D_main_bss_801420C0 + second * 8, (u16)D_main_bss_8013C480[v][0], 8, func_main_80085CD8);
        D_main_bss_8013AC30 = p;
        if (p != 0) {
            return *(s32 *)p;
        }
    }
    return 0;
}

s32 compareHalfwordAtOffset8(u8 *a, u8 *b) {
    return *(u16 *)(a + 8) - *(u16 *)(b + 8);
}

extern s32 D_main_bss_8013C44C;
extern u8 D_main_bss_8013AC40[];
extern s16 D_main_bss_8013AC48;
extern u8 *D_main_bss_8013AC4C;
extern u8 *D_main_bss_8013AC50;
extern u8 D_main_bss_8013B048[];
s32 compareHalfwordAtOffset8(u8 *a, u8 *b);
static __inline__ u8 *bsrchLV5(u8 *key, u8 *base, s32 n, s32 size, s32 (*cmp)(u8 *, u8 *)) {
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
s32 factor5SortedTableLookupWidePairRecord(s16 key, u8 *out) {
    u8 *p;
    u8 *t;
    s32 w;
    D_main_bss_8013AC48 = key;
    p = bsrchLV5(D_main_bss_8013AC40, D_main_bss_8013B048, D_main_bss_8013C44C, 0xC, compareHalfwordAtOffset8);
    D_main_bss_8013AC4C = p;
    if (p != 0) {
        t = *(u8 **)p;
        *(s32 *)out = *(s32 *)t;
        *(s32 *)(out + 4) = *(s32 *)(p + 4);
        *(s32 *)(out + 8) = 0;
        *(s32 *)(out + 0x10) = *(s32 *)(t + 8);
        *(s32 *)(out + 0xC) = *(s32 *)(t + 4) & 0xFFFFFF;
        w = *(s32 *)(t + 0xC);
        D_main_bss_8013AC50 = t;
        *(s32 *)(out + 0x14) = w;
        *(u8 *)(out + 0x18) = *(u8 *)(t + 4);
        return 0;
    }
    return -1;
}

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

extern s32 D_main_bss_8013AF08;
extern u8 D_main_bss_8013AC78[];
extern s16 D_main_bss_8013AC7C;
extern u8 *D_main_bss_8013AC80;
extern u8 D_main_bss_80148450[];
s32 compareHalfwordAtOffset4_v3(u8 *a, u8 *b);
static __inline__ u8 *bsrchLV3(u8 *key, u8 *base, s32 n, s32 size, s32 (*cmp)(u8 *, u8 *)) {
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
s32 factor5SortedTableLookupTaggedValue(s16 key, u16 *out) {
    u8 *p;
    D_main_bss_8013AC7C = key;
    p = bsrchLV3(D_main_bss_8013AC78, D_main_bss_80148450, D_main_bss_8013AF08, 8, compareHalfwordAtOffset4_v3);
    D_main_bss_8013AC80 = p;
    if (p != 0) {
        *out = *(u16 *)(p + 6);
        return *(s32 *)D_main_bss_8013AC80;
    }
    return 0;
}

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

extern u32 D_main_bss_8013ACF8;
extern u8 *D_main_bss_8013AF00;
extern u8 *D_main_bss_8013AF04;
u32 allocVoiceHandleNode(u8 *v) {
    register u32 id asm("$7");
    u32 k;
    u32 n;
    register u8 *a2 asm("$6");
    register u8 *t0 asm("$8");
    register u8 *a1 asm("$5");
    u8 *t;
    register u32 ret asm("$2");
    do {
        n = D_main_bss_8013ACF8;
        D_main_bss_8013ACF8 = n + 1;
        id = n;
    } while (n == -1);
    a2 = D_main_bss_8013AF00;
    t0 = 0;
    while (a2 != 0) {
        k = *(u32 *)(a2 + 8);
        if (id < k) {
            break;
        }
        if (k == id) {
            do {
                n = D_main_bss_8013ACF8;
                D_main_bss_8013ACF8 = n + 1;
            } while (n == -1);
            id = n;
        }
        t0 = a2;
        a2 = *(u8 **)a2;
    }
    a1 = D_main_bss_8013AF04;
    ret = -1;
    if (a1 != 0) {
        t = *(u8 **)a1;
        D_main_bss_8013AF04 = t;
        if (t != 0) {
            *(s32 *)(t + 4) = 0;
        }
        if (t0 == 0) {
            D_main_bss_8013AF00 = a1;
            *(u8 **)(a1 + 4) = t0;
        } else {
            *(u8 **)t0 = a1;
            *(u8 **)(a1 + 4) = t0;
        }
        *(u8 **)a1 = a2;
        if (a2 != 0) {
            *(u8 **)(a2 + 4) = a1;
        }
        *(u32 *)(a1 + 8) = id;
        ret = id;
        *(s32 *)(a1 + 0xC) = *(s32 *)(v + 0x64);
        *(u8 **)(v + 0x18) = a1;
    }
    return ret;
}

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

s32 dispatchSequencerNoteEventK(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32) __asm__("dispatchSequencerNoteEvent");
extern u8 gMusyXActiveFlag;
extern u16 D_main_bss_8013AC90;
extern u8 D_main_bss_8013CC80[];
extern s32 D_main_bss_80140800;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 cmpU16ByValue(u8 *a, u8 *b);
s32 bsearchFactor5TableByU16Key(u16 key, u8 a, u8 b) {
    s32 ret = -1;
    s32 r7;
    u8 *p;
    u8 s5;
    u8 s6;
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        s5 = a;
        s6 = b;
        r7 = -1;
        D_main_bss_8013AC90 = key;
        p = bsrch((u8 *)&D_main_bss_8013AC90, D_main_bss_8013CC80, D_main_bss_80140800, 0xC, cmpU16ByValue);
        if (p != 0) {
            if (s5 == 0xFF) {
                s5 = p[6];
            }
            if (s6 == 0xFF) {
                s6 = p[7];
            }
            r7 = dispatchSequencerNoteEventK((*(u16 *)(p + 2) << 16) | (p[5] << 8) | p[4], p[8] | 0x80, s5, s6, 0xFF, 0xFF, 0, 0xFF, p[9], 0);
        }
        ret = r7;
        factor5MutexRelease();
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", validateVoiceHandle);

extern u8 gMusyXActiveFlag;
extern u16 D_main_bss_8013AC90;
extern u8 D_main_bss_8013CC80[];
extern s32 D_main_bss_80140800;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 cmpU16ByValue(u8 *a, u8 *b);
void musyxSetSequenceParamLocked(u16 key, s8 val) {
    u8 *p;
    u8 a0;
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        D_main_bss_8013AC90 = key;
        p = bsrch((u8 *)&D_main_bss_8013AC90, D_main_bss_8013CC80, D_main_bss_80140800, 0xC, cmpU16ByValue);
        a0 = val;
        if (p != 0) {
            if (a0 != 0xFE) {
                p[9] = val;
                setAudioFaderState(a0, 3);
            } else {
                p[9] = 0x1F;
            }
        }
        factor5MutexRelease();
    }
}

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

typedef struct VhNodeK { struct VhNodeK *next; s32 pad4; u32 h; s32 slot; } VhNodeK;
extern VhNodeK *gVhHeadK __asm__("D_main_bss_8013AF00");
typedef struct {
    s32 next;
    u8 pad4[0x10];
    u32 flags;
    u8 pad18[0x27];
    u8 trkA;
    u8 pad40[9];
    u8 trkB;
    u8 pad4A[0xA];
    s32 id;
    u8 pad58[0x124];
} ChanRecK;
extern ChanRecK gChanRecK[] __asm__("D_main_bss_8013D890");
extern u8 gNoteTblK[][0x86] __asm__("D_main_bss_80140A10");
extern u8 gNoteTrkTblK[][16][0x86] __asm__("D_main_bss_801440C8");
static __inline__ VhNodeK *vhFindK(u32 h) {
    VhNodeK *n = gVhHeadK;
    while (n != NULL) {
        if (n->h == h) {
            return n;
        }
        if (h < n->h) {
            return NULL;
        }
        n = n->next;
    }
    return NULL;
}
static __inline__ s32 vhResolveK(u32 h) {
    VhNodeK *n;
    if (h != (u32)-1) {
        n = vhFindK(h);
        if (n != NULL) {
            return n->slot;
        }
    }
    return -1;
}
static __inline__ void setCtrlHiK(u8 t, u8 idx, u8 c, u16 v) {
    if (t != 0xFF) {
        gNoteTrkTblK[t][idx][c] = (v >> 7) & 0x7F;
    } else {
        gNoteTblK[idx][c] = (v >> 7) & 0x7F;
    }
}
static __inline__ void setCtrlTK(u8 t, u8 idx, u8 c, u8 v) {
    if (t != 0xFF) {
        gNoteTrkTblK[t][idx][c] = v;
    } else {
        gNoteTblK[idx][c] = v;
    }
}
#define GETTRK(idx) ((gChanRecK[idx].flags & 2) ? gChanRecK[idx].trkB : gChanRecK[idx].trkA)
#define setCtrlK(idx, c, v) setCtrlTK(GETTRK(idx), idx, c, v)
s32 spreadVoiceKeyTransposeAcrossChain(s32 h, u16 val) {
    s32 r = -1;
    s32 s;
    s32 idx;
    s = vhResolveK(h);
    while (s != -1) {
            idx = s & 0xFF;
            if (gChanRecK[idx].id != s) {
                break;
            }
            if (gChanRecK[idx].flags & 2) {
                setCtrlHiK(gChanRecK[idx].trkB, idx, 0x84, val);
                setCtrlTK(gChanRecK[idx].trkB, idx, 0x85, val & 0x7F);
            } else {
                setCtrlHiK(gChanRecK[idx].trkA, idx, 0x84, val);
                setCtrlTK(gChanRecK[idx].trkA, idx, 0x85, val & 0x7F);
            }
            s = gChanRecK[idx].next;
            r = 0;
    }
    return r;
}

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

typedef struct VhNodeP { struct VhNodeP *next; s32 pad4; u32 h; s32 slot; } VhNodeP;
extern VhNodeP *gVhHeadP __asm__("D_main_bss_8013AF00");
typedef struct {
    s32 next;
    u8 pad4[0x10];
    u32 flags;
    u8 pad18[0x27];
    u8 trkA;
    u8 pad40[9];
    u8 trkB;
    u8 pad4A[0xA];
    s32 id;
    u8 pad58[0x124];
} ChanRecP;
extern ChanRecP gChanRecP[] __asm__("D_main_bss_8013D890");
extern u8 gNoteTblP[][0x86] __asm__("D_main_bss_80140A10");
extern u8 gNoteTrkTblP[][16][0x86] __asm__("D_main_bss_801440C8");
static __inline__ VhNodeP *vhFindP(u32 h) {
    VhNodeP *n = gVhHeadP;
    while (n != NULL) {
        if (n->h == h) {
            return n;
        }
        if (h < n->h) {
            return NULL;
        }
        n = n->next;
    }
    return NULL;
}
static __inline__ s32 vhResolveP(u32 h) {
    VhNodeP *n;
    if (h != (u32)-1) {
        n = vhFindP(h);
        if (n != NULL) {
            return n->slot;
        }
    }
    return -1;
}
static __inline__ void setCtrlHiP(u8 t, u8 idx, u8 c, u16 v) {
    if (t != 0xFF) {
        gNoteTrkTblP[t][idx][c] = (v >> 7) & 0x7F;
    } else {
        gNoteTblP[idx][c] = (v >> 7) & 0x7F;
    }
}
static __inline__ void setCtrlTP(u8 t, u8 idx, u8 c, u8 v) {
    if (t != 0xFF) {
        gNoteTrkTblP[t][idx][c] = v;
    } else {
        gNoteTblP[idx][c] = v;
    }
}
#define GETTRK(idx) ((gChanRecP[idx].flags & 2) ? gChanRecP[idx].trkB : gChanRecP[idx].trkA)
#define setCtrlP(idx, c, v) setCtrlTP(GETTRK(idx), idx, c, v)
s32 spreadVoicePanVolumeAcrossChain(s32 h, u16 val) {
    s32 r = -1;
    s32 s;
    s32 idx;
    s = vhResolveP(h);
    while (s != -1) {
            idx = s & 0xFF;
            if (gChanRecP[idx].id != s) {
                break;
            }
            if (gChanRecP[idx].flags & 2) {
                setCtrlHiP(gChanRecP[idx].trkB, idx, 0x80, val);
                setCtrlTP(gChanRecP[idx].trkB, idx, 0x81, val & 0x7F);
            } else {
                setCtrlHiP(gChanRecP[idx].trkA, idx, 0x80, val);
                setCtrlTP(gChanRecP[idx].trkA, idx, 0x81, val & 0x7F);
            }
            s = gChanRecP[idx].next;
            r = 0;
    }
    return r;
}

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

typedef struct VhNodePL { struct VhNodePL *next; s32 pad4; u32 h; s32 slot; } VhNodePL;
extern VhNodePL *gVhHeadPL __asm__("D_main_bss_8013AF00");
typedef struct {
    s32 next;
    u8 pad4[0x10];
    u32 flags;
    u8 pad18[0x27];
    u8 trkA;
    u8 pad40[9];
    u8 trkB;
    u8 pad4A[0xA];
    s32 id;
    u8 pad58[0x124];
} ChanRecPL;
extern ChanRecPL gChanRecPL[] __asm__("D_main_bss_8013D890");
extern u8 gNoteTblPL[][0x86] __asm__("D_main_bss_80140A10");
extern u8 gNoteTrkTblPL[][16][0x86] __asm__("D_main_bss_801440C8");
static __inline__ VhNodePL *vhFindPL(u32 h) {
    VhNodePL *n = gVhHeadPL;
    while (n != NULL) {
        if (n->h == h) {
            return n;
        }
        if (h < n->h) {
            return NULL;
        }
        n = n->next;
    }
    return NULL;
}
static __inline__ s32 vhResolvePL(u32 h) {
    VhNodePL *n;
    if (h != (u32)-1) {
        n = vhFindPL(h);
        if (n != NULL) {
            return n->slot;
        }
    }
    return -1;
}
static __inline__ void setCtrlTPL(u8 t, u8 idx, u8 c, u8 v) {
    if (t != 0xFF) {
        gNoteTrkTblPL[t][idx][c] = v & 0x7F;
    } else {
        gNoteTblPL[idx][c] = v & 0x7F;
    }
}
extern u8 gMusyXActiveFlag;
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 spreadVoiceParamPairLocked(s32 h, u8 v) {
    s32 r = -1;
    s32 idx;
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        h = vhResolvePL(h);
        while ((s32)h != -1) {
            idx = h & 0xFF;
            if (gChanRecPL[idx].id != h) {
                break;
            }
            if (gChanRecPL[idx].flags & 2) {
                setCtrlTPL(gChanRecPL[idx].trkB, idx, 1, v);
                setCtrlTPL(gChanRecPL[idx].trkB, idx, 0x21, 0);
            } else {
                setCtrlTPL(gChanRecPL[idx].trkA, idx, 1, v);
                setCtrlTPL(gChanRecPL[idx].trkA, idx, 0x21, 0);
            }
            h = gChanRecPL[idx].next;
            r = 0;
        }
        factor5MutexRelease();
    }
    return r;
}

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

extern u32 D_main_800A0F54;
s32 soundMacroOpLoopRandomCount(u8 *a0, u8 *cmd) {
    u8 *ch = a0;
    register u32 t asm("$3");
    register u32 d asm("$3");
    u32 w;
    u32 r;
    if (*(u16 *)(ch + 0x6C) == 0) {
        if (*(u16 *)cmd & 1) {
            d = D_main_800A0F54;
            t = d * 0xA8351D63;
            r = (u16)(t >> 6) % *(u16 *)(cmd + 4);
            D_main_800A0F54 = t;
            *(u16 *)(ch + 0x6C) = r;
        } else {
            *(u16 *)(ch + 0x6C) = *(u16 *)(cmd + 4);
        }
        if (*(u16 *)(ch + 0x6C) == 0xFFFF) {
            goto block7;
        }
        *(u16 *)(ch + 0x6C) = *(u16 *)(ch + 0x6C) + 1;
    }
    *(u16 *)(ch + 0x6C) = *(u16 *)(ch + 0x6C) - 1;
    if ((u16)*(u16 *)(ch + 0x6C) != 0) {
block7:
        if ((*(u32 *)cmd >> 8) & 1) {
            w = *(u32 *)(ch + 0x24);
            if (!(w & 0x4000000)) {
                if (w & 8) {
                    *(u16 *)(ch + 0x6C) = 0;
                    return 0;
                }
            }
        }
        *(s32 *)(ch + 4) = *(s32 *)ch + *(u16 *)(cmd + 6) * 8;
    }
    return 0;
}

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

extern u8 D_main_8013D880[];
extern u8 D_main_bss_8013D8D0[];
extern u8 D_main_bss_8013D8AE[];
extern s32 D_main_bss_8013D8A8[];
extern u8 D_main_bss_80141AD0;
void freeSynthVoiceFromActiveList();
void beginVoiceFadeRelease(s32 i);
void stopAllSynthVoices(s32 a) {
    s32 i;
    s32 off;
    u8 *v;
    for (i = 0; i < D_main_bss_80141AD0; i++) {
        off = i * 0x17C;
        v = D_main_8013D880 + off;
        if (*(s32 *)(D_main_8013D880 + off) != 0) {
            if ((a & 0xFF) != 0 && D_main_bss_8013D8D0[off] != 0) {
                continue;
            }
            freeSynthVoiceFromActiveList(v);
            *(s32 *)(v + 0x64) = -1;
            *(s32 *)v = 0;
            v[0x2E] = 0;
            *(s32 *)(v + 0x28) = 0;
            *(u32 *)(v + 0x24) &= ~3;
            *(s32 *)(D_main_8013D880 + off) = 0;
            *(u32 *)(D_main_8013D880 + off + 0x24) &= ~3;
            D_main_bss_8013D8AE[off] = 0;
            *(s32 *)((s32)D_main_bss_8013D8A8 + off) = 0;
        }
        beginVoiceFadeRelease(i);
    }
}

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

typedef struct { u8 type; u8 pad1[3]; s32 cur; s32 target; s32 step; s32 time; u8 pad14[0x14]; } FaderH;
extern FaderH gFaderH[] __asm__("D_main_bss_80141B2C");
void setupAudioFaderRamp(u8 vol, u16 time, u8 which) {
    u32 i;
    s32 t;

    if (time == 0) {
        time++;
    }
    t = time << 8;
    switch (which) {
    case 0xFF:
        for (i = 0; i < 32; i++) {
            gFaderH[i].target = vol << 16;
            gFaderH[i].time = t;
            gFaderH[i].step = (gFaderH[i].target - gFaderH[i].cur) / time;
        }
        break;
    case 0xFD:
        for (i = 0; i < 32; i++) {
            if (gFaderH[i].type == 0) {
                gFaderH[i].target = vol << 16;
                gFaderH[i].time = t;
                gFaderH[i].step = (gFaderH[i].target - gFaderH[i].cur) / time;
            }
        }
        break;
    case 0xFE:
        for (i = 0; i < 32; i++) {
            if (gFaderH[i].type == 1) {
                gFaderH[i].target = vol << 16;
                gFaderH[i].time = t;
                gFaderH[i].step = (gFaderH[i].target - gFaderH[i].cur) / time;
            }
        }
        break;
    default:
        gFaderH[which].target = vol << 16;
        gFaderH[which].time = *(volatile s32 *)&t;
        gFaderH[which].step = (gFaderH[which].target - gFaderH[which].cur) / time;
        break;
    }
}

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

typedef struct SongBufNode { struct SongBufNode *next; struct SongBufNode *prev; u8 *buf; u8 pad[8]; } SongBufNode;
void *rs_malloc(u32, u16);
extern SongBufNode *D_main_bss_801499AC;
extern s32 D_main_bss_801499B0;
extern s32 D_main_bss_801499B8;
extern u8 *D_main_bss_801499BC;
extern SongBufNode *D_main_bss_801499C0;
void buildSongDecodeBufferRing(s32 n) {
    s32 i;
    u32 sz = n << 8;
    D_main_bss_801499C0 = rs_malloc(n * 0x14, 0);
    D_main_bss_801499BC = rs_malloc(sz, 0);
    osInvalDCache(D_main_bss_801499BC, sz);
    D_main_bss_801499B0 = 0;
    D_main_bss_801499AC = D_main_bss_801499C0;
    D_main_bss_801499C0[0].buf = D_main_bss_801499BC;
    D_main_bss_801499C0[0].prev = 0;
    for (i = 1; i < n; i++) {
        D_main_bss_801499C0[i].prev = &D_main_bss_801499C0[i - 1];
        D_main_bss_801499C0[i].buf = D_main_bss_801499BC + i * 0x100;
        D_main_bss_801499C0[i - 1].next = &D_main_bss_801499C0[i];
    }
    D_main_bss_801499B8 = 0;
    D_main_bss_801499C0[i - 1].next = 0;
}

extern SongBufNode *D_main_bss_801499AC;
extern s32 D_main_bss_801499B0;
extern u16 D_main_bss_80149724;
extern u8 *D_main_bss_80149728;
u8 *acquireSampleStreamBlock(s32 key) {
    u8 *n;
    u8 *t;
    u8 *rec;
    u16 idx;
    u8 *buf;
    n = (u8 *)D_main_bss_801499B0;
    if (n != 0) {
        do {
            if (*(s32 *)(n + 0xC) == key) {
                *(u16 *)(n + 0x10) = 2;
                return *(u8 **)(n + 8);
            }
            n = *(u8 **)n;
        } while (n != 0);
    }
    t = (u8 *)D_main_bss_801499AC;
    if (t != 0) {
        n = t;
        t = *(u8 **)n;
        D_main_bss_801499AC = (SongBufNode *)t;
        if (t != 0) {
            *(u8 **)(t + 4) = 0;
        }
        if (D_main_bss_801499B0 != 0) {
            *(u8 **)(D_main_bss_801499B0 + 4) = n;
        }
        t = (u8 *)D_main_bss_801499B0;
        D_main_bss_801499B0 = (s32)n;
        *(u8 **)n = t;
    } else {
        n = (u8 *)D_main_bss_801499B0;
        for (; n != 0; n = *(u8 **)n) {
            if (*(u16 *)(n + 0x10) == 0) {
                break;
            }
        }
    }
    idx = D_main_bss_80149724;
    rec = (u8 *)(idx * 12 + (s32)D_main_bss_80149728);
    *(u16 *)(n + 0x10) = 2;
    *(s32 *)(n + 0xC) = key;
    *(s32 *)(rec + 4) = key;
    *(s32 *)rec = 0x100;
    buf = *(u8 **)(n + 8);
    D_main_bss_80149724 = idx + 1;
    *(u8 **)(rec + 8) = buf;
    return *(u8 **)(n + 8);
}

typedef struct SSBNode { struct SSBNode *next; struct SSBNode *prev; u8 pad[0xC]; u8 *buf; } SSBNode;
void *rs_malloc(u32, u16);
extern u8 *D_main_bss_801499C4;
extern SSBNode *D_main_bss_801499C8;
extern SSBNode *D_main_bss_801499CC;
extern SSBNode *D_main_bss_801499B4;
extern SSBNode *D_main_bss_801499E4;
void initSampleStreamBlockCache(u16 n) {
    s32 i;
    u32 sz = n * 0x600;
    D_main_bss_801499C4 = rs_malloc(sz, 0);
    osInvalDCache(D_main_bss_801499C4, sz);
    D_main_bss_801499C8 = rs_malloc(n * 0x18, 0);
    D_main_bss_801499E4 = 0;
    D_main_bss_801499B4 = 0;
    D_main_bss_801499CC = D_main_bss_801499C8;
    D_main_bss_801499C8[0].prev = 0;
    D_main_bss_801499C8[0].buf = D_main_bss_801499C4;
    for (i = 1; i < n; i++) {
        D_main_bss_801499C8[i - 1].next = &D_main_bss_801499C8[i];
        D_main_bss_801499C8[i].prev = &D_main_bss_801499C8[i - 1];
        D_main_bss_801499C8[i].buf = D_main_bss_801499C4 + i * 0x600;
    }
    D_main_bss_801499C8[i - 1].next = 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", moveSampleBlockToFront);

SSBNode *recycleSampleStreamBlock(void) {
    register SSBNode *n asm("$3");
    SSBNode *t;
    register SSBNode *t2 asm("$2");
    register SSBNode *t1 asm("$2");
    register SSBNode *c asm("$2");
    c = D_main_bss_801499CC;
    if (c != 0) {
        n = c;
        t1 = n->next;
        D_main_bss_801499CC = t1;
        if (t1 != 0) {
            t1->prev = 0;
        }
        if (D_main_bss_801499B4 == 0) {
            n->next = D_main_bss_801499E4;
            if (D_main_bss_801499E4 != 0) {
                D_main_bss_801499E4->prev = n;
            }
            D_main_bss_801499E4 = n;
        } else {
            n->next = 0;
            n->prev = D_main_bss_801499B4;
            D_main_bss_801499B4->next = n;
        }
        D_main_bss_801499B4 = n;
    } else {
        n = D_main_bss_801499E4;
        if (n != D_main_bss_801499B4) {
            t = n->next;
            if (t != 0) {
                t->prev = n->prev;
            }
            t = n->prev;
            if (t != 0) {
                t->next = n->next;
            } else {
                D_main_bss_801499E4 = n->next;
            }
            t2 = D_main_bss_801499B4;
            D_main_bss_801499B4 = n;
            t2->next = n;
            n->prev = t2;
            n->next = 0;
        }
    }
    return n;
}

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

extern u8 gMusyXActiveFlag;
extern void *D_main_bss_801496FC;
extern u8 *D_main_bss_80149728;
extern volatile u8 D_main_bss_8014974C;
extern void *D_main_bss_80149758;
extern void *D_main_bss_8014975C;
extern void *D_main_bss_80149764;
extern s32 D_main_bss_80149768;
extern void *D_main_bss_80149770;
extern volatile s16 D_main_bss_8014998A;
extern u8 *D_main_bss_801499BC;
extern SongBufNode *D_main_bss_801499C0;
extern void (*D_main_bss_801499D8)(void (*)(void));
void musyxSynthFrame(void);
void rs_free(void *);
void waitForMusyXAudioTaskDone(void) {
    if (gMusyXActiveFlag != 0) {
        D_main_bss_8014998A = 0x10;
        while (D_main_bss_8014998A > 0) {
        }
        D_main_bss_801499D8(musyxSynthFrame);
        if (D_main_bss_80149768 != 0) {
            D_main_bss_80149768 = 0;
            rs_free(0);
        }
        if (D_main_bss_80149770 != 0) {
            rs_free(D_main_bss_80149770);
        }
        while (D_main_bss_8014974C != 0) {
        }
        rs_free(D_main_bss_80149728);
        rs_free(D_main_bss_801499BC);
        rs_free(D_main_bss_801499C0);
        rs_free(D_main_bss_80149758);
        rs_free(D_main_bss_8014975C);
        rs_free(D_main_bss_801496FC);
        rs_free(D_main_bss_80149764);
    }
}

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
