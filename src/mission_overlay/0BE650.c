#include "common.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BE650", D_mission_overlay_800A60D0);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0BE650", D_mission_overlay_800A60D8);

#include "common_types.h"
extern u8 sCraftBytes[][0x2A0] __asm__("D_main_bss_80137DBC");
extern s32 D_main_bss_80130B58;
extern struct { u8 pad[0x18]; u16 unk18; u8 pad1A[0xA]; } sHudDefs[] __asm__("D_mission_overlay_8010BE18");
s32 lookupHmtMaterialByName(s32, char *, void *);
extern s32 D_mission_overlay_8010BEA8[][16];
extern void initPlayerCraftMovementMode(void *);
extern s32 countTrailingZeros16(u16);

void playerNabooStarfighterInit(s32 *arg0, s32 arg1, s32 arg2) {
    u8 *p = sCraftBytes[arg1];
    f32 hp;
    f32 b, c, d, e, g, h, i, j, k, l, m, n, o, q;
    *(s16 *)(p + 0x180) = arg2;
    arg0[0] = arg1;
    *(u16 *)(p + 0xB4) = 8;
    initPlayerCraftMovementMode(p);
    hp = 150.0f;
    if (D_main_bss_80130B58 & 0x40) {
        hp = 40.0f;
    }
    b = 3.0f;
    c = 0.1f;
    d = 15.0f;
    e = 10.0f;
    g = -40.0f;
    h = -45.0f;
    i = 40.0f;
    j = 60.0f;
    k = 180.0f;
    l = 0.75f;
    m = 2.0f;
    n = 20.0f;
    o = 5.0f;
    q = 0.08f;
    *(f32 *)(p + 0xC0) = hp;
    *(f32 *)(p + 0xC4) = hp;
    *(s32 *)(p + 0x13C) = 0;
    *(s32 *)(p + 0x14C) = 0;
    *(s32 *)(p + 0x11C) = 0;
    *(s32 *)(p + 0xD8) = 0;
    *(s32 *)(p + 0xDC) = 0;
    *(s32 *)(p + 0xE0) = 0;
    *(s16 *)(p + 0x158) = 0;
    *(s32 *)(p + 0x160) = 0;
    *(f32 *)(p + 0xE8) = b;
    *(f32 *)(p + 0xEC) = b;
    *(f32 *)(p + 0xF0) = c;
    *(f32 *)(p + 0xF4) = c;
    *(f32 *)(p + 0xFC) = b;
    *(f32 *)(p + 0x104) = d;
    *(f32 *)(p + 0x108) = e;
    *(f32 *)(p + 0x110) = g;
    *(f32 *)(p + 0x114) = h;
    *(f32 *)(p + 0x118) = i;
    *(f32 *)(p + 0x120) = j;
    *(f32 *)(p + 0x124) = k;
    *(f32 *)(p + 0x130) = l;
    *(f32 *)(p + 0x134) = m;
    *(f32 *)(p + 0x138) = n;
    *(f32 *)(p + 0xF8) = 1.6f;
    *(f32 *)(p + 0x140) = e;
    *(f32 *)(p + 0x144) = j;
    *(f32 *)(p + 0x148) = e;
    *(f32 *)(p + 0x150) = o;
    *(f32 *)(p + 0x154) = i;
    *(f32 *)(p + 0x128) = c;
    *(f32 *)(p + 0x168) = 0.32f;
    *(f32 *)(p + 0x12C) = c;
    *(f32 *)(p + 0x164) = q;
    *(s32 *)(p + 0x170) = 0;
    *(f32 *)(p + 0x174) = q;
    D_mission_overlay_8010BEA8[arg0[0]][countTrailingZeros16(sHudDefs[arg0[0]].unk18)] = 0;
    *(u8 *)((u8 *)arg0 + 4) = 0;
    *(u16 *)((u8 *)arg0 + 6) = 0xFFFF;
    arg0[7] = lookupHmtMaterialByName(*(s32 *)p, "f_trns_l", (u8 *)arg0 + 0x14);
    arg0[8] = lookupHmtMaterialByName(*(s32 *)p, "f_trns_r", (u8 *)arg0 + 0x18);
}

