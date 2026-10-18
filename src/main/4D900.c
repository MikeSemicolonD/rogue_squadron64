#include "common.h"
#include "common_types.h"

#include "main/1D000.h"
#include "main/4D900.h"
#include "player.h"

extern void *D_main_8009EB98[];
void updateEffectObjectTransformPieces(void *, s32, s32, f32, s32);
typedef struct {
    u8 unk0;
    u8 pad1[3];
    void *unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x4C];
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    s32 unk70;
    u8 pad74[0xD0];
} SceneNode;
extern s32 D_main_bss_80138260;
extern SceneNode *D_main_bss_80138894;
extern SceneNode D_main_bss_80138D18[];

extern f32 sinf(f32);
extern f32 cosf(f32);
extern s32 sampleTerrainAtNpcPosition(f32 *, f32 *, void *, f32 *);
extern void clampVec3ToUnitIfLongerThan(f32 *);
extern void addScaledVec3ToVec3(f32 *, f32 *, f32, f32 *);
extern f32 wrapAngleToCyclicRange(f32, f32, void *, f32 *);
extern u8 D_main_bss_80138058[];

void applyPlayerVehicleStateUpdate(u8 *arg0) {
    f32 buf[40];
    SceneNode *n;
    u8 *cur;
    f32 f;
    f32 *p;
    f32 *q;
    s32 i;

    n = &D_main_bss_80138D18[*(s32 *)(arg0 + 0xC)];
    cur = n->unk4;
    if (*(u16 *)(cur + 4) == 3) {
        return;
    }
    if (*(u16 *)arg0 & 0x20) {
        if (*(u16 *)(arg0 + 4) == 3) {
            return;
        }
    } else {
        if (arg0 == cur) {
            buf[10] = (f32)(-*(s32 *)((u8 *)n + 0x18)) * 0.5 * (240.0 / *(s32 *)((u8 *)n + 0x1C));
            buf[11] = (f32)(-*(s32 *)((u8 *)n + 0x1C)) * 0.5 * (240.0 / *(s32 *)((u8 *)n + 0x1C));
            f = (*(f32 *)((u8 *)n + 0x28) + 2.0f) * 0.5f * 3.1415927f / 180.0f;
            f = sinf(f) / cosf(f);
            buf[12] = 120.0f / f;
            f = *(f32 *)((u8 *)n + 0x2C) + *(f32 *)((u8 *)n + 0x2C);
            normalize_vector(&buf[10]);
            buf[10] = buf[10] * f;
            buf[11] = buf[11] * f;
            buf[12] = buf[12] * f;
            transformVec3ByMat34(arg0 + 0x28, &buf[10], &buf[14]);
            buf[10] = -buf[10];
            transformVec3ByMat34(arg0 + 0x28, &buf[10], &buf[17]);
            buf[11] = -buf[11];
            transformVec3ByMat34(arg0 + 0x28, &buf[10], &buf[20]);
            buf[10] = -buf[10];
            transformVec3ByMat34(arg0 + 0x28, &buf[10], &buf[23]);
            for (i = 0; i < 3; i++) {
                p = buf + i * 3;
                q = p + 14;
                buf[10] = q[0] - *(f32 *)(arg0 + 0x10);
                buf[11] = q[1] - *(f32 *)(arg0 + 0x14);
                buf[12] = q[2] - *(f32 *)(arg0 + 0x18);
                if (sampleTerrainAtNpcPosition((f32 *)(arg0 + 0x10), &buf[10], D_main_bss_80138058, buf)) {
                    clampVec3ToUnitIfLongerThan(&buf[10]);
                    buf[10] = -buf[10];
                    buf[11] = -buf[11];
                    buf[12] = -buf[12];
                    addScaledVec3ToVec3((f32 *)(arg0 + 0x10), buf, f, &buf[10]);
                    *(f32 *)(arg0 + 0x4C) = *(f32 *)(arg0 + 0x10);
                    *(f32 *)(arg0 + 0x50) = *(f32 *)(arg0 + 0x14);
                    *(f32 *)(arg0 + 0x54) = *(f32 *)(arg0 + 0x18);
                }
            }
        }
        if (*(u16 *)(arg0 + 4) == 3) {
            return;
        }
    }
    f = wrapAngleToCyclicRange(*(f32 *)(arg0 + 0x4C), *(f32 *)(arg0 + 0x54), D_main_bss_80138058, &buf[26]) - *(f32 *)(arg0 + 0x50);
    buf[36] = *(f32 *)(arg0 + 0x10) - buf[26];
    buf[37] = *(f32 *)(arg0 + 0x14) - buf[27];
    {
        f32 t = buf[28];
        buf[38] = *(f32 *)(arg0 + 0x18) - t;
    }
    vec3Length(&buf[36]);
    if (f < *(f32 *)(arg0 + 0xB8)) {
        f32 g = buf[27] - *(f32 *)(arg0 + 0xB8);
        *(f32 *)(arg0 + 0x50) = g;
        *(f32 *)(arg0 + 0x14) = g;
    }
}

typedef struct { s32 b[12]; } RoBlob30;
typedef struct { s32 a, b, c; } RoV3;
extern void floatModulo(f32, f32);

void rotateObjectMatrixAboutStoredAxis(u8 *arg0, f32 dt) {
    f32 m[12];
    f32 w[4];
    f32 v[4];
    f32 pos[4];
    f32 t0, t1, t2, n0, n2;
    f32 q2[4];
    f32 q3[4];
    f32 q1[4];
    *(RoBlob30 *)m = **(RoBlob30 **)(arg0 + 0x74);
    *(RoV3 *)v = *(RoV3 *)(arg0 + 0x58);
    if (v[0] != 0.0f || v[1] != 0.0f || v[2] != 0.0f) {
        transformVec3ByMat34(m, v, w);
        m[9] = w[0];
        m[10] = w[1];
        m[11] = w[2];
    } else {
        w[0] = m[9];
        w[1] = m[10];
        w[2] = m[11];
    }
    quatFromCardinalAxis(q2, 1, *(f32 *)(arg0 + 0xD0));
    quatFromCardinalAxis(q3, 0, *(f32 *)(arg0 + 0xE0));
    quatMultiply(q2, q3, q1);
    quatToRotationMatrix(q1, m);
    *(f32 *)(arg0 + 0x94) = *(f32 *)(arg0 + 0x94) + *(f32 *)(arg0 + 0xDC) * dt;
    if (*(f32 *)(arg0 + 0x94) < 1.5f) {
        *(f32 *)(arg0 + 0x94) = 1.5f;
        *(f32 *)(arg0 + 0xDC) = 0.0f;
    }
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = *(f32 *)(arg0 + 0x94);
    rotateVec3ByMat3x3(m, v, v);
    t0 = *(f32 *)(*(u8 **)(arg0 + 0x74) + 0x24);
    n0 = v[0] + t0;
    pos[0] = t0;
    t1 = *(f32 *)(*(u8 **)(arg0 + 0x74) + 0x28);
    pos[1] = t1;
    t2 = *(f32 *)(*(u8 **)(arg0 + 0x74) + 0x2C);
    v[0] = n0;
    n2 = v[2] + t2;
    pos[2] = t2;
    v[1] += t1;
    v[2] = n2;
    *(f32 *)(arg0 + 0x4C) = v[0];
    *(f32 *)(arg0 + 0x50) = v[1];
    *(f32 *)(arg0 + 0x54) = v[2];
    *(RoV3 *)(arg0 + 0x10) = *(RoV3 *)v;
    *(f32 *)(arg0 + 0xD0) = *(f32 *)(arg0 + 0xD0) + *(f32 *)(arg0 + 0xD8) * dt;
    floatModulo(*(f32 *)(arg0 + 0xD0), 180.0f);
}

typedef struct { s32 a, b, c; } PvV3;
typedef struct { s32 b[12]; } PvM;
typedef struct {
    u16 flags;
    u16 mode;
    u16 type;
    u16 f6;
    s32 f8;
    s32 idx;
    f32 pos[3];
    f32 ang[3];
    f32 m[12];
    f32 v58[3];
    u8 pad64[0xC];
    f32 *f70;
    f32 *f74;
    f32 v78[3];
    u8 pad84[0xC];
    f32 *f90;
    f32 f94;
    f32 f98;
    f32 f9C;
    f32 fA0;
    f32 fA4;
    u8 padA8[0x14];
    u8 *fBC;
    u8 *fC0;
    f32 fC4;
    f32 fC8;
    f32 fCC;
} PvObj;
extern u8 D_main_bss_80138838;
extern u8 D_main_bss_80137CF4;
extern void computeAngleToTargetFromTransform(u8 *, u8 *, u8 *);
void buildOrientationFromPosAndAngles(void *, void *, void *);
extern void transformVec3ByMat34(void *, f32 *, f32 *);
extern void updateAudioListenerPosFromPlayer(void);
void pvImpl(PvObj *o, f32 dt) __asm__("updatePlayerVehicleByControlMode");
static __inline__ f32 pvAbs(f32 x) {
    f32 r;
    FABSF(r, x);
    return r;
}

void pvImpl(PvObj *o, f32 dt) {
    f32 v10[4];
    f32 v20[4];
    f32 w30[4];
    f32 m40[12];
    f32 v70[4];
    f32 a80[4];
    f32 b90[4];
    PvV3 saved;
    f32 tgt;
    f32 len;
    f32 t;
    f32 cur;
    f32 d;
    f32 b;
    f32 r;

    tgt = 0.0f;
    if (D_main_bss_80137CF4 != 0) {
        return;
    }
    if (D_main_bss_80138838 != 0 && o->mode != 4) {
        return;
    }
    saved = *(PvV3 *)o->pos;
    switch (o->mode) {
    case 0:
        buildOrientationFromPosAndAngles(o->m, o->pos, o->ang);
        break;
    case 2:
        {
            f32 *pm = o->m;
            f32 *pp = o->pos;
            __asm__("" :: "r"(pm), "r"(pp));
            *(PvV3 *)v10 = *(PvV3 *)o->v58;
            buildOrientationFromPosAndAngles(pm, pp, o->ang);
        }
        goto xform;
    case 1:
        if (o->flags & 0x200) {
            computeAngleToTargetFromTransform((u8 *)o->f70, (u8 *)o->pos, (u8 *)o->ang);
            *(s32 *)&o->ang[1] = 0;
            *(s32 *)&o->ang[2] = 0;
            buildOrientationFromPosAndAngles(o->m, o->pos, o->ang);
        } else {
            *(PvM *)o->m = *(PvM *)o->f70;
        }
        if (o->f90 != NULL) {
            *(PvV3 *)o->ang = *(PvV3 *)o->f90;
            o->pos[0] = o->f70[9];
            o->pos[1] = o->f70[10];
            o->pos[2] = o->f70[11];
        } else {
            computeAngleToTargetFromTransform((u8 *)o->m, (u8 *)o->pos, (u8 *)o->ang);
        }
        *(PvV3 *)v10 = *(PvV3 *)o->v58;
    xform:
        if (v10[0] != 0.0f || v10[1] != 0.0f || v10[2] != 0.0f) {
            transformVec3ByMat34(o->m, v10, v20);
            o->m[9] = v20[0];
            o->m[10] = v20[1];
            o->m[11] = v20[2];
        }
        break;
    case 3:
        *(PvM *)m40 = *(PvM *)o->f70;
        *(PvV3 *)v10 = *(PvV3 *)o->v58;
        if (v10[0] != 0.0f || v10[1] != 0.0f || v10[2] != 0.0f) {
            transformVec3ByMat34(m40, v10, v20);
            m40[9] = v20[0];
            m40[10] = v20[1];
            m40[11] = v20[2];
        } else {
            v20[0] = m40[9];
            v20[1] = m40[10];
            v20[2] = m40[11];
        }
        if (o->fA4 < dt && o->fA4 != 0.0f) {
            v10[0] = v20[0] - o->pos[0];
            v10[1] = v20[1] - o->pos[1];
            v10[2] = v20[2] - o->pos[2];
            clampVec3ToUnitIfLongerThan(v10);
            o->pos[0] += o->f98 * (dt - o->fA4) * v10[0];
            o->pos[1] += o->f98 * (dt - o->fA4) * v10[1];
            o->pos[2] += o->f98 * (dt - o->fA4) * v10[2];
            o->m[9] = o->pos[0];
            o->m[10] = o->pos[1];
            o->m[11] = o->pos[2];
            dt = o->fA4;
        }
        o->fA4 = dt;
        v70[0] = v20[0] - o->pos[0];
        v70[1] = v20[1] - o->pos[1];
        v70[2] = v20[2] - o->pos[2];
        len = vec3Length(v70);
        if (0.01f < len) {
            {
            f32 q = pvAbs(len - o->f94);
            if (1.0f < q) {
                q = 1.0f;
            }
            tgt = q * o->f9C;
            }
            cur = o->f98;
            d = tgt - cur;
            t = pvAbs(d);
            b = o->f9C * dt;
            t = t * dt;
            if (t < b) {
                b = t;
            }
            if (b < 0.01f) {
                b = 0.0f;
            }
            if (0.0f < d) {
                o->f98 = cur + b;
            } else {
                o->f98 = cur - b;
            }
            if (tgt < o->f98) {
                o->f98 = tgt;
            }
            clampVec3ToUnitIfLongerThan(v70);
            o->pos[0] += o->f98 * dt * v70[0];
            o->pos[1] += o->f98 * dt * v70[1];
            o->pos[2] += o->f98 * dt * v70[2];
            o->m[9] = o->pos[0];
            o->m[10] = o->pos[1];
            o->m[11] = o->pos[2];
        } else {
            o->m[9] = m40[9];
            o->m[10] = m40[10];
            o->m[11] = m40[11];
            o->pos[0] = o->m[9];
            o->pos[1] = o->m[10];
            o->pos[2] = o->m[11];
        }
        {
            u8 *p = D_main_bss_80138D18[o->idx].unk4;
            if (*(u16 *)(p + 2) == 4 && *(PvObj **)(p + 0xC0) == o) {
                o->f98 = tgt;
            }
        }
        break;
    case 4:
        if (!(0.0f < o->fCC)) {
            r = o->fC4 / o->fC8;
            if (r > 1.0) {
                r = 1.0f;
            }
            a80[0] = ((PvObj *)o->fBC)->m[9];
            a80[1] = ((PvObj *)o->fBC)->m[10];
            a80[2] = ((PvObj *)o->fBC)->m[11];
            b90[0] = ((PvObj *)o->fC0)->m[9];
            b90[1] = ((PvObj *)o->fC0)->m[10];
            b90[2] = ((PvObj *)o->fC0)->m[11];
            o->pos[0] = b90[0] - a80[0];
            o->pos[1] = b90[1] - a80[1];
            o->pos[2] = b90[2] - a80[2];
            addScaledVec3ToVec3(o->pos, a80, r, o->pos);
            o->m[9] = o->pos[0];
            o->m[10] = o->pos[1];
            o->m[11] = o->pos[2];
            if ((u8 *)o == D_main_bss_80138D18[o->idx].unk4) {
                updateAudioListenerPosFromPlayer();
            }
        }
        break;
    }
    if (o->type == 4) {
        rotateObjectMatrixAboutStoredAxis((u8 *)o, dt);
    }
    if (o->flags & 8) {
        v10[0] = o->f74[2];
        v10[1] = o->f74[5];
        v10[2] = o->f74[8];
        v10[1] = 0.0f;
        clampVec3ToUnitIfLongerThan(v10);
        w30[0] = o->m[2];
        w30[1] = o->m[5];
        w30[2] = o->m[8];
        w30[1] = 0.0f;
        clampVec3ToUnitIfLongerThan(w30);
        if (vec3Dot(v10, w30) < 0.0f) {
            *(PvV3 *)o->pos = saved;
        } else {
            transformVec3ByMat34(o->f74, o->v78, v20);
            v70[0] = o->pos[0] - v20[0];
            v70[1] = o->pos[1] - v20[1];
            {
                register f32 pz asm("$f2") = o->pos[2];
                v70[2] = pz - v20[2];
            }
            dt = 2.5f;
            if (!(dt <= vec3Length(v70))) {
                goto skip;
            }
            clampVec3ToUnitIfLongerThan(v70);
            addScaledVec3ToVec3(o->pos, v20, dt, v70);
        }
        o->m[9] = o->pos[0];
        o->m[10] = o->pos[1];
        o->m[11] = o->pos[2];
    }
skip:
    if (o->type == 0 && !(*(s32 *)o & 0x4100000)) {
        transformVec3ByMat34(o->f74, o->v78, v20);
        v70[0] = o->pos[0] - v20[0];
        v70[1] = o->pos[1] - v20[1];
        v70[2] = o->pos[2] - v20[2];
        if (8.75f <= vec3Length(v70)) {
            *(PvM *)o->m = *(PvM *)o->f74;
            o->pos[0] = o->m[9];
            o->pos[1] = o->m[10];
            o->pos[2] = o->m[11];
            updateAudioListenerPosFromPlayer();
        }
    }
    applyPlayerVehicleStateUpdate((u8 *)o);
}

