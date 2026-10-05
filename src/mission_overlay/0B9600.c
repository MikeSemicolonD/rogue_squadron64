#include "common.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B9600", D_mission_overlay_800A5C20);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B9600", D_mission_overlay_800A5C28);

#include "common_types.h"
typedef struct {
    s32 f00;
    u8 p04[0x18 - 4];
    s32 f18;
    u8 f1C;
    u8 f1D;
    u8 p1E[2];
    u16 f20;
} VwHdr;
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
    u8 p182[0x190 - 0x182];
    s32 f190;
    u8 p194[0x2A0 - 0x194];
} VwPlayer;

extern VwPlayer sVwPlayers[] __asm__("D_main_bss_80137DBC");
extern s32 D_main_bss_80130B58;
void initPlayerCraftMovementMode(VwPlayer *);
s32 lookupHmtMaterialByName(s32, char *, void *);

void playerVwingInit(s32 *a0, s32 arg1, s32 arg2)
{
  VwHdr *arg0 = (VwHdr *)a0;
  VwPlayer *p = &sVwPlayers[arg1];
  f32 v;
  register f32 c asm("$f10");
  p->f180 = arg2;
  arg0->f00 = arg1;
  p->fB4 = 3;
  initPlayerCraftMovementMode(p);
  v = 150.0f;
  if (D_main_bss_80130B58 & 0x40) {
    v = 40.0f;
  }
  p->fC0 = v;
  p->fC4 = v;
  p->f13C = 0;
  p->f14C = 0;
  p->f11C = 0;
  p->fD8 = 0;
  p->fDC = 0;
  p->fE0 = 0;
  p->f158 = 0;
  p->f160 = 0;
  p->fF0 = 0.14999999f;
  p->fE8 = 3.0f;
  p->fEC = 3.0f;
  p->fF4 = 0.33333334f;
  p->fF8 = 1.6f;
  p->fFC = 1.5f;
  p->f104 = 15.0f;
  p->f108 = 20.0f;
  p->f110 = -40.0f;
  p->f114 = -45.0f;
  p->f118 = 50.0f;
  p->f120 = 45.0f;
  p->f124 = 75.0f;
  p->f138 = 20.0f;
  p->f140 = 10.0f;
  p->f148 = 10.0f;
  p->f154 = 50.0f;
  p->f128 = 0.25f;
  p->f12C = 0.25f;
  c = 0.2f;
  p->f164 = c;
  p->f130 = 0.75f;
  p->f134 = 1.75f;
  p->f144 = 60.0f;
  p->f150 = 5.0f;
  p->f168 = 0.05f;
  arg0->f18 = 0;
  arg0->f1C = 0;
  arg0->f1D = 0;
  p->f170 = 0;
  p->f174 = c;
  p->f190 = 0;
  *(s32 *)((u8 *)arg0 + 0xC) = lookupHmtMaterialByName(p->f00, "f_trns_l", (u8 *)arg0 + 4);
  *(s32 *)((u8 *)arg0 + 0x10) = lookupHmtMaterialByName(p->f00, "f_trns_r", (u8 *)arg0 + 8);
  arg0->f20 = 0xFFFF;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B9600", updateVwingEngineEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B9600", orientVwingSubmodelByQuat);

#include "common_types.h"
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
    f32 unk168;
    u8 pad16C[0x178 - 0x16C];
    s32 unk178;
    u8 pad17C[4];
    u16 unk180;
    u8 pad182[0x2A0 - 0x182];
} VwEngPlayer;

typedef struct {
    u8 pad0[0x1A];
    u16 mask1A;
    u8 pad1C;
    u8 mask1D;
    u16 mask1E;
    u8 pad20[4];
} VwHudDef;

typedef struct {
    s32 idx;
    u8 pad4[0x10];
    f32 f14;
    f32 f18;
    u8 b1C;
    u8 b1D;
    u8 b1E;
    u8 pad1F;
    u16 target;
    u8 pad22[2];
    u8 lockBuf[4];
} VwEngine;

extern VwEngPlayer sVwEng[] __asm__("D_main_bss_80137DBC");
#define VWP sVwEng
extern u16 D_main_bss_80130B88[][3];
extern VwHudDef D_mission_overlay_8010BE18[];
extern u8 gGameSettings;
extern s32 gPlayersRaw[] __asm__("gPlayers");

