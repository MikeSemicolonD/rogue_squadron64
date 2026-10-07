#include "common.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BD840", D_mission_overlay_800A5FE0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BD840", D_mission_overlay_800A5FE8);

#include "common_types.h"
extern u8 D_main_bss_80137DBC[][0x2A0];
extern s32 D_main_bss_80130B58;
extern struct { u8 pad[0x18]; u16 unk18; u8 pad1A[0xA]; } D_mission_overlay_8010BE18[];
extern s32 D_mission_overlay_8010BEA8[][16];
extern void initPlayerCraftMovementMode(void *);
extern s32 countTrailingZeros16(u16);

void playerT16Init(void *argv, s32 arg1, s32 arg2) {
    s32 *arg0 = argv;
    u8 *p = D_main_bss_80137DBC[arg1];
    f32 hp;
    *(s16 *)(p + 0x180) = arg2;
    arg0[0] = arg1;
    *(u16 *)(p + 0xB4) = 7;
    initPlayerCraftMovementMode(p);
    hp = 80.0f;
    if (D_main_bss_80130B58 & 0x40) {
        hp = 40.0f;
    }
    *(f32 *)(p + 0xC0) = hp;
    *(f32 *)(p + 0xE8) = 3.0f;
    *(f32 *)(p + 0xC4) = hp;
    *(f32 *)(p + 0xEC) = 3.0f;
    ((f32 *)arg0)[1] = 1.0f;
    *(f32 *)(p + 0xF0) = 0.2f;
    *(f32 *)(p + 0xF4) = 0.1f;
    *(f32 *)(p + 0xF8) = 1.8f;
    *(f32 *)(p + 0xFC) = 2.0f;
    *(f32 *)(p + 0x104) = 15.0f;
    *(f32 *)(p + 0x108) = 10.0f;
    *(s32 *)(p + 0x13C) = 0;
    *(s32 *)(p + 0x14C) = 0;
    *(f32 *)(p + 0x110) = -30.0f;
    *(f32 *)(p + 0x114) = -35.0f;
    *(f32 *)(p + 0x118) = 30.0f;
    *(f32 *)(p + 0x120) = 60.0f;
    *(f32 *)(p + 0x124) = 180.0f;
    *(f32 *)(p + 0x130) = 0.75f;
    *(f32 *)(p + 0x134) = 2.0f;
    *(f32 *)(p + 0x138) = 20.0f;
    *(f32 *)(p + 0x140) = 10.0f;
    *(f32 *)(p + 0x144) = 60.0f;
    *(f32 *)(p + 0x148) = 10.0f;
    *(f32 *)(p + 0x150) = 5.0f;
    *(s32 *)(p + 0x11C) = 0;
    *(f32 *)(p + 0x128) = 0.1f;
    *(f32 *)(p + 0x12C) = 0.1f;
    *(s32 *)(p + 0xD8) = 0;
    *(s32 *)(p + 0xDC) = 0;
    *(s32 *)(p + 0xE0) = 0;
    *(u16 *)(p + 0x158) = 0;
    *(f32 *)(p + 0x154) = 40.0f;
    *(s32 *)(p + 0x160) = 0;
    *(f32 *)(p + 0x164) = 0.3f;
    *(s32 *)(p + 0x170) = 0;
    *(f32 *)(p + 0x168) = 0.5f;
    *(f32 *)(p + 0x174) = 0.3f;
    D_mission_overlay_8010BEA8[arg0[0]][countTrailingZeros16(D_mission_overlay_8010BE18[arg0[0]].unk18)] = 0;
}

typedef struct {
    u8 pad0[0x12];
    u16 maskA;
    u8 pad14[4];
    u16 maskB;
    u8 pad1A[0xA];
} T16Cfg;

typedef struct {
    u8 pad0[0xB8];
    s32 owner;
    u8 padBC[0xE8 - 0xBC];
    f32 fE8;
    f32 fEC;
    f32 fF0;
    f32 fF4;
    u8 padF8[0x180 - 0xF8];
    u16 flags;
    u8 pad182[0x2A0 - 0x182];
} T16Craft;

