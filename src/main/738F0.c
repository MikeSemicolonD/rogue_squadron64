#include "common.h"
#include "common_types.h"

extern u16 spawnNpcOfType(void *, void *, u32, u8);

typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s16 unk24;
} HeavyBurstArgs;

extern s32 heavyRandomBurstNpcHandler(void *, u16, void *);

__asm__(".section .rodata\n.align 2\nD_main_8003CEF0:\n.asciz \"gnrc_stuff/wtrspray\"\n.align 2\n.section .text");

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF04);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF10);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003CF20);

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    f32 unk10;
    s32 unk14;
    u8 pad18[8];
    u8 unk20;
    u8 pad21[0xF];
} WaterSprayRec;
typedef struct {
    s16 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    s8 unk10;
    union {
        s32 w[4];
        char c[13];
    } name;
} WaterTexDesc;
typedef struct {
    u8 pad[0x1C];
    struct { u8 pad[8]; s32 unk8; } *unk1C;
} MeshdefList;
extern s32 D_main_bss_8013A8B0;
extern s32 D_main_bss_8013A8B4;
extern s32 D_main_bss_8013A8B8;
extern WaterSprayRec D_main_bss_8013A8C0;
extern WaterSprayRec D_main_bss_8013A8F0;
extern WaterSprayRec D_main_bss_8013A920;
extern u8 D_main_bss_8013A944;
extern char D_main_8003CEF0[];
extern char D_main_8003CF04[];
extern s32 D_main_8003CF10[];
extern char D_main_8003CF20[];
extern void load_hmt_and_hob(char *, s32, s32, s32);
extern MeshdefList *walkMeshdef0List(char *);
extern u16 findTextureByName(char *);
extern void releaseTextureLutEntry(s32);
extern void *load_asset(char *);
extern void full_header_image_offset_convert(void *, void *);
extern s32 registerHmtTextureInTable(void *, void *, s32);
extern void rs_free(void *);
extern void setMaterialFlagByIdInMeshTree(s32, s32, s32);
extern void releaseMeshAsset(void *);
extern s32 loadAssetIntoNewSlot(char *, char *);
extern void setPoolEntryPhaseAndMarkActive(u16, f32, s32);

void initWaterSprayParticles(void) {
    WaterTexDesc d;
    MeshdefList *mesh;
    u16 tex;
    void *asset;
    u8 *hdr;
    s32 mat;

    D_main_bss_8013A8B0 = 0;
    D_main_bss_8013A8C0.unk20 = 0;
    D_main_bss_8013A8C0.unkC = 0;
    D_main_bss_8013A8C0.unk14 = 0;
    D_main_bss_8013A8F0.unk20 = 0;
    D_main_bss_8013A8F0.unkC = 0;
    D_main_bss_8013A8F0.unk14 = 0;
    D_main_bss_8013A920.unk20 = 0;
    D_main_bss_8013A920.unkC = 0;
    D_main_bss_8013A920.unk14 = 0;
    D_main_bss_8013A8C0.unk10 = 2.0f;
    D_main_bss_8013A8F0.unk10 = 1.5f;
    D_main_bss_8013A920.unk10 = 0.5f;
    load_hmt_and_hob(D_main_8003CEF0, 0, 0, 0);
    mesh = walkMeshdef0List(D_main_8003CF04);
    tex = findTextureByName((char *)D_main_8003CF10);
    releaseTextureLutEntry(tex);
    asset = load_asset(D_main_8003CF20);
    hdr = (u8 *)asset + 4;
    d.unk0 = 1;
    d.unkC = 0;
    d.unk10 = 1;
    d.unk4 = 1.0f;
    d.unk8 = 1.0f;
    __builtin_memcpy(d.name.c, D_main_8003CF10, 13);
    full_header_image_offset_convert(hdr, hdr);
    mat = registerHmtTextureInTable(&d, hdr, 0);
    rs_free(asset);
    setMaterialFlagByIdInMeshTree(mesh->unk1C->unk8, tex, mat & 0xFFFF);
    releaseMeshAsset(mesh);
    setPoolEntryPhaseAndMarkActive(loadAssetIntoNewSlot((char *)D_main_8003CF10, D_main_8003CF20), 12.0f, 0);
    D_main_bss_8013A944 = 1;
    D_main_bss_8013A8B4 = 0;
    D_main_bss_8013A8B8 = 0;
}

