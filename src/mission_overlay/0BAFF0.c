#include "common.h"

#include "common_types.h"
#include "mission_overlay/0BAFF0.h"
#include "rs_math.h"

typedef struct {
    s32 f00;
    f32 f04;
} FalconInitArg;

typedef struct {
    s32 f00;
    u8 p04[0xB4 - 4];
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
    u8 p10C[4];
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
    f32 f164;
    f32 f168;
    u8 p16C[4];
    s32 f170;
    f32 f174;
    u8 p178[8];
    s16 f180;
    u8 p182[0x2A0 - 0x182];
} FalconInitPlayer;

extern FalconInitPlayer gFalconInitPlayers[] __asm__("D_main_bss_80137DBC");
extern u32 D_main_bss_80130B58;
void initPlayerCraftMovementMode(FalconInitPlayer *);
typedef struct {
    u8 p00[0x18];
    u16 f18;
    u8 p1A[0x24 - 0x1A];
} FalconCueRec;
extern FalconCueRec Dfcr8010BE18[] __asm__("D_mission_overlay_8010BE18");
extern s32 D_mission_overlay_8010BEA8[][16];
s32 countTrailingZeros16(u16);
void bindFalconSubmodelMaterials(FalconInitPlayer *, FalconInitArg *);


void pfImpl(FalconInitArg *, s32, s16) __asm__("playerFalconInit");
void pfImpl(FalconInitArg *arg0, s32 arg1, s16 arg2) {
    FalconInitPlayer *p;
    f32 fs5;

    p = &gFalconInitPlayers[arg1];
    p->f180 = arg2;
    arg0->f00 = arg1;
    p->fB4 = 5;
    initPlayerCraftMovementMode(p);
    fs5 = 400.0f;
    if (D_main_bss_80130B58 & 0x40) {
        fs5 = 40.0f;
    }
    p->fC0 = fs5;
    p->fC4 = fs5;
    p->fE8 = 3.0f;
    p->fEC = 3.0f;
    arg0->f04 = 1.0f;
    p->fF0 = 0.0625f;
    p->fF4 = 0.03125f;
    p->fF8 = 1.3f;
    p->fFC = 2.0f;
    p->f104 = 15.0f;
    p->f108 = 10.0f;
    p->f14C = p->f13C = 0;
    p->f110 = -30.0f;
    p->f114 = -45.0f;
    p->f118 = 40.0f;
    p->f120 = 60.0f;
    p->f124 = 180.0f;
    p->f130 = 0.75f;
    p->f134 = 2.0f;
    p->f138 = 20.0f;
    p->f140 = 10.0f;
    p->f144 = 60.0f;
    p->f148 = 10.0f;
    p->f154 = 40.0f;
    p->f11C = 0;
    p->f128 = 0.1f;
    p->f12C = 0.1f;
    p->fE0 = p->fDC = p->fD8 = 0;
    p->f158 = 0;
    p->f150 = 5.0f;
    p->f160 = 0;
    p->f164 = 0.1f;
    p->f170 = 0;
    p->f174 = 0.1f;
    p->f168 = 0.5f;
    D_mission_overlay_8010BEA8[arg0->f00][countTrailingZeros16(Dfcr8010BE18[arg0->f00].f18)] = 0;
    bindFalconSubmodelMaterials(p, arg0);
}

typedef struct {
    u8 pad0[0x12];
    u16 maskA;
    u8 pad14[4];
    u16 maskB;
    u8 pad1A[0xA];
} FfCfg;

typedef struct {
    u8 pad0[0xB8];
    s32 owner;
    u8 padBC[0xE8 - 0xBC];
    f32 fE8;
    f32 fEC;
    f32 fF0;
    f32 fF4;
    u8 padF8[0x180 - 0xF8];
    u16 flags;
    u8 pad182[0x2A0 - 0x182];
} FfCraft;

typedef struct {
    s32 index;
    f32 scale;
} FfArg;

extern u8 ffCraftB[][0x2A0] __asm__("D_main_bss_80137DBC");
extern u16 ffB88[][3] __asm__("D_main_bss_80130B88");
extern FfCfg ffCfg[] __asm__("D_mission_overlay_8010BE18");
extern u8 ffD800C[][0x2A0] __asm__("D_main_bss_8013800C");
extern s32 getCraftAnimationSlotFlag(s32);
extern f32 getCraftAnimationSlotValue(s32);
extern void setCraftAnimationSlotParams(s32, s32, f32);
extern void updatePlayerCraftPhysics(void *, f32);
extern void computeBootConfigScaledVec4(s32, f32, f32, void *, f32, f32);

