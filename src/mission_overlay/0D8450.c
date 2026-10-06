#include "common.h"
#include "common_types.h"

extern void rs_memset(void *, s32, s32);
extern s32 setNpcHealth(s32, void *, void *);
extern void initActorMotionParams(s32, f32, f32, f32, f32);
extern void setObjectDetailLevel(s32, s32);
extern void *lookupHmtMaterialByName(s32, char *, s32 *);
extern s32 D_main_bss_80137CE4;

void npcWingmanResetState(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 *def = *(u8 **)(npc + 0x34);

    rs_memset(npc + 0x68, 0, 0x30);
    if (setNpcHealth(*(s32 *)(npc + 0x38), def + 0x6C, def) > 0) {
        initActorMotionParams(*(s32 *)(npc + 0x38), ((f32 *)(def + 0xC0))[D_main_bss_80137CE4], ((f32 *)(def + 0xC4))[D_main_bss_80137CE4], ((f32 *)(def + 0xC8))[D_main_bss_80137CE4], ((f32 *)(def + 0xCC))[D_main_bss_80137CE4]);
        setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(def + 0xAC));
        npc[0x5C] = 0;
    } else {
        npc[0x5C] = 4;
        npc[0x84] = 1;
    }
    npc[0x53] = 0;
    npc[0xF4] = 0;
    if (*(s32 *)(def + 0x8C) == 0) {
        if (*(s32 *)(def + 0xB4) == 0) {
            *(f32 *)(npc + 0xE4) = 0.0f;
            *(f32 *)(npc + 0xE8) = 0.0f;
        } else {
            *(f32 *)(npc + 0xE4) = 10.0f;
            *(f32 *)(npc + 0xE8) = 1.0f;
        }
        *(s32 *)(npc + 0xEC) = 0;
        *(void **)(npc + 0x98) = lookupHmtMaterialByName(*(s32 *)(npc + 0x30), "wngrot_a", NULL);
        *(void **)(npc + 0x9C) = lookupHmtMaterialByName(*(s32 *)(npc + 0x30), "wngrot_b", NULL);
        npc[0xF0] = 0;
    }
}

extern void initObjectAnimSubstruct(s32, f32, f32, f32, f32, void *, s32, f32, f32, s32);
extern s32 npcWingmanState0(void *);
extern s32 npcWingmanState1(void *);
extern s32 npcWingmanState2(void *);
extern s32 npcWingmanState3(void *);
extern s32 npcWingmanState4(void *);
extern s32 npcWingmanState5(void *);
extern s32 npcWingmanStateNoop(void);
extern s32 npcWingmanState6(void *);
extern f32 D_mission_overlay_8010A910[];

void func_mission_overlay_800D7974(u8 *arg0) {
    u8 *def = *(u8 **)(arg0 + 0x34);
    void *fn;

    arg0[0x5E] = 0;
    arg0[0x5F] = 0;
    switch (arg0[0x5D]) {
    case 0: fn = npcWingmanState0; break;
    case 1: fn = npcWingmanState1; break;
    case 2: fn = npcWingmanState2; break;
    case 3: fn = npcWingmanState3; break;
    case 4: fn = npcWingmanState4; break;
    case 5: fn = npcWingmanState5; break;
    case 6: fn = npcWingmanStateNoop; break;
    case 7: fn = npcWingmanState6; break;
    default: return;
    }
    initObjectAnimSubstruct(*(s32 *)(arg0 + 0x38), *(f32 *)(def + 0xD0), *(f32 *)(def + 0xD4), *(f32 *)(def + 0xD8), *(f32 *)(def + 0xDC), fn, 0, D_mission_overlay_8010A910[arg0[0x5D]], 15.0f, 0);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanStateEffectShared);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A781C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7820);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7824);

extern char D_mission_overlay_800A781C[];
extern char D_mission_overlay_800A7820[];
extern char D_mission_overlay_800A7824[];
extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern u8 npcWingmanStateEffectShared(void *, void *, f32, u8);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 npcWingmanState0(void *arg0) {
    u8 sp28[0x30];
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    char *name = NULL;
    s32 idx = 0;
    s32 r;
    s32 st = npc[0x53];

    if (st < 4) {
        if (st >= 2) goto effect;
    } else if (st == 5) {
        goto effect;
    }
    {
        switch (npc[0x5E]) {
        case 0:
            name = D_mission_overlay_800A781C;
            idx = 0;
            break;
        case 1:
            name = D_mission_overlay_800A781C;
            idx = 1;
            break;
        case 2:
            name = D_mission_overlay_800A7820;
            idx = 0;
            break;
        case 3:
            name = D_mission_overlay_800A7820;
            idx = 1;
            break;
        }
        npc[0x5E] = (npc[0x5E] + 1) & 3;
        lookupHmtTextureByName(*(s32 *)(npc + 0x30), name, idx, sp28, 0, 0);
        r = npcWingmanStateEffectShared(npc, sp28, 0.0f, npc[0x53]) & 0xFF;
        if (r == 1) {
            if (npc[0x53] == r) {
                play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 0x34, 0x78, 0x3C);
            } else {
                play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 2, 0x5A, 0x28);
            }
        }
    }
    goto done;
effect:
    {
        npc[0x5E] = (npc[0x5E] & 1) ^ 1;
        lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A7824, npc[0x5E], sp28, 0, 0);
        npcWingmanStateEffectShared(npc, sp28, 0.0f, npc[0x53]);
    }
done:
    return 0;
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7834);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanState1);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7844);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7848);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A784C);

f32 getNpcHealthPercentage(s32);
void playSpeechClip(s32, s32, f32, s32);
s16 rand(void);
f32 fabsf(f32);
extern f32 D_main_bss_80130BA4;
extern s32 D_mission_overlay_8010CA20;

typedef struct {
    f32 t0;
    f32 iv;
    u8 pad8[4];
    u8 hurt;
    u8 padD[3];
    f32 t10;
    u8 done14;
    u8 pad15[3];
    f32 t18;
    u8 done1C;
} WingSpeech;

#define WING_CASE(n, a, b, c)                                         \
    case n:                                                           \
        if (st->t0 == 0.0f) {                                         \
            s1 = a;                                                   \
            st->t0 = D_main_bss_80130BA4;                             \
            st->iv = 30.0f;                                           \
        } else if (st->iv <= D_main_bss_80130BA4 - st->t0) {          \
            s1 = b;                                                   \
            st->t0 = D_main_bss_80130BA4;                             \
            st->iv = 1000000.0f;                                      \
        }                                                             \
        if (st->hurt == 0 && getNpcHealthPercentage(*(s32 *)(npc + 0x38)) <= 50.0f) { \
            st->hurt = 1;                                             \
            s2 = c;                                                   \
        }                                                             \
        break;