typedef struct {
    s32 index;
    f32 scale;
} T16Arg;

extern u16 D_main_bss_80130B88[][3];
extern u8 D_main_bss_8013800C[][0x2A0];
extern s32 getCraftAnimationSlotFlag(s32);
extern f32 getCraftAnimationSlotValue(s32);
extern void setCraftAnimationSlotParams(s32, s32, f32);
extern void updatePlayerCraftPhysics(void *, f32);
extern void computeBootConfigScaledVec4(s32, f32, f32, void *, f32, f32);

void computeT16TransformImpl(T16Arg *arg0, f32 dt) __asm__("computeT16Transform");
void computeT16TransformImpl(T16Arg *arg0, f32 dt) {
    T16Craft *c;
    f32 fs0;
    f32 sc;
    f32 t;
    f32 e8;
    f32 lim;
    u16 bits;
    register f32 *tb asm("$16");
    register T16Cfg *cf asm("$19");

    c = (T16Craft *)D_main_bss_80137DBC[arg0->index];
    if (*(u16 *)((s32)D_main_bss_80137DBC + c->owner * 0x2A0 + 0x180) & 1) {
        fs0 = c->fEC;
        sc = 0.375f;
        if ((D_main_bss_80130B88[arg0->index][0] & ((T16Cfg *)D_mission_overlay_8010BE18)[arg0->index].maskA) && !(D_main_bss_80130B88[arg0->index][0] & ((T16Cfg *)D_mission_overlay_8010BE18)[arg0->index].maskB)) {
            sc = 0.0f;
            fs0 -= 0.3f;
        }
        {
            f32 t1 = arg0->scale * 1.875f;
            if (fs0 < t1) {
                fs0 = t1;
            }
        }
        { s32 hi; __asm__("lui %0, %%hi(D_mission_overlay_8010BE18)" : "=r"(hi)); __asm__("addiu %0, %1, %%lo(D_mission_overlay_8010BE18)" : "=r"(cf) : "r"(hi)); }
        {
            s32 k = countTrailingZeros16(cf[arg0->index].maskB);
            tb = (f32 *)D_mission_overlay_8010BEA8;
            fs0 += *(f32 *)((k << 2) + (arg0->index << 6) + (s32)tb) * 0.6f;
        }
        countTrailingZeros16(cf[arg0->index].maskB);
        {
        s32 ii = arg0->index;
        __asm__("" : "+r"(ii));
        if (D_main_bss_80130B88[ii][0] & cf[ii].maskB) {
            if (!(u8)getCraftAnimationSlotFlag(0)) {
                setCraftAnimationSlotParams(0, 1, 0.0f);
            }
        } else if ((u8)getCraftAnimationSlotFlag(0) == 1) {
            if (getCraftAnimationSlotValue(0) == 0.0f) {
                setCraftAnimationSlotParams(0, 1, 0.5f);
            }
        }
        }
        bits = D_main_bss_80130B88[arg0->index][0];
        if (!(bits & ((T16Cfg *)D_mission_overlay_8010BE18)[arg0->index].maskA) && !(bits & ((T16Cfg *)D_mission_overlay_8010BE18)[arg0->index].maskB) && c->fE8 < 3.0f) {
            f32 t2 = arg0->scale * 3.0f;
            fs0 += 0.3f;
            if (t2 < fs0) {
                fs0 = t2;
            }
        }
        {
            register f32 t3 asm("$f2") = arg0->scale * 6.0f;
            if (t3 < fs0) {
                fs0 = t3;
            }
        }
        {
            f32 e8a = c->fE8;
            f32 la = c->fF0;
            c->fEC = fs0;
            if (la < fs0 - e8a) {
                c->fE8 = e8a + la;
            } else {
                c->fE8 = fs0;
            }
        }
        e8 = c->fE8;
        lim = c->fF4;
        if (fs0 - e8 < -lim) {
            c->fE8 = e8 - lim;
        } else {
            c->fE8 = fs0;
        }
        __asm__("" :: "f"(sc));
        arg0->scale = 1.0f;
    }
    updatePlayerCraftPhysics(c, dt);
    sc = 0.375f;
    t = arg0->scale;
    computeBootConfigScaledVec4(arg0->index, sc, sc, D_main_bss_8013800C[arg0->index], (c->fE8 - t * 1.875f) / (t * 4.125f) + 1.0f, dt);
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BD840", D_mission_overlay_800A6074);

typedef struct {
    s32 unk0;
    u8 pad4[0x28 - 4];
    f32 unk28;
    u8 pad2C[0xB6 - 0x2C];
    u16 unkB6;
    s32 unkB8;
    u8 padBC[0x158 - 0xBC];
    u16 unk158;
    u8 pad15A[2];
    s32 unk15C;
    f32 unk160;
    f32 unk164;
    u8 pad168[0x16C - 0x168];
    f32 unk16C;
    u8 pad170[0x178 - 0x170];
    s32 unk178;
    u8 pad17C[4];
    u16 unk180;
    u8 pad182[0x2A0 - 0x182];
} T16MuPlayer;

typedef struct {
    u8 pad0[0x1A];
    u16 mask1A;
    u8 pad1C;
    u8 mask1D;
    u16 mask1E;
    u8 pad20[4];
} T16HudDef;

typedef struct {
    s16 unk0;
    u8 pad2[0x16];
    f32 unk18;
    u8 pad1C[4];
} T16MuSlotArgs;

#define T16P ((T16MuPlayer *)D_main_bss_80137DBC)
extern u16 t16Btn[][3] __asm__("D_main_bss_80130B88");
extern T16HudDef t16Hud[] __asm__("D_mission_overlay_8010BE18");
extern char D_mission_overlay_800A6074[];
extern u8 D_mission_overlay_80109A48[];
void lookupHmtTextureByName(void *, char *, s32, void *, s32, s32);
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);
s32 slotDispatcherIter(u16, s32, void *);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void tickCraftAnimationSlot(s32, f32);
extern u8 tickHudInstanceTargetingAndSpawns(s32, f32, void *, s32, s32, void *, s32);
extern void dispatchHudInstanceWeaponEffect(s32, s32, void *, s32, s32, s32, s32);

