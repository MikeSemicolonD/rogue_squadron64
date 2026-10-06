#include "common.h"
#include "common_types.h"

struct NiObj { u8 pad0[0x34]; u8 *f34; s32 f38; u8 pad3C[0x34]; s16 f70; s16 f72; s16 f74; u8 pad76[2]; f32 f78; f32 f7C; s32 f80; s32 f84; };
typedef struct { u8 pad0[4]; struct NiObj *obj; } NiActor;
extern s32 D_main_bss_80137CE4;
s32 spawnNpcDestructionEffect();
s32 playNpcAmbientEffect();
s32 spawnNpcImpactEffectVariant();
s32 playNpcStateChangeEffect();
s32 setNpcHealth(s32, u8 *, u8 *);
void setObjectDetailLevel(s32, s32);
void initActorMotionParams(s32, f32, f32, f32, f32);
void initObjectAnimSubstruct(s32, f32, f32, f32, f32, s32 (*)(), s32, f32, f32, f32);

void initNpcActorFromSpawnMessage(NiActor *arg0)
{
  struct NiObj *o = arg0->obj;
  u8 *e;
  if (setNpcHealth(o->f38, o->f34 + 0x6C, o->f34) > 0)
  {
    o->f72 = 0;
  }
  else
  {
    o->f72 = 3;
  }
  o->f84 = 0;
  o->f80 = 0;
  o->f74 = 0;
  o->f7C = 1.0f;
  o->f78 = *((f32 *) (((D_main_bss_80137CE4 * 4) + o->f34) + 0x9C));
  ;
  initActorMotionParams(o->f38, *((f32 *) ((o->f34 + (D_main_bss_80137CE4 * 4)) + 0x98)), *((f32 *) ((o->f34 + (D_main_bss_80137CE4 * 4)) + 0xA0)), *((f32 *) ((o->f34 + (D_main_bss_80137CE4 * 4)) + 0xA4)), *((f32 *) ((o->f34 + (D_main_bss_80137CE4 * 4)) + 0xA8)));
  setObjectDetailLevel(o->f38, *((s32 *) (o->f34 + 0x8C)));
  switch (o->f70)
  {
    case 1:
      e = o->f34;
      initObjectAnimSubstruct(o->f38, *((f32 *) (e + 0xAC)), *((f32 *) (e + 0xB0)), *((f32 *) (e + 0xB4)), *((f32 *) (e + 0xB8)), spawnNpcDestructionEffect, 0, 5.0f, 50.0f, *((f32 *) (((D_main_bss_80137CE4 * 4) + e) + 0xBC)));
      break;

    case 3:
      e = o->f34;
      initObjectAnimSubstruct(o->f38, *((f32 *) (e + 0xAC)), *((f32 *) (e + 0xB0)), *((f32 *) (e + 0xB4)), *((f32 *) (e + 0xB8)), playNpcAmbientEffect, 0, 10.0f, 15.0f, *((f32 *) (((D_main_bss_80137CE4 * 4) + e) + 0xBC)));
      break;

    case 4:
      e = o->f34;
      initObjectAnimSubstruct(o->f38, *((f32 *) (e + 0xAC)), *((f32 *) (e + 0xB0)), *((f32 *) (e + 0xB4)), *((f32 *) (e + 0xB8)), spawnNpcImpactEffectVariant, 0, 10.0f, 50.0f, *((f32 *) (((D_main_bss_80137CE4 * 4) + e) + 0xBC)));
      break;

    default:
      e = o->f34;
      initObjectAnimSubstruct(o->f38, *((f32 *) (e + 0xAC)), *((f32 *) (e + 0xB0)), *((f32 *) (e + 0xB4)), *((f32 *) (e + 0xB8)), playNpcStateChangeEffect, 0, 10.0f, 15.0f, *((f32 *) (((D_main_bss_80137CE4 * 4) + e) + 0xBC)));
      break;

  }

}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A6994);

extern char D_mission_overlay_800A6994[];
extern u8 D_mission_overlay_8010A5AC[];
void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
void generatePerpEmitDirectionWithJitter(s32, void *, s32);
u8 tickProgressChannel(s32, void *, s32, f32 *);
s32 triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 playNpcStateChangeEffect(u8 *arg0) {
    u8 sp28[0x30];
    u8 sp58[0x30];
    u8 sp88[0x30];
    f32 spB8;
    f32 spBC;
    s32 temp_s1;
    s32 temp_v0;
    u8 *temp_s2;

    temp_s2 = *(u8 **)(arg0 + 4);
    lookupHmtTextureByName(*(s32 *)(temp_s2 + 0x30), D_mission_overlay_800A6994, 0, sp28, (s32)sp88, 0);
    lookupHmtTextureByName(*(s32 *)(temp_s2 + 0x30), D_mission_overlay_800A6994, 1, sp58, (s32)sp88, 1);
    generatePerpEmitDirectionWithJitter(*(s32 *)(temp_s2 + 0x38), sp28, 0);
    generatePerpEmitDirectionWithJitter(*(s32 *)(temp_s2 + 0x38), sp58, 1);
    temp_s1 = tickProgressChannel(*(s32 *)(temp_s2 + 0x38), sp28, 0, &spB8) & 0xFF;
    if (temp_s1 == 1) {
        temp_v0 = tickProgressChannel(*(s32 *)(temp_s2 + 0x38), sp58, 0, &spBC) & 0xFF;
        if (temp_v0 == temp_s1) {
            triggerCueWithSlotEffect(*(s32 *)(temp_s2 + 0x38), 2, sp28, D_mission_overlay_8010A5AC, temp_v0, 10.0f, spB8);
            triggerCueWithSlotEffect(*(s32 *)(temp_s2 + 0x38), 2, sp58, D_mission_overlay_8010A5AC, 0, 10.0f, spBC);
            *(s32 *)(temp_s2 + 0x7C) = 0;
            play3DSoundEvent(0, temp_s2, temp_s2 + 0x24, 18.0f, 0.5f, 0, 0x16, 0x7F, 0x28);
        }
    }
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A69A0);

