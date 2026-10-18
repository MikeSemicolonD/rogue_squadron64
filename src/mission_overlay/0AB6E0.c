#include "common.h"
#include "common_types.h"
#include "rs_math.h"

extern u8 ssCraftBytes[][0x2A0] __asm__("D_main_bss_80137DBC");
extern struct { u8 pad[0xC]; u32 pl[3]; u32 flags; } ssGs __asm__("gGameSettings");
extern u8 D_main_8009EBBC;
extern void ssInitMove(void *) __asm__("initPlayerCraftMovementMode");
s32 ssLookupMat(s32, char *, void *) __asm__("lookupHmtMaterialByName");
void ssResetFx(void) __asm__("resetEffectSequenceState");

void ssImpl(u8 *arg0, s32 arg1, s32 arg2) __asm__("playerSnowSpeederInit");
void ssImpl(u8 *arg0, s32 arg1, s32 arg2) {
    u8 *p = ssCraftBytes[arg1];
    f32 hp;
    f32 a, d, e, f, g, h, i, j, k, l, m, n, o, q, r;
    *(s16 *)(p + 0x180) = arg2;
    *(s32 *)arg0 = arg1;
    *(u16 *)(p + 0xB4) = 4;
    ssInitMove(p);
    if (ssGs.flags & 0x40) {
        hp = 40.0f;
    } else {
        hp = 150.0f;
    }
    *(f32 *)(p + 0xC0) = hp;
    *(f32 *)(p + 0xC4) = hp;
    *(f32 *)(p + 0xE8) = (arg0[0x2D] == 0) ? 2.625f : 1.3125f;
    *(f32 *)(p + 0xEC) = (arg0[0x2D] == 0) ? 2.625f : 1.3125f;
    *(f32 *)(p + 0xF0) = (arg0[0x2D] == 0) ? 0.11875f : 0.059375f;
    a = (arg0[0x2D] == 0) ? 0.11875f : 0.059375f;
    *(f32 *)(p + 0xF8) = 1.4f;
    d = 1.8f;
    e = 15.0f;
    f = 10.0f;
    g = 1.0f;
    h = -40.0f;
    i = 35.0f;
    j = 0.75f;
    k = 3.0f;
    l = 20.0f;
    m = 60.0f;
    n = 5.0f;
    o = 40.0f;
    q = 0.2f;
    r = 0.15f;
    *(f32 *)(p + 0xF4) = a;
    *(s32 *)(p + 0x13C) = 0;
    *(s32 *)(p + 0x14C) = 0;
    *(s32 *)(p + 0x11C) = 0;
    *(s32 *)(p + 0xD8) = 0;
    *(s32 *)(p + 0xDC) = 0;
    *(s32 *)(p + 0xE0) = 0;
    *(s16 *)(p + 0x158) = 0;
    *(s32 *)(p + 0x160) = 0;
    *(s32 *)(p + 0x170) = 0;
    *(s32 *)(p + 0x168) = 0;
    *(s32 *)(p + 0x174) = 0;
    *(f32 *)(p + 0xFC) = d;
    *(f32 *)(p + 0x104) = e;
    *(f32 *)(p + 0x108) = f;
    *(f32 *)(p + 0x10C) = g;
    *(f32 *)(p + 0x110) = h;
    *(f32 *)(p + 0x114) = h;
    *(f32 *)(p + 0x118) = i;
    *(f32 *)(p + 0x120) = i;
    *(f32 *)(p + 0x124) = i;
    *(f32 *)(p + 0x130) = j;
    *(f32 *)(p + 0x134) = k;
    *(f32 *)(p + 0x138) = l;
    *(f32 *)(p + 0x140) = f;
    *(f32 *)(p + 0x144) = m;
    *(f32 *)(p + 0x148) = f;
    *(f32 *)(p + 0x150) = n;
    *(f32 *)(p + 0x154) = o;
    *(f32 *)(p + 0x128) = q;
    *(f32 *)(p + 0x12C) = r;
    *(f32 *)(p + 0x164) = 0.137f;
    ssGs.pl[arg1] &= ~0x1000000;
    ((s32 *)arg0)[1] = 0;
    ((s32 *)arg0)[2] = 0;
    ((s32 *)arg0)[3] = ssLookupMat(*(s32 *)p, "botrns_l", arg0 + 0x1C);
    ((s32 *)arg0)[4] = ssLookupMat(*(s32 *)p, "botrns_r", arg0 + 0x20);
    ((s32 *)arg0)[5] = ssLookupMat(*(s32 *)p, "uptrns_l", arg0 + 0x24);
    ((s32 *)arg0)[6] = ssLookupMat(*(s32 *)p, "uptrns_r", arg0 + 0x28);
    *(s32 *)(p + 0x194) = 4;
    ssResetFx();
    arg0[0x2F] = 0xFF;
    arg0[0x2C] = 0;
    arg0[0x2D] = 0;
    arg0[0x11C] = 0;
    D_main_8009EBBC = 0;
    *(u16 *)(arg0 + 0x10C) = 0xFFFF;
}

