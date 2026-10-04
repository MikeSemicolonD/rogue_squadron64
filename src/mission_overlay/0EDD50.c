#include "common.h"
#include "common_types.h"

typedef struct {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 pad9;
    u16 unkA;
} SoundDescriptor;

typedef struct {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    u16 unk8;
    u8 unkA;
    u8 padB[0x1C - 0xB];
} SoundDescriptorStackEntry;

typedef struct {
    s32 unk0;
    s16 unk4;
    s16 unk6;
    u8 unk8;
    u8 pad9;
    s16 unkA;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    s16 unk10;
    s16 unk12;
} SoundCueRequest;

extern SoundDescriptor D_mission_overlay_8010C170;
extern SoundCueRequest D_mission_overlay_8010C200;
extern u8 D_mission_overlay_8010C262;
extern u8 D_mission_overlay_8010C268;
extern u8 D_mission_overlay_8010C310;
extern SoundDescriptorStackEntry D_mission_overlay_8010C320[];
extern SoundDescriptor D_mission_overlay_8010C400;
extern u16 D_mission_overlay_8010B304[];

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", claimSongSlotForCurrentHandle);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", tickActiveSongSlots);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", shouldSwitchToPendingSong);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", selectAndStageNextSong);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", stopSongAndRebuildActiveCueList);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", processPendingSoundCueRequest);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", tickSongFadeTimer);

void pushActiveSoundDescriptor(void) {
    D_mission_overlay_8010C320[D_mission_overlay_8010C310].unk0 = D_mission_overlay_8010C400.unk0;
    D_mission_overlay_8010C320[D_mission_overlay_8010C310].unk4 = D_mission_overlay_8010C400.unk4;
    D_mission_overlay_8010C320[D_mission_overlay_8010C310].unk6 = D_mission_overlay_8010C400.unk6;
    D_mission_overlay_8010C320[D_mission_overlay_8010C310].unkA = D_mission_overlay_8010C400.unk8;
    D_mission_overlay_8010C320[D_mission_overlay_8010C310].unk8 = D_mission_overlay_8010C400.unkA;
    D_mission_overlay_8010C310++;
}

void popActiveSoundDescriptor(void) {
    D_mission_overlay_8010C310--;
    D_mission_overlay_8010C170.unk0 = D_mission_overlay_8010C320[D_mission_overlay_8010C310].unk0;
    D_mission_overlay_8010C170.unk4 = D_mission_overlay_8010C320[D_mission_overlay_8010C310].unk4;
    D_mission_overlay_8010C170.unk6 = D_mission_overlay_8010C320[D_mission_overlay_8010C310].unk6;
    D_mission_overlay_8010C170.unk8 = D_mission_overlay_8010C320[D_mission_overlay_8010C310].unkA;
    D_mission_overlay_8010C170.unkA = D_mission_overlay_8010C320[D_mission_overlay_8010C310].unk8;
}

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

static __inline__ void setSoundCueRequest(s16 arg0, s16 arg1) {
    D_mission_overlay_8010C200.unkA = 1;
    D_mission_overlay_8010C200.unk8 = 0x7F;
    D_mission_overlay_8010C200.unk4 = arg0;
    D_mission_overlay_8010C200.unk6 = arg1;
    D_mission_overlay_8010C200.unkF = 0;
    D_mission_overlay_8010C200.unk10 = 100;
    D_mission_overlay_8010C200.unk12 = 100;
    D_mission_overlay_8010C200.unkC = 0;
    D_mission_overlay_8010C200.unkD = 0;
    D_mission_overlay_8010C200.unkE = 0;
    D_mission_overlay_8010C268 = 1;
    D_mission_overlay_8010C262 = 1;
}

void stageSoundCueRequestByIdAndParam(s16 arg0, s16 arg1) {
    setSoundCueRequest(arg0, arg1);
}

void initSoundCueRequest(u32 arg0) {
    s16 id;

    if (arg0 < 8) {
        id = 0x1D;
        if (arg0 == 3) {
            id = 0x1E;
        }
        setSoundCueRequest(id, D_mission_overlay_8010B304[arg0]);
    }
}

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