extern s32 slotDispatcherIter(u16, s32, void *);
typedef struct {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    s32 unk8;
    s32 unkC;
    f32 unk10;
    s8 unk14;
    u8 pad15[0xB];
} DestructParams;

extern f32 *gomtA(s32, void *) __asm__("getObjectMeshTransformOrLocal");
extern s16 getObjectNpcTypeId(s32);
extern void spawnByteAnimDebrisWithParam(void *, s32);



s32 spawnNpcDestructionEffect(NiActor *arg0)
{
  struct NiObj *o;
  u8 *e;
  DestructParams sp28;
  u8 sp48[0x30];
  u8 sp78[0x30];
  u8 spA8[0x30];
  f32 spD8;
  f32 spDC;
  s32 done;
  s32 *hp;
  s32 nh;
  u16 idA;
  u16 idB;
  f32 *mt;
  o = arg0->obj;
  e = o->f34;
  mt = gomtA(o->f38, sp48);
  if (((*((f32 *) (e + 0xD0))) * 0.25f) < mt[1])
  {
    return 0;
  }
  hp = (s32 *)&e[D_main_bss_80137CE4 * 4 + 0xC0];
  done = 0;
  if (*hp > 0)
  {
    if ((*((s32 *) (e + 0xC4))) != 0)
    {
      nh = *hp - 1;
    }
    else
    {
      nh = *hp - 2;
    }
    *hp = nh;
    if (nh <= 0)
    {
      done = 1;
    }
    sp28.unk0 = 0;
    idB = 0xFFFF;
    sp28.unk2 = getObjectNpcTypeId(o->f38);
    sp28.unk4 = (*((s32 *) ((e + (D_main_bss_80137CE4 * 4)) + 0xCC))) * 0.033333335f;
    sp28.unk8 = 0;
    sp28.unkC = 0;
    sp28.unk10 = -1.0f;
    sp28.unk14 = 2;
    lookupHmtTextureByName(*((s32 *) (((u8 *) o) + 0x30)), D_mission_overlay_800A6994, 0, sp48, (s32) spA8, 0);
    lookupHmtTextureByName(*((s32 *) (((u8 *) o) + 0x30)), D_mission_overlay_800A6994, 1, sp78, (s32) spA8, 1);
    generatePerpEmitDirectionWithJitter(o->f38, sp48, 0);
    generatePerpEmitDirectionWithJitter(o->f38, sp78, 1);
    idA = idB;
    if ((*((s32 *) (e + 0xC4))) == 0)
    {
      if (tickProgressChannel(o->f38, sp48, 0, &spD8) == 1)
      {
        idA = triggerCueWithSlotEffect(o->f38, 0xB, sp48, 0, 0, 5.0f, spD8);
        spawnByteAnimDebrisWithParam(sp48, 0x80);
      }
      if (tickProgressChannel(o->f38, sp78, 0, &spDC) == 1)
      {
        idB = triggerCueWithSlotEffect(o->f38, 0xB, sp78, 0, 0, 5.0f, spDC);
        spawnByteAnimDebrisWithParam(sp78, 0x80);
      }
    }
    else
    {
      o->f74 ^= 1;
      if (o->f74 != 0)
      {
        if (tickProgressChannel(o->f38, sp48, 0, &spD8) == 1)
        {
          idA = triggerCueWithSlotEffect(o->f38, 0xB, sp48, 0, 0, 5.0f, spD8);
          spawnByteAnimDebrisWithParam(sp48, 0x80);
        }
      }
      else
        if (tickProgressChannel(o->f38, sp78, 0, &spDC) == 1)
      {
        idA = triggerCueWithSlotEffect(o->f38, 0xB, sp78, 0, 0, 5.0f, spDC);
        spawnByteAnimDebrisWithParam(sp78, 0x80);

      }
    }
    if ((*((s32 *) (e + 0xC8))) != 0)
    {
      if (idA != 0xFFFF)
      {
        slotDispatcherIter(idA, 0xA, &sp28);
      }
      if (idB != 0xFFFF)
      {
        slotDispatcherIter(idB, 0xA, &sp28);
      }
    }
    if ((idA != 0xFFFF) || (idB != 0xFFFF))
    {
      play3DSoundEvent(0, o, ((u8 *) o) + 0x24, 19.0f, 0.5f, 0, 0x30, 0x7F, 0x28);
    }
    else
    {
      return done;
    }
  }
  return done;
}

s32 getObjectMeshTransformOrLocal();
s16 getObjectNpcTypeId(s32);
s32 slotDispatcherIter(u16, s32, void *);
typedef struct { s16 a; s16 b; f32 c; s32 d; s32 e; f32 f; s8 g; u8 pad[0x20 - 0x15]; } ImpactSlotArgs;

