#include "common.h"
#include "common_types.h"
#include "rs_math.h"

typedef struct {
    f32 m[12];
} Tca3Mtx;
typedef struct {
    Tca3Mtx mtx;
    u8 pad30[8];
    s32 obj;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    u8 pad50[0x14];
    s16 h64;
} Tca3Npc;
u8 isPendingChildNpcActive(s32);
u8 validateActorTargetLOS(s32);
void buildRotationMatrixSlot0(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
void transformVec3ByMat34(void *, void *, void *);
extern u8 D_main_bss_80130B63;
s32 playAttachmentCueNoTexture(void *arg0);
extern void tca3InitAnim(s32, f32, f32, f32, f32, void *, s32, f32, f32, f32) __asm__("initObjectAnimSubstruct");
extern void applyToObjectSubstructByFlag(s32, f32, f32, s32);

void transformCraftAnchorsApplySubFx3(Tca3Npc *npc, f32 dt) {
    Tca3Mtx saved;
    f32 m[12];
    u8 r;
    u8 r2;

    if (isPendingChildNpcActive(npc->obj) == 1) {
        saved = npc->mtx;
        buildRotationMatrixSlot0(m, npc->f4C);
        composeRotationMatrixSlot1(m, npc->f48);
        transformVec3ByMat34(m, &saved.m[3], &npc->mtx.m[3]);
        transformVec3ByMat34(m, &saved.m[6], &npc->mtx.m[6]);
        r = validateActorTargetLOS(npc->obj);
        if (r == 1) {
            if (D_main_bss_80130B63 != 0) {
                npc->h64 = 3;
            } else {
                r2 = isPendingChildNpcActive(npc->obj);
                if (r2 == r && validateActorTargetLOS(npc->obj) == r2) {
                    {
                        union { s32 i; f32 f; } u1, u0;
                        u1.i = 0x3F800000;
                        u0.i = 0;
                        tca3InitAnim(npc->obj, u1.f, u0.f, u1.f, u0.f, playAttachmentCueNoTexture, 0, 10.0f, 15.0f, u0.f);
                    }
                    applyToObjectSubstructByFlag(npc->obj, dt, 0.0f, 0);
                }
            }
        }
        npc->mtx = saved;
    }
}

typedef struct {
    u8 pad0[0x38];
    s32 obj;
    u8 pad3C[0xC];
    f32 f48;
    f32 f4C;
    u8 pad50[0xC];
    f32 f5C;
} FsNpc;
typedef struct { s32 x, y, z; } FsV3i;
extern f32 D_mission_overlay_8010B0B0[];
u8 isPendingChildNpcActive(s32);
u8 computeActorAnchorDeltaAfterLOS(s32);
void *getObjectMeshTransformOrLocal(s32, void *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void mat3x3InverseInto(void *, void *);
void transformVec3ByMat34(void *, void *, void *);
void vec3NormalizeInto(void *, void *);
void buildRotationMatrixSlot0(void *, f32);
void buildRotationMatrixSlot1(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
f32 vec3Dot(void *, void *);
f32 vec3Length(void *);
f32 constMinusSinfApprox(f32);
void vec3Cross(void *, void *, void *);
void normalize_vector(void *);
void quatFromAxisAngle(void *, void *, f32);
void rotateVec3ByQuat(void *, void *, void *);

void tickFighterSquadronWithSplinePaths(FsNpc *npc, f32 dt) {
    f32 mtx[12];
    f32 inv[12];
    f32 dir[4];
    f32 v80[4];
    f32 meshbuf[12];
    f32 ang;
    f32 lim;
    f32 b;

    if (isPendingChildNpcActive(npc->obj) == 1 && computeActorAnchorDeltaAfterLOS(npc->obj) == 1) {
        f32 axis[4];
        f32 q[4];
        f32 cr[4];
        f32 t1[4];
        f32 t2[4];
        void *mesh;

        mesh = getObjectMeshTransformOrLocal(npc->obj, meshbuf);
        mat34CrossRowsAndCopyPos(mtx, npc, 1.0f);
        mat3x3InverseInto(inv, mtx);
        transformVec3ByMat34(inv, mesh, v80);
        vec3NormalizeInto(dir, v80);
        buildRotationMatrixSlot0(mtx, npc->f4C);
        composeRotationMatrixSlot1(mtx, npc->f48);
        transformVec3ByMat34(mtx, D_mission_overlay_8010B0B0, v80);
        ang = constMinusSinfApprox(vec3Dot(v80, dir)) * 57.29578f;
        if (0.001f < ang) {
            lim = npc->f5C * (dt * 30.0f);
            if (lim < ang) {
                ang = lim;
            }
            vec3Cross(axis, v80, dir);
            normalize_vector(axis);
            quatFromAxisAngle(q, axis, ang);
            rotateVec3ByQuat(q, v80, dir);
            axis[1] = 0.0f;
            axis[0] = dir[0];
            axis[2] = dir[2];
            ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B0B0, axis) / (vec3Length(D_mission_overlay_8010B0B0) * vec3Length(axis))) * 57.29578f;
            *(FsV3i *)t1 = *(FsV3i *)D_mission_overlay_8010B0B0;
            t1[1] = 0.0f;
            *(FsV3i *)t2 = *(FsV3i *)axis;
            t2[1] = 0.0f;
            vec3Cross(cr, t1, t2);
            if (!(0.0f <= cr[1])) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(mtx, -ang);
            transformVec3ByMat34(mtx, dir, axis);
            axis[0] = 0.0f;
            npc->f48 = ang;
            b = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B0B0, axis) / (vec3Length(D_mission_overlay_8010B0B0) * vec3Length(axis))) * 57.29578f;
            if (!(axis[1] <= 0.0f)) {
                b = -b;
            }
            npc->f4C = b;
        }
    } else {
        f32 m[12];
        f32 r[4];
        f32 v[4];
        f32 axis[4];
        f32 q[4];
        f32 cr[4];
        f32 t1[4];
        f32 t2[4];

        buildRotationMatrixSlot0(m, npc->f4C);
        composeRotationMatrixSlot1(m, npc->f48);
        transformVec3ByMat34(m, D_mission_overlay_8010B0B0, v);
        ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B0B0, v)) * 57.29578f;
        if (0.001f < ang) {
            lim = npc->f5C * (dt * 30.0f);
            if (lim < ang) {
                ang = lim;
            }
            vec3Cross(axis, v, D_mission_overlay_8010B0B0);
            normalize_vector(axis);
            quatFromAxisAngle(q, axis, ang);
            rotateVec3ByQuat(q, v, r);
            axis[1] = 0.0f;
            axis[0] = r[0];
            axis[2] = r[2];
            ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B0B0, axis) / (vec3Length(D_mission_overlay_8010B0B0) * vec3Length(axis))) * 57.29578f;
            *(FsV3i *)t1 = *(FsV3i *)D_mission_overlay_8010B0B0;
            t1[1] = 0.0f;
            *(FsV3i *)t2 = *(FsV3i *)axis;
            t2[1] = 0.0f;
            vec3Cross(cr, t1, t2);
            if (!(0.0f <= cr[1])) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(m, -ang);
            transformVec3ByMat34(m, r, axis);
            axis[0] = 0.0f;
            npc->f48 = ang;
            b = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010B0B0, axis) / (vec3Length(D_mission_overlay_8010B0B0) * vec3Length(axis))) * 57.29578f;
            if (!(axis[1] <= 0.0f)) {
                b = -b;
            }
            npc->f4C = b;
        }
    }
}

