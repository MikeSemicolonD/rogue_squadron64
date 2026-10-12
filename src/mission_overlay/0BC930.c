#include "common.h"

#include "common_types.h"
typedef struct {
    u8 pad0[0xB4];
    s16 unkB4;
    u8 padB6[0xD8 - 0xB6];
    s32 unkD8;
    s32 unkDC;
    s32 unkE0;
    f32 unkE4;
    f32 unkE8;
    f32 unkEC;
    f32 unkF0;
    f32 unkF4;
    f32 unkF8;
    f32 unkFC;
    u8 pad100[4];
    f32 unk104;
    f32 unk108;
    u8 pad10C[4];
    f32 unk110;
    f32 unk114;
    f32 unk118;
    s32 unk11C;
    f32 unk120;
    f32 unk124;
    f32 unk128;
    f32 unk12C;
    f32 unk130;
    f32 unk134;
    f32 unk138;
    s32 unk13C;
    f32 unk140;
    f32 unk144;
    f32 unk148;
    s32 unk14C;
    f32 unk150;
    f32 unk154;
    u16 unk158;
    u8 pad15A[6];
    s32 unk160;
    f32 unk164;
    f32 unk168;
    u8 pad16C[4];
    s32 unk170;
    f32 unk174;
    u8 pad178[8];
    u16 unk180;
    u8 pad182[0x2A0 - 0x182];
} TieIntPlayer;

typedef struct {
    s32 idx;
    f32 f4;
    u16 h8;
} TieIntHandle;

extern u8 D_main_bss_80137DBC[][0x2A0];
extern u32 D_main_bss_80130B58;
typedef struct { u8 pad[0x18]; u16 h18; u8 pad1A[0xA]; } TieEnt;
extern u8 D_mission_overlay_8010BE18[];
extern u32 D_mission_overlay_8010BEA8[];
extern void initPlayerCraftMovementMode(void *);
extern s32 countTrailingZeros16(u16);

void playerTieInterceptorInit(TieIntHandle *h, s32 idx, s32 mode) {
    TieIntPlayer *p = (TieIntPlayer *)D_main_bss_80137DBC[idx];
    f32 e;
    s32 z;

    p->unk180 = mode;
    h->idx = idx;
    p->unkB4 = 6;
    initPlayerCraftMovementMode(p);
    e = 50.0f;
    if (D_main_bss_80130B58 & 0x40) {
        e = 40.0f;
    }
    *(f32 *)((u8 *)p + 0xC0) = e;
    *(f32 *)((u8 *)p + 0xC4) = e;
    p->unkE8 = 3.375f;
    p->unkEC = 3.375f;
    h->f4 = 1.0f;
    p->unkF0 = 0.14999999f;
    p->unkF4 = 0.074999995f;
    p->unkF8 = 1.6f;
    p->unkFC = 2.0f;
    p->unk104 = 15.0f;
    p->unk108 = 10.0f;
    p->unk13C = 0;
    p->unk14C = 0;
    p->unk110 = -35.0f;
    p->unk114 = -45.0f;
    p->unk118 = 40.0f;
    p->unk120 = 60.0f;
    p->unk124 = 180.0f;
    p->unk130 = 0.75f;
    p->unk134 = 2.0f;
    p->unk138 = 20.0f;
    p->unk140 = 10.0f;
    p->unk144 = 60.0f;
    p->unk148 = 10.0f;
    p->unk154 = 40.0f;
    p->unk11C = 0;
    p->unk128 = 0.1f;
    p->unk12C = 0.1f;
    p->unkD8 = 0;
    p->unkDC = 0;
    p->unkE0 = 0;
    p->unk158 = 0;
    p->unk150 = 5.0f;
    p->unk160 = 0;
    p->unk164 = 0.08f;
    p->unk168 = 0.32f;
    p->unk170 = 0;
    p->unk174 = 0.08f;
    { s32 k = countTrailingZeros16(((TieEnt *)D_mission_overlay_8010BE18)[h->idx].h18);
    *(u32 *)((u8 *)D_mission_overlay_8010BEA8 + k * 4 + h->idx * 64) = 0; }
    h->h8 = 0xFFFF;
}

