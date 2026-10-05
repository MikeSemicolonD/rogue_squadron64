#include "common.h"
#include "common_types.h"

extern f32 D_mission_overlay_8010A6A4[];
extern u8 D_mission_overlay_8010A6B8[];
extern f32 D_mission_overlay_8010A6BC[];
extern u8 D_mission_overlay_8010A6C4[];
extern f32 D_mission_overlay_8010A6C8[];
extern u8 D_mission_overlay_8010A6D8[];
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void advanceAtStEffectPhaseSound(u8 *arg0, f32 arg1, u8 arg2) {
    f32 *tab;
    u8 *flags;
    f32 t;
    u8 idx;
    switch (*(s16 *)(arg0 + 0x7E)) {
    case 0:
        tab = D_mission_overlay_8010A6A4;
        flags = D_mission_overlay_8010A6B8;
        break;
    case 1:
        tab = D_mission_overlay_8010A6BC;
        flags = D_mission_overlay_8010A6C4;
        break;
    case 2:
        tab = D_mission_overlay_8010A6C8;
        flags = D_mission_overlay_8010A6D8;
        break;
    default:
        return;
    }
    t = *(f32 *)(arg0 + 0xAC) + (arg1 / *(f32 *)(arg0 + 0x98));
    *(f32 *)(arg0 + 0xAC) = t;
    if (t > 1.0f) {
        arg0[0xFB] = 0;
        *(f32 *)(arg0 + 0xAC) = *(f32 *)(arg0 + 0x94);
        *(f32 *)(arg0 + 0xB0) = tab[0];
    }
    if (!arg2 && *(f32 *)(arg0 + 0xAC) >= *(f32 *)(arg0 + 0xB0)) {
        idx = arg0[0xFB];
        arg0[0xFB] = idx + 1;
        if (flags[idx] == 0) {
            play3DSoundEvent(0, arg0, arg0 + 0x24, 18.0f, 0.6f, 0, 5, 0x78, 0x32);
        } else {
            play3DSoundEvent(0, arg0, arg0 + 0x24, 16.0f, 0.5f, 0, 6, 0x78, 0x32);
        }
        *(f32 *)(arg0 + 0xB0) = tab[arg0[0xFB]];
    }
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A700C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A7010);

struct CfObj { u8 pad0[4]; f32 f4; u8 pad8[0x1C]; u8 pos[0xC]; s32 f30; u8 *f34; s32 f38; u8 pad3C[0x28]; s32 f64; u8 pad68[4]; f32 f6C; };
typedef struct { u8 pad0[4]; struct CfObj *obj; } CfActor;
extern u8 D_mission_overlay_800A700C[];
extern u8 D_mission_overlay_800A7010[];
extern u8 D_mission_overlay_8010A698[];
extern s32 D_main_bss_80137CE4;
s32 lookupHmtTextureByName(s32, u8 *, s32, u8 *, s32, s32);
s32 setObjectSubstructF10IfReady(s32, f32, s32);
s32 tickProgressChannel(s32, u8 *, s32, f32 *);
s32 resolveNpcAttachmentPos(s32, u8 *, f32, f32);
s32 generatePerpEmitDirectionWithJitter(s32, u8 *, s32);
s32 triggerCueWithSlotEffect(s32, s32, u8 *, u8 *, s32, f32, f32);
s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
s32 tickAtStCannonFireEffect(CfActor *arg0, s32 arg1) {
    u8 buf[0x30];
    f32 sp58;
    struct CfObj *o = arg0->obj;
    f32 fv;
    s32 r;
    if (arg1 == 0) {
        lookupHmtTextureByName(o->f30, D_mission_overlay_800A700C, 0, buf, 0, 0);
        setObjectSubstructF10IfReady(o->f38, 0.06666667f, 0);
        o->f6C = ((f32 *)buf)[1] - o->f4;
        o->f64 = 0;
    } else {
        lookupHmtTextureByName(o->f30, D_mission_overlay_800A7010, 0, buf, 0, 0);
    }
    fv = *(f32 *)(o->f34 + D_main_bss_80137CE4 * 4 + 0xD8);
    if (fv != 0.0f) {
        resolveNpcAttachmentPos(o->f38, buf, 10.0f, fv);
    }
    generatePerpEmitDirectionWithJitter(o->f38, buf, 0);
    r = tickProgressChannel(o->f38, buf, 0, &sp58) & 0xFF;
    if (r == 1) {
        triggerCueWithSlotEffect(o->f38, 3, buf, D_mission_overlay_8010A698, r, 10.0f, sp58);
        play3DSoundEvent(0, o, o->pos, 20.0f, 0.4f, 0, 0xD, 0x78, 0x28);
    }
    return 0;
}