// NOTE: 21 rows left: FP temp swaps $f2/$f4 (1.0f/mesh r chain, case 6/7 rand-offset chain, abs.s dests) and move s7,s0 (extra) lands first instead of in the beqz delay slot (sched2 picks the lwc1 2.4f hazard first)
#include "common_types.h"
typedef struct { f32 x, y, z; } GtV3;
typedef struct GtItem {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 pad2[0xE];
    /* 0x10 */ GtV3 pos;
    /* 0x1C */ f32 ang[3];
    /* 0x28 */ f32 scale[3];
    /* 0x34 */ u8 pad34[0x2C];
    /* 0x60 */ s32 objBool;
    /* 0x64 */ s32 objCount;
    /* 0x68 */ s32 objMin;
    /* 0x6C */ u8 pad6C[4];
    /* 0x70 */ s32 f70;
    /* 0x74 */ s32 f74;
    /* 0x78 */ s32 f78;
    /* 0x7C */ s32 f7C;
    /* 0x80 */ s32 f80;
    /* 0x84 */ s32 f84;
    /* 0x88 */ s32 f88;
    /* 0x8C */ s32 nameOff;
    /* 0x90 */ f32 f90;
    /* 0x94 */ f32 f94;
    /* 0x98 */ f32 f98;
    /* 0x9C */ s32 f9C;
    /* 0xA0 */ s32 craft;
    /* 0xA4 */ s32 fA4;
    /* 0xA8 */ s32 fA8;
} GtItem;
typedef struct GtCtx {
    u8 pad0[0x10];
    s32 f10;
    f32 f14;
    f32 f18;
} GtCtx;
typedef struct GtObj {
    /* 0x00 */ GtV3 pos;
    /* 0x0C */ f32 dir[3];
    /* 0x18 */ u8 pad18[0xC];
    /* 0x24 */ f32 v24[3];
    /* 0x30 */ s32 mesh;
    /* 0x34 */ GtItem *item;
    /* 0x38 */ s32 actor;
    /* 0x3C */ GtCtx *ctx;
    /* 0x40 */ f32 radius;
    /* 0x44 */ f32 scale;
    /* 0x48 */ f32 f48;
    /* 0x4C */ f32 f4C;
    /* 0x50 */ u16 h50;
    /* 0x52 */ u16 h52;
    /* 0x54 */ u16 h54;
    /* 0x56 */ u16 h56;
    /* 0x58 */ f32 f58;
    /* 0x5C */ f32 f5C;
    /* 0x60 */ s16 type;
    /* 0x62 */ s16 frame;
    /* 0x64 */ s16 state;
    /* 0x66 */ u8 b66;
    /* 0x67 */ s8 away;
    /* 0x68 */ f32 f68;
} GtObj;
typedef struct GtNpc {
    u8 pad0[4];
    GtObj *obj;
    GtObj *f8;
    s32 fC;
    u8 pad10[4];
    u16 flags;
    u16 h16;
} GtNpc;
typedef struct GtSrc {
    u8 pad0[2];
    u8 kind;
} GtSrc;
typedef struct GtSpawn {
    char *name;
    GtSrc *src;
    GtV3 *pos;
    GtItem *item;
} GtSpawn;
typedef struct GtLevelItem {
    u8 pad0[2];
    u8 kind;
    u8 pad3[0xD];
    GtV3 pos;
    f32 f1C;
    u8 pad20[8];
    f32 f28;
    u8 pad2C[4];
    f32 f30;
} GtLevelItem;
typedef struct GtHit {
    u16 h0;
    u8 pad2[4];
    u16 h6;
} GtHit;
typedef struct GtMsg {
    s32 f0;
    s32 f4;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 padB;
    s32 fC;
    u8 b10;
    u8 pad11[7];
    u8 b18;
} GtMsg;

