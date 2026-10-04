#include "common.h"
#include "common_types.h"

void *getNpcContextField8(u16);
s32 getPlayerField2(s32);

f32 calculateDatItemDistanceToPlayer(char *arg0) {
    f32 d[3];
    f32 *a;
    f32 *b;
    u8 *item;
    f32 len;

    item = getLevelDatItemByName(arg0);
    if (item != NULL && *(u16 *)(item + 6) != 0xFFFF) {
        a = getNpcContextField8(*(u16 *)(item + 6));
        b = getNpcContextField8(getPlayerField2(0) & 0xFFFF);
        d[0] = a[0] - b[0];
        d[1] = a[1] - b[1];
        d[2] = a[2] - b[2];
        __asm__("sqrt.s %0, %1" : "=f"(len) : "f"(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]));
        return len;
    }
    return 1e7f;
}

void *getCraftRecordByIdx(s32);

f32 getScaledPlayerCraftSpeed(void) {
    return (*(f32 *)((u8 *)(getCraftRecordByIdx(0)) + 4)) * 4.0f;
}

typedef struct {
    u8 pad0[4];
    f32 unk4;
    s32 unk8;
    f32 unkC;
    u8 unk10;
    u8 pad11[7];
    u8 action;
    u8 pad19[7];
} DatItemSpawnArgs;

s32 slotDispatcherIter(u16, s32, void *);
void *getLevelDatItemByName(char *);

void spawnEffectOnNamedDatItem(char *name, f32 arg1, s32 arg2, f32 arg3) {
    DatItemSpawnArgs args;
    u8 *item;

    item = getLevelDatItemByName(name);
    if (item != NULL && *(u16 *)(item + 6) != 0xFFFF) {
        args.action = 5;
        args.unk4 = arg1;
        args.unk8 = 0;
        args.unkC = arg3;
        args.unk10 = arg2;
        slotDispatcherIter(*(u16 *)(item + 6), 9, &args);
    }
}

u8 initActorAsType1(void *, void *, f32, f32, f32, f32, f32);

s32 initActorTowardNamedDatItem(char *name, char *targetName) {
    u8 *item;
    void *target;
    u8 *npc;
    f32 yaw;
    f32 pitch;

    item = getLevelDatItemByName(name);
    if (item != NULL) {
        if (*(u16 *)(item + 6) == 0xFFFF) {
            return 0;
        }
        target = getLevelDatItemByName(targetName);
        if (target == NULL) {
            return 0;
        }
        npc = *(u8 **)(getNpcContextByIndex(*(u16 *)(item + 6)) + 0x10);
        if (npc != NULL) {
            if (npc[0x112] == 1) {
                yaw = *(f32 *)(npc + 0x4C);
                pitch = *(f32 *)(npc + 0x50);
            } else {
                pitch = 0.0f;
                yaw = pitch;
            }
            return initActorAsType1(npc, target, pitch, 0.0f, 0.0f, 0.0f, yaw);
        }
    }
    return 0;
}

void *getLevelDatItemByName(char *);
u8 *getNpcContextByIndex(u16);
u8 initActorAsType1WithAnchor(void *, void *, f32, f32, f32, f32, f32);

s32 initAnchoredActorTowardNamedDatItem(char *name, char *targetName) {
    u8 *item;
    void *target;
    u8 *npc;
    f32 yaw;
    f32 pitch;

    item = getLevelDatItemByName(name);
    if (item == NULL) {
        return 0;
    }
    if (*(u16 *)(item + 6) == 0xFFFF) {
        return 0;
    }
    target = getLevelDatItemByName(targetName);
    if (target == NULL) {
        return 0;
    }
    npc = *(u8 **)(getNpcContextByIndex(*(u16 *)(item + 6)) + 0x10);
    if (npc == NULL) {
        return 0;
    }
    if (npc[0x112] != 1) {
        return 0;
    }
    yaw = *(f32 *)(npc + 0x4C);
    pitch = *(f32 *)(npc + 0x50);
    return initActorAsType1WithAnchor(npc, target, pitch, 0.0f, 0.0f, 0.0f, yaw);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", getDatItemHealth);

void *getLevelDatItemByName(char *);
u8 *getNpcContextByIndex(u16);
f32 getNpcHealthPercentage(void *);

f32 getDatItemHealthPercentage(char *name) {
    u8 *item;
    void *npc;

    item = getLevelDatItemByName(name);
    if (item != NULL && *(u16 *)(item + 6) != 0xFFFF) {
        npc = *(void **)(getNpcContextByIndex(*(u16 *)(item + 6)) + 0x10);
        if (npc != NULL) {
            return getNpcHealthPercentage(npc);
        }
    }
    return 100.0f;
}

s32 slotDispatcherIter(u16, s32, void *);

typedef struct {
    s32 value;
    u8 pad4[0x14];
    u8 action;
    u8 pad19[7];
} DatItemEffectArgs;

void despawnEffectOnNamedDatItem(char *name, s32 arg1) {
    DatItemEffectArgs args;
    u8 *item;

    item = getLevelDatItemByName(name);
    if (item != NULL && *(u16 *)(item + 6) != 0xFFFF && arg1 >= 0 && arg1 < 3) {
        args.action = 8;
        args.value = arg1;
        slotDispatcherIter(*(u16 *)(item + 6), 9, &args);
    }
}

extern f32 D_main_bss_8013973C;

void setLevelObjectTrackingScalar(f32 arg0) {
    D_main_bss_8013973C = arg0;
}

void playSpeechClip(s32, s32, f32, s32);

void playObjectiveVoiceLine1(s32 arg0) {
    playSpeechClip(arg0, 0x73, 0, 0x43);
}

void playObjectiveVoiceLine2(s32 arg0, f32 arg1) {
    playSpeechClip(arg0, 0x73, arg1, 0x43);
}

s32 initSpeechPlaybackState();

void dispatchHudEffectUpdate(void) {
    initSpeechPlaybackState();
}

s32 triggerStageMusicForNamedDatItem();

void delegateToLevelStageTick(void) {
    triggerStageMusicForNamedDatItem();
}

s32 triggerStageAmbientForNamedDatItem();

void triggerNamedAssetCue(void) {
    triggerStageAmbientForNamedDatItem();
}

s32 initSoundCueRequest();

void triggerSoundCueByType(void) {
    initSoundCueRequest();
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", fake_func_800C7DB4);

__asm__(".section .rodata\n.word 0x93C20010\n.section .text");