void npcWingmanBehaviorByMode(u8 *npc, f32 arg1, s32 mode) {
    WingSpeech *st;
    s32 s1;
    s32 s2;
    u32 kind;
    f32 zero;

    if (D_mission_overlay_8010CA20 != 0) {
        return;
    }
    kind = *(u32 *)(*(u8 **)(npc + 0x34) + 0x90);
    s1 = -1;
    if (kind == 7) {
        return;
    }
    zero = 0.0f;
    st = (WingSpeech *)(npc + 0x68);
    switch (mode) {
    case 0:
        s2 = -1;
        switch (kind) {
            WING_CASE(0, 0x1E4, 0x221, 0x1EE)
            WING_CASE(1, 0x26, 0x23, 0x29)
            WING_CASE(2, 0x257, 0x254, 0x25A)
            WING_CASE(3, 0x96, 0x93, 0x99)
            WING_CASE(4, 0xBC, 0xB5, 0xCB)
            WING_CASE(6, 0x3B, 0x3E, 0x41)
            WING_CASE(5, 0x1AF, 0x1AC, 0x1B2)
        }
        if (s1 != -1) {
            playSpeechClip(s1, 0x73, zero, 0);
        }
        if (s2 != -1) {
            playSpeechClip(s2, 0x73, zero, 0);
        }
        break;
    case 2:
        if (st->done14 == 0) {
            if (st->t10 == zero) {
                st->t10 = D_main_bss_80130BA4 + 5.0f + (f32)(s16)(rand() % 8) * 3.5f;
            }
            if (D_main_bss_80130BA4 >= st->t10) {
                st->done14 = 1;
                switch (*(u32 *)(*(u8 **)(npc + 0x34) + 0x90)) {
                case 0:
                    s1 = 0x1EA;
                    break;
                case 4:
                    s1 = 0xCC;
                    break;
                }
                if (s1 != -1) {
                    playSpeechClip(s1, 0x73, zero, 9);
                }
            }
        }
        break;
    case 3:
        switch (kind) {
        case 0:
            s1 = (s16)(rand() % 6) + 0x1FD;
            break;
        case 1:
            s1 = (s16)(rand() % 5) + 0x1E;
            break;
        case 2:
            s1 = (s16)(rand() % 3) + 0x260;
            break;
        case 3:
            s1 = 0x9F;
            break;
        case 4:
            s1 = (s16)(rand() % 4) + 0xD1;
            break;
        case 6:
            s1 = 0x47;
            break;
        case 5:
            s1 = (s16)(rand() % 6) + 0x1B8;
            break;
        }
        if (s1 != -1) {
            playSpeechClip(s1, 0x73, zero, 1);
        }
        break;
    case 4:
        if (st->done1C == 0) {
            if (st->t18 == zero) {

                f32 ab, q = ((f32)(rand() & 0x7F) - 64.0f) * 0.03125f;
                __asm__ volatile("abs.s %0, %1" : "=f"(ab) : "f"(q));
                st->t18 = D_main_bss_80130BA4 + ab + 3.0f;
            }
            if (D_main_bss_80130BA4 >= st->t18) {
                st->done1C = 1;
                switch (*(u32 *)(*(u8 **)(npc + 0x34) + 0x90)) {
                case 0:
                    s1 = 0x1E7;
                    break;
                case 1:
                    s1 = 0x24;
                    break;
                case 2:
                    s1 = 0x255;
                    break;
                case 3:
                    s1 = 0x94;
                    break;
                case 4:
                    s1 = 0xBB;
                    break;
                case 6:
                    s1 = 0x3C;
                    break;
                case 5:
                    s1 = 0x1AD;
                    break;
                }
                if (s1 != -1) {
                    playSpeechClip(s1, 0x73, zero, 1);
                }
            }
        }
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanSpawnBurstEffects);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0D8450", D_mission_overlay_800A7954);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcWingmanSteerToward);

s32 buildRotationMatrixSlot2(s32, f32);
f32 cosf(f32);
u8 isAudioVoiceActive(void *);
s32 updateActive3DAudioSource(void *, void *, void *, u8);

void npcWingmanUpdateEngineAudio(void *arg0, f32 arg1) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    u8 temp_v0;
    void *temp_s1;

    temp_fv1 = (*(f32 *)((u8 *)(arg0) + 0xEC));
    if (temp_fv1 > 0.0f) {
        temp_fv0 = (*(f32 *)((u8 *)(arg0) + 0xE8)) + (temp_fv1 * arg1);
        (*(f32 *)((u8 *)(arg0) + 0xE8)) = temp_fv0;
        if (temp_fv0 > 1.0f) {
            (*(f32 *)((u8 *)(arg0) + 0xE8)) = 1.0f;
            (*(f32 *)((u8 *)(arg0) + 0xEC)) = 0.0f;
        }
        (*(f32 *)((u8 *)(arg0) + 0xE4)) = (f32) ((1.0f - ((cosf((*(f32 *)((u8 *)(arg0) + 0xE8)) * 3.1415927f) + 1.0f) * 0.5f)) * 10.0f);
    } else if (temp_fv1 < 0.0f) {
        temp_fv0_2 = (*(f32 *)((u8 *)(arg0) + 0xE8)) + (temp_fv1 * arg1);
        (*(f32 *)((u8 *)(arg0) + 0xE8)) = temp_fv0_2;
        if (temp_fv0_2 < 0.0f) {
            (*(f32 *)((u8 *)(arg0) + 0xE8)) = 0.0f;
            (*(f32 *)((u8 *)(arg0) + 0xEC)) = 0.0f;
        }
        (*(f32 *)((u8 *)(arg0) + 0xE4)) = (f32) ((1.0f - ((cosf((*(f32 *)((u8 *)(arg0) + 0xE8)) * 3.1415927f) + 1.0f) * 0.5f)) * 10.0f);
    }
    buildRotationMatrixSlot2((*(s32 *)((u8 *)(arg0) + 0x98)) + 0x1C, (*(f32 *)((u8 *)(arg0) + 0xE4)));
    buildRotationMatrixSlot2((*(s32 *)((u8 *)(arg0) + 0x9C)) + 0x1C, -(*(f32 *)((u8 *)(arg0) + 0xE4)));
    temp_s1 = arg0 + 0xA0;
    if ((*(u8 *)((u8 *)(arg0) + 0xF0)) != 0) {
        temp_v0 = isAudioVoiceActive(temp_s1);
        (*(u8 *)((u8 *)(arg0) + 0xF0)) = temp_v0;
        if (temp_v0 & 0xFF) {
            updateActive3DAudioSource(temp_s1, arg0, arg0 + 0x24, (*(u8 *)((u8 *)(arg0) + 0xF1)));
        }
    }
}

extern char D_mission_overlay_800A7834[];
typedef struct {
    f32 x, y, z;
    u8 padC[0x18];
    f32 vel[3];
    u8 **mesh;
    u8 *rec;
    s32 obj;
    s32 ctx;
    f32 radius;
    f32 scale;
    u16 slot48;
    u16 slot4A;
    u16 slot4C;
    u16 slot4E;
    u16 slot50;
    s8 outCount;
    u8 f53;
    u8 pad54[4];
    f32 f58;
    u8 mode;
    u8 type;
    u8 pad5E[0x42];
    u8 audio[0x4C];
    f32 fEC;
    u8 fF0;
    u8 padF1[3];
    u8 fF4;
} WmObj;

typedef struct {
    u16 slot;
    s16 kind;
} WmSpawn;