void ffImpl(FfArg *arg0, f32 dt) __asm__("computeFalconFlightTransform");
void ffImpl(FfArg *arg0, f32 dt) {
    FfCraft *c;
    f32 fs0;
    f32 sc;
    f32 t;
    f32 e8;
    f32 lim;
    u16 bits;
    register f32 *tb asm("$16");
    register FfCfg *cf asm("$19");

    c = (FfCraft *)ffCraftB[arg0->index];
    if (*(u16 *)((s32)ffCraftB + c->owner * 0x2A0 + 0x180) & 1) {
        fs0 = c->fEC;
        sc = 0.65625f;
        if ((ffB88[arg0->index][0] & ffCfg[arg0->index].maskA) && !(ffB88[arg0->index][0] & ffCfg[arg0->index].maskB)) {
            sc = 0.0f;
            fs0 -= 0.09375f;
        }
        {
            f32 t1 = arg0->scale * 2.25f;
            if (fs0 < t1) {
                fs0 = t1;
            }
        }
        { s32 hi; __asm__("lui %0, %%hi(D_mission_overlay_8010BE18)" : "=r"(hi)); __asm__("addiu %0, %1, %%lo(D_mission_overlay_8010BE18)" : "=r"(cf) : "r"(hi)); }
        {
            s32 k = countTrailingZeros16(cf[arg0->index].maskB);
            tb = (f32 *)D_mission_overlay_8010BEA8;
            fs0 += *(f32 *)((k << 2) + (arg0->index << 6) + (s32)tb) * 0.1875f;
        }
        countTrailingZeros16(cf[arg0->index].maskB);
        {
        s32 ii;

        do {
            ii = arg0->index;
        } while (0);
        if (ffB88[ii][0] & cf[ii].maskB) {
            if (!(u8)getCraftAnimationSlotFlag(0)) {
                setCraftAnimationSlotParams(0, 1, 0.0f);
            }
        } else if ((u8)getCraftAnimationSlotFlag(0) == 1) {
            if (getCraftAnimationSlotValue(0) == 0.0f) {
                setCraftAnimationSlotParams(0, 1, 0.5f);
            }
        }
        }
        bits = ffB88[arg0->index][0];
        if (!(bits & ffCfg[arg0->index].maskA) && !(bits & ffCfg[arg0->index].maskB) && c->fE8 < 3.0f) {
            f32 t2 = arg0->scale * 3.0f;
            fs0 += 0.09375f;
            if (t2 < fs0) {
                fs0 = t2;
            }
        }
        {
            register f32 t3 asm("$f2") = arg0->scale * 5.625f;
            if (t3 < fs0) {
                fs0 = t3;
            }
        }
        {
            f32 e8a = c->fE8;
            f32 la = c->fF0;
            c->fEC = fs0;
            if (la < fs0 - e8a) {
                c->fE8 = e8a + la;
            } else {
                c->fE8 = fs0;
            }
        }
        e8 = c->fE8;
        lim = c->fF4;
        if (fs0 - e8 < -lim) {
            c->fE8 = e8 - lim;
        } else {
            c->fE8 = fs0;
        }
        __asm__("" :: "f"(sc));
        arg0->scale = 1.0f;
    }
    updatePlayerCraftPhysics(c, dt);
    sc = 0.65625f;
    t = arg0->scale;
    computeBootConfigScaledVec4(arg0->index, sc, sc, ffD800C[arg0->index], (c->fE8 - t * 2.25f) / (t * 3.375f) + 1.0f, dt);
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BAFF0", D_mission_overlay_800A5E00);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BAFF0", D_mission_overlay_800A5E04);

typedef struct {
    s32 unk0;
    u8 pad4[0x28 - 4];
    u8 unk28[4];
    u8 pad2C[0xB6 - 0x2C];
    u16 unkB6;
    u8 padB8[0x16C - 0xB8];
    f32 unk16C;
    u8 pad170[0x2A0 - 0x170];
} FalconEngPlayer;

extern FalconEngPlayer D_main_bss_80137DBC[];
extern s32 D_mission_overlay_80109998[];
extern u8 D_mission_overlay_801099A0[];
extern u8 gGameSettings;
void lookupHmtTextureByName(s32, s32, s32, void *, void *, s32);
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void playSpeechClipOncePerLevel(s32, s32);

