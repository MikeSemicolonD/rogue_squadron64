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

typedef struct { s32 key; s32 unk4; u32 unk8; u8 unkC; u8 padD[3]; } TSSlot;
typedef struct { s32 unk0; u16 unk4; u16 unk6; u8 unk8; u8 pad9; s16 unkA; u8 unkC; u8 unkD; u8 unkE; u8 unkF; u16 unk10; u16 unk12; u8 pad14[0x10]; } TSDesc;
typedef struct { s32 unk0; u16 unk4; u16 pad6; s32 unk8; u16 unkC; u16 padE; s32 unk10; u16 unk14; u16 unk16; u8 unk18; u8 pad19[0xD]; s8 unk26; u8 pad27; } TSArgs;
extern TSSlot gTSSlots[8] __asm__("D_mission_overlay_8010C270");
extern TSDesc gTSNew __asm__("D_mission_overlay_8010C140");
extern TSDesc gTSCur __asm__("D_mission_overlay_8010C0E0");
extern u8 D_mission_overlay_8010C260;
extern u8 D_mission_overlay_8010C261;
extern u8 D_mission_overlay_8010C263;
extern u8 D_mission_overlay_8010C2F0;
extern u8 D_mission_overlay_8010C14C;
extern u8 D_mission_overlay_8010C14D;
extern u8 isSongHandleActive(s32);
extern s32 tickSongSequenceLocked(s32);
extern void quiesceSongSlotCmdLocked(s32);
extern void setSongParamPairCmdLocked(s32, s32, s32);
extern void queueAudioVoiceCmd(s32, u16, s32, s32);
extern s32 playSongById(u16, u16, s32, s32);
extern s32 findAudioChannelById(u16);
extern void playSimpleAudioCmd(s32, s32, s32);
extern void playSongIfMusyXActive(TSArgs *, TSDesc *, s32, s32);
extern void claimSongSlotForCurrentHandle(u8);

static __inline__ TSSlot *tsFind(void) {
    s32 i = 0;
    TSSlot *p = gTSSlots;
    s32 k = (gTSNew.unk4 << 16) | gTSNew.unk6;
    do {
        i++;
        if (p->key == k) {
            return p;
        }
        p++;
    } while (i < 8);
    return NULL;
}

#define TS_EVICT() \
    if ((s8)D_mission_overlay_8010C2F0 == 8) { \
        s32 idx_ = 0, i_ = 0; u32 best_ = 0; TSSlot *p_ = gTSSlots; \
        do { u32 t_ = p_->unk8; if (best_ < t_) { best_ = t_; idx_ = i_; } i_++; p_++; } while (i_ < 8); \
        tickSongSequenceLocked(gTSSlots[idx_].unk4); gTSSlots[idx_].key = -1; }

#define TS_FREE(s) \
    s->key = -1; s->unk4 = 0; s->unk8 = 0; D_mission_overlay_8010C2F0 -= 1;

static __inline__ void tsPlayArgs(TSArgs *a, s32 flags) {
    D_mission_overlay_8010C260 = 1;
    a->unk26 = flags;
    D_mission_overlay_8010C261 = 0;
    {
        u32 fa = gTSNew.unk10;
        u32 fb = gTSNew.unk12;
        u8 cm = gTSNew.unk8;
        a->unk0 = gTSCur.unk0;
        a->unk4 = fa;
        a->unkC = fb;
        a->unk18 = cm;
        playSongIfMusyXActive(a, &gTSNew, fa, fb);
    }
}

