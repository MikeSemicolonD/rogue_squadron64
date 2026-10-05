#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B81D0", D_mission_overlay_800A5B20);

typedef struct {
    s32 object;
    u8 p4[0xB4 - 0x4];
    s16 fB4;
    u8 pB6[0xC0 - 0xB6];
    f32 fC0;
    f32 fC4;
    u8 pC8[0xD8 - 0xC8];
    s32 fD8;
    s32 fDC;
    s32 fE0;
    u8 pE4[4];
    f32 fE8;
    f32 fEC;
    f32 fF0;
    f32 fF4;
    f32 fF8;
    f32 fFC;
    u8 p100[4];
    f32 f104;
    f32 f108;
    f32 f10C;
    f32 f110;
    f32 f114;
    f32 f118;
    s32 f11C;
    f32 f120;
    f32 f124;
    f32 f128;
    f32 f12C;
    f32 f130;
    f32 f134;
    f32 f138;
    s32 f13C;
    f32 f140;
    f32 f144;
    f32 f148;
    s32 f14C;
    f32 f150;
    f32 f154;
    s16 f158;
    u8 p15A[6];
    s32 f160;
    f32 f164;
    f32 f168;
    u8 p16C[4];
    s32 f170;
    f32 f174;
    s32 f178;
    u8 p17C[4];
    s16 f180;
} CraftPlayer;

typedef struct {
    s32 idx;
    u16 h4;
    u8 p6[2];
    s32 w8;
    s32 wC;
    u8 name[4];
    s32 mat;
} CraftAnim;

extern CraftPlayer sCraftPlayers[] __asm__("D_main_bss_80137DBC");
extern s32 D_main_bss_80130B58;
void initPlayerCraftMovementMode(CraftPlayer *);
s32 lookupHmtMaterialByName(s32, char *, void *);

void playerYwingInit(CraftAnim *anim, s32 idx, s16 arg2) {
    CraftPlayer *p;
    f32 speed;

    p = (CraftPlayer *)((u8 *)sCraftPlayers + idx * 0x2A0);
    p->f180 = arg2;
    anim->idx = idx;
    p->fB4 = 1;
    initPlayerCraftMovementMode(p);
    speed = 350.0f;
    if (D_main_bss_80130B58 & 0x40) {
        speed = 40.0f;
    }
    p->fC0 = speed;
    p->fC4 = speed;
    p->f11C = (p->f14C = (p->f13C = 0));
    p->fE0 = (p->fDC = (p->fD8 = 0));
    p->f158 = 0;
    p->f160 = 0;
    p->fF0 = 0.025f;
    p->fE8 = 2.25f;
    p->fEC = 2.25f;
    p->fF4 = 0.112500004f;
    p->fF8 = 1.3f;
    p->fFC = 2.0f;
    p->f104 = 15.0f;
    p->f108 = 10.0f;
    p->f110 = -40.0f;
    p->f114 = -35.0f;
    p->f118 = 60.0f;
    p->f120 = 60.0f;
    p->f124 = 180.0f;
    p->f130 = 0.75f;
    p->f134 = 2.0f;
    p->f138 = 10.0f;
    p->f140 = 5.0f;
    p->f144 = 40.0f;
    p->f148 = 5.0f;
    p->f150 = 5.0f;
    p->f154 = 40.0f;
    p->f164 = 0.25f;
    p->f128 = 0.1f;
    p->f170 = 0;
    p->f12C = 0.15f;
    p->f168 = 0.5f;
    p->f174 = 0.25f;
    anim->h4 = 0xFFFF;
    anim->w8 = 0;
    anim->wC = 0;
    anim->mat = lookupHmtMaterialByName(p->object, "tpgn_trn", anim->name);
}

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
