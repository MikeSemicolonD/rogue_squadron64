#include "common.h"
#include "common_types.h"

#include "level_objectives.h"
#include "mission_overlay/0F3E90.h"

typedef struct { s32 unk0; u8 pad[0x20]; } ModelAnimSlot24;
extern ModelAnimSlot24 D_mission_overlay_8010C4A0[];

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", resolveScriptedNameTokenList);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", computeRandomizedOrientationFrame);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", updateNpcEffectIntensity);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0F3E90", D_mission_overlay_800A8BB8);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", executeActorType1Effect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", executeActorType2Effect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", executeActorType3Effect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", initActorAsType4);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", buildSineWaveEffectGeometryA);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", buildSineWaveEffectGeometryB);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", renderNpcAnchoredProceduralEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", spawnAndUpdateEffectActors);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", executeActorType4Effect);

void clearObjectField112(void *arg0) {
    (*(s8 *)((u8 *)(arg0) + 0x112)) = 0;
}

typedef struct { s32 x, y, z; } T1V3;
struct T1Src {
    u8 pad0[0x1C];
    s32 unk1C;
    u8 *unk20;
    f32 unk24;
    s32 unk28;
    f32 *unk2C;
};

struct T1State {
    s32 unk0;
    u8 *unk4;
    u8 *unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    f32 unk1C;
    s32 unk20;
    struct T1Src *unk24;
    s32 unk28;
    f32 unk2C;
    f32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 pad4C[4];
    f32 unk50;
    u8 pad54[0xC];
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
    f32 unk70;
    f32 unk74;
    f32 unk78;
    s32 unk7C;
    f32 unk80;
    f32 unk84;
    s32 unk88;
    u8 pad8C[4];
    s32 unk90;
    u8 pad94[4];
    s32 unk98;
    s32 unk9C;
    s32 unkA0;
    u8 padA4[4];
    f32 unkA8;
    u8 padAC[4];
    s32 unkB0;
    s32 unkB4;
    s32 unkB8;
    u8 quat[0x10];
    f32 unkCC;
    s32 unkD0;
    s32 unkD4;
    s32 unkD8;
    f32 unkDC;
    f32 unkE0;
    u8 padE4[4];
    s32 unkE8;
    u8 padEC[8];
    s32 unkF4;
    s32 unkF8;
    u8 unkFC;
    u8 padFD;
    u8 unkFE;
    u8 padFF[5];
    s32 unk104;
};

extern void *getNpcContextField8(u16);
extern void setupActorAnchorTransformType1(void *, void *, void *, void *, f32);
extern void quatFromCardinalAxis(f32 *, u8, f32);

s32 initActorAsType1(u8 *arg0, struct T1Src *arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    u8 *obj = arg0;
    struct T1State *s = (struct T1State *)(obj + 8);
    s32 *ctx;
    u8 *end;

    obj[0x112] = 1;
    s->unk24 = arg1;
    s->unk28 = 0;
    s->unk0 = arg1->unk1C;
    s->unk4 = arg1->unk20;
    end = arg1->unk20 + arg1->unk1C * 0xC;
    s->unk14 = 0;
    s->unk10 = 0;
    s->unkC = 0;
    s->unk34 = 0;
    s->unk20 = 0;
    s->unk18 = 0;
    s->unk1C = 1.0f;
    s->unk48 = arg2;
    s->unk50 = arg2;
    s->unk8 = end;
    s->unk2C = arg2 / arg1->unk24;
    s->unk104 = 0;
    s->unkFC = 0;
    s->unkFE = 0;
    s->unk30 = arg3 * s->unk2C;
    if (s->unk30 > 1.0f) {
        s->unk30 = 0.0f;
    }
    if (arg1->unk28 != 0) {
        s->unk40 = *arg1->unk2C;
    } else {
        s->unk40 = 10.0f;
    }
    s->unk3C = 0;
    s->unk44 = arg6;
    s->unk38 = 0;
    ctx = (s32 *)getNpcContextField8(*(u16 *)(arg0 + 0x198));
    setupActorAnchorTransformType1(s, (u8 *)arg1 + 0x10, ctx, &s->unkC, s->unk30);
    s->unkA8 = 0.0f;
    s->unk60 = 0;
    s->unk64 = 0;
    s->unk68 = 0;
    s->unk6C = 0;
    s->unk88 = 0;
    s->unk98 = 0;
    s->unk9C = 0;
    s->unkA0 = 0;
    s->unk90 = 0;
    s->unk70 = 2.0f;
    s->unk74 = 0.05f;
    s->unk78 = 0.022f;
    s->unk80 = 0.5f;
    s->unk84 = 0.5f;
    quatFromCardinalAxis((f32 *)s->quat, 2, s->unkA8);
    s->unkB0 = 0;
    s->unkB4 = 0;
    s->unkB8 = 0;
    s->unk7C = 0;
    s->unkDC = arg4;
    s->unkCC = 360.0f;
    s->unkE0 = arg5;
    *(T1V3 *)&s->unkD0 = *(T1V3 *)ctx;
    s->unkE8 = 0;
    s->unkF4 = 0;
    s->unkF8 = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", initActorAsType1WithAnchor);

s32 setType1ActorVelocity(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    u8 *p;
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 1) {
        p = (u8 *)arg0 + 8;
        *(f32 *)(p + 0x7C) = arg2;
        *(f32 *)(p + 0xCC) = arg3;
        *(f32 *)(p + 0x60) = arg1 * 0.25f;
        return 1;
    }
    return 0;
}