typedef struct {
    f32 x, y, z;
} EoV3;
typedef struct {
    u8 pad0[2];
    u16 h2;
    u8 pad4[0x2A0 - 4];
} EoPlayer;
typedef struct {
    u8 pad0[0xC];
    s32 player;
    EoV3 pos;
    u8 pad1C[0x4C - 0x1C];
    f32 m4C;
    f32 m50;
    f32 m54;
    u8 pad58[0x74 - 0x58];
    f32 *m74;
    EoV3 v78;
    u8 pad84[0xB4 - 0x84];
    f32 tB4;
} EoObj;
extern EoPlayer eoPlayers[] __asm__("gPlayers");
extern s32 D_8010CA20;
extern u16 D_main_bss_8013957C;
void eoXform(f32 *, EoV3 *, EoV3 *) __asm__("transformVec3ByMat34");
s32 eoSample(EoV3 *, EoV3 *, void *, void *) __asm__("sampleTerrainAtNpcPosition");
void eoApply(EoObj *) __asm__("applyPlayerVehicleStateUpdate");
void updateAudioListenerPosFromPlayer(void);
s32 findActiveNpcInSlotChain(u16, void *);
u8 *getNpcContextByIndex(u16);
s32 findSegmentObjectSphereHit(s32, void *, void *, void *);
s32 revalidateNpcSlotIterator(void *);
f32 *getNpcContextField8(u16);

static __inline__ u16 eoFindHit(s32 player, EoV3 *a, EoV3 *b, void *hit, u16 chain) {
    u8 it[8];
    u16 self;
    u16 cur;
    s32 idx;
    s32 mesh;

    if (D_8010CA20 == 5) {
        return 0xFFFF;
    }
    self = eoPlayers[player].h2;
    idx = findActiveNpcInSlotChain(chain, it);
    if ((idx & 0xFFFF) != 0xFFFF) {
        do {
            cur = idx;
            mesh = *(s32 *)(getNpcContextByIndex(cur) + 0xC);
            if (mesh != 0 && cur != self) {
                if (findSegmentObjectSphereHit(mesh, a, b, hit) != 0) {
                    return cur;
                }
            }
            idx = revalidateNpcSlotIterator(it);
        } while ((idx & 0xFFFF) != 0xFFFF);
    }
    return 0xFFFF;
}

void updateEffectObjectMotionOnTerrain(EoObj *o, f32 dt) {
    EoV3 p10;
    EoV3 d20;
    EoV3 d30;
    u8 hit[0x28];
    u16 idx;
    f32 *c;

    if (D_8010CA20 == 5) {
        return;
    }
    if (o->m74 == NULL) {
        return;
    }
    d20 = o->v78;
    eoXform(o->m74, &d20, &p10);
    d20.x = o->pos.x - p10.x;
    d20.y = o->pos.y - p10.y;
    d20.z = o->pos.z - p10.z;
    if (eoSample(&p10, &d20, D_main_bss_80138058, hit) != 0) {
        o->tB4 += dt;
        if (o->tB4 > 0.5f) {
            o->pos = *(EoV3 *)hit;
            o->m4C = o->pos.x;
            o->m50 = o->pos.y;
            o->m54 = o->pos.z;
            eoApply(o);
            updateAudioListenerPosFromPlayer();
            o->tB4 = 0.0f;
        }
        return;
    }
    idx = eoFindHit(o->player, &p10, &d20, hit, D_main_bss_8013957C);
    if (idx != 0xFFFF) {
        o->tB4 += dt;
        if (o->tB4 > 0.5f) {
            c = getNpcContextField8(idx);
            d30.x = p10.x - c[0];
            d30.y = p10.y - c[1];
            d30.z = p10.z - c[2];
            o->m50 = o->pos.y = o->pos.y - dt;
            eoApply(o);
            updateAudioListenerPosFromPlayer();
        }
    } else {
        o->tB4 = 0.0f;
    }
}

typedef struct { f32 x, y, z; } AlV3;
typedef struct {
    u8 pad0[4];
    u16 h4;
    u8 pad6[0xA];
    AlV3 pos;
    AlV3 ang;
    u8 pad28[8];
    f32 f30;
    u8 pad34[8];
    f32 f3C;
    u8 pad40[8];
    f32 f48;
    AlV3 p4C;
} AlObj;
extern struct { f32 x, y; } alStk __asm__("D_8010BDD8");
extern u16 alB88 __asm__("D_main_bss_80130B88");
extern u16 D_8010BE1E;
extern u16 D_8010BE38;
void buildTransformMatrixFromEulerAngles(void *, f32, f32, f32);
void mat3x4Multiply(void *, void *, void *);
extern void computeAngleToTargetFromTransform(u8 *, u8 *, u8 *);
void applyPlayerVehicleStateUpdate(u8 *arg0);

static __inline__ f32 alAbs(f32 x) {
    f32 r;
    FABSF(r, x);
    return r;
}

void applyObjectLocalToWorldTransform(AlObj *o, f32 dt) {
    f32 m[12];
    AlV3 t;
    f32 speed;
    f32 rx, ry, rz;
    f32 f;

    if (o->h4 != 0) {
        return;
    }
    speed = 0.0f;
    rz = speed;
    ry = speed;
    rx = speed;
    if ((alB88 & D_8010BE1E) && (alAbs(alStk.x) > 0.1f || alAbs(alStk.y) > 0.1f)) {
        if (alAbs(alStk.x) > 0.1f) {
            rx = alStk.x * -90.0f * dt;
        }
        if (alAbs(alStk.y) > 0.1f) {
            ry = alStk.y * 90.0f * dt;
        }
    } else if (alB88 & D_8010BE38) {
        if (alAbs(alStk.x) > 0.1f) {
            rz = alStk.x * -90.0f * dt;
        }
    } else {
        if (alAbs(alStk.y) > 0.1f) {
            speed = alStk.y * 2.5;
        }
        if (alAbs(alStk.x) > 0.1f) {
            rx = alStk.x * -90.0f * dt;
        }
    }
    if (alB88 & 0x2000) {
        speed *= 10.0f;
    }
    if (alB88 & 2) {
        speed /= 10.0f;
    }
    buildTransformMatrixFromEulerAngles(m, rx, ry, rz);
    t.x = o->p4C.x;
    t.y = o->p4C.y;
    t.z = o->p4C.z;
    mat3x4Multiply((u8 *)o + 0x28, m, (u8 *)o + 0x28);
    o->p4C.x = t.x;
    o->p4C.y = t.y;
    o->p4C.z = t.z;
    computeAngleToTargetFromTransform((u8 *)o + 0x28, (u8 *)&o->pos, (u8 *)&o->ang);
    if (speed != 0.0f) {
        f = speed * dt;
        t.x = o->f30;
        t.y = o->f3C;
        t.z = o->f48;
        o->pos.x += f * t.x;
        o->pos.y += f * t.y;
        o->pos.z += f * t.z;
        o->p4C.x = o->pos.x;
        o->p4C.y = o->pos.y;
        o->p4C.z = o->pos.z;
    }
    applyPlayerVehicleStateUpdate((u8 *)o);
}

INCLUDE_ASM("asm/nonmatchings/main/4D900", updateEffectObjectOrientationQuat);

typedef struct { s32 b[12]; } Blob30;
extern u8 D_main_bss_80138268[][6][0xF8];
extern void destroyNpcSlotChain(u16);
extern void updatePlayerVehicleByControlMode(void *, f32);
extern void updateEffectObjectOrientationQuat(void *, void *, f32);
extern void updateAudioListenerPosFromPlayer(void);

void releaseEffectObjectNpcSlots(s32 idx, s32 view, u8 copy) {
    u8 *cur;
    u8 *nw;
    u8 *t;
    f32 dt;

    cur = D_main_bss_80138D18[idx].unk4;
    nw = D_main_bss_80138268[idx][view];
    if (cur != nw) {
        *(u16 *)cur &= ~1;
        if (*(u16 *)(cur + 2) == 4) {
            t = *(u8 **)(cur + 0xBC);
            if (*(u16 *)(t + 0xF4) != 0xFFFF) {
                destroyNpcSlotChain(*(u16 *)(t + 0xF4));
                *(u16 *)(t + 0xF4) = 0xFFFF;
            }
            *(u16 *)(*(u8 **)(cur + 0xBC)) &= ~1;
            t = *(u8 **)(cur + 0xC0);
            if (*(u16 *)(t + 0xF4) != 0xFFFF) {
                destroyNpcSlotChain(*(u16 *)(t + 0xF4));
                *(u16 *)(t + 0xF4) = 0xFFFF;
            }
            *(u16 *)(*(u8 **)(cur + 0xC0)) &= ~1;
        }
        if (*(u16 *)(cur + 0xF4) != 0xFFFF) {
            destroyNpcSlotChain(*(u16 *)(cur + 0xF4));
            *(u16 *)(cur + 0xF4) = 0xFFFF;
        }
        D_main_bss_80138D18[idx].unk4 = nw;
        *(u16 *)nw |= 1;
        if (copy) {
            *(Blob30 *)(nw + 0x28) = *(Blob30 *)(cur + 0x28);
            *(f32 *)(nw + 0x10) = *(f32 *)(nw + 0x4C);
            *(f32 *)(nw + 0x14) = *(f32 *)(nw + 0x50);
            *(f32 *)(nw + 0x18) = *(f32 *)(nw + 0x54);
        }
        *(f32 *)(nw + 0x98) = *(f32 *)(nw + 0xA0);
        *(f32 *)(nw + 0x9C) = *(f32 *)(nw + 0xA0);
        dt = 0.033333335f;
        updatePlayerVehicleByControlMode(nw, dt);
        updateEffectObjectOrientationQuat(&D_main_bss_80138D18[*(s32 *)(nw + 0xC)], nw, dt);
        updateAudioListenerPosFromPlayer();
    }
}

typedef struct { s32 b[12]; } Blob30Dup;
extern u8 D_main_bss_80138930[][4][0xF8];
extern void destroyNpcSlotChain(u16);
extern void updatePlayerVehicleByControlMode(void *, f32);
extern void updateEffectObjectOrientationQuat(void *, void *, f32);
extern void updateAudioListenerPosFromPlayer(void);

void releaseEffectObjectNpcSlotsVariant(s32 idx, s32 view, u8 copy)
{
  u8 *cur;
  u8 *nw;
  u8 *t;
  f32 dt;
  f32 a;
  u8 *new_var;
  cur = D_main_bss_80138D18[idx].unk4;
  nw = D_main_bss_80138930[idx][view];
  if (cur != nw)
  {
    *((u16 *) cur) &= ~1;
    if ((*((u16 *) (cur + 2))) == 4)
    {
      t = *((u8 **) (cur + 0xBC));
      if ((*((u16 *) (t + 0xF4))) != 0xFFFF)
      {
        destroyNpcSlotChain(*((u16 *) (t + 0xF4)));
        *((u16 *) (t + 0xF4)) = 0xFFFF;
      }
      *((u16 *) (*((u8 **) (cur + 0xBC)))) &= ~1;
      t = *((u8 **) (cur + 0xC0));
      if ((*((u16 *) (t + 0xF4))) != 0xFFFF)
      {
        destroyNpcSlotChain(*((u16 *) (t + 0xF4)));
        *((u16 *) (t + 0xF4)) = 0xFFFF;
      }
      *((u16 *) (*((u8 **) (cur + 0xC0)))) &= ~1;
    }
    new_var = cur + 0xF4;
    if ((*((u16 *) (cur + 0xF4))) != 0xFFFF)
    {
      destroyNpcSlotChain(*((u16 *) new_var));
      *((u16 *) (cur + 0xF4)) = 0xFFFF;
    }
    D_main_bss_80138D18[idx].unk4 = nw;
    *((u16 *) nw) |= 1;
    if ((!((*((u16 *) nw)) & 0x20)) && copy)
    {
      *((Blob30 *) (nw + 0x28)) = *((Blob30 *) (cur + 0x28));
      ;
      *((f32 *) (nw + 0x10)) = *((f32 *) (nw + 0x4C));
      *((f32 *) (nw + 0x14)) = *((f32 *) (nw + 0x50));
      *((f32 *) (nw + 0x18)) = *((f32 *) (nw + 0x54));
      *((f32 *) (nw + 0x98)) = *((f32 *) (nw + 0xA0));
      *((f32 *) (nw + 0x9C)) = *((f32 *) (nw + 0xA0));
    }
    dt = 0.033333335f;
    updatePlayerVehicleByControlMode(nw, dt);
    updateEffectObjectOrientationQuat(&D_main_bss_80138D18[*((s32 *) (nw + 0xC))], nw, dt);
    updateAudioListenerPosFromPlayer();
  }
}

