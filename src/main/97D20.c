#include "common.h"
#include "common_types.h"

extern s16 D_main_bss_80152A10;

void resetSongSubsystemCounter(void) {
    D_main_bss_80152A10 = 0;
}

static __inline__ u8 *findSndChunkEntry(u8 *p, u16 id) {
    while (*(s32 *)p != -1) {
        if (*(u16 *)(p + 4) == id) {
            return p;
        }
        p += *(s32 *)p;
    }
    return NULL;
}

extern void factor5SecondSortedTableInsertValue(u16, void *);

void bindMacroIdsToSoundGroup(u16 *ids, u8 *base) {
    u8 *e;

    while (*ids != 0xFFFF) {
        e = findSndChunkEntry(base + *(s32 *)(base + 4), *ids);
        if (e != NULL) {
            factor5SecondSortedTableInsertValue(*ids, e + 8);
        }
        ids++;
    }
}

extern void factor5SortedTableInsertValue(u16, void *);

void registerSndMacroTable(u16 *ids, u8 *base) {
    u8 *e;

    while (*ids != 0xFFFF) {
        e = findSndChunkEntry(base + *(s32 *)(base + 8), *ids);
        if (e != NULL) {
            factor5SortedTableInsertValue(*ids, e + 8);
        }
        ids++;
    }
}

extern void factor5SortedTableInsertTaggedValue(u16, void *, u16);

void registerSndCurveTable(u16 *ids, u8 *base) {
    u8 *e;

    while (*ids != 0xFFFF) {
        e = findSndChunkEntry(base + *(s32 *)(base + 0xC), *ids);
        if (e != NULL) {
            factor5SortedTableInsertTaggedValue(*ids, e + 0xC, *(u16 *)(e + 0xA));
        }
        ids++;
    }
}

extern u8 *relocateSndPointer(u8 *);
extern void factor5SortedTableInsertWidePair(u16, void *, u32);

static __inline__ u8 *findSample(u8 *p, u16 id, u8 *base, u32 *out) {
    while (*(u16 *)p != 0xFFFF) {
        if (*(u16 *)p == id) {
            *out = (u32)base + *(s32 *)(p + 4);
            return p + 8;
        }
        p += 0x18;
    }
    return NULL;
}

void registerSndSampleTable(u16 *ids, u8 *a1, u8 *a2) {
    u32 v;
    u32 *out = &v;
    u8 *base = relocateSndPointer(a1);
    u8 *e;

    while (*ids != 0xFFFF) {
        e = findSample(a2, *ids, base, out);
        if (e != NULL) {
            factor5SortedTableInsertWidePair(*ids, e, v);
        }
        ids++;
    }
}

typedef struct {
    u16 unk0;
    u16 unk2;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 pad9[3];
} SndMidiSetupEntry;

typedef struct {
    u16 count;
    u16 pad2;
    SndMidiSetupEntry entries[1];
} SndMidiSetup;

extern void factor5SortedTableInsertVoiceRecord(u16, u16, u8, u8, u8, u8, u8);

void applySndMidiSetupRecords(SndMidiSetup *arg0) {
    s32 i;

    for (i = 0; i < arg0->count; i++) {
        factor5SortedTableInsertVoiceRecord(arg0->entries[i].unk0, arg0->entries[i].unk2, arg0->entries[i].unk7, arg0->entries[i].unk6, arg0->entries[i].unk5, arg0->entries[i].unk4, arg0->entries[i].unk8);
    }
}

extern void factor5SortedTableRemoveVoiceRecord(u16);

void releaseSndMidiSetupRecords(SndMidiSetup *arg0) {
    s32 i;

    for (i = 0; i < arg0->count; i++) {
        factor5SortedTableRemoveVoiceRecord(arg0->entries[i].unk0);
    }
}

INCLUDE_ASM("asm/nonmatchings/main/97D20", parseSndFiles);

extern u8 gMusyXActiveFlag;
extern u8 *D_main_bss_801529D0[];
extern void factor5BucketedTableRemoveEntry(u16);
extern void factor5SortedTableRemoveWidePair(u16);
extern void factor5SecondSortedTableRemoveValue(u16);
extern void factor5SortedTableRemoveValue(u16);
extern void factor5SortedTableRemoveTaggedValue(u16);
extern void factor5SortedTableRemoveVoiceRecord(u16);

static __inline__ void unl0(u16 *ids) {
    while (*ids != 0xFFFF) {
        factor5BucketedTableRemoveEntry(*ids);
        ids++;
    }
}

static __inline__ void unl1(u16 *ids) {
    while (*ids != 0xFFFF) {
        factor5SortedTableRemoveWidePair(*ids);
        ids++;
    }
}

static __inline__ void unl2(u16 *ids) {
    while (*ids != 0xFFFF) {
        factor5SecondSortedTableRemoveValue(*ids);
        ids++;
    }
}

static __inline__ void unl3(u16 *ids) {
    while (*ids != 0xFFFF) {
        factor5SortedTableRemoveValue(*ids);
        ids++;
    }
}

static __inline__ void unl4(u16 *ids) {
    while (*ids != 0xFFFF) {
        factor5SortedTableRemoveTaggedValue(*ids);
        ids++;
    }
}

s32 unloadLastSndFileGroup(void) {
    u8 *e;
    u8 *g;
    u8 *q;
    s16 n;
    s32 i;

    if (gMusyXActiveFlag != 0 && D_main_bss_80152A10 != 0) {
        n = D_main_bss_80152A10 - 1;
        e = D_main_bss_801529D0[n];
        {
            s32 o0 = *(s32 *)(e + 8);
            D_main_bss_80152A10 = n;
            unl0((u16 *)(o0 + (s32)e + 8));
        }
        unl1((u16 *)(*(s32 *)(e + 0xC) + (s32)e + 8));
        unl2((u16 *)(*(s32 *)(e + 0x10) + (s32)e + 8));
        unl3((u16 *)(*(s32 *)(e + 0x14) + (s32)e + 8));
        unl4((u16 *)(*(s32 *)(e + 0x18) + (s32)e + 8));
        if (*(u16 *)(e + 6) == 1) {
            g = (u8 *)(*(s32 *)(e + 0x1C) + (s32)e);
            g += 8;
            for (i = 0; i < *(u16 *)g; i++) {
                factor5SortedTableRemoveVoiceRecord(*(u16 *)(g + i * 0xC + 4));
            }
        }
        return 1;
    }
    return 0;
}

s32 returnZeroAudioStub(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/97D20", playSongByIdLockCtl);

INCLUDE_ASM("asm/nonmatchings/main/97D20", playSongById);

INCLUDE_ASM("asm/nonmatchings/main/97D20", fake_func_80097D58);
