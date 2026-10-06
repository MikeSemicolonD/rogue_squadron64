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

extern void scaleVec3ByRandomRange(f32 *, f32, f32);
extern u8 *getNpcContextByIndex(u16);
extern void mat34CrossRowsAndCopyPos(void *, void *, f32);
extern s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
typedef struct { u8 a, b, c, d; } AtStRgba;
typedef struct { s32 a, b, c; } V3i;
extern AtStRgba D_mission_overlay_800A705C;
extern char D_mission_overlay_800A7060[];
extern u8 D_main_bss_80130B63;
extern s32 gCurrentLevel;
extern void clearModelAnimChannelEntry(s32);
extern void releaseModelAnimSlot(s32);
extern void transformMeshPartIntoWorld(s32, f32 *);
extern void spawnNpcType0xAFromTemplate(void *, f32);
extern void spawnByteAnimDebrisDefault(void *);
extern void spawnOrientedNpc(s32, f32 *, s32, void *, f32, f32, f32, f32);
extern void spawnDestructionEffectBurst(f32 *, s32, f32, f32, f32, f32);
extern void composeRandomRotationMatrix(f32 *, f32 *, f32, s32, s32, s32);
extern void spawnDebris1Npc(f32 *, f32 *, f32, f32, f32);
extern void spawnSplineWalkerCraft(void *, f32, f32, s32);
extern void *walkMeshdef0List(char *);
extern void releaseMeshAsset(void *);
extern void initActorRenderDescriptorWithNpcVelocity(s32, s32);
s16 randS(void) __asm__("rand");
#define FABS(x) ({ f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(x)); _r; })

typedef struct {
    f32 x, y, z;
    u8 pad0C[0x24 - 0x0C];
    f32 f24;
    u8 pad28[0x30 - 0x28];
    s32 mesh30;
    s32 u34;
    s32 u38;
    u8 pad3C[0x50 - 0x3C];
    f32 f50, f54;
    u8 pad58[0x80 - 0x58];
    s32 u80;
    u8 pad84[0x8C - 0x84];
    s32 u8C, u90;
    u8 pad94[0xFA - 0x94];
    u8 uFA;
} AtStNpc;