extern u16 D_main_bss_80139560[];
extern u16 D_main_bss_80139574;
extern u16 D_main_bss_80139582;
extern u16 D_main_bss_801399E8[];
extern u8 D_main_bss_80130B39;
extern u8 D_main_bss_80138058[];
extern s32 gCurrentLevel;
extern u8 gObjectiveBooleans[];
extern s32 gObjectiveCounts[];
extern u8 gtFlag[] __asm__("D_main_bss_80130B63");
u16 popNpcSlotFromTail(u16, void *);
void composeEulerRotationXYZ(void *, f32, f32, f32);
s32 walkMeshdef0List(char *);
void setPoolEntryPhase(u16, f32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
void composeRotationMatrixSlot2(void *, f32);
void addVec3At0x24(void *, f32, f32, f32);
void createAndInitObject(s32 *, s32, void *, void (*)(void *), s32);
void applyCraftAnimDetailParamsB(void *);
void *getLevelDatItemByName(char *);
void initActorAsType1(s32, void *, f32, s32, f32, f32, s32);
void initActorAsType2(s32, void *, f32, f32);
void initActorAsType3(s32, void *, f32, f32);
void setType2ActorVelocity(s32, f32, f32, f32, f32, f32);
void setType3ActorParams(s32, f32, f32, f32, f32, f32);
void updateObjectFlags110(s32, s32, s32);
s32 rand(void);
f32 vec3Length(void *);
f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
void normalize_vector(void *);
void *allocateAndInitCraftNpcContext(f32, f32, s32);
void rs_free(void *);
s32 getNpcCurrentHealth(s32);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(s32 *);
void releaseMeshAsset(s32);
void destroyNpcSlotByIndex(u16);
s16 getPoolEntryFrameIndex(u16);
void func_mission_overlay_800AA6D0(void *, f32, void *);
void dispatchEffectByActorType(s32, f32);
u8 func_mission_overlay_800EFDE0(s32, s32, s32, f32);
void *getNpcContextByIndex(u16);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void spawnNpcType0xAFromTemplate(void *, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void addNpcToVisibilityBucket(s32, s32, void *, f32);
void advanceNpcOnCurvedPath(s32, s32, void *, GtCtx *);
s32 getObjectDetailLevel(s32);
void func_mission_overlay_800EFD6C(s32);
s32 dealDamageToNpc(s32, u16);
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
void clearPendingChildNpc(s32);
void setObjectFlagBit4(void *);
void setType1ActorParams(s32, s32, u8, u8, u8, s32);
void setObjectDetailLevel(s32, s32);
void spawnSplineWalkerCraft(void *, f32, f32, s32);
void dispatchSlotAction5IfActive(void *, void *);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyObjectOwnedNpcSlot(s32);

s32 npcGroundTroopUpdate(GtNpc *npc, u16 action, void *arg) {
    GtObj *o;
    GtItem *it;
    GtLevelItem *li;
    GtSpawn *sp;
    GtMsg *msg;
    GtHit *hit;
    char *name;
    char *mn;
    f32 dt;
    f32 scale;
    f32 r;
    f32 half;
    f32 mx;
    GtV3 d;
    void *extra;
    u8 res;

    o = npc->obj;
    switch (action) {
    case 1:
    case 8:
        mn = "gt_strun";
        mn = "gt_stsht";
        it = arg;
        npc->flags |= 0x100;
        scale = 2.4f;
        extra = arg;
        if (gtFlag[0]) {
            scale = 12.0f;
        }
        if (!(npc->flags & 0x20)) {
            o->item = arg;
            o->pos.x = it->pos.x;
            o->pos.y = it->pos.y;
            o->pos.z = it->pos.z;
            name = (char *)(it->nameOff + (s32)arg);
        } else {
            sp = arg;
            it = sp->item;
            o->item = it;
            switch (sp->src->kind) {
            case 3:
            case 6:
            case 7:
                o->pos = *sp->pos;
                name = sp->name;
                break;
            default:
                name = "-";
                o->pos.x = 0.0f;
                o->pos.y = 0.0f;
                o->pos.z = 0.0f;
                break;
            }
        }
        switch (it->type) {
        case 0x3B:
            o->type = 0;
            mn = "gt_strun";
            setPoolEntryPhase(D_main_bss_801399E8[0], scale * it->f90);
            scale = scale * it->f90;
            setPoolEntryPhase(D_main_bss_801399E8[1], scale);
            break;
        case 0x3C:
            o->type = 1;
            scale = scale * it->f90;
            mn = "gt_rprun";
            setPoolEntryPhase(D_main_bss_801399E8[2], scale);
            break;
        case 0x3D:
        default:
            o->type = 2;
            scale = scale * it->f90;
            mn = "gt_civrun";
            setPoolEntryPhase(D_main_bss_801399E8[4], scale);
            break;
        case 0x50:
            o->type = 3;
            scale = scale * it->f90;
            mn = "gt_iburun";
            setPoolEntryPhase(D_main_bss_801399E8[6], scale);
            break;
        }
        o->mesh = walkMeshdef0List(mn);
        composeEulerRotationXYZ(o, it->ang[0], it->ang[1], it->ang[2]);
        o->v24[0] = o->v24[1] = o->v24[2] = 0.0f;
        {
        f32 q = 1.0f / ((f32 *)*(u8 **)o->mesh)[0x34 / 4];
        o->scale = q * it->scale[0];
        initVec4TripletFromArgs((u8 *)o->mesh + 0x28, q * it->scale[0], q * it->scale[1], q * it->scale[2]);
        }
        composeRotationMatrixSlot0((u8 *)o->mesh + 0x28, it->ang[0]);
        composeRotationMatrixSlot1((u8 *)o->mesh + 0x28, it->ang[1]);
        composeRotationMatrixSlot2((u8 *)o->mesh + 0x28, it->ang[2]);
        addVec3At0x24((u8 *)o->mesh + 0x28, o->pos.x, o->pos.y, o->pos.z);
        npc->f8 = o;
        npc->fC = o->mesh;
        o->h50 = popNpcSlotFromTail(D_main_bss_80139560[14], npc);
        o->h52 = popNpcSlotFromTail(D_main_bss_80139560[it->craft == 1 ? 0x17 : 0x16], npc);
        o->h54 = popNpcSlotFromTail(D_main_bss_80139560[it->craft == 1 ? 7 : 9], npc);
        if (it->fA4 != 0) {
            o->h56 = popNpcSlotFromTail(D_main_bss_80139560[it->craft == 1 ? 0xD : 0xC], npc);
        } else {
            o->h56 = 0xFFFF;
        }
        popNpcSlotFromTail(D_main_bss_80139582, npc);
        o->radius = *(f32 *)(*(u8 **)o->mesh + 0x44) * o->scale;
        o->f48 = 0.0f;
        o->f4C = 0.0f;
        o->frame = 0;
        o->away = 0;
        o->f68 = 0.0f;
        createAndInitObject(&o->actor, 0, npc, applyCraftAnimDetailParamsB, action == 1 ? 0 : (s32)extra);
        if (*name != '-') {
            li = getLevelDatItemByName(name);
            switch (li->kind) {
            case 3:
                initActorAsType1(o->actor, li, o->f58, o->item->f9C, o->item->f94, o->item->f98, 0);
                updateObjectFlags110(o->actor, 4, 0);
                break;
            case 7:
                initActorAsType2(o->actor, li, o->f58, 5.0f);
                setType2ActorVelocity(o->actor, 4.0f, 3.0f, 22.5f, 180.0f, 1.0f);
                if (npc->flags & 0x20) {
                    half = 64.0f;
                    { register f32 q asm("$f4") = (f32)(rand() & 0x7F) - half; o->pos.x = li->pos.x + q / (half / li->f1C); }
                    o->pos.y = li->pos.y;
                    o->pos.z = li->pos.z + ((f32)(rand() & 0x7F) - half) / (half / li->f1C);
                    d.x = o->pos.x - li->pos.x;
                    d.y = o->pos.y - li->pos.y;
                    d.z = o->pos.z - li->pos.z;
                    r = vec3Length(&d);
                    if (li->f1C < r) {
                        o->pos.x = li->pos.x + d.x * (li->f1C / r);
                        o->pos.z = li->pos.z + d.z * (li->f1C / r);
                    }
                    o->pos.y = wrapAngleToCyclicRange(o->pos.x, o->pos.z, D_main_bss_80138058, 0);
                    scale = 0.015625f;
                    o->dir[0] = ((f32)(rand() & 0x7F) - half) * scale;
                    o->dir[1] = 0.0f;
                    o->dir[2] = ((f32)(rand() & 0x7F) - half) * scale;
                    normalize_vector(o->dir);
                }
                break;
            case 6:
                initActorAsType3(o->actor, li, o->f58, 5.0f);
                setType3ActorParams(o->actor, 4.0f, 3.0f, 22.5f, 180.0f, 1.0f);
                if (npc->flags & 0x20) {
                    half = 64.0f;
                    { f32 q; FABSF(q, ((f32)(rand() & 0x7F) - half) / (half / li->f28));
                    o->pos.x = li->pos.x + q; }
                    { f32 q; FABSF(q, ((f32)(rand() & 0x7F) - half) / (half / li->f30));
                    o->pos.z = li->pos.z + q; }
                    o->pos.y = wrapAngleToCyclicRange(o->pos.x, o->pos.z, D_main_bss_80138058, 0);
                    scale = 0.015625f;
                    o->dir[0] = ((f32)(rand() & 0x7F) - half) * scale;
                    o->dir[1] = 0.0f;
                    o->dir[2] = ((f32)(rand() & 0x7F) - half) * scale;
                    normalize_vector(o->dir);
                }
                break;
            }
            updateObjectFlags110(o->actor, 4, 0);
        }
        o->ctx = allocateAndInitCraftNpcContext(o->scale, o->scale, 10);
        o->ctx->f14 = 1.0f;
        o->ctx->f10 = 0;
        o->ctx->f18 = 0.8f;
        break;
    case 2:
        if (o->ctx != NULL) {
            rs_free(o->ctx);
        }
        initActorRenderDescriptorIfUninit(o->actor, getNpcCurrentHealth(o->actor) < 1, o->item, 0, (u8 *)o->item + 0x70);
        clearPendingAndDestroyChildNpc(&o->actor);
        releaseMeshAsset(o->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg;
        if (gCurrentLevel == 0x14) {
            if ((o->item->objBool != 0 && gObjectiveBooleans[o->item->objBool - 1] == 0) || (o->item->objCount != 0 && gObjectiveCounts[o->item->objCount - 1] < o->item->objMin)) {
            kill:
                destroyNpcSlotByIndex(npc->h16);
                return 1;
            }
        }
        switch (o->state) {
        case 0:
            o->state = 1;
        case 1:
            o->frame = getPoolEntryFrameIndex(D_main_bss_801399E8[o->type * 2]);
            func_mission_overlay_800AA6D0(o, dt, (u8 *)o->item + 0x34);
            dispatchEffectByActorType(o->actor, dt);
            if (o->type == 0) {
                if (gtFlag[0]) {
                    if (o->frame < 2) {
                        break;
                    }
                    res = func_mission_overlay_800EFDE0(o->actor, o->item->fA8, 6, dt);
                } else {
                    o->f68 += dt;
                    if (!(1.0f <= o->f68)) {
                        break;
                    }
                    o->f68 -= 1.0f;
                    res = func_mission_overlay_800EFDE0(o->actor, o->item->fA8, 6, dt);
                }
                if (res) {
                    o->state = 1;
                }
                tickFighterSquadronWithSplinePaths((void *)o, dt);
                transformCraftAnchorsApplySubFx3((void *)o, dt);
            }
            break;
        case 3:
            o->frame = getPoolEntryFrameIndex(D_main_bss_801399E8[0]);
            if (o->frame == 0) {
                releaseMeshAsset(o->mesh);
                o->mesh = walkMeshdef0List("gt_stsht");
                *(s32 *)((u8 *)getNpcContextByIndex(*(u16 *)(o->actor + 0x198)) + 0xC) = o->mesh;
                mat34CrossRowsAndCopyPos((u8 *)o->mesh + 0x28, o, o->scale);
                o->state = 4;
                o->b66 = 0;
            } else {
                func_mission_overlay_800AA6D0(o, dt, (u8 *)o->item + 0x34);
                dispatchEffectByActorType(o->actor, dt);
            }
            break;
        case 4:
            o->frame = getPoolEntryFrameIndex(D_main_bss_801399E8[1]);
            if (o->frame == 0 && o->b66 == 1) {
                releaseMeshAsset(o->mesh);
                o->mesh = walkMeshdef0List("gt_strun");
                *(s32 *)((u8 *)getNpcContextByIndex(*(u16 *)(o->actor + 0x198)) + 0xC) = o->mesh;
                mat34CrossRowsAndCopyPos((u8 *)o->mesh + 0x28, o, o->scale);
                o->state = 1;
            } else if (o->frame == 4) {
                res = isPendingChildNpcActive(o->actor);
                if (res == 1 && validateActorTargetLOS(o->actor) == res) {
                    union { s32 i; f32 f; } u1, u0;
                    u1.i = 0x3F800000;
                    u0.i = 0;
                    tca3InitAnim(o->actor, u1.f, u0.f, u1.f, u0.f, playAttachmentCueNoTexture, 0, 10.0f, 15.0f, u0.f);
                    applyToObjectSubstructByFlag(o->actor, dt, 0.0f, 0);
                }
                o->b66 = 1;
            }
            break;
        case 2:
            spawnNpcType0xAFromTemplate(o, o->radius * 3.0f);
            play3DSoundEvent(0, o, o->v24, 24.0f, 0.5f, 0, 0x4E, 0x78, 0x3C);
            goto kill;
        }
        if (o->item->f88 == 0 || isNpcWithinActiveReferenceRange(o)) {
            o->away = 0;
        } else if (++o->away > 0x14) {
            goto kill;
        }
        destroyObjectOwnedNpcSlot(o->actor);
        return 1;
    case 4:
        mat34CrossRowsAndCopyPos((u8 *)o->mesh + 0x28, o, o->scale);
        addNpcToVisibilityBucket(((s32 *)arg)[0], o->mesh, o, o->radius);
        if (o->ctx != NULL) {
            advanceNpcOnCurvedPath(((s32 *)arg)[2], ((s32 *)arg)[0], o, o->ctx);
        }
        return 1;
    case 5:
        hit = arg;
        if (getNpcCurrentHealth(o->actor) > 0) {
            play3DSoundEvent(0, o, o->v24, 24.0f, 0.5f, 0, 0xC, 0x78, 0x3C);
            if (getObjectDetailLevel(o->actor) == 1 && !D_main_bss_80130B39) {
                func_mission_overlay_800EFD6C(0x1F4);
            }
            if (dealDamageToNpc(o->actor, hit->h6) <= 0) {
                o->state = 2;
                unregisterAndFreeNpcSlot(o->h50, npc);
                unregisterAndFreeNpcSlot(o->h52, npc);
                unregisterAndFreeNpcSlot(o->h54, npc);
                if (o->h56 != 0xFFFF) {
                    unregisterAndFreeNpcSlot(o->h56, npc);
                }
                popNpcSlotFromTail(D_main_bss_80139574, npc);
                datItemSetObjectiveBooleanCount(o->item->f78, o->item->f7C, o->item->f70, o->item->f74, o->item->f80, o->item->f84);
                tallyMidDetailObject(npc);
                clearPendingChildNpc(o->actor);
                setObjectFlagBit4(npc);
            }
        }
        if (hit->h0 != 0xFFFF) {
            destroyNpcSlotByIndex(hit->h0);
        }
        return 1;
    case 9:
        msg = arg;
        switch (msg->b18) {
        case 1:
            setType1ActorParams(o->actor, msg->f0, msg->b9, msg->bA, msg->b8, msg->f4);
            return 1;
        case 8:
            if (getNpcCurrentHealth(o->actor) > 0) {
                unregisterAndFreeNpcSlot(o->h52, npc);
                o->h52 = popNpcSlotFromTail(D_main_bss_80139560[((GtMsg *)arg)->f0 == 1 ? 0x17 : 0x16], npc);
                unregisterAndFreeNpcSlot(o->h54, npc);
                o->h54 = popNpcSlotFromTail(D_main_bss_80139560[((GtMsg *)arg)->f0 == 1 ? 7 : 9], npc);
                if (o->h56 != 0xFFFF) {
                    unregisterAndFreeNpcSlot(o->h56, npc);
                    if (o->item->fA4 != 0) {
                        o->h56 = popNpcSlotFromTail(D_main_bss_80139560[((GtMsg *)arg)->f0 == 1 ? 0xD : 0xC], npc);
                    }
                }
                setObjectDetailLevel(o->actor, msg->f0);
            }
            return 1;
        case 9:
            play3DSoundEvent(0, o, o->v24, 24.0f, 0.5f, 0, 0x4E, 0x78, 0x3C);
            datItemSetObjectiveBooleanCount(o->item->f78, o->item->f7C, o->item->f70, o->item->f74, o->item->f80, o->item->f84);
            spawnSplineWalkerCraft(o, o->scale, o->scale, 0xC);
            goto kill;
        }
        return 1;
    case 7:
        dispatchSlotAction5IfActive(npc, arg);
        break;
    }
    return 1;
}

typedef struct {
    f32 m[12];
} AttachMtx;

extern void resolveNpcAttachmentPos(s32, AttachMtx *, f32, f32);
extern u8 tickProgressChannel(s32, AttachMtx *, s32, f32 *);
extern void triggerCueWithSlotEffect(s32, s32, AttachMtx *, void *, s32, f32, f32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern u8 D_mission_overlay_8010B0BC[];

s32 playAttachmentCueNoTexture(void *arg0) {
    AttachMtx mtx;
    f32 progress;
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 r;

    mtx = *(AttachMtx *)npc;
    mtx.m[1] -= *(f32 *)(npc + 0x44) * 2.4f;
    resolveNpcAttachmentPos(*(s32 *)(npc + 0x38), &mtx, 10.0f, 45.0f);
    r = tickProgressChannel(*(s32 *)(npc + 0x38), &mtx, 0, &progress);
    if (r == 1) {
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 6, &mtx, D_mission_overlay_8010B0BC, r, 10.0f, progress);
        play3DSoundEvent(0, npc, npc + 0x24, 12.0f, 0.8f, 0, 0x1D, 0x6E, 0x28);
    }
    return 0;
}

#include "common_types.h"

extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern void initActorMotionParams(s32, f32, f32, f32, f32);
extern void initObjectAnimSubstruct(s32, f32, f32, f32, f32, void *, s32, f32, f32, f32);
extern s32 D_main_bss_80137CE4;

void applyCraftAnimDetailParamsB(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);

    *(s16 *)(npc + 0x64) = 0;
    *(f32 *)(npc + 0x58) = *(f32 *)(*(u8 **)(npc + 0x34) + 0x90);
    *(f32 *)(npc + 0x5C) = 10.0f;
    setNpcHealth(*(s32 *)(npc + 0x38), *(u8 **)(npc + 0x34) + 0x6C, *(u8 **)(npc + 0x34));
    setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(*(u8 **)(npc + 0x34) + 0xA0));
    if (*(s16 *)(npc + 0x60) == 0) {
        initActorMotionParams(*(s32 *)(npc + 0x38), ((f32 *)(*(u8 **)(npc + 0x34) + 0xAC))[D_main_bss_80137CE4], ((f32 *)(*(u8 **)(npc + 0x34) + 0xB0))[D_main_bss_80137CE4], ((f32 *)(*(u8 **)(npc + 0x34) + 0xB4))[D_main_bss_80137CE4], ((f32 *)(*(u8 **)(npc + 0x34) + 0xB8))[D_main_bss_80137CE4]);
        initObjectAnimSubstruct(*(s32 *)(npc + 0x38), 1.0f, 0.0f, 1.0f, 0.0f, playAttachmentCueNoTexture, 0, 10.0f, 15.0f, 0.0f);
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E7DD0", fake_func_800E8A34);