extern f32 D_mission_overlay_8010A68C[];
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
void *getObjectMeshTransformOrLocal(s32, void *);
s32 isPendingChildNpcActive(s32);
s32 computeActorAnchorDeltaAfterLOS(s32);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void mat3x3InverseInto(void *, void *);
void transformVec3ByMat34(void *, void *, void *);
void vec3NormalizeInto(void *, void *);
void buildRotationMatrixSlot0(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
void buildRotationMatrixSlot1(void *, f32);
f32 constMinusSinfApprox(f32);
f32 vec3Dot(void *, void *);
f32 vec3Length(void *);
void vec3Cross(void *, void *, void *);
void normalize_vector(void *);
void quatFromAxisAngle(void *, void *, f32);
void rotateVec3ByQuat(void *, void *, void *);
void factor5RemoveListNode(void *);

typedef struct { f32 x, y, z; } AkV3;
typedef struct { f32 x, y, z, w; } AkV4;
typedef struct { u8 pad0[0x24]; u8 p24[0x14]; s32 f38; u8 pad3C[0x1C]; f32 f58; f32 f5C; f32 f60; u8 pad64[8]; f32 f6C; u8 pad70[0x44]; u8 pB4[0x44]; u8 fF8; } AkBody;

void updateAtStBodyKinematics(AkBody *self, f32 dt) {
    f32 m28[12];
    f32 m58[12];
    AkV4 v88;
    AkV4 v98;
    f32 mA8[12];
    u8 a;
    s32 b;
    f32 *t;
    f32 ang;
    f32 lim;
    f32 ang2;
    f32 c1;
    f32 c2;

    a = isPendingChildNpcActive(self->f38);
    if (a == 1) {
        b = computeActorAnchorDeltaAfterLOS(self->f38) & 0xFF;
        if (b == a) {
            AkV4 vD8;
            f32 qE8[4];
            AkV4 vF8;
            AkV4 v108;
            AkV4 v118;
            t = getObjectMeshTransformOrLocal(self->f38, mA8);
            mat34CrossRowsAndCopyPos(m28, self, 1.0f);
            mat3x3InverseInto(m58, m28);
            transformVec3ByMat34(m58, t, &v98);
            v98.y -= self->f6C;
            vec3NormalizeInto(&v88, &v98);
            buildRotationMatrixSlot0(m28, self->f5C);
            composeRotationMatrixSlot1(m28, self->f58);
            transformVec3ByMat34(m28, D_mission_overlay_8010A68C, &v98);
            ang = constMinusSinfApprox(vec3Dot(&v98, &v88)) * 57.29578f;
            if (ang > 0.001f) {
                if (ang > 5.0f && self->fF8 == 0) {
                    self->fF8 = b;
                    play3DSoundEventVariant(self->pB4, self, self->p24, 8.0f, 0.5f, 7, 0x49, b, 0x6E, 0x28);
                }
                lim = self->f60 * (dt * 30.0f);
                if (lim < ang) ang = lim;
                vec3Cross(&vD8, &v98, &v88);
                normalize_vector(&vD8);
                quatFromAxisAngle(qE8, &vD8, ang);
                rotateVec3ByQuat(qE8, &v98, &v88);
                vD8.x = v88.x;
                vD8.y = 0.0f;
                vD8.z = v88.z;
                ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A68C, &vD8) / (vec3Length(D_mission_overlay_8010A68C) * vec3Length(&vD8)));
                *(AkV3 *)&v108 = *(AkV3 *)D_mission_overlay_8010A68C;
                v108.y = 0.0f;
                *(AkV3 *)&v118 = *(AkV3 *)&vD8;
                v118.y = 0.0f;
                ang = ang * 57.29578f;
                vec3Cross(&vF8, &v108, &v118);
                if (!(vF8.y >= 0.0f)) ang = -ang;
                buildRotationMatrixSlot1(m28, -ang);
                transformVec3ByMat34(m28, &v88, &vD8);
                vD8.x = 0.0f;
                self->f58 = ang;
                ang2 = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A68C, &vD8) / (vec3Length(D_mission_overlay_8010A68C) * vec3Length(&vD8))) * 57.29578f;
                if (!(vD8.y <= 0.0f)) ang2 = -ang2;
                c1 = self->f58;
                self->f5C = ang2;
                if (c1 > 360.0f) {
                    self->f58 = 360.0f;
                } else if (c1 < -360.0f) {
                    self->f58 = -360.0f;
                }
                c2 = self->f5C;
                if (c2 > 20.0f) {
                    self->f5C = 20.0f;
                } else if (c2 < -20.0f) {
                    self->f5C = -20.0f;
                }
            } else if (self->fF8 == b) {
                self->fF8 = 0;
                factor5RemoveListNode(self->pB4);
            }
            return;
        }
    }
    {
        f32 mD8[12];
        AkV4 v108;
        AkV4 v118;
        AkV4 v128;
        f32 q138[4];
        AkV4 v148;
        AkV4 v158;
        AkV4 v168;
        buildRotationMatrixSlot0(mD8, self->f5C);
        composeRotationMatrixSlot1(mD8, self->f58);
        transformVec3ByMat34(mD8, D_mission_overlay_8010A68C, &v118);
        ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A68C, &v118)) * 57.29578f;
        if (ang > 0.001f) {
            if (ang > 5.0f && self->fF8 == 0) {
                self->fF8 = 1;
                play3DSoundEventVariant(self->pB4, self, self->p24, 8.0f, 0.5f, 7, 0x49, 1, 0x6E, 0x28);
            }
            lim = self->f60 * (dt * 30.0f);
            if (lim < ang) ang = lim;
            vec3Cross(&v128, &v118, D_mission_overlay_8010A68C);
            normalize_vector(&v128);
            quatFromAxisAngle(q138, &v128, ang);
            rotateVec3ByQuat(q138, &v118, &v108);
            v128.x = v108.x;
            v128.y = 0.0f;
            v128.z = v108.z;
            ang = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A68C, &v128) / (vec3Length(D_mission_overlay_8010A68C) * vec3Length(&v128)));
            *(AkV3 *)&v158 = *(AkV3 *)D_mission_overlay_8010A68C;
            v158.y = 0.0f;
            *(AkV3 *)&v168 = *(AkV3 *)&v128;
            v168.y = 0.0f;
            ang = ang * 57.29578f;
            vec3Cross(&v148, &v158, &v168);
            if (!(v148.y >= 0.0f)) ang = -ang;
            buildRotationMatrixSlot1(mD8, -ang);
            transformVec3ByMat34(mD8, &v108, &v128);
            v128.x = 0.0f;
            self->f58 = ang;
            ang2 = constMinusSinfApprox(vec3Dot(D_mission_overlay_8010A68C, &v128) / (vec3Length(D_mission_overlay_8010A68C) * vec3Length(&v128))) * 57.29578f;
            if (!(v128.y <= 0.0f)) ang2 = -ang2;
            self->f5C = ang2;
        } else if (self->fF8 == 1) {
            self->fF8 = 0;
            factor5RemoveListNode(self->pB4);
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A705C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A7060);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", npcAtStHandleDestruction);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", advanceAtStDeathAnimPhase);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70DC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70E0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70E8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70F4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A7100);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", npcAtStUpdate);