extern void tickCraftAnimationSlot(s32, f32);
extern u8 tickHudInstanceTargetingAndSpawns(s32, f32, void *, s32, s32, void *, s32);
extern void dispatchHudInstanceWeaponEffect(s32, s32, void *, s32, s32, s32, s32);
extern void orientVwingSubmodelByQuat(VwEngine *, u16, f32, s32, void *);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void playSpeechClipOncePerLevel(s32, s32);
extern void playSpeechClipOncePerChange(s32, s32);
extern u16 findLockOnTarget(void *, void *, u16, f32, f32, f32);

void tickVwingEngineAudio(VwEngine *e, f32 dt) {
    f32 sp28[4];
    u16 sp38;
    VwEngPlayer *p;
    s32 mode;
    f32 f;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;
    f32 f7;
    u16 r;
    s32 a0v;
    u8 *g;
    s32 off;

    p = &VWP[e->idx];
    g = (u8 *)sVwEng - 4;
    if (*(u16 *)(g + p->unkB8 * 0x2A0 + 0x184) & 1) {
        if (0.0f < p->unk160) {
            p->unk160 = p->unk160 - dt;
        } else {
            if (D_main_bss_80130B88[e->idx][0] & D_mission_overlay_8010BE18[e->idx].mask1A) {
                mode = *(s32 *)(g + e->idx * 0x2A0 + 0x160);
                if (mode == 1) {
                    f = e->f18;
                    if (f < 30.0f || e->b1C == 0) {
                        e->b1C = 0;
                        if (e->b1D == 0) {
                            p->unk160 = p->unk160 + p->unk168;
                            orientVwingSubmodelByQuat(e, 0, e->f14, (e->b1E % 6) == 0, sp28);
                            e->b1E = e->b1E + 1;
                            orientVwingSubmodelByQuat(e, 1, -e->f14, (e->b1E % 6) == 0, sp28);
                            f2 = e->f14 + dt * 800.0f;
                            e->b1E = e->b1E + 1;
                            e->f14 = f2;
                            if (f2 > 360.0f) {
                                e->f14 = f2 - 360.0f;
                            }
                            f3 = e->f18 + dt * 100.0f;
                            e->f18 = f3;
                            if (f3 > 100.0f) {
                                e->b1C = mode;
                                playSpeechClipOncePerLevel(gGameSettings != 0xF ? 0x12E : 0x212, 1);
                                playSpeechClipOncePerLevel(gGameSettings != 0xF ? 0x12F : 0x213, 1);
                            }
                            play3DSoundEvent(0, sp28, (u8 *)p + 0x28, 20.0f, 0.2f, 0, 2, 0x5A, 0x28);
                        }
                    } else {
                        if (f > 0.0f) {
                            f4 = f - dt * 20.0f;
                            e->f18 = f4;
                            if (f4 < 0.0f) {
                                e->f18 = 0.0f;
                            }
                        }
                        e->b1D = 1;
                        playSpeechClipOncePerLevel(gGameSettings != 0xF ? 0x12D : 0x211, 1);
                    }
                } else {
                    f = e->f18;
                    if (f < 30.0f || e->b1C == 0) {
                        e->b1C = 0;
                        if (e->b1D == 0) {
                            p->unk160 = p->unk160 + p->unk164;
                            orientVwingSubmodelByQuat(e, p->unk158, 0.0f, 1, sp28);
                            p->unk158 = p->unk158 ^ 1;
                            play3DSoundEvent(0, sp28, (u8 *)p + 0x28, 20.0f, 0.2f, 0, 2, 0x5A, 0x28);
                        }
                    } else {
                        if (f > 0.0f) {
                            f5 = f - dt * 20.0f;
                            e->f18 = f5;
                            if (f5 < 0.0f) {
                                e->f18 = 0.0f;
                            }
                        }
                        e->b1D = 1;
                    }
                }
            } else {
                f6 = e->f18;
                if (f6 > 0.0f) {
                    f7 = f6 - dt * 20.0f;
                    e->f18 = f7;
                    if (f7 < 0.0f) {
                        e->f18 = 0.0f;
                    }
                }
                e->b1D = 0;
            }
            if (tickHudInstanceTargetingAndSpawns(0, dt, (u8 *)p + 4, p->unk0, (D_main_bss_80130B88[e->idx][0] & 0xFF) & D_mission_overlay_8010BE18[e->idx].mask1D, &sp38, p->unkB6)) {
                dispatchHudInstanceWeaponEffect(0, p->unkB6, (u8 *)p + 4, p->unk0, p->unk178, p->unk158, sp38);
            }
            if (D_main_bss_80130B88[e->idx][0] & D_mission_overlay_8010BE18[e->idx].mask1E) {
                p->unk158 = 0;
                p->unk15C = p->unk15C ^ 1;
                e->f14 = 0.0f;
                e->b1E = 0;
                if (gPlayersRaw[e->idx * 0xA8 + 0x58] == 1) {
                    playSpeechClipOncePerChange(gGameSettings != 0xF ? 0x12C : 0x210, 9);
                }
            }
        }
    }
    r = findLockOnTarget((u8 *)p + 4, (u8 *)e + 0x24, e->target, 10.0f, 0.987f, 12.5f);
    a0v = r & 0xFFFF;
    sp38 = r;
    if (a0v != 0xFFFF) {
        e->target = r;
    } else {
        e->target = a0v;
    }
    tickCraftAnimationSlot(0, dt);
}