INCLUDE_ASM("asm/nonmatchings/main/738F0", npcWaterSprayUpdate);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnDestructionEffectBurst);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnDistanceScaledDebrisBurst);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnDirectionalDebrisBurst);

INCLUDE_ASM("asm/nonmatchings/main/738F0", distanceAndDopplerNpcHelper);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D088);

INCLUDE_ASM("asm/nonmatchings/main/738F0", explosionEffectNpcHandler);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D0C8);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D0CC);

INCLUDE_ASM("asm/nonmatchings/main/738F0", triggerDistanceScaledExplosion);

INCLUDE_ASM("asm/nonmatchings/main/738F0", triggerObjectDestructionEffects);

#include "main/192E0.h"
#include "main/1D000.h"
#include "main/5A750.h"
extern void *getNpcContextField8(u16);
typedef struct {
    u8 pad0[0x5C];
    Vec3f a;
    Vec3f b;
} LimbAnchors;
typedef struct {
    LimbAnchors *anchors;
    u8 pad4[0x24];
    Mat4x3 m;
} LimbObj;
typedef struct {
    u8 pad[0xC];
    LimbObj *obj;
} LimbCtx;
extern u8 *getNpcContextByIndex(u16);

void transformLimbStrideAnchorsLocal(u16 idx, f32 *out, f32 *out2) {
    Mat4x3 inv;
    Mat4x3 basis;
    Vec3f pa;
    Vec3f pb;
    LimbObj *obj;
    LimbAnchors *an;
    f32 *a;
    f32 *b;
    f32 s;
    f32 (*m)[3];

    obj = ((LimbCtx *)getNpcContextByIndex(idx))->obj;
    an = obj->anchors;
    m = obj->m;
    a = an->a;
    b = an->b;
    transformVec3ByMat34(m, a, pa);
    transformVec3ByMat34(m, b, pb);
    __asm__ volatile("sqrt.s %0, %1" : "=f"(s) : "f"(obj->m[0][0] * obj->m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]));
    out[0] = (an->b[0] - an->a[0]) * s;
    __asm__ volatile("sqrt.s %0, %1" : "=f"(s) : "f"(m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1]));
    out[1] = (b[1] - a[1]) * s;
    __asm__ volatile("sqrt.s %0, %1" : "=f"(s) : "f"(m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2]));
    out[2] = (b[2] - a[2]) * s;
    if (out2 != NULL) {
        out2[0] = pa[0] + (pb[0] - pa[0]) * 0.5f;
        out2[1] = pa[1] + (pb[1] - pa[1]) * 0.5f;
        out2[2] = pa[2] + (pb[2] - pa[2]) * 0.5f;
        mat34CrossRowsAndCopyPos(basis, getNpcContextField8(idx), 1.0f);
        mat3x3InverseInto(inv, basis);
        transformVec3ByMat34(inv, out2, out2);
    }
}

INCLUDE_ASM("asm/nonmatchings/main/738F0", randomParticleWithParentNpcHandler);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D15C);

extern u8 *D_main_bss_80138D1C;
extern s16 rand(void);
typedef struct { f32 x, y, z; } CamVec3;
extern CamVec3 D_main_8003D15C;

void buildRandomCameraFacingOrientation(Vec3f out, Vec3f dst, f32 scale, s32 range, s32 base, u8 mode) {
    Mat4x3 frame;
    Vec4f q40;
    Vec4f q50;
    Vec4f q60;
    Vec3f v70;
    Vec3f v80;
    Vec3f v90;
    f32 len;
    f32 *axis;
    f32 *tmp;

    extractOrthonormalFrameFromStruct(frame, (void *)(D_main_bss_80138D1C + 0x28));
    if (mode == 0) {
        if (range == 0) {
            quatFromAxisAngle(q40, frame[2], (f32)base);
        } else {
            quatFromAxisAngle(q50, frame[2], (f32)(base + rand() % range));
            quatFromAxisAngle(q60, frame[1], (f32)rand());
            quatMultiply(q60, q50, q40);
        }
        rotateVec3ByQuat(q40, frame[1], dst);
    } else {
        if (range == 0) {
            *(CamVec3 *)v80 = D_main_8003D15C;
            vec3Cross(v70, frame[2], frame[1]);
            vec3Cross(v90, v80, frame[1]);
            len = vec3Length(v90);
            if (len > 0.00001f) {
                v90[0] /= len;
                v90[1] /= len;
                v90[2] /= len;
                vec3Cross(v80, frame[1], v90);
                normalize_vector(v80);
                quatFromAxisAngle(q40, frame[1], -sinfApprox(vec3Dot(v70, v80)) * 57.29578f);
                rotateVec3ByQuat(q40, frame[2], v90);
            }
            vec3Cross(v70, v90, frame[1]);
            if (vec3Length(v70) > 0.00001f) {
                quatFromAxisAngleSafe(q40, v70, (f32)base);
                rotateVec3ByQuat(q40, v90, dst);
            }
        } else {
            quatFromAxisAngle(q50, frame[1], (f32)(base + rand() % range));
            quatFromAxisAngle(q60, frame[2], (f32)rand());
            quatMultiply(q60, q50, q40);
            rotateVec3ByQuat(q40, frame[2], dst);
        }
    }
    if (out != NULL) {
        out[0] = dst[0] * scale;
        out[1] = dst[1] * scale;
        out[2] = dst[2] * scale;
    }
}

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D170);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnScaledOrientedEffectTriple);

typedef struct { u8 p0[4]; struct HBNode *unk04; u8 p8[0xE]; u16 unk16; } HBSelf;
typedef struct HBNode {
    struct HBNode *next;
    struct HBNode *prev;
    s16 s8;
    s16 sA;
    s16 sC;
    u8 pE[2];
    u16 h10;
    u16 h12;
    u8 p14[8];
    s32 w1C;
    f32 f20;
    f32 f24;
    s16 h28;
    s16 h2A;
    u8 b2C;
    u8 b2D;
    u8 b2E;
    u8 b2F;
    f32 f30;
    f32 f34;
    f32 f38;
    f32 f3C;
    f32 f40;
    f32 f44;
    f32 f48;
    f32 f4C;
    f32 f50;
    f32 f54;
    f32 f58;
    f32 f5C;
    f32 f60;
    f32 f64;
} HBNode;
typedef struct { f32 x, y, z; } HBVec;
typedef struct {
    HBVec *pos;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
} HBSpawn;
typedef struct {
    f32 dt;
    u8 p4[0x14];
    f32 f18;
    f32 f1C;
    f32 f20;
    u8 p24[0x24];
    struct { u8 p[0x20]; HBNode *head; } *unk48;
} HBTick;
extern f32 cosf(f32);
extern u8 transformVec3ToNpcLocalWithScale(void *, s32, void *, f32, s32);
extern u16 D_main_bss_80139574;
extern u8 *D_main_bss_80138D1C;
extern u8 *D_main_bss_80130C08;
extern void popNpcSlotFromTail(u16, void *);
extern void destroyNpcSlotByIndex(u16);

