#include "common.h"

#include "mission_overlay/0B4EC0.h"

u32 D_mission_overlay_8010BC80[4];
f32 D_mission_overlay_8010BC90[4];

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5820);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5828);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5830);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5838);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5840);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B4EC0", D_mission_overlay_800A5848);

extern u8 xwCraftBytes[][0x2A0] __asm__("D_main_bss_80137DBC");
extern s32 D_main_bss_80130B58;
extern struct { u8 pad[0x18]; u16 unk18; u8 pad1A[0xA]; } xwHud[] __asm__("D_mission_overlay_8010BE18");
extern f32 D_mission_overlay_8010BEA8[][0x10];
extern void initPlayerCraftMovementMode(void *);
s32 xwLookupMat(s32, char *, void *) __asm__("lookupHmtMaterialByName");
s32 countTrailingZeros16(u16);
void buildRotationMatrixFromEulerAngles(void *, f32, f32, f32);

void playerXwingInit(s32 *arg0, s32 arg1, s32 arg2) {
    u8 *p = xwCraftBytes[arg1];
    f32 hp;
    register f32 h asm("$f10");
    f32 b, c, d, f, e, g, i, j, k, l, m, n, o;
    f32 z;
    *(s16 *)(p + 0x180) = arg2;
    arg0[0] = arg1;
    *(u16 *)(p + 0xB4) = 0;
    initPlayerCraftMovementMode(p);
    hp = 150.0f;
    if (D_main_bss_80130B58 & 0x40) {
        hp = 40.0f;
    }
    *(f32 *)(p + 0xF8) = 1.6f;
    b = 2.625f;
    c = 0.0625f;
    d = 1.75f;
    f = 15.0f;
    e = 10.0f;
    g = -30.0f;
    h = 40.0f;
    i = 60.0f;
    j = 180.0f;
    k = 0.75f;
    l = 2.0f;
    m = 20.0f;
    n = 5.0f;
    o = 0.1f;
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
    *(f32 *)(p + 0xFC) = d;
    *(f32 *)(p + 0x104) = f;
    *(f32 *)(p + 0x108) = e;
    *(f32 *)(p + 0x110) = g;
    *(f32 *)(p + 0x114) = g;
    *(f32 *)(p + 0x118) = h;
    *(f32 *)(p + 0x120) = i;
    *(f32 *)(p + 0x124) = j;
    *(f32 *)(p + 0x130) = k;
    *(f32 *)(p + 0x134) = l;
    *(f32 *)(p + 0x138) = m;
    *(f32 *)(p + 0x140) = e;
    *(f32 *)(p + 0x144) = i;
    *(f32 *)(p + 0x148) = e;
    *(f32 *)(p + 0x150) = n;
    *(f32 *)(p + 0x154) = h;
    *(f32 *)(p + 0x128) = o;
    *(f32 *)(p + 0x168) = 0.5f;
    *(f32 *)(p + 0x12C) = o;
    *(f32 *)(p + 0x164) = o;
    *(s32 *)(p + 0x170) = 0;
    *(f32 *)(p + 0x174) = o;
    D_mission_overlay_8010BEA8[arg0[0]][countTrailingZeros16(xwHud[arg0[0]].unk18)] = 0.0f;
    arg0[1] = 0;
    arg0[2] = 0;
    D_mission_overlay_8010BC80[arg0[0]] = 0;
    D_mission_overlay_8010BC90[arg0[0]] = *(f32 *)&arg0[1];
    *(f32 *)&arg0[5] = 1.0f;
    arg0[3] = xwLookupMat(*(s32 *)p, "wngrot_a", NULL);
    z = 0.0f;
    arg0[4] = xwLookupMat(*(s32 *)p, "wngrot_b", NULL);
    buildRotationMatrixFromEulerAngles((u8 *)arg0[3] + 0x1C, z, z, -10.0f);
    buildRotationMatrixFromEulerAngles((u8 *)arg0[4] + 0x1C, z, z, e);
    *((u8 *)arg0 + 0x19) = 0;
    *(u16 *)((u8 *)arg0 + 0x1A) = 0xFFFF;
    *((u8 *)arg0 + 0x18) = 0;
}