void t16MuImpl(s32 *arg0, f32 dt) __asm__("playerT16MainUpdate");
void t16MuImpl(s32 *arg0, f32 dt) {
    u8 tex[0x30];
    T16MuSlotArgs args;
    u16 out[2];
    T16MuPlayer *p;
    u16 cue;

    p = &T16P[*arg0];
    if (*(u16 *)((u8 *)D_main_bss_80137DBC + p->unkB8 * 0x2A0 + 0x180) & 1) {
        if (0.0f < p->unk160) {
            p->unk160 = p->unk160 - dt;
        } else if (t16Btn[*arg0][0] & t16Hud[*arg0].mask1A) {
            p->unk160 = p->unk160 + p->unk164;
            {
                T16MuPlayer *q = &T16P[*arg0];
                lookupHmtTextureByName((void *)q->unk0, D_mission_overlay_800A6074, p->unk158 & 1, tex, 0, 0);
                cue = dispatchCueByCategory(0, q->unkB6, tex, D_mission_overlay_80109A48, 1, 12.5f, q->unk16C);
                args.unk0 = 1;
                args.unk18 = 0.7f;
                slotDispatcherIter(cue, 10, &args);
                play3DSoundEvent(0, tex, &q->unk28, 20.0f, 0.2f, 0, 0x31, 0x64, 0x32);
            }
            p->unk158 ^= 1;
        }
        if (tickHudInstanceTargetingAndSpawns(0, dt, (u8 *)p + 4, p->unk0, (t16Btn[*arg0][0] & 0xFF) & t16Hud[*arg0].mask1D, out, p->unkB6)) {
            dispatchHudInstanceWeaponEffect(0, p->unkB6, (u8 *)p + 4, p->unk0, p->unk178, p->unk158, out[0]);
        }
        if (t16Btn[*arg0][0] & t16Hud[*arg0].mask1E) {
            p->unk158 = 0;
            p->unk15C = (p->unk15C + 1) & 3;
        }
    }
    tickCraftAnimationSlot(0, dt);
}