typedef struct {
    u16 flags;
    u16 f2;
    u16 type;
    u16 f6;
    s32 f8;
    s32 idx;
    u8 pad10[0x18];
    f32 m28[9];
    f32 f4C;
    f32 f50;
    f32 f54;
    u8 pad58[0x18];
    void *f70;
    u8 pad74[0x5C];
    f32 fD0;
    f32 fD4;
    f32 fD8;
    f32 fDC;
    f32 fE0;
    f32 fE4;
    f32 fE8;
} BeObj;
typedef struct {
    u8 pad0[0xB8];
    u16 craft;
    u8 padBA[0xCA];
    u16 f184;
    u8 pad186[0x11A];
} BePlayer;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} BeV3;
typedef struct {
    f32 x;
    f32 y;
} BeStick;
typedef struct {
    u8 pad0[6];
    u16 mask;
    u8 pad8[0x1C];
} BeBind;
typedef struct {
    s32 pad[3];
    s32 f;
} BeGs;
extern BePlayer bePlayers[] __asm__("gPlayers");
extern BeV3 D_mission_overlay_8010A144[];
extern BeStick D_8010BDD8[];
extern BeBind D_8010BE18[];
extern u16 D_main_bss_80130B88[][3];
extern s32 D_8010CA20;
extern u8 D_main_bss_80138838;
extern u8 D_main_bss_80137CF4;
extern s32 beGs[] __asm__("gGameSettings");
u8 getHudSecondaryWeponCount(void);
u8 isHudSecondaryWeaponActive(void);
f32 getConfigFloatValue(void);
void buildTransformMatrixFromEulerAngles(void *, f32, f32, f32);
void mat3x4Multiply(void *, void *, void *);
static __inline__ f32 beAbs(f32 x) {
    f32 r;
    FABSF(r, x);
    return r;
}

void buildEffectObjectWorldTransform(BeObj *o, f32 dt) {
    f32 m[12];
    f32 sv[3];
    s32 t;

    if (o->type == 3) {
        o->fD4 = D_mission_overlay_8010A144[bePlayers[o->idx].craft].x;
        o->fE4 = D_mission_overlay_8010A144[bePlayers[o->idx].craft].y;
        o->fE8 = D_mission_overlay_8010A144[bePlayers[o->idx].craft].z;
    } else {
        o->fD4 = 80.0f;
        o->fE4 = -45.0f;
        o->fE8 = 45.0f;
    }
    if (o->flags & 0x10) {
        return;
    }
    if (D_main_bss_80138838 != 0) {
        return;
    }
    if (!(bePlayers[o->idx].f184 & 1)) {
        return;
    }
    if (D_8010CA20 == 0 && (t = o->type) < 4 && t != 0) {
        if (D_main_bss_80130B88[o->idx][0] & D_8010BE18[o->idx].mask) {
            if (D_8010BDD8[o->idx].x != 0.0f || D_8010BDD8[o->idx].y != 0.0f) {
                if (D_8010BDD8[o->idx].x != 0.0f) {
                    o->fD0 += -D_8010BDD8[o->idx].x * 90.0f * dt;
                }
                if (D_8010BDD8[o->idx].y != 0.0f) {
                    o->fE0 += D_8010BDD8[o->idx].y * 90.0f * dt;
                }
            }
            if (D_main_bss_80130B88[o->idx][0] & D_8010BE18[o->idx].mask) {
            if (D_8010BDD8[o->idx].x != 0.0f || D_8010BDD8[o->idx].y != 0.0f) {
                if (*(u16 *)((u8 *)D_main_bss_80138D18[o->idx].unk4 + 4) == 3) {
                    if (o->fE0 < o->fE4) {
                        o->fE0 = o->fE4;
                    }
                } else if (beAbs(o->fE0) > beAbs(o->fE4)) {
                    if (o->fE0 < 0.0f) {
                        o->fE0 = o->fE4;
                    } else {
                        o->fE0 = -o->fE4;
                    }
                }
                if (beAbs(o->fD0) > o->fD4) {
                    if (0.0f < o->fD0) {
                        o->fD0 = o->fD4;
                    } else {
                        o->fD0 = -o->fD4;
                    }
                }
            }
            }
        }
        if (o->fE0 > o->fE8) {
            o->fE0 = o->fE8;
        }
        if ((((BeGs *)&beGs[o->idx])->f & 0x100) || *(u16 *)((u8 *)D_main_bss_80138D18[o->idx].unk4 + 4) != 3) {
            if (!(D_main_bss_80130B88[o->idx][0] & D_8010BE18[o->idx].mask) || D_8010BDD8[o->idx].x == 0.0f) {
                if (0.0f < o->fD0) {
                    o->fD0 -= dt * 90.0f;
                    if (o->fD0 < 0.0f) {
                        o->fD0 = 0.0f;
                    }
                } else {
                    o->fD0 += dt * 90.0f;
                    if (0.0f < o->fD0) {
                        o->fD0 = 0.0f;
                    }
                }
            }
            if (!(D_main_bss_80130B88[o->idx][0] & D_8010BE18[o->idx].mask) || D_8010BDD8[o->idx].y == 0.0f) {
                if (0.0f < o->fE0) {
                    o->fE0 -= dt * 90.0f;
                    if (o->fE0 < 0.0f) {
                        o->fE0 = 0.0f;
                    }
                } else {
                    o->fE0 += dt * 90.0f;
                    if (0.0f < o->fE0) {
                        o->fE0 = 0.0f;
                    }
                }
            }
        }
        if (bePlayers[o->idx].craft == 1 && getHudSecondaryWeponCount() != 0
            && *(u16 *)((u8 *)D_main_bss_80138D18[o->idx].unk4 + 4) == 3) {
            if (0.0f < getConfigFloatValue() || isHudSecondaryWeaponActive() != 0) {
                o->fE0 = 45.0f;
            }
        }
    }
    sv[0] = o->f4C;
    sv[1] = o->f50;
    sv[2] = o->f54;
    o->f4C = 0.0f;
    o->f50 = 0.0f;
    o->f54 = 0.0f;
    if (*(u16 *)((u8 *)D_main_bss_80138D18[o->idx].unk4 + 4) == 3) {
        buildTransformMatrixFromEulerAngles(m, o->fD0, o->fE0, o->f54);
        mat3x4Multiply(o->f70, m, o->m28);
    } else if (D_main_bss_80137CF4 == 0) {
        {
        f32 z = o->f54;
        buildTransformMatrixFromEulerAngles(m, o->fD0, z, z);
        mat3x4Multiply(o->m28, m, o->m28);
        }
    }
    o->f4C = sv[0];
    o->f50 = sv[1];
    o->f54 = sv[2];
}

#define UNK4(n) (*(u8 * volatile *)((u8 *)(n) + 4))
void deImpl(f32 dt) __asm__("destroyEffectObjectTypeNpcSlots");
extern u16 getNextSlotNpcTypeId(u16);

void deImpl(f32 dt) {
    s32 i;
    s32 j;
    SceneNode *n;
    SceneNode *n2;
    u8 *p;
    u8 *q;
    u32 id;

    for (i = 0; i < 1; i++) {
        n = &D_main_bss_80138D18[i];
        if (n->unk0 != 0) {
            if (D_8010CA20 == 5) {
                p = UNK4(n);
                if (*(u16 *)(p + 0xF4) != 0xFFFF && getNextSlotNpcTypeId(*(u16 *)(p + 0xF4)) == 0xFFFF) {
                    *(s16 *)(p + 2) = 0;
                    *(s16 *)(p + 4) = 0;
                    if (*(u16 *)(p + 0xF4) != 0xFFFF) {
                        destroyNpcSlotChain(*(u16 *)(p + 0xF4));
                        *(u16 *)(p + 0xF4) = 0xFFFF;
                    }
                }
                updatePlayerVehicleByControlMode(UNK4(n), dt);
                updateEffectObjectOrientationQuat(n, UNK4(n), dt);
            } else {
                for (j = 0; j < 6; j++) {
                    p = D_main_bss_80138268[i][j];
                    if (*(u16 *)p & 1) {
                        f32 f = *(f32 *)(p + 0xCC);
                        if (f > 0.0f) {
                            f -= dt;
                            *(f32 *)(p + 0xCC) = f;
                            if (f < 0.0f) {
                                *(f32 *)(p + 0xC4) = -f;
                                *(f32 *)(p + 0xCC) = 0.0f;
                            }
                        } else {
                            *(f32 *)(p + 0xC4) = *(f32 *)(p + 0xC4) + dt;
                        }
                        if (*(u16 *)(p + 0xF4) != 0xFFFF && getNextSlotNpcTypeId(*(u16 *)(p + 0xF4)) == 0xFFFF) {
                            *(s16 *)(p + 2) = 0;
                            *(s16 *)(p + 4) = 0;
                            if (*(u16 *)(p + 0xF4) != 0xFFFF) {
                                destroyNpcSlotChain(*(u16 *)(p + 0xF4));
                                *(u16 *)(p + 0xF4) = 0xFFFF;
                            }
                        }
                        updatePlayerVehicleByControlMode(p, dt);
                        updateEffectObjectOrientationQuat(n, p, dt);
                    }
                }
                for (j = 0; j < 4; j++) {
                    p = D_main_bss_80138930[i][j];
                    if (*(u16 *)p & 1) {
                        f32 f = *(f32 *)(p + 0xCC);
                        if (f > 0.0f) {
                            f -= dt;
                            *(f32 *)(p + 0xCC) = f;
                            if (f < 0.0f) {
                                *(f32 *)(p + 0xC4) = -f;
                                *(f32 *)(p + 0xCC) = 0.0f;
                            }
                        } else {
                            *(f32 *)(p + 0xC4) = *(f32 *)(p + 0xC4) + dt;
                        }
                        if (*(u16 *)(p + 0xF4) != 0xFFFF) {
                            id = getNextSlotNpcTypeId(*(u16 *)(p + 0xF4)) & 0xFFFF;
                            if (id == 0xFFFF) {
                                *(s16 *)(p + 2) = 0;
                                *(s16 *)(p + 4) = 0;
                                if (*(u16 *)(p + 0xF4) != 0xFFFF) {
                                    destroyNpcSlotChain(*(u16 *)(p + 0xF4));
                                    *(u16 *)(p + 0xF4) = 0xFFFF;
                                }
                            }
                        }
                        updatePlayerVehicleByControlMode(p, dt);
                        updateEffectObjectOrientationQuat(n, p, dt);
                    }
                }
            }
        }
        n2 = &D_main_bss_80138D18[i];
        buildEffectObjectWorldTransform((BeObj *)UNK4(n2), dt);
        q = UNK4(n2);
        if (*(u16 *)q & 0x40) {
            updateEffectObjectMotionOnTerrain((EoObj *)q, dt);
        }
    }
}

typedef struct {
    u16 h0;
    u16 h2;
    u16 h4;
    u16 h6;
    s32 w8;
    s32 player;
    u8 pad10[0x48];
    f32 v58[3];
    f32 v64[3];
    u8 pad70[4];
    s32 key;
    f32 v78[3];
    f32 v84[3];
    u8 pad90[4];
    f32 f94;
    u8 pad98[4];
    f32 f9C;
    f32 fA0;
    u8 padA4[4];
    f32 fA8;
    u8 padAC[0x4C];
} CbObj;
typedef struct {
    u8 pad0[0x14];
    u16 h14;
    u16 h16;
    u8 pad18[8];
    u16 h20;
    u8 pad22[2];
} CbBind;
typedef struct {
    u8 pad0[0xB8];
    u16 hB8;
    u8 padBA[0xCA];
    u16 h184;
    u8 pad186[0x11A];
} CbPlayer;
typedef struct { s32 pad[3]; s32 f; } CbGs;
typedef struct { f32 x, y, z, w; } CbV4;
extern u8 D_main_bss_80138925;
extern u8 D_main_bss_80138926;
extern CbBind cbBind[] __asm__("D_8010BE18");
extern CbPlayer cbPlayers[] __asm__("gPlayers");
extern CbObj cbObjs[][6] __asm__("D_main_bss_80138268");

static __inline__ void cbStep(f32 *tgt, f32 *dst, f32 *pos, f32 k) {
    CbV4 t;

    t.x = tgt[0] - pos[0];
    t.y = tgt[1] - pos[1];
    t.z = tgt[2] - pos[2];
    addScaledVec3ToVec3(dst, pos, k, &t.x);
}

