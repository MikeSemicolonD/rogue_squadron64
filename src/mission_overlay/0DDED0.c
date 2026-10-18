#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7DE0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7DEC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7DF8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7E00);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7E0C);

typedef struct { u8 pad0[4]; u8 *obj; } NiActor;
typedef struct { u8 pad0[0x64]; s32 a64[2]; s32 a6C[2]; u8 pad74[0x68]; f32 aDC[2]; s32 aE4[2]; } NiVecs;
struct EffectRow {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    f32 unkC;
};
extern struct EffectRow D_mission_overlay_8010A9C4[];
extern f32 D_mission_overlay_8010AA00;
extern s32 D_main_bss_80137CE4;
extern s32 npcTickEffectChannelC();
extern s32 npcTickEffectChannelD();
extern s32 npcTickEffectChannelE();
extern s32 playAttachmentMaterialFadeSound();
extern void setNpcHealth(s32, u8 *, u8 *);
extern void setObjectDetailLevel(s32, s32);
extern void initActorMotionParams(s32, s32, s32, s32, f32);
extern void initObjectAnimSubstruct(s32, s32, s32, s32, f32, s32 (*)(), s32, f32, f32, s32);

void npcInitFullModel(NiActor *arg0) {
    u8 *o = arg0->obj;
    u8 *e = *(u8 **)(o + 0x34);
    s32 i;
    u8 *p;
    u8 *t;
    f32 fs;

    o[0xD1] = 0;
    for (i = 0; i < 2; i++) {
        ((NiVecs *)o)->a64[i] = 0;
        ((NiVecs *)o)->a6C[i] = 0;
        ((NiVecs *)o)->aDC[i] = 1.0f;
        ((NiVecs *)o)->aE4[i] = 0;
    }
    *(u16 *)(o + 0xD2) = 0;
    *(f32 *)(o + 0xD8) = *(f32 *)(*(u8 **)(o + 0x34) + 0x90);
    setNpcHealth(*(s32 *)(o + 0x38), *(u8 **)(o + 0x34) + 0x6C, *(u8 **)(o + 0x34));
    setObjectDetailLevel(*(s32 *)(o + 0x38), *(s32 *)(*(u8 **)(o + 0x34) + 0xA8));
    *(f32 *)(o + 0xD4) = *(f32 *)((u8 *)(D_main_bss_80137CE4 * 4) + (s32)*(u8 **)(o + 0x34) + 0xC0);
    t = (u8 *)(D_main_bss_80137CE4 * 4) + (s32)*(u8 **)(o + 0x34);
    initActorMotionParams(*(s32 *)(o + 0x38), *(s32 *)(t + 0xB8), *(s32 *)(t + 0xBC), *(s32 *)(t + 0xC4), *(f32 *)(t + 0xC8));
    switch (o[0xCF]) {
    case 0:
        initObjectAnimSubstruct(*(s32 *)(o + 0x38), *(s32 *)(e + 0xCC), *(s32 *)(e + 0xD0), *(s32 *)(e + 0xD4), *(f32 *)(e + 0xD8), npcTickEffectChannelC, 0, D_mission_overlay_8010A9C4[o[0xCF]].unkC, 15.0f, 0);
        break;
    case 1:
        initObjectAnimSubstruct(*(s32 *)(o + 0x38), *(s32 *)(e + 0xCC), *(s32 *)(e + 0xD0), *(s32 *)(e + 0xD4), *(f32 *)(e + 0xD8), npcTickEffectChannelD, 0, D_mission_overlay_8010A9C4[o[0xCF]].unkC, 15.0f, 0);
        break;
    case 2:
        fs = 15.0f;
        initObjectAnimSubstruct(*(s32 *)(o + 0x38), *(s32 *)(e + 0xCC), *(s32 *)(e + 0xD0), *(s32 *)(e + 0xD4), *(f32 *)(e + 0xD8), playAttachmentMaterialFadeSound, 0, D_mission_overlay_8010A9C4[o[0xCF]].unkC, fs, 0);
        initObjectAnimSubstruct(*(s32 *)(o + 0x38), *(s32 *)(e + 0xCC), *(s32 *)(e + 0xD0), *(s32 *)(e + 0xD4), *(f32 *)(e + 0xD8), npcTickEffectChannelE, 1, D_mission_overlay_8010AA00, fs, 0);
        break;
    }
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0DDED0", D_mission_overlay_800A7E28);


extern char D_mission_overlay_800A7E28[];
extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void resolveNpcAttachmentPos(s32, void *, s32, f32);
extern s32 tickProgressChannel(s32, void *, s32, f32 *);
extern void triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);

s32 npcTickEffectChannelC(void *arg0)
{
  u8 sp28[0x30];
  f32 sp58;
  f32 fv;
  s32 r;
  struct EffectRow *e;
  u8 *npc = *((u8 **) (((u8 *) arg0) + 4));
  lookupHmtTextureByName(*((s32 *) (npc + 0x30)), D_mission_overlay_800A7E28, 0, sp28, 0, 0);
  fv = ((f32 *) (*((u8 **) (npc + 0x34))))[D_main_bss_80137CE4 + 0x37];
  if (fv != 0.0f)
  {
    e = &D_mission_overlay_8010A9C4[npc[0xCF]];
    e++;
    e--;
    resolveNpcAttachmentPos(*((s32 *) (npc + 0x38)), sp28, *((s32 *) (&e->unkC)), fv);
  }
  r = tickProgressChannel(*((s32 *) (npc + 0x38)), sp28, 0, &sp58) & 0xFF;
  if (r == 1)
  {
    *((f32 *) (npc + 0xDC)) = 0.0f;
    triggerCueWithSlotEffect(*((s32 *) (npc + 0x38)), 0, sp28, &D_mission_overlay_8010A9C4[npc[0xCF]], r, D_mission_overlay_8010A9C4[npc[0xCF]].unkC, sp58);
    play3DSoundEvent(0, npc, npc + 0x24, 18.0f, 0.5f, 0, 0x48, 0x6E, 0x28);
  }
  return 0;
}