void tickActiveSongSlots(void) {
    TSArgs args;
    register TSArgs *a asm("$4");
    TSSlot *s;
    TSSlot *pb;
    TSSlot *t;
    s32 i;
    s32 flags;
    u8 mode;

    for (i = 0; i < 8; i++) {
        if (gTSSlots[i].key != -1) {
            gTSSlots[i].unk8++;
        }
    }
    if (D_mission_overlay_8010C263 == 0) {
        if (gTSNew.unkA == 0) {
            gTSCur = gTSNew;
            gTSCur.unk0 = -1;
            return;
        }
        s = tsFind();
        if (s != NULL && isSongHandleActive(s->unk4)) {
            quiesceSongSlotCmdLocked(s->unk4);
            queueAudioVoiceCmd(gTSNew.unk8, gTSNew.unk12, s->unk4, 0);
            TS_FREE(s);
            goto copy_set;
        }
        t = s;
        if (t != NULL) {
            TS_FREE(t);
        }
        TS_EVICT();
        gTSNew.unk0 = playSongById(gTSNew.unk4, gTSNew.unk6, findAudioChannelById(gTSNew.unk6), 0);
        playSimpleAudioCmd(gTSNew.unk8, 0, 0xFD);
    copy_set:
        gTSCur = gTSNew;
        D_mission_overlay_8010C263 = 1;
        return;
    }
    if (gTSNew.unkA == 0) {
        D_mission_overlay_8010C260 = 1;
        D_mission_overlay_8010C261 = 1;
        gTSNew.unk0 = -1;
        queueAudioVoiceCmd(0, gTSNew.unk10, gTSCur.unk0, 1);
        return;
    }
    if (isSongHandleActive(gTSCur.unk0)) {
        flags = 0;
        if (gTSNew.unkC == 0) {
            if (gTSNew.unkD != 0) {
                flags = 0x40;
            } else {
                flags = 1;
            }
        }
        goto cont_b;
    found_b:
        s = pb;
        goto done_b;
    cont_b:
        if (gTSNew.unkF == 1) {
            flags |= 4;
        }
        {
            s32 ib = 0;
            s32 kb = (gTSNew.unk4 << 16) | gTSNew.unk6;
            pb = gTSSlots;
        loop_b:
            ib++;
            if (pb->key == kb) {
                goto found_b;
            }
            pb++;
            if (ib < 8) {
                goto loop_b;
            }
            s = NULL;
        }
    done_b:
        mode = gTSNew.unkE;
        if (mode == 1) {
            if (s == NULL) {
                args.unk10 = findAudioChannelById(gTSNew.unk6);
                args.unk14 = gTSNew.unk4;
                args.unk16 = gTSNew.unk6;
                TS_EVICT();
            } else if (isSongHandleActive(s->unk4)) {
                args.unk8 = s->unk4;
                flags |= 2;
                if (s->unkC == mode) {
                    setSongParamPairCmdLocked(s->unk4, -1, -1);
                }
                gTSNew.unk0 = s->unk4;
                TS_FREE(s);
            } else {
                TS_FREE(s);
                args.unk10 = findAudioChannelById(gTSNew.unk6);
                args.unk14 = gTSNew.unk4;
                args.unk16 = gTSNew.unk6;
                TS_EVICT();
            }
        } else {
            if (s != NULL) {
                tickSongSequenceLocked(s->unk4);
                TS_FREE(s);
            }
            args.unk10 = findAudioChannelById(gTSNew.unk6);
            args.unk14 = gTSNew.unk4;
            args.unk16 = gTSNew.unk6;
            TS_EVICT();
        }
        if (D_mission_overlay_8010C14C == 0) {
            TS_EVICT();
            claimSongSlotForCurrentHandle(D_mission_overlay_8010C14D);
        }
        a = &args;
        __asm__("" : "+r"(a));
        {
        u32 fa; u32 fb; register u8 cm asm("$8"); register s32 cur asm("$3"); register TSDesc *n asm("$5") = &gTSNew;
D_mission_overlay_8010C260 = 1;
cur = gTSCur.unk0;
args.unk26 = flags;
fa = n->unk10;
fb = n->unk12;
cm = n->unk8;
D_mission_overlay_8010C261 = 0;
args.unk0 = cur;
__asm__("" :: "r"(cm));
args.unk4 = fa;
args.unkC = fb;
args.unk18 = cm;
        playSongIfMusyXActive(a, n, fa, fb);
        }
        return;
    }
    s = tsFind();
    mode = gTSNew.unkE;
    if (mode == 1) {
        if (s == NULL) {
            TS_EVICT();
            goto play;
        }
        if (isSongHandleActive(s->unk4)) {
            if (s->unkC == mode) {
                setSongParamPairCmdLocked(s->unk4, -1, -1);
            }
            quiesceSongSlotCmdLocked(s->unk4);
            queueAudioVoiceCmd(gTSNew.unk8, gTSNew.unk12, s->unk4, 0);
            gTSNew.unk0 = s->unk4;
            TS_FREE(s);
        } else {
            TS_FREE(s);
            TS_EVICT();
            goto play;
        }
    } else {
        if (s != NULL) {
            if (isSongHandleActive(s->unk4)) {
                tickSongSequenceLocked(s->unk4);
            }
            TS_FREE(s);
        }
        TS_EVICT();
    play:
        gTSNew.unk0 = playSongById(gTSNew.unk4, gTSNew.unk6, findAudioChannelById(gTSNew.unk6), 0);
        playSimpleAudioCmd(gTSNew.unk8, 0, 0xFD);
    }
    gTSCur = gTSNew;
    D_mission_overlay_8010C260 = 0;
    D_mission_overlay_8010C261 = 0;
}

