#include "common.h"

#include "hob.h"

#include "main/5AD20.h"

struct vertex D_main_8009ECC0[] = {
    {0xFF80, 0x0000, 0xFF80, 0x0000},
    {0x0080, 0x0000, 0xFF80, 0x0000},
    {0x0080, 0x0000, 0x0080, 0x0000},
    {0xFF80, 0x0000, 0x0080, 0x0000},
};

f32 D_main_8009ECE0[] = {
    5.0f,
    -5.0f,
    21.0f,
    -21.0f,
};

INCLUDE_ASM("asm/nonmatchings/main/5AD20", loadTopCloudsAsset);

INCLUDE_ASM("asm/nonmatchings/main/5AD20", updateWalkerParticlePositions);

INCLUDE_RODATA("asm/nonmatchings/main/5AD20", D_main_8003AE10);

INCLUDE_ASM("asm/nonmatchings/main/5AD20", loadSkyHorizonHob);

f32 atan2Approx(f32, f32);
void linkDirectionalTrailSegments(f32 *arg0, u8 *arg1) {
    u8 *base = arg1 + 0x1C;
    s32 lo;
    s32 hi;
    s32 i;
    s32 t;
    u8 *n;
    u8 *m;

    f32 ab;
    __asm__ volatile("abs.s %0, %1" : "=f"(ab) : "f"(arg0[4]));
    if (0.7f < ab) {
        lo = 0;
        hi = 7;
    } else {
        t = (s32)(atan2Approx(arg0[3], arg0[5]) / 0.7853982f) & 7;
        lo = t - 2;
        hi = t + 2;
    }
    i = lo;
    if (hi >= lo) {
        do {
            n = (u8 *)((i & 7) * 0x5C + (s32)base);
            if (i != lo) {
                *(u8 **)(n + 4) = base + (((i - 1) & 7) * 0x5C + 0x2E0);
            } else {
                *(u8 **)(n + 4) = 0;
            }
            m = (u8 *)((i & 7) * 0x5C + (s32)base);
            *(u8 **)m = base + ((i & 7) * 0x5C + 0x2E0);
            *(u8 **)(m + 0x2E4) = m;
            if (i != hi) {
                *(u8 **)(m + 0x2E0) = base + ((i + 1) & 7) * 0x5C;
            } else {
                *(u8 **)(m + 0x2E0) = 0;
            }
            i++;
        } while (hi >= i);
    }
    *(u8 **)(*(u8 **)(arg1 + 0x18) + 0x1C) = arg1 + ((lo & 7) * 0x5C + 0x1C);
}

INCLUDE_ASM("asm/nonmatchings/main/5AD20", setupWalkerSpriteTileQuad);

typedef struct {
    f32 x, y, z;
} CwV3;

typedef struct {
    u8 pad0[0x10];
    f32 f10;
    f32 f14;
    f32 f18;
} CwCam;

typedef struct {
    u8 pad0[0x38];
    f32 f1C;
    u8 pad20[0x5C - 0x3C];
} CwSeg;

typedef struct {
    s32 w0;
    f32 f4;
    f32 f8;
    f32 fC;
    u8 pad10[8];
    u8 *mesh;
    u8 pad1C[0xED4 - 0x1C];
    u8 *m[2];
    s32 n;
    CwV3 off[2];
    f32 scale[2];
    u8 *pF00;
    CwV3 vF04;
    s32 wF10;
} CwW;

typedef struct {
    u8 pad0[4];
    void *w;
} CwNpc;

typedef struct {
    u8 pad[0x48];
    CwCam *cam;
} CwCamSet;

extern u8 D_main_bss_80130B38;
extern u8 D_main_bss_80130B39;
extern u8 D_main_bss_80130B63;
extern struct { u8 b0; } gGameSettings;
extern u32 gCurrentLevel;
extern CwCamSet D_main_bss_80136DC0;
extern CwCam *D_main_bss_80136E08;
extern u8 *D_main_bss_80138D1C;
extern char D_main_8003AE10[];

