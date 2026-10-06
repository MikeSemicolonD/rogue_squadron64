#include "common.h"
#include "common_types.h"
#include "common_variables.h"

#include "main/08120.h"

/* RO/Data, uncomment when ro/data matching is possible
s8 *gPostIntroCrawlCraftObjectNames[4][4] = {
    { "xwing", "xwing", "xwing", NULL },
    { "xwing", "xwing", "xwing", "xwing" },
    { "awing", "awing", "awing", "awing" },
    { "vwing", "vwing", "vwing", "vwing" },
};
s8 *gPostIntroCrawlHobFiles[4][4] = {
    { (s8 *) "pl_crafts/xwing", NULL, NULL, NULL },
    { (s8 *) "pl_crafts/xwing", NULL, NULL, NULL },
    { (s8 *) "pl_crafts/awing", NULL, NULL, NULL },
    { (s8 *) "pl_crafts/vwing", NULL, NULL, NULL },
};
*/

// Interim ro/data externs
extern char *gPostIntroCrawlCraftObjectNames[4][4];
extern char *gPostIntroCrawlHobFiles[4][4];

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/intro_crawl_handling", D_menu_overlay_800A78B0);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/intro_crawl_handling", D_menu_overlay_800A78B8);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/intro_crawl_handling", D_menu_overlay_800A78C0);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/intro_crawl_handling", D_menu_overlay_800A78C8);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/intro_crawl_handling", D_menu_overlay_800A78D8);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/intro_crawl_handling", D_menu_overlay_800A78E8);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/intro_crawl_handling", runModelViewerLoop);

