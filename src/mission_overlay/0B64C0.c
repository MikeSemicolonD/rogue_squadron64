#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A5990);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A5998);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A59A0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", playerAwingInit);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", resetEngineTrailQuads);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", acquireLockOnTarget);

typedef struct {
    s32 unk0;
    u8 pad4[0xB2];
    u16 unkB6;
    u8 padB8[0xB4];
    f32 unk16C;
    u8 pad170[0x2A0 - 0x170];
} ImpactObj;
typedef struct {
    u8 pad0[4];
    struct { u8 pad[4]; u16 unk4; } *unk4;
} ImpactAux;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
} ImpV3;
extern ImpactObj D_main_bss_80137DBC[];
extern u8 D_main_bss_80138D18[];
extern f32 D_mission_overlay_80109880[][3];
extern u8 D_mission_overlay_80109800[];
void lookupHmtTextureByName(s32, char *, s32, f32 *, s32, s32);
void accumulateVectorInObjectFrame(f32 *, f32 *, void *);
void quatFromAxisAngle(f32 *, f32 *, f32);
void rotateVec3ByQuat(f32 *, f32 *, f32 *);
void dispatchCueByCategory(s32, u16, f32 *, void *, s32, f32, f32);

void emitTexturedImpactEffect(u8 *arg0, s32 arg1, ImpV3 *arg2) {
    f32 m[4][3];
    ImpV3 sp50;
    f32 sp60[4];
    ImpactObj *o;
    s32 bit;
    f32 v;
    char *name;

    o = &D_main_bss_80137DBC[*(s32 *)arg0];
    if (arg1 & 1) {
        lookupHmtTextureByName(o->unk0, "b", 0, m[0], 0, 0);
    } else {
        lookupHmtTextureByName(o->unk0, "a", 0, m[0], 0, 0);
    }
    if (((ImpactAux *)(D_main_bss_80138D18 + *(s32 *)arg0 * 0x144))->unk4->unk4 == 3) {
        bit = arg1 & 1;
        accumulateVectorInObjectFrame(m[0], D_mission_overlay_80109880[bit], o);
        if (bit != 0) {
            v = *(f32 *)(arg0 + 0x44);
            if (v > 0.0f) {
                if (v < 18.0f) {
                    quatFromAxisAngle(sp60, m[2], -v * 0.8f);
                    sp50 = *(ImpV3 *)m[1];
                    rotateVec3ByQuat(sp60, (f32 *)&sp50, m[1]);
                }
            }
        } else {
            v = *(f32 *)(arg0 + 0x40);
            if (v < 0.0f) {
                if (v > -18.0f) {
                    quatFromAxisAngle(sp60, m[2], -v * 0.8f);
                    sp50 = *(ImpV3 *)m[1];
                    rotateVec3ByQuat(sp60, (f32 *)&sp50, m[1]);
                }
            }
        }
    }
    dispatchCueByCategory(0, o->unkB6, m[0], D_mission_overlay_80109800, 1, 15.0f, o->unk16C);
    *arg2 = *(ImpV3 *)m[0];
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", updateEngineThrustEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", playerAwingUpdate);

u16 acquireLockOnTarget(s32 arg0, s32 arg1, u16 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6);

u16 findLockOnTarget(s32 arg0, s32 arg1, u16 arg2, s32 arg3, f32 arg4, f32 arg5) {
    return acquireLockOnTarget(arg0, arg1, arg2, arg3, arg4, arg5, 0);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", fake_func_800B75C4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A5B14);