s32 spawnNpcImpactEffectVariant(u8 *arg0) {
    u8 sp28[0x30];
    u8 sp58[0x30];
    u8 sp88[0x30];
    ImpactSlotArgs spB8;
    f32 spD8;
    f32 spDC;
    u8 *temp_s2;
    u8 *temp_s3;
    s32 temp_s1;
    s32 temp_v0;
    s32 s1;
    s32 s5;
    s32 *cnt;
    s32 v;

    temp_s2 = *(u8 **)(arg0 + 4);
    temp_s3 = *(u8 **)(temp_s2 + 0x34);
    if (*(s32 *)(temp_s3 + 0xC0) == 0) {
        lookupHmtTextureByName(*(s32 *)(temp_s2 + 0x30), D_mission_overlay_800A6994, 0, sp28, (s32)sp88, 0);
        lookupHmtTextureByName(*(s32 *)(temp_s2 + 0x30), D_mission_overlay_800A6994, 1, sp58, (s32)sp88, 1);
        generatePerpEmitDirectionWithJitter(*(s32 *)(temp_s2 + 0x38), sp28, 0);
        generatePerpEmitDirectionWithJitter(*(s32 *)(temp_s2 + 0x38), sp58, 1);
        temp_s1 = tickProgressChannel(*(s32 *)(temp_s2 + 0x38), sp28, 0, &spD8) & 0xFF;
        if (temp_s1 != 1) {
            return 0;
        }
        temp_v0 = tickProgressChannel(*(s32 *)(temp_s2 + 0x38), sp58, 0, &spDC) & 0xFF;
        if (temp_v0 != temp_s1) {
            return 0;
        }
        triggerCueWithSlotEffect(*(s32 *)(temp_s2 + 0x38), 2, sp28, D_mission_overlay_8010A5AC, temp_v0, 10.0f, spD8);
        triggerCueWithSlotEffect(*(s32 *)(temp_s2 + 0x38), 2, sp58, D_mission_overlay_8010A5AC, 0, 10.0f, spDC);
        play3DSoundEvent(0, temp_s2, temp_s2 + 0x24, 18.0f, 0.5f, 0, 0x16, 0x7F, 0x28);
        return 0;
    } else {
        if (*(f32 *)(getObjectMeshTransformOrLocal(*(s32 *)(temp_s2 + 0x38), sp28) + 4) > *(f32 *)(temp_s3 + 0xD4) * 0.25f) {
            return 0;
        }
        cnt = (s32 *)&temp_s3[D_main_bss_80137CE4 * 4 + 0xC4];
        v = *cnt;
        if (v <= 0) {
            return 0;
        }
        {
            if (*(s32 *)(temp_s3 + 0xC8) == 0) {
                *cnt = v - 2;
            } else {
                *cnt = v - 1;
            }
            spB8.a = 0;
            s5 = 0xFFFF;
            spB8.b = getObjectNpcTypeId(*(s32 *)(temp_s2 + 0x38));
            spB8.c = (f32)*(s32 *)&temp_s3[D_main_bss_80137CE4 * 4 + 0xD0] * 0.033333335f;
            spB8.d = 0;
            spB8.e = 0;
            spB8.f = -1.0f;
            spB8.g = 2;
            lookupHmtTextureByName(*(s32 *)(temp_s2 + 0x30), D_mission_overlay_800A6994, 0, sp28, (s32)sp88, 0);
            lookupHmtTextureByName(*(s32 *)(temp_s2 + 0x30), D_mission_overlay_800A6994, 1, sp58, (s32)sp88, 1);
            generatePerpEmitDirectionWithJitter(*(s32 *)(temp_s2 + 0x38), sp28, 0);
            generatePerpEmitDirectionWithJitter(*(s32 *)(temp_s2 + 0x38), sp58, 1);
            s1 = s5;
            if (*(s32 *)(temp_s3 + 0xC8) == 0) {
                if ((tickProgressChannel(*(s32 *)(temp_s2 + 0x38), sp28, 0, &spD8) & 0xFF) == 1) {
                    s1 = triggerCueWithSlotEffect(*(s32 *)(temp_s2 + 0x38), 0xB, sp28, NULL, 0, 5.0f, spD8);
                }
                if ((tickProgressChannel(*(s32 *)(temp_s2 + 0x38), sp58, 0, &spDC) & 0xFF) == 1) {
                    s5 = triggerCueWithSlotEffect(*(s32 *)(temp_s2 + 0x38), 0xB, sp58, NULL, 0, 5.0f, spDC);
                }
            } else {
                *(u16 *)(temp_s2 + 0x74) ^= 1;
                if (*(u16 *)(temp_s2 + 0x74) != 0) {
                    if ((tickProgressChannel(*(s32 *)(temp_s2 + 0x38), sp28, 0, &spD8) & 0xFF) == 1) {
                        s1 = triggerCueWithSlotEffect(*(s32 *)(temp_s2 + 0x38), 0xB, sp28, NULL, 0, 5.0f, spD8);
                    }
                } else if ((tickProgressChannel(*(s32 *)(temp_s2 + 0x38), sp58, 0, &spDC) & 0xFF) == 1) {
                    s1 = triggerCueWithSlotEffect(*(s32 *)(temp_s2 + 0x38), 0xB, sp58, NULL, 0, 5.0f, spDC);
                }
            }
            if (*(s32 *)(temp_s3 + 0xCC) != 0) {
                if ((u16)s1 != 0xFFFF) {
                    slotDispatcherIter(s1 & 0xFFFF, 0xA, &spB8);
                }
                if ((u16)s5 != 0xFFFF) {
                    slotDispatcherIter(s5 & 0xFFFF, 0xA, &spB8);
                }
            }
            if ((u16)s1 != 0xFFFF || (u16)s5 != (u16)s1) {
                play3DSoundEvent(0, temp_s2, temp_s2 + 0x24, 19.0f, 0.5f, 0, 0x30, 0x7F, 0x28);
            }
        }
    }
    return 0;
}