void computeBootConfigScaledVec4(s32 idx, f32 a, f32 b, s32 key, f32 c, f32 d) {
    CbV4 v;
    CbV4 w;
    CbObj *o;
    s32 i;
    s32 p;

    if (D_main_bss_80138925 != 0 || D_main_bss_80138926 != 0 || D_main_bss_80137CF4 != 0) {
        return;
    }
    for (i = 0; i < 6; i++) {
        o = &cbObjs[idx][i];
        if (!(o->h0 & 1)) {
            continue;
        }
        if (o->h2 != 3) {
            continue;
        }
        if (o->key != key) {
            continue;
        }
        switch (o->h4) {
        case 2:
            o->f94 = b / 5.0f;
            break;
        case 3:
            o->f94 = b;
            break;
        default:
            o->f94 = a;
            o->f9C = c * o->fA0;
            break;
        }
        if ((((CbGs *)&beGs[idx])->f & 0x1000000) && (D_main_bss_80130B88[idx][0] & cbBind[idx].h20)
            && !(cbPlayers[idx].h184 & 2) && !(*(u16 *)D_main_bss_80138D18[idx].unk4 & 0x10)) {
            o->fA8 += d;
            if (1.0f < o->fA8) {
                o->fA8 = 1.0f;
            }
        } else {
            o->fA8 -= d;
            if (o->fA8 < 0.0f) {
                o->fA8 = 0.0f;
            }
        }
        p = o->player;
        if (cbPlayers[p].hB8 == 8 && o->w8 < 2 && (D_main_bss_80130B88[p][0] & cbBind[p].h20)) {
            o->f94 = b * 0.5f;
            if ((D_main_bss_80130B88[o->player][0] & cbBind[o->player].h14) || (D_main_bss_80130B88[o->player][0] & cbBind[o->player].h16)) {
                o->f94 = b;
            }
        }
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = o->v64[2];
        __asm__("");
        w.x = 0.0f;
        w.y = 0.0f;
        w.z = o->v84[2];
        cbStep(&v.x, o->v58, o->v64, o->fA8);
        cbStep(&w.x, o->v78, o->v84, o->fA8);
    }
}

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 w[4];
    f32 f[3];
} PvSub;
typedef struct {
    u8 b0;
    u8 pad1[3];
    void *p4;
    PvSub sub;
    u8 q34[0x110];
} PvNode;
typedef struct { s32 w[4]; } PvTbl;
extern PvNode pvNodes[] __asm__("D_main_bss_80138D18");
extern PvNode *pvCur __asm__("D_main_bss_80138894");
extern PvTbl D_main_8009DEE0[];
void resetEffectObjectVecQuads(s32);
s32 getBootConfigField12(void);
s32 getBootConfigField14(void);

