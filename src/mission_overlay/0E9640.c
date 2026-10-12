#include "common.h"
#include "common_types.h"
#include "rs_math.h"

f32 fabsf(f32);
s32 rand(void);
typedef struct { f32 x, y, z; } RdVec3;
typedef struct {
    RdVec3 pos;
    RdVec3 v0C;
    RdVec3 v18;
    u8 pad24[0xC];
    s32 meshPart;
    u8 pad34[4];
    u8 *def;
    s16 phase;
    u8 pad3E[2];
    f32 radius;
    f32 speed;
} RdObj;
extern void transformLimbStrideAnchorsLocal(u16, RdVec3 *, s32);
extern void transformMeshPartIntoWorld(s32, RdVec3 *);
extern void spawnByteAnimDebrisDefault(void *);
extern void spawnNpcType0xAFromTemplate(void *, f32);
extern void composeRandomRotationMatrix(RdVec3 *, RdVec3 *, f32, s32, s32, s32);
extern void scaleVec3ByRandomRange(RdVec3 *, f32, f32);
extern void spawnDebris1Npc(RdVec3 *, RdVec3 *, f32, f32, f32);
extern void spawnSplineWalkerCraft(void *, f32, f32, s32);
extern void gameStateByteGatedNpcHelper(s32, RdVec3 *, s32, f32, f32, f32);

void runDestructionPhaseSequence(RdObj *obj) {
    RdVec3 v[4];
    RdVec3 limb;
    RdVec3 mesh;
    RdVec3 pos;
    RdVec3 dir;
    f32 a;
    f32 b;
    f32 c;
    s32 i;
    s32 n;

    transformLimbStrideAnchorsLocal(*(u16 *)(obj->def + 0x198), &limb, 0);
    transformMeshPartIntoWorld(obj->meshPart, &mesh);
    switch (obj->phase) {
    case 0:
        spawnByteAnimDebrisDefault(obj);
        spawnNpcType0xAFromTemplate(obj, obj->radius * 1.2f);
        n = (s16)((s16)rand() % 3) + 5;
        for (i = 0; i < n; i++) {
            composeRandomRotationMatrix(&pos, &dir, obj->radius * 0.25f, 0x46, 0, 0);
            pos.x += obj->pos.x;
            pos.y += obj->pos.y;
            pos.z += obj->pos.z;
            scaleVec3ByRandomRange(&dir, 1.0f, 2.0f);
            FABSF(a, ((f32)(rand() & 0x7F) - 64.0f) / 12.8f); a += 12.0f;
            FABSF(b, ((f32)(rand() & 0x7F) - 64.0f) / 213.33333f); b += 0.6f;
            FABSF(c, ((f32)(rand() & 0x7F) - 64.0f) / 320.0f); c += 0.2f; spawnDebris1Npc(&pos, &dir, a, b, c);
        }
        spawnSplineWalkerCraft(obj, obj->speed, obj->speed * 1.5f, 0xC);
        break;
    case 1:
        v[2] = obj->v18;
        v[1] = obj->v0C;
        v[3] = limb;
        v[0] = mesh;
        gameStateByteGatedNpcHelper(2, v, 0, 0.8f, 1.2f, 0.6f);
        spawnNpcType0xAFromTemplate(obj, obj->radius * 5.0f);
        spawnByteAnimDebrisDefault(obj);
        for (i = 0; i < 15; i++) {
            composeRandomRotationMatrix(&pos, &dir, obj->radius * 0.25f, 0x32, 0, 0);
            pos.x += obj->pos.x;
            pos.y += obj->pos.y;
            pos.z += obj->pos.z;
            scaleVec3ByRandomRange(&dir, 1.5f, 4.0f);
            FABSF(a, ((f32)(rand() & 0x7F) - 64.0f) / 12.8f); a += 12.0f;
            FABSF(b, ((f32)(rand() & 0x7F) - 64.0f) / 25.6f); b += 2.5f;
            FABSF(c, ((f32)(rand() & 0x7F) - 64.0f) / 320.0f); c += 0.2f; spawnDebris1Npc(&pos, &dir, a, b, c);
        }
        spawnSplineWalkerCraft(obj, obj->speed * 6.0f, obj->speed * 10.0f, 0xC);
        break;
    case 2:
        spawnNpcType0xAFromTemplate(obj, obj->radius * 3.0f);
        break;
    case 3:
        spawnNpcType0xAFromTemplate(obj, obj->radius * 3.0f);
        break;
    case 4:
        spawnNpcType0xAFromTemplate(obj, obj->radius * 3.0f);
        break;
    }
}