#include "common_types.h"
typedef struct {
    u8 pad0[0x2A0];
} VwSlot;

extern VwSlot D_main_bss_80137DBC[];
typedef struct {
    u8 p0[4];
    u8 *ptr;
    u8 p8[0x144 - 8];
} Row144;

typedef struct {
    u8 p0[2];
    u16 f2;
    u8 p4[0x18];
    u16 f1C;
} Tail;

extern Row144 D_main_bss_80138D18[];
extern Tail D_main_bss_80139560;
extern s32 D_main_bss_80130B58;
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_8010996C[];
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];

extern s32 rs_malloc(s32, s32);
extern void rs_free(s32);
extern s32 walkMeshdef0List(char *);
extern void loadPlayerStartPosition(void *, void *);
extern void playerVwingInit(s32 *, s32, s32);
extern s32 refreshPlayerSecondaryWeaponHud(s32);
extern void allocateCraftAnimationStateForSlot(void *, s32, void *);
extern void popNpcSlotFromTail(u16, void *);
extern s32 allocateAndInitCraftNpcContext(f32, f32, s32);
extern void spawnNpcOfType(void *, void *, s32, s32);
extern void resetTransientPlayerStateFlags(void);
extern void resetCraftAnimationStateForSlot(s32);
extern void cancelSceneQueueHandle(void *);
extern void destroySceneNpcsAndUnlink(void *);
extern void releaseMeshAsset(s32);
extern void teardownHudInstancesAndUnbindNpcs(void);
extern void freePlayerAuxBuffersIfActive(s32);
extern void updateVwingEngineEffect(s32 *, s32);
extern void tryPlaySpatialSoundWithGates(void *, void *);
extern void destroyNpcSlotByIndex(u16);
extern void enqueueMeshTypeForCleanup(s32);
extern void initVec4TripletFromArgs(void *, f32, f32, f32);
extern void mat3x4Multiply(s32, void *, s32);
extern void addNpcToVisibilityBucket(s32, s32, void *, f32);
extern void advanceNpcOnCurvedPath(s32, s32, void *, s32);
extern void updatePlayerHudFrame(s32, void *, void *);

