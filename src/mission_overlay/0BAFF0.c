#include "common.h"

#include "common_types.h"
#include "mission_overlay/0BAFF0.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BAFF0", playerFalconInit);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BAFF0", computeFalconFlightTransform);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BAFF0", D_mission_overlay_800A5E00);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BAFF0", D_mission_overlay_800A5E04);

typedef struct {
    s32 unk0;
    u8 pad4[0x28 - 4];
    u8 unk28[4];
    u8 pad2C[0xB6 - 0x2C];
    u16 unkB6;
    u8 padB8[0x16C - 0xB8];
    f32 unk16C;
    u8 pad170[0x2A0 - 0x170];
} FalconEngPlayer;

extern FalconEngPlayer D_main_bss_80137DBC[];
extern s32 D_mission_overlay_80109998[];
extern u8 D_mission_overlay_801099A0[];
extern u8 gGameSettings;
void lookupHmtTextureByName(s32, s32, s32, void *, void *, s32);
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void playSpeechClipOncePerLevel(s32, s32);

void triggerFalconEngineEffect(s32 *arg0, s32 arg1) {
    u8 sp28[0x30];
    u8 sp58[0x30];
    s32 *s3;
    s32 *tbl;
    FalconEngPlayer *s0;
    s32 a0;

    tbl = D_mission_overlay_80109998;
    s3 = tbl + (arg1 & 0xFF);
    s0 = &D_main_bss_80137DBC[*arg0];
    lookupHmtTextureByName(s0->unk0, *s3, 0, sp28, sp58, 0);
    dispatchCueByCategory(0, s0->unkB6, sp28, D_mission_overlay_801099A0, 1, 12.5f, s0->unk16C);
    lookupHmtTextureByName(s0->unk0, *s3, 1, sp28, sp58, 1);
    dispatchCueByCategory(0, s0->unkB6, sp28, D_mission_overlay_801099A0, 1, 12.5f, s0->unk16C);
    play3DSoundEvent(0, sp28, s0->unk28, 20.0f, 0.2f, 0, 0x2F, 0x6E, 0x3C);
    a0 = 0x28C;
    if (gGameSettings != 0xF) {
        a0 = 0x133;
    }
    playSpeechClipOncePerLevel(a0, 9);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BAFF0", bindFalconSubmodelMaterials);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BAFF0", playerFalconMainUpdate);

typedef struct {
    u8 pad0[0x1A];
    u16 mask1A;
    u8 pad1C;
    u8 mask1D;
    u16 mask1E;
    u8 pad20[4];
} HudDef;

typedef struct {
    s32 unk0;
    u8 pad4[0xB6 - 4];
    u16 unkB6;
    s32 unkB8;
    u8 padBC[0x158 - 0xBC];
    u16 unk158;
    u8 pad15A[2];
    s32 unk15C;
    f32 unk160;
    f32 unk164;
    u8 pad168[0x178 - 0x168];
    s32 unk178;
    u8 pad17C[4];
    u16 unk180;
    u8 pad182[0x2A0 - 0x182];
} FalconSpawnPlayer;

#define FSP ((FalconSpawnPlayer *)D_main_bss_80137DBC)
extern u16 D_main_bss_80130B88[][3];
extern HudDef D_mission_overlay_8010BE18[];
extern void triggerFalconEngineEffect(s32 *, s32);
extern void playerFalconMainUpdate(void *, s32 *, f32);
extern void tickCraftAnimationSlot(s32, f32);
extern u8 tickHudInstanceTargetingAndSpawns(s32, f32, void *, s32, s32, void *, s32);
extern void dispatchHudInstanceWeaponEffect(s32, s32, void *, s32, s32, s32, s32);

