#include "common.h"

#include "mission_overlay/0B4EC0.h"

u32 D_mission_overlay_8010BC80[4];
f32 D_mission_overlay_8010BC90[4];

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5820);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5828);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5830);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5838);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5840);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5848);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B4EC0", playerXwingInit);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B4EC0", playWeaponFireSound);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B4EC0", playerXwingFireBlaster);

typedef struct {
    /* 0x00 */ s32 idx;
    /* 0x04 */ f32 f4;
    /* 0x08 */ u32 w8;
    /* 0x0C */ u8 padC[0xC];
    /* 0x18 */ u8 b18;
    /* 0x19 */ u8 b19;
    /* 0x1A */ u16 h1A;
    /* 0x1C */ u8 b1C[0x10];
} XesNpc;

typedef struct {
    /* 0x000 */ s32 mesh;
    /* 0x004 */ u8 pad4[0xB0];
    /* 0x0B4 */ u16 hB4;
    /* 0x0B6 */ u16 hB6;
    /* 0x0B8 */ s32 index;
    /* 0x0BC */ u8 padBC[0x158 - 0xBC];
    /* 0x158 */ u16 h158;
    /* 0x15A */ u8 pad15A[2];
    /* 0x15C */ s32 w15C;
    /* 0x160 */ f32 f160;
    /* 0x164 */ f32 f164;
    /* 0x168 */ f32 f168;
    /* 0x16C */ u8 pad16C[0x178 - 0x16C];
    /* 0x178 */ s32 w178;
    /* 0x17C */ u8 pad17C[0x2A0 - 0x17C];
} XesPlayer;

typedef struct {
    u8 pad0[0x1A];
    u16 mask1A;
    u8 pad1C;
    u8 mask1D;
    u16 mask1E;
    u8 pad20[4];
} XesHud;

typedef struct {
    u8 pad0[4];
    u8 *p4;
    u8 pad8[0x144 - 8];
} XesCam;

extern u8 D_main_bss_80137DBC[];
extern u16 D_main_bss_80130B88[][3];
extern XesHud D_mission_overlay_8010BE18[];
extern XesCam D_main_bss_80138D18[];
extern u8 gGameSettings;
void playerXwingFireBlaster(void *, u32, void *);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void playSpeechClipOncePerLevel(s32, s32);
u8 tickHudInstanceTargetingAndSpawns(s32, f32, void *, s32, s32, void *, s32);
void dispatchHudInstanceWeaponEffect(s32, s32, void *, s32, s32, s32, s32);
s32 findLockOnTarget(void *, void *, u16, f32, f32, f32);
void tickCraftAnimationSlot(s32, f32);

#define XP ((XesPlayer *)D_main_bss_80137DBC)

