#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/97D20", resetSongSubsystemCounter);

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

INCLUDE_ASM("asm/nonmatchings/main/97D20", registerSndMacroTable);

INCLUDE_ASM("asm/nonmatchings/main/97D20", registerSndCurveTable);

INCLUDE_ASM("asm/nonmatchings/main/97D20", registerSndSampleTable);

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

INCLUDE_ASM("asm/nonmatchings/main/97D20", unloadLastSndFileGroup);

s32 returnZeroAudioStub(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/97D20", playSongByIdLockCtl);

INCLUDE_ASM("asm/nonmatchings/main/97D20", playSongById);

INCLUDE_ASM("asm/nonmatchings/main/97D20", fake_func_80097D58);
