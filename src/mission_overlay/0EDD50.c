#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", claimSongSlotForCurrentHandle);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", tickActiveSongSlots);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", shouldSwitchToPendingSong);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", selectAndStageNextSong);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", stopSongAndRebuildActiveCueList);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", processPendingSoundCueRequest);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", tickSongFadeTimer);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", pushActiveSoundDescriptor);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", popActiveSoundDescriptor);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", preloadSceneReferencedSongs);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", stageSongFromRequestDescriptor);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", resetMusicSubsystemState);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", initLevelMusicBank);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", stopAllMusicWithFade);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", startLevelBackgroundMusic);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", tickObjectSoundCueState);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", triggerStageMusicForNamedDatItem);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", triggerStageAmbientForNamedDatItem);

s32 freeAudioCacheEntry(s32);
s32 resetMusicSubsystemState(s32);
s32 tickSongSequenceLocked(s32);
extern s32 D_mission_overlay_8010C0E0;
extern s32 D_mission_overlay_8010C140;
extern u8 D_mission_overlay_8010C260;

s32 stopMusicAndResetAudio(void) {
    if (D_mission_overlay_8010C260 != 0) {
        tickSongSequenceLocked(D_mission_overlay_8010C140);
    }
    tickSongSequenceLocked(D_mission_overlay_8010C0E0);
    freeAudioCacheEntry(-1);
    resetMusicSubsystemState(1);
    return 1;
}

s32 preloadSceneReferencedSongs();

s32 preloadSceneSongsWrapper(void) {
    preloadSceneReferencedSongs();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", commitStagedSongAndPlay);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", stageSoundCueRequestByIdAndParam);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", initSoundCueRequest);

extern u8 D_mission_overlay_8010C0E8;

u8 getSoundCueSubsystemFlag(void) {
    return D_mission_overlay_8010C0E8;
}

void func_mission_overlay_800EFD64(void) {
}

void func_mission_overlay_800EFD6C(void) {
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", fake_func_800EFD74);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0EDD50", D_mission_overlay_800A8960);