typedef struct {
    /* 0x00 */ s32 idx;
    /* 0x04 */ f32 f4;
    /* 0x08 */ s32 w8;
    /* 0x0C */ u8 *pC;
    /* 0x10 */ u8 *p10;
    /* 0x14 */ f32 f14;
} PwState;

typedef struct {
    /* 0x000 */ u8 pad0[0xB8];
    /* 0x0B8 */ s32 index;
    /* 0x0BC */ u8 padBC[0xE8 - 0xBC];
    /* 0x0E8 */ f32 fE8;
    /* 0x0EC */ f32 fEC;
    /* 0x0F0 */ f32 fF0;
    /* 0x0F4 */ f32 fF4;
    /* 0x0F8 */ f32 fF8;
    /* 0x0FC */ u8 padFC[0x120 - 0xFC];
    /* 0x120 */ f32 f120;
    /* 0x124 */ u8 pad124[0x180 - 0x124];
    /* 0x180 */ u16 flags;
    /* 0x182 */ u8 pad182[0x2A0 - 0x182];
} PwPlayer;

typedef struct {
    u8 pad0[0x12];
    u16 m12;
    u8 pad14[4];
    u16 m18;
    u8 pad1A[8];
    u16 m22;
} PwHud;

typedef struct {
    u8 pad0[4];
    u8 *p4;
    u8 pad8[0x144 - 8];
} PwCam;

extern PwPlayer D_pw_players[] __asm__("D_main_bss_80137DBC");
extern u16 D_pw_btn[][3] __asm__("D_main_bss_80130B88");
extern PwHud D_pw_hud[] __asm__("D_mission_overlay_8010BE18");
extern PwCam D_pw_cam[] __asm__("D_main_bss_80138D18");
extern f32 D_mission_overlay_8010BEA8[][0x10];
extern u8 D_main_bss_8013800C[];
s32 countTrailingZeros16(u16);
u8 getCraftAnimationSlotFlag(s32);
f32 getCraftAnimationSlotValue(s32);
void setCraftAnimationSlotParams(s32, s32, f32);
void updatePlayerCraftPhysics(void *, f32);
void computeBootConfigScaledVec4(s32, f32, f32, u8 *, f32, f32);
void bsearchFactor5TableByU16Key(s32, s32, s32);
void scheduleSceneFormatMessageTimed(void *, s32);
void buildRotationMatrixFromEulerAngles(void *, f32, f32, f32);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

static __inline__ u8 pwSlotReady(u8 arg0) {
    s32 ret;
    ret = 0;
    if ((D_mission_overlay_8010BC80[arg0] != 1) || !(0.95f < D_mission_overlay_8010BC90[arg0])) {
        ret = 1;
    }
    return ret;
}