typedef struct {
    u8 pad0[0x4C];
    u32 flags;
    f32 f50, f54, f58;
    f32 f5C, f60, f64;
    u8 q68[0x10];
    f32 f78, f7C, f80;
} NbDef;

typedef struct {
    s32 index;
    u8 pad4[0x10];
    NbDef *def1;
    NbDef *def2;
    u8 *obj1;
    u8 *obj2;
} NbArg;

typedef struct {
    u8 pad0[0xB8];
    s32 owner;
    u8 padBC[0x2C];
    f32 fE8;
    f32 fEC;
    f32 fF0;
    f32 fF4;
    u8 padF8[0x28];
    f32 f120;
} NbCraft;

typedef struct {
    u8 pad0[0x12];
    u16 maskA;
    u8 pad14[4];
    u16 maskB;
    u8 pad1A[0xA];
} NbCfg;

extern u16 nbB88[][3] __asm__("D_main_bss_80130B88");
extern u8 D_main_bss_8013800C[][0x2A0];
extern f32 D_mission_overlay_8010BDD8[][2];
extern void updatePlayerCraftPhysics(void *, f32);
extern void computeBootConfigScaledVec4(s32, f32, f32, void *, f32, f32);
extern void clearVec4QuadStruct(void *);
extern void addVec3At0x24(void *, f32, f32, f32);
extern void applyScaleToMat3x4(void *, f32, f32, f32);
extern void composeRotationMatrixSlot0(void *, f32);
extern void composeQuatToMat3x4(void *, void *);

#define NB_SUB(D, M, ANG)                                                              \
    {                                                                                  \
        NbDef *d;                                                                      \
        u8 *m;                                                                         \
        fs0 = D_mission_overlay_8010BDD8[c->owner][0] * (ANG);                         \
        d = D;                                                                         \
        m = M + 0x1C;                                                                  \
        clearVec4QuadStruct(m);                                                        \
        if (d->flags & 1) {                                                            \
            addVec3At0x24(m, -d->f50, -d->f54, -d->f58);                               \
        }                                                                              \
        if (d->flags & 2) {                                                            \
            applyScaleToMat3x4(m, d->f5C, d->f60, d->f64);                             \
        }                                                                              \
        composeRotationMatrixSlot0(m, fs0);                                            \
        if (d->flags & 4) {                                                            \
            composeQuatToMat3x4(m, d->q68);                                            \
        }                                                                              \
        {                                                                              \
            u32 fl = d->flags;                                                         \
            if ((fl & 9) == 9) {                                                       \
                addVec3At0x24(m, d->f78 + d->f50, d->f7C + d->f54, d->f80 + d->f58);   \
            } else if ((fl & 9) == 8) {                                                \
                addVec3At0x24(m, d->f78, d->f7C, d->f80);                              \
            } else if (fl & 1) {                                                       \
                addVec3At0x24(m, d->f50, d->f54, d->f58);                              \
            }                                                                          \
        }                                                                              \
    }