extern s32 D_menu_overlay_800D0360;
extern s32 D_menu_overlay_800D0364;
extern s32 D_menu_overlay_800D03CC;
typedef struct {
    u8 pad0[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
} ModelViewerView;
extern ModelViewerView D_menu_overlay_800D0370;
void selectRenderPresetByIndex(s32);
void setViewStateTripletBytes(s32, s32, s32);
void setMissionLevelInitByte(s32);
s32 allocateSlotTable(s32);
void loadCharTextureSet(s32, s32, s32, s32);
s32 loadDatFile(char *);

void initModelViewer(void) {
    D_menu_overlay_800D0370.unk10 = 0x280;
    D_menu_overlay_800D0370.unk14 = 0x12C;
    D_menu_overlay_800D0370.unk18 = 0x140;
    D_menu_overlay_800D0370.unk4 = 0;
    D_menu_overlay_800D0370.unk8 = 0;
    D_menu_overlay_800D0370.unkC = 0;
    D_menu_overlay_800D0370.unk1C = 0x96;
    D_menu_overlay_800D0370.unk20 = 45.0f;
    D_menu_overlay_800D0370.unk24 = 0.1171875f;
    D_menu_overlay_800D0370.unk28 = 78.125f;
    selectRenderPresetByIndex(0);
    setViewStateTripletBytes(0, 0, 0);
    setMissionLevelInitByte(1);
    D_menu_overlay_800D0360 = allocateSlotTable(8);
    D_menu_overlay_800D0364 = allocateSlotTable(8);
    loadCharTextureSet(D_menu_overlay_800D0360, 3, 1, 0x10);
    D_menu_overlay_800D03CC = loadDatFile("frontend/starwars");
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/intro_crawl_handling", buildModelViewerTextPage);

typedef struct {
    u16 h0;
    u16 h2;
    u8 pad4[0xE];
    u8 b12;
    u8 pad13[7];
    u8 b1A;
    u8 b1B;
    u8 b1C;
    u8 pad1D;
    u16 h1E;
    u16 h20;
    u16 h22;
    u16 h24;
} MvSndCfg;

extern MvSndCfg D_menu_overlay_800CFFE0;
extern s32 D_main_bss_80138920;
extern s32 D_menu_overlay_800D00A8;
extern u8 D_menu_overlay_800D0020[];
extern u8 gPostIntroCrawlNumCraft[];
extern u8 D_menu_overlay_800D0120[][0x90];
extern u8 D_menu_overlay_800CFFB0[];
extern u8 D_menu_overlay_800D039C[];
void parseLoadedSndSection(s32);
void loadSongAssetByName(s32, s32);
void playSimpleAudioCmd(s32, s32, s32);
void syncMusyXIfActive(void *);
s32 findAudioChannelById(s32);
s32 playSongById(s32, s32, s32, s32);
void initVec4TripletFromArgs(void *, f32, f32, f32);
void addVec3At0x24(void *, f32, f32, f32);
void mat3x3InverseInto(void *, void *);
void play3DSoundEvent(void *, void *, void *, f32, f32, s32, s32, s32, s32);
void play3DSoundEventVariant(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32);
void register3DAudioListenerNode(void *, void *, void *, void *, void *, f32, f32, f32, s32, s32);

static __inline__ f32 *mvXform(f32 y) {
    initVec4TripletFromArgs(D_menu_overlay_800CFFB0, 0.625f, 0.625f, 1.0f);
    addVec3At0x24(D_menu_overlay_800CFFB0, 0.0f, y, 0.0f);
    mat3x3InverseInto(D_menu_overlay_800D039C, D_menu_overlay_800CFFB0);
    return (f32 *)D_menu_overlay_800CFFB0;
}

void runModelViewerSoundDemo(u8 craft) {
    f32 v1[4];
    f32 v2[4];
    f32 v3[4];
    f32 vel[3];
    f32 *m;
    u8 *pos;
    char *name;
    u8 i;

    rs_memset((u8 *)vel, 0, 0xC);
    parseLoadedSndSection(2);
    loadSongAssetByName(D_main_bss_80138920, 2);
    playSimpleAudioCmd(0x7F, 0x32, 0xFE);
    playSimpleAudioCmd(0x78, 0x32, 0xFD);
    D_menu_overlay_800CFFE0.h0 = 0xA0;
    D_menu_overlay_800CFFE0.b1A = 1;
    D_menu_overlay_800CFFE0.b12 = 0x78;
    D_menu_overlay_800CFFE0.b1B = 0x32;
    D_menu_overlay_800CFFE0.h1E = 0x51E;
    D_menu_overlay_800CFFE0.h20 = 0xF5C;
    D_menu_overlay_800CFFE0.h2 = 0xA0;
    D_menu_overlay_800CFFE0.h22 = 0x1999;
    D_menu_overlay_800CFFE0.b1C = 1;
    D_menu_overlay_800CFFE0.h24 = 0x800;
    syncMusyXIfActive(&D_menu_overlay_800CFFE0);
    D_menu_overlay_800D00A8 = playSongById(2, 2, findAudioChannelById(2), 0);
    m = NULL;
    for (i = 0; i < gPostIntroCrawlNumCraft[craft]; i++) {
        pos = D_menu_overlay_800D0120[i] + 0x50;
        m = mvXform(0.0f);
        name = gPostIntroCrawlCraftObjectNames[craft][i];
        if (name == NULL) {
            break;
        }
        switch (name[0]) {
        case 'a':
            play3DSoundEvent(D_menu_overlay_800D0120[i] + 8, pos, vel, 10.0f, 0.3f, 15, 15, 0, 0);
            D_menu_overlay_800D0120[i][0x4C] = 0x78;
            break;
        case 'x':
            play3DSoundEvent(D_menu_overlay_800D0120[i] + 8, pos, vel, 10.0f, 0.5f, 15, 0xE, 0, 0);
            D_menu_overlay_800D0120[i][0x4C] = 0x78;
            break;
        case 's':
            play3DSoundEvent(D_menu_overlay_800D0120[i] + 8, pos, vel, 10.0f, 0.0f, 15, 0x13, 0x78, 0);
            D_menu_overlay_800D0120[i][0x4C] = 0x5A;
            break;
        case 'v':
            play3DSoundEvent(D_menu_overlay_800D0120[i] + 8, pos, vel, 10.0f, 0.3f, 15, 0x12, 0x78, 0);
            D_menu_overlay_800D0120[i][0x4C] = 0x64;
            break;
        case 'y':
            play3DSoundEvent(D_menu_overlay_800D0120[i] + 8, pos, vel, 10.0f, 0.3f, 15, 0x11, 0x78, 0);
            D_menu_overlay_800D0120[i][0x4C] = 0x64;
            break;
        case 't':
            play3DSoundEventVariant(D_menu_overlay_800D0120[i] + 8, pos, vel, 21.0f, 0.6f, 15, 7, 1, 0x7F, 0x28);
            D_menu_overlay_800D0120[i][0x4C] = 0x7F;
            break;
        case 'f':
            play3DSoundEvent(D_menu_overlay_800D0120[i] + 8, pos, vel, 12.0f, 0.6f, 15, 0x2E, 0x78, 0);
            D_menu_overlay_800D0120[i][0x4C] = 0x78;
            break;
        case 'k':
            play3DSoundEvent(D_menu_overlay_800D0120[i] + 8, pos, vel, 10.0f, 0.7f, 15, 0x6F, 0x5A, 0);
            D_menu_overlay_800D0120[i][0x4C] = 0x6E;
            break;
        }
    }
    v1[0] = m[9];
    v1[1] = m[10];
    v1[2] = m[11];
    v2[0] = m[2];
    v2[1] = m[5];
    v2[2] = m[8];
    v3[0] = -m[1];
    v3[1] = -m[4];
    v3[2] = -m[7];
    register3DAudioListenerNode(D_menu_overlay_800D0020, v1, v2, v2, v3, 2.0f, 2.0f, 50.0f, 0, 0x7F);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/intro_crawl_handling", updateModelViewerAudioSource);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/intro_crawl_handling", loadModelViewerModels);

#ifdef NONMATCHING_DATA
// This probably can't be matched until the ro/data for this entire file is figured out.
void selectPostCrawlCraft(u8 arg0) {
    u8 var_s0;
    char *var_a1;
    char *var_s1;

    switch (gGameSettings.vehicleId) {
    case XWING_CRAFT:
        var_s1 = "pl_crafts/xwing";
        var_a1 = "xwing";
        break;
    case YWING_CRAFT:
        var_s1 = "pl_crafts/ywing";
        var_a1 = "ywing";
        break;
    case AWING_CRAFT:
        var_s1 = "pl_crafts/awing";
        var_a1 = "awing";
        break;
    case VWING_CRAFT:
        var_s1 = "pl_crafts/vwing";
        var_a1 = "vwing";
        break;
    case SNOWSPEEDER_CRAFT:
        var_s1 = "pl_crafts/snowspeeder";
        var_a1 = "snowspeeder";
        break;
    case FALCON_CRAFT:
        var_s1 = "pl_crafts/falcon";
        var_a1 = "falcon";
        break;
    case TIEINTER_CRAFT:
        var_s1 = "imp_stuff/tieinter";
        var_a1 = "tie_inter";
        break;
    case T16_CRAFT:
        var_s1 = "pl_crafts/t16";
        var_a1 = "t16";
        break;
    case KOELSCH_CRAFT:
        var_s1 = "pl_crafts/koelsch";
        var_a1 = "koelsch";
        break;
    default:
        return;
    }
    gPostIntroCrawlCraftObjectNames[arg0][0] = var_a1;
    for (var_s0 = 0; var_s0 < 4; var_s0++) {
        if (gPostIntroCrawlHobFiles[arg0][var_s0] == NULL) {
            gPostIntroCrawlHobFiles[arg0][var_s0] = var_s1;
            break;
        }
        if (rs_strcmp(gPostIntroCrawlHobFiles[arg0][var_s0], var_s1) == 0) break;
    }
    return;
}
#else
extern u8 D_main_bss_80130B41;
extern char D_menu_overlay_800A78B0[];
extern char D_menu_overlay_800A78B8[];
extern char D_menu_overlay_800A78C0[];
extern char D_menu_overlay_800A78C8[];
extern char D_menu_overlay_800A78D8[];
extern char D_menu_overlay_800A78E8[];
void selectPostCrawlCraft(u8 arg0) {
    u8 var_s0;
    char *var_a1;
    char *var_s1;

    switch (D_main_bss_80130B41) {
    case 0:
        var_s1 = D_menu_overlay_800A78E8;
        var_a1 = D_menu_overlay_800A78C0;
        break;
    case 1:
        var_s1 = "pl_crafts/ywing";
        var_a1 = "ywing";
        break;
    case 2:
        var_s1 = D_menu_overlay_800A78D8;
        var_a1 = D_menu_overlay_800A78B8;
        break;
    case 3:
        var_s1 = D_menu_overlay_800A78C8;
        var_a1 = D_menu_overlay_800A78B0;
        break;
    case 4:
        var_s1 = "pl_crafts/snowspeeder";
        var_a1 = "snowspeeder";
        break;
    case 5:
        var_s1 = "pl_crafts/falcon";
        var_a1 = "falcon";
        break;
    case 6:
        var_s1 = "imp_stuff/tieinter";
        var_a1 = "tie_inter";
        break;
    case 7:
        var_s1 = "pl_crafts/t16";
        var_a1 = "t16";
        break;
    case 8:
        var_s1 = "pl_crafts/koelsch";
        var_a1 = "koelsch";
        break;
    default:
        return;
    }
    gPostIntroCrawlCraftObjectNames[arg0][0] = var_a1;
    for (var_s0 = 0; var_s0 < 4; var_s0++) {
        if (gPostIntroCrawlHobFiles[arg0][var_s0] == NULL) {
            gPostIntroCrawlHobFiles[arg0][var_s0] = var_s1;
            break;
        }
        if (rs_strcmp(gPostIntroCrawlHobFiles[arg0][var_s0], var_s1) == 0) break;
    }
}
#endif

s32 resetPlayerSlotChannelTransform(s32);
s32 rs_free(s32);
extern s32 D_menu_overlay_800D0360;
extern s32 D_menu_overlay_800D0364;
extern s32 D_menu_overlay_800D03CC;

void shutdownModelViewer(void) {
    rs_free(D_menu_overlay_800D03CC);
    resetPlayerSlotChannelTransform(3);
    rs_free(D_menu_overlay_800D0364);
    rs_free(D_menu_overlay_800D0360);
}

s32 enqueueMeshForDeferredRelease(s32 *);

void releaseMeshLinkedList(void *arg0) {
    s32 *var_s0;

    var_s0 = (*(s32 **)((u8 *)(arg0) + 0x10));
    if (var_s0 != NULL) {
        do {
            enqueueMeshForDeferredRelease(var_s0);
            var_s0 = *var_s0;
        } while (var_s0 != NULL);
    }
}

extern s32 D_menu_overlay_800D0110;

void freeModelViewerMeshChain(u8 *arg0) {
    s32 *p;
    s32 *q;

    p = *(s32 **)(arg0 + 0x10);
    while (p != NULL) {
        q = p;
        p = (s32 *)*p;
        if (q[0x17] != 0) {
            rs_free(q[0x17]);
        }
        rs_free((s32)q);
    }
    rs_free(D_menu_overlay_800D0110);
}

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x28];
} ModelViewerSlot;