void npcAtStHandleDestruction(void *npcv) {
    AtStNpc *npc = npcv;
    f32 mtx[3];
    f32 vel[3];
    f32 *p;
    f32 pos[3];
    AtStRgba color;
    f32 big;
    f32 fa;
    f32 fb;
    f32 fc;
    s32 i;
    s32 n;
    s32 k;

    color = D_mission_overlay_800A705C;
    if (npc->u80 != 0) {
        npc->u80 = 0;
        clearModelAnimChannelEntry(npc->u90);
        releaseModelAnimSlot(npc->u8C);
    }
    *(V3i *)pos = *(V3i *)npc;
    if (*(s32 *)(npc->u34 + 0xA8) == 0) {
        p = pos;
        transformMeshPartIntoWorld(npc->mesh30, p);
    }
    big = npc->f54 + npc->f54;
    spawnNpcType0xAFromTemplate(pos, npc->f50 * 4.0f);
    spawnByteAnimDebrisDefault(npc);
    play3DSoundEvent(0, npc, &npc->f24, 24.0f, 0.7f, 0, 0x21, 0x7D, 0x50);
    if (D_main_bss_80130B63 != 0) {
spawn:
        spawnOrientedNpc(0x8002, pos, 0, NULL, big * 0.75f, big * 1.2f, 1.0f, 0.6f);
        spawnOrientedNpc(0x8001, pos, 0, &color, big * 0.75f, big * 0.9f, 1.0f, 0.4f);
    } else {
        switch (gCurrentLevel) {
        case 3:
        case 6:
        case 9:
        case 0xD:
            break;
        default:
            goto spawn;
        }
    }
    big = big * 0.5f;
    spawnDestructionEffectBurst(pos, 0xFFFF, 1.6f, big, 1.5f, 1.0f);
    n = (s16)(randS() % 3) + 5;
    for (i = 0; i < n; i++) {
        {
            composeRandomRotationMatrix(mtx, vel, npc->f50 * 0.5f, 0x3C, 0, 0);
            mtx[0] += pos[0];
            mtx[1] += pos[1];
            mtx[2] += pos[2];
            scaleVec3ByRandomRange(vel, 3.0f, 4.0f);
            fa = FABS(((f32)(randS() & 0x7F) - 64.0f) / 12.8f);
            fa = fa + 12.0f;
            fb = FABS(((f32)(randS() & 0x7F) - 64.0f) * 0.0078125f) + 1.8f;
            spawnDebris1Npc(mtx, vel, fa, fb, FABS(((f32)(randS() & 0x7F) - 64.0f) / 320.0f) + 0.2f);
        }
    }
    switch (*(s32 *)(npc->u34 + 0xA8)) {
    case 0:
        releaseMeshAsset((void *)npc->mesh30);
        npc->mesh30 = (s32)walkMeshdef0List(D_mission_overlay_800A7060);
        mat34CrossRowsAndCopyPos((void *)(npc->mesh30 + 0x28), npc, npc->f54);
        *(s32 *)((u8 *)getNpcContextByIndex(*(u16 *)(npc->u38 + 0x198)) + 0xC) = npc->mesh30;
        npc->uFA = 2;
        initActorRenderDescriptorWithNpcVelocity(npc->u38, npc->u34);
        break;
    case 1:
        { register f32 sc asm("$f0") = npc->f54; spawnSplineWalkerCraft(npc, sc * 1.75f, sc * 2.25f, 0xC); }
        npc->uFA = 3;
        break;
    default:
        npc->uFA = 3;
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0CFB20", advanceAtStDeathAnimPhase);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70DC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70E0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70E8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A70F4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0CFB20", D_mission_overlay_800A7100);

typedef struct { f32 x, y, z; } SVec3;
typedef struct { f32 m[12]; } SMat;
typedef struct {
    SVec3 pos;
    SVec3 fwd;
    SVec3 up;
    SVec3 vel;
    u8 *mesh;
    u8 *rec;
    s32 obj;
    u8 *node0;
    u8 *node1;
    u8 *mat0;
    u8 *mat1;
    u8 *ctx;
    f32 radius;
    f32 scale;
    f32 f58;
    f32 f5C;
    f32 f60;
    f32 f64;
    f32 f68;
    f32 f6C;
    u16 slot70;
    u16 slot72;
    u16 slot74;
    u16 slot76;
    u16 slot78;
    u16 slot7A;
    u16 slot7C;
    s16 animIdx;
    s32 anim[3];
    s32 animSlot;
    s32 chan;
    f32 phase;
    f32 dur;
    f32 rate;
    f32 fA0;
    s32 iA4;
    u8 bA8;
    u8 bA9;
    u8 bAA;
    u8 bAB;
    f32 fAC;
    f32 fB0;
    u8 audio[0x44];
    u8 audioOn;
    u8 outCount;
    u8 mode;
    u8 bFB;
} AtSt;

#define SABSF(x) ({ f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(x)); _r; })

extern u8 D_main_bss_80130B39;
extern u8 D_main_bss_80130B63;
extern u8 *D_main_bss_80138D1C;
extern u8 D_main_bss_80138058[];
extern u16 D_main_bss_80139560[];
extern u16 D_main_bss_80139574;
extern char D_mission_overlay_800A7060[];
extern char D_mission_overlay_800A70DC[];
extern char D_mission_overlay_800A70E0[];
extern char D_mission_overlay_800A70E8[];
extern char D_mission_overlay_800A70F4[];
extern char D_mission_overlay_800A7100[];
extern u8 D_mission_overlay_8010A680[];
void *walkMeshdef0List(char *);
void composeEulerRotationXYZ(void *, s32, s32, s32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, s32);
void composeRotationMatrixSlot1I(void *, s32) __asm__("composeRotationMatrixSlot1");
void composeRotationMatrixSlot2(void *, s32);
void addVec3At0x24(void *, f32, f32, f32);
u16 popNpcSlotFromTail(u16, void *);
s32 lookupHmtMaterialByName(void *, char *, void *);
u16 spawnInheritedNpcVariantA(u16, void *);
void *allocateAndInitCraftNpcContext(f32, f32, s32);
void createAndInitObject(void *, s32, void *, void *, void *);
void npcInitFromTemplate(u8 *);
void *getLevelDatItemByName(char *);
void initActorAsType1(s32, void *, s32, s32, f32, f32, s32);
void updateObjectFlags110(s32, s32, s32);
s32 load_model_animation(char *);
s32 flattenAnimTreeAndAllocateSlot(s32, s32);
s32 markModelAnimChannelEntryActive(s32, s32);
s32 rand(void);
void setModelAnimSlotCycleDuration(s32, f32);
void seekAllModelAnimChannelsInSlotToTime(s32, f32);
void clearModelAnimChannelEntry(s32);
void releaseModelAnimSlot(s32);
void rs_free(void *);
void destroyNpcSlotByIndex(u16);
s32 getNpcCurrentHealth(s32);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void releaseMeshAsset(void *);
void func_mission_overlay_800AA6D0(void *, f32, void *);
void dispatchEffectByActorType(s32, f32);
void advanceAtStDeathAnimPhase(void *);
void setType1ActorParams(s32, f32, u8, u8, u8, s32);
u8 func_mission_overlay_800EFDE0(s32, s32, s32, f32);
void applyToObjectSubstructByFlag(s32, f32, f32, s32);
u8 validateActorTargetLOS(s32);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyObjectOwnedNpcSlot(s32);
s32 checkAndReturnByteFlagAsU8(s32, void *, void *, f32);
s32 sampleTerrainAtNpcPosition(void *, void *, void *, s32);
void parseModelAnimType2Entry(s32);
void zmemcpy(void *, void *, s32);
void mat3x4Multiply(void *, void *, void *);
void clearVec4QuadStruct(void *);
void applyScaleToMat3x4(void *, f32, f32, f32);
void composeQuatToMat3x4(void *, void *);
s32 updateActive3DAudioSource(void *, void *, void *, u8);
void addNpcToVisibilityBucket(s32, void *, void *, f32);
void enqueueMeshTypeForCleanup(void *);
void advanceNpcOnCurvedPath(s32, s32, void *, void *);
void spawnNpcType0xAFromTemplate(void *, f32);
void spawnRandomParticleWithParent(void *, u16, f32, s32);
void extrapolateNpcPositionForCurrentMode(void *);
s32 getObjectDetailLevel(s32);
void func_mission_overlay_800EFD6C(s32);
s32 dealDamageToNpc(s32, u16);
void npcAtStHandleDestruction(void *);
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
s32 clearPendingChildNpc(s32);
void setObjectFlagBit4(void *);
void setObjectDetailLevel(s32, s32);
void dispatchSlotAction5IfActive(void *, void *);

static __inline__ s32 atStCheckLOS(AtSt *s2, SMat *a, SMat *b) {
    s32 flag = 0;
    if ((u8)isPendingChildNpcActive(s2->obj) == 1) {
        *a = *(SMat *)s2;
        buildRotationMatrixSlot0(b, s2->f5C);
        composeRotationMatrixSlot1(b, s2->f58);
        transformVec3ByMat34(b, &a->m[3], &s2->fwd);
        transformVec3ByMat34(b, &a->m[6], &s2->up);
        if (validateActorTargetLOS(s2->obj) == 1) {
            flag = 1;
        }
        *(SMat *)s2 = *a;
    }
    return flag;
}

s32 npcAtStUpdate(u8 *arg0, s32 action, u8 *arg2) {
    AtSt *s2 = *(AtSt **)(arg0 + 4);
    SVec3 sp28;
    SMat sp38;
    SMat sp68;
    f32 sp98[4];
    f32 spA8[4];
    f32 spB8[3];
    f32 dt;
    s32 cnt;
    char *name;
    u8 *rec;
    u8 *msg;
    u8 *a4;
    u8 *a5;
    u8 *a9;
    s32 flag;
    s32 act;

    act = action;
    switch ((u16)action) {
    case 1:
    case 8:
        rec = arg2;
        msg = arg2;
        *(u16 *)(arg0 + 0x14) |= 0x100;
        if (!(*(u16 *)(arg0 + 0x14) & 0x20)) {
            s2->rec = arg2;
            s2->pos.x = *(f32 *)(arg2 + 0x10);
            s2->pos.y = *(f32 *)(arg2 + 0x14);
            s2->pos.z = *(f32 *)(arg2 + 0x18);
            name = (char *)(*(s32 *)(arg2 + 0x8C) + (s32)arg2);
        } else {
            rec = *(u8 **)(arg2 + 0xC);
            s2->rec = rec;
            if (*(u8 *)(*(u8 **)(arg2 + 4) + 2) == 3) {
                s2->pos = **(SVec3 **)(arg2 + 8);
                name = *(char **)arg2;
            } else {
                name = D_mission_overlay_800A70DC;
                s2->pos.x = 0.0f;
                s2->pos.y = 0.0f;
                s2->pos.z = 0.0f;
            }
        }
        cnt = *(s32 *)(D_main_bss_80137CE4 * 4 + (s32)s2->rec + 0x6C);
        {
            u8 *t;
            u8 *mesh;
            *(u8 **)((u8 *)s2 + 0x30) = walkMeshdef0List(cnt > 0 ? D_mission_overlay_800A70E0 : D_mission_overlay_800A7060);
            mesh = *(u8 **)((u8 *)s2 + 0x30);
            if (D_main_bss_80130B63 != 0) {
                t = D_mission_overlay_8010A680;
            } else {
                t = &D_mission_overlay_8010A680[8];
            }
            *(u8 **)(mesh + 4) = t;
        }
        composeEulerRotationXYZ(s2, *(s32 *)(rec + 0x1C), *(s32 *)(rec + 0x20), *(s32 *)(rec + 0x24));
        s2->vel.x = s2->vel.y = s2->vel.z = 0.0f;
        {
            f32 inv = 1.0f / *(f32 *)(*(u8 **)s2->mesh + 0x34);
            f32 sc = inv * *(f32 *)(rec + 0x28);
            s2->scale = sc;
            s2->f6C = sc * 4.0f * -0.520477f;
            initVec4TripletFromArgs(s2->mesh + 0x28, inv * *(f32 *)(rec + 0x28), inv * *(f32 *)(rec + 0x2C), inv * *(f32 *)(rec + 0x30));
        }
        composeRotationMatrixSlot0(s2->mesh + 0x28, *(s32 *)(rec + 0x1C));
        composeRotationMatrixSlot1I(s2->mesh + 0x28, *(s32 *)(rec + 0x20));
        composeRotationMatrixSlot2(s2->mesh + 0x28, *(s32 *)(rec + 0x24));
        addVec3At0x24(s2->mesh + 0x28, s2->pos.x, s2->pos.y, s2->pos.z);
        *(AtSt **)(arg0 + 8) = s2;
        *(u8 **)(arg0 + 0xC) = s2->mesh;
        if (cnt > 0) {
            u8 *b = (u8 *)D_main_bss_80139560;
            s32 o;
            s2->slot70 = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
            o = 0x2C;
            if (*(s32 *)(rec + 0xA0) == 1) {
                o = 0x2E;
            }
            s2->slot72 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            s2->node0 = (u8 *)lookupHmtMaterialByName(s2->mesh, D_mission_overlay_800A70E8, &s2->mat0);
            s2->node1 = (u8 *)lookupHmtMaterialByName(s2->mesh, D_mission_overlay_800A70F4, &s2->mat1);
            o = 0x12;
            if (*(s32 *)(rec + 0xA0) == 1) {
                o = 0xE;
            }
            s2->slot76 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            if (*(s32 *)(rec + 0xA4) != 0) {
                o = 0x18;
                if (*(s32 *)(rec + 0xA0) == 1) {
                    o = 0x1A;
                }
                s2->slot78 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            } else {
                s2->slot78 = 0xFFFF;
            }
            sp28.x = s2->scale * 0.0f;
            sp28.y = s2->scale * -1.8f;
            sp28.z = s2->scale * 0.0f;
            s2->slot7A = spawnInheritedNpcVariantA(*(u16 *)(arg0 + 0x16), &sp28);
        } else {
            u8 *b = (u8 *)D_main_bss_80139560;
            popNpcSlotFromTail(*(u16 *)(b + 0x14), arg0);
            s2->slot70 = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
            s2->slot7A = 0xFFFF;
        }
        {
            f32 sc = s2->scale;
            s2->radius = *(f32 *)(*(u8 **)s2->mesh + 0x44) * sc;
            s2->f58 = 0.0f;
            s2->f5C = 0.0f;
            s2->outCount = 0;
            s2->audioOn = 0;
            s2->ctx = allocateAndInitCraftNpcContext(sc * 0.7f, sc * 0.9f, 0xA);
        }
        *(f32 *)(s2->ctx + 0x14) = 1.0f;
        *(f32 *)(s2->ctx + 4) = s2->scale * -0.65f;
        *(f32 *)(s2->ctx + 0x10) = 0.0f;
        *(f32 *)(s2->ctx + 0x18) = 0.6f;
        createAndInitObject(&s2->obj, 0, arg0, npcInitFromTemplate, (u16)act == 1 ? NULL : msg);
        if (cnt > 0) {
            if (*name != '-') {
                void *item = getLevelDatItemByName(name);
                u8 *r = s2->rec;
                initActorAsType1(s2->obj, item, *(s32 *)(r + 0x90), *(s32 *)(r + 0x9C), *(f32 *)(r + 0x94), *(f32 *)(s2->rec + 0x98), 0);
                updateObjectFlags110(s2->obj, 7, 0);
            }
            s2->animIdx = 0;
            s2->fAC = 0.0f;
            s2->rate = 0.5f / s2->scale;
            s2->fB0 = D_mission_overlay_8010A6A4[0];
            s2->bFB = 0;
            s2->bAB = 0;
            s2->anim[0] = load_model_animation(D_mission_overlay_800A7100);
            s2->anim[1] = load_model_animation("imp_stuff/atst_start");
            s2->anim[2] = load_model_animation("imp_stuff/atst_stop");
            s2->animSlot = flattenAnimTreeAndAllocateSlot(*(s32 *)(s2->mesh + 0x18), s2->anim[s2->animIdx]);
            s2->chan = markModelAnimChannelEntryActive(s2->animSlot, 0);
            s2->phase = SABSF(((f32)(rand() & 0x7F) - 64.0f) * 0.015625f);
            s2->dur = 1.0f / (*(f32 *)(s2->rec + 0x90) * s2->rate);
            setModelAnimSlotCycleDuration(s2->animSlot, s2->dur);
            seekAllModelAnimChannelsInSlotToTime(s2->animSlot, 0.0f);
            return 1;
        }
        s2->anim[0] = s2->anim[1] = s2->anim[2] = 0;
        break;
    case 2:
        if (s2->anim[0] != 0) {
            s2->anim[0] = 0;
            clearModelAnimChannelEntry(s2->chan);
            releaseModelAnimSlot(s2->animSlot);
        }
        if (s2->audioOn == 1) {
            s2->audioOn = 0;
            factor5RemoveListNode(s2->audio);
        }
        if (s2->ctx != NULL) {
            rs_free(s2->ctx);
        }
        if (s2->slot7A != 0xFFFF) {
            destroyNpcSlotByIndex(s2->slot7A);
            s2->slot7A = 0xFFFF;
        }
        if (!(*(u16 *)(arg0 + 0x14) & 0x20)) {
            initActorRenderDescriptorIfUninit(s2->obj, *(s32 *)(s2->rec + 0xA8) != 0, s2->rec, 0, s2->rec + 0x70);
        } else {
            initActorRenderDescriptorIfUninit(s2->obj, getNpcCurrentHealth(s2->obj) < 1, s2->rec, 0, s2->rec + 0x70);
        }
        clearPendingAndDestroyChildNpc(&s2->obj);
        releaseMeshAsset(s2->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        {
            f32 inc = dt * 4.0f;
            if (s2->f64 < 1.0f) {
                s2->f64 += inc;
                if (1.0f < s2->f64) {
                    s2->f64 = 1.0f;
                    s2->f68 = 0.0f;
                } else if (s2->f64 < 0.2f) {
                    s2->f68 = s2->f64 * 5.0f;
                } else {
                    s2->f68 = 1.0f - (s2->f64 - 0.2f) * 1.25f;
                }
            }
        }
        switch (s2->mode) {
        case 0:
            s2->mode = 1;
        case 1:
            switch (s2->animIdx) {
            case 0:
                func_mission_overlay_800AA6D0(s2, dt, s2->rec + 0x34);
                dispatchEffectByActorType(s2->obj, dt);
                s2->phase += dt / s2->dur;
                if (s2->phase > 1.0f) {
                    s2->phase -= 1.0f;
                    if (s2->bAB != 0) {
                        advanceAtStDeathAnimPhase(s2);
                    }
                }
                advanceAtStEffectPhaseSound((u8 *)s2, dt, 0);
                break;
            case 1:
                func_mission_overlay_800AA6D0(s2, dt, s2->rec + 0x34);
                dispatchEffectByActorType(s2->obj, dt);
                s2->phase += dt / s2->dur;
                if (s2->phase > 1.0f) {
                    s2->phase -= 1.0f;
                    s2->bAB = 3;
                    advanceAtStDeathAnimPhase(s2);
                }
                advanceAtStEffectPhaseSound((u8 *)s2, dt, 0);
                break;
            case 2:
                if (s2->phase < 1.0f) {
                    s2->phase += dt / s2->dur;
                    if (s2->phase >= 1.0f) {
                        s2->phase = 1.0f;
                        setType1ActorParams(s2->obj, s2->fA0, s2->bA9, s2->bAA, s2->bA8, s2->iA4);
                    } else if (s2->phase < 0.25f) {
                        func_mission_overlay_800AA6D0(s2, dt, s2->rec + 0x34);
                        dispatchEffectByActorType(s2->obj, dt);
                        advanceAtStEffectPhaseSound((u8 *)s2, dt, 0);
                    }
                } else {
                    dispatchEffectByActorType(s2->obj, dt);
                    if (s2->bAB != 0) {
                        advanceAtStDeathAnimPhase(s2);
                    }
                }
                break;
            }
            seekAllModelAnimChannelsInSlotToTime(s2->animSlot, s2->phase * s2->dur);
            if (func_mission_overlay_800EFDE0(s2->obj, *(s32 *)(s2->rec + 0xAC), *(s32 *)(s2->rec + 0xB0), dt)) {
                s2->mode = 1;
            }
            updateAtStBodyKinematics((AkBody *)s2, dt);
            flag = atStCheckLOS(s2, &sp38, &sp68);
            if (flag == 1) {
                applyToObjectSubstructByFlag(s2->obj, dt, 0.0f, 0);
            }
            break;
        case 2:
            break;
        case 3:
        destroy:
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        if (*(s32 *)(s2->rec + 0x88) == 0) {
            s2->outCount = 0;
        } else if (isNpcWithinActiveReferenceRange(s2) != 0) {
            s2->outCount = 0;
        } else {
            s2->outCount++;
            if (s2->outCount >= 0x15) {
                goto destroy;
            }
        }
        destroyObjectOwnedNpcSlot(s2->obj);
        return 1;
    case 4:
        a4 = arg2;
        if (checkAndReturnByteFlagAsU8(*(s32 *)arg2, s2->mesh, s2, s2->radius) != 0) {
            if (s2->mode != 2) {
                u8 *m;
                u8 *mp;
                {
                    f32 x = s2->pos.x - s2->fwd.x * s2->scale * 0.3f;
                    f32 y;
                    f32 z;
                    sp98[0] = x;
                    y = s2->pos.y - s2->scale * 2.6f;
                    sp98[1] = y;
                    z = s2->pos.z - s2->fwd.z * s2->scale * 0.3f;
                    m = D_main_bss_80138D1C + 0x28;
                    sp98[2] = z;
                    spA8[0] = *(f32 *)(m + 0x24);
                    spA8[1] = *(f32 *)(m + 0x28);
                    spA8[2] = *(f32 *)(m + 0x2C);
                    spB8[0] = x - spA8[0];
                    spB8[1] = y - spA8[1];
                    spB8[2] = z - spA8[2];
                    if (sampleTerrainAtNpcPosition(spA8, spB8, D_main_bss_80138058, 0) == 0) {
                        parseModelAnimType2Entry(s2->animSlot);
                    }
                }
                m = s2->node0 + 0x1C;
                buildRotationMatrixSlot0(&sp38, -s2->f5C);
                composeRotationMatrixSlot1(&sp38, s2->f58);
                zmemcpy(&sp68, m, 0x30);
                mat3x4Multiply(&sp68, &sp38, m);
                mp = s2->mat1;
                m = s2->node1 + 0x1C;
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
                addVec3At0x24(m, 0.0f, 0.0f, s2->f68 * 8.0f);
                if ((*(s32 *)(mp + 0x4C) & 9) == 9) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x78) + *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x7C) + *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x80) + *(f32 *)(mp + 0x58));
                } else if ((*(s32 *)(mp + 0x4C) & 9) == 8) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x78), *(f32 *)(mp + 0x7C), *(f32 *)(mp + 0x80));
                } else if (*(s32 *)(mp + 0x4C) & 1) {
                    addVec3At0x24(m, *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x58));
                }
            }
            if (s2->audioOn != 0) {
                updateActive3DAudioSource(s2->audio, s2, &s2->vel, 0x64);
            }
            mat34CrossRowsAndCopyPos(s2->mesh + 0x28, s2, s2->scale);
            addNpcToVisibilityBucket(*(s32 *)a4, s2->mesh, s2, s2->radius);
        } else {
            if (s2->audioOn != 0) {
                updateActive3DAudioSource(s2->audio, s2, &s2->vel, 0x64);
            }
            enqueueMeshTypeForCleanup(s2->mesh);
            mat34CrossRowsAndCopyPos(s2->mesh + 0x28, s2, s2->scale);
        }
        if (s2->ctx != NULL) {
            advanceNpcOnCurvedPath(*(s32 *)(a4 + 8), *(s32 *)a4, s2, s2->ctx);
            return 1;
        }
        return 1;
    case 5:
        a5 = arg2;
        if (s2->mode == 2) {
            u8 *p = *(u8 **)(arg2 + 8);
            if (p != NULL) {
                f32 k = 0.15f;
                if (*(u16 *)(arg2 + 4) != 0xC) {
                    spawnNpcType0xAFromTemplate(p, k);
                } else {
                    spawnRandomParticleWithParent(p, 0xFFFF, k, 0);
                }
            }
        } else {
            extrapolateNpcPositionForCurrentMode(arg2);
        }
        if (getNpcCurrentHealth(s2->obj) > 0) {
            play3DSoundEvent(0, s2, &s2->vel, 24.0f, 0.5f, 0, 0x21, 0x7D, 0x50);
            if (getObjectDetailLevel(s2->obj) == 1 && D_main_bss_80130B39 == 0) {
                func_mission_overlay_800EFD6C(0x1F4);
            }
            if (dealDamageToNpc(s2->obj, *(u16 *)(a5 + 6)) <= 0) {
                npcAtStHandleDestruction(s2);
                if (s2->ctx != NULL) {
                    rs_free(s2->ctx);
                }
                s2->ctx = NULL;
                unregisterAndFreeNpcSlot(s2->slot72, arg0);
                unregisterAndFreeNpcSlot(s2->slot76, arg0);
                if (s2->slot78 != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s2->slot78, arg0);
                }
                popNpcSlotFromTail(D_main_bss_80139574, arg0);
                {
                    u8 *r = s2->rec;
                    datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s2->rec + 0x84));
                }
                tallyMidDetailObject(arg0);
                clearPendingChildNpc(s2->obj);
                setObjectFlagBit4(arg0);
                if (s2->slot7A != 0xFFFF) {
                    destroyNpcSlotByIndex(s2->slot7A);
                    s2->slot7A = 0xFFFF;
                }
                if (s2->audioOn == 1) {
                    s2->audioOn = 0;
                    factor5RemoveListNode(s2->audio);
                }
            }
        }
        if (*(u16 *)a5 != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)a5);
            return 1;
        }
        return 1;
    case 9:
        a9 = arg2;
        switch (arg2[0x18]) {
        case 1:
            s2->bA9 = arg2[9];
            s2->bAA = arg2[0xA];
            s2->bA8 = arg2[8];
            s2->iA4 = *(s32 *)(arg2 + 4);
            s2->fA0 = *(f32 *)arg2;
            s2->bAB = 1;
            break;
        case 2:
            s2->dur = 1.0f / (*(f32 *)arg2 * s2->rate);
            setModelAnimSlotCycleDuration(s2->animSlot, s2->dur);
            return 1;
        case 3:
            s2->bAB = 2;
            break;
        case 8:
            if (getNpcCurrentHealth(s2->obj) > 0) {
                u8 *b;
                s32 o;
                unregisterAndFreeNpcSlot(s2->slot72, arg0);
                b = (u8 *)D_main_bss_80139560;
                o = 0x2C;
                if (*(s32 *)arg2 == 1) {
                    o = 0x2E;
                }
                s2->slot72 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                unregisterAndFreeNpcSlot(s2->slot76, arg0);
                o = 0x12;
                if (*(s32 *)arg2 == 1) {
                    o = 0xE;
                }
                s2->slot76 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                if (s2->slot78 != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s2->slot78, arg0);
                    if (*(s32 *)(s2->rec + 0xA4) != 0) {
                        o = 0x18;
                        if (*(s32 *)arg2 == 1) {
                            o = 0x1A;
                        }
                        s2->slot78 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    }
                }
                setObjectDetailLevel(s2->obj, *(s32 *)a9);
                return 1;
            }
            return 1;
        default:
            return 1;
        }
        break;
    case 7:
        dispatchSlotAction5IfActive(arg0, arg2);
        break;
    }
    return 1;
}

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