typedef struct {
    union { u8 pad0[0xB8]; f32 mat0[4][3]; } u0;
    s32 tgt;
    u8 padBC[0xE8 - 0xBC];
    f32 fE8;
    f32 fEC;
    f32 fF0;
    f32 fF4;
    u8 padF8[0x118 - 0xF8];
    f32 f118;
    u8 pad11C[0x180 - 0x11C];
    u16 h180;
    u8 pad182[0x250 - 0x182];
    f32 mat[4][3];
    u8 pad280[0x2A0 - 0x280];
} CePl;
typedef struct {
    u8 pad0[6];
    u16 h6;
    u8 pad8[0xC];
    u16 h14;
    u16 h16;
    u16 h18;
    u8 pad1A[0xA];
} CeBtn;
typedef struct {
    s32 idx;
    f32 f4;
    f32 f8;
    u8 *n[4];
    u8 *m[4];
    u8 pad2C;
    u8 small;
} CeObj;
extern u16 D_main_bss_80130B88[][3];
extern CeBtn D_mission_overlay_8010BE18[];
extern f32 D_mission_overlay_8010BDD8[][2];
f32 vec3Dot(f32 *, f32 *);
void clearVec4QuadStruct(void *);
void addVec3At0x24(void *, f32, f32, f32);
void applyScaleToMat3x4(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, f32);
void composeQuatToMat3x4(void *, void *);
f32 cosf(f32);
void updatePlayerCraftPhysics(void *, f32);
void computeBootConfigScaledVec4(s32, s32, s32, void *, f32, f32);
extern CePl cePlayers[] __asm__("D_main_bss_80137DBC");
#define CEP cePlayers
#define CEM(j) ((CePl *)((u8 *)cePlayers + 0x250))[j].u0.mat0
#define CE_BTN(o, f) (D_main_bss_80130B88[(o)->idx][0] & D_mission_overlay_8010BE18[(o)->idx].f)
#define CE_MAX(o) (!(o)->small ? 2.625f : 1.3125f)
#define CE_MIN(o) (!(o)->small ? 1.875f : 0.9375f)
#define CE_BOOST(o) (!(o)->small ? 3.5625f : 1.78125f)
#define CE_JOINT(k, r) \
    { u8 *m; u8 *n; \
    n = arg0->n[k] + 0x1C; \
    m = arg0->m[k]; \
    clearVec4QuadStruct((void *)n); \
    if (*(s32 *)(m + 0x4C) & 1) { \
        addVec3At0x24((void *)n, -*(f32 *)(m + 0x50), -*(f32 *)(m + 0x54), -*(f32 *)(m + 0x58)); \
    } \
    if (*(s32 *)(m + 0x4C) & 2) { \
        applyScaleToMat3x4((void *)n, *(f32 *)(m + 0x5C), *(f32 *)(m + 0x60), *(f32 *)(m + 0x64)); \
    } \
    composeRotationMatrixSlot0((void *)n, r); \
    if (*(s32 *)(m + 0x4C) & 4) { \
        composeQuatToMat3x4((void *)n, (void *)(m + 0x68)); \
    } \
    { s32 fl = *(s32 *)(m + 0x4C); \
    if ((fl & 9) == 9) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x78) + *(f32 *)(m + 0x50), *(f32 *)(m + 0x7C) + *(f32 *)(m + 0x54), *(f32 *)(m + 0x80) + *(f32 *)(m + 0x58)); \
    } else if ((fl & 9) == 8) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x78), *(f32 *)(m + 0x7C), *(f32 *)(m + 0x80)); \
    } else if (fl & 1) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x50), *(f32 *)(m + 0x54), *(f32 *)(m + 0x58)); \
    } } }
#define CE_JOINTP(k, pre, r) \
    { u8 *m; u8 *n; \
    n = arg0->n[k] + 0x1C; \
    m = arg0->m[k]; \
    pre; \
    clearVec4QuadStruct((void *)n); \
    if (*(s32 *)(m + 0x4C) & 1) { \
        addVec3At0x24((void *)n, -*(f32 *)(m + 0x50), -*(f32 *)(m + 0x54), -*(f32 *)(m + 0x58)); \
    } \
    if (*(s32 *)(m + 0x4C) & 2) { \
        applyScaleToMat3x4((void *)n, *(f32 *)(m + 0x5C), *(f32 *)(m + 0x60), *(f32 *)(m + 0x64)); \
    } \
    composeRotationMatrixSlot0((void *)n, r); \
    if (*(s32 *)(m + 0x4C) & 4) { \
        composeQuatToMat3x4((void *)n, (void *)(m + 0x68)); \
    } \
    { s32 fl = *(s32 *)(m + 0x4C); \
    if ((fl & 9) == 9) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x78) + *(f32 *)(m + 0x50), *(f32 *)(m + 0x7C) + *(f32 *)(m + 0x54), *(f32 *)(m + 0x80) + *(f32 *)(m + 0x58)); \
    } else if ((fl & 9) == 8) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x78), *(f32 *)(m + 0x7C), *(f32 *)(m + 0x80)); \
    } else if (fl & 1) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x50), *(f32 *)(m + 0x54), *(f32 *)(m + 0x58)); \
    } } }
