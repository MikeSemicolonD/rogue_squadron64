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

extern s8 D_mission_overlay_8010B6E8;
extern f32 vec3Length(f32 *);
extern void initVec4TripletFromArgs(f32 *, f32, f32, f32);
extern void mat3x4Multiply(void *, void *, void *);
extern void addNpcToVisibilityBucket(s32, void *, void *, f32);
typedef struct {
    u8 active;
    u8 head;
    u8 count;
} CtState;
typedef struct {
    u8 pad[4];
    u8 *cam;
} CtCam;
extern CtCam D_main_bss_80138D18;

void submitCameraTrackedObjectToRender(s32 *arg0) {
    f32 m[12];
    f32 d[4];
    f32 pos[3];
    f32 f;
    s32 i;
    EffectModelInstance *pool;
    u8 *inst;
    u8 *p;
    s32 idx;
    CtState *st = (CtState *)&D_mission_overlay_8010B6E8;

    if (st->active != 0 && st->count != 0) {
        i = 0;
        do {
            idx = st->head - i;
            if (idx < 0) {
                idx += 60;
            }
            pool = D_mission_overlay_8010B6E0;
            p = (u8 *)(idx * 0xF8 + (s32)pool);
            if (p[0xF4] != 0) {
                u8 *cam;
                inst = p;
                cam = D_main_bss_80138D18.cam;
                d[0] = *(f32 *)(inst + 0) - *(f32 *)(cam + 0x10);
                d[1] = *(f32 *)(inst + 4) - *(f32 *)(cam + 0x14);
                d[2] = *(f32 *)(inst + 8) - *(f32 *)(cam + 0x18);
                f = (vec3Length(d) - 1.2f) * 6.2f;
                if (f < 1.0f) {
                    f = 1.0f;
                } else if (15.0f < f) {
                    f = 15.0f;
                }
                pos[0] = *(f32 *)(inst + 0) + *(f32 *)(inst + 0x28) * 0.165f;
                pos[1] = *(f32 *)(inst + 4) + *(f32 *)(inst + 0x2C) * 0.165f;
                pos[2] = *(f32 *)(inst + 8) + *(f32 *)(inst + 0x30) * 0.165f;
                initVec4TripletFromArgs(m, f, f, 1.0f);
                mat3x4Multiply(inst + 0x10, m, inst + 0x68);
                addNpcToVisibilityBucket(*arg0, inst + 0x40, pos, 0.33f);
            }
            i++;
        } while (i < st->count);
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ADF80", emitEffectParticlesAlongPath);

extern u8 D_mission_overlay_800A53E0[];
extern u8 D_mission_overlay_800A53F8[];
extern s32 D_main_bss_80130B50;
extern s32 D_mission_overlay_8010B738;
void *rs_malloc(u32, u16);
s32 load_hmt_and_hob(u8 *, s32, s32, s32);
u8 *getHobObjectByName(u8 *);
u8 *createMeshInstanceFromSource(u8 *, u8 *);
void applyFlagsToMeshTreeOrList(u8 *, s32, s32, s32);

void loadEffectModelInstancePool(void) {
    u8 *obj;
    u32 i;

    D_mission_overlay_8010B6E0 = rs_malloc(0x3A20, 0);
    load_hmt_and_hob(D_mission_overlay_800A53E0, 0, 0, 0);
    obj = getHobObjectByName(D_mission_overlay_800A53F8);
    for (i = 0; i < 0x3C; i++) {
        createMeshInstanceFromSource(obj, D_mission_overlay_8010B6E0[i].mesh);
    }
    if (!(D_main_bss_80130B50 & 1)) {
        applyFlagsToMeshTreeOrList(D_mission_overlay_8010B6E0->mesh, 0, 0x30000000, 0);
    }
    D_mission_overlay_8010B738 = 0;
}

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
