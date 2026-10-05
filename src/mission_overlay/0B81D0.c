#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B81D0", D_mission_overlay_800A5B20);

typedef struct {
    s32 object;
    u8 p4[0xB4 - 0x4];
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
    f32 f10C;
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
    s32 f178;
    u8 p17C[4];
    s16 f180;
} CraftPlayer;

typedef struct {
    s32 idx;
    u16 h4;
    u8 p6[2];
    s32 w8;
    s32 wC;
    u8 name[4];
    s32 mat;
} CraftAnim;

extern CraftPlayer sCraftPlayers[] __asm__("D_main_bss_80137DBC");
extern s32 D_main_bss_80130B58;
void initPlayerCraftMovementMode(CraftPlayer *);
s32 lookupHmtMaterialByName(s32, char *, void *);

void playerYwingInit(CraftAnim *anim, s32 idx, s16 arg2) {
    CraftPlayer *p;
    f32 speed;

    p = (CraftPlayer *)((u8 *)sCraftPlayers + idx * 0x2A0);
    p->f180 = arg2;
    anim->idx = idx;
    p->fB4 = 1;
    initPlayerCraftMovementMode(p);
    speed = 350.0f;
    if (D_main_bss_80130B58 & 0x40) {
        speed = 40.0f;
    }
    p->fC0 = speed;
    p->fC4 = speed;
    p->f11C = (p->f14C = (p->f13C = 0));
    p->fE0 = (p->fDC = (p->fD8 = 0));
    p->f158 = 0;
    p->f160 = 0;
    p->fF0 = 0.025f;
    p->fE8 = 2.25f;
    p->fEC = 2.25f;
    p->fF4 = 0.112500004f;
    p->fF8 = 1.3f;
    p->fFC = 2.0f;
    p->f104 = 15.0f;
    p->f108 = 10.0f;
    p->f110 = -40.0f;
    p->f114 = -35.0f;
    p->f118 = 60.0f;
    p->f120 = 60.0f;
    p->f124 = 180.0f;
    p->f130 = 0.75f;
    p->f134 = 2.0f;
    p->f138 = 10.0f;
    p->f140 = 5.0f;
    p->f144 = 40.0f;
    p->f148 = 5.0f;
    p->f150 = 5.0f;
    p->f154 = 40.0f;
    p->f164 = 0.25f;
    p->f128 = 0.1f;
    p->f170 = 0;
    p->f12C = 0.15f;
    p->f168 = 0.5f;
    p->f174 = 0.25f;
    anim->h4 = 0xFFFF;
    anim->w8 = 0;
    anim->wC = 0;
    anim->mat = lookupHmtMaterialByName(p->object, "tpgn_trn", anim->name);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B81D0", tickCraftAbilityCooldown);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B81D0", D_mission_overlay_800A5B9C);

typedef struct {
    u8 pad0[0x4C];
    u32 flags;
    f32 pos[3];
    f32 scale[3];
    f32 quat[4];
    f32 off[3];
} EffectCfg;

typedef struct {
    s32 index;
    u16 target;
    u16 pad6;
    f32 f8;
    f32 fC;
    EffectCfg *cfg;
    u8 *mat;
} EffectOrient;

extern s32 findLockOnTarget(void *, void *, u16, f32, f32, f32);
extern void mat34CrossRowsAndCopyPos(void *, void *, f32, u32);
extern void mat3x3InverseInto(void *, void *);
extern void transformVec3ByMat34(void *, void *, void *);
extern f32 normalize_vector(void *);
extern f32 vec3Dot(void *, void *);
extern f32 sinfApprox(f32);
extern f32 constMinusSinfApprox(f32);
extern void clearVec4QuadStruct(void *);
extern void addVec3At0x24(void *, f32, f32, f32);
extern void applyScaleToMat3x4(void *, f32, f32, f32);
extern void composeQuatToMat3x4(void *, void *);
extern void composeRotationMatrixSlot0(void *, f32);
extern void composeRotationMatrixSlot1(void *, f32);
typedef struct {
    u8 pad0[4];
    struct {
        u8 pad0[4];
        u16 kind;
    } *info;
    u8 pad8[0x13C];
} EffMeta;
extern EffMeta gEffMeta[] __asm__("D_main_bss_80138D18");
extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern void accumulateVectorInObjectFrame(void *, void *, void *);
extern u8 D_mission_overlay_801098FC[];
extern u8 D_mission_overlay_80109908[];