void releaseMeshAsset(s32);
extern u8 gPostIntroCrawlNumCraft[];
extern ModelViewerSlot D_menu_overlay_800D00B0[];
extern u8 D_menu_overlay_800D0120[][0x90];

void releaseModelViewerModelAssets(u8 craft) {
    u8 i;

    for (i = 0; i < 2; i++) {
        if (D_menu_overlay_800D00B0[i].unk4 != 0) {
            releaseMeshAsset(D_menu_overlay_800D00B0[i].unk4);
        }
    }
    for (i = 0; i < gPostIntroCrawlNumCraft[craft]; i++) {
        releaseMeshAsset(*(s32 *)D_menu_overlay_800D0120[i]);
    }
}

void initVec4TripletFromArgs(void *, f32, f32, f32);
void addVec3At0x24(void *, f32, f32, f32);
void mat3x3InverseInto(void *, void *);
extern u8 D_menu_overlay_800CFFB0[];
extern u8 D_menu_overlay_800D039C[];

void *setModelViewerObjectTransform(f32 arg0) {
    initVec4TripletFromArgs(D_menu_overlay_800CFFB0, 0.625f, 0.625f, 1.0f);
    addVec3At0x24(D_menu_overlay_800CFFB0, 0.0f, arg0, 0.0f);
    mat3x3InverseInto(D_menu_overlay_800D039C, D_menu_overlay_800CFFB0);
    return D_menu_overlay_800CFFB0;
}