f32 setType1ActorField40(void *arg0, f32 arg1) {
    f32 var_fv0;

    var_fv0 = 0.0f;
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 1) {
        var_fv0 = (*(f32 *)((u8 *)(arg0) + 0x40));
        (*(f32 *)((u8 *)(arg0) + 0x40)) = arg1;
    }
    return var_fv0;
}

typedef struct { f32 x, y, z; } Vec3Struct_2;
extern void *getNpcContextField8(u16);

s32 initActorAsType2(void *arg0, s32 arg1, f32 arg2, f32 arg3) {
    u8 *p = (u8 *)arg0 + 8;
    void *ctx;

    *(u8 *)((u8 *)arg0 + 0x112) = 2;
    ctx = getNpcContextField8(*(u16 *)((u8 *)arg0 + 0x198));
    *(Vec3Struct_2 *)((u8 *)arg0 + 8) = *(Vec3Struct_2 *)((u8 *)ctx + 0xC);
    *(f32 *)(p + 0x18) = 0.0f;
    *(f32 *)(p + 0xC) = *(f32 *)(p + 0x10) = arg3;
    *(f32 *)(p + 0x14) = arg2;
    *(s32 *)(p + 0x30) = arg1;
    *(u8 *)(p + 0x34) = *(u8 *)(p + 0x35) = 0;
    *(f32 *)(p + 0x2C) = *(f32 *)(p + 0x1C) = *(f32 *)(p + 0x20) = *(f32 *)(p + 0x24) = *(f32 *)(p + 0x28) = *(f32 *)(p + 0x18);
    return 1;
}

s32 setType2ActorVelocity(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    u8 *p;
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 2) {
        p = (u8 *)arg0 + 8;
        *(s32 *)(p + 0x18) = 0;
        *(f32 *)(p + 0x24) = arg1;
        *(f32 *)(p + 0x28) = arg2;
        *(f32 *)(p + 0x1C) = arg3;
        *(f32 *)(p + 0x20) = arg4;
        *(f32 *)(p + 0x2C) = arg5;
        return 1;
    }
    return 0;
}

typedef struct { f32 x, y, z; } Vec3Struct_3;
extern void *getNpcContextField8(u16);

s32 initActorAsType3(void *arg0, s32 arg1, f32 arg2, f32 arg3) {
    u8 *p = (u8 *)arg0 + 8;
    void *ctx;

    *(u8 *)((u8 *)arg0 + 0x112) = 3;
    ctx = getNpcContextField8(*(u16 *)((u8 *)arg0 + 0x198));
    *(Vec3Struct_3 *)((u8 *)arg0 + 8) = *(Vec3Struct_3 *)((u8 *)ctx + 0xC);
    *(f32 *)(p + 0x18) = 0.0f;
    *(f32 *)(p + 0xC) = *(f32 *)(p + 0x10) = arg3;
    *(f32 *)(p + 0x14) = arg2;
    *(s32 *)(p + 0x30) = arg1;
    *(u8 *)(p + 0x34) = *(u8 *)(p + 0x35) = 0;
    *(f32 *)(p + 0x2C) = *(f32 *)(p + 0x1C) = *(f32 *)(p + 0x20) = *(f32 *)(p + 0x24) = *(f32 *)(p + 0x28) = *(f32 *)(p + 0x18);
    return 1;
}