void triggerFalconEngineEffect(s32 *arg0, s32 arg1) {
    u8 sp28[0x30];
    u8 sp58[0x30];
    s32 *s3;
    s32 *tbl;
    FalconEngPlayer *s0;
    s32 a0;

    tbl = D_mission_overlay_80109998;
    s3 = tbl + (arg1 & 0xFF);
    s0 = &D_main_bss_80137DBC[*arg0];
    lookupHmtTextureByName(s0->unk0, *s3, 0, sp28, sp58, 0);
    dispatchCueByCategory(0, s0->unkB6, sp28, D_mission_overlay_801099A0, 1, 12.5f, s0->unk16C);
    lookupHmtTextureByName(s0->unk0, *s3, 1, sp28, sp58, 1);
    dispatchCueByCategory(0, s0->unkB6, sp28, D_mission_overlay_801099A0, 1, 12.5f, s0->unk16C);
    play3DSoundEvent(0, sp28, s0->unk28, 20.0f, 0.2f, 0, 0x2F, 0x6E, 0x3C);
    a0 = 0x28C;
    if (gGameSettings != 0xF) {
        a0 = 0x133;
    }
    playSpeechClipOncePerLevel(a0, 9);
}

typedef struct BfsNode {
    u8 pad0[8];
    struct BfsNode *parent;
    u8 padC[0x10];
    f32 m[12];
} BfsNode;
typedef struct { u32 flags; s32 x, y, z; } BfsDefPos;
typedef struct {
    u8 pad0[0x4C];
    u32 flags;
    struct { s32 x, y, z; } pos;
} BfsDef;
typedef struct { f32 m[12]; } BfsMat;
typedef struct { s32 x, y, z; } BfsV3i;
typedef struct {
    u8 pad0[8];
    BfsDef *def[4];
    BfsNode *node[4];
    u16 lock[2];
    BfsMat mat[2];
    f32 pos[2][3];
    f32 tYaw[2];
    f32 cYaw[2];
    f32 tPit[2];
    f32 cPit[2];
} BfsTur;
BfsNode *lookupHmtMaterialByName(s32, char *, BfsDef **);
void mat3x4Multiply(void *, void *, void *);
void clearVec4QuadStruct(void *);

void bfsImpl(FalconInitPlayer *p, BfsTur *t) __asm__("bindFalconSubmodelMaterials");
void bfsImpl(FalconInitPlayer *p, BfsTur *t) {
    BfsMat tmp;
    BfsNode *n;
    BfsMat *m;

    t->node[0] = lookupHmtMaterialByName(p->f00, "top_trns", &t->def[0]);
    t->node[1] = lookupHmtMaterialByName(p->f00, "rohr_t_1", &t->def[1]);
    t->node[2] = lookupHmtMaterialByName(p->f00, "top_tr_2", &t->def[2]);
    t->node[3] = lookupHmtMaterialByName(p->f00, "rohr_t_2", &t->def[3]);
    m = &t->mat[0];
    n = t->node[0];
    {
    u8 *root = (u8 *)p->f00 + 0xC;
    clearVec4QuadStruct(m);
    for (n = n->parent; n != NULL; n = n->parent) {
        if ((u8 *)n == root) {
            break;
        }
        tmp = *m;
        mat3x4Multiply(n->m, &tmp, m);
    }
    }
    m = &t->mat[1];
    n = t->node[2];
    {
    u8 *root = (u8 *)p->f00 + 0xC;
    clearVec4QuadStruct(m);
    for (n = n->parent; n != NULL; n = n->parent) {
        if ((u8 *)n == root) {
            break;
        }
        tmp = *m;
        mat3x4Multiply(n->m, &tmp, m);
    }
    }
    if (t->def[0]->flags & 1) {
        *(BfsV3i *)t->pos[0] = *(BfsV3i *)&t->def[0]->pos;
    } else {
        t->pos[0][0] = t->pos[0][1] = t->pos[0][2] = 0.0f;
    }
    if (t->def[2]->flags & 1) {
        *(BfsV3i *)t->pos[1] = *(BfsV3i *)&t->def[2]->pos;
    } else {
        t->pos[1][0] = t->pos[1][1] = t->pos[1][2] = 0.0f;
    }
    t->lock[0] = t->lock[1] = 0xFFFF;
    t->tYaw[0] = t->tYaw[1] = t->cYaw[0] = t->cYaw[1] = 0.0f;
    t->tPit[0] = t->tPit[1] = t->cPit[0] = t->cPit[1] = 0.0f;
}

