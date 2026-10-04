#include "common.h"
#include "common_types.h"
#include "dat.h"
#include "levels.h"
#include "cinematic_overlay/1381D0.h"
#include "main/192E0.h"
#include "main/42AF0.h"
#include "main/66FB0.h"

struct cutsceneIdMapEntry {
    u16 unk0;
    u16 unk2;
};

/* Data Variable, uncomment when Data matching is possible
struct cutsceneIdMapEntry gCutsceneIdMappingTable[] = {...};
*/

// Interim `extern` definitions for Data variable. Remove these when Data is matchable

extern struct cutsceneIdMapEntry gCutsceneIdMappingTable[];

/* BSS Variables, uncomment when BSS matching is possible

struct D_cinematic_overlay_800B0D00_type D_cinematic_overlay_800B0D00[0x40];
UNIDENTIFIED_TYPE *D_cinematic_overlay_800B1900;
struct cuts_file_constant *D_cinematic_overlay_800B1904;
Vec3f *D_cinematic_overlay_800B1A08;
*/

// Interim `extern` definitions for BSS variables. Remove these when BSS matching is possible.
extern struct D_cinematic_overlay_800B0D00_type D_cinematic_overlay_800B0D00[0x40];
extern UNIDENTIFIED_TYPE *D_cinematic_overlay_800B1900;
extern struct cuts_file_constant *D_cinematic_overlay_800B1904;
extern Vec3f *D_cinematic_overlay_800B1A08;

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5130);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", strCutsceneTypeSpecial);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", strCutsceneTypeExtro);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", strCutsceneTypeIntro);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", cinematicLoopBody);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", load_cutscene);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", strCinPlCraftsVwing);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A518C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A519C);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", cinematicSlotUpdate);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", setupCutsceneLevel);

typedef struct {
    s32 unk0;
    void *unk4;
    void *unk8;
    void *unkC;
    void *unk10;
    void *unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    u8 pad24[0x24];
    void *unk48;
} CineDispatch;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
} CineBlock;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    void *unk10;
    s32 unk14;
} CineNode;

typedef struct {
    s32 unk0;
    void *unk4;
} CinePair;

extern u8 D_cinematic_overlay_800B09C0[];
extern CinePair D_cinematic_overlay_800B09D0;
extern u8 D_cinematic_overlay_800B09E0[];
extern CineDispatch D_cinematic_overlay_800B0A00;
extern CineBlock D_cinematic_overlay_800B0A50;
extern CineNode D_cinematic_overlay_800B0AB0;
void clearStructPair2C30(void *);
void extractOrthonormalFrameFromStruct(void *, void *);
void setVec3At0x24(void *, s32, s32, s32);