#include "level_objectives.h"
extern u8 D_mission_overlay_8010C2F1;
extern u8 D_mission_overlay_8010C2F5;
extern u8 D_mission_overlay_8010C2F6;
extern u8 D_mission_overlay_8010C2F7;
extern s32 D_mission_overlay_8010C2F8;

s32 shouldSwitchToPendingSong(void) {
    s32 need;

    if (D_mission_overlay_8010C2F1 == 1) {
        if (D_mission_overlay_8010C2F5 != 0) {
            if (gObjectiveBooleans[D_mission_overlay_8010C2F5 - 1] != D_mission_overlay_8010C2F6) {
                return 0;
            }
        } else if (D_mission_overlay_8010C2F7 == 0) {
            goto end;
        }
        if (D_mission_overlay_8010C2F7 == 0) {
            goto one;
        }
        need = D_mission_overlay_8010C2F8;
        if (need < 0) {
            if (gObjectiveCounts[D_mission_overlay_8010C2F7 - 1] < -need) {
                goto one;
            }
            return 0;
        }
        if (gObjectiveCounts[D_mission_overlay_8010C2F7 - 1] < need) {
            return 0;
        }
one:
        return 1;
    }
end:
    return 0;
}

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

typedef struct {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 pad9;
    s16 unkA;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    s16 unk10;
    s16 unk12;
    u8 pad14[0x10];
} PpDesc;

typedef struct {
    f32 f0;
    f32 f4;
    u8 pad8[0x10];
    s32 n18;
    s32 m1C;
    u8 pad20[7];
    u8 b27;
    u8 b28;
    u8 b29;
    u8 b2A;
    u8 b2B;
    s32 v2C;
} PpCfg;

extern PpDesc gPpCur __asm__("D_mission_overlay_8010C110");
extern PpDesc gPp0E0 __asm__("D_mission_overlay_8010C0E0");
extern PpCfg gPpCfg __asm__("D_mission_overlay_8010C230");
extern u8 D_mission_overlay_8010C264;
extern u8 D_mission_overlay_8010C265;
extern u8 D_mission_overlay_8010C266;
extern u8 D_mission_overlay_8010C267;
extern u8 D_mission_overlay_8010C269;
extern u8 D_mission_overlay_8010C2F4;
extern u8 D_mission_overlay_8010C2FC;
extern u8 D_mission_overlay_8010C2FD;
extern f32 gPp300 __asm__("D_mission_overlay_8010C300");
extern f32 D_mission_overlay_8010C304;
extern s32 D_mission_overlay_8010C308;
extern s32 D_mission_overlay_8010C30C;
extern s32 D_mission_overlay_8010C114;
extern s32 D_mission_overlay_8010C1A4;
extern u16 D_mission_overlay_8010C250;
extern s16 rand(void);
void stopSongAndRebuildActiveCueList(u8);

