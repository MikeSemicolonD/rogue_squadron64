#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/main/98960", clearStreamedVoiceFlags);

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

INCLUDE_ASM("asm/nonmatchings/main/98960", isAudioVoiceActive);

INCLUDE_ASM("asm/nonmatchings/main/98960", play3DSoundEvent);

INCLUDE_ASM("asm/nonmatchings/main/98960", play3DSoundEventVariant);

INCLUDE_ASM("asm/nonmatchings/main/98960", factor5RemoveListNode);

s32 factor5MutexAcquire();
s32 factor5MutexRelease();
extern u8 gMusyXActiveFlag;

s32 mostlyMusyxFlagGatedHelper(void *arg0) {
    s32 var_s1;

    var_s1 = -1;
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        if ((*(s32 *)((u8 *)(arg0) + 8)) & 0x10000) {
            var_s1 = (*(s32 *)((u8 *)(arg0) + 0x34));
        }
        factor5MutexRelease();
    }
    return var_s1;
}

INCLUDE_ASM("asm/nonmatchings/main/98960", tickAndReap3DAudioVoices);

INCLUDE_ASM("asm/nonmatchings/main/98960", setMusyX3DProperties);

INCLUDE_ASM("asm/nonmatchings/main/98960", register3DAudioListenerNode);

INCLUDE_ASM("asm/nonmatchings/main/98960", unlinkMusyXListNode);

INCLUDE_ASM("asm/nonmatchings/main/98960", enqueueSoundInPriorityGroup);

INCLUDE_ASM("asm/nonmatchings/main/98960", enqueueSpatialSoundInPriorityGroup);

INCLUDE_ASM("asm/nonmatchings/main/98960", dispatchPrioritizedSoundQueue);

INCLUDE_ASM("asm/nonmatchings/main/98960", update3DAudioFrame);

extern s32 D_main_bss_80153414;
extern s32 D_main_bss_80153418;

void reset3DAudioLists(void) {
    D_main_bss_80153414 = 0;
    D_main_bss_80153418 = 0;
}

void noopHandler_80099C44(void) {
}

INCLUDE_ASM("asm/nonmatchings/main/98960", fake_func_80099C4C);