s32 setType3ActorParams(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    u8 *p;
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 3) {
        p = (u8 *)arg0 + 8;
        *(s32 *)(p + 0x18) = 0;
        *(f32 *)(p + 0x24) = arg1;
        *(f32 *)(p + 0x28) = arg2;
        *(f32 *)(p + 0x1C) = arg3;
        *(f32 *)(p + 0x20) = arg4;
        *(f32 *)(p + 0x2C) = arg5;
        return 1;
    }
    return 0;
}

extern void executeActorType1Effect(void *, f32);
extern void executeActorType2Effect(void *, f32);
extern void executeActorType3Effect(void *, f32);
extern void executeActorType4Effect(void *, f32);

void dispatchEffectByActorType(void *arg0, f32 arg1) {
    switch (*(u8 *)((u8 *)arg0 + 0x112)) {
    case 1:
        executeActorType1Effect(arg0, arg1);
        break;
    case 2:
        executeActorType2Effect(arg0, arg1);
        break;
    case 3:
        executeActorType3Effect(arg0, arg1);
        break;
    case 4:
        executeActorType4Effect(arg0, arg1);
        break;
    }
}

s32 setType1ActorParams(void *arg0, f32 arg1, s8 arg2, s8 arg3, s8 arg4, s32 arg5) {
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 1) {
        (*(f32 *)((u8 *)(arg0) + 0x10C)) = arg1;
        (*(s8 *)((u8 *)(arg0) + 0x104)) = arg2;
        (*(s8 *)((u8 *)(arg0) + 0x105)) = arg3;
        (*(s8 *)((u8 *)(arg0) + 0x106)) = arg4;
        (*(s32 *)((u8 *)(arg0) + 0x108)) = arg5;
        return 1;
    }
    return 0;
}

void updateObjectFlags110(void *arg0, s32 arg1, s32 arg2) {
    (*(u16 *)((u8 *)(arg0) + 0x110)) = (u16) (((*(u16 *)((u8 *)(arg0) + 0x110)) | arg1) & ~arg2);
}

void resetType1FxFields(void *arg0) {
    if ((*(u8 *)((u8 *)(arg0) + 0x112)) == 1) {
        (*(s32 *)((u8 *)(arg0) + 0xFC)) = 0;
        (*(f32 *)((u8 *)(arg0) + 0x100)) = 1.0f;
    }
}

void updateType1AnimRamp(void *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4) {
    u8 *p;
    u8 type = *(u8 *)((u8 *)arg0 + 0x112);
    f32 delta;

    if (type == 1) {
        p = (u8 *)arg0 + 8;
        if (arg4 == type) {
            *(f32 *)(p + 0x50) = *(f32 *)(p + 0x48) * arg1;
        } else {
            *(f32 *)(p + 0x50) = arg1;
        }
        if (*(f32 *)(p + 0x50) < arg2) {
            *(f32 *)(p + 0x50) = arg2;
        }
        delta = *(f32 *)(p + 0x50) - *(f32 *)(p + 0x48);
        *(f32 *)(p + 0x4C) = *(f32 *)(p + 0x48);
        *(f32 *)(p + 0x54) = delta;
        if (delta != 0.0f) {
            *(f32 *)(p + 0x58) = 0.0f;
            if (arg3 > 0.0f) {
                *(f32 *)(p + 0x5C) = 1.0f / arg3;
                return;
            }
            *(f32 *)(p + 0x48) = *(f32 *)(p + 0x50);
            *(f32 *)(p + 0x2C) = *(f32 *)(p + 0x48) / *(f32 *)(*(u8 **)(p + 0x24) + 0x24);
        }
    }
}

