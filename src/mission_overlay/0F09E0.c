#include "common.h"
#include "common_types.h"

#include "main/1D000.h"
#include "mission_overlay/0F09E0.h"
#include "mission_stats.h"

extern s32 D_main_bss_80137CE4;

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F09E0", func_mission_overlay_800EFDE0);

typedef struct {
    u8 pad0[0x1A];
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
    u8 unk20;
    u8 unk21;
} PendingChildNpc;

s32 findActiveNpcInSlotChain(u16, s32);
void *getNpcContextByIndex(u16);
s32 unregisterAndFreeNpcSlot(u16, void *);

static inline void clearPendingChildNpcInline(PendingChildNpc *p) {
    if (p->unk20 == 1 && p->unk1A != 0xFFFF) {
        if ((findActiveNpcInSlotChain(p->unk1C, 0) & 0xFFFF) != 0xFFFF) {
            unregisterAndFreeNpcSlot(p->unk1E, getNpcContextByIndex(p->unk1E));
        }
        p->unk1A = 0xFFFF;
        p->unk1E = 0xFFFF;
        p->unk20 = 0;
    }
}

s32 isPendingChildNpcActive(u8 *obj) {
    PendingChildNpc *p = (PendingChildNpc *)(obj + 0x114);
    u16 idx;

    if (p->unk21 == 0) {
        return 0;
    }
    if (p->unk20 != 0) {
        if (p->unk1C == 0xFFFF) {
            return 0;
        }
        if (p->unk1E == 0xFFFF) {
            return 0;
        }
        if (p->unk1A == 0xFFFF) {
            return 0;
        }
        idx = findActiveNpcInSlotChain(p->unk1C, 0) & 0xFFFF;
        if (idx == 0xFFFF) {
            clearPendingChildNpcInline(p);
            return 0;
        }
        if (*(u16 *)((u8 *)getNpcContextByIndex(idx) + 0x14) & 0x10) {
            clearPendingChildNpcInline(p);
            return 0;
        }
        return 1;
    }
    return 0;
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} LosChild;
void *getNpcContextField8(u16);
f32 vec3Dot(f32 *, f32 *);
f32 vec3Length(f32 *);

s32 validateActorTargetLOS(u8 *obj) {
    PendingChildNpc *p = (PendingChildNpc *)(obj + 0x114);
    f32 v[3];
    f32 *a;
    f32 *b;
    f32 d2;
    f32 dot;
    f32 len;
    f32 c;
    f32 r;
    f32 th;
    u16 idx;

    if (p->unk21 == 0) {
        return 0;
    }
    if (p->unk20 == 0) {
        return 0;
    }
    if (p->unk1C == 0xFFFF) {
        return 0;
    }
    if (p->unk1E == 0xFFFF) {
        return 0;
    }
    if (p->unk1A == 0xFFFF) {
        return 0;
    }
    idx = findActiveNpcInSlotChain(p->unk1C, 0) & 0xFFFF;
    if (idx == 0xFFFF || (*(u16 *)((u8 *)getNpcContextByIndex(idx) + 0x14) & 0x10)) {
        clearPendingChildNpcInline(p);
        return 0;
    }
    a = getNpcContextField8(*(u16 *)(obj + 0x198));
    b = getNpcContextField8(idx);
    r = ((LosChild *)p)->unkC;
    th = ((LosChild *)p)->unk8;
    v[0] = b[0] - a[0];
    v[1] = b[1] - a[1];
    v[2] = b[2] - a[2];
    d2 = v[0] * v[0] + v[2] * v[2];
    if (!(r * r < d2)) {
        dot = vec3Dot(a + 3, v);
        len = vec3Length(a + 3);
        c = dot / (len * vec3Length(v));
        if (d2 < 1.0f) {
            if (0.0f <= c) {
                return 1;
            }
        }
        if (!(c < th)) {
            return 1;
        }
    }
    return 0;
}

