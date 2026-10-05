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

INCLUDE_ASM("asm/nonmatchings/main/94F50", stepSongPitchBendLanes);

INCLUDE_ASM("asm/nonmatchings/main/94F50", stepSongModulationLanes);

INCLUDE_ASM("asm/nonmatchings/main/94F50", advanceSongRegion);

INCLUDE_ASM("asm/nonmatchings/main/94F50", updateSongTempoTickRate);

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

INCLUDE_ASM("asm/nonmatchings/main/94F50", stopSongByHandle);

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