typedef struct {
    u8 pad0[0x12];
    u16 maskA;
    u8 pad14[4];
    u16 maskB;
    u8 pad1A[0xA];
} TitCfg;

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
} TitCraft;

typedef struct {
    s32 index;
    f32 scale;
} TitArg;

extern u16 sTitB88[][3] __asm__("D_main_bss_80130B88");
extern u8 D_main_bss_8013800C[][0x2A0];
extern void updatePlayerCraftPhysics(void *, f32);
extern void computeBootConfigScaledVec4(s32, f32, f32, void *, f32, f32);

void titImpl(TitArg *arg0, f32 dt) __asm__("computeTieInterceptorTransform");
void titImpl(TitArg *arg0, f32 dt) {
    TitCraft *c;
    f32 fs0;
    f32 sc;
    f32 t;
    f32 e8;
    f32 lim;
    u16 bits;
    register f32 *tb asm("$16");
    register TitCfg *cf asm("$19");

    c = (TitCraft *)D_main_bss_80137DBC[arg0->index];
    if (*(u16 *)((s32)D_main_bss_80137DBC + c->owner * 0x2A0 + 0x180) & 1) {
        fs0 = c->fEC;
        sc = 0.375f;
        if ((sTitB88[arg0->index][0] & ((TitCfg *)D_mission_overlay_8010BE18)[arg0->index].maskA) && !(sTitB88[arg0->index][0] & ((TitCfg *)D_mission_overlay_8010BE18)[arg0->index].maskB)) {
            sc = 0.0f;
            fs0 -= 0.225f;
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
            fs0 += *(f32 *)((k << 2) + (arg0->index << 6) + (s32)tb) * 0.45f;
        }
        countTrailingZeros16(cf[arg0->index].maskB);
        {
            s32 ii = arg0->index;
            __asm__("" :: "r"(ii));
            bits = sTitB88[ii][0];
        }
        if (!(bits & cf[arg0->index].maskA) && !(bits & cf[arg0->index].maskB) && c->fE8 < 3.375f) {
            f32 t2 = arg0->scale * 3.375f;
            fs0 += 0.225f;
            if (t2 < fs0) {
                fs0 = t2;
            }
        }
        {
            register f32 t3 asm("$f2") = arg0->scale * 4.5f;
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
    t = arg0->scale * 2.25f;
    sc = 0.375f;
    computeBootConfigScaledVec4(arg0->index, sc, sc, D_main_bss_8013800C[arg0->index], (c->fE8 - t) / t + 1.0f, dt);
}

typedef struct {
    f32 x, y, z;
} TtV3;
typedef struct {
    TtV3 pos;
    TtV3 a;
    TtV3 b;
    TtV3 c;
} TtFrame;
typedef struct {
    u8 pad0[4];
    u8 *p4;
    u8 pad8[0x13C];
} TtE;
extern TtE ttD18[] __asm__("D_main_bss_80138D18");
extern TtV3 D_mission_overlay_801099C4[];
extern u8 D_mission_overlay_801099B0[];
void lookupHmtTextureByName(s32, char *, s32, void *, void *, s32);
void accumulateVectorInObjectFrame(void *, void *, void *);
void normalize_vector(void *);
f32 vec3Dot(void *, void *);
f32 constMinusSinfApprox(f32);
void vec3Cross(void *, void *, void *);
void quatFromAxisAngleSafe(void *, void *, f32);
void rotateVec3ByQuat(void *, void *, void *);
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

void triggerTieInterceptorEffect(s32 *arg0, s32 arg1) {
    s32 *a0p = arg0;
    s32 a1v = arg1;
    TtFrame f;
    f32 v[4];
    f32 ax[4];
    f32 q[4];
    u8 *pl;
    f32 ang;

    pl = D_main_bss_80137DBC[a0p[0]];
    if (a1v & 2) {
        lookupHmtTextureByName(*(s32 *)pl, "c_d", a1v & 1, &f, NULL, 0);
    } else {
        lookupHmtTextureByName(*(s32 *)pl, "a_b", a1v & 1, &f, NULL, 0);
    }
    if (*(u16 *)(ttD18[a0p[0]].p4 + 4) == 3) {
        accumulateVectorInObjectFrame(&f, &D_mission_overlay_801099C4[a1v & 3], pl);
        if (*(u16 *)(a0p + 2) != 0xFFFF) {
            v[0] = *(f32 *)(a0p + 3) - f.pos.x;
            v[1] = *(f32 *)(a0p + 4) - f.pos.y;
            v[2] = *(f32 *)(a0p + 5) - f.pos.z;
            normalize_vector(v);
            ang = constMinusSinfApprox(vec3Dot(&f.a, v)) * 57.295776f;
            vec3Cross(ax, &f.a, v);
            ang *= 0.8f;
            quatFromAxisAngleSafe(q, ax, ang);
            *(TtV3 *)v = f.a;
            rotateVec3ByQuat(q, v, &f.a);
            *(TtV3 *)v = f.b;
            rotateVec3ByQuat(q, v, &f.b);
        }
    }
    dispatchCueByCategory(2, *(u16 *)(pl + 0xB6), &f, D_mission_overlay_801099B0, 1, 12.5f, *(f32 *)(pl + 0x16C));
    play3DSoundEvent(0, &f, pl + 0x28, 15.0f, 0.2f, 0, 0xB, 0x6E, 0x3C);
}

typedef struct {
    s32 idx;
    u8 pad4[4];
    u16 lock;
    u8 padA[2];
    u8 pos[0];
} TioCtl;

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
} TioPlayer;

typedef struct { u16 button; s8 x; s8 y; u8 err; u8 pad; } TioPad;
typedef struct { u8 pad[0x1A]; u16 fire_blasters; u16 fire_secondary; u16 fire_mode; u8 pad20[4]; } TioCfg;

extern TioPlayer sTioPlayers[] __asm__("D_main_bss_80137DBC");
extern TioPad sTioPads[] __asm__("D_main_bss_80130B88");
extern TioCfg sTioCfg[] __asm__("D_mission_overlay_8010BE18");
extern void triggerTieInterceptorEffect_l(void *, s32) __asm__("triggerTieInterceptorEffect");
extern u8 tioTickHud(s32, f32, void *, s32, s32, u16 *, s32) __asm__("tickHudInstanceTargetingAndSpawns");
extern void tioDispatch(s32, u16, void *, s32, s32, s32, s32) __asm__("dispatchHudInstanceWeaponEffect");
extern s32 tioLock(void *, void *, u16, f32, f32, f32) __asm__("findLockOnTarget");
extern void tioAnim(s32, f32) __asm__("tickCraftAnimationSlot");

void tioImpl(TioCtl *ctl, f32 dt) __asm__("computeTieInterceptorOrientation");
void tioImpl(TioCtl *ctl, f32 dt) {
    u16 sp20;
    TioPlayer *c;
    void *pos;
    s32 r;
    u16 t;
    u8 *base;

    c = &sTioPlayers[ctl->idx];
    base = (u8 *)sTioPlayers - 4;
    if (*(u16 *)(base + c->wB8 * 0x2A0 + 0x184) & 1) {
        if (c->timer > 0.0f) {
            c->timer = c->timer - dt;
        } else if (sTioPads[ctl->idx].button & sTioCfg[ctl->idx].fire_blasters) {
            if (*(s32 *)(base + ctl->idx * 0x2A0 + 0x160) == 1) {
                c->timer = c->timer + c->f168;
                triggerTieInterceptorEffect_l(ctl, c->h158);
                triggerTieInterceptorEffect_l(ctl, c->h158 + 1);
                c->h158 ^= 2;
            } else if (*(s32 *)(base + ctl->idx * 0x2A0 + 0x160) == 2) {
                c->timer = c->timer + c->f168 * 1.5;
                triggerTieInterceptorEffect_l(ctl, 0);
                triggerTieInterceptorEffect_l(ctl, 1);
                triggerTieInterceptorEffect_l(ctl, 2);
                triggerTieInterceptorEffect_l(ctl, 3);
            } else {
                c->timer = c->timer + c->f164;
                triggerTieInterceptorEffect_l(ctl, c->h158);
                c->h158 = (c->h158 + 1) & 3;
            }
        }
        pos = &c->pos[0];
        if (tioTickHud(0, dt, pos, c->w0, (u8)(sTioPads[ctl->idx].button & sTioCfg[ctl->idx].fire_secondary), &sp20, c->hB6)) {
            tioDispatch(0, c->hB6, pos, c->w0, c->w178, c->h158, sp20);
        }
        if (sTioPads[ctl->idx].button & sTioCfg[ctl->idx].fire_mode) {
            if (++c->w15C >= 3) {
                c->w15C = 0;
            }
            c->h158 = 0;
        }
    }
    r = tioLock(&c->pos[0], ctl->pos, ctl->lock, 8.0f, 0.992f, 12.5f);
    t = r;
    sp20 = r;
    if (t != 0xFFFF) {
        ctl->lock = r;
    } else {
        ctl->lock = 0xFFFF;
    }
    tioAnim(0, dt);
}

#include "common_types.h"
extern struct E144 D_main_bss_80138D18[];
extern u8 D_main_bss_80139560[];
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_801099BC[];
struct E144 { s32 pad; u8 *p; u8 rest[0x13C]; };
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];
extern void *rs_malloc(s32, s32);
extern void rs_free(void *);
extern s32 walkMeshdef0List(char *);
extern void loadPlayerStartPosition(void *, void *);
extern s32 refreshPlayerSecondaryWeaponHud(s32);
extern void allocateCraftAnimationStateForSlot(void *, s32, void *);
extern void popNpcSlotFromTail(u16, void *);
extern void *allocateAndInitCraftNpcContext(f32, f32, s32);
extern void spawnNpcOfType(void *, void *, s32, s32);
extern void resetTransientPlayerStateFlags(void);
extern void resetCraftAnimationStateForSlot(s32);
extern void destroySceneNpcsAndUnlink(void *);
extern void cancelSceneQueueHandle(void *);
extern void releaseMeshAsset(s32);
extern void teardownHudInstancesAndUnbindNpcs(void);
extern void freePlayerAuxBuffersIfActive(s32);
extern void computeTieInterceptorTransform(void *, s32);
extern void computeTieInterceptorOrientation(void *, s32);
extern void tryPlaySpatialSoundWithGates(void *, void *);
extern void destroyNpcSlotByIndex(u16);
extern void enqueueMeshTypeForCleanup(s32);
extern void addNpcToVisibilityBucket(s32, s32, void *, f32);
extern void advanceNpcOnCurvedPath(s32, s32, void *, s32);
extern void updatePlayerHudFrame(s32, void *, void *);

