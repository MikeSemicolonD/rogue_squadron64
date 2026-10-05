#include "common.h"
#include "common_types.h"

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

typedef struct { s32 b[12]; } Blob30;
extern u8 D_main_bss_80138268[][6][0xF8];
extern void destroyNpcSlotChain(u16);
extern void updatePlayerVehicleByControlMode(void *, f32);
extern void updateEffectObjectOrientationQuat(void *, void *, f32);
extern void updateAudioListenerPosFromPlayer(void);

void releaseEffectObjectNpcSlots(s32 idx, s32 view, u8 copy) {
    u8 *cur;
    u8 *nw;
    u8 *t;
    f32 dt;

    cur = D_main_bss_80138D18[idx].unk4;
    nw = D_main_bss_80138268[idx][view];
    if (cur != nw) {
        *(u16 *)cur &= ~1;
        if (*(u16 *)(cur + 2) == 4) {
            t = *(u8 **)(cur + 0xBC);
            if (*(u16 *)(t + 0xF4) != 0xFFFF) {
                destroyNpcSlotChain(*(u16 *)(t + 0xF4));
                *(u16 *)(t + 0xF4) = 0xFFFF;
            }
            *(u16 *)(*(u8 **)(cur + 0xBC)) &= ~1;
            t = *(u8 **)(cur + 0xC0);
            if (*(u16 *)(t + 0xF4) != 0xFFFF) {
                destroyNpcSlotChain(*(u16 *)(t + 0xF4));
                *(u16 *)(t + 0xF4) = 0xFFFF;
            }
            *(u16 *)(*(u8 **)(cur + 0xC0)) &= ~1;
        }
        if (*(u16 *)(cur + 0xF4) != 0xFFFF) {
            destroyNpcSlotChain(*(u16 *)(cur + 0xF4));
            *(u16 *)(cur + 0xF4) = 0xFFFF;
        }
        D_main_bss_80138D18[idx].unk4 = nw;
        *(u16 *)nw |= 1;
        if (copy) {
            *(Blob30 *)(nw + 0x28) = *(Blob30 *)(cur + 0x28);
            *(f32 *)(nw + 0x10) = *(f32 *)(nw + 0x4C);
            *(f32 *)(nw + 0x14) = *(f32 *)(nw + 0x50);
            *(f32 *)(nw + 0x18) = *(f32 *)(nw + 0x54);
        }
        *(f32 *)(nw + 0x98) = *(f32 *)(nw + 0xA0);
        *(f32 *)(nw + 0x9C) = *(f32 *)(nw + 0xA0);
        dt = 0.033333335f;
        updatePlayerVehicleByControlMode(nw, dt);
        updateEffectObjectOrientationQuat(&D_main_bss_80138D18[*(s32 *)(nw + 0xC)], nw, dt);
        updateAudioListenerPosFromPlayer();
    }
}

typedef struct { s32 b[12]; } Blob30Dup;
extern u8 D_main_bss_80138930[][4][0xF8];
extern void destroyNpcSlotChain(u16);
extern void updatePlayerVehicleByControlMode(void *, f32);
extern void updateEffectObjectOrientationQuat(void *, void *, f32);
extern void updateAudioListenerPosFromPlayer(void);

void releaseEffectObjectNpcSlotsVariant(s32 idx, s32 view, u8 copy)
{
  u8 *cur;
  u8 *nw;
  u8 *t;
  f32 dt;
  f32 a;
  u8 *new_var;
  cur = D_main_bss_80138D18[idx].unk4;
  nw = D_main_bss_80138930[idx][view];
  if (cur != nw)
  {
    *((u16 *) cur) &= ~1;
    if ((*((u16 *) (cur + 2))) == 4)
    {
      t = *((u8 **) (cur + 0xBC));
      if ((*((u16 *) (t + 0xF4))) != 0xFFFF)
      {
        destroyNpcSlotChain(*((u16 *) (t + 0xF4)));
        *((u16 *) (t + 0xF4)) = 0xFFFF;
      }
      *((u16 *) (*((u8 **) (cur + 0xBC)))) &= ~1;
      t = *((u8 **) (cur + 0xC0));
      if ((*((u16 *) (t + 0xF4))) != 0xFFFF)
      {
        destroyNpcSlotChain(*((u16 *) (t + 0xF4)));
        *((u16 *) (t + 0xF4)) = 0xFFFF;
      }
      *((u16 *) (*((u8 **) (cur + 0xC0)))) &= ~1;
    }
    new_var = cur + 0xF4;
    if ((*((u16 *) (cur + 0xF4))) != 0xFFFF)
    {
      destroyNpcSlotChain(*((u16 *) new_var));
      *((u16 *) (cur + 0xF4)) = 0xFFFF;
    }
    D_main_bss_80138D18[idx].unk4 = nw;
    *((u16 *) nw) |= 1;
    if ((!((*((u16 *) nw)) & 0x20)) && copy)
    {
      *((Blob30 *) (nw + 0x28)) = *((Blob30 *) (cur + 0x28));
      ;
      *((f32 *) (nw + 0x10)) = *((f32 *) (nw + 0x4C));
      *((f32 *) (nw + 0x14)) = *((f32 *) (nw + 0x50));
      *((f32 *) (nw + 0x18)) = *((f32 *) (nw + 0x54));
      *((f32 *) (nw + 0x98)) = *((f32 *) (nw + 0xA0));
      *((f32 *) (nw + 0x9C)) = *((f32 *) (nw + 0xA0));
    }
    dt = 0.033333335f;
    updatePlayerVehicleByControlMode(nw, dt);
    updateEffectObjectOrientationQuat(&D_main_bss_80138D18[*((s32 *) (nw + 0xC))], nw, dt);
    updateAudioListenerPosFromPlayer();
  }
}

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