s32 npcTickEffectChannelD(void *arg0)
{
  u8 sp28[0x30];
  f32 sp58;
  f32 fv;
  s32 r;
  struct EffectRow *e;
  u8 *npc = *((u8 **) (((u8 *) arg0) + 4));
  lookupHmtTextureByName(*((s32 *) (npc + 0x30)), D_mission_overlay_800A7E28, 0, sp28, 0, 0);
  fv = ((f32 *) (*((u8 **) (npc + 0x34))))[D_main_bss_80137CE4 + 0x37];
  if (fv != 0.0f)
  {
    e = &D_mission_overlay_8010A9C4[npc[0xCF]];
    e++;
    e--;
    resolveNpcAttachmentPos(*((s32 *) (npc + 0x38)), sp28, *((s32 *) (&e->unkC)), fv);
  }
  r = tickProgressChannel(*((s32 *) (npc + 0x38)), sp28, 0, &sp58) & 0xFF;
  if (r == 1)
  {
    *((f32 *) (npc + 0xDC)) = 0.0f;
    triggerCueWithSlotEffect(*((s32 *) (npc + 0x38)), 2, sp28, &D_mission_overlay_8010A9C4[npc[0xCF]], r, D_mission_overlay_8010A9C4[npc[0xCF]].unkC, sp58);
    play3DSoundEvent(0, npc, npc + 0x24, 18.0f, 0.4f, 0, 0x48, 0x6E, 0x28);
  }
  return 0;
}

extern struct EffectRow D_mission_overlay_8010A9F4;
s32 npcTickEffectChannelE(void *arg0)
{
  u8 sp28[0x30];
  u8 sp58[0x30];
  u8 sp88[0x30];
  f32 spB8;
  f32 fv;
  s32 r;
  u8 *npc = *((u8 **) (((u8 *) arg0) + 4));
  lookupHmtTextureByName(*((s32 *) (npc + 0x30)), "a_b", 0, sp28, (s32) sp88, 0);
  lookupHmtTextureByName(*((s32 *) (npc + 0x30)), "a_b", 1, sp58, (s32) sp88, 1);
  fv = ((f32 *) (*((u8 **) (npc + 0x34))))[D_main_bss_80137CE4 + 0x37];
  if (fv != 0.0f)
  {
    struct EffectRow *row = (struct EffectRow *)&D_mission_overlay_8010A9F4;

    resolveNpcAttachmentPos(*((s32 *) (npc + 0x38)), sp28, *((s32 *) (&row->unkC)), fv);
    resolveNpcAttachmentPos(*((s32 *) (npc + 0x38)), sp58, *((s32 *) (&row->unkC)), fv);
  }
  r = tickProgressChannel(*((s32 *) (npc + 0x38)), sp28, 1, &spB8) & 0xFF;
  if (r == 1)
  {
    struct EffectRow *row = (struct EffectRow *)&D_mission_overlay_8010A9F4;

    *((f32 *) (npc + 0xE0)) = 0.0f;
    { f32 c = row->unkC; triggerCueWithSlotEffect(*((s32 *) (npc + 0x38)), 0, sp28, row, r, c, spB8); }
    { f32 c = row->unkC; triggerCueWithSlotEffect(*((s32 *) (npc + 0x38)), 0, sp58, row, 0, c, spB8); }
    play3DSoundEvent(0, npc, npc + 0x24, 18.0f, 0.3f, 0, 0x1D, 0x78, 0x28);
  }
  return 0;
}

s32 playAttachmentMaterialFadeSound(void *arg0)
{
  u8 sp28[0x30];
  f32 sp58;
  f32 fv;
  s32 r;
  struct EffectRow *e;
  u8 *npc = *((u8 **) (((u8 *) arg0) + 4));
  lookupHmtTextureByName(*((s32 *) (npc + 0x30)), D_mission_overlay_800A7E28, 0, sp28, 0, 0);
  fv = ((f32 *) (*((u8 **) (npc + 0x34))))[D_main_bss_80137CE4 + 0x37];
  if (fv != 0.0f)
  {
    e = &D_mission_overlay_8010A9C4[npc[0xCF]];
    e++;
    e--;
    resolveNpcAttachmentPos(*((s32 *) (npc + 0x38)), sp28, *((s32 *) (&e->unkC)), fv);
  }
  r = tickProgressChannel(*((s32 *) (npc + 0x38)), sp28, 0, &sp58) & 0xFF;
  if (r == 1)
  {
    *((f32 *) (npc + 0xDC)) = 0.0f;
    triggerCueWithSlotEffect(*((s32 *) (npc + 0x38)), 0, sp28, &D_mission_overlay_8010A9C4[npc[0xCF]], r, D_mission_overlay_8010A9C4[npc[0xCF]].unkC, sp58);
    play3DSoundEvent(0, npc, npc + 0x24, 19.0f, 0.5f, 0, 0x48, 0x78, 0x28);
  }
  return 0;
}

typedef struct { f32 m[12]; } CraftMtx;
u8 tcPending(s32) __asm__("isPendingChildNpcActive");
u8 tcLos(s32) __asm__("validateActorTargetLOS");
void tcBuild0(f32 *, s32) __asm__("buildRotationMatrixSlot0");
void tcComp1(f32 *, s32) __asm__("composeRotationMatrixSlot1");
void tcXform(f32 *, f32 *, f32 *) __asm__("transformVec3ByMat34");
void tcApply(s32, f32, f32, s32) __asm__("applyToObjectSubstructByFlag");

void tcImpl(u8 *arg0, f32 arg1) __asm__("transformCraftDualAnchorsAndApplyMotion");
void tcImpl(u8 *arg0, f32 arg1) {
    CraftMtx saved;
    CraftMtx rot;
    s32 i = 0;
    s32 r;

    do {
        if (tcPending(*(s32 *)(arg0 + 0x38)) == 1) {
            saved = *(CraftMtx *)arg0;
            tcBuild0(rot.m, *(s32 *)(arg0 + i * 4 + 0x6C));
            tcComp1(rot.m, *(s32 *)(arg0 + i * 4 + 0x64));
            tcXform(rot.m, &saved.m[3], (f32 *)(arg0 + 0xC));
            tcXform(rot.m, &saved.m[6], (f32 *)(arg0 + 0x18));
            r = tcLos(*(s32 *)(arg0 + 0x38));
            if (r == 1) {
                switch (i) {
                case 0:
                    tcApply(*(s32 *)(arg0 + 0x38), arg1, 0.0f, 0);
                    break;
                case 1:
                    tcApply(*(s32 *)(arg0 + 0x38), arg1, 0.0f, 1);
                    break;
                }
            }
            *(CraftMtx *)arg0 = saved;
        }
        i++;
    } while (i < 2);
}