s32 computeActorAnchorDeltaAfterLOS(u8 *obj) {
    PendingChildNpc *p = (PendingChildNpc *)(obj + 0x114);
    f32 v[3];
    f32 *a;
    f32 *b;
    f32 d2;
    f32 dot;
    f32 len;
    f32 c;
    f32 r;
    f32 th;
    u16 idx;

    if (p->unk21 == 0) {
        return 0;
    }
    if (p->unk20 == 0) {
        return 0;
    }
    if (p->unk1C == 0xFFFF) {
        return 0;
    }
    if (p->unk1E == 0xFFFF) {
        return 0;
    }
    if (p->unk1A == 0xFFFF) {
        return 0;
    }
    idx = findActiveNpcInSlotChain(p->unk1C, 0) & 0xFFFF;
    if (idx == 0xFFFF || (*(u16 *)((u8 *)getNpcContextByIndex(idx) + 0x14) & 0x10)) {
        clearPendingChildNpcInline(p);
        return 0;
    }
    a = getNpcContextField8(*(u16 *)(obj + 0x198));
    b = getNpcContextField8(idx);
    r = ((LosChild *)p)->unk4;
    th = *(f32 *)(obj + 0x114);
    v[0] = b[0] - a[0];
    v[1] = b[1] - a[1];
    v[2] = b[2] - a[2];
    d2 = v[0] * v[0] + v[2] * v[2];
    if (!(r * r < d2)) {
        dot = vec3Dot(a + 3, v);
        len = vec3Length(a + 3);
        c = dot / (len * vec3Length(v));
        if (d2 < 1.0f) {
            if (0.0f <= c) {
                return 1;
            }
        }
        if (!(c < th)) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F09E0", evaluateTargetTrackingVisibility);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F09E0", tickObjectAnimSubstruct);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F09E0", resolveNpcAttachmentPos);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F09E0", quicksortFloatKeysWithValues);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F09E0", gatherAndSortNearbyNpcViewPoints);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F09E0", acquireNpcTargetsInAimCone);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F09E0", tickProgressChannel);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F09E0", raycastTerrainAndNpcs);

typedef struct { f32 x, y, z; } Vec3Cp2;

void *getNpcContextField8(u16);
void parseDatItemCommon(void *, void *);
void datItemSetObjectiveBooleanCount(s32, s32, s32, s32, s32, s32);

s32 initActorRenderDescriptorIfUninit(u8 *arg0, u8 arg1, u8 *arg2, u8 arg3, s32 *arg4) {
    s32 *p;
    s32 *q = arg4;
    Vec3Cp2 *npc;

    if (arg0[0x1A7] == 0) {
        *(u16 *)(arg2 + 6) = 0xFFFF;
        if (arg1 == 0 && !(*(u32 *)(arg0 + 0x1A4) & 0xFF00FF00)) {
            if (arg3 == 1) {
                npc = getNpcContextField8(*(u16 *)(arg0 + 0x198));
                *(Vec3Cp2 *)(arg2 + 0x10) = *npc;
            }
            parseDatItemCommon(arg2, arg2 + 0x10);
        }
    } else {
        if (*(u16 *)(arg2 + 6) == *(u16 *)(arg0 + 0x198)) {
            *(u16 *)(arg2 + 6) = 0xFFFF;
        }
        if (arg1 == 0 && !(*(u32 *)(arg0 + 0x1A4) & 0xFF00FF00)) {
            p = *(s32 **)(arg0 + 0x19C);
            if (p != NULL) {
                *p = *p - 1;
            }
        } else {
            p = *(s32 **)(arg0 + 0x19C);
            if (p != NULL) {
                *p = *p - 1;
            }
            p = *(s32 **)(arg0 + 0x1A0);
            if (p != NULL) {
                *p = *p + 1;
            }
        }
    }
    if (arg0[0x1A5] != 0 && arg4 != NULL) {
        datItemSetObjectiveBooleanCount(q[0], q[1], q[2], q[3], q[4], q[5]);
    }
    return 1;
}

void *getNpcContextField8(u16);
void computeBillboardFacingVector(void *, void *);

typedef struct { f32 x, y, z; } Vec3Cp;

void initActorRenderDescriptorWithNpcVelocity(u8 *arg0, u8 *arg1) {
    Vec3Cp sp10;
    Vec3Cp *npc;

    if (arg0[0x1A7] == 0) {
        npc = getNpcContextField8(*(u16 *)(arg0 + 0x198));
        computeBillboardFacingVector(npc, &sp10);
        *(Vec3Cp *)(arg1 + 0x10) = *npc;
        *(Vec3Cp *)(arg1 + 0x1C) = sp10;
    }
}