void orientEffectToVelocity(s32 *arg0, EffectOrient *st, f32 dt) {
    u8 sp18[0x30];
    u8 sp48[0x30];
    f32 sp78[4];
    f32 sp88[4];
    f32 sp98[4];
    u8 spA8[0x30];
    s32 id;
    f32 yaw;
    f32 keep;
    f32 len;
    f32 cur;
    f32 roll;
    u8 *mat;
    EffectCfg *cfg;
    u32 fl;

    id = findLockOnTarget(arg0 + 1, sp88, st->target, 11.0f, 0.965f, 10.0f);
    if ((id & 0xFFFF) != 0xFFFF) {
        st->target = id;
        mat34CrossRowsAndCopyPos(sp18, arg0 + 1, 1.0f, id);
        mat3x3InverseInto(sp48, sp18);
        lookupHmtTextureByName(*arg0, "scnd", 0, spA8, 0, 0);
        if (gEffMeta[st->index].info->kind == 3) {
            accumulateVectorInObjectFrame(spA8, D_mission_overlay_80109908, arg0);
        }
        transformVec3ByMat34(sp48, sp88, sp78);
        transformVec3ByMat34(sp48, spA8, sp98);
        sp78[0] -= sp98[0];
        sp78[1] -= sp98[1];
        sp78[2] -= sp98[2];
        normalize_vector(sp78);
        keep = sp78[1];
        sp78[1] = 0.0f;
        len = normalize_vector(sp78);
        st->f8 = sinfApprox(vec3Dot(sp78, D_mission_overlay_801098FC)) * 57.295776f;
        if (keep < 0.0f) {
            yaw = constMinusSinfApprox(len) * 57.295776f;
            if (22.5f < yaw) {
                yaw = 22.5f;
            }
        } else {
            yaw = 0.0f;
        }
    } else {
        st->f8 = 0.0f;
        yaw = 0.0f;
    }
    cur = st->fC;
    if (cur < st->f8) {
        st->fC = cur + dt * 15.0f;
        if (st->fC > st->f8) {
            st->fC = st->f8;
        }
    } else {
        st->fC = cur - dt * 15.0f;
        if (st->fC < st->f8) {
            st->fC = st->f8;
        }
    }
    mat = st->mat + 0x1C;
    cfg = st->cfg;
    roll = st->fC;
    clearVec4QuadStruct(mat);
    if (cfg->flags & 1) {
        addVec3At0x24(mat, -cfg->pos[0], -cfg->pos[1], -cfg->pos[2]);
    }
    if (cfg->flags & 2) {
        applyScaleToMat3x4(mat, cfg->scale[0], cfg->scale[1], cfg->scale[2]);
    }
    if (cfg->flags & 4) {
        composeQuatToMat3x4(mat, cfg->quat);
    }
    composeRotationMatrixSlot0(mat, yaw);
    composeRotationMatrixSlot1(mat, roll);
    fl = cfg->flags;
    if ((fl & 9) == 9) {
        addVec3At0x24(mat, cfg->off[0] + cfg->pos[0], cfg->off[1] + cfg->pos[1], cfg->off[2] + cfg->pos[2]);
    } else if ((fl & 9) == 8) {
        addVec3At0x24(mat, cfg->off[0], cfg->off[1], cfg->off[2]);
    } else if (fl & 1) {
        addVec3At0x24(mat, cfg->pos[0], cfg->pos[1], cfg->pos[2]);
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B81D0", spawnTexturedExplosionBurst);

typedef struct {
    s32 idx;
    void *p4;
    void *p8;
    void *pC;
    u8 p10[6];
    u16 h16;
} YwNpc;

typedef struct {
    s32 object;
    u8 p4[0xB0];
    u16 hB4;
    u16 hB6;
    s32 wB8;
    s32 wBC;
    u8 pC0[0x178 - 0xC0];
    s32 w178;
    u8 p17C[4];
    u16 h180;
    u8 p182[2];
    f32 f184;
    u8 p188[0x2A0 - 0x188];
} YwPlayer;

typedef struct {
    u8 p0[4];
    struct {
        u8 p0[4];
        u16 h4;
    } *p4;
    u8 p8[0x144 - 8];
} YwMeta;

typedef struct {
    u8 p0[2];
    u16 h2;
    u8 p4[0x18];
    u16 h1C;
} YwNpcTbl;

extern YwPlayer ywPlayers[] __asm__("D_main_bss_80137DBC");
extern YwMeta ywMeta[] __asm__("D_main_bss_80138D18");
extern YwNpcTbl ywNpcTbl __asm__("D_main_bss_80139560");
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_801098DC[];
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];
extern void *rs_malloc(s32, s32);
extern void rs_free(void *);
extern s32 walkMeshdef0List(char *);
extern void loadPlayerStartPosition(void *, void *);
extern void configurePlayerSecondaryWeaponHud(s32, s32, s32, s32);
extern s32 refreshPlayerSecondaryWeaponHud(s32);
extern void allocateCraftAnimationStateForSlot(void *, s32, void *);
extern void popNpcSlotFromTail(u16, void *);
extern void *allocateAndInitCraftNpcContext(f32, f32, s32);
extern void spawnNpcOfType(void *, void *, s32, s32);
extern void resetTransientPlayerStateFlags(void);
extern void resetCraftAnimationStateForSlot(s32);
extern void cancelSceneQueueHandle(void *);
extern void destroySceneNpcsAndUnlink(void *);
extern void releaseMeshAsset(s32);
extern void teardownHudInstancesAndUnbindNpcs(void);
extern void freePlayerAuxBuffersIfActive(s32);
extern void tickCraftAbilityCooldown(void *, s32);
extern void spawnTexturedExplosionBurst(void *, s32);
extern void tryPlaySpatialSoundWithGates(void *, void *);
extern void destroyNpcSlotByIndex(u16);
extern void enqueueMeshTypeForCleanup(s32);
extern void addNpcToVisibilityBucket(s32, s32, void *, f32);
extern void advanceNpcOnCurvedPath(s32, s32, void *, void *);
extern void updatePlayerHudFrame(s32, void *, void *);

s32 playerYwingUpdate(YwNpc *npc, u32 msg, s32 *arg) {
    YwPlayer *pl;
    void *anim;
    s32 s2;
    u16 sp10[2];
    f32 *fa;
    void *np;
    anim = npc->p4;
    if ((u16)msg != 2 && (D_mission_overlay_8010CA1C & 4)) {
        return 1;
    }
    switch ((u16)msg) {
    case 1:
        fa = (f32 *)arg;
        anim = rs_malloc(0x18, 0);
        npc->p4 = anim;
        pl = &ywPlayers[(s32)fa[0]];
        pl->object = walkMeshdef0List("ywing");
        pl->hB6 = npc->h16;
        npc->pC = (void *)pl->object;
        npc->p8 = (u8 *)pl + 4;
        if (fa[0] >= 0.0f) {
            ((u16 *)&ywPlayers[(s32)fa[0]])[-1] = npc->h16;
            pl->wB8 = (s32)fa[0];
            s2 = 1;
        } else {
            s2 = 0;
        }
        loadPlayerStartPosition(pl, 0);
        playerYwingInit(anim, (s32)fa[0], s2);
        configurePlayerSecondaryWeaponHud(1, 1, 0xFF, 0);
        pl->w178 = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
        allocateCraftAnimationStateForSlot(pl, 0, D_mission_overlay_801098DC);
        popNpcSlotFromTail(ywNpcTbl.h2, npc);
        popNpcSlotFromTail(ywNpcTbl.h1C, npc);
        pl->wBC = (s32)allocateAndInitCraftNpcContext(0.15f, 0.3f, 3);
        sp10[0] = npc->h16;
        sp10[1] = pl->hB4;
        spawnNpcOfType(attached3DSoundEmitterNpcHandler, sp10, 1, 0x64);
        spawnNpcOfType(attachedMeshOverlayNpcHandler, &npc->h16, 1, 0x64);
        return 1;
    case 12:
        pl = &ywPlayers[((YwNpc *)anim)->idx];
        pl->f184 = 2.0f;
        pl->h180 = (pl->h180 & 0xFFDF) | 0x40;
        loadPlayerStartPosition(pl, (u8 *)pl + 4);
        playerYwingInit(anim, pl->wB8, 0x40);
        resetTransientPlayerStateFlags();
        resetCraftAnimationStateForSlot(0);
        return 1;
    case 2:
        pl = &ywPlayers[((YwNpc *)anim)->idx];
        cancelSceneQueueHandle(pl);
        destroySceneNpcsAndUnlink(pl);
        rs_free((void *)pl->wBC);
        releaseMeshAsset(pl->object);
        teardownHudInstancesAndUnbindNpcs();
        freePlayerAuxBuffersIfActive(0);
        return 1;
    case 3:
        tickCraftAbilityCooldown(anim, arg[0]);
        spawnTexturedExplosionBurst(anim, arg[0]);
        return 1;
    case 5:
        tryPlaySpatialSoundWithGates(&ywPlayers[((YwNpc *)anim)->idx], arg);
        if (*(u16 *)arg != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)arg);
        }
        return 1;
    case 4:
        pl = &ywPlayers[((YwNpc *)anim)->idx];
        enqueueMeshTypeForCleanup(pl->object);
        if (!(pl->h180 & 0x100)) {
            np = (u8 *)pl + 4;
            if (ywMeta[pl->wB8].p4->h4 != 3) {
                addNpcToVisibilityBucket(arg[0], pl->object, np, 1.0f);
                if (!(pl->h180 & 0x80)) {
                    advanceNpcOnCurvedPath(arg[2], arg[0], np, (void *)pl->wBC);
                }
            }
            updatePlayerHudFrame(0, arg, (u8 *)pl + 4);
        }
        return 1;
    default:
        return 1;
    }
}