void processPendingSoundCueRequest(void) {
    PpDesc tmp;
    s32 v;

    if (D_mission_overlay_8010C268 == 1) {
        if (D_mission_overlay_8010C264 == 0 && D_mission_overlay_8010C265 == 0) {
            gPpCur = *(PpDesc *)&D_mission_overlay_8010C200;
            D_mission_overlay_8010C265 = 1;
            D_mission_overlay_8010C264 = 0;
            D_mission_overlay_8010C266 = 0;
            D_mission_overlay_8010C2FD = 0;
            D_mission_overlay_8010C2FC = 0;
        }
        D_mission_overlay_8010C268 = 0;
    } else if (D_mission_overlay_8010C264 == 0 && D_mission_overlay_8010C265 == 0) {
        if (D_mission_overlay_8010C267 == 1) {
            if (gPpCfg.b28 == 0) {
                if (D_mission_overlay_8010C2F2 == 1 && gPpCfg.f4 > 0.0f) {
                    D_mission_overlay_8010C2FC = 1;
                    D_mission_overlay_8010C2FD = 0;
                    D_mission_overlay_8010C304 = gPpCfg.f4;
                    gPp300 = 0.0f;
                    gPpCfg.f4 = 0.0f;
                    D_mission_overlay_8010C267 = 0;
                    D_mission_overlay_8010C2F3 = 0;
                    D_mission_overlay_8010C2F2 = 0;
                } else {
                    D_mission_overlay_8010C2F3 = 0;
                    D_mission_overlay_8010C2F2 = 0;
                    D_mission_overlay_8010C267 = 0;
                    if (D_mission_overlay_8010C2FC == 0 && D_mission_overlay_8010C2FD == 0) {
                        gPpCur = *(PpDesc *)&D_mission_overlay_8010C170;
                    }
                }
                D_mission_overlay_8010C2F1 = 0;
            } else {
                D_mission_overlay_8010C2F3 = 0;
                D_mission_overlay_8010C2F2 = 0;
                D_mission_overlay_8010C2F1 = 1;
                D_mission_overlay_8010C2F5 = gPpCfg.b29;
                D_mission_overlay_8010C2F6 = gPpCfg.b2A;
                D_mission_overlay_8010C2F7 = gPpCfg.b2B;
                D_mission_overlay_8010C2F8 = gPpCfg.v2C;
                if (gPpCfg.b27 == 1) {
                    D_mission_overlay_8010C2FD = 0;
                    D_mission_overlay_8010C2FC = 0;
                }
                if (!(u8)selectAndStageNextSong()) {
                if (D_mission_overlay_8010C2FC == 0 && D_mission_overlay_8010C2FD == 0) {
                    D_mission_overlay_8010C267 = 0;
                    if (gPpCfg.f0 != 0.0f) {
                        D_mission_overlay_8010C304 = gPpCfg.f0;
                        D_mission_overlay_8010C2FC = 1;
                    } else if (gPpCfg.n18 != 1) {
                        D_mission_overlay_8010C2FD = 1;
                        D_mission_overlay_8010C30C = -1;
                        D_mission_overlay_8010C308 = gPpCfg.n18;
                        if (gPpCfg.n18 == 0) {
                            D_mission_overlay_8010C308 = rand() % gPpCfg.m1C + 1;
                        }
                    }
                    gPpCur = *(PpDesc *)&D_mission_overlay_8010C170;
                } else {
                    gPpCur = gPp0E0;
                }
                } else {
                    D_mission_overlay_8010C267 = 0;
                    gPpCur = *(PpDesc *)&D_mission_overlay_8010C170;
                }
            }
        } else if (D_mission_overlay_8010C266 != 0) {
            D_mission_overlay_8010C266 = 0;
            if (D_mission_overlay_8010C2F2 == 0) {
                gPpCur = *(PpDesc *)&D_mission_overlay_8010C400;
            } else {
                gPpCur = *(PpDesc *)&D_mission_overlay_8010C170;
            }
            gPpCur.unkA = 1;
            gPpCur.unkF = 0;
            gPpCur.unk10 = 100;
            gPpCur.unk12 = 100;
            gPpCur.unkC = 1;
            gPpCur.unkD = 0;
            gPpCur.unkE = 1;
        } else {
            if (D_mission_overlay_8010C2F4 == 1) {
                if (D_mission_overlay_8010C2F2 == 0) {
                    gPpCur = *(PpDesc *)&D_mission_overlay_8010C400;
                    if (gPpCfg.f0 != 0.0f) {
                        D_mission_overlay_8010C304 = gPpCfg.f0;
                        D_mission_overlay_8010C2FC = 1;
                    } else if (gPpCfg.n18 != 1) {
                        D_mission_overlay_8010C2FD = 1;
                        D_mission_overlay_8010C30C = -1;
                        D_mission_overlay_8010C308 = gPpCfg.n18;
                        if (gPpCfg.n18 == 0) {
                            D_mission_overlay_8010C308 = rand() % gPpCfg.m1C + 1;
                        }
                    }
                } else {
                    selectAndStageNextSong();
                    gPpCur = *(PpDesc *)&D_mission_overlay_8010C170;
                }
            } else if (D_mission_overlay_8010C30C != -1) {
                D_mission_overlay_8010C30C = -1;
                v = D_mission_overlay_8010C250;
                if (v >= 2) {
                    tmp = gPp0E0;
                    tmp.unkA = v;
                    tmp.unk4 = D_mission_overlay_8010B1C0[v - 2].a;
                    tmp.unk6 = D_mission_overlay_8010B1C0[v - 2].b;
                    tmp.unk8 = D_mission_overlay_8010B1C0[v - 2].c;
                    tmp.unkC = 1;
                    tmp.unkD = 0;
                    tmp.unkE = 1;
                    tmp.unkF = 0;
                    tmp.unk10 = 0;
                    tmp.unk12 = 0;
                    gPpCur = tmp;
                }
            } else {
                gPpCur = *(PpDesc *)&D_mission_overlay_8010C400;
            }
            D_mission_overlay_8010C2F4 = 0;
        }
    }
    if (D_mission_overlay_8010C269 == 1 && D_mission_overlay_8010C114 == D_mission_overlay_8010C1A4) {
        stopSongAndRebuildActiveCueList(0);
    }
}

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

