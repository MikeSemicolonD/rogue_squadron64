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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", computeTrackedObjectWorldAnchor);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", beginCameraViewTransition);

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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", isCameraTransitionIdle);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", fake_func_800AE3E4);