typedef struct {
    u8 pad0[0x4C];
    u32 flags;
    f32 f50, f54, f58;
    s32 w5C, w60, w64;
    u8 q68[0x10];
    f32 f78, f7C, f80;
} PfDef;

typedef struct {
    u8 pad0[8];
    PfDef *def[4];
    u8 *node[4];
    u16 lock[2];
    f32 mat[2][12];
    f32 pos[2][3];
    f32 tYaw[2];
    f32 cYaw[2];
    f32 tPit[2];
    f32 cPit[2];
} PfTur;

u16 pfLock(void *src, f32 *out, u16 cur, f32 range, f32 minDot, f32 lead, u8 mode) __asm__("acquireLockOnTarget");
f32 pfNorm(f32 *) __asm__("normalize_vector");
f32 pfCms(f32) __asm__("constMinusSinfApprox");
void pfMul(void *, void *, void *) __asm__("mat3x4Multiply");
void pfInv(void *, void *) __asm__("mat3x3InverseInto");
void pfXf(void *, void *, void *) __asm__("transformVec3ByMat34");
void pfClr(void *) __asm__("clearVec4QuadStruct");
void pfAdd(void *, f32, f32, f32) __asm__("addVec3At0x24");
void pfScl(void *, s32, s32, s32) __asm__("applyScaleToMat3x4");
void pfQuat(void *, void *) __asm__("composeQuatToMat3x4");
void pfRot0(void *, f32) __asm__("composeRotationMatrixSlot0");
void pfRot1(void *, f32) __asm__("composeRotationMatrixSlot1");

#define PF_SUB(NODE, DEF, ANG, ROT) \
    { \
        u8 *m; \
        PfDef *d; \
        f32 ang; \
        m = (NODE) + 0x1C; \
        d = (DEF); \
        ang = (ANG); \
        pfClr(m); \
        if (d->flags & 1) { \
            pfAdd(m, -d->f50, -d->f54, -d->f58); \
        } \
        if (d->flags & 2) { \
            pfScl(m, d->w5C, d->w60, d->w64); \
        } \
        if (d->flags & 4) { \
            pfQuat(m, d->q68); \
        } \
        ROT(m, ang); \
        { \
            u32 fl = d->flags; \
            if ((fl & 9) == 9) { \
                pfAdd(m, d->f78 + d->f50, d->f7C + d->f54, d->f80 + d->f58); \
            } else if ((fl & 9) == 8) { \
                pfAdd(m, d->f78, d->f7C, d->f80); \
            } else if (fl & 1) { \
                pfAdd(m, d->f50, d->f54, d->f58); \
            } \
        } \
    }

#define PF_STEP(CF, TF) \
    { \
        f32 cur, tgt, d, s; \
        cur = t->CF[i]; \
        tgt = t->TF[i]; \
        d = tgt - cur; \
        if (fabsfInline(d) > 0.35f) { \
            if (cur < tgt) { \
                if (d > 180.0f) { \
                    s = dt * -70.0f; \
                } else { \
                    s = dt * 70.0f; \
                } \
            } else { \
                if (cur - tgt > 180.0f) { \
                    s = dt * 70.0f; \
                } else { \
                    s = dt * -70.0f; \
                } \
            } \
            cur += s; \
            if (cur < 0.0f) { \
                cur += 360.0f; \
            } else if (cur > 360.0f) { \
                cur -= 360.0f; \
            } \
        } else { \
            cur = tgt; \
        } \
        t->CF[i] = cur; \
    }

