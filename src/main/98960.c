#include "common.h"
#include "common_types.h"

typedef struct {
    u8 active;
    u8 pad[0x17];
} StreamedVoice;

extern u8 D_main_bss_80141AD0;
extern StreamedVoice D_main_bss_80152A20[];

void clearStreamedVoiceFlags(void) {
    s32 i;

    for (i = 0; i < D_main_bss_80141AD0; i++) {
        D_main_bss_80152A20[i].active = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/98960", serviceStreamedVoices);

INCLUDE_ASM("asm/nonmatchings/main/98960", flushStreamedVoiceBuffers);

INCLUDE_ASM("asm/nonmatchings/main/98960", startStreamedSampleVoice);

s32 streamSampleCountToByteSize(s32 arg0) {
    return (arg0 + 4) * 2;
}

INCLUDE_ASM("asm/nonmatchings/main/98960", setVoiceVolumePanLocked);

INCLUDE_ASM("asm/nonmatchings/main/98960", stopStreamedVoice);

INCLUDE_ASM("asm/nonmatchings/main/98960", compute3DSourceSpatialMix);

INCLUDE_ASM("asm/nonmatchings/main/98960", applyVoice3DMixParams);

INCLUDE_ASM("asm/nonmatchings/main/98960", updateActive3DAudioSource);

extern u8 gMusyXActiveFlag;

s32 isAudioVoiceActive(u8 *voice) {
    s32 r;

    if (gMusyXActiveFlag == 0) {
        r = 0;
    } else {
        r = *(u16 *)(voice + 8) & 1;
    }
    return r;
}

INCLUDE_ASM("asm/nonmatchings/main/98960", play3DSoundEvent);

INCLUDE_ASM("asm/nonmatchings/main/98960", play3DSoundEventVariant);

INCLUDE_ASM("asm/nonmatchings/main/98960", factor5RemoveListNode);

INCLUDE_ASM("asm/nonmatchings/main/98960", mostlyMusyxFlagGatedHelper);

INCLUDE_ASM("asm/nonmatchings/main/98960", tickAndReap3DAudioVoices);

INCLUDE_ASM("asm/nonmatchings/main/98960", setMusyX3DProperties);

INCLUDE_ASM("asm/nonmatchings/main/98960", register3DAudioListenerNode);

INCLUDE_ASM("asm/nonmatchings/main/98960", unlinkMusyXListNode);

INCLUDE_ASM("asm/nonmatchings/main/98960", enqueueSoundInPriorityGroup);

INCLUDE_ASM("asm/nonmatchings/main/98960", enqueueSpatialSoundInPriorityGroup);

INCLUDE_ASM("asm/nonmatchings/main/98960", dispatchPrioritizedSoundQueue);

INCLUDE_ASM("asm/nonmatchings/main/98960", update3DAudioFrame);

INCLUDE_ASM("asm/nonmatchings/main/98960", reset3DAudioLists);

void noopHandler_80099C44(void) {
}

INCLUDE_ASM("asm/nonmatchings/main/98960", fake_func_80099C4C);
