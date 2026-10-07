#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A5990);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A5998);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A59A0);

extern u8 awCraftBytes[][0x2A0] __asm__("D_main_bss_80137DBC");
extern s32 D_main_bss_80130B58;
extern void initPlayerCraftMovementMode(void *);
s32 awLookupMat(s32, char *, void *) __asm__("lookupHmtMaterialByName");

void playerAwingInit(s32 *arg0, s32 arg1, s32 arg2) {
    u8 *p = awCraftBytes[arg1];
    f32 hp;
    f32 a, b, c, d, e, f, g, h, i, j, k, l, m, n, o;
    *(s16 *)(p + 0x180) = arg2;
    arg0[0] = arg1;
    *(u16 *)(p + 0xB4) = 2;
    initPlayerCraftMovementMode(p);
    hp = 75.0f;
    if (D_main_bss_80130B58 & 0x40) {
        hp = 40.0f;
    }
    a = 0.046875f;
    b = 3.0f;
    c = 0.03125f;
    d = 1.6f;
    e = 1.8f;
    f = 15.0f;
    g = 10.0f;
    h = -40.0f;
    i = -38.23f;
    j = 40.0f;
    k = 65.0f;
    l = 180.0f;
    m = 0.75f;
    n = 2.0f;
    o = 0.1f;
    *(f32 *)(p + 0xC0) = hp;
    *(f32 *)(p + 0xC4) = hp;
    *(s32 *)(p + 0x13C) = 0;
    *(s32 *)(p + 0x14C) = 0;
    *(s32 *)(p + 0x11C) = 0;
    *(s32 *)(p + 0xD8) = 0;
    *(s32 *)(p + 0xDC) = 0;
    *(s32 *)(p + 0xE0) = 0;
    *(s16 *)(p + 0x158) = 0;
    *(f32 *)(p + 0xE8) = b;
    *(f32 *)(p + 0xEC) = b;
    *(f32 *)(p + 0xF0) = a;
    *(f32 *)(p + 0xF4) = c;
    *(f32 *)(p + 0xF8) = d;
    *(f32 *)(p + 0xFC) = e;
    *(f32 *)(p + 0x104) = f;
    *(f32 *)(p + 0x108) = g;
    *(f32 *)(p + 0x110) = h;
    *(f32 *)(p + 0x114) = i;
    *(f32 *)(p + 0x118) = j;
    *(f32 *)(p + 0x120) = k;
    *(f32 *)(p + 0x124) = l;
    *(f32 *)(p + 0x130) = m;
    *(f32 *)(p + 0x134) = n;
    *(f32 *)(p + 0x138) = 20.0f;
    *(f32 *)(p + 0x140) = g;
    *(f32 *)(p + 0x144) = 60.0f;
    *(f32 *)(p + 0x148) = g;
    *(f32 *)(p + 0x150) = 5.0f;
    *(f32 *)(p + 0x154) = 50.0f;
    *(f32 *)(p + 0x128) = o;
    *(f32 *)(p + 0x12C) = o;
    *(u8 *)((u8 *)arg0 + 0x48) = 0;
    *(s32 *)(p + 0x160) = 0;
    *(f32 *)(p + 0x164) = o;
    *(f32 *)(p + 0x168) = 0.4f;
    *(s32 *)(p + 0x170) = 0;
    *(f32 *)(p + 0x174) = o;
    arg0[3] = awLookupMat(*(s32 *)p, "f_trns_l", arg0 + 1);
    arg0[4] = awLookupMat(*(s32 *)p, "f_trns_r", arg0 + 2);
    arg0[7] = awLookupMat(*(s32 *)p, "rot_b", arg0 + 5);
    arg0[8] = awLookupMat(*(s32 *)p, "rot_a", arg0 + 6);
    arg0[0xB] = awLookupMat(*(s32 *)p, "l_gn_trn", arg0 + 9);
    arg0[0xC] = awLookupMat(*(s32 *)p, "r_gn_trn", arg0 + 0xA);
    *(u16 *)((u8 *)arg0 + 0x34) = 0xFFFF;
    arg0[0xE] = 0;
    arg0[0xF] = 0;
}

