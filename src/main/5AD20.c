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

typedef struct {
    f32 offX;
    f32 speed;
    f32 scrollX;
    f32 scrollZ;
    f32 prevX;
    f32 prevZ;
    u8 grid[4][4];
} WpCell;

typedef struct WpNode {
    struct WpNode *next;
    struct WpNode *prev;
} WpNode;

extern f32 floatModulo(f32, f32);
extern f32 sinf(f32);
s16 rand(void);
extern u8 transformVec3ToNpcLocalWithScale(s32, s32, f32 *, f32, void *);
extern void addVec3At0x24(void *, f32, f32, f32);
extern void initVec4TripletFromArgs_l(void *, f32, f32, f32) __asm__("initVec4TripletFromArgs");
extern void mat3x4Multiply(void *, void *, void *);
extern void normalize_vector(f32 *);
extern void quatFromAxisAngle(void *, f32 *, f32);
extern void quatToRotationMatrix(void *, void *);
extern f32 sinfApprox(f32);

void updWPP(WpNode **, s32, u8 *, f32 *, f32 *) __asm__("updateWalkerParticlePositions");
void updWPP(WpNode **head, s32 arg1, u8 *arg2, f32 *arg3, f32 *arg4) {
    f32 pos[3];
    f32 m[12];
    f32 m2[12];
    f32 axis[4];
    f32 dir[4];
    f32 pad[4];
    f32 q[4];
    u8 *base;
    u8 *entries;
    s32 total;
    s32 k;
    s32 i;
    s32 j;
    f32 zero;
    f32 thirty;
    f32 angle;
    f32 x;
    f32 z;
    f32 v;
    WpCell *cell;
    u8 *g;
    u8 *e;
    WpNode *n;
    WpNode *h;
    s32 idx;
    s32 rb;
    s32 rc;

    zero = 0.0f;
    total = 0;
    k = 0;
    base = *(u8 **)(arg2 + 0xF00);
    thirty = 30.0f;
    entries = base + 0x20D0;
    do {
        cell = (WpCell *)(base + (k * 0x38 + 0x2BB0));
        pos[1] = arg4[1] + cell->offX;
        v = cell->scrollX + (arg4[0] * cell->speed - cell->prevX);
        cell->scrollX = v;
        if (v < zero) {
            cell->scrollX = thirty - floatModulo(-v, thirty);
            for (i = 0; i < 4; i++) {
                for (j = 3; j > 0; j--) {
                    cell->grid[i][j] = cell->grid[i][j - 1];
                }
                cell->grid[i][0] = 0xFF;
            }
        } else if (thirty < v) {
            cell->scrollX = floatModulo(v, thirty);
            for (i = 0; i < 4; i++) {
                for (j = 1; j < 4; j++) {
                    cell->grid[i][j - 1] = cell->grid[i][j];
                }
                cell->grid[i][j - 1] = 0xFF;
            }
        }
        cell->prevX = arg4[0] * cell->speed;
        v = cell->scrollZ + (arg4[2] * cell->speed - cell->prevZ);
        cell->scrollZ = v;
        if (v < zero) {
            cell->scrollZ = thirty - floatModulo(-v, thirty);
            for (i = 3; i > 0; i--) {
                for (j = 0; j < 4; j++) {
                    cell->grid[i][j] = cell->grid[i - 1][j];
                }
            }
            for (j = 0; j < 4; j++) {
                cell->grid[0][j] = 0xFF;
            }
        } else if (thirty < v) {
            cell->scrollZ = floatModulo(v, thirty);
            for (i = 1; i < 4; i++) {
                for (j = 0; j < 4; j++) {
                    cell->grid[i - 1][j] = cell->grid[i][j];
                }
            }
            for (j = 0; j < 4; j++) {
                cell->grid[0][j + 12] = 0xFF;
            }
        }
        cell->prevZ = arg4[2] * cell->speed;
        __asm__ volatile("abs.s %0, %1" : "=f"(v) : "f"(arg3[4]));
        if (v < 0.999f) {
            f32 b;
            f32 c;
            c = 1.0f;
            angle = c - sinfApprox(v) * 0.63661975f;
            b = 0.5f;
            angle = (c - sinf((b - angle) * 3.1415927f)) * b;
            dir[0] = arg3[3];
            dir[1] = 0.0f;
            dir[2] = arg3[5];
            normalize_vector(dir);
            axis[0] = dir[2];
            axis[1] = 0.0f;
            axis[2] = -dir[0];
            quatFromAxisAngle(q, axis, D_main_8009ECE0[k] * angle);
            quatToRotationMatrix(q, m);
            addVec3At0x24(m, arg3[0], arg3[1], arg3[2]);
        } else {
            angle = 0.0f;
        }
        z = -30.0f;
        for (j = 0; j < 16;) {
            if (total >= 50) {
                break;
            }
            i = 0;
            x = -30.0f;
            do {
                if (cell->grid[0][j] == 0xFF) {
                    cell->grid[0][j] = rand() % 7;
                }
                pos[0] = arg4[0] - cell->scrollX + x;
                pos[2] = arg4[2] - cell->scrollZ + z;
                if (transformVec3ToNpcLocalWithScale(arg1, 0, pos, 30.0f, NULL)) {
                    n = (WpNode *)(base + total * 0x4C);
                    e = base + total * 0x5C;
                    if (k >= 3) {
                        g = entries + (cell->grid[0][j] + 7) * 0x5C;
                    } else {
                        g = entries + cell->grid[0][j] * 0x5C;
                    }
                    *(u8 **)(e + 0xEE0) = g;
                    initVec4TripletFromArgs_l((u8 *)n + 0x1C, thirty, 1.0f, thirty);
                    addVec3At0x24((u8 *)n + 0x1C, pos[0], pos[1], pos[2]);
                    if (angle != zero) {
                        addVec3At0x24((u8 *)n + 0x1C, -arg3[0], -arg3[1], -arg3[2]);
                        mat3x4Multiply(m, (u8 *)n + 0x1C, (u8 *)n + 0x1C);
                    }
                    n->next = (h = *head);
                    if (h != NULL) {
                        h->prev = n;
                    }
                    total++;
                    n->prev = NULL;
                    *head = n;
                    if (total >= 50) {
                        break;
                        do { } while (0);
                    }
                }
                j++;
                i++;
                x += thirty;
            } while (i < 4);
            z += thirty;
        }
        k++;
    } while (k < 4);
}

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