void initCinematicDispatchSlots(s32 *arg0, void *arg1) {
    u32 i;

    i = 0;
    *arg0 = 0;
    do {
        *(u32 *)(D_cinematic_overlay_800B09C0 + (i & 0xFF) * 4) = 0;
        i++;
    } while ((i & 0xFF) < 4);
    D_cinematic_overlay_800B0A00.unk0 = (s32)arg0;
    D_cinematic_overlay_800B0A00.unk4 = D_cinematic_overlay_800B09C0;
    D_cinematic_overlay_800B0A00.unk8 = D_cinematic_overlay_800B09C0 + 4;
    D_cinematic_overlay_800B0A00.unkC = D_cinematic_overlay_800B09C0 + 8;
    D_cinematic_overlay_800B0A00.unk10 = D_cinematic_overlay_800B09C0 + 0xC;
    D_cinematic_overlay_800B0A00.unk14 = &D_cinematic_overlay_800B09D0;
    D_cinematic_overlay_800B0A00.unk48 = &D_cinematic_overlay_800B0A50;
    D_cinematic_overlay_800B09D0.unk0 = 0;
    D_cinematic_overlay_800B09D0.unk4 = D_cinematic_overlay_800B09E0;
    extractOrthonormalFrameFromStruct(&D_cinematic_overlay_800B0A00.unk18, arg1);
    D_cinematic_overlay_800B0AB0.unkC = 0;
    D_cinematic_overlay_800B0AB0.unk8 = 0;
    D_cinematic_overlay_800B0AB0.unk4 = 0;
    D_cinematic_overlay_800B0AB0.unk0 = 0;
    D_cinematic_overlay_800B0AB0.unk14 = 0;
    D_cinematic_overlay_800B0AB0.unk10 = &D_cinematic_overlay_800B0A50;
    setVec3At0x24((u8 *)&D_cinematic_overlay_800B0AB0 + 0x1C, D_cinematic_overlay_800B0A00.unk18, D_cinematic_overlay_800B0A00.unk1C, D_cinematic_overlay_800B0A00.unk20);
    D_cinematic_overlay_800B0A50.unk8 = 0;
    D_cinematic_overlay_800B0A50.unk4 = 0;
    D_cinematic_overlay_800B0A50.unk0 = 0;
    D_cinematic_overlay_800B0A50.unkC = 0x49000000;
    D_cinematic_overlay_800B0A50.unk10 = 0;
    D_cinematic_overlay_800B0A50.unk18 = 0;
    D_cinematic_overlay_800B0A50.unk14 = 0;
    D_cinematic_overlay_800B0A50.unk20 = 0;
    clearStructPair2C30(&D_cinematic_overlay_800B0A50);
}

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", cinematicSlotBatchDispatch);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", slotEffectHandlerDispatch);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", cutscenePopulateSlotsFromLevelLists);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A52B4);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", cinematicSlotDispatcher);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", spawnCutsceneObjectsFromList);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", cutsceneDispatchSlotsByFlag);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A52F0);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A52FC);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_800A5300);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", strCinRedbox1);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_800A5308);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_800A530C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5310);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5320);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", spawnCutsceneEffectsAndCues);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", initCutsceneAudioChannels);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", initCutsceneScene);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", initSceneForMission);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", emit3DSoundsForActiveNpcs);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", updatePositionalAudioSource);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A54A8);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A54B4);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", applyCutsceneSlotMaterialOverrides);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", tickCutsceneActionSlots);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A54CC);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", applyNamedEffectParameterDefault);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A54F4);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5500);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A550C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5518);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5524);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5530);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A553C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5548);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5554);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5560);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A556C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5570);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5574);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5578);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5594);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", spawnCutsceneDebrisField);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", npcIncomingMissileUpdate);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", buildCutsceneGradientBuffers);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5820);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A582C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5830);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", jtbl_cinematic_overlay_800A5838);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5850);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5854);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5858);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A585C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5860);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5864);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5868);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A586C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5870);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5874);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5878);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A587C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5880);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5884);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5888);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A588C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5890);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5894);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5898);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A589C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A58A0);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A58A4);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A58A8);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A58AC);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A58B0);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A58B4);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A58B8);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A58BC);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", spawnNpcBurstAlongSegment);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", processCutsceneActions);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", computeCutsceneScreenScale);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", tickCutsceneCameraFromTimeline);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", transformAndNormalizeDirectionByMatrix);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", loadBackdropAsset);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5B6C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5B74);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5B7C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5B84);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5B88);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_800A5B9C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5BAC);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", initCinematicSceneAssets);

extern u8 D_cinematic_overlay_800B0B1E;

void cinematicLoopBody(s32, s32, u8);

void dispatchCinematicFromMainLoop(u8 *medals, u8 arg1) {
    u8 allBronze = 1;
    u8 allSilver = allBronze;
    u8 allGold = allBronze;
    u8 i;

    for (i = 0; i < 16; i++) {
        if (medals[i] < 3) {
            allGold = 0;
        }
        if (medals[i] < 2) {
            allSilver = 0;
        }
        if (medals[i] == 0) {
            allBronze = 0;
        }
    }
    D_cinematic_overlay_800B0B1E = 0;
    if (allBronze) {
        D_cinematic_overlay_800B0B1E = 1;
    }
    if (allSilver) {
        D_cinematic_overlay_800B0B1E = 2;
    }
    if (allGold) {
        D_cinematic_overlay_800B0B1E = 3;
    }
    cinematicLoopBody(3, 2, arg1);
}

u8 shouldShowCutsceneForLevelStage(u8 levelId, u8 arg1) {
    u8 ret;

    ret = (arg1 == 0);
    if (arg1 == 1) {
        ret = 1;
    }
    if (levelId >= LEVEL_BEGGARS_CANYON) {
        ret = 0;
    }
    if (levelId == LEVEL_CORELLIA) {
        if (arg1 == 2) {
            ret = 1;
        }
    }
    if ((levelId == LEVEL_LOGO) && ((arg1 & 0xFF) == 2)) {
        ret = 1;
    }
    return ret;
}

