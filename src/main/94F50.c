#include "common.h"
#include "common_types.h"

#include "main/832A0.h"
#include "main/94F50.h"

// Interim BSS externs

extern struct D_main_bss_801511C0_type D_main_bss_801511C0[0x100];
extern u32 D_main_bss_801499F0;
extern u32 D_main_bss_801499FC;
extern struct D_main_bss_80149A00_type  D_main_bss_80149A00[8];
extern struct D_main_bss_80149A00_type *D_main_bss_801529C0;
extern struct D_main_bss_801511C0_type *D_main_bss_801529C4;

INCLUDE_ASM("asm/nonmatchings/main/94F50", startSongSequence);

INCLUDE_ASM("asm/nonmatchings/main/94F50", stepActiveSongTracks);

#if 0
// https://decomp.me/scratch/9HNev
s32 tickScheduledSongEvents(void) {
    s32 temp_v0_3;
    struct D_main_bss_801511C0_type *temp_s1;
    struct D_main_bss_801511C0_type *temp_v0;
    struct D_main_bss_801511C0_type *var_s0;

    temp_v0 = D_main_bss_801529C0->unkE78[0];
    if (temp_v0 == NULL) return 0;
    while (temp_v0 != NULL) {
        D_main_bss_801499FC += 1;
        temp_s1 = temp_v0->unk00;
        if ((temp_v0->unk14 + D_main_bss_801529C0->unk110[4]) >= temp_v0->unk0C) {
            flagVoiceChainForStop(temp_v0->unk08);
            if (temp_v0->unk00 != NULL) {
                temp_v0->unk00->unk04 = temp_v0->unk04;
            }
            if (temp_v0->unk04 != NULL) {
                temp_v0->unk04->unk00 = temp_v0->unk00;
            } else {
                D_main_bss_801529C0->unkE78[0] = temp_v0->unk00;
            }
            temp_v0->unk00 = D_main_bss_801529C0->unkE78[1];
            if (temp_v0->unk00 != NULL) {
                D_main_bss_801529C0->unkE78[1]->unk04 = temp_v0;
            }
            temp_v0->unk04 = NULL;
            D_main_bss_801529C0->unkE78[1] = temp_v0;
        } else {
            temp_v0_3 = temp_v0->unk10 + D_main_bss_801529C0->unk110[2];
            temp_v0->unk10 = temp_v0_3 & 0xFFFF;
            temp_v0->unk14 += (temp_v0_3 >> 0x10) + D_main_bss_801529C0->unk110[3];
        }
        temp_v0 = temp_s1;
    }
    return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/main/94F50", tickScheduledSongEvents);
#endif

typedef struct {
    s32 baseTime;
    s32 pad4;
    u8 *stream;
    s32 padC;
    u16 value;
    u16 pad12;
    u32 time;
    s32 pad18;
    u8 channel;
    u8 pad1D[7];
} SongLane;

#define LANE(o) ((SongLane *)((u8 *)D_main_bss_801529C0 + (o) + 0x56C))

extern u8 D_main_bss_801529CB;
void setChannelNoteCell(u8, u8, u8, u8);

void stepSongPitchBendLanes(void) {
    s32 off;
    s32 o;
    u8 done;
    s32 b0;
    s32 b1;
    s32 delta;
    s32 len;
    u32 t;
    s32 v;
    u8 *p;
    u8 *q;

    off = 0;
    do {
        if (LANE(off)->stream != NULL) {
            done = 0;
            o = off;
            do {
                b0 = LANE(o)->stream[0];
                b1 = LANE(o)->stream[1];
                if ((b0 == 0x80) & (b1 == 0)) {
                    LANE(o)->stream = NULL;
                    done = 1;
                } else {
                    if (b0 & 0x80) {
                        delta = b1 | ((b0 & 0x7F) << 8);
                        len = 2;
                    } else {
                        delta = b0 & 0xFF;
                        len = 1;
                    }
                    t = delta + LANE(o)->time;
                    if (LANE(o)->baseTime + D_main_bss_801529C0->unk110[4] >= t) {
                        LANE(o)->stream = LANE(o)->stream + len;
                        LANE(o)->time = t;
                        p = LANE(o)->stream;
                        b0 = p[0];
                        b1 = p[1];
                        if (b0 & 0x80) {
                            v = ((s32)((b1 | ((b0 & 0x7F) << 8)) << 17)) >> 17;
                            LANE(o)->stream = p + 2;
                        } else {
                            v = ((s32)(b0 << 25)) >> 25;
                            LANE(o)->stream = p + 1;
                        }
                        LANE(o)->value += v;
                        setChannelNoteCell(0x80, LANE(o)->channel, D_main_bss_801529CB, (LANE(o)->value >> 7) & 0xFF);
                        setChannelNoteCell(0x81, LANE(o)->channel, D_main_bss_801529CB, LANE(o)->value & 0x7F);
                    } else {
                        done = 1;
                    }
                }
            } while (!done);
        }
        off += 0x24;
    } while (off < 0x900);
}

INCLUDE_ASM("asm/nonmatchings/main/94F50", stepSongModulationLanes);

INCLUDE_ASM("asm/nonmatchings/main/94F50", advanceSongRegion);

extern s32 D_main_bss_80142038;
extern s32 D_main_bss_801440C0;
extern u8 D_main_bss_801529CB;
void setTrackVoiceTickBudget(u32, u8, struct D_main_bss_80149A00_type *);

void updateSongTempoTickRate(u32 arg0) {
    struct SNG_unk0C_type *cur;
    struct SNG_unk0C_type *prev;
    u32 budget;
    register u32 lo asm("$2");
    register s32 neg asm("$16");

    D_main_bss_801529C0->unkE6C = D_main_bss_801529C0->unkE68;
    D_main_bss_801529C0->unkE74 = arg0;
    D_main_bss_801529C0->unkE70 = 0;
    if (D_main_bss_801529C0->unkE6C->unk0 != -1U) {
        neg = -1;
loop:
        cur = D_main_bss_801529C0->unkE6C;
        if (D_main_bss_801529C0->unkE74 + D_main_bss_801529C0->unk110[4] >= cur->unk0) {
            budget = cur->unk4;
            D_main_bss_801529C0->unk110[5] = budget;
            setTrackVoiceTickBudget(budget, D_main_bss_801529CB, D_main_bss_801529C0);
            prev = D_main_bss_801529C0->unkE6C;
            D_main_bss_801529C0->unkE6C = prev + 1;
            if (((s32 *)prev)[2] != neg) {
                goto loop;
            }
        }
    }
    { register u32 pr asm("$3"); register u32 qq asm("$2"); register s32 dd asm("$4"); qq = (u32)(D_main_bss_801529C0->unk110[5] * 0x600) / 240; dd = (s32)(D_main_bss_80142038 << 16) / D_main_bss_801440C0; pr = qq * dd; lo = pr * D_main_bss_801529C0->unkEC2; }
    D_main_bss_801529C0->unk110[2] = (lo >> 8) & 0xFFFF;
    D_main_bss_801529C0->unk110[3] = lo >> 24;
    D_main_bss_801529C0->unk110[4] = (s32)(lo >> 24) >> 1;
}

static inline s32 findSongSlotByHandle(u32 handle) {
    u32 i;

    for (i = 0; i < 8; i++) {
        if (D_main_bss_80149A00[i].unkEC1 == 0 && D_main_bss_80149A00[i].unk000 == (handle & 0x7FFFFFFF)) {
            return i | (handle & 0x80000000);
        }
    }
    return -1;
}
u16 getSongParamByHandle(u32 handle) {
    s32 slot;

    if (gMusyXActiveFlag != 0) {
        slot = findSongSlotByHandle(handle);
        if (slot != -1) {
            if (slot >= 0) {
                return D_main_bss_80149A00[slot].unkEC6;
            }
        }
    }
    return 0;
}

s32 isSongHandleActive(u32 handle) {
    if (gMusyXActiveFlag != 0) {
        return findSongSlotByHandle(handle) != -1;
    }
    return 0;
}

extern void stopVoicesByHandle(s32);

s32 stopSongByHandle(s32 handle) {
    struct D_main_bss_80149A00_type *e;
    struct D_main_bss_80149A00_type *e2;
    struct D_main_bss_801511C0_type *n;
    struct D_main_bss_801511C0_type *t;
    struct D_main_bss_801511C0_type *m;

    handle = findSongSlotByHandle(handle);
    if (handle != -1) {
        if (handle >= 0) {
            if (D_main_bss_80149A00[handle].unkEC0 != 0 && D_main_bss_80149A00[handle].unkEC1 == 0) {
                e = &D_main_bss_80149A00[handle];
                D_main_bss_80149A00[handle].unkEC0 = 0;
                n = e->unkE78[0];
                while (n != 0) {
                    stopVoicesByHandle(n->unk08);
                    n = n->unk00;
                }
                n = e->unkE78[1];
                while (n != 0) {
                    stopVoicesByHandle(n->unk08);
                    n = n->unk00;
                }
                e2 = &D_main_bss_80149A00[handle];
                m = e2->unkE78[0];
                if (m != 0) {
                    while (m->unk00 != 0) {
                        m = m->unk00;
                    }
                    if (D_main_bss_801529C4 != 0) {
                        m->unk00 = D_main_bss_801529C4;
                        D_main_bss_801529C4->unk04 = m;
                    }
                    t = e2->unkE78[0];
                    e2->unkE78[0] = 0;
                    D_main_bss_801529C4 = t;
                }
                m = e2->unkE78[1];
                if (m != 0) {
                    while (m->unk00 != 0) {
                        m = m->unk00;
                    }
                    if (D_main_bss_801529C4 != 0) {
                        m->unk00 = D_main_bss_801529C4;
                        D_main_bss_801529C4->unk04 = m;
                    }
                    t = e2->unkE78[1];
                    e2->unkE78[1] = 0;
                    D_main_bss_801529C4 = t;
                }
            }
        } else {
            handle &= 0x7FFFFFFF;
            if (D_main_bss_80149A00[handle].unkEC0 != 0 && D_main_bss_80149A00[handle].unkEC1 == 0) {
                D_main_bss_80149A00[handle].unkEEE |= 8;
            }
        }
    }
}

s32 stopSongByHandle(s32);

void stopSongByHandleLocked(s32 arg0) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        stopSongByHandle(arg0);
        factor5MutexRelease();
    }
}

