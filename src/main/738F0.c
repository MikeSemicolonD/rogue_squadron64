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

typedef struct { f32 x, y, z; } PgBlk;
typedef struct { f32 f[12]; char name[4]; } PgHs;
typedef struct {
    f32 pos[3];
    f32 rot[6];
    f32 vel[3];
    u8 *mesh;
    f32 mat[12];
    u8 *beam;
    u8 *rec;
    s32 obj;
    u8 *n0;
    u8 *n1;
    u8 *n2;
    u8 *nc[8];
    u8 *m0;
    u8 *m1;
    u8 *m2;
    u8 *mc[8];
    f32 sc[3];
    s32 health[8];
    u16 slot[8];
    u16 fx[2];
    u16 deb[2];
    PgBlk debData[2];
    u8 a124;
    u8 state;
    s16 count;
    f32 radius;
    f32 scale;
    f32 a130;
    f32 a134;
    f32 a138;
    f32 t;
    f32 ease;
    u16 s144;
    u16 s146;
    u16 s148;
    u16 s14A;
    s32 cnt;
    u8 audio[0x88];
    u8 audioOn;
    u8 pad1D9[3];
    u8 dat[0x38];
} PgObj;
extern u16 D_main_bss_80139560[];
extern u8 D_main_bss_80130BA0;
u16 pgPop(u16, void *) __asm__("popNpcSlotFromTail");
u8 *pgWalk(char *) __asm__("walkMeshdef0List");
void *rs_malloc(u32, u16);
void applyFlagsToMeshTreeOrList(void *, s32, s32, s32);
u8 *lookupHmtMaterialByName(void *, char *, void *);
u16 spawnInheritedNpcVariantC(u16, char *, s32);
void pgTex(void *, char *, s32, void *, s32, s32) __asm__("lookupHmtTextureByName");
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
void createAndInitObject(void *, s32, void *, void *, s32);
void initSpawnedNpcHealthAndDetail(void *);
void spawnNpcWithRandomRotation(void *);
s32 sprintf(char *, const char *, ...);
u16 spawnHeavyMechSubEffect(void *, void *, char *);
void dispatchDatSubtypeByRandomIndex(void *, void *);
void factor5RemoveListNode(void *);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void walkDatTreeAndCollectSubtypes(void *, void *);
void npcPowerGeneratorHandleDestruction();
f32 quadraticEaseInOut(f32);
f32 floatModulo(f32, f32);
void spawnDebrisBurstFromTemplate(void *, s32);
s32 isNpcWithinActiveReferenceRange(void *);
void walkDatTreeAndScaleLeafByFloat(void *, void *, f32);
void destroyObjectOwnedNpcSlot(s32);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
void walkDatTreeAndVisitChildren(void *, void *, void *);
void updateActive3DAudioSource(void *, void *, void *, s32);
s32 getNpcCurrentHealth(s32);
extern u8 D_main_bss_80130B39;
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void spawnOrientedNpc(s32, void *, s32, s32, f32, f32, f32, f32);
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
void setObjectFlagBit4(void *);
void dispatchSlotAction5IfActive(void *, void *);
#define PG_JOINT_HEAD(mm, nn) \
    m = (mm); \
    n = (nn) + 0x1C; \
    clearVec4QuadStruct((void *)n); \
    if (*(s32 *)(m + 0x4C) & 1) { \
        addVec3At0x24((void *)n, -*(f32 *)(m + 0x50), -*(f32 *)(m + 0x54), -*(f32 *)(m + 0x58)); \
    } \
    if (*(s32 *)(m + 0x4C) & 2) { \
        applyScaleToMat3x4((void *)n, *(f32 *)(m + 0x5C), *(f32 *)(m + 0x60), *(f32 *)(m + 0x64)); \
    } \
    if (*(s32 *)(m + 0x4C) & 4) { \
        composeQuatToMat3x4((void *)n, (void *)(m + 0x68)); \
    }
#define PG_JOINT_TAIL() \
    { s32 fl = *(s32 *)(m + 0x4C); \
    if ((fl & 9) == 9) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x78) + *(f32 *)(m + 0x50), *(f32 *)(m + 0x7C) + *(f32 *)(m + 0x54), *(f32 *)(m + 0x80) + *(f32 *)(m + 0x58)); \
    } else if ((fl & 9) == 8) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x78), *(f32 *)(m + 0x7C), *(f32 *)(m + 0x80)); \
    } else if (fl & 1) { \
        addVec3At0x24((void *)n, *(f32 *)(m + 0x50), *(f32 *)(m + 0x54), *(f32 *)(m + 0x58)); \
    } }