void playXwingEngineSound(XesNpc *e, f32 dt) {
    XesPlayer *p;
    u8 *b4;
    f32 f;
    struct { u8 b[0x10]; } sp28;
    u16 out[2];
    register void *a1 asm("$5");
    s32 mode;
    u32 w;

    p = &XP[e->idx];
    b4 = D_main_bss_80137DBC - 4;
    if (*(u16 *)(b4 + p->index * 0x2A0 + 0x184) & 1) {
        D_mission_overlay_8010BC80[e->idx] = e->w8;
        D_mission_overlay_8010BC90[e->idx] = e->f4;
        f = p->f160;
        if (0.0f < f) {
            p->f160 = f - dt;
        } else if (D_main_bss_80130B88[e->idx][0] & D_mission_overlay_8010BE18[e->idx].mask1A) {
          w = e->w8;
          if (w != 1) {
            mode = *(s32 *)(b4 + e->idx * 0x2A0 + 0x160);
            if (mode == 1) {
                p->f160 = f + p->f168;
                playerXwingFireBlaster(e, p->h158, 0);
                playerXwingFireBlaster(e, p->h158 + 1, 0);
                p->h158 ^= 2;
                play3DSoundEvent(0, (u8 *)p + 4, (u8 *)p + 0x28, 20.0f, 0.2f, 0, 3, 0x5A, 0x28);
            } else if (mode == 2) {
                p->f160 = (f32)((f64)f + (f64)p->f168 * 1.5);
                playerXwingFireBlaster(e, 0, 0);
                playerXwingFireBlaster(e, 1, 0);
                playerXwingFireBlaster(e, 2, 0);
                playerXwingFireBlaster(e, 3, 0);
                play3DSoundEvent(0, (u8 *)p + 4, (u8 *)p + 0x28, 20.0f, 0.2f, 0, 4, 0x5A, 0x28);
            } else {
                p->f160 = f + p->f164;
                playerXwingFireBlaster(e, p->h158, &sp28);
                p->h158 = (p->h158 + 1) & 3;
                play3DSoundEvent(0, &sp28, (u8 *)p + 0x28, 20.0f, 0.2f, 0, 2, 0x5A, 0x28);
            }
          } else if (e->b18 == 0) {
            e->b18 = w;
            if (e->f4 > 0.95f) {
                playSpeechClipOncePerLevel(gGameSettings != 0xF ? 0x134 : 0x28C, 9);
            }
          }
        } else {
            e->b18 = 0;
        }
        if (tickHudInstanceTargetingAndSpawns(0, dt, (u8 *)p + 4, p->mesh, (D_main_bss_80130B88[e->idx][0] & 0xFF) & D_mission_overlay_8010BE18[e->idx].mask1D, out, p->hB6)) {
            dispatchHudInstanceWeaponEffect(0, p->hB6, (u8 *)p + 4, p->mesh, p->w178, e->b19, out[0]);
            e->b19 ^= 1;
        }
        if (D_main_bss_80130B88[e->idx][0] & D_mission_overlay_8010BE18[e->idx].mask1E) {
            p->w15C++;
            if (p->w15C >= 3) {
                p->w15C = 0;
            }
            p->h158 = 0;
        }
    }
    a1 = (u8 *)p + 4;
    {
        f32 range = 9.0f;
        u8 *bp = e->b1C;
        s32 hh = e->h1A;
        s32 r;
        s32 t;
        if (*(u16 *)(D_main_bss_80138D18[e->idx].p4 + 4) == 3) {
            range = 16.0f;
        }
        r = findLockOnTarget(a1, bp, hh, range, 0.992f, 12.5f);
        t = r & 0xFFFF;
        out[0] = r;
        if (t != 0xFFFF) {
            e->h1A = r;
        } else {
            e->h1A = t;
        }
    }
    tickCraftAnimationSlot(0, dt);
}

#include "main/3F160.h"
#include "main/02420.h"
typedef struct {
    /* 0x000 */ s32 mesh;
    /* 0x004 */ u8 pad4[0xB0];
    /* 0x0B4 */ u16 hB4;
    /* 0x0B6 */ u16 hB6;
    /* 0x0B8 */ s32 index;
    /* 0x0BC */ s32 ctx;
    /* 0x0C0 */ u8 padC0[0x178 - 0xC0];
    /* 0x178 */ s32 w178;
    /* 0x17C */ u8 pad17C[4];
    /* 0x180 */ u16 flags;
    /* 0x182 */ u8 pad182[2];
    /* 0x184 */ f32 f184;
    /* 0x188 */ u8 pad188[0x2A0 - 0x188];
} FalconUpdPlayer;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 *state;
    /* 0x08 */ void *w8;
    /* 0x0C */ s32 mesh;
    /* 0x10 */ u8 pad10[6];
    /* 0x16 */ u16 h16;
} FalconUpdNpc;

typedef XesCam FalconUpdCam;

#define FUP ((FalconUpdPlayer *)D_main_bss_80137DBC)
extern u16 D_main_bss_80139560[];
extern u8 D_mission_overlay_801097BC[];
extern u8 D_main_bss_80137DBC[];
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_801097BC[];
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];

void *walkMeshdef0List(char *);
void playerXwingInit(s32 *, s32, s32);
void loadPlayerStartPosition(void *, void *);
s32 refreshPlayerSecondaryWeaponHud(s32);
void allocateCraftAnimationStateForSlot(void *, s32, void *);
s32 allocateAndInitCraftNpcContext(f32, f32, s32);
void resetTransientPlayerStateFlags(void);
void resetCraftAnimationStateForSlot(s32);
void destroySceneNpcsAndUnlink(void *);
void cancelSceneQueueHandle(void *);
void releaseMeshAsset(s32);
void teardownHudInstancesAndUnbindNpcs(void);
void freePlayerAuxBuffersIfActive(s32);
void playWeaponFireSound(s32 *, s32);
void playXwingEngineSound(XesNpc *, f32);
void tryPlaySpatialSoundWithGates(void *, void *);
void enqueueMeshTypeForCleanup(s32);
void addNpcToVisibilityBucket(s32, s32, void *, f32);
void advanceNpcOnCurvedPath(s32, s32, void *, s32);
void updatePlayerHudFrame(s32, void *, void *);