#define CE_JOINTQ(k, pre, r) \
    { u8 *m; u8 *n; \
    n = arg0->n[k] + 0x1C; \
    pre; \
    m = arg0->m[k]; \
    clearVec4QuadStruct((void *)n); \
    if (*(s32 *)(m + 0x4C) & 1) { \
        addVec3At0x24((void *)n, -*(f32 *)(m + 0x50), -*(f32 *)(m + 0x54), -*(f32 *)(m + 0x58)); \
    } \
    if (*(s32 *)(m + 0x4C) & 2) { \
        applyScaleToMat3x4((void *)n, *(f32 *)(m + 0x5C), *(f32 *)(m + 0x60), *(f32 *)(m + 0x64)); \
    } \
    composeRotationMatrixSlot0((void *)n, r); \
    if (*(s32 *)(m + 0x4C) & 4) { \
        composeQuatToMat3x4((void *)n, (void *)(m + 0x68)); \
    } \
    { s32 fl = *(s32 *)(m + 0x4C); \
    if ((fl & 9) == 9) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x78) + *(f32 *)(m + 0x50), *(f32 *)(m + 0x7C) + *(f32 *)(m + 0x54), *(f32 *)(m + 0x80) + *(f32 *)(m + 0x58)); \
    } else if ((fl & 9) == 8) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x78), *(f32 *)(m + 0x7C), *(f32 *)(m + 0x80)); \
    } else if (fl & 1) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x50), *(f32 *)(m + 0x54), *(f32 *)(m + 0x58)); \
    } } }

void cbsvF(s32, f32, f32, void *, f32, f32) __asm__("computeBootConfigScaledVec4");
void composeEffectObjectTransformMatrix(CeObj *arg0, f32 dt) {
    CePl *s3 = &CEP[arg0->idx];
    u8 down = 0;
    f32 v[3];
    f32 up[3];
    f32 spd;
    f32 rot;

    if (*(u16 *)((s32)cePlayers + s3->tgt * sizeof(CePl) + 0x180) & 1) {
        spd = s3->fEC;
        v[0] = CEM(s3->tgt)[0][0];
        v[1] = CEM(s3->tgt)[1][0];
        v[2] = CEM(s3->tgt)[2][0];
        up[0] = 0.0f;
        up[1] = -1.0f;
        up[2] = 0.0f;
        if (vec3Dot(v, up) > 0.0f) {
            down = 1;
        }
        s3->f118 = 35.0f;
        if (CE_BTN(arg0, h14)) {
            spd = CE_MIN(arg0) + (CE_MAX(arg0) - CE_MIN(arg0)) / 3.0f;
            arg0->f4 += dt;
            if (arg0->f4 > 0.5f) {
                arg0->f4 = 0.5f;
            }
            if (down && !CE_BTN(arg0, h16)) {
                s3->f118 = 60.0f;
            }
        } else {
            arg0->f4 -= dt;
            if (arg0->f4 < 0.0f) {
                arg0->f4 = 0.0f;
            }
            s3->f118 = 35.0f;
        }
        if (CE_BTN(arg0, h16)) {
            spd = CE_MIN(arg0) + (CE_MAX(arg0) - CE_MIN(arg0)) / 3.0f;
            arg0->f8 += dt;
            if (arg0->f8 > 0.5f) {
                arg0->f8 = 0.5f;
            }
            if (!down && !CE_BTN(arg0, h14)) {
                s3->f118 = 60.0f;
            }
        } else {
            arg0->f8 -= dt;
            if (arg0->f8 < 0.0f) {
                arg0->f8 = 0.0f;
            }
        }
        if (CE_BTN(arg0, h14) && CE_BTN(arg0, h16)) {
            spd = CE_MIN(arg0);
        }
        CE_JOINTP(0, rot = arg0->f4 * 2.0f * -90.0f, rot)
        CE_JOINTP(1, rot = arg0->f8 * 2.0f * -90.0f, rot)
        if (!CE_BTN(arg0, h6)) {
            rot = D_mission_overlay_8010BDD8[arg0->idx][0];
            if (rot < 0.0f) {
                rot = cosf(-rot * 1.5707964f);
                CE_JOINTP(2, { register f32 one asm("$f2") = 1.0f; register f32 t asm("$f20") = one - rot; rot = t * 45.0f; }, rot)
                CE_JOINT(3, 0.0f)
            } else {
                rot = 1.0f - cosf(rot * 1.5707964f);
                CE_JOINT(2, 0.0f)
                rot = rot * 45.0f;
                CE_JOINT(3, rot)
            }
        } else {
            CE_JOINT(2, 0.0f)
            CE_JOINT(3, 0.0f)
        }
        if (CE_BTN(arg0, h18)) {
            spd = CE_BOOST(arg0);
        }
        if (!CE_BTN(arg0, h16) && !CE_BTN(arg0, h14) && !CE_BTN(arg0, h18)) {
            if (s3->fE8 < CE_MAX(arg0)) {
                spd = CE_MAX(arg0);
            }
        }
        if (spd < CE_MIN(arg0)) {
            spd = CE_MIN(arg0);
        }
        if (spd > CE_BOOST(arg0)) {
            spd = CE_BOOST(arg0);
        }
        s3->fEC = spd;
        if (s3->fF0 < spd - s3->fE8) {
            s3->fE8 = s3->fE8 + s3->fF0;
        } else {
            s3->fE8 = spd;
        }
        if (spd - s3->fE8 < -s3->fF4) {
            s3->fE8 = s3->fE8 - s3->fF4;
        } else {
            s3->fE8 = spd;
        }
    } else {
        CE_JOINT(0, 0.0f)
        CE_JOINT(1, 0.0f)
        CE_JOINT(2, 0.0f)
        CE_JOINT(3, 0.0f)
    }
    updatePlayerCraftPhysics(s3, dt);
    {
        register f32 a asm("$f2") = CE_BOOST(arg0);
        register f32 b asm("$f4") = CE_MIN(arg0);
        register f32 c asm("$f6") = s3->fE8;
        __asm__ volatile("" :: "f"(a), "f"(b), "f"(c) : "memory");
    }
    {
        f32 sc = arg0->small ? 0.75f : 1.0f;
        s32 id = arg0->idx;
        __asm__ volatile("");
        { register f32 c asm("$5") = 0.046875f; cbsvF(arg0->idx, c, c, CEP[id].mat, sc, dt); }
    }
}

