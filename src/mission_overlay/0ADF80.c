#include "common.h"
#include "common_types.h"

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 padC[0xC];
    f32 unk18;
    u8 pad1C[0x8];
    f32 unk24;
    u8 pad28[0x8];
    f32 unk30;
    u8 pad34[0xC];
    u8 mesh[0xB4];
    u8 active;
    u8 padF5[3];
} EffectModelInstance;

extern EffectModelInstance *D_mission_overlay_8010B6E0;

void computeTrackedObjectWorldAnchor(s8 *obj) {
    EffectModelInstance *pool = D_mission_overlay_8010B6E0;

    if (pool[((u8 *)obj)[1]].active) {
        *(f32 *)(obj + 0x40) = pool[((u8 *)obj)[1]].unk0 + pool[((u8 *)obj)[1]].unk18;
        *(f32 *)(obj + 0x44) = pool[((u8 *)obj)[1]].unk4 + pool[((u8 *)obj)[1]].unk24;
        *(f32 *)(obj + 0x48) = pool[((u8 *)obj)[1]].unk8 + pool[((u8 *)obj)[1]].unk30;
    } else {
        *(f32 *)(obj + 0x40) = *(f32 *)(obj + 0x44) = *(f32 *)(obj + 0x48) = 0.0f;
    }
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0ADF80", D_mission_overlay_800A53E0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0ADF80", D_mission_overlay_800A53F8);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", updateCinematicCameraStateMachine);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", submitCameraTrackedObjectToRender);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", emitEffectParticlesAlongPath);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", loadEffectModelInstancePool);

extern s8 D_mission_overlay_8010B6E8;

void resetEffectSequenceState(void) {
    D_mission_overlay_8010B6E8 = 0;
}

extern void releaseMeshAsset(void *);
extern void rs_free(void *);

void freeEffectModelInstancePool(void) {
    u32 i;

    for (i = 0; i < 60; i++) {
        releaseMeshAsset(D_mission_overlay_8010B6E0[i].mesh);
    }
    rs_free(D_mission_overlay_8010B6E0);
}

extern s32 D_mission_overlay_8010B738;

s32 getEffectModelPoolHandle(void) {
    return D_mission_overlay_8010B738;
}

typedef struct {
    s32 m[12];
} CameraXform12;

typedef struct {
    f32 x, y, z;
} CameraVec3;

void beginCameraViewTransition(CameraXform12 *xf, CameraVec3 *target, u8 *flags) {
    u8 *s = (u8 *)&D_mission_overlay_8010B6E8;

    if (target != NULL) {
        *(CameraVec3 *)(s + 0x34) = *target;
        s[3] = 1;
    } else {
        s[3] = 0;
    }
    s[0] = 1;
    *(CameraXform12 *)(s + 4) = *xf;
    s[1] = 0;
    s[2] = 0;
    flags[0] = 0;
    flags[1] = 0;
    *(s32 *)(s + 0x50) += 1;
}

void requestCameraSnapToTrackedAnchor(void) {
    (*(s8 *)((u8 *)(&D_mission_overlay_8010B6E8) + 0)) = 4;
    computeTrackedObjectWorldAnchor(&D_mission_overlay_8010B6E8);
    (*(s32 *)((u8 *)(&D_mission_overlay_8010B6E8) + 0x4C)) = 0;
}

void beginCameraTrackedTransition(void) {
    (*(s8 *)((u8 *)(&D_mission_overlay_8010B6E8) + 0)) = 3;
    computeTrackedObjectWorldAnchor(&D_mission_overlay_8010B6E8);
    (*(s32 *)((u8 *)(&D_mission_overlay_8010B6E8) + 0x4C)) = 0;
}

void advanceCameraTransitionOnCue(s32 arg0) {
    if (((u8) (*(s8 *)((u8 *)(&D_mission_overlay_8010B6E8) + 0)) == 3) && ((*(s32 *)((u8 *)(&D_mission_overlay_8010B6E8) + 0x50)) == arg0)) {
        (*(s8 *)((u8 *)(&D_mission_overlay_8010B6E8) + 0)) = 4;
    }
}

s32 isCameraTransitionIdle(void) {
    s32 ret = 0;
    u8 state = D_mission_overlay_8010B6E8;

    if (state == 0 || state == 4) {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", fake_func_800AE3E4);