typedef struct { f32 x, y, z; } UoV3;
typedef struct { s32 x, y, z; } UoV3i;
typedef struct {
    UoV3 pos;
    UoV3 fwd;
    UoV3 up;
    UoV3 vel;
    u8 pad30[8];
    s32 obj;
    u8 pad3C[0x18];
    f32 scale;
    f32 radius;
    f32 yaw;
    f32 pitch;
    u8 pad64[0xC];
    s16 kind;
    u8 pad72[6];
    f32 rate;
    u8 pad7C[0x10];
    u8 audio[0x44];
    u16 sndId;
    u8 audioOn;
} UoNpc;
typedef struct { f32 a, b; } UoLim;
extern f32 D_mission_overlay_8010A5A0[];
extern f32 D_mission_overlay_8010A5B8[];
extern UoLim D_mission_overlay_8010A5CC[];
u8 isPendingChildNpcActive(s32);
u8 computeActorAnchorDeltaAfterLOS(s32);
void *uoGetMesh(s32, void *) __asm__("getObjectMeshTransformOrLocal");
void computeAnchorRelativePositionByDistanceRatio(void *, void *, f32, void *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void mat3x3InverseInto(void *, void *);
void transformVec3ByMat34(void *, void *, void *);
void vec3NormalizeInto(void *, void *);
void buildRotationMatrixSlot0(void *, f32);
void buildRotationMatrixSlot1(void *, f32);
void uoComposeSlot1(void *, f32) __asm__("composeRotationMatrixSlot1");
f32 vec3Dot(void *, void *);
f32 vec3Length(void *);
f32 constMinusSinfApprox(f32);
void vec3Cross(void *, void *, void *);
void normalize_vector(void *);
void quatFromAxisAngle(void *, void *, f32);
void rotateVec3ByQuat(void *, void *, void *);
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
void factor5RemoveListNode(void *);

void uoImpl(UoNpc *npc, f32 dt) __asm__("updateNpcOrientationFromMotion");
void uoImpl(UoNpc *npc, f32 dt) {
    UoV3 sv;
    f32 m[12];
    f32 dir[4];
    f32 v[4];
    f32 rel[4];
    f32 meshbuf[12];
    f32 mtx[12];
    f32 inv[12];
    f32 axis[4];
    f32 q[4];
    f32 cr[4];
    f32 t1[4];
    f32 t2[4];
    f32 ang;
    f32 lim;
    f32 b;
    f32 p;
    u8 ok;
    u8 big;
    void *mesh;
    UoV3 *f;

    f = &npc->fwd;
    sv = *f;
    buildRotationMatrixSlot0(m, npc->pitch);
    do {
        uoComposeSlot1(m, npc->yaw + 180.0f);
    } while (0);
    transformVec3ByMat34(m, &sv, f);
    ok = isPendingChildNpcActive(npc->obj) == 1 && computeActorAnchorDeltaAfterLOS(npc->obj) == 1;
    *f = sv;
    if (ok == 1) {
        mesh = uoGetMesh(npc->obj, meshbuf);
        if (npc->kind != 1) {
            computeAnchorRelativePositionByDistanceRatio(npc, mesh, 10.0f, rel);
        } else {
            computeAnchorRelativePositionByDistanceRatio(npc, mesh, 5.0f, rel);
        }
        mat34CrossRowsAndCopyPos(mtx, npc, 1.0f);
        mat3x3InverseInto(inv, mtx);
        transformVec3ByMat34(inv, rel, v);
        v[1] += D_mission_overlay_8010A5B8[npc->kind] * npc->scale;
        vec3NormalizeInto(dir, v);
        buildRotationMatrixSlot0(mtx, npc->pitch + 180.0f);
        uoComposeSlot1(mtx, npc->yaw);
        transformVec3ByMat34(mtx, D_mission_overlay_8010A5A0, v);
        ang = constMinusSinfApprox(vec3Dot(v, dir)) * 57.29578f;
        if (0.001f < ang) {
            big = 0;
            if (10.0f < ang) {
                big = 1;
            }
            lim = npc->rate * (dt * 30.0f);
            if (lim < ang) {
                ang = lim;
            }
            vec3Cross(axis, v, dir);
            normalize_vector(axis);
            quatFromAxisAngle(q, axis, ang);
            rotateVec3ByQuat(q, v, dir);
            axis[1] = 0.0f;
            axis[0] = dir[0];
            axis[2] = dir[2];
            ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A5A0, axis) / (vec3Length(D_mission_overlay_8010A5A0) * vec3Length(axis))) * 57.29578f;
            *(UoV3i *)t1 = *(UoV3i *)D_mission_overlay_8010A5A0;
            t1[1] = 0.0f;
            *(UoV3i *)t2 = *(UoV3i *)axis;
            t2[1] = 0.0f;
            vec3Cross(cr, t1, t2);
            if (!(0.0f <= cr[1])) {
                ang = -ang;
            }
            buildRotationMatrixSlot1(mtx, -ang + 180.0f);
            transformVec3ByMat34(mtx, dir, axis);
            axis[0] = 0.0f;
            npc->yaw = ang + 180.0f;
            b = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A5A0, axis) / (vec3Length(D_mission_overlay_8010A5A0) * vec3Length(axis))) * 57.29578f;
            if (!(axis[1] <= 0.0f)) {
                b = -b;
            }
            p = b + 180.0f;
            npc->pitch = p;
            if (180.0f < p) {
                if (D_mission_overlay_8010A5CC[npc->kind].a < 360.0f - p) {
                    npc->pitch = 360.0f - D_mission_overlay_8010A5CC[npc->kind].a;
                }
            } else if (-p < D_mission_overlay_8010A5CC[npc->kind].b) {
                npc->pitch = -D_mission_overlay_8010A5CC[npc->kind].b;
            }
            if (big) {
                if (npc->audioOn == 0) {
                    npc->audioOn = 1;
                    npc->sndId = 0x2000;
                    play3DSoundEventVariant(npc->audio, npc, &npc->vel, 8.0f, 0.1f, 7, 0x27, 1, 100, 0x28);
                }
                return;
            }
        }
        if (npc->audioOn == 1) {
            npc->audioOn = 0;
            factor5RemoveListNode(npc->audio);
        }
    }
}