typedef struct {
    s32 unk0;
    u8 pad4[0xB4];
    s32 unkB8;
    u8 padBC[0xE8 - 0xBC];
    f32 unkE8;
    f32 unkEC;
    f32 unkF0;
    f32 unkF4;
    u8 padF8[0x180 - 0xF8];
    u16 unk180;
    u8 pad182[0x2A0 - 0x182];
} TrailObj;
typedef struct {
    u8 pad0[0x4C];
    s32 flags;
    f32 pos[3];
    f32 scale[3];
    f32 quat[4];
    f32 off[3];
} TrailNode;
typedef struct {
    s32 unk0;
    TrailNode *n4;
    TrailNode *n8;
    u8 *unkC;
    u8 *unk10;
    TrailNode *n14;
    TrailNode *n18;
    u8 *unk1C;
    u8 *unk20;
} TrailArg;
typedef struct {
    u16 pad0[3];
    u16 unk6;
    u16 pad8[5];
    u16 unk12;
    u16 pad14[2];
    u16 unk18;
    u16 pad1A[3];
    u16 unk20;
    u16 pad22;
} TrailBtn;
extern TrailObj D_trail_objs[] __asm__("D_main_bss_80137DBC");
extern u16 D_main_bss_80130B88[][3];
extern TrailBtn D_mission_overlay_8010BE18[];
extern f32 D_mission_overlay_8010BDD8[][2];
extern u8 D_main_bss_8013800C[];
u8 getCraftAnimationSlotFlag(s32);
f32 getCraftAnimationSlotValue(s32);
void setCraftAnimationSlotParams(s32, s32, f32);
void updatePlayerCraftPhysics(TrailObj *, f32);
void computeBootConfigScaledVec4(s32, f32, f32, u8 *, f32, f32);
void clearVec4QuadStruct(u8 *);
void addVec3At0x24(u8 *, f32, f32, f32);
void applyScaleToMat3x4(u8 *, f32, f32, f32);
void composeQuatToMat3x4(u8 *, f32 *);
void composeRotationMatrixSlot1(u8 *, f32);

static __inline__ void placeTrailQuad(u8 *q, TrailNode *n, f32 ang) {
    clearVec4QuadStruct(q);
    if (n->flags & 1) {
        addVec3At0x24(q, -n->pos[0], -n->pos[1], -n->pos[2]);
    }
    if (n->flags & 2) {
        applyScaleToMat3x4(q, n->scale[0], n->scale[1], n->scale[2]);
    }
    if (n->flags & 4) {
        composeQuatToMat3x4(q, n->quat);
    }
    composeRotationMatrixSlot1(q, ang);
    if ((n->flags & 9) == 9) {
        addVec3At0x24(q, n->off[0] + n->pos[0], n->off[1] + n->pos[1], n->off[2] + n->pos[2]);
    } else if ((n->flags & 9) == 8) {
        addVec3At0x24(q, n->off[0], n->off[1], n->off[2]);
    } else if (n->flags & 1) {
        addVec3At0x24(q, n->pos[0], n->pos[1], n->pos[2]);
    }
}