void initPlayerVehicleStateTables(void) {
    s32 i;
    PvNode *n;
    PvSub *s;

    D_main_bss_80138260 = 1;
    for (i = 0; i < 1; i++) {
        resetEffectObjectVecQuads(i);
        n = &pvNodes[i];
        s = &n->sub;
        n->b0 = 0;
        n->p4 = D_main_bss_80138268[i];
        n->sub.a = 0;
        s->b = 0;
        s->d = 0;
        s->c = 0;
        s->w[0] = D_main_8009DEE0[i].w[0];
        s->w[1] = D_main_8009DEE0[i].w[1];
        s->w[2] = D_main_8009DEE0[i].w[2];
        s->w[3] = D_main_8009DEE0[i].w[3];
        s->f[0] = 65.0f;
        s->f[1] = 0.1171875f;
        s->f[2] = 93.75f;
        clearVec4QuadStruct((void *)n->q34);
    }
    pvCur = pvNodes;
    if (D_main_bss_80138260 == 1) {
        s = &pvNodes[0].sub;
        pvNodes[0].b0 = 1;
        s->w[0] = (u16)getBootConfigField12();
        s->w[1] = (u16)getBootConfigField14();
        s->w[3] = (u32)s->w[1] >> 1;
        s->w[2] = s->w[0] / 2;
    } else {
        for (i = 0; i < 1; i++) {
            pvNodes[i].b0 = 1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/4D900", updateMultiNodeAudioListeners);

extern u8 D_main_bss_80138930[][4][0xF8];
extern u8 D_main_8009EC14[];
extern u8 D_main_8009EBBC;
extern u16 D_ebc4u __asm__("D_main_8009EBC4");
extern u8 D_rA80[] __asm__("D_main_bss_80137A80");

#define INIT_EFF(e, B, X1, X2) \
    *(u16 *)(e + 2) = 0; \
    *(u16 *)(e + 4) = 0; \
    *(u16 *)(e + 0) = 0; \
    clearVec4QuadStruct(e + 0x28); \
    *(f32 *)(e + 0xC8) = 1.0f; \
    *(s32 *)(e + 0x58) = 0; \
    *(s32 *)(e + 0x5C) = 0; \
    *(s32 *)(e + 0x60) = 0; \
    *(s32 *)(e + 0x64) = 0; \
    *(s32 *)(e + 0x68) = 0; \
    *(s32 *)(e + 0x6C) = 0; \
    *(s32 *)(e + 0x78) = 0; \
    *(s32 *)(e + 0x7C) = 0; \
    *(s32 *)(e + 0x80) = 0; \
    *(s32 *)(e + 0x84) = 0; \
    *(s32 *)(e + 0x88) = 0; \
    *(s32 *)(e + 0x8C) = 0; \
    *(s32 *)(e + 0x10) = 0; \
    *(s32 *)(e + 0x14) = 0; \
    *(s32 *)(e + 0x18) = 0; \
    *(s32 *)(e + 0x1C) = 0; \
    *(s32 *)(e + 0x20) = 0; \
    *(s32 *)(e + 0x24) = 0; \
    *(u8 **)(e + 0x70) = D_main_8009EC14; \
    *(u8 **)(e + 0x74) = D_main_8009EC14; \
    *(s32 *)(e + 0x90) = 0; \
    *(s32 *)(e + 0x94) = 0; \
    *(s32 *)(e + 0x98) = 0; \
    *(s32 *)(e + 0x9C) = 0; \
    *(s32 *)(e + 0xA0) = 0; \
    *(u8 **)(e + 0xBC) = (u8 *)B; \
    *(u8 **)(e + 0xC0) = (u8 *)B; \
    *(s32 *)(e + 0xC4) = 0; \
    *(s32 *)(e + 0xCC) = 0; \
    *(s32 *)(e + 0xD0) = 0; \
    *(s32 *)(e + 0xD8) = 0; \
    *(s32 *)(e + 0xE0) = 0; \
    *(s32 *)(e + 0xDC) = 0; \
    X1 \
    *(f32 *)(e + 0xB8) = 0.3515625f; \
    *(f32 *)(e + 0xD4) = 80.0f; \
    *(f32 *)(e + 0xE4) = -45.0f; \
    *(f32 *)(e + 0xE8) = 45.0f; \
    *(f32 *)(e + 0xA4) = 0.033333335f; \
    *(s32 *)(e + 0xA8) = 0; \
    *(f32 *)(e + 0xAC) = 0.075f; \
    *(f32 *)(e + 0xB0) = 10.0f; \
    *(s32 *)(e + 0xEC) = 0; \
    X2 \
    *(s32 *)(e + 0xF0) = 0; \
    *(s32 *)(e + 0xB4) = 0;

void resetEffectObjectVecQuads(s32 arg0)
{
    s32 i;
    u8 *e;
    register u16 ff asm("$18");

    D_main_bss_80138D18[arg0].unk4 = D_main_bss_80138268[arg0][2];
    for (i = 0; i < 6; i++) {
        e = D_main_bss_80138268[arg0][i];
        *(s32 *)(e + 8) = i;
        *(s32 *)(e + 0xC) = arg0;
        INIT_EFF(e, D_main_bss_80138268, *(u16 *)(e + 0xF4) = 0xFFFF;, ;)
    }
    for (i = 0; i < 4; ) {
        e = D_main_bss_80138930[arg0][i];
        *(s32 *)(e + 8) = i;
        *(s32 *)(e + 0xC) = arg0;
        *(u16 *)(e + 2) = 0;
        *(u16 *)(e + 4) = 0;
        *(u16 *)(e + 0) = 0;
        clearVec4QuadStruct(e + 0x28);
        i++;
        ff = 0xFFFF;
        *(f32 *)(e + 0xC8) = 1.0f;
        *(s32 *)(e + 0x58) = 0;
        *(s32 *)(e + 0x5C) = 0;
        *(s32 *)(e + 0x60) = 0;
        *(s32 *)(e + 0x64) = 0;
        *(s32 *)(e + 0x68) = 0;
        *(s32 *)(e + 0x6C) = 0;
        *(s32 *)(e + 0x78) = 0;
        *(s32 *)(e + 0x7C) = 0;
        *(s32 *)(e + 0x80) = 0;
        *(s32 *)(e + 0x84) = 0;
        *(s32 *)(e + 0x88) = 0;
        *(s32 *)(e + 0x8C) = 0;
        *(s32 *)(e + 0x10) = 0;
        *(s32 *)(e + 0x14) = 0;
        *(s32 *)(e + 0x18) = 0;
        *(s32 *)(e + 0x1C) = 0;
        *(s32 *)(e + 0x20) = 0;
        *(s32 *)(e + 0x24) = 0;
        *(u8 **)(e + 0x70) = D_main_8009EC14;
        *(u8 **)(e + 0x74) = D_main_8009EC14;
        *(s32 *)(e + 0x90) = 0;
        *(s32 *)(e + 0x94) = 0;
        *(s32 *)(e + 0x98) = 0;
        *(s32 *)(e + 0x9C) = 0;
        *(s32 *)(e + 0xA0) = 0;
        *(u8 **)(e + 0xBC) = (u8 *)D_main_bss_80138268;
        *(u8 **)(e + 0xC0) = (u8 *)D_main_bss_80138268;
        *(s32 *)(e + 0xC4) = 0;
        *(s32 *)(e + 0xCC) = 0;
        *(s32 *)(e + 0xD0) = 0;
        *(s32 *)(e + 0xD8) = 0;
        *(s32 *)(e + 0xE0) = 0;
        *(s32 *)(e + 0xDC) = 0;
        *(u16 *)e = 0x10;
        *(f32 *)(e + 0xB8) = 0.3515625f;
        *(f32 *)(e + 0xD4) = 80.0f;
        *(f32 *)(e + 0xE4) = -45.0f;
        *(f32 *)(e + 0xE8) = 45.0f;
        *(f32 *)(e + 0xA4) = 0.033333335f;
        *(s32 *)(e + 0xA8) = 0;
        *(f32 *)(e + 0xAC) = 0.075f;
        *(f32 *)(e + 0xB0) = 10.0f;
        *(s32 *)(e + 0xEC) = 0;
        *(u16 *)(e + 0xF4) = ff;
        *(s32 *)(e + 0xF0) = 0;
        *(s32 *)(e + 0xB4) = 0;
    }
    updateAudioListenerPosFromPlayer();
    D_main_8009EBBC = 0;
    ff = 0xFFFF;
    D_ebc4u = ff;
    clearVec4QuadStruct(D_rA80);
}

extern u8 D_main_bss_80138930[][4][0xF8];
typedef struct {
    u8 pad0[0x1CC];
    s32 view;
    u8 pad1D0[0x84];
    f32 ref[0x13];
} AsnPlayer;
extern AsnPlayer asnPlayers[] __asm__("gPlayers");

void activateSceneNodeAndAudioListener(s32 idx) {
    SceneNode *n;
    u8 *top;
    u8 *cur;
    register u8 *craft asm("$5");
    u8 *nw;
    f32 *ref;
    f32 zero;
    f32 one;

    zero = 0.0f;
    top = D_main_bss_80138268[idx][5];
    *(u16 *)top |= 0x400;
    { SceneNode *b = D_main_bss_80138D18; n = &b[idx]; }
    n->unk4 = top;
    updateEffectObjectOrientationQuat(n, top, zero);
    { register s32 o asm("$2") = (s32)D_main_bss_80138268[0][asnPlayers[idx].view]; craft = (u8 *)(idx * 0x5D0 + o); }
    cur = n->unk4;
    one = 1.0f;
    ref = asnPlayers[idx].ref;
    if (cur != craft) {
        nw = D_main_bss_80138930[idx][0];
        *(u16 *)(nw + 2) = 4;
        *(u8 **)(nw + 0xBC) = cur;
        *(u8 **)(nw + 0xC0) = craft;
        *(f32 *)(nw + 0xC4) = zero;
        *(f32 *)(nw + 0xC8) = one;
        *(f32 *)(nw + 0xCC) = one;
        *(f32 **)(nw + 0x74) = ref;
        *(u16 *)nw |= 1;
        if (D_main_bss_80138260 == 1) {
            D_main_bss_80138894->unk4 = nw;
        }
        n->unk4 = nw;
        *(Blob30 *)(nw + 0x28) = *(Blob30 *)(cur + 0x28);
        *(RoV3 *)(nw + 0x10) = *(RoV3 *)(cur + 0x10);
        *(RoV3 *)(nw + 0x1C) = *(RoV3 *)(cur + 0x1C);
        *(u16 *)cur |= 1;
        *(u16 *)craft |= 1;
        *(Blob30 *)(craft + 0x28) = *(Blob30 *)(cur + 0x28);
        *(f32 *)(craft + 0x10) = *(f32 *)(craft + 0x4C);
        *(f32 *)(craft + 0x14) = *(f32 *)(craft + 0x50);
        *(f32 *)(craft + 0x18) = *(f32 *)(craft + 0x54);
        *(f32 *)(craft + 0x98) = *(f32 *)(craft + 0xA0);
        *(f32 *)(craft + 0x9C) = *(f32 *)(craft + 0xA0);
        D_main_bss_80138D18[idx].unk4 = nw;
        updateAudioListenerPosFromPlayer();
    }
}

typedef struct { s32 w[12]; } EfM48;
typedef struct { s32 a, b, c; } EfV3;
typedef struct { u8 b[0x2A0]; } SaPlayer_l;
extern f32 D_mission_overlay_8010A144_b[][3] __asm__("D_mission_overlay_8010A144");
extern SaPlayer_l D_main_bss_8013800C_l[] __asm__("D_main_bss_8013800C");
extern u8 D_main_8009EC14[];
extern u8 D_main_8009EBBC;
extern u16 D_main_8009EBC4_l __asm__("D_main_8009EBC4");
extern u8 D_main_bss_80137A80_u8[] __asm__("D_main_bss_80137A80");
extern f32 D_mission_overlay_8010A144_l[][3] __asm__("D_mission_overlay_8010A144");
extern void transformVec3ByMat34(void *, f32 *, f32 *);
extern void scaleVec3ByScalar(f32 *, f32, f32 *);
extern void resetEffectObjectVecQuads(s32);
extern void activateSceneNodeAndAudioListener(s32);
extern void applyPlayerVehicleStateUpdate(u8 *);

void updateEffectObjectTransformPieces(void *s3v, s32 arg1, s32 arg2, f32 arg3, s32 arg4) {
    f32 sp10[3];
    f32 sp20[3];
    s32 sp30;
    u8 *sp34;
    f32 (*tb1)[3];
    f32 (*tb2)[3];
    u8 *s4;
    register u8 *s6 asm("$22");
    f32 *s2;
    f32 *s0;
    u8 *s1;
    register s32 s5 asm("$21");
    register s32 s7 asm("$23");
    s32 v1;
#define s3 ((u8*)s3v)
    u8 *t0;

    resetEffectObjectVecQuads(arg1);
    s7 = 0;
    sp30 = arg1 * 3;
    v1 = arg1 * 21;
    v1 <<= 5;
    t0 = (u8 *)D_main_bss_8013800C_l;
    s4 = t0 + v1;
    t0 -= 0x254;
    s6 = t0 + v1;
    t0 += 0x284;
    sp34 = t0 + v1;
    s5 = s7;
    tb1 = D_mission_overlay_8010A144_l;
    tb2 = D_mission_overlay_8010A144_b;
    s2 = (f32 *)(s3 + 0xC);
  loop:
    {
        s1 = &D_main_bss_80138268[0][0][0] + sp30 * 0x1F0 + s5;
        *(u16 *)(s1 + 4) = *(u16 *)s3;
        *(u16 *)(s1 + 2) = *(u16 *)((u8 *)s2 - 0xA);
        *(u16 *)(s1 + 0) = *(u16 *)((u8 *)s2 - 8);
        *(f32 *)(s1 + 0x9C) = s2[-1];
        *(f32 *)(s1 + 0xA0) = s2[-1];
        *(f32 *)(s1 + 0x98) = s2[-1];
        scaleVec3ByScalar((f32 *)(s1 + 0x10), arg3, s2);
        *(f32 *)(s1 + 0x4C) = *(f32 *)(s1 + 0x10);
        *(f32 *)(s1 + 0x50) = *(f32 *)(s1 + 0x14);
        *(f32 *)(s1 + 0x54) = *(f32 *)(s1 + 0x18);
        scaleVec3ByScalar((f32 *)(s1 + 0x1C), arg3, (f32 *)(s3 + 0x18));
        scaleVec3ByScalar((f32 *)(s1 + 0x58), arg3, (f32 *)(s3 + 0x24));
        scaleVec3ByScalar((f32 *)(s1 + 0x64), arg3, (f32 *)(s3 + 0x24));
        scaleVec3ByScalar((f32 *)(s1 + 0x78), arg3, (f32 *)(s3 + 0x30));
        scaleVec3ByScalar((f32 *)(s1 + 0x84), arg3, (f32 *)(s3 + 0x30));
        switch (*(u16 *)(s1 + 2)) {
        case 1: {
            u8 *src;
            s32 *d;
            *(u8 **)(s1 + 0x70) = s4;
            if (*(u16 *)(s1 + 4) != 3) {
                *(u8 **)(s1 + 0x74) = s4;
            } else {
                *(u8 **)(s1 + 0x74) = 0;
                *(f32 *)(s1 + 0xD4) = tb1[*(u16 *)(s6 + 0xB8)][0];
                *(f32 *)(s1 + 0xE4) = tb2[*(u16 *)(s6 + 0xB8)][1];
                *(f32 *)(s1 + 0xE8) = 5.0f;
            }
            d = (s32 *)(s1 + 0x28);
            src = *(u8 **)(s1 + 0x70);
            *(u8 **)(s1 + 0x90) = sp34;
            *(EfM48 *)d = *(EfM48 *)src;
            *(EfV3 *)sp10 = *(EfV3 *)(s1 + 0x58);
            transformVec3ByMat34(s1 + 0x28, sp10, sp20);
            *(f32 *)(s1 + 0x4C) = sp20[0];
            *(f32 *)(s1 + 0x50) = sp20[1];
            *(f32 *)(s1 + 0x54) = sp20[2];
            *(EfV3 *)(s1 + 0x10) = *(EfV3 *)sp20;
            break;
        }
        case 2:
        case 3: {
            u8 *src;
            s32 *d;
            if (*(u16 *)(s1 + 4) == 2) {
                *(u8 **)(s1 + 0x90) = sp34;
            }
            src = s4;
            *(u8 **)(s1 + 0x70) = s4;
            *(u8 **)(s1 + 0x74) = s4;
            *(f32 *)(s1 + 0x98) = *(f32 *)(s1 + 0x9C);
            *(EfM48 *)(s1 + 0x28) = *(EfM48 *)src;
            scaleVec3ByScalar(sp10, 0.25f, s2);
            transformVec3ByMat34(s1 + 0x28, sp10, sp20);
            *(f32 *)(s1 + 0x4C) = sp20[0];
            *(f32 *)(s1 + 0x50) = sp20[1];
            *(f32 *)(s1 + 0x54) = sp20[2];
            *(EfV3 *)(s1 + 0x10) = *(EfV3 *)sp20;
            break;
        }
        default:
            *(u8 **)(s1 + 0x74) = D_main_8009EC14;
            break;
        }
        switch (*(u16 *)(s6 + 0xB8)) {
        case 4:
            *(f32 *)(s1 + 0xAC) = 0.065f;
            break;
        case 3:
            *(f32 *)(s1 + 0xAC) = 0.05f;
            break;
        default:
            *(f32 *)(s1 + 0xAC) = 0.075f;
            break;
        }
        applyPlayerVehicleStateUpdate(s1);
        s2 += 0xF;
        s3v = (u8*)s3v + 0x3C;
        s7 += 1;
        s5 += 0xF8;
    }
    if (s7 < 6) goto loop;
    activateSceneNodeAndAudioListener(arg1);
    updateAudioListenerPosFromPlayer();
    D_main_8009EBBC = 0;
    D_main_8009EBC4_l = 0xFFFF;
    clearVec4QuadStruct(D_main_bss_80137A80_u8);
}

typedef struct { u8 b[0x2A0]; } SaPlayer;
extern SaPlayer D_main_bss_8013800C[];
typedef struct { s32 a, b, c; } SrbV3;
typedef struct { s32 w[12]; } SrbM48;
extern u8 D_main_bss_80138A28[][0x3E0];
extern u8 D_main_8009EC14[];
extern u16 rand(void);
extern void applyPlayerVehicleStateUpdate(u8 *);

void spawnRandomizedEffectBurst(u8 *arg0) {
    u8 *e = D_main_bss_80138A28[*(s32 *)(arg0 + 0xB8)];
    u8 *t = (u8 *)&D_main_bss_8013800C[*(s32 *)(arg0 + 0xB8)];
    f32 v[3];
    f32 f;
    f32 g;
    f32 x;
    u8 *obj;

    *(u16 *)(e + 2) = 0;
    *(u16 *)(e + 4) = 0;
    *(u16 *)(e + 0) = 0;
    clearVec4QuadStruct(e + 0x28);
    *(u8 **)(e + 0x70) = D_main_8009EC14;
    *(u8 **)(e + 0x74) = D_main_8009EC14;
    *(s32 *)(e + 0x58) = 0;
    *(s32 *)(e + 0x5C) = 0;
    *(s32 *)(e + 0x60) = 0;
    *(s32 *)(e + 0x64) = 0;
    *(s32 *)(e + 0x68) = 0;
    *(s32 *)(e + 0x6C) = 0;
    *(s32 *)(e + 0x78) = 0;
    *(s32 *)(e + 0x7C) = 0;
    *(s32 *)(e + 0x80) = 0;
    *(s32 *)(e + 0x84) = 0;
    *(s32 *)(e + 0x88) = 0;
    *(s32 *)(e + 0x8C) = 0;
    *(s32 *)(e + 0x10) = 0;
    *(s32 *)(e + 0x14) = 0;
    *(s32 *)(e + 0x18) = 0;
    *(s32 *)(e + 0x1C) = 0;
    *(s32 *)(e + 0x20) = 0;
    *(s32 *)(e + 0x24) = 0;
    *(s32 *)(e + 0x90) = 0;
    *(s32 *)(e + 0x94) = 0;
    *(s32 *)(e + 0x98) = 0;
    *(s32 *)(e + 0x9C) = 0;
    *(s32 *)(e + 0xA0) = 0;
    *(u8 **)(e + 0xBC) = (u8 *)D_main_bss_80138268;
    *(u8 **)(e + 0xC0) = (u8 *)D_main_bss_80138268;
    *(s32 *)(e + 0xC4) = 0;
    *(s32 *)(e + 0xCC) = 0;
    *(s32 *)(e + 0xD0) = 0;
    *(s32 *)(e + 0xD8) = 0;
    *(s32 *)(e + 0xE0) = 0;
    *(f32 *)(e + 0xC8) = 1.0f;
    *(s32 *)(e + 0xDC) = 0;
    *(f32 *)(e + 0xD4) = 80.0f;
    *(u16 *)(e + 0xF4) = 0xFFFF;
    *(f32 *)(e + 0xB8) = 0.3515625f;
    *(f32 *)(e + 0xE4) = -45.0f;
    *(f32 *)(e + 0xE8) = 45.0f;
    *(f32 *)(e + 0xA4) = 0.033333335f;
    *(s32 *)(e + 0xA8) = 0;
    *(f32 *)(e + 0xAC) = 0.075f;
    *(f32 *)(e + 0xB0) = 10.0f;
    *(s32 *)(e + 0xEC) = 0;
    *(s32 *)(e + 0xF0) = 0;
    *(s32 *)(e + 0xB4) = 0;
    *(u16 *)(e + 0) = 0x53;
    *(f32 *)(e + 0x94) = 1.0f;
    *(f32 *)(e + 0xB8) = 1.5f;
    v[0] = *(f32 *)(t + 8);
    v[1] = *(f32 *)(t + 0x14);
    v[2] = *(f32 *)(t + 0x20);
    *(u16 *)(e + 2) = 2;
    *(u16 *)(e + 4) = 0;
    *(s32 *)(e + 0x9C) = 0;
    *(s32 *)(e + 0x98) = 0;
    x = ((f32)(rand() & 0x7F) - 64.0f) / 6.4f;
    FABSF(f, x);
    f = f + 10.0f;
    *(s32 *)(e + 0xDC) = 0;
    *(f32 *)(e + 0xAC) = 0.075f;
    *(f32 *)(e + 0x94) = f * 0.25f;
    x = ((f32)(rand() & 0x7F) - 64.0f) / 0.17777778f;
    FABSF(g, x);
    *(f32 *)(e + 0xD0) = g;
    *(s32 *)(e + 0xD8) = 0;
    x = ((f32)(rand() & 0x7F) - 64.0f) / 1.0666667f;
    FABSF(g, x);
    *(f32 *)(e + 0xE0) = g;
    *(s32 *)(e + 0x58) = 0;
    *(s32 *)(e + 0x5C) = 0;
    *(s32 *)(e + 0x60) = 0;
    *(SrbV3 *)(e + 0x64) = *(SrbV3 *)(e + 0x58);
    obj = D_main_bss_80138D18[*(s32 *)(arg0 + 0xB8)].unk4;
    *(SrbM48 *)(e + 0x28) = *(SrbM48 *)(obj + 0x28);
    *(f32 *)(e + 0x10) = *(f32 *)(e + 0x4C);
    *(f32 *)(e + 0x14) = *(f32 *)(e + 0x50);
    *(f32 *)(e + 0x18) = *(f32 *)(e + 0x54);
    applyPlayerVehicleStateUpdate(e);
    *(u8 **)(e + 0x70) = t;
    *(u8 **)(e + 0x74) = t;
    *(s32 *)(e + 0x78) = 0;
    *(s32 *)(e + 0x7C) = 0;
    *(s32 *)(e + 0x80) = 0;
    *(s32 *)(e + 0x84) = 0;
    *(s32 *)(e + 0x88) = 0;
    *(s32 *)(e + 0x8C) = 0;
    rotateObjectMatrixAboutStoredAxis(e, 0.033333335f);
    releaseEffectObjectNpcSlotsVariant(*(s32 *)(arg0 + 0xB8), 1, 0);
}

#include "rs_math.h"
typedef struct {
    f32 v[4];
    f32 p[4];
    f32 s[4];
    f32 q[4];
} SsdLocals;
static __inline__ f32 ssdAbs(f32 x) {
    f32 r;
    FABSF(r, x);
    return r;
}
extern void clampVec3ToUnitIfLongerThan(f32 *);
extern void scaleVec3ByScalar(f32 *, f32, f32 *);

void spawnScatteredDebrisParticles(u8 *arg0) {
    u8 *e;
    u8 *t;
    u8 *obj;
    s32 sel;
    s32 r;
    f32 x;
    register f32 f asm("$f0");
    SsdLocals l;

    if (*(u16 *)((u8 *)D_main_bss_80138D18[*(s32 *)(arg0 + 0xB8)].unk4 + 4) != 3 || !(rand() & 3)) {
        e = D_main_bss_80138A28[*(s32 *)(arg0 + 0xB8)];
        t = (u8 *)&D_main_bss_8013800C[*(s32 *)(arg0 + 0xB8)];
        *(u16 *)(e + 2) = 0;
        *(u16 *)(e + 4) = 0;
        *(u16 *)(e + 0) = 0;
        clearVec4QuadStruct(e + 0x28);
        *(u8 **)(e + 0x70) = D_main_8009EC14;
        *(u8 **)(e + 0x74) = D_main_8009EC14;
        *(s32 *)(e + 0x58) = 0;
        *(s32 *)(e + 0x5C) = 0;
        *(s32 *)(e + 0x60) = 0;
        *(s32 *)(e + 0x64) = 0;
        *(s32 *)(e + 0x68) = 0;
        *(s32 *)(e + 0x6C) = 0;
        *(s32 *)(e + 0x78) = 0;
        *(s32 *)(e + 0x7C) = 0;
        *(s32 *)(e + 0x80) = 0;
        *(s32 *)(e + 0x84) = 0;
        *(s32 *)(e + 0x88) = 0;
        *(s32 *)(e + 0x8C) = 0;
        *(s32 *)(e + 0x10) = 0;
        *(s32 *)(e + 0x14) = 0;
        *(s32 *)(e + 0x18) = 0;
        *(s32 *)(e + 0x1C) = 0;
        *(s32 *)(e + 0x20) = 0;
        *(s32 *)(e + 0x24) = 0;
        *(s32 *)(e + 0x90) = 0;
        *(s32 *)(e + 0x94) = 0;
        *(s32 *)(e + 0x98) = 0;
        *(s32 *)(e + 0x9C) = 0;
        *(s32 *)(e + 0xA0) = 0;
        *(u8 **)(e + 0xBC) = (u8 *)D_main_bss_80138268;
        *(u8 **)(e + 0xC0) = (u8 *)D_main_bss_80138268;
        *(s32 *)(e + 0xC4) = 0;
        *(s32 *)(e + 0xCC) = 0;
        *(s32 *)(e + 0xD0) = 0;
        *(s32 *)(e + 0xD8) = 0;
        *(s32 *)(e + 0xE0) = 0;
        *(f32 *)(e + 0xC8) = 1.0f;
        *(s32 *)(e + 0xDC) = 0;
        *(f32 *)(e + 0xD4) = 80.0f;
        *(f32 *)(e + 0xE4) = -45.0f;
        *(f32 *)(e + 0xE8) = 45.0f;
        *(f32 *)(e + 0xA4) = 0.033333335f;
        *(s32 *)(e + 0xA8) = 0;
        *(f32 *)(e + 0xAC) = 0.075f;
        *(f32 *)(e + 0xB0) = 10.0f;
        *(s32 *)(e + 0xEC) = 0;
        *(u16 *)(e + 0xF4) = 0xFFFF;
        *(f32 *)(e + 0xB8) = 0.3515625f;
        *(s32 *)(e + 0xF0) = 0;
        *(s32 *)(e + 0xB4) = 0;
        *(f32 *)(e + 0x94) = 1.0f;
        *(u16 *)(e + 0) |= 0x53;
        *(f32 *)(e + 0xB8) = 1.5f;
        r = rand() & 3;
        if (*(u16 *)((u8 *)D_main_bss_80138D18[*(s32 *)(arg0 + 0xB8)].unk4 + 4) == 2) {
            r = 3;
        }
        sel = r & 0xFFFF;
        l.v[0] = *(f32 *)(t + 8);
        l.v[1] = *(f32 *)(t + 0x14);
        l.v[2] = *(f32 *)(t + 0x20);
        switch (sel) {
        case 0:
        default:
            *(u16 *)(e + 2) = 2;
            *(u16 *)(e + 4) = 0;
            *(u16 *)(e + 0) |= 0x48;
            *(SrbM48 *)(e + 0x28) = *(SrbM48 *)t;
            *(s32 *)(e + 0x78) = 0;
            *(s32 *)(e + 0x7C) = 0;
            *(s32 *)(e + 0x80) = 0;
            l.v[1] = 0.0f;
            clampVec3ToUnitIfLongerThan(l.v);
            scaleVec3ByScalar(l.s, 2.0f * *(f32 *)(arg0 + 0xE8), l.v);
            l.p[0] = *(f32 *)(t + 0x24);
            l.p[1] = *(f32 *)(t + 0x28);
            l.p[2] = *(f32 *)(t + 0x2C);
            l.p[0] = l.s[0] + l.p[0];
            l.p[1] = l.s[1] + l.p[1];
            l.p[2] = l.s[2] + l.p[2];
            quatFromCardinalAxis(l.q, 1, ((f32)(rand() & 0x7F) - 64.0f) / 0.7111111f);
            l.v[1] = 0.0f;
            clampVec3ToUnitIfLongerThan(l.v);
            scaleVec3ByScalar(l.v, ssdAbs(((f32)(rand() & 0x7F) - 64.0f) * 0.015625f) + 1.0f, l.v);
            rotateVec3ByQuat(l.q, l.v, l.s);
            l.p[0] = l.s[0] + l.p[0];
            l.p[1] = l.s[1] + l.p[1];
            l.p[2] = l.s[2] + l.p[2];
            *(f32 *)(e + 0x4C) = l.p[0];
            *(f32 *)(e + 0x50) = l.p[1];
            *(f32 *)(e + 0x54) = l.p[2];
            applyPlayerVehicleStateUpdate(e);
            break;
        case 1:
            *(u16 *)(e + 2) = 2;
            *(u16 *)(e + 4) = 4;
            f = (fabsf(((f32)(rand() & 0x7F) - 64.0f) / 6.4f) + 10.0f) * 0.25f;
            *(f32 *)(e + 0xDC) = -0.125f;
            *(f32 *)(e + 0x94) = f;
            *(f32 *)(e + 0xD0) = ssdAbs(((f32)(rand() & 0x7F) - 64.0f) / 0.17777778f);
            if (ssdAbs(((f32)(rand() & 0x7F) - 64.0f) * 0.015625f) < 0.5f) {
                *(f32 *)(e + 0xD8) = 45.0f;
            } else {
                *(f32 *)(e + 0xD8) = -45.0f;
            }
            *(s32 *)(e + 0x58) = 0;
            *(s32 *)(e + 0x5C) = 0;
            *(s32 *)(e + 0x60) = 0;
            *(f32 *)(e + 0xE0) = 45.0f;
            obj = D_main_bss_80138D18[*(s32 *)(arg0 + 0xB8)].unk4;
            *(SrbM48 *)(e + 0x28) = *(SrbM48 *)(obj + 0x28);
            break;
        case 2:
            *(u16 *)(e + 2) = sel;
            *(u16 *)(e + 4) = 4;
            *(f32 *)(e + 0x9C) = 5.0f;
            *(f32 *)(e + 0x98) = 5.0f;
            f = (fabsf(((f32)(rand() & 0x7F) - 64.0f) / 6.4f) + 10.0f) * 0.25f;
            *(s32 *)(e + 0xDC) = 0;
            *(f32 *)(e + 0xAC) = 0.075f;
            *(u16 *)(e + 0) |= 0x40;
            *(f32 *)(e + 0x94) = f;
            *(f32 *)(e + 0xD0) = ssdAbs(((f32)(rand() & 0x7F) - 64.0f) / 0.17777778f);
            *(s32 *)(e + 0xD8) = 0;
            if (ssdAbs(((f32)(rand() & 0x7F) - 64.0f) * 0.015625f) < 0.5f) {
                *(f32 *)(e + 0xD0) = -*(f32 *)(e + 0xD0);
            }
            *(f32 *)(e + 0xE0) = ssdAbs(((f32)(rand() & 0x7F) - 64.0f) / 1.0666667f);
            *(s32 *)(e + 0x58) = 0;
            *(s32 *)(e + 0x5C) = 0;
            *(s32 *)(e + 0x60) = 0;
            obj = D_main_bss_80138D18[*(s32 *)(arg0 + 0xB8)].unk4;
            *(SrbM48 *)(e + 0x28) = *(SrbM48 *)(obj + 0x28);
            break;
        case 3:
            *(u16 *)(e + 2) = sel;
            *(u16 *)(e + 4) = 1;
            *(s32 *)(e + 0xDC) = 0;
            *(f32 *)(e + 0x9C) = 6.0f;
            *(f32 *)(e + 0x98) = 6.0f;
            *(f32 *)(e + 0x94) = 0.625f;
            x = ((f32)(rand() & 0x7F) - 64.0f) / 21.333334f * 0.25f;
            *(f32 *)(e + 0x5C) = -0.375f;
            *(f32 *)(e + 0x60) = -0.75f;
            *(f32 *)(e + 0xAC) = 0.05f;
            *(f32 *)(e + 0x58) = x;
            obj = D_main_bss_80138D18[*(s32 *)(arg0 + 0xB8)].unk4;
            *(SrbM48 *)(e + 0x28) = *(SrbM48 *)(obj + 0x28);
            break;
        }
        obj = D_main_bss_80138D18[*(s32 *)(arg0 + 0xB8)].unk4;
        {
            register u16 j asm("$3") = *(u16 *)(obj + 4);
            __asm__ volatile("" : : "r"(j));
        }
        *(f32 *)(e + 0x10) = *(f32 *)(e + 0x4C);
        *(f32 *)(e + 0x14) = *(f32 *)(e + 0x50);
        *(f32 *)(e + 0x18) = *(f32 *)(e + 0x54);
        *(SrbV3 *)(e + 0x64) = *(SrbV3 *)(e + 0x58);
        applyPlayerVehicleStateUpdate(e);
        *(u8 **)(e + 0x70) = t;
        *(u8 **)(e + 0x74) = t;
        *(s32 *)(e + 0x78) = 0;
        *(s32 *)(e + 0x7C) = 0;
        *(s32 *)(e + 0x80) = 0;
        *(s32 *)(e + 0x84) = 0;
        *(s32 *)(e + 0x88) = 0;
        *(s32 *)(e + 0x8C) = 0;
        *(s32 *)(e + 0x90) = 0;
        *(s32 *)(e + 0xA4) = 0;
        *(f32 *)(e + 0xB8) = 0.3515625f;
        *(f32 *)(e + 0xA0) = *(f32 *)(e + 0x9C);
        releaseEffectObjectNpcSlotsVariant(*(s32 *)(arg0 + 0xB8), 1, 0);
    }
}

#include "common_types.h"
typedef struct { s32 b[12]; } SaBlob30;
typedef struct { s32 a, b, c; } SaV3;
typedef struct {
    u16 flags;
    u8 pad2[0x6E];
    SaBlob30 *mat;
    f32 *node;
    u8 pad78[0x3E0 - 0x78];
} SaRec;
typedef struct { u8 pad[0x24]; f32 x, y, z; } SaPos;
extern u8 D_main_8009EBBC;
extern SaRec D_main_bss_80138C18[];
extern SaPos D_main_bss_80137A80;
extern void transformVec3ByMat34(void *, f32 *, f32 *);
extern void clampVec3ToUnitIfLongerThan(f32 *);
extern void scaleVec3ByScalar(f32 *, f32, f32 *);

void submitActiveEffectObjectRender(s32 idx) {
    f32 p[3];
    f32 q[3];
    f32 r[3];
    SaRec *rec;
    if (D_main_8009EBBC == 0) {
        rec = &D_main_bss_80138C18[idx];
        if (rec->flags & 1) {
            *rec->mat = *(SaBlob30 *)&D_main_bss_8013800C[idx];
            p[0] = 0;
            p[1] = -1.0f;
            p[2] = 0.75f;
            transformVec3ByMat34(rec->mat, p, p);
            q[0] = *(f32 *)((u8 *)rec->node + 0x24);
            q[1] = *(f32 *)((u8 *)rec->node + 0x28);
            q[2] = *(f32 *)((u8 *)rec->node + 0x2C);
            p[0] = p[0] - q[0];
            p[1] = p[1] - q[1];
            p[2] = p[2] - q[2];
            *(SaV3 *)r = *(SaV3 *)p;
            r[1] = 0;
            clampVec3ToUnitIfLongerThan(r);
            scaleVec3ByScalar(r, 2.0f, r);
            r[0] = p[0] + r[0];
            r[1] = p[1] + r[1];
            r[2] = p[2] + r[2];
            p[0] = q[0] + r[0];
            p[1] = q[1] + r[1];
            p[2] = q[2] + r[2];
            D_main_bss_80137A80.x = p[0];
            D_main_bss_80137A80.z = p[2];
            p[1] = p[1] - 0.25f;
            D_main_bss_80137A80.y = p[1];
        }
    }
}

extern s16 D_main_8009EBC4;
extern u8 *getNpcContextByIndex(u16);
extern u16 findFreeNpcSlotByKey(u16, u16);
extern void computeAngleToTargetFromTransform(u8 *, u8 *, u8 *);
typedef struct { s32 w[12]; } IeM48;
typedef struct { u8 pad[0xC8]; f32 c8; } IeObj;
typedef struct { s32 a, b, c; } IeV3;

void initEffectObjectDefaults(s32 arg0, u16 arg1) {
    u8 *e;
    u8 *s5;
    u16 a1s;
    u8 *ctx;
    u16 key;
    u8 *cur;
    u8 *c2;
    u8 *nw;
    f32 t;
    f32 fk = 0.3515625f;

    e = (u8 *)&D_main_bss_80138C18[arg0];
    s5 = e + 0x28;
    *(u16 *)(e + 2) = 0;
    *(u16 *)(e + 4) = 0;
    *(u16 *)(e + 0) = 0;
    clearVec4QuadStruct(s5);
    a1s = arg1;
    key = a1s;
    *(u8 **)(e + 0x70) = D_main_8009EC14;
    *(u8 **)(e + 0x74) = D_main_8009EC14;
    *(u8 **)(e + 0xBC) = (u8 *)D_main_bss_80138268;
    *(u8 **)(e + 0xC0) = (u8 *)D_main_bss_80138268;
    *(s32 *)(e + 0x58) = 0;
    *(s32 *)(e + 0x5C) = 0;
    *(s32 *)(e + 0x60) = 0;
    *(s32 *)(e + 0x64) = 0;
    *(s32 *)(e + 0x68) = 0;
    *(s32 *)(e + 0x6C) = 0;
    *(s32 *)(e + 0x78) = 0;
    *(s32 *)(e + 0x7C) = 0;
    *(s32 *)(e + 0x80) = 0;
    *(s32 *)(e + 0x84) = 0;
    *(s32 *)(e + 0x88) = 0;
    *(s32 *)(e + 0x8C) = 0;
    *(s32 *)(e + 0x10) = 0;
    *(s32 *)(e + 0x14) = 0;
    *(s32 *)(e + 0x18) = 0;
    *(s32 *)(e + 0x1C) = 0;
    *(s32 *)(e + 0x20) = 0;
    *(s32 *)(e + 0x24) = 0;
    *(s32 *)(e + 0x90) = 0;
    *(s32 *)(e + 0x94) = 0;
    *(s32 *)(e + 0x98) = 0;
    *(s32 *)(e + 0x9C) = 0;
    *(s32 *)(e + 0xA0) = 0;
    *(s32 *)(e + 0xC4) = 0;
    *(s32 *)(e + 0xCC) = 0;
    *(s32 *)(e + 0xD0) = 0;
    *(s32 *)(e + 0xD8) = 0;
    *(s32 *)(e + 0xE0) = 0;
    *(f32 *)(e + 0xC8) = 1.0f;
    *(s32 *)(e + 0xDC) = 0;
    *(f32 *)(e + 0xD4) = 80.0f;
    *(f32 *)(e + 0xE4) = -45.0f;
    *(f32 *)(e + 0xE8) = 45.0f;
    *(f32 *)(e + 0xA4) = 0.033333335f;
    *(s32 *)(e + 0xA8) = 0;
    *(f32 *)(e + 0xAC) = 0.075f;
    *(f32 *)(e + 0xB0) = 10.0f;
    *(s32 *)(e + 0xEC) = 0;
    *(u16 *)(e + 0xF4) = 0xFFFF;
    *(s32 *)(e + 0xF0) = 0;
    *(s32 *)(e + 0xB4) = 0;
    *(f32 *)(e + 0xB8) = fk;
    ctx = *(u8 **)(getNpcContextByIndex(key) + 0xC);
    if (ctx != 0) {
        f32 z = 0.0f;
        *(u16 *)(e + 0xF4) = findFreeNpcSlotByKey(0xFFFF, key);
        *(u16 *)(e + 0) = 0x13;
        *(u8 **)(e + 0x74) = ctx + 0x28;
        *(u8 **)(e + 0x70) = (u8 *)&D_main_bss_80137A80;
        D_main_8009EBBC = 0;
        *(s32 *)(e + 0x58) = 0;
        *(s32 *)(e + 0x5C) = 0;
        *(s32 *)(e + 0x60) = 0;
        *(IeV3 *)(e + 0x64) = *(IeV3 *)(e + 0x58);
        *(s32 *)(e + 0x78) = 0;
        *(s32 *)(e + 0x80) = 0;
        D_main_8009EBC4 = a1s;
        *(f32 *)(e + 0x7C) = -7.5f;
        *(IeV3 *)(e + 0x84) = *(IeV3 *)(e + 0x78);
        *(s32 *)(e + 0x90) = 0;
        *(f32 *)(e + 0xA8) = z;
        *(f32 *)(e + 0xA4) = z;
        *(f32 *)(e + 0xEC) = z;
        ((void (*)(s32, f32))submitActiveEffectObjectRender)(arg0, z);
        *(u16 *)(e + 2) = 3;
        *(u16 *)(e + 4) = 1;
        *(f32 *)(e + 0xDC) = z;
        *(f32 *)(e + 0x98) = z;
        *(f32 *)(e + 0xB8) = fk;
        *(f32 *)(e + 0x94) = 0.5f;
        *(f32 *)(e + 0x9C) = 3.5f;
        *(f32 *)(e + 0xA0) = 3.5f;
        *(IeM48 *)s5 = *(IeM48 *)((u8 *)D_main_bss_80138D18[arg0].unk4 + 0x28);
        computeAngleToTargetFromTransform(e + 0x28, e + 0x10, e + 0x1C);
        cur = D_main_bss_80138D18[arg0].unk4;
        if (*(u16 *)((u8 *)cur + 2) == 4) {
            releaseEffectObjectNpcSlotsVariant(arg0, 3, 1);
            return;
        }
        c2 = cur;
        if (c2 != e) {
            nw = D_main_bss_80138930[arg0][0];
            *(u16 *)(nw + 2) = 4;
            *(u8 **)(nw + 0xBC) = c2;
            *(u8 **)(nw + 0xC0) = e;
            *(s32 *)(nw + 0xC4) = 0;
            *(s32 *)(nw + 0xCC) = 0;
            *(s32 *)(nw + 0x74) = 0;
            *(u16 *)nw |= 1;
            ((IeObj *)nw)->c8 = 1.0f;
            if (D_main_bss_80138260 == 1) {
                D_main_bss_80138894->unk4 = nw;
                D_main_bss_80138D18[arg0].unk4 = nw;
            } else {
                D_main_bss_80138D18[arg0].unk4 = nw;
            }
            *(IeM48 *)(nw + 0x28) = *(IeM48 *)((u8 *)c2 + 0x28);
            *(IeV3 *)(nw + 0x10) = *(IeV3 *)((u8 *)c2 + 0x10);
            *(IeV3 *)(nw + 0x1C) = *(IeV3 *)((u8 *)c2 + 0x1C);
            *(u16 *)c2 |= 1;
            *(u16 *)e |= 1;
            *(IeM48 *)(e + 0x28) = *(IeM48 *)((u8 *)c2 + 0x28);
            *(f32 *)(e + 0x10) = *(f32 *)(e + 0x4C);
            *(f32 *)(e + 0x14) = *(f32 *)(e + 0x50);
            *(f32 *)(e + 0x18) = *(f32 *)(e + 0x54);
            *(f32 *)(e + 0x98) = *(f32 *)(e + 0xA0);
            *(f32 *)(e + 0x9C) = *(f32 *)(e + 0xA0);
            D_main_bss_80138D18[arg0].unk4 = nw;
            updateAudioListenerPosFromPlayer();
        }
    }
}

typedef struct { s32 w[62]; } SeBlob;
typedef struct { s32 a, b, c; } SeV3;
extern u8 D_main_8009EBBC;
extern u16 seWatch __asm__("D_main_8009EBC4");
f32 fabsf(f32);

void seImpl(s32 idx, u8 *o) __asm__("spawnEffectObjectAtNpc");
void seImpl(s32 idx, u8 *o) {
    f32 v[3];
    f32 k;
    f32 c64;
    f32 half;
    u8 *ctx;
    f32 t0;

    if ((*(u16 *)D_main_bss_80138D18[idx].unk4 & 0x10) && *(s32 *)((u8 *)D_main_bss_80138D18[idx].unk4 + 8) != 3) {
        D_main_8009EBBC = 0;
        return;
    }
    *(SeBlob *)o = *(SeBlob *)D_main_bss_80138D18[idx].unk4;
    *(u16 *)((u8 *)D_main_bss_80138D18[idx].unk4 + 0xF4) = 0xFFFF;
    *(s32 *)(o + 8) = 2;
    *(u16 *)(o + 2) = 2;
    *(u16 *)(o + 4) = 0;
    *(f32 *)(o + 0xEC) = 7.0f;
    *(s32 *)(o + 0x98) = 0;
    *(s32 *)(o + 0x9C) = 0;
    c64 = 64.0f;
    k = 0.015625f;
    FABSF(t0, ((f32)(rand() & 0x7F) - c64) * k);
    half = 0.5f;
    if (t0 > half) {
        f32 t = fabsf(((f32)(rand() & 0x7F) - c64) * k);
        k = 37.5f;
        if (t > half) {
            k = -37.5f;
        }
        v[0] = k;
        v[1] = -100.0f;
        v[2] = 150.0f;
        *(s32 *)(o + 0x78) = 0;
        *(s32 *)(o + 0x7C) = 0;
        *(s32 *)(o + 0x80) = 0;
    } else {
        f32 t = fabsf(((f32)(rand() & 0x7F) - c64) * k);
        k = 50.0f;
        if (t > half) {
            k = -50.0f;
        }
        v[0] = k;
        *(s32 *)&v[1] = 0;
        v[2] = 112.5f;
        *(s32 *)(o + 0x78) = 0;
        *(f32 *)(o + 0x7C) = -12.5f;
        *(f32 *)(o + 0x80) = 50.0f;
    }
    if (seWatch != 0xFFFF) {
        ctx = getNpcContextByIndex(seWatch);
        if (*(s32 *)(ctx + 0xC) != 0) {
            u8 *m = (u8 *)*(s32 *)(ctx + 0xC) + 0x28;
            *(u16 *)o = 0x33;
            *(u8 **)(o + 0x74) = m;
            transformVec3ByMat34(m, v, (f32 *)(o + 0x10));
            *(SeV3 *)(o + 0x84) = *(SeV3 *)(o + 0x78);
            *(s32 *)(o + 0x70) = 0;
            *(s32 *)(o + 0x90) = 0;
            *(f32 *)(o + 0x4C) = *(f32 *)(o + 0x10);
            *(f32 *)(o + 0x50) = *(f32 *)(o + 0x14);
            *(f32 *)(o + 0x54) = *(f32 *)(o + 0x18);
            applyPlayerVehicleStateUpdate(o);
        }
    }
}

typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u8 p6[2];
    s32 f8;
    s32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    s32 f1C;
    s32 f20;
    s32 f24;
    u8 p28[0x4C - 0x28];
    f32 f4C;
    f32 f50;
    f32 f54;
    f32 f58;
    f32 f5C;
    f32 f60;
    s32 f64;
    s32 f68;
    s32 f6C;
    void *f70;
    void *f74;
    f32 f78;
    f32 f7C;
    f32 f80;
    f32 f84;
    f32 f88;
    f32 f8C;
    s32 f90;
    s32 f94;
    s32 f98;
    s32 f9C;
    s32 fA0;
    f32 fA4;
    s32 fA8;
    f32 fAC;
    f32 fB0;
    s32 fB4;
    f32 fB8;
    void *fBC;
    void *fC0;
    s32 fC4;
    f32 fC8;
    s32 fCC;
    s32 fD0;
    f32 fD4;
    s32 fD8;
    s32 fDC;
    s32 fE0;
    f32 fE4;
    f32 fE8;
    f32 fEC;
    s32 fF0;
    u16 fF4;
    u8 pF6[2];
} EffObj;
extern u8 D_main_bss_80138458[];
extern u8 D_main_8009EC14[];
extern u8 D_main_8009EBBC;
extern u8 D_main_bss_80138B20[];
extern s32 D_8010CA20;
void resetHudInstancesAndUnbindNpcs(void);
void *getLevelDatItemByName(char *);
typedef struct { s32 a, b, c; } V3i;
void buildTransformMatrixFromEulerAngles(void *, f32, f32, f32);
u8 *getNpcContextByIndex(u16);
s16 ffnskA(s32, u16) __asm__("findFreeNpcSlotByKey");
void spawnEffectObjectAtNpc(s32, void *);
void releaseEffectObjectNpcSlotsVariant(s32, s32, u8);
extern s16 D_main_8009EBC4;
void updateAudioListenerPosFromPlayer(void);

void initEffectObjectFromLevelData(s32 arg0, s32 arg1)
{
  EffObj *o;
  u8 *item;
  u8 *name;
  u8 *it2;
  u16 idx;
  u8 *ctx;
  s32 v;
  s32 sp10[3];
  resetHudInstancesAndUnbindNpcs();
  if (D_8010CA20 == 0 || D_8010CA20 == 7)
  {
    o = (EffObj *)(D_main_bss_80138B20 + arg0 * 0x3E0);
    if (*(u16 *)D_main_bss_80138D18[arg0].unk4 & 0x20)
    {
      D_main_8009EBBC = 0;
    }
    o->f2 = 0;
    o->f4 = 0;
    o->f0 = 0;
    clearVec4QuadStruct((void *)((u8 *)o + 0x28));
    o->f70 = D_main_8009EC14;
    o->f74 = D_main_8009EC14;
    o->fBC = D_main_bss_80138268;
    o->fC0 = D_main_bss_80138268;
    o->f58 = 0;
    o->f5C = 0;
    o->f60 = 0;
    o->f64 = 0;
    o->f68 = 0;
    o->f6C = 0;
    o->f78 = 0;
    o->f7C = 0;
    o->f80 = 0;
    o->f84 = 0;
    o->f88 = 0;
    o->f8C = 0;
    o->f10 = 0.0f;
    o->f14 = 0.0f;
    o->f18 = 0.0f;
    o->f1C = 0;
    o->f20 = 0;
    o->f24 = 0;
    o->f90 = 0;
    o->f94 = 0;
    o->f98 = 0;
    o->f9C = 0;
    o->fA0 = 0;
    o->fC4 = 0;
    o->fCC = 0;
    o->fD0 = 0;
    o->fD8 = 0;
    o->fE0 = 0;
    o->fC8 = 1.0f;
    o->fDC = 0;
    o->fD4 = 80.0f;
    o->fE4 = -45.0f;
    o->fE8 = 45.0f;
    o->fA4 = 0.033333335f;
    o->fA8 = 0;
    o->fAC = 0.075f;
    o->fB0 = 10.0f;
    o->fEC = 0;
    o->fF4 = 0xFFFF;
    o->fF0 = 0;
    o->fB4 = 0;
    o->f0 = 0x33;
    o->fB8 = 0.3515625f;
    if (D_main_8009EBBC == 0)
    {
      item = getLevelDatItemByName((char *)arg1);
      *(V3i *)&o->f10 = *(V3i *)(item + 0x10);
      buildTransformMatrixFromEulerAngles((u8 *)o + 0x28, 0.0f, 0.0f, 0.0f);
      composeRotationMatrixSlot0((u8 *)o + 0x28, *(f32 *)(item + 0x1C));
      composeRotationMatrixSlot1((u8 *)o + 0x28, *(f32 *)(item + 0x20));
      composeRotationMatrixSlot2((u8 *)o + 0x28, *(f32 *)(item + 0x24));
      o->f4C = o->f10;
      o->f50 = o->f14;
      o->f54 = o->f18;
      computeAngleToTargetFromTransform((u8 *)o + 0x28, sp10, (u8 *)o + 0x1C);
      applyPlayerVehicleStateUpdate(o);
      o->fEC = *(f32 *)(item + 0x60);
      name = (u8 *)(*(s32 *)(item + 0x64) + (s32)item);
      if (*name != 0x2D)
      {
        it2 = getLevelDatItemByName((char *)name);
        if (it2 != NULL)
        {
          idx = *(u16 *)(it2 + 6);
          if (idx != 0xFFFF)
          {
            v = *(s32 *)(getNpcContextByIndex(idx) + 0xC);
            if (v != 0)
            {
              o->f74 = (void *)(v + 0x28);
              o->f58 = 0.0f;
              o->f5C = 0.0f;
              o->f60 = 0.0f;
              o->f78 = 0.0f;
              o->f7C = 0.0f;
              o->f80 = 0.0f;
              o->f84 = 0.0f;
              o->f88 = 0.0f;
              o->f8C = 0.0f;
              o->f2 = 2;
              o->f4 = 0;
              o->fF4 = ffnskA(0xFFFF, idx);
            }
          }
        }
      }
    }
    else
    {
      spawnEffectObjectAtNpc(arg0, o);
    }
    releaseEffectObjectNpcSlotsVariant(arg0, 2, 0);
    o->fF0 = arg1;
  }
}

extern u8 D_main_bss_80137DBC[][0x2A0];
extern void *getLevelDatItemByName(char *);
extern s32 D_8010C9E0;
extern s32 D_main_8009EC10;
void destroyNpcSlotChain(u16);
extern void despawnCraftAnimationSlotNpcs(s32);
extern void loadPlayerStartPosition(void *, s32);
typedef struct { u8 pad[4]; f32 x, y, z; } DePl;
typedef struct { u16 kind; u8 pad[0xE]; f32 x, y, z; } DeIt;
void destroyEffectObjectAndAssets(s32 idx, char *name) {
    u8 *player = D_main_bss_80137DBC[idx];
    u8 *obj = D_main_bss_80138D18[idx].unk4;
    u8 *item;
    u8 *v;
    u8 *str;
    u16 kind;
    if (*(u16 *)(obj + 0xF4) != 0xFFFF) {
        destroyNpcSlotChain(*(u16 *)(obj + 0xF4));
        *(u16 *)(obj + 0xF4) = 0xFFFF;
    }
    if (name != 0) {
        item = getLevelDatItemByName(name);
        str = (u8 *)(*(s32 *)(item + 0x68) + (s32)item);
        if (*str != 0x2D && *str != 0) {
            { register DeIt *it asm("$3") = getLevelDatItemByName((char *)str);
            switch (it->kind) {
            case 2:
                ((DePl *)player)->x = it->x;
                ((DePl *)player)->y = it->y;
                D_8010C9E0 |= 0x80;
                ((DePl *)player)->z = it->z;
                return;
            case 1:
                despawnCraftAnimationSlotNpcs(0);
                loadPlayerStartPosition(player, 0);
                break;
            case 0x26:
                D_main_8009EC10 = (s32)str;
                D_8010C9E0 |= 0x40;
                return;
            } }
        }
    }
    D_8010C9E0 |= 0x80;
}

void destroyNpcSlotChain(u16);
void deactivateEffectObject(s32 idx) {
    u8 *obj;

    *(u16 *)D_main_bss_80138D18[idx].unk4 &= ~1;
    obj = D_main_bss_80138D18[idx].unk4;
    if (*(u16 *)(obj + 0xF4) != 0xFFFF) {
        destroyNpcSlotChain(*(u16 *)(obj + 0xF4));
        *(u16 *)(obj + 0xF4) = 0xFFFF;
    }
    updateEffectObjectTransformPieces(D_main_8009EB98[gPlayers[idx].inner.unk0B4], idx, (s32)((u8 *)&gPlayers[0].inner.posX + idx * sizeof(struct player_struct)), 0.046875f, gPlayers[idx].inner.unk178[0x14]);
}

extern s32 gCurrentLevel;
extern void setActiveRenderListPtr(void *);
extern void setRenderStateFlagByteOne(s32);
extern void setRenderStateFlagByteTwo(s32);
extern void setRenderStateFlagByteThree(s32);
extern void setupCameraMatrices(void *);
extern void initRenderStateArrays(void);
extern void getConfigFloatPair(f32 *, f32 *);

void refreshEffectObjectCamerasAndState(void) {
    RoBlob30 save;
    SceneNode *e;
    s32 i;
    s32 *camp;
    s32 cam;
    s32 s10;
    s32 s14;
    void *p;
    f32 a;
    f32 b;

    for (i = 0; i < 1; i++) {
        e = &D_main_bss_80138D18[i];
        if (e->unk0 == 0) {
            continue;
        }
        p = NULL;
        if (gCurrentLevel == 10) {
            goto done;
        }
        if (*(s32 *)((u8 *)e + 0x74) == 0) {
            if (gCurrentLevel != 7) {
                goto done;
            }
        } else {
            p = (u8 *)e + 0x74;
        }
        setActiveRenderListPtr(p);
        p = (void *)1;
    done:
        setRenderStateFlagByteOne((s32)p);
        camp = &e->unk8;
        cam = e->unk8;
        e->unk8 = e->unk64;
        s10 = e->unk10;
        s14 = e->unk14;
        e->unk10 = e->unk14 = 0;
        setupCameraMatrices(camp);
        initRenderStateArrays();
        setRenderStateFlagByteOne(0);
        e->unk8 = e->unk68;
        e->unk10 = e->unk14 = 0;
        setupCameraMatrices(camp);
        initRenderStateArrays();
        setRenderStateFlagByteOne(0);
        e->unk8 = cam;
        setupCameraMatrices(camp);
        e->unk8 = e->unk6C;
        if (e->unk8 != 0) {
            initRenderStateArrays();
            a = *(f32 *)((u8 *)e + 0x2C);
            b = *(f32 *)((u8 *)e + 0x30);
            getConfigFloatPair((f32 *)((u8 *)e + 0x2C), (f32 *)((u8 *)e + 0x30));
            setRenderStateFlagByteOne(1);
            setRenderStateFlagByteThree(0);
            setRenderStateFlagByteTwo(1);
            setActiveRenderListPtr(NULL);
            setupCameraMatrices(camp);
            setRenderStateFlagByteThree(1);
            setRenderStateFlagByteOne(0);
            *(f32 *)((u8 *)e + 0x2C) = a;
            *(f32 *)((u8 *)e + 0x30) = b;
        }
        initRenderStateArrays();
        e->unk10 = s10;
        e->unk14 = s14;
        e->unk8 = e->unk70;
        save = *(RoBlob30 *)((u8 *)e + 0x34);
        clearVec4QuadStruct((void *)((u8 *)e + 0x34));
        setupCameraMatrices(&e->unk8);
        *(RoBlob30 *)((u8 *)e + 0x34) = save;
    }
}

void dispatchEffectObjectBehavior(s32 idx, s32 kind, s32 arg2) {
    updateEffectObjectTransformPieces(D_main_8009EB98[kind], idx, arg2, 0.046875f, gPlayers[idx].inner.unk178[0x14]);
}

static inline void registerSceneNodeInline(u8 *obj, u8 *node) {
    if (D_main_bss_80138260 == 1) {
        D_main_bss_80138894->unk4 = node;
    } else {
        D_main_bss_80138D18[*(s32 *)(node + 0xC)].unk4 = node;
    }
    mat3x3InverseInto(obj + 0x2C, node + 0x28);
}

void registerSceneNodeAndInvertRotation(u8 *obj, u8 *node) {
    registerSceneNodeInline(obj, node);
}

void buildOrientationFromPosAndAngles(void *, void *, void *);
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} TransformNodeVec3;
void initTransformNodeFromVectors(u8 *node, TransformNodeVec3 *a, TransformNodeVec3 *b) {
    buildOrientationFromPosAndAngles(node + 0x28, a, b);
    *(TransformNodeVec3 *)(node + 0x10) = *a;
    *(TransformNodeVec3 *)(node + 0x1C) = *b;
}

// The argument types for `arg0` and `arg1` are almost certainly wrong, but function isn't called anywhere so who cares
void computeAimAnglesFromObjectPositions(Mat4x3 arg0, Mat4x3 arg1, Vec3f arg2, f32 arg3) {
    Vec3f sp10;
    f32 temp_fa0;
    f32 temp_ft1;
    f32 temp_fv0;

    sp10[0] = arg1[3][0] - arg0[3][0];
    sp10[1] = arg1[3][1] - arg0[3][1];
    sp10[2] = arg1[3][2] - arg0[3][2];
    temp_ft1 = vec3Length(sp10);
    arg2[2] = arg3;
    if (temp_ft1 > 0.0001f) {
        temp_fv0 = 1.0f / temp_ft1;
        sp10[0] = temp_fv0 * sp10[0];
        sp10[1] = temp_fv0 * sp10[1];
        sp10[2] = temp_fv0 * sp10[2];
        arg2[1] = RADIAN_TO_DEGREE_F(sinfApprox(sp10[1]));
        arg2[0] = RADIAN_TO_DEGREE_F(atan2Approx(-sp10[0], sp10[2]));
    }
}

typedef struct SNode2 {
    u16 flags;
    u16 type;
    void *p4;
    u8 pad8[8];
    struct { s32 w[3]; } wa;
    struct { s32 w[3]; } wb;
    union {
        Blob30 blk;
        struct { u8 pad[0x24]; f32 f4C, f50, f54; } fl;
    } m28;
    u8 pad58[0x1C];
    void *unk74;
    u8 pad78[0x20];
    f32 f98, f9C, fA0;
    u8 padA4[0x18];
    struct SNode2 *pBC;
    struct SNode2 *pC0;
    s32 wC4;
    f32 fC8;
    f32 fCC;
    u8 padD0[0x3E0 - 0xD0];
} SNode2;
extern s32 D_main_bss_80138260;
extern void updateAudioListenerPosFromPlayer(void);

void setupSceneNodeTransitionBetweenNodes(s32 idx, SNode2 *a, SNode2 *b, s32 arg3, f32 arg4, f32 arg5) {
    SNode2 *t;
    if (a != b) {
        t = &((SNode2 *)D_main_bss_80138930)[idx];
        t->type = 4;
        t->pBC = a;
        t->pC0 = b;
        t->wC4 = 0;
        t->fC8 = arg4;
        t->flags |= 1;
        t->fCC = arg5;
        t->unk74 = (void *)arg3;
        if (D_main_bss_80138260 == 1) {
            D_main_bss_80138894->unk4 = t;
            D_main_bss_80138D18[idx].unk4 = t;
        } else {
            D_main_bss_80138D18[idx].unk4 = t;
        }
        t->m28.blk = a->m28.blk;
        t->wa = a->wa;
        t->wb = a->wb;
        a->flags |= 1;
        b->flags |= 1;
        b->m28.blk = a->m28.blk;
        ((f32 *)&b->wa)[0] = b->m28.fl.f4C;
        ((f32 *)&b->wa)[1] = b->m28.fl.f50;
        ((f32 *)&b->wa)[2] = b->m28.fl.f54;
        b->f98 = b->fA0;
        b->f9C = b->fA0;
        D_main_bss_80138D18[idx].unk4 = t;
        updateAudioListenerPosFromPlayer();
    }
}

extern s32 D_8010CA20;
extern u8 D_main_8009EBBC;
extern s32 D_main_8009EBC0;
extern s32 D_main_8009EC10;
extern s32 D_8010C9E0;
void requestCinematicNodeEvent(s32 idx) {
    u8 *p;

    if (D_8010CA20 == 0) {
        p = D_main_bss_80138D18[idx].unk4;
        if (!(*(u16 *)p & 0x10) || *(s32 *)(p + 8) == 3) {
            D_main_8009EBBC = 1;
            D_main_8009EC10 = D_main_8009EBC0;
            D_8010C9E0 |= 0x40;
        }
    }
}

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    s32 unk30;
    f32 unk34;
    u8 pad38[0x20];
} SceneNodeShakeState;
extern SceneNodeShakeState D_main_bss_80137D08[][2];
void resetSceneNodeShakeStateArray(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 1; i++) {
        for (j = 0; j < 2; j++) {
            SceneNodeShakeState *s = &D_main_bss_80137D08[i][j];

            s->unk0 = 0;
            s->unk4 = 0;
            s->unk8 = 0;
            s->unkC = 0;
            s->unk10 = 0;
            s->unk14 = 0;
            s->unk18 = 0;
            s->unk1C = 0;
            s->unk20 = 0;
            s->unk2C = 1.0f;
            s->unk28 = 1.0f;
            s->unk24 = 1.0f;
            s->unk30 = 0;
            s->unk34 = 1.0f;
        }
    }
}

