#include "common.h"
#include "common_types.h"
#include "PR/os.h"

typedef struct { s32 a; s32 b; s32 c; u8 *ch; u8 state; u8 pad[3]; } MaSlotF;
extern MaSlotF gSlotsF[] __asm__("gActiveModelAnimSlots");
extern const f32 D_main_8003DB14;
typedef struct { f32 f0; s32 pad4; s32 pad8; s32 *p; } MaChF;
#define CHP (((MaChF *)((u8 *)((group * 16) + (s32)gSlotsF[slotId - 1].ch)))->p)
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DB10);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DB14);

void findModelAnimKeyframeByPhase(s32 slotId, s32 group, f32 phase) {
    s16 ts = (s32)(phase * D_main_8003DB14);
    u8 *g = *(u8 **)(gSlotsF[slotId - 1].c + 4) + (group * 16);
    u32 i;
    for (i = 0; i < *(u16 *)(g + 0xE); i++) {
        u8 *e;
        u8 *ent = (u8 *)(i * 0x1C + (s32)*(u8 **)g);
        s32 n = *(s32 *)ent;
        s32 mid;
        if (n != 0) {
            s16 *tm;
            s32 lo;
            s32 hi;
            s32 val;
            e = ent;
            tm = *(s16 **)(e + 8);
            lo = 1;
            hi = n;
            do {
                mid = (lo + hi) >> 1;
                val = tm[mid - 1];
                if (val == ts) {
                    goto found;
                }
                if (ts < val) {
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            } while (lo < hi);
            mid = lo - (ts < tm[lo - 1]);
found:
            mid = mid - 1;
            CHP[i * 2] = mid;
            if (mid != *(s32 *)e - 1) {
                s16 *tm2 = *(s16 **)(e + 8);
                s32 t0 = tm2[mid];
                s32 t1 = tm2[mid + 1];
                ((f32 *)CHP)[i * 2 + 1] = (f32)(ts - t0) / (f32)(t1 - t0);
            } else {
                CHP[i * 2 + 1] = 0;
            }
        } else {
            CHP[i * 2] = 0;
            CHP[i * 2 + 1] = 0;
        }
    }
    ((MaChF *)((u8 *)((group * 16) + (s32)gSlotsF[slotId - 1].ch)))->f0 = phase;
}

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

extern const f32 D_main_8003DB18;
void *rs_malloc(u32, u16);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DB18);

s32 allocateModelAnimSlotImpl(void *a, void *b, s32 n) __asm__("allocateModelAnimSlot");
typedef struct { s32 w0; f32 f4; u8 b8; u8 pad9[3]; s32 *p; } MaChAMA;
s32 allocateModelAnimSlotImpl(void *a, void *b, s32 n) {
    u32 i;
    u32 found = 0;
    u32 idx;
    for (i = 0; i < 0x20; i++) {
        if (gActiveModelAnimSlots[i].state == 0) {
            found = i + 1;
            break;
        }
    }
    if (found != 0) {
        idx = found - 1;
        gActiveModelAnimSlots[idx].a = (s32)a;
        gActiveModelAnimSlots[idx].b = n;
        gActiveModelAnimSlots[idx].c = (s32)b;
        gActiveModelAnimSlots[idx].ch = rs_malloc(*(u32 *)gActiveModelAnimSlots[idx].c << 4, 0);
        gActiveModelAnimSlots[idx].state = 1;
        gActiveModelAnimSlots[idx].pad[0] = 0;
        for (i = 0; i < *(u32 *)gActiveModelAnimSlots[idx].c; i++) {
            MaChAMA *ch;
            ch = (MaChAMA *)gActiveModelAnimSlots[idx].ch;
            ch[i].w0 = 0;
            ch = (MaChAMA *)gActiveModelAnimSlots[idx].ch;
            ch[i].f4 = D_main_8003DB18;
            ch = (MaChAMA *)gActiveModelAnimSlots[idx].ch;
            ch[i].b8 = 0;
            ((MaChAMA *)gActiveModelAnimSlots[idx].ch)[i].p = rs_malloc(n << 3, 0);
            ((MaChAMA *)gActiveModelAnimSlots[idx].ch)[i].p[0] = 0;
            ((MaChAMA *)gActiveModelAnimSlots[idx].ch)[i].p[1] = 0;
        }
    }
    return found;
}

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

typedef struct { s32 a; s32 b; u32 *c; u8 *ch; u8 state; u8 owned; u8 pad[2]; } MaSlotRL;
extern MaSlotRL gSlotsRL[] __asm__("gActiveModelAnimSlots");
void rs_free(void *);
void releaseModelAnimSlot(s32 id) {
    u32 i;
    s32 n = id - 1;

    for (i = 0; i < *gSlotsRL[n].c; i++) {
        rs_free(*(void **)(i * 16 + gSlotsRL[n].ch + 0xC));
    }
    rs_free(gSlotsRL[n].ch);
    if (gSlotsRL[n].owned != 0) {
        rs_free((void *)gSlotsRL[n].a);
    }
    gSlotsRL[n].a = 0;
    gSlotsRL[n].b = 0;
    gSlotsRL[n].c = 0;
    gSlotsRL[n].state = 0;
}

typedef struct { s32 a; s32 b; s32 c; u8 *ch; u8 state; u8 pad[3]; } MaSlotMA;
extern MaSlotMA gSlotsMA[] __asm__("gActiveModelAnimSlots");
static __inline__ u8 maSlotValidMA(u32 id) {
    s32 r = 0;
    if (id != 0 && id <= 32) {
        r = gSlotsMA[id - 1].state == 1;
    }
    return r;
}
u32 markModelAnimChannelEntryActive(u32 id, u32 sub) {
    u32 r = 0;

    if (maSlotValidMA(id)) {
        *(u8 *)(sub * 16 + gSlotsMA[id - 1].ch + 8) |= 1;
        r = (id << 16) + sub;
    }
    return r;
}

typedef struct { s32 a; s32 b; s32 c; u8 *ch; u8 state; u8 pad[3]; } MaSlotCE;
extern MaSlotCE gSlotsCE[] __asm__("gActiveModelAnimSlots");
static __inline__ u8 maSlotValidCE(u32 id) {
    s32 r = 0;
    if (id != 0 && id <= 32) {
        r = gSlotsCE[id - 1].state == 1;
    }
    return r;
}
void clearModelAnimChannelEntry(u32 h) {
    u32 id = h >> 16;
    u32 sub = h & 0xFFFF;

    if (maSlotValidCE(id)) {
        *(u8 *)(sub * 16 + gSlotsCE[id - 1].ch + 8) = 0;
    }
}

typedef struct { s32 a; s32 b; s32 c; u8 *ch; u8 state; u8 pad[3]; } MaSlotST;
extern MaSlotST gSlotsST[] __asm__("gActiveModelAnimSlots");
void findModelAnimKeyframeByPhase(s32 slotId, s32 group, f32 phase);
static __inline__ u8 maSlotValidST(u32 id) {
    s32 r = 0;
    if (id != 0 && id <= 32) {
        r = gSlotsST[id - 1].state == 1;
    }
    return r;
}
void seekModelAnimChannelToTime(u32 h, f32 t) {
    u32 id = h >> 16;
    u32 sub = h & 0xFFFF;

    if (maSlotValidST(id)) {
        if (t < 0.0f) {
            t = 0.0f;
        } else if (*(f32 *)(sub * 16 + gSlotsST[id - 1].ch + 4) < t) {
            t = *(f32 *)(sub * 16 + gSlotsST[id - 1].ch + 4);
        }
        findModelAnimKeyframeByPhase(id, sub, t / *(f32 *)(sub * 16 + gSlotsST[id - 1].ch + 4));
    }
}

typedef struct { s32 a; s32 b; u32 *c; u8 *ch; u8 state; u8 pad[3]; } MaSlotSA;
extern MaSlotSA gSlotsSA[] __asm__("gActiveModelAnimSlots");
void findModelAnimKeyframeByPhase(s32 slotId, s32 group, f32 phase);
static __inline__ u8 maSlotValidSA(u32 id) {
    s32 r = 0;
    if (id != 0 && id <= 32) {
        r = gSlotsSA[id - 1].state == 1;
    }
    return r;
}
void seekAllModelAnimChannelsInSlotToTime(u32 id, f32 t) {
    u32 i;
    f32 tt;

    if (maSlotValidSA(id)) {
        for (i = 0; i < *gSlotsSA[id - 1].c; i++) {
            if (t < 0.0f) {
                tt = 0.0f;
            } else if (*(f32 *)(i * 16 + gSlotsSA[id - 1].ch + 4) < t) {
                tt = *(f32 *)(i * 16 + gSlotsSA[id - 1].ch + 4);
            } else {
                tt = t;
            }
            findModelAnimKeyframeByPhase(id, i, tt / *(f32 *)(i * 16 + gSlotsSA[id - 1].ch + 4));
        }
    }
}

typedef struct { s32 a; s32 b; s32 c; u8 *ch; u8 state; u8 pad[3]; } MaSlotSD;
extern MaSlotSD gSlotsSD[] __asm__("gActiveModelAnimSlots");
static __inline__ u8 maSlotValidSD(u32 id) {
    s32 r = 0;
    if (id != 0 && id <= 32) {
        r = gSlotsSD[id - 1].state == 1;
    }
    return r;
}
void setModelAnimChannelEntryDuration(u32 h, f32 v) {
    u32 id = h >> 16;
    u32 sub = h & 0xFFFF;

    if (maSlotValidSD(id)) {
        *(f32 *)(sub * 16 + gSlotsSD[id - 1].ch + 4) = v;
    }
}


typedef struct { s32 a; s32 b; s32 c; u8 *ch; u8 state; u8 pad[3]; } MaSlotGD;
extern MaSlotGD gSlotsGD[] __asm__("gActiveModelAnimSlots");
static __inline__ u8 maSlotValidGD(u32 id) {
    s32 r = 0;
    if (id != 0 && id <= 32) {
        r = gSlotsGD[id - 1].state == 1;
    }
    return r;
}
f32 getModelAnimChannelEntryDuration(u32 h) {
    u32 id = h >> 16;
    u32 sub = h & 0xFFFF;
    f32 r;

    if (maSlotValidGD(id)) {
        r = *(f32 *)(sub * 16 + gSlotsGD[id - 1].ch + 4);
    } else {
        r = 1.0f;
    }
    return r;
}

typedef struct { s32 a; s32 b; u32 *c; u8 *ch; u8 state; u8 pad[3]; } MaSlotCD;
extern MaSlotCD gSlotsCD[] __asm__("gActiveModelAnimSlots");
static __inline__ u8 maSlotValidCD(u32 id) {
    s32 r = 0;
    if (id != 0 && id <= 32) {
        r = gSlotsCD[id - 1].state == 1;
    }
    return r;
}
void setModelAnimSlotCycleDuration(u32 id, f32 v) {
    u32 i;

    if (maSlotValidCD(id)) {
        for (i = 0; i < *gSlotsCD[id - 1].c; i++) {
            *(f32 *)(i * 16 + gSlotsCD[id - 1].ch + 4) = v;
        }
    }
}


typedef struct { s32 a; s32 b; s32 c; u8 *ch; u8 state; u8 pad[3]; } MaSlotKV;
extern MaSlotKV gSlotsKV[] __asm__("gActiveModelAnimSlots");
#define KVENT(id, sub) (*(u8 **)(gSlotsKV[(id) - 1].c + 4) + (sub) * 16)
#define KVSCL(id, sub) (*(f32 *)((sub) * 16 + gSlotsKV[(id) - 1].ch))
static __inline__ u8 maSlotValidKV(u32 id) {
    s32 r = 0;
    if (id != 0 && id <= 32) {
        r = gSlotsKV[id - 1].state == 1;
    }
    return r;
}
s32 sampleModelAnimKeyframeVec3(u32 h, f32 *out) {
    u32 id = h >> 16;
    u32 sub = h & 0xFFFF;

    if (maSlotValidKV(id)) {
        if (*(u32 *)(KVENT(id, sub) + 4) & 1) {
            out[0] = (f32)*(s16 *)(KVENT(id, sub) + 8) * KVSCL(id, sub) * 0.00390625f;
            out[1] = (f32)*(s16 *)(KVENT(id, sub) + 0xA) * KVSCL(id, sub) * 0.00390625f;
            out[2] = (f32)*(s16 *)(KVENT(id, sub) + 0xC) * KVSCL(id, sub) * 0.00390625f;
            return 1;
        }
        return 0;
    }
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DB24);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DB28);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DB2C);

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