#include "game_settings.h"
typedef struct {
    u8 p00[0xB4];
    s16 fB4;
    u8 pB6[0xC0 - 0xB6];
    f32 fC0;
    f32 fC4;
    u8 pC8[0xD8 - 0xC8];
    s32 fD8;
    s32 fDC;
    s32 fE0;
    u8 pE4[4];
    f32 fE8;
    f32 fEC;
    f32 fF0;
    f32 fF4;
    f32 fF8;
    f32 fFC;
    u8 p100[4];
    f32 f104;
    f32 f108;
    f32 f10C;
    f32 f110;
    f32 f114;
    f32 f118;
    s32 f11C;
    f32 f120;
    f32 f124;
    f32 f128;
    f32 f12C;
    f32 f130;
    f32 f134;
    f32 f138;
    s32 f13C;
    f32 f140;
    f32 f144;
    f32 f148;
    s32 f14C;
    f32 f150;
    f32 f154;
    s16 f158;
    u8 p15A[6];
    s32 f160;
    s32 f164;
    s32 f168;
    u8 p16C[4];
    s32 f170;
    s32 f174;
    s32 f178;
    u8 p17C[4];
    s16 f180;
    u8 p182[0x194 - 0x182];
    s32 f194;
} AtStPlayer;

extern AtStPlayer D_main_bss_80137DBC;
void initPlayerCraftMovementMode(AtStPlayer *);
s32 refreshPlayerSecondaryWeaponHud(s32, void *, s32);