s32 playerTieInterceptorUpdate(u8 *arg0, s32 arg1, s32 *arg2) {
    s32 *s0 = *(s32 **)(arg0 + 4);
    u8 *s1;
    s32 s2;
    s32 *m;
    u16 sp10[2];
    s32 v;
    s32 t;
    f32 *af;
    u8 *h;

    if ((arg1 & 0xFFFF) != 2 && (D_mission_overlay_8010CA1C & 4)) {
        return 1;
    } else {
        t = arg1 & 0xFFFF;
        switch (t) {
        case 1:
            af = (f32 *)arg2;
            m = rs_malloc(0x18, 0);
            s0 = m;
            *(s32 **)(arg0 + 4) = s0;
            s1 = D_main_bss_80137DBC[(s32)*af];
            *(s32 *)s1 = walkMeshdef0List("tie_inter");
            *(u16 *)(s1 + 0xB6) = *(u16 *)(arg0 + 0x16);
            *(s32 *)(arg0 + 0xC) = *(s32 *)s1;
            *(u8 **)(arg0 + 8) = s1 + 4;
            if (*af >= 0.0f) {
                *(u16 *)((u8 *)D_main_bss_80137DBC + (s32)*af * 0x2A0 - 2) = *(u16 *)(arg0 + 0x16);
                *(s32 *)(s1 + 0xB8) = (s32)*af;
                s2 = 1;
            } else {
                s2 = 0;
            }
            loadPlayerStartPosition(s1, 0);
            playerTieInterceptorInit(s0, (s32)*af, s2);
            *(s32 *)(s1 + 0x178) = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
            allocateCraftAnimationStateForSlot(s1, 0, D_mission_overlay_801099BC);
            h = D_main_bss_80139560;
            popNpcSlotFromTail(*(u16 *)(h + 2), arg0);
            popNpcSlotFromTail(*(u16 *)(h + 0x1C), arg0);
            *(void **)(s1 + 0xBC) = allocateAndInitCraftNpcContext(0.125f, 0.125f, 7);
            sp10[0] = *(u16 *)(arg0 + 0x16);
            sp10[1] = *(u16 *)(s1 + 0xB4);
            spawnNpcOfType(attached3DSoundEmitterNpcHandler, sp10, 1, 0x64);
            spawnNpcOfType(attachedMeshOverlayNpcHandler, arg0 + 0x16, 1, 0x64);
            return 1;
        case 12:
            s1 = D_main_bss_80137DBC[*s0];
            *(f32 *)(s1 + 0x184) = 2.0f;
            *(u16 *)(s1 + 0x180) = (*(u16 *)(s1 + 0x180) & 0xFFDF) | 0x40;
            loadPlayerStartPosition(s1, s1 + 4);
            playerTieInterceptorInit(s0, *(s32 *)(s1 + 0xB8), 0x40);
            resetTransientPlayerStateFlags();
            resetCraftAnimationStateForSlot(0);
            return 1;
        case 2:
            s1 = D_main_bss_80137DBC[*s0];
            destroySceneNpcsAndUnlink(s1);
            cancelSceneQueueHandle(s1);
            rs_free(*(void **)(s1 + 0xBC));
            releaseMeshAsset(*(s32 *)s1);
            teardownHudInstancesAndUnbindNpcs();
            freePlayerAuxBuffersIfActive(0);
            return 1;
        case 3:
            computeTieInterceptorTransform(s0, *arg2);
            computeTieInterceptorOrientation(s0, *arg2);
            return 1;
        case 5:
            tryPlaySpatialSoundWithGates(D_main_bss_80137DBC[*s0], arg2);
            if (*(u16 *)arg2 != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)arg2);
            }
            return 1;
        case 4:
            s1 = D_main_bss_80137DBC[*s0];
            enqueueMeshTypeForCleanup(*(s32 *)s1);
            if (!(*(u16 *)(s1 + 0x180) & 0x100)) {
                if (*(u16 *)(D_main_bss_80138D18[*(s32 *)(s1 + 0xB8)].p + 4) != 3) {
                    addNpcToVisibilityBucket(*arg2, *(s32 *)s1, s1 + 4, 1.0f);
                    if (!(*(u16 *)(s1 + 0x180) & 0x80)) {
                        advanceNpcOnCurvedPath(arg2[2], *arg2, s1 + 4, *(s32 *)(s1 + 0xBC));
                    }
                }
                updatePlayerHudFrame(0, arg2, s1 + 4);
            }
            return 1;
        }
        return 1;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0BC930", fake_func_800BCC38);

static u32 D_mission_overlay_800A5FD8[] __attribute__((section(".rodata"))) = { 0x27BDFFC8, 0xAFBF0034 };