typedef struct { s32 a, b, c; } EcV3i;
typedef struct { u8 pad0[0x44]; u16 h44; u8 b46; } EcAudio;
typedef struct { u8 pad0[0x1A8]; EcAudio *audio; } EcActor;
typedef struct {
    u8 pad0[0x38];
    EcActor *obj;
    u8 pad3C[0x24];
    f32 scale;
    f32 a64[2];
    f32 a6C[2];
    u8 pad74[0x5B];
    u8 type;
    u8 padD0[4];
    f32 fD4;
} EcObj;
typedef struct {
    u8 pad0[0x10];
    f32 off[2][3];
    f32 maxA[2];
    f32 minA[2];
    f32 maxB[2];
    f32 minB[2];
    u8 pad48[8];
} EcRow;
extern EcRow D_ec_8010AA04[] __asm__("D_mission_overlay_8010AA04");
extern f32 D_mission_overlay_8010A964[];
s32 isPendingChildNpcActive(EcActor *);
s32 computeActorAnchorDeltaAfterLOS(EcActor *);
void *getObjectMeshTransformOrLocal(EcActor *, void *);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void mat3x3InverseInto(void *, void *);
void transformVec3ByMat34(void *, void *, void *);
f32 vec3NormalizeInto(void *, void *);
void buildRotationMatrixSlot0(void *, f32);
void buildRotationMatrixSlot1(void *, f32);
void ecCompose1(void *, f32) __asm__("composeRotationMatrixSlot1");
f32 vec3Dot(void *, void *);
f32 vec3Length(void *);
f32 constMinusSinfApprox(f32);
void vec3Cross(void *, void *, void *);
f32 normalize_vector(void *);
void quatFromAxisAngle(void *, void *, f32);
void rotateVec3ByQuat(void *, void *, void *);
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
void factor5RemoveListNode(void *);

static __inline__ void ecRot(void *q, void *v, void *r) { rotateVec3ByQuat(q, v, r); }