s32 playerVwingUpdate(u8 *npc, s32 msg, u8 *ctx) {
    u16 sp10[2];
    f32 sp18[12];
    s32 *s0;
    u8 *s1;
    s32 flag;
    s32 a2;
    f32 fa0;
    f32 fa1;
    s32 *mem;
    u8 *c1;
    u8 *p4;

    s0 = *(s32 **)(npc + 4);
    if ((msg & 0xFFFF) == 2 || !(D_mission_overlay_8010CA1C & 4)) {
        switch ((u16)msg) {
        case 1:
            c1 = ctx;
            s0 = (s32 *)rs_malloc(0x30, 0);
            *(s32 **)(npc + 4) = s0;
            s1 = (u8 *)&D_main_bss_80137DBC[(s32)*(f32 *)ctx];
            *(s32 *)s1 = walkMeshdef0List("vwing");
            *(u16 *)(s1 + 0xB6) = *(u16 *)(npc + 0x16);
            *(s32 *)(npc + 0xC) = *(s32 *)s1;
            *(u8 **)(npc + 8) = s1 + 4;
            if (*(f32 *)ctx >= 0.0f) {
                *(u16 *)((u8 *)&D_main_bss_80137DBC[(s32)*(f32 *)ctx] - 2) = *(u16 *)(npc + 0x16);
                *(s32 *)(s1 + 0xB8) = (s32)*(f32 *)ctx;
                flag = 1;
            } else {
                flag = 0;
            }
            loadPlayerStartPosition(s1, 0);
            playerVwingInit(s0, (s32)*(f32 *)c1, flag);
            *(s32 *)(s1 + 0x178) = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
            allocateCraftAnimationStateForSlot(s1, 0, D_mission_overlay_8010996C);
            popNpcSlotFromTail(D_main_bss_80139560.f2, npc);
            popNpcSlotFromTail(D_main_bss_80139560.f1C, npc);
            if (D_main_bss_80130B58 & 2) {
                a2 = allocateAndInitCraftNpcContext(0.13f, 0.26f, 0xB);
            } else {
                a2 = allocateAndInitCraftNpcContext(0.2f, 0.15f, 1);
            }
            *(s32 *)(s1 + 0xBC) = a2;
            sp10[0] = *(u16 *)(npc + 0x16);
            sp10[1] = *(u16 *)(s1 + 0xB4);
            spawnNpcOfType(attached3DSoundEmitterNpcHandler, sp10, 1, 0x64);
            spawnNpcOfType(attachedMeshOverlayNpcHandler, npc + 0x16, 1, 0x64);
            return 1;
        case 12:
            s1 = (u8 *)&D_main_bss_80137DBC[*s0];
            *(f32 *)(s1 + 0x184) = 2.0f;
            *(u16 *)(s1 + 0x180) = (*(u16 *)(s1 + 0x180) & 0xFFDF) | 0x40;
            loadPlayerStartPosition(s1, s1 + 4);
            playerVwingInit(s0, *(s32 *)(s1 + 0xB8), 0x40);
            resetTransientPlayerStateFlags();
            resetCraftAnimationStateForSlot(0);
            return 1;
        case 2:
            s1 = (u8 *)&D_main_bss_80137DBC[*s0];
            cancelSceneQueueHandle(s1);
            destroySceneNpcsAndUnlink(s1);
            rs_free(*(s32 *)(s1 + 0xBC));
            releaseMeshAsset(*(s32 *)s1);
            teardownHudInstancesAndUnbindNpcs();
            freePlayerAuxBuffersIfActive(0);
            return 1;
        case 3:
            updateVwingEngineEffect(s0, *(s32 *)ctx);
            tickVwingEngineAudio((VwEngine *)s0, *(f32 *)ctx);
            return 1;
        case 5:
            tryPlaySpatialSoundWithGates(&D_main_bss_80137DBC[*s0], ctx);
            if (*(u16 *)ctx != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)ctx);
            }
            return 1;
        case 4:
            s1 = (u8 *)&D_main_bss_80137DBC[*s0];
            enqueueMeshTypeForCleanup(*(s32 *)s1);
            if (!(*(u16 *)(s1 + 0x180) & 0x100)) {
                if (*(u16 *)(D_main_bss_80138D18[*(s32 *)(s1 + 0xB8)].ptr + 4) != 3) {
                    if (D_main_bss_80130B58 & 2) {
                        initVec4TripletFromArgs(sp18, 1.4f, 1.4f, 1.4f);
                        mat3x4Multiply(*(s32 *)s1 + 0x28, sp18, *(s32 *)s1 + 0x28);
                    }
                    p4 = s1 + 4;
                    addNpcToVisibilityBucket(*(s32 *)ctx, *(s32 *)s1, p4, 1.0f);
                    if (!(*(u16 *)(s1 + 0x180) & 0x80)) {
                        advanceNpcOnCurvedPath(*(s32 *)(ctx + 8), *(s32 *)ctx, p4, *(s32 *)(s1 + 0xBC));
                    }
                }
                updatePlayerHudFrame(0, ctx, s1 + 4);
            }
            return 1;
        }
    }
    return 1;
}