void *walkMeshdef0List(char *);
void composeEulerRotationXYZ(void *, s32, s32, s32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, s32);
void composeRotationMatrixSlot1(void *, s32);
void composeRotationMatrixSlot2(void *, s32);
void addVec3At0x24(void *, f32, f32, f32);
void createAndInitObject(void *, s32, void *, void *, s32);
s32 getLevelDatItemByName(char *);
void initActorAsType1(s32, s32, s32, s32, f32, f32, f32);
void setType1ActorVelocity(s32, s32, f32, f32);
u16 popNpcSlotFromTail(u16, void *);
s16 spawnNpcOfType(void *, void *, s32, s32);
s32 allocateAndInitCraftNpcContext(f32, f32, s32);
void factor5RemoveListNode(void *);
void rs_free(s32);
void initActorRenderDescriptorIfUninit(s32, s32, void *, s32, void *);
void clearPendingAndDestroyChildNpc(void *);
void releaseMeshAsset(void *);
void destroyNpcSlotByIndex(u16);
void func_mission_overlay_800AA6D0(void *, f32, void *);
void dispatchEffectByActorType(s32, f32);
void mat34CrossRowsAndCopyPos(void *, void *, f32);
void func_mission_overlay_800EFDE0(s32, s32, s32, f32);
u8 validateActorTargetLOS(s32);
void applyToObjectSubstructByFlag(s32, f32, s32, f32);
void npcWingmanSteerToward(void *, f32);
void npcWingmanSpawnBurstEffects(void *);
s32 isNpcWithinActiveReferenceRange(void *);
void destroyObjectOwnedNpcSlot(s32);
s32 addNpcToVisibilityBucket(s32, void *, void *, f32);
void advanceNpcOnCurvedPath(s32, s32, void *, s32);
u8 *getNpcContextField8(u16);
f32 vec3Length(f32 *);
void syncType1ActorFrameToAnchorIfZeroGate(s32, f32 *);
s32 getNpcCurrentHealth(s32);
void extrapolateNpcPositionForCurrentMode(void *);
s32 getPlayerField2(s32);
s32 dealDamageToNpc(s32, u16);
void unregisterAndFreeNpcSlot(u16, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);
void tallyMidDetailObject(void *);
void setObjectFlagBit4(void *);
void setType1ActorParams(s32, s32, u8, u8, u8, s32);
void dispatchSlotAction5IfActive(void *, void *);
extern u8 D_main_bss_80139560[];
extern u16 D_main_bss_80139574;
extern u16 D_main_bss_80139584;
extern u8 gObjectiveBooleans[];
extern s32 gObjectiveCounts[];
extern u8 attached3DSoundEmitterNpcHandler[];