void teImpl(EcObj *npc, f32 dt) __asm__("tickEnemyCraftWithDestruction");
void teImpl(EcObj *npc, f32 dt)
{
  s32 i;
  f32 ang;
  f32 lim;
  f32 b;
  f32 z;
  u8 snd;
  EcAudio *au;
  f32 mtx[12];
  f32 inv[12];
  f32 dir[4];
  f32 v98[4];
  f32 meshbuf[12];
  union 
  {
    struct 
    {
      f32 axis[4];
      f32 q[4];
      f32 cr[4];
      f32 t1[4];
      f32 t2[4];
    } a;
    struct 
    {
      f32 m[12];
      f32 r[4];
      f32 v[4];
      f32 axis[4];
      f32 q[4];
      f32 cr[4];
      f32 t1[4];
      f32 t2[4];
    } b;
  } u;
  for (i = 0; i < 2; i++)
  {
    if ((((u8) isPendingChildNpcActive(npc->obj)) == 1) && (((u8) computeActorAnchorDeltaAfterLOS(npc->obj)) == 1))
    {
      void *mesh;
      mesh = getObjectMeshTransformOrLocal(npc->obj, meshbuf);
      mat34CrossRowsAndCopyPos(mtx, npc, 1.0f);
      mat3x3InverseInto(inv, mtx);
      transformVec3ByMat34(inv, mesh, v98);
      v98[0] += D_ec_8010AA04[npc->type].off[i][0] * npc->scale;
      v98[1] += D_ec_8010AA04[npc->type].off[i][1] * npc->scale;
      v98[2] += D_ec_8010AA04[npc->type].off[i][2] * npc->scale;
      vec3NormalizeInto(dir, v98);
      buildRotationMatrixSlot0(mtx, npc->a6C[i]);
      ecCompose1(mtx, npc->a64[i]);
      transformVec3ByMat34(mtx, D_mission_overlay_8010A964, v98);
      ang = constMinusSinfApprox(vec3Dot(v98, dir)) * 57.29578f;
      if (!(0.001f < ang))
      {
        goto off;
      }
      snd = 0;
      if (10.0f < ang)
      {
        snd = 1;
      }
      lim = npc->fD4 * (dt * 30.0f);
      if (lim < ang)
      {
        ang = lim;
      }
      vec3Cross(u.a.axis, v98, dir);
      normalize_vector(u.a.axis);
      quatFromAxisAngle(u.a.q, u.a.axis, ang);
      rotateVec3ByQuat(u.a.q, v98, dir);
      u.a.axis[1] = 0.0f;
      u.a.axis[0] = dir[0];
      u.a.axis[2] = dir[2];
      ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A964, u.a.axis) / (vec3Length(D_mission_overlay_8010A964) * vec3Length(u.a.axis))) * 57.29578f;
      *((EcV3i *) u.a.t1) = *((EcV3i *) D_mission_overlay_8010A964);
      u.a.t1[1] = 0.0f;
      *((EcV3i *) u.a.t2) = *((EcV3i *) u.a.axis);
      u.a.t2[1] = 0.0f;
      vec3Cross(u.a.cr, u.a.t1, u.a.t2);
      z = 0.0f;
      __asm__("" : "+f"(z));
      if (!(z <= u.a.cr[1]))
      {
        ang = -ang;
      }
      buildRotationMatrixSlot1(mtx, -ang);
      transformVec3ByMat34(mtx, dir, u.a.axis);
      u.a.axis[0] = z;
      npc->a64[i] = ang;
      b = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A964, u.a.axis) / (vec3Length(D_mission_overlay_8010A964) * vec3Length(u.a.axis))) * 57.29578f;
      if (!(u.a.axis[1] <= z))
      {
        b = -b;
      }
      npc->a6C[i] = b;
      if (D_ec_8010AA04[npc->type].maxA[i] < npc->a64[i])
      {
        npc->a64[i] = D_ec_8010AA04[npc->type].maxA[i];
        snd = 0;
      }
      else
        if (npc->a64[i] < D_ec_8010AA04[npc->type].minA[i])
      {
        npc->a64[i] = D_ec_8010AA04[npc->type].minA[i];
        snd = 0;
      }
      if (D_ec_8010AA04[npc->type].maxB[i] < npc->a6C[i])
      {
        npc->a6C[i] = D_ec_8010AA04[npc->type].maxB[i];
        snd = 0;
      }
      else
        if (npc->a6C[i] < D_ec_8010AA04[npc->type].minB[i])
      {
        npc->a6C[i] = D_ec_8010AA04[npc->type].minB[i];
        snd = 0;
      }
      if (snd != 0)
      {
        au = npc->obj->audio;
        if (au->b46 == 0)
        {
          au->b46 = 1;
          au->h44 = 0x2000;
          switch (npc->type)
          {
            case 0:
              play3DSoundEventVariant(au, npc, ((u8 *) npc) + 0x24, 8.0f, 0.1f, 7, 0x4B, 1, 0x7F, 0x28);
              break;

            case 1:
              play3DSoundEventVariant(au, npc, ((u8 *) npc) + 0x24, 8.0f, 0.1f, 7, 0x4B, 1, 0x7F, 0x28);
              break;

            case 2:
              play3DSoundEventVariant(au, npc, ((u8 *) npc) + 0x24, 8.0f, 0.1f, 7, 0x4B, 1, 0x7F, 0x28);
              break;

          }

        }
      }
      continue;
    }
    else
    {
      buildRotationMatrixSlot0(u.b.m, npc->a6C[i]);
      ecCompose1(u.b.m, npc->a64[i]);
      transformVec3ByMat34(u.b.m, D_mission_overlay_8010A964, u.b.v);
      ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A964, u.b.v)) * 57.29578f;
      if (!(0.001f < ang))
      {
        goto off;
      }
      {
        if (10.0f < ang)
        {
          au = npc->obj->audio;
          if (au->b46 == 0)
          {
            au->b46 = 1;
            au->h44 = 0x2000;
            switch (npc->type)
            {
              case 0:
                play3DSoundEventVariant(au, npc, ((u8 *) npc) + 0x24, 8.0f, 0.1f, 7, 0x4B, 1, 0x7F, 0x28);
                break;

              case 1:
                play3DSoundEventVariant(au, npc, ((u8 *) npc) + 0x24, 8.0f, 0.1f, 7, 0x4B, 1, 0x7F, 0x28);
                break;

              case 2:
                play3DSoundEventVariant(au, npc, ((u8 *) npc) + 0x24, 8.0f, 0.1f, 7, 0x4B, 1, 0x7F, 0x28);
                break;

            }

          }
        }
        if (ang)
        {
          lim = npc->fD4 * (dt * 30.0f);
        }
        else
        {
          lim = npc->fD4 * (dt * 30.0f);
        }
        if (lim < ang)
        {
          ang = lim;
        }
        vec3Cross(u.b.axis, u.b.v, D_mission_overlay_8010A964);
        normalize_vector(u.b.axis);
        quatFromAxisAngle(u.b.q, u.b.axis, ang);
        ecRot(u.b.q, u.b.v, u.b.r);
        u.b.axis[1] = 0.0f;
        u.b.axis[0] = u.b.r[0];
        u.b.axis[2] = u.b.r[2];
        ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A964, u.b.axis) / (vec3Length(D_mission_overlay_8010A964) * vec3Length(u.b.axis))) * 57.29578f;
        *((EcV3i *) u.b.t1) = *((EcV3i *) D_mission_overlay_8010A964);
        u.b.t1[1] = 0.0f;
        *((EcV3i *) u.b.t2) = *((EcV3i *) u.b.axis);
        u.b.t2[1] = 0.0f;
        vec3Cross(u.b.cr, u.b.t1, u.b.t2);
        z = 0.0f;
        __asm__("" : "+f"(z));
        if (!(z <= u.b.cr[1]))
        {
          ang = -ang;
        }
        buildRotationMatrixSlot1(u.b.m, -ang);
        transformVec3ByMat34(u.b.m, u.b.r, u.b.axis);
        u.b.axis[0] = z;
        npc->a64[i] = ang;
        b = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A964, u.b.axis) / (vec3Length(D_mission_overlay_8010A964) * vec3Length(u.b.axis))) * 57.29578f;
        if (!(u.b.axis[1] <= z))
        {
          b = -b;
        }
        npc->a6C[i] = b;
        continue;
      }
    }
    off:
    au = npc->obj->audio;

    if (au->b46 == 1)
    {
      au->b46 = 0;
      factor5RemoveListNode(au);
    }
  }

}

typedef struct {
    u8 pad0[0x4C];
    u32 flags;
    f32 f50, f54, f58;
    f32 f5C, f60, f64;
    f32 q68[4];
    f32 f78, f7C, f80;
} DeDef;

typedef struct {
    u8 pad0[0x30];
    u8 *mesh;
    u8 pad34[8];
    u8 *objA[2];
    u8 *objB[2];
    DeDef *defA[2];
    DeDef *defB[2];
    f32 f5C;
    f32 scale;
    f32 angA[2];
    f32 angB[2];
    u8 pad74[0x5B];
    u8 type;
    u8 padD0[0x14];
    f32 aE4[2];
} DeObj;

extern void deClear(void *) __asm__("clearVec4QuadStruct");
extern void deAdd(void *, f32, f32, f32) __asm__("addVec3At0x24");
extern void deScale(void *, f32, f32, f32) __asm__("applyScaleToMat3x4");
extern void deQuat(void *, void *) __asm__("composeQuatToMat3x4");
extern void deRot0(void *, f32) __asm__("composeRotationMatrixSlot0");
extern void deRot1(void *, f32) __asm__("composeRotationMatrixSlot1");
extern void deMat(void *, void *, f32) __asm__("mat34CrossRowsAndCopyPos");

#define DE_TAIL(d, m)                                                  \
    {                                                                  \
        u32 fl = d->flags;                                             \
        if ((fl & 9) == 9) {                                           \
            deAdd(m, d->f78 + d->f50, d->f7C + d->f54, d->f80 + d->f58); \
        } else if ((fl & 9) == 8) {                                    \
            deAdd(m, d->f78, d->f7C, d->f80);                          \
        } else if (fl & 1) {                                           \
            deAdd(m, d->f50, d->f54, d->f58);                          \
        }                                                              \
    }