void resetEngineTrailQuads(TrailArg *arg0, f32 arg1) {
    TrailObj *o = &D_trail_objs[arg0->unk0];
    f32 v;
    TrailNode *n;
    u8 *q;
    f32 ang;

    if (*(u16 *)((s32)D_trail_objs + o->unkB8 * sizeof(TrailObj) + 0x180) & 1) {
        v = o->unkEC;
        if (D_main_bss_80130B88[arg0->unk0][0] & D_mission_overlay_8010BE18[arg0->unk0].unk12) {
            v -= 0.09375f;
        }
        if (v < 2.25f) {
            v = 2.25f;
        }
        if (D_main_bss_80130B88[arg0->unk0][0] & D_mission_overlay_8010BE18[arg0->unk0].unk18) {
            v += 0.09375f;
            if (getCraftAnimationSlotFlag(0) == 0) {
                setCraftAnimationSlotParams(0, 1, 0);
            }
        } else if (getCraftAnimationSlotFlag(0) == 1) {
            if (getCraftAnimationSlotValue(0) == 0.0f) {
                setCraftAnimationSlotParams(0, 1, 0.5f);
            }
        }
        if (!(D_main_bss_80130B88[arg0->unk0][0] & D_mission_overlay_8010BE18[arg0->unk0].unk12) && !(D_main_bss_80130B88[arg0->unk0][0] & D_mission_overlay_8010BE18[arg0->unk0].unk18) && o->unkE8 < 3.0f) {
            v += 0.09375f;
            if (v > 3.0f) {
                v = 3.0f;
            }
        }
        if (v > 5.625f) {
            v = 5.625f;
        }
        o->unkEC = v;
        if (o->unkF0 < v - o->unkE8) {
            o->unkE8 = o->unkE8 + o->unkF0;
        } else {
            o->unkE8 = v;
        }
        if (v - o->unkE8 < -o->unkF4) {
            o->unkE8 = o->unkE8 - o->unkF4;
        } else {
            o->unkE8 = v;
        }
    }
    updatePlayerCraftPhysics(o, arg1);
    computeBootConfigScaledVec4(arg0->unk0, 0.28125f, 0.28125f, D_main_bss_8013800C + arg0->unk0 * 0x2A0, (o->unkE8 - 2.25f) / 3.375f + 1.5f, arg1);
    {
        if (!(D_main_bss_80130B88[arg0->unk0][0] & D_mission_overlay_8010BE18[arg0->unk0].unk6) && !(D_main_bss_80130B88[arg0->unk0][0] & D_mission_overlay_8010BE18[arg0->unk0].unk20)) {
            n = arg0->n4;
            q = arg0->unkC + 0x1C;
            ang = D_mission_overlay_8010BDD8[o->unkB8][0] * -20.25f * 0.5f;
            placeTrailQuad(q, n, ang);
            n = arg0->n14;
            q = arg0->unk1C + 0x1C;
            ang = D_mission_overlay_8010BDD8[o->unkB8][0] * -31.5f * 0.5f;
            placeTrailQuad(q, n, ang);
            n = arg0->n8;
            q = arg0->unk10 + 0x1C;
            ang = D_mission_overlay_8010BDD8[o->unkB8][0] * -20.25f * 0.5f;
            placeTrailQuad(q, n, ang);
            n = arg0->n18;
            q = arg0->unk20 + 0x1C;
            ang = D_mission_overlay_8010BDD8[o->unkB8][0] * -31.5f * 0.5f;
            placeTrailQuad(q, n, ang);
        }
    }
}

typedef struct { f32 x, y, z; } LockVec3;
typedef struct {
    f32 pos[3];
    u8 pad0C[0x24 - 0xC];
    f32 vel[3];
} LockNpcData;
typedef struct {
    u8 pad0[8];
    LockNpcData *data;
    void *part;
    u8 pad10[4];
    u16 flags;
} LockNpc;
extern u16 D_mission_overlay_80109874[];
extern u16 D_main_bss_80139560[];
extern s32 findActiveNpcInSlotChain(u16, void *);
extern LockNpc *getNpcCtxL(u16) __asm__("getNpcContextByIndex");
extern s32 revalidateNpcSlotIterator(void *);
extern void transformMeshPartIntoWorld(void *, f32 *);
extern f32 vec3DotL(f32 *, f32 *) __asm__("vec3Dot");
extern f32 vec3LenL(f32 *) __asm__("vec3Length");
extern void normVecL(f32 *) __asm__("normalize_vector");

