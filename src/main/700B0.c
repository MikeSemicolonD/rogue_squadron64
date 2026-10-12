#include "common.h"
#include "common_types.h"

#include "main/04030.h"
#include "main/3F160.h"
#include "main/700B0.h"

typedef struct DebrisSpawnArgs {
    u8 pad00[0x10];
    f32 f10, f14, f18;
    u8 pad1C[0x38 - 0x1C];
    f32 f38;
    s16 h3C, h3E;
    f32 f40;
    u8 pad44[0x4C - 0x44];
    f32 f4C;
    u8 pad50[0x54 - 0x50];
    f32 f54, f58;
    u8 pad5C[0x64 - 0x5C];
    void *p64;
    s32 i68;
    s8 b6C, b6D;
    s16 h6E, h70, h72;
    s32 pad74;
    s32 i74;
    u16 h78;
} DebrisSpawnArgs;
extern s32 D_main_bss_80130C04;
extern u8 D_main_bss_80139870[];
extern void initNpcContextFromTransform(void *, s32, s32);
extern s32 spawnRandomBurstNpcVariantWrapper(void *);
extern void assignNpcTargetAndPosition(s32, s32, void *, f32);

s32 spawnDestructionDebris(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    DebrisSpawnArgs s;
    f32 vec[3];
    s32 r;

    initNpcContextFromTransform(&s, arg1, 0);
    s.p64 = D_main_bss_80139870;
    s.b6C = 0xB;
    s.h6E = 0x1E00;
    s.b6D = 0x10;
    s.i68 = D_main_bss_80130C04 + 0x40;
    s.h78 |= 0x18;
    if (arg2 < 0.0f) {
        s.b6C = 0x14;
        arg2 = -arg2;
        s.h6E = 0;
        s.i68 = 0;
        s.b6D = 0;
        s.h78 &= 0xFFEF;
    }
    s.h70 = (u32)(arg4 * 0.125f * 256.0f);
    s.h72 = (u32)(arg4 / 6.0f * 256.0f);
    s.h3C = 0;
    s.h3E = 0;
    s.f40 = arg3;
    s.f4C = arg2;
    s.f58 = 1.0f;
    s.f38 = s.f14 = s.f10 = s.f18 = 0.0f;
    s.f54 = 0.8f;
    s.i74 |= 0x09000000;
    r = spawnRandomBurstNpcVariantWrapper(&s);
    if ((u16)arg0 != 0xFFFF) {
        vec[1] = vec[2] = vec[0] = 0.0f;
        assignNpcTargetAndPosition((u16)r, (u16)arg0, vec, 0.0f);
    }
    return (u16)r;
}

typedef struct {
    f32 x, y, z;
} DbV3;

typedef struct {
    f32 x, y, z;
    DbV3 fwd;
    DbV3 up;
    DbV3 vel;
    u8 *mesh;
    f32 axis[3];
    f32 spin;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    f32 f54;
    f32 f58;
    u16 h5C;
} DbObj;

typedef struct {
    DbV3 *pos;
    DbV3 *vel;
    f32 f8;
    f32 fC;
    f32 f10;
} DbArgs;

extern u16 D_main_bss_80139574;
extern u8 D_main_bss_80138058[];
f32 dbNormalize(void *) __asm__("normalize_vector");
f32 dbWrap(f32, f32, void *, void *) __asm__("wrapAngleToCyclicRange");
s32 dbBlocked(f32, f32, void *) __asm__("isTerrainCellBlockedAtWorldXz");
f32 dbNormInto(void *, void *) __asm__("vec3NormalizeInto");
void dbTod(void *, void *, s32, s32) __asm__("triggerObjectDestructionEffects");
void dbQuat(f32 *, void *, f32) __asm__("quatFromAxisAngle");
void dbRot(f32 *, void *, void *) __asm__("rotateVec3ByQuat");
void dbOrtho(void *) __asm__("orthonormalizeFrame");
void dbM34(void *, void *, f32) __asm__("mat34CrossRowsAndCopyPos");
void dbVis(s32, void *, void *, f32) __asm__("addNpcToVisibilityBucket");
void *dbWalk(char *) __asm__("walkMeshdef0List");
void dbRelease(void *) __asm__("releaseMeshAsset");
void dbPop(u16, void *) __asm__("popNpcSlotFromTail");
void dbDestroy(u16) __asm__("destroyNpcSlotByIndex");
s32 dbRand(void) __asm__("rand");