void addVec3At0x24_l(Mat4x3, f32, f32, f32) __asm__("addVec3At0x24");
void buildRotationMatrixSlot1_l(Mat4x3, f32) __asm__("buildRotationMatrixSlot1");
void normalize_vector_l(Vec3f) __asm__("normalize_vector");
void transformVec3ByMat34_l(Mat4x3, Vec3f, Vec3f) __asm__("transformVec3ByMat34");

typedef struct SWView {
    u8 pad0[0x10];
    s32 w;
    s32 h;
    u8 pad18[4];
    s32 y0;
    f32 fov;
    u8 pad24[8];
    u8 cam[0xC];
    f32 f38;
    f32 f3c;
} SWView;

typedef struct SWBuf {
    s32 count;
    u8 *data;
} SWBuf;

typedef struct SWSrc {
    SWView *view;
    u8 pad4[0x10];
    SWBuf *buf;
} SWSrc;

typedef struct SWObj {
    u8 pad0[4];
    f32 f4;
    u8 pad8[4];
    f32 fC;
    f32 f10;
    f32 f14;
    u8 *p18;
} SWObj;

#define SW_SQRT(out, in) __asm__ volatile("sqrt.s %0, %1" : "=f"(out) : "f"(in))
#define SW_LO16(v, off) (*(u16 *)((u8 *)(v) + (off)))

u32 getBootConfigField12(void);
u32 getBootConfigField14(void);
f32 sqrtf(f32);
f32 cosf(f32);
f32 sinf(f32);