// NOTE: ~13 rows: only the post-loop join differs (n reload block / v in v1 vs v0); same template as SecondInsertValue/InsertTaggedValue/InsertWidePair
typedef struct { s32 a; s32 b; } TblIns1;
extern s32 D_main_bss_8013C450;
extern u8 D_main_bss_8013BC4C[];
extern u8 D_main_bss_8013BC48[];
extern TblIns1 D_main_bss_8013BC50[];
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5SortedTableInsertValue(u16 key, s32 val) {
    s32 i;
    s32 j;
    s32 off;
    s32 v;
    factor5MutexAcquire();
    for (i = 0; i < D_main_bss_8013C450; i++) {
        off = i * 8;
        if (!(*(u16 *)(D_main_bss_8013BC4C + off) < (u32)key)) {
            break;
        }
    }
    if (i < D_main_bss_8013C450) {
        if (*(u16 *)(D_main_bss_8013BC4C + i * 8) != key) {
            j = D_main_bss_8013C450 - 1;
            if (D_main_bss_8013C450 < 0x100) {
                if (j >= i) {
                    do {
                        D_main_bss_8013BC50[j] = D_main_bss_8013BC50[j - 1];
                        j--;
                    } while (j >= i);
                }
                v = D_main_bss_8013C450 + 1;
                goto store;
            }
        }
        goto fail;
    }
    if (D_main_bss_8013C450 >= 0x100) {
fail:
        factor5MutexRelease();
        return 0;
    }
    v = D_main_bss_8013C450 + 1;
store:
    D_main_bss_8013C450 = v;
    *(u16 *)(D_main_bss_8013BC4C + i * 8) = key;
    *(s32 *)(D_main_bss_8013BC48 + i * 8) = val;
    factor5MutexRelease();
    return 1;
}

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

typedef struct { s32 a; s32 b; } TblIns3;
extern s32 D_main_bss_8013AF08;
extern u8 D_main_bss_80148454[];
extern u8 D_main_bss_80148450[];
extern u8 D_main_bss_80148456[];
extern TblIns3 D_main_bss_80148458[];
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5SortedTableInsertTaggedValue(u16 key, s32 val, u16 tag) {
    s32 i;
    s32 j;
    s32 off;
    s32 v;
    factor5MutexAcquire();
    for (i = 0; i < D_main_bss_8013AF08; i++) {
        off = i * 8;
        if (!(*(u16 *)(D_main_bss_80148454 + off) < (u32)key)) {
            break;
        }
    }
    if (i < D_main_bss_8013AF08) {
        if (*(u16 *)(D_main_bss_80148454 + i * 8) != key) {
            j = D_main_bss_8013AF08 - 1;
            if (D_main_bss_8013AF08 < 0x100) {
                if (j >= i) {
                    do {
                        D_main_bss_80148458[j] = D_main_bss_80148458[j - 1];
                        j--;
                    } while (j >= i);
                }
                v = D_main_bss_8013AF08 + 1;
                goto store;
            }
        }
        goto fail;
    }
    if (D_main_bss_8013AF08 >= 0x100) {
fail:
        factor5MutexRelease();
        return 0;
    }
    v = D_main_bss_8013AF08 + 1;
store:
    D_main_bss_8013AF08 = v;
    *(u16 *)(D_main_bss_80148454 + i * 8) = key;
    *(s32 *)(D_main_bss_80148450 + i * 8) = val;
    *(u16 *)(D_main_bss_80148456 + i * 8) = tag;
    factor5MutexRelease();
    return 1;
}

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

// NOTE: ~13 rows: only the post-loop join differs (n reload block / v in v1 vs v0); same template as SecondInsertValue/InsertTaggedValue/InsertWidePair
typedef struct { s32 a; s32 b; } TblIns2;
extern s32 D_main_bss_8013AF0C;
extern u8 D_main_bss_80148C6C[];
extern u8 D_main_bss_80148C68[];
extern TblIns2 D_main_bss_80148C70[];
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5SecondSortedTableInsertValue(u16 key, s32 val) {
    s32 i;
    s32 j;
    s32 off;
    s32 v;
    factor5MutexAcquire();
    for (i = 0; i < D_main_bss_8013AF0C; i++) {
        off = i * 8;
        if (!(*(u16 *)(D_main_bss_80148C6C + off) < (u32)key)) {
            break;
        }
    }
    if (i < D_main_bss_8013AF0C) {
        if (*(u16 *)(D_main_bss_80148C6C + i * 8) != key) {
            j = D_main_bss_8013AF0C - 1;
            if (D_main_bss_8013AF0C < 0x100) {
                if (j >= i) {
                    do {
                        D_main_bss_80148C70[j] = D_main_bss_80148C70[j - 1];
                        j--;
                    } while (j >= i);
                }
                v = D_main_bss_8013AF0C + 1;
                goto store;
            }
        }
        goto fail;
    }
    if (D_main_bss_8013AF0C >= 0x100) {
fail:
        factor5MutexRelease();
        return 0;
    }
    v = D_main_bss_8013AF0C + 1;
store:
    D_main_bss_8013AF0C = v;
    *(u16 *)(D_main_bss_80148C6C + i * 8) = key;
    *(s32 *)(D_main_bss_80148C68 + i * 8) = val;
    factor5MutexRelease();
    return 1;
}

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

typedef struct { s32 a; s32 b; s32 c; } TblIns4;
extern s32 D_main_bss_8013C44C;
extern u8 D_main_bss_8013B050[];
extern u8 D_main_bss_8013B048[];
extern u8 D_main_bss_8013B04C[];
extern TblIns4 D_main_bss_8013B054[];
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5SortedTableInsertWidePair(u16 key, s32 v1, s32 v2) {
    s32 i;
    s32 j;
    s32 off;
    s32 v;
    factor5MutexAcquire();
    for (i = 0; i < D_main_bss_8013C44C; i++) {
        off = i * 12;
        if (!(*(u16 *)(D_main_bss_8013B050 + off) < (u32)key)) {
            break;
        }
    }
    if (i < D_main_bss_8013C44C) {
        if (*(u16 *)(D_main_bss_8013B050 + i * 12) != key) {
            j = D_main_bss_8013C44C - 1;
            if (D_main_bss_8013C44C < 0x100) {
                if (j >= i) {
                    do {
                        D_main_bss_8013B054[j] = D_main_bss_8013B054[j - 1];
                        j--;
                    } while (j >= i);
                }
                v = D_main_bss_8013C44C + 1;
                goto store;
            }
        }
        goto fail;
    }
    if (D_main_bss_8013C44C >= 0x100) {
fail:
        factor5MutexRelease();
        return 0;
    }
    v = D_main_bss_8013C44C + 1;
store:
    D_main_bss_8013C44C = v;
    *(u16 *)(D_main_bss_8013B050 + i * 12) = key;
    *(s32 *)(D_main_bss_8013B048 + i * 12) = v1;
    *(s32 *)(D_main_bss_8013B04C + i * 12) = v2;
    factor5MutexRelease();
    return 1;
}

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

typedef struct { u16 h[6]; } TblVRI;
typedef struct { u16 key; u16 h2; u8 b4; u8 b5; u8 b6; u8 b7; u8 b8; u8 b9; u8 pad[2]; } RecVRI;
extern RecVRI gRecVRI[] __asm__("D_main_bss_8013CC80");
extern s32 gCountVRI __asm__("D_main_bss_80140800");
extern u8 gTblVRI[] __asm__("D_main_bss_8013CC80");
extern TblVRI gShiftVRI[] __asm__("D_main_bss_8013CC8C");
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5SortedTableInsertVoiceRecord(u16 key, u16 h2, u8 b7, u8 b6, u8 b5, u8 b4, u8 b8) {
    s32 i;
    s32 j;
    s32 off;
    s32 v;
    factor5MutexAcquire();
    for (i = 0; i < gCountVRI; i++) {
        off = i * 12;
        if (!(*(u16 *)(gTblVRI + off) < (u32)key)) {
            break;
        }
    }
    if (i < gCountVRI) {
        if (*(u16 *)(gTblVRI + i * 12) != key) {
            j = gCountVRI - 1;
            if (gCountVRI < 0x100) {
                if (j >= i) {
                    do {
                        gShiftVRI[j] = gShiftVRI[j - 1];
                        j--;
                    } while (j >= i);
                }
                v = gCountVRI + 1;
                goto setcount;
            }
            goto fail;
        }
        goto store;
    }
    if (gCountVRI >= 0x100) {
fail:
        factor5MutexRelease();
        return 0;
    }
    v = gCountVRI + 1;
setcount:
    gCountVRI = v;
store:
    gRecVRI[i].key = key;
    gRecVRI[i].h2 = h2;
    gRecVRI[i].b7 = b7;
    gRecVRI[i].b6 = b6;
    gRecVRI[i].b5 = b5;
    gRecVRI[i].b4 = b4;
    gRecVRI[i].b8 = b8;
    gRecVRI[i].b9 = 0x1F;
    factor5MutexRelease();
    return 1;
}

typedef struct { u16 h[6]; } TblE12VR;
extern s32 gCountVR __asm__("D_main_bss_80140800");
extern u8 gKeysVR[] __asm__("D_main_bss_8013CC80");
extern TblE12VR gRecsVR[] __asm__("D_main_bss_8013CC74");
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5SortedTableRemoveVoiceRecord(s32 v) {
    s32 i;
    s32 j;
    s32 off;
    factor5MutexAcquire();
    for (i = 0; i < gCountVR; i++) {
        off = i * 0xC;
        if (*(u16 *)(gKeysVR + off) == (v & 0xFFFF)) {
            break;
        }
    }
    if (i != gCountVR) {
        j = i + 1;
        if (j < gCountVR) {
            do {
                gRecsVR[j] = gRecsVR[j + 1];
                j++;
            } while (j < gCountVR);
        }
        gCountVR = gCountVR - 1;
        factor5MutexRelease();
        return 1;
    }
    factor5MutexRelease();
    return 0;
}

typedef struct { s32 v; u16 key; u16 pad; } BtRecBTI;
extern s16 gBucketsBTI[][2] __asm__("D_main_bss_8013C480");
extern BtRecBTI gTblBTI[] __asm__("D_main_bss_801420C0");
extern BtRecBTI gTblBTI1[] __asm__("D_main_bss_801420C8");
extern s32 gTotalBTI __asm__("D_main_bss_80148C50");
extern u16 gTotalLoBTI __asm__("D_main_bss_80148C52");
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5BucketedTableInsertEntry(u16 key, s32 val) {
    s32 b;
    s32 start;
    s32 i;
    s32 idx;
    s32 off;
    s32 v;
    s16 (*q)[2];

    factor5MutexAcquire();
    b = key >> 6;
    if ((u16)gBucketsBTI[b][0] == 0) {
        idx = gTotalLoBTI;
        gBucketsBTI[b][1] = gTotalLoBTI;
        start = idx;
    } else {
        start = (u16)gBucketsBTI[b][1];
        for (i = 0; i < (u16)gBucketsBTI[b][0]; i++) {
            if (!(gTblBTI[start + i].key < key)) {
                break;
            }
        }
        if (i < (u16)gBucketsBTI[b][0]) {
            idx = start + i;
            if (gTblBTI[idx].key == key) {
                goto fail;
            }
        } else {
            idx = start + i;
        }
    }
    if (gTotalBTI < 0x400) {
        q = gBucketsBTI;
        for (off = 0; off < 0x800; off += 4) {
            v = *(u16 *)((s32)gBucketsBTI + off + 2);
            if (start < v) {
                q[0][1] = v + 1;
            }
            q++;
        }
        for (i = gTotalBTI - 1; i >= idx; i--) {
            gTblBTI1[i] = gTblBTI1[i - 1];
        }
        gTblBTI[idx].key = key;
        gTblBTI[idx].v = val;
        gBucketsBTI[b][0] = (u16)gBucketsBTI[b][0] + 1;
        gTotalBTI = gTotalBTI + 1;
        factor5MutexRelease();
        return 1;
    }
fail:
    factor5MutexRelease();
    return 0;
}

