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

extern f32 D_mission_overlay_8010B790;
extern f32 D_mission_overlay_8010B794;
extern f32 D_mission_overlay_8010B798;
extern f32 D_mission_overlay_8010B79C;
extern u8 csPl[][0x2A0] __asm__("D_main_bss_8013800C");
extern f32 csTgt[3] __asm__("D_main_bss_80137CE8");
extern f32 vec3Dot(void *, void *);
f32 sinfApprox(f32);
extern void clampVec3ToUnitIfLongerThan(void *);
typedef struct {
    f32 v[3];
} CsV3;

void computeCraftSelectTurnFromInput(u8 *o, f32 dt) {
    f32 *pos;
    f32 out;
    f32 ang;
    f32 k;
    f32 zero;
    f32 d;
    f32 t;
    u8 *m;
    f32 a[4];
    f32 b[4];

    pos = (f32 *)(o + 4);
    out = 0.0f;
    if (pos[0] < D_mission_overlay_8010B790) {
        out = D_mission_overlay_8010B790 - pos[0];
    }
    if (D_mission_overlay_8010B794 < pos[0]) {
        out = pos[0] - D_mission_overlay_8010B794;
    }
    if (pos[2] < D_mission_overlay_8010B798) {
        out = D_mission_overlay_8010B798 - pos[2];
    }
    if (D_mission_overlay_8010B79C < pos[2]) {
        out = pos[2] - D_mission_overlay_8010B79C;
    }
    m = csPl[*(s32 *)(o + 0xB8)];
    a[0] = *(f32 *)(m + 0);
    a[1] = *(f32 *)(m + 0xC);
    a[2] = *(f32 *)(m + 0x18);
    b[0] = 0.0f;
    b[1] = -1.0f;
    b[2] = 0.0f;
    k = 57.29578f;
    t = sinfApprox(vec3Dot(a, b)) * k;
    __asm__ volatile("abs.s %0, %1" : "=f"(ang) : "f"(t));
    zero = 0.0f;
    if (zero < out) {
        *(u16 *)(o + 0x180) |= 2;
        a[0] = csTgt[0] - pos[0];
        a[1] = csTgt[1] - pos[1];
        a[2] = csTgt[2] - pos[2];
        a[1] = zero;
        clampVec3ToUnitIfLongerThan(a);
        *(CsV3 *)b = *(CsV3 *)(o + 0x10);
        b[1] = zero;
        clampVec3ToUnitIfLongerThan(b);
        d = vec3Dot(b, a);
        out = a[0] * b[2] - a[2] * b[0];
        if (d < 0.9961946f && ang < 10.0f) {
            t = 90.0f - sinfApprox(d) * k;
            if (out < zero) {
                *(f32 *)(o + 0xD8) = t * dt;
            } else {
                *(f32 *)(o + 0xD8) = -(t * dt);
            }
        }
    } else {
        *(u16 *)(o + 0x180) &= ~2;
    }
}

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

extern s32 D_main_bss_80130B50;
extern u32 D_mission_overlay_8010CA20;
extern u8 D_mission_overlay_8010BBD0[][12];
u8 isRumbleSlotActive(u8);
s32 startRumbleEffect(u8, void *);
s32 stopRumbleEffect(s32);
extern f32 vec3Length(void *);

