#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", playerSnowSpeederInit);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", composeEffectObjectTransformMatrix);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", tickEffectObjectMotionAndOrientation);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AB6E0", D_mission_overlay_800A536C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", tickCinematicEffectObject);

extern u8 *D_mission_overlay_8010B6D0;
typedef struct {
    s32 idx;
    void *p4;
    void *p8;
    void *pC;
    u8 p10[6];
    u16 h16;
} YwNpc;

typedef struct {
    s32 object;
    u8 p4[0xB0];
    u16 hB4;
    u16 hB6;
    s32 wB8;
    s32 wBC;
    u8 pC0[0x178 - 0xC0];
    s32 w178;
    u8 p17C[4];
    u16 h180;
    u8 p182[2];
    f32 f184;
    u8 p188[0x2A0 - 0x188];
} YwPlayer;

typedef struct {
    u8 p0[4];
    struct {
        u8 p0[4];
        u16 h4;
    } *p4;
    u8 p8[0x144 - 8];
} YwMeta;

typedef struct {
    u8 p0[2];
    u16 h2;
    u8 p4[0x18];
    u16 h1C;
} YwNpcTbl;

extern YwPlayer ywPlayers[] __asm__("D_main_bss_80137DBC");
extern YwMeta ywMeta[] __asm__("D_main_bss_80138D18");
extern YwNpcTbl ywNpcTbl __asm__("D_main_bss_80139560");
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_801098DC[];
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];
extern void *rs_malloc(s32, s32);
extern void rs_free(void *);
extern s32 walkMeshdef0List(char *);
extern void loadPlayerStartPosition(void *, void *);
extern void configurePlayerSecondaryWeaponHud(s32, s32, s32, s32);
extern s32 refreshPlayerSecondaryWeaponHud(s32);
extern void allocateCraftAnimationStateForSlot(void *, s32, void *);
extern void popNpcSlotFromTail(u16, void *);
extern void *allocateAndInitCraftNpcContext(f32, f32, s32);
extern void spawnNpcOfType(void *, void *, s32, s32);
extern void resetTransientPlayerStateFlags(void);
extern void resetCraftAnimationStateForSlot(s32);
extern void cancelSceneQueueHandle(void *);
extern void destroySceneNpcsAndUnlink(void *);
extern void releaseMeshAsset(s32);
extern void teardownHudInstancesAndUnbindNpcs(void);
extern void freePlayerAuxBuffersIfActive(s32);
extern void tryPlaySpatialSoundWithGates(void *, void *);
extern void destroyNpcSlotByIndex(u16);
extern void enqueueMeshTypeForCleanup(s32);
extern void addNpcToVisibilityBucket(s32, s32, void *, f32);
extern void advanceNpcOnCurvedPath(s32, s32, void *, void *);
extern void updatePlayerHudFrame(s32, void *, void *);