typedef struct { s32 a; s32 b; } BtE8BTR;
extern s16 gBucketsBTR[][2] __asm__("D_main_bss_8013C480");
typedef struct { s32 v; u16 key; u16 pad; } BtRecBTR;
extern BtRecBTR gTblBTR[] __asm__("D_main_bss_801420C0");
extern BtE8BTR gShiftBTR[] __asm__("D_main_bss_801420B8");
extern s32 gTotalBTR __asm__("D_main_bss_80148C50");
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
s32 factor5BucketedTableRemoveEntry(u16 key) {
    s32 b;
    s32 start;
    s32 i;
    s32 off;
    s32 v;
    s16 (*q)[2];

    factor5MutexAcquire();
    b = key >> 6;
    if ((u16)gBucketsBTR[b][0] != 0) {
        start = (u16)gBucketsBTR[b][1];
        for (i = 0; i < (u16)gBucketsBTR[b][0]; i++) {
            if (gTblBTR[start + i].key == key) {
                break;
            }
        }
        if (i < (u16)gBucketsBTR[b][0]) {
            for (i = start + i + 1; i < gTotalBTR; i++) {
                gShiftBTR[i] = gShiftBTR[i + 1];
            }
            q = gBucketsBTR;
            for (off = 0; off < 0x800; off += 4) {
                v = *(u16 *)((s32)gBucketsBTR + off + 2);
                if (start < v) {
                    q[0][1] = v - 1;
                }
                q++;
            }
            gBucketsBTR[b][0] = (u16)gBucketsBTR[b][0] - 1;
            gTotalBTR = gTotalBTR - 1;
        }
    }
    factor5MutexRelease();
    return 0;
}

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

typedef struct FsNode { struct FsNode *next; struct FsNode *prev; u32 h; s32 slot; } FsNode;
extern FsNode *gFsHead __asm__("D_main_bss_8013AF00");
extern FsNode *gFsFree __asm__("D_main_bss_8013AF04");
extern s32 gFsNext[] __asm__("D_main_bss_8013D890");
extern s32 gFsPrev[] __asm__("D_main_bss_8013D894");
extern FsNode *gFsNodeArr[] __asm__("D_main_bss_8013D898");
#define FSX(arr, i) (*(s32 *)((u8 *)(arr) + (u8)(i) * 0x17C))
void fsImplFS(u8 *v) __asm__("freeSynthVoiceFromActiveList");
void fsImplFS(u8 *v) {
    s32 prev;
    s32 next;
    FsNode *n;

    if (*(s32 *)(v + 0x64) == -1) {
        return;
    }
    prev = *(s32 *)(v + 0x14);
    if (prev != -1) {
        FSX(gFsNext, prev) = *(s32 *)(v + 0x10);
        next = *(s32 *)(v + 0x10);
        if (next != -1) {
            FSX(gFsPrev, next) = *(s32 *)(v + 0x14);
        }
    } else if (*(s32 *)(v + 0x10) != prev) {
        (*(FsNode **)(v + 0x18))->slot = *(s32 *)(v + 0x10);
        FSX(gFsPrev, v[0x13]) = prev;
        *(FsNode **)((u8 *)gFsNodeArr + v[0x13] * 0x17C) = *(FsNode **)(v + 0x18);
    } else {
        n = *(FsNode **)(v + 0x18);
        if (n->prev != NULL) {
            n->prev->next = n->next;
        } else {
            gFsHead = n->next;
        }
        n = *(FsNode **)(v + 0x18);
        if (n->next != NULL) {
            n->next->prev = n->prev;
            n = *(FsNode **)(v + 0x18);
        }
        n->next = gFsFree;
        if (gFsFree != NULL) {
            gFsFree->prev = *(FsNode **)(v + 0x18);
        }
        (*(FsNode **)(v + 0x18))->prev = NULL;
        gFsFree = *(FsNode **)(v + 0x18);
    }
}

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