static __inline__ void icRumble(u8 *arg0, s32 arg1) {
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

void integrateCraftVelocityAndCollide(void *op, f32 dt) {
    u8 *o = op;
    f32 len;

    *(f32 *)(o + 4) += *(f32 *)(o + 0x198) * dt;
    *(f32 *)(o + 8) += *(f32 *)(o + 0x19C) * dt;
    *(f32 *)(o + 0xC) += *(f32 *)(o + 0x1A0) * dt;
    if (*(f32 *)(o + 0x198) != 0.0f || *(f32 *)(o + 0x19C) != 0.0f || *(f32 *)(o + 0x1A0) != 0.0f) {
        len = vec3Length(o + 0x198);
        if (len < 10.0f) {
            icRumble(o, 3);
        } else if (len < 20.0f) {
            icRumble(o, 2);
        } else {
            icRumble(o, 1);
        }
    }
    *(f32 *)(o + 0x198) = *(f32 *)(o + 0x19C) = *(f32 *)(o + 0x1A0) = 0.0f;
}

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

#define VABS(x) ({ f32 _x = (x); f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(_x)); _r; })
typedef struct { u8 b[4]; } Bytes4;
typedef struct {
    u16 f0;
    u16 f2;
    u16 f4;
    u8 pad6[0xA];
    f32 pos[3];
    u8 pad1C[0xA4];
    void *unkC0;
} TargetRec;
typedef struct {
    u8 pad0[4];
    TargetRec *rec;
    u8 pad8[0x13C];
} TargetSlot;
typedef struct { u8 b[0x3E0]; } BigSlot;
typedef struct {
    u8 pad0[4];
    f32 pos[3];
    u8 pad10[0x1C];
    s32 unk2C;
    u8 pad30[0x80];
    s32 unkB0;
    u8 padB4[2];
    u16 unkB6;
    s32 unkB8;
    u8 padBC[4];
    s32 unkC0;
    u8 padC4[0x7C];
    s32 unk140;
    u8 pad144[0x3C];
    u16 unk180;
    u8 pad182[2];
    f32 unk184;
    u8 pad188[0x44];
    u16 unk1CC;
    u8 pad1CE[0x7E];
    u8 unk24C;
} SceneObj;
typedef struct {
    s32 w58;
    f32 f5C;
    u8 rest[0x20];
} WrapOut;
typedef struct {
    f32 v20[3];
    u8 pad2C[4];
    f32 v30[3];
    u8 pad3C[4];
    f32 m40[4];
    Bytes4 c50;
    u8 pad54[4];
    WrapOut w;
} SceneLocals;

extern TargetSlot D_main_bss_80138D18[];
extern BigSlot D_main_bss_80138A28[];
extern s32 D_mission_overlay_8010CA1C;
extern u16 getNextSlotNpcTypeId(u16);
extern void destroyNpcSlotByIndex(u16);
extern void destroyNpcSlotChain(u16);
extern u16 allocateNpcSlot(s32);
extern void *getNpcContextByIndex(u16);
extern void setObjectFlagBit4(void *);
extern void resetHudInstancesAndUnbindNpcs(void);
extern void triggerPlayerVehicleSpecialSlotEffect(void);
extern void factor5RemoveListNode(void *);
extern f32 vec3Length(void *);
extern void spawnRandomizedEffectBurst(void *);
extern s32 isTerrainCellBlockedAtWorldXz(f32, f32, void *);
extern void spawnWaterSprayDebrisAndBurst(void *, f32, f32, f32, f32, f32);
extern void spawnEffectNpcWithRampedScale(void *, u16, f32, f32, f32);
extern void spawnOrientedNpc(s32, void *, s32, void *, f32, f32, f32, f32);
extern void spawnNpcType0xAFromTemplate(void *, f32);
extern void composeRandomRotationMatrix(void *, void *, f32, s32, s32, s32);
extern void scaleVec3ByRandomRange(void *, f32, f32);
extern void spawnDebris1Npc(void *, void *, f32, f32, f32);
extern u8 D_main_bss_80138058[];
extern u16 rand(void);
extern u8 D_mission_overlay_800A55C0[];
extern s32 D_main_bss_80130B50;
extern u32 D_mission_overlay_8010CA20;
extern u8 D_mission_overlay_8010BBD0[][12];
u8 isRumbleSlotActive(u8);
s32 startRumbleEffect(u8, void *);
s32 stopRumbleEffect(s32);
static __inline__ void rumbleInlineA(u8 *arg0, s32 arg1) {
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


void spawnSceneDebrisAndEffectCluster(SceneObj *arg0, s32 arg1) {
    SceneLocals l;
    u16 flags;
    u16 id;
    s32 i;
    s32 n;
    s16 t;
    TargetRec *rec;
    BigSlot *A;
    u8 *wr;
    s32 sel;
    f32 x;
    struct player_struct *pl;

    l.c50 = *(Bytes4 *)D_mission_overlay_800A55C0;
    pl = gPlayers;
    flags = ((u16 *)&pl[arg0->unkB8].inner.unk178[2])[0];
    if (flags & 0x10) {
        return;
    }
    if (flags & 0x20) {
        return;
    }
    resetHudInstancesAndUnbindNpcs();
    triggerPlayerVehicleSpecialSlotEffect();
    if (arg0->unk1CC != 0xFFFF) {
        while ((id = getNextSlotNpcTypeId(arg0->unk1CC)) != 0xFFFF) {
            destroyNpcSlotByIndex(id);
        }
        destroyNpcSlotChain(arg0->unk1CC);
        arg0->unk1CC = 0xFFFF;
    }
    if (arg0->unk24C != 0) {
        arg0->unk24C = 0;
        factor5RemoveListNode((u8 *)arg0 + 0x208);
    }
    arg0->unk1CC = allocateNpcSlot(0);
    wrapAngleToCyclicRange(arg0->pos[0], arg0->pos[2], D_main_bss_80138058, (u8 *)&l.w);
    if (l.w.f5C <= arg0->pos[1]) {
        arg0->pos[1] = l.w.f5C - 0.125f;
    }
    arg0->unk2C = 0;
    D_mission_overlay_8010CA1C |= 0x100;
    arg0->unk180 = (arg0->unk180 & 0xFFF6) | 0x190;
    arg0->unk184 = 0.5f;
    setObjectFlagBit4(getNpcContextByIndex(arg0->unkB6));
    arg0->unk140 = 0;
    rec = D_main_bss_80138D18[arg0->unkB8].rec;
    l.v20[0] = arg0->pos[0] - rec->pos[0];
    l.v20[1] = arg0->pos[1] - rec->pos[1];
    l.v20[2] = arg0->pos[2] - rec->pos[2];
    {
        f32 len = vec3Length(l.v20);
        if (D_main_bss_80138D18[arg0->unkB8].rec->f4 == 3
            || (!(rec->f0 & 0x10) && rec->f4 == 2 && len < 0.75f)
            || ((rec != (TargetRec *)&D_main_bss_80138A28[arg0->unkB8]) && (!(rec->f0 & 0x10) || *(u16 *)((u8 *)rec + 2) != 4 || rec->unkC0 != (void *)&D_main_bss_80138A28[arg0->unkB8]))) {
            spawnRandomizedEffectBurst(arg0);
        }
    }
    *(volatile s32 *)&arg0->unkC0 = 0;
    rumbleInlineA((u8 *)arg0, 0xC);
    wrapAngleToCyclicRange(arg0->pos[0], arg0->pos[2], D_main_bss_80138058, (u8 *)&l.w);
    if (l.w.f5C <= arg0->pos[1]) {
        arg0->pos[1] = l.w.f5C - 0.125f;
    }
    if (arg0->unk24C != 0) {
        arg0->unk24C = 0;
        factor5RemoveListNode((u8 *)arg0 + 0x208);
    }
    sel = arg1 & 0xFF;
    if (sel == 1 && isTerrainCellBlockedAtWorldXz(arg0->pos[0], arg0->pos[2], D_main_bss_80138058) == 1) {
        spawnWaterSprayDebrisAndBurst(arg0->pos, 0.2f, 2.0f, 2.0f, 4.0f, 1.0f);
    } else {
        spawnEffectNpcWithRampedScale(arg0->pos, arg0->unkB6, 1.875f, 5.625f, 0.2f);
        spawnOrientedNpc(0x8002, arg0->pos, 0, NULL, 0.1875f, 1.875f, 1.0f, 0.6f);
        spawnOrientedNpc(0x8001, arg0->pos, 0, &l.c50, 0.1875f, 1.875f, 1.0f, 0.4f);
        i = 0;
        t = (s16)rand() % 3;
        n = t + 2;
        if (n > 0) {
            do {
                spawnNpcType0xAFromTemplate(arg0->pos, VABS(((f32)(rand() & 0x7F) - 64.0f) / 21.333334f + 1.0f));
                i++;
            } while (i < n);
        }
    }
    i = 0;
    t = (s16)rand() % 5;
    n = t + 10;
    if (n > 0) {
        do {
            f32 a;
            f32 b;
            composeRandomRotationMatrix(l.m40, l.v30, 2.0f, 0x3C, 0, 0);
            scaleVec3ByRandomRange(l.v30, 3.0f, 4.0f);
            x = ((f32)(rand() & 0x7F) - 64.0f) / 12.8f;
            a = VABS(x) + 12.0f;
            x = ((f32)(rand() & 0x7F) - 64.0f) * 0.0078125f;
            b = VABS(x) + 0.5f;
            x = ((f32)(rand() & 0x7F) - 64.0f) / 320.0f;
            spawnDebris1Npc(arg0->pos, l.v30, a, b, VABS(x) + 0.2f);
            i++;
        } while (i < n);
    }
}

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

typedef struct {
    f32 q[4];
    s32 ang[4];
    f32 m[12];
    u8 flag;
} SplineLocals;

typedef struct {
    u8 *unk0;
    f32 pos[3];
    f32 dir[3];
    u8 pad1C[0xC];
    f32 vel[3];
    u8 pad34[0x80];
    u16 unkB4;
    u8 padB6[2];
    s32 unkB8;
    u8 padBC[0x10];
    s32 unkCC[3];
    u8 padD8[0x10];
    f32 unkE8;
    u8 padEC[0x54];
    f32 unk140;
    u8 pad144[0x48];
    f32 unk18C;
} SplineCraft;

typedef struct { s32 a, b, c; u8 pad[0x294]; } AngleSlot;
extern AngleSlot D_main_bss_8013803C_l[] __asm__("D_main_bss_8013803C");

extern void play3DSoundEvent(void *, void *, void *, f32, f32, s32, s32, s32, s32);

extern void quatFromAxisAngleSafe_l(void *, void *, f32) __asm__("quatFromAxisAngleSafe");
extern void rotateVec3ByQuat_l(void *, void *, void *) __asm__("rotateVec3ByQuat");
extern void orthonormalizeFrame_l(void *) __asm__("orthonormalizeFrame");
extern void mat34CrossRowsAndCopyPos_l(void *, void *, f32) __asm__("mat34CrossRowsAndCopyPos");
extern void addScaledVec3ToVec3(void *, void *, f32, void *);
void spawnSceneDebrisAndEffectClusterU(void *, u8) __asm__("spawnSceneDebrisAndEffectCluster");
extern void integrateCraftVelocityAndCollide(void *, f32);
extern u8 stepObjectOrientationTowardTarget(void *, f32, void *, void *, void *, u8 *);
extern void normalize_vector(void *);
extern void spawnSplineWalkerCraft(void *, f32, f32, s32);
extern void initVec4TripletFromArgs_l(void *, s32, s32, s32) __asm__("initVec4TripletFromArgs");
extern void mat3x4Multiply_l(void *, void *, void *) __asm__("mat3x4Multiply");

void initVec4F(f32 *, f32, f32, f32) __asm__("initVec4TripletFromArgs");
static __inline__ void usScale(f32 *m, s32 type) {
    register f32 c asm("$5") = 0.0125f;
    if (type == 5) {
        c = 0.021875f;
    }
    initVec4F(m, c, c, c);
}
void updateSplineCraftTransform(SplineCraft *arg0, f32 arg1) {
    f32 q[4];
    s32 ang[4];
    f32 m[12];
    u8 flag;
    Tf *s2;
    Tf *t;
    f32 v;
    f32 w;
    s32 c;
    u16 ty;

    s2 = &D_main_bss_8013800C[arg0->unkB8];
    if (arg0->dir[1] < 0.0f) {
        arg0->dir[1] = arg0->dir[1] + arg1 * 0.5f;
    } else {
        arg0->dir[1] = arg0->dir[1] + arg1 * 0.25f;
    }
    if (arg0->dir[1] > 0.5f) {
        arg0->dir[1] = 0.5f;
    }
    clampVec3ToUnitIfLongerThan(arg0->dir);
    quatFromAxisAngleSafe_l(q, arg0->dir, arg0->unk140 * arg1);
    rotateVec3ByQuat_l(q, (u8 *)arg0 + 0x1C, (u8 *)arg0 + 0x1C);
    clampVec3ToUnitIfLongerThan((u8 *)arg0 + 0x1C);
    orthonormalizeFrame_l(arg0->pos);
    mat34CrossRowsAndCopyPos_l(s2, arg0->pos, 1.0f);
    arg0->vel[0] = arg0->unkE8 * arg0->dir[0];
    arg0->vel[1] = arg0->unkE8 * arg0->dir[1];
    arg0->vel[2] = arg0->unkE8 * arg0->dir[2];
    arg0->unkE8 = arg0->unkE8 * 1.01f;
    addScaledVec3ToVec3(arg0->pos, arg0->pos, arg1, arg0->vel);
    s2->x = arg0->pos[0];
    s2->y = arg0->pos[1];
    s2->z = arg0->pos[2];
    computeAngleToTargetFromTransform(s2, ang, arg0->unkCC);
    extractOrthonormalFrameFromStruct(arg0->pos, s2);
    if (arg0->unk18C > 0.0f) {
        arg0->unk18C -= arg1;
        if (arg0->unk18C < 0.0f) {
            arg0->unk18C = 0.0f;
            spawnSceneDebrisAndEffectClusterU(arg0, 0);
        }
    }
    integrateCraftVelocityAndCollide(arg0, arg1);
    switch (stepObjectOrientationTowardTarget(arg0, arg1, &arg0->unkCC[0], &arg0->unkCC[1], &arg0->unkCC[2], &flag)) {
    case 1:
        if (flag == 0) {
            play3DSoundEvent(NULL, arg0->pos, arg0->vel, 20.0f, 0.2f, 0, 0x3E, 0x7A, 0x28);
        } else {
            play3DSoundEvent(NULL, arg0->pos, arg0->vel, 24.0f, 0.2f, 0, 0xC, 0x73, 0x28);
            if (isTerrainCellBlockedAtWorldXz(arg0->pos[0], arg0->pos[2], D_main_bss_80138058) != 1) {
                *(s32 *)&arg0->dir[1] = 0;
                normalize_vector(arg0->dir);
                *(s32 *)((u8 *)arg0 + 0x1C) = 0;
                *(s32 *)((u8 *)arg0 + 0x24) = 0;
                *(f32 *)((u8 *)arg0 + 0x20) = 1.0f;
                orthonormalizeFrame_l(arg0->pos);
                mat34CrossRowsAndCopyPos_l(&D_main_bss_8013800C[arg0->unkB8], arg0->pos, 1.0f);
                spawnSplineWalkerCraft(arg0->pos, 0.375f, 0.46875f, 0xC);
            }
        }
        spawnSceneDebrisAndEffectClusterU(arg0, flag);
        break;
    case 2:
        if (flag == 0) {
            play3DSoundEvent(NULL, arg0->pos, arg0->vel, 20.0f, 0.2f, 0, 0x3E, 0x7A, 0x28);
        } else {
            play3DSoundEvent(NULL, arg0->pos, arg0->vel, 24.0f, 0.2f, 0, 0xC, 0x73, 0x28);
            if (isTerrainCellBlockedAtWorldXz(arg0->pos[0], arg0->pos[2], D_main_bss_80138058) != 1) {
                *(s32 *)&arg0->dir[1] = 0;
                normalize_vector(arg0->dir);
                *(s32 *)((u8 *)arg0 + 0x1C) = 0;
                *(s32 *)((u8 *)arg0 + 0x24) = 0;
                *(f32 *)((u8 *)arg0 + 0x20) = 1.0f;
                orthonormalizeFrame_l(arg0->pos);
                mat34CrossRowsAndCopyPos_l(&D_main_bss_8013800C[arg0->unkB8], arg0->pos, 1.0f);
                spawnSplineWalkerCraft(arg0->pos, 0.375f, 0.46875f, 0xC);
            }
        }
        spawnSceneDebrisAndEffectClusterU(arg0, flag);
        orthonormalizeFrame_l(arg0->pos);
        break;
    default:
        v = arg0->unk140;
        if (v > 0.0f) {
            w = v + 2.0f;
            arg0->unk140 = w;
            if (w > 180.0f) {
                arg0->unk140 = 180.0f;
            }
        } else {
            w = v - 2.0f;
            arg0->unk140 = w;
            if (w < -180.0f) {
                arg0->unk140 = -180.0f;
            }
        }
        break;
    }
    orthonormalizeFrame_l(arg0->pos);
    do {
    mat34CrossRowsAndCopyPos_l(s2, arg0->pos, 1.0f);
    t = &D_main_bss_8013800C[arg0->unkB8];
    t->x = arg0->pos[0];
    t->y = arg0->pos[1];
    t->z = arg0->pos[2];
    ty = arg0->unkB4;
    } while (0);
    usScale(m, ty);
    mat3x4Multiply_l(t, m, arg0->unk0 + 0x28);
    *(V3 *)&D_main_bss_8013803C_l[arg0->unkB8] = *(V3 *)arg0->unkCC;
}

extern u8 Cot800C[][0x2A0] __asm__("D_main_bss_8013800C");
extern u8 D_main_bss_8013803C[][0x2A0];
extern u8 D_main_bss_80138058[];
typedef struct { u8 pad0[4]; void *unk4; u8 pad8[0x13C]; } CotNode;
extern CotNode CotD18[] __asm__("D_main_bss_80138D18");
extern u32 D_mission_overlay_8010C9E0;
extern u8 D_mission_overlay_8010CA18;
extern u32 D_mission_overlay_8010CA20;
typedef struct { s32 a, b, c; } CotV3;
extern void orthonormalizeFrame(f32 *);
f32 wrapAngleToCyclicRangeF(f32, f32, void *, f32 *) __asm__("wrapAngleToCyclicRange");
extern void scaleVec3ByScalar(f32 *, f32, f32 *);


extern void quatFromAxisAngleSafe(f32 *, f32 *, s32);
extern void rotateVec3ByQuat(f32 *, f32 *, f32 *);
extern void mat34CrossRowsAndCopyPos(void *, f32 *, f32);
extern void initVec4TripletFromArgs(f32 *, s32, s32, s32);
extern void mat3x4Multiply(void *, f32 *, f32 *);

void initVec4F(f32 *, f32, f32, f32) __asm__("initVec4TripletFromArgs");
static __inline__ void cotScale(f32 *m, s32 type) {
    register f32 c asm("$5") = 0.0125f;
    if (type == 5) {
        c = 0.021875f;
    }
    initVec4F(m, c, c, c);
}
void computeOrientedTransformFromQuat(u8 *arg0, f32 dt)
{
  f32 q[4];
  f32 w[3];
  f32 pad[5];
  f32 m[12];
  u8 *pl;
  u8 *pl2;
  f32 f;
  f32 t;
  f32 g;
  s32 sc;
  u16 ty;
  CotNode *node;
  CotNode *base;
  t = (*((f32 *) (arg0 + 0x184))) - dt;
  pl = Cot800C[*((s32 *) (arg0 + 0xB8))];
  *((f32 *) (arg0 + 0x184)) = t;
  if (t <= 0.0f)
  {
    *((u16 *) (arg0 + 0x180)) |= 0x100;
    if (!((*((u16 *) (Cot800C[*((s32 *) (arg0 + 0xB8))] - 0xD0))) & 0x20))
    {
      *((u16 *) (arg0 + 0x180)) = ((*((u16 *) (arg0 + 0x180))) & 0xFFE6) | 0x20;
      *((f32 *) (arg0 + 0xC0)) = 0.0f;
      *((f32 *) (arg0 + 0x184)) = 20.0f;
      orthonormalizeFrame((f32 *) (arg0 + 4));
      wrapAngleToCyclicRangeF(*((f32 *) (arg0 + 4)), *((f32 *) (arg0 + 0xC)), D_main_bss_80138058, w);
      if (w[1] <= (*((f32 *) (arg0 + 8))))
      {
        *((f32 *) (arg0 + 8)) = w[1] - 0.125f;
      }
      if (D_mission_overlay_8010CA20 == 0)
      {
        D_mission_overlay_8010CA18 = arg0[0xBB];
        D_mission_overlay_8010C9E0 |= 2;
      }
    }
  }
  else
  {
    if (((*((f32 *) (arg0 + 0x28))) > 0.0f) || ((*((f32 *) (arg0 + 0x30))) > 0.0f))
    {
      *((f32 *) (arg0 + 4)) += (*((f32 *) (arg0 + 0x28))) * dt;
      *((f32 *) (arg0 + 0xC)) += (*((f32 *) (arg0 + 0x30))) * dt;
      scaleVec3ByScalar((f32 *) (arg0 + 0x28), 0.75f, (f32 *) (arg0 + 0x28));
      if (vec3Length((f32 *) (arg0 + 0x28)) < 0.025f)
      {
        *((f32 *) (arg0 + 0x28)) = 0.0f;
        *((f32 *) (arg0 + 0x2C)) = 0.0f;
        *((f32 *) (arg0 + 0x30)) = 0.0f;
        *((f32 *) (arg0 + 0xE8)) = 0.0f;
      }
    }
    wrapAngleToCyclicRangeF(*((f32 *) (arg0 + 4)), *((f32 *) (arg0 + 0xC)), D_main_bss_80138058, w);
    if (w[1] <= (*((f32 *) (arg0 + 8))))
    {
      *((f32 *) (arg0 + 8)) = w[1] - 0.125f;
    }
    clampVec3ToUnitIfLongerThan((f32 *) (arg0 + 0x10));
    quatFromAxisAngleSafe(q, (f32 *) (arg0 + 0x10), 0);
    rotateVec3ByQuat(q, (f32 *) (arg0 + 0x1C), (f32 *) (arg0 + 0x1C));
    clampVec3ToUnitIfLongerThan((f32 *) (arg0 + 0x1C));
    orthonormalizeFrame((f32 *) (arg0 + 4));
do { mat34CrossRowsAndCopyPos(pl, (f32 *) (arg0 + 4), 1.0f); pl2 = Cot800C[*((s32 *) (arg0 + 0xB8))]; *((f32 *) (pl2 + 0x24)) = *((f32 *) (arg0 + 4)); *((f32 *) (pl2 + 0x28)) = *((f32 *) (arg0 + 8)); *((f32 *) (pl2 + 0x2C)) = *((f32 *) (arg0 + 0xC)); ty = *((u16 *) (arg0 + 0xB4)); } while (0);
cotScale(m, ty);
    mat3x4Multiply(pl2, m, (f32 *) ((*((u8 **) arg0)) + 0x28));
    *((CotV3 *) D_main_bss_8013803C[*((s32 *) (arg0 + 0xB8))]) = *((CotV3 *) (arg0 + 0xCC));
    base = CotD18;
    node = &base[*((s32 *) (arg0 + 0xB8))];
    if ((*((u16 *) (((u8 *) node->unk4) + 4))) == 4)
    {
      f = *((f32 *) (((u8 *) node->unk4) + 0xD8));
      if (f < 0.0f)
      {
        g = f + 0.5f;
        *((f32 *) (((u8 *) node->unk4) + 0xD8)) = g;
        if (g > 0.0f)
        {
          *((f32 *) (((u8 *) base[*((s32 *) (arg0 + 0xB8))].unk4) + 0xD8)) = 0.0f;
        }
      }
      else
      {
        g = f - 0.5f;
        *((f32 *) (((u8 *) node->unk4) + 0xD8)) = g;
        if (g < 0.0f)
        {
          *((f32 *) (((u8 *) base[*((s32 *) (arg0 + 0xB8))].unk4) + 0xD8)) = 0.0f;
        }
      }
    }
  }
}

void despawnCraftAnimationSlotNpcsAndMarkStopping(s32);

static __inline__ u8 tcOnce(s32 clip, u16 flag) {
    s32 i;
    if (clip == 0x28C) {
        return 0;
    }
    for (i = 0; i < 14; i++) {
        if (D_mission_overlay_8010B740[i] == clip) {
            i += (s32)D_mission_overlay_8010B780;
            if (*(u8 *)i != 0) return 0;
            *(u8 *)i = 1;
            break;
        }
    }
    if ((gGameSettings != 0xF) ? (clip == 0x104) : (clip == 0x28C)) {
        playSpeechClip(clip, 0x78, 0, flag);
    } else {
        playSpeechClip(clip, 0x73, 0, flag);
    }
    D_mission_overlay_801096B4 = clip;
    D_mission_overlay_801096B0 = 5.0f;
    return 1;
}

static __inline__ u8 tcInv(u8 *o) {
    if (*(f32 *)(o + 0xC8) > 0.0f) {
        if (*(f32 *)(o + 0xC8) == 1.0f) {
            *(f32 *)(o + 0xC8) -= 0.01f;
        }
        return 1;
    }
    return 0;
}

s32 tcImpl(u8 *o, f32 dt) __asm__("tickCinematicObjectStateMachine");
s32 tcImpl(u8 *o, f32 dt) {
    f32 t;

    t = *(f32 *)(o + 0xC0) - (tcInv(o) ? 0.0f : dt);
    *(f32 *)(o + 0xC0) = t;
    if (t <= 0.0f) {
        spawnNpcDestructionDebris((NpcDebrisObj *)o);
        despawnCraftAnimationSlotNpcsAndMarkStopping(0);
        return 1;
    }
    switch (*(u16 *)(o + 0xB4)) {
    case 0:
    case 8:
        if (D_mission_overlay_801096B8 != 0 && *(f32 *)(o + 0xC0) / *(f32 *)(o + 0xC4) < 0.25f) {
            tcOnce((gGameSettings != 0xF) ? 0x272 : 0x28C, 0);
            tcOnce((gGameSettings != 0xF) ? 0x104 : 0x28C, 1);
            D_mission_overlay_801096B8 = 0;
            break;
        }
        playRandomCutsceneVoiceLine(o);
        break;
    case 1:
        if (tcOnce((gGameSettings != 0xF) ? 0x122 : 0x206, 1)) {
            return 0;
        }
        if (tcOnce((gGameSettings != 0xF) ? 0x123 : 0x207, 1)) {
            return 0;
        }
        if (D_mission_overlay_801096B8 != 0 && *(f32 *)(o + 0xC0) / *(f32 *)(o + 0xC4) < 0.25f) {
            tcOnce((gGameSettings != 0xF) ? 0x272 : 0x28C, 0);
            tcOnce((gGameSettings != 0xF) ? 0x104 : 0x28C, 1);
            D_mission_overlay_801096B8 = 0;
            break;
        }
        playRandomCutsceneVoiceLine(o);
        break;
    case 2:
        if (tcOnce((gGameSettings != 0xF) ? 0x124 : 0x208, 1)) {
            return 0;
        }
        playRandomCutsceneVoiceLine(o);
        break;
    case 5:
        if (tcOnce((gGameSettings != 0xF) ? 0x132 : 0x28C, 1)) {
            return 0;
        }
    default:
        playRandomCutsceneVoiceLine(o);
        break;
    }
    return 0;
}

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

typedef struct { u8 p[0x198]; s32 f198; s32 f19C; s32 f1A0; } IpA;
typedef struct { u8 p[0x184]; u16 f184; } IpP;
typedef struct { s32 pad[3]; s32 f; } GsArr;
#define F(t,o) (*(t *)((u8 *)arg0 + (o)))
#define GS ((s32 *)&gGameSettings)
extern f32 D_mission_overlay_801096B0;
extern s32 D_mission_overlay_801096B4;
extern u8 D_mission_overlay_801096B8;
extern u8 D_mission_overlay_801096B9;
extern s32 D_mission_overlay_8010BC6C;
extern s32 D_mission_overlay_8010BC70;
extern s32 D_mission_overlay_8010CA1C;
extern s32 D_main_bss_80130B18;
extern u16 getNextSlotNpcTypeId(u16);
extern void destroyNpcSlotByIndex(u16);
extern void destroyNpcSlotChain(u16);
extern void factor5RemoveListNode(void *);
extern u16 allocateNpcSlot(s32);
extern void dispatchEffectObjectBehavior(s32, u16, f32 *);
void applyCraftCapabilityFlagsV(void *) __asm__("applyCraftCapabilityFlags");
void populateCutsceneSubtitleTextIdsV(void) __asm__("populateCutsceneSubtitleTextIds");
void initPlayerCraftTrailBuffersV(void *) __asm__("initPlayerCraftTrailBuffers");

void initPlayerCraftMovementMode(struct inner_player_struct *arg0)
{
  u8 *gs;
  struct player_struct *pp;
  struct player_struct *pl;
  D_mission_overlay_801096B0 = 0.0f;
  D_mission_overlay_801096B4 = -1;
  arg0->unk028 = 0.0f;
  arg0->unk02C = 0.0f;
  arg0->unk030 = 0.0f;
  D_mission_overlay_801096B8 = 1;
  pl = gPlayers;
  pp = &pl[arg0->unk0B8];
  if (!(((IpP *)pp)->f184 & 0x40))
  {
    *((s32 *) (((u8 *) arg0) + 0x1C8)) = 2;
    *((s32 *) (((u8 *) arg0) + 0x184)) = 0;
    arg0->fire_mode = 0;
    *((u16 *) (((u8 *) arg0) + 0x1CC)) = 0xFFFF;
  }
  else
  {
    *((f32 *) (((u8 *) arg0) + 0x184)) = 2.0f;
  }
  if ((*((u16 *) (((u8 *) arg0) + 0x1CC))) != 0xFFFF)
  {
    u16 a;
    while ((a = getNextSlotNpcTypeId(*((u16 *) (((u8 *) arg0) + 0x1CC)))) != 0xFFFF)
    {
      destroyNpcSlotByIndex(a);
    }

    destroyNpcSlotChain(*((u16 *) (((u8 *) arg0) + 0x1CC)));
    *((u16 *) (((u8 *) arg0) + 0x1CC)) = 0xFFFF;
  }
  if ((*((u8 *) (((u8 *) arg0) + 0x24C))) != 0)
  {
    *((u8 *) (((u8 *) arg0) + 0x24C)) = 0;
    factor5RemoveListNode(((u8 *) arg0) + 0x208);
  }
  *((u16 *) (((u8 *) arg0) + 0x1CC)) = allocateNpcSlot(0);
  ;
  if ((((GsArr *)((s32 *)&gGameSettings + arg0->unk0B8))->f) & 0x200)
  {
    arg0->blasterDamageMultiplier = 2.0f;
  }
  else
  {
    arg0->blasterDamageMultiplier = 1.0f;
  }
  {
    f32 f = 0.0f;
    if (D_main_bss_80130B18 & 0x10000)
    {
      f = 1.0f;
    }
    arg0->advancedShieldTimer = f;
  }
  *((s32 *) (((u8 *) arg0) + 0x188)) = 0;
  *((s32 *) (((u8 *) arg0) + 0x18C)) = 0;
  *((s32 *) (((u8 *) arg0) + 0x17C)) = 0;
  dispatchEffectObjectBehavior(arg0->unk0B8, arg0->unk0B4, &arg0->posX);
  D_mission_overlay_8010BC6C = 0;
  D_mission_overlay_8010BC70 = 0;
  ((IpA *)arg0)->f1A0 = 0;
  ((IpA *)arg0)->f19C = 0;
  ((IpA *)arg0)->f198 = 0;
  D_mission_overlay_8010CA1C &= ~0x100;
  applyCraftCapabilityFlagsV(arg0);
  populateCutsceneSubtitleTextIdsV();
  switch (arg0->unk0B4)
  {
    case 3:
    case 4:
      ((GsArr *)((s32 *)&gGameSettings + arg0->unk0B8))->f &= 0xFEFFFFFF;
      break;
    default:
      ((GsArr *)((s32 *)&gGameSettings + arg0->unk0B8))->f |= 0x01000000;
      break;
  }
  initPlayerCraftTrailBuffersV(arg0);
  D_mission_overlay_801096B9 = 0;
  *((u8 *) (((u8 *) arg0) + 0x1BC)) = 0;
}

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

s32 psImpl(s32 clip, s32 flag) __asm__("playSpeechClipOncePerLevel");
s32 psImpl(s32 clip, s32 flag) {
    s32 i;
    if (clip == 0x28C) return 0;
    for (i = 0; i < 14; i++) {
        if (D_mission_overlay_8010B740[i] == clip) {
            i += (s32)D_mission_overlay_8010B780;
            if (*(u8 *)i != 0) return 0;
            *(u8 *)i = 1;
            break;
        }
    }
    if ((gGameSettings != 0xF) ? (clip == 0x104) : (clip == 0x28C)) {
        playSpeechClip(clip, 0x78, 0, flag);
    } else {
        playSpeechClip(clip, 0x73, 0, flag);
    }
    D_mission_overlay_801096B4 = clip;
    D_mission_overlay_801096B0 = 5.0f;
    return 1;
}

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