void spawnFalconEngineParticles(s32 *arg0, f32 dt) {
    u16 out[2];
    FalconSpawnPlayer *p;

    p = &FSP[*arg0];
    if (*(u16 *)((u8 *)D_main_bss_80137DBC + p->unkB8 * 0x2A0 + 0x180) & 1) {
        if (0.0f < p->unk160) {
            p->unk160 = p->unk160 - dt;
        } else if (D_main_bss_80130B88[*arg0][0] & D_mission_overlay_8010BE18[*arg0].mask1A) {
            p->unk160 = p->unk160 + p->unk164;
            triggerFalconEngineEffect(arg0, *((u8 *)&p->unk158 + 1));
            p->unk158 ^= 1;
        }
        if (tickHudInstanceTargetingAndSpawns(0, dt, (u8 *)p + 4, p->unk0, (D_main_bss_80130B88[*arg0][0] & 0xFF) & D_mission_overlay_8010BE18[*arg0].mask1D, out, p->unkB6)) {
            dispatchHudInstanceWeaponEffect(0, p->unkB6, (u8 *)p + 4, p->unk0, p->unk178, p->unk158, out[0]);
        }
        if (D_main_bss_80130B88[*arg0][0] & D_mission_overlay_8010BE18[*arg0].mask1E) {
            p->unk158 = 0;
            p->unk15C = (p->unk15C + 1) & 3;
        }
    }
    playerFalconMainUpdate(p, arg0, dt);
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

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u8 *p4;
    /* 0x08 */ u8 pad8[0x144 - 8];
} FalconUpdCam;

#define FUP ((FalconUpdPlayer *)D_main_bss_80137DBC)
extern FalconUpdCam D_main_bss_80138D18[];
extern u16 D_main_bss_80139560[];
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_80109990[];
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];

void *walkMeshdef0List(char *);
void loadPlayerStartPosition(void *, void *);
void playerFalconInit(s32 *, s32, s32);
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
void computeFalconFlightTransform(s32 *, s32);
void tryPlaySpatialSoundWithGates(void *, void *);
void enqueueMeshTypeForCleanup(s32);
void addNpcToVisibilityBucket(s32, s32, void *, f32);
void advanceNpcOnCurvedPath(s32, s32, void *, s32);
void updatePlayerHudFrame(s32, void *, void *);

s32 playerFalconUpdate(FalconUpdNpc *arg0, s32 arg1, u32 *arg2) {
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
            s0 = rs_malloc(0xC4, 0);
            arg0->state = s0;
            p = &FUP[(s32)*(f32 *)arg2];
            p->mesh = (s32)walkMeshdef0List("falcon");
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
            playerFalconInit(s0, (s32)*q, flag);
            p->w178 = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
            allocateCraftAnimationStateForSlot(p, 0, D_mission_overlay_80109990);
            popNpcSlotFromTail(D_main_bss_80139560[1], (void *)arg0);
            popNpcSlotFromTail(D_main_bss_80139560[14], (void *)arg0);
            p->ctx = allocateAndInitCraftNpcContext(0.6125f, 0.6125f, 5);
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
            playerFalconInit(s0, p->index, 0x40);
            resetTransientPlayerStateFlags();
            resetCraftAnimationStateForSlot(0);
            return 1;
        case 2:
            p = &FUP[*s0];
            destroySceneNpcsAndUnlink(p);
            cancelSceneQueueHandle(p);
            rs_free((void *)p->ctx);
            releaseMeshAsset(p->mesh);
            teardownHudInstancesAndUnbindNpcs();
            freePlayerAuxBuffersIfActive(0);
            return 1;
        case 3:
            computeFalconFlightTransform(s0, *arg2);
            spawnFalconEngineParticles(s0, *(f32 *)arg2);
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

#if 0
// https://decomp.me/scratch/yyxM0
f32 integrateFalconFlightPhysics(f32 arg0, f32 arg1, f32 arg2) {
    f32 temp_fa0;
    f32 var_fv0;

    if (!(fabsf(arg1 - arg0) > 0.35f)) {
        return arg1;
    }
    if (!(arg0 < arg1)) {
        if (!((arg0 - arg1) > 180.0f)) {
            var_fv0 = -70.0f;
        } else {
            var_fv0 = 70.0f;
        }
    } else {
        if (!(arg1 - arg0 > 180.0f)) {
            var_fv0 = 70.0f;
        } else {
            var_fv0 = -70.0f;
        }
    }
    arg0 += (arg2 * var_fv0);
    if (arg0 < 0.0f) {
        arg0 += 360.0f;
    } else if (360.0f < arg0) {
        arg0 -= 360.0f;
    }
    return arg0;
}

// DO NOT DELETE ME I AM REQUIRED FOR MATCHING
const u32 rodata_pad_0BAFF0[2] = {
    0x03A0F021,
    0x24040014,
};
#else
INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BAFF0", integrateFalconFlightPhysics);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BAFF0", D_mission_overlay_800A5ED4);
#endif