typedef struct { f32 m[12]; } PaMat;
typedef struct {
    f32 a0;
    f32 a4;
    f32 v[3];
    f32 f4C;
    f32 f50;
    f32 f54;
    f32 f58;
    f32 f5C;
    f32 f60;
    f32 f64;
} PaFx;
typedef struct {
    u8 pad0[0x30];
    u8 *mesh;
    u8 *node0;
    u8 *node1;
    s32 w3C;
    u8 *mat1;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    f32 f54;
    s32 w58;
    u8 b5C;
    u8 pad5D[3];
    f32 f60;
    s32 w64;
    s32 w68;
    s32 w6C;
    u16 pad70;
    u16 h72;
    s32 anim[3];
    s32 animSlot;
    s32 chan;
    s32 w88;
    f32 f8C;
    f32 f90;
    u8 pad94[0xB];
    u8 b9F;
    s16 hA0;
    u8 bA2;
    u8 bA3;
    void *save;
    u16 hA8;
    u8 bAA;
    u8 bAB;
    u16 hAC;
    u8 bAE;
    u8 bAF;
    s32 wB0;
} PaSt;
typedef struct {
    u8 pad0[4];
    f32 f4;
    u8 pad8[8];
    s32 w10;
    f32 f14;
    f32 f18;
} PaCtx;
extern u32 D_mission_overlay_8010CA1C;
extern u16 D_main_bss_80130B88[];
extern u32 D_mission_overlay_8010C9E0;
typedef struct { u8 pad[6]; u16 h6; } PaBe;
extern PaBe D_mission_overlay_8010BE18;
typedef struct { u8 pad[0xC]; u32 hi:24; u32 b7:1; u32 lo:7; } PaGs;
extern u8 D_main_8009E5F8[];
extern u8 D_mission_overlay_8010A6DC[];
extern u8 D_main_bss_8013800C[];
extern u8 D_main_bss_80138D18[];
void *rs_malloc(s32, s32);
void loadPlayerStartPosition(void *, void *);
void clearObjectFlagBit4(void *);
void resetTransientPlayerStateFlags(void);
void teardownHudInstancesAndUnbindNpcs(void);
void updatePlayerAtStBehavior(void *, s32);
void computeBootConfigScaledVec4(s32, s32, s32, void *, f32, f32);
void cbsvF(s32, f32, f32, void *, f32, f32) __asm__("computeBootConfigScaledVec4");
void vec3ExtrapolateFirstOrder(void *, s32, void *, f32);
void distanceAndDopplerNpcHelper(void *, f32, f32);
void buildRandomCameraFacingOrientation(s32, void *, f32, s32, s32, s32);
u16 spawnHeavyMechSubEffect(void *, void *, char *);
void slotDispatcherIter(u16, s32, void *);
void updatePlayerHudFrame(s32, void *, void *);
void paStInit(void *, s32) __asm__("playerAtStInit");
void paTransformMeshPart(void *, void *) __asm__("transformMeshPartIntoWorld");