s32 dbImpl(u8 *npc, u16 action, void *arg) __asm__("npcDebris1Update");
s32 dbImpl(u8 *npc, u16 action, void *arg) {
    DbObj *d;
    DbV3 v18;
    f32 buf[10];
    f32 q[4];

    d = *(DbObj **)(npc + 4);
    switch (action) {
    case 1: {
        DbArgs *a = arg;
        f32 zero;
        *(DbV3 *)d = *a->pos;
        d->vel = *a->vel;
        d->fwd = d->vel;
        d->fwd.z = 0.0f;
        if (d->fwd.x == d->fwd.z) {
            d->fwd.x = 0.0f;
            d->fwd.y = 0.0f;
            d->fwd.z = 1.0f;
            d->spin = 360.0f;
        } else {
            d->spin = dbNormalize(&d->fwd) * 360.0f;
        }
        d->up.x = 0.0f;
        d->up.z = 0.0f;
        d->up.y = 1.0f;
        *(DbObj **)(npc + 8) = d;
        d->axis[1] = 0.0f;
        d->axis[0] = -d->vel.z;
        d->axis[2] = d->vel.x;
        if (d->axis[0] == 0.0f && d->axis[2] == 0.0f) {
            d->axis[0] = 1.0f;
        }
        dbNormalize(d->axis);
        d->f50 = 0.0f;
        d->f44 = 0.0f;
        d->f4C = 4.0f;
        d->f48 = 0.5f;
        d->f54 = 2.0f;
        d->f58 = a->f10 * 0.05f;
        zero = 0.0f;
        if (d->f58 < zero || !(dbRand() & 3)) {
            if (d->f58 < zero) {
                a->f10 = -a->f10;
            }
            d->f4C = zero;
            d->mesh = NULL;
            d->f50 = 0.8f;
            d->f54 = d->f54 * 0.5f;
        } else {
            d->mesh = dbWalk("debris1");
        }
        dbPop(D_main_bss_80139574, npc);
        d->h5C = spawnDestructionDebris(*(u16 *)(npc + 0x16), *(s32 *)(npc + 8), d->mesh == NULL ? -a->f8 : a->f8, a->fC, a->f10);
        break;
    }
    case 2:
        if (d->mesh != NULL) {
            dbRelease(d->mesh);
        }
        return 1;
    case 3: {
        f32 dt = *(f32 *)arg;
        f32 zero;
        f32 kk;
        f32 dot;
        f32 dd;
        f32 a54;
        f32 a44;
        f32 a;

        if (d->f54 >= 0.0f) {
            d->f54 -= dt;
            if (d->f54 < 0.0f) {
                dbDestroy(*(u16 *)(npc + 0x16));
                return 1;
            }
        }
        d->f44 += dt;
        if (dbWrap(d->x, d->z, D_main_bss_80138058, buf) < d->y) {
            if (dbBlocked(d->x, d->z, NULL) == 1) {
                dbTod(d, &d->fwd, 0xFFFF, 0);
                d->f54 = 0.0f;
                break;
            }
            kk = dbNormInto(&v18, &d->vel);
            dot = v18.x * buf[3] + v18.y * buf[4] + v18.z * buf[5];
            dd = dot + dot;
            zero = 0.0f;
            if (zero < dd) {
                if (d->f44 < 0.25f) {
                    if (d->vel.x * d->vel.x + d->vel.z * d->vel.z < 0.040000003f) {
                        kk = zero;
                    }
                }
                kk *= d->f48;
                d->f44 = 0.0f;
                if (kk < 0.01f) {
                    d->vel.x = d->vel.y = d->vel.z = d->f44;
                } else {
                    a54 = d->f54;
                    a44 = d->f44;
                    if (a54 < a44) {
                        a = a54 + 1.0f;
                        d->f54 = a;
                        if (a44 <= a) {
                            d->f54 = a44;
                            break;
                        }
                    }
                    d->vel.x = (v18.x - dd * buf[3]) * kk;
                    d->vel.y = (v18.y - dd * buf[4]) * kk;
                    d->vel.z = (v18.z - dd * buf[5]) * kk;
                }
            }
        }
        d->x += d->vel.x * dt;
        d->y += d->vel.y * dt;
        d->z += d->vel.z * dt;
        d->vel.y += d->f4C * dt;
        d->vel.x -= d->vel.x * d->f50 * dt;
        d->vel.y -= d->vel.y * d->f50 * dt;
        d->vel.z -= d->vel.z * d->f50 * dt;
        dbQuat(q, d->axis, d->spin * dt);
        v18 = d->fwd;
        dbRot(q, &v18, &d->fwd);
        v18 = d->up;
        dbRot(q, &v18, &d->up);
        dbOrtho(d);
        return 1;
    }
    case 4:
        if (d->mesh != NULL) {
            dbM34(d->mesh + 0x28, d, d->f58);
            dbVis(*(s32 *)arg, d->mesh, d, 1.0f);
        }
        break;
    }
    return 1;
}

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strShockSph);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strShockBig);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strShockSml);

typedef struct { s32 a, b, c, d; } OriChunk;
typedef struct { u8 r, g, b, a; } OriRgba;
typedef struct {
    u8 *mesh;
    f32 mtx[12];
    OriRgba col;
    s32 flags;
    f32 f3C, f40, f44, f48, f4C, f50;
} OriNpc;
typedef struct { f32 *mat; OriRgba *color; s32 kind; f32 f0C, f10, f14; } OriSpawn;
extern u32 D_main_800A0A90[];
extern u16 D_main_bss_80139574;

extern u16 D_main_bss_80139900[];
extern u16 oriTblA[] __asm__("D_main_bss_80139870");
extern u8 *instantiateNamedMeshInstance(u32);
extern void releaseMeshAsset(void *);
extern void applyRgbaTintToMeshVertices(void *, void *);
extern void setMaterialFlagByIdInMeshTree(void *, s32, u16);
extern void mat34CrossRowsAndCopyPosPtr(void *, void *, f32 *);
extern void buildRotationMatrixSlot1(void *, f32);
extern void mat3x4Multiply(void *, void *, void *);
extern void addNpcToVisibilityBucket(void *, void *, void *, f32);
extern f32 sinf(f32);