u16 acquireLockOnTargetImpl(f32 *src, f32 *out, u16 cur, f32 range, f32 minDot, f32 lead, u8 mode) __asm__("acquireLockOnTarget");
u16 acquireLockOnTargetImpl(f32 *src, f32 *out, u16 cur, f32 range, f32 minDot, f32 lead, u8 mode) {
    f32 d[3];
    f32 aim[3];
    f32 pos[3];
    f32 org[3];
    u8 iter[8];
    f32 bestScore;
    f32 minD;
    f32 len;
    f32 dot;
    f32 t;
    u16 best;
    u16 cid;
    s32 id;
    s32 k;
    LockNpc *npc;

    minD = range * 0.1f;
    org[0] = src[0] - src[3] * minD;
    org[1] = src[1] - src[4] * minD;
    best = 0xFFFF;
    org[2] = src[2] - src[5] * minD;
    range = range * 1.1f;
    if (D_mission_overlay_80109874[0] != 0xFFFF) {
        k = 0;
        do {
            id = findActiveNpcInSlotChain(D_main_bss_80139560[D_mission_overlay_80109874[k]], iter);
            while ((id & 0xFFFF) != 0xFFFF) {
                npc = getNpcCtxL(id & 0xFFFF);
                if (!(npc->flags & 0x100)) {
                    if (npc->part != 0) {
                        transformMeshPartIntoWorld(npc->part, pos);
                    } else {
                        *(LockVec3 *)pos = *(LockVec3 *)npc->data;
                    }
                    d[0] = pos[0] - org[0];
                    d[1] = pos[1] - org[1];
                    d[2] = pos[2] - org[2];
                    len = vec3LenL(d);
                    if (len < range && minD < len) {
d[0] /= len;
                        d[1] /= len;
                        d[2] /= len;
                        if (lead != 0.0f) {
                            t = len / lead;
                            aim[0] = pos[0] + npc->data->vel[0] * t;
                            aim[1] = pos[1] + npc->data->vel[1] * t;
                            aim[2] = pos[2] + npc->data->vel[2] * t;
                            d[0] = aim[0] - org[0];
                            d[1] = aim[1] - org[1];
                            d[2] = aim[2] - org[2];
                            normVecL(d);
                        } else {
                            *(LockVec3 *)aim = *(LockVec3 *)pos;
                        }
                        dot = vec3DotL(d, src + 3);
                        if (minDot < dot) {
                            switch (mode) {
                            case 1:
                                if (vec3DotL(src + 6, d) > 0.0f) {
                                    goto next;
                                }
                                break;
                            case 2:
                                if (vec3DotL(src + 6, d) < 0.0f) {
                                    goto next;
                                }
                                break;
                            }
                            cid = id;
                            if (cid == cur) {
                                *(LockVec3 *)out = *(LockVec3 *)aim;
                                return cid;
                            }
                            len = len * ((1.0f - dot) * 180.0f + 1.0f);
                            if ((best & 0xFFFF) == 0xFFFF || !(bestScore < len)) {
                                best = id;
                                bestScore = len;
                                *(LockVec3 *)out = *(LockVec3 *)aim;
                            }
                        }
                    }
                }
            next:
                id = revalidateNpcSlotIterator(iter);
            }
k++;
        } while (D_mission_overlay_80109874[k] != 0xFFFF);
    }
    return best;
}

typedef struct {
    s32 unk0;
    u8 pad4[0xB2];
    u16 unkB6;
    u8 padB8[0xB4];
    f32 unk16C;
    u8 pad170[0x2A0 - 0x170];
} ImpactObj;
typedef struct {
    u8 pad0[4];
    struct { u8 pad[4]; u16 unk4; } *unk4;
} ImpactAux;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} ImpV3;
extern ImpactObj D_main_bss_80137DBC[];
extern u8 D_main_bss_80138D18[];
extern f32 D_mission_overlay_80109880[][3];
extern u8 D_mission_overlay_80109800[];
void lookupHmtTextureByName(s32, char *, s32, f32 *, s32, s32);
void accumulateVectorInObjectFrame(f32 *, f32 *, void *);
void quatFromAxisAngle(f32 *, f32 *, f32);
void rotateVec3ByQuat(f32 *, f32 *, f32 *);
void dispatchCueByCategory(s32, u16, f32 *, void *, s32, f32, f32);