s32 setNpcHealth(u8* npc, s32* health, u8* record) {
    u8* rec = record;

    if (npc[0x1A7] == 0) {
        *(s32**)(npc + 0x190) = health;
        if (*(s32*)(record + 0x54) == (s32)0x80000000) {
            *(s32*)(record + 0x54) = health[D_main_bss_80137CE4];
        }
        *(s32*)(npc + 0x194) = *(s32*)(rec + 0x54);
    } else {
        *(s32*)(npc + 0x190) = health[D_main_bss_80137CE4];
        *(s32*)(npc + 0x194) = health[D_main_bss_80137CE4];
    }
    return health[D_main_bss_80137CE4];
}

s32 getNpcCurrentHealth(u8* npc) {
    if (npc[0x1A7] != 0) {
        return *(s32*)(npc + 0x190);
    }
    return (*(s32**)(npc + 0x190))[D_main_bss_80137CE4];
}

void dealDamageToNpc(u8* npc, s32 damage) {
    if (npc[0x1A7] == 0) {
        (*(s32**)(npc + 0x190))[D_main_bss_80137CE4] -= damage;
    } else {
        *(s32*)(npc + 0x190) -= damage;
    }
}

s32 getNpcMissingHealth(u8* npc) {
    if (npc[0x1A7] != 0) {
        return *(s32*)(npc + 0x194) - *(s32*)(npc + 0x190);
    }
    return *(s32*)(npc + 0x194) - (*(s32**)(npc + 0x190))[D_main_bss_80137CE4];
}

f32 getNpcHealthPercentage(u8* npc) {
    if (npc[0x1A7] != 0) {
        return ((f32)*(s32*)(npc + 0x190) / (f32)*(s32*)(npc + 0x194)) * 100.0f;
    }
    return ((f32)(*(s32**)(npc + 0x190))[D_main_bss_80137CE4] / (f32)*(s32*)(npc + 0x194)) * 100.0f;
}

s32 isVectorWithinConeAndRange(Mat4x3 arg0, f32 arg1, f32 arg2, Vec3f arg3) {
    Vec3f sp10;
    f32 temp_fs1_2;
    f32 temp_fs2;
    s32 var_v0;

    sp10[0] = arg3[0] - arg0[0][0];
    sp10[1] = arg3[1] - arg0[0][1];
    sp10[2] = arg3[2] - arg0[0][2];
    temp_fs2 = ((sp10[0] * sp10[0]) + (sp10[2] * sp10[2]));
    if ((arg1 * arg1) < temp_fs2) {
        return 0;
    }
    temp_fs1_2 = vec3Dot(arg0[1], sp10) / (vec3Length(arg0[1]) * vec3Length(sp10));
    // I hate that this matches :(
    if (!(temp_fs2 < 1.0f) || (var_v0 = 1, !(temp_fs1_2 >= 0.0f))) {
        if (!(temp_fs1_2 < arg2)) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
    }
    return var_v0;
}

s32 isVectorInConeWriteDistance(Mat4x3 arg0, f32 arg1, f32 arg2, Vec3f arg3, f32 *arg4) {
    Vec3f sp10;

    sp10[0] = arg3[0] - arg0[0][0];
    sp10[1] = arg3[1] - arg0[0][1];
    sp10[2] = arg3[2] - arg0[0][2];
    if (!((arg1 * arg1) < ((sp10[0] * sp10[0]) + (sp10[2] * sp10[2])))) {
        if (!((vec3Dot(arg0[1], sp10) / (vec3Length(arg0[1]) * vec3Length(sp10))) < arg2)) {
            *arg4 = vec3Length(sp10);
            return 1;
        }
    }
    return 0;
}

s32 computeTurnAxisTowardTarget(Mat4x3 arg0, f32 arg1, f32 arg2, Vec3f arg3, UNIDENTIFIED_TYPE *arg4, struct Struct3f *arg5) {
    Vec3f sp10;
    struct Struct3f sp20;
    f32 *temp_s1;
    f32 temp_fa0;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_ft0;
    f32 temp_fv0;

    sp10[0] = arg3[0] - arg0[0][0];
    sp10[1] = arg3[1] - arg0[0][1];
    sp10[2] = arg3[2] - arg0[0][2];
    if (((arg1 * arg1) < ((sp10[0] * sp10[0]) + (sp10[2] * sp10[2])))) return 0;

    normalize_vector(sp10);
    temp_fa0 = vec3Dot(arg0[1], sp10) / (vec3Length(arg0[1]) * vec3Length(sp10));
    if (temp_fa0 < arg2) return 0;

    constMinusSinfApprox(temp_fa0);
    vec3Cross(&sp20, arg0[1], sp10);
    if (vec3Length(&sp20) != 0.0f) {
        normalize_vector(&sp20);
    }
    *arg5 = sp20;
    return 1;
}