extern void stopVoicesByHandle(s32);

void tickSongSequence(s32 handle) {
    struct D_main_bss_80149A00_type *e;
    struct D_main_bss_80149A00_type *e2;
    struct D_main_bss_801511C0_type *n;
    struct D_main_bss_801511C0_type *t;
    struct D_main_bss_801511C0_type *m;

    handle = findSongSlotByHandle(handle);
    if (handle != -1) {
        if (handle >= 0) {
            if (D_main_bss_80149A00[handle].unkEC0 != 0 && D_main_bss_80149A00[handle].unkEC1 == 0) {
                e = &D_main_bss_80149A00[handle];
                D_main_bss_80149A00[handle].unkEC0 = 0;
                n = e->unkE78[0];
                while (n != 0) {
                    stopVoicesByHandle(n->unk08);
                    n = n->unk00;
                }
                n = e->unkE78[1];
                while (n != 0) {
                    stopVoicesByHandle(n->unk08);
                    n = n->unk00;
                }
                e2 = &D_main_bss_80149A00[handle];
                m = e2->unkE78[0];
                if (m != 0) {
                    while (m->unk00 != 0) {
                        m = m->unk00;
                    }
                    if (D_main_bss_801529C4 != 0) {
                        m->unk00 = D_main_bss_801529C4;
                        D_main_bss_801529C4->unk04 = m;
                    }
                    t = e2->unkE78[0];
                    e2->unkE78[0] = 0;
                    D_main_bss_801529C4 = t;
                }
                m = e2->unkE78[1];
                if (m != 0) {
                    while (m->unk00 != 0) {
                        m = m->unk00;
                    }
                    if (D_main_bss_801529C4 != 0) {
                        m->unk00 = D_main_bss_801529C4;
                        D_main_bss_801529C4->unk04 = m;
                    }
                    t = e2->unkE78[1];
                    e2->unkE78[1] = 0;
                    D_main_bss_801529C4 = t;
                }
            }
            D_main_bss_80149A00[handle].unkEC1 = 1;
        } else {
            handle &= 0x7FFFFFFF;
            if (D_main_bss_80149A00[handle].unkEC0 != 0 && D_main_bss_80149A00[handle].unkEC1 == 0) {
                D_main_bss_80149A00[handle].unkEF0[0] = 0;
            }
        }
    }
}