void deImpl(DeObj *o, f32 dt) __asm__("func_mission_overlay_800DE4EC");
void deImpl(DeObj *o, f32 dt) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (o->objA[i] != NULL) {
            u8 *m = o->objA[i] + 0x1C;
            DeDef *d = o->defA[i];
            deClear(m);
            if (d->flags & 1) {
                deAdd(m, -d->f50, -d->f54, -d->f58);
            }
            if (d->flags & 2) {
                deScale(m, d->f5C, d->f60, d->f64);
            }
            if (d->flags & 4) {
                deQuat(m, d->q68);
            }
            deRot1(m, o->angA[i]);
            DE_TAIL(d, m)
        }
        if (o->objB[i] != NULL) {
            u8 *m = o->objB[i] + 0x1C;
            DeDef *d = o->defB[i];
            deClear(m);
            if (d->flags & 1) {
                deAdd(m, -d->f50, -d->f54, -d->f58);
            }
            if (d->flags & 2) {
                deScale(m, d->f5C, d->f60, d->f64);
            }
            if (d->flags & 4) {
                deQuat(m, d->q68);
            }
            deAdd(m, 0.0f, 0.0f, -o->aE4[i] * ((struct { u8 p[0x48]; f32 v; } *)((o->type * 0x50 + i * 4) + (s32)D_ec_8010AA04))->v);
            deRot0(m, o->angB[i]);
            DE_TAIL(d, m)
        }
    }
    deMat(o->mesh + 0x28, o, o->scale);
}

typedef struct { f32 x, y, z; } GVec3;
typedef struct {
    GVec3 pos;
    GVec3 fwd;
    GVec3 up;
    GVec3 vel;
    u8 *mesh;
    u8 *rec;
    s32 obj;
    u8 *node0[2];
    u8 *node1[2];
    u8 *mat0[2];
    u8 *mat1[2];
    f32 radius;
    f32 scale;
    s32 a64[2];
    s32 a6C[2];
    u16 slot74;
    u16 slot76;
    u16 slot78;
    u16 slot7A;
    u8 *ctx;
    f32 phase;
    f32 rate;
    u8 audio[0x44];
    u16 sCC;
    u8 audioOn;
    u8 type;
    s8 outCount;
    u8 mode;
    u16 sD2;
    f32 fD4;
    s32 iD8;
    f32 aDC[2];
    f32 aE4[2];
} GtObj;
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    u16 u18;
    u16 u1A;
} GtParam;
extern GtParam D_mission_overlay_8010A970[];
typedef struct { s32 a[2]; s32 b[2]; u8 pad[0x40]; } GtNames;
extern GtNames D_mission_overlay_8010AA04[];
extern s32 D_mission_overlay_8010A960[];
extern u16 D_main_bss_80139560[];
extern u16 D_main_bss_80139574;
extern u8 D_main_bss_80130B39;
extern f32 D_main_bss_80130BA4;
extern f32 D_mission_overlay_8010C0A0_f __asm__("D_mission_overlay_8010C0A0");
extern s32 gCurrentLevel;
s16 rand(void);
f32 sinf(f32);
u8 *walkMeshdef0List(char *);
void composeEulerRotationXYZ(void *, s32, s32, s32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, s32);
void composeRotationMatrixSlot1(void *, s32);
void composeRotationMatrixSlot2(void *, s32);
void addVec3At0x24(void *, f32, f32, f32);
u16 popNpcSlotFromTail(u16, void *);
u8 *lookupHmtMaterialByName(void *, s32, void *);
void createAndInitObject(void *, s32, void *, void *, s32);
s32 getLevelDatItemByName(char *);
void initActorAsType1(s32, s32, s32, s32, f32, f32, s32);
void setType1ActorField40(s32, s32);
void updateObjectFlags110(s32, s32, s32);
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
u8 *allocateAndInitCraftNpcContext(f32, f32, u16);
void dispatchDatSubtypeByRandomIndex(void *, void *);
void factor5RemoveListNode(void *);
void walkDatTreeAndCollectSubtypes(void *, void *);
void rs_free(void *);
s32 getNpcCurrentHealth(s32);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void releaseMeshAsset(void *);
void func_mission_overlay_800AA6D0(void *, f32, void *);
void dispatchEffectByActorType(s32, f32);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void transformVec3ByMat34(void *, void *, void *);
void func_mission_overlay_800DE4EC(void *, f32);
s32 func_mission_overlay_800EFDE0(s32, s32, s32, f32);
void tickEnemyCraftWithDestruction(void *, f32);
void transformCraftDualAnchorsAndApplyMotion(void *, f32);
void composeRandomRotationMatrix(void *, void *, f32, s32, s32, s32);
void scaleVec3ByRandomRange(void *, f32, f32);
void spawnDebris1Npc(void *, void *, f32, f32, f32);
void spawnDestructionEffectBurst(void *, s32, f32, f32, f32, f32);
void zmemcpy(void *, void *, s32);
void gameStateByteGatedNpcHelper(s32, void *, s32, f32, f32, f32);
void spawnSplineWalkerCraft(void *, f32, f32, s32);
void spawnNpcType0xAFromTemplate(void *, f32);
void destroyNpcSlotByIndex(u16);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyObjectOwnedNpcSlot(s32);
void walkDatTreeAndScaleLeafByFloat(void *, void *, s32);
void updateActive3DAudioSource(void *, void *, void *, s32);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
void walkDatTreeAndVisitChildren(void *, void *, void *);
void advanceNpcOnCurvedPath(s32, s32, void *, void *);
void extrapolateNpcPositionForCurrentMode(void *);
s32 getObjectDetailLevel(s32);
void func_mission_overlay_800EFD6C(s32);
s32 dealDamageToNpc(s32, u16);
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
s32 clearPendingChildNpc(s32);
void setObjectFlagBit4(void *);
s32 getPlayerField2(s32);
void playSpeechClip(s32, s32, f32, s32);
void setType1ActorParams(s32, s32, u8, u8, u8, s32);
void dispatchSlotAction5IfActive(void *, void *);