#if 0
// The register allocation surrounding the struct copy is a little incorrect, which is annoying because
// that works just fine in `computeTurnAxisTowardTarget`
f32 computeTurnVectorTowardTarget(Mat4x3 arg0, Vec3f arg1, struct Struct3f *arg2, f32 *arg3) {
    Vec3f sp10;
    struct Struct3f sp20;
    f32 temp_fs0;

    sp10[0] = arg1[0] - arg0[0][0];
    sp10[1] = arg1[1] - arg0[0][1];
    sp10[2] = arg1[2] - arg0[0][2];
    temp_fs0 = constMinusSinfApprox(vec3Dot(arg0[1], sp10) / (vec3Length(arg0[1]) * vec3Length(sp10))) * 57.29578f;
    vec3Cross(&sp20, arg0[1], sp10);
    if (vec3Length(&sp20) != 0.0f) {
        normalize_vector(&sp20);
    }
    *arg2 = sp20;
    return temp_fs0;
}
#else
INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F09E0", computeTurnVectorTowardTarget);
#endif

#if 0
// The register allocation surrounding the struct copy is a little incorrect, which is annoying because
// that works just fine in `computeTurnAxisTowardTarget`
// https://decomp.me/scratch/D6Lx1
f32 computeTurnVectorAndDistanceToTarget(Mat4x3 arg0, Vec3f arg1, struct Struct3f *arg2, f32 *arg3) {
    Vec3f sp10;
    struct Struct3f sp20;
    f32 temp_fs0;

    sp10[0] = arg1[0] - arg0[0][0];
    sp10[1] = arg1[1] - arg0[0][1];
    sp10[2] = arg1[2] - arg0[0][2];
    *arg3 = vec3Length(sp10);
    temp_fs0 = constMinusSinfApprox(vec3Dot(arg0[1], sp10) / (vec3Length(arg0[1]) * vec3Length(sp10))) * 57.29578f;
    vec3Cross(&sp20, arg0[1], sp10);
    if (vec3Length(&sp20) != 0.0f) {
        normalize_vector(&sp20);
    }
    *arg2 = sp20;
    return temp_fs0;
}
#else
INCLUDE_ASM("asm/nonmatchings/mission_overlay/0F09E0", computeTurnVectorAndDistanceToTarget);
#endif

typedef struct {
    u8 active;
    u8 pad1[7];
    Mat4x3 matrix;
    u8 pad38[0x144 - 0x38];
} TriggerVolume;

extern TriggerVolume D_main_bss_80138D18[];

u8 transformVec3ToNpcLocalWithScale(Mat4x3, s32, f32 *, f32, f32 *);

s32 isPointInsideTriggerVolume(f32 *point, f32 scale) {
    s32 i;
    f32 local[2];

    TriggerVolume *tv;

    for (i = 0; i < 1; i++) {
        tv = &D_main_bss_80138D18[i];
        if (tv->active != 0 && transformVec3ToNpcLocalWithScale(tv->matrix, 0, point, scale, local)) {
            return 1;
        }
    }
    return 0;
}

void *getNpcContextByIndex(u16);

s16 getNpcDetailLevelByIndex(u16 index) {
    u8 *ctx = getNpcContextByIndex(index);
    u8 *npc = *(u8 **)(ctx + 0x10);

    if (npc != NULL) {
        return *(s16 *)(npc + 0x19A);
    }
    return 3 - (ctx[0x15] >> 6);
}

void *getNpcContextByIndex(u16);

void setObjectDetailLevel(void *arg0, s16 arg1) {
    void *temp_v0;

    (*(s16 *)((u8 *)(arg0) + 0x19A)) = arg1;
    temp_v0 = getNpcContextByIndex((*(u16 *)((u8 *)(arg0) + 0x198)));
    (*(u16 *)((u8 *)(temp_v0) + 0x14)) = (u16) (((*(u16 *)((u8 *)(temp_v0) + 0x14)) & 0xFF3F) | ((3 - arg1) << 6));
}