void pwImpl(PwState *e, f32 dt) __asm__("playWeaponFireSound");
void pwImpl(PwState *e, f32 dt) {
    PwPlayer *p;
    f32 v;
    register f32 k asm("$f22");
    f32 lim;
    f32 r;
    register PwHud *hud asm("$19");
    register s32 tbl asm("$16");
    s32 ct;

    p = &D_pw_players[e->idx];
    if (*(u16 *)((s32)D_pw_players + p->index * 0x2A0 + 0x180) & 1) {
        v = p->fEC;
        k = 0.28125f;
        if ((D_pw_btn[e->idx][0] & D_pw_hud[e->idx].m12) && !(D_pw_btn[e->idx][0] & D_pw_hud[e->idx].m18)) {
            v -= 0.1875f;
            k = -0.09375f;
        }
        __asm__ volatile("" :: "f"(k));
        p->f120 = 60.0f;
        if (v < e->f14 * 2.25f) {
            v = e->f14 * 2.25f;
        }
        { s32 hi; __asm__("lui %0, %%hi(D_mission_overlay_8010BE18)" : "=r"(hi)); __asm__("addiu %0, %1, %%lo(D_mission_overlay_8010BE18)" : "=r"(hud) : "r"(hi)); }
        ct = countTrailingZeros16(hud[e->idx].m18);
        tbl = (s32)D_mission_overlay_8010BEA8;
        v += *(f32 *)((e->idx * 0x40 + ct * 4) + tbl) * 0.1875f;
        countTrailingZeros16(hud[e->idx].m18);
        { s32 ix = e->idx; __asm__("" :: "r"(ix));
        if ((D_pw_btn[ix][0] & hud[ix].m18) && pwSlotReady(e->idx)) {
            if (getCraftAnimationSlotFlag(0) == 0) {
                setCraftAnimationSlotParams(0, 1, 0);
            }
        } else if (getCraftAnimationSlotFlag(0) == 1) {
            if (getCraftAnimationSlotValue(0) == 0.0f) {
                setCraftAnimationSlotParams(0, 1, 0.5f);
            }
        }
        }
        if (!(D_pw_btn[e->idx][0] & D_pw_hud[e->idx].m12) && !(D_pw_btn[e->idx][0] & D_pw_hud[e->idx].m18) && p->fE8 < 2.625f) {
            lim = e->f14 * 2.625f;
            v += 0.1875f;
            if (lim < v) {
                v = lim;
            }
        }
        { register f32 z asm("$f4") = 0.0f; register f32 t asm("$f0") = e->f4; if (t != z) {
            v = e->f14 * 3.75f;
        } }
        if (e->f14 * 3.75f < v) {
            v = e->f14 * 3.75f;
        }
        p->fEC = v;
        if (p->fF0 < v - p->fE8) {
            p->fE8 = p->fE8 + p->fF0;
        } else {
            p->fE8 = v;
        }
        if (v - p->fE8 < -p->fF4) {
            p->fE8 = p->fE8 - p->fF4;
        } else {
            p->fE8 = v;
        }
        if (e->w8 == 0) {
            if (e->f4 == 0.0f) {
                if (D_pw_btn[e->idx][0] & D_pw_hud[e->idx].m22) {
                    if (*(u16 *)(D_pw_cam[e->idx].p4 + 4) == 3) {
                        bsearchFactor5TableByU16Key(0x4D, 0x78, 0x40);
                    } else {
                        play3DSoundEvent(0, (u8 *)p + 4, (u8 *)p + 0x28, 20.0f, 0.0f, 0, 0x20, 0x5A, 0);
                    }
                    e->f4 += dt;
                    play3DSoundEvent(0, (u8 *)p + 4, (u8 *)p + 0x28, 20.0f, 0.4f, 0, 0x25, 0x7A, 0);
                    scheduleSceneFormatMessageTimed(p, 8);
                    setCraftAnimationSlotParams(0, 2, 1.5f);
                }
            } else {
                e->f4 += dt;
                if (e->f4 > 1.0f) {
                    e->f4 = 1.0f;
                    e->w8 = 1;
                    p->fF8 = 1.2800001f;
                }
            }
        } else if (e->f4 == 1.0f) {
            if ((D_pw_btn[e->idx][0] & D_pw_hud[e->idx].m22) || (D_pw_btn[e->idx][0] & D_pw_hud[e->idx].m12)) {
                if (*(u16 *)(D_pw_cam[e->idx].p4 + 4) == 3) {
                    bsearchFactor5TableByU16Key(0x37, 0x78, 0x40);
                } else {
                    play3DSoundEvent(0, (u8 *)p + 4, (u8 *)p + 0x28, 20.0f, 0.0f, 0, 0x1F, 0x5A, 0);
                }
                e->f4 -= dt;
            }
        } else {
            e->f4 -= dt;
            if (e->f4 < 0.0f) {
                e->f4 = 0.0f;
                e->w8 = 0;
                p->fF8 = 1.6f;
            }
        }
        e->f14 = e->f4 * 0.5f + 1.0f;
        r = (1.0f - e->f4) * 10.0f;
        buildRotationMatrixFromEulerAngles(e->pC + 0x1C, 0.0f, 0.0f, -r);
        buildRotationMatrixFromEulerAngles(e->p10 + 0x1C, 0.0f, 0.0f, r);
    }
    k = 0.28125f;
    updatePlayerCraftPhysics(p, dt);
    { f32 t = e->f14; computeBootConfigScaledVec4(e->idx, k, k, D_main_bss_8013800C + e->idx * 0x2A0, t, dt); }
}

