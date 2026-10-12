#include "common.h"
#include "common_types.h"
#include "rs_math.h"

struct TcObj { u8 pad0[0x30]; s32 f30; u8 *f34; s32 f38; u8 pad3C[0x20]; s16 f5C; s16 f5E; u8 pad60[0x65]; u8 fC5; };
typedef struct { u8 pad0[4]; struct TcObj *obj; } TcActor;
extern s32 D_main_bss_80137CE4;
s32 npcTickEffectChannelA();
s32 npcTickEffectChannelB();
s32 npcTickEffectChannelWithSlotDispatch();
void setNpcHealth(s32, u8 *, u8 *);
void setObjectDetailLevel(s32, s32);
void initActorMotionParams(s32, f32, f32, f32, f32);
void initObjectAnimSubstruct(s32, f32, f32, f32, f32, s32 (*)(), s32, f32, f32, s32);

void npcInitWithMotionParams(TcActor *arg0) {
    struct TcObj *o = arg0->obj;
    u8 *e = o->f34;
    u8 *t;

    o->f5E = 0;
    o->f5C = 0;
    setNpcHealth(o->f38, e + 0x6C, e);
    setObjectDetailLevel(o->f38, *(s32 *)(o->f34 + 0xBC));
    switch (o->fC5) {
    case 0:
        t = (u8 *)(D_main_bss_80137CE4 * 4) + (s32)e;
        initActorMotionParams(o->f38, *(f32 *)(t + 0xC8), *(f32 *)(t + 0xCC), *(f32 *)(t + 0xC8), *(f32 *)(t + 0xCC));
        initObjectAnimSubstruct(o->f38, *(f32 *)(e + 0xD0), *(f32 *)(e + 0xD4), *(f32 *)(e + 0xD8), *(f32 *)(e + 0xDC), npcTickEffectChannelA, 0, 10.0f, 15.0f, 0);
        break;
    case 1:
        t = (u8 *)(D_main_bss_80137CE4 * 4) + (s32)e;
        initActorMotionParams(o->f38, *(f32 *)(t + 0xC8), *(f32 *)(t + 0xCC), *(f32 *)(t + 0xC8), *(f32 *)(t + 0xCC));
        initObjectAnimSubstruct(o->f38, *(f32 *)(e + 0xD0), *(f32 *)(e + 0xD4), *(f32 *)(e + 0xD8), *(f32 *)(e + 0xDC), npcTickEffectChannelB, 0, 10.0f, 15.0f, 0);
        break;
    case 2:
        t = (u8 *)(D_main_bss_80137CE4 * 4) + (s32)e;
        initActorMotionParams(o->f38, *(f32 *)(t + 0xCC), *(f32 *)(t + 0xD0), *(f32 *)(t + 0xCC), *(f32 *)(t + 0xD0));
        initObjectAnimSubstruct(o->f38, *(f32 *)(e + 0xD4), *(f32 *)(e + 0xD8), *(f32 *)(e + 0xDC), *(f32 *)(e + 0xE0), npcTickEffectChannelB, 0, 10.0f, 15.0f, 0);
        initObjectAnimSubstruct(o->f38, *(f32 *)(e + 0xF0), *(f32 *)(e + 0xF4), *(f32 *)(e + 0xF8), *(f32 *)(e + 0xFC), npcTickEffectChannelWithSlotDispatch, 1, 5.0f, 50.0f, 0);
        break;
    }
}

struct TaObj { u8 pad0[0x24]; u8 pos[0xC]; s32 f30; u8 *f34; s32 f38; u8 pad3C[0x20]; s16 f5C; u8 pad5E[2]; f32 f60; };
typedef struct { u8 pad0[4]; struct TaObj *obj; } TaActor;
extern u8 D_mission_overlay_8010A850[];
extern s32 D_main_bss_80137CE4;
s32 lookupHmtTextureByName(s32, char *, s32, u8 *, s32, s32);
s32 setObjectSubstructF10IfReady(s32, f32, s32);
s32 resolveNpcAttachmentPos(s32, u8 *, f32, f32);
s32 tickProgressChannel(s32, u8 *, s32, f32 *);
s32 triggerCueWithSlotEffect(s32, s32, u8 *, u8 *, s32, f32, f32);
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 npcTickEffectChannelA(TaActor *arg0, s32 arg1) {
    u8 buf[0x30];
    f32 sp58;
    struct TaObj *o = arg0->obj;
    f32 fv;
    s32 r;

    if (o->f60 < 90.0f) {
        return 0;
    }
    if (o->f5C == 0) {
        if (arg1 == 0) {
            lookupHmtTextureByName(o->f30, "a_c", 0, buf, 0, 0);
            setObjectSubstructF10IfReady(o->f38, 0.16666667f, 0);
        } else {
            lookupHmtTextureByName(o->f30, "a_c", 1, buf, 0, 0);
            o->f5C ^= 1;
        }
    } else {
        if (arg1 == 0) {
            lookupHmtTextureByName(o->f30, "b_d", 0, buf, 0, 0);
            setObjectSubstructF10IfReady(o->f38, 0.16666667f, 0);
        } else {
            lookupHmtTextureByName(o->f30, "b_d", 1, buf, 0, 0);
            o->f5C ^= 1;
        }
    }
    fv = *(f32 *)(o->f34 + D_main_bss_80137CE4 * 4 + 0xE0);
    if (fv != 0.0f) {
        resolveNpcAttachmentPos(o->f38, buf, 10.0f, fv);
    }
    r = tickProgressChannel(o->f38, buf, 0, &sp58) & 0xFF;
    if (r != 1) {
        return 0;
    }
    triggerCueWithSlotEffect(o->f38, 2, buf, D_mission_overlay_8010A850, r, 10.0f, sp58);
    play3DSoundEvent(0, o, o->pos, 18.0f, 0.3f, 0, 0x48, 0x6E, 0x28);
    return 0;
}