#include "main/3F160.h"
#include "main/02420.h"
typedef struct {
    u8 *mesh;
    u8 pad04[0xB4 - 4];
    u16 u0B4;
    u16 u0B6;
    s32 u0B8;
    void *u0BC;
    u8 pad0C0[0x178 - 0xC0];
    s32 u178;
    u8 pad17C[0x180 - 0x17C];
    u16 u180;
    u8 pad182[2];
    f32 u184;
    u8 pad188[0x2A0 - 0x188];
} T16Player;
extern u8 D_main_bss_80137DBC[][0x2A0];
extern struct { u8 pad0[2]; u16 u2; u8 pad4[0x18]; u16 u1C; } D_main_bss_80139560;
extern u8 D_mission_overlay_80109A40[];
typedef struct { u8 pad0[4]; u8 *u4; u8 pad8[0x144 - 8]; } T16Cell;
extern T16Cell D_main_bss_80138D18[];
extern s32 D_mission_overlay_8010CA1C;
extern void *walkMeshdef0List(char *);
extern void loadPlayerStartPosition(void *, void *);
extern void playerT16Init(void *, s32, s32);
extern void computeT16Transform(void *, s32);
extern void playerT16MainUpdate(void *, s32);
extern s32 refreshPlayerSecondaryWeaponHud(s32);
extern void allocateCraftAnimationStateForSlot(void *, s32, void *);
extern void resetCraftAnimationStateForSlot(s32);
extern void resetTransientPlayerStateFlags(void);
extern void *allocateAndInitCraftNpcContext(f32, f32, s32);
extern void cancelSceneQueueHandle(void *);
extern void destroySceneNpcsAndUnlink(void *);
extern void rs_free(void *);
extern void releaseMeshAsset(void *);
extern void teardownHudInstancesAndUnbindNpcs(void);
extern void freePlayerAuxBuffersIfActive(s32);
extern void tryPlaySpatialSoundWithGates(void *, void *);
extern void enqueueMeshTypeForCleanup(void *);
extern void addNpcToVisibilityBucket(s32, void *, void *, f32);
extern void advanceNpcOnCurvedPath(s32, s32, void *, void *);
extern void updatePlayerHudFrame(s32, void *, void *);
extern s32 attached3DSoundEmitterNpcHandler();
extern s32 attachedMeshOverlayNpcHandler();