void releaseMeshAsset(void *);
void *walkMeshdef0List(char *);
void initVec4TripletFromArgs(void *, s32, s32, s32);
void composeRotationMatrixSlot0(void *, s32);
void composeRotationMatrixSlot1(void *, s32);
void composeRotationMatrixSlot2(void *, s32);
void addVec3At0x24(void *, s32, s32, s32);
extern char D_mission_overlay_800A6A0C[];
extern char D_mission_overlay_800A6A18[];
extern char D_mission_overlay_800A6A24[];
extern char D_mission_overlay_800A6A30[];

typedef struct {
    u8 pad0[0x1C];
    s32 rot[3];
    s32 scale[3];
} NpcModelTemplate;

typedef struct {
    s32 pos[3];
    u8 padC[0x24];
    u8 *mesh;
    NpcModelTemplate *tmpl;
    u8 pad38[0x38];
    s16 state;
} NpcModelOwner;

void setupNpcModelForState(NpcModelOwner *npc) {
    NpcModelTemplate *tmpl;

    releaseMeshAsset(npc->mesh);
    switch (npc->state) {
        case 2:
            npc->mesh = walkMeshdef0List(D_mission_overlay_800A6A0C);
            break;
        case 3:
            npc->mesh = walkMeshdef0List(D_mission_overlay_800A6A18);
            break;
        case 4:
            npc->mesh = walkMeshdef0List(D_mission_overlay_800A6A24);
            break;
        default:
            npc->mesh = walkMeshdef0List(D_mission_overlay_800A6A30);
            break;
    }
    tmpl = npc->tmpl;
    initVec4TripletFromArgs(npc->mesh + 0x28, tmpl->scale[0], tmpl->scale[1], tmpl->scale[2]);
    composeRotationMatrixSlot0(npc->mesh + 0x28, tmpl->rot[0]);
    composeRotationMatrixSlot1(npc->mesh + 0x28, tmpl->rot[1]);
    composeRotationMatrixSlot2(npc->mesh + 0x28, tmpl->rot[2]);
    addVec3At0x24(npc->mesh + 0x28, npc->pos[0], npc->pos[1], npc->pos[2]);
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A6A0C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A6A18);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A6A24);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C89C0", D_mission_overlay_800A6A30);

typedef struct { f32 x, y, z; } TVec3;
typedef struct {
    TVec3 pos;
    TVec3 fwd;
    TVec3 up;
    TVec3 vel;
    u8 *mesh;
    u8 *rec;
    s32 obj;
    u8 *node[3];
    u8 *mat[3];
    f32 scale;
    f32 radius;
    f32 yaw;
    f32 pitch;
    u16 slot64;
    u16 slot66;
    u16 slot68;
    u16 slot6A;
    s32 outCount;
    s16 kind;
    s16 state;
    u8 pad74[8];
    f32 f7C;
    f32 f80;
    f32 t84;
    s32 c88;
    u8 audio[0x44];
    u16 sndId;
    u8 audioOn;
} Turret;

#define TABSF(x) ({ f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(x)); _r; })

extern u8 D_main_bss_801399F8[];
extern u16 D_main_bss_80139560[];
extern u16 D_main_bss_80139574;
extern s32 gCurrentLevel;
void composeEulerRotationXYZ(void *, s32, s32, s32);
void addVec3At0x24F(void *, f32, f32, f32) __asm__("addVec3At0x24");
void composeRotationMatrixSlot0F(void *, f32) __asm__("composeRotationMatrixSlot0");
void composeRotationMatrixSlot1F(void *, f32) __asm__("composeRotationMatrixSlot1");
u16 popNpcSlotFromTail(u16, void *);
s32 lookupHmtMaterialByName(void *, char *, void *);
void createAndInitObject(void *, s32, void *, void *, s32);
void factor5RemoveListNode(void *);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void func_mission_overlay_800EFDE0(s32, s32, s32, f32);
void updateNpcOrientationFromMotion(void *, f32);
void buildRotationMatrixSlot0(void *, f32);
void transformVec3ByMat34(void *, void *, void *);
u8 validateActorTargetLOS(s32);
void applyToObjectSubstructByFlag(s32, f32, f32, s32);
s32 rand(void);
void spawnRandomScaleEffectDefault(void *);
s32 spawnNpcType0xAFromTemplate(void *, f32);
void spawnByteAnimDebrisDefault(void *);
void unregisterAndFreeNpcSlot(u16, void *);
void composeRandomRotationMatrix(void *, void *, f32, s32, s32, s32);
void scaleVec3ByRandomRange(void *, f32, f32);
void spawnDebris1Npc(void *, void *, f32, f32, f32);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyNpcSlotByIndex(u16);
void destroyObjectOwnedNpcSlot(s32);
void clearVec4QuadStruct(void *);
void applyScaleToMat3x4(void *, f32, f32, f32);
void composeQuatToMat3x4(void *, void *);
s32 updateActive3DAudioSource(void *, void *, void *, u8);
s32 mostlyMusyxFlagGatedHelper(void *);
void safeLookup3DSoundEntry(s32, u16);
void addNpcToVisibilityBucket(s32, void *, void *, f32);
s32 getNpcCurrentHealth(s32);
void extrapolateNpcPositionForCurrentMode(void *);
s32 dealDamageToNpc(s32, u16);
void spawnDestructionEffectBurst(void *, u16, f32, f32, f32, f32);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
s32 clearPendingChildNpc(s32);
void setObjectFlagBit4(void *);
void dispatchSlotAction5IfActive(void *, void *);