void playerAtStInit(s32 arg0, s16 arg1)
{
  AtStPlayer *p = &D_main_bss_80137DBC;
  register u32 mask asm("$6");
  p->f180 = arg1;
  p->fB4 = 0;
  initPlayerCraftMovementMode(p);
  mask = 0xFEFFFFFF;
  p->f11C = (p->f14C = (p->f13C = 0));
  p->fE0 = (p->fDC = (p->fD8 = 0));
  p->f158 = 0;
  p->fC0 = 150.0f;
  p->fC4 = 150.0f;
  p->fE8 = 2.625f;
  p->fEC = 2.625f;
  p->fF0 = 0.11875f;
  p->fF4 = 0.11875f;
  p->fF8 = 1.4f;
  p->fFC = 1.8f;
  p->f104 = 15.0f;
  p->f108 = 10.0f;
  p->f10C = 1.0f;
  p->f110 = -40.0f;
  p->f114 = -40.0f;
  p->f118 = 35.0f;
  p->f120 = 35.0f;
  p->f124 = 35.0f;
  p->f130 = 0.75f;
  p->f134 = 3.0f;
  p->f138 = 20.0f;
  p->f140 = 10.0f;
  p->f144 = 60.0f;
  p->f148 = 10.0f;
  p->f150 = 5.0f;
  p->f154 = 40.0f;
  p->f128 = 0.2f;
  p->f12C = 0.15f;
  p->f174 = (p->f168 = (p->f164 = (p->f170 = (p->f160 = 0))));
  p->f194 = 4;
  gGameSettings.unlockAndSettingsFlags[0] &= mask;
  p->f178 = refreshPlayerSecondaryWeaponHud(0, &gGameSettings, 0xFEFFFFFF) & 0xFF;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A721C);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", spawnPlayerAtStCannonFire);

extern u16 D_main_bss_8013957C;
extern u8 D_main_bss_80138058[];
s32 findActiveNpcInSlotChain(u16, void *);
u8 *getNpcContextByIndex(u16);
s32 revalidateNpcSlotIterator(void *);
f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
s32 findSegmentObjectSphereHit(s32, void *, void *, void *);

