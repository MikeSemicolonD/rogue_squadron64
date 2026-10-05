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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B4EC0", playXwingEngineSound);

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

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u8 *p4;
    /* 0x08 */ u8 pad8[0x144 - 8];
} FalconUpdCam;

#define FUP ((FalconUpdPlayer *)D_main_bss_80137DBC)
extern FalconUpdCam D_main_bss_80138D18[];
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
void playXwingEngineSound(s32 *, s32);
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
            playXwingEngineSound(s0, *arg2);
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