s16 getObjectDetailLevel(void *arg0) {
    return (*(s16 *)((u8 *)(arg0) + 0x19A));
}

f32 cosf(f32);
s32 rand(void);

void initActorMotionParams(u8 *actor, f32 angleA, f32 speedA, f32 angleB, f32 speedB) {
    *(f32 *)(actor + 0x114) = cosf(angleA * 0.017453292f);
    *(f32 *)(actor + 0x118) = speedA * 0.25f;
    *(f32 *)(actor + 0x11C) = cosf(angleB * 0.017453292f);
    *(f32 *)(actor + 0x120) = speedB * 0.25f;
    *(f32 *)(actor + 0x124) = (s16)((s16)rand() % 30) * 0.033333335f;
    actor[0x136] = 0;
    actor[0x137] = 0;
    actor[0x135] = 1;
}

s32 transformMeshPartIntoWorld(s32, s32);
s32 zmemcpy(s32, s32, s32);

s32 getObjectMeshTransformOrLocal(void *arg0, s32 arg1) {
    void *temp_s0;

    temp_s0 = getNpcContextByIndex(findActiveNpcInSlotChain((*(u16 *)((u8 *)(arg0) + 0x130)), 0) & 0xFFFF);
    if ((arg1 == 0) || ((*(s32 *)((u8 *)(temp_s0) + 0xC)) == 0)) {
        return (*(s32 *)((u8 *)(temp_s0) + 8));
    }
    zmemcpy(arg1, (*(s32 *)((u8 *)(temp_s0) + 8)), 0x30);
    transformMeshPartIntoWorld((*(s32 *)((u8 *)(temp_s0) + 0xC)), arg1);
    return arg1;
}

s32 findActiveNpcInSlotChain(u16, s32);

s32 getObjectNpcTypeId(void *arg0) {
    return findActiveNpcInSlotChain((*(u16 *)((u8 *)(arg0) + 0x130)), 0) & 0xFFFF;
}

s32 unregisterAndFreeNpcSlot(u16, void *);

void clearPendingChildNpc(s32 arg0) {
    void *temp_s0;

    temp_s0 = arg0 + 0x114;
    if (((*(u8 *)((u8 *)(temp_s0) + 0x20)) == 1) && ((*(u16 *)((u8 *)(temp_s0) + 0x1A)) != 0xFFFF)) {
        if ((findActiveNpcInSlotChain((*(u16 *)((u8 *)(temp_s0) + 0x1C)), 0) & 0xFFFF) != 0xFFFF) {
            unregisterAndFreeNpcSlot((*(u16 *)((u8 *)(temp_s0) + 0x1E)), getNpcContextByIndex((*(u16 *)((u8 *)(temp_s0) + 0x1E))));
        }
        (*(u16 *)((u8 *)(temp_s0) + 0x1A)) = 0xFFFFU;
        (*(u16 *)((u8 *)(temp_s0) + 0x1E)) = 0xFFFFU;
        (*(u8 *)((u8 *)(temp_s0) + 0x20)) = 0U;
    }
}

void setObjectFlagBit4(void *arg0) {
    (*(u16 *)((u8 *)(arg0) + 0x14)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x14)) | 0x10);
}

void clearObjectFlagBit4(void *arg0) {
    (*(u16 *)((u8 *)(arg0) + 0x14)) = (u16) ((*(u16 *)((u8 *)(arg0) + 0x14)) & 0xFFEF);
}

void computeAnchorRelativePositionByDistanceRatio(Vec3f arg0, Mat4x3 arg1, f32 arg2, Vec3f arg3) {
    Vec3f sp10;
    f32 temp_fv0;
    f32 var_ft0;

    sp10[0] = arg1[0][0] - arg0[0];
    sp10[1] = arg1[0][1] - arg0[1];
    sp10[2] = arg1[0][2] - arg0[2];
    temp_fv0 = vec3Length(sp10);
    if (arg2 > 0.0f) {
        var_ft0 = temp_fv0 / arg2;
    } else {
        var_ft0 = 0.0f;
    }
    arg3[0] = (f32) (arg1[0][0] + (arg1[3][0] * var_ft0));
    arg3[1] = (f32) (arg1[0][1] + (arg1[3][1] * var_ft0));
    arg3[2] = (f32) (arg1[0][2] + (arg1[3][2] * var_ft0));
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s32 unkC;
    s32 unk10;
    f32 unk14;
    s32 unk18;
    s16 unk1C;
    s16 unk1E;
    s32 unk20;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    u8 unk29;
    s8 unk2A;
    u8 unk2B;
} ObjectAnimSubstruct;