typedef struct {
    s32 unk0;
    u8 pad4[0xB2];
    u16 unkB6;
    u8 padB8[0xB4];
    f32 unk16C;
    u8 pad170[0x130];
} EffectCueSrc;

typedef struct {
    u8 pad0[4];
    struct {
        u8 pad0[4];
        u16 unk4;
    } *unk4;
    u8 pad8[0x13C];
} EffectCueMeta;

typedef struct {
    f32 x, y, z;
} EffectCueVec;

extern EffectCueSrc D_main_bss_80137DBC[];
extern EffectCueMeta D_main_bss_80138D18[];
extern char D_mission_overlay_800A5B9C[];
extern u8 D_mission_overlay_801098B0[];
extern EffectCueVec D_mission_overlay_801098E4[];
void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
void accumulateVectorInObjectFrame(void *, void *, void *);
u16 dispatchCueByCategory(s32, u16, void *, void *, s32, f32, f32);

void emitTexturedEffectCue(s32 *arg0, s32 arg1, EffectCueVec *arg2) {
    struct {
        EffectCueVec v;
        u8 pad[0x20];
    } sp20;
    s32 s2;
    EffectCueSrc *s1;
    char *name = D_mission_overlay_800A5B9C;

    s2 = arg1 & 1;
    s1 = &D_main_bss_80137DBC[*arg0];
    lookupHmtTextureByName(s1->unk0, name, s2, &sp20.v, 0, 0);
    if (D_main_bss_80138D18[*arg0].unk4->unk4 == 3) {
        accumulateVectorInObjectFrame(&sp20.v, &D_mission_overlay_801098E4[s2], s1);
    }
    dispatchCueByCategory(0, s1->unkB6, &sp20.v, D_mission_overlay_801098B0, 1, 12.5f, s1->unk16C);
    *arg2 = sp20.v;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B81D0", fake_func_800B89F4);

static u32 D_mission_overlay_800A5C18[] __attribute__((section(".rodata"))) = { 0, 0x27BDFFC8 };