extern s32 D_main_bss_80138920;
extern s32 D_main_bss_80139B4C;
extern s32 D_main_bss_80139B50;
extern s32 D_main_bss_80139B54;
extern s32 D_main_8009FCD0;
extern s32 gCurrentLevel;
extern u8 D_mission_overlay_8010C424;
extern struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x10];
    s32 unk18;
    s32 unk1C;
    u8 pad20[6];
    u8 unk26;
    u8 unk27;
} D_mission_overlay_8010C230;
s32 parseSndFiles(s32, s32, void *, s32, s32);
void loadSongAssetByName(s32, s32);

s32 initLevelMusicBank(void) {
    resetMusicSubsystemState(1);
    D_mission_overlay_8010C424 = 0;
    D_mission_overlay_8010C230.unk0 = 0;
    D_mission_overlay_8010C230.unk1C = 0;
    D_mission_overlay_8010C230.unk18 = 0;
    D_mission_overlay_8010C230.unk27 = 0;
    D_mission_overlay_8010C230.unk26 = 0;
    D_mission_overlay_8010C230.unk4 = 0;
    parseSndFiles(D_main_bss_80139B54, 0x1D, (void *)D_main_8009FCD0, D_main_bss_80139B4C, D_main_bss_80139B50);
    loadSongAssetByName(D_main_bss_80138920, 0x35);
    loadSongAssetByName(D_main_bss_80138920, 0x36);
    loadSongAssetByName(D_main_bss_80138920, 0x37);
    loadSongAssetByName(D_main_bss_80138920, 0x3C);
    switch (gCurrentLevel) {
    case 3:
        loadSongAssetByName(D_main_bss_80138920, 0x3A);
        break;
    case 8:
        loadSongAssetByName(D_main_bss_80138920, 0x39);
        break;
    case 9:
        loadSongAssetByName(D_main_bss_80138920, 0x3A);
        loadSongAssetByName(D_main_bss_80138920, 0x3B);
        break;
    case 0x12:
        loadSongAssetByName(D_main_bss_80138920, 0x3B);
        break;
    }
    parseSndFiles(D_main_bss_80139B54, 0x1E, (void *)D_main_8009FCD0, D_main_bss_80139B4C, D_main_bss_80139B50);
    loadSongAssetByName(D_main_bss_80138920, 0x59);
    return 1;
}

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

