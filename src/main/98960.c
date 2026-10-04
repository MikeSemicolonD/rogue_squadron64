#include "common.h"
#include "common_types.h"

typedef struct {
    u8 active;
    u8 pad1[7];
    void *unk8;
    void *unkC;
    u8 pad10[8];
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

void copyFourHalfwordsWriteback(void *, void *);

void flushStreamedVoiceBuffers(void) {
    s32 i;

    for (i = 0; i < D_main_bss_80141AD0; i++) {
        if (D_main_bss_80152A20[i].active == 1) {
            copyFourHalfwordsWriteback(D_main_bss_80152A20[i].unk8, D_main_bss_80152A20[i].unkC);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/98960", startStreamedSampleVoice);

s32 streamSampleCountToByteSize(s32 arg0) {
    return (arg0 + 4) * 2;
}

extern u8 gMusyXActiveFlag;
s32 factor5MutexAcquire();
s32 factor5MutexRelease();
void setVoiceModulationParams(s32, s32, s32, s32, s32);

void setVoiceVolumePanLocked(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    if ((gMusyXActiveFlag != 0) & (~arg0 != 0)) {
        factor5MutexAcquire();
        setVoiceModulationParams(arg0, arg1 << 0x10, arg2 << 0x10, arg3 << 0x10, arg4 << 0x10);
        factor5MutexRelease();
    }
}

extern u8 gMusyXActiveFlag;
s32 factor5MutexAcquire();
s32 factor5MutexRelease();
void silenceVoiceSlot(s32);

void stopStreamedVoice(s32 arg0) {
    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        if (D_main_bss_80152A20[arg0].active == 1) {
            D_main_bss_80152A20[arg0].active = 0;
            silenceVoiceSlot(arg0);
        }
        factor5MutexRelease();
    }
}

INCLUDE_ASM("asm/nonmatchings/main/98960", compute3DSourceSpatialMix);

INCLUDE_ASM("asm/nonmatchings/main/98960", applyVoice3DMixParams);

extern f32 D_main_8003DEC0;
extern u8 gMusyXActiveFlag;
s32 factor5MutexAcquire();
s32 factor5MutexRelease();

typedef struct {
    s32 x, y, z;
} Vec3i;

typedef struct {
    u8 pad0[0xC];
    Vec3i pos;
    Vec3i vel;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
} Active3DSource;

s32 updateActive3DAudioSource(Active3DSource *arg0, Vec3i *arg1, Vec3i *arg2, u8 arg3) {
    f32 v;

    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        v = (f32)arg3 / D_main_8003DEC0;
        arg0->pos = *arg1;
        arg0->vel = *arg2;
        arg0->unk28 = v;
        if (v < arg0->unk2C) {
            arg0->unk2C = v;
        }
        factor5MutexRelease();
        return 1;
    }
    return 0;
}

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

extern s32 D_main_bss_80153414;
extern u8 gMusyXActiveFlag;
s32 flagVoiceChainForStop(s32);
s32 factor5MutexAcquire();
s32 factor5MutexRelease();

inline s32 factor5RemoveListNode(void *arg0) {
    s32 temp_a0;
    void **temp_v1_2;
    void *temp_v1;

    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        temp_v1 = (*(void **)((u8 *)(arg0) + 0));
        if (temp_v1 != NULL) {
            (*(void ***)((u8 *)(temp_v1) + 4)) = (void **) (*(void ***)((u8 *)(arg0) + 4));
        }
        temp_v1_2 = (*(void ***)((u8 *)(arg0) + 4));
        if (temp_v1_2 != NULL) {
            *temp_v1_2 = (*(void **)((u8 *)(arg0) + 0));
        } else {
            D_main_bss_80153414 = (s32) (*(void **)((u8 *)(arg0) + 0));
        }
        temp_a0 = (*(s32 *)((u8 *)(arg0) + 0x34));
        (*(s32 *)((u8 *)(arg0) + 8)) = (s32) (*(u16 *)((u8 *)(arg0) + 0xA));
        if (temp_a0 != -1) {
            flagVoiceChainForStop(temp_a0);
        }
        factor5MutexRelease();
        return 1;
    }
    return 0;
}

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

void tickAndReap3DAudioVoices(void) {
    void *node = (void *)D_main_bss_80153414;
    void *next;

    while (node != NULL) {
        next = *(void **)node;
        factor5RemoveListNode(node);
        node = next;
    }
}

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} IVec3;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} FVec3;