#define SP ((OriSpawn *)arg2)
s32 orientedNpcHandler(struct D_80130BB8_type *self, u16 arg1, void *arg2) {
    OriNpc *s = (OriNpc *)self->unk04;
    f32 vec[3];
    f32 rot[12];
    f32 dt;
    f32 a;
    f32 b;
    f32 r;
    f32 w;
    f32 al;
    s32 k;
    u16 *tbl;
    void **ctx;

    switch (arg1) {
    case 1:
        {
            OriChunk *dst = (OriChunk *)s->mtx;
            OriChunk *src = (OriChunk *)SP->mat;
            OriChunk *end = src + 3;
            do {
                *dst = *src;
                src++;
                dst++;
            } while (src != end);
        }
        self->unk08 = (void *)s->mtx;
        k = SP->kind;
        s->flags = k;
        s->mesh = instantiateNamedMeshInstance(D_main_800A0A90[k & 0xFF]);
        *(u32 *)(s->mesh + 0x64) = (*(u32 *)(s->mesh + 0x64) & 0xF03FFFFF) | 0x09000000;
        s->f3C = SP->f0C;
        s->f40 = SP->f10 - SP->f0C;
        s->f44 = 1.0f;
        s->f4C = 640.0f;
        s->f50 = 0.0f;
        s->f48 = 1.0f / SP->f14;
        if (SP->color == NULL) {
            s->col.r = 0xFF;
            s->col.g = 0xFF;
            s->col.b = 0xFF;
        } else {
            s->col = *SP->color;
        }
        popNpcSlotFromTail(D_main_bss_80139574, self);
        return 1;
    case 2:
        releaseMeshAsset(s->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        s->f44 = s->f44 - dt * s->f48;
        if (s->f44 <= 0.0f) {
            destroyNpcSlotByIndex(self->unk16);
            return 1;
        }
        s->f50 += s->f4C * dt;
        break;
    case 4:
        ctx = (void **)arg2;
        s->col.a = (u32)(s->f44 * 255.0f);
        applyRgbaTintToMeshVertices(s->mesh, &s->col);
        if ((u8)s->flags == 2) {
            al = s->f44; w = 1.0f; w -= al; w *= 20.0f;
            setMaterialFlagByIdInMeshTree(s->mesh + 0x58, 0xFFFF, oriTblA[(s32)w]);
        } else if ((u8)s->flags == 3) {
            al = s->f44; w = 1.0f; w -= al; w *= 6.0f;
            setMaterialFlagByIdInMeshTree(s->mesh + 0x58, 0xFFFF, D_main_bss_80139900[(s32)w]);
        }
        if (!(s->flags & 0x8000)) {
            r = s->f3C + sinf((1.0f - s->f44) * 3.1415927f * 0.5f) * s->f40;
        } else if (s->f44 > 0.5f) {
            r = s->f3C + sinf((1.0f - s->f44) * 3.1415927f) * s->f40;
        } else {
            r = sinf((1.0f - s->f44) * 3.1415927f) * (s->f3C + s->f40);
        }
        vec[0] = s->mtx[9] * r;
        vec[1] = s->mtx[10] * r;
        vec[2] = s->mtx[11] * r;
        mat34CrossRowsAndCopyPosPtr(s->mesh + 0x28, s->mtx, vec);
        buildRotationMatrixSlot1(rot, s->f50);
        mat3x4Multiply(s->mesh + 0x28, rot, s->mesh + 0x28);
        addNpcToVisibilityBucket(*ctx, s->mesh, s->mtx, r + r);
        break;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/700B0", multiEventTemplateNpcHandler);

typedef struct { u8 c[4]; } WdCol;
typedef struct WdNode {
    u8 type;
    u8 b1;
    s16 h2;
    u8 b4;
    u8 b5;
    u8 b6;
    u8 pad7;
    struct WdNode *children;
    u8 padC[0xC];
    s16 h18;
    u16 h1A;
    u8 pad1C[8];
    f32 f24;
    f32 f28;
    f32 f2C;
    s16 h30;
    s16 h32;
    WdCol c34;
} WdNode;
extern WdCol wdCols[] __asm__("D_main_800A0B38");
extern f32 wdScales[] __asm__("D_main_800A0B84");
extern s32 D_main_bss_80130B50;
extern u8 *wdGs __asm__("D_main_bss_80130C08");
s32 findNameTreeEntryIndexByName(void *, char *, s32 *);
void *wdMalloc(s32, s32) __asm__("rs_malloc");

s32 wdImpl(WdNode *n, void *tree, char *name, s32 flags, s32 sub, s32 k) __asm__("walkDatTreeAndAllocSubtypeBuffers");
s32 wdImpl(WdNode *n, void *tree, char *name, s32 flags, s32 sub, s32 k) {
    s32 idx;
    s32 cnt;
    f32 f;

    cnt = findNameTreeEntryIndexByName(tree, name, &idx);
    if (cnt > 0) {
        if ((cnt >= 2 || (flags & 0x80)) && sub < 0) {
            if (n->type == 0xFF) {
                n->type = 0x80;
                n->b4 = 0;
                n->children = wdMalloc(0x2A0, 0);
            }
            for (idx = 0; n->b4 < 12; n->b4++) {
                if (idx >= cnt) {
                    break;
                }
                n->children[n->b4].type = 0xFF;
                wdImpl(&n->children[n->b4], tree, name, flags & ~0x80, idx, k);
                idx++;
            }
            return 1;
        }
        if (n->type != 0xFF && (n->type & 0x80)) {
            if (n->b4 >= 12) {
                return 0;
            }
            n->b4++;
            n = &n->children[n->b4 - 1];
        }
        n->type = flags;
        n->b1 = 0;
        n->b4 = idx;
        n->h2 = k;
        if (sub >= 0) {
            n->b5 = sub;
        } else {
            n->b5 = 0;
        }
        n->h18 = 0x301;
        n->b6 = 0;
        n->h32 = 0;
        n->h30 = 0;
        n->f24 = 45.0f;
        f = wdScales[flags & 0x1F];
        if (f <= 0.5f) {
            n->f28 = n->f2C = f * ((D_main_bss_80130B50 & 1) ? 1.1f : 1.3f);
        } else {
            n->f28 = n->f2C = f;
        }
        n->c34 = wdCols[flags & 0x1F];
        n->h1A = *(u16 *)(wdGs + 0x24);
    } else {
        n->type = 0xFF;
    }
    return 0;
}

extern u16 rand(void);
typedef struct { u8 pad0[0x18]; u32 flags; } DatSubInfo;
typedef struct { u8 pad0[0x10]; DatSubInfo *info; } DatSubObj;
extern s32 walkDatTreeAndAllocSubtypeBuffers(void *, void *, char *, s32, s32, s32);

s32 dispatchDatSubtypeByRandomIndex(u8 *arg0, DatSubObj **arg1) {
    s32 ret;
    s32 r;

    ret = 0;
    r = rand() & 0x7FF;
    *arg0 = 0xFF;
    if ((*arg1)->info->flags & 0xFFFFF) {
        if ((*arg1)->info->flags & 0x1) {
            ret = walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 0, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x200) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 11, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x20) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 5, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x4000) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 15, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x2) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwb", 3, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x400) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwb", 12, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x4) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 129, -1, r) & 0xFF;
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwb", 129, -1, r) & 0xFF;
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwc", 129, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x8) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 4, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x10) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 6, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x40) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 7, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x80) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwb", 0, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x100) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 138, -1, r) & 0xFF;
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwb", 201, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x800) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 12, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x1000) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 13, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x2000) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 14, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x8000) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 80, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x10000) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwb", 2, -1, r) & 0xFF;
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 12, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x20000) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 17, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x40000) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwa", 18, -1, r) & 0xFF;
        }
        if ((*arg1)->info->flags & 0x80000) {
            ret |= walkDatTreeAndAllocSubtypeBuffers(arg0, arg1, "glwb", 18, -1, r) & 0xFF;
        }
        return ret > 0;
    }
    return 0;
}

