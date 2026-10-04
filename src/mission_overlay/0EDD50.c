#include "common.h"
#include "common_types.h"

typedef struct {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 pad9;
    u16 unkA;
    u8 padC[0x18];
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

extern SoundDescriptor gSoundDesc0E0 __asm__("D_mission_overlay_8010C0E0");
extern u16 D_mission_overlay_8010C252;
extern u16 D_mission_overlay_8010C452;
extern u8 D_mission_overlay_8010C2F2;
extern u8 D_mission_overlay_8010C2F3;
extern struct { u16 a; u16 b; u8 c; u8 pad; } D_mission_overlay_8010B1C0[];
s32 shouldSwitchToPendingSong();

s32 selectAndStageNextSong(void) {
    s32 sw;
    s32 v;
    u8 c;

    sw = shouldSwitchToPendingSong() & 0xFF;
    if (sw == 1) {
        v = D_mission_overlay_8010C252;
        D_mission_overlay_8010C2F2 = sw;
        D_mission_overlay_8010C2F3 = sw;
        if (v < 2) {
            v = D_mission_overlay_8010C452;
        }
        if (v == sw) {
            D_mission_overlay_8010C170 = gSoundDesc0E0;
            return 1;
        }
        D_mission_overlay_8010C170.unkA = v;
        D_mission_overlay_8010C170.unk4 = D_mission_overlay_8010B1C0[v - 2].a;
        D_mission_overlay_8010C170.unk6 = D_mission_overlay_8010B1C0[v - 2].b;
        c = D_mission_overlay_8010B1C0[v - 2].c;
        D_mission_overlay_8010C170.padC[2] = 0;
        D_mission_overlay_8010C170.padC[0] = 0;
        D_mission_overlay_8010C170.padC[1] = 0;
        D_mission_overlay_8010C170.padC[3] = 0;
        D_mission_overlay_8010C170.unk8 = c;
        return 1;
    }
    return 0;
}

extern SoundDescriptor D_mission_overlay_8010C1A0;
extern SoundDescriptor gSoundDesc1D0 __asm__("D_mission_overlay_8010C1D0");
extern SoundDescriptor gSoundDesc110 __asm__("D_mission_overlay_8010C110");
extern struct { s32 key; s32 unk4; s32 unk8; s32 unkC; } gCueSlots[8] __asm__("D_mission_overlay_8010C270");
extern u8 D_mission_overlay_8010C269;
s32 tickSongSequenceLocked(s32);

void stopSongAndRebuildActiveCueList(u8 arg0) {
    s32 i;
    s32 j;
    s32 key;
    SoundDescriptorStackEntry *e;
    typeof(&gCueSlots[0]) slot;
    typeof(&gCueSlots[0]) found;

    i = 0;
    slot = gCueSlots;
    key = (D_mission_overlay_8010C1A0.unk4 << 16) | D_mission_overlay_8010C1A0.unk6;
loop:
    i++;
    if (slot->key == key) {
        found = slot;
        goto done;
    }
    slot++;
    if (i < 8) goto loop;
    found = NULL;
done:
    if (found != NULL) {
        tickSongSequenceLocked(found->unk4);
        found->key = -1;
    }
    j = 0;
    do {
        e = &D_mission_overlay_8010C320[j];
        if (e->unk4 = D_mission_overlay_8010C1A0.unk4) {
            if (e->unk6 = D_mission_overlay_8010C1A0.unk6) {
                e->unk4 = gSoundDesc1D0.unk4;
                e->unk6 = gSoundDesc1D0.unk6;
                e->unk0 = -1;
            }
        }
        j++;
    } while (j < 8);
    D_mission_overlay_8010C269 = 0;
    gSoundDesc110 = gSoundDesc1D0;
    D_mission_overlay_8010C400 = gSoundDesc1D0;
    D_mission_overlay_8010C1A0 = gSoundDesc1D0;
    D_mission_overlay_8010C262 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", processPendingSoundCueRequest);

extern u8 gFadeA __asm__("D_mission_overlay_8010C2FC");
extern u8 gFadeB __asm__("D_mission_overlay_8010C2FD");
extern f32 gFadeT __asm__("D_mission_overlay_8010C300");
extern f32 gFadeLimit __asm__("D_mission_overlay_8010C304");
extern s32 gFadeC __asm__("D_mission_overlay_8010C308");
extern s32 gFadeD __asm__("D_mission_overlay_8010C30C");
extern s32 gSongHandle __asm__("D_mission_overlay_8010C0E0");
extern s32 gSongHandle4 __asm__("D_mission_overlay_8010C0E4");
extern s32 gSongHandleB4 __asm__("D_mission_overlay_8010C1A4");
extern u8 gFlag260 __asm__("D_mission_overlay_8010C260");
extern u8 gFlag264 __asm__("D_mission_overlay_8010C264");
extern u8 gFlag266 __asm__("D_mission_overlay_8010C266");
extern u8 gFlag2F1 __asm__("D_mission_overlay_8010C2F1");
extern u8 gFlag2F4 __asm__("D_mission_overlay_8010C2F4");
extern u32 gFlags9E0 __asm__("D_mission_overlay_8010C9E0");
extern u8 D_mission_overlay_8010C269;
extern u8 D_mission_overlay_8010C2F2;
extern u8 D_mission_overlay_8010C2F3;
extern u8 D_mission_overlay_8010C262;
extern s32 gDescA[] __asm__("D_mission_overlay_8010C110");
extern s32 gDescB[] __asm__("D_mission_overlay_8010C140");
typedef struct { s32 a[9]; } Blk8;
extern s32 getSongParamByHandle(s32);
extern u8 isSongHandleActive(s32);
extern void processPendingSoundCueRequest(void);
extern void tickActiveSongSlots(void);
s32 shouldSwitchToPendingSong();
void stopSongAndRebuildActiveCueList(u8);

void tickSongFadeTimer(f32 arg0) {
    u8 t;
    u8 s;
    if (gFadeA == 1) {
        gFadeT = gFadeT + arg0;
        if (gFadeLimit <= gFadeT) {
            D_mission_overlay_8010C262 = 1;
            gFadeA = 0;
            D_mission_overlay_8010C2F2 = 0;
        }
    } else {
        s = gFadeB;
        if (s == 1) {
            if (gFadeD == -1) {
                gFadeD = getSongParamByHandle(gSongHandle) & 0xFFFF;
                gFadeC += gFadeD;
            }
            if ((getSongParamByHandle(gSongHandle) & 0xFFFF) >= gFadeC) {
                D_mission_overlay_8010C262 = s;
                gFadeB = 0;
                D_mission_overlay_8010C2F2 = 0;
            }
        }
    }
    if (gFlag264 != 0) {
        if (!isSongHandleActive(gSongHandle)) {
            gFlag264 = 0;
            gFlag266 = 1;
            gFlags9E0 |= 0x100;
            D_mission_overlay_8010C262 = 1;
        }
    }
    t = gFlag2F1;
    if (t == 1) {
        D_mission_overlay_8010C2F3 = D_mission_overlay_8010C2F2;
        D_mission_overlay_8010C2F2 = shouldSwitchToPendingSong();
        if (D_mission_overlay_8010C2F2 != D_mission_overlay_8010C2F3) {
            gFlag2F4 = t;
            D_mission_overlay_8010C2F3 = D_mission_overlay_8010C2F2;
            D_mission_overlay_8010C262 = t;
        }
    }
    if (D_mission_overlay_8010C262 == 1) {
        processPendingSoundCueRequest();
        if (gFlag260 == 0) {
            D_mission_overlay_8010C262 = 0;
            if (gSongHandle4 != gDescA[1]) {
                *(Blk8 *)gDescB = *(Blk8 *)gDescA;
                tickActiveSongSlots();
            }
        }
    } else if (D_mission_overlay_8010C269 == 1 && gSongHandle4 == gSongHandleB4) {
        stopSongAndRebuildActiveCueList(1);
    }
}

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

extern SoundDescriptor D_mission_overlay_8010C1A0;
extern s32 D_mission_overlay_8010C140;
typedef struct {
    f32 unk0;
    u8 pad4[0x4];
    u32 unk8;
    u32 unkC;
    u8 pad10[0x10];
    u16 unk20;
    u16 unk22;
    u16 unk24;
    u16 unk26;
    u8 pad28[8];
    u8 unk30;
    u8 unk31;
} SongRequest;
typedef struct {
    f32 unk0;
    u8 pad4[0x14];
    s32 unk18;
    s32 unk1C;
    u16 unk20;
    u16 unk22;
    u16 unk24;
    u8 unk26;
    u8 unk27;
} SongStage;
extern SongStage D_mission_overlay_8010C430;

void stageSongFromRequestDescriptor(SongRequest *arg0) {
    D_mission_overlay_8010C1A0.unk0 = -1;
    D_mission_overlay_8010C1A0.unkA = arg0->unk20;
    if (arg0->unk20 >= 2) {
        D_mission_overlay_8010C1A0.unk4 = D_mission_overlay_8010B1C0[arg0->unk20 - 2].a;
        D_mission_overlay_8010C1A0.unk6 = D_mission_overlay_8010B1C0[arg0->unk20 - 2].b;
        D_mission_overlay_8010C1A0.unk8 = D_mission_overlay_8010B1C0[arg0->unk20 - 2].c;
    } else {
        D_mission_overlay_8010C1A0.unk4 = 0xFFFF;
        D_mission_overlay_8010C1A0.unk6 = 0xFFFF;
        D_mission_overlay_8010C1A0.unk8 = 0;
    }
    ((SoundCueRequest *)&D_mission_overlay_8010C1A0)->unkC = 0;
    ((SoundCueRequest *)&D_mission_overlay_8010C1A0)->unkD = 0;
    ((SoundCueRequest *)&D_mission_overlay_8010C1A0)->unkE = 0;
    ((SoundCueRequest *)&D_mission_overlay_8010C1A0)->unkF = 0;
    ((SoundCueRequest *)&D_mission_overlay_8010C1A0)->unk10 = 0;
    ((SoundCueRequest *)&D_mission_overlay_8010C1A0)->unk12 = 0;
    D_mission_overlay_8010C430.unk0 = arg0->unk0;
    D_mission_overlay_8010C430.unk18 = arg0->unk8;
    D_mission_overlay_8010C430.unk1C = arg0->unkC;
    D_mission_overlay_8010C430.unk20 = arg0->unk22;
    D_mission_overlay_8010C430.unk22 = arg0->unk24;
    D_mission_overlay_8010C430.unk24 = arg0->unk26;
    D_mission_overlay_8010C430.unk26 = arg0->unk30;
    D_mission_overlay_8010C430.unk27 = arg0->unk31;
    *(SoundDescriptor *)&D_mission_overlay_8010C140 = D_mission_overlay_8010C1A0;
    tickActiveSongSlots();
    D_mission_overlay_8010C1A0.unk0 = gSoundDesc0E0.unk0;
    D_mission_overlay_8010C400 = D_mission_overlay_8010C1A0;
}

extern f32 D_mission_overlay_80109FE0;
extern s32 D_mission_overlay_8010C110;
extern s32 D_mission_overlay_8010C0E0;
extern u8 D_mission_overlay_8010C260;
extern u8 D_mission_overlay_8010C263;
extern u8 D_mission_overlay_8010C264;
extern u8 D_mission_overlay_8010C265;
extern u8 D_mission_overlay_8010C266;
extern u8 D_mission_overlay_8010C267;
extern u8 D_mission_overlay_8010C269;
extern struct { s32 key; s32 unk4; s32 unk8; s32 unkC; } D_mission_overlay_8010C270[8];
extern u8 D_mission_overlay_8010C2F0;
extern u8 D_mission_overlay_8010C2F1;
extern u8 D_mission_overlay_8010C2F2;
extern u8 D_mission_overlay_8010C2F3;
extern u8 D_mission_overlay_8010C2F4;
extern u8 D_mission_overlay_8010C2FC;
extern u8 D_mission_overlay_8010C2FD;
extern s32 D_mission_overlay_8010C300;
extern s32 D_mission_overlay_8010C308;
extern s32 D_mission_overlay_8010C30C;
extern u8 D_mission_overlay_8010C460;
extern u8 D_mission_overlay_8010C461;
extern u8 D_mission_overlay_8010C462;

s32 resetMusicSubsystemState(s32 arg0) {
    s32 i;

    D_mission_overlay_8010C461 = 0;
    D_mission_overlay_8010C460 = 0;
    D_mission_overlay_8010C462 = 0;
    D_mission_overlay_80109FE0 = 0.7225f;
    if (arg0 & 0xFF) {
        D_mission_overlay_8010C110 = -1;
        D_mission_overlay_8010C0E0 = -1;
        D_mission_overlay_8010C260 = 0;
    }
    D_mission_overlay_8010C264 = 0;
    D_mission_overlay_8010C263 = 0;
    D_mission_overlay_8010C262 = 0;
    D_mission_overlay_8010C266 = 0;
    D_mission_overlay_8010C265 = 0;
    D_mission_overlay_8010C268 = 0;
    D_mission_overlay_8010C267 = 0;
    D_mission_overlay_8010C269 = 0;
    D_mission_overlay_8010C2F0 = 0;
    D_mission_overlay_8010C2FD = 0;
    D_mission_overlay_8010C2FC = 0;
    D_mission_overlay_8010C300 = 0;
    D_mission_overlay_8010C308 = 0;
    D_mission_overlay_8010C2F1 = 0;
    D_mission_overlay_8010C2F4 = 0;
    D_mission_overlay_8010C2F3 = 0;
    D_mission_overlay_8010C2F2 = 0;
    for (i = 0; i < 8; i++) {
        D_mission_overlay_8010C270[i].key = -1;
        D_mission_overlay_8010C270[i].unk8 = 0;
    }
    D_mission_overlay_8010C310 = 0;
    D_mission_overlay_8010C30C = -1;
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", initLevelMusicBank);

typedef struct { s32 key; s32 unk4; s32 unk8; s32 unkC; } SongSlotB;
extern SongSlotB gSongSlotsB[8] __asm__("D_mission_overlay_8010C270");
extern s32 D_mission_overlay_8010C140;
void queueAudioVoiceCmd(s32, u16, s32, s32);

void stopAllMusicWithFade(f32 arg0) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (gSongSlotsB[i].key != -1) {
            gSongSlotsB[i].key = -1;
            tickSongSequenceLocked(gSongSlotsB[i].unk4);
        }
    }
    if (D_mission_overlay_8010C260 != 0) {
        tickSongSequenceLocked(D_mission_overlay_8010C0E0);
        queueAudioVoiceCmd(0, (u32)(arg0 * 1000.0f), D_mission_overlay_8010C140, 1);
    } else {
        queueAudioVoiceCmd(0, (u32)(arg0 * 1000.0f), D_mission_overlay_8010C0E0, 1);
    }
    resetMusicSubsystemState(1);
}

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

extern void tickActiveSongSlots(void);
extern SoundDescriptor D_mission_overlay_8010C1A0;
extern u8 D_mission_overlay_8010C424;

s32 commitStagedSongAndPlay(void) {
    if (D_mission_overlay_8010C424 == 0) {
        return 0;
    }
    *(SoundDescriptor *)&D_mission_overlay_8010C140 = D_mission_overlay_8010C1A0;
    D_mission_overlay_8010C400 = D_mission_overlay_8010C1A0;
    tickActiveSongSlots();
    D_mission_overlay_8010C1A0.unk0 = D_mission_overlay_8010C0E0;
    return 1;
}

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