typedef struct {
    f32 x, y, z;
} XfV3;
typedef struct {
    XfV3 pos;
    XfV3 a;
    XfV3 b;
    XfV3 c;
} XfFrame;
typedef struct {
    u8 pad0[4];
    u8 *p4;
    u8 pad8[0x13C];
} XfE;
extern u8 xfCraftBytes[][0x2A0] __asm__("D_main_bss_80137DBC");
extern XfE xfD18[] __asm__("D_main_bss_80138D18");
extern XfV3 xfVecs[] __asm__("D_mission_overlay_801097C4");
extern u8 xfCues[] __asm__("D_mission_overlay_80109730");
void xfLookupHmt(s32, char *, s32, void *, void *, s32) __asm__("lookupHmtTextureByName");
void xfAccum(void *, void *, void *) __asm__("accumulateVectorInObjectFrame");
void xfNormalize(void *) __asm__("normalize_vector");
f32 xfDot(void *, void *) __asm__("vec3Dot");
f32 xfSinApprox(f32) __asm__("constMinusSinfApprox");
void xfCross(void *, void *, void *) __asm__("vec3Cross");
void xfQuat(void *, void *, f32) __asm__("quatFromAxisAngleSafe");
void xfRotate(void *, void *, void *) __asm__("rotateVec3ByQuat");
u16 xfCue(s32, u16, void *, void *, s32, f32, f32) __asm__("dispatchCueByCategory");

void xfImpl(s32 *arg0, u32 arg1, XfV3 *out) __asm__("playerXwingFireBlaster");
void xfImpl(s32 *arg0, u32 arg1, XfV3 *out) {
    XfFrame f;
    f32 v[4];
    f32 ax[4];
    f32 q[4];
    u8 *pl;
    f32 ang;

    pl = xfCraftBytes[arg0[0]];
    xfLookupHmt(*(s32 *)pl, (arg1 & 2) ? "b" : "a", arg1 & 1, &f, NULL, 0);
    if (*(u16 *)(xfD18[arg0[0]].p4 + 4) == 3) {
        xfAccum(&f, &xfVecs[arg1], pl);
    }
    if (*(u16 *)((u8 *)arg0 + 0x1A) != 0xFFFF) {
        v[0] = *(f32 *)(arg0 + 7) - f.pos.x;
        v[1] = *(f32 *)(arg0 + 8) - f.pos.y;
        v[2] = *(f32 *)(arg0 + 9) - f.pos.z;
        xfNormalize(v);
        ang = xfSinApprox(xfDot(&f.a, v)) * 57.295776f;
        xfCross(ax, &f.a, v);
        if (*(u16 *)(xfD18[arg0[0]].p4 + 4) != 3) {
            xfQuat(q, ax, ang * 0.4f);
        } else {
            xfQuat(q, ax, ang * 0.8f);
        }
        *(XfV3 *)v = f.a;
        xfRotate(q, v, &f.a);
        *(XfV3 *)v = f.b;
        xfRotate(q, v, &f.b);
    }
    xfCue(0, *(u16 *)(pl + 0xB6), &f, xfCues, 1, 12.5f, *(f32 *)(pl + 0x16C));
    if (out != NULL) {
        *out = f.pos;
    }
}

typedef struct {
    /* 0x00 */ s32 idx;
    /* 0x04 */ f32 f4;
    /* 0x08 */ u32 w8;
    /* 0x0C */ u8 padC[0xC];
    /* 0x18 */ u8 b18;
    /* 0x19 */ u8 b19;
    /* 0x1A */ u16 h1A;
    /* 0x1C */ u8 b1C[0x10];
} XesNpc;

typedef struct {
    /* 0x000 */ s32 mesh;
    /* 0x004 */ u8 pad4[0xB0];
    /* 0x0B4 */ u16 hB4;
    /* 0x0B6 */ u16 hB6;
    /* 0x0B8 */ s32 index;
    /* 0x0BC */ u8 padBC[0x158 - 0xBC];
    /* 0x158 */ u16 h158;
    /* 0x15A */ u8 pad15A[2];
    /* 0x15C */ s32 w15C;
    /* 0x160 */ f32 f160;
    /* 0x164 */ f32 f164;
    /* 0x168 */ f32 f168;
    /* 0x16C */ u8 pad16C[0x178 - 0x16C];
    /* 0x178 */ s32 w178;
    /* 0x17C */ u8 pad17C[0x2A0 - 0x17C];
} XesPlayer;

