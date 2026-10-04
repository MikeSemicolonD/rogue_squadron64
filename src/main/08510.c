#include "common.h"
#include "common_types.h"

#include "main/08510.h"
#include "main/1EE30.h"

// Interim BSS externs
extern struct DisplayListBuffer *D_main_bss_801163B0;

INCLUDE_ASM("asm/nonmatchings/main/08510", registerSiCallback);

extern s32 D_main_bss_8011A8A4[];

void findAndZeroTableSlotMatching(s32 arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_main_bss_8011A8A4[i] == arg0) {
            D_main_bss_8011A8A4[i] = 0;
            return;
        }
    }
}

extern s32 D_main_bss_8011A8B0;

void clearFourWordTable(void) {
    s32 i;
    s32 *p;

    i = 3;
    p = &D_main_bss_8011A8B0;
    do {
        *p-- = 0;
    } while (--i >= 0);
}

#if 0
// I strongly suspect this file is compiled with O3, and that this function gets inlined
void heapFreeListInsert(struct DisplayListBuffer *arg0) {
    struct DisplayListBuffer *var_v1;

    if (arg0 != NULL) {
        var_v1 = arg0;
        if (arg0->next != NULL) {
            do {
                var_v1 = var_v1->next;
            } while (var_v1->next != NULL);
        }
        var_v1->next = D_main_bss_801163B0;
        if (D_main_bss_801163B0 != NULL) {
            D_main_bss_801163B0->prev = var_v1;
        }
        D_main_bss_801163B0 = arg0;
        D_main_bss_801163B0->prev = NULL;
    }
}
#else
void heapFreeListInsert(struct DisplayListBuffer *arg0) {
    struct DisplayListBuffer *var_v1;

    if (arg0 != NULL) {
        var_v1 = arg0;
        if (arg0->next != NULL) {
            do {
                var_v1 = var_v1->next;
            } while (var_v1->next != NULL);
        }
        var_v1->next = D_main_bss_801163B0;
        if (D_main_bss_801163B0 != NULL) {
            D_main_bss_801163B0->prev = var_v1;
        }
        D_main_bss_801163B0 = arg0;
        arg0->prev = NULL;
    }
}
#endif

INCLUDE_ASM("asm/nonmatchings/main/08510", heapWalker);

#if 0
s32 countDisplayListChunks(void) {
    s32 blah;
    struct DisplayListBuffer *var_v1;

    blah = 0;
    var_v1 = D_main_bss_801163B0;
    while (var_v1 != NULL) {
        var_v1 = var_v1->next;
        blah += sizeof(struct DisplayListBuffer);
    }
    return blah;
}
#else
s32 countDisplayListChunks(void) {
    s32 var_v0;
    struct DisplayListBuffer *var_v1;

    var_v1 = D_main_bss_801163B0;
    var_v0 = 0;
    if (var_v1 != NULL) {
        do {
            var_v1 = var_v1->next;
            var_v0 += 0x108;
        } while (var_v1 != NULL);
    }
    return var_v0;
}
#endif

#if 0
struct DisplayListBuffer *reclaimDisplayListChunk(void) {
    struct DisplayListBuffer *temp_a0;
    struct DisplayListBuffer *temp_v0;
    struct DisplayListBuffer *temp_v0_2;
    struct DisplayListBuffer *var_v1;

    temp_a0 = D_main_bss_801163B0;
    if (temp_a0 == NULL) {
        temp_v0 = findAndUnlinkSmallestEntry();
        heapFreeListInsert(temp_v0);
        // if (temp_v0 != NULL) {
        //     var_v1 = temp_v0;
        //     if (temp_v0->next != NULL) {
        //         do {
        //             var_v1 = var_v1->next;
        //         } while (var_v1->next != NULL);
        //     }
        //     var_v1->next = D_main_bss_801163B0;
        //     if (D_main_bss_801163B0 != NULL) {
        //         D_main_bss_801163B0->prev = var_v1;
        //     }
        //     D_main_bss_801163B0 = temp_v0;
        //     temp_v0->prev = NULL;
        // }
    }
    D_main_bss_801163B0 = D_main_bss_801163B0->next;
    if (D_main_bss_801163B0 != NULL) {
        D_main_bss_801163B0->prev = NULL;
    }
    return temp_a0;
}
#else
INCLUDE_ASM("asm/nonmatchings/main/08510", reclaimDisplayListChunk);
#endif

INCLUDE_ASM("asm/nonmatchings/main/08510", allocateDisplayListBuffer);

INCLUDE_ASM("asm/nonmatchings/main/08510", allocDLBlockToFillRectList);

INCLUDE_ASM("asm/nonmatchings/main/08510", allocDLBlockToListB);

INCLUDE_ASM("asm/nonmatchings/main/08510", allocDLBlockToListC);

INCLUDE_ASM("asm/nonmatchings/main/08510", allocDLBlockToListD);

INCLUDE_ASM("asm/nonmatchings/main/08510", drainMeshReleaseQueue);

INCLUDE_ASM("asm/nonmatchings/main/08510", enqueueMeshForDeferredRelease);