void emitTexturedImpactEffect(u8 *arg0, s32 arg1, ImpV3 *arg2) {
    f32 m[4][3];
    ImpV3 sp50;
    f32 sp60[4];
    ImpactObj *o;
    s32 bit;
    f32 v;
    char *name;

    o = &D_main_bss_80137DBC[*(s32 *)arg0];
    if (arg1 & 1) {
        lookupHmtTextureByName(o->unk0, "b", 0, m[0], 0, 0);
    } else {
        lookupHmtTextureByName(o->unk0, "a", 0, m[0], 0, 0);
    }
    if (((ImpactAux *)(D_main_bss_80138D18 + *(s32 *)arg0 * 0x144))->unk4->unk4 == 3) {
        bit = arg1 & 1;
        accumulateVectorInObjectFrame(m[0], D_mission_overlay_80109880[bit], o);
        if (bit != 0) {
            v = *(f32 *)(arg0 + 0x44);
            if (v > 0.0f) {
                if (v < 18.0f) {
                    quatFromAxisAngle(sp60, m[2], -v * 0.8f);
                    sp50 = *(ImpV3 *)m[1];
                    rotateVec3ByQuat(sp60, (f32 *)&sp50, m[1]);
                }
            }
        } else {
            v = *(f32 *)(arg0 + 0x40);
            if (v < 0.0f) {
                if (v > -18.0f) {
                    quatFromAxisAngle(sp60, m[2], -v * 0.8f);
                    sp50 = *(ImpV3 *)m[1];
                    rotateVec3ByQuat(sp60, (f32 *)&sp50, m[1]);
                }
            }
        }
    }
    dispatchCueByCategory(0, o->unkB6, m[0], D_mission_overlay_80109800, 1, 15.0f, o->unk16C);
    *arg2 = *(ImpV3 *)m[0];
}

typedef struct {
    u8 pad0[0x4C];
    u32 flags;
    f32 pos[3];
    f32 scale[3];
    f32 quat[4];
    f32 off[3];
} ThrustCfg;

typedef struct {
    s32 index;
    u8 pad4[0x20];
    ThrustCfg *cfgA;
    ThrustCfg *cfgB;
    u8 *matA;
    u8 *matB;
    u16 target;
    u16 pad36;
    f32 cur;
    f32 goal;
    f32 left;
    f32 right;
    u8 toggle;
} ThrustState;

typedef struct {
    s32 unk0;
    u8 pad4[0xC];
    f32 vel[3];
    u8 pad1C[0xB6 - 0x1C];
    u16 unkB6;
    s32 unkB8;
    u8 padBC[0x158 - 0xBC];
    u16 unk158;
    u8 pad15A[2];
    s32 unk15C;
    f32 unk160;
    f32 unk164;
    f32 unk168;
    u8 pad16C[0x178 - 0x16C];
    s32 unk178;
    u8 pad17C[0x2A0 - 0x17C];
} ThrustPlayer;

typedef struct {
    u8 pad0[0x1A];
    u16 mask1A;
    u8 pad1C;
    u8 mask1D;
    u16 mask1E;
    u8 pad20[0x4];
} ThrustHud;