s32 heavyRandomBurstNpcHandler(void *selfp, u16 action, void *arg2) {
    HBSelf *self = selfp;
    HBNode *n = self->unk04;
    register HBTick *a2 asm("$17");
    HBSpawn *sp = arg2;
    HBTick *tk = arg2;
    f32 dt;
    f32 one;
    f32 pi;
    f32 half;
    f32 v[3];
    f32 *cam;
    f32 *pos;
    f32 m;
    f32 d;

    switch (action) {
    case 1:
        n->h10 = 0x301;
        n->b2C = 0xFF;
        n->b2D = 0xFF;
        n->b2E = 0xFF;
        n->b2F = 0xFF;
        n->sC = 0;
        n->sA = 0;
        n->s8 = 0;
        n->h2A = 0;
        n->h28 = 0;
        n->w1C = 0;
        n->f3C = sp->f4;
        n->f44 = sp->f10;
        n->h12 = *(u16 *)(D_main_bss_80130C08 + 0x20);
        n->f24 = n->f20 = 0.001f;
        *(HBVec *)&n->f30 = *sp->pos;
        n->f60 = 0.0f;
        n->f40 = sp->fC;
        n->f58 = 1.0f;
        n->f5C = 1.0f;
        n->f54 = sp->f8 - sp->f4;
        n->f50 = sp->f1C;
        n->f48 = sp->f14;
        n->f4C = sp->f18;
        d = sp->f20;
        n->f64 = d;
        if (d == 0.0f) {
            n->f64 = 0.033333335f;
        }
        popNpcSlotFromTail(D_main_bss_80139574, self);
        return 1;
    case 2:
        break;
    case 3:
        dt = tk->dt;
        n->f60 = n->f60 + n->f40 * dt;
        one = 1.0f;
        if (n->f60 < one) {
            pi = 3.1415927f;
            half = 0.5f;
            n->f58 = n->f3C + (one - cosf(n->f60 * pi * half)) * n->f54 * (n->f44 * 3.0f) * n->f48;
            n->f5C = n->f3C + (one - cosf(n->f60 * pi * half)) * n->f54 * (n->f44 * 0.25f) * n->f4C;
            n->f20 = n->f58;
            if (n->f20 < 0.001f) n->f20 = 0.001f;
            n->f24 = n->f5C;
            if (n->f24 < 0.001f) n->f24 = 0.001f;
            m = n->f60;
            d = n->f64;
            if (d < m) {
                n->b2F = (u32)((one - m) * (one / d) * 255.0f);
            }
            if (n->f50 > 0.0f) {
                cam = (f32 *)(D_main_bss_80138D1C + 0x28);
                v[0] = cam[9] - n->f30;
                v[1] = cam[10] - n->f34;
                v[2] = cam[11] - n->f38;
                n->f30 = n->f30 + v[0] * n->f50 * dt;
                n->f34 = n->f34 + v[1] * n->f50 * dt;
                n->f38 = n->f38 + v[2] * n->f50 * dt;
            }
        } else {
            destroyNpcSlotByIndex(self->unk16);
            return 1;
        }
        break;
    case 4:
        a2 = arg2;
        __asm__("" : "+r"(a2));
        pos = &n->f30;
        m = n->f5C;
        if (m < n->f58) m = n->f58;
        if (!transformVec3ToNpcLocalWithScale(*(void **)a2, 0, pos, m, 0)) {
            return 1;
        }
        {
            HBNode *head;
            n->s8 = (s32)((n->f30 - a2->f18) * 256.0f);
            n->sA = (s32)((n->f34 - a2->f1C) * 256.0f);
            n->sC = (s32)((n->f38 - a2->f20) * 256.0f);
            head = a2->unk48->head;
            n->next = head;
            if (head != NULL) head->prev = n;
            n->prev = NULL;
            tk->unk48->head = n;
        }
        break;
    default:
        return 1;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/738F0", buildNpcAnchoredCameraEffectTransform);

void computeWalkerLimbStrideTargets(u16 id, f32 *base, f32 *outA, f32 *outB, f32 k) {
    f32 a[4];
    f32 b[4];
    f32 c[4];
    f32 m[12];
    mat34CrossRowsAndCopyPos((void *)m, getNpcContextField8(id), 1.0f);
    transformLimbStrideAnchorsLocal(id, a, b);
    c[0] = b[0] - a[0] * 0.5f * k;
    c[1] = b[1] + a[1] * 0.5f * k;
    c[2] = b[2] - a[2] * 0.5f * k;
    transformVec3ByMat34(m, c, base);
    c[0] = b[0] + a[0] * 0.5f * k;
    c[1] = b[1] + a[1] * 0.5f * k;
    c[2] = b[2] - a[2] * 0.5f * k;
    transformVec3ByMat34(m, c, c);
    outA[0] = c[0] - base[0];
    outA[1] = c[1] - base[1];
    outA[2] = c[2] - base[2];
    c[0] = b[0] - a[0] * 0.5f * k;
    c[1] = b[1] + a[1] * 0.5f * k;
    c[2] = b[2] + a[2] * 0.5f * k;
    transformVec3ByMat34(m, c, c);
    outB[0] = c[0] - base[0];
    outB[1] = c[1] - base[1];
    outB[2] = c[2] - base[2];
}

typedef struct {
    f32 x, y, z;
} ExtrapVec3;

extern s32 D_8010CA20;
extern void distanceAndDopplerNpcHelper(f32 *, f32, f32);
extern void spawnNpcType0xAFromTemplate(f32 *, f32);
extern void spawnRandomScaleColoredEffectFromCaller(void *, f32, f32, s32);

static __inline__ void extrapolateVec3Inline(f32 *src, f32 *out, f32 t) {
    out[0] = src[0] - src[3] * t;
    out[1] = src[1] - src[4] * t;
    out[2] = src[2] - src[5] * t;
}

void extrapolateNpcPositionForCurrentMode(u8 *obj) {
    f32 pos[8];
    f32 *src = *(f32 **)(obj + 8);
    f32 *out;
    f32 k;

    if (src != NULL) {
        if (D_8010CA20 == 0) {
            out = pos;
            k = 0.2f;
            pos[0] = src[0] - src[3] * k;
            out[1] = src[1] - src[4] * k;
            out[2] = src[2] - src[5] * k;
        } else {
            *(ExtrapVec3 *)pos = *(ExtrapVec3 *)src;
        }
        switch (*(u16 *)(obj + 4)) {
        case 12:
            spawnRandomScaleColoredEffectFromCaller(pos, 0.4f, 0.8f, 0);
            return;
        case 8:
        case 9:
            return;
        case 10:
        case 11:
        case 13:
        case 14:
            spawnNpcType0xAFromTemplate(pos, 0.6f);
            return;
        default:
            distanceAndDopplerNpcHelper(pos, 0.05f, 0.2f);
            spawnNpcType0xAFromTemplate(pos, 0.2f);
            return;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D220);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D224);

INCLUDE_ASM("asm/nonmatchings/main/738F0", npcPowerGeneratorHandleDestruction);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnDirectionalDebrisBurstAnchored);

INCLUDE_ASM("asm/nonmatchings/main/738F0", npcWakeUpdate);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D2D4);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnGatedDistanceEffectPair);

typedef struct {
    f32 unk0;
    f32 unk4;
    s16 unk8;
} RandomParticleArgs;

extern void spawnRandomScaleColoredEffectFromCaller(void *, f32, f32, s32);
extern void randomParticleWithParentNpcHandler(void);

void spawnRandomParticleWithParent(void *arg0, s32 arg1, f32 arg2, u8 arg3) {
    RandomParticleArgs args;

    if (arg0 != NULL) {
        spawnRandomScaleColoredEffectFromCaller(arg0, arg2, arg2 + arg2, 0);
    }
    if (arg3) {
        args.unk8 = arg1;
        args.unk4 = arg2;
        args.unk0 = 0.6f;
        spawnNpcOfType(randomParticleWithParentNpcHandler, &args, 4, 10);
    }
}

extern f32 vec3Length(Vec3f);
extern u8 *D_main_bss_80138D1C;

f32 distanceFromCameraToPoint(f32 *arg0) {
    Vec3f d;
    u8 *cam = D_main_bss_80138D1C + 0x28;

    d[0] = arg0[0] - *(f32 *)(cam + 0x24);
    d[1] = arg0[1] - *(f32 *)(cam + 0x28);
    d[2] = arg0[2] - *(f32 *)(cam + 0x2C);
    return vec3Length(d);
}

static __inline__ u16 spawnHeavyBurstInline(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    HeavyBurstArgs args;

    args.unk0 = arg0;
    args.unkC = 1.0f;
    if (arg9 > 0.0f) {
        args.unkC = 1.0f / arg9;
    }
    args.unk10 = arg4;
    args.unk24 = arg1;
    args.unk4 = arg2;
    args.unk8 = arg3;
    args.unk14 = arg5;
    args.unk18 = arg6;
    args.unk1C = arg7;
    args.unk20 = arg8;
    return spawnNpcOfType(heavyRandomBurstNpcHandler, &args, 1, 100);
}

u16 spawnEffectNpcWithRampedScale(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    return spawnHeavyBurstInline(arg0, arg1, arg2, arg3, 1.3333334f, 1.0f, 1.0f, 3.0f, 0.5f, arg4);
}

u16 spawnEffectNpcWithRampedScaleExt(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9) {
    HeavyBurstArgs args;

    args.unk0 = arg0;
    args.unkC = 1.0f;
    if (arg9 > 0.0f) {
        args.unkC = 1.0f / arg9;
    }
    args.unk10 = arg4;
    args.unk24 = arg1;
    args.unk14 = arg5;
    args.unk18 = arg6;
    args.unk1C = arg7;
    args.unk4 = arg2;
    args.unk8 = arg3;
    args.unk20 = arg8;
    return spawnNpcOfType(heavyRandomBurstNpcHandler, &args, 1, 100);
}

void vec3ExtrapolateFirstOrder(f32 *arg0, s32 arg1, f32 *arg2, f32 arg3) {
    arg2[0] = arg0[0] - arg0[3] * arg3;
    arg2[1] = arg0[1] - arg0[4] * arg3;
    arg2[2] = arg0[2] - arg0[5] * arg3;
}

extern void buildNpcAnchoredCameraEffectTransform(u16, void *, s32, f32);

void buildNpcAnchoredCameraEffectTransformWrapper(u16 arg0, void *arg1, f32 arg2) {
    buildNpcAnchoredCameraEffectTransform(arg0, arg1, 0, arg2);
}

typedef struct {
    s32 unk0;
    u8 pad4[0x18];
    s16 unk1C;
    s16 unk1E;
} WaterSprayArgs;