#define XFORM_HEAD(nd, mt) \
    mp = (mt); \
    m = (nd) + 0x1C; \
    clearVec4QuadStruct(m); \
    if (*(s32 *)(mp + 0x4C) & 1) { \
        addVec3At0x24F(m, -*(f32 *)(mp + 0x50), -*(f32 *)(mp + 0x54), -*(f32 *)(mp + 0x58)); \
    } \
    if (*(s32 *)(mp + 0x4C) & 2) { \
        applyScaleToMat3x4(m, *(f32 *)(mp + 0x5C), *(f32 *)(mp + 0x60), *(f32 *)(mp + 0x64)); \
    } \
    if (*(s32 *)(mp + 0x4C) & 4) { \
        composeQuatToMat3x4(m, mp + 0x68); \
    }

#define XFORM_TAIL() \
    if ((*(s32 *)(mp + 0x4C) & 9) == 9) { \
        addVec3At0x24F(m, *(f32 *)(mp + 0x78) + *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x7C) + *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x80) + *(f32 *)(mp + 0x58)); \
    } else if ((*(s32 *)(mp + 0x4C) & 9) == 8) { \
        addVec3At0x24F(m, *(f32 *)(mp + 0x78), *(f32 *)(mp + 0x7C), *(f32 *)(mp + 0x80)); \
    } else if (*(s32 *)(mp + 0x4C) & 1) { \
        addVec3At0x24F(m, *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x58)); \
    }