void initObjectAnimSubstruct(u8 *obj, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 useAlt, f32 arg7, f32 arg8, f32 arg9) {
    ObjectAnimSubstruct *sub;
    f32 angle;

    if (useAlt == 0) {
        sub = (ObjectAnimSubstruct *)(obj + 0x138);
    } else {
        sub = (ObjectAnimSubstruct *)(obj + 0x164);
    }
    angle = arg9;
    sub->unk0 = arg1;
    sub->unk4 = arg2;
    sub->unk1C = arg3;
    if (sub->unk1C == 0) {
        sub->unk1C++;
    }
    sub->unk8 = arg4;
    sub->unk18 = arg5;
    sub->unkC = 0;
    sub->unk2B = 1;
    sub->unk1E = 0;
    sub->unk10 = 0;
    sub->unk28 = 0;
    sub->unk14 = 1.0f;
    sub->unk24 = arg8 * 100.0f;
    sub->unk26 = arg7 * 100.0f;
    if (angle > 45.0f) {
        angle = 45.0f;
    }
    sub->unk29 = 0;
    sub->unk20 = 0;
    sub->unk2A = angle * 2.8222222f;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    s32 unkC;
    s32 unk10;
    f32 unk14;
    s32 unk18;
    s16 unk1C;
    s16 unk1E;
    s32 unk20;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    u8 unk29;
    s8 unk2A;
    u8 unk2B;
} AnimSubstruct;

void initAnimSubstructFromParams(AnimSubstruct *sub, s32 arg1, s32 arg2, f32 arg3, f32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    sub->unk0 = arg1;
    sub->unk4 = arg2;
    sub->unk1C = arg3;
    if (sub->unk1C == 0) {
        sub->unk1C++;
    }
    sub->unk8 = arg4;
    sub->unk18 = arg5;
    sub->unkC = 0;
    sub->unk2B = 1;
    sub->unk1E = 0;
    sub->unk10 = 0;
    sub->unk28 = 0;
    sub->unk14 = 1.0f;
    sub->unk24 = arg7 * 100.0f;
    sub->unk26 = arg6 * 100.0f;
    if (arg8 > 45.0f) {
        arg8 = 45.0f;
    }
    sub->unk29 = 0;
    sub->unk20 = 0;
    sub->unk2A = arg8 * 2.8222222f;
}

void tickObjectAnimSubstruct(u8 *obj, u8 *sub, f32 arg2, f32 arg3);

void applyToObjectSubstructByFlag(u8 *obj, f32 arg1, f32 arg2, s32 useAlt) {
    u8 *sub;

    if (useAlt == 0) {
        sub = obj + 0x138;
    } else {
        sub = obj + 0x164;
    }
    tickObjectAnimSubstruct(obj, sub, arg1, arg2);
}

void setObjectSubstructF10IfReady(u8 *obj, f32 value, s32 useAlt) {
    u8 *sub;

    if (useAlt == 0) {
        sub = obj + 0x138;
    } else {
        sub = obj + 0x164;
    }
    if (*(s32 *)(sub + 0x18) != 0 && sub[0x2B] != 0) {
        *(f32 *)(sub + 0x10) = value;
    }
}

void setAnimSubstructValueIfActive(void *arg0, f32 arg1) {
    if (((*(s32 *)((u8 *)(arg0) + 0x18)) != 0) && ((*(u8 *)((u8 *)(arg0) + 0x2B)) != 0)) {
        (*(f32 *)((u8 *)(arg0) + 0x10)) = arg1;
    }
}

void vec3Cross(f32 *, f32 *, f32 *);
s32 rand();
extern f32 D_mission_overlay_8010C470;
extern f32 D_mission_overlay_8010C474;