void tickSongSequenceLocked(s32 arg0) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        tickSongSequence(arg0);
        factor5MutexRelease();
    }
}

void tickActiveSongs(void) {
    u32 i;

    for (i = 0; i < 8; i++) {
        tickSongSequence(D_main_bss_80149A00[i].unk000);
    }
}

s32 setSongPauseStateByHandle(u32 handle, u8 paused) {
    s32 slot;

    if (gMusyXActiveFlag != 0) {
        slot = findSongSlotByHandle(handle);
        if (slot != -1) {
            if (slot >= 0) {
                D_main_bss_80149A00[slot].unkEC5 = paused == 0;
                return 1;
            }
        }
    }
    return 0;
}

s32 applySongU16ParamCmd(s32 handle, s32 value) {
    handle = findSongSlotByHandle(handle);
    if (handle != -1) {
        if (handle >= 0) {
            D_main_bss_80149A00[handle].unkEC2 = value;
        } else {
            handle &= 0x7FFFFFFF;
            D_main_bss_80149A00[handle].unkEEC = value;
            D_main_bss_80149A00[handle].unkEEE |= 0x20;
        }
    }
}

s32 applySongU16ParamCmd(s32, s32);

void applySongU16ParamCmdLocked(s32 arg0, s32 arg1) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        applySongU16ParamCmd(arg0, arg1 & 0xFFFF);
        factor5MutexRelease();
    }
}