typedef struct DatWalkNode {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    struct DatWalkNode *unk8;
    struct DatWalkNode *unkC;
    s16 h10, h12, h14;
    u8 pad16[0x24 - 0x16];
    f32 f24;
    u8 pad28[0x37 - 0x28];
    u8 b37;
} DatWalkNode;
typedef struct { f32 px, py, pz, dx, dy, dz; f32 pad[6]; } AttachPt;
typedef struct DatWalkLink { void *unk0; struct DatWalkLink *unk4; } DatWalkLink;
typedef struct { u8 pad0[0x18]; f32 f18, f1C, f20, f24, f28, f2C; u8 pad30[0x48 - 0x30]; struct { u8 pad[0x20]; DatWalkNode *head; } *p48; } DatWalkCtx;
extern u8 D_main_bss_8013A898;
extern u8 *D_main_bss_8013A89C;
extern AttachPt *D_main_bss_8013A8A0;
extern u8 D_main_800A0B38[][4];
extern f32 D_main_800A0BD0[];
f32 vec3NormalizeInto(f32 *, f32 *);
void computeNamedAttachPointTransform(void *, s32, s32, s32 *, void *, s32, s32);

void walkDatTreeAndVisitChildren(DatWalkNode *n, u8 *arg1, DatWalkCtx *ctx) {
    s32 i;
    AttachPt tmp;
    f32 dir[4];
    f32 d[3];
    AttachPt *p;
    f32 t;
    f32 k;
    s32 v;

    i = n->unk4;
    if (n->unk0 & 0x80) {
        i = 0;
        if (n->unk4 != 0) {
            do {
                walkDatTreeAndVisitChildren(&n->unk8[i], arg1, ctx);
                i++;
            } while (i < n->unk4);
        }
    } else {
        if (n->unk6 != 0) {
            p = &D_main_bss_8013A8A0[n->unk6];
        } else {
            if ((*(u16 *)(arg1 + 8) & 0x20) && D_main_bss_8013A898 != 0) {
                u8 c = D_main_bss_8013A898 - 1;
                D_main_bss_8013A898 = c;
                n->unk6 = D_main_bss_8013A89C[c];
                p = &D_main_bss_8013A8A0[n->unk6];
                computeNamedAttachPointTransform(arg1, 0, n->unk5, &i, p, 0, 0);
            } else {
                p = &tmp;
                computeNamedAttachPointTransform(arg1, 0, n->unk5, &i, p, 0, 0);
            }
        }
        d[0] = p->px - ctx->f18;
        d[1] = p->py - ctx->f1C;
        d[2] = p->pz - ctx->f20;
        vec3NormalizeInto(dir, d);
        t = -(p->dx * dir[0] + p->dy * dir[1] + p->dz * dir[2]);
        if (!(n->unk0 & 0x40)) {
            t += 0.6f;
        } else {
            t += 0.95f;
        }
        if (t < 0.0f) {
            t = 0.0f;
        } else if (t > 1.0f) {
            t = 1.0f;
        }
        switch (n->unk1) {
        case 0:
            break;
        case 1:
            t *= (f32)(0x100 - n->unk2) * 0.00390625f;
            break;
        case 2:
            t = 0.0f;
            break;
        case 3:
            t *= (f32)n->unk2 * 0.00390625f;
            break;
        }
        n->b37 = (f32)D_main_800A0B38[n->unk0 & 0x1F][3] * t;
        if (n->b37 >= 4) {
            t = dir[0] * ctx->f24 + dir[1] * ctx->f28 + dir[2] * ctx->f2C;
            n->f24 = t * 180.0f;
            k = D_main_800A0BD0[n->unk0 & 0x1F];
            n->h10 = (d[0] - dir[0] * k) * 256.0f;
            n->h12 = (d[1] - dir[1] * k) * 256.0f;
            n->h14 = (d[2] - dir[2] * k) * 256.0f;
            n->unk8 = ctx->p48->head;
            if (n->unk8 != NULL) {
                ((DatWalkLink *)n->unk8)->unk4 = (DatWalkLink *)((u8 *)n + 8);
            }
            n->unkC = 0;
            ctx->p48->head = (DatWalkNode *)((u8 *)n + 8);
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVYa4Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVYa2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strProbeDroid);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVCrsHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRTrPillar);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBThcapHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRBlkHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBTspHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBTrpHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRaptor);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRebTransport);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strWrldDvstr);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVHlsHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strWaveskimmer);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBPwrtranHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBMedHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBMe5Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strIRfcHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBGs2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBGs1Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strITrd2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm7Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm6Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm5newHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm4Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm3Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm1Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBTecHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strB20sbHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr8Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr7Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr6Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr5Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr4Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBLrsp);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strImpShuttle);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strILndHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strILtsrcHi);

typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    u8 padC[8];
    s16 h14;
    s16 h16;
    s16 h18;
    s16 h1A;
    s16 h1C;
    s16 h1E;
    s16 h20;
    s16 h22;
    u8 b[16];
} SfxEnt;

typedef struct {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
    void *p10;
    s32 w14;
    s32 w18;
    u8 v1C[0x30];
    s32 w4C;
    s32 w50;
    s32 w54;
    s32 w58;
    s32 w5C;
    s32 w60;
    s32 w64;
    s32 w68;
    void *p6C;
    s32 w70;
    s32 w74;
    u8 pad78[0x30];
    s32 wA8;
    s32 wAC;
    SfxEnt *pB0;
    s32 wB4;
    SfxEnt ent[7];
} SfxState;

typedef struct {
    char *name;
    s32 flags;
} SfxMesh;

extern SfxState D_main_8013A670;
extern SfxMesh D_main_800A0C1C[];
extern u8 *D_main_bss_80130C08;
extern s32 D_main_bss_8013A894;
extern u8 D_main_bss_8013A898;
extern u8 *D_main_bss_8013A89C;
extern u8 D_main_bss_80130B63;
extern s32 gCurrentLevel;
extern void load_hmt_and_hob(char *, s32, s32, s32);
extern void clearVec4QuadStruct(void *);
extern s32 clearStructPair2C30(void *);
extern u8 isHobObjectLoaded(char *);
extern void *lsMalloc(s32, s32) __asm__("rs_malloc");
extern void *lsAttach __asm__("D_main_bss_8013A8A0");