void nbImpl(NbArg *arg0, f32 dt) __asm__("buildNabooSubmodelTransform");
void nbImpl(NbArg *arg0, f32 dt) {
    NbCraft *c;
    f32 fs0;
    f32 sc;
    u16 bits;
    register f32 *tb asm("$16");
    NbCfg *cf;

    c = (NbCraft *)sCraftBytes[arg0->index];
    if (*(u16 *)((s32)sCraftBytes + c->owner * 0x2A0 + 0x180) & 1) {
        fs0 = c->fEC;
        sc = 0.375f;
        if ((nbB88[arg0->index][0] & ((NbCfg *)sHudDefs)[arg0->index].maskA) && !(nbB88[arg0->index][0] & ((NbCfg *)sHudDefs)[arg0->index].maskB)) {
            sc = 0.0f;
            fs0 -= 0.3f;
        }
        c->f120 = 60.0f;
        if (fs0 < 1.6875f) {
            fs0 = 1.6875f;
        }
        { s32 hi; __asm__("lui %0, %%hi(D_mission_overlay_8010BE18)" : "=r"(hi)); __asm__("addiu %0, %1, %%lo(D_mission_overlay_8010BE18)" : "=r"(cf) : "r"(hi)); }
        {
            s32 k = countTrailingZeros16(cf[arg0->index].maskB);
            tb = (f32 *)D_mission_overlay_8010BEA8;
            fs0 += *(f32 *)((k << 2) + (arg0->index << 6) + (s32)tb) * 0.3f;
        }
        countTrailingZeros16(cf[arg0->index].maskB);
        {
            s32 ii = arg0->index;
            __asm__("" :: "r"(ii));
            bits = nbB88[ii][0];
        }
        if (!(bits & cf[arg0->index].maskA) && !(bits & cf[arg0->index].maskB) && c->fE8 < 3.0f) {
            fs0 += 0.3f;
            if (3.0f < fs0) {
                fs0 = 3.0f;
            }
        }
        {
            register f32 t3 asm("$f2") = 6.0f;
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
        {
            f32 e8 = c->fE8;
            f32 lim = c->fF4;
            if (fs0 - e8 < -lim) {
                c->fE8 = e8 - lim;
            } else {
                c->fE8 = fs0;
            }
        }
        __asm__("" :: "f"(sc));
    }
    updatePlayerCraftPhysics(c, dt);
    sc = 0.375f;
    computeBootConfigScaledVec4(arg0->index, sc, sc, D_main_bss_8013800C[arg0->index], (c->fE8 - 1.6875f) / 4.3125f + 1.0f, dt);
    NB_SUB(arg0->def1, arg0->obj1, 45.0f)
    NB_SUB(arg0->def2, arg0->obj2, -45.0f)
}

typedef struct {
    f32 x, y, z;
} NeV3;
typedef struct {
    NeV3 pos;
    NeV3 a;
    NeV3 b;
    NeV3 c;
} NeFrame;
typedef struct {
    u8 pad0[4];
    u8 *p4;
    u8 pad8[0x13C];
} NeE;
extern NeE neD18[] __asm__("D_main_bss_80138D18");
extern NeV3 D_mission_overlay_80109AB4[];
extern u8 D_mission_overlay_80109A60[];
void neLookupHmt(s32, char *, s32, void *, void *, s32) __asm__("lookupHmtTextureByName");
void accumulateVectorInObjectFrame(void *, void *, void *);
f32 normalize_vector(void *);
f32 vec3Dot(void *, void *);
f32 constMinusSinfApprox(f32);
void vec3Cross(void *, void *, void *);
void quatFromAxisAngleSafe(void *, void *, f32);
void rotateVec3ByQuat(void *, void *, void *);
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);

void neImpl(s32 *arg0, s32 arg1, NeV3 *out) __asm__("triggerNabooEngineEffect");
void neImpl(s32 *arg0, s32 arg1, NeV3 *out) {
    NeFrame f;
    f32 v[4];
    f32 ax[4];
    f32 q[4];
    u8 *pl;
    f32 ang;
    s32 b;

    pl = sCraftBytes[arg0[0]];
    neLookupHmt(*(s32 *)pl, "a_b", b = arg1 & 1, &f, NULL, 0);
    if (*(u16 *)(neD18[arg0[0]].p4 + 4) == 3) {
        accumulateVectorInObjectFrame(&f, &D_mission_overlay_80109AB4[b], pl);
    }
    if (*(u16 *)((u8 *)arg0 + 6) != 0xFFFF) {
        v[0] = *(f32 *)(arg0 + 2) - f.pos.x;
        v[1] = *(f32 *)(arg0 + 3) - f.pos.y;
        v[2] = *(f32 *)(arg0 + 4) - f.pos.z;
        normalize_vector(v);
        ang = constMinusSinfApprox(vec3Dot(&f.a, v)) * 57.295776f;
        vec3Cross(ax, &f.a, v);
        if (*(u16 *)(neD18[arg0[0]].p4 + 4) != 3) {
            quatFromAxisAngleSafe(q, ax, ang * 0.4f);
        } else {
            quatFromAxisAngleSafe(q, ax, ang * 0.8f);
        }
        *(NeV3 *)v = f.a;
        rotateVec3ByQuat(q, v, &f.a);
        *(NeV3 *)v = f.b;
        rotateVec3ByQuat(q, v, &f.b);
    }
    dispatchCueByCategory(2, *(u16 *)(pl + 0xB6), &f, D_mission_overlay_80109A60, 1, 15.0f, *(f32 *)(pl + 0x16C));
    if (out != NULL) {
        *out = f.pos;
    }
}