typedef struct {
    f32 x, y, z;
} TeV3;

typedef struct {
    TeV3 p;
    TeV3 a;
    TeV3 b;
    f32 pad[3];
} TeTf;

typedef struct {
    TeV3 v;
    f32 pad;
} TeV4;

typedef struct {
    u8 pad0[0x10C];
    u16 h10C;
    u8 pad10E[2];
    TeV3 tgt;
} TeTarget;

typedef struct {
    s32 object;
    u8 pad4[0xB2];
    u16 hB6;
    s32 wB8;
    u8 padBC[0x16C - 0xBC];
    f32 f16C;
} TeObj;

typedef struct {
    u8 pad0[4];
    struct {
        u8 pad0[4];
        u16 type;
    } *p4;
    u8 pad8[0x144 - 8];
} TeMeta;

extern TeMeta D_main_bss_80138D18[] __asm__("D_main_bss_80138D18");
extern u8 D_mission_overlay_80109640[];
extern u8 D_mission_overlay_80109654[];
extern void teLookupHmt(s32, char *, s32, void *, void *, s32) __asm__("lookupHmtTextureByName");
extern void accumulateVectorInObjectFrame(void *, void *, void *);
extern f32 normalize_vector(void *);
extern f32 constMinusSinfApprox(f32);
extern void vec3Cross(void *, void *, void *);
extern void quatFromAxisAngleSafe(void *, void *, f32);
extern void rotateVec3ByQuat(void *, void *, void *);
extern void dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);
extern void play3DSoundEvent(s32, void *, void *, s32, f32, s32, s32, s32, s32);

static __inline__ void teAim(TeTarget *tgt, TeTf *t) {
    TeV4 dir;
    TeV4 axis;
    f32 quat[4];
    f32 ang;
    TeV3 *a;

    dir.v.x = tgt->tgt.x - t->p.x;
    dir.v.y = tgt->tgt.y - t->p.y;
    dir.v.z = tgt->tgt.z - t->p.z;
    normalize_vector(&dir);
    a = &t->a;
    ang = constMinusSinfApprox(vec3Dot((f32 *)a, (f32 *)&dir)) * 57.295776f;
    vec3Cross(&axis, a, &dir);
    quatFromAxisAngleSafe(quat, &axis, ang * 0.6f);
    dir.v = t->a;
    rotateVec3ByQuat(quat, &dir, a);
    dir.v = t->b;
    rotateVec3ByQuat(quat, &dir, &t->b);
}