void loadSfxAsset(void) {
    SfxEnt *e;
    s32 i;
    s32 k;
    s32 hw;

    load_hmt_and_hob("gnrc_stuff/sfx", 0, 0, 0);
    D_main_8013A670.wC = 0;
    D_main_8013A670.w8 = 0;
    D_main_8013A670.w4 = 0;
    D_main_8013A670.w0 = 0;
    D_main_8013A670.p10 = &D_main_8013A670.w4C;
    D_main_8013A670.w14 = 0;
    clearVec4QuadStruct(D_main_8013A670.v1C);
    D_main_8013A670.w58 = 0x100000;
    D_main_8013A670.w50 = 0;
    D_main_8013A670.w4C = 0;
    D_main_8013A670.w54 = 0;
    D_main_8013A670.w68 = 0;
    D_main_8013A670.w5C = 0;
    D_main_8013A670.w60 = 0;
    D_main_8013A670.w64 = 0;
    D_main_8013A670.p6C = &D_main_8013A670.wA8;
    D_main_8013A670.w70 = 0;
    D_main_8013A670.w74 = 0;
    clearStructPair2C30(&D_main_8013A670.w4C);
    D_main_8013A670.wAC = 0;
    D_main_8013A670.wA8 = 0;
    D_main_8013A670.pB0 = D_main_8013A670.ent;
    D_main_8013A670.wB4 = 0;
    hw = *(u16 *)(D_main_bss_80130C08 + 0x22) << 16;
    for (e = D_main_8013A670.ent, i = 0; i < 7; e++, i++) {
        e->w0 = 0x9E;
        e->w4 = 0xD0C9005;
        e->w8 = hw;
        e->h14 = e->h20 = 0;
        e->h16 = e->h1A = ((7 - i) << 12) / 7;
        e->h1E = e->h22 = ((6 - i) << 12) / 7;
        e->h18 = e->h1C = 0x1000;
        e->b[0] = 0xFF;
        e->b[1] = 0xFF;
        e->b[2] = 0xFF;
        e->b[3] = 0xFF;
        e->b[4] = 0xFF;
        e->b[5] = 0xFF;
        e->b[6] = 0xFF;
        e->b[7] = 0xFF;
        e->b[8] = 0xFF;
        e->b[9] = 0xFF;
        e->b[10] = 0xFF;
        e->b[11] = 0xFF;
        e->b[12] = 0xFF;
        e->b[13] = 0xFF;
        e->b[14] = 0xFF;
        e->b[15] = 0xFF;
    }
    D_main_bss_8013A894 = 0;
    k = 0;
    if (D_main_800A0C1C[0].name != NULL) {
        do {
            if (isHobObjectLoaded(D_main_800A0C1C[k].name)) {
                u8 **m = dbWalk(D_main_800A0C1C[k].name);
                *(s32 *)(*(u8 **)(*m + 0x10) + 0x18) |= D_main_800A0C1C[k].flags;
                dbRelease(m);
            }
            k++;
        } while (D_main_800A0C1C[k].name != NULL);
    }
    if (D_main_bss_80130B63 != 0) {
        D_main_bss_8013A898 = 0xFF;
    } else {
        switch (gCurrentLevel) {
        case 0:
        case 4:
        case 9:
        case 10:
            D_main_bss_8013A898 = 0xAA;
            break;
        default:
            D_main_bss_8013A898 = 0;
            break;
        }
    }
    if (D_main_bss_8013A898 != 0) {
        D_main_bss_8013A89C = lsMalloc(D_main_bss_8013A898, 0);
        lsAttach = lsMalloc(D_main_bss_8013A898 * 48, 0);
        for (i = 0; i < D_main_bss_8013A898; i++) {
            D_main_bss_8013A89C[i] = i;
        }
    }
}

void buildRotationMatrixSlot0(f32 *, f32);
void composeRotationMatrixSlot0(f32 *, f32);
void composeRotationMatrixSlot1(f32 *, f32);

void composeRandomRotationMatrix(f32 *arg0, f32 *arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    f32 m[12];
    f32 v;
    f32 t;

    if (arg3 != 0) {
        v = (f32)((s16)rand() % arg3);
    } else {
        v = 0.0f;
    }
    buildRotationMatrixSlot0(m, v);
    composeRotationMatrixSlot1(m, (f32)(s16)rand());
    if (arg4 != 0) {
        composeRotationMatrixSlot0(m, (f32)arg4);
    }
    if (arg5 != 0) {
        composeRotationMatrixSlot1(m, (f32)arg5);
    }
    t = -m[1];
    arg1[0] = t;
    arg1[1] = -m[4];
    arg1[2] = -m[7];
    arg0[0] = arg1[0] * arg2;
    arg0[1] = arg1[1] * arg2;
    arg0[2] = arg1[2] * arg2;
}

void composeRandomRotationMatrixVariant(f32 *arg0, f32 *arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    f32 m[12];
    f32 v;
    f32 t;

    if (arg3 != 0) {
        v = (f32)(arg4 + (s16)rand() % arg3);
    } else {
        v = (f32)arg4;
    }
    buildRotationMatrixSlot0(m, v);
    composeRotationMatrixSlot1(m, (f32)(s16)rand());
    if (arg5 != 0) {
        composeRotationMatrixSlot0(m, (f32)arg5);
    }
    if (arg6 != 0) {
        composeRotationMatrixSlot1(m, (f32)arg6);
    }
    t = -m[1];
    arg1[0] = t;
    arg1[1] = -m[4];
    arg1[2] = -m[7];
    arg0[0] = arg1[0] * arg2;
    arg0[1] = arg1[1] * arg2;
    arg0[2] = arg1[2] * arg2;
}

void scaleVec3ByRandomRange(Vec3f arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;

    temp_fv0 = (((rand() % 4096) * (arg2 - arg1)) / 4095.0f) + arg1;
    arg0[0] *= temp_fv0;
    arg0[1] *= temp_fv0;
    arg0[2] *= temp_fv0;
}

extern u8 D_main_bss_80130B63;
s32 npcDebris1Update(struct D_80130BB8_type *self, u16 arg1, void *arg2);

typedef struct { s32 a; s32 b; f32 c; f32 d; f32 e; } Debris1Args;

void spawnDebris1Npc(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    Debris1Args args;

    if ((D_main_bss_80130B63 != 0) || (findLargestFreeHeapChunk() >= 0x3A98U)) {
        args.a = arg0;
        args.b = arg1;
        args.e = arg3;
        args.d = arg2;
        args.c = arg4;
        spawnNpcOfType(npcDebris1Update, &args, 1U, 0xFU);
    }
}