s32 quiesceSongSlotCmd(s32 handle) {
    handle = findSongSlotByHandle(handle);
    if (handle != -1) {
        if (handle >= 0) {
            D_main_bss_80149A00[handle].unkEC0 = 1;
        } else {
            D_main_bss_80149A00[handle & 0x7FFFFFFF].unkEEE &= ~8;
        }
    }
}

s32 quiesceSongSlotCmd(s32);

void quiesceSongSlotCmdLocked(s32 arg0) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        quiesceSongSlotCmd(arg0);
        factor5MutexRelease();
    }
}

s32 setSongParamPairCmd(s32 handle, s32 a, s32 b) {
    handle = findSongSlotByHandle(handle);
    if (handle != -1) {
        if (handle >= 0) {
            D_main_bss_80149A00[handle].unk110[0] = a;
            D_main_bss_80149A00[handle].unk110[1] = b;
        } else {
            handle &= 0x7FFFFFFF;
            D_main_bss_80149A00[handle].unkEC8[7] = a;
            D_main_bss_80149A00[handle].unkEC8[8] = b;
            D_main_bss_80149A00[handle].unkEEE |= 0x10;
        }
    }
}

s32 setSongParamPairCmd(s32, s32, s32);

void setSongParamPairCmdLocked(s32 arg0, s32 arg1, s32 arg2) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        setSongParamPairCmd(arg0, arg1, arg2);
        factor5MutexRelease();
    }
}

INCLUDE_ASM("asm/nonmatchings/main/94F50", queueAudioVoiceCmdLocked);

void queueAudioVoiceCmdLocked(u8, u16, s32, u8);
void queueAudioVoiceCmd(u8 arg0, u16 arg1, s32 arg2, u8 arg3) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        queueAudioVoiceCmdLocked(arg0, arg1, arg2, arg3);
        factor5MutexRelease();
    }
}

u8 getSongStateByteByHandle(u32 handle) {
    s32 slot;

    if (gMusyXActiveFlag != 0) {
        slot = findSongSlotByHandle(handle);
        if (slot != -1) {
            return D_main_bss_80149A00[slot].unkEC4;
        }
    }
    return 0;
}

void setAudioFaderState(u8, s32);
void setSongChannelParamByHandle(u32 handle, u8 ch, u8 val) {
    s32 slot;

    if (gMusyXActiveFlag != 0) {
        slot = findSongSlotByHandle(handle);
        if (slot != -1) {
            D_main_bss_80149A00[slot].unk528[ch] = val;
            setAudioFaderState(val, 2);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/94F50", processSongByHandle);

s32 processSongByHandle(s32, s32, s32);

void playSongIfMusyXActive(s32 arg0, s32 arg1) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        processSongByHandle(arg0, arg1, 0);
        factor5MutexRelease();
    }
}

s32 isSongHandleFree(s32 *h) {
    s32 v = *h;
    if (v != -1) {
        return ((u32)v >> 31) ^ 1;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/94F50", tickAllActiveSongs);

void initSongSequencerPools(void) {
    struct D_main_bss_801511C0_type *var_v1_2;
    u32 var_a0;
    s32 var_a1;

    for (var_a0 = 0; var_a0 < 8; var_a0++) {
        D_main_bss_80149A00[var_a0].unkEC0 = 0;
        D_main_bss_80149A00[var_a0].unkEC1 = 1; 
    }
    var_v1_2 = NULL;
    D_main_bss_801529C4 = &D_main_bss_801511C0;
    for (var_a1 = 0; var_a1 < 0x100; var_a1++) {
        D_main_bss_801511C0[var_a1].unk04 = var_v1_2;
        if (var_v1_2 != NULL) {
            var_v1_2->unk00 = &D_main_bss_801511C0[var_a1];
        }
        var_v1_2 = &D_main_bss_801511C0[var_a1];
    }
    var_v1_2->unk00 = NULL;
    D_main_bss_801499F0 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main/94F50", fake_func_8009711C);
