#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main/6A6F0", collideSegmentAgainstObjectNodes);

INCLUDE_ASM("asm/nonmatchings/main/6A6F0", findSegmentObjectSphereHit);

INCLUDE_ASM("asm/nonmatchings/main/6A6F0", projectPointOntoObjectSphereHit);

void transformVec3ByMat34(void *, void *, void *);
void transformMeshPartIntoWorld(unsigned char **arg0, void *arg1) {
    transformVec3ByMat34((unsigned char *)arg0 + 0x28, *arg0 + 0x4C, arg1);
}

INCLUDE_ASM("asm/nonmatchings/main/6A6F0", fake_func_8006ACA4);

INCLUDE_RODATA("asm/nonmatchings/main/6A6F0", D_main_8003C8F8);