#include "controller_settings.h"
#include "main/bss_80130B10.h"

typedef struct {
    s32 idx;
    u8 flip;
    u8 pad5;
    u16 lock;
    u8 pos[0];
} BlinkCtl;

typedef struct {
    s32 w0;
    f32 pos[10];
    u8 pad2C[0xB6 - 0x2C];
    u16 hB6;
    s32 wB8;
    u8 padBC[0x158 - 0xBC];
    u16 h158;
    u8 pad15A[2];
    s32 w15C;
    f32 timer;
    f32 f164;
    f32 f168;
    u8 pad16C[0x178 - 0x16C];
    s32 w178;
    u8 pad17C[0x2A0 - 0x17C];
} BlinkPlayer;

extern BlinkPlayer sBlinkPlayers[] __asm__("D_main_bss_80137DBC");
extern union ControllerSettings D_mission_overlay_8010BE18[];
extern void triggerNabooEngineEffect(void *, s32, void *);
extern s32 play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern u8 tickHudInstanceTargetingAndSpawns(s32, f32, void *, s32, s32, u16 *, s32);
extern void dispatchHudInstanceWeaponEffect(s32, u16, void *, s32, s32, s32, s32);
extern s32 findLockOnTarget(void *, void *, u16, f32, f32, f32);
extern void tickCraftAnimationSlot(s32, f32);

void tickPlayerCraftBlinkIndicator(BlinkCtl *ctl, f32 dt) {
    u8 sp28[16];
    u16 sp38;
    BlinkPlayer *c;
    void *pos;
    s32 r;
    u16 t;
    u8 *base;

    c = &sBlinkPlayers[ctl->idx];
    base = (u8 *)sBlinkPlayers - 4;
    if (*(u16 *)(base + c->wB8 * 0x2A0 + 0x184) & 1) {
        if (c->timer > 0.0f) {
            c->timer = c->timer - dt;
        } else if (D_main_bss_80130B88[ctl->idx].button & D_mission_overlay_8010BE18[ctl->idx].asStruct.fire_blasters) {
            if (*(s32 *)(base + ctl->idx * 0x2A0 + 0x160) == 1) {
                c->timer = c->timer + c->f168;
                triggerNabooEngineEffect(ctl, c->h158, 0);
                triggerNabooEngineEffect(ctl, c->h158 + 1, 0);
                play3DSoundEvent(0, &c->pos[0], &c->pos[9], 20.0f, 0.2f, 0, 0x71, 0x5A, 0x28);
            } else {
                c->timer = c->timer + c->f164;
                triggerNabooEngineEffect(ctl, c->h158, sp28);
                c->h158 ^= 1;
                play3DSoundEvent(0, sp28, &c->pos[9], 20.0f, 0.2f, 0, 0x71, 0x5A, 0x28);
            }
        }
        pos = &c->pos[0];
        if (tickHudInstanceTargetingAndSpawns(0, dt, pos, c->w0, (u8)(D_main_bss_80130B88[ctl->idx].button & D_mission_overlay_8010BE18[ctl->idx].asStruct.fire_secondary), &sp38, c->hB6)) {
            dispatchHudInstanceWeaponEffect(0, c->hB6, pos, c->w0, c->w178, ctl->flip, sp38);
            ctl->flip ^= 1;
        }
        if (D_main_bss_80130B88[ctl->idx].button & D_mission_overlay_8010BE18[ctl->idx].asStruct.fire_mode) {
            c->h158 = 0;
            c->w15C ^= 1;
        }
    }
    r = findLockOnTarget(&c->pos[0], (u8 *)ctl + 8, ctl->lock, 8.0f, 0.992f, 15.0f);
    t = r;
    sp38 = r;
    if (t != 0xFFFF) {
        ctl->lock = r;
    } else {
        ctl->lock = 0xFFFF;
    }
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
} NbUpdPlayer;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 *state;
    /* 0x08 */ void *w8;
    /* 0x0C */ s32 mesh;
    /* 0x10 */ u8 pad10[6];
    /* 0x16 */ u16 h16;
} NbUpdNpc;

