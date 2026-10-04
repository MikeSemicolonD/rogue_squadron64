#include "common.h"

#include "main/1D000.h"
#include "main/4D900.h"

INCLUDE_ASM("asm/nonmatchings/main/4D900", applyPlayerVehicleStateUpdate);

INCLUDE_ASM("asm/nonmatchings/main/4D900", rotateObjectMatrixAboutStoredAxis);

INCLUDE_ASM("asm/nonmatchings/main/4D900", updatePlayerVehicleByControlMode);

INCLUDE_ASM("asm/nonmatchings/main/4D900", updateEffectObjectMotionOnTerrain);

INCLUDE_ASM("asm/nonmatchings/main/4D900", applyObjectLocalToWorldTransform);

INCLUDE_ASM("asm/nonmatchings/main/4D900", updateEffectObjectOrientationQuat);

INCLUDE_ASM("asm/nonmatchings/main/4D900", releaseEffectObjectNpcSlots);

INCLUDE_ASM("asm/nonmatchings/main/4D900", releaseEffectObjectNpcSlotsVariant);

INCLUDE_ASM("asm/nonmatchings/main/4D900", buildEffectObjectWorldTransform);

INCLUDE_ASM("asm/nonmatchings/main/4D900", destroyEffectObjectTypeNpcSlots);

INCLUDE_ASM("asm/nonmatchings/main/4D900", computeBootConfigScaledVec4);

INCLUDE_ASM("asm/nonmatchings/main/4D900", initPlayerVehicleStateTables);

INCLUDE_ASM("asm/nonmatchings/main/4D900", updateMultiNodeAudioListeners);

INCLUDE_ASM("asm/nonmatchings/main/4D900", resetEffectObjectVecQuads);

INCLUDE_ASM("asm/nonmatchings/main/4D900", activateSceneNodeAndAudioListener);

INCLUDE_ASM("asm/nonmatchings/main/4D900", updateEffectObjectTransformPieces);

INCLUDE_ASM("asm/nonmatchings/main/4D900", spawnRandomizedEffectBurst);

INCLUDE_ASM("asm/nonmatchings/main/4D900", spawnScatteredDebrisParticles);

INCLUDE_ASM("asm/nonmatchings/main/4D900", submitActiveEffectObjectRender);

INCLUDE_ASM("asm/nonmatchings/main/4D900", initEffectObjectDefaults);

INCLUDE_ASM("asm/nonmatchings/main/4D900", spawnEffectObjectAtNpc);

INCLUDE_ASM("asm/nonmatchings/main/4D900", initEffectObjectFromLevelData);

INCLUDE_ASM("asm/nonmatchings/main/4D900", destroyEffectObjectAndAssets);

INCLUDE_ASM("asm/nonmatchings/main/4D900", deactivateEffectObject);

INCLUDE_ASM("asm/nonmatchings/main/4D900", refreshEffectObjectCamerasAndState);

#include "player.h"
extern void *D_main_8009EB98[];
void updateEffectObjectTransformPieces(void *, s32, s32, f32, s32);
void dispatchEffectObjectBehavior(s32 idx, s32 kind, s32 arg2) {
    updateEffectObjectTransformPieces(D_main_8009EB98[kind], idx, arg2, 0.046875f, gPlayers[idx].inner.unk178[0x14]);
}

typedef struct {
    u8 pad0[4];
    void *unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x4C];
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    u8 pad74[0xD0];
} SceneNode;
extern s32 D_main_bss_80138260;
extern SceneNode *D_main_bss_80138894;
extern SceneNode D_main_bss_80138D18[];
void registerSceneNodeAndInvertRotation(u8 *obj, u8 *node) {
    if (D_main_bss_80138260 == 1) {
        D_main_bss_80138894->unk4 = node;
    } else {
        D_main_bss_80138D18[*(s32 *)(node + 0xC)].unk4 = node;
    }
    mat3x3InverseInto(obj + 0x2C, node + 0x28);
}

INCLUDE_ASM("asm/nonmatchings/main/4D900", initTransformNodeFromVectors);

// The argument types for `arg0` and `arg1` are almost certainly wrong, but function isn't called anywhere so who cares
void computeAimAnglesFromObjectPositions(Mat4x3 arg0, Mat4x3 arg1, Vec3f arg2, f32 arg3) {
    Vec3f sp10;
    f32 temp_fa0;
    f32 temp_ft1;
    f32 temp_fv0;

    sp10[0] = arg1[3][0] - arg0[3][0];
    sp10[1] = arg1[3][1] - arg0[3][1];
    sp10[2] = arg1[3][2] - arg0[3][2];
    temp_ft1 = vec3Length(sp10);
    arg2[2] = arg3;
    if (temp_ft1 > 0.0001f) {
        temp_fv0 = 1.0f / temp_ft1;
        sp10[0] = temp_fv0 * sp10[0];
        sp10[1] = temp_fv0 * sp10[1];
        sp10[2] = temp_fv0 * sp10[2];
        arg2[1] = RADIAN_TO_DEGREE_F(sinfApprox(sp10[1]));
        arg2[0] = RADIAN_TO_DEGREE_F(atan2Approx(-sp10[0], sp10[2]));
    }
}

INCLUDE_ASM("asm/nonmatchings/main/4D900", setupSceneNodeTransitionBetweenNodes);

INCLUDE_ASM("asm/nonmatchings/main/4D900", requestCinematicNodeEvent);

INCLUDE_ASM("asm/nonmatchings/main/4D900", resetSceneNodeShakeStateArray);

INCLUDE_ASM("asm/nonmatchings/main/4D900", clearSceneNodeMotionFields);

INCLUDE_ASM("asm/nonmatchings/main/4D900", refreshAllSceneNodeInverseTransforms);

// The argument types for `arg0` and `arg1` are probably wrong, but this function is unused so who cares
void computeAimAnglesFromPoints(Vec3f arg0, Vec3f arg1, Vec3f arg2, f32 arg3) {
    Vec3f sp10;
    f32 temp_fv0; 
    f32 temp_fv0_2;
    f32 temp_fv0_3;

    sp10[0] = arg1[0] - arg0[0];
    sp10[1] = arg1[1] - arg0[1];
    sp10[2] = arg1[2] - arg0[2];
    temp_fv0 = vec3Length(sp10);
    if (temp_fv0 > 0.0001f) {
        temp_fv0_2 = 1.0f / temp_fv0;
        sp10[0] = temp_fv0_2 * sp10[0];
        sp10[1] = temp_fv0_2 * sp10[1];
        sp10[2] = temp_fv0_2 * sp10[2];
        temp_fv0_3 = RADIAN_TO_DEGREE_F(sinfApprox(sp10[1]));
        arg2[2] = arg3;
        arg2[1] = temp_fv0_3;
        arg2[0] = RADIAN_TO_DEGREE_F(atan2Approx(-sp10[0], sp10[2]));
    }
}

const rodata_pad_4D900[] = {
    0x000F1880,
    0x00431021,
    0x02A2102B,
};

INCLUDE_ASM("asm/nonmatchings/main/4D900", fake_func_800538AC);