#include "common_types.h"
typedef struct { s32 b[12]; } SaBlob30;
typedef struct { s32 a, b, c; } SaV3;
typedef struct {
    u16 flags;
    u8 pad2[0x6E];
    SaBlob30 *mat;
    f32 *node;
    u8 pad78[0x3E0 - 0x78];
} SaRec;
typedef struct { u8 pad[0x24]; f32 x, y, z; } SaPos;
typedef struct { u8 b[0x2A0]; } SaPlayer;
extern u8 D_main_8009EBBC;
extern SaRec D_main_bss_80138C18[];
extern SaPlayer D_main_bss_8013800C[];
extern SaPos D_main_bss_80137A80;
extern void transformVec3ByMat34(void *, f32 *, f32 *);
extern void clampVec3ToUnitIfLongerThan(f32 *);
extern void scaleVec3ByScalar(f32 *, f32, f32 *);

void submitActiveEffectObjectRender(s32 idx) {
    f32 p[3];
    f32 q[3];
    f32 r[3];
    SaRec *rec;
    if (D_main_8009EBBC == 0) {
        rec = &D_main_bss_80138C18[idx];
        if (rec->flags & 1) {
            *rec->mat = *(SaBlob30 *)&D_main_bss_8013800C[idx];
            p[0] = 0;
            p[1] = -1.0f;
            p[2] = 0.75f;
            transformVec3ByMat34(rec->mat, p, p);
            q[0] = *(f32 *)((u8 *)rec->node + 0x24);
            q[1] = *(f32 *)((u8 *)rec->node + 0x28);
            q[2] = *(f32 *)((u8 *)rec->node + 0x2C);
            p[0] = p[0] - q[0];
            p[1] = p[1] - q[1];
            p[2] = p[2] - q[2];
            *(SaV3 *)r = *(SaV3 *)p;
            r[1] = 0;
            clampVec3ToUnitIfLongerThan(r);
            scaleVec3ByScalar(r, 2.0f, r);
            r[0] = p[0] + r[0];
            r[1] = p[1] + r[1];
            r[2] = p[2] + r[2];
            p[0] = q[0] + r[0];
            p[1] = q[1] + r[1];
            p[2] = q[2] + r[2];
            D_main_bss_80137A80.x = p[0];
            D_main_bss_80137A80.z = p[2];
            p[1] = p[1] - 0.25f;
            D_main_bss_80137A80.y = p[1];
        }
    }
}

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

extern s32 gCurrentLevel;
extern void setActiveRenderListPtr(void *);
extern void setRenderStateFlagByteOne(s32);
extern void setRenderStateFlagByteTwo(s32);
extern void setRenderStateFlagByteThree(s32);
extern void setupCameraMatrices(void *);
extern void initRenderStateArrays(void);
extern void getConfigFloatPair(f32 *, f32 *);

void refreshEffectObjectCamerasAndState(void) {
    RoBlob30 save;
    SceneNode *e;
    s32 i;
    s32 *camp;
    s32 cam;
    s32 s10;
    s32 s14;
    void *p;
    f32 a;
    f32 b;

    for (i = 0; i < 1; i++) {
        e = &D_main_bss_80138D18[i];
        if (e->unk0 == 0) {
            continue;
        }
        p = NULL;
        if (gCurrentLevel == 10) {
            goto done;
        }
        if (*(s32 *)((u8 *)e + 0x74) == 0) {
            if (gCurrentLevel != 7) {
                goto done;
            }
        } else {
            p = (u8 *)e + 0x74;
        }
        setActiveRenderListPtr(p);
        p = (void *)1;
    done:
        setRenderStateFlagByteOne((s32)p);
        camp = &e->unk8;
        cam = e->unk8;
        e->unk8 = e->unk64;
        s10 = e->unk10;
        s14 = e->unk14;
        e->unk10 = e->unk14 = 0;
        setupCameraMatrices(camp);
        initRenderStateArrays();
        setRenderStateFlagByteOne(0);
        e->unk8 = e->unk68;
        e->unk10 = e->unk14 = 0;
        setupCameraMatrices(camp);
        initRenderStateArrays();
        setRenderStateFlagByteOne(0);
        e->unk8 = cam;
        setupCameraMatrices(camp);
        e->unk8 = e->unk6C;
        if (e->unk8 != 0) {
            initRenderStateArrays();
            a = *(f32 *)((u8 *)e + 0x2C);
            b = *(f32 *)((u8 *)e + 0x30);
            getConfigFloatPair((f32 *)((u8 *)e + 0x2C), (f32 *)((u8 *)e + 0x30));
            setRenderStateFlagByteOne(1);
            setRenderStateFlagByteThree(0);
            setRenderStateFlagByteTwo(1);
            setActiveRenderListPtr(NULL);
            setupCameraMatrices(camp);
            setRenderStateFlagByteThree(1);
            setRenderStateFlagByteOne(0);
            *(f32 *)((u8 *)e + 0x2C) = a;
            *(f32 *)((u8 *)e + 0x30) = b;
        }
        initRenderStateArrays();
        e->unk10 = s10;
        e->unk14 = s14;
        e->unk8 = e->unk70;
        save = *(RoBlob30 *)((u8 *)e + 0x34);
        clearVec4QuadStruct((void *)((u8 *)e + 0x34));
        setupCameraMatrices(&e->unk8);
        *(RoBlob30 *)((u8 *)e + 0x34) = save;
    }
}

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

const s32 rodata_pad_4D900[] = {
    0x000F1880,
    0x00431021,
    0x02A2102B,
};

INCLUDE_ASM("asm/nonmatchings/main/4D900", fake_func_800538AC);