typedef struct {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ u8 *p4;
    /* 0x08 */ u8 pad8[0x144 - 8];
} NbUpdCam;

#define NUP ((NbUpdPlayer *)D_main_bss_80137DBC)
extern NbUpdCam D_main_bss_80138D18[];
extern u16 D_main_bss_80139560[];
extern u8 D_mission_overlay_80109AAC[];
extern u8 D_main_bss_80137DBC[];
extern s32 D_mission_overlay_8010CA1C;
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];

void *walkMeshdef0List(char *);
void playerNabooStarfighterInit(s32 *, s32, s32);
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
void buildNabooSubmodelTransform(s32 *, s32);
void tickPlayerCraftBlinkIndicatorCall(s32 *, s32) __asm__("tickPlayerCraftBlinkIndicator");
void tryPlaySpatialSoundWithGates(void *, void *);
void enqueueMeshTypeForCleanup(s32);
void addNpcToVisibilityBucket(s32, s32, void *, f32);
void advanceNpcOnCurvedPath(s32, s32, void *, s32);
void updatePlayerHudFrame(s32, void *, void *);

s32 playerNabooStarfighterUpdate(NbUpdNpc *arg0, s32 arg1, u32 *arg2) {
    s32 *s0;
    NbUpdPlayer *p;
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
            s0 = rs_malloc(0x24, 0);
            arg0->state = s0;
            p = &NUP[(s32)*(f32 *)arg2];
            p->mesh = (s32)walkMeshdef0List("koelsch");
            p->hB6 = arg0->h16;
            arg0->mesh = p->mesh;
            arg0->w8 = (u8 *)p + 4;
            if (0.0f <= *(f32 *)arg2) {
                *(u16 *)((u8 *)&NUP[(s32)*(f32 *)arg2] - 2) = arg0->h16;
                p->index = (s32)*(f32 *)arg2;
                flag = 1;
            } else {
                flag = 0;
            }
            loadPlayerStartPosition(p, NULL);
            playerNabooStarfighterInit(s0, (s32)*q, flag);
            p->w178 = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
            allocateCraftAnimationStateForSlot(p, 0, D_mission_overlay_80109AAC);
            popNpcSlotFromTail(D_main_bss_80139560[1], (void *)arg0);
            popNpcSlotFromTail(D_main_bss_80139560[14], (void *)arg0);
            p->ctx = allocateAndInitCraftNpcContext(0.15f, 0.25f, 8);
            sp10[0] = arg0->h16;
            sp10[1] = p->hB4;
            spawnNpcOfType((void *)attached3DSoundEmitterNpcHandler, sp10, 1, 0x64);
            spawnNpcOfType((void *)attachedMeshOverlayNpcHandler, &arg0->h16, 1, 0x64);
            return 1;
        case 12:
            p = &NUP[*s0];
            p->f184 = 2.0f;
            p->flags = (p->flags & 0xFFDF) | 0x40;
            loadPlayerStartPosition(p, (u8 *)p + 4);
            playerNabooStarfighterInit(s0, p->index, 0x40);
            resetTransientPlayerStateFlags();
            resetCraftAnimationStateForSlot(0);
            return 1;
        case 2:
            p = &NUP[*s0];
            destroySceneNpcsAndUnlink(p);
            cancelSceneQueueHandle(p);
            teardownHudInstancesAndUnbindNpcs();
            freePlayerAuxBuffersIfActive(0);
            rs_free((void *)p->ctx);
            releaseMeshAsset(p->mesh);
            return 1;
        case 3:
            buildNabooSubmodelTransform(s0, *arg2);
            tickPlayerCraftBlinkIndicatorCall(s0, *arg2);
            return 1;
        case 5:
            tryPlaySpatialSoundWithGates(&NUP[*s0], arg2);
            if (*(u16 *)arg2 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)arg2);
            }
            return 1;
        case 4:
            p = &NUP[*s0];
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

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BE650", fake_func_800BEBFC);


// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
const u32 rodat_pad_0BE650 = 0x93C20012;
