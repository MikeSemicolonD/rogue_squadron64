#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/97D20", resetSongSubsystemCounter);

INCLUDE_ASM("asm/nonmatchings/main/97D20", bindMacroIdsToSoundGroup);

INCLUDE_ASM("asm/nonmatchings/main/97D20", registerSndMacroTable);

INCLUDE_ASM("asm/nonmatchings/main/97D20", registerSndCurveTable);

INCLUDE_ASM("asm/nonmatchings/main/97D20", registerSndSampleTable);

INCLUDE_ASM("asm/nonmatchings/main/97D20", applySndMidiSetupRecords);

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
} SndMidiSetupRecord;

extern void factor5SortedTableRemoveVoiceRecord(u16);

void releaseSndMidiSetupRecords(u16 *arg0) {
    s32 i;

    for (i = 0; i < *arg0; i++) {
        factor5SortedTableRemoveVoiceRecord(((SndMidiSetupRecord *)arg0)[i].unk4);
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