s32 npcGroundTransportUpdate(u8 *arg0, u16 action, u8 *arg2) {
    GtObj *s1 = *(GtObj **)(arg0 + 4);
    f32 sp[20];
    u8 *rec;
    u8 *sub;
    u8 *a4;
    u8 *a5;
    u8 *a9;
    f32 dt;
    char *name;
    s32 i;

    switch (action) {
    case 1:
        {
        u8 *sb1;
        rec = arg2;
        s1->rec = arg2;
        name = NULL;
        switch (*(u16 *)rec) {
        case 0x2B:
            s1->type = 0;
            name = "reb_transport";
            break;
        case 0x2D:
            s1->type = 1;
            name = "cargo_v01";
            break;
        case 0x2E:
            s1->type = 2;
            name = "r_combat";
            break;
        }
        s1->mesh = walkMeshdef0List(name);
        *(s32 **)(s1->mesh + 4) = D_mission_overlay_8010A960;
        s1->pos.x = *(f32 *)(rec + 0x10);
        s1->pos.y = *(f32 *)(rec + 0x14);
        s1->pos.z = *(f32 *)(rec + 0x18);
        composeEulerRotationXYZ(s1, *(s32 *)(rec + 0x1C), *(s32 *)(rec + 0x20), *(s32 *)(rec + 0x24));
        s1->vel.x = s1->vel.y = s1->vel.z = 0.0f;
        {
            f32 one = 1.0f;
            f32 inv = one / *(f32 *)(*(u8 **)s1->mesh + 0x34);
            s1->scale = inv * *(f32 *)(rec + 0x28);
            initVec4TripletFromArgs(s1->mesh + 0x28, inv * *(f32 *)(rec + 0x28), inv * *(f32 *)(rec + 0x2C), inv * *(f32 *)(rec + 0x30));
            composeRotationMatrixSlot0(s1->mesh + 0x28, *(s32 *)(rec + 0x1C));
            composeRotationMatrixSlot1(s1->mesh + 0x28, *(s32 *)(rec + 0x20));
            composeRotationMatrixSlot2(s1->mesh + 0x28, *(s32 *)(rec + 0x24));
            addVec3At0x24(s1->mesh + 0x28, s1->pos.x, s1->pos.y, s1->pos.z);
            s1->radius = *(f32 *)(*(u8 **)s1->mesh + 0x44) * s1->scale;
            *(GtObj **)(arg0 + 8) = s1;
            *(u8 **)(arg0 + 0xC) = s1->mesh;
            {
                u8 *b = (u8 *)D_main_bss_80139560;
                s32 o;
                s1->slot74 = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
                o = 0x2C;
                if (*(s32 *)(rec + 0xA8) == 1) {
                    o = 0x2E;
                }
                s1->slot76 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            }
            s1->outCount = 0;
            s1->phase = ((f32)(rand() & 0x7F) - 64.0f) / 64.064064f;
            s1->rate = one;
        }
        for (i = 0; i < 2; i++) {
            s32 n = D_mission_overlay_8010AA04[s1->type].a[i];
            if (n != 0) {
                s1->node0[i] = lookupHmtMaterialByName(s1->mesh, n, &s1->mat0[i]);
            } else {
                s1->node0[i] = NULL;
            }
            n = D_mission_overlay_8010AA04[s1->type].b[i];
            if (n != 0) {
                s1->node1[i] = lookupHmtMaterialByName(s1->mesh, n, &s1->mat1[i]);
            } else {
                s1->node1[i] = NULL;
            }
        }
        {
            u8 *b = (u8 *)D_main_bss_80139560;
            s32 o;
            o = 0x12;
            if (*(s32 *)(rec + 0xA8) == 1) {
                o = 0xE;
            }
            s1->slot78 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            if (*(s32 *)(rec + 0xAC) != 0) {
                s32 o2 = 0x18;
                if (*(s32 *)(rec + 0xA8) == 1) {
                    o2 = 0x1A;
                }
                s1->slot7A = popNpcSlotFromTail(*(u16 *)(o2 + b), arg0);
            } else {
                s1->slot7A = 0xFFFF;
            }
        }
        createAndInitObject(&s1->obj, 0x80, arg0, npcInitFullModel, 0);
        sb1 = *(u8 **)(s1->obj + 0x1A8);
        sb1[0x46] = 0;
        s1->audioOn = 0;
        name = (char *)(*(s32 *)(rec + 0x8C) + (s32)rec);
        if (*name != '-') {
            s32 item = getLevelDatItemByName(name);
            u8 *r = s1->rec;
            initActorAsType1(s1->obj, item, s1->iD8, *(s32 *)(r + 0x9C), *(f32 *)(r + 0x94), *(f32 *)(s1->rec + 0x98), 0);
            setType1ActorField40(s1->obj, *(s32 *)(s1->rec + 0xA0));
            updateObjectFlags110(s1->obj, 0x17, 0);
            s1->audioOn = 1;
            s1->sCC = 0x2000;
            switch (s1->type) {
            case 0:
                play3DSoundEventVariant(s1->audio, s1, &s1->vel, 5.0f, 0.4f, 0xF, 0x4C, 1, 0x50, 0);
                break;
            case 1:
                play3DSoundEventVariant(s1->audio, s1, &s1->vel, 5.0f, 0.1f, 0xF, 0x4C, 1, 0x50, 0);
                break;
            case 2:
                play3DSoundEventVariant(s1->audio, s1, &s1->vel, 8.0f, 0.6f, 0xF, 0x4C, 1, 0x78, 0);
                break;
            }
        }
        {
            GtParam *t = D_mission_overlay_8010A970;
            s1->ctx = allocateAndInitCraftNpcContext(t[s1->type].fC * s1->scale, t[s1->type].f8 * s1->scale, t[s1->type].u1A);
            *(f32 *)(s1->ctx + 0x14) = t[s1->type].f0;
            *(f32 *)(s1->ctx + 4) = t[s1->type].f10 * s1->scale;
            *(f32 *)(s1->ctx + 0x10) = t[s1->type].f4;
            *(f32 *)(s1->ctx + 0x18) = t[s1->type].f14;
        }
        dispatchDatSubtypeByRandomIndex(sb1 + 0x48, s1->mesh);
        return 1;
        }
    case 2:
        sub = *(u8 **)(s1->obj + 0x1A8);
        if (sub[0x46] == 1) {
            sub[0x46] = 0;
            factor5RemoveListNode(sub);
        }
        if (s1->audioOn == 1) {
            s1->audioOn = 0;
            factor5RemoveListNode(s1->audio);
        }
        walkDatTreeAndCollectSubtypes(sub + 0x48, s1->mesh);
        if (s1->ctx != NULL) {
            rs_free(s1->ctx);
        }
        initActorRenderDescriptorIfUninit(s1->obj, getNpcCurrentHealth(s1->obj) < 1, s1->rec, 0, s1->rec + 0x70);
        clearPendingAndDestroyChildNpc(&s1->obj);
        releaseMeshAsset(s1->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        sub = *(u8 **)(s1->obj + 0x1A8);
        {
            f32 inc = dt * 4.0f;
            s32 j;
            for (j = 0; j < 2; j++) {
                if (s1->aDC[j] < 1.0f) {
                    s1->aDC[j] += inc;
                    if (1.0f < s1->aDC[j]) {
                        s1->aDC[j] = 1.0f;
                        s1->aE4[j] = 0.0f;
                    } else if (s1->aDC[j] < 0.2f) {
                        s1->aE4[j] = s1->aDC[j] * 5.0f;
                    } else {
                        s1->aE4[j] = 1.0f - (s1->aDC[j] - 0.2f) * 1.25f;
                    }
                }
            }
        }
        switch (s1->mode) {
        case 0:
            s1->mode = 1;
        case 1:
            func_mission_overlay_800AA6D0(s1, dt, s1->rec + 0x34);
            dispatchEffectByActorType(s1->obj, dt);
            s1->phase += dt * s1->rate;
            if (s1->phase > 1.0f) {
                s1->phase -= 2.0f;
            }
            mat34CrossRowsAndCopyPos(sp, s1, 1.0f);
            sp[11] = 0.0f;
            sp[10] = 0.0f;
            sp[9] = 0.0f;
            sp[14] = 0.0f;
            sp[12] = 0.0f;
            sp[13] = sinf(s1->phase * 3.1415927f) * *(f32 *)(s1->rec + 0xA4) * 0.25f;
            transformVec3ByMat34(sp, &sp[12], &sp[16]);
            s1->pos.x += sp[16];
            s1->pos.y += sp[17];
            s1->pos.z += sp[18];
            func_mission_overlay_800DE4EC(s1, dt);
            func_mission_overlay_800EFDE0(s1->obj, *(s32 *)(s1->rec + 0xB0), *(s32 *)(s1->rec + 0xB4), dt);
            tickEnemyCraftWithDestruction(s1, dt);
            transformCraftDualAnchorsAndApplyMotion(s1, dt);
            break;
        case 2:
            func_mission_overlay_800DE4EC(s1, dt);
            switch (s1->type) {
            case 0:
            case 1:
                {
                    register s32 k asm("$16");
                    s32 n = (rand() & 1) + 2;
                    for (k = 0; k < n; ) {
                        composeRandomRotationMatrix(sp, &sp[4], s1->radius * 0.5f, 0x5A, 0, 0);
                        sp[0] += s1->pos.x + s1->fwd.x * s1->radius / 1.5f;
                        sp[1] += s1->pos.y + s1->fwd.y * s1->radius / 1.5f;
                        sp[2] += s1->pos.z + s1->fwd.z * s1->radius / 1.5f;
                        scaleVec3ByRandomRange(&sp[4], 3.0f, 4.0f);
                        spawnDebris1Npc(sp, &sp[4], 30.0f, 0.8f, 0.3f);
                        composeRandomRotationMatrix(sp, &sp[4], s1->radius * 0.5f, 0x5A, 0, 0);
                        sp[0] += s1->pos.x - s1->fwd.x * s1->radius / 1.5f;
                        sp[1] += s1->pos.y - s1->fwd.y * s1->radius / 1.5f;
                        sp[2] += s1->pos.z - s1->fwd.z * s1->radius / 1.5f;
                        k++;
                        scaleVec3ByRandomRange(&sp[4], 3.0f, 4.0f);
                        spawnDebris1Npc(sp, &sp[4], 30.0f, 0.8f, 0.3f);
                    }
                }
                spawnDestructionEffectBurst(s1, 0xFFFF, 1.0f, 0.7f, 1.2f, 0.5f);
                zmemcpy(&sp[8], s1, 0x30);
                sp[17] = s1->radius * 0.4f;
                sp[18] = s1->radius * 0.4f;
                sp[19] = s1->radius * 0.9f;
                gameStateByteGatedNpcHelper(2, &sp[8], 0, s1->radius, s1->radius * 1.5f, 0.35f);
                spawnSplineWalkerCraft(s1, D_mission_overlay_8010A970[s1->type].fC * s1->scale * 4.0f, D_mission_overlay_8010A970[s1->type].f8 * s1->scale * 1.5f, 0xC);
                break;
            default:
                {
                    s32 k;
                    s32 n = (s16)(rand() % 3) + 3;
                    for (k = 0; k < n; k++) {
                        composeRandomRotationMatrix(sp, &sp[4], s1->radius * 0.5f, 0x5A, 0, 0);
                        sp[0] += s1->pos.x;
                        sp[1] += s1->pos.y;
                        sp[2] += s1->pos.z;
                        scaleVec3ByRandomRange(&sp[4], 3.0f, 4.0f);
                        spawnDebris1Npc(sp, &sp[4], 30.0f, 0.8f, 0.3f);
                    }
                }
                spawnDestructionEffectBurst(s1, 0xFFFF, 1.0f, 0.7f, 1.2f, 0.5f);
                zmemcpy(&sp[8], s1, 0x30);
                sp[17] = s1->radius * 0.8f;
                sp[18] = s1->radius * 0.4f;
                sp[19] = s1->radius * 0.8f;
                gameStateByteGatedNpcHelper(2, &sp[8], 0, s1->radius, s1->radius * 1.5f, 0.35f);
                spawnSplineWalkerCraft(s1, D_mission_overlay_8010A970[s1->type].fC * s1->scale * 2.5f, D_mission_overlay_8010A970[s1->type].f8 * s1->scale * 1.5f, 0xC);
                break;
            }
            spawnNpcType0xAFromTemplate(s1, s1->radius * 5.0f);
            switch (s1->type) {
            case 0:
                play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.5f, 0, 0x21, 0x7D, 0x50);
                break;
            case 1:
                play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.5f, 0, 0x21, 0x7D, 0x50);
                break;
            case 2:
                play3DSoundEvent(0, s1, &s1->vel, 24.0f, 0.5f, 0, 0x22, 0x7D, 0x50);
                break;
            }
        destroy:
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        if (isNpcWithinActiveReferenceRange(s1) != 0) {
            s1->outCount = 0;
        } else if (*(s32 *)(s1->rec + 0x88) == 0) {
            s1->outCount = 0;
        } else {
            s1->outCount++;
            if (s1->outCount >= 0x15) {
                goto destroy;
            }
        }
        destroyObjectOwnedNpcSlot(s1->obj);
        if (sub[0x48] != 0xFF) {
            walkDatTreeAndScaleLeafByFloat(sub + 0x48, s1->mesh, *(s32 *)arg2);
            return 1;
        }
        return 1;
    case 4:
        a4 = arg2;
        sub = *(u8 **)(s1->obj + 0x1A8);
        if (sub[0x46] != 0) {
            updateActive3DAudioSource(sub, s1, &s1->vel, 0x7F);
        }
        if (s1->audioOn != 0) {
            updateActive3DAudioSource(s1->audio, s1, &s1->vel, 0x7F);
        }
        if (addNpcToVisibilityBucket(*(s32 *)arg2, s1->mesh, s1, s1->radius) != 0 && sub[0x48] != 0xFF) {
            walkDatTreeAndVisitChildren(sub + 0x48, s1->mesh, arg2);
        }
        if (s1->ctx != NULL) {
            advanceNpcOnCurvedPath(*(s32 *)(a4 + 8), *(s32 *)a4, s1, s1->ctx);
            return 1;
        }
        return 1;
    case 5:
        a5 = arg2;
        if (getNpcCurrentHealth(s1->obj) > 0) {
            extrapolateNpcPositionForCurrentMode(arg2);
            switch (s1->type) {
            case 0:
                play3DSoundEvent(0, s1, &s1->vel, 20.0f, 0.5f, 0, 0x2A, 0x78, 0x50);
                break;
            case 1:
                play3DSoundEvent(0, s1, &s1->vel, 20.0f, 0.5f, 0, 0x2A, 0x78, 0x50);
                break;
            case 2:
                play3DSoundEvent(0, s1, &s1->vel, 20.0f, 0.5f, 0, 0x2A, 0x78, 0x50);
                break;
            }
            if (getObjectDetailLevel(s1->obj) == 1 && D_main_bss_80130B39 == 0) {
                func_mission_overlay_800EFD6C(0x1F4);
            }
            if (dealDamageToNpc(s1->obj, *(u16 *)(a5 + 6)) <= 0) {
                s1->mode = 2;
                unregisterAndFreeNpcSlot(s1->slot74, arg0);
                unregisterAndFreeNpcSlot(s1->slot76, arg0);
                unregisterAndFreeNpcSlot(s1->slot78, arg0);
                if (s1->slot7A != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s1->slot7A, arg0);
                }
                popNpcSlotFromTail(D_main_bss_80139574, arg0);
                {
                    u8 *r = s1->rec;
                    datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s1->rec + 0x84));
                }
                tallyMidDetailObject(arg0);
                clearPendingChildNpc(s1->obj);
                setObjectFlagBit4(arg0);
                {
                    u8 *p = *(u8 **)(s1->obj + 0x1A8);
                    if (p[0x46] == 1) {
                        p[0x46] = 0;
                        factor5RemoveListNode(p);
                    }
                }
                if (s1->audioOn == 1) {
                    s1->audioOn = 0;
                    factor5RemoveListNode(s1->audio);
                }
            } else if (gCurrentLevel != 0x14 && *(u16 *)(a5 + 2) != 0xFFFF && getObjectDetailLevel(s1->obj) == 0 && *(u16 *)(a5 + 2) == (u16)getPlayerField2(0) && D_mission_overlay_8010C0A0_f < D_main_bss_80130BA4) {
                D_mission_overlay_8010C0A0_f = D_main_bss_80130BA4 + 20.0f;
                playSpeechClip(0x217, 0x73, 0.0f, 0);
            }
        }
        if (*(u16 *)a5 != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)a5);
            return 1;
        }
        return 1;
    case 9:
        {
        s32 obj;
        a9 = arg2;
        obj = s1->obj;
        switch (arg2[0x18]) {
        case 1:
            setType1ActorParams(s1->obj, *(s32 *)arg2, arg2[9], arg2[0xA], arg2[8], *(s32 *)(arg2 + 4));
            return 1;
        case 2:
        case 3:
            break;
        case 8:
            if (getNpcCurrentHealth(obj) > 0) {
                u8 *b;
                s32 o;
                unregisterAndFreeNpcSlot(s1->slot76, arg0);
                b = (u8 *)D_main_bss_80139560;
                o = 0x2C;
                if (*(s32 *)arg2 == 1) {
                    o = 0x2E;
                }
                s1->slot76 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                unregisterAndFreeNpcSlot(s1->slot78, arg0);
                o = 0x12;
                if (*(s32 *)arg2 == 1) {
                    o = 0xE;
                }
                s1->slot78 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                if (s1->slot7A != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s1->slot7A, arg0);
                    if (*(s32 *)(s1->rec + 0xAC) != 0) {
                        o = 0x18;
                        if (*(s32 *)arg2 == 1) {
                            o = 0x1A;
                        }
                        s1->slot7A = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    }
                }
                setObjectDetailLevel(s1->obj, *(s32 *)a9);
                return 1;
            }
            return 1;
        default:
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

extern s32 D_mission_overlay_8010C0A0;

void resetCraftSubsystemGlobal(void) {
    D_mission_overlay_8010C0A0 = 0;
}

void func_mission_overlay_800DFB84(void) {
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0DDED0", fake_func_800DFB8C);