void setupWalkerSpriteTileQuad_d(SWSrc *arg0, SWObj *arg1, SWObj *arg2) __asm__("setupWalkerSpriteTileQuad");
void setupWalkerSpriteTileQuad_d(SWSrc *arg0, SWObj *arg1, SWObj *arg2) {
    struct {
        f32 v10[3];
        f32 pad1c;
        f32 v20[3];
        f32 pad2c;
        f32 v30[3];
        f32 pad3c;
        Mat4x3 m40;
    } l;
    f32 q[3][3];
    s32 s2 = (getBootConfigField14() & 0xFFFF) / 30 & 0xFFFF;
    s32 s7 = (getBootConfigField12() & 0xFFFF) / 20 & 0xFFFF;
    f32 fs1;
    f32 fs0;
    f32 len;
    f32 sq;
    f32 ang;
    f32 cot;
    f32 rot;
    s32 i;
    f32 *pp;
    u8 *ent;
    s32 t0;
    s32 t3;
    s32 a1;
    s32 a3;
    s32 e3;
    s32 ea;
    s32 ev;
    s32 e1;
    s32 hw;
    s32 hh;
    s32 y0;
    s32 t1;
    s32 a2;
    s32 va;
    s32 vv;
    s32 vt;
    f32 fx;
    f32 gx;
    f32 gy;
    f32 ga;
    f32 gb;
    f32 fy;
    f32 fa;
    f32 fb;

    sq = arg1->f14 * arg1->f14 + arg1->f10 * arg1->f10;
    SW_SQRT(len, sq);
    fs1 = len * arg1->f4;
    fx = arg2->fC;
    l.v10[0] = fx;
    l.v10[1] = 0.0f;
    fy = arg2->f14;
    fa = fx * fx;
    fb = fy * fy;
    l.v10[2] = fy;
    SW_SQRT(fs0, fa + fb);
    if (!(fs0 < 0.5f)) {
        l.v10[0] = fx / fs0;
        l.v10[1] = arg1->f10 / arg1->f14 / fs0;
        l.v10[2] = fy / fs0;
        normalize_vector_l(l.v10);
        l.v10[0] = l.v10[0] * fs1;
        l.v10[1] = l.v10[1] * fs1;
        l.v10[2] = l.v10[2] * fs1;
        fs1 = arg0->view->fov * 0.008726646f;
        fs0 = cosf(fs1) / sinf(fs1);
        for (i = 0; i < 3; i++) {
            buildRotationMatrixSlot1_l(l.m40, (i == 0) ? -25.0f : (i == 2) ? 25.0f : 0.0f);
            addVec3At0x24_l(l.m40, ((f32 *)arg1->p18)[0x4C / 4], ((f32 *)arg1->p18)[0x50 / 4], ((f32 *)arg1->p18)[0x54 / 4]);
            transformVec3ByMat34_l(l.m40, l.v10, l.v20);
            transformVec3ByMat34_l((void *)arg0->view->cam, l.v20, l.v30);
            q[i][0] = l.v30[0] * fs0 / l.v30[2] * 0.75f;
            q[i][1] = l.v30[1] * fs0 / l.v30[2];
            q[i][2] = l.v30[2];
        }
        hw = arg0->view->w / 2;
        gx = (f32)hw;
        hh = arg0->view->h / 2;
        gy = (f32)hh;
        ent = arg0->buf->data + arg0->buf->count * 8;
        t0 = gx + gx * q[0][3];
        t3 = gy + gy * q[0][4];
        __asm__ volatile("abs.s %0, %1" : "=f"(gb) : "f"(arg0->view->f3c));
        __asm__ volatile("abs.s %0, %1" : "=f"(ga) : "f"(arg0->view->f38));
        if (ga < gb) {
            if (t0 & 3) {
                t0 = (t0 + 4) & 0xFFFC;
            }
            a3 = (f32)t3 - (f32)t0 * ((q[0][4] - q[0][1]) / (q[0][3] - q[0][0]));
            a1 = (f32)t3 + (f32)(arg0->view->w - t0) * ((q[0][7] - q[0][4]) / (q[0][6] - q[0][3]));
            y0 = arg0->view->y0;
            a2 = y0 - hh;
            t1 = y0 + hh;
            if (q[0][0] < q[0][6]) {
                t3 -= s2;
                if (t3 < a2) {
                    t3 = a2;
                } else if (t3 >= t1) {
                    t3 = t1 - 1;
                }
                a1 -= s2;
                if (a1 < a2) {
                    a1 = a2;
                } else if (a1 >= t1) {
                    a1 = t1 - 1;
                }
                a3 -= s2;
                if (a3 < a2) {
                    a3 = a2;
                } else if (a3 >= t1) {
                    a3 = t1 - 1;
                }
                s2 = t1 - arg0->view->h / 10;
                if (s2 < a3) {
                    a3 = s2;
                }
                if (s2 < a1) {
                    a1 = s2;
                }
                *(s16 *)(ent + 0) = t0;
                *(s16 *)(ent + 4) = SW_LO16(arg0->view, 0x12) - 1;
                va = t3;
                if (a1 < t3) {
                    va = a1;
                }
                vv = t3;
                *(s16 *)(ent + 2) = va;
                vt = t1 - 1;
                *(s16 *)(ent + 6) = vt;
                *(s16 *)(ent + 0xC) = t0 - 1;
                *(s16 *)(ent + 8) = 0;
                if (a3 < vv) {
                    vv = a3;
                }
                *(s16 *)(ent + 0xA) = vv;
                *(s16 *)(ent + 0xE) = vt;
            } else {
                t3 += s2;
                if (t3 < a2) {
                    t3 = a2;
                } else if (t3 >= t1) {
                    t3 = t1 - 1;
                }
                a1 += s2;
                if (a1 < a2) {
                    a1 = a2;
                } else if (a1 >= t1) {
                    a1 = t1 - 1;
                }
                a3 += s2;
                if (a3 < a2) {
                    a3 = a2;
                } else if (a3 >= t1) {
                    a3 = t1 - 1;
                }
                s2 = a2 + arg0->view->h / 10;
                if (a3 < s2) {
                    a3 = s2;
                }
                if (a1 < s2) {
                    a1 = s2;
                }
                *(s16 *)(ent + 0) = t0;
                *(s16 *)(ent + 4) = SW_LO16(arg0->view, 0x12) - 1;
                *(s16 *)(ent + 2) = a2;
                va = t3;
                if (t3 < a1) {
                    va = a1;
                }
                vv = t3;
                *(s16 *)(ent + 6) = va;
                *(s16 *)(ent + 8) = 0;
                *(s16 *)(ent + 0xC) = t0 - 1;
                *(s16 *)(ent + 0xA) = a2;
                if (vv < a3) {
                    vv = a3;
                }
                *(s16 *)(ent + 0xE) = vv;
            }
        } else {
            e3 = (f32)t0 - (f32)t3 * ((q[0][3] - q[0][0]) / (q[0][4] - q[0][1]));
            e1 = (f32)t0 + (f32)(arg0->view->h - t3) * ((q[0][6] - q[0][3]) / (q[0][7] - q[0][4]));
            if (q[0][1] < q[0][7]) {
                t0 += s2;
                if (t0 < 0) {
                    t0 = 0;
                } else if (t0 >= arg0->view->w) {
                    t0 = arg0->view->w - 1;
                }
                e3 += s7;
                if (e3 < 0) {
                    e3 = 0;
                } else if (e3 >= arg0->view->w) {
                    e3 = arg0->view->w - 1;
                }
                e1 += s7;
                if (e1 < 0) {
                    e1 = 0;
                } else if (e1 >= arg0->view->w) {
                    e1 = arg0->view->w - 1;
                }
                if (t0 & 3) {
                    t0 = (t0 + 4) & 0xFFFC;
                }
                if (e3 & 3) {
                    e3 = (e3 + 4) & 0xFFFC;
                }
                if (e1 & 3) {
                    e1 = (e1 + 4) & 0xFFFC;
                }
                *(s16 *)(ent + 0) = 0;
                *(s16 *)(ent + 4) = ((t0 < e3) ? e3 : t0) - 1;
                *(s16 *)(ent + 2) = 0;
                *(s16 *)(ent + 6) = t3;
                *(s16 *)(ent + 8) = 0;
                *(s16 *)(ent + 0xC) = ((t0 < e1) ? e1 : t0) - 1;
                *(s16 *)(ent + 0xA) = t3 + 1;
            } else {
                t0 -= s2;
                if (t0 < 0) {
                    t0 = 0;
                } else if (t0 >= arg0->view->w) {
                    t0 = arg0->view->w - 1;
                }
                e3 -= s7;
                if (e3 < 0) {
                    e3 = 0;
                } else if (e3 >= arg0->view->w) {
                    e3 = arg0->view->w - 1;
                }
                e1 -= s7;
                if (e1 < 0) {
                    e1 = 0;
                } else if (e1 >= arg0->view->w) {
                    e1 = arg0->view->w - 1;
                }
                t0 &= 0xFFFC;
                e3 &= 0xFFFC;
                e1 &= 0xFFFC;
                ea = t0;
                if (e3 < t0) {
                    ea = e3;
                }
                *(s16 *)(ent + 0) = ea;
                *(s16 *)(ent + 4) = SW_LO16(arg0->view, 0x12) - 1;
                ev = t0;
                *(s16 *)(ent + 2) = 0;
                *(s16 *)(ent + 6) = t3;
                if (e1 < ev) {
                    ev = e1;
                }
                *(s16 *)(ent + 8) = ev;
                *(s16 *)(ent + 0xC) = SW_LO16(arg0->view, 0x12) - 1;
                *(s16 *)(ent + 0xA) = t3 + 1;
            }
            *(s16 *)(ent + 0xE) = SW_LO16(arg0->view, 0x16) - 1;
        }
        arg0->buf->count = arg0->buf->count + 2;
    }
}

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