void clearSceneNodeMotionFields(void) {
    s32 i;

    if (D_main_bss_80138260 == 1) {
        D_main_bss_80138894->unk8 = 0;
        D_main_bss_80138894->unk14 = 0;
        D_main_bss_80138894->unk10 = 0;
        D_main_bss_80138894->unk70 = 0;
        D_main_bss_80138894->unk6C = 0;
        D_main_bss_80138894->unk68 = 0;
        D_main_bss_80138894->unk64 = 0;
        return;
    }
    for (i = 0; i < 1; i++) {
        D_main_bss_80138D18[i].unk8 = 0;
        D_main_bss_80138D18[i].unk14 = 0;
        D_main_bss_80138D18[i].unk10 = 0;
        D_main_bss_80138D18[i].unk70 = 0;
        D_main_bss_80138D18[i].unk6C = 0;
        D_main_bss_80138D18[i].unk68 = 0;
        D_main_bss_80138D18[i].unk64 = 0;
    }
}

void destroyEffectObjectTypeNpcSlots(void);
void refreshAllSceneNodeInverseTransforms(void) {
    s32 i;

    destroyEffectObjectTypeNpcSlots();
    for (i = 0; i < 1; i++) {
        SceneNode *n = &D_main_bss_80138D18[i];

        if (n->unk0 != 0) {
            registerSceneNodeInline((u8 *)n + 8, n->unk4);
        }
    }
}