typedef struct {
    u8 pad0[0xC];
    IVec3 pos;
    IVec3 vel;
    IVec3 up;
    FVec3 cross;
    FVec3 fwd;
    f32 inv[15];
    f32 volume;
} MusyX3D;

extern f32 D_main_8003DECC;
extern void crossProductVec3(void *, void *, void *);
extern void invertOrientationMatrix(void *, void *);

s32 setMusyX3DProperties(MusyX3D *arg0, IVec3 *arg1, IVec3 *arg2, IVec3 *arg3, FVec3 *arg4, u8 arg5) {
    f32 sp10[12];

    if (gMusyXActiveFlag != 0) {
    factor5MutexAcquire();
    arg0->pos = *arg1;
    arg0->vel = *arg2;
    arg0->up = *arg3;
    arg0->fwd.x = -arg4->x;
    arg0->fwd.y = -arg4->y;
    arg0->fwd.z = -arg4->z;
    crossProductVec3(&arg0->cross, &arg0->fwd, &arg0->up);
    sp10[0] = arg0->cross.x;
    sp10[3] = arg0->cross.y;
    sp10[6] = arg0->cross.z;
    sp10[1] = arg0->fwd.x;
    sp10[4] = arg0->fwd.y;
    sp10[7] = arg0->fwd.z;
    sp10[2] = *(f32 *)&arg0->up.x;
    sp10[5] = *(f32 *)&arg0->up.y;
    sp10[8] = *(f32 *)&arg0->up.z;
    sp10[9] = *(f32 *)&arg0->pos.x;
    sp10[10] = *(f32 *)&arg0->pos.y;
    sp10[11] = *(f32 *)&arg0->pos.z;
    invertOrientationMatrix(&arg0->inv, sp10);
    arg0->volume = (f32)arg5 / D_main_8003DECC;
    factor5MutexRelease();
    return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/main/98960", register3DAudioListenerNode);

extern s32 D_main_bss_80153418;
s32 unlinkMusyXListNode(void *arg0) {
    void **temp_v1_2;
    void *temp_v1;

    if (gMusyXActiveFlag != 0) {
        factor5MutexAcquire();
        temp_v1 = (*(void **)((u8 *)(arg0) + 0));
        if (temp_v1 != NULL) {
            (*(void ***)((u8 *)(temp_v1) + 4)) = (void **) (*(void ***)((u8 *)(arg0) + 4));
        }
        temp_v1_2 = (*(void ***)((u8 *)(arg0) + 4));
        if (temp_v1_2 != NULL) {
            *temp_v1_2 = (*(void **)((u8 *)(arg0) + 0));
        } else {
            D_main_bss_80153418 = (s32) (*(void **)((u8 *)(arg0) + 0));
        }
        factor5MutexRelease();
        return 1;
    }
    return 0;
}

typedef struct SndNode {
    struct SndNode *next;
    f32 pri;
    void *snd;
} SndNode;
typedef struct {
    s32 id;
    s32 unk4;
    SndNode *head;
} SndGroup;
extern SndGroup D_main_bss_80152D70[];
extern u8 D_main_bss_80152EF0;
extern SndNode D_main_bss_80153290[];
extern u8 D_main_bss_80153410;

void enqueueSoundInPriorityGroup(void *arg0, f32 arg1) {
    s32 i;
    SndNode *prev;
    SndNode *cur;
    s32 cnt;
    s32 k;

    for (i = 0; i < D_main_bss_80152EF0; i++) {
        if (*(s32 *)((u8 *)arg0 + 0x38) == D_main_bss_80152D70[i].id) {
            break;
        }
    }
    if (i == D_main_bss_80152EF0) {
        D_main_bss_80152D70[i].unk4 = 0;
        D_main_bss_80152D70[i].head = 0;
        cnt = *(s32 *)((u8 *)arg0 + 0x38);
        D_main_bss_80152EF0++;
        D_main_bss_80152D70[i].id = cnt;
    }
    cur = D_main_bss_80152D70[i].head;
    prev = 0;
    while (cur != 0) {
        if (arg1 < cur->pri) {
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    if (prev == 0) {
        D_main_bss_80152D70[i].head = &D_main_bss_80153290[D_main_bss_80153410];
    } else {
        prev->next = &D_main_bss_80153290[D_main_bss_80153410];
    }
    k = D_main_bss_80153410;
    D_main_bss_80153290[k].next = cur;
    D_main_bss_80153290[k].snd = arg0;
    D_main_bss_80153410 = k + 1;
    D_main_bss_80153290[k].pri = arg1;
}

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