typedef struct VhNodeRV { struct VhNodeRV *next; s32 pad4; u32 h; s32 slot; } VhNodeRV;
extern VhNodeRV *gVhHeadRV __asm__("D_main_bss_8013AF00");
static __inline__ VhNodeRV *vhFindRV(u32 h) {
    VhNodeRV *n = gVhHeadRV;
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
s32 resolveVoiceSlotByHandle(u32 h) {
    VhNodeRV *n;
    if (h != (u32)-1) {
        n = vhFindRV(h);
        if (n != NULL) {
            return n->slot;
        }
    }
    return -1;
}

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

s32 findActiveVoiceByKeyPairFV(u8, u8, u8) __asm__("findActiveVoiceByKeyPair");
static __inline__ u8 getChByteAltFV(u8 a, u8 b) {
    if (b != 0xFF) {
        return D_main_bss_801483D0[b][a];
    }
    return D_main_bss_80142018[a];
}
s32 findVoiceForNote(u8 note, u8 a, u8 b) {
    s32 r;

    if (a != 0xFF && getChByteAltFV(a, b) != 0) {
        r = findActiveVoiceByKeyPairFV(note & 0x7F, a, b);
        if (r != -1) {
            return r;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", startNoteOnVoice);

INCLUDE_ASM("asm/nonmatchings/main/832A0", applyNoteEventToGroup);

INCLUDE_ASM("asm/nonmatchings/main/832A0", dispatchSequencerNoteEvent);

s32 dispatchSequencerNoteEventK(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32) __asm__("dispatchSequencerNoteEvent");
s32 musyxNoteEventLockedDispatch(u16 key, u8 a, u8 b) {
    s32 r7;
    u8 *p;
    u8 s5;
    u8 s6;

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
    return r7;
}

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

typedef struct VhNodeVV { struct VhNodeVV *next; s32 pad4; u32 h; s32 slot; } VhNodeVV;
extern VhNodeVV *gVhHeadVV __asm__("D_main_bss_8013AF00");
static __inline__ VhNodeVV *vhFindVV(u32 h) {
    VhNodeVV *n = gVhHeadVV;
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
static __inline__ s32 vhResolveVV(u32 h) {
    VhNodeVV *n;
    if (h != (u32)-1) {
        n = vhFindVV(h);
        if (n != NULL) {
            return n->slot;
        }
    }
    return -1;
}
u32 validateVoiceHandle(u32 h) {
    if (vhResolveVV(h) != -1) {
        return h;
    }
    return -1;
}

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

typedef struct VhNodeEV { struct VhNodeEV *next; s32 pad4; u32 h; s32 slot; } VhNodeEV;
extern VhNodeEV *gVhHeadEV __asm__("D_main_bss_8013AF00");
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
} ChanRecEV;
extern ChanRecEV gChanRecEV[] __asm__("D_main_bss_8013D890");
extern u8 gNoteTblEV[][0x86] __asm__("D_main_bss_80140A10");
extern u8 gNoteTrkTblEV[][16][0x86] __asm__("D_main_bss_801440C8");
static __inline__ VhNodeEV *vhFindEV(u32 h) {
    VhNodeEV *n = gVhHeadEV;
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
static __inline__ s32 vhResolveEV(u32 h) {
    VhNodeEV *n;
    if (h != (u32)-1) {
        n = vhFindEV(h);
        if (n != NULL) {
            return n->slot;
        }
    }
    return -1;
}
static __inline__ void setCtrlTEV(u8 t, u8 idx, u8 c, u8 v) {
    if (t != 0xFF) {
        gNoteTrkTblEV[t][idx][c] = v & 0x7F;
    } else {
        gNoteTblEV[idx][c] = v & 0x7F;
    }
}
s32 setVoiceParamByHandle(s32 h, u8 v) {
    s32 r = -1;
    s32 idx;
    h = vhResolveEV(h);
    while ((s32)h != -1) {
        idx = h & 0xFF;
        if (gChanRecEV[idx].id != h) {
            break;
        }
        if (gChanRecEV[idx].flags & 2) {
            setCtrlTEV(gChanRecEV[idx].trkB, idx, 0xA, v);
        } else {
            setCtrlTEV(gChanRecEV[idx].trkA, idx, 0xA, v);
        }
        h = gChanRecEV[idx].next;
        r = 0;
    }
    return r;
}

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

s32 applyVoiceCmdByHandle(s32 h, u8 v) {
    s32 r = -1;
    s32 idx;
    h = vhResolveEV(h);
    while ((s32)h != -1) {
        idx = h & 0xFF;
        if (gChanRecEV[idx].id != h) {
            break;
        }
        if (gChanRecEV[idx].flags & 2) {
            setCtrlTEV(gChanRecEV[idx].trkB, idx, 0x83, v);
        } else {
            setCtrlTEV(gChanRecEV[idx].trkA, idx, 0x83, v);
        }
        h = gChanRecEV[idx].next;
        r = 0;
    }
    return r;
}

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

s32 spreadVoiceByteParamAcrossChain(s32 h, u8 v) {
    s32 r = -1;
    s32 idx;
    h = vhResolvePL(h);
    while ((s32)h != -1) {
        idx = h & 0xFF;
        if (gChanRecPL[idx].id != h) {
            break;
        }
        if (gChanRecPL[idx].flags & 2) {
            setCtrlTPL(gChanRecPL[idx].trkB, idx, 7, v);
        } else {
            setCtrlTPL(gChanRecPL[idx].trkA, idx, 7, v);
        }
        h = gChanRecPL[idx].next;
        r = 0;
    }
    return r;
}

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

s32 flagVoiceChainForStop(s32 h) {
    s32 r = -1;
    s32 idx;
    if (gMusyXActiveFlag != 0) {
        h = vhResolvePL(h);
        while ((s32)h != -1) {
            idx = h & 0xFF;
            if (gChanRecPL[idx].id == h) {
                r = 0;
                gChanRecPL[idx].flags |= 8;
            }
            h = gChanRecPL[idx].next;
        }
    }
    return r;
}

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

extern u32 D_main_800A0F54;
extern s32 D_main_bss_8013ACD0[];
s32 isAudioSlotActive(s32);
static __inline__ s32 budgetCCW(u8 *ch) {
    s32 *base = D_main_bss_8013ACD0;
    s32 *p;
    u8 idx = ch[0x4F];
    if (idx != 0xFF) {
        p = base + idx;
    } else {
        p = base + 8;
    }
    return *p;
}
static __inline__ void scaleByBudgetCCW(u32 *p, u8 *ch) {
    *p = ((*p * 32000) / budgetCCW(ch)) << 3;
}
u8 computeChannelWaitDurationImpl(u8 *ch, u8 *op) __asm__("computeChannelWaitDuration");
u8 computeChannelWaitDurationImpl(u8 *ch, u8 *op) {
    u32 r;
    if ((*(u32 *)op >> 8) & 1) {
        if ((*(u32 *)(ch + 0x24) & 0x30) == 0) {
            return 0;
        }
        *(u32 *)(ch + 0x24) |= 4;
    } else {
        *(u32 *)(ch + 0x24) &= ~4;
    }
    if (op[0] & 1) {
        if (!(*(u32 *)(ch + 0x24) & 0x20) && !(isAudioSlotActive(ch[0x67]) & 0xFF)) {
            return 0;
        }
        *(u32 *)(ch + 0x24) |= 0x80000;
    } else {
        *(u32 *)(ch + 0x24) &= ~0x80000;
    }
    if (*(u16 *)op & 1) {
        u32 seed = D_main_800A0F54 * 0xA8351D63;
        r = (seed >> 6) & 0xFFFF;
        r = r % (u32)*(u16 *)(op + 4);
        D_main_800A0F54 = seed;
        *(u32 *)(ch + 0x40) = r;
    } else {
        *(u32 *)(ch + 0x40) = *(u16 *)(op + 4);
    }
    if (*(u32 *)(ch + 0x40) != 0xFFFF) {
        if ((*(u32 *)(op + 4) >> 8) & 1) {
            *(u32 *)(ch + 0x40) = *(u32 *)(ch + 0x40) << 8;
        } else {
            scaleByBudgetCCW((u32 *)(ch + 0x40), ch);
        }
    }
    return *(u32 *)(ch + 0x40) != 0;
}

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

s32 bucketLookupFF(u32) __asm__("factor5BucketedTableLookupValue");
s32 soundMacroOpGosubLoopCounterFiftyFour(u8 *ch, u8 *cmdArg) {
    register u8 *cmd asm("$17") = cmdArg;
    s32 v;
    u32 c = *(u32 *)cmd;
    s32 unused[2];

    if (*(u16 *)(ch + 0x54) >= cmd[2]) {
        v = bucketLookupFF(c >> 16);
        if (v != 0) {
            *(s32 *)ch = v;
            *(s32 *)(ch + 4) = v + *(u16 *)(cmd + 6) * 8;
        }
    }
    return 0;
}

s32 bucketLookupTH(u32) __asm__("factor5BucketedTableLookupValue");
s32 soundMacroOpGosubLoopCounterThirty(u8 *ch, u8 *cmdArg) {
    register u8 *cmd asm("$17") = cmdArg;
    s32 v;
    u32 c = *(u32 *)cmd;
    s32 unused[2];

    if (*(u16 *)(ch + 0x30) >= cmd[2]) {
        v = bucketLookupTH(c >> 16);
        if (v != 0) {
            *(s32 *)ch = v;
            *(s32 *)(ch + 4) = v + *(u16 *)(cmd + 6) * 8;
        }
    }
    return 0;
}

s32 bucketLookupML(u32) __asm__("factor5BucketedTableLookupValue");
u16 evalModRecML(u8 *, u8 *) __asm__("evaluateVoiceModulatorRecord");
s32 soundMacroOpGosubModulatorLoop(u8 *ch, u8 *cmd) {
    s32 v;
    u32 c;
    u8 x;
    s32 unused[2];

    if (ch[0x4E] != 0xFF) {
        x = (u8)(evalModRecML(ch, ch + 0x11A) >> 7);
        c = *(u32 *)cmd;
        if (x >= cmd[2]) {
            v = bucketLookupML(c >> 16);
            if (v != 0) {
                *(s32 *)ch = v;
                *(s32 *)(ch + 4) = v + *(u16 *)(cmd + 6) * 8;
            }
        }
    }
    return 0;
}

s32 bucketLookupRL(u32) __asm__("factor5BucketedTableLookupValue");
extern u32 gRandRL __asm__("D_main_800A0F54");
s32 soundMacroOpGosubRandomLoop(u8 *ch, u8 *cmdArg) {
    register u8 *cmd asm("$17") = cmdArg;
    s32 v;
    u32 c;
    u32 t;
    s32 unused[2];

    if (ch[0x4E] != 0xFF) {
        __asm__("" : "=r"(cmd) : "0"(cmd));
        t = gRandRL * 0xA8351D63;
        c = *(u32 *)cmd;
        gRandRL = t;
        if ((u8)(t >> 6) >= cmd[2]) {
            v = bucketLookupRL(c >> 16);
            if (v != 0) {
                *(s32 *)ch = v;
                *(s32 *)(ch + 4) = v + *(u16 *)(cmd + 6) * 8;
            }
        }
    }
    return 0;
}

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

s32 startNoteOnVoiceK(s32, u16, s32, u8, s32, s32, s32, s32, s32, s32, s32) __asm__("startNoteOnVoice");
extern u8 D_main_bss_8013D894[];
s32 soundMacroOpKeyOnNote(u8 *ch, u8 *cmd) {
    u32 w;
    s32 n;
    u32 key;
    s32 vel;
    s32 r;
    s32 unused[2];
    w = *(u32 *)cmd;
    n = *(u16 *)(ch + 0x52) + ((s32)(w << 16) >> 24);
    key = ((w >> 16) << 16) | (cmd[5] << 8) | cmd[6];
    if (n >= 0) {
        vel = 0x7F;
        if (n < 0x80) {
            vel = n;
        }
    } else {
        vel = 0;
    }
    n = vel;
    if (ch[0x50] != 0) {
        n |= 0x80;
    }
    r = startNoteOnVoiceK(key, *(u16 *)(ch + 0xB6), n & 0xFF, ch[0x31], ch[0x39], ch[0x4E], ch[0x4F], *(u16 *)(cmd + 6), ch[0x2F], 0, ch[0xBA]);
    *(s32 *)(ch + 0x10) = r;
    *(s32 *)(D_main_bss_8013D894 + (r & 0xFF) * 0x17C) = *(s32 *)(ch + 0x64);
    return 0;
}

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

extern u8 gGlobRegsSG[] __asm__("D_main_bss_80148C58");
s32 soundMacroOpStoreGlobalRegister(u8 *ch, u8 *cmd) {
    s32 unused[2];

    gGlobRegsSG[cmd[2]] = *(u16 *)cmd;
    return 0;
}

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

s32 musyxComputeNotePlaybackRate(u8, u32);
static __inline__ s32 sweepStepAB(u8 *a) {
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
s32 soundMacroOpStartNoteAbsoluteSweep(u8 *ch, u8 *cmd) {
    u8 note = cmd[2];
    *(u16 *)(ch + 0x54) = note;
    *(s32 *)(ch + 0x70) = musyxComputeNotePlaybackRate(note, *(u32 *)(ch + 0x60)) & 0xFFFF;
    *(u8 *)(ch + 0xBC) = *(u16 *)cmd;
    *(s32 *)(ch + 0x70) = (*(s32 *)(ch + 0x70) + sweepStepAB(ch)) << 16;
    *(u32 *)cmd = 4;
    return computeChannelWaitDuration(ch, cmd);
}

s32 musyxComputeNotePlaybackRate(u8, u32);
static __inline__ s32 sweepStepRE(u8 *a) {
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
u8 soundMacroOpStartNoteRelativeSweep(u8 *ch, u8 *cmd) {
    u32 c = *(volatile u32 *)cmd;
    u16 b;

    if ((c >> 24) == 0) {
        b = *(u16 *)(ch + 0x54);
    } else {
        b = *(u16 *)(ch + 0x52);
    }
    b += (u8)(c >> 8);
    *(u16 *)(ch + 0x54) = b;
    *(s32 *)(ch + 0x70) = musyxComputeNotePlaybackRate(ch[0x55], *(u32 *)(ch + 0x60)) & 0xFFFF;
    *(u8 *)(ch + 0xBC) = *(u16 *)cmd;
    *(s32 *)(ch + 0x70) = (*(s32 *)(ch + 0x70) + sweepStepRE(ch)) << 16;
    *(u32 *)cmd = 4;
    return computeChannelWaitDuration(ch, cmd);
}

s32 musyxComputeNotePlaybackRate(u8, u32);
static __inline__ s32 sweepStepTR(u8 *a) {
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
u8 soundMacroOpStartNoteTransposedSweep(u8 *ch, u8 *cmd) {
    u16 note = ch[0xBD] + cmd[2];
    *(u16 *)(ch + 0x54) = note;
    *(s32 *)(ch + 0x70) = musyxComputeNotePlaybackRate(note, *(u32 *)(ch + 0x60)) & 0xFFFF;
    *(u8 *)(ch + 0xBC) = *(u16 *)cmd;
    *(s32 *)(ch + 0x70) = (*(s32 *)(ch + 0x70) + sweepStepTR(ch)) << 16;
    *(u32 *)cmd = 4;
    return computeChannelWaitDuration(ch, cmd);
}

typedef struct { u32 w0; u32 w4; u32 w8; u32 wC; u32 w10; u32 w14; u8 b18; } SInfoPK;
extern SInfoPK gSInfoPK __asm__("D_main_bss_8013ACA0");
extern u32 gSInfoW0PK __asm__("D_main_bss_8013ACA0");
extern u32 gSInfoW4PK __asm__("D_main_bss_8013ACA4");
s32 musyxComputeNotePlaybackRate(u8, u32);
void musyxInitVoiceFromSamplePK(u8, u8 *, s32) __asm__("musyxInitVoiceFromSample");
static __inline__ s32 lookupWprPK(s16 key, u8 *out) {
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
static __inline__ s32 sweepStepPK(u8 *a, u16 v) {
    s32 r;
    if (*(s8 *)(a + 0xBC) != 0) {
        if (*(s8 *)(a + 0xBC) > 0) {
            r = (((scaleFixedPointByRatioA(v) & 0xFFFF) - *(s32 *)(a + 0x70)) * *(s8 *)(a + 0xBC)) / 100;
        } else {
            r = ((*(s32 *)(a + 0x70) - (scaleFixedPointByRatioB(v) & 0xFFFF)) * *(s8 *)(a + 0xBC)) / 100;
        }
    } else {
        r = 0;
    }
    return r;
}
s32 soundMacroOpPlaySampleKeymap(u8 *ch, u32 *cmd) {
    s32 flag;
    u8 k;
    u32 f;
    u16 r;
    if (lookupWprPK(cmd[0] >> 8, (u8 *)&gSInfoPK) == 0) {
        if (*(u8 *)cmd == 0) {
            gSInfoPK.w8 = cmd[1];
        } else {
            gSInfoPK.w8 = (u32)((0x7F - *(u16 *)(ch + 0x30)) * cmd[1]) / 127;
        }
        if (gSInfoPK.w8 >= gSInfoPK.wC) {
            gSInfoPK.w8 = gSInfoPK.wC - 1;
        }
        k = ch[0x67];
        if (!(*(u32 *)(ch + 0x24) & 0x200)) {
            musyxInitVoiceFromSamplePK(k, (u8 *)&gSInfoPK, 1);
        } else {
            musyxInitVoiceFromSamplePK(k, (u8 *)&gSInfoPK, 0);
        }
        *(u32 *)(ch + 0x9C) = musyxComputeNotePlaybackRate(ch[0xBD], gSInfoW0PK) << 16;
        *(u32 *)(ch + 0x60) = gSInfoW0PK;
        f = *(u32 *)(ch + 0x24) | 0x20;
        *(u32 *)(ch + 0x5C) = gSInfoW4PK;
        *(u32 *)(ch + 0x24) = f;
        if (!(f & 0x100)) {
            r = musyxComputeNotePlaybackRate(ch[0x55], *(u32 *)(ch + 0x60)) & 0xFFFF;
            *(s32 *)(ch + 0x70) = r;
            *(s32 *)(ch + 0x70) = (*(s32 *)(ch + 0x70) + sweepStepPK(ch, r)) << 16;
            cmd[0] = 4;
            return computeChannelWaitDuration(ch, cmd);
        }
    }
    return 0;
}

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

s32 soundMacroOpSetProgramTableValue(u8 *ch, u32 *cmd) {
    u32 c = *(volatile u32 *)cmd;
    u8 *e = ch + ((c >> 8) & 0xFF) * 12;
    s32 x = *(s32 *)(e + 0x168);
    s32 t = (c >> 16) << 8;

    if (x != 0) {
        *(s32 *)(e + 0x164) = 0;
    }
    *(s32 *)(e + 0x168) = *(volatile s32 *)&t;
    return 0;
}

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

extern s32 D_main_bss_8013AF0C;
extern u8 D_main_bss_8013AC58[];
extern s16 D_main_bss_8013AC5C;
extern u8 *D_main_bss_8013AC60;
extern u8 D_main_bss_80148C68[];
s32 compareHalfwordAtOffset4_v2(u8 *a, u8 *b);
static __inline__ u8 *bsrchSVV(u8 *key, u8 *base, s32 n, s32 size, s32 (*cmp)(u8 *, u8 *)) {
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
typedef struct { u8 pad[0x30]; u32 vol; u32 vol2; } SVV_V;
s32 soundMacroSetVoiceVolume(SVV_V *v, u8 *op) {
    u32 vol;
    u8 *tbl;
    u8 *found;
    if (op[6] == 0) {
        v->vol = (v->vol * op[2]) >> 7;
    } else {
        v->vol = (v->vol2 * op[2]) >> 7;
    }
    v->vol += op[1] << 16;
    if (v->vol > 0x7F0000) {
        v->vol = 0x7F0000;
    }
    vol = v->vol;
    if (op[0] != 0) {
        D_main_bss_8013AC5C = op[0];
        found = bsrchSVV(D_main_bss_8013AC58, D_main_bss_80148C68, D_main_bss_8013AF0C, 8, compareHalfwordAtOffset4_v2);
        D_main_bss_8013AC60 = found;
        tbl = 0;
        if (found != 0) {
            tbl = *(u8 **)found;
        }
        if (tbl != 0) {
            u32 idx = vol >> 16;
            u32 fr = vol & 0xFFFF;
            if (idx < 0x7F) {
                u8 *p = (u8 *)(idx + (u32)tbl);
                u32 hi = p[1];
                u32 lo = p[0];
                vol = (lo << 16) + (hi - lo) * fr;
            } else {
                vol = tbl[idx] << 16;
            }
        }
        v->vol = vol;
    } else {
        v->vol = vol;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", soundMacroSetupVolumeRamp);

extern u32 D_main_800A0F54;
s32 soundMacroOpStartNoteAbsoluteSweep(u8 *, u8 *);
typedef struct { u32 w0; u32 w1; } PRKOp;
s32 soundMacroPlayRandomKeyNote(u8 *v, u8 *op) {
    u8 lo, hi, vel;
    u16 r;
    u32 w, fw, vs;
    s32 unused[2];
    s32 rem;
    if (op[6] == 0) {
        w = *(u32 *)op;
        lo = w >> 8;
        hi = w >> 24;
        if (hi < lo) {
            u8 t = lo;
            lo = hi;
            hi = t;
        }
    } else {
        s32 base = *(u16 *)(v + 0x54);
        s32 a = base + op[0];
        s16 b = base - op[2];
        if ((s16)b >= 0) {
            if ((s16)b < 0x80) {
                lo = b;
            } else {
                lo = 0x7F;
            }
        } else {
            lo = 0;
        }
        if ((s16)a >= 0) {
            if ((s16)a < 0x80) {
                hi = a;
            } else {
                hi = 0x7F;
            }
        } else {
            hi = 0;
        }
    }
    if (op[7] != 0) {
        D_main_800A0F54 *= 0xA8351D63;
        r = D_main_800A0F54 >> 6;
        vel = r % 201 - 100;
    } else {
        vel = op[1];
    }
    ((u32 *)op)[1] = 0;
    D_main_800A0F54 *= 0xA8351D63;
    r = D_main_800A0F54 >> 6;
    rem = r % (hi - lo + 1);
    vs = vel << 16;
    fw = ((lo + rem) << 8) | 0x19;
    *(u32 *)op = vs | fw;
    soundMacroOpStartNoteAbsoluteSweep(v, op);
    return 0;
}

s32 soundMacroSetFlagBitVibrato(u8 *ch) {
    *(u32 *)(ch + 0x24) |= 0x20000;
    return 0;
}

s32 soundMacroSetFlagBitTremolo(u8 *ch) {
    *(u32 *)(ch + 0x24) |= 0x40000;
    return 0;
}


typedef struct { u8 ctrl; u8 op; s16 scale; } SqModEnt;
typedef struct { SqModEnt e[4]; u8 count; } SqModRec;
__inline__ void soundMacroPushEffectEvent(SqModRec *rec, u8 *cmd) {
    u8 n = rec->count;
    u32 c;
    if (n < 4) {
        rec->count = n + 1;
        c = *(u32 *)cmd >> 8;
        switch ((u8)c) {
        case 0x80:
            c = 0x80;
            break;
        case 0x81:
            c = 0x82;
            break;
        case 0x82:
            c = 0xA0;
            break;
        case 0x83:
            c = 0xA1;
            break;
        case 0x84:
            c = 0x83;
            break;
        case 0x85:
            c = 0x84;
            break;
        }
        rec->e[n].ctrl = c;
        rec->e[n].op = *(u32 *)(cmd + 4);
        rec->e[n].scale = (*(s16 *)cmd << 8) / 100;
    }
}


s32 seqCmdHandler40(u8 *chArg, u8 *cmd) {
    register u8 *ch asm("$6") = chArg;
    if ((((*(u32 *)(ch + 0x24) >> 20) & 1) == 0) | (cmd[7] == 0)) {
        *(u32 *)(ch + 0x24) |= 0x100000;
        ch[0xD0] = 0;
    }
    soundMacroPushEffectEvent((SqModRec *)(ch + 0xC0), cmd);
    return 0;
}


s32 seqCmdHandler41(u8 *chArg, u8 *cmd) {
    register u8 *ch asm("$6") = chArg;
    if ((((*(u32 *)(ch + 0x24) >> 21) & 1) == 0) | (cmd[7] == 0)) {
        *(u32 *)(ch + 0x24) |= 0x200000;
        ch[0xE2] = 0;
    }
    soundMacroPushEffectEvent((SqModRec *)(ch + 0xD2), cmd);
    return 0;
}


s32 seqCmdHandler42(u8 *chArg, u8 *cmd) {
    register u8 *ch asm("$6") = chArg;
    if ((((*(u32 *)(ch + 0x24) >> 22) & 1) == 0) | (cmd[7] == 0)) {
        *(u32 *)(ch + 0x24) |= 0x400000;
        ch[0x106] = 0;
    }
    soundMacroPushEffectEvent((SqModRec *)(ch + 0xF6), cmd);
    return 0;
}


s32 seqCmdHandler43(u8 *chArg, u8 *cmd) {
    register u8 *ch asm("$6") = chArg;
    if ((((*(u32 *)(ch + 0x24) >> 23) & 1) == 0) | (cmd[7] == 0)) {
        *(u32 *)(ch + 0x24) |= 0x800000;
        ch[0x12A] = 0;
    }
    soundMacroPushEffectEvent((SqModRec *)(ch + 0x11A), cmd);
    return 0;
}


s32 seqCmdHandler44(u8 *chArg, u8 *cmd) {
    register u8 *ch asm("$6") = chArg;
    if ((((*(u32 *)(ch + 0x24) >> 25) & 1) == 0) | (cmd[7] == 0)) {
        *(u32 *)(ch + 0x24) |= 0x2000000;
        ch[0x13C] = 0;
    }
    soundMacroPushEffectEvent((SqModRec *)(ch + 0x12C), cmd);
    return 0;
}


s32 seqCmdHandler45(u8 *chArg, u8 *cmd) {
    register u8 *ch asm("$6") = chArg;
    if ((((*(u32 *)(ch + 0x24) >> 25) & 1) == 0) | (cmd[7] == 0)) {
        *(u32 *)(ch + 0x24) |= 0x2000000;
        ch[0x14E] = 0;
    }
    soundMacroPushEffectEvent((SqModRec *)(ch + 0x13E), cmd);
    return 0;
}


s32 seqCmdHandler46(u8 *chArg, u8 *cmd) {
    register u8 *ch asm("$6") = chArg;
    if ((((*(u32 *)(ch + 0x24) >> 24) & 1) == 0) | (cmd[7] == 0)) {
        *(u32 *)(ch + 0x24) |= 0x1000000;
        ch[0x160] = 0;
    }
    soundMacroPushEffectEvent((SqModRec *)(ch + 0x150), cmd);
    return 0;
}

s32 musyxComputeNotePlaybackRate(u8, u32);
static __inline__ void setChByteAltRV(u8 a, u8 b, u8 v) {
    if (b != 0xFF) {
        D_main_bss_801483D0[b][a] = v;
        return;
    }
    D_main_bss_80142018[a] = v;
}
void refreshVoicePlaybackRate(u8 *v) {
    if (v[0xA0] != 1) {
        *(u32 *)(v + 0x94) = *(u32 *)(v + 0x98);
    } else {
        *(u32 *)(v + 0x94) = 0;
    }
    *(u32 *)(v + 0x9C) = musyxComputeNotePlaybackRate(v[0xBD], *(u32 *)(v + 0x60)) << 16;
    if (v[0x4E] != 0xFF) {
        setChByteAltRV(v[0x4E], v[0x4F], 1);
    }
}

extern s32 D_main_bss_8013ACD0[];
extern u8 D_main_bss_80142018[];
extern u8 D_main_bss_801483D0[][16];
s32 musyxComputeNotePlaybackRate(u8, u32);
static __inline__ s32 budgetSPT(u8 *ch) {
    s32 *base = D_main_bss_8013ACD0;
    s32 *p;
    u8 idx = ch[0x4F];
    if (idx != 0xFF) {
        p = base + idx;
    } else {
        p = base + 8;
    }
    return *p;
}
static __inline__ void scaleByBudgetSPT(u32 *p, u8 *ch) {
    *p = ((*p * 32000) / budgetSPT(ch)) << 3;
}
static __inline__ void setByteAltSPT(u8 a, u8 b, u8 v) {
    if (b != 0xFF) {
        D_main_bss_801483D0[b][a] = v;
        return;
    }
    D_main_bss_80142018[a] = v;
}
s32 soundMacroSetPitchTarget(u8 *ch, u8 *op) {
    u32 v;
    u32 bit;
    u8 a;
    ch[0xA0] = *(u16 *)op;
    bit = (*(u32 *)(op + 4) >> 8) & 1;
    v = *(u16 *)(op + 4);
    if (bit) {
        v = v << 8;
    } else {
        scaleByBudgetSPT(&v, ch);
    }
    *(u32 *)(ch + 0x98) = v;
    switch (op[2]) {
    case 0:
        *(u32 *)(ch + 0x24) = (*(u32 *)(ch + 0x24) & ~0x800) | 0x1000;
        a = ch[0x4E];
        if (a != 0xFF) {
            setByteAltSPT(a, ch[0x4F], 0);
        }
        break;
    case 1:
        if ((*(u32 *)(ch + 0x24) & 0x800) == 0) {
            if (ch[0xA0] != 1) {
                *(u32 *)(ch + 0x94) = v;
            } else {
                *(u32 *)(ch + 0x94) = 0;
            }
            *(u32 *)(ch + 0x9C) = musyxComputeNotePlaybackRate(ch[0xBD], *(u32 *)(ch + 0x60)) << 16;
            a = ch[0x4E];
            if (a != 0xFF) {
                setByteAltSPT(a, ch[0x4F], 1);
            }
        }
        *(u32 *)(ch + 0x24) = 0x1800;
        break;
    }
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/main/832A0", jtbl_main_8003DBF0);

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

// NOTE: ~10 rows: h param gets copied (move a1,a0) and r lands a2 instead of a1; template as spreadVoiceParamPairLocked + release inline
extern u8 D_main_8013D880[];
void freeSynthVoiceFromActiveList();
void beginVoiceFadeRelease(s32 i);
s32 stopVoicesByHandle(s32 h) {
    s32 r = -1;
    s32 idx;
    s32 off;
    u8 *v;
    if (gMusyXActiveFlag != 0) {
        h = vhResolvePL(h);
        while (h != -1) {
            idx = h & 0xFF;
            off = idx * 0x17C;
            if (gChanRecPL[idx].id == h) {
                if (*(s32 *)(D_main_8013D880 + off) != 0) {
                    v = D_main_8013D880 + off;
                    freeSynthVoiceFromActiveList(v);
                    *(s32 *)(v + 0x64) = -1;
                    *(s32 *)v = 0;
                    v[0x2E] = 0;
                    *(s32 *)(v + 0x28) = 0;
                    *(u32 *)(v + 0x24) &= ~3;
                }
                beginVoiceFadeRelease(idx);
                r = 0;
            }
            h = gChanRecPL[idx].next;
        }
    }
    return r;
}

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


typedef struct { s32 cur; s32 target; s32 step; s32 time; s32 handle; u8 type; u8 b15; u8 pad16[0x12]; } FaderDA;
extern FaderDA gFaderDA[] __asm__("D_main_bss_80141B18");
void dispatchAudioCommand(u8 vol, u16 time, u8 which, s32 type, s32 handle) {
    u32 i;
    s32 t;
    u8 ty;

    if (time == 0) {
        time++;
    }
    t = time << 8;
    switch (which) {
    case 0xFF:
        for (i = 0; i < 32; i++) {
            if (gFaderDA[i].type < 2) {
                gFaderDA[i].target = vol << 16;
                gFaderDA[i].time = *(s32 *)&t;
                gFaderDA[i].step = (gFaderDA[i].target - gFaderDA[i].cur) / time;
                gFaderDA[i].handle = -1;
            }
        }
        break;
    case 0xFC:
        for (i = 0; i < 32; i++) {
            if ((u8)(gFaderDA[i].type - 2) < 2) {
                gFaderDA[i].target = vol << 16;
                gFaderDA[i].time = *(s32 *)&t;
                gFaderDA[i].step = (gFaderDA[i].target - gFaderDA[i].cur) / time;
                gFaderDA[i].handle = -1;
            }
        }
        break;
    case 0xFA:
        ty = 2;
        goto loop;
    case 0xFB:
        ty = 3;
        goto loop;
    case 0xFD:
        ty = 0;
        goto loop;
    case 0xFE:
        ty = 1;
    loop:
        for (i = 0; i < 32; i++) {
            if (gFaderDA[i].type == ty) {
                gFaderDA[i].target = vol << 16;
                gFaderDA[i].time = *(s32 *)&t;
                gFaderDA[i].step = (gFaderDA[i].target - gFaderDA[i].cur) / time;
                gFaderDA[i].handle = -1;
            }
        }
        break;
    default:
        gFaderDA[which].target = vol << 16;
        gFaderDA[which].time = t;
        gFaderDA[which].b15 = type;
        gFaderDA[which].handle = handle;
        gFaderDA[which].step = (gFaderDA[which].target - gFaderDA[which].cur) / time;
        break;
    }
}

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

extern u8 gMusyXActiveFlag;
extern u8 gSlotBusyAA __asm__("D_main_bss_8013ACF4");
extern u8 gNumSlotsAA __asm__("D_main_bss_80141AD0");
s32 audioStubReturnZero();
s32 isAudioSlotActive(s32);
s32 anyAudioSlotActive(void) {
    u8 r = 0;
    s32 i;

    if (gMusyXActiveFlag) {
        gSlotBusyAA = 1;
        if (!(u8)audioStubReturnZero()) {
            for (i = 0; i < gNumSlotsAA; i++) {
                r |= isAudioSlotActive(i);
            }
        } else {
            r = 1;
        }
        gSlotBusyAA = 0;
    }
    return r == 0;
}

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

extern u8 *gAiBufsRL[16] __asm__("D_main_bss_801496B0");
extern volatile u8 gAiBufIdxRL __asm__("D_main_bss_801496F0");
extern OSMesgQueue gAiQueueRL __asm__("D_main_bss_80149670");
void *rs_malloc(u32, u16);
void rs_memset(u8 *, s32, s32);
void runAiAudioStreamPlaybackLoop(void *arg) {
    s32 i;
    u8 done;
    OSMesg msg;

    gAiBufsRL[0] = rs_malloc(0x3000, 0x80);
    for (i = 1; i < 16; i++) {
        gAiBufsRL[i] = gAiBufsRL[i - 1] + 0x300;
    }
    rs_memset(gAiBufsRL[0], 0, 0x3000);
    done = 0;
    osWritebackDCache(gAiBufsRL[0], 0x3000);
    gAiBufIdxRL = 0;
    osAiSetNextBuffer(gAiBufsRL[0], 0x300);
    do {
        osRecvMesg(&gAiQueueRL, &msg, OS_MESG_BLOCK);
        switch (*(u8 *)msg) {
        case 1:
            gAiBufIdxRL = (gAiBufIdxRL + 1) % 16;
            osAiSetNextBuffer(gAiBufsRL[gAiBufIdxRL], 0x300);
            break;
        case 0xFF:
            done = 1;
            break;
        }
    } while (!done);
}

extern void *D_main_bss_80149770;
extern s32 D_main_bss_801496F4;
extern u32 D_main_bss_8014976C;
extern s32 D_main_bss_80149768;
typedef struct { void *buf; u32 sz; u16 a8; u16 aA; u32 w[8]; u16 b[10]; u16 c[4]; } TempoSchedBTS;
void *rs_malloc(u32, u16);
void rs_memset(u8 *, s32, s32);
void factor5MutexAcquire(void);
void factor5MutexRelease(void);
void buildSongTempoScheduleImpl(u8 *song) __asm__("buildSongTempoSchedule");
void buildSongTempoScheduleImpl(u8 *song) {
    TempoSchedBTS *p;
    register u32 sz asm("$17");
    register u32 q asm("$3");
    register u32 m asm("$2");
    u32 i;
    void *buf;
    if (D_main_bss_80149770 != 0) {
        sz = (u32)(*(u16 *)song * D_main_bss_801496F4) / 1000;
        q = sz / 192;
        m = q * 192;
        sz = m + 0xC0;
        p = rs_malloc(0x48, 0);
        buf = D_main_bss_80149770;
        p->buf = buf;
        rs_memset(buf, 0, sz * 2);
        osWritebackDCache(p->buf, sz * 2);
        p->sz = sz;
        p->aA = song[0x1B] << 8;
        p->a8 = song[0x1A];
        for (i = 0; i < song[0x1A]; i++) {
            p->w[i] = (((u32)(D_main_bss_801496F4 * ((u16 *)song)[1 + i]) / 1000) + 3) & 0xFFFC;
            p->b[i] = *(song + i + 0x12) << 8;
        }
        if (song[0x1C] == 1) {
            for (i = 0; i < 4; i++) {
                p->c[i] = ((u16 *)(song + 0x1E))[i];
            }
        } else {
            p->c[0] = 0;
            p->c[1] = 0;
            p->c[2] = 0;
            p->c[3] = 0x7FFF;
        }
        osWritebackDCache(p, 0x48);
        factor5MutexAcquire();
        D_main_bss_8014976C = 0;
        D_main_bss_80149768 = (s32)p;
        factor5MutexRelease();
    }
}


typedef struct { u8 b0; u8 pad1[0x83]; u8 b84; u8 b85; u8 pad86[2]; } SongChSC;
extern SongChSC *gChansA_SC __asm__("D_main_bss_801496F8");
extern SongChSC *gChansB_SC __asm__("D_main_bss_801496FC");
extern u16 gNumChSC __asm__("D_main_bss_80149700");
extern u8 gB9702SC __asm__("D_main_bss_80149702");
extern u16 gH9710SC __asm__("D_main_bss_80149710");
extern u16 gH9712SC __asm__("D_main_bss_80149712");
extern u16 gNumBufSC __asm__("D_main_bss_8014974E");
extern void *gBufA_SC __asm__("D_main_bss_80149758");
extern void *gBufB_SC __asm__("D_main_bss_8014975C");
extern u16 gNumSlotSC __asm__("D_main_bss_80149704");
extern void *gSlotA_SC __asm__("D_main_bss_80149708");
extern void *gSlotB_SC __asm__("D_main_bss_8014970C");
extern u8 *gMixBufSC __asm__("D_main_bss_80149764");
void allocateSongChannelArray(u16 nch, u32 rate) {
    u16 i;

    gNumChSC = nch;
    gChansA_SC = gChansB_SC = rs_malloc(nch * sizeof(SongChSC), 0);
    gB9702SC = 0;
    gH9710SC = 0;
    gH9712SC = 0;
    for (i = 0; i < gNumChSC; i++) {
        gChansB_SC[i].b0 = 0;
        gChansB_SC[i].b85 = 0;
        gChansB_SC[i].b84 = 0xFF;
    }
    gNumBufSC = (u32)((f32)rate / 50.0f / 192.0f * 1.2f) + 1;
    gBufA_SC = rs_malloc(gNumBufSC * 0xA10, 0);
    gBufB_SC = rs_malloc(gNumBufSC * 0xA10, 0);
    gNumSlotSC = gNumBufSC * (nch + 1);
    gSlotA_SC = rs_malloc(gNumSlotSC * sizeof(SongChSC), 0);
    gSlotB_SC = rs_malloc(gNumSlotSC * sizeof(SongChSC), 0);
    gMixBufSC = rs_malloc(0x298, 0);
    rs_memset(gMixBufSC, 0, 0x298);
    osWritebackDCache(gMixBufSC, 0x298);
}

extern const f64 D_main_8003DD68;
extern const f32 D_main_8003DD70;
extern const f32 D_main_8003DD74;
extern const f32 D_main_8003DD78;
extern const f32 D_main_8003DD7C;
extern const f64 D_main_8003DD80;
extern const f32 D_main_8003DD88;
extern const f32 D_main_8003DD8C;
extern u16 D_main_bss_8014971C;
extern u32 D_main_bss_80149720;
extern u8 *D_main_bss_80149728;
extern OSMesgQueue D_main_bss_80149730;
extern OSMesg D_main_bss_80149748;
extern u8 D_main_bss_8014974C;
extern u16 D_main_800A1760[];
void *rs_malloc(u32, u16);
void buildSongDecodeBufferRing(s32);
void initSampleStreamBlockCache(u16);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DD68);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DD70);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DD74);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DD78);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DD7C);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DD80);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DD88);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DD8C);

void setupSongRenderBuffers(u16 n, u32 x, u8 mode) {
    f64 d;
    f32 f;
    u32 q;
    u32 t1;
    u32 sz;
    u32 nn;
    register u32 k asm("$4");
    nn = n;
    d = (s32)x;
    if ((s32)x >= 0) goto L1;
    d = d + D_main_8003DD68;
L1:
    f = (f32)d / D_main_8003DD70 * D_main_8003DD74 / D_main_8003DD78;
    if (f >= D_main_8003DD7C) goto L2;
    q = (s32)f;
    goto L3;
L2:
    q = (s32)(f - D_main_8003DD7C) | 0x80000000;
L3:
    t1 = nn * ((u16)q + 1);
    k = 0x310;
    D_main_bss_80149720 = k;
    D_main_bss_8014971C = t1;
    sz = (u16)t1 * k;
    d = (s32)sz;
    if ((s32)sz >= 0) goto L4;
    d = d + D_main_8003DD80;
L4:
    f = (f32)d * D_main_8003DD88;
    if (f >= D_main_8003DD8C) goto L5;
    q = (s32)f;
    goto L6;
L5:
    q = (s32)(f - D_main_8003DD8C) | 0x80000000;
L6:
    D_main_bss_80149720 = ((((q + 0x3F) >> 6) * 40) + 0xF) & 0xFFF0;
    D_main_bss_80149728 = rs_malloc(D_main_bss_8014971C * 24, 0);
    osCreateMesgQueue(&D_main_bss_80149730, &D_main_bss_80149748, 1);
    D_main_bss_8014974C = 0;
    buildSongDecodeBufferRing(D_main_bss_8014971C);
    initSampleStreamBlockCache(D_main_800A1760[mode] * n);
}


typedef struct {
    u8 b0;
    u8 keyOn;
    u8 pad2[0x28];
    u16 decayTime;
    f32 sustain;
    u16 releaseTime;
    u8 pad32[0x26];
    u16 duration;
    u8 pad5A[2];
    f32 cur;
    u32 elapsed;
    f32 target;
    f32 start;
    u8 state;
} EnvVE;
extern u32 gRateVE __asm__("D_main_bss_801496F4");
void advanceVolumeFadeEnvelope(EnvVE *e, u16 dt, u8 *done) {
    u32 step = (dt * 32000 / gRateVE) << 11;
    f32 t;

    if (e->keyOn == 0 && e->state != 3) {
        e->state = 3;
        e->target = 0.0f;
        e->elapsed = 0;
        e->start = e->cur;
        e->duration = e->releaseTime;
    } else if ((u16)(e->elapsed >> 16) >= e->duration) {
        switch (e->state) {
        case 0:
            e->state = 1;
            e->elapsed = 0;
            e->start = 1.0f;
            e->target = e->sustain;
            e->duration = e->decayTime;
            break;
        case 1:
            e->state = 2;
            e->start = e->sustain;
            e->target = e->sustain;
            e->cur = e->sustain;
            return;
        case 3:
            *done = 0;
            e->cur = 0.0f;
            return;
        }
    }
    if (e->duration != 0) {
        t = (f32)e->elapsed / (f32)(e->duration << 16);
    } else {
        t = 1.0f;
    }
    e->cur = (e->target - e->start) * t + e->start;
    e->elapsed += step;
}

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

void moveSampleBlockToFront(SSBNode *n) {
    SSBNode *t;

    if (n != D_main_bss_801499B4) {
        if (n->next != NULL) {
            n->next->prev = n->prev;
        }
        if (n->prev != NULL) {
            n->prev->next = n->next;
        } else {
            D_main_bss_801499E4 = n->next;
        }
        t = D_main_bss_801499B4;
        D_main_bss_801499B4 = n;
        t->next = n;
        n->prev = t;
        n->next = NULL;
    }
}

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

INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DDA8);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DDB0);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DDB8);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DDC0);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DDC8);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DDD0);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DDD8);
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DDE0);

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxRenderVoiceSamples);