s32 orientedNpcHandler(struct D_80130BB8_type *self, u16 arg1, void *arg2);
typedef struct {
    s32 x;
    s32 y;
    s32 z;
} V3I;

typedef struct {
    f32 pos[3];
    f32 inv[3];
    f32 dir[3];
    f32 one[3];
} OrientedFrame;

typedef struct {
    OrientedFrame *frame;
    s32 a;
    s32 b;
    f32 c;
    f32 d;
    f32 e;
} OrientedSpawnArgs;

void orthonormalizeFrame(OrientedFrame *);

void spawnOrientedEffectIfBudgetOk(f32 *pos, f32 *dir, s32 arg2, f32 arg3, f32 arg4)
{
  OrientedFrame fr;
  OrientedSpawnArgs args;
  OrientedFrame *fp;
  float new_var;
  *((V3I *) fr.pos) = *((V3I *) pos);
  if (dir != 0)
  {
    *((V3I *) fr.dir) = *((V3I *) dir);
  }
  else
  {
    fr.dir[0] = 0.0f;
    fr.dir[2] = 0.0f;
    fr.dir[1] = 1.0f;
  }
  fr.inv[0] = 1.0f - fr.dir[0];
  (&fr)->inv[1] = 1.0f - fr.dir[1];
  fr.inv[2] = 1.0f - fr.dir[2];
  fr.one[2] = 1.0f;
  fr.one[1] = 1.0f;
  fr.one[0] = 1.0f;
  orthonormalizeFrame(&fr);
  fp = &fr;
  new_var = 0.0001f;
  if ((D_main_bss_80130B63 != 0) || ((findLargestFreeHeapChunk() >= 0x3A98U) && (countDisplayListChunks() >= 0x4E20)))
  {
    args.c = new_var;
    args.frame = fp;
    args.a = arg2;
    args.b = 0;
    args.d = arg3;
    args.e = arg4;
    spawnNpcOfType(orientedNpcHandler, &args, 1U, 0xFU);
  }
}


void spawnOrientedEffectIfBudgetOkAlt(f32 *pos, f32 *dir, s32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    OrientedFrame fr;
    OrientedSpawnArgs args;
    OrientedFrame *fp;

    *(V3I *)fr.pos = *(V3I *)pos;
    if (dir != NULL) {
        *(V3I *)fr.dir = *(V3I *)dir;
    } else {
        fr.dir[0] = 0.0f;
        fr.dir[2] = 0.0f;
        fr.dir[1] = 1.0f;
    }
    fr.inv[0] = 1.0f - fr.dir[0];
    fr.inv[1] = 1.0f - fr.dir[1];
    fr.inv[2] = 1.0f - fr.dir[2];
    fr.one[2] = 1.0f;
    fr.one[1] = 1.0f;
    fr.one[0] = 1.0f;
    orthonormalizeFrame(&fr);
    fp = &fr;
    if ((D_main_bss_80130B63 != 0) || ((findLargestFreeHeapChunk() >= 0x3A98U) && (countDisplayListChunks() >= 0x4E20))) {
        args.d = arg4;
        args.frame = fp;
        args.a = arg2;
        args.b = 0;
        args.c = arg3;
        args.e = arg5;
        spawnNpcOfType(orientedNpcHandler, &args, 1U, 0xFU);
    }
}

void spawnOrientedNpc(s32 arg0, f32 *pos, f32 *dir, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7) {
    OrientedFrame fr;
    OrientedSpawnArgs args;
    OrientedFrame *fp;

    *(V3I *)fr.pos = *(V3I *)pos;
    if (dir != NULL) {
        *(V3I *)fr.dir = *(V3I *)dir;
    } else {
        fr.dir[0] = 0.0f;
        fr.dir[2] = 0.0f;
        fr.dir[1] = 1.0f;
    }
    fr.inv[0] = 1.0f - fr.dir[0];
    fr.inv[1] = 1.0f - fr.dir[1];
    fr.inv[2] = 1.0f - fr.dir[2];
    fr.one[1] = arg6;
    fr.one[0] = 1.0f;
    fr.one[2] = 1.0f;
    orthonormalizeFrame(&fr);
    fp = &fr;
    if ((D_main_bss_80130B63 != 0) || ((findLargestFreeHeapChunk() >= 0x3A98U) && (countDisplayListChunks() >= 0x4E20))) {
        args.c = arg4;
        args.d = arg5;
        args.frame = fp;
        args.a = arg3;
        args.b = arg0;
        args.e = arg7;
        spawnNpcOfType(orientedNpcHandler, &args, 1U, 0xFU);
    }
}

extern u8 D_main_bss_80130B63;
s32 orientedNpcHandler(struct D_80130BB8_type *self, u16 arg1, void *arg2);

typedef struct { s32 a; s32 b; s32 c; f32 d; f32 e; f32 f; } OrientedNpcArgs;

