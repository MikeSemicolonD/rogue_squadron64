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

INCLUDE_ASM("asm/nonmatchings/main/700B0", orientedNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/700B0", multiEventTemplateNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/700B0", walkDatTreeAndAllocSubtypeBuffers);

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
void vec3NormalizeInto(f32 *, f32 *);
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

INCLUDE_ASM("asm/nonmatchings/main/700B0", loadSfxAsset);

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