// The argument types for `arg0` and `arg1` are probably wrong, but this function is unused so who cares
void computeAimAnglesFromPoints(Vec3f arg0, Vec3f arg1, Vec3f arg2, f32 arg3) {
    Vec3f sp10;
    f32 temp_fv0; 
    f32 temp_fv0_2;
    f32 temp_fv0_3;

    sp10[0] = arg1[0] - arg0[0];
    sp10[1] = arg1[1] - arg0[1];
    sp10[2] = arg1[2] - arg0[2];
    temp_fv0 = vec3Length(sp10);
    if (temp_fv0 > 0.0001f) {
        temp_fv0_2 = 1.0f / temp_fv0;
        sp10[0] = temp_fv0_2 * sp10[0];
        sp10[1] = temp_fv0_2 * sp10[1];
        sp10[2] = temp_fv0_2 * sp10[2];
        temp_fv0_3 = RADIAN_TO_DEGREE_F(sinfApprox(sp10[1]));
        arg2[2] = arg3;
        arg2[1] = temp_fv0_3;
        arg2[0] = RADIAN_TO_DEGREE_F(atan2Approx(-sp10[0], sp10[2]));
    }
}

const s32 rodata_pad_4D900[] = {
    0x000F1880,
    0x00431021,
    0x02A2102B,
};

INCLUDE_ASM("asm/nonmatchings/main/4D900", fake_func_800538AC);