static __inline__ u8 pgAlive(PgObj *s2) {
    if (D_main_bss_80130B39 == 0) {
        return getNpcCurrentHealth(s2->obj) > 0;
    }
    return 1;
}

s32 func_main_80077AF0(u8 *arg0, u16 action, u8 *arg2) {
    union {
        struct { char nm[12]; s32 pad; PgHs hs; s32 pad2; char buf[16]; } c1;
        struct { char pad[0x10]; f32 v[3]; } c4;
        struct { char pad[0x20]; PgHs hs; s32 pad2; f32 m[12]; char nm[4]; } c5;
    } u;
    PgObj *s2 = *(PgObj **)(arg0 + 4);

    switch (action) {
    case 1:
        {
            u8 *rec = arg2;
            f32 inv;
            s32 i;
            s2 = rs_malloc(0x214, 0);
            *(PgObj **)(arg0 + 4) = s2;
            *(u16 *)(arg0 + 0x14) |= 0x100;
            s2->rec = rec;
            s2->mesh = pgWalk(*(char **)(rec + 0x5C));
            s2->beam = pgWalk("engybeam");
            applyFlagsToMeshTreeOrList(s2->beam, 0, 0x10000, 0);
            s2->pos[0] = *(f32 *)(rec + 0x10);
            s2->pos[1] = *(f32 *)(rec + 0x14);
            s2->pos[2] = *(f32 *)(rec + 0x18);
            composeEulerRotationXYZ((void *)s2, *(f32 *)(rec + 0x1C), *(f32 *)(rec + 0x20), *(f32 *)(rec + 0x24));
            s2->vel[0] = s2->vel[1] = s2->vel[2] = 0.0f;
            inv = 1.0f / *(f32 *)(*(u8 **)s2->mesh + 0x34);
            s2->scale = inv * *(f32 *)(rec + 0x28);
            initVec4TripletFromArgs((void *)(s2->mesh + 0x28), inv * *(f32 *)(rec + 0x28), inv * *(f32 *)(rec + 0x2C), inv * *(f32 *)(rec + 0x30));
            composeRotationMatrixSlot0((void *)(s2->mesh + 0x28), *(f32 *)(rec + 0x1C));
            composeRotationMatrixSlot1((void *)(s2->mesh + 0x28), *(f32 *)(rec + 0x20));
            composeRotationMatrixSlot2((void *)(s2->mesh + 0x28), *(f32 *)(rec + 0x24));
            addVec3At0x24((void *)(s2->mesh + 0x28), s2->pos[0], s2->pos[1], s2->pos[2]);
            *(PgObj **)(arg0 + 8) = s2;
            *(u8 **)(arg0 + 0xC) = s2->mesh;
            s2->n0 = lookupHmtMaterialByName(s2->mesh, "base", &s2->m0);
            s2->n1 = lookupHmtMaterialByName(s2->mesh, "maintrns", &s2->m1);
            s2->n2 = lookupHmtMaterialByName(s2->mesh, "top_top", &s2->m2);
            {
                __builtin_memcpy(u.c1.nm, "cb_trns1", 9);
                for (i = 0; i < 8; i++) {
                    s2->nc[i] = lookupHmtMaterialByName(s2->mesh, u.c1.nm, &s2->mc[i]);
                    u.c1.nm[7]++;
                }
            }
            {
                __builtin_memcpy(u.c1.nm, "cb1", 4);
                for (i = 0; i < 8; i++) {
                    s2->slot[i] = spawnInheritedNpcVariantC(*(u16 *)(arg0 + 0x16), u.c1.nm, 0);
                    u.c1.nm[2]++;
                }
            }
            pgTex(s2->mesh, "03", 0, s2->mat, 0, 0);
            s2->mat[6] = -s2->mat[6];
            s2->mat[7] = -s2->mat[7];
            s2->sc[0] = s2->scale * 1.8f;
            s2->mat[8] = -s2->mat[8];
            s2->sc[1] = 1.5f;
            s2->sc[2] = s2->scale * 1.8f;
            { /*B1*/
                u8 *b = (u8 *)D_main_bss_80139560;
                s32 o = 0x12;
                if (*(s32 *)(rec + 0x8C) == 1) {
                    o = 0xE;
                }
                s2->s148 = pgPop(*(u16 *)(o + b), arg0);
                if (*(s32 *)(rec + 0x90) != 0) {
                    s32 o2 = 0x18;
                    if (*(s32 *)(rec + 0x8C) == 1) {
                        o2 = 0x1A;
                    }
                    s2->s14A = pgPop(*(u16 *)(o2 + b), arg0);
                } else {
                    s2->s14A = 0xFFFF;
                }
            }
            {
                u8 *b;
                s32 t;
                s32 o;
                __asm__("la %0, D_main_bss_80139560" : "=r"(b));
                s2->s144 = pgPop(*(u16 *)(b + 0x1C), arg0);
                t = *(s32 *)(rec + 0x8C);
                o = (t == 1) ? 0x26 : (t == 0) ? 0x28 : 0x2A;
                s2->s146 = pgPop(*(u16 *)(b + o), arg0);
            } /*B2*/
            s2->radius = *(f32 *)(*(u8 **)s2->mesh + 0x44) * s2->scale;
            s2->a130 = 0.0f;
            s2->a134 = 0.0f;
            s2->a138 = 0.0f;
            s2->t = 0.0f;
            s2->ease = 0.0f;
            s2->a124 = 0;
            s2->count = 0;
            s2->cnt = 0;
            s2->deb[0] = s2->deb[1] = s2->fx[0] = s2->fx[1] = 0xFFFF;
            s2->audioOn = 1;
            play3DSoundEventVariant(s2->audio, s2, s2->vel, 14.0f, 0.6f, 7, 0x14, 1, 0x7F, 0x3C);
            if (D_main_bss_80130B39 == 0) {
                createAndInitObject(&s2->obj, 0, arg0, initSpawnedNpcHealthAndDetail, 0);
            } else {
                s2->state = 0;
                if (D_main_bss_80130BA0 != 0) {
                    for (i = 0; i < 7; ) {
                        s32 j;
                        s2->health[i] = -1;
                        u.c1.hs.name[0] = 'c';
                        u.c1.hs.name[1] = 'b';
                        u.c1.hs.name[2] = i + '1';
                        u.c1.hs.name[3] = 0;
                        spawnNpcWithRandomRotation(&u.c1.hs);
                        j = i + 1;
                        u.c1.hs.f[6] = 0.0f;
                        sprintf(u.c1.buf, "cb_trns%d", j);
                        spawnHeavyMechSubEffect(&u.c1.hs, arg0, u.c1.buf);
                        destroyNpcSlotByIndex(s2->slot[i]);
                        s2->slot[i] = 0xFFFF;
                        i = j;
                    }
                    s2->health[7] = 1;
                    s2->count = 7;
                }
            }
            dispatchDatSubtypeByRandomIndex(s2->dat, s2->mesh);
            return 1;
        }
    case 2:
        if (s2->audioOn == 1) {
            s2->audioOn = 0;
            factor5RemoveListNode(s2->audio);
        }
        if (D_main_bss_80130B39 == 0) {
            initActorRenderDescriptorIfUninit(s2->obj, s2->state == 1, s2->rec, 0, s2->rec + 0x70);
            clearPendingAndDestroyChildNpc(&s2->obj);
        }
        walkDatTreeAndCollectSubtypes(s2->dat, s2->mesh);
        releaseMeshAsset(s2->mesh);
        return 1;
    case 3:
        {
            f32 dt = *(f32 *)arg2;
            f32 d;
            npcPowerGeneratorHandleDestruction();
            switch (s2->state) {
            case 0:
                d = *(f32 *)(s2->rec + 0x94) * dt * 30.0f;
                s2->a134 = floatModulo(s2->a134 + d, 360.0f);
                s2->a130 = floatModulo(s2->a130 - d, 360.0f);
                s2->a138 = floatModulo(s2->a138 + (d + d), 360.0f);
                break;
            case 1:
                {
                    f32 e;
                    s2->t = s2->t + dt / 1.5f;
                    if (s2->t > 1.0f) {
                        s2->t = 1.0f;
                    }
                    e = quadraticEaseInOut(s2->t);
                    s2->ease = e;
                    d = *(f32 *)(s2->rec + 0x94) * dt * 30.0f * (1.0f - e);
                    s2->a134 = floatModulo(s2->a134 + d, 360.0f);
                    s2->a130 = floatModulo(s2->a130 - d, 360.0f);
                    if (s2->deb[0] != 0xFFFF) {
                        s2->debData[0].y -= 6.0f;
                        spawnDebrisBurstFromTemplate(s2, 0);
                    }
                    if (s2->deb[1] != 0xFFFF) {
                        spawnDebrisBurstFromTemplate(s2, 1);
                    }
                    if (s2->a124 == 2) {
                    destroy:
                        destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
                        return 1;
                    }
                }
                break;
            }
            if (*(s32 *)(s2->rec + 0x88) == 0) {
                s2->cnt = 0;
            } else if (isNpcWithinActiveReferenceRange(s2) != 0) {
                s2->cnt = 0;
            } else if (++s2->cnt >= 0x15) {
                goto destroy;
            }
            if (s2->dat[0] != 0xFF) {
                walkDatTreeAndScaleLeafByFloat(s2->dat, s2->mesh, *(f32 *)arg2);
            }
            if (D_main_bss_80130B39 == 0) {
                destroyObjectOwnedNpcSlot(s2->obj);
                return 1;
            }
            return 1;
        }
    case 4:
        {
            u8 *a4 = arg2;
            s32 i;
            u8 *m;
            u8 *n;
            PG_JOINT_HEAD(s2->m0, s2->n0)
            composeRotationMatrixSlot1((void *)n, s2->a134);
            PG_JOINT_TAIL()
            PG_JOINT_HEAD(s2->m1, s2->n1)
            composeRotationMatrixSlot1((void *)n, s2->a130);
            PG_JOINT_TAIL()
            PG_JOINT_HEAD(s2->m2, s2->n2)
            addVec3At0x24((void *)n, 0.0f, s2->ease + s2->ease, 0.0f);
            PG_JOINT_TAIL()
            for (i = 0; i < 8; i++) {
                if (s2->health[i] > 0) {
                    PG_JOINT_HEAD(s2->mc[i], s2->nc[i])
                    composeRotationMatrixSlot1((void *)n, s2->a138);
                    PG_JOINT_TAIL()
                }
            }
            mat34CrossRowsAndCopyPos((void *)(s2->mesh + 0x28), (void *)s2, s2->scale);
            if (addNpcToVisibilityBucket(*(s32 *)a4, s2->mesh, s2, s2->radius) != 0 && s2->dat[0] != 0xFF) {
                walkDatTreeAndVisitChildren(s2->dat, s2->mesh, a4);
            }
            pgTex(s2->mesh, "03", 0, s2->mat, 0, 0);
            s2->mat[6] = -s2->mat[6];
            s2->mat[7] = -s2->mat[7];
            s2->mat[8] = -s2->mat[8];
            u.c4.v[0] = s2->sc[0] * (1.0f - s2->ease);
            u.c4.v[1] = s2->sc[1] * (1.0f - s2->ease);
            u.c4.v[2] = s2->sc[2] * (1.0f - s2->ease);
            if (u.c4.v[1] > 0.0f) {
                mat34CrossRowsAndCopyPosPtr((void *)(s2->beam + 0x28), (void *)s2->mat, u.c4.v);
                addNpcToVisibilityBucket(*(s32 *)a4, s2->beam, s2->mat, s2->radius);
            }
            for (i = 0; i < 2; i++) {
                if (s2->fx[i] != 0xFFFF) {
                    slotDispatcherIter(s2->fx[i], 0xE, arg2);
                }
            }
            if (s2->audioOn != 0) {
                updateActive3DAudioSource(s2->audio, s2, s2->vel, 0x7F);
                return 1;
            }
        }
        break;
    case 5:
        {
            u8 *a5 = arg2;
            s32 idx;
            s32 alive = pgAlive(s2);
            if (alive == 1) {
                u8 *msg;
                u8 *nm;
                u8 c0;
                u8 c1;
                extrapolateNpcPositionForCurrentMode(a5);
                msg = *(u8 **)(a5 + 8);
                if (msg != NULL && (nm = *(u8 **)(msg + 0x24)) != NULL && (c0 = nm[0]) == 'c' && (c1 = nm[1]) == 'b' && nm[2] == '_') {
                    u8 c7 = nm[7];
                    idx = c7 - '1';
                    if (s2->health[idx] > 0) {
                        play3DSoundEvent(0, s2, s2->vel, 24.0f, 0.4f, 0, 0x2A, 0x78, 0x3C);
                        if ((s2->health[idx] -= *(u16 *)(a5 + 6)) <= 0) {
                            u.c5.nm[0] = c0;
                            u.c5.nm[1] = c1;
                            u.c5.nm[2] = c7;
                            u.c5.nm[3] = 0;
                            pgTex(s2->mesh, u.c5.nm, 0, u.c5.m, 0, 0);
                            spawnOrientedNpc(2, u.c5.m, 0, 0, s2->scale * 1.3f, s2->scale * 1.9f, 0.8f, 0.6f);
                            spawnOrientedNpc(2, u.c5.m, 0, 0, s2->scale * 1.1f, s2->scale + s2->scale, 0.8f, 0.5f);
                            spawnOrientedNpc(3, u.c5.m, 0, 0, s2->scale * 0.9f, s2->scale * 2.2f, 0.8f, 0.45f);
                            spawnNpcType0xAFromTemplate(u.c5.m, s2->scale * 4.0f);
                            play3DSoundEvent(0, s2, s2->vel, 24.0f, 0.6f, 0, 0x23, 0x7D, 0x50);
                            if (s2->slot[idx] != 0xFFFF) {
                                destroyNpcSlotByIndex(s2->slot[idx]);
                            }
                            s2->slot[idx] = 0xFFFF;
                            spawnNpcWithRandomRotation(&u.c5.hs);
                            u.c5.hs.f[6] = 0.0f;
                            spawnHeavyMechSubEffect(&u.c5.hs, arg0, (char *)nm);
                            if (++s2->count == 8) {
                                s2->state = alive;
                                spawnNpcWithRandomRotation(&u.c5.hs);
                                u.c5.hs.f[8] = 0.0f;
                                u.c5.hs.f[9] = 0.0f;
                                u.c5.hs.f[10] = 0.0f;
                                u.c5.hs.f[4] = 0.5f;
                                u.c5.hs.f[2] = -0.5f;
                                u.c5.hs.f[3] = -2.8f;
                                u.c5.hs.f[5] = 2.4f;
                                u.c5.hs.f[11] = 5.0f;
                                u.c5.hs.f[6] = 2.5f;
                                s2->fx[0] = spawnHeavyMechSubEffect(&u.c5.hs, arg0, "maintrns");
                                u.c5.hs.f[4] = 0.9f;
                                u.c5.hs.f[5] = 1.3f;
                                u.c5.hs.f[2] = 0.2f;
                                u.c5.hs.f[3] = 0.2f;
                                u.c5.hs.f[11] = 45.0f;
                                u.c5.hs.f[6] = 3.4f;
                                s2->fx[1] = spawnHeavyMechSubEffect(&u.c5.hs, arg0, "base");
                                if (D_main_bss_80130B39 == 0) {
                                    unregisterAndFreeNpcSlot(s2->s146, arg0);
                                    unregisterAndFreeNpcSlot(s2->s148, arg0);
                                    if (s2->s14A != 0xFFFF) {
                                        unregisterAndFreeNpcSlot(s2->s14A, arg0);
                                    }
                                    pgPop(D_main_bss_80139574, arg0);
                                    {
                                        u8 *r = s2->rec;
                                        datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s2->rec + 0x84));
                                    }
                                    tallyMidDetailObject(arg0);
                                    setObjectFlagBit4(arg0);
                                }
                                if (s2->audioOn == 1) {
                                    s2->audioOn = 0;
                                    factor5RemoveListNode(s2->audio);
                                }
                            }
                        }
                    }
                } else {
                    play3DSoundEvent(0, s2, s2->vel, 18.0f, 0.4f, 0, 0x2A, 0x78, 0x3C);
                }
            }
            if (*(u16 *)a5 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)a5);
                return 1;
            }
            return 1;
        }
    case 15:
        {
            u16 *msg = (u16 *)arg2;
            s32 i;
            for (i = 0; i < 2; i++) {
                if (s2->fx[i] == msg[0]) {
                    s2->deb[i] = s2->fx[i];
                    s2->debData[i] = *(PgBlk *)(msg + 2);
                    msg[0] = 0xFFFF;
                    return 1;
                }
            }
            return 1;
        }
    case 7:
        if (D_main_bss_80130B39 == 0) {
            dispatchSlotAction5IfActive(arg0, arg2);
        }
        break;
    }
    return 1;
}

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