extern ThrustPlayer gThrustPlayers[] __asm__("D_main_bss_80137DBC");
extern u16 D_main_bss_80130B88[][3];
extern ThrustHud gThrustHud[] __asm__("D_mission_overlay_8010BE18");
extern f32 D_mission_overlay_80109888;
extern u8 D_mission_overlay_80109898[];
extern u8 D_mission_overlay_801098A4[];
u16 acquireLockOnTarget(s32 arg0, s32 arg1, u16 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
u8 tickHudInstanceTargetingAndSpawns(s32, f32, void *, s32, s32, void *, s32);
void dispatchHudInstanceWeaponEffect(s32, s32, void *, s32, s32, s32, s32);
void tickCraftAnimationSlot(s32, f32);
void mat34CrossRowsAndCopyPos(void *, void *, f32, s32);
s32 acquireLockOnTargetS(s32 arg0, s32 arg1, u16 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6) __asm__("acquireLockOnTarget");
s32 acquireLockOnTargetP(void *arg0, f32 *arg1, u16 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) __asm__("acquireLockOnTarget");
void mat3x3InverseInto(void *, void *);
void transformVec3ByMat34(void *, void *, void *);
f32 normalize_vector(void *);
f32 vec3Dot(void *, void *);
f32 vec3Length(void *);
f32 sinfApprox(f32);
void composeRotationMatrixSlot0(void *, f32);

void updateEngineThrustEffectImpl(ThrustState *arg0, f32 dt) __asm__("updateEngineThrustEffect");
static __inline__ s32 uetLock(u8 *a, f32 *t, u16 c) {
    return acquireLockOnTargetP(a, t, c, 10.0f, 0.9659258f, 15.0f, 0);
}
static __inline__ void uetPlace(u8 *mat, ThrustCfg *cfg, f32 yaw) {
    u32 fl;
    u32 t9;
    clearVec4QuadStruct(mat);
    if (cfg->flags & 1) {
        addVec3At0x24(mat, -cfg->pos[0], -cfg->pos[1], -cfg->pos[2]);
    }
    if (cfg->flags & 2) {
        applyScaleToMat3x4(mat, cfg->scale[0], cfg->scale[1], cfg->scale[2]);
    }
    if (cfg->flags & 4) {
        composeQuatToMat3x4(mat, cfg->quat);
    }
    composeRotationMatrixSlot0(mat, yaw);
    fl = cfg->flags;
    t9 = fl & 9;
    if (t9 == 9) {
        addVec3At0x24(mat, cfg->off[0] + cfg->pos[0], cfg->off[1] + cfg->pos[1], cfg->off[2] + cfg->pos[2]);
    } else if (t9 == 8) {
        addVec3At0x24(mat, cfg->off[0], cfg->off[1], cfg->off[2]);
    } else if (fl & 1) {
        addVec3At0x24(mat, cfg->pos[0], cfg->pos[1], cfg->pos[2]);
    }
}

void updateEngineThrustEffectImpl(ThrustState *arg0, f32 dt) {
    f32 m[12];
    f32 inv[12];
    f32 local[4];
    f32 target[4];
    ImpV3 pos;
    f32 vr[4];
    f32 vl[4];
    u16 out;
    s32 id;
    ThrustPlayer *p;
    u8 *b;
    f32 cur;
    f32 yaw;
    u8 *mat;
    ThrustCfg *cfg;
    u32 fl;
    u32 t9;

    p = &gThrustPlayers[arg0->index];
    b = (u8 *)gThrustPlayers - 4;
    if (*(u16 *)(b + p->unkB8 * 0x2A0 + 0x184) & 1) {
        if (0.0f < p->unk160) {
            p->unk160 = p->unk160 - dt;
        } else if (D_main_bss_80130B88[arg0->index][0] & gThrustHud[arg0->index].mask1A) {
            if (*(s32 *)(b + arg0->index * 0x2A0 + 0x160) == 1) {
                p->unk160 = p->unk160 + p->unk168;
                emitTexturedImpactEffect((u8 *)arg0, p->unk158, &pos);
                play3DSoundEvent(0, &pos, (u8 *)p + 0x28, 20.0f, 0.2f, 0, 2, 0x5A, 0x28);
                emitTexturedImpactEffect((u8 *)arg0, p->unk158 + 1, &pos);
                play3DSoundEvent(0, &pos, (u8 *)p + 0x28, 20.0f, 0.2f, 0, 2, 0x5A, 0x28);
                p->unk158 = p->unk158 ^ 2;
            } else {
                p->unk160 = p->unk160 + p->unk164;
                emitTexturedImpactEffect((u8 *)arg0, p->unk158, &pos);
                p->unk158 = (p->unk158 + 1) & 1;
                play3DSoundEvent(0, &pos, (u8 *)p + 0x28, 20.0f, 0.2f, 0, 2, 0x5A, 0x28);
            }
        }
        if (tickHudInstanceTargetingAndSpawns(0, dt, (u8 *)p + 4, p->unk0, (D_main_bss_80130B88[arg0->index][0] & 0xFF) & gThrustHud[arg0->index].mask1D, &out, p->unkB6)) {
            dispatchHudInstanceWeaponEffect(0, p->unkB6, (u8 *)p + 4, p->unk0, p->unk178, arg0->toggle, out);
            arg0->toggle = arg0->toggle ^ 1;
        }
        if (D_main_bss_80130B88[arg0->index][0] & gThrustHud[arg0->index].mask1E) {
            p->unk158 = 0;
            p->unk15C = p->unk15C ^ 1;
        }
    }
    id = uetLock((u8 *)p + 4, target, arg0->target);
    out = id;
    if ((id & 0xFFFF) != 0xFFFF) {
        arg0->target = id;
        mat34CrossRowsAndCopyPos(m, (u8 *)p + 4, 1.0f, id);
        if (((ImpactAux *)(D_main_bss_80138D18 + arg0->index * 0x144))->unk4->unk4 == 3) {
            m[9] += p->vel[0] * D_mission_overlay_80109888;
            m[10] += p->vel[1] * D_mission_overlay_80109888;
            m[11] += p->vel[2] * D_mission_overlay_80109888;
        }
        mat3x3InverseInto(inv, m);
        transformVec3ByMat34(inv, &target[0], local);
        if (vec3Length(local) <= 0.0f) {
            goto zero;
        }
        vl[1] = 0.0f;
        vl[2] = local[2];
        vl[0] = local[0] + -0.4f;
        normalize_vector(vl);
        arg0->left = sinfApprox(vec3Dot(vl, D_mission_overlay_801098A4)) * 57.295776f;
        vr[1] = 0.0f;
        vr[2] = local[2];
        vr[0] = local[0] + 0.4f;
        normalize_vector(vr);
        arg0->right = sinfApprox(vec3Dot(vr, D_mission_overlay_801098A4)) * 57.295776f;
        local[0] = 0.0f;
        normalize_vector(local);
        arg0->goal = sinfApprox(vec3Dot(local, D_mission_overlay_80109898)) * 57.295776f;
    } else {
zero:
        arg0->goal = arg0->left = arg0->right = 0.0f;
    }
    cur = arg0->cur;
    if (cur < arg0->goal) {
        arg0->cur = cur + dt * 21.0f;
        if (arg0->cur > arg0->goal) {
            arg0->cur = arg0->goal;
        }
    } else {
        arg0->cur = cur - dt * 21.0f;
        if (arg0->cur < arg0->goal) {
            arg0->cur = arg0->goal;
        }
    }
    uetPlace(arg0->matA + 0x1C, arg0->cfgA, arg0->cur);
    uetPlace(arg0->matB + 0x1C, arg0->cfgB, arg0->cur);
    tickCraftAnimationSlot(0, dt);
}

#include "main/3F160.h"
#include "main/02420.h"
typedef struct {
    /* 0x000 */ s32 mesh;
    /* 0x004 */ u8 pad4[0xB0];
    /* 0x0B4 */ u16 hB4;
    /* 0x0B6 */ u16 hB6;
    /* 0x0B8 */ s32 index;
    /* 0x0BC */ s32 ctx;
    /* 0x0C0 */ u8 padC0[0x178 - 0xC0];
    /* 0x178 */ s32 w178;
    /* 0x17C */ u8 pad17C[4];
    /* 0x180 */ u16 flags;
    /* 0x182 */ u8 pad182[2];
    /* 0x184 */ f32 f184;
    /* 0x188 */ u8 pad188[0x2A0 - 0x188];
} AwUpdPlayer;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 *state;
    /* 0x08 */ void *w8;
    /* 0x0C */ s32 mesh;
    /* 0x10 */ u8 pad10[6];
    /* 0x16 */ u16 h16;
} AwUpdNpc;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u8 *p4;
    /* 0x08 */ u8 pad8[0x144 - 8];
} AwUpdCam;