f32 getActorCurrentValueByType(void *arg0) {
    u8 temp_v1;

    temp_v1 = (*(u8 *)((u8 *)(arg0) + 0x112));
    switch (temp_v1) {                              /* irregular */
    case 1:
        return (*(f32 *)((u8 *)(arg0) + 0x50));
    case 4:
        return (*(f32 *)((u8 *)(arg0) + 0x28));
    default:
        return 0.0f;
    }
}

#include "main/1D000.h"
#include "main/192E0.h"
#include "main/3F160.h"
#include "main/5A750.h"

f32 sinf(f32);

void syncType1ActorFrameToAnchorIfZeroGate(u8 *arg0, Vec3f arg1) {
    Mat4x3 sp10;
    Mat4x3 sp40;
    Vec3f sp70;
    f32 ang;
    f32 s;
    u8 *s1;

    if (arg0[0x112] == 1) {
        s1 = arg0 + 8;
        if (*(f32 *)(s1 + 0xE8) == 0.0f) {
            mat34CrossRowsAndCopyPos(sp10, getNpcContextField8(*(u16 *)(arg0 + 0x198)), 1.0f);
            mat3x3InverseInto(sp40, sp10);
            rotateVec3ByMat3x3(sp40, arg1, sp70);
            if (sp70[0] != 0.0f || sp70[1] != 0.0f) {
                normalize_vector(sp70);
                ang = atan2Approx(sp70[0], sp70[1]);
                s = sinf(2.0f * ang);
                *(f32 *)(s1 + 0xE4) = ang * 57.29578f;
                s = s * 45.0f;
                *(f32 *)(s1 + 0xE8) = vec3Length(arg1);
                *(f32 *)(s1 + 0xEC) = 0.0f;
                *(f32 *)(s1 + 0xF0) = 0.5f;
                *(f32 *)(s1 + 0x14) += s;
            }
        }
    }
}

typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    s16 unk6;
    s32 unk8;
} SpawnSlotMsg;

extern u16 findNpcInScaledBoxRegionExcludingPair(void *, u16, f32, u16, u16, s32);
extern s32 slotDispatcherIter(u16, s32, void *);
extern void *getNpcContextField8(u16);
extern u16 D_main_bss_8013957C;

s32 spawnNpcAnchoredEffectSlot(void *arg0, f32 arg1, s32 arg2) {
    SpawnSlotMsg msg;
    u16 id;
    u16 slot;
    s32 ret;

    ret = 0;
    slot = findNpcInScaledBoxRegionExcludingPair(getNpcContextField8(*(u16 *)((u8 *)arg0 + 0x198)), *(u16 *)((u8 *)arg0 + 0x198), arg1, 0xFFFF, D_main_bss_8013957C, 0);
    if (slot != 0xFFFF) {
        id = *(u16 *)((u8 *)arg0 + 0x198);
        slotDispatcherIter(slot, 6, &id);
        if (arg2 != 0) {
            msg.unk0 = 0xFFFF;
            msg.unk2 = 0xFFFF;
            msg.unk4 = 7;
            msg.unk6 = arg2;
            msg.unk8 = 0;
            slotDispatcherIter(slot, 5, &msg);
        }
        ret = 1;
    }
    return ret;
}

extern s32 rs_strcmp(u8 *, u8 *);
extern u8 *rs_strcpy(u8 *, u8 *);
extern void *load_asset(char *);
extern void model_animation_offset_convert(void *);

void *load_model_animation(char *name) {
    s32 i;
    s32 freeSlot;

    i = 0;
    freeSlot = -1;
    for (; i < 16; i++) {
        if (D_mission_overlay_8010C4A0[i].unk0 != 0) {
            if (rs_strcmp(D_mission_overlay_8010C4A0[i].pad, (u8 *)name) == 0) {
                return (void *)D_mission_overlay_8010C4A0[i].unk0;
            }
        } else {
            freeSlot = i;
        }
    }
    if (freeSlot == -1) {
        return NULL;
    }
    rs_strcpy(D_mission_overlay_8010C4A0[freeSlot].pad, (u8 *)name);
    D_mission_overlay_8010C4A0[freeSlot].unk0 = (s32)load_asset(name);
    model_animation_offset_convert((void *)D_mission_overlay_8010C4A0[freeSlot].unk0);
    return (void *)D_mission_overlay_8010C4A0[freeSlot].unk0;
}