struct TbObj { u8 pad0[0x24]; u8 pos[0xC]; s32 f30; u8 *f34; s32 f38; u8 pad3C[0x20]; s16 f5C; u8 pad5E[2]; f32 f60; u8 pad64[0x61]; u8 fC5; };
typedef struct { u8 pad0[4]; struct TbObj *obj; } TbActor;
extern u8 D_mission_overlay_8010A85C[];
extern s32 D_main_bss_80137CE4;
s32 lookupHmtTextureByName(s32, char *, s32, u8 *, s32, s32);
s32 setObjectSubstructF10IfReady(s32, f32, s32);
s32 resolveNpcAttachmentPos(s32, u8 *, f32, f32);
s32 tickProgressChannel(s32, u8 *, s32, f32 *);
s32 triggerCueWithSlotEffect(s32, s32, u8 *, u8 *, s32, f32, f32);
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 npcTickEffectChannelB(TbActor *arg0, s32 arg1) {
    u8 buf[0x30];
    f32 sp58;
    struct TbObj *o = arg0->obj;
    f32 fv;
    s32 r;

    if (o->f60 < 70.0f) {
        return 0;
    }
    if (o->f5C == 0) {
        if (arg1 == 0) {
            lookupHmtTextureByName(o->f30, "a_b", 0, buf, 0, 0);
            setObjectSubstructF10IfReady(o->f38, 0.16666667f, 0);
        } else {
            lookupHmtTextureByName(o->f30, "a_b", 1, buf, 0, 0);
            o->f5C ^= 1;
        }
    } else {
        if (arg1 == 0) {
            lookupHmtTextureByName(o->f30, "c_d", 0, buf, 0, 0);
            setObjectSubstructF10IfReady(o->f38, 0.16666667f, 0);
        } else {
            lookupHmtTextureByName(o->f30, "c_d", 1, buf, 0, 0);
            o->f5C ^= 1;
        }
    }
    if (o->fC5 == 1) {
        fv = *(f32 *)(o->f34 + D_main_bss_80137CE4 * 4 + 0xE0);
    } else {
        fv = *(f32 *)(o->f34 + D_main_bss_80137CE4 * 4 + 0x100);
    }
    if (fv != 0.0f) {
        resolveNpcAttachmentPos(o->f38, buf, 10.0f, fv);
    }
    r = tickProgressChannel(o->f38, buf, 0, &sp58) & 0xFF;
    if (r != 1) {
        return 0;
    }
    triggerCueWithSlotEffect(o->f38, 2, buf, D_mission_overlay_8010A85C, r, 10.0f, sp58);
    play3DSoundEvent(0, o, o->pos, 18.0f, 0.3f, 0, 0x48, 0x6E, 0x28);
    return 0;
}

struct TsObj { u8 pad0[0x24]; u8 pos[0xC]; s32 f30; u8 *f34; s32 f38; u8 pad3C[0x20]; f32 f5C_pad; };
struct TsObj2 { u8 pad0[0x24]; u8 pos[0xC]; s32 f30; u8 *f34; s32 f38; u8 pad3C[0x20]; s16 f5C; u8 pad5E[2]; f32 f60; };
typedef struct { u8 pad0[4]; struct TsObj2 *obj; } TsActor;
typedef struct { s16 a; s16 b; f32 x; f32 y; f32 z; f32 w; u8 flag; u8 pad[0xB]; } TsEvent;
extern s32 D_main_bss_80137CE4;
extern u8 D_mission_overlay_8010A868[];
s32 lookupHmtTextureByName(s32, char *, s32, u8 *, s32, s32);
s32 resolveNpcAttachmentPos(s32, u8 *, f32, f32);
s32 tickProgressChannel(s32, u8 *, s32, f32 *);
s32 triggerCueWithSlotEffect(s32, s32, u8 *, u8 *, s32, f32, f32);
s16 getObjectNpcTypeId(s32);
s32 slotDispatcherIter(s32, s32, TsEvent *);
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 npcTickEffectChannelWithSlotDispatch(TsActor *arg0) {
    u8 buf[0x30];
    TsEvent ev;
    f32 sp78;
    struct TsObj2 *o = arg0->obj;
    f32 fv;
    s32 r;
    s32 cue;

    if (o->f60 < 70.0f) {
        return 0;
    }
    lookupHmtTextureByName(o->f30, "scnd", o->f5C, buf, 0, 0);
    o->f5C ^= 1;
    fv = *(f32 *)(o->f34 + D_main_bss_80137CE4 * 4 + 0x100);
    if (fv != 0.0f) {
        resolveNpcAttachmentPos(o->f38, buf, 5.0f, fv);
    }
    r = tickProgressChannel(o->f38, buf, 1, &sp78) & 0xFF;
    if (r != 1) {
        return 0;
    }
    cue = triggerCueWithSlotEffect(o->f38, 0xB, buf, D_mission_overlay_8010A868, 0, 5.0f, sp78);
    ev.a = 0;
    ev.x = 0.0f;
    ev.y = 0.0f;
    ev.z = 0.0f;
    ev.flag = r;
    ev.w = -1.0f;
    ev.b = getObjectNpcTypeId(o->f38);
    slotDispatcherIter(cue & 0xFFFF, 0xA, &ev);
    play3DSoundEvent(0, o, o->pos, 18.0f, 0.3f, 0, 0x30, 0x78, 0x50);
    return 0;
}

