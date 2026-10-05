#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A5990);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A5998);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A59A0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", playerAwingInit);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", resetEngineTrailQuads);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", acquireLockOnTarget);

typedef struct {
    s32 unk0;
    u8 pad4[0xB2];
    u16 unkB6;
    u8 padB8[0xB4];
    f32 unk16C;
    u8 pad170[0x2A0 - 0x170];
} ImpactObj;
typedef struct {
    u8 pad0[4];
    struct { u8 pad[4]; u16 unk4; } *unk4;
} ImpactAux;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} ImpV3;
extern ImpactObj D_main_bss_80137DBC[];
extern u8 D_main_bss_80138D18[];
extern f32 D_mission_overlay_80109880[][3];
extern u8 D_mission_overlay_80109800[];
void lookupHmtTextureByName(s32, char *, s32, f32 *, s32, s32);
void accumulateVectorInObjectFrame(f32 *, f32 *, void *);
void quatFromAxisAngle(f32 *, f32 *, f32);
void rotateVec3ByQuat(f32 *, f32 *, f32 *);
void dispatchCueByCategory(s32, u16, f32 *, void *, s32, f32, f32);

void emitTexturedImpactEffect(u8 *arg0, s32 arg1, ImpV3 *arg2) {
    f32 m[4][3];
    ImpV3 sp50;
    f32 sp60[4];
    ImpactObj *o;
    s32 bit;
    f32 v;
    char *name;

    o = &D_main_bss_80137DBC[*(s32 *)arg0];
    if (arg1 & 1) {
        lookupHmtTextureByName(o->unk0, "b", 0, m[0], 0, 0);
    } else {
        lookupHmtTextureByName(o->unk0, "a", 0, m[0], 0, 0);
    }
    if (((ImpactAux *)(D_main_bss_80138D18 + *(s32 *)arg0 * 0x144))->unk4->unk4 == 3) {
        bit = arg1 & 1;
        accumulateVectorInObjectFrame(m[0], D_mission_overlay_80109880[bit], o);
        if (bit != 0) {
            v = *(f32 *)(arg0 + 0x44);
            if (v > 0.0f) {
                if (v < 18.0f) {
                    quatFromAxisAngle(sp60, m[2], -v * 0.8f);
                    sp50 = *(ImpV3 *)m[1];
                    rotateVec3ByQuat(sp60, (f32 *)&sp50, m[1]);
                }
            }
        } else {
            v = *(f32 *)(arg0 + 0x40);
            if (v < 0.0f) {
                if (v > -18.0f) {
                    quatFromAxisAngle(sp60, m[2], -v * 0.8f);
                    sp50 = *(ImpV3 *)m[1];
                    rotateVec3ByQuat(sp60, (f32 *)&sp50, m[1]);
                }
            }
        }
    }
    dispatchCueByCategory(0, o->unkB6, m[0], D_mission_overlay_80109800, 1, 15.0f, o->unk16C);
    *arg2 = *(ImpV3 *)m[0];
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", updateEngineThrustEffect);

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
} AwUpdPlayer;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 *state;
    /* 0x08 */ void *w8;
    /* 0x0C */ s32 mesh;
    /* 0x10 */ u8 pad10[6];
    /* 0x16 */ u16 h16;
} AwUpdNpc;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u8 *p4;
    /* 0x08 */ u8 pad8[0x144 - 8];
} AwUpdCam;

#define AUP ((AwUpdPlayer *)D_main_bss_80137DBC)
extern u16 D_main_bss_80139560[];
extern u8 D_mission_overlay_8010986C[];
extern s32 D_mission_overlay_8010CA1C;
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];

void *walkMeshdef0List(char *);
void playerAwingInit(s32 *, s32, s32);
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
void resetEngineTrailQuads(s32 *, s32);
void updateEngineThrustEffect(s32 *, s32);
void tryPlaySpatialSoundWithGates(void *, void *);
void enqueueMeshTypeForCleanup(s32);
void addNpcToVisibilityBucket(s32, s32, void *, f32);
void advanceNpcOnCurvedPath(s32, s32, void *, s32);
void updatePlayerHudFrame(s32, void *, void *);

s32 playerAwingUpdate(AwUpdNpc *arg0, s32 arg1, u32 *arg2) {
    s32 *s0;
    AwUpdPlayer *p;
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
            s0 = rs_malloc(0x4C, 0);
            arg0->state = s0;
            p = &AUP[(s32)*(f32 *)arg2];
            p->mesh = (s32)walkMeshdef0List("awing");
            p->hB6 = arg0->h16;
            arg0->mesh = p->mesh;
            arg0->w8 = (u8 *)p + 4;
            if (0.0f <= *(f32 *)arg2) {
                *(u16 *)((u8 *)&AUP[(s32)*(f32 *)arg2] - 2) = arg0->h16;
                p->index = (s32)*(f32 *)arg2;
                flag = 1;
            } else {
                flag = 0;
            }
            loadPlayerStartPosition(p, NULL);
            playerAwingInit(s0, (s32)*q, flag);
            p->w178 = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
            allocateCraftAnimationStateForSlot(p, 0, D_mission_overlay_8010986C);
            popNpcSlotFromTail(D_main_bss_80139560[1], (void *)arg0);
            popNpcSlotFromTail(D_main_bss_80139560[14], (void *)arg0);
            p->ctx = allocateAndInitCraftNpcContext(0.125f, 0.125f, 0);
            sp10[0] = arg0->h16;
            sp10[1] = p->hB4;
            spawnNpcOfType((void *)attached3DSoundEmitterNpcHandler, sp10, 1, 0x64);
            spawnNpcOfType((void *)attachedMeshOverlayNpcHandler, &arg0->h16, 1, 0x64);
            return 1;
        case 12:
            p = &AUP[*s0];
            p->f184 = 2.0f;
            p->flags = (p->flags & 0xFFDF) | 0x40;
            loadPlayerStartPosition(p, (u8 *)p + 4);
            playerAwingInit(s0, p->index, 0x40);
            resetTransientPlayerStateFlags();
            resetCraftAnimationStateForSlot(0);
            return 1;
        case 2:
            p = &AUP[*s0];
            destroySceneNpcsAndUnlink(p);
            cancelSceneQueueHandle(p);
            rs_free((void *)p->ctx);
            releaseMeshAsset(p->mesh);
            teardownHudInstancesAndUnbindNpcs();
            freePlayerAuxBuffersIfActive(0);
            return 1;
        case 3:
            resetEngineTrailQuads(s0, *arg2);
            updateEngineThrustEffect(s0, *arg2);
            return 1;
        case 5:
            tryPlaySpatialSoundWithGates(&AUP[*s0], arg2);
            if (*(u16 *)arg2 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)arg2);
            }
            return 1;
        case 4:
            p = &AUP[*s0];
            enqueueMeshTypeForCleanup(p->mesh);
            if (!(p->flags & 0x100)) {
                if (*(u16 *)(((AwUpdCam *)D_main_bss_80138D18)[p->index].p4 + 4) != 3) {
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

u16 acquireLockOnTarget(s32 arg0, s32 arg1, u16 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6);

u16 findLockOnTarget(s32 arg0, s32 arg1, u16 arg2, s32 arg3, f32 arg4, f32 arg5) {
    return acquireLockOnTarget(arg0, arg1, arg2, arg3, arg4, arg5, 0);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", fake_func_800B75C4);


// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
const u32 rodat_pad_0B64C0[2] = { 0x93C20000, 0x24430001 };