extern void resetModelAnimSlotTable(void);

s32 reset_model_animations(void) {
    s32 i;

    resetModelAnimSlotTable();
    for (i = 15; i >= 0; i--) {
        D_mission_overlay_8010C4A0[i].unk0 = 0;
    }
    return 1;
}

extern void rs_free(void *);

s32 reset_and_free_model_animations(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (*(void **)&D_mission_overlay_8010C4A0[i].unk0 != NULL) {
            rs_free(*(void **)&D_mission_overlay_8010C4A0[i].unk0);
        }
        D_mission_overlay_8010C4A0[i].unk0 = 0;
    }
    resetModelAnimSlotTable();
    return 1;
}

#if 0
// The major mismatch with this is that the original code accesses a bunch of information
// via negative offsets from the unk0D element. This is strange, I don't think you can tickle
// GCC into doing this through "normal" code.
s32 checkObjectiveHandles(f32 arg0) {
    s32 var_s2;
    s32 temp_a0;
    s32 temp_a1;
    struct simpleCheckHandle *var_s1;

    for (var_s2 = 0; var_s2 < 0x30; var_s2++) {
        var_s1 = &simpleCheckHandles[var_s2];
        if (var_s1->active != 1) continue;

        switch (var_s1->checkType) {
            case 0:
                temp_a0 = var_s1->checks.boolcount.objectiveBooleanIndex;
                if ((temp_a0 != 0) && (gObjectiveBooleans[temp_a0 - 1] != var_s1->checks.boolcount.objectiveBooleanValue)) continue;

                temp_a0 = var_s1->checks.boolcount.objectiveCountIndex;
                if (temp_a0 == 0) break;
                temp_a1 = var_s1->checks.boolcount.unk07;
                if ((temp_a1 == 0) && (gObjectiveCounts[temp_a0 - 1] < var_s1->objectiveCountValue)) continue;

                if (var_s1->checks.boolcount.unk07 != 1) break;
                if (gObjectiveCounts[var_s1->checks.boolcount.unk07 - 1] >= var_s1->objectiveCountValue) continue;
                break;
            case 1:
                var_s1->checks.timer.timer -= arg0;
                if (var_s1->checks.timer.timer > 0.0f) continue;
                break;
            default:
                continue;
        }
        var_s1->active = 0;
        if (var_s1->unk0D == 0) {
            var_s1->handle();
        }
    }
    return 1;

//         if (simpleCheckHandles[var_s2].checkType != 0) {
//             if (simpleCheckHandles[var_s2].checkType != 1) continue;
//             simpleCheckHandles[var_s2].checks.timer.timer -= arg0;
//             if (simpleCheckHandles[var_s2].checks.timer.timer <= 0.0f) {
//                 simpleCheckHandles[var_s2].active = 0;
//                 if (simpleCheckHandles[var_s2].unk0D == 0) {
//                     simpleCheckHandles[var_s2].handle();
//                 }
//             }
//         } else {
//             temp_a0 = simpleCheckHandles[var_s2].checks.boolcount.objectiveBooleanIndex;
//             if ((temp_a0 == 0) ||
//                 (gObjectiveBooleans[temp_a0 - 1] == simpleCheckHandles[var_s2].checks.boolcount.objectiveBooleanValue)) {
//                     temp_a0 = simpleCheckHandles[var_s2].checks.boolcount.objectiveCountIndex;
//                     if (temp_a0 == 0) {
//                         temp_a1 = simpleCheckHandles[var_s2].checks.boolcount.unk07;
//                         if((temp_a1 != 0) || (gObjectiveCounts[temp_a0 - 1] >= simpleCheckHandles[var_s2].objectiveCountValue)) {
//                             if (temp_a1 == 1)
//                         }
//                     } else {
//                         simpleCheckHandles[var_s2].active = 0;
//                         if (simpleCheckHandles[var_s2].unk0D == 0) {
//                             simpleCheckHandles[var_s2].handle();
//                         }
//                     }
//                 }
//         }
//     }
//     return 1;
//     var_s2 = 0;
//     var_s1 = simpleCheckHandles;
//     var_s0 = &simpleCheckHandles->unk0D;
//     do {
//         temp_a1 = var_s0->unk1;
//         if (temp_a1 == 1) {
//             temp_v0 = var_s0->unk-1;
//             if (temp_v0 != 0) {
//                 if (temp_v0 != temp_a1) {
//                     var_s2 += 1;
//                 } else {
//                     temp_fv0 = var_s0->unk-9 - arg0;
//                     var_s0->unk-9 = temp_fv0;
//                     if (!(temp_fv0 > 0.0f)) {
//                         goto block_14;
//                     }
//                     goto block_16;
//                 }
//             } else {
//                 temp_v0_2 = (bitwise u8) var_s0->unk-9;
//                 if ((temp_v0_2 == 0) || (gObjectiveBooleans[temp_v0_2].unk-1 == var_s0->unk-8)) {
//                     temp_v0_3 = var_s0->unk-7;
//                     if (temp_v0_3 != 0) {
//                         temp_a0 = var_s0->unk-6;
//                         if ((temp_a0 != 0) || ((s32) gObjectiveCounts[temp_v0_3 - 1] >= var_s0->unk-5)) {
//                             if (temp_a0 == temp_a1) {
//                                 if ((s32) gObjectiveCounts[var_s0->unk-7 - 1] < var_s0->unk-5) {
//                                     goto block_14;
//                                 }
//                             } else {
//                                 goto block_14;
//                             }
//                         }
//                     } else {
// block_14:
//                         var_s0->unk1 = 0U;
//                         if (var_s0->unk0 == 0) {
//                             var_s1->handle();
//                         }
//                     }
//                 }
//                 goto block_16;
//             }
//         } else {
// block_16:
//             var_s2 += 1;
//         }
//         var_s0 += 0x10;
//         var_s1 += 0x10;
//     } while (var_s2 < 0x30);
//     return 1;
}
#else
INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", checkObjectiveHandles);
#endif