INCLUDE_ASM("asm/nonmatchings/main/08510", recordDeferredDrawRefVariant);

INCLUDE_ASM("asm/nonmatchings/main/08510", commitMeshDrawBatchRefs);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitAllocatedDLCommand);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitFaceDLCommands);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitFrameRdpInitDl);

extern s32 D_main_bss_801142C4;

s32 setActiveRenderListPtr(s32 arg0) {
    D_main_bss_801142C4 = arg0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/08510", emitColorFillRect);

extern s8 D_main_bss_8011A88C;
extern s16 D_main_bss_8011A880;
extern s16 D_main_bss_8011A882;
extern s16 D_main_bss_8011A884;
extern u16 D_main_bss_8011A886;
extern u8 D_main_bss_8011A888;
extern u8 D_main_bss_8011A889;
extern u8 D_main_bss_8011A88A;
extern s8 D_main_bss_8011A88D;
extern s8 D_main_bss_8011A88E;

s32 setScreenColorOverlay(s8 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4, u8 arg5, u8 arg6, u8 arg7) {
    D_main_bss_8011A88C = 1;
    D_main_bss_8011A880 = arg1;
    D_main_bss_8011A882 = arg2;
    D_main_bss_8011A884 = arg3;
    D_main_bss_8011A88D = arg0;
    D_main_bss_8011A88E = 0;
    D_main_bss_8011A888 = arg5;
    D_main_bss_8011A889 = arg6;
    D_main_bss_8011A88A = arg7;
    D_main_bss_8011A886 = arg4;
    return 1;
}

extern s8 D_main_bss_8011A88C;

s32 disableScreenColorOverlay(void) {
    D_main_bss_8011A88C = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/08510", frameStartReset);

s32 clearStructPair2C30(void *arg0) {
    (*(s32 *)((u8 *)(arg0) + 0x2C)) = 0;
    (*(s32 *)((u8 *)(arg0) + 0x30)) = 0;
    return 1;
}

s32 clearFrameReadyFlag();
s32 waitForPostSwapAck();
extern s8 D_main_bss_8011A89A;

s32 waitForPrevFrameDone(void) {
    waitForPostSwapAck();
    D_main_bss_8011A89A = 1;
    clearFrameReadyFlag();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/08510", beginFrameDLChunk);

INCLUDE_ASM("asm/nonmatchings/main/08510", initRenderStateArrays);

INCLUDE_ASM("asm/nonmatchings/main/08510", drawFrameProfilerBars);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitCombinerStateAndPatch);

extern s32 D_main_bss_8011A900;
extern s32 D_main_bss_8011A904;
extern s32 D_main_bss_80128ED8;

void computeFrameDeltaTime(void) {
    if (D_main_bss_8011A900 == -1) {
        D_main_bss_8011A904 = 0;
    } else {
        D_main_bss_8011A904 = D_main_bss_80128ED8 - D_main_bss_8011A900;
    }
    D_main_bss_8011A900 = D_main_bss_80128ED8;
}

INCLUDE_ASM("asm/nonmatchings/main/08510", timeSnapshotFiller);

INCLUDE_ASM("asm/nonmatchings/main/08510", bufferArbiterProducerScanWait);

INCLUDE_ASM("asm/nonmatchings/main/08510", submitGfxFrame);

INCLUDE_ASM("asm/nonmatchings/main/08510", recordDeferredDrawRefA);

INCLUDE_ASM("asm/nonmatchings/main/08510", recordDeferredDrawRefB);

INCLUDE_ASM("asm/nonmatchings/main/08510", recordDeferredDrawRefC);

INCLUDE_ASM("asm/nonmatchings/main/08510", recordDeferredDrawRefD);

INCLUDE_ASM("asm/nonmatchings/main/08510", reserveAndEmitDLEntry);

INCLUDE_ASM("asm/nonmatchings/main/08510", reserveAlignedDLSpace);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005A0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005A8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005B0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005B8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005C0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005C8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005D0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005D8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005E0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005E8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005F0);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_800005F8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_80000600);

INCLUDE_RODATA("asm/nonmatchings/main/08510", D_main_80000608);

INCLUDE_ASM("asm/nonmatchings/main/08510", heapFreeListDequeue);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitTexturedFaceGeometry);

INCLUDE_ASM("asm/nonmatchings/main/08510", transformLightByType);

INCLUDE_ASM("asm/nonmatchings/main/08510", appendRdpStateDl);

INCLUDE_ASM("asm/nonmatchings/main/08510", selectRenderPresetByIndex);

INCLUDE_ASM("asm/nonmatchings/main/08510", selectSecondaryPresetByIndex);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitMaterialTexturedDL);

INCLUDE_ASM("asm/nonmatchings/main/08510", emitMaterialTexturedDLAlt);

INCLUDE_ASM("asm/nonmatchings/main/08510", resetSceneLightsAndMaterials);

INCLUDE_ASM("asm/nonmatchings/main/08510", transformSceneLights);

INCLUDE_ASM("asm/nonmatchings/main/08510", bindFaceVerticesToCache);

