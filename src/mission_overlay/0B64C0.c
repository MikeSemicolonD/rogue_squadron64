#include "common.h"
#include "common_types.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A5990);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A5998);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A59A0);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", playerAwingInit);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", resetEngineTrailQuads);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", acquireLockOnTarget);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", emitTexturedImpactEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", updateEngineThrustEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", playerAwingUpdate);

u16 acquireLockOnTarget(s32 arg0, s32 arg1, u16 arg2, s32 arg3, f32 arg4, f32 arg5, s32 arg6);

u16 findLockOnTarget(s32 arg0, s32 arg1, u16 arg2, s32 arg3, f32 arg4, f32 arg5) {
    return acquireLockOnTarget(arg0, arg1, arg2, arg3, arg4, arg5, 0);
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B64C0", fake_func_800B75C4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B64C0", D_mission_overlay_800A5B14);