s32 runMusyXTaskLocked();

void runMusyXTaskWrapper(void) {
    runMusyXTaskLocked();
}

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

typedef struct {
    u8 pad[0x20];
    ListNode *list;
} ListOwner20;

void appendNodeToListTail(ListOwner20 *owner, ListNode *node) {
    ListNode *p;

    if (owner->list == NULL) {
        owner->list = node;
        return;
    }
    p = owner->list;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = node;
    node->prev = p;
}

typedef struct {
    u8 pad[0x10];
    ListNode *list;
} ListOwner10;

void appendNodeToListHead(ListOwner10 *owner, ListNode *node) {
    ListNode *p;

    if (owner->list == NULL) {
        owner->list = node;
        return;
    }
    p = owner->list;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = node;
    node->prev = p;
}

__asm__(".section .rodata\n.word 0x000520C0\n.word 0x00832021\n.section .text");

void *rs_malloc(s32, s32);
void applySpeechVolumeScalar(f32);

typedef struct {
    f32 volume;
    f32 unk4;
    u16 ids[8];
    u16 count;
    u8 unk1A;
    u8 flag;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 pad1F;
    f32 unk20;
} VoiceLineStruct;

u8 enqueueSpeechClip(u16, u8);
u8 isSpeechSlotActive(u8);
void stopSpeechSlotIfActive(u8);
s32 tickMultiPartVoiceLine(VoiceLineStruct *v, f32 dt) {
    if (v == NULL) {
        return 1;
    }
    if (v->unk1E == 1) {
        if (v->unk1C == 0) {
            goto done;
        }
        v->unk20 += dt;
        if (v->unk20 > 1.0f) {
            v->unk20 = 1.0f;
        }
        applySpeechVolumeScalar(1.0f - v->unk20);
        if (v->unk20 == 1.0f) {
            stopSpeechSlotIfActive(v->unk1C);
            return 1;
        }
        return 0;
    }
    if (v->unk1D != 0) {
        if (v->unk1C != 0) {
            if (isSpeechSlotActive(v->unk1C)) {
                return 0;
            }
            v->unk1C = 0;
        } else {
            v->unk4 += dt;
            if (v->volume < v->unk4) {
                v->unk4 = 0;
                v->unk1D = 0;
            }
        }
        goto ret0;
    }
    if (v->unk1A == v->count) {
done:
        rs_free(v);
        return 1;
    }
    v->unk1C = enqueueSpeechClip(v->ids[v->unk1A], v->flag);
    v->unk1D = 1;
    v->unk1A++;
ret0:
    return 0;
}

VoiceLineStruct *mallocVoiceLineStruct(u16 *ids, f32 volume, u8 flag) {
    VoiceLineStruct *v;
    u16 i;

    v = rs_malloc(sizeof(VoiceLineStruct), 0);
    v->flag = flag;
    v->unk4 = 0;
    v->unk1A = 0;
    v->unk1C = 0;
    v->unk1D = 0;
    v->unk1E = 0;
    v->unk20 = 0;
    v->volume = volume;
    applySpeechVolumeScalar(1.0f);
    for (i = 0; ids[i] != 0xFFFF; i++) {
        v->ids[i] = ids[i];
    }
    v->count = i;
    return v;
}

void setVoiceLineLoopFlag(void *arg0) {
    (*(s8 *)((u8 *)(arg0) + 0x1E)) = 1;
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/intro_crawl_handling", fake_func_800CC038);

__asm__(".section .rodata\n.word 0x00220821\n.word 0x94223BF8\n.section .text");
