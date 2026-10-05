#include "common.h"

#include "main/1D000.h"
#include "main/4D900.h"
#include "player.h"

extern void *D_main_8009EB98[];
void updateEffectObjectTransformPieces(void *, s32, s32, f32, s32);
typedef struct {
    u8 unk0;
    u8 pad1[3];
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

INCLUDE_ASM("asm/nonmatchings/main/4D900", applyPlayerVehicleStateUpdate);

typedef struct { s32 b[12]; } RoBlob30;
typedef struct { s32 a, b, c; } RoV3;
extern void floatModulo(f32, f32);

void rotateObjectMatrixAboutStoredAxis(u8 *arg0, f32 dt) {
    f32 m[12];
    f32 w[4];
    f32 v[4];
    f32 pos[4];
    f32 t0, t1, t2, n0, n2;
    f32 q2[4];
    f32 q3[4];
    f32 q1[4];
    *(RoBlob30 *)m = **(RoBlob30 **)(arg0 + 0x74);
    *(RoV3 *)v = *(RoV3 *)(arg0 + 0x58);
    if (v[0] != 0.0f || v[1] != 0.0f || v[2] != 0.0f) {
        transformVec3ByMat34(m, v, w);
        m[9] = w[0];
        m[10] = w[1];
        m[11] = w[2];
    } else {
        w[0] = m[9];
        w[1] = m[10];
        w[2] = m[11];
    }
    quatFromCardinalAxis(q2, 1, *(f32 *)(arg0 + 0xD0));
    quatFromCardinalAxis(q3, 0, *(f32 *)(arg0 + 0xE0));
    quatMultiply(q2, q3, q1);
    quatToRotationMatrix(q1, m);
    *(f32 *)(arg0 + 0x94) = *(f32 *)(arg0 + 0x94) + *(f32 *)(arg0 + 0xDC) * dt;
    if (*(f32 *)(arg0 + 0x94) < 1.5f) {
        *(f32 *)(arg0 + 0x94) = 1.5f;
        *(f32 *)(arg0 + 0xDC) = 0.0f;
    }
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = *(f32 *)(arg0 + 0x94);
    rotateVec3ByMat3x3(m, v, v);
    t0 = *(f32 *)(*(u8 **)(arg0 + 0x74) + 0x24);
    n0 = v[0] + t0;
    pos[0] = t0;
    t1 = *(f32 *)(*(u8 **)(arg0 + 0x74) + 0x28);
    pos[1] = t1;
    t2 = *(f32 *)(*(u8 **)(arg0 + 0x74) + 0x2C);
    v[0] = n0;
    n2 = v[2] + t2;
    pos[2] = t2;
    v[1] += t1;
    v[2] = n2;
    *(f32 *)(arg0 + 0x4C) = v[0];
    *(f32 *)(arg0 + 0x50) = v[1];
    *(f32 *)(arg0 + 0x54) = v[2];
    *(RoV3 *)(arg0 + 0x10) = *(RoV3 *)v;
    *(f32 *)(arg0 + 0xD0) = *(f32 *)(arg0 + 0xD0) + *(f32 *)(arg0 + 0xD8) * dt;
    floatModulo(*(f32 *)(arg0 + 0xD0), 180.0f);
}

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

void destroyNpcSlotChain(u16);
void deactivateEffectObject(s32 idx) {
    u8 *obj;

    *(u16 *)D_main_bss_80138D18[idx].unk4 &= ~1;
    obj = D_main_bss_80138D18[idx].unk4;
    if (*(u16 *)(obj + 0xF4) != 0xFFFF) {
        destroyNpcSlotChain(*(u16 *)(obj + 0xF4));
        *(u16 *)(obj + 0xF4) = 0xFFFF;
    }
    updateEffectObjectTransformPieces(D_main_8009EB98[gPlayers[idx].inner.unk0B4], idx, (s32)((u8 *)&gPlayers[0].inner.posX + idx * sizeof(struct player_struct)), 0.046875f, gPlayers[idx].inner.unk178[0x14]);
}

INCLUDE_ASM("asm/nonmatchings/main/4D900", refreshEffectObjectCamerasAndState);

void dispatchEffectObjectBehavior(s32 idx, s32 kind, s32 arg2) {
    updateEffectObjectTransformPieces(D_main_8009EB98[kind], idx, arg2, 0.046875f, gPlayers[idx].inner.unk178[0x14]);
}

static inline void registerSceneNodeInline(u8 *obj, u8 *node) {
    if (D_main_bss_80138260 == 1) {
        D_main_bss_80138894->unk4 = node;
    } else {
        D_main_bss_80138D18[*(s32 *)(node + 0xC)].unk4 = node;
    }
    mat3x3InverseInto(obj + 0x2C, node + 0x28);
}

void registerSceneNodeAndInvertRotation(u8 *obj, u8 *node) {
    registerSceneNodeInline(obj, node);
}

void buildOrientationFromPosAndAngles(void *, void *, void *);
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} TransformNodeVec3;
void initTransformNodeFromVectors(u8 *node, TransformNodeVec3 *a, TransformNodeVec3 *b) {
    buildOrientationFromPosAndAngles(node + 0x28, a, b);
    *(TransformNodeVec3 *)(node + 0x10) = *a;
    *(TransformNodeVec3 *)(node + 0x1C) = *b;
}

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