s32 npcTurretUpdate(u8 *arg0, u16 action, u8 *arg2) {
    Turret *s1 = *(Turret **)(arg0 + 4);
    TVec3 sp28;
    f32 sp38[12];
    s16 kind;
    s32 cnt;
    s32 i;
    s32 n;
    f32 dt;
    u8 *mp;
    u8 *m;
    u8 *a;
    u8 *a4;
    u8 *a5;

    switch (action) {
    case 1:
        switch (*(u16 *)arg2) {
        case 0xD:
        default:
            kind = 0;
            break;
        case 0x1E:
            kind = 1;
            break;
        case 0x28:
            kind = 2;
            break;
        case 0x41:
            kind = 3;
            break;
        case 0x42:
            kind = 4;
            break;
        }
        s1->rec = arg2;
        cnt = *(s32 *)(D_main_bss_80137CE4 * 4 + (s32)arg2 + 0x6C);
        {
            char *name;
            switch (kind) {
            default:
                if (cnt > 0) {
                    name = "i_gtu_hi";
                } else {
                    name = D_mission_overlay_800A6A30;
                }
                break;
            case 1:
                if (cnt > 0) {
                    name = "i_mtu_hi";
                } else {
                    name = D_mission_overlay_800A6A30;
                }
                break;
            case 2:
                if (cnt > 0) {
                    name = "megaturret";
                } else {
                    name = D_mission_overlay_800A6A0C;
                }
                break;
            case 3:
                if (cnt > 0) {
                    name = "r_tur_hi";
                } else {
                    name = D_mission_overlay_800A6A18;
                }
                break;
            case 4:
                if (cnt > 0) {
                    name = "b_ttu_hi";
                } else {
                    name = D_mission_overlay_800A6A24;
                }
                break;
            }
            s1->mesh = walkMeshdef0List(name);
        }
        s1->pos.x = *(f32 *)(arg2 + 0x10);
        s1->pos.y = *(f32 *)(arg2 + 0x14);
        s1->pos.z = *(f32 *)(arg2 + 0x18);
        composeEulerRotationXYZ(s1, *(s32 *)(arg2 + 0x1C), *(s32 *)(arg2 + 0x20), *(s32 *)(arg2 + 0x24));
        s1->vel.x = s1->vel.y = s1->vel.z = 0.0f;
        s1->scale = (1.0f / *(f32 *)(*(u8 **)s1->mesh + 0x34)) * *(f32 *)(arg2 + 0x28);
        initVec4TripletFromArgs(s1->mesh + 0x28, *(s32 *)(arg2 + 0x28), *(s32 *)(arg2 + 0x2C), *(s32 *)(arg2 + 0x30));
        composeRotationMatrixSlot0(s1->mesh + 0x28, *(s32 *)(arg2 + 0x1C));
        composeRotationMatrixSlot1(s1->mesh + 0x28, *(s32 *)(arg2 + 0x20));
        composeRotationMatrixSlot2(s1->mesh + 0x28, *(s32 *)(arg2 + 0x24));
        addVec3At0x24F(s1->mesh + 0x28, s1->pos.x, s1->pos.y, s1->pos.z);
        *(Turret **)(arg0 + 8) = s1;
        *(u8 **)(arg0 + 0xC) = s1->mesh;
        if (cnt > 0) {
            char *n0;
            char *n1;
            char *n2;
            {
                u8 *b = (u8 *)D_main_bss_80139560;
                s32 o;
                s1->slot64 = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
                o = 0x2C;
                if (*(s32 *)(arg2 + 0x8C) == 1) {
                    o = 0x2E;
                }
                s1->slot66 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            }
            if (kind == 0 || kind >= 3) {
                n0 = "top_tran";
                n1 = "barrel_t";
                n2 = "rohr_tra";
            } else {
                n0 = "top_tran";
                n1 = "barrel_t";
                n2 = "barrels";
            }
            s1->node[0] = (u8 *)lookupHmtMaterialByName(s1->mesh, n0, &s1->mat[0]);
            s1->node[1] = (u8 *)lookupHmtMaterialByName(s1->mesh, n1, &s1->mat[1]);
            s1->node[2] = (u8 *)lookupHmtMaterialByName(s1->mesh, n2, &s1->mat[2]);
            {
                u8 *b = (u8 *)D_main_bss_80139560;
                s32 o;
                o = 0x10;
                if (*(s32 *)(arg2 + 0x8C) == 1) {
                    o = 0xC;
                }
                s1->slot68 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                if (*(s32 *)(arg2 + 0x90) != 0) {
                    o = 0x18;
                    if (*(s32 *)(arg2 + 0x8C) == 1) {
                        o = 0x1A;
                    }
                    s1->slot6A = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                } else {
                    s1->slot6A = 0xFFFF;
                }
            }
        } else {
            popNpcSlotFromTail(D_main_bss_80139574, arg0);
        }
        s1->radius = *(f32 *)(*(u8 **)s1->mesh + 0x44) * s1->scale;
        s1->kind = kind;
        createAndInitObject(&s1->obj, 0, arg0, initNpcActorFromSpawnMessage, 0);
        s1->yaw = 0.0f;
        s1->pitch = 0.0f;
        s1->outCount = 0;
        s1->audioOn = 0;
        break;
    case 2:
        if (s1->audioOn == 1) {
            s1->audioOn = 0;
            factor5RemoveListNode(s1->audio);
        }
        initActorRenderDescriptorIfUninit(s1->obj, 0, s1->rec, 0, s1->rec + 0x70);
        clearPendingAndDestroyChildNpc(&s1->obj);
        releaseMeshAsset(s1->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        s1->t84 -= dt;
        switch (s1->state) {
        case 0:
            func_mission_overlay_800EFDE0(s1->obj, *(s32 *)(s1->rec + 0x94), 6, 10.0f);
            s1->state = 1;
            break;
        case 1: {
            s32 idx = 0;
            switch (s1->kind) {
            case 0:
                idx = 0;
                break;
            case 1:
                idx = 1;
                break;
            case 2:
                idx = 2;
                break;
            case 3:
                idx = 4;
                break;
            case 4:
                idx = 5;
                break;
            }
            if (D_main_bss_801399F8[idx] == 1) {
                u8 los;
                func_mission_overlay_800EFDE0(s1->obj, *(s32 *)(s1->rec + 0x94), 6, dt);
                s1->state = 1;
                updateNpcOrientationFromMotion(s1, dt);
                sp28 = s1->fwd;
                buildRotationMatrixSlot0(sp38, s1->pitch);
                composeRotationMatrixSlot1F(sp38, s1->yaw + 180.0f);
                transformVec3ByMat34(sp38, &sp28, &s1->fwd);
                los = validateActorTargetLOS(s1->obj);
                s1->fwd = sp28;
                if (los) {
                    applyToObjectSubstructByFlag(s1->obj, dt, 0.0f, 0);
                }
            }
            break;
        }
        case 2:
            s1->t84 -= dt;
            if (s1->t84 <= 0.0) {
                s1->t84 = TABSF(((f32)(rand() & 0x7F) - 64.0f) / 800.0f) + 0.1f;
                sp28.x = s1->pos.x + ((f32)(rand() & 0x7F) - 64.0f) / 400.0f * 4.0f;
                sp28.y = s1->pos.y - TABSF(((f32)(rand() & 0x7F) - 64.0f) / 320.0f * 4.0f);
                sp28.z = s1->pos.z + ((f32)(rand() & 0x7F) - 64.0f) / 400.0f * 4.0f;
                spawnRandomScaleEffectDefault(&sp28);
                play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.5f, 0, 0x2A, 0x7F, 0x50);
                s1->c88--;
                if (s1->c88 <= 0) {
                    spawnNpcType0xAFromTemplate(s1, s1->radius * 3.0f);
                    spawnByteAnimDebrisDefault(s1);
                    play3DSoundEvent(0, s1, &s1->vel, 25.0f, 0.8f, 0, 0x26, 0x7F, 0x5A);
                    s1->state = 3;
                    setupNpcModelForState((NpcModelOwner *)s1);
                    *(u8 **)(arg0 + 0xC) = NULL;
                    unregisterAndFreeNpcSlot(s1->slot64, arg0);
                    if (s1->kind != 2) {
                        n = (s16)((s16)rand() % 4) + 3;
                    } else {
                        n = (s16)((s16)rand() % 3) + 5;
                    }
                    for (i = 0; i < n; i++) {
                        composeRandomRotationMatrix(sp38, &sp38[4], s1->radius * 0.5f, 60, 0, 0);
                        sp38[0] += s1->pos.x;
                        sp38[1] += s1->pos.y;
                        sp38[2] += s1->pos.z;
                        scaleVec3ByRandomRange(&sp38[4], 3.0f, 4.0f);
                        if (s1->kind != 2) {
                            f32 a = TABSF(((f32)(rand() & 0x7F) - 64.0f) / 12.8f) + 12.0f;
                            f32 b = TABSF(((f32)(rand() & 0x7F) - 64.0f) / 42.666668f) + 2.0f;
                            spawnDebris1Npc(sp38, &sp38[4], a, b, TABSF(((f32)(rand() & 0x7F) - 64.0f) / 213.33333f) + 0.3f);
                        } else {
                            f32 a = TABSF(((f32)(rand() & 0x7F) - 64.0f) * 0.125f) + 18.0f;
                            f32 b = TABSF(((f32)(rand() & 0x7F) - 64.0f) / 25.6f) + 3.0f;
                            spawnDebris1Npc(sp38, &sp38[4], a, b, TABSF(((f32)(rand() & 0x7F) - 64.0f) * 0.0078125f) + 0.5f);
                        }
                    }
                }
            }
            break;
        }
        if (s1->kind != 1) {
            f32 inc = dt * 4.0f;
            if (s1->f7C < 1.0f) {
                s1->f7C += inc;
                if (1.0f < s1->f7C) {
                    s1->f7C = 1.0f;
                    s1->f80 = 0.0f;
                } else if (s1->f7C < 0.2f) {
                    s1->f80 = s1->f7C * 5.0f;
                } else {
                    s1->f80 = 1.0f - (s1->f7C - 0.2f) * 1.25f;
                }
            }
        }
        if (isNpcWithinActiveReferenceRange(s1) != 0) {
            s1->outCount = 0;
        } else {
            s1->outCount++;
            if (s1->outCount >= 0x15) {
                destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                return 1;
            }
        }
        destroyObjectOwnedNpcSlot(s1->obj);
        return 1;
    case 4:
        a4 = arg2;
        if (s1->state != 3) {
            XFORM_HEAD(s1->node[0], s1->mat[0]);
            composeRotationMatrixSlot1F(m, s1->yaw);
            XFORM_TAIL();
            XFORM_HEAD(s1->node[1], s1->mat[1]);
            composeRotationMatrixSlot0F(m, s1->pitch);
            XFORM_TAIL();
            XFORM_HEAD(s1->node[2], s1->mat[2]);
            addVec3At0x24F(m, 0.0f, 0.0f, s1->f80 * 4.0f);
            XFORM_TAIL();
        }
        {
            u8 *au = s1->audio;
            if (s1->audioOn != 0) {
                updateActive3DAudioSource(au, s1, &s1->vel, 0x64);
                safeLookup3DSoundEntry(mostlyMusyxFlagGatedHelper(au), s1->sndId);
            }
        }
        addNpcToVisibilityBucket(*(s32 *)a4, s1->mesh, s1, s1->radius);
        return 1;
    case 5:
        a5 = arg2;
        if (getNpcCurrentHealth(s1->obj) > 0) {
            extrapolateNpcPositionForCurrentMode(a5);
            play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.5f, 0, 0x2A, 0x7F, 0x50);
            if (dealDamageToNpc(s1->obj, *(u16 *)(a5 + 6)) <= 0) {
                if (s1->audioOn == 1) {
                    s1->audioOn = 0;
                    factor5RemoveListNode(s1->audio);
                }
                s1->state = 2;
                s1->t84 = 0.0f;
                s1->c88 = (s16)((s16)rand() % 3) + 3;
                if (gCurrentLevel != 0x11) {
                    spawnDestructionEffectBurst(s1, 0xFFFF, 1.6f, 0.7f, 1.2f, 1.5f);
                }
                unregisterAndFreeNpcSlot(s1->slot66, arg0);
                unregisterAndFreeNpcSlot(s1->slot68, arg0);
                if (s1->slot6A != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s1->slot6A, arg0);
                }
                popNpcSlotFromTail(D_main_bss_80139574, arg0);
                {
                    u8 *r = s1->rec;
                    datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s1->rec + 0x84));
                }
                tallyMidDetailObject(arg0);
                clearPendingChildNpc(s1->obj);
                setObjectFlagBit4(arg0);
            }
        }
        if (*(u16 *)a5 != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)a5);
            return 1;
        }
        return 1;
    case 9:
        a = arg2;
        if (arg2[0x18] == 8) {
            if (getNpcCurrentHealth(s1->obj) > 0) {
                u8 *b;
                register s32 one asm("$18");
                s32 o;
                unregisterAndFreeNpcSlot(s1->slot66, arg0);
                b = (u8 *)D_main_bss_80139560;
                one = 1;
                o = 0x2C;
                if (*(s32 *)arg2 == one) {
                    o = 0x2E;
                }
                s1->slot66 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                unregisterAndFreeNpcSlot(s1->slot68, arg0);
                o = 0x12;
                if (*(s32 *)arg2 == one) {
                    o = 0xE;
                }
                s1->slot68 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                if (s1->slot6A != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s1->slot6A, arg0);
                    if (*(s32 *)(s1->rec + 0x90) != 0) {
                        o = 0x18;
                        if (*(s32 *)arg2 == one) {
                            o = 0x1A;
                        }
                        s1->slot6A = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    }
                }
                setObjectDetailLevel(s1->obj, *(s32 *)a);
            }
        }
    case 7:
        dispatchSlotAction5IfActive(arg0, arg2);
        return 1;
    case 11:
        *(u16 *)(arg2 + 2) = *(u16 *)s1->rec;
        return 1;
    }
    return 1;
}

void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
void generatePerpEmitDirectionWithJitter(s32, void *, s32);
u8 tickProgressChannel(s32, void *, s32, f32 *);
s32 triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern char D_mission_overlay_800A69A0[];
extern u8 D_mission_overlay_8010A5AC[];

s32 playNpcAmbientEffect(u8 *arg0) {
    u8 *npc;
    u8 emit[0x30];
    f32 progress;
    u8 state;

    npc = *(u8 **)(arg0 + 4);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A69A0, 0, emit, 0, 0);
    generatePerpEmitDirectionWithJitter(*(s32 *)(npc + 0x38), emit, 0);
    state = tickProgressChannel(*(s32 *)(npc + 0x38), emit, 0, &progress);
    if (state == 1) {
        triggerCueWithSlotEffect(*(s32 *)(npc + 0x38), 0, emit, D_mission_overlay_8010A5AC, state, 10.0f, progress);
        play3DSoundEvent(0, npc, npc + 0x24, 15.0f, 0.5f, 0, 0x16, 0x7F, 0x28);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C89C0", fake_func_800CA26C);

__asm__(".section .rodata\n.word 0x3C02801C\n.word 0x8C423BBC\n.word 0x3043008B\n.section .text");