s32 initializeObjectiveHandles(void) {
    s32 var_v1;

    for (var_v1 = 0x2F; var_v1 >= 0; var_v1--) {
        simpleCheckHandles[var_v1].active = 0;
    }
    return 1;
}

s32 addBooleanCountHandle(void (*handle)(), u8 booleanIndex, u8 booleanValue, u8 checkIndex, u32 checkCount, u8 arg5) {
    s32 var_v1;

    for (var_v1 = 0; var_v1 < 0x30; var_v1++) {
        if (simpleCheckHandles[var_v1].active == 0) break;
    }

    if (var_v1 == 0x30) {
        return 0;
    } else { 
        simpleCheckHandles[var_v1].active = 1;
        simpleCheckHandles[var_v1].unk0D = 0;
        simpleCheckHandles[var_v1].checkType = 0;
        simpleCheckHandles[var_v1].handle = handle;
        simpleCheckHandles[var_v1].checks.boolcount.objectiveBooleanIndex = booleanIndex;
        simpleCheckHandles[var_v1].checks.boolcount.objectiveBooleanValue = booleanValue;
        simpleCheckHandles[var_v1].checks.boolcount.objectiveCountIndex = checkIndex;
        simpleCheckHandles[var_v1].objectiveCountValue = checkCount;
        simpleCheckHandles[var_v1].checks.boolcount.unk07 = arg5;
        return 1;
    }
}

s32 addTimerHandle(void (*handle)(), f32 timerValue) {
    s32 var_v1;

    for (var_v1 = 0; var_v1 < 0x30; var_v1++) {
        if (simpleCheckHandles[var_v1].active == 0) break;
    }

    if (var_v1 == 0x30) {
        return 0;
    } else {
        simpleCheckHandles[var_v1].active = 1;
        simpleCheckHandles[var_v1].unk0D = 0;
        simpleCheckHandles[var_v1].checkType = 1;
        simpleCheckHandles[var_v1].handle = handle;
        simpleCheckHandles[var_v1].checks.timer.timer = timerValue;
        return 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F3E90", fake_func_800FA248);

static u32 D_mission_overlay_800A8F68[] __attribute__((section(".rodata"))) = { 0xAFBF002C, 0xAFBE0028 };
