#include "common.h"

INCLUDE_ASM("asm/nonmatchings/main/7B470", allocateNpcMeshVertexBuffer);

INCLUDE_ASM("asm/nonmatchings/main/7B470", transformMeshVerticesForNpc);

INCLUDE_ASM("asm/nonmatchings/main/7B470", npcDeformingMeshUpdate);

INCLUDE_ASM("asm/nonmatchings/main/7B470", npcShieldUpdate);

INCLUDE_ASM("asm/nonmatchings/main/7B470", heavyAttachedAudioEmitterNpcHandler);

extern void *D_main_bss_8013A970;
static const char D_main_8003D624[12] = "shield_PAL\0000";
void loadShieldPalette(void) {
    D_main_bss_8013A970 = load_asset((char *)D_main_8003D624);
}

INCLUDE_ASM("asm/nonmatchings/main/7B470", fake_func_8007C298);