#define AUP ((AwUpdPlayer *)D_main_bss_80137DBC)
extern u16 D_main_bss_80139560[];
extern u8 D_mission_overlay_8010986C[];
extern s32 D_mission_overlay_8010CA1C;
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];

void *walkMeshdef0List(char *);
void playerAwingInit(s32 *, s32, s32);
void loadPlayerStartPosition(void *, void *);
s32 refreshPlayerSecondaryWeaponHud(s32);
void allocateCraftAnimationStateForSlot(void *, s32, void *);
s32 allocateAndInitCraftNpcContext(f32, f32, s32);
void resetTransientPlayerStateFlags(void);
void resetCraftAnimationStateForSlot(s32);
void destroySceneNpcsAndUnlink(void *);
void cancelSceneQueueHandle(void *);
void releaseMeshAsset(s32);
void teardownHudInstancesAndUnbindNpcs(void);
void freePlayerAuxBuffersIfActive(s32);
void resetEngineTrailQuadsCall(s32 *, s32) __asm__("resetEngineTrailQuads");
void updateEngineThrustEffect(s32 *, s32);
void tryPlaySpatialSoundWithGates(void *, void *);
void enqueueMeshTypeForCleanup(s32);
void addNpcToVisibilityBucket(s32, s32, void *, f32);
void advanceNpcOnCurvedPath(s32, s32, void *, s32);
void updatePlayerHudFrame(s32, void *, void *);