extern u8 D_main_8009EBBC;
extern u8 D_mission_overlay_8010964C[];
extern char D_mission_overlay_800A536C[];
extern void playerSnowSpeederInit(void *, s32, s32);
extern void loadEffectModelInstancePool(void);
extern void freeEffectModelInstancePool(void);
extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern void updateCinematicCameraStateMachine(void *, void *, s32);
extern void tickCraftAnimationSlot(s32, s32);
extern void composeEffectObjectTransformMatrix(void *, s32);
extern void tickCinematicEffectObject(void *, s32);
extern void advanceCameraTransitionOnCue(s32);
extern void submitCameraTrackedObjectToRender(void *);
s32 playerSnowSpeederUpdate(YwNpc *npc, u32 msg, s32 *arg) {
    YwPlayer *pl;
    u8 *anim;
    s32 s2;
    u16 sp18[0x18];
    void *np;
    s32 *a2;
    f32 *fa;

    anim = npc->p4;
    if (D_main_8009EBBC) {
        switch ((u16)msg) {
        case 2:
            pl = &ywPlayers[((YwNpc *)anim)->idx];
            goto destroy;
        case 3:
            pl = &ywPlayers[((YwNpc *)anim)->idx];
            lookupHmtTextureByName(pl->object, D_mission_overlay_800A536C, 0, sp18, 0, 0);
            updateCinematicCameraStateMachine(sp18, anim + 0x30, arg[0]);
            tickCraftAnimationSlot(0, arg[0]);
            return 1;
        case 4:
            pl = &ywPlayers[((YwNpc *)anim)->idx];
            enqueueMeshTypeForCleanup(pl->object);
            submitCameraTrackedObjectToRender(arg);
            return 1;
        case 9:
            goto cue;
        default:
            return 1;
        }
    }
    if ((u16)msg != 2 && (D_mission_overlay_8010CA1C & 4)) {
        return 1;
    }
    switch ((u16)msg) {
    case 1:
        fa = (f32 *)arg;
        anim = rs_malloc(0x120, 0);
        npc->p4 = anim;
        pl = &ywPlayers[(s32)fa[0]];
        D_mission_overlay_8010B6D0 = anim;
        pl->object = walkMeshdef0List("snowspeeder");
        pl->hB6 = npc->h16;
        npc->pC = (void *)pl->object;
        npc->p8 = (u8 *)pl + 4;
        if (fa[0] >= 0.0f) {
            ((u16 *)&ywPlayers[(s32)fa[0]])[-1] = npc->h16;
            pl->wB8 = (s32)fa[0];
            s2 = 1;
        } else {
            s2 = 0;
        }
        loadPlayerStartPosition(pl, 0);
        playerSnowSpeederInit(anim, (s32)fa[0], s2);
        pl->w178 = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
        loadEffectModelInstancePool();
        allocateCraftAnimationStateForSlot(pl, 0, D_mission_overlay_8010964C);
        popNpcSlotFromTail(ywNpcTbl.h2, npc);
        popNpcSlotFromTail(ywNpcTbl.h1C, npc);
        pl->wBC = (s32)allocateAndInitCraftNpcContext(0.125f, 0.125f, 4);
        sp18[0] = npc->h16;
        sp18[1] = pl->hB4;
        spawnNpcOfType(attached3DSoundEmitterNpcHandler, sp18, 1, 0x64);
        spawnNpcOfType(attachedMeshOverlayNpcHandler, &npc->h16, 1, 0x64);
        return 1;
    case 12:
        pl = &ywPlayers[((YwNpc *)anim)->idx];
        pl->f184 = 2.0f;
        pl->h180 = (pl->h180 & 0xFFDF) | 0x40;
        loadPlayerStartPosition(pl, (u8 *)pl + 4);
        playerSnowSpeederInit(anim, pl->wB8, 0x40);
        resetTransientPlayerStateFlags();
        resetCraftAnimationStateForSlot(0);
        return 1;
    case 2:
        pl = &ywPlayers[((YwNpc *)anim)->idx];
        cancelSceneQueueHandle(pl);
destroy:
        destroySceneNpcsAndUnlink(pl);
        rs_free((void *)pl->wBC);
        releaseMeshAsset(pl->object);
        teardownHudInstancesAndUnbindNpcs();
        freePlayerAuxBuffersIfActive(0);
        freeEffectModelInstancePool();
        return 1;
    case 3:
        composeEffectObjectTransformMatrix(anim, arg[0]);
        tickCinematicEffectObject(anim, arg[0]);
        return 1;
    case 9:
cue:
        if (*((u8 *)arg + 0x18) == 0xE) {
            advanceCameraTransitionOnCue(arg[1]);
        }
        return 1;
    case 5:
        tryPlaySpatialSoundWithGates(&ywPlayers[((YwNpc *)anim)->idx], arg);
        if (*(u16 *)arg != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)arg);
        }
        return 1;
    case 4:
        pl = &ywPlayers[((YwNpc *)anim)->idx];
        enqueueMeshTypeForCleanup(pl->object);
        a2 = arg;
        if (!(pl->h180 & 0x100)) {
            np = (u8 *)pl + 4;
            if (ywMeta[pl->wB8].p4->h4 != 3) {
                addNpcToVisibilityBucket(a2[0], pl->object, np, 1.0f);
                if (!(pl->h180 & 0x80)) {
                    advanceNpcOnCurvedPath(a2[2], a2[0], np, (void *)pl->wBC);
                }
            }
            updatePlayerHudFrame(0, a2, (u8 *)pl + 4);
            submitCameraTrackedObjectToRender(a2);
        }
        return 1;
    default:
        return 1;
    }
}

s32 getPlayerVehicleId(s32);
s32 slotDispatcherIter(u16, s32, void *);
extern u8 *D_mission_overlay_8010B6D0;
typedef struct {
    u8 pad0[0x18];
    u8 cmd;
    u8 pad19[7];
} SpecialSlotEffectArgs;
void triggerPlayerVehicleSpecialSlotEffect(void) {
    SpecialSlotEffectArgs args;

    if (getPlayerVehicleId(0) == 4 && D_mission_overlay_8010B6D0[0x2C] != 0 && D_mission_overlay_8010B6D0[0x2D] != 0) {
        args.cmd = 0xD;
        slotDispatcherIter(*(u16 *)(D_mission_overlay_8010B6D0 + 0xF0), 9, &args);
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", fake_func_800AD378);

__asm__(".section .rodata\n.word 0x03C0E821\n.word 0x8FBF001C\n.section .text");
