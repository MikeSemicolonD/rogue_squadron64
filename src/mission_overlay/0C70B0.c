#include "common.h"
#include "common_types.h"

typedef struct {
    s32 name;
    u8 type;
    u8 pad5[3];
} HangarDisplayItem;

extern HangarDisplayItem *D_mission_overlay_8010A420[];
extern f32 D_mission_overlay_8010A204[][4];
extern s32 findNamedEntryInCurrentObject(s32);
extern void findHudElementExtremes(void *, s32, s32);

typedef struct {
    u8 pad0[0x1C8];
    f32 timers[6];
} HangarDisplayState;

void initHangarDisplayItemTimers(u8 *obj, u8 idx) {
    u8 i;
    s32 e;

    if (D_mission_overlay_8010A420[idx] != NULL) {
        obj[0x1E0] = 0;
        for (i = 0; D_mission_overlay_8010A420[idx][i].name != 0; i++) {
            e = findNamedEntryInCurrentObject(D_mission_overlay_8010A420[idx][i].name);
            if (e != 0) {
                findHudElementExtremes(obj + (obj[0x1E0] * 0x48 + 0x18), e, 1);
                ((HangarDisplayState *)obj)->timers[obj[0x1E0]] = D_mission_overlay_8010A204[D_mission_overlay_8010A420[idx][obj[0x1E0]].type][0];
                *(obj[0x1E0] + obj + 0x1E1) = 0;
                obj[0x1E0]++;
            }
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A6880);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A688C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A6894);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A689C);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68A4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68AC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68B4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68BC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68C4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68CC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68D4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68DC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68E4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68EC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68F4);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A68FC);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A6904);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C70B0", tickHangarDisplayItemAnimations);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C70B0", hangarVehicleDisplayNpcHandler);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C70B0", applyNpcPositionDrift);

extern f32 D_mission_overlay_8010A1F8;
extern f32 D_mission_overlay_8010A1FC;

void getConfigFloatPair(f32 *arg0, f32 *arg1) {
    *arg0 = D_mission_overlay_8010A1F8;
    *arg1 = D_mission_overlay_8010A1FC;
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0C70B0", accumulateVectorInObjectFrame);

extern f32 D_mission_overlay_8010A200;

f32 getConfigFloatValue(void) {
    return D_mission_overlay_8010A200;
}

s32 findModelChildNodeByName(s32, s32);
extern s32 *D_mission_overlay_8010C090;

s32 findNamedEntryInCurrentObject(s32 arg0) {
    return findModelChildNodeByName(*D_mission_overlay_8010C090, arg0);
}

typedef struct {
    s32 m[12];
} ObjMatrix3x4;

void copyCurrentObjectMatrix(ObjMatrix3x4 *out) {
    *out = *(ObjMatrix3x4 *)(*D_mission_overlay_8010C090 + 0x28);
}

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0C70B0", D_mission_overlay_800A6958);