void pfmuImpl(s32 *arg0, PfTur *t, f32 dt) __asm__("playerFalconMainUpdate");
void pfmuImpl(s32 *arg0, PfTur *t, f32 dt) {
    f32 sp20[4];
    f32 sp30[4];
    f32 v[4];
    f32 sp50[12];
    f32 sp80[12];
    u32 i;
    u16 r;
    f32 y;
    f32 len;
    f32 a;

    for (i = 0; i < 2; i++) {
        r = pfLock(arg0 + 1, sp20, t->lock[i], 18.0f, 0.89f, 12.5f, i + 1);
        if (r != 0xFFFF) {
            t->lock[i] = r;
            pfMul((u8 *)*arg0 + 0x28, t->mat[i], sp50);
            pfInv(sp80, sp50);
            pfXf(sp80, sp20, sp30);
            v[0] = sp30[0] - t->pos[i][0];
            v[1] = sp30[1] - t->pos[i][1];
            v[2] = sp30[2] - t->pos[i][2];
            pfNorm(v);
            y = v[1];
            v[1] = 0.0f;
            len = pfNorm(v);
            a = pfCms(v[2]) * 57.295776f;
            t->tYaw[i] = a;
            if (v[0] < 0.0f) {
                t->tYaw[i] = 360.0f - a;
            }
            if ((y < 0.0f && i == 0) || (y > 0.0f && i == 1)) {
                t->tPit[i] = pfCms(len) * 57.295776f;
            } else {
                t->tPit[i] = 0.0f;
            }
        } else {
            t->tYaw[i] = 0.0f;
            t->tPit[i] = 0.0f;
        }
        PF_STEP(cYaw, tYaw)
        PF_STEP(cPit, tPit)
    }
    PF_SUB(t->node[0], t->def[0], t->cYaw[0], pfRot1);
    PF_SUB(t->node[1], t->def[1], t->cPit[0], pfRot0);
    PF_SUB(t->node[2], t->def[2], t->cYaw[1], pfRot1);
    PF_SUB(t->node[3], t->def[3], -t->cPit[1], pfRot0);
}

typedef struct {
    u8 pad0[0x1A];
    u16 mask1A;
    u8 pad1C;
    u8 mask1D;
    u16 mask1E;
    u8 pad20[4];
} HudDef;

typedef struct {
    s32 unk0;
    u8 pad4[0xB6 - 4];
    u16 unkB6;
    s32 unkB8;
    u8 padBC[0x158 - 0xBC];
    u16 unk158;
    u8 pad15A[2];
    s32 unk15C;
    f32 unk160;
    f32 unk164;
    u8 pad168[0x178 - 0x168];
    s32 unk178;
    u8 pad17C[4];
    u16 unk180;
    u8 pad182[0x2A0 - 0x182];
} FalconSpawnPlayer;

#define FSP ((FalconSpawnPlayer *)D_main_bss_80137DBC)
extern u16 D_main_bss_80130B88[][3];
extern HudDef D_mission_overlay_8010BE18[];
extern void triggerFalconEngineEffect(s32 *, s32);
extern void playerFalconMainUpdate(void *, s32 *, f32);
extern void tickCraftAnimationSlot(s32, f32);
extern u8 tickHudInstanceTargetingAndSpawns(s32, f32, void *, s32, s32, void *, s32);
extern void dispatchHudInstanceWeaponEffect(s32, s32, void *, s32, s32, s32, s32);

void spawnFalconEngineParticles(s32 *arg0, f32 dt) {
    u16 out[2];
    FalconSpawnPlayer *p;

    p = &FSP[*arg0];
    if (*(u16 *)((u8 *)D_main_bss_80137DBC + p->unkB8 * 0x2A0 + 0x180) & 1) {
        if (0.0f < p->unk160) {
            p->unk160 = p->unk160 - dt;
        } else if (D_main_bss_80130B88[*arg0][0] & D_mission_overlay_8010BE18[*arg0].mask1A) {
            p->unk160 = p->unk160 + p->unk164;
            triggerFalconEngineEffect(arg0, *((u8 *)&p->unk158 + 1));
            p->unk158 ^= 1;
        }
        if (tickHudInstanceTargetingAndSpawns(0, dt, (u8 *)p + 4, p->unk0, (D_main_bss_80130B88[*arg0][0] & 0xFF) & D_mission_overlay_8010BE18[*arg0].mask1D, out, p->unkB6)) {
            dispatchHudInstanceWeaponEffect(0, p->unkB6, (u8 *)p + 4, p->unk0, p->unk178, p->unk158, out[0]);
        }
        if (D_main_bss_80130B88[*arg0][0] & D_mission_overlay_8010BE18[*arg0].mask1E) {
            p->unk158 = 0;
            p->unk15C = (p->unk15C + 1) & 3;
        }
    }
    playerFalconMainUpdate(p, arg0, dt);
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
} FalconUpdPlayer;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 *state;
    /* 0x08 */ void *w8;
    /* 0x0C */ s32 mesh;
    /* 0x10 */ u8 pad10[6];
    /* 0x16 */ u16 h16;
} FalconUpdNpc;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u8 *p4;
    /* 0x08 */ u8 pad8[0x144 - 8];
} FalconUpdCam;

#define FUP ((FalconUpdPlayer *)D_main_bss_80137DBC)
extern FalconUpdCam D_main_bss_80138D18[];
extern u16 D_main_bss_80139560[];
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_80109990[];
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];