typedef struct { s32 a; s32 b; s32 c; } Copy12KO;
extern u8 *gFramesKO __asm__("D_main_bss_80149750");
extern u16 gFrameIdxKO __asm__("D_main_bss_80149760");
f64 truncDouble(f64);
#define KB(p, o) (*(u8 *)((p) + (o)))
#define KH(p, o) (*(u16 *)((p) + (o)))
#define KS(p, o) (*(s16 *)((p) + (o)))
#define KW(p, o) (*(s32 *)((p) + (o)))
#define KD(p, o) (*(f64 *)((p) + (o)))
#define KC(p, o) (*(Copy12KO *)((p) + (o)))
void musyxKeyOnVoice(u8 *v) {
    u8 *frame = gFramesKO + gFrameIdxKO * 0xA10;
    u8 *c = frame + (KH(frame, 0) * 0x50 + 0x10);
    u32 pos;

    if (KB(v, 0x21) != 0) {
        if (KB(v, 0x21) != 3) {
            return;
        }
        KH(c, 0x22) = KH(v, 0x24);
        pos = (KD(v, 0x50) - truncDouble(KD(v, 0x50))) * 65536.0;
        KH(c, 0x20) = pos;
        KH(c, 0x4C) = pos + (KH(v, 0x24) << 4) * KH(v, 0x44);
        KB(c, 0x3C) = (KH(v, 0x44) + (KH(v, 0x48) & 0x1F) + 0x1F) >> 5;
        KB(c, 0x3E) = KH(v, 0x48);
        KC(c, 0x24) = KC(v, 0x28);
        KW(c, 0x40) = KW(v, 0x40);
        KH(c, 0x4E) = KH(v, 0x64);
        if (KW(v, 0x34) != 0) {
            KB(c, 0x3D) = (KH(v, 0x46) + (KH(v, 0x4A) & 0x1F) + 0x1F) >> 5;
            KB(c, 0x3F) = KH(v, 0x4A);
            KC(c, 0x30) = KC(v, 0x34);
        } else {
            KB(c, 0x3D) = 0;
        }
    } else {
        KH(c, 0x22) = KH(v, 0x24);
        pos = (KD(v, 0x50) - truncDouble(KD(v, 0x50))) * 65536.0;
        KH(c, 0x20) = pos;
        KH(c, 0x4C) = pos + (KH(v, 0x24) << 4) * KH(v, 0x44);
        KH(c, 0x40) = KH(v, 0x44);
        KB(c, 0x3C) = 0;
        KB(c, 0x3E) = KH(v, 0x48);
        KC(c, 0x24) = KC(v, 0x28);
        KH(c, 0x4E) = KH(v, 0x64);
        if (KW(v, 0x34) != 0) {
            KH(c, 0x42) = KH(v, 0x46);
            KB(c, 0x3F) = KH(v, 0x4A);
            KC(c, 0x30) = KC(v, 0x34);
        } else {
            KH(c, 0x42) = 0;
        }
    }
    KH(c, 0x48) = KW(v, 0x58);
    KH(c, 0x4A) = KW(v, 0x5C);
    KW(c, 0x44) = 0;
    KW(c, 0x0) = KS(v, 0x6E) << 16;
    KW(c, 0x4) = KS(v, 0x70) << 16;
    KW(c, 0x8) = KS(v, 0x72) << 16;
    KW(c, 0xC) = KS(v, 0x74) << 16;
    KW(c, 0x10) = ((KS(v, 0x66) - KS(v, 0x6E)) << 16) / KH(v, 0x60);
    KW(c, 0x14) = ((KS(v, 0x68) - KS(v, 0x70)) << 16) / KH(v, 0x60);
    KW(c, 0x18) = ((KS(v, 0x6A) - KS(v, 0x72)) << 16) / KH(v, 0x60);
    KW(c, 0x1C) = ((KS(v, 0x6C) - KS(v, 0x74)) << 16) / KH(v, 0x60);
    KH(frame, 0)++;
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", musyxMixActiveVoices);

extern u8 gVcB702 __asm__("D_main_bss_80149702");
extern u8 *gVcB758[] __asm__("D_main_bss_80149758");
extern u16 gVcB760 __asm__("D_main_bss_80149760");
extern u8 *gVcB750 __asm__("D_main_bss_80149750");
extern s32 gVcB764 __asm__("D_main_bss_80149764");
extern u8 *gVcB768 __asm__("D_main_bss_80149768");
extern s32 gVcB76C __asm__("D_main_bss_8014976C");
extern u16 gVcB74E __asm__("D_main_bss_8014974E");
void musyxKeyOnVoiceVcB(u8 *) __asm__("musyxKeyOnVoice");
void musyxBuildVoiceCommandList(u8 *voices, u16 n) {
    u16 i;
    u8 *v;
    u8 *rec;
    u8 *rec2;
    u16 cnt;
    register u8 *blk asm("$5");
    s32 last;
    s32 len;
    gVcB750 = gVcB758[gVcB702];
    gVcB760 = 0;
    *(u16 *)gVcB750 = 0;
    for (i = 0; i < n; i++) {
        v = (u8 *)(i * 0x88 + (s32)voices);
        if (v[0x22] == 0) {
            musyxKeyOnVoiceVcB(v);
            continue;
        }
        rec = (u8 *)(gVcB760 * 0xA10 + (s32)gVcB750);
        cnt = *(u16 *)rec;
        if (cnt == 0) {
            *(u16 *)(rec + 0x3C) = 0;
            *(s32 *)(rec + 0x54) = *(s32 *)(v + 0x7C);
        } else {
            last = cnt - 1;
            *(s32 *)(rec + (last * 5 << 4) + 0x54) = *(s32 *)(v + 0x7C);
        }
        rec2 = (u8 *)(gVcB760 * 0xA10 + (s32)gVcB750);
        blk = gVcB768;
        *(s32 *)(rec2 + 8) = gVcB764;
        *(s32 *)(rec2 + 4) = *(s32 *)(voices + i * 0x88 + 0x84);
        *(u8 **)(rec2 + 0xC) = blk;
        if (blk != 0) {
            *(s16 *)(rec2 + 2) = gVcB76C / 192;
            len = *(s32 *)(blk + 4);
            gVcB76C = gVcB76C + 0xC0;
            if (gVcB76C == len) {
                gVcB76C = 0;
            }
        }
        gVcB760 = gVcB760 + 1;
        if (gVcB760 < gVcB74E) {
            *(u16 *)(gVcB760 * 0xA10 + (s32)gVcB750) = 0;
        }
    }
}


typedef struct SfNodeSF { struct SfNodeSF *next; u8 pad4[0xC]; u16 h10; } SfNodeSF;
typedef struct { u8 b0; u8 pad1[7]; f64 pos; u32 w10; u32 w14; u8 pad18[0x70]; } SfVoiceSF;
typedef struct { u32 type, flags; u8 *ucode_boot; u32 ucode_boot_size; u8 *ucode; u32 ucode_size; u8 *ucode_data; u32 ucode_data_size; u32 dram_stack, dram_stack_size, output_buff, output_buff_size; u8 *data_ptr; u32 data_size, yield_data_ptr, yield_data_size; } SfTaskSF;
extern SfTaskSF gAspTaskSF __asm__("aspTask");
extern u8 rspbootTextStart[];
extern u8 gRspbootEndSF[] __asm__("findModelAnimKeyframeByPhase");
extern u8 aspMainTextStart[];
extern u8 aspMainDataStart[];
extern volatile u8 gSfRingSF __asm__("D_main_bss_801496F0");
extern u8 gMusyXActiveFlag;
extern u16 gSfPosSF __asm__("D_main_bss_80149988");
extern u16 gSfPos2SF __asm__("D_main_bss_80149988");
extern u16 gSfFreeSF __asm__("D_main_bss_80149988+2");
extern u8 gSfPendSF __asm__("D_main_bss_8014974C");
extern OSMesgQueue gSfQueueSF __asm__("D_main_bss_80149730");
extern u8 gSfSideSF __asm__("D_main_bss_80149702");
extern u8 *gSfCmdBufSF[2] __asm__("D_main_bss_80149708");
extern u16 gSfCmdCntSF[2] __asm__("D_main_bss_80149710");
extern SfNodeSF *gSfNodesSF __asm__("D_main_bss_801499B0");
extern u16 gSfDmaCntSF __asm__("D_main_bss_80149724");
extern u8 *gSfDmaListSF __asm__("D_main_bss_80149728");
extern u16 gSfNumVoicesSF __asm__("D_main_bss_80149700");
extern SfVoiceSF *gSfVoicesSF __asm__("D_main_bss_801496F8");
extern u16 gSfNumBufSF __asm__("D_main_bss_8014974E");
extern u8 *gSfMixBufSF[16] __asm__("D_main_bss_801496B0");
extern u32 gSfTickSF __asm__("D_main_bss_80149714");
extern u32 gSfTickReloadSF __asm__("D_main_bss_80149718");
extern u8 gSfAspPendSF __asm__("D_main_bss_8014974D");
extern OSMesgQueue gSfSpQueueSF __asm__("D_main_bss_8011A800");
extern u16 gSfFramesSF __asm__("D_main_bss_80149760");
extern u8 *gSfFrameBufSF __asm__("D_main_bss_80149750");
extern void (*gSfStartTaskSF)(SfTaskSF *) __asm__("D_main_bss_801499D0");
extern void (*gSfSubmitSF)(u8 *, u16, OSMesgQueue *) __asm__("D_main_bss_801499DC");
extern u32 gSfLastDtSF __asm__("D_main_800A1778");
extern f32 gSfDtSumSF __asm__("D_main_800A176C");
extern f32 gSfDtCntSF __asm__("D_main_800A1770");
extern f32 gSfDtAvgSF __asm__("D_main_800A1774");
extern u32 gSfCostSF __asm__("D_main_bss_801499E8");
void factor5QueueBlock(void);
void factor5QueueSignal(void);
void recordFrameTimestamp();
void update3DAudioFrame();
void musyxBuildVoiceCommandList();
void tickAllActiveSongs();
void tickAudioSequencerFrame(void);
void musyxMixActiveVoices();
void flushStreamedVoiceBuffers();
void yieldFromSpThread();
void serviceStreamedVoices();
u32 getTimeSinceLastFrame();
u32 __osDisableInt(void);
void __osRestoreInt(u32);
void osYieldThread(void);
static __inline__ void sfMixOne(u16 idx, u16 off) {
    if (gMusyXActiveFlag && --gSfTickSF == 0) {
        gSfTickSF = gSfTickReloadSF;
        tickAllActiveSongs();
        tickAudioSequencerFrame();
    }
    musyxMixActiveVoices(gSfMixBufSF[idx], off, 0xC0);
}
void musyxSynthFrame(void) {
    u32 t0;
    u32 mask;
    u16 end;
    u16 i;
    u16 n;
    u16 off;
    s32 k;
    SfNodeSF *p;
    SfVoiceSF *v;
    u32 dt;
    u8 *fb;
    u16 fc;

    factor5QueueBlock();
    recordFrameTimestamp();
    t0 = osGetTime();
    mask = __osDisableInt();
    if (gSfRingSF != 0) {
        end = gSfRingSF - 1;
    } else {
        end = 15;
    }
    __osRestoreInt(mask);
    if (gMusyXActiveFlag) {
        update3DAudioFrame();
    }
    if (gSfPosSF != 0xFFFF) {
        if (gSfPendSF) {
            osRecvMesg(&gSfQueueSF, NULL, OS_MESG_BLOCK);
            gSfPendSF = 0;
            osYieldThread();
        }
        musyxBuildVoiceCommandList(gSfCmdBufSF[gSfSideSF ^ 1], gSfCmdCntSF[gSfSideSF ^ 1]);
        gSfDmaCntSF = 0;
        gSfCmdCntSF[gSfSideSF] = 0;
        for (p = gSfNodesSF; p != NULL; p = p->next) {
            if (p->h10 != 0) {
                p->h10--;
            }
        }
        if (gSfPosSF != end) {
            for (k = 0; k < gSfNumVoicesSF; k++) {
                if (gSfVoicesSF[k].b0) {
                    gSfVoicesSF[k].w14 = gSfVoicesSF[k].w10;
                    gSfVoicesSF[k].w10 = gSfVoicesSF[k].pos;
                }
            }
            off = 0;
            n = 0;
            if (end > (u32)gSfPosSF) {
                for (i = gSfPosSF; i < end;) {
                    if (n >= gSfNumBufSF) {
                        break;
                    }
                    sfMixOne(i++, off);
                    off += 0xC0;
                    n++;
                }
            } else {
                for (i = gSfPos2SF; i < 16;) {
                    if (n >= gSfNumBufSF) {
                        break;
                    }
                    sfMixOne(i++, off);
                    off += 0xC0;
                    n++;
                }
                for (i = 0; i < end;) {
                    if (n >= gSfNumBufSF) {
                        break;
                    }
                    sfMixOne(i++, off);
                    off += 0xC0;
                    n++;
                }
            }
            if (gSfDmaCntSF != 0) {
                gSfPendSF = 1;
                gSfSubmitSF(gSfDmaListSF, gSfDmaCntSF, &gSfQueueSF);
            }
            gSfPosSF = i;
            gSfFreeSF -= n;
        }
        flushStreamedVoiceBuffers();
        if (gSfAspPendSF) {
            osRecvMesg(&gSfSpQueueSF, NULL, OS_MESG_BLOCK);
            yieldFromSpThread();
            gSfAspPendSF = 0;
        }
        fb = gSfFrameBufSF;
        fc = gSfFramesSF;
        if (fc != 0) {
            gAspTaskSF.type = 2;
            gAspTaskSF.flags = 0;
            gAspTaskSF.ucode_boot = rspbootTextStart;
            gAspTaskSF.ucode_boot_size = gRspbootEndSF - rspbootTextStart;
            gAspTaskSF.ucode = aspMainTextStart;
            gAspTaskSF.ucode_size = 0x1000;
            gAspTaskSF.ucode_data = aspMainDataStart;
            gAspTaskSF.ucode_data_size = 0x800;
            gAspTaskSF.data_ptr = fb;
            gAspTaskSF.data_size = fc;
            osWritebackDCache(fb, fc * 0xA10);
            gSfStartTaskSF(&gAspTaskSF);
            gSfAspPendSF = 1;
        }
        gSfSideSF ^= 1;
        if (gMusyXActiveFlag) {
            serviceStreamedVoices();
        }
    } else {
        gSfPosSF = end;
    }
    dt = getTimeSinceLastFrame();
    gSfLastDtSF = dt;
    gSfDtSumSF += (f32)dt;
    gSfDtCntSF += 1.0f;
    gSfDtAvgSF = gSfDtSumSF / gSfDtCntSF;
    gSfCostSF = (u32)osGetTime() - t0;
    factor5QueueSignal();
}


void postViThreadCommand();
void submitDmaRequestBatch();
void registerSiCallback();
void findAndZeroTableSlotMatching();
void getAssetRamAddress();
void musyxSynthFrame(void);
void allocateSongChannelArray(u16, u32);
char *strcpy(char *, const char *);
extern void (*D_main_bss_801499D0)();
extern void (*D_main_bss_801499DC)();
extern void (*D_main_bss_801499D4)();
extern void (*D_main_bss_801499D8)(void (*)(void));
extern void (*D_main_bss_801499E0)();
extern u8 D_main_bss_8014974D;
extern s32 D_main_bss_80149768;
extern u32 D_main_bss_80149774;
extern void *D_main_bss_80149770;
extern u16 D_main_bss_80149988;
extern u32 D_main_bss_80149714;
extern u32 D_main_bss_80149718;
extern s32 D_main_bss_80142038;
typedef struct { u32 rate; u8 c; u8 d; u8 pad6[0x100]; char name[19]; } MixInfoRM;
extern MixInfoRM gMixInfoRM __asm__("D_main_bss_80140808");
void initN64RspMixer(u32 *rate, u16 nch, u16 ms, u8 mode) {
    u32 n;

    if (nch > 32) {
        nch = 32;
    }
    D_main_bss_801499D0 = postViThreadCommand;
    D_main_bss_801499DC = submitDmaRequestBatch;
    D_main_bss_801499D4 = registerSiCallback;
    D_main_bss_801499D8 = (void (*)(void (*)(void)))findAndZeroTableSlotMatching;
    D_main_bss_801499E0 = getAssetRamAddress;
    D_main_bss_8014974D = 0;
    allocateSongChannelArray(nch, *rate);
    setupSongRenderBuffers(nch, *rate, mode);
    n = *rate;
    if (ms != 0) {
        n = n * ms / 1000;
        D_main_bss_80149768 = 0;
        n = (n / 192) * 192 + 192;
        D_main_bss_80149774 = n;
        D_main_bss_80149770 = rs_malloc(n * 2, 0);
    } else {
        D_main_bss_80149770 = NULL;
    }
    D_main_bss_80149988 = 0xFFFF;
    D_main_bss_801499D4(musyxSynthFrame);
    n = (f32)*rate / 60.0f / 192.0f + 0.5f;
    D_main_bss_80149718 = n;
    D_main_bss_80149714 = n;
    D_main_bss_80142038 = n * 192;
    gMixInfoRM.rate = *rate;
    gMixInfoRM.d = 0x10;
    gMixInfoRM.c = 1;
    strcpy(gMixInfoRM.name, "N64 RSP mixer V1.0");
}

INCLUDE_ASM("asm/nonmatchings/main/832A0", initAudioSubsystem);

INCLUDE_ASM("asm/nonmatchings/main/832A0", reapplyAudioConfig);

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
extern void *gSongBufSD __asm__("D_main_bss_801499C0");
extern void *gStreamNodesSD __asm__("D_main_bss_801499C8");
extern void *gStreamBufSD __asm__("D_main_bss_801499C4");
extern void (*D_main_bss_801499D8)(void (*)(void));
extern OSMesgQueue gAiQueueSD __asm__("D_main_bss_80149670");
extern void *gMixBufsSD[] __asm__("D_main_bss_801496B0");
extern void *gAiStackSD __asm__("D_main_bss_80149660");
void musyxSynthFrame(void);
void rs_free(void *);
void shutdownAudioEngine(void) {
    u8 m;

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
        rs_free(gSongBufSD);
        rs_free(gStreamNodesSD);
        rs_free(gStreamBufSD);
        rs_free(D_main_bss_80149758);
        rs_free(D_main_bss_8014975C);
        rs_free(D_main_bss_801496FC);
        rs_free(D_main_bss_80149764);
        m = 0xFF;
        osSendMesg(&gAiQueueSD, (OSMesg)&m, OS_MESG_BLOCK);
        rs_free(gMixBufsSD[0]);
        rs_free(gAiStackSD);
    }
}

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


