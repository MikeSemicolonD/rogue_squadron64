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

INCLUDE_ASM("asm/nonmatchings/menu_overlay/intro_crawl_handling", initModelViewer);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/intro_crawl_handling", buildModelViewerTextPage);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/intro_crawl_handling", runModelViewerSoundDemo);

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
INCLUDE_ASM("asm/nonmatchings/menu_overlay/intro_crawl_handling", selectPostCrawlCraft);
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

INCLUDE_ASM("asm/nonmatchings/menu_overlay/intro_crawl_handling", releaseModelViewerModelAssets);

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

INCLUDE_ASM("asm/nonmatchings/menu_overlay/intro_crawl_handling", tickMultiPartVoiceLine);

void *rs_malloc(s32, s32);
void applySpeechVolumeScalar(f32);

typedef struct {
    f32 volume;
    s32 unk4;
    u16 ids[8];
    u16 count;
    u8 unk1A;
    u8 flag;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 pad1F;
    s32 unk20;
} VoiceLineStruct;

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