void tickEffectObjectMotionAndOrientation(TeTarget *tgt, TeObj *obj) {
    TeTf tf;
    u8 aux[0x30];
    TeV4 avg;

    if (D_main_bss_80138D18[obj->wB8].p4->type == 3) {
        TeTf *t;
        f32 sc;

        teLookupHmt(obj->object, "ab", 0, &tf, aux, 0);
        accumulateVectorInObjectFrame(&tf, D_mission_overlay_80109654, obj);
        t = &tf;
        if (tgt->h10C != 0xFFFF) {
            teAim(tgt, t);
        }
        dispatchCueByCategory(0, obj->hB6, t, D_mission_overlay_80109640, 1, sc = 12.5f, obj->f16C);
        avg.v = tf.p;
        teLookupHmt(obj->object, "ab", 1, t, aux, 1);
        accumulateVectorInObjectFrame(t, D_mission_overlay_80109654 + 0xC, obj);
        if (tgt->h10C != 0xFFFF) {
            teAim(tgt, t);
        }
        dispatchCueByCategory(0, obj->hB6, t, D_mission_overlay_80109640, 1, sc, obj->f16C);
    } else {
        teLookupHmt(obj->object, "ab", 0, &tf, aux, 0);
        dispatchCueByCategory(0, obj->hB6, &tf, D_mission_overlay_80109640, 1, 12.5f, obj->f16C);
        avg.v = tf.p;
        teLookupHmt(obj->object, "ab", 1, &tf, aux, 1);
        dispatchCueByCategory(0, obj->hB6, &tf, D_mission_overlay_80109640, 1, 12.5f, obj->f16C);
    }
    avg.v.x = (tf.p.x + avg.v.x) * 0.5f;
    avg.v.y = (tf.p.y + avg.v.y) * 0.5f;
    avg.v.z = (tf.p.z + avg.v.z) * 0.5f;
    play3DSoundEvent(0, &avg, (u8 *)obj + 0x28, 0x41A00000, 0.2f, 0, 2, 0x5A, 0x28);
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AB6E0", D_mission_overlay_800A536C);

typedef struct {
    s32 object;
    f32 v4[3];
    u8 p10[0xB6 - 0x10];
    u16 hB6;
    s32 wB8;
    u8 pBC[0x160 - 0xBC];
    f32 f160;
    f32 f164;
    u8 p168[0x180 - 0x168];
    u16 h180;
    u8 p182[0x1C8 - 0x182];
    s32 w1C8;
    u8 p1CC[0x2A0 - 0x1CC];
} CtPl;
typedef struct {
    f32 x, y, z;
} CtV3;
typedef struct {
    s32 idx;
    u8 p4[0x2C - 4];
    u8 b2C;
    u8 b2D;
    u8 b2E;
    u8 b2F;
    CtV3 v30;
    u8 p3C[0x54 - 0x3C];
    u8 x54[0xF0 - 0x54];
    u16 hF0;
    u8 pF2[2];
    u8 xF4[4];
    f32 fF8;
    CtV3 vFC;
    u8 x108[2];
    u8 b10A;
    u8 p10B;
    u16 h10C;
    u8 p10E[2];
    u8 x110[0x11C - 0x110];
    u8 b11C;
} CtObj;
typedef struct {
    u8 p0[0x1A];
    u16 h1A;
    u16 h1C;
    u8 p1E[0x24 - 0x1E];
} CtBtn;
typedef struct {
    u16 h;
    u8 p2[2];
    s32 w;
    u8 p8[0x18 - 8];
    u8 b18;
    u8 p19[0x20 - 0x19];
} CtArgs;
extern CtPl ctPl[] __asm__("D_main_bss_80137DBC");
extern char D_mission_overlay_800A536C[];
extern f32 D_mission_overlay_801096B0;
extern u8 gGameSettings;
extern s32 D_mission_overlay_8010CA1C;
extern void ctLookupHmt(s32, char *, s32, void *, s32, s32) __asm__("lookupHmtTextureByName");
extern void ctUpdateCam(void *, void *, f32) __asm__("updateCinematicCameraStateMachine");
extern void ctTickAnim(s32, f32) __asm__("tickCraftAnimationSlot");
extern u16 findNearestNpcWithinRange(f32, void *, void *, void *);
extern void playSpeechClipOncePerLevel(s32, s32);
extern void resetSpeechOncePerLevelFlag(s32);
extern s32 isCameraTransitionIdle(void);
extern void beginCameraViewTransition(void *, s32, void *);
extern void scheduleSceneFormatMessageTimed(void *, s32);
extern void initEffectObjectDefaults(s32, u16);
extern s32 slotDispatcherIter(u16, s32, void *);
extern void bsearchFactor5TableByU16Key(s32, s32, s32);
extern void requestCameraSnapToTrackedAnchor(void);
extern void releaseEffectObjectNpcSlots(s32, s32, s32);
extern void submitActiveEffectObjectRender(s32, f32);
extern s32 emitEffectParticlesAlongPath(void *, void *, void *, f32, void *);
extern void playSpeechClipOncePerChange(s32, s32);
extern s32 getEffectModelPoolHandle(void);
extern void beginCameraTrackedTransition(void);
extern s32 rand(void);
extern void requestCinematicNodeEvent(s32);
extern void tickHudInstanceTargetingAndSpawns(s32, f32, void *, s32, s32, u16 *, s32);
extern u16 findLockOnTarget(void *, void *, u16, f32, f32, f32);
extern void ctTeMove(void *, void *, s32) __asm__("tickEffectObjectMotionAndOrientation");
void ctTick(CtObj *o, f32 dt) __asm__("tickCinematicEffectObject");

static __inline__ f32 ctAbs(f32 x) {
    f32 r;
    FABSF(r, x);
    return r;
}

void ctTick(CtObj *o, f32 dt) {
    u8 sp28[0x30];
    CtArgs args;
    s32 sp78;
    u16 sp7C;
    CtPl *pl;
    void *q3;
    u16 r;

    pl = &ctPl[o->idx];
    if (*(u16 *)((s32)ctPl + pl->wB8 * 0x2A0 + 0x180) & 1) {
        if (pl->f160 > 0.0f) {
            pl->f160 -= dt;
        } else if (D_main_bss_80130B88[o->idx][0] & ((CtBtn *)D_mission_overlay_8010BE18)[o->idx].h1A) {
            pl->f160 += pl->f164;
            ctTeMove(o, pl, *(s32 *)&pl->f164);
        }
        ctLookupHmt(pl->object, D_mission_overlay_800A536C, 0, sp28, 0, 0);
        if (o->b2C == 0 && D_mission_overlay_801096B0 <= 0.0f) {
            if ((o->hF0 = findNearestNpcWithinRange(2.5f, &sp78, &o->v30, o->xF4)) != 0xFFFF) {
                playSpeechClipOncePerLevel(gGameSettings != 0xF ? 0x125 : 0x209, 9);
            } else {
                resetSpeechOncePerLevelFlag(gGameSettings != 0xF ? 0x125 : 0x209);
            }
        }
        if (D_main_bss_80130B88[o->idx][0] & ((CtBtn *)D_mission_overlay_8010BE18)[o->idx].h1C) {
            if (o->b11C == 0) {
                o->b11C = 1;
                if (o->b2C == 0) {
                    if (isCameraTransitionIdle() & 0xFF) {
                        if (o->b2F != 0) {
                            if ((o->hF0 = findNearestNpcWithinRange(2.5f, &sp78, &o->v30, o->xF4)) != 0xFFFF && ctAbs(o->v30.y - pl->v4[1]) <= 1.5f) {
                                beginCameraViewTransition(sp28, 0, o->x108);
                                o->b2C = 1;
                                o->b2D = 1;
                                o->b2E = 0;
                                o->fF8 = 0.0f;
                                o->b10A = 0;
                                o->vFC = *(CtV3 *)pl->v4;
                                play3DSoundEvent(0, &o->v30, o->x54, 0x41A00000, 0.2f, 0, 0x6A, 0x78, 0x3C);
                                scheduleSceneFormatMessageTimed(pl, 9);
                                initEffectObjectDefaults(pl->wB8, o->hF0);
                                args.b18 = 0xC;
                                slotDispatcherIter(o->hF0, 9, &args);
                                if (o->b2F != 0xFF) {
                                    o->b2F--;
                                }
                            } else {
                                o->b2D = 0;
                            }
                        }
                        bsearchFactor5TableByU16Key(0x67, 0x5A, 0xFF);
                    } else if (o->b2C != 0) {
                        goto end_tr;
                    } else {
                        goto skip;
                    }
                } else {
end_tr:
                    if (o->b2D != 0) {
                        args.b18 = 0xD;
                        slotDispatcherIter(o->hF0, 9, &args);
                        scheduleSceneFormatMessageTimed(pl, 0xA);
                    }
                    requestCameraSnapToTrackedAnchor();
                    o->b2C = 0;
                    o->b2D = 0;
                    releaseEffectObjectNpcSlots(pl->wB8, pl->w1C8, 1);
                    D_mission_overlay_8010CA1C &= ~0x100;
                }
            }
        } else {
            o->b11C = 0;
        }
        if (o->b2C != 0) {
            submitActiveEffectObjectRender(pl->wB8, dt);
        }
skip:
        ctUpdateCam(sp28, &o->v30, dt);
        if (o->b2D != 0) {
            if (!(emitEffectParticlesAlongPath(pl->v4, o->x108, &o->v30, 3.2f, &o->b10A) & 0xFF)
                || ctAbs(o->vFC.y - pl->v4[1]) > 2.6f) {
                goto end_tr;
            }
            if (o->b10A >= 3) {
                o->fF8 += dt;
            }
            if (o->b10A == 2 && o->b2E == 0) {
                o->b2E = 1;
                playSpeechClipOncePerChange(gGameSettings != 0xF ? 0x12A : 0x20E, 9);
            }
            if (o->fF8 > 0.5f) {
                args.b18 = 0xE;
                args.h = pl->hB6;
                args.w = getEffectModelPoolHandle();
                slotDispatcherIter(o->hF0, 9, &args);
                beginCameraTrackedTransition();
                o->b2C = 0;
                o->b2D = 0;
                rand();
                playSpeechClipOncePerChange(gGameSettings != 0xF ? 0x128 : 0x20C, 9);
                scheduleSceneFormatMessageTimed(pl, 0xA);
                requestCinematicNodeEvent(pl->wB8);
                D_mission_overlay_8010CA1C &= ~0x100;
            }
        }
    }
    q3 = pl->v4;
    tickHudInstanceTargetingAndSpawns(0, dt, q3, pl->object, 0, &sp7C, pl->hB6);
    r = findLockOnTarget(q3, o->x110, o->h10C, 10.0f, 0.987f, 12.5f);
    sp7C = r;
    if (r != 0xFFFF) {
        o->h10C = r;
    } else {
        o->h10C = 0xFFFF;
    }
    ctTickAnim(0, dt);
}

extern u8 *D_mission_overlay_8010B6D0;
typedef struct {
    s32 idx;
    void *p4;
    void *p8;
    void *pC;
    u8 p10[6];
    u16 h16;
} YwNpc;

typedef struct {
    s32 object;
    u8 p4[0xB0];
    u16 hB4;
    u16 hB6;
    s32 wB8;
    s32 wBC;
    u8 pC0[0x178 - 0xC0];
    s32 w178;
    u8 p17C[4];
    u16 h180;
    u8 p182[2];
    f32 f184;
    u8 p188[0x2A0 - 0x188];
} YwPlayer;

typedef struct {
    u8 p0[4];
    struct {
        u8 p0[4];
        u16 h4;
    } *p4;
    u8 p8[0x144 - 8];
} YwMeta;

typedef struct {
    u8 p0[2];
    u16 h2;
    u8 p4[0x18];
    u16 h1C;
} YwNpcTbl;

extern YwPlayer ywPlayers[] __asm__("D_main_bss_80137DBC");
extern YwMeta ywMeta[] __asm__("D_main_bss_80138D18");
extern YwNpcTbl ywNpcTbl __asm__("D_main_bss_80139560");
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_801098DC[];
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];
extern void *rs_malloc(s32, s32);
extern void rs_free(void *);
extern s32 walkMeshdef0List(char *);
extern void loadPlayerStartPosition(void *, void *);
extern void configurePlayerSecondaryWeaponHud(s32, s32, s32, s32);
extern s32 refreshPlayerSecondaryWeaponHud(s32);
extern void allocateCraftAnimationStateForSlot(void *, s32, void *);
extern void popNpcSlotFromTail(u16, void *);
extern void *allocateAndInitCraftNpcContext(f32, f32, s32);
extern void spawnNpcOfType(void *, void *, s32, s32);
extern void resetTransientPlayerStateFlags(void);
extern void resetCraftAnimationStateForSlot(s32);
extern void cancelSceneQueueHandle(void *);
extern void destroySceneNpcsAndUnlink(void *);
extern void releaseMeshAsset(s32);
extern void teardownHudInstancesAndUnbindNpcs(void);
extern void freePlayerAuxBuffersIfActive(s32);
extern void tryPlaySpatialSoundWithGates(void *, void *);
extern void destroyNpcSlotByIndex(u16);
extern void enqueueMeshTypeForCleanup(s32);
extern void addNpcToVisibilityBucket(s32, s32, void *, f32);
extern void advanceNpcOnCurvedPath(s32, s32, void *, void *);
extern void updatePlayerHudFrame(s32, void *, void *);