INCLUDE_ASM("asm/nonmatchings/main/08510", renderLitTexturedMeshFaces);

INCLUDE_ASM("asm/nonmatchings/main/08510", submitSceneNodeRender);

INCLUDE_ASM("asm/nonmatchings/main/08510", renderFlatMeshFaceGroup);

INCLUDE_ASM("asm/nonmatchings/main/08510", renderUnlitMeshFaces);

INCLUDE_ASM("asm/nonmatchings/main/08510", resetVertexCacheSlot);

INCLUDE_ASM("asm/nonmatchings/main/08510", buildOrientedFaceGeometry);

INCLUDE_ASM("asm/nonmatchings/main/08510", renderLitMeshFaceGroup);

INCLUDE_ASM("asm/nonmatchings/main/08510", processMeshdef1ForLod);

INCLUDE_ASM("asm/nonmatchings/main/08510", processSceneNode);

INCLUDE_ASM("asm/nonmatchings/main/08510", traverseSceneGraphRecursive);

INCLUDE_ASM("asm/nonmatchings/main/08510", drawTextGlyphRect);

INCLUDE_ASM("asm/nonmatchings/main/08510", drawSubtitleText);

INCLUDE_ASM("asm/nonmatchings/main/08510", setupCameraMatrices);

extern s8 D_main_bss_8011A86C;
extern s8 D_main_bss_8011A86D;
extern s8 D_main_bss_8011A86E;

s32 setFrameLevelStateBytes(s8 arg0, s8 arg1, s8 arg2) {
    D_main_bss_8011A86C = arg0;
    D_main_bss_8011A86D = arg1;
    D_main_bss_8011A86E = arg2;
    return 1;
}

extern s8 D_main_bss_8011A870;

s32 setRenderStateFlagByteOne(s8 arg0) {
    D_main_bss_8011A870 = arg0;
    return 1;
}

extern s8 D_main_bss_8011A871;

s32 setRenderStateFlagByteTwo(s8 arg0) {
    D_main_bss_8011A871 = arg0;
    return 1;
}

extern s8 D_main_bss_8011A872;

s32 setRenderStateFlagByteThree(s8 arg0) {
    D_main_bss_8011A872 = arg0;
    return 1;
}

extern s8 D_main_bss_8011A875;
extern s8 D_main_bss_8011A874;
extern s8 D_main_bss_8011A873;
extern f32 D_main_bss_8011A878;
extern f32 D_main_bss_8011A87C;

s32 setViewStateBytesAndFadeScale(s8 arg0, s8 arg1, s8 arg2, f32 arg3, f32 arg4) {
    D_main_bss_8011A873 = arg0;
    D_main_bss_8011A874 = arg1;
    D_main_bss_8011A875 = arg2;
    D_main_bss_8011A878 = arg3;
    D_main_bss_8011A87C = (32.0f / arg4) + arg3;
    return 1;
}

extern s8 D_main_bss_8011A873;
extern s8 D_main_bss_8011A874;
extern s8 D_main_bss_8011A875;

s32 setViewStateTripletBytes(s8 arg0, s8 arg1, s8 arg2) {
    D_main_bss_8011A873 = arg0;
    D_main_bss_8011A874 = arg1;
    D_main_bss_8011A875 = arg2;
    return 1;
}

extern s8 D_main_bss_8011A898;

s32 setMissionLevelInitByte(s8 arg0) {
    D_main_bss_8011A898 = arg0;
    return 1;
}

s32 resetMaterialPoolWrapper(void) {
    resetMaterialPool();
    return 1;
}

extern f32 D_main_bss_8011A840;

void setRenderViewScaleFloat(f32 arg0) {
    D_main_bss_8011A840 = arg0;
}

INCLUDE_ASM("asm/nonmatchings/main/08510", buildAndRegisterDefaultMaterial);

INCLUDE_ASM("asm/nonmatchings/main/08510", advanceVideoFrame);

INCLUDE_ASM("asm/nonmatchings/main/08510", initVideoBootWrapper);

s32 destroyTextureLUTs();
s32 rs_free(struct D_main_bss_8011A444 *);
s32 selectAndApplyViMode();
extern struct D_main_bss_8011A444 *D_main_bss_8010E8A8;
extern struct D_main_bss_8011A444 *D_main_bss_8010E8AC;
extern struct D_main_bss_8011A444 *D_main_bss_801143AC;
extern struct D_main_bss_8011A444 *D_main_bss_801163B4;

s32 freeRenderSubsystemResources(void) {
    destroyTextureLUTs();
    rs_free(D_main_bss_8011A444);
    if (D_main_bss_801163B4 != NULL) {
        rs_free(D_main_bss_801163B4);
    }
    if (D_main_bss_801143AC != NULL) {
        rs_free(D_main_bss_801143AC);
    }
    rs_free(D_main_bss_8010E8A8);
    rs_free(D_main_bss_8010E8AC);
    selectAndApplyViMode();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/main/08510", fake_func_800186D8);

INCLUDE_RODATA("asm/nonmatchings/main/08510", junk_800007E8);