typedef struct { f32 x, y, z; } AdV3;
s32 advancePlayerAtStLocomotion(f32 *p) {
    u8 sp10[0x28];
    AdV3 a;
    AdV3 b;
    u8 it[8];
    u16 cur;
    s32 idx;
    s32 mesh;
    f32 n;
    f32 t;

    if (0.0f <= p[0x18]) {
        a.x = p[0] + p[3];
        a.z = p[2] + p[5];
    } else {
        n = -p[3];
        t = p[0];
        t += n;
        a.x = t;
        n = -p[5];
        t = p[2];
        t += n;
        a.z = t;
    }
    if (wrapAngleToCyclicRange(a.x, a.z, D_main_bss_80138058, 0) < 0.8f) {
        return 1;
    }
    a = *(AdV3 *)p;
    a.y = a.y - 0.12f;
    b.x = p[3] * 0.2f;
    b.y = p[4] * 0.2f;
    b.z = p[5] * 0.2f;
    if (p[0x18] < 0.0f) {
        b.x = -b.x;
        b.y = -b.y;
        b.z = -b.z;
    }
    idx = findActiveNpcInSlotChain(D_main_bss_8013957C, it);
    if ((idx & 0xFFFF) != 0xFFFF) {
        do {
            cur = idx;
            if (cur != *(u16 *)((u8 *)p + 0x72)) {
                mesh = *(s32 *)(getNpcContextByIndex(cur) + 0xC);
                if (mesh != 0) {
                    if (findSegmentObjectSphereHit(mesh, &a, &b, sp10) != 0) {
                        return 1;
                    }
                }
            }
            idx = revalidateNpcSlotIterator(it);
        } while ((idx & 0xFFFF) != 0xFFFF);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", updatePlayerAtStBehavior);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", playerAtStUpdate);

s32 setNpcHealth(s32, void *, void *);
void initActorMotionParams(s32, s32, s32, s32, f32);
void initObjectAnimSubstruct(s32, s32, s32, s32, f32, void *, s32, f32, f32, s32);
void setObjectDetailLevel(s32, s32);
s32 tickAtStCannonFireEffect();
extern s32 D_main_bss_80137CE4;

void npcInitFromTemplate(u8 *arg0) {
    u8 *npc;
    u8 *tmpl;

    npc = *(u8 **)(arg0 + 4);
    tmpl = *(u8 **)(npc + 0x34);
    *(f32 *)(npc + 0x64) = 1.0f;
    *(s32 *)(npc + 0x68) = 0;
    if (setNpcHealth(*(s32 *)(npc + 0x38), tmpl + 0x6C, tmpl) > 0) {
        npc[0xFA] = 0;
        npc[0x7C] = 0;
        *(f32 *)(npc + 0x60) = ((f32 *)(tmpl + 0xBC))[D_main_bss_80137CE4];
        initActorMotionParams(*(s32 *)(npc + 0x38), ((s32 *)(tmpl + 0xB4))[D_main_bss_80137CE4], ((s32 *)(tmpl + 0xB8))[D_main_bss_80137CE4], ((s32 *)(tmpl + 0xC0))[D_main_bss_80137CE4], ((f32 *)(tmpl + 0xC4))[D_main_bss_80137CE4]);
        initObjectAnimSubstruct(*(s32 *)(npc + 0x38), *(s32 *)(tmpl + 0xC8), *(s32 *)(tmpl + 0xCC), *(s32 *)(tmpl + 0xD0), *(f32 *)(tmpl + 0xD4), tickAtStCannonFireEffect, 0, 10.0f, 15.0f, 0);
        setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(tmpl + 0xA0));
    } else {
        npc[0xFA] = 2;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", spawnScaledBootVec4Effect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", fake_func_800D2C98);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A73B8);