s32 playerAwingUpdate(AwUpdNpc *arg0, s32 arg1, u32 *arg2) {
    s32 *s0;
    AwUpdPlayer *p;
    s32 flag;
    u16 sp10[2];
    u16 act;
    f32 *q;

    s0 = arg0->state;
    if ((arg1 & 0xFFFF) == 2 || !(D_mission_overlay_8010CA1C & 4)) {
        act = arg1;
        switch (act) {
        case 1:
            q = (f32 *)arg2;
            s0 = rs_malloc(0x4C, 0);
            arg0->state = s0;
            p = &AUP[(s32)*(f32 *)arg2];
            p->mesh = (s32)walkMeshdef0List("awing");
            p->hB6 = arg0->h16;
            arg0->mesh = p->mesh;
            arg0->w8 = (u8 *)p + 4;
            if (0.0f <= *(f32 *)arg2) {
                *(u16 *)((u8 *)&AUP[(s32)*(f32 *)arg2] - 2) = arg0->h16;
                p->index = (s32)*(f32 *)arg2;
                flag = 1;
            } else {
                flag = 0;
            }
            loadPlayerStartPosition(p, NULL);
            playerAwingInit(s0, (s32)*q, flag);
            p->w178 = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
            allocateCraftAnimationStateForSlot(p, 0, D_mission_overlay_8010986C);
            popNpcSlotFromTail(D_main_bss_80139560[1], (void *)arg0);
            popNpcSlotFromTail(D_main_bss_80139560[14], (void *)arg0);
            p->ctx = allocateAndInitCraftNpcContext(0.125f, 0.125f, 0);
            sp10[0] = arg0->h16;
            sp10[1] = p->hB4;
            spawnNpcOfType((void *)attached3DSoundEmitterNpcHandler, sp10, 1, 0x64);
            spawnNpcOfType((void *)attachedMeshOverlayNpcHandler, &arg0->h16, 1, 0x64);
            return 1;
        case 12:
            p = &AUP[*s0];
            p->f184 = 2.0f;
            p->flags = (p->flags & 0xFFDF) | 0x40;
            loadPlayerStartPosition(p, (u8 *)p + 4);
            playerAwingInit(s0, p->index, 0x40);
            resetTransientPlayerStateFlags();
            resetCraftAnimationStateForSlot(0);
            return 1;
        case 2:
            p = &AUP[*s0];
            destroySceneNpcsAndUnlink(p);
            cancelSceneQueueHandle(p);
            rs_free((void *)p->ctx);
            releaseMeshAsset(p->mesh);
            teardownHudInstancesAndUnbindNpcs();
            freePlayerAuxBuffersIfActive(0);
            return 1;
        case 3:
            resetEngineTrailQuadsCall(s0, *arg2);
            updateEngineThrustEffect(s0, *arg2);
            return 1;
        case 5:
            tryPlaySpatialSoundWithGates(&AUP[*s0], arg2);
            if (*(u16 *)arg2 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)arg2);
            }
            return 1;
        case 4:
            p = &AUP[*s0];
            enqueueMeshTypeForCleanup(p->mesh);
            if (!(p->flags & 0x100)) {
                if (*(u16 *)(((AwUpdCam *)D_main_bss_80138D18)[p->index].p4 + 4) != 3) {
                    addNpcToVisibilityBucket(arg2[0], p->mesh, (u8 *)p + 4, 1.0f);
                    if (!(p->flags & 0x80)) {
                        advanceNpcOnCurvedPath(arg2[2], arg2[0], (u8 *)p + 4, p->ctx);
                    }
                }
                updatePlayerHudFrame(0, arg2, (u8 *)p + 4);
            }
            return 1;
        }
    }
    return 1;
}

u16 acquireLockOnTarget(s32 arg0, s32 arg1, u16 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6);

u16 findLockOnTarget(s32 arg0, s32 arg1, u16 arg2, s32 arg3, f32 arg4, f32 arg5) {
    return acquireLockOnTarget(arg0, arg1, arg2, arg3, arg4, arg5, 0);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", fake_func_800B75C4);


// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
const u32 rodat_pad_0B64C0[2] = { 0x93C20000, 0x24430001 };
