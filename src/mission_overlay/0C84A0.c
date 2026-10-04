#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", calculateDatItemDistanceToPlayer);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", initActorTowardNamedDatItem);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C84A0", initAnchoredActorTowardNamedDatItem);

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