extern u8 D_main_8009EBBC;
extern u8 D_mission_overlay_8010964C[];
extern char D_mission_overlay_800A536C[];
extern void playerSnowSpeederInit(void *, s32, s32);
extern void loadEffectModelInstancePool(void);
extern void freeEffectModelInstancePool(void);
extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern void updateCinematicCameraStateMachine(void *, void *, s32);
extern void tickCraftAnimationSlot(s32, s32);
extern void ceCall(void *, s32) __asm__("composeEffectObjectTransformMatrix");
extern void tickCinematicEffectObject(void *, s32);
extern void advanceCameraTransitionOnCue(s32);
extern void submitCameraTrackedObjectToRender(void *);
s32 playerSnowSpeederUpdate(YwNpc *npc, u32 msg, s32 *arg) {
    YwPlayer *pl;
    u8 *anim;
    s32 s2;
    u16 sp18[0x18];
    void *np;
    s32 *a2;
    f32 *fa;

    anim = npc->p4;
    if (D_main_8009EBBC) {
        switch ((u16)msg) {
        case 2:
            pl = &ywPlayers[((YwNpc *)anim)->idx];
            goto destroy;
        case 3:
            pl = &ywPlayers[((YwNpc *)anim)->idx];
            lookupHmtTextureByName(pl->object, D_mission_overlay_800A536C, 0, sp18, 0, 0);
            updateCinematicCameraStateMachine(sp18, anim + 0x30, arg[0]);
            tickCraftAnimationSlot(0, arg[0]);
            return 1;
        case 4:
            pl = &ywPlayers[((YwNpc *)anim)->idx];
            enqueueMeshTypeForCleanup(pl->object);
            submitCameraTrackedObjectToRender(arg);
            return 1;
        case 9:
            goto cue;
        default:
            return 1;
        }
    }
    if ((u16)msg != 2 && (D_mission_overlay_8010CA1C & 4)) {
        return 1;
    }
    switch ((u16)msg) {
    case 1:
        fa = (f32 *)arg;
        anim = rs_malloc(0x120, 0);
        npc->p4 = anim;
        pl = &ywPlayers[(s32)fa[0]];
        D_mission_overlay_8010B6D0 = anim;
        pl->object = walkMeshdef0List("snowspeeder");
        pl->hB6 = npc->h16;
        npc->pC = (void *)pl->object;
        npc->p8 = (u8 *)pl + 4;
        if (fa[0] >= 0.0f) {
            ((u16 *)&ywPlayers[(s32)fa[0]])[-1] = npc->h16;
            pl->wB8 = (s32)fa[0];
            s2 = 1;
        } else {
            s2 = 0;
        }
        loadPlayerStartPosition(pl, 0);
        playerSnowSpeederInit(anim, (s32)fa[0], s2);
        pl->w178 = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
        loadEffectModelInstancePool();
        allocateCraftAnimationStateForSlot(pl, 0, D_mission_overlay_8010964C);
        popNpcSlotFromTail(ywNpcTbl.h2, npc);
        popNpcSlotFromTail(ywNpcTbl.h1C, npc);
        pl->wBC = (s32)allocateAndInitCraftNpcContext(0.125f, 0.125f, 4);
        sp18[0] = npc->h16;
        sp18[1] = pl->hB4;
        spawnNpcOfType(attached3DSoundEmitterNpcHandler, sp18, 1, 0x64);
        spawnNpcOfType(attachedMeshOverlayNpcHandler, &npc->h16, 1, 0x64);
        return 1;
    case 12:
        pl = &ywPlayers[((YwNpc *)anim)->idx];
        pl->f184 = 2.0f;
        pl->h180 = (pl->h180 & 0xFFDF) | 0x40;
        loadPlayerStartPosition(pl, (u8 *)pl + 4);
        playerSnowSpeederInit(anim, pl->wB8, 0x40);
        resetTransientPlayerStateFlags();
        resetCraftAnimationStateForSlot(0);
        return 1;
    case 2:
        pl = &ywPlayers[((YwNpc *)anim)->idx];
        cancelSceneQueueHandle(pl);
destroy:
        destroySceneNpcsAndUnlink(pl);
        rs_free((void *)pl->wBC);
        releaseMeshAsset(pl->object);
        teardownHudInstancesAndUnbindNpcs();
        freePlayerAuxBuffersIfActive(0);
        freeEffectModelInstancePool();
        return 1;
    case 3:
        ceCall(anim, arg[0]);
        tickCinematicEffectObject(anim, arg[0]);
        return 1;
    case 9:
cue:
        if (*((u8 *)arg + 0x18) == 0xE) {
            advanceCameraTransitionOnCue(arg[1]);
        }
        return 1;
    case 5:
        tryPlaySpatialSoundWithGates(&ywPlayers[((YwNpc *)anim)->idx], arg);
        if (*(u16 *)arg != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)arg);
        }
        return 1;
    case 4:
        pl = &ywPlayers[((YwNpc *)anim)->idx];
        enqueueMeshTypeForCleanup(pl->object);
        a2 = arg;
        if (!(pl->h180 & 0x100)) {
            np = (u8 *)pl + 4;
            if (ywMeta[pl->wB8].p4->h4 != 3) {
                addNpcToVisibilityBucket(a2[0], pl->object, np, 1.0f);
                if (!(pl->h180 & 0x80)) {
                    advanceNpcOnCurvedPath(a2[2], a2[0], np, (void *)pl->wBC);
                }
            }
            updatePlayerHudFrame(0, a2, (u8 *)pl + 4);
            submitCameraTrackedObjectToRender(a2);
        }
        return 1;
    default:
        return 1;
    }
}

s32 getPlayerVehicleId(s32);
s32 slotDispatcherIter(u16, s32, void *);
extern u8 *D_mission_overlay_8010B6D0;
typedef struct {
    u8 pad0[0x18];
    u8 cmd;
    u8 pad19[7];
} SpecialSlotEffectArgs;
void triggerPlayerVehicleSpecialSlotEffect(void) {
    SpecialSlotEffectArgs args;

    if (getPlayerVehicleId(0) == 4 && D_mission_overlay_8010B6D0[0x2C] != 0 && D_mission_overlay_8010B6D0[0x2D] != 0) {
        args.cmd = 0xD;
        slotDispatcherIter(*(u16 *)(D_mission_overlay_8010B6D0 + 0xF0), 9, &args);
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AB6E0", fake_func_800AD378);

__asm__(".section .rodata\n.word 0x03C0E821\n.word 0x8FBF001C\n.section .text");