extern char D_cinematic_overlay_800A54CC[];
extern char D_cinematic_overlay_800A54F4[];
extern char D_cinematic_overlay_800A550C[];
extern char D_cinematic_overlay_800A5524[];

char *getAssetNameForNpcType(u8 datSubType) {
    switch (datSubType) {
        case DAT_UNKNOWN_00:
        case DAT_TYPE_0_GENERIC_BUILDING:
        case DAT_TYPE_0_21:
        case DAT_TYPE_0_IMPERIAL_TRAIN_PILLAR:
        case DAT_TYPE_0_IMPERIAL_PLATFORM:
        case DAT_TYPE_0_POWER_GENERATOR:
        case DAT_TYPE_0_4B:
            return NULL;
        case DAT_TYPE_0_TALORAAN_TURRET:
            return D_cinematic_overlay_800A5524;
        case DAT_TYPE_0_RADAR_DISH:
            return "b_lrsp";
        case DAT_TYPE_0_REBEL_TRANSPORT:
            return "reb_transport";
        case DAT_TYPE_0_REBEL_COMBAT:
            return "r_combat";
        case DAT_TYPE_0_MEGA_TURRENT:
            return D_cinematic_overlay_800A54F4;
        case DAT_TYPE_0_REBEL_TURRET:
            return D_cinematic_overlay_800A550C;
        case DAT_TYPE_0_GUN_TURRET:
            return D_cinematic_overlay_800A54CC;
        default:
            return NULL;
    }
}

Vec3f *func_cinematic_overlay_800AEA18(void) {
    return D_cinematic_overlay_800B1A08;
}

void cuts_0058_bubble_sort(struct cuts_file_constant *cutscene) {
    struct cuts_0058_type temp;
    struct cuts_0058_type *temp_s0;
    struct cuts_0058_type *temp_s1;
    u16 var_s2;
    u16 var_s3;

    if (cutscene->unk0058_active_count >= 2U) {
        for (var_s3 = 0; var_s3 < cutscene->unk0058_active_count; var_s3++) {
            for (var_s2 = var_s3 + 1; var_s2 < cutscene->unk0058_active_count; var_s2++) {
                temp_s0 = &cutscene->unk0058[var_s3];
                temp_s1 = &cutscene->unk0058[var_s2];
                if (temp_s0->unk04 > temp_s1->unk04) {
                    zmemcpy(&temp,   temp_s0, sizeof(struct cuts_0058_type));
                    zmemcpy(temp_s0, temp_s1, sizeof(struct cuts_0058_type));
                    zmemcpy(temp_s1, &temp,   sizeof(struct cuts_0058_type));
                }
            }
        }
    }
}

void noopHandler_800AEB30(void) {
}

s32 freeManifestSegmentAssets(s32);
s32 freeTxtFile();
extern u8 D_cinematic_overlay_800B0960;
extern s32 D_main_bss_80137CFC;
extern u8 gBootConfig;

void freeCutsceneResources(void) {
    freeTxtFile();
    freeManifestSegmentAssets(D_main_bss_80137CFC);
    zmemcpy(&gBootConfig, &D_cinematic_overlay_800B0960, 0x50U);
}

typedef struct {
    s32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    u8 active;
} CutsceneActionSlot;

extern CutsceneActionSlot D_cinematic_overlay_800B0BC0[];

void applyCutsceneSlotMaterialOverrides(void);

void resetCutsceneActionSlots(void) {
    u16 i;

    for (i = 0; i < 0x10; i++) {
        D_cinematic_overlay_800B0BC0[i].active = 0;
        D_cinematic_overlay_800B0BC0[i].unk0 = 0;
    }
    applyCutsceneSlotMaterialOverrides();
}