typedef struct {
    u8 pad0[0x10];
    f32 pos[3];
    f32 ang[3];
    f32 scale[3];
    u8 pad34[0x5C - 0x34];
    s32 meshName;
    u8 pad60[0x70 - 0x60];
    s32 f70;
    s32 f74;
    s32 f78;
    s32 f7C;
    s32 f80;
    s32 f84;
    s32 f88;
    u8 pad8C[2];
    u16 phase;
    s32 nameOff;
    u8 pad94[0x98 - 0x94];
    f32 f98;
    f32 f9C;
    s32 fA0;
    s32 fA4;
    f32 fA8;
    s32 craft;
    s32 fB0;
} TcItem;
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u8 pad18[2];
    u16 h1A;
} TcRec;
typedef struct {
    u8 pad0[4];
    f32 f4;
    u8 pad8[8];
    f32 f10;
    f32 f14;
    f32 f18;
} TcCtx;
typedef struct {
    f32 pos[3];
    u8 padC[0x24 - 0xC];
    f32 v24[3];
    s32 mesh;
    TcItem *item;
    s32 actor;
    s16 phase;
    s16 state;
    f32 radius;
    f32 speed;
    f32 f48;
    f32 f4C;
    f32 f50;
    TcCtx *ctx;
    u16 h58;
    u16 h5A;
    u16 h5C;
    u16 h5E;
    u8 snd[0xA4 - 0x60];
    u8 bA4;
    u8 bA5;
    s16 hA6;
} TcObj;
typedef struct {
    u8 pad0[4];
    TcObj *obj;
    TcObj *f8;
    s32 fC;
    u8 pad10[6];
    u16 h16;
} TcNpc;
typedef struct {
    u16 h0;
    u8 pad2[4];
    u16 h6;
} TcHit;
typedef struct {
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
} TcMsg;
extern u16 D_main_bss_80139560[];
extern TcRec D_mission_overlay_8010B0D0[];
s32 walkMeshdef0List(s32);
void composeEulerRotationXYZ(void *, f32, f32, f32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
void composeRotationMatrixSlot2(void *, f32);
void addVec3At0x24(void *, f32, f32, f32);
u16 popNpcSlotFromTail(u16, void *);
void createAndInitObject(s32 *, s32, void *, void (*)(void *), s32);
void *getLevelDatItemByName(u8 *);
void initActorAsType1(s32, void *, f32, s32, f32, f32, s32);
void updateObjectFlags110(s32, s32, s32);
void setType1ActorField40(s32, s32);
void play3DSoundEventVariant(void *, void *, f32 *, f32, f32, s32, s32, s32, s32, s32);
void play3DSoundEvent(s32, void *, f32 *, f32, f32, s32, s32, s32, s32);
TcCtx *allocateAndInitCraftNpcContext(f32, f32, u16);
void factor5RemoveListNode(void *);
void rs_free(void *);
s32 getNpcCurrentHealth(s32);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(s32 *);
void releaseMeshAsset(s32);
void func_mission_overlay_800AA6D0(void *, f32, void *);
void dispatchEffectByActorType(s32, f32);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
f32 sinf(f32);
void transformVec3ByMat34(f32 *, f32 *, f32 *);
void destroyNpcSlotByIndex(u16);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyObjectOwnedNpcSlot(s32);
void updateActive3DAudioSource(void *, void *, f32 *, u8);
void addNpcToVisibilityBucket(s32, s32, void *, f32);
void advanceNpcOnCurvedPath(s32, s32, void *, TcCtx *);
void extrapolateNpcPositionForCurrentMode(void *);
s32 dealDamageToNpc(s32, u16);
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
void clearPendingChildNpc(s32);
void setObjectFlagBit4(void *);
void setType1ActorParams(s32, s32, u8, u8, u8, s32);
void updateType1AnimRamp(s32, s32, s32, s32, u8);
void dispatchSlotAction5IfActive(void *, void *);
void initNpcHealthAndDetailFromChild(void *);
extern void setObjectDetailLevel(s32, s32);

s32 tickCraftWithPhasedDestruction(TcNpc *npc, u16 action, void *arg) {
    TcObj *o;
    TcItem *it;
    TcHit *hit;
    TcMsg *msg;
    TcRec *tbl;
    u8 *name;
    f32 dt;
    f32 m[12];
    f32 v[3];
    f32 out[3];

    o = npc->obj;
    switch (action) {
    case 1:
        o->item = arg;
        it = arg;
        o->mesh = walkMeshdef0List(it->meshName);
        o->phase = it->phase;
        o->pos[0] = it->pos[0];
        o->pos[1] = it->pos[1];
        o->pos[2] = it->pos[2];
        composeEulerRotationXYZ(o, it->ang[0], it->ang[1], it->ang[2]);
        o->v24[0] = o->v24[1] = o->v24[2] = 0.0f;
        o->speed = it->scale[0];
        initVec4TripletFromArgs((u8 *)o->mesh + 0x28, it->scale[0], it->scale[1], it->scale[2]);
        composeRotationMatrixSlot0((u8 *)o->mesh + 0x28, it->ang[0]);
        composeRotationMatrixSlot1((u8 *)o->mesh + 0x28, it->ang[1]);
        composeRotationMatrixSlot2((u8 *)o->mesh + 0x28, it->ang[2]);
        addVec3At0x24((u8 *)o->mesh + 0x28, o->pos[0], o->pos[1], o->pos[2]);
        o->radius = *(f32 *)(*(u8 **)o->mesh + 0x44) * o->speed;
        npc->f8 = o;
        npc->fC = o->mesh;
        o->hA6 = 0;
        o->f48 = ((f32)(rand() & 0x7F) - 64.0f) / 64.064064f;
        o->f4C = 1.0f;
        o->h58 = popNpcSlotFromTail(D_main_bss_80139560[14], npc);
        o->h5A = popNpcSlotFromTail(D_main_bss_80139560[it->craft == 1 ? 0x17 : it->craft == 0 ? 0x16 : 0x15], npc);
        o->h5C = popNpcSlotFromTail(D_main_bss_80139560[it->craft == 1 ? 7 : 9], npc);
        if (it->fB0 != 0) {
            o->h5E = popNpcSlotFromTail(D_main_bss_80139560[it->craft == 1 ? 13 : 12], npc);
        } else {
            o->h5E = 0xFFFF;
        }
        createAndInitObject(&o->actor, 0, npc, initNpcHealthAndDetailFromChild, 0);
        o->bA4 = 0;
        name = (u8 *)(it->nameOff + (s32)it);
        if (*name != '-') {
            initActorAsType1(o->actor, getLevelDatItemByName(name), o->f50, o->item->fA0, o->item->f98, o->item->f9C, 0);
            switch (o->phase) {
            case 0:
            case 1:
            case 3:
            case 4:
                updateObjectFlags110(o->actor, 0x14, 0);
                setType1ActorField40(o->actor, o->item->fA4);
                break;
            }
            switch (o->phase) {
            case 0:
                o->bA5 = 0x78;
                o->bA4 = 1;
                play3DSoundEventVariant(o->snd, o, o->v24, 9.0f, 0.6f, 0xF, 0x52, 1, 0x78, 0);
                break;
            case 1:
                o->bA5 = 0x7D;
                o->bA4 = 1;
                play3DSoundEventVariant(o->snd, o, o->v24, 18.0f, 0.8f, 0xF, 0x3D, 1, 0x7D, 0);
                break;
            case 2:
                o->bA5 = 0x78;
                o->bA4 = 1;
                play3DSoundEventVariant(o->snd, o, o->v24, 15.0f, 0.6f, 0xF, 0x6B, 1, 0x78, 0);
                break;
            case 3:
                o->bA5 = 0x7C;
                o->bA4 = 1;
                play3DSoundEventVariant(o->snd, o, o->v24, 15.0f, 0.6f, 0xF, 0x6C, 1, 0x7C, 0);
                break;
            }
        }
        tbl = D_mission_overlay_8010B0D0;
        if (tbl[o->phase].f0 != 0.0f) {
            o->ctx = allocateAndInitCraftNpcContext(tbl[o->phase].fC * o->speed, tbl[o->phase].f8 * o->speed, tbl[o->phase].h1A);
            o->ctx->f14 = tbl[o->phase].f0;
            o->ctx->f4 = tbl[o->phase].f10 * o->speed;
            o->ctx->f10 = tbl[o->phase].f4;
            o->ctx->f18 = tbl[o->phase].f14;
        } else {
            o->ctx = NULL;
        }
        break;
    case 2:
        if (o->bA4 == 1) {
            o->bA4 = 0;
            factor5RemoveListNode(o->snd);
        }
        if (o->ctx != NULL) {
            rs_free(o->ctx);
        }
        initActorRenderDescriptorIfUninit(o->actor, getNpcCurrentHealth(o->actor) < 1, o->item, 0, (u8 *)o->item + 0x70);
        clearPendingAndDestroyChildNpc(&o->actor);
        releaseMeshAsset(o->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg;
        switch (o->state) {
        case 0:
            o->state = 1;
        case 1:
            func_mission_overlay_800AA6D0(o, dt, (u8 *)o->item + 0x34);
            dispatchEffectByActorType(o->actor, dt);
            mat34CrossRowsAndCopyPos((u8 *)o->mesh + 0x28, o, o->speed);
            o->f48 += dt * o->f4C;
            if (o->f48 > 1.0f) {
                o->f48 -= 2.0f;
            }
            mat34CrossRowsAndCopyPos(m, o, 1.0f);
            m[11] = 0.0f;
            m[10] = 0.0f;
            m[9] = 0.0f;
            v[2] = 0.0f;
            v[0] = 0.0f;
            v[1] = sinf(o->f48 * 3.1415927f) * o->item->fA8 * 0.25f;
            transformVec3ByMat34(m, v, out);
            o->pos[0] += out[0];
            o->pos[1] += out[1];
            o->pos[2] += out[2];
            break;
        case 2:
            runDestructionPhaseSequence((RdObj *)o);
            switch (o->phase) {
            case 0:
                play3DSoundEvent(0, o, o->v24, 20.0f, 0.8f, 0, 0x21, 0x7F, 0x50);
                break;
            case 1:
                play3DSoundEvent(0, o, o->v24, 24.0f, 0.8f, 0, 0x23, 0x7F, 0x50);
                break;
            case 2:
                play3DSoundEvent(0, o, o->v24, 24.0f, 0.8f, 0, 0x22, 0x7F, 0x50);
                break;
            case 3:
                play3DSoundEvent(0, o, o->v24, 24.0f, 0.8f, 0, 0x21, 0x7F, 0x50);
                break;
            case 4:
                play3DSoundEvent(0, o, o->v24, 24.0f, 0.8f, 0, 0x24, 0x7F, 0x50);
                break;
            }
        kill:
            destroyNpcSlotByIndex(npc->h16);
            return 1;
        }
        if (o->item->f88 == 0 || isNpcWithinActiveReferenceRange(o)) {
            o->hA6 = 0;
        } else if (++o->hA6 > 0x14) {
            goto kill;
        }
        destroyObjectOwnedNpcSlot(o->actor);
        return 1;
    case 4:
        if (o->bA4 != 0) {
            updateActive3DAudioSource(o->snd, o, o->v24, o->bA5);
        }
        addNpcToVisibilityBucket(((s32 *)arg)[0], o->mesh, o, o->radius);
        if (o->ctx != NULL) {
            advanceNpcOnCurvedPath(((s32 *)arg)[2], ((s32 *)arg)[0], o, o->ctx);
        }
        return 1;
    case 5:
        hit = arg;
        if (getNpcCurrentHealth(o->actor) > 0) {
            extrapolateNpcPositionForCurrentMode(hit);
            switch (o->phase) {
            case 1:
                play3DSoundEvent(0, o, o->v24, 24.0f, 0.5f, 0, 0x2A, 0x7D, 0x50);
                break;
            case 3:
                play3DSoundEvent(0, o, o->v24, 12.0f, 0.5f, 0, 0x2A, 0x6E, 0x50);
                break;
            case 0:
            case 2:
            case 4:
                play3DSoundEvent(0, o, o->v24, 24.0f, 0.5f, 0, 0x2A, 0x6E, 0x50);
                break;
            }
            if (dealDamageToNpc(o->actor, hit->h6) <= 0) {
                o->state = 2;
                unregisterAndFreeNpcSlot(o->h58, npc);
                if (o->h5E != 0xFFFF) {
                    unregisterAndFreeNpcSlot(o->h5E, npc);
                }
                datItemSetObjectiveBooleanCount(o->item->f78, o->item->f7C, o->item->f70, o->item->f74, o->item->f80, o->item->f84);
                tallyMidDetailObject(npc);
                clearPendingChildNpc(o->actor);
                setObjectFlagBit4(npc);
                if (o->bA4 == 1) {
                    o->bA4 = 0;
                    factor5RemoveListNode(o->snd);
                }
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
        case 5:
            updateType1AnimRamp(o->actor, msg->f4, *(s32 *)&msg->b8, msg->fC, msg->b10);
            return 1;
        case 8:
            if (getNpcCurrentHealth(o->actor) > 0) {
                unregisterAndFreeNpcSlot(o->h5A, npc);
                o->h5A = popNpcSlotFromTail(D_main_bss_80139560[((TcMsg *)arg)->f0 == 1 ? 0x17 : 0x16], npc);
                unregisterAndFreeNpcSlot(o->h5C, npc);
                o->h5C = popNpcSlotFromTail(D_main_bss_80139560[((TcMsg *)arg)->f0 == 1 ? 7 : 9], npc);
                if (o->h5E != 0xFFFF) {
                    unregisterAndFreeNpcSlot(o->h5E, npc);
                    if (o->item->fB0 != 0) {
                        o->h5E = popNpcSlotFromTail(D_main_bss_80139560[((TcMsg *)arg)->f0 == 1 ? 13 : 12], npc);
                    }
                }
                setObjectDetailLevel(o->actor, msg->f0);
            }
            return 1;
        }
        break;
    case 7:
        dispatchSlotAction5IfActive(npc, arg);
        break;
    }
    return 1;
}

extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);

void initNpcHealthAndDetailFromChild(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 *def = *(u8 **)(npc + 0x34);

    *(s16 *)(npc + 0x3E) = 0;
    *(f32 *)(npc + 0x50) = *(f32 *)(def + 0x94);
    setNpcHealth(*(s32 *)(npc + 0x38), *(u8 **)(npc + 0x34) + 0x6C, *(u8 **)(npc + 0x34));
    setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(*(u8 **)(npc + 0x34) + 0xAC));
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E9640", fake_func_800E9AD8);

__asm__(".section .rodata\n.word 0x14610004\n.section .text");
