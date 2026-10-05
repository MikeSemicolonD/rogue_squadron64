#include "common.h"
#include "common_types.h"

#include "mission_overlay/0AEFF0.h"

typedef struct {
    u16 onTime;
    u16 count;
    u16 *strength;
    u16 *period;
} RumbleDef;

void serviceRumblePakMotors(void);
s32 clearControllerPakPresence(u8);
extern u16 D_mission_overlay_801096BC[];
extern u16 D_mission_overlay_801096D8[];
extern u16 D_mission_overlay_801096F4[];
extern u16 D_mission_overlay_80109710[];
extern u16 D_mission_overlay_8010B7B0[13][20];
extern u16 D_mission_overlay_8010B9C0[13][20];
extern RumbleDef sRumbleDefs[] __asm__("D_mission_overlay_8010BBD0");

void initPlayerCraftTrailBuffers(u8 *arg0) {
    s32 i;
    s32 j;
    f32 a;
    f32 b;

    serviceRumblePakMotors();
    clearControllerPakPresence(arg0[0xBB]);
    *(s32 *)(arg0 + 0x1C4) = 0;
    *(s32 *)(arg0 + 0x1C0) = -1;
    for (i = 0; i < 13; i++) {
        sRumbleDefs[i].onTime = D_mission_overlay_801096BC[*(s32 *)(arg0 + 0xB8)];
        sRumbleDefs[i].count = D_mission_overlay_801096D8[*(s32 *)(arg0 + 0xB8)];
        sRumbleDefs[i].strength = D_mission_overlay_8010B7B0[i];
        sRumbleDefs[i].period = D_mission_overlay_8010B9C0[i];
        a = D_mission_overlay_801096F4[i];
        b = D_mission_overlay_80109710[i];
        for (j = 0; j < D_mission_overlay_801096D8[*(s32 *)(arg0 + 0xB8)]; j++) {
            D_mission_overlay_8010B7B0[i][j] = a;
            D_mission_overlay_8010B9C0[i][j] = b;
            a *= 1.1f;
            b *= 0.9f;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", computeCraftSelectTurnFromInput);

extern s32 D_mission_overlay_8010B740[];
extern u8 D_mission_overlay_8010B780[];
extern u8 gGameSettings;

void populateCutsceneSubtitleTextIds(void) {
    s32 i;
    u8 *p;

    i = 13;
    p = D_mission_overlay_8010B780 + i;
    do {
        *p-- = 0;
    } while (--i >= 0);
    D_mission_overlay_8010B740[0] = (gGameSettings != 0xF) ? 0x104 : 0x28C;
    D_mission_overlay_8010B740[1] = (gGameSettings != 0xF) ? 0x272 : 0x28C;
    D_mission_overlay_8010B740[2] = (gGameSettings != 0xF) ? 0x134 : 0x28C;
    D_mission_overlay_8010B740[3] = (gGameSettings != 0xF) ? 0x122 : 0x206;
    D_mission_overlay_8010B740[4] = (gGameSettings != 0xF) ? 0x123 : 0x207;
    D_mission_overlay_8010B740[5] = (gGameSettings != 0xF) ? 0x124 : 0x208;
    D_mission_overlay_8010B740[6] = (gGameSettings != 0xF) ? 0x12B : 0x20F;
    D_mission_overlay_8010B740[7] = (gGameSettings != 0xF) ? 0x12E : 0x212;
    D_mission_overlay_8010B740[8] = (gGameSettings != 0xF) ? 0x12F : 0x213;
    D_mission_overlay_8010B740[9] = (gGameSettings != 0xF) ? 0x12D : 0x211;
    D_mission_overlay_8010B740[10] = (gGameSettings != 0xF) ? 0x130 : 0x214;
    D_mission_overlay_8010B740[11] = (gGameSettings != 0xF) ? 0x131 : 0x28C;
    D_mission_overlay_8010B740[12] = (gGameSettings != 0xF) ? 0x132 : 0x28C;
    D_mission_overlay_8010B740[13] = (gGameSettings != 0xF) ? 0x133 : 0x28C;
}

extern void playSpeechClip(s32, s32, f32, u16);
extern s32 D_mission_overlay_801096B4;
extern f32 D_mission_overlay_801096B0;
extern u8 D_mission_overlay_801096B8;
extern s32 D_mission_overlay_80109680[];
extern s32 D_mission_overlay_80109698[];
extern u16 rand(void);

static __inline__ void playOnceInline(s32 arg0, s32 arg1) {
    if (arg0 != D_mission_overlay_801096B4 && arg0 != 0x28C) {
        playSpeechClip(arg0, 0x73, 0, arg1);
        D_mission_overlay_801096B4 = arg0;
        D_mission_overlay_801096B0 = 5.0f;
    }
}

void playRandomCutsceneVoiceLine(u8 *arg0) {
    s32 s0 = D_mission_overlay_801096B4;

    if (D_mission_overlay_801096B0 > 0.0f) {
        return;
    }
    if ((f32)(rand() & 0x3F) * 0.015625f >= 0.5f) {
        return;
    }
    if (s0 == D_mission_overlay_801096B4) {
        do {
            if (gGameSettings != 0xF) {
                s0 = D_mission_overlay_80109680[(s32)((f32)(rand() & 0x3F) / 10.666667f)];
            } else {
                s0 = D_mission_overlay_80109698[(s32)((f32)(rand() & 0x3F) / 10.666667f)];
            }
        } while (s0 == D_mission_overlay_801096B4);
    }
    switch (*(u16 *)(arg0 + 0xB4)) {
    case 0:
    case 1:
    case 8:
        if (D_mission_overlay_801096B8 == 1) {
            if ((f32)(rand() & 0x3F) * 0.015625f < 0.2f && D_mission_overlay_801096B4 != 0x112 && *(f32 *)(arg0 + 0xC0) / *(f32 *)(arg0 + 0xC4) > 0.25f) {
                s0 = 0x112;
                D_mission_overlay_801096B4 = s0;
                goto play;
            }
            if ((f32)(rand() & 0x3F) * 0.015625f < 0.1f) {
                do {
                    s0 = (s32)((f32)(rand() & 0x3F) * 0.03125f + (gGameSettings != 0xF ? 265.0f : 652.0f));
                } while (s0 == D_mission_overlay_801096B4);
                playOnceInline(s0, 0);
                D_mission_overlay_801096B4 = s0;
                s0 = (s32)((f32)(rand() & 0x3F) * 0.03125f + (gGameSettings != 0xF ? 620.0f : 652.0f));
                goto play;
            } else {
                if ((f32)(rand() & 0x3F) * 0.015625f < 0.1f) {
                    s0 = (gGameSettings != 0xF) ? 0x102 : 0x28C;
                    D_mission_overlay_801096B4 = s0;
                }
                goto play;
            }
        }
        D_mission_overlay_801096B4 = s0;
        goto play;
    default:
        D_mission_overlay_801096B4 = s0;
        break;
    }
play:
    playSpeechClip(s0, 0x73, 0, 1);
    D_mission_overlay_801096B0 = 5.0f;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", integrateCraftVelocityAndCollide);

s32 isTerrainCellBlockedAtWorldXz(f32, f32, void *);
void play3DSoundEvent(void *, void *, void *, f32, f32, s32, s32, s32, s32);
extern u32 D_mission_overlay_8010CA20;
extern u8 D_main_bss_80138058[];

void playCutsceneObjectImpactSound(u8 *obj) {
    struct player_struct *players;

    if (obj[0x24C] != 0) {
        return;
    }
    if (D_mission_overlay_8010CA20 != 0) {
        return;
    }
    players = gPlayers;
    if (!(*(u16 *)&players[*(s32 *)(obj + 0xB8)].inner.unk178[2] & 1)) {
        return;
    }
    obj[0x24C] = 1;
    switch (isTerrainCellBlockedAtWorldXz(*(f32 *)(obj + 4), *(f32 *)(obj + 0xC), D_main_bss_80138058)) {
        default:
        case 0:
            play3DSoundEvent(obj + 0x208, obj + 4, obj + 0x28, 18.0f, 0.6f, 0xF, 0x7E, 0x7D, 0x50);
            break;
        case 1:
            play3DSoundEvent(obj + 0x208, obj + 4, obj + 0x28, 18.0f, 0.6f, 0xF, 0x7F, 0x7D, 0x50);
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", tickCutsceneObject);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", findNearestSceneObjectToPoint);

typedef struct { s32 a, b, c; } V3;
typedef struct {
    u8 pad0[0x10];
    f32 x, y, z;
    V3 r;
    u8 pad1[0x84 - 0x28];
    f32 f84, f88, f8C;
} StartDat;
typedef struct {
    u8 pad[0x20];
    f32 a20, a24, pad28, a2C, a30;
} StartBounds;
typedef struct {
    f32 pad0;
    f32 x, y, z;
    u8 pad1[0xB6 - 0x10];
    u16 npc;
    s32 idx;
} StartPl;
extern StartBounds D_main_bss_80136DC0;
typedef struct { u8 pad[0x24]; f32 x, y, z; u8 pad2[0x2A0 - 0x30]; } Tf;
extern Tf D_main_bss_8013800C[];
extern f32 D_mission_overlay_8010B790;
extern f32 D_mission_overlay_8010B794;
extern f32 D_mission_overlay_8010B798;
extern f32 D_mission_overlay_8010B79C;
extern f32 D_mission_overlay_8010B7A0;
extern f32 D_mission_overlay_8010B7A4;
extern void *findNearestSceneObjectToPoint(s32);
extern StartDat *getLevelDatItemByName(char *);
extern f32 wrapAngleToCyclicRange(f32, f32, void *, u8 *);
extern u8 D_main_bss_80138058[];
extern void buildTransformMatrixFromEulerAngles(void *, f32, f32, f32);
extern void composeRotationMatrixSlot0(void *, s32);
extern void composeRotationMatrixSlot1(void *, s32);
extern void composeRotationMatrixSlot2(void *, s32);
extern void extractOrthonormalFrameFromStruct(void *, void *);
extern void computeAngleToTargetFromTransform(void *, s32 *, void *);
extern void clearObjectFlagBit4(void *);
extern void *getNpcContextByIndex(u16);

#define PM (&D_main_bss_8013800C[arg0->idx])
void loadPlayerStartPosition(StartPl *arg0, s32 arg1) {
    V3 sp;
    StartDat *d;
    StartDat *o;
    f32 var_fv0;
    f32 b;
    f32 t;

    if (arg1 == 0 || (o = findNearestSceneObjectToPoint(arg1)) == NULL) {
        d = getLevelDatItemByName("player_StartPosition");
        if (d != NULL) {
            arg0->x = d->x;
            arg0->y = d->y;
            arg0->z = d->z;
            sp = d->r;
            D_mission_overlay_8010B790 = D_main_bss_80136DC0.a20 + d->f8C;
            D_mission_overlay_8010B794 = D_main_bss_80136DC0.a24 - d->f8C;
            D_mission_overlay_8010B798 = D_main_bss_80136DC0.a2C + d->f8C;
            D_mission_overlay_8010B79C = D_main_bss_80136DC0.a30 - d->f8C;
            if (d->f84 < d->f88) {
                D_mission_overlay_8010B7A0 = d->f84;
                D_mission_overlay_8010B7A4 = d->f88;
            } else {
                D_mission_overlay_8010B7A0 = -15.0f;
                D_mission_overlay_8010B7A4 = 15.0f;
            }
        } else {
            arg0->x = D_main_bss_80136DC0.a20 + (D_main_bss_80136DC0.a24 - D_main_bss_80136DC0.a20) * 0.5f;
            arg0->z = D_main_bss_80136DC0.a2C + (D_main_bss_80136DC0.a30 - D_main_bss_80136DC0.a2C) * 0.5f;
            var_fv0 = wrapAngleToCyclicRange(arg0->x, arg0->z, D_main_bss_80138058, 0) - 10.0f;
            D_mission_overlay_8010B7A0 = -15.0f;
            arg0->y = var_fv0;
            D_mission_overlay_8010B7A4 = 15.0f;
            sp.a = 0;
            sp.b = 0;
            *(f32 *)&sp.c = 1.0f;
            D_mission_overlay_8010B790 = D_main_bss_80136DC0.a20 + 15.0f;
            D_mission_overlay_8010B794 = D_main_bss_80136DC0.a24 - 15.0f;
            D_mission_overlay_8010B798 = D_main_bss_80136DC0.a2C + 15.0f;
            D_mission_overlay_8010B79C = D_main_bss_80136DC0.a30 - 15.0f;
        }
    } else {
        arg0->x = o->x;
        arg0->y = o->y;
        arg0->z = o->z;
        sp = o->r;
    }
    buildTransformMatrixFromEulerAngles(PM, 0.0f, 0.0f, 0.0f);
    composeRotationMatrixSlot0(PM, sp.a);
    composeRotationMatrixSlot1(PM, sp.b);
    composeRotationMatrixSlot2(PM, sp.c);
    PM->x = arg0->x;
    PM->y = arg0->y;
    PM->z = arg0->z;
    extractOrthonormalFrameFromStruct(&arg0->x, PM);
    computeAngleToTargetFromTransform(PM, &sp.a, (u8 *)arg0 + 0xCC);
    clearObjectFlagBit4(getNpcContextByIndex(arg0->npc));
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0AEFF0", D_mission_overlay_800A55C0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", spawnSceneDebrisAndEffectCluster);

typedef struct {
    u8 pad0[0xB6];
    u16 unkB6;
    s32 unkB8;
    u8 padBC[4];
    s32 unkC0;
    u8 padC4[0x7C];
    f32 unk140;
    u8 pad144[0x3C];
    u16 unk180;
    u8 pad182[0xA];
    f32 unk18C;
    u8 pad190[0x3C];
    u16 unk1CC;
    u8 pad1CE[0x7E];
    u8 unk24C;
} NpcDebrisObj;
#include "player.h"
extern void resetHudInstancesAndUnbindNpcs(void);
extern void triggerPlayerVehicleSpecialSlotEffect(void);
extern void spawnScatteredDebrisParticles(void *);
extern u16 spawnDestructionDebris(u16, void *, f32, f32, f32);
extern void *getNpcContextByIndex(u16);
extern u16 popNpcSlotFromTail(u16, void *);
extern void setObjectFlagBit4(void *);
extern u16 rand(void);
extern s32 D_mission_overlay_8010CA1C;
extern u8 gGameSettings;
u8 isRumbleSlotActive(u8);
s32 startRumbleEffect(u8, void *);
s32 stopRumbleEffect(s32);
extern s32 D_main_bss_80130B50;
extern u32 D_mission_overlay_8010CA20;
extern u8 D_mission_overlay_8010BBD0[][12];
void playSpeechClip(s32, s32, f32, u16);
static __inline__ void rumbleInline(u8 *arg0, s32 arg1) {
    if (D_main_bss_80130B50 & 0x60) {
        return;
    }
    if (D_mission_overlay_8010CA20 != 0) {
        return;
    }
    if (arg1 < *(s32 *)(arg0 + 0x1C4) && isRumbleSlotActive(arg0[0xBB])) {
        return;
    }
    if (*(s32 *)(arg0 + 0x1C0) != -1) {
        stopRumbleEffect(*(s32 *)(arg0 + 0x1C0));
    }
    *(s32 *)(arg0 + 0x1C0) = startRumbleEffect(arg0[0xBB], D_mission_overlay_8010BBD0[arg1]);
    if (*(s32 *)(arg0 + 0x1C0) != -1) {
        *(s32 *)(arg0 + 0x1C4) = arg1;
    }
}
void factor5RemoveListNode(void *);

void spawnNpcDestructionDebris(NpcDebrisObj *arg0) {
    u16 flags;
    struct player_struct *pl;
    s32 a;
    u16 id;

    pl = gPlayers;
    flags = ((u16 *)&pl[arg0->unkB8].inner.unk178[2])[0];
    if (!(flags & 8))
    if (!(flags & 0x10))
    if (!(flags & 0x20)) {
        resetHudInstancesAndUnbindNpcs();
        triggerPlayerVehicleSpecialSlotEffect();
        D_mission_overlay_8010CA1C |= 0x100;
        arg0->unk180 = (arg0->unk180 & 0xFFFE) | 8;
        if ((f32)(rand() & 0x3F) * 0.015625f < 0.5f) {
            arg0->unk140 = -60.0f;
        } else {
            arg0->unk140 = 60.0f;
        }
        arg0->unkC0 = 0;
        a = rand() & 3;
        if (a >= 3) {
            a = 2;
        }
        if (gGameSettings != 0xF) {
            a += 0x116;
        } else {
            a += 0x1FE;
        }
        playSpeechClip(a, 0x73, 0, 0x30);
        arg0->unk18C = 6.0f;
        spawnScatteredDebrisParticles(arg0);
        id = spawnDestructionDebris(arg0->unkB6, (u8 *)arg0 + 4, 1.0f, 20.0f, 3.0f);
        if (id != 0xFFFF) {
            popNpcSlotFromTail(arg0->unk1CC, getNpcContextByIndex(id));
        }
        setObjectFlagBit4(getNpcContextByIndex(arg0->unkB6));
        rumbleInline((u8 *)arg0, 0xB);
        if (arg0->unk24C != 0) {
            arg0->unk24C = 0;
            factor5RemoveListNode((u8 *)arg0 + 0x208);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", updateSplineCraftTransform);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", computeOrientedTransformFromQuat);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", tickCinematicObjectStateMachine);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", updatePlayerCraftPhysics);

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u8 pad6[0x18];
    u16 unk1E;
    u8 pad20[4];
} CraftCapabilityDef;

extern CraftCapabilityDef D_mission_overlay_8010BE18[];
extern u16 D_mission_overlay_8010BFA8[];

void applyCraftCapabilityFlags(u8 *arg0) {
    D_mission_overlay_8010BFA8[*(s32 *)(arg0 + 0xB8)] |= D_mission_overlay_8010BE18[*(s32 *)(arg0 + 0xB8)].unk0;
    D_mission_overlay_8010BFA8[*(s32 *)(arg0 + 0xB8)] |= D_mission_overlay_8010BE18[*(s32 *)(arg0 + 0xB8)].unk4;
    D_mission_overlay_8010BFA8[*(s32 *)(arg0 + 0xB8)] |= D_mission_overlay_8010BE18[*(s32 *)(arg0 + 0xB8)].unk2;
    D_mission_overlay_8010BFA8[*(s32 *)(arg0 + 0xB8)] |= D_mission_overlay_8010BE18[*(s32 *)(arg0 + 0xB8)].unk1E;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", initPlayerCraftMovementMode);

typedef struct {
    u8 pad0[4];
    f32 pos[3];
    f32 vec10[3];
    u8 pad1C[4];
    f32 unk20;
    u8 pad24[0x90];
    u16 unkB4;
    u8 padB6[2];
    s32 unkB8;
    u8 padBC[0x7C];
    f32 unk138;
    f32 unk13C;
    u8 pad140[8];
    f32 unk148;
    f32 unk14C;
    u8 pad150[0x70];
    s32 unk1C0;
    s32 unk1C4;
} SpatialSoundNpc;

typedef struct {
    u8 pad0[4];
    u16 unk4;
    u16 unk6;
    f32 *unk8;
} SpatialSoundArg;

extern void play3DSoundEvent(void *, void *, void *, f32, f32, s32, s32, s32, s32);
extern void vec3ExtrapolateFirstOrder(void *, s32, void *, f32);
extern void spawnNpcType0xAFromTemplate(void *, f32);
extern void spawnRandomParticleWithParent(void *, s32, f32, s32);
extern void distanceAndDopplerNpcHelper(void *, f32, f32);
extern void tickCinematicObjectStateMachine(void *, f32);
extern void clampVec3ToUnitIfLongerThan(void *);
extern f32 vec3Dot(void *, void *);
extern void applyNpcPositionDrift(void *, void *, f32);
extern void func_mission_overlay_800EFD64(s32, s32);
extern s32 slotDispatcherIter(u16, s32, void *);
extern u8 D_main_bss_80138838;
extern u8 D_main_bss_80138926;
extern u16 D_main_bss_8013957E;

void tryPlaySpatialSoundWithGates(SpatialSoundNpc *arg0, SpatialSoundArg *arg1) {
    struct {
        f32 v28[3];
        u8 pad34[4];
        u8 b38[0x18];
        s8 c50;
        u8 pad51[7];
        f32 v58[3];
    } l;
    f32 *s2 = arg1->unk8;
    f32 fs0;
    f32 t;
    struct player_struct *pl;
    s32 *gs;

    if (D_main_bss_80138838 != 0) {
        return;
    }
    if (D_main_bss_80138926 != 0) {
        return;
    }
    gs = (s32 *)&gGameSettings;
    if ((gs + arg0->unkB8)[3] & 0x800000) {
        return;
    }
    pl = gPlayers;
    if (((u16 *)&pl[arg0->unkB8].inner.unk178[2])[0] & 0x78) {
        return;
    }
    if (s2 != NULL) {
        play3DSoundEvent(NULL, arg0->pos, (u8 *)arg0 + 0x28, 24.0f, 0.6f, 0, 0x1B, 0x7F, 0x5A);
        switch (arg0->unkB4) {
        case 0:
        case 2:
        case 8:
            fs0 = 0.2f;
            break;
        case 3:
        case 4:
        case 6:
            fs0 = 0.3f;
            break;
        case 1:
        case 7:
            fs0 = 0.55f;
            break;
        case 5:
            fs0 = 0.8f;
            break;
        }
        switch (arg1->unk4) {
        case 0xA:
        case 0xB:
        case 0xD:
            vec3ExtrapolateFirstOrder(s2, 0, l.v58, -0.1f);
            spawnNpcType0xAFromTemplate(l.v58, fs0 * 0.6f);
            break;
        case 0xC:
            vec3ExtrapolateFirstOrder(s2, 0, l.v58, -0.1f);
            spawnRandomParticleWithParent(l.v58, 0xFFFF, fs0 * 0.5f, 0);
            break;
        default:
            vec3ExtrapolateFirstOrder(s2, 0, l.v58, -0.1f);
            distanceAndDopplerNpcHelper(l.v58, fs0 * 0.04f, 0.02f);
            break;
        }
    }
    rumbleInline((u8 *)arg0, 0);
    tickCinematicObjectStateMachine(arg0, (f32)arg1->unk6);
    fs0 = (f32)arg1->unk6 / 20.0f;
    if (fs0 > 1.0f) {
        fs0 = 1.0f;
    }
    if (fs0 < 0.0f) {
        fs0 = 0.0f;
    }
    if (s2 != NULL) {
        l.v28[0] = arg0->pos[0] - s2[0];
        t = arg0->pos[1] - s2[1];
        l.v28[1] = t;
        l.v28[2] = arg0->pos[2] - s2[2];
        if ((t > 0.0f && arg0->unk20 > 0.0f) || (t < 0.0f && arg0->unk20 < 0.0f)) {
            arg0->unk14C = arg0->unk14C + arg0->unk148 * fs0;
        } else {
            arg0->unk14C = arg0->unk14C - arg0->unk148 * fs0;
        }
        clampVec3ToUnitIfLongerThan(l.v28);
        if (vec3Dot(l.v28, arg0->vec10) > 0.0f) {
            arg0->unk13C = arg0->unk13C + arg0->unk138 * fs0;
        } else {
            arg0->unk13C = arg0->unk13C - arg0->unk138 * fs0;
        }
        applyNpcPositionDrift(arg0, l.v28, fs0);
    }
    func_mission_overlay_800EFD64(0, 0);
    l.c50 = 0xB;
    slotDispatcherIter(D_main_bss_8013957E, 9, l.b38);
}

u8 isRumbleSlotActive(u8);
s32 startRumbleEffect(u8, void *);
s32 stopRumbleEffect(s32);
extern s32 D_main_bss_80130B50;
extern u32 D_mission_overlay_8010CA20;
extern u8 D_mission_overlay_8010BBD0[][12];

void scheduleSceneFormatMessageTimed(u8 *arg0, s32 arg1) {
    if (D_main_bss_80130B50 & 0x60) {
        return;
    }
    if (D_mission_overlay_8010CA20 != 0) {
        return;
    }
    if (arg1 < *(s32 *)(arg0 + 0x1C4) && isRumbleSlotActive(arg0[0xBB])) {
        return;
    }
    if (*(s32 *)(arg0 + 0x1C0) != -1) {
        stopRumbleEffect(*(s32 *)(arg0 + 0x1C0));
    }
    *(s32 *)(arg0 + 0x1C0) = startRumbleEffect(arg0[0xBB], D_mission_overlay_8010BBD0[arg1]);
    if (*(s32 *)(arg0 + 0x1C0) != -1) {
        *(s32 *)(arg0 + 0x1C4) = arg1;
    }
}

s32 stopRumbleEffect(s32);

void cancelSceneQueueHandle(void *arg0) {
    s32 temp_a0;

    temp_a0 = (*(s32 *)((u8 *)(arg0) + 0x1C0));
    if (temp_a0 != -1) {
        stopRumbleEffect(temp_a0);
        (*(s32 *)((u8 *)(arg0) + 0x1C0)) = -1;
    }
}

void playSpeechClip(s32, s32, f32, u16);
extern s32 D_mission_overlay_801096B4;
extern f32 D_mission_overlay_801096B0;

void playSpeechClipOncePerChange(s32 arg0, s32 arg1) {
    if (arg0 != D_mission_overlay_801096B4 && arg0 != 0x28C) {
        playSpeechClip(arg0, 0x73, 0, arg1);
        D_mission_overlay_801096B4 = arg0;
        D_mission_overlay_801096B0 = 5.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", playSpeechClipOncePerLevel);

extern s32 D_mission_overlay_8010B740[];
extern u8 D_mission_overlay_8010B780[];

void resetSpeechOncePerLevelFlag(s32 arg0) {
    s32 i = 0;
    s32 *ids;
    u8 *flags;

    if (arg0 != 0x28C) {
        ids = D_mission_overlay_8010B740;
        flags = D_mission_overlay_8010B780;
    loop:
        if (ids[i] == arg0) {
            *(u8 *)(i + (s32)flags) = 0;
            return;
        }
        i++;
        if (i < 14) {
            goto loop;
        }
    }
}

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} PlayerSlotVec3;

void setPlayerSlotPositionVec3(u8 idx, PlayerSlotVec3 *v) {
    struct player_struct *p = gPlayers;

    *(PlayerSlotVec3 *)&p[idx].inner.unk178[8] = *v;
}

u16 getNextSlotNpcTypeId(u16);
void destroyNpcSlotByIndex(u16);
void destroyNpcSlotChain(u16);
void factor5RemoveListNode(void *);

void destroySceneNpcsAndUnlink(u8 *arg0) {
    u16 id;

    if (*(u16 *)(arg0 + 0x1CC) != 0xFFFF) {
        for (;;) {
            id = getNextSlotNpcTypeId(*(u16 *)(arg0 + 0x1CC));
            if (id == 0xFFFF) {
                break;
            }
            destroyNpcSlotByIndex(id);
        }
        destroyNpcSlotChain(*(u16 *)(arg0 + 0x1CC));
        *(u16 *)(arg0 + 0x1CC) = 0xFFFF;
    }
    if (arg0[0x24C] != 0) {
        arg0[0x24C] = 0;
        factor5RemoveListNode(arg0 + 0x208);
    }
}

extern f32 D_mission_overlay_801096B0;

void decayWeaponCooldownTimer(s32 arg0, f32 arg1) {
    if (D_mission_overlay_801096B0 > 0.0f) {
        D_mission_overlay_801096B0 -= arg1;
    }
}

extern f32 D_mission_overlay_8010B7A0;

f32 getWeaponChargeLevel(void) {
    return D_mission_overlay_8010B7A0;
}

extern s32 D_main_bss_80137CE4;
extern u8 D_mission_overlay_801096B8;

void advancePitchTowardTarget(u8 *arg0, f32 dt) {
    if (*(f32 *)(arg0 + 0xC0) <= 0.0f || D_main_bss_80137CE4 == 3 || *(f32 *)(arg0 + 0xC0) == *(f32 *)(arg0 + 0xC4) || D_mission_overlay_801096B8 == 0) {
        return;
    }
    switch (*(u16 *)(arg0 + 0xB4)) {
        case 0:
        case 1:
        case 5:
        case 8:
            *(f32 *)(arg0 + 0xC0) += *(f32 *)(arg0 + 0xC4) / 180.0f * dt;
            if (*(f32 *)(arg0 + 0xC4) < *(f32 *)(arg0 + 0xC0)) {
                *(f32 *)(arg0 + 0xC0) = *(f32 *)(arg0 + 0xC4);
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0AEFF0", fake_func_800B42BC);

__asm__(".section .rodata\n.word 0x27BD0008\n.word 0x03E00008\n.word 0x00000000\n.section .text");