s32 npcWingmanUpdate(u8 *arg0, s32 action, u8 *arg2) {
    WmObj *s0 = *(WmObj **)(arg0 + 4);
    s32 act = action;
    WmSpawn sp;
    f32 v[4];
    f32 tex[12];
    char *name;
    f32 dt;

    switch ((u16)action) {
    case 1:
        {
        u8 *rec = arg2;
        switch (*(u32 *)(arg2 + 0x8C)) {
        case 0:
        default:
            name = "wmxwng";
            break;
        case 1:
            name = "wmywng";
            break;
        case 2:
            name = "wmawng";
            break;
        case 3:
            name = "wmvwng";
            break;
        case 4:
            name = "wmspdr";
            break;
        case 5:
            name = "wmfalc";
            break;
        case 6:
            name = "tie";
            break;
        case 7:
            name = "t16";
            break;
        }
        s0->mesh = walkMeshdef0List(name);
        s0->rec = arg2;
        s0->x = *(f32 *)(arg2 + 0x10);
        s0->y = *(f32 *)(arg2 + 0x14);
        s0->z = *(f32 *)(arg2 + 0x18);
        composeEulerRotationXYZ(s0, *(s32 *)(arg2 + 0x1C), *(s32 *)(arg2 + 0x20), *(s32 *)(arg2 + 0x24));
        s0->vel[0] = s0->vel[1] = s0->vel[2] = 0.0f;
        {
            f32 inv = 1.0f / *(f32 *)(*s0->mesh + 0x34);
            s0->scale = inv * *(f32 *)(arg2 + 0x28);
            initVec4TripletFromArgs((u8 *)s0->mesh + 0x28, inv * *(f32 *)(arg2 + 0x28), inv * *(f32 *)(arg2 + 0x2C), inv * *(f32 *)(arg2 + 0x30));
        }
        composeRotationMatrixSlot0((u8 *)s0->mesh + 0x28, *(s32 *)(arg2 + 0x1C));
        composeRotationMatrixSlot1((u8 *)s0->mesh + 0x28, *(s32 *)(arg2 + 0x20));
        composeRotationMatrixSlot2((u8 *)s0->mesh + 0x28, *(s32 *)(arg2 + 0x24));
        addVec3At0x24((u8 *)s0->mesh + 0x28, s0->x, s0->y, s0->z);
        *(WmObj **)(arg0 + 8) = s0;
        *(u8 ***)(arg0 + 0xC) = s0->mesh;
        s0->radius = *(f32 *)(*s0->mesh + 0x44) * *(f32 *)(s0->rec + 0x28);
        createAndInitObject(&s0->obj, 0, arg0, npcWingmanResetState, (u16)act != 1 ? (s32)rec : 0);
        s0->type = arg2[0x8F];
        func_mission_overlay_800D7974((u8 *)s0);
        if (s0->mode != 4) {
            name = (char *)(*(s32 *)(arg2 + 0x94) + (s32)arg2);
            if (*name != '-') {
                s32 item = getLevelDatItemByName(name);
                u8 *r = s0->rec;
                initActorAsType1(s0->obj, item, *(s32 *)(r + 0x98), *(s32 *)(r + 0xA8), *(f32 *)(r + 0xA0), *(f32 *)(s0->rec + 0xA4), 1.5f);
                setType1ActorVelocity(s0->obj, *(s32 *)(s0->rec + 0x9C), 2.0f, 10.0f);
                s0->mode = 1;
            }
            {
                u8 *b = D_main_bss_80139560;
                s32 o;
                *(u16 *)((u8 *)s0 + 0x48) = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
                *(u16 *)((u8 *)s0 + 0x4A) = popNpcSlotFromTail(*(u16 *)(b + 0x24), arg0);
                o = 0;
                if (*(s32 *)(arg2 + 0xAC) == 1) {
                    o = 0xA;
                }
                *(u16 *)((u8 *)s0 + 0x4C) = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                popNpcSlotFromTail(*(u16 *)(b + 0x1E), arg0);
                if (*(s32 *)(arg2 + 0xB0) != 0) {
                    s32 o2 = 0x18;
                    if (*(s32 *)(arg2 + 0xAC) == 1) {
                        o2 = 0x1A;
                    }
                    s0->slot4E = popNpcSlotFromTail(*(u16 *)(o2 + b), arg0);
                } else {
                    s0->slot4E = 0xFFFF;
                }
            }
            sp.slot = *(u16 *)(arg0 + 0x16);
            sp.kind = s0->type + 9;
            s0->slot50 = spawnNpcOfType(attached3DSoundEmitterNpcHandler, &sp, 1, 100);
        } else {
            popNpcSlotFromTail(D_main_bss_80139584, arg0);
            s0->slot50 = 0xFFFF;
        }
        switch (s0->type) {
        case 0:
            s0->ctx = allocateAndInitCraftNpcContext(0.25f, 0.25f, 2);
            break;
        case 1:
            s0->ctx = allocateAndInitCraftNpcContext(0.15f, 0.3f, 3);
            break;
        case 2:
            s0->ctx = allocateAndInitCraftNpcContext(0.125f, 0.125f, 0);
            break;
        case 3:
            s0->ctx = allocateAndInitCraftNpcContext(0.2f, 0.15f, 1);
            break;
        case 4:
            s0->ctx = allocateAndInitCraftNpcContext(0.125f, 0.125f, 4);
            break;
        case 5:
        case 6:
            s0->ctx = 0;
            break;
        case 7:
            s0->ctx = allocateAndInitCraftNpcContext(0.25f, 0.25f, 6);
            break;
        }
        s0->outCount = 0;
        }
        break;
    case 2:
        if (s0->type == 0) {
            if (s0->fF0 != 0 && isAudioVoiceActive(s0->audio)) {
                s0->fF0 = 0;
                factor5RemoveListNode(s0->audio);
            }
        }
        if (s0->ctx != 0) {
            rs_free(s0->ctx);
        }
        initActorRenderDescriptorIfUninit(s0->obj, 0, s0->rec, 0, s0->rec + 0x70);
        clearPendingAndDestroyChildNpc(&s0->obj);
        releaseMeshAsset(s0->mesh);
        return 1;
    case 3:
        {
        u8 *rec = s0->rec;
        dt = *(f32 *)arg2;
        if ((*(s32 *)(rec + 0x60) != 0 && gObjectiveBooleans[*(s32 *)(rec + 0x60) - 1] == 0) || (*(s32 *)(rec + 0x64) != 0 && gObjectiveCounts[*(s32 *)(rec + 0x64) - 1] < *(s32 *)(rec + 0x68))) {
        destroy:
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        }
        func_mission_overlay_800AA6D0(s0, dt, s0->rec + 0x34);
        switch (s0->mode) {
        case 0:
            break;
        case 1:
            dispatchEffectByActorType(s0->obj, dt);
            if (s0->type == 0) {
                npcWingmanUpdateEngineAudio(s0, dt);
            }
            mat34CrossRowsAndCopyPos((u8 *)s0->mesh + 0x28, s0, s0->scale);
            func_mission_overlay_800EFDE0(s0->obj, *(s32 *)(s0->rec + 0xB8), *(s32 *)(s0->rec + 0xBC), dt);
            if (validateActorTargetLOS(s0->obj) == 1) {
                applyToObjectSubstructByFlag(s0->obj, dt, 0, 0.0f);
            }
            npcWingmanBehaviorByMode((u8 *)s0, dt, 2);
            break;
        case 2:
        case 3:
            npcWingmanSteerToward(s0, dt);
            break;
        case 4:
            npcWingmanBehaviorByMode((u8 *)s0, dt, 4);
            break;
        }
        if (*(s32 *)(s0->rec + 0x88) != 0) {
            if (s0->mode == 1 || s0->mode == 4) {
                if (isNpcWithinActiveReferenceRange(s0) == 0) {
                    if (++s0->outCount >= 0x15) {
                        goto destroy;
                    }
                } else {
                    s0->outCount = 0;
                }
                destroyObjectOwnedNpcSlot(s0->obj);
            }
            return 1;
        }
        s0->outCount = 0;
        destroyObjectOwnedNpcSlot(s0->obj);
        return 1;
    case 4:
        addNpcToVisibilityBucket(*(s32 *)arg2, s0->mesh, s0, s0->radius);
        if (s0->ctx != 0) {
            advanceNpcOnCurvedPath(*(s32 *)(arg2 + 8), *(s32 *)arg2, s0, s0->ctx);
        }
        return 1;
    case 6:
        if (*(u16 *)arg2 != 0xFFFF) {
            u8 *p = getNpcContextField8(*(u16 *)arg2);
            f32 len;
            v[0] = s0->x - *(f32 *)(p + 0);
            v[1] = s0->y - *(f32 *)(p + 4);
            v[2] = s0->z - *(f32 *)(p + 8);
            len = vec3Length(v);
            if (len > 0.0f) {
                v[0] = v[0] / len * 0.5f;
                v[1] = v[1] / len * 0.5f;
                v[2] = v[2] / len * 0.5f;
                syncType1ActorFrameToAnchorIfZeroGate(s0->obj, v);
            }
        }
        s0->fF4 = 1;
        play3DSoundEvent(0, s0, s0->vel, 14.0f, 0.4f, 0, 0x3E, 0x7E, 0x5A);
        return 1;
    case 5:
        {
        u8 *a5 = arg2;
        if (getNpcCurrentHealth(s0->obj) > 0) {
            extrapolateNpcPositionForCurrentMode(arg2);
            if (s0->fF4 == 0) {
                play3DSoundEvent(0, s0, s0->vel, 14.0f, 0.4f, 0, 0x1B, 0x7E, 0x5A);
            }
            s0->fF4 = 0;
            if (*(u16 *)arg2 != 0xFFFF && *(u16 *)(arg2 + 2) != (u16)getPlayerField2(0)) {
                npcWingmanBehaviorByMode((u8 *)s0, 0.0f, 0);
            }
            if (dealDamageToNpc(s0->obj, *(u16 *)(a5 + 6)) <= 0) {
                lookupHmtTextureByName((s32)s0->mesh, D_mission_overlay_800A7834, 0, tex, 0, 0);
                s0->f58 = tex[1] - s0->y;
                s0->mode = 2;
                npcWingmanBehaviorByMode((u8 *)s0, 0.0f, 3);
                npcWingmanSpawnBurstEffects(s0);
                unregisterAndFreeNpcSlot(s0->slot48, arg0);
                unregisterAndFreeNpcSlot(s0->slot4A, arg0);
                unregisterAndFreeNpcSlot(s0->slot4C, arg0);
                if (s0->slot4E != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s0->slot4E, arg0);
                }
                popNpcSlotFromTail(D_main_bss_80139574, arg0);
                {
                    u8 *r = s0->rec;
                    datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s0->rec + 0x84));
                }
                tallyMidDetailObject(arg0);
                setObjectFlagBit4(arg0);
            }
        }
        if (*(u16 *)a5 != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)a5);
        }
        return 1;
        }
    case 9:
        switch (arg2[0x18]) {
        case 11:
            npcWingmanBehaviorByMode((u8 *)s0, 0.0f, 5);
            return 1;
        case 1:
            setType1ActorParams(s0->obj, *(s32 *)arg2, arg2[9], arg2[0xA], arg2[8], *(s32 *)(arg2 + 4));
            return 1;
        case 4:
            s0->f53 = arg2[3];
            break;
        case 0:
            if (*(s32 *)arg2 == 2 && s0->type == 0) {
                if ((s32)*(f32 *)(arg2 + 4) == 0) {
                    s0->fEC = -1.0f;
                    play3DSoundEvent(0, s0, s0->vel, 20.0f, 0.0f, 0, 0x20, 0x5A, 0);
                } else {
                    s0->fEC = 1.0f;
                    play3DSoundEvent(0, s0, s0->vel, 20.0f, 0.0f, 0, 0x1F, 0x5A, 0);
                }
            }
            return 1;
        case 8:
            if (getNpcCurrentHealth(s0->obj) > 0) {
                u8 *b;
                s32 o;
                u16 id;
                unregisterAndFreeNpcSlot(s0->slot4A, arg0);
                b = D_main_bss_80139560;
                o = 0x2C;
                if (*(s32 *)arg2 == 1) {
                    o = 0x2E;
                }
                s0->slot4A = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                unregisterAndFreeNpcSlot(s0->slot4C, arg0);
                o = 0x12;
                if (*(s32 *)arg2 == 1) {
                    o = 0xE;
                }
                s0->slot4C = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                if (s0->slot4E != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s0->slot4E, arg0);
                    if (*(s32 *)(s0->rec + 0xB0) != 0) {
                        o = 0x18;
                        if (*(s32 *)arg2 == 1) {
                            o = 0x1A;
                        }
                        s0->slot4E = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    }
                }
                setObjectDetailLevel(s0->obj, *(s32 *)arg2);
            }
            return 1;
        }
        break;
    case 7:
        dispatchSlotAction5IfActive(arg0, arg2);
        return 1;
    case 11:
        *(u16 *)(arg2 + 2) = 0x27;
        break;
    }
    return 1;
}