typedef struct {
    u8 pad0[0x1A];
    u16 mask1A;
    u8 pad1C;
    u8 mask1D;
    u16 mask1E;
    u8 pad20[4];
} XesHud;

typedef struct {
    u8 pad0[4];
    u8 *p4;
    u8 pad8[0x144 - 8];
} XesCam;

extern u8 D_main_bss_80137DBC[];
extern u16 D_main_bss_80130B88[][3];
extern XesHud D_mission_overlay_8010BE18[];
extern XesCam D_main_bss_80138D18[];
extern u8 gGameSettings;
void playerXwingFireBlaster(void *, u32, void *);
void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
void playSpeechClipOncePerLevel(s32, s32);
u8 tickHudInstanceTargetingAndSpawns(s32, f32, void *, s32, s32, void *, s32);
void dispatchHudInstanceWeaponEffect(s32, s32, void *, s32, s32, s32, s32);
s32 findLockOnTarget(void *, void *, u16, f32, f32, f32);
void tickCraftAnimationSlot(s32, f32);

#define XP ((XesPlayer *)D_main_bss_80137DBC)

void playXwingEngineSound(XesNpc *e, f32 dt) {
    XesPlayer *p;
    u8 *b4;
    f32 f;
    struct { u8 b[0x10]; } sp28;
    u16 out[2];
    register void *a1 asm("$5");
    s32 mode;
    u32 w;

    p = &XP[e->idx];
    b4 = D_main_bss_80137DBC - 4;
    if (*(u16 *)(b4 + p->index * 0x2A0 + 0x184) & 1) {
        D_mission_overlay_8010BC80[e->idx] = e->w8;
        D_mission_overlay_8010BC90[e->idx] = e->f4;
        f = p->f160;
        if (0.0f < f) {
            p->f160 = f - dt;
        } else if (D_main_bss_80130B88[e->idx][0] & D_mission_overlay_8010BE18[e->idx].mask1A) {
          w = e->w8;
          if (w != 1) {
            mode = *(s32 *)(b4 + e->idx * 0x2A0 + 0x160);
            if (mode == 1) {
                p->f160 = f + p->f168;
                playerXwingFireBlaster(e, p->h158, 0);
                playerXwingFireBlaster(e, p->h158 + 1, 0);
                p->h158 ^= 2;
                play3DSoundEvent(0, (u8 *)p + 4, (u8 *)p + 0x28, 20.0f, 0.2f, 0, 3, 0x5A, 0x28);
            } else if (mode == 2) {
                p->f160 = (f32)((f64)f + (f64)p->f168 * 1.5);
                playerXwingFireBlaster(e, 0, 0);
                playerXwingFireBlaster(e, 1, 0);
                playerXwingFireBlaster(e, 2, 0);
                playerXwingFireBlaster(e, 3, 0);
                play3DSoundEvent(0, (u8 *)p + 4, (u8 *)p + 0x28, 20.0f, 0.2f, 0, 4, 0x5A, 0x28);
            } else {
                p->f160 = f + p->f164;
                playerXwingFireBlaster(e, p->h158, &sp28);
                p->h158 = (p->h158 + 1) & 3;
                play3DSoundEvent(0, &sp28, (u8 *)p + 0x28, 20.0f, 0.2f, 0, 2, 0x5A, 0x28);
            }
          } else if (e->b18 == 0) {
            e->b18 = w;
            if (e->f4 > 0.95f) {
                playSpeechClipOncePerLevel(gGameSettings != 0xF ? 0x134 : 0x28C, 9);
            }
          }
        } else {
            e->b18 = 0;
        }
        if (tickHudInstanceTargetingAndSpawns(0, dt, (u8 *)p + 4, p->mesh, (D_main_bss_80130B88[e->idx][0] & 0xFF) & D_mission_overlay_8010BE18[e->idx].mask1D, out, p->hB6)) {
            dispatchHudInstanceWeaponEffect(0, p->hB6, (u8 *)p + 4, p->mesh, p->w178, e->b19, out[0]);
            e->b19 ^= 1;
        }
        if (D_main_bss_80130B88[e->idx][0] & D_mission_overlay_8010BE18[e->idx].mask1E) {
            p->w15C++;
            if (p->w15C >= 3) {
                p->w15C = 0;
            }
            p->h158 = 0;
        }
    }
    a1 = (u8 *)p + 4;
    {
        f32 range = 9.0f;
        u8 *bp = e->b1C;
        s32 hh = e->h1A;
        s32 r;
        s32 t;
        if (*(u16 *)(D_main_bss_80138D18[e->idx].p4 + 4) == 3) {
            range = 16.0f;
        }
        r = findLockOnTarget(a1, bp, hh, range, 0.992f, 12.5f);
        t = r & 0xFFFF;
        out[0] = r;
        if (t != 0xFFFF) {
            e->h1A = r;
        } else {
            e->h1A = t;
        }
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
} FalconUpdPlayer;

typedef struct {
    /* 0x00 */ s32 w0;
    /* 0x04 */ s32 *state;
    /* 0x08 */ void *w8;
    /* 0x0C */ s32 mesh;
    /* 0x10 */ u8 pad10[6];
    /* 0x16 */ u16 h16;
} FalconUpdNpc;

typedef XesCam FalconUpdCam;

#define FUP ((FalconUpdPlayer *)D_main_bss_80137DBC)
extern u16 D_main_bss_80139560[];
extern u8 D_mission_overlay_801097BC[];
extern u8 D_main_bss_80137DBC[];
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_801097BC[];
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];