void gameStateByteGatedNpcHelper(s32 arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    OrientedNpcArgs args;

    if ((D_main_bss_80130B63 != 0) || ((findLargestFreeHeapChunk() >= 0x3A98U) && (countDisplayListChunks() >= 0x4E20))) {
        args.e = arg4;
        args.a = arg1;
        args.b = arg2;
        args.c = arg0;
        args.d = arg3;
        args.f = arg5;
        spawnNpcOfType(orientedNpcHandler, &args, 1U, 0xFU);
    }
}

s32 multiEventTemplateNpcHandler(struct D_80130BB8_type *self, u16 arg1, void *arg2);
s32 getPlayerField2(s32);
extern s32 D_main_bss_8013A894;

typedef struct {
    u16 idx;
    s16 cnt;
    u8 pad4[4];
    s32 w18;
    f32 f1C;
    s32 w20;
    s32 w24;
    u8 b28;
    u8 b29;
    u8 pad2A[2];
} MeArgs;

u16 spawnMultiEventNpcWrapper(u16 idx, f32 arg1, s32 cnt, s32 arg3, s32 arg4, u8 arg5, u8 arg6) {
    MeArgs args;
    u8 *ctx;

    ctx = (u8 *)getNpcContextByIndex(idx);
    if (ctx != NULL) {
        if (D_main_bss_80130B63 == 0) {
            if (idx != (u16)getPlayerField2(0) && D_main_bss_8013A894 >= 0xB) {
                return 0xFFFF;
            }
        }
        args.idx = idx;
        args.b28 = arg5;
        args.b29 = arg6;
        args.w20 = arg3;
        args.cnt = cnt;
        if (args.cnt <= 0) {
            args.cnt = 1;
        }
        args.w18 = -1;
        args.f1C = arg1;
        args.w24 = arg4;
        return spawnNpcOfType((npc_update)multiEventTemplateNpcHandler, &args, 4, ctx[0x19] + 1);
    }
    return 0xFFFF;
}

typedef struct {
    u16 a;
    s16 b;
    u8 c;
    u8 pad5[3];
    s32 buf;
    f32 d;
    s32 e;
    s32 f;
    u8 g;
    u8 h;
    u8 pad3A[2];
} ScArgs;

s32 scCnapt(void *, s32, s32, s32 *, void *, s32, s32) __asm__("computeNamedAttachPointTransform");

u16 spawnNpcChildForActivePlayerCell(u16 idx, f32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6) {
    ScArgs args;
    u8 sp40[0x30];
    u8 *ctx;

    ctx = (u8 *)getNpcContextByIndex(idx);
    if (ctx != NULL) {
        if (D_main_bss_80130B63 == 0) {
            if (idx != (u16)getPlayerField2(0) && D_main_bss_8013A894 >= 0xB) {
                return 0xFFFF;
            }
        }
        if (*(void **)(ctx + 0xC) != NULL) {
            if (scCnapt(*(void **)(ctx + 0xC), arg3, arg4, &args.buf, sp40, 0, 0) != 0) {
                args.c = arg4;
                args.a = idx;
                args.g = arg6;
                args.h = 0;
                args.e = 0;
                args.b = arg2;
                if (args.b <= 0) {
                    args.b = 1;
                }
                args.d = arg1;
                args.f = arg5;
                return spawnNpcOfType((npc_update)multiEventTemplateNpcHandler, &args, 4, ctx[0x19] + 1);
            }
        }
    }
    return 0xFFFF;
}

void sendSlotActionTwelve(u16 arg0) {
    if (arg0 != 0xFFFF) {
        slotDispatcherIter(arg0, 0xC, NULL);
    }
}

typedef struct DatTreeNode {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    u8 unk4;
    u8 pad5;
    u8 unk6;
    u8 pad7;
    struct DatTreeNode *unk8;
    u8 padC[0x2C];
} DatTreeNode;
extern u8 D_main_bss_8013A898;
extern u8 *D_main_bss_8013A89C;
void rs_free(void *);
void walkDatTreeAndCollectSubtypes(DatTreeNode *n) {
    s32 i;

    if (n->unk0 == 0xFF) {
        return;
    }
    if (n->unk0 & 0x80) {
        for (i = 0; i < n->unk4; i++) {
            if (n->unk8[i].unk6 != 0) {
                D_main_bss_8013A89C[D_main_bss_8013A898++] = n->unk8[i].unk6;
            }
        }
        rs_free(n->unk8);
        n->unk0 = 0xFF;
    } else if (n->unk6 != 0) {
        D_main_bss_8013A89C[D_main_bss_8013A898++] = n->unk6;
    }
}

extern u16 D_main_800A0AA0[][4];
void walkDatTreeAndScaleLeafByFloat(DatTreeNode *n, s32 arg1, f32 scale) {
    s32 i;

    if (n->unk0 & 0x80) {
        for (i = 0; i < n->unk4; i++) {
            walkDatTreeAndScaleLeafByFloat(&n->unk8[i], arg1, scale);
        }
    } else {
        n->unk2 = n->unk2 + D_main_800A0AA0[n->unk0 & 0x1F][n->unk1] * scale;
        if (n->unk2 > 0x100) {
            n->unk2 = 0;
            n->unk1 = (n->unk1 + 1) & 3;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/main/700B0", fake_func_80072CE8);

static u32 D_main_8003CEE4[] __attribute__((section(".rodata"))) = { 0x152A00C3, 0x00000000, 0x03688024 };