extern s32 D_8010CA20;
extern u8 D_main_8009EBBC;
extern s32 D_main_8009EBC0;
extern s32 D_main_8009EC10;
extern s32 D_8010C9E0;
void requestCinematicNodeEvent(s32 idx) {
    u8 *p;

    if (D_8010CA20 == 0) {
        p = D_main_bss_80138D18[idx].unk4;
        if (!(*(u16 *)p & 0x10) || *(s32 *)(p + 8) == 3) {
            D_main_8009EBBC = 1;
            D_main_8009EC10 = D_main_8009EBC0;
            D_8010C9E0 |= 0x40;
        }
    }
}

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    s32 unk30;
    f32 unk34;
    u8 pad38[0x20];
} SceneNodeShakeState;
extern SceneNodeShakeState D_main_bss_80137D08[][2];
void resetSceneNodeShakeStateArray(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            SceneNodeShakeState *s = &D_main_bss_80137D08[i][j];

            s->unk0 = 0;
            s->unk4 = 0;
            s->unk8 = 0;
            s->unkC = 0;
            s->unk10 = 0;
            s->unk14 = 0;
            s->unk18 = 0;
            s->unk1C = 0;
            s->unk20 = 0;
            s->unk2C = 1.0f;
            s->unk28 = 1.0f;
            s->unk24 = 1.0f;
            s->unk30 = 0;
            s->unk34 = 1.0f;
        }
    }
}

void clearSceneNodeMotionFields(void) {
    s32 i;

    if (D_main_bss_80138260 == 1) {
        D_main_bss_80138894->unk8 = 0;
        D_main_bss_80138894->unk14 = 0;
        D_main_bss_80138894->unk10 = 0;
        D_main_bss_80138894->unk70 = 0;
        D_main_bss_80138894->unk6C = 0;
        D_main_bss_80138894->unk68 = 0;
        D_main_bss_80138894->unk64 = 0;
        return;
    }
    for (i = 0; i < 1; i++) {
        D_main_bss_80138D18[i].unk8 = 0;
        D_main_bss_80138D18[i].unk14 = 0;
        D_main_bss_80138D18[i].unk10 = 0;
        D_main_bss_80138D18[i].unk70 = 0;
        D_main_bss_80138D18[i].unk6C = 0;
        D_main_bss_80138D18[i].unk68 = 0;
        D_main_bss_80138D18[i].unk64 = 0;
    }
}

void destroyEffectObjectTypeNpcSlots(void);
void refreshAllSceneNodeInverseTransforms(void) {
    s32 i;

    destroyEffectObjectTypeNpcSlots();
    for (i = 0; i < 1; i++) {
        SceneNode *n = &D_main_bss_80138D18[i];

        if (n->unk0 != 0) {
            registerSceneNodeInline((u8 *)n + 8, n->unk4);
        }
    }
}

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