extern char D_mission_overlay_800A781C[];
extern char D_mission_overlay_800A7820[];
extern void lookupHmtTextureByName(s32, char *, s32, void *, s32, s32);
extern u8 npcWingmanStateEffectShared(void *, void *, f32, u8);
extern void play3DSoundEvent(s32, void *, void *, f32, f32, s32, s32, s32, s32);

s32 npcWingmanState2(void *arg0) {
    u8 tex[0x30];
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    char *name = NULL;

    switch (npc[0x5E]) {
    case 0:
        name = D_mission_overlay_800A781C;
        break;
    case 1:
        name = D_mission_overlay_800A7820;
        break;
    }
    npc[0x5E] ^= 1;
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), name, 0, tex, 0, 0);
    if (npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]) == 1) {
        play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 2, 90, 40);
    }
    return 0;
}

extern char D_mission_overlay_800A7844[];

s32 npcWingmanState3(void *arg0) {
    u8 tex[0x30];
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    char *name = NULL;
    s32 variant = 0;

    switch (npc[0x5E]) {
    case 0:
        name = D_mission_overlay_800A7844;
        break;
    case 1:
        name = D_mission_overlay_800A7844;
        variant = 1;
        break;
    }
    npc[0x5E] ^= 1;
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), name, variant, tex, 0, 0);
    if (npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]) == 1) {
        play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 2, 90, 40);
    }
    return 0;
}

extern char D_mission_overlay_800A7848[];

s32 npcWingmanState4(void *arg0) {
    u8 tex[0x30];
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 hit;

    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A7848, 0, tex, 0, 0);
    hit = npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), D_mission_overlay_800A7848, 1, tex, 0, 0);
    hit |= npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]);
    if (hit == 1) {
        play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 2, 90, 40);
    }
    return 0;
}

extern char D_mission_overlay_800A784C[];

s32 npcWingmanState5(void *arg0) {
    u8 tex[0x30];
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    char *name = NULL;
    u8 hit;

    switch (npc[0x5E]) {
    case 0:
        name = D_mission_overlay_800A7844;
        break;
    case 1:
        name = D_mission_overlay_800A784C;
        break;
    }
    npc[0x5E] ^= 1;
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), name, 0, tex, 0, 0);
    hit = npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]);
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), name, 1, tex, 0, 0);
    hit |= npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]);
    if (hit == 1) {
        play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 0x2F, 0x6E, 0x3C);
    }
    return 0;
}

s32 npcWingmanStateNoop(void) {
    return 1;
}

s32 npcWingmanState6(void *arg0) {
    u8 tex[0x30];
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    char *name = NULL;
    s32 variant = 0;

    switch (npc[0x5E]) {
    case 0:
        name = D_mission_overlay_800A7844;
        break;
    case 1:
        name = D_mission_overlay_800A7844;
        variant = 1;
        break;
    }
    npc[0x5E] ^= 1;
    lookupHmtTextureByName(*(s32 *)(npc + 0x30), name, variant, tex, 0, 0);
    if (npcWingmanStateEffectShared(npc, tex, 0.0f, npc[0x53]) == 1) {
        play3DSoundEvent(0, npc, npc + 0x24, 20.0f, 0.2f, 0, 0x31, 100, 50);
    }
    return 0;
}

static u32 D_mission_overlay_800A7B04[] __attribute__((section(".rodata"))) = { 0x10600001, 0x00000000, 0x8FC2001C };

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcTieVariantTickEffects);

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} TieVec3;

extern u8 spawnNpcAnchoredEffectSlot(s32, f32, s32);
extern f32 wrapAngleToCyclicRange(f32, f32, void *, s32);
extern s32 isTerrainCellBlockedAtWorldXz(f32, f32, void *);
extern void quatFromAxisAngle(f32 *, void *, f32);
extern void rotateVec3ByQuat(f32 *, void *, void *);
extern u8 D_main_bss_80138058[];

void npcTieVariantSteerToward(u8 *arg0, f32 dt) {
    f32 q[4];
    TieVec3 v;
    f32 h;
    u8 st;

    if (arg0[0x87] != 2) {
        return;
    }
    *(f32 *)(arg0 + 0) += *(f32 *)(arg0 + 0x24) * dt;
    *(f32 *)(arg0 + 4) += *(f32 *)(arg0 + 0x28) * dt;
    *(f32 *)(arg0 + 8) += *(f32 *)(arg0 + 0x2C) * dt;
    if (spawnNpcAnchoredEffectSlot(*(s32 *)(arg0 + 0x38), dt, 100) == 1) {
        arg0[0x87] = 3;
    }
    *(f32 *)(arg0 + 0x28) += dt * 2.2f;
    h = wrapAngleToCyclicRange(*(f32 *)(arg0 + 0), *(f32 *)(arg0 + 8), D_main_bss_80138058, 0);
    if (h < *(f32 *)(arg0 + 4)) {
        *(f32 *)(arg0 + 4) = h;
        if (isTerrainCellBlockedAtWorldXz(*(f32 *)(arg0 + 0), *(f32 *)(arg0 + 8), D_main_bss_80138058) == 0) {
            st = 3;
        } else {
            st = 4;
        }
        arg0[0x87] = st;
    }
    quatFromAxisAngle(q, arg0 + 0x98, -*(f32 *)(arg0 + 0xA4));
    rotateVec3ByQuat(q, arg0 + 0xC, &v);
    *(TieVec3 *)(arg0 + 0xC) = v;
    rotateVec3ByQuat(q, arg0 + 0x18, &v);
    *(TieVec3 *)(arg0 + 0x18) = v;
    *(u16 *)(arg0 + 0x84) += (u32)(dt * 2497.561f);
    if (*(u16 *)(arg0 + 0x84) >= 0x4000) {
        *(u16 *)(arg0 + 0x84) = 0x3FFF;
    }
}

extern u8 validateActorTargetLOS(s32);
extern void applyToObjectSubstructByFlag(s32, f32, s32, f32);
extern f32 getEffectIntensity(s32);
extern void setEffectIntensity(s32, f32);
extern s32 triggerCueWithSlotEffect(s32, s32, void *, void *, s32, f32, f32);
extern s32 slotDispatcherIter(u16, s32, void *);

typedef struct {
    u16 kind;
    u8 pad[0x16];
    f32 val;
} TieSlotMsg;