s32 playerXwingUpdate(FalconUpdNpc *arg0, s32 arg1, u32 *arg2) {
    s32 *s0;
    FalconUpdPlayer *p;
    s32 flag;
    u16 sp10[2];
    u16 act;
    f32 *q;

    s0 = arg0->state;
    if ((arg1 & 0xFFFF) == 2 || !(D_mission_overlay_8010CA1C & 4)) {
        act = arg1;
        switch (act) {
        case 1:
            q = (f32 *)arg2;
            s0 = rs_malloc(0x28, 0);
            arg0->state = s0;
            p = &FUP[(s32)*(f32 *)arg2];
            p->mesh = (s32)walkMeshdef0List("xwing");
            p->hB6 = arg0->h16;
            arg0->mesh = p->mesh;
            arg0->w8 = (u8 *)p + 4;
            if (0.0f <= *(f32 *)arg2) {
                *(u16 *)((u8 *)&FUP[(s32)*(f32 *)arg2] - 2) = arg0->h16;
                p->index = (s32)*(f32 *)arg2;
                flag = 1;
            } else {
                flag = 0;
            }
            loadPlayerStartPosition(p, NULL);
            playerXwingInit(s0, (s32)*q, flag);
            p->w178 = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
            allocateCraftAnimationStateForSlot(p, 0, D_mission_overlay_801097BC);
            popNpcSlotFromTail(D_main_bss_80139560[1], (void *)arg0);
            popNpcSlotFromTail(D_main_bss_80139560[14], (void *)arg0);
            p->ctx = allocateAndInitCraftNpcContext(0.25f, 0.25f, 2);
            sp10[0] = arg0->h16;
            sp10[1] = p->hB4;
            spawnNpcOfType((void *)attached3DSoundEmitterNpcHandler, sp10, 1, 0x64);
            spawnNpcOfType((void *)attachedMeshOverlayNpcHandler, &arg0->h16, 1, 0x64);
            return 1;
        case 12:
            p = &FUP[*s0];
            p->f184 = 2.0f;
            p->flags = (p->flags & 0xFFDF) | 0x40;
            loadPlayerStartPosition(p, (u8 *)p + 4);
            playerXwingInit(s0, p->index, 0x40);
            resetTransientPlayerStateFlags();
            resetCraftAnimationStateForSlot(0);
            return 1;
        case 2:
            p = &FUP[*s0];
            cancelSceneQueueHandle(p);
            destroySceneNpcsAndUnlink(p);
            teardownHudInstancesAndUnbindNpcs();
            freePlayerAuxBuffersIfActive(0);
            rs_free((void *)p->ctx);
            releaseMeshAsset(p->mesh);
            return 1;
        case 3:
            playWeaponFireSound(s0, *arg2);
            playXwingEngineSound((XesNpc *)s0, *(f32 *)arg2);
            return 1;
        case 5:
            tryPlaySpatialSoundWithGates(&FUP[*s0], arg2);
            if (*(u16 *)arg2 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)arg2);
            }
            return 1;
        case 4:
            p = &FUP[*s0];
            enqueueMeshTypeForCleanup(p->mesh);
            if (!(p->flags & 0x100)) {
                if (*(u16 *)(D_main_bss_80138D18[p->index].p4 + 4) != 3) {
                    addNpcToVisibilityBucket(arg2[0], p->mesh, (u8 *)p + 4, 1.0f);
                    if (!(p->flags & 0x80)) {
                        advanceNpcOnCurvedPath(arg2[2], arg2[0], (u8 *)p + 4, p->ctx);
                    }
                }
                updatePlayerHudFrame(0, arg2, (u8 *)p + 4);
            }
            return 1;
        }
    }
    return 1;
}

u8 isWeaponSlotReady(u8 arg0) {
    u8 ret;
    ret = 0;
    if ((D_mission_overlay_8010BC80[arg0] != 1) || !(0.95f < D_mission_overlay_8010BC90[arg0])) {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B4EC0", fake_func_800B58B4);

// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
const u32 rodat_pad_0B4EC0 = 0x24640001;