typedef struct {
    u8 b0;
    u8 b1;
    u16 flags;
    u16 vol;
    u8 pad6[2];
    f64 pos;
    u32 len10;
    u32 len14;
    s16 a18[4];
    s16 a20[4];
    s16 h28;
    s16 h2A;
    f32 f2C;
    s16 h30;
    u8 pad32[2];
    u32 addr;
    u32 w38;
    u32 w3C;
    u32 w40;
    s16 h44;
    s16 h46;
    s16 h48;
    s16 h4A;
    u8 pad4C[0x21];
    u8 b6D;
    u8 pad6E[0x1A];
} VoiceIV;
typedef struct { u32 w0; u32 addr; u32 len; u32 wC; u32 w10; u32 w14; u8 b18; } SampleIV;
extern VoiceIV *gVoicesIV __asm__("D_main_bss_801496F8");
void musyxInitVoiceFromSample(s32 idx, SampleIV *s, u8 init) {
    VoiceIV *v;
    VoiceIV *w;
    VoiceIV *x;
    s32 bw;
    s32 bx;

    v = &gVoicesIV[(u16)idx];
    v->vol = 0x1000;
    v->b0 = 0;
    v->flags = 0;
    v->b1 = 1;
    v->a18[0] = 0;
    v->a20[0] = 0;
    v->a18[1] = 0;
    v->a20[1] = 0;
    v->a18[2] = 0;
    v->a20[2] = 0;
    v->a18[3] = 0;
    v->a20[3] = 0;
    v->h44 = 0;
    v->h46 = 0;
    v->h48 = 0;
    v->h4A = 0;
    if (init) {
        bw = (s32)gVoicesIV;
        w = (VoiceIV *)(idx * sizeof(VoiceIV) + bw);
        w->h28 = 0;
        w->h2A = 0;
        w->f2C = 1.0f;
        w->h30 = 20;
    }
    bx = (s32)gVoicesIV;
    x = (VoiceIV *)(idx * sizeof(VoiceIV) + bx);
    x->addr = s->addr;
    x->pos = s->len;
    x->len10 = x->len14 = s->len;
    x->w38 = s->wC;
    x->w3C = s->w10;
    x->w40 = s->w14;
    x->b6D = s->b18;
    if ((s->addr & 0xF0000000) != 0x80000000) {
        gVoicesIV[idx].flags |= 1;
    }
}

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
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DE58);

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
INCLUDE_RODATA("asm/nonmatchings/main/832A0", D_main_8003DE60);

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