void generatePerpEmitDirectionWithJitter(s8 *arg0, f32 *arg1, s32 arg2) {
    u8 flag = arg2;
    f32 sp10[4];
    f32 sp20[4];
    f32 sp30[4];
    f32 sp40[4];
    f32 *a;
    f32 *b;
    f32 f0;

    if (arg0[0x162] != 0) {
        a = arg1 + 6;
        b = arg1 + 3;
        vec3Cross(sp10, a, b);
        if (!flag) {
            f0 = (f32)arg0[0x162] * 0.35433072f;
            D_mission_overlay_8010C470 = ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / f0);
            D_mission_overlay_8010C474 = ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / f0);
        }
        quatFromAxisAngle(sp30, sp10, D_mission_overlay_8010C470);
        quatFromAxisAngle(sp40, a, D_mission_overlay_8010C474);
        quatMultiply(sp40, sp30, sp20);
        rotateVec3ByQuat(sp20, b, b);
        rotateVec3ByQuat(sp20, a, a);
    }
}

s32 tickProgressChannel(s32, f32 *, s32, s32);

s32 stepAndTickProgressChannel(s32 arg0, u8 *arg1, f32 arg2, s32 arg3, s32 arg4) {
    f32 sp[12];

    zmemcpy((s32)sp, (s32)arg1, 0x30);
    sp[0] += sp[3] * arg2;
    sp[1] += sp[4] * arg2;
    sp[2] += sp[5] * arg2;
    return tickProgressChannel(arg0, sp, arg3, arg4) & 0xFF;
}

f32 getEffectIntensity(void *arg0) {
    return (*(f32 *)((u8 *)(arg0) + 0x14C));
}

s32 setEffectIntensity(void *arg0, s32 arg1) {
    (*(s32 *)((u8 *)(arg0) + 0x14C)) = arg1;
    return 1;
}

typedef struct {
    s16 type;
    u8 pad2[0x16];
    f32 value;
    u8 mode;
} CueSlotMessage;

f32 getEffectIntensity(void *);
s32 dispatchCueByCategory(s32, u16, s32, s32, u8, f32, f32);
s32 slotDispatcherIter(u16, s32, void *);

u16 triggerCueWithSlotEffect(u8 *npc, s32 arg1, s32 arg2, s32 arg3, u8 arg4, f32 arg5, f32 arg6) {
    CueSlotMessage msg;
    s32 id;

    id = dispatchCueByCategory(arg1, *(u16 *)(npc + 0x198), arg2, arg3, arg4, arg5, getEffectIntensity(npc));
    if (arg6 >= 0.0f) {
        msg.value = arg6;
        if (arg6 == 0.0f) {
            msg.mode = 2;
        } else {
            msg.mode = 1;
        }
        msg.type = 2;
        slotDispatcherIter(id, 10, &msg);
    }
    return id;
}

s32 copyPipeDelimitedField(u8 *s, s32 field, u8 *out) {
    s32 count = 0;

    s++;
    while (*s != 0) {
        if (*s == '|') {
            s++;
            count++;
        } else if (s[1] == 0) {
            count++;
        }
        if (count == field) {
            while (*s != 0 && *s != '|') {
                *out++ = *s++;
            }
            *out = 0;
            if (*s != 0) {
                return field + 1;
            }
            return 0;
        }
        s++;
    }
    return 0;
}

s32 copyRandomPipeDelimitedField(u8 *arg0, u8 *arg1) {
    s32 field;
    s32 count;
    s32 ret;
    u8 *s;
    u8 *o;
    u8 c;

    if (arg0[0] != 0) {
        field = (s16)rand() % *arg0++;
        o = arg1;
        s = arg0;
        c = *s;
        count = 0;
        while (c != 0) {
            if (c == '|') {
                s++;
                count++;
            } else if (s[1] == 0) {
                count++;
            }
            if (count == field) {
                while (*s != 0 && *s != 0x7C) {
                    *o++ = *s++;
                }
                *o = 0;
                ret = 0;
                if (*s != 0) {
                    ret = field + 1;
                }
                goto done;
            }
            s++;
            c = *s;
        }
        ret = 0;
done:
        return ret;
    }
    *arg1 = 0;
    return 0;
}

s32 returnZero_800F3258(void) {
    return 0;
}

void tallyMidDetailObject(u8 *obj) {
    if ((obj[0x15] >> 6) == 2) {
        missionStats.enemies_destroyed++;
    }
}