typedef struct { u8 pad0[4]; u8 *p; u8 pad8[0x13C]; } PasEnt;
s32 playerAtStUpdate(u8 *arg0, s32 action, u8 *arg2) {
    PaSt *s2 = *(PaSt **)(arg0 + 4);
    f32 sp28[4];
    union { PaMat m; PaFx fx; } sp38;
    f32 sp68[4];
    PaMat sp78;
    u8 *s4;

    if ((u16)action != 2 && (D_mission_overlay_8010CA1C & 4)) {
        return 1;
    }
    s4 = (u8 *)&D_main_bss_80137DBC;
    switch ((u16)action) {
    case 1: {
        void *p;
        PaCtx *ctx;
        f32 one;
        f32 half;
        f32 t;

        p = rs_malloc(0x168, 0);
        s2->save = p;
        zmemcpy(p, D_main_8009E5F8, 0x168);
        zmemcpy(D_main_8009E5F8, D_mission_overlay_8010A6DC, 0x168);
        s2->hA8 = D_mission_overlay_8010BE18.h6;
        s4 = (u8 *)&D_main_bss_80137DBC;
        D_mission_overlay_8010BE18.h6 = 0;
        s2->bAF = ((PaGs *)&gGameSettings)->b7;
        gGameSettings.unlockAndSettingsFlags[0] &= ~0x80;
        p = walkMeshdef0List(D_mission_overlay_800A70E0);
        *(void **)&D_main_bss_80137DBC = p;
        s2->mesh = p;
        *(u8 **)(*(u8 **)&D_main_bss_80137DBC + 4) = D_mission_overlay_8010A680;
        *(u16 *)(s4 + 0xB6) = *(u16 *)(arg0 + 0x16);
        *(void **)(arg0 + 0xC) = *(void **)&D_main_bss_80137DBC;
        *(u8 **)(arg0 + 8) = s4 + 4;
        *(u16 *)(s4 - 2) = *(u16 *)(arg0 + 0x16);
        *(s32 *)(s4 + 0xB8) = 0;
        loadPlayerStartPosition(s4, 0);
        paStInit(s2, 1);
        popNpcSlotFromTail(D_main_bss_80139560[1], arg0);
        popNpcSlotFromTail(D_main_bss_80139560[0xE], arg0);
        one = 1.0f;
        s2->f44 = one / *(f32 *)(*(u8 **)s2->mesh + 0x34) * 0.2f;
        { f32 r = 0.18f; ctx = allocateAndInitCraftNpcContext(r, r, 10); }
        { f32 m = -0.08f;
        half = 0.5f;
        ctx->f14 = one;
        ctx->w10 = 0;
        ctx->f18 = half;
        ctx->f4 = m; }
        *(PaCtx **)(s4 + 0xBC) = ctx;
        s2->node0 = (u8 *)lookupHmtMaterialByName(s2->mesh, D_mission_overlay_800A70E8, &s2->w3C);
        s2->node1 = (u8 *)lookupHmtMaterialByName(s2->mesh, D_mission_overlay_800A70F4, &s2->mat1);
        *(s32 *)&s2->f48 = 0;
        *(s32 *)&s2->f4C = 0;
        s2->f60 = 0.1f;
        s2->h72 = *(u16 *)(arg0 + 0x16);
        s2->bAA = 1;
        s2->wB0 = 0x28;
        s2->f50 = one;
        *(s32 *)&s2->f54 = 0;
        s2->w58 = 0;
        s2->b5C = 0;
        s2->w68 = 0;
        s2->w6C = 0;
        s2->w64 = 0;
        s2->bA3 = 0;
        s2->bA2 = 0;
        s2->bAB = 0;
        s2->hAC = 0xFFFF;
        s2->bAE = 0;
        s2->b9F = 0;
        s2->hA0 = 0;
        s2->f90 = half / s2->f44;
        s2->anim[0] = load_model_animation(D_mission_overlay_800A7100);
        s2->anim[1] = 0;
        s2->anim[2] = 0;
        s2->animSlot = flattenAnimTreeAndAllocateSlot(*(s32 *)(s2->mesh + 0x18), s2->anim[s2->hA0]);
        s2->chan = markModelAnimChannelEntryActive(s2->animSlot, 0);
        t = one / (s2->f60 * s2->f90);
        s2->w88 = 0;
        s2->f8C = t;
        setModelAnimSlotCycleDuration(s2->animSlot, t);
        seekAllModelAnimChannelsInSlotToTime(s2->animSlot, 0);
        clearObjectFlagBit4(arg0);
        *(u16 *)(arg0 + 0x14) |= 0xC0;
        *(PaMat *)s2 = *(PaMat *)(s4 + 4);
        return 1;
    }
    case 0xC:
        loadPlayerStartPosition(s4, s4 + 4);
        paStInit(s2, 0x40);
        resetTransientPlayerStateFlags();
        return 1;
    case 2:
        zmemcpy(D_main_8009E5F8, s2->save, 0x168);
        rs_free(s2->save);
        D_mission_overlay_8010BE18.h6 = s2->hA8;
        if (s2->bAF != 0) {
            gGameSettings.unlockAndSettingsFlags[0] |= 0x80;
        }
        rs_free(*(void **)(s4 + 0xBC));
        releaseMeshAsset(*(void **)s4);
        teardownHudInstancesAndUnbindNpcs();
        return 1;
    case 3: {
        u8 *a3 = arg2;
        D_main_bss_80130B88[0] &= 0xF0FF;
        gGameSettings.unlockAndSettingsFlags[0] &= ~0x80;
        if (s2->wB0 > 0) {
            updatePlayerAtStBehavior(s2, *(s32 *)arg2);
        }
        *(PaMat *)(s4 + 4) = *(PaMat *)s2;
        {
            union { s32 i; f32 f; } u;
            register f32 d asm("$f2");
            u.i = 0x3D400000;
            d = *(f32 *)a3;
            __asm__("" :: "f"(d));
            cbsvF(0, u.f, u.f, D_main_bss_8013800C, 1.0f, d);
        }
        return 1;
    }
    case 5: {
        u8 *a5 = arg2;
        f32 k;
        f32 h;
        f32 z;
        s32 v;

        if (*(void **)(arg2 + 8) != NULL) {
            vec3ExtrapolateFirstOrder(*(void **)(arg2 + 8), 0, sp28, -0.1f);
            k = 0.2f;
            distanceAndDopplerNpcHelper(sp28, 0.05f, k);
            spawnNpcType0xAFromTemplate(sp28, k);
        }
        if (s2->wB0 > 0) {
            v = s2->wB0 - *(u16 *)(arg2 + 6);
            s2->wB0 = v;
            if (v <= 0) {
                paTransformMeshPart(s2->mesh, sp68);
                sp68[1] -= 0.12f;
                spawnByteAnimDebrisDefault(s2);
                h = 0.5f;
                spawnDestructionEffectBurst(sp68, 0xFFFF, 1.2f, h, 0.6f, 10.0f);
                spawnNpcType0xAFromTemplate(sp68, 3.0f);
                play3DSoundEvent(0, s2, (u8 *)s2 + 0x24, 24.0f, 0.7f, 0, 0x21, 0x7D, 0x50);
                z = 0.0f;
                buildRandomCameraFacingOrientation(0, sp38.fx.v, z, 5, -0xF, 1);
                sp38.fx.v[0] *= -2.0f;
                sp38.fx.v[1] *= -2.0f;
                sp38.fx.v[2] *= -2.0f;
                sp38.fx.f64 = 180.0f;
                sp38.fx.f5C = -0.05f;
                sp38.fx.f54 = h;
                sp38.fx.f58 = z;
                sp38.fx.f60 = z;
                sp38.fx.f4C = 4.0f;
                sp38.fx.f50 = -3.0f;
                s2->hAC = spawnHeavyMechSubEffect(&sp38, arg0, D_mission_overlay_800A70E8);
                D_mission_overlay_8010C9E0 |= 2;
            }
        }
        if (*(u16 *)a5 != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)a5);
        }
        return 1;
    }
    case 0xF:
        *(u16 *)arg2 = 0xFFFF;
        break;
    case 4: {
        u8 *a4 = arg2;
        u8 *m;
        u8 *mp;
        f32 one;
        u8 *pos;

        if (s2->wB0 > 0) {
            parseModelAnimType2Entry(s2->animSlot);
            m = s2->node0 + 0x1C;
            buildRotationMatrixSlot0(&sp38, -s2->f4C);
            composeRotationMatrixSlot1(&sp38, s2->f48);
            zmemcpy(&sp78, m, 0x30);
            mat3x4Multiply(&sp78, &sp38, m);
            mp = s2->mat1;
            m = s2->node1 + 0x1C;
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
            addVec3At0x24(m, 0.0f, 0.0f, s2->f54 * 8.0f);
            if ((*(s32 *)(mp + 0x4C) & 9) == 9) {
                addVec3At0x24(m, *(f32 *)(mp + 0x78) + *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x7C) + *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x80) + *(f32 *)(mp + 0x58));
            } else if ((*(s32 *)(mp + 0x4C) & 9) == 8) {
                addVec3At0x24(m, *(f32 *)(mp + 0x78), *(f32 *)(mp + 0x7C), *(f32 *)(mp + 0x80));
            } else if (*(s32 *)(mp + 0x4C) & 1) {
                addVec3At0x24(m, *(f32 *)(mp + 0x50), *(f32 *)(mp + 0x54), *(f32 *)(mp + 0x58));
            }
        }
        pos = s4 + 4;
        mat34CrossRowsAndCopyPos(*(u8 **)s4 + 0x28, pos, 0.2f);
        one = 1.0f;
        mat34CrossRowsAndCopyPos(D_main_bss_8013800C, pos, one);
        enqueueMeshTypeForCleanup(*(void **)s4);
        if (*(u16 *)(s4 + 0x180) & 0x100) {
            return 1;
        }
        if (*(u16 *)(((PasEnt *)D_main_bss_80138D18)[*(s32 *)(s4 + 0xB8)].p + 4) != 3) {
            addNpcToVisibilityBucket(*(s32 *)a4, *(void **)s4, pos, one);
            if (s2->hAC != 0xFFFF) {
                slotDispatcherIter(s2->hAC, 0xE, arg2);
            }
            if (!(*(u16 *)(s4 + 0x180) & 0x80)) {
                advanceNpcOnCurvedPath(*(s32 *)(a4 + 8), *(s32 *)a4, pos, *(void **)(s4 + 0xBC));
            }
        }
        updatePlayerHudFrame(0, a4, s4 + 4);
        break;
    }
    }
    return 1;
}

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