void npcTieVariantTickAttachmentEffect(u8 *arg0, f32 dt) {
    u8 tex[0x30];
    TieSlotMsg msg;
    f32 zero;
    f32 inten;
    s32 h;
    s32 *cnt;
    s32 *base;
    u8 *def;

    if (validateActorTargetLOS(*(s32 *)(arg0 + 0x38)) == 1) {
        applyToObjectSubstructByFlag(*(s32 *)(arg0 + 0x38), dt, 0, 0.0f);
    }
    if (arg0[0xBA] != 0) {
        f32 t = *(f32 *)(arg0 + 0xA8) - dt;
        zero = 0.0f;
        *(f32 *)(arg0 + 0xA8) = t;
        if (t <= zero) {
            base = (s32 *)(*(u8 **)(arg0 + 0x34) + 0xE4);
            cnt = (s32 *)(D_main_bss_80137CE4 * 4 + (s32)base);
            if (*cnt > 0) {
                (*cnt)--;
                *(f32 *)(arg0 + 0xA8) = *(f32 *)(arg0 + 0xAC);
                lookupHmtTextureByName(*(s32 *)(arg0 + 0x30), "c", 0, tex, 0, 0);
                if (arg0[0xBB] == 1) {
                    *(f32 *)(tex + 0x24) = zero;
                    *(f32 *)(tex + 0x28) = 4.0f;
                    *(f32 *)(tex + 0x2C) = zero;
                } else {
                    *(f32 *)(tex + 0x24) = *(f32 *)(arg0 + 0x24);
                    *(f32 *)(tex + 0x28) = *(f32 *)(arg0 + 0x28) + 4.0f;
                    *(f32 *)(tex + 0x2C) = *(f32 *)(arg0 + 0x2C);
                }
                inten = getEffectIntensity(*(s32 *)(arg0 + 0x38));
                setEffectIntensity(*(s32 *)(arg0 + 0x38), *(f32 *)(arg0 + 0xB0));
                h = triggerCueWithSlotEffect(*(s32 *)(arg0 + 0x38), 9, tex, 0, 0, 0, -1.0f);
                setEffectIntensity(*(s32 *)(arg0 + 0x38), inten);
                msg.kind = 6;
                msg.val = *(f32 *)(arg0 + 0xB4);
                slotDispatcherIter(h, 0xA, &msg);
                play3DSoundEvent(0, arg0, arg0 + 0x24, 14.0f, 0.8f, 0, 0x30, 0x6E, 0x3C);
                if (--*(s16 *)(arg0 + 0xB8) > 0) {
                    return;
                }
            }
            arg0[0xBA] = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0D8450", npcTieVariantHandleDestruction);

#define TV_ABSF(x) ({ f32 _r; __asm__ volatile("abs.s %0, %1" : "=f"(_r) : "f"(x)); _r; })

typedef struct {
    f32 x, y, z;
} TvVec;

typedef struct {
    u16 a, b;
    u16 c, d;
    f32 e;
} TvMsg;

typedef struct {
    f32 x, y, z;
    u8 pad0C[0x18];
    f32 vel[3];
    u8 *mesh;
    u8 *def;
    s32 obj;
    s32 ctx;
    u8 audio[0x44];
    u16 snd;
    u8 audioOn;
    u8 state;
    u16 pad88;
    s16 kind;
    f32 radius;
    u16 slot90;
    u16 slot92;
    u16 slot94;
    u16 slot96;
    u8 pad98[0x10];
    s32 iA8;
    f32 fAC;
    f32 fB0;
    f32 fB4;
    s16 sB8;
    u8 bBA;
    u8 bBB;
    u8 bBC;
    s8 outCount;
} TvObj;

extern u8 D_main_bss_80130B39;
extern u8 D_mission_overlay_8010A930[];
void npcRadarDishInit(void *);
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
void initActorAsType4(s32, char *, f32, s32, s32);
void updateObjectFlags110(s32, s32, s32);
void mat34CrossRowsAndCopyPosPtr(void *, void *, void *);
void composeRandomRotationMatrix(void *, void *, f32, s32, s32, s32);
void scaleVec3ByRandomRange(void *, f32, f32);
void spawnDebris1Npc(void *, void *, f32, f32, f32);
void spawnOrientedEffectIfBudgetOk(void *, s32, s32, f32, f32);
void spawnNpcType0xAFromTemplate(void *, f32);
void spawnByteAnimDebrisDefault(void *);
void distanceAndDopplerNpcHelper(void *, f32, f32);
void spawnWaterSprayDebrisAndBurst(void *, f32, f32, f32, f32, f32);
s32 mostlyMusyxFlagGatedHelper(void *);
void safeLookup3DSoundEntry(s32, u16);
void npcTieVariantHandleDestruction(void *, u16, u16, u16);
s32 getObjectDetailLevel(s32);
void func_mission_overlay_800EFD6C(s32);
f32 getActorCurrentValueByType(s32);

s32 npcTieVariantUpdate(u8 *arg0, s32 action, u8 *arg2) {
    s32 act = action;
    register TvObj *s1 asm("$17") = *(TvObj **)(arg0 + 4);
    union {
        TvVec v;
        TvMsg m;
    } sp28;
    f32 sp38[4];
    f32 sp48[4];
    f32 sp58[4];
    f32 dt;
    s32 i;
    s32 n;

    switch ((u16)act) {
    case 1:
    case 8:
        {
        u8 *rec = arg2;
        u8 *src = arg2;
        char *name;
        s16 kind;
        if (*(u16 *)(arg0 + 0x14) & 0x20) {
            rec = *(u8 **)(arg2 + 0xC);
            s1->def = rec;
        } else {
            s1->def = arg2;
        }
        switch (*(u16 *)rec) {
        case 0x13:
            kind = 2;
            s1->mesh = walkMeshdef0List("tie_bomber");
            break;
        case 0x12:
            kind = 1;
            s1->mesh = walkMeshdef0List("tie_inter");
            break;
        case 0x29:
            kind = 3;
            s1->mesh = walkMeshdef0List("tie_d");
            break;
        case 0x43:
            kind = 4;
            s1->mesh = walkMeshdef0List("v_tcc_hi");
            break;
        case 0xC:
        default:
            kind = 0;
            s1->mesh = walkMeshdef0List("tie_fighter");
            break;
        }
        *(u8 **)(s1->mesh + 4) = D_mission_overlay_8010A930;
        if ((u16)act == 1) {
            s1->x = *(f32 *)(rec + 0x10);
            s1->y = *(f32 *)(rec + 0x14);
            s1->z = *(f32 *)(rec + 0x18);
            name = (char *)(*(s32 *)(rec + 0x8C) + (s32)rec);
        } else if (*(u8 *)(*(u8 **)(src + 4) + 2) == 3) {
            *(TvVec *)s1 = **(TvVec **)(src + 8);
            name = *(char **)src;
        } else {
            name = (char *)(*(s32 *)(rec + 0x8C) + (s32)rec);
            if (name != NULL && *name == '+') {
                *(TvVec *)s1 = **(TvVec **)(src + 8);
            } else {
                name = "-";
                s1->x = 0.0f;
                s1->y = 0.0f;
                s1->z = 0.0f;
            }
        }
        composeEulerRotationXYZ(s1, *(s32 *)(rec + 0x1C), *(s32 *)(rec + 0x20), *(s32 *)(rec + 0x24));
        s1->vel[0] = s1->vel[1] = s1->vel[2] = 0.0001f;
        mat34CrossRowsAndCopyPosPtr(s1->mesh + 0x28, s1, rec + 0x28);
        *(TvObj **)(arg0 + 8) = s1;
        *(u8 **)(arg0 + 0xC) = s1->mesh;
        {
            u8 *b = D_main_bss_80139560;
            s32 o;
            s1->slot90 = popNpcSlotFromTail(*(u16 *)(b + 0x1C), arg0);
            o = 0x2C;
            if (*(s32 *)(rec + 0xB4) == 1) {
                o = 0x2E;
            }
            s1->slot92 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            o = 0;
            if (*(s32 *)(rec + 0xB4) == 1) {
                o = 0xA;
            }
            s1->slot94 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            if (*(s32 *)(rec + 0xB8) != 0) {
                o = 0x18;
                if (*(s32 *)(rec + 0xB4) == 1) {
                    o = 0x1A;
                }
                s1->slot96 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
            } else {
                s1->slot96 = 0xFFFF;
            }
        }
        createAndInitObject(&s1->obj, 0, arg0, npcRadarDishInit, (u16)act != 1 ? (s32)src : 0);
        s1->kind = kind;
        s1->audioOn = 0;
        if (*name == '+') {
            u8 *d = s1->def;
            initActorAsType4(s1->obj, name + 1, ((f32 *)(d + 0x90))[D_main_bss_80137CE4], *(s32 *)(d + 0xB0), *(s32 *)(d + 0xAC));
            {
                u8 *d2 = s1->def;
                u16 f = (*(s32 *)(d2 + 0xA4) != 0) << 6;
                if (*(s32 *)(d2 + 0xA8) != 0) {
                    f |= 0x80;
                }
                updateObjectFlags110(s1->obj, f, f ^ 0xFFFF);
            }
            if (kind == 4) {
                goto snd4;
            }
            s1->audioOn = 1;
            s1->snd = 0x2000;
            play3DSoundEventVariant(s1->audio, s1, s1->vel, 21.0f, 0.6f, 0xF, 7, 1, 0x7F, 0x28);
        } else if (*name != '-') {
            s32 item = getLevelDatItemByName(name);
            u8 *d = s1->def;
            initActorAsType1(s1->obj, item, ((s32 *)(d + 0x90))[D_main_bss_80137CE4], *(s32 *)(d + 0xA0), *(f32 *)(d + 0x98), *(f32 *)(s1->def + 0x9C), 2.0f);
            setType1ActorVelocity(s1->obj, *(s32 *)(s1->def + 0x94), 2.0f, 10.0f);
            if (kind != 4) {
                s1->audioOn = 1;
                s1->snd = 0x2000;
                play3DSoundEventVariant(s1->audio, s1, s1->vel, 21.0f, 0.6f, 0xF, 7, 1, 0x7F, 0x28);
            } else {
            snd4:
                s1->audioOn = 1;
                s1->snd = 0x2000;
                play3DSoundEventVariant(s1->audio, s1, s1->vel, 12.0f, 0.6f, 0xF, 0x51, 1, 0x7F, 0x3C);
            }
        }
        switch (s1->kind) {
        case 1:
            s1->ctx = allocateAndInitCraftNpcContext(0.22f, 0.35f, 9);
            break;
        case 2:
            s1->ctx = allocateAndInitCraftNpcContext(0.35f, 0.23f, 0xD);
            break;
        case 3:
            s1->ctx = allocateAndInitCraftNpcContext(0.22f, 0.35f, 9);
            break;
        case 4:
            s1->ctx = 0;
            break;
        case 0:
        default:
            s1->ctx = allocateAndInitCraftNpcContext(0.24f, 0.24f, 9);
            break;
        }
        if (s1->ctx != 0) {
            *(f32 *)(s1->ctx + 0x14) = 7.0f;
            *(f32 *)(s1->ctx + 0x10) = 1.0f;
        }
        s1->outCount = 0;
        s1->radius = *(f32 *)(*(u8 **)s1->mesh + 0x44) * *(f32 *)(s1->def + 0x28);
        }
        break;
    case 2:
        initActorRenderDescriptorIfUninit(s1->obj, getNpcCurrentHealth(s1->obj) < 1, s1->def, 0, s1->def + 0x70);
        if (s1->audioOn != 0) {
            factor5RemoveListNode(s1->audio);
        }
        if (s1->ctx != 0) {
            rs_free(s1->ctx);
        }
        clearPendingAndDestroyChildNpc(&s1->obj);
        releaseMeshAsset(s1->mesh);
        return 1;
    case 3:
        dt = *(f32 *)arg2;
        func_mission_overlay_800AA6D0(s1, dt, s1->def + 0x34);
        switch (s1->state) {
        case 0:
            s1->state = 1;
        case 1:
            dispatchEffectByActorType(s1->obj, dt);
            func_mission_overlay_800EFDE0(s1->obj, *(s32 *)(s1->def + 0xBC), 6, dt);
            npcTieVariantTickAttachmentEffect((u8 *)s1, dt);
            break;
        case 2:
            npcTieVariantSteerToward((u8 *)s1, dt);
            break;
        case 3:
            if (s1->bBC != 0) {
                s32 n3 = (s16)(rand() % 2) + 3;
                for (i = 0; i < n3; i++) {
                    f32 a, b;
                    composeRandomRotationMatrix(&sp28, sp38, s1->radius * 0.5f, 0x5A, 0, 0);
                    sp28.v.x += s1->x;
                    sp28.v.y += s1->y;
                    sp28.v.z += s1->z;
                    scaleVec3ByRandomRange(sp38, 3.0f, 4.0f);
                    a = TV_ABSF(((f32)(rand() & 0x7F) - 64.0f) / 12.8f) + 27.0f;
                    b = TV_ABSF(((f32)(rand() & 0x7F) - 64.0f) / 160.0f) + 0.5f;
                    spawnDebris1Npc(&sp28, sp38, a, b, TV_ABSF(((f32)(rand() & 0x7F) - 64.0f) / 213.33333f) + 0.2f);
                }
            }
            spawnOrientedEffectIfBudgetOk(s1, 0, 0, 1.0f, 1.0f);
            spawnNpcType0xAFromTemplate(s1, s1->radius * 4.0f);
            spawnByteAnimDebrisDefault(s1);
            play3DSoundEvent(0, s1, s1->vel, 24.0f, 0.8f, 0, 0x21, 0x7F, 0x50);
        case 5:
        destroy:
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        case 4:
            n = (s16)(rand() % 3) + 5;
            for (i = 0; i < n; i++) {
                f32 a, b;
                composeRandomRotationMatrix(sp48, sp58, s1->radius * 0.5f, 0x50, 0, 0);
                sp48[0] += s1->x;
                sp48[1] += s1->y;
                sp48[2] += s1->z;
                scaleVec3ByRandomRange(sp58, 1.5f, 3.5f);
                a = TV_ABSF(((f32)(rand() & 0x7F) - 64.0f) / 12.8f) + 12.0f;
                b = TV_ABSF(((f32)(rand() & 0x7F) - 64.0f) * 0.015625f) + 1.0f;
                spawnDebris1Npc(sp48, sp58, a, b, TV_ABSF(((f32)(rand() & 0x7F) - 64.0f) / 213.33333f) + 0.3f);
                distanceAndDopplerNpcHelper(sp48, 0.1f, 0.4f);
            }
            spawnWaterSprayDebrisAndBurst(s1, 0.2f, 2.0f, 2.0f, 4.0f, 1.0f);
            spawnByteAnimDebrisDefault(s1);
            play3DSoundEvent(0, s1, s1->vel, 20.0f, 0.8f, 0, 0x73, 0x7F, 0x50);
            destroyNpcSlotByIndex(*(u16 *)(arg0 + 0x16));
            return 1;
        }
        if (*(s32 *)(s1->def + 0x88) == 0 || isNpcWithinActiveReferenceRange(s1) != 0) {
            s1->outCount = 0;
        } else if (++s1->outCount >= 0x15) {
            goto destroy;
        }
        destroyObjectOwnedNpcSlot(s1->obj);
        return 1;
    case 7:
        dispatchSlotAction5IfActive(arg0, arg2);
        return 1;
    case 4:
        if (s1->state == 2) {
            mat34CrossRowsAndCopyPos(s1->mesh + 0x28, s1, *(f32 *)(s1->def + 0x28));
            {
                u8 *au = s1->audio;
                if (s1->audioOn != 0) {
                    updateActive3DAudioSource(au, s1, s1->vel, 0x7F);
                    safeLookup3DSoundEntry(mostlyMusyxFlagGatedHelper(au), s1->snd);
                }
            }
        } else if (s1->state != 3) {
            mat34CrossRowsAndCopyPos(s1->mesh + 0x28, s1, *(f32 *)(s1->def + 0x28));
            if (s1->audioOn != 0) {
                updateActive3DAudioSource(s1->audio, s1, s1->vel, 0x7F);
            }
        }
        addNpcToVisibilityBucket(*(s32 *)arg2, s1->mesh, s1, s1->radius);
        if (s1->ctx != 0) {
            advanceNpcOnCurvedPath(*(s32 *)(arg2 + 8), *(s32 *)arg2, s1, s1->ctx);
        }
        return 1;
    case 6:
        if (*(u16 *)arg2 != 0xFFFF) {
            u8 *p = getNpcContextField8(*(u16 *)arg2);
            f32 len;
            sp28.v.x = s1->x - *(f32 *)(p + 0);
            sp28.v.y = s1->y - *(f32 *)(p + 4);
            sp28.v.z = s1->z - *(f32 *)(p + 8);
            len = vec3Length(&sp28.v.x);
            if (len > 0.0f) {
                sp28.v.x = sp28.v.x / len * 0.5f;
                sp28.v.y = sp28.v.y / len * 0.5f;
                sp28.v.z = sp28.v.z / len * 0.5f;
                syncType1ActorFrameToAnchorIfZeroGate(s1->obj, &sp28.v.x);
            }
        }
        return 1;
    case 5:
        {
        u8 *a5 = arg2;
        if (getNpcCurrentHealth(s1->obj) > 0) {
            extrapolateNpcPositionForCurrentMode(arg2);
            if (s1->kind != 4) {
                play3DSoundEvent(0, s1, s1->vel, 24.0f, 0.5f, 0, 0x2A, 0x7D, 0x5A);
            } else {
                play3DSoundEvent(0, s1, s1->vel, 12.0f, 0.5f, 0, 0x2A, 0x6E, 0x50);
            }
            if (getObjectDetailLevel(s1->obj) == 1 && D_main_bss_80130B39 == 0) {
                func_mission_overlay_800EFD6C(0x1F4);
            }
            if (dealDamageToNpc(s1->obj, *(u16 *)(a5 + 6)) <= 0) {
                unregisterAndFreeNpcSlot(s1->slot90, arg0);
                unregisterAndFreeNpcSlot(s1->slot92, arg0);
                unregisterAndFreeNpcSlot(s1->slot94, arg0);
                if (s1->slot96 != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s1->slot96, arg0);
                }
                popNpcSlotFromTail(D_main_bss_80139574, arg0);
                npcTieVariantHandleDestruction(s1, *(u16 *)a5, *(u16 *)(a5 + 2), *(u16 *)(a5 + 4));
                {
                    u8 *r = s1->def;
                    datItemSetObjectiveBooleanCount(*(s32 *)(r + 0x78), *(s32 *)(r + 0x7C), *(s32 *)(r + 0x70), *(s32 *)(r + 0x74), *(s32 *)(r + 0x80), *(s32 *)(s1->def + 0x84));
                }
                tallyMidDetailObject(arg0);
                setObjectFlagBit4(arg0);
            }
        }
        if (*(u16 *)a5 != 0xFFFF) {
            destroyNpcSlotByIndex(*(u16 *)a5);
        }
        return 1;
        }
    case 9:
        {
        u8 *a9 = arg2;
        switch (a9[0x18]) {
        case 0:
            if (*(s32 *)a9 == 0 && s1->kind == 2) {
                s1->bBA = 1;
                if (*(f32 *)(a9 + 0xC) == 0.0f) {
                    s1->bBB = 1;
                } else {
                    s1->bBB = 0;
                }
                s1->iA8 = 0;
                s1->fAC = *(f32 *)(a9 + 8);
                s1->sB8 = *(f32 *)(a9 + 4);
                s1->fB0 = *(f32 *)(a9 + 0x10);
                s1->fB4 = *(f32 *)(a9 + 0x14);
            }
            break;
        case 6:
            sp28.m.a = *(u16 *)a9;
            sp28.m.b = 0xFFFF;
            sp28.m.c = 7;
            sp28.m.d = *(u16 *)(a9 + 2);
            sp28.m.e = 0.0f;
            slotDispatcherIter(*(u16 *)(arg0 + 0x16), 5, &sp28);
            return 1;
        case 7:
            a9 = *(u8 **)a9;
            if (*a9 == '+') {
                f32 v = getActorCurrentValueByType(s1->obj);
                u8 *d = s1->def;
                initActorAsType4(s1->obj, (char *)a9 + 1, v, *(s32 *)(d + 0xB0), *(s32 *)(d + 0xAC));
                {
                    u8 *d2 = s1->def;
                    u16 f = (*(s32 *)(d2 + 0xA4) != 0) << 6;
                    if (*(s32 *)(d2 + 0xA8) != 0) {
                        f |= 0x80;
                    }
                    updateObjectFlags110(s1->obj, f, f ^ 0xFFFF);
                }
            }
            return 1;
        case 8:
            if (getNpcCurrentHealth(s1->obj) > 0) {
                u8 *b;
                s32 o;
                unregisterAndFreeNpcSlot(s1->slot92, arg0);
                b = D_main_bss_80139560;
                o = 0x2C;
                if (*(s32 *)a9 == 1) {
                    o = 0x2E;
                }
                s1->slot92 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                unregisterAndFreeNpcSlot(s1->slot94, arg0);
                o = 0x12;
                if (*(s32 *)a9 == 1) {
                    o = 0xE;
                }
                s1->slot94 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                if (s1->slot96 != 0xFFFF) {
                    unregisterAndFreeNpcSlot(s1->slot96, arg0);
                    if (*(s32 *)(s1->def + 0xB8) != 0) {
                        o = 0x18;
                        if (*(s32 *)a9 == 1) {
                            o = 0x1A;
                        }
                        s1->slot96 = popNpcSlotFromTail(*(u16 *)(o + b), arg0);
                    }
                }
                setObjectDetailLevel(s1->obj, *(s32 *)a9);
            }
            break;
        }
        }
        break;
    }
    return 1;
}












































extern s32 setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);
extern void initActorMotionParams(s32, f32, f32, f32, f32);
extern void initObjectAnimSubstruct(s32, f32, f32, f32, f32, void *, s32, f32, f32, s32);
extern void npcTieVariantTickEffects(void);
extern s32 D_main_bss_80137CE4;

void npcRadarDishInit(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 *def = *(u8 **)(npc + 0x34);

    npc[0x87] = 0;
    npc[0xBA] = 0;
    *(s16 *)(npc + 0x88) = 0;
    setNpcHealth(*(s32 *)(npc + 0x38), *(u8 **)(npc + 0x34) + 0x6C, *(u8 **)(npc + 0x34));
    initActorMotionParams(*(s32 *)(npc + 0x38), ((f32 *)(def + 0xC0))[D_main_bss_80137CE4], ((f32 *)(def + 0xC4))[D_main_bss_80137CE4], ((f32 *)(def + 0xC8))[D_main_bss_80137CE4], ((f32 *)(def + 0xCC))[D_main_bss_80137CE4]);
    setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(*(u8 **)(npc + 0x34) + 0xB4));
    initObjectAnimSubstruct(*(s32 *)(npc + 0x38), *(f32 *)(def + 0xD0), *(f32 *)(def + 0xD4), *(f32 *)(def + 0xD8), *(f32 *)(def + 0xDC), npcTieVariantTickEffects, 0, 10.0f, 15.0f, 0);
}

static u32 D_mission_overlay_800A7D04[] __attribute__((section(".rodata"))) = { 0x8FC2001C, 0x3C018005, 0xC420FE44 };