s32 playerT16Update(struct D_80130BB8_type *self, u16 arg1, f32 *arg2) {
    s32 *state = (s32 *)self->unk04;
    T16Player *p;
    s32 hasSlot;
    u16 args[2];
    u16 slot;
    f32 *alias;

    if (arg1 != 2 && (D_mission_overlay_8010CA1C & 4)) {
        return 1;
    }
    {
        switch (arg1 & 0xFFFF) {
        case 1:
            alias = arg2;
            state = rs_malloc(8, 0);
            self->unk04 = (void *)state;
            p = (T16Player *)D_main_bss_80137DBC[(s32)arg2[0]];
            p->mesh = walkMeshdef0List("t16");
            p->u0B6 = self->unk16;
            self->unk0C = (u32)p->mesh;
            self->unk08 = (void *)((u8 *)p + 4);
            if (arg2[0] >= 0.0f) {
                ((u16 *)D_main_bss_80137DBC[(s32)arg2[0]])[-1] = self->unk16;
                p->u0B8 = (s32)arg2[0];
                hasSlot = 1;
            } else {
                hasSlot = 0;
            }
            loadPlayerStartPosition(p, NULL);
            playerT16Init(state, (s32)alias[0], hasSlot);
            p->u178 = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
            allocateCraftAnimationStateForSlot(p, 0, D_mission_overlay_80109A40);
            popNpcSlotFromTail(D_main_bss_80139560.u2, self);
            popNpcSlotFromTail(D_main_bss_80139560.u1C, self);
            p->u0BC = allocateAndInitCraftNpcContext(0.25f, 0.25f, 6);
            args[0] = self->unk16;
            args[1] = p->u0B4;
            spawnNpcOfType(attached3DSoundEmitterNpcHandler, args, 1, 0x64);
            spawnNpcOfType(attachedMeshOverlayNpcHandler, &self->unk16, 1, 0x64);
            return 1;
        case 12:
            p = (T16Player *)D_main_bss_80137DBC[state[0]];
            p->u184 = 2.0f;
            p->u180 = (p->u180 & 0xFFDF) | 0x40;
            loadPlayerStartPosition(p, (u8 *)p + 4);
            playerT16Init(state, p->u0B8, 0x40);
            resetTransientPlayerStateFlags();
            resetCraftAnimationStateForSlot(0);
            return 1;
        case 2:
            p = (T16Player *)D_main_bss_80137DBC[state[0]];
            cancelSceneQueueHandle(p);
            destroySceneNpcsAndUnlink(p);
            rs_free(p->u0BC);
            releaseMeshAsset(p->mesh);
            teardownHudInstancesAndUnbindNpcs();
            freePlayerAuxBuffersIfActive(0);
            return 1;
        case 3:
            computeT16Transform(state, *(s32 *)arg2);
            playerT16MainUpdate(state, *(s32 *)arg2);
            return 1;
        case 5:
            tryPlaySpatialSoundWithGates(D_main_bss_80137DBC[state[0]], arg2);
            if (*(u16 *)arg2 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)arg2);
                return 1;
            }
            return 1;
        case 4:
            p = (T16Player *)D_main_bss_80137DBC[state[0]];
            enqueueMeshTypeForCleanup(p->mesh);
            if (!(p->u180 & 0x100)) {
                if (*(u16 *)(D_main_bss_80138D18[p->u0B8].u4 + 4) != 3) {
                    addNpcToVisibilityBucket(*(s32 *)arg2, p->mesh, (u8 *)p + 4, 1.0f);
                    if (!(p->u180 & 0x80)) {
                        advanceNpcOnCurvedPath(((s32 *)arg2)[2], *(s32 *)arg2, (u8 *)p + 4, p->u0BC);
                    }
                }
                updatePlayerHudFrame(0, arg2, (u8 *)p + 4);
            }
            return 1;
        }
    }
    return 1;
}

#include "common_types.h"
#include "player.h"
extern char D_mission_overlay_800A6074[];
extern u8 D_mission_overlay_80109A48[];
extern u8 D_main_bss_80137DBC[][0x2A0];
void lookupHmtTextureByName(void *, char *, s32, void *, s32, s32);
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);
s32 slotDispatcherIter(u16, s32, void *);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
typedef struct {
    s16 unk0;
    u8 pad2[0x16];
    f32 unk18;
    u8 pad1C[4];
} T16SlotArgs;
void triggerT16Effect(s32 *arg0, s32 arg1) {
    u8 tex[0x30];
    T16SlotArgs args;
    struct inner_player_struct *p = (struct inner_player_struct *)D_main_bss_80137DBC[*arg0];
    u16 cue;

    lookupHmtTextureByName(p->object, D_mission_overlay_800A6074, arg1 & 1, tex, 0, 0);
    cue = dispatchCueByCategory(0, p->unk0B6, tex, D_mission_overlay_80109A48, 1, 12.5f, p->blasterDamageMultiplier);
    args.unk0 = 1;
    args.unk18 = 0.7f;
    slotDispatcherIter(cue, 10, &args);
    play3DSoundEvent(0, tex, &p->unk028, 20.0f, 0.2f, 0, 0x31, 0x64, 0x32);
}

const u32 rodata_pad_0BD840 = 0x8FBE0030;
