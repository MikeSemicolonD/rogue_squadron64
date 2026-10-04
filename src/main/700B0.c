#include "common.h"

#include "main/04030.h"
#include "main/3F160.h"
#include "main/700B0.h"

INCLUDE_ASM("asm/nonmatchings/main/700B0", spawnDestructionDebris);

INCLUDE_ASM("asm/nonmatchings/main/700B0", npcDebris1Update);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strShockSph);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strShockBig);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strShockSml);

INCLUDE_ASM("asm/nonmatchings/main/700B0", orientedNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/700B0", multiEventTemplateNpcHandler);

INCLUDE_ASM("asm/nonmatchings/main/700B0", walkDatTreeAndAllocSubtypeBuffers);

INCLUDE_ASM("asm/nonmatchings/main/700B0", dispatchDatSubtypeByRandomIndex);

INCLUDE_ASM("asm/nonmatchings/main/700B0", walkDatTreeAndVisitChildren);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVYa4Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVYa2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strProbeDroid);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVCrsHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRTrPillar);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBThcapHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRBlkHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBTspHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBTrpHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRaptor);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strRebTransport);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strWrldDvstr);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strVHlsHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strWaveskimmer);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBPwrtranHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBMedHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBMe5Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strIRfcHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBGs2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBGs1Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strITrd2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm7Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm6Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm5newHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm4Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm3Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBKm1Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBTecHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strB20sbHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr8Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr7Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr6Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr5Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr4Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBCr2Hi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strBLrsp);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strImpShuttle);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strILndHi);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", strILtsrcHi);

INCLUDE_ASM("asm/nonmatchings/main/700B0", loadSfxAsset);

INCLUDE_ASM("asm/nonmatchings/main/700B0", composeRandomRotationMatrix);

INCLUDE_ASM("asm/nonmatchings/main/700B0", composeRandomRotationMatrixVariant);

void scaleVec3ByRandomRange(Vec3f arg0, f32 arg1, f32 arg2) {
    f32 temp_fv0;

    temp_fv0 = (((rand() % 4096) * (arg2 - arg1)) / 4095.0f) + arg1;
    arg0[0] *= temp_fv0;
    arg0[1] *= temp_fv0;
    arg0[2] *= temp_fv0;
}

INCLUDE_ASM("asm/nonmatchings/main/700B0", spawnDebris1Npc);

INCLUDE_ASM("asm/nonmatchings/main/700B0", spawnOrientedEffectIfBudgetOk);

INCLUDE_ASM("asm/nonmatchings/main/700B0", spawnOrientedEffectIfBudgetOkAlt);

INCLUDE_ASM("asm/nonmatchings/main/700B0", spawnOrientedNpc);

INCLUDE_ASM("asm/nonmatchings/main/700B0", gameStateByteGatedNpcHelper);

INCLUDE_ASM("asm/nonmatchings/main/700B0", spawnMultiEventNpcWrapper);

INCLUDE_ASM("asm/nonmatchings/main/700B0", spawnNpcChildForActivePlayerCell);

void sendSlotActionTwelve(u16 arg0) {
    if (arg0 != 0xFFFF) {
        slotDispatcherIter(arg0, 0xC, NULL);
    }
}

typedef struct DatTreeNode {
    u8 unk0;
    u8 pad1[3];
    u8 unk4;
    u8 pad5;
    u8 unk6;
    u8 pad7;
    struct DatTreeNode *unk8;
    u8 padC[0x2C];
} DatTreeNode;
extern u8 D_main_bss_8013A898;
extern u8 *D_main_bss_8013A89C;
void rs_free(void *);
void walkDatTreeAndCollectSubtypes(DatTreeNode *n) {
    s32 i;

    if (n->unk0 == 0xFF) {
        return;
    }
    if (n->unk0 & 0x80) {
        for (i = 0; i < n->unk4; i++) {
            if (n->unk8[i].unk6 != 0) {
                D_main_bss_8013A89C[D_main_bss_8013A898++] = n->unk8[i].unk6;
            }
        }
        rs_free(n->unk8);
        n->unk0 = 0xFF;
    } else if (n->unk6 != 0) {
        D_main_bss_8013A89C[D_main_bss_8013A898++] = n->unk6;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/700B0", walkDatTreeAndScaleLeafByFloat);

INCLUDE_ASM("asm/nonmatchings/main/700B0", fake_func_80072CE8);

INCLUDE_RODATA("asm/nonmatchings/main/700B0", D_main_8003CEE0);