extern u8 *getNpcContextByIndex(u16);
extern u8 D_main_bss_8013A944;
extern void npcWaterSprayUpdate(void);

u16 spawnWaterSprayNpc(s32 arg0, s32 arg1) {
    WaterSprayArgs args;
    u16 id = arg0;

    if (D_main_bss_8013A944 != 0) {
        args.unk1C = id;
        args.unk0 = arg1;
        args.unk1E = 0;
        return spawnNpcOfType(npcWaterSprayUpdate, &args, 1, getNpcContextByIndex(id)[0x19] + 1);
    }
    return 0xFFFF;
}

void spawnOrientedEffectIfBudgetOkAlt(f32 *, f32 *, s32, f32, f32, f32);
typedef struct { f32 *vec; void *parent; u8 pad8[4]; f32 f24c; f32 f28c; f32 pad2C; f32 f30c; u16 s34; s16 s36; } WsArgs;
void spawnDistanceScaledDebrisBurst(void *, f32, f32);
extern f32 D_main_bss_80136FA8;
void spawnWaterSprayDebrisAndBurst(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    WsArgs a;
    f32 v[3];
    if (D_main_bss_8013A944 != 0) {
        a.s34 = 0xFFFF;
        v[1] = arg3;
        a.s36 = 2;
        a.parent = arg0;
        v[0] = arg1;
        v[2] = arg1;
        a.vec = v;
        a.f30c = arg4;
        a.f28c = 1.0f / arg5;
        a.f24c = arg2 - arg1;
        spawnNpcOfType(npcWaterSprayUpdate, &a, 1, 0xF);
        spawnDistanceScaledDebrisBurst(arg0, arg2 * 0.75f, arg4 * 0.4f);
        v[0] = arg0[0];
        v[1] = (arg0[1] - D_main_bss_80136FA8) - 0.05f;
        v[2] = arg0[2];
        spawnOrientedEffectIfBudgetOkAlt(v, 0, 0, arg1 * 0.3f, arg2 * 0.6f, arg5 * 2.2f);
    }
}

typedef struct {
    u8 *parent;
    s32 unk4;
    void *unk8;
    s32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
} WakeTrailArgs;

extern u8 D_main_800A0D70[];
extern void npcWakeUpdate(void);

void spawnSpeedGatedTrailEffect(s16 arg0, u8 *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7, f32 arg8) {
    WakeTrailArgs args;

    if (D_main_bss_8013A944 != 0 && arg5 > 0.0f && vec3Length((f32 *)(arg1 + 0x24)) > 0.0f) {
        args.parent = arg1;
        args.unk14 = arg5;
        args.unk18 = arg3;
        args.unk2C = arg0;
        args.unkC = 0;
        args.unk1C = arg4;
        args.unk4 = arg7;
        args.unk24 = arg8;
        args.unk8 = D_main_800A0D70;
        args.unk20 = 1.0f / arg6;
        args.unk28 = 0.3f;
        args.unk10 = arg2 * 0.5f;
        spawnNpcOfType(npcWakeUpdate, &args, 2, 15);
    }
}

void forwardToNpcGeneratorSpawn(u16 arg0, s32 arg1, f32 arg2) {
    Vec3f out;

    buildNpcAnchoredCameraEffectTransform(arg0, out, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/main/738F0", func_main_80077AF0);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D448);

INCLUDE_RODATA("asm/nonmatchings/main/738F0", D_main_8003D454);

INCLUDE_ASM("asm/nonmatchings/main/738F0", spawnDebrisBurstFromTemplate);

typedef struct {
    u8 pad0[0x6C];
    s32 health[8];
    u8 pad8C_[0x8C - 0x6C - 0x20];
} NpcDefHealth;

extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern s32 D_main_bss_80137CE4;

void initSpawnedNpcHealthAndDetail(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    s32 i;

    *(u8 *)(npc + 0x125) = 0;
    for (i = 0; i < 8; i++) {
        ((s32 *)(npc + 0xD4))[i] = D_main_bss_80137CE4[(*(NpcDefHealth **)(npc + 0x68))->health];
    }
    setNpcHealth(*(s32 *)(npc + 0x6C), (*(NpcDefHealth **)(npc + 0x68))->health, *(NpcDefHealth **)(npc + 0x68));
    setObjectDetailLevel(*(s32 *)(npc + 0x6C), *(s32 *)(*(u8 **)(npc + 0x68) + 0x8C));
}

INCLUDE_ASM("asm/nonmatchings/main/738F0", fake_func_80079278);
