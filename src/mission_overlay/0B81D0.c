#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B81D0", D_mission_overlay_800A5B20);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B81D0", playerYwingInit);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B81D0", tickCraftAbilityCooldown);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B81D0", D_mission_overlay_800A5B9C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B81D0", orientEffectToVelocity);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B81D0", spawnTexturedExplosionBurst);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B81D0", playerYwingUpdate);

typedef struct {
    s32 unk0;
    u8 pad4[0xB2];
    u16 unkB6;
    u8 padB8[0xB4];
    f32 unk16C;
    u8 pad170[0x130];
} EffectCueSrc;

typedef struct {
    u8 pad0[4];
    struct {
        u8 pad0[4];
        u16 unk4;
    } *unk4;
    u8 pad8[0x13C];
} EffectCueMeta;

typedef struct {
    f32 x, y, z;
} EffectCueVec;

extern EffectCueSrc D_main_bss_80137DBC[];
extern EffectCueMeta D_main_bss_80138D18[];
extern char D_mission_overlay_800A5B9C[];
extern u8 D_mission_overlay_801098B0[];
extern EffectCueVec D_mission_overlay_801098E4[];
void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
void accumulateVectorInObjectFrame(void *, void *, void *);
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);

void emitTexturedEffectCue(s32 *arg0, s32 arg1, EffectCueVec *arg2) {
    struct {
        EffectCueVec v;
        u8 pad[0x20];
    } sp20;
    s32 s2;
    EffectCueSrc *s1;
    char *name = D_mission_overlay_800A5B9C;

    s2 = arg1 & 1;
    s1 = &D_main_bss_80137DBC[*arg0];
    lookupHmtTextureByName(s1->unk0, name, s2, &sp20.v, 0, 0);
    if (D_main_bss_80138D18[*arg0].unk4->unk4 == 3) {
        accumulateVectorInObjectFrame(&sp20.v, &D_mission_overlay_801098E4[s2], s1);
    }
    dispatchCueByCategory(0, s1->unkB6, &sp20.v, D_mission_overlay_801098B0, 1, 12.5f, s1->unk16C);
    *arg2 = sp20.v;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B81D0", fake_func_800B89F4);

static u32 D_mission_overlay_800A5C18[] __attribute__((section(".rodata"))) = { 0, 0x27BDFFC8 };