void *walkMeshdef0List(char *);
void loadPlayerStartPosition(void *, void *);
void playerFalconInit(s32 *, s32, s32);
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
void computeFalconFlightTransform(s32 *, s32);
void tryPlaySpatialSoundWithGates(void *, void *);
void enqueueMeshTypeForCleanup(s32);
void addNpcToVisibilityBucket(s32, s32, void *, f32);
void advanceNpcOnCurvedPath(s32, s32, void *, s32);
void updatePlayerHudFrame(s32, void *, void *);

s32 playerFalconUpdate(FalconUpdNpc *arg0, s32 arg1, u32 *arg2) {
    s32 *s0;
    FalconUpdPlayer *p;
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
            s0 = rs_malloc(0xC4, 0);
            arg0->state = s0;
            p = &FUP[(s32)*(f32 *)arg2];
            p->mesh = (s32)walkMeshdef0List("falcon");
            p->hB6 = arg0->h16;
            arg0->mesh = p->mesh;
            arg0->w8 = (u8 *)p + 4;
            if (0.0f <= *(f32 *)arg2) {
                *(u16 *)((u8 *)&FUP[(s32)*(f32 *)arg2] - 2) = arg0->h16;
                p->index = (s32)*(f32 *)arg2;
                flag = 1;
            } else {
                flag = 0;
            }
            loadPlayerStartPosition(p, NULL);
            playerFalconInit(s0, (s32)*q, flag);
            p->w178 = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
            allocateCraftAnimationStateForSlot(p, 0, D_mission_overlay_80109990);
            popNpcSlotFromTail(D_main_bss_80139560[1], (void *)arg0);
            popNpcSlotFromTail(D_main_bss_80139560[14], (void *)arg0);
            p->ctx = allocateAndInitCraftNpcContext(0.6125f, 0.6125f, 5);
            sp10[0] = arg0->h16;
            sp10[1] = p->hB4;
            spawnNpcOfType((void *)attached3DSoundEmitterNpcHandler, sp10, 1, 0x64);
            spawnNpcOfType((void *)attachedMeshOverlayNpcHandler, &arg0->h16, 1, 0x64);
            return 1;
        case 12:
            p = &FUP[*s0];
            p->f184 = 2.0f;
            p->flags = (p->flags & 0xFFDF) | 0x40;
            loadPlayerStartPosition(p, (u8 *)p + 4);
            playerFalconInit(s0, p->index, 0x40);
            resetTransientPlayerStateFlags();
            resetCraftAnimationStateForSlot(0);
            return 1;
        case 2:
            p = &FUP[*s0];
            destroySceneNpcsAndUnlink(p);
            cancelSceneQueueHandle(p);
            rs_free((void *)p->ctx);
            releaseMeshAsset(p->mesh);
            teardownHudInstancesAndUnbindNpcs();
            freePlayerAuxBuffersIfActive(0);
            return 1;
        case 3:
            computeFalconFlightTransform(s0, *arg2);
            spawnFalconEngineParticles(s0, *(f32 *)arg2);
            return 1;
        case 5:
            tryPlaySpatialSoundWithGates(&FUP[*s0], arg2);
            if (*(u16 *)arg2 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)arg2);
            }
            return 1;
        case 4:
            p = &FUP[*s0];
            enqueueMeshTypeForCleanup(p->mesh);
            if (!(p->flags & 0x100)) {
                if (*(u16 *)(D_main_bss_80138D18[p->index].p4 + 4) != 3) {
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

static __inline__ f32 absIF(f32 x) {
    f32 r;
    FABSF(r, x);
    return r;
}
f32 integrateFalconFlightPhysics(f32 a, f32 b, f32 dt) {
    f32 d;
    register f32 v asm("$f0");

    d = b - a;
    if (absIF(d) > 0.35f) {
    if (a < b) {
        if (180.0f < d) {
            goto neg;
        }
        v = 70.0f;
    } else {
        v = 180.0f;
        if (v < a - b) {
            v = 70.0f;
        } else {
neg:
            v = -70.0f;
        }
    }
    a += dt * v;
    if (a < 0.0f) {
        a += 360.0f;
    } else if (360.0f < a) {
        a -= 360.0f;
    }
    } else {
        a = b;
    }
    return a;
}

const u32 rodata_pad_0BAFF0[2] = {
    0x03A0F021,
    0x24040014,
};