void *walkMeshdef0List(char *);
void playerXwingInit(s32 *, s32, s32);
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
void playWeaponFireSound(s32 *, s32);
void playXwingEngineSound(XesNpc *, f32);
void tryPlaySpatialSoundWithGates(void *, void *);
void enqueueMeshTypeForCleanup(s32);
void addNpcToVisibilityBucket(s32, s32, void *, f32);
void advanceNpcOnCurvedPath(s32, s32, void *, s32);
void updatePlayerHudFrame(s32, void *, void *);

s32 playerXwingUpdate(FalconUpdNpc *arg0, s32 arg1, u32 *arg2) {
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
            s0 = rs_malloc(0x28, 0);
            arg0->state = s0;
            p = &FUP[(s32)*(f32 *)arg2];
            p->mesh = (s32)walkMeshdef0List("xwing");
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
            playerXwingInit(s0, (s32)*q, flag);
            p->w178 = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
            allocateCraftAnimationStateForSlot(p, 0, D_mission_overlay_801097BC);
            popNpcSlotFromTail(D_main_bss_80139560[1], (void *)arg0);
            popNpcSlotFromTail(D_main_bss_80139560[14], (void *)arg0);
            p->ctx = allocateAndInitCraftNpcContext(0.25f, 0.25f, 2);
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
            playerXwingInit(s0, p->index, 0x40);
            resetTransientPlayerStateFlags();
            resetCraftAnimationStateForSlot(0);
            return 1;
        case 2:
            p = &FUP[*s0];
            cancelSceneQueueHandle(p);
            destroySceneNpcsAndUnlink(p);
            teardownHudInstancesAndUnbindNpcs();
            freePlayerAuxBuffersIfActive(0);
            rs_free((void *)p->ctx);
            releaseMeshAsset(p->mesh);
            return 1;
        case 3:
            playWeaponFireSound(s0, *arg2);
            playXwingEngineSound((XesNpc *)s0, *(f32 *)arg2);
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

u8 isWeaponSlotReady(u8 arg0) {
    u8 ret;
    ret = 0;
    if ((D_mission_overlay_8010BC80[arg0] != 1) || !(0.95f < D_mission_overlay_8010BC90[arg0])) {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B4EC0", fake_func_800B58B4);

// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
const u32 rodat_pad_0B4EC0 = 0x24640001;