void scheduleCutsceneActionSlot(s16 id, f32 arg1, f32 arg2, f32 arg3) {
    u16 i;

    for (i = 0; i < 0x10; i++) {
        if (D_cinematic_overlay_800B0BC0[i].active == 0) {
            D_cinematic_overlay_800B0BC0[i].unk10 = id;
            D_cinematic_overlay_800B0BC0[i].active = 1;
            D_cinematic_overlay_800B0BC0[i].unk8 = arg2;
            D_cinematic_overlay_800B0BC0[i].unkC = arg3;
            D_cinematic_overlay_800B0BC0[i].unk4 = arg1 - 180.0f;
            return;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", composeInterpolatedNodeMatricesAlt);

void setNpcForwardVectorByIndex(u16, f32 *);

typedef struct {
    u8 pad0[0x88];
    u8 mat[0x30];
    u16 slot;
    u8 padBA[0x13C - 0xBA];
} CutNpcSlotB;

void tickCutsceneNpcSlots(void *arg0) {
    f32 a[3];
    f32 b[3];
    u32 i;
    u16 slot;
    s32 next;

    i = 0;
    if (*(u16 *)((u8 *)arg0 + 0x4A) != 0) {
        do {
            slot = ((CutNpcSlotB *)D_cinematic_overlay_800B1900)[i].slot;
            if (slot != 0xFFFF) {
                next = getNextSlotNpcTypeId(slot) & 0xFFFF;
                if (next != 0xFFFF) {
                    a[0] = 0.0f;
                    a[1] = -0.1f;
                    a[2] = -0.4f;
                    transformVec3ByMat34((void *)((CutNpcSlotB *)D_cinematic_overlay_800B1900)[i].mat, a, b);
                    setNpcForwardVectorByIndex(next, b);
                } else {
                    destroyNpcSlotChain(slot);
                    ((CutNpcSlotB *)D_cinematic_overlay_800B1900)[i].slot = next;
                }
            }
            i++;
        } while (i < *(u16 *)((u8 *)arg0 + 0x4A));
    }
}

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", despawnCutsceneNpcSlot);

void initCutsceneSlotTable(void) {
    u32 var_a0;

    for (var_a0 = 0; var_a0 < 0x40; var_a0++) {
        D_cinematic_overlay_800B0D00[var_a0].unk00 = 0;
    }
}

void insertCutsceneSlot(struct D_cinematic_overlay_800B0D00_type *arg0) {
    u32 var_v1;

    for (var_v1 = 0; var_v1 < 0x40; var_v1++) {
        if (D_cinematic_overlay_800B0D00[var_v1].unk00 == 0) {
            zmemcpy(&D_cinematic_overlay_800B0D00[var_v1], arg0, sizeof(struct D_cinematic_overlay_800B0D00_type));
            break;
        }
    }
}

u16 lookupCutsceneIdMapping(s32 arg0) {
    u16 var_a1;
    u16 ret = 0xFFFF;

    for (var_a1 = 0; var_a1 < 0x5E; var_a1++) {
        if (gCutsceneIdMappingTable[var_a1].unk0 == arg0) {
            ret = gCutsceneIdMappingTable[var_a1].unk2;
            break;
        }
    }
    return ret;
}

extern u16 D_main_bss_80139560[];

u16 findActiveNpcInSlotChain(u16, void *);
void destroyNpcSlotByIndex(u16);

void destroyAllNpcsInSlotChain(s32 chain) {
    u8 iter[8];
    u16 idx;

    while ((idx = findActiveNpcInSlotChain(D_main_bss_80139560[chain], iter)) != 0xFFFF) {
        destroyNpcSlotByIndex(idx);
    }
}

s32 load_hmt_and_hob(s32 *, s32, s32, s32);
s32 walkMeshdef0List(s32 *);
extern s32 D_cinematic_overlay_800A5578;
extern s32 D_cinematic_overlay_800A5594;
extern s32 D_cinematic_overlay_800B0B18;

void maybeLoadYwingCutscene(s32 arg0, s32 arg1) {
    s32 temp_a0;

    temp_a0 = arg0 & 0xFF;
    D_cinematic_overlay_800B0B18 = 0;
    if (((temp_a0 == 4) && ((arg1 & 0xFF) == 1)) || ((temp_a0 == 7) && !(arg1 & 0xFF))) {
        load_hmt_and_hob(&D_cinematic_overlay_800A5578, 0, 1, 0x10000);
        D_cinematic_overlay_800B0B18 = walkMeshdef0List(&D_cinematic_overlay_800A5594);
    }
}

extern f32 D_cinematic_overlay_800B0B2C;

void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot2(void *, f32);
void composeRotationMatrixSlot0(void *, f32);
void addVec3At0x24(void *, f32, f32, f32);
void composeQuatToMat3x4(void *, void *);
f32 sinf(f32);

void buildBobbingObjectMatrix(Vec3f pos, void *out) {
    u8 *obj;

    if (D_cinematic_overlay_800B0B18 != 0) {
        obj = (u8 *)D_cinematic_overlay_800B0B18 + 0x28;
        initVec4TripletFromArgs(obj, 0.1f, 0.1f, 0.1f);
        composeRotationMatrixSlot2(obj, sinf(D_cinematic_overlay_800B0B2C * 1.2f) * 4.0f);
        composeRotationMatrixSlot0(obj, sinf(D_cinematic_overlay_800B0B2C + D_cinematic_overlay_800B0B2C) * 1.5f);
        addVec3At0x24(obj, 0.0f, 0.089999996f, 0.49f);
        composeQuatToMat3x4(obj, out);
        addVec3At0x24(obj, pos[0], pos[1], pos[2]);
    }
}

void cinematicShutdownAudioAndAssets(void) {
    finalizeCurrentSpeechBuffer();
    teardownAnimatedMapGridLayer(); 
}

s32 bytesDiffer(u8 *arg0, u8 *arg1, u32 arg2) {
    u16 var_a3;

    for (var_a3 = 0; var_a3 < arg2; ++var_a3) {
        if (arg0[var_a3] != arg1[var_a3]) return 1;
    }
    return 0;
}

s32 matchKeywordWithPriority(u8 **ctx, u8 *word, s32 priority) {
    u8 *e = *(u8 **)(*ctx + 0x30);
    s32 i;

    while (*e != 0) {
        for (i = 0; i < 6; i++) {
            if (e[i] != word[i]) {
                goto next;
            }
            if (e[i] == 0) {
                break;
            }
        }
        if (e[i] == word[i] && e[i] == 0) {
            return priority < e[7];
        }
    next:
        e = e + e[7] * 0x24 + 8;
    }
    return 0;
}

f32 floatModulo(f32, f32);
void timeSnapshotFiller(void *);
extern s32 D_main_bss_8013889C;

f32 cinematicComputeDt(void) {
    f32 snap[10];
    f32 dt;
    f32 mod;

    timeSnapshotFiller(snap);
    dt = snap[8];
    D_main_bss_8013889C += 1;
    mod = floatModulo(dt, snap[7]);
    if (mod > 0.0f) {
        if ((mod / snap[7]) < 0.5f) {
            dt -= mod;
        } else {
            dt = (dt + snap[7]) - mod;
        }
    }
    if (dt <= 0.0f) {
        dt = 0.016666668f;
    }
    return dt;
}

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", cinematicInitializer);

extern s32 D_cinematic_overlay_800B0934;

s32 isCinematicActive(void) {
    return D_cinematic_overlay_800B0934 != 0;
}

extern u8 D_cinematic_overlay_800B0938;
extern f32 D_cinematic_overlay_800B1EE8;

s32 cinematicStageAdvancer(s32 arg0, s32 arg1, f32 dt) {
    f32 value;

    if (D_cinematic_overlay_800B0934 != 0) {
        value = D_cinematic_overlay_800B1EE8 * dt + (*(u8 **)(D_cinematic_overlay_800B0934 + 0xC))[0x2F];
        if (value > 255.0f) {
            (*(u8 **)(D_cinematic_overlay_800B0934 + 0xC))[0x2F] = 0xFF;
            if (++D_cinematic_overlay_800B0938 >= 7) {
                return 1;
            }
        } else {
            (*(u8 **)(D_cinematic_overlay_800B0934 + 0xC))[0x2F] = value;
        }
    }
    return 0;
}

void removeLookupTableEntry(void *, void *);
void requestViFeatureChange(s32);

void cinematicDeactivator(void *arg0) {
    if (D_cinematic_overlay_800B0934 != 0) {
        removeLookupTableEntry(arg0, *(void **)(D_cinematic_overlay_800B0934 + 0xC));
        D_cinematic_overlay_800B0934 = 0;
        if (!(*(u32 *)(&gBootConfig + 0x44) & 0x80)) {
            requestViFeatureChange(8);
        }
    }
}

s32 getCinematicStateSubObject(void *arg0) {
    return (*(s32 *)((u8 *)(arg0) + 0xC));
}

f32 cinematicInterpRatio(void) {
    f32 var_ft0;

    var_ft0 = 1.0f;
    if (D_cinematic_overlay_800B0934 != 0) {
        var_ft0 = 1.0f - ((f32) (*(u8 *)((u8 *)((*(void **)((u8 *)(D_cinematic_overlay_800B0934) + 0xC))) + 0x2F)) / 255.0f);
    }
    return var_ft0;
}

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", fake_func_800AF6A8);