extern s32 rand();
extern void spawnNpcType0xAFromTemplate(void *, f32);
extern void zmemcpy(void *, void *, s32);
extern void gameStateByteGatedNpcHelper(s32, void *, s32, f32, f32, f32);
extern void spawnDestructionEffectBurst(void *, u16, f32, f32, f32, f32);
extern void composeRandomRotationMatrix(f32 *, f32 *, f32, s32, s32, s32);
extern void scaleVec3ByRandomRange(f32 *, f32, f32);
extern void spawnDebris1Npc(f32 *, f32 *, f32, f32, f32);
extern void spawnDestructionDebris(u16, void *, f32, f32, f32);
extern void spawnDirectionalDebrisBurst(void *, u16, f32, f32, s32, f32);
extern f32 vec3Length(void *);
extern void normalize_vector(void *);

void npcShuttleHandleDestruction(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  f32 sp18[4];
  f32 sp28[3];
  f32 sp38[12];
  f32 fs0;
  f32 fs1;
  f32 v;
  s32 t;
  s32 n;
  s32 i;
  s32 r;
  r = (arg3 == 0xC) * 2; t = r;
  switch (r)
  {
  case 0:
      spawnNpcType0xAFromTemplate(arg0, (*((f32 *) (arg0 + 0x4C))) * 4.0f);
      *((s16 *) (arg0 + 0x5E)) = 4;
      zmemcpy(sp38, arg0, 0x30);
      if (arg0[0xC5] == 0)
      {
        sp38[9] = *((f32 *) (arg0 + 0x4C));
        sp38[10] = *((f32 *) (arg0 + 0x4C));
        sp38[11] = *((f32 *) (arg0 + 0x4C));
      }
      else
      {
        sp38[9] = (*((f32 *) (arg0 + 0x4C))) * 0.6f;
        sp38[10] = (*((f32 *) (arg0 + 0x4C))) * 0.6f;
        sp38[11] = (*((f32 *) (arg0 + 0x4C))) * 0.6f;
      }
      v = *((f32 *) (arg0 + 0x4C));
      gameStateByteGatedNpcHelper(2, sp38, 0, v * 0.8f, v * 1.2f, 0.5f);
      spawnDestructionEffectBurst(arg0, 0xFFFF, 1.0f, 0.7f, 1.2f, 0.5f);
      n = ((s16) (((s16) rand()) % 5)) + 5;
      for (i = 0; i < n; i++)
      {
          composeRandomRotationMatrix(sp28, sp18, (*((f32 *) (arg0 + 0x4C))) * 0.5f, 0x87, 0, 0);
          sp28[0] += *((f32 *) (arg0 + 0));
          sp28[1] += *((f32 *) (arg0 + 4));
          sp28[2] += *((f32 *) (arg0 + 8));
          scaleVec3ByRandomRange(sp18, 3.0f, 4.0f);
          fs1 = FABSF_VAL(((((f32) (rand() & 0x7F)) - 64.0f) * 0.03125f) * 5.0f);
          fs1 = fs1 + 40.0f;
          fs0 = FABSF_VAL((((f32) (rand() & 0x7F)) - 64.0f) * 0.0078125f) + 1.0f;
          spawnDebris1Npc(sp28, sp18, fs1, fs0, FABSF_VAL((((f32) (rand() & 0x7F)) - 64.0f) / 213.33333f) + 0.3f);
      }
    break;
  case 1:
    *((s16 *) (arg0 + 0x5E)) = 2;
    r = 0;
    switch ((s16) rand() % 3)
    {
      case 0:
        spawnDestructionEffectBurst(arg0, *((u16 *) ((*((u8 **) (arg0 + 0x38))) + 0x198)), 2.0f, 0.7f, 1.2f, 1.5f);
        break;

      case 1:
        spawnDestructionDebris(*((u16 *) ((*((u8 **) (arg0 + 0x38))) + 0x198)), arg0, 0.6f, 20.0f, 3.0f);
        break;

      case 2:
        spawnDirectionalDebrisBurst(arg0, *((u16 *) ((*((u8 **) (arg0 + 0x38))) + 0x198)), 1.0f, 0.5f, 0, 5.0f);
        break;

    }
    r = 0;

        break;
  case 2:
  default:
    *((s16 *) (arg0 + 0x5E)) = 2;
  }
  do
  {
    *((f32 *) (arg0 + 0x70)) = (((f32) (rand() & 0x7F)) - 64.0f) * 0.015625f;
    *((f32 *) (arg0 + 0x74)) = (((f32) (rand() & 0x7F)) - 64.0f) * 0.015625f;
    *((f32 *) (arg0 + 0x78)) = (((f32) (rand() & 0x7F)) - 64.0f) * 0.015625f;
  }
  while (vec3Length(arg0 + 0x70) == 0.0f);
  normalize_vector(arg0 + 0x70);
  *((f32 *) (arg0 + 0x7C)) = FABSF_VAL((((f32) (rand() & 0x7F)) - 64.0f) * 0.0625f) + 4.0f;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D38A0", D_mission_overlay_800A747C);

typedef struct { f32 x, y, z; } ShVec3;
typedef struct {
    ShVec3 pos;
    ShVec3 fwd;
    ShVec3 up;
    ShVec3 vel;
    u8 *mesh;
    u8 *rec;
    s32 obj;
    u8 *node0;
    u8 *node1;
    u8 *mat0;
    u8 *mat1;
    f32 radius;
    f32 scale;
    u16 slot54;
    u16 slot56;
    u16 slot58;
    u16 slot5A;
    s16 s5C;
    s16 mode;
    f32 f60;
    f32 f64;
    f32 f68;
    s32 outCount;
    f32 axis[3];
    f32 f7C;
    u8 audio[0x44];
    u8 audioOn;
    u8 type;
    u8 padC6[2];
    u8 datC8;
} ShObj;
typedef struct { u16 a; u16 b; u16 c; u16 d; s32 e; } ShEvent;
extern char D_mission_overlay_800A747C[];
extern s32 D_mission_overlay_8010A874[];
extern u16 D_main_bss_80139560[];
extern u16 D_main_bss_80139574;
extern u8 D_main_bss_80130B39;
extern u8 D_main_bss_80138058[];
s16 rand_npcs(void) __asm__("rand");
f32 cosf(f32);
u8 *walkMeshdef0List(char *);
void composeEulerRotationXYZ(void *, s32, s32, s32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, s32);
void composeRotationMatrixSlot1(void *, s32);
void composeRotationMatrixSlot2(void *, f32);
void addVec3At0x24(void *, f32, f32, f32);
u16 popNpcSlotFromTail(u16, void *);
u8 *lookupHmtMaterialByName(void *, char *, void *);
void createAndInitObject(void *, s32, void *, void *, void *);
s32 getLevelDatItemByName(char *);
void initActorAsType1(s32, s32, s32, s32, f32, f32, f32);
void initActorAsType4(s32, char *, f32, s32, s32);
void resetType1FxFields(s32);
void updateObjectFlags110(s32, s32, s32);
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
void dispatchDatSubtypeByRandomIndex(void *, void *);
void factor5RemoveListNode(void *);
void walkDatTreeAndCollectSubtypes(void *, void *);
s32 getNpcCurrentHealth(s32);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void releaseMeshAsset(void *);
void func_mission_overlay_800AA6D0(void *, f32, void *);
void dispatchEffectByActorType(s32, f32);
s32 func_mission_overlay_800EFDE0(s32, s32, s32, f32);
u8 validateActorTargetLOS(s32);
u8 evaluateTargetTrackingVisibility(s32, s32, s32);
void applyToObjectSubstructByFlag(s32, f32, f32, s32);
u8 spawnNpcAnchoredEffectSlot(s32, f32, s32);
f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
void quatFromAxisAngle(void *, void *, f32);
void rotateVec3ByQuat(void *, void *, void *);
void composeRandomRotationMatrix_npcs(void *, void *, f32, s32, s32, s32) __asm__("composeRandomRotationMatrix");
void scaleVec3ByRandomRange_npcs(void *, f32, f32) __asm__("scaleVec3ByRandomRange");
void spawnDebris1Npc_npcs(void *, void *, f32, f32, f32) __asm__("spawnDebris1Npc");
void spawnDestructionEffectBurst_npcs(void *, s32, f32, f32, f32, f32) __asm__("spawnDestructionEffectBurst");
void spawnOrientedEffectIfBudgetOk(void *, s32, s32, f32, f32);
void zmemcpy(void *, void *, s32);
void gameStateByteGatedNpcHelper(s32, void *, s32, f32, f32, f32);
void spawnNpcType0xAFromTemplate(void *, f32);
void destroyNpcSlotByIndex(u16);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyObjectOwnedNpcSlot(s32);
void walkDatTreeAndScaleLeafByFloat(void *, void *, s32);
void clearVec4QuadStruct(void *);
void applyScaleToMat3x4(void *, f32, f32, f32);
void composeQuatToMat3x4(void *, void *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
void walkDatTreeAndVisitChildren(void *, void *, void *);
void updateActive3DAudioSource(void *, void *, void *, s32);
f32 *getNpcContextField8(u16);
f32 vec3Length(void *);
void syncType1ActorFrameToAnchorIfZeroGate(s32, void *);
void vec3ExtrapolateFirstOrder(void *, s32, void *, f32);
void distanceAndDopplerNpcHelper(void *, f32, f32);
void spawnRandomScaleColoredEffectAltVariant(void *, f32);
s32 getObjectDetailLevel(s32);
void func_mission_overlay_800EFD6C(s32);
s32 dealDamageToNpc(s32, u16);
void nsuDestroy(void *, u16, u16, u16) __asm__("npcShuttleHandleDestruction");
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
void setObjectFlagBit4(void *);
void setType1ActorParams(s32, s32, u8, u8, u8, s32);
f32 getActorCurrentValueByType(s32);
void dispatchSlotAction5IfActive(void *, void *);

static __inline__ void shRot(ShVec3 *t, void *b) { rotateVec3ByQuat((f32 *)((u8 *)t - 16), b, t); }
s32 npcShuttleUpdate(u8 *arg0, u16 action, u8 *arg2) {
    ShObj *s1 = *(ShObj **)(arg0 + 4);
    f32 q[4];
    ShVec3 v;
    s32 pad;
    f32 m[12];
    u8 *rec;
    u8 *msg;
    char *name;
    u8 type;
    s32 act;
    f32 dt;

    switch ((u16)action) {
    case 1:
    case 8:
        rec = arg2;
        type = 0;
        msg = arg2;
        if (!(*(u16 *)(arg0 + 0x14) & 0x20)) {
            s1->rec = arg2;
            s1->pos.x = *(f32 *)(arg2 + 0x10);
            s1->pos.y = *(f32 *)(arg2 + 0x14);
            s1->pos.z = *(f32 *)(arg2 + 0x18);
            name = (char *)(*(s32 *)(arg2 + 0x8C) + (s32)arg2);
        } else {
            rec = *(u8 **)(arg2 + 0xC);
            s1->rec = rec;
            if (*(u8 *)(*(u8 **)(arg2 + 4) + 2) == 3) {
                s1->pos = **(ShVec3 **)(arg2 + 8);
                name = *(char **)arg2;
            } else {
                name = D_mission_overlay_800A747C;
                s1->pos.x = 0.0f;
                s1->pos.y = 0.0f;
                s1->pos.z = 0.0f;
            }
        }
        switch (*(u16 *)rec) {
        case 0x24:
            type = 0;
            s1->mesh = walkMeshdef0List("imp_shuttle");
            break;
        case 0x2C:
            type = 1;
            s1->mesh = walkMeshdef0List("v_hls_hi");
            break;
        case 0x48:
            type = 2;
            s1->mesh = walkMeshdef0List("mshuttle");
            break;
        case 0x4D:
            type = 3;
            s1->mesh = walkMeshdef0List("raptor");
            break;
        }
        *(u16 *)(s1->mesh + 8) |= 0x40;
        *(s32 **)(s1->mesh + 4) = D_mission_overlay_8010A874;
        s1->type = type;
        composeEulerRotationXYZ(s1, *(s32 *)(rec + 0x1C), *(s32 *)(rec + 0x20), *(s32 *)(rec + 0x24));
        s1->vel.x = s1->vel.y = s1->vel.z = 0.0001f;
        {
            f32 inv = 1.0f / *(f32 *)(*(u8 **)s1->mesh + 0x34);
            s1->scale = inv * *(f32 *)(rec + 0x28);
            initVec4TripletFromArgs(s1->mesh + 0x28, inv * *(f32 *)(rec + 0x28), inv * *(f32 *)(rec + 0x2C), inv * *(f32 *)(rec + 0x30));
        }
        composeRotationMatrixSlot0(s1->mesh + 0x28, *(s32 *)(rec + 0x1C));
        composeRotationMatrixSlot1(s1->mesh + 0x28, *(s32 *)(rec + 0x20));
        composeRotationMatrixSlot2(s1->mesh + 0x28, *(f32 *)(rec + 0x24));
        addVec3At0x24(s1->mesh + 0x28, s1->pos.x, s1->pos.y, s1->pos.z);
        if (s1->type != 3) {
            s1->node0 = lookupHmtMaterialByName(s1->mesh, "wngrot_a", &s1->mat0);
            s1->node1 = lookupHmtMaterialByName(s1->mesh, "wngrot_b", &s1->mat1);
        }
        *(ShObj **)(arg0 + 8) = s1;
        *(u8 **)(arg0 + 0xC) = s1->mesh;
        {
            u8 *b = (u8 *)D_main_bss_80139560;
            s32 o;
            s1->slot54 = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
            o = 0x30;
            if (*(s32 *)(rec + 0xBC) == 1) {
                o = 0x32;
            }
            s1->slot56 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            o = 0;
            if (*(s32 *)(rec + 0xBC) == 1) {
                o = 0xA;
            }
            s1->slot58 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            if (*(s32 *)(rec + 0xC0) != 0) {
                s32 o2 = 0x18;
                if (*(s32 *)(rec + 0xBC) == 1) {
                    o2 = 0x1A;
                }
                s1->slot5A = popNpcSlotFromTail(*(u16 *)(o2 + b), arg0);
            } else {
                s1->slot5A = 0xFFFF;
            }
        }
        s1->radius = *(f32 *)(*(u8 **)s1->mesh + 0x44) * *(f32 *)(s1->rec + 0x28);
        createAndInitObject(&s1->obj, 0, arg0, npcInitWithMotionParams, (u16)action == 1 ? NULL : msg);
        if (*name == '+') {
            u16 f;
            u16 g;
            u8 *r = s1->rec;
            initActorAsType4(s1->obj, name + 1, *(f32 *)(r + 0x90), *(s32 *)(r + 0xAC), *(s32 *)(r + 0xA8));
            r = s1->rec;
            f = (*(s32 *)(r + 0xA0) != 0) << 6;
            if (*(s32 *)(r + 0xA4) != 0) {
                f |= 0x80;
            }
            g = f;
            updateObjectFlags110(s1->obj, g, g ^ 0xFFFF);
        } else if (*name != '-') {
            s32 item = getLevelDatItemByName(name);
            u8 *r = s1->rec;
            s32 f;
            initActorAsType1(s1->obj, item, *(s32 *)(r + 0x90), *(s32 *)(r + 0x9C), *(f32 *)(r + 0x94), *(f32 *)(s1->rec + 0x98), 0.5f);
            s1->mode = 1;
            f = 2;
            if (*(s32 *)(s1->rec + 0xB8) != 0) {
                f = 0xA;
            }
            updateObjectFlags110(s1->obj, f, 0);
            if (*(s32 *)(rec + 0xB4) != 0) {
                resetType1FxFields(s1->obj);
            }
        }
        s1->outCount = 0;
        if (*(s32 *)(rec + 0xB0) == 0) {
            s1->f60 = 0.0f;
            s1->f64 = 0.0f;
        } else {
            s1->f60 = 110.0f;
            __asm__("");
            s1->f64 = 1.0f;
        }
        s1->f68 = 0.0f;
        if (s1->type != 3) {
            s1->audioOn = 1;
            play3DSoundEventVariant(s1->audio, s1, &s1->vel, 14.0f, 0.4f, 0xF, 0x39, 1, 0x78, 0x28);
        } else {
            s1->audioOn = 1;
            play3DSoundEventVariant(s1->audio, s1, &s1->vel, 18.0f, 0.6f, 0xF, 0x53, 1, 0x7F, 0x28);
        }
        __asm__("" :: "r"(type));
        dispatchDatSubtypeByRandomIndex(&s1->datC8, s1->mesh);
        return 1;
    case 2:
        if (s1->audioOn == 1) {
            factor5RemoveListNode(s1->audio);
        }
        initActorRenderDescriptorIfUninit(s1->obj, getNpcCurrentHealth(s1->obj) < 1, s1->rec, 0, s1->rec + 0x70);
        clearPendingAndDestroyChildNpc(&s1->obj);
        walkDatTreeAndCollectSubtypes(&s1->datC8, s1->mesh);
        releaseMeshAsset(s1->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        func_mission_overlay_800AA6D0(s1, dt, s1->rec + 0x34);
        switch (s1->mode) {
        case 0:
            if (s1->f68 > 0.0f) {
                s1->f64 += s1->f68 * dt;
                if (s1->f64 > 1.0f) {
                    s1->f64 = 1.0f;
                    s1->f68 = 0.0f;
                }
                s1->f60 = (1.0f - (cosf(s1->f64 * 3.1415927f) + 1.0f) * 0.5f) * 110.0f;
            } else if (s1->f68 < 0.0f) {
                s1->f64 += s1->f68 * dt;
                if (s1->f64 < 0.0f) {
                    s1->f64 = 0.0f;
                    s1->f68 = 0.0f;
                }
                s1->f60 = (1.0f - (cosf(s1->f64 * 3.1415927f) + 1.0f) * 0.5f) * 110.0f;
            }
            break;
        case 1:
            dispatchEffectByActorType(s1->obj, dt);
            if (s1->f68 > 0.0f) {
                s1->f64 += s1->f68 * dt;
                if (s1->f64 > 1.0f) {
                    s1->f64 = 1.0f;
                    s1->f68 = 0.0f;
                }
                s1->f60 = (1.0f - (cosf(s1->f64 * 3.1415927f) + 1.0f) * 0.5f) * 110.0f;
            } else if (s1->f68 < 0.0f) {
                s1->f64 += s1->f68 * dt;
                if (s1->f64 < 0.0f) {
                    s1->f64 = 0.0f;
                    s1->f68 = 0.0f;
                }
                s1->f60 = (1.0f - (cosf(s1->f64 * 3.1415927f) + 1.0f) * 0.5f) * 110.0f;
            }
            switch (s1->type) {
            case 0:
            case 1:
                func_mission_overlay_800EFDE0(s1->obj, *(s32 *)(s1->rec + 0xC4), 6, dt);
                if (validateActorTargetLOS(s1->obj) == 1) {
                    applyToObjectSubstructByFlag(s1->obj, dt, 0.0f, 0);
                }
                break;
            case 2:
                {
                    u8 *r = s1->rec;
                    u8 *t;
                    func_mission_overlay_800EFDE0(s1->obj, *(s32 *)(r + 0xC4), *(s32 *)(r + 0xC8), dt);
                    if (validateActorTargetLOS(s1->obj) == 1) {
                        applyToObjectSubstructByFlag(s1->obj, dt, 0.0f, 0);
                    }
                    t = (u8 *)(D_main_bss_80137CE4 * 4) + (s32)r;
                    if (evaluateTargetTrackingVisibility(s1->obj, *(s32 *)(t + 0xEC), *(s32 *)(t + 0xE8)) == 1) {
                        applyToObjectSubstructByFlag(s1->obj, dt, 0.0f, 1);
                    }
                }
                break;
            }
            break;
        case 2:
            if (s1->mode == 2) {
                f32 h;
                s1->pos.x += s1->vel.x * dt;
                s1->pos.y += s1->vel.y * dt;
                s1->pos.z += s1->vel.z * dt;
                if (spawnNpcAnchoredEffectSlot(s1->obj, dt, 0x64) == 1) {
                    s1->mode = 3;
                }
                s1->vel.y += dt * 2.2f;
                h = wrapAngleToCyclicRange(s1->pos.x, s1->pos.z, D_main_bss_80138058, 0);
                if (h < s1->pos.y) {
                    s1->pos.y = h;
                    s1->mode = 3;
                }
                quatFromAxisAngle(q, s1->axis, -s1->f7C);
                shRot(&v, &s1->fwd);
                s1->fwd = v;
                rotateVec3ByQuat(q, &s1->up, &v);
                s1->up = v;
            }
            break;
        case 3:
            {
                s32 k;
                s32 n = (s16)(rand_npcs() % 5) + 5;
                for (k = 0; k < n; k++) {
                    f32 a;
                    f32 b;
                    composeRandomRotationMatrix_npcs(q, &v, s1->radius * 0.5f, 0x5A, 0, 0);
                    q[0] += s1->pos.x;
                    q[1] += s1->pos.y;
                    q[2] += s1->pos.z;
                    scaleVec3ByRandomRange_npcs(&v, 3.0f, 4.0f);
                    a = FABSF_VAL(((f32)(rand_npcs() & 0x7F) - 64.0f) * 0.03125f * 5.0f) + 40.0f;
                    b = FABSF_VAL(((f32)(rand_npcs() & 0x7F) - 64.0f) * 0.0078125f) + 1.0f;
                    spawnDebris1Npc_npcs(q, &v, a, b, FABSF_VAL(((f32)(rand_npcs() & 0x7F) - 64.0f) / 213.33333f) + 0.3f);
                }
            }
            spawnDestructionEffectBurst_npcs(s1, 0xFFFF, 2.0f, 1.5f, 1.2f, 0.8f);
            spawnOrientedEffectIfBudgetOk(s1, 0, 0, 2.5f, 1.0f);
            zmemcpy(m, s1, 0x30);
            if (s1->type == 0) {
                m[9] = s1->radius;
                m[10] = s1->radius;
                m[11] = s1->radius;
            } else {
                m[9] = s1->radius * 0.6f;
                m[10] = s1->radius * 0.6f;
                m[11] = s1->radius * 0.6f;
            }
            gameStateByteGatedNpcHelper(2, m, 0, s1->radius * 0.8f, s1->radius * 1.2f, 0.5f);
            spawnNpcType0xAFromTemplate(s1, s1->radius * 4.0f);
            if (s1->type != 3) {
                play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.3f, 0, 0x22, 0x7D, 0x50);
            } else {
                play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.8f, 0, 0x22, 0x7F, 0x50);
            }
        case 4:
        destroy:
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        if (*(s32 *)(s1->rec + 0x88) == 0) {
            s1->outCount = 0;
        } else if (isNpcWithinActiveReferenceRange(s1) != 0) {
            s1->outCount = 0;
        } else {
            s1->outCount++;
            if (s1->outCount >= 0x15) {
                goto destroy;
            }
        }
        destroyObjectOwnedNpcSlot(s1->obj);
        if (s1->datC8 != 0xFF) {
            walkDatTreeAndScaleLeafByFloat(&s1->datC8, s1->mesh, *(s32 *)arg2);
            return 1;
        }
        return 1;
    case 4:
        {
            u8 *a4 = arg2;
            if (s1->type != 3) {
                u8 *m;
                u8 *mp;
                mp = s1->mat0;
                m = s1->node0 + 0x1C;
                clearVec4QuadStruct(m);
                if (*(s32 *)(mp + 0x4C) & 1) {
                    addVec3At0x24(m, -*(f32 *)(mp + 0x50), -*(f32 *)(mp + 0x54), -*(f32 *)(mp + 0x58));
                }
                if (*(s32 *)(mp + 0x4C) & 2) {
                    applyScaleToMat3x4(m, *(f32 *)(mp + 0x5C), *(f32 *)(mp + 0x60), *(f32 *)(mp + 0x64));
                }
                if (*(s32 *)(mp + 0x4C) & 4) {
                    composeQuatToMat3x4(m, mp + 0x68);
                }
                composeRotationMatrixSlot2(m, s1->f60);
                if ((*(s32 *)(mp + 0x4C) & 9) == 9) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x78) + *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x7C) + *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x80) + *(f32 *)(mp + 0x58));
                } else if ((*(s32 *)(mp + 0x4C) & 9) == 8) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x78), *(f32 *)(mp + 0x7C), *(f32 *)(mp + 0x80));
                } else if (*(s32 *)(mp + 0x4C) & 1) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x58));
                }
                mp = s1->mat1;
                m = s1->node1 + 0x1C;
                clearVec4QuadStruct(m);
                if (*(s32 *)(mp + 0x4C) & 1) {
                    addVec3At0x24(m, -*(f32 *)(mp + 0x50), -*(f32 *)(mp + 0x54), -*(f32 *)(mp + 0x58));
                }
                if (*(s32 *)(mp + 0x4C) & 2) {
                    applyScaleToMat3x4(m, *(f32 *)(mp + 0x5C), *(f32 *)(mp + 0x60), *(f32 *)(mp + 0x64));
                }
                if (*(s32 *)(mp + 0x4C) & 4) {
                    composeQuatToMat3x4(m, mp + 0x68);
                }
                composeRotationMatrixSlot2(m, -s1->f60);
                if ((*(s32 *)(mp + 0x4C) & 9) == 9) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x78) + *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x7C) + *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x80) + *(f32 *)(mp + 0x58));
                } else if ((*(s32 *)(mp + 0x4C) & 9) == 8) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x78), *(f32 *)(mp + 0x7C), *(f32 *)(mp + 0x80));
                } else if (*(s32 *)(mp + 0x4C) & 1) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x58));
                }
            }
            mat34CrossRowsAndCopyPos(s1->mesh + 0x28, s1, s1->scale);
            if (addNpcToVisibilityBucket(*(s32 *)a4, s1->mesh, s1, s1->radius) != 0 && s1->datC8 != 0xFF) {
                walkDatTreeAndVisitChildren(&s1->datC8, s1->mesh, a4);
            }
            if (s1->audioOn == 1) {
                updateActive3DAudioSource(s1->audio, s1, &s1->vel, 0x6E);
                return 1;
            }
        }
        return 1;
    case 6:
        if (*(u16 *)arg2 != 0xFFFF) {
            f32 *p = getNpcContextField8(*(u16 *)arg2);
            f32 len;
            q[0] = s1->pos.x - p[0];
            q[1] = s1->pos.y - p[1];
            q[2] = s1->pos.z - p[2];
            len = vec3Length(q);
            if (len > 0.0f) {
                q[0] = q[0] / len * 0.2f;
                q[1] = q[1] / len * 0.2f;
                q[2] = q[2] / len * 0.2f;
                syncType1ActorFrameToAnchorIfZeroGate(s1->obj, q);
                return 1;
            }
        }
        return 1;
    case 5:
        {
            u8 *a5 = arg2;
            if (getNpcCurrentHealth(s1->obj) > 0) {
                u8 *p = *(u8 **)(arg2 + 8);
                if (p != NULL) {
                    f32 k = 0.2f;
                    vec3ExtrapolateFirstOrder(p, 0, q, k);
                    if (*(u16 *)(arg2 + 4) != 0xC) {
                        distanceAndDopplerNpcHelper(q, 0.05f, k);
                        spawnNpcType0xAFromTemplate(q, k);
                    } else {
                        spawnRandomScaleColoredEffectAltVariant(q, 0.4f);
                    }
                }
                if (s1->type != 3) {
                    play3DSoundEvent(0, s1, &s1->vel, 18.0f, 0.1f, 0, 0x4F, 0x78, 0x50);
                } else {
                    play3DSoundEvent(0, s1, &s1->vel, 20.0f, 0.3f, 0, 0x4F, 0x78, 0x50);
                }
                if (getObjectDetailLevel(s1->obj) == 1 && D_main_bss_80130B39 == 0) {
                    func_mission_overlay_800EFD6C(0x1F4);
                }
                if (dealDamageToNpc(s1->obj, *(u16 *)(a5 + 6)) <= 0) {
                    nsuDestroy(s1, *(u16 *)a5, *(u16 *)(a5 + 2), *(u16 *)(a5 + 4));
                    unregisterAndFreeNpcSlot(s1->slot54, arg0);
                    unregisterAndFreeNpcSlot(s1->slot56, arg0);
                    unregisterAndFreeNpcSlot(s1->slot58, arg0);
                    if (s1->slot5A != 0xFFFF) {
                        unregisterAndFreeNpcSlot(s1->slot5A, arg0);
                    }
                    popNpcSlotFromTail(D_main_bss_80139574, arg0);
                    {
                        u8 *r = s1->rec;
                        datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s1->rec + 0x84));
                    }
                    tallyMidDetailObject(arg0);
                    setObjectFlagBit4(arg0);
                }
            }
            if (*(u16 *)a5 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)a5);
                return 1;
            }
        }
        return 1;
    case 9:
        {
            u8 *a9 = arg2;
            switch (arg2[0x18]) {
            case 0:
                if (*(s32 *)a9 == 1) {
                    if ((s32)*(f32 *)(a9 + 4) == 0) {
                        s1->f68 = -1.0f / *(f32 *)(a9 + 8);
                        if (s1->type == 3) break;
                    } else {
                        s1->f68 = 1.0f / *(f32 *)(a9 + 8);
                        if (s1->type == 3) break;
                    }
                    play3DSoundEvent(0, s1, &s1->vel, 10.0f, 0.1f, 0, 0x50, 0x78, 0x28);
                    return 1;
                }
                break;
            case 1:
                setType1ActorParams(s1->obj, *(s32 *)a9, a9[9], a9[0xA], a9[8], *(s32 *)(a9 + 4));
                return 1;
            case 6:
                if (s1->type != 2) {
                    ((ShEvent *)&v)->a = *(u16 *)a9;
                    ((ShEvent *)&v)->b = 0xFFFF;
                    ((ShEvent *)&v)->c = 7;
                    ((ShEvent *)&v)->d = *(u16 *)(a9 + 2);
                    ((ShEvent *)&v)->e = 0;
                    slotDispatcherIter(*(u16 *)(arg0 + 0x16), 5, (TsEvent *)&v);
                    return 1;
                }
                break;
            case 7:
                {
                    char *nm = *(char **)a9;
                    if (*nm == '+') {
                        u16 f;
                        u16 g;
                        u8 *r;
                        initActorAsType4(s1->obj, nm + 1, getActorCurrentValueByType(s1->obj), *(s32 *)(s1->rec + 0xAC), *(s32 *)(s1->rec + 0xA8));
                        r = s1->rec;
                        f = (*(s32 *)(r + 0xA0) != 0) << 6;
                        if (*(s32 *)(r + 0xA4) != 0) {
                            f |= 0x80;
                        }
                        g = f;
                        updateObjectFlags110(s1->obj, g, g ^ 0xFFFF);
                        return 1;
                    }
                }
                return 1;
            case 8:
                if (getNpcCurrentHealth(s1->obj) > 0) {
                    u8 *b;
                    s32 o;
                    unregisterAndFreeNpcSlot(s1->slot56, arg0);
                    b = (u8 *)D_main_bss_80139560;
                    o = 0x2C;
                    if (*(s32 *)a9 == 1) {
                        o = 0x2E;
                    }
                    s1->slot56 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    unregisterAndFreeNpcSlot(s1->slot58, arg0);
                    o = 0x12;
                    if (*(s32 *)a9 == 1) {
                        o = 0xE;
                    }
                    s1->slot58 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    if (s1->slot5A != 0xFFFF) {
                        unregisterAndFreeNpcSlot(s1->slot5A, arg0);
                        if (*(s32 *)(s1->rec + 0xC0) != 0) {
                            o = 0x18;
                            if (*(s32 *)a9 == 1) {
                                o = 0x1A;
                            }
                            s1->slot5A = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                        }
                    }
                    setObjectDetailLevel(s1->obj, *(s32 *)a9);
                    return 1;
                }
                return 1;
            }
        }
        break;
    case 7:
        dispatchSlotAction5IfActive(arg0, arg2);
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D38A0", fake_func_800D4EC4);

__asm__(".section .rodata\n.word 0x8FC30020\n.word 0x30624000\n.section .text");