void *rs_malloc(s32, s32);
void rs_free(void *);
s32 sprintf(char *, const char *, ...);
s32 isCraftAvailableByIdx(s32);
void load_hmt_and_hob(char *, s32, s32, s32);
void *walkMeshdef0List(char *);
void loadSkyHorizonHob(CwW *);
void loadTopCloudsAsset(CwW *);
f32 getLevelConfigFloatA(void);
f32 getLevelConfigFloatB(void);
void normalize_vector(f32 *);
void initVec4TripletFromArgs(void *, s32, s32, s32);
void cwInitF(void *, f32, f32, f32) __asm__("initVec4TripletFromArgs");
void composeRotationMatrixSlot0(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
void composeRotationMatrixSlot2(void *, f32);
void rotateVec3ByMat3x3(f32 *, f32 *, f32 *);
void applyFlagsToMeshTreeOrList(void *, s32, s32, s32);
void releaseMeshAsset(void *);
void extractOrthonormalFrameFromStruct(f32 *, void *);
void orthonormalizeFrame(f32 *);
void mat34CrossRowsAndCopyPos(void *, f32 *, f32);
void updateWalkerParticlePositions(void *, void *, CwW *, f32 *, f32 *);
void addVec3At0x24(void *, f32, f32, f32);
void setupWalkerSpriteTileQuad(void *, CwW *, f32 *);

#define CW_SQRT(out, in) __asm__ volatile("sqrt.s %0, %1" : "=f"(out) : "f"(in))

static __inline__ void cwOrient(f32 *v, f32 *out, CwCam *cam, f32 zero, f32 k, f32 r0, f32 r2, f32 r1) {
    f32 m[12];
    f32 sq;

    v[0] = -*(f32 *)((u8 *)cam + 0x10);
    v[2] = -*(f32 *)((u8 *)cam + 0x18);
    if (v[0] == zero) {
        v[0] = 1.0f;
    }
    CW_SQRT(sq, v[0] * v[0] + v[2] * v[2]);
    v[1] = -sq / k;
    normalize_vector(v);
    cwInitF(m, 18.0f, 18.0f, 18.0f);
    composeRotationMatrixSlot0(m, r0);
    composeRotationMatrixSlot2(m, r2);
    composeRotationMatrixSlot1(m, r1);
    rotateVec3ByMat3x3(m, v, out);
}

s32 cinematicSplineWalkerNpcHandler(u8 *arg0, u16 action, u8 **arg2) {
    char buf[0x28];
    f32 v[4];
    CwW *w;
    s32 i;
    f32 zero;
    f32 k;
    u8 *mesh;
    u8 *node;
    u8 *head;
    char *name;
    u8 **a2;

    w = *(CwW **)(arg0 + 4);
    switch (action) {
    case 1:
        w = rs_malloc(0xF14, 0);
        ((CwNpc *)arg0)->w = w;
        i = gGameSettings.b0;
        if (D_main_bss_80130B39 != 0) {
            if (i == 0x13) {
                i = 0;
            }
            if (D_main_bss_80130B38 != 0) {
                i = 0x11;
            }
        }
        switch (i) {
        case 9:
            i = 8;
            break;
        case 0x10:
            i = 0;
            break;
        case 0x11:
            i = 5;
            break;
        case 0x14:
            i = 1;
            break;
        }
        sprintf(buf, "level/sky_%c", (i < 10) ? i + '0' : i + 'W');
        load_hmt_and_hob(buf, 0, isCraftAvailableByIdx(0) != 0 ? 2 : 0, 0);
        w->mesh = walkMeshdef0List(D_main_8003AE10);
        loadSkyHorizonHob(w);
        if (D_main_bss_80130B39 != 0 && D_main_bss_80130B38 != 0) {
            w->f8 = 7.0f;
            w->fC = 1.5f;
        } else {
            zero = 18.0f;
            w->f8 = getLevelConfigFloatA() * zero / zero;
            w->fC = getLevelConfigFloatB() * zero / zero;
        }
        w->w0 = 0;
        w->n = 0;
        w->pF00 = NULL;
        switch (gCurrentLevel) {
        case 10:
            loadTopCloudsAsset(w);
            break;
        case 5:
            if (D_main_bss_80130B63 != 0 || D_main_bss_80130B39 != 0) {
                name = "gnrc_stuff/1ade_moon";
            } else {
                name = "gnrc_stuff/jade_moon";
            }
            load_hmt_and_hob(name, 0, 0, 0);
            *(u8 **)((u8 *)w + 0xED4) = walkMeshdef0List("jade_moon");
            zero = 0.0f;
            k = 2.0f;
            cwOrient(v, &w->off[0].x, D_main_bss_80136E08, zero, k, zero, 13.0f, zero);
            w->scale[0] = k;
            applyFlagsToMeshTreeOrList(w->m[0], 0, 0x470000, 0);
            w->n = 1;
            break;
        case 0:
        case 0x10:
            load_hmt_and_hob("gnrc_stuff/tat_sun", 0, 0, 0);
            *(u8 **)((u8 *)w + 0xED4) = walkMeshdef0List("tat_sun");
            zero = 0.0f;
            k = 1.8f;
            cwOrient(v, &w->off[0].x, D_main_bss_80136DC0.cam, zero, k, zero, zero, zero);
            w->scale[0] = 1.4f;
            applyFlagsToMeshTreeOrList(w->m[0], 0, 0x9070000, 0);
            w->m[1] = walkMeshdef0List("tat_sun2");
            cwOrient(v, &w->off[1].x, D_main_bss_80136DC0.cam, zero, k, -10.0f, zero, 15.0f);
            w->scale[1] = 1.5f;
            applyFlagsToMeshTreeOrList(w->m[1], 0, 0x9070000, 0);
            w->n = 2;
            break;
        case 1:
            load_hmt_and_hob("gnrc_stuff/bark_moon", 0, 0, 0);
            *(u8 **)((u8 *)w + 0xED4) = walkMeshdef0List("moon");
            zero = 0.0f;
            cwOrient(v, &w->off[0].x, D_main_bss_80136E08, zero, 1.8f, 5.0f, zero, 30.0f);
            w->scale[0] = 1.0f;
            applyFlagsToMeshTreeOrList(w->m[0], 0, 0x70000, 0);
            w->n = 1;
            break;
        }
        w->vF04 = *(CwV3 *)&D_main_bss_80136E08->f10;
        w->wF10 = 0;
        break;
    case 2:
        for (i = 0; i < w->n; i++) {
            releaseMeshAsset(w->m[i]);
        }
        releaseMeshAsset(w->mesh);
        if (w->pF00 != NULL) {
            rs_free(*(void **)(w->pF00 + 0x2B44));
            rs_free(w->pF00);
        }
        break;
    case 3:
        break;
    case 4: {
        f32 m[12];
        f32 fr[12];

        a2 = arg2;
        extractOrthonormalFrameFromStruct(m, D_main_bss_80138D1C + 0x28);
        if (w->mesh != NULL) {
            w->f4 = 18.0f;
            for (i = 0; i < 16; i++) {
                ((CwSeg *)w)[i].f1C = *(f32 *)(*a2 + 0x28) - 0.2f;
            }
            v[0] = m[0];
            v[1] = m[1] / w->fC + w->f8;
            v[2] = m[2];
            for (i = 0; i < w->n; i++) {
                node = w->m[i] + 0xC;
                fr[0] = v[0] + w->off[i].x;
                fr[1] = v[1] + w->off[i].y;
                fr[2] = v[2] + w->off[i].z;
                fr[3] = -(fr[0] - m[0]);
                fr[4] = -(fr[1] - m[1]);
                fr[5] = -(fr[2] - m[2]);
                if (gCurrentLevel == 0) {
                    fr[6] = m[6];
                    fr[7] = m[7];
                    fr[8] = m[8];
                } else {
                    fr[6] = 0.0f;
                    fr[8] = 0.0f;
                    fr[7] = 1.0f;
                }
                orthonormalizeFrame(fr);
                mat34CrossRowsAndCopyPos(node + 0x1C, fr, w->scale[i]);
                head = *(u8 **)a2[1];
                *(u8 **)node = head;
                if (head != NULL) {
                    *(u8 **)(head + 4) = node;
                }
                *(u8 **)a2[1] = node;
                *(u8 **)(node + 4) = NULL;
            }
            if (w->pF00 != NULL) {
                updateWalkerParticlePositions(a2[1], a2[0], w, m, v);
            }
            mesh = w->mesh;
            node = mesh + 0x28;
            initVec4TripletFromArgs(node, *(s32 *)&w->f4, *(s32 *)&w->f4, *(s32 *)&w->f4);
            addVec3At0x24(node, v[0], v[1], v[2]);
            linkDirectionalTrailSegments(m, (u8 *)w);
            setupWalkerSpriteTileQuad(a2, w, m);
            node = mesh + 0xC;
            head = *(u8 **)a2[1];
            *(u8 **)node = head;
            if (head != NULL) {
                *(u8 **)(head + 4) = node;
            }
            *(u8 **)a2[1] = node;
            *(u8 **)(node + 4) = NULL;
        }
        break;
    }
    }
    return 1;
}

extern s16 D_main_bss_80139560[];

s16 allocateNpcSlot(void *);

void allocAllInitialNpcSlots(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        D_main_bss_80139560[i] = allocateNpcSlot(NULL);
    }
}

INCLUDE_ASM("asm/nonmatchings/main/5AD20", fake_func_8005C61C);