typedef struct {
    s32 unk0;
    u8 pad4[4];
    s32 unk8;
    s32 unkC;
    u8 pad10[0x10];
    u16 unk20;
    u16 unk22;
    u16 unk24;
    u16 unk26;
    u16 unk28;
    u16 unk2A;
    u16 unk2C;
    s8 unk2E;
    s8 unk2F;
    s8 unk30;
    s8 unk31;
    u8 pad32[0xE];
} LevelSongReq;
extern s32 gCurrentLevel;
extern u8 D_mission_overlay_8010C424;
extern u8 D_mission_overlay_8010C261;
extern u8 D_mission_overlay_8010B2EC[];
void tickSongFadeTimer(f32);
s32 isSongHandleFree(void *);
void setSongPauseStateByHandle(s32, s32);

void startLevelBackgroundMusic(f32 arg0) {
    LevelSongReq req;
    s32 i;
    s32 cur;
    u8 lvl;
    SoundDescriptor *d;
    typeof(&D_mission_overlay_8010B1C0[0]) tbl;

    if (D_mission_overlay_8010C424 == 0) {
        cur = gCurrentLevel;
        tbl = D_mission_overlay_8010B1C0;
        req.unk0 = 0;
        req.unk8 = 0;
        req.unkC = 0;
        lvl = D_mission_overlay_8010B2EC[cur];
        i = 0;
        while (tbl[i].b != lvl) {
            i++;
        }
        req.unk20 = i + 2;
        req.unk22 = 1;
        req.unk2C = 0xFFFF;
        req.unk24 = 1;
        req.unk26 = 1;
        req.unk28 = 0;
        req.unk2A = 0;
        req.unk2E = 1;
        req.unk2F = 1;
        req.unk30 = 0;
        req.unk31 = 0;
        D_mission_overlay_8010C424 = 1;
        stageSongFromRequestDescriptor((SongRequest *)&req);
    }
    if (D_mission_overlay_8010C260 == 1) {
        if (D_mission_overlay_8010C261 == D_mission_overlay_8010C260) {
            d = &gSoundDesc0E0;
            if (!(isSongHandleActive(d->unk0) & 0xFF)) {
                D_mission_overlay_8010C261 = 0;
                D_mission_overlay_8010C260 = 0;
                *d = *(SoundDescriptor *)&D_mission_overlay_8010C140;
                D_mission_overlay_8010C263 = 0;
                D_mission_overlay_8010C300 = 0;
            }
        } else if (isSongHandleFree(&D_mission_overlay_8010C140) & 0xFF) {
            D_mission_overlay_8010C261 = 0;
            D_mission_overlay_8010C260 = 0;
            gSoundDesc0E0 = *(SoundDescriptor *)&D_mission_overlay_8010C140;
            D_mission_overlay_8010C300 = 0;
            if (D_mission_overlay_8010C265 != 0) {
                D_mission_overlay_8010C265 = 0;
                D_mission_overlay_8010C264 = 1;
                setSongPauseStateByHandle(D_mission_overlay_8010C0E0, 0);
            }
        }
    } else {
        tickSongFadeTimer(arg0);
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0EDD50", tickObjectSoundCueState);

extern s32 D_mission_overlay_8010CA20;
typedef struct {
    s32 unk0;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 pad9;
    s16 unkA;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    s16 unk10;
    s16 unk12;
} StageCue;
extern StageCue gCue1D0 __asm__("D_mission_overlay_8010C1D0");
extern void *getLevelDatItemByName(char *);

void triggerStageMusicForNamedDatItem(char *name, s32 which) {
    u8 *item;
    s32 idx;
    s32 i;
    u16 *t;
    u16 ca;
    u16 cb;
    s32 xa;
    s32 xb;

    if (D_mission_overlay_8010CA20 != 0) {
        return;
    }
    item = getLevelDatItemByName(name);
    if (item == NULL) {
        return;
    }
    switch (which) {
    case 0:
        idx = *(s32 *)(item + 0x3C);
        break;
    case 1:
        idx = *(s32 *)(item + 0x40);
        break;
    case 2:
        idx = *(s32 *)(item + 0x44);
        break;
    case 3:
        idx = *(s32 *)(item + 0x48);
        break;
    default:
        return;
    }
    idx -= 2;
    if (idx < 0) {
        return;
    }
    gCue1D0.unk0 = -1;
    t = &D_mission_overlay_8010B1C0[0].a;
    ca = t[idx * 3];
    gCue1D0.unk4 = ca;
    D_mission_overlay_8010C269 = 1;
    cb = t[idx * 3 + 1];
    gCue1D0.unk6 = cb;
    gCue1D0.unk8 = ((u8 *)t)[idx * 6 + 4];
    xb = cb;
    i = 0;
    if (t[1] != xb) {
        u16 *p;
        xa = ca;
        p = t;
loop:
        if (*p != xa) {
            p += 3;
            i++;
            if (p[1] != xb) {
                goto loop;
            }
        }
    }
    gCue1D0.unkA = i + 2;
    gCue1D0.unkC = 0;
    gCue1D0.unkD = 0;
    gCue1D0.unkE = 0;
    gCue1D0.unkF = 0;
    gCue1D0.unk10 = (u32)(*(f32 *)(item + 0x54) * 1000.0f);
    gCue1D0.unk12 = (u32)(*(f32 *)(item + 0x50) * 1000.0f);
}

void triggerStageAmbientForNamedDatItem(char *name, s32 which) {
    u8 *item;
    s32 idx;
    s32 i;
    u16 *t;
    u16 ca;
    u16 cb;
    s32 xa;
    s32 xb;

    item = getLevelDatItemByName(name);
    if (item == NULL) {
        return;
    }
    switch (which) {
    case 0:
        idx = *(s32 *)(item + 0x3C);
        break;
    case 1:
        idx = *(s32 *)(item + 0x40);
        break;
    case 2:
        idx = *(s32 *)(item + 0x44);
        break;
    case 3:
        idx = *(s32 *)(item + 0x48);
        break;
    default:
        return;
    }
    idx -= 2;
    if (idx < 0) {
        return;
    }
    gCue1D0.unk0 = -1;
    t = &D_mission_overlay_8010B1C0[0].a;
    ca = t[idx * 3];
    gCue1D0.unk4 = ca;
    D_mission_overlay_8010C269 = 1;
    cb = t[idx * 3 + 1];
    gCue1D0.unk6 = cb;
    gCue1D0.unk8 = ((u8 *)t)[idx * 6 + 4];
    xb = cb;
    i = 0;
    if (t[1] != xb) {
        u16 *p;
        xa = ca;
        p = t;
loop:
        if (*p != xa) {
            p += 3;
            i++;
            if (p[1] != xb) {
                goto loop;
            }
        }
    }
    gCue1D0.unkA = i + 2;
    gCue1D0.unkC = 0;
    gCue1D0.unkD = 0;
    gCue1D0.unkE = 0;
    gCue1D0.unkF = 0;
    gCue1D0.unk10 = (u32)(*(f32 *)(item + 0x54) * 1000.0f);
    gCue1D0.unk12 = (u32)(*(f32 *)(item + 0x50) * 1000.0f);
    stopSongAndRebuildActiveCueList(1);
}

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


static u32 D_800A8964[] __attribute__((section(".rodata"))) = { 0x10600003, 0, 0x0802A263 };
