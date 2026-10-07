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

static const char D_cinematic_overlay_800A516C[16] = "cuts/id%d_%s";

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", strCinPlCraftsVwing);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A518C);

typedef struct { s32 a, b, c, d; } LcStr16;
typedef struct { char name[0x4C]; } LcEnt;
typedef struct { u8 pad[0x4A]; u16 count; u8 pad2[0x13D8 - 0x4C]; LcEnt ents[60]; } LcFile;
typedef struct { u8 b0; u8 b1; u8 pad[0x66]; f32 f68; u8 pad2[0x4C]; u16 hB8; u8 pad3[0x13C - 0xBA]; } LcSlot;
extern struct { u8 b0; u8 b1; u8 pad[0x16]; u32 w18; } lcGs __asm__("gGameSettings");
extern char *cutsceneTypeStrings[];
extern u16 D_cinematic_overlay_800B0B20;
extern char strCinPlCraftsVwing[];
extern char D_cinematic_overlay_800A518C[];
extern s32 D_cinematic_overlay_800B1A10[4];
extern s32 D_cinematic_overlay_800B1A20[4];
extern LcSlot *lcSlots __asm__("D_cinematic_overlay_800B1900");
s32 sprintf(char *, const char *, ...);
LcFile *load_asset_with_malloc_flags(char *, s32);
void processCutsceneActions(u8 *arg0, s32 arg1);
extern void *rs_malloc(u32, u16);
extern void *rs_memset(void *, s32, s32);
s32 strlen(const char *);
s32 rs_strcmp(char *, char *);
void clearVec4QuadStruct(void *);
void spawnCutsceneObjectsFromList(LcFile *, u8, s32);
void initWaterSprayEffectAndSfx(void);
void loadLevelTextureCache(s32);
void initCutsceneAudioChannels(LcFile *);

LcFile *load_cutscene(u8 id, u8 type) {
    char buf[0x20];
    LcFile *c;
    u32 i;
    s32 n;
    char *name;

    sprintf(buf, D_cinematic_overlay_800A516C, id, cutsceneTypeStrings[type]);
    c = load_asset_with_malloc_flags(buf, 0x10);
    processCutsceneActions((u8 *)c, lcGs.b1);
    D_cinematic_overlay_800B0B20 = 0;
    if (id == 0x13 && (lcGs.w18 & 2)) {
        *(LcStr16 *)c->ents[32].name = *(LcStr16 *)strCinPlCraftsVwing;
        *(LcStr16 *)c->ents[35].name = *(LcStr16 *)strCinPlCraftsVwing;
    }
    lcSlots = rs_malloc(c->count * sizeof(LcSlot), 0x10);
    rs_memset(lcSlots, 0, c->count * sizeof(LcSlot));
    for (i = 0; i < c->count; i++) {
        lcSlots[i].b0 = 0;
        lcSlots[i].f68 = 5.0f;
        lcSlots[i].hB8 = 0xFFFF;
        clearVec4QuadStruct((u8 *)&lcSlots[i] + 0x88);
        name = c->ents[i].name;
        n = strlen(name) - 1;
        lcSlots[i].b1 = n;
        if (rs_strcmp(name, D_cinematic_overlay_800A518C) != 0 && (u32)(c->ents[i].name[n] - '0') < 10) {
            do {
                n--;
            } while ((u32)(c->ents[i].name[n] - '0') < 10 || c->ents[i].name[n] == '_');
            lcSlots[i].b1 = n;
        }
    }
    cuts_0058_bubble_sort((struct cuts_file_constant *)c);
    spawnCutsceneObjectsFromList(c, id, 0);
    initWaterSprayEffectAndSfx();
    spawnCutsceneObjectsFromList(c, id, 1);
    if (id != 10) {
        loadLevelTextureCache(0x5DC0);
    }
    initCutsceneAudioChannels(c);
    for (i = 0; i < 4; i++) {
        D_cinematic_overlay_800B1A10[i] = -1;
        D_cinematic_overlay_800B1A20[i] = -1;
    }
    return c;
}

typedef struct { f32 v; f32 s; f32 t; } CsuKey;
extern u16 D_cinematic_overlay_800B0B22;

void cinematicSlotUpdateU8(u8 *, f32 *, f32, f32, u8) __asm__("cinematicSlotUpdate");

void cinematicSlotUpdateU8(u8 *arg0, f32 *arg1, f32 arg2, f32 arg3, u8 arg4) {
    u16 idx[4];
    f32 val[4];
    f32 c[8];
    f32 tm[4];
    u8 *g;
    s32 n;
    u16 i;
    u16 j;
    f32 x;
    f32 d;
    f32 t;
    f32 t2;
    f32 t3;
    CsuKey *e;

    g = (u8 *)D_cinematic_overlay_800B1904;
    n = (s32)(arg2 * ((f32)*(u32 *)(g + 0x44) / arg3));
    tm[0] = (f32)(n - 1) / ((f32)*(u32 *)(g + 0x44) / arg3);
    tm[1] = (f32)n / ((f32)*(u32 *)(g + 0x44) / arg3);
    tm[2] = (f32)(n + 1) / ((f32)*(u32 *)(g + 0x44) / arg3);
    tm[3] = (f32)(n + 2) / ((f32)*(u32 *)(g + 0x44) / arg3);
    if (tm[0] < 0.0f || 1.0f < tm[2] || 1.0f < tm[3] || (D_cinematic_overlay_800B0B22 != 0 && arg4 == 0)) {
        j = 0;
        while (((CsuKey *)arg0)[j].t <= arg2) {
            j++;
        }
        if (j != 0) {
            j--;
        }
        e = (CsuKey *)(j * 12 + (s32)arg0);
        *arg1 = (arg2 - e->t) * e->s + e->v;
    } else {
        for (i = 0; i < 4; i++) {
            register f32 *vp asm("$8") = (f32 *)((i << 2) + (s32)idx);
            vp = (f32 *)((s32)vp + 8);
            __asm__("" :: "r"(vp));
            x = tm[i];
            j = 0;
            while (((CsuKey *)arg0)[j].t <= x) {
                j++;
            }
            if (j != 0) {
                j--;
            }
            { s32 k = j; e = (CsuKey *)(k * 12 + (s32)arg0);
            *vp = (x - e->t) * e->s + e->v;
            idx[i] = k; }
        }
        d = tm[2] - tm[1];
        if (d < 0.00005f) {
            d = 0.00005f;
        }
        t = (arg2 - tm[1]) / d;
        t2 = t * t;
        t3 = t2 * t;
        c[4] = t3 * -0.5f + t2 + t * -0.5f;
        c[5] = t3 * 1.5f + t2 * -2.5f + 1.0f;
        c[6] = t3 * -1.5f + (t2 + t2) + t * 0.5f;
        c[7] = t3 * 0.5f + t2 * -0.5f;
        c[1] = t;
        c[2] = t2;
        c[3] = t3;
        *arg1 = c[4] * val[0] + c[5] * val[1] + c[6] * val[2] + c[7] * val[3];
    }
}

extern f32 D_main_bss_80136FBC;
extern f32 D_main_bss_80136FAC;
extern u16 D_cinematic_overlay_800B090C[];
extern u16 scNpc __asm__("D_main_bss_80130BA2");
extern u8 scFlag __asm__("D_main_bss_80130B38");
extern u8 scVoice __asm__("D_main_bss_80130B62");
extern u8 scLvl[] __asm__("D_main_bss_80136E18");
extern void *scB00 __asm__("D_cinematic_overlay_800B0B00");
extern void *scB04 __asm__("D_cinematic_overlay_800B0B04");
extern void *scB08 __asm__("D_cinematic_overlay_800B0B08");
extern void *scB0C __asm__("D_cinematic_overlay_800B0B0C");
extern void *scB10 __asm__("D_cinematic_overlay_800B0B10");
extern u8 scActor[] __asm__("cutsceneActorNpcHandler");
void initNpcBookkeepingTables(void);
void setMissionLevelInitByte(s32);
void loadLevelAssets(u16);
void scBounds(f32, f32) __asm__("setGridLayerScrollBounds");
void setGridLayerScrollX(f32);
u16 scSpawn(void *, void *, s32, s32) __asm__("spawnNpcOfType");
void *scBackdrop(char *, s32, s32, s32) __asm__("loadBackdropAsset");
void *scSub(void *) __asm__("getCinematicStateSubObject");
void scInsert(void *, void *, s32) __asm__("insertLookupEntry");
void buildCutsceneGradientBuffers(void);
s32 scLoadHob(char *, s32, s32, s32) __asm__("load_hmt_and_hob");
void loadWeaponsHobObjects(void);
void allocAnimationPhasePool(s32);
void clearTrackedNpcSlots(void);
void allocAndInitParticlePool(void);
void scSpeech(s32, u8) __asm__("initSpeechSubsystem");

void setupCutsceneLevel(s32 level) {
    initNpcBookkeepingTables();
    D_main_bss_80136FBC = 0.9f;
    D_main_bss_80136FAC = 5.0f;
    setMissionLevelInitByte(1);
    loadLevelAssets(D_cinematic_overlay_800B090C[level]);
    scBounds(16.0f, 24.0f);
    setGridLayerScrollX(1.4117647f);
    scNpc = scSpawn(scActor, NULL, 4, 0x64);
    switch (level) {
    case 2:
        D_main_bss_80136FBC = 0.3f;
        break;
    case 3:
        if (scFlag != 0) {
            scLvl[0] = 0;
            scLvl[1] = 0;
            scLvl[2] = 0;
            scB10 = scBackdrop("big_cor", 0x40, 0x20, 0);
            scInsert(scB00, scSub(scB10), 0x14);
            buildCutsceneGradientBuffers();
        }
        break;
    case 6:
        scLoadHob("imp_stuff/atst", 0, 1, 0);
        scLoadHob("imp_stuff/atat", 0, 1, 0);
        break;
    case 15:
        scLoadHob("imp_stuff/wrld_dvfx", 0, 0, 0);
        break;
    case 19:
        setGridLayerScrollX(1.0f);
        scLvl[0] = 0xFF;
        scLvl[1] = 0xFF;
        scLvl[2] = 0xFF;
        scB04 = scBackdrop("nin", 0x40, 0x40, 0);
        scB08 = scBackdrop("f5", 0x40, 0x20, 0);
        scB0C = scBackdrop("factor", 0x80, 0x20, 1);
        scInsert(scB00, scSub(scB04), 0x14);
        scInsert(scB00, scSub(scB08), 0x16);
        scInsert(scB00, scSub(scB0C), 0x14);
        D_main_bss_80136FBC = 0.975f;
        D_main_bss_80136FAC = 5.0f;
        break;
    }
    loadWeaponsHobObjects();
    allocAnimationPhasePool(0x10);
    clearTrackedNpcSlots();
    allocAndInitParticlePool();
    scSpeech(0, scVoice);
}

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

extern u16 D_main_bss_80139560[];
extern u16 D_main_bss_80130BA2;
s32 slotDispatcherIter(u16, s32, void *);
void cinematicSlotBatchDispatch(CineNode **arg0) {
    s32 n;
    slotDispatcherIter(D_main_bss_80139560[3], 4, &D_cinematic_overlay_800B0A00);
    slotDispatcherIter(D_main_bss_80139560[4], 4, &D_cinematic_overlay_800B0A00);
    slotDispatcherIter(D_main_bss_80139560[6], 4, &D_cinematic_overlay_800B0A00);
    slotDispatcherIter(D_main_bss_80139560[8], 4, &D_cinematic_overlay_800B0A00);
    slotDispatcherIter(D_main_bss_80139560[10], 4, &D_cinematic_overlay_800B0A00);
    slotDispatcherIter(D_main_bss_80139560[7], 4, &D_cinematic_overlay_800B0A00);
    slotDispatcherIter(D_main_bss_80130BA2, 4, &D_cinematic_overlay_800B0A00);
    D_cinematic_overlay_800B0AB0.unk0 = n = ({ s32 t = (s32)*arg0; __asm__("" : "+r"(t)); t; });
    if (n != 0) ((CineNode *)n)->unk4 = (s32)&D_cinematic_overlay_800B0AB0;
    D_cinematic_overlay_800B0AB0.unk4 = 0;
    *arg0 = &D_cinematic_overlay_800B0AB0;
}

extern u8 sehBusy __asm__("D_cinematic_overlay_800B09B0");
extern s32 D_cinematic_overlay_800B0AFC;
extern void *D_cinematic_overlay_800B0B00;
extern u8 D_cinematic_overlay_800B0B14;
extern u8 D_cinematic_overlay_800B0B1D;
extern u8 D_main_bss_80136E18[];
extern s32 D_cinematic_overlay_800B0B18;
s32 setActiveRenderListPtr();
void setRenderStateFlagByteOne(s32);
void setRenderStateFlagByteTwo(s32);
void setRenderStateFlagByteThree(s32);
void setupCameraMatrices(void *);
void initRenderStateArrays(void);
void linkHudNodeAndComputeScreenPos(void *);
s32 rebuildActiveDisplayObjectList();
void setFrameLevelStateBytes(u8, u8, u8);

typedef struct { void *p0; s32 p4; s32 p8; s32 pC; } SehObj;

void slotEffectHandlerDispatch(u8 *arg0, u8 arg1) {
    void *saved;
    s32 a0;
    void **tbl;
    void **t;
    s32 x;

    if (sehBusy != 0) {
        setFrameLevelStateBytes(0, 0, 0);
        setActiveRenderListPtr(0);
        setRenderStateFlagByteOne(1);
        *(s32 *)(arg0 + 0) = 0;
        *(s32 *)(arg0 + 8) = 0;
        *(s32 *)(arg0 + 0xC) = 0;
        linkHudNodeAndComputeScreenPos(arg0);
        setupCameraMatrices(arg0);
        sehBusy -= 1;
        return;
    }
    if (arg1 != 0x13) {
        if (arg1 == 0xA) {
            __asm__("");
            a0 = 0;
            goto call;
        }
        if (D_cinematic_overlay_800B09D0.unk0 == 0) {
            a0 = 0;
            goto call;
        }
        setActiveRenderListPtr(&D_cinematic_overlay_800B09D0);
    }
    a0 = 1;
call:
    setRenderStateFlagByteOne(a0);
    tbl = (void **)D_cinematic_overlay_800B09C0;
    x = D_cinematic_overlay_800B0B00;
    saved = *(void **)arg0;
    ((SehObj *)arg0)->p8 = 0;
    *(void **)arg0 = tbl[0];
    *(s32 *)(arg0 + 0xC) = rebuildActiveDisplayObjectList(x);
    setFrameLevelStateBytes(D_main_bss_80136E18[0], D_main_bss_80136E18[1], D_main_bss_80136E18[2]);
    setupCameraMatrices(arg0);
    initRenderStateArrays();
    setRenderStateFlagByteOne(0);
    *(s32 *)(arg0 + 0xC) = 0;
    t = tbl[1];
    ((SehObj *)arg0)->p0 = t;
    if (D_cinematic_overlay_800B0B1D != 0) {
        ((SehObj *)arg0)->p0 = *t;
    }
    setupCameraMatrices(arg0);
    initRenderStateArrays();
    x = D_cinematic_overlay_800B0AFC;
    *(void **)arg0 = saved;
    *(s32 *)(arg0 + 8) = rebuildActiveDisplayObjectList(x);
    linkHudNodeAndComputeScreenPos(arg0);
    setupCameraMatrices(arg0);
    if (D_cinematic_overlay_800B0B18 != 0 && D_cinematic_overlay_800B0B14 != 0) {
        f32 fs0;
        f32 fs1;
        initRenderStateArrays();
        setupCameraMatrices(arg0);
        fs0 = *(f32 *)(arg0 + 0x24);
        fs1 = *(f32 *)(arg0 + 0x28);
        *(f32 *)(arg0 + 0x24) = 0.1171875f;
        *(f32 *)(arg0 + 0x28) = 27.34375f;
        setRenderStateFlagByteOne(1);
        setRenderStateFlagByteThree(0);
        setRenderStateFlagByteTwo(1);
        setActiveRenderListPtr(0);
        *(s32 *)arg0 = 0;
        *(s32 *)(D_cinematic_overlay_800B0B18 + 0xC) = 0;
        *(s32 *)(D_cinematic_overlay_800B0B18 + 0x10) = 0;
        *(s32 *)arg0 = D_cinematic_overlay_800B0B18 + 0xC;
        __asm__("" :: "m"(*(s32 *)arg0) : "$4");
        setupCameraMatrices(arg0);
        setRenderStateFlagByteThree(1);
        setRenderStateFlagByteOne(0);
        *(f32 *)(arg0 + 0x24) = fs0;
        *(f32 *)(arg0 + 0x28) = fs1;
    }
}

typedef struct { f32 x, y, z; } CpV3;
extern f32 D_cinematic_overlay_800B0940[];
extern u16 D_cinematic_overlay_800B09B4;
extern u16 D_cinematic_overlay_800B09B6;
extern u8 D_cinematic_overlay_800B1910[];
extern void *D_main_bss_80138D1C;
void cpSlot(u8 *, f32 *, f32, f32, s32) __asm__("cinematicSlotUpdate");
void cpTriplet(void *, f32, f32, f32) __asm__("initVec4TripletFromArgs");
void cpQuat(void *, void *, f32) __asm__("quatFromAxisAngleSafe");
void cpCompose(void *, void *) __asm__("composeQuatToMat3x4");
void cpAdd(void *, f32, f32, f32) __asm__("addVec3At0x24");
void cpInv(void *, void *) __asm__("mat3x3InverseInto");
void cpBob(f32 *, void *) __asm__("buildBobbingObjectMatrix");

f32 *cutscenePopulateSlotsFromLevelLists(u8 *arg0, u8 *arg1, u8 arg2, void *mat, f32 t) {
    struct { f32 a18, a1C, a20, a24; f32 q[4]; f32 a38; } L;
    u8 *s1 = arg1 + arg2 * 0x20;
    f32 s;

    cpSlot(arg1 + (*(s32 *)(s1 + 0x1334) * 0xC + 0x25AC), (f32 *)(arg0 + 0x20), t, 8.0f, 1);
    cpSlot(arg1 + (*(s32 *)(s1 + 0x1318) * 0xC + 0x25AC), &D_cinematic_overlay_800B0940[0], t, 8.0f, 0);
    cpSlot(arg1 + (*(s32 *)(s1 + 0x131C) * 0xC + 0x25AC), &D_cinematic_overlay_800B0940[1], t, 8.0f, 0);
    cpSlot(arg1 + (*(s32 *)(s1 + 0x1320) * 0xC + 0x25AC), &D_cinematic_overlay_800B0940[2], t, 8.0f, 0);
    cpSlot(arg1 + (*(s32 *)(s1 + 0x1330) * 0xC + 0x25AC), &L.a38, t, 2.5f, 1);
    cpSlot(arg1 + (*(s32 *)(s1 + 0x1324) * 0xC + 0x25AC), &L.a18, t, 2.5f, 1);
    cpSlot(arg1 + (*(s32 *)(s1 + 0x1328) * 0xC + 0x25AC), &L.a1C, t, 2.5f, 1);
    cpSlot(arg1 + (*(s32 *)(s1 + 0x132C) * 0xC + 0x25AC), &L.a20, t, 2.5f, 1);
    D_cinematic_overlay_800B0940[0] *= 0.25f;
    D_cinematic_overlay_800B0940[1] *= 0.25f;
    D_cinematic_overlay_800B0940[2] *= 0.25f;
    s = (f32)D_cinematic_overlay_800B09B4 / (f32)D_cinematic_overlay_800B09B6;
    cpTriplet(mat, s, s, 1.0f);
    cpQuat(L.q, &L.a18, L.a38);
    cpCompose(mat, L.q);
    cpAdd(mat, D_cinematic_overlay_800B0940[0], D_cinematic_overlay_800B0940[1], D_cinematic_overlay_800B0940[2]);
    {
        u8 *p;
        D_main_bss_80138D1C = p = D_cinematic_overlay_800B1910;
        *(CpV3 *)(p + 0x10) = *(CpV3 *)D_cinematic_overlay_800B0940;
    }
    cpInv(arg0 + 0x2C, mat);
    cpBob(D_cinematic_overlay_800B0940, L.q);
    return D_cinematic_overlay_800B0940;
}

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A52B4);

extern void cinematicSlotUpdate(u8 *, f32 *, f32, f32, s32);
extern f32 D_cinematic_overlay_800B0950[];
struct E5C { u8 p[0x54]; f32 v; u8 q[4]; };
extern struct E5C D_800AF92C[];
extern void setVec3At0x24f(void *, f32, f32, f32) __asm__("setVec3At0x24");
extern void addVec3At0x24(void *, f32, f32, f32);
extern void applyScaleToMat3x4f(void *, f32, f32, f32) __asm__("applyScaleToMat3x4");
extern void composeRotationMatrixSlot1(void *, f32);
extern void quatFromAxisAngleSafe(void *, void *, f32);
extern void composeQuatToMat3x4(void *, void *);
struct C13C { u8 p[2]; u8 t; u8 q[0x139]; };
extern f32 D_cinematic_overlay_800B0B30;
extern u8 D_cinematic_overlay_800A52B4[];

f32 *cinematicSlotDispatcher(u8 *arg0, s32 arg1, void *arg2, f32 arg3) {
    struct { f32 a18, a1C, a20, a24, a28, a2C, a30, a34; f32 q[4]; f32 a48, a4C; } L;
    register void *a2v asm("$20") = arg2;
    s32 off;
    u8 *b;
    f32 sc;
    u8 tv;
    u8 *s1 = arg0 + ((arg1 & 0xFF) * 0x4C + 0x13D8);

    if (s1[0x1F] & 0x40) {
        cinematicSlotUpdate(arg0 + (*(s32 *)(s1 + 0x20) * 0xC + 0x25AC), &D_cinematic_overlay_800B0950[0], arg3, 6.0f, 0);
        cinematicSlotUpdate(arg0 + (*(s32 *)(s1 + 0x24) * 0xC + 0x25AC), &D_cinematic_overlay_800B0950[1], arg3, 6.0f, 0);
        cinematicSlotUpdate(arg0 + (*(s32 *)(s1 + 0x28) * 0xC + 0x25AC), &D_cinematic_overlay_800B0950[2], arg3, 6.0f, 0);
        cinematicSlotUpdate(arg0 + (*(s32 *)(s1 + 0x2C) * 0xC + 0x25AC), &L.a48, arg3, 6.0f, 0);
        cinematicSlotUpdate(arg0 + (*(s32 *)(s1 + 0x40) * 0xC + 0x25AC), &L.a28, arg3, 3.5f, 0);
        cinematicSlotUpdate(arg0 + (*(s32 *)(s1 + 0x44) * 0xC + 0x25AC), &L.a2C, arg3, 3.5f, 0);
        cinematicSlotUpdate(arg0 + (*(s32 *)(s1 + 0x48) * 0xC + 0x25AC), &L.a30, arg3, 3.5f, 0);
        cinematicSlotUpdate(arg0 + (*(s32 *)(s1 + 0x30) * 0xC + 0x25AC), &L.a18, arg3, 3.5f, 1);
        cinematicSlotUpdate(arg0 + (*(s32 *)(s1 + 0x34) * 0xC + 0x25AC), &L.a1C, arg3, 3.5f, 1);
        cinematicSlotUpdate(arg0 + (*(s32 *)(s1 + 0x38) * 0xC + 0x25AC), &L.a20, arg3, 3.5f, 1);
        cinematicSlotUpdate(arg0 + (*(s32 *)(s1 + 0x3C) * 0xC + 0x25AC), &L.a4C, arg3, 3.5f, 1);
    } else {
        D_cinematic_overlay_800B0950[0] = *(f32 *)(s1 + 0x20);
        D_cinematic_overlay_800B0950[1] = *(f32 *)(s1 + 0x24);
        D_cinematic_overlay_800B0950[2] = *(f32 *)(s1 + 0x28);
        L.a48 = *(f32 *)(s1 + 0x2C);
        L.a28 = *(f32 *)(s1 + 0x40);
        L.a2C = *(f32 *)(s1 + 0x44);
        L.a30 = *(f32 *)(s1 + 0x48);
        L.a18 = *(f32 *)(s1 + 0x30);
        L.a1C = *(f32 *)(s1 + 0x34);
        L.a20 = *(f32 *)(s1 + 0x38);
        L.a4C = *(f32 *)(s1 + 0x3C);
    }
    D_cinematic_overlay_800B0950[0] *= 0.25f;
    D_cinematic_overlay_800B0950[1] *= 0.25f;
    D_cinematic_overlay_800B0950[2] *= 0.25f;
    L.a28 *= 0.25f;
    L.a2C *= 0.25f;
    L.a30 *= 0.25f;
    if (s1[0x1F] & 0x80) {
        if (!(bytesDiffer(s1, D_cinematic_overlay_800A52B4, 2) & 0xFF)) {
            L.a48 = D_800AF92C[((struct C13C *)D_cinematic_overlay_800B1900)[arg1 & 0xFF].t].v;
        } else {
            f32 t = L.a48 * 0.22222222f;
            f32 u = D_800AF92C[((struct C13C *)D_cinematic_overlay_800B1900)[arg1 & 0xFF].t].v;
            L.a48 = t;
            if (u != 0.0f) {
                L.a48 = t * u;
            }
        }
    } else {
        L.a48 = 1.0f;
    }
    off = arg1 & 0xFF;
    b = (u8 *)D_cinematic_overlay_800B1900;
    off *= 0x13C;
    *(f32 *)(off + (s32)b + 0x64) = L.a48;
    setVec3At0x24f(a2v, -L.a28, -L.a2C, -L.a30);
    tv = ((u8 *)D_cinematic_overlay_800B1900)[off + 2];
    if (tv == 0x1A) goto rot;
    if (tv == 0x1B) {
rot:
        {
        composeRotationMatrixSlot1(a2v, 180.0f);
        }
    }
    quatFromAxisAngleSafe(L.q, &L.a18, L.a4C);
    composeQuatToMat3x4(a2v, L.q);
    sc = L.a48;
    applyScaleToMat3x4f(a2v, sc, sc, sc);
    if (((u8 *)D_cinematic_overlay_800B1900)[(arg1 & 0xFF) * 0x13C + 2] == 0x1B) {
        applyScaleToMat3x4f(a2v, D_cinematic_overlay_800B0B30, D_cinematic_overlay_800B0B30, D_cinematic_overlay_800B0B30);
    }
    addVec3At0x24(a2v, L.a28 + D_cinematic_overlay_800B0950[0], L.a2C + D_cinematic_overlay_800B0950[1], L.a30 + D_cinematic_overlay_800B0950[2]);
    return D_cinematic_overlay_800B0950;
}

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", spawnCutsceneObjectsFromList);

typedef struct CdNode { struct CdNode *next; struct CdNode *prev; struct CdNode *parent; struct CdNode *child; } CdNode;
typedef struct { u8 pad0[0x44]; f32 f44; } CdMesh;
typedef struct { CdMesh *mesh; u8 pad4[8]; CdNode node; } CdObj;
typedef struct { u8 pad0[0xC]; f32 x; f32 z; } CdOff;
extern CdOff D_800B04AC[];
extern u8 D_cinematic_overlay_800B09C4[];
void advanceNpcOnCurvedPath(void *, void *, f32 *, s32);
s32 transformVec3ToNpcLocalWithScale(void *, void *, void *, f32, void *);
f32 floatModulo(f32, f32);
void seekAllModelAnimChannelsInSlotToTime(s32, f32);
void parseModelAnimType2Entry(s32);
void updateAnimatedTextureStreaming(s32, Vec3f *, f32);
void walkDatTreeAndScaleLeafByFloat(void *, void *, f32);
void walkDatTreeAndVisitChildren(void *, void *, void *);

#define CD_SLOT(o) ((u8 *)(i * 0x13C + (s32)D_cinematic_overlay_800B1900))

static __inline__ void cdLink(CdNode *n, CdNode *par) {
    CdNode *t2;

    n->parent = par;
    t2 = par->child;
    if (t2 == NULL) {
        par->child = n;
        n->prev = NULL;
        n->next = NULL;
    } else {
        while (t2->next != NULL) {
            t2 = t2->next;
        }
        t2->next = n;
        n->prev = t2;
    }
}

void cutsceneDispatchSlotsByFlag(CdNode **root, u8 *scene, f32 t, f32 scale) {
    f32 m[12];
    u8 sp48[8];
    u32 i;
    s32 o;
    u8 *f;
    u8 *s;
    s32 hi;

    for (i = 0; i < *(u16 *)(scene + 0x4A); i++) {
        hi = 0x80;
        if ((scene[i * 0x4C + 0x13F7] & 0x80) == hi) {
            cinematicSlotDispatcher(scene, (u8)i, (u8 *)((CdObj *)*(void **)(CD_SLOT(o) + 0x50)) + 0x28, t);
        } else {
            cinematicSlotDispatcher(scene, (u8)i, (u8 *)D_cinematic_overlay_800B1900 + i * 0x13C + 0x20, t);
        }
    }
    initCutsceneScene(scene);
    __asm__("" :: "r"(root));
    __asm__("" :: "r"(root));
    {
        typedef struct { u8 pad0[4]; s32 x4; s32 x8; s32 xC; s32 x10; u8 pad14[0x3C]; CdObj *obj; u8 pad54[0xE8]; } CdSl;
        for (i = 0; i < *(u16 *)(scene + 0x4A); i++) {
            CdObj *obj = ((CdSl *)D_cinematic_overlay_800B1900)[i].obj;
            if (obj != NULL) {
                obj->node.prev = NULL;
                obj->node.next = NULL;
                obj->node.parent = NULL;
            } else {
                ((CdSl *)D_cinematic_overlay_800B1900)[i].x10 = 0;
                ((CdSl *)D_cinematic_overlay_800B1900)[i].x8 = 0;
                ((CdSl *)D_cinematic_overlay_800B1900)[i].x4 = 0;
                ((CdSl *)D_cinematic_overlay_800B1900)[i].xC = 0;
            }
        }
    }
    for (i = 0; i < *(u16 *)(scene + 0x4A); i++) {
        u8 fl = scene[i * 0x4C + 0x13F7];
        u32 p;
        if (fl & 0x80) {
            if ((fl & 0x3F) == 0x3F) {
                u8 *sl = CD_SLOT(o);
                CdObj *ob0 = *(CdObj **)(sl + 0x50);
                CdNode *r = *root;
                ob0->node.next = r;
                if (r != NULL) {
                    (*(CdObj **)(sl + 0x50))->node.next->prev = &(*(CdObj **)(sl + 0x50))->node;
                }
                (*(CdObj **)(CD_SLOT(o) + 0x50))->node.prev = NULL;
                *root = &(*(CdObj **)(CD_SLOT(o) + 0x50))->node;
            } else {
                CdNode *par = (CdNode *)((fl & 0x3F) * 0x13C + (s32)D_cinematic_overlay_800B1900 + 4);
                CdObj *ob = *(CdObj **)(CD_SLOT(o) + 0x50);
                CdNode *n = &ob->node;
                CdNode *t2;
                n->parent = par;
                t2 = par->child;
                if (t2 == NULL) {
                    par->child = n;
                    n->prev = NULL;
                    ob->node.next = NULL;
                } else {
                    while (t2->next != NULL) {
                        t2 = t2->next;
                    }
                    t2->next = n;
                    n->prev = t2;
                }
            }
            if ((*(u32 *)CD_SLOT(o) & 0xFF000004) == 4) {
                extractOrthonormalFrameFromStruct(m, CD_SLOT(o) + 0x88);
                {
                    u8 *sl = CD_SLOT(o);
                    m[0] += D_800B04AC[sl[2]].x;
                    m[2] += D_800B04AC[sl[2]].z;
                    advanceNpcOnCurvedPath(D_cinematic_overlay_800B09C4, root, m, *(s32 *)(sl + 0x6C));
                }
            }
        } else {
            p = fl & 0x3F;
            if (p == 0x3F) {
                u8 *sl = CD_SLOT(o);
                CdNode *r = *root;
                ((CdNode *)(sl + 4))->next = r;
                sl += 4;
                if (r != NULL) {
                    r->prev = (CdNode *)sl;
                }
                sl = CD_SLOT(o) + 4;
                ((CdNode *)sl)->prev = NULL;
                *root = (CdNode *)sl;
            } else {
                cdLink((CdNode *)(CD_SLOT(o) + 4), (CdNode *)(p * 0x13C + (s32)D_cinematic_overlay_800B1900 + 4));
            }
        }
    }
    for (i = 0; i < *(u16 *)(scene + 0x4A); i++) {
        if (scene[i * 0x4C + 0x13F7] & 0x80) {
            u8 *sl = CD_SLOT(o);
            if (!(u8)transformVec3ToNpcLocalWithScale(root, (u8 *)root + 0x2C, sl + 0x70, (*(CdObj **)(sl + 0x50))->mesh->f44 * *(f32 *)(sl + 0x64), sp48) || *CD_SLOT(o) != 0) {
                CdObj *ob = *(CdObj **)(CD_SLOT(o) + 0x50);
                CdNode *n = &ob->node;
                CdNode *t2 = *root;
                CdNode *par;
                if (t2 == n) {
                    *root = ob->node.next;
                    continue;
                }
                if (t2 != NULL) {
                    do {
                        if (t2 == n) {
                            goto unlink;
                        }
                        t2 = t2->next;
                    } while (t2 != NULL);
                }
                par = n->parent;
                if (par->child == n) {
                    par->child = n->next;
                    continue;
                }
                t2 = par->child;
                if (t2 != NULL) {
                    do {
                        if (t2 == n) {
                        unlink:
                            if (t2->prev != NULL) {
                                t2->prev->next = t2->next;
                            }
                            if (t2->next != NULL) {
                                t2->next->prev = t2->prev;
                            }
                            break;
                        }
                        t2 = t2->next;
                    } while (t2 != NULL);
                }
            } else {
                if (*(s32 *)(CD_SLOT(o) + 0x58) != 0xFFFF) {
                    seekAllModelAnimChannelsInSlotToTime(*(s32 *)(CD_SLOT(o) + 0x58), floatModulo(t * *(f32 *)(CD_SLOT(o) + 0x68), 1.0f));
                    parseModelAnimType2Entry(*(s32 *)(CD_SLOT(o) + 0x58));
                }
                if (CD_SLOT(o)[3] & 1) {
                    updateAnimatedTextureStreaming(*(s32 *)(CD_SLOT(o) + 0x60), D_cinematic_overlay_800B1A08, 6.0f);
                }
                if (*(s32 *)(CD_SLOT(o) + 0x54) == 0 && CD_SLOT(o)[0x104] != 0xFF) {
                    walkDatTreeAndScaleLeafByFloat(CD_SLOT(o) + 0x104, *(void **)(CD_SLOT(o) + 0x50), scale);
                    walkDatTreeAndVisitChildren((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C + 0x104, *(void **)((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C + 0x50), &D_cinematic_overlay_800B0A00);
                }
            }
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A52F0);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A52FC);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_800A5300);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", strCinRedbox1);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_800A5308);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_800A530C);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5310);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5320);

typedef struct {
    s32 type;
    u32 time;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} ScEv;

typedef struct {
    u8 pad0[0x4A];
    u16 nSlots;
    u16 pad4C;
    u16 nEv;
    f32 f50;
    f32 f54;
    ScEv ev[1];
} ScFile;

typedef struct { u8 r, g, b, a; } ScCol;
typedef struct { f32 v[3]; } ScV3;
typedef struct { s32 k[4]; } ScKw;

extern u8 *scSlots __asm__("D_cinematic_overlay_800B1900");
extern ScV3 scTplV __asm__("D_cinematic_overlay_800A52F0");
extern ScCol scTplCol __asm__("D_cinematic_overlay_800A52FC");
extern ScKw scTplKw __asm__("D_cinematic_overlay_800A5310");
extern ScV3 scTplV2 __asm__("D_cinematic_overlay_800A5320");
extern u16 scSpeechKeys[] __asm__("D_cinematic_overlay_800AF6E8");
extern u16 scVoiceBank __asm__("D_cinematic_overlay_800AF6BE");
extern s32 scAF6BC __asm__("D_cinematic_overlay_800AF6BC");
extern u8 scSongVol __asm__("D_cinematic_overlay_800B1A30");
extern u8 scB09B0 __asm__("D_cinematic_overlay_800B09B0");
extern u8 scB0B1C __asm__("D_cinematic_overlay_800B0B1C");
extern u8 scB0B14 __asm__("D_cinematic_overlay_800B0B14");
extern u16 scB0B24 __asm__("D_cinematic_overlay_800B0B24");

void scPlaySpeech(s32, s32, s32, s32) __asm__("playSpeechClip");
s32 scBsearch(u16, s32, s32) __asm__("bsearchFactor5TableByU16Key");
void scType0xA(u8 *, f32) __asm__("spawnNpcType0xAFromTemplate");
void scByteAnim(u8 *) __asm__("spawnByteAnimDebrisDefault");
void scParticle(u8 *, u16, f32, s32) __asm__("spawnRandomParticleWithParent");
void scOriented(s32, u8 *, f32 *, ScCol *, f32, f32, f32, f32) __asm__("spawnOrientedNpc");
void scRandRot(f32 *, f32 *, f32, s32, s32, s32) __asm__("composeRandomRotationMatrix");
void scScaleRand(f32 *, f32, f32) __asm__("scaleVec3ByRandomRange");
s16 scRand(void) __asm__("rand");
void scDebris1(u8 *, f32 *, f32, f32, f32) __asm__("spawnDebris1Npc");
void scSpray(u8 *, f32, f32, f32, f32, f32) __asm__("spawnWaterSprayDebrisAndBurst");
void scDespawn(u8) __asm__("despawnCutsceneNpcSlot");
u16 scLookupId(s32) __asm__("lookupCutsceneIdMapping");
s32 scFindChan(s32) __asm__("findAudioChannelById");
s32 scPlaySong(u16, s32, s32, s32) __asm__("playSongById");
void scQueueVoice(s32, u16, s32, s32) __asm__("queueAudioVoiceCmd");
void scFrame(f32 *, u8 *) __asm__("extractOrthonormalFrameFromStruct");
void scCue(s32, u16, f32 *, f32 *, s32, f32, f32) __asm__("dispatchCueByCategory");
u8 scMatchKw(s32, s32, s32) __asm__("matchKeywordWithPriority");
s32 scHmtByName(s32, s32, s32, f32 *, s32, s32) __asm__("lookupHmtTextureByName");
void scNormalize(f32 *) __asm__("normalize_vector");
void scSchedule(u16, f32, f32, f32) __asm__("scheduleCutsceneActionSlot");
void scStopVoice(s32) __asm__("stopVoiceByHandleLocked");
void scSimpleAudio(u8, u16, s32) __asm__("playSimpleAudioCmd");
void scDebrisField(ScEv *) __asm__("spawnCutsceneDebrisField");
void scBurst(u8, u8, f32 *, f32 *) __asm__("spawnNpcBurstAlongSegment");
void scBounds2(f32, f32) __asm__("setGridLayerScrollBounds");
void scDestroyChain(s32) __asm__("destroyAllNpcsInSlotChain");

#define SC_SLOT(i) (scSlots + (i) * 0x13C)
#define SC_B(e, o) (*(u8 *)((u8 *)(e) + (o)))
#define SC_H(e, o) (*(u16 *)((u8 *)(e) + (o)))

u8 spawnCutsceneEffectsAndCues(ScFile *cf, u32 time, u8 arg2, f32 arg3, u8 arg4) {
    f32 v20[4];
    ScCol col;
    f32 q38[4];
    f32 dir[4];
    s32 kw[4];
    f32 v68[4];
    f32 m[12];
    u8 ret;
    ScEv *e;
    f32 f;
    f32 a;
    f32 b;
    u32 i;
    s32 k;
    s32 h;
    u16 id;
    u16 mapped;

    *(ScV3 *)v20 = scTplV;
    col = scTplCol;
    ret = arg2;
    while (D_cinematic_overlay_800B0B20 < 200) {
        if (time < cf->ev[D_cinematic_overlay_800B0B20].time) {
            break;
        }
        e = &cf->ev[D_cinematic_overlay_800B0B20];
        switch (e->type) {
            case 0:
                if (arg4 == 0) {
                    scPlaySpeech(e->a, e->b ? SC_B(e, 0xF) : 0x7F, 0, 3);
                }
                break;
            case 4:
                ret = SC_B(e, 0xB);
                scB09B0 = 3;
                break;
            case 3:
                if (arg4 == 0) {
                    e->d &= 3;
                    D_cinematic_overlay_800B1A20[e->d] = scBsearch(scSpeechKeys[e->a], e->b ? SC_B(e, 0xF) : 0x7F, e->c ? SC_B(e, 0x13) : 0x40);
                }
                break;
            case 5:
                if (e->b != 0) {
                    f = (f32)(u32)e->b / 500.0f;
                } else {
                    f = 1.0f;
                }
                switch (e->c) {
                    case 0:
                        scType0xA(SC_SLOT(e->a) + 0x70, f);
                        scByteAnim(SC_SLOT(e->a) + 0x70);
                        break;
                    case 1:
                        scParticle(SC_SLOT(e->a) + 0x70, 0xFFFF, f, 0);
                        break;
                    case 2:
                        scOriented(0, SC_SLOT(e->a) + 0x70, v20, &col, 0.5f, f, 1.5f, 0.7f);
                        f *= 0.9f;
                        scOriented(0, SC_SLOT(e->a) + 0x70, v20, &col, 0.5f, f, 1.5f, 1.4f);
                        f *= 0.9f;
                        scOriented(0, SC_SLOT(e->a) + 0x70, v20, &col, 0.5f, f, 1.5f, 2.1f);
                        break;
                    case 3:
                        for (i = 0, k = 0; i < 8; i++) {
                            scRandRot(q38, dir, 1.0f, 15, 75, k);
                            k += 45;
                            scScaleRand(dir, 0.3f, 0.8f);
                            a = ((scRand() & 0x7F) - 64.0f) / 12.8f + 14.0f;
                            b = ((scRand() & 0x7F) - 64.0f) * 0.00390625f + 0.7f;
                            scDebris1(SC_SLOT(e->a) + 0x70, dir, a, b, 0.8f);
                        }
                        break;
                    case 4:
                        scSpray(SC_SLOT(e->a) + 0x70, f / 10.0f, f, f / 10.0f, f, 1.0f);
                        break;
                }
                break;
            case 7:
                *SC_SLOT(e->a) = 1;
                if ((u32)e->a < cf->nSlots) {
                    scDespawn(SC_B(e, 0xB));
                }
                break;
            case 6:
                *SC_SLOT(e->a) = 0;
                break;
            case 1:
                e->c &= 3;
                h = D_cinematic_overlay_800B1A10[e->c];
                if (h == -1) {
                    id = gCutsceneIdMappingTable[e->a].unk0;
                    mapped = scLookupId(id);
                    {
                    s32 r = scPlaySong(mapped, id, scFindChan(id), 0);
                    if (r != h) {
                        D_cinematic_overlay_800B1A10[e->c] = r;
                        scQueueVoice(e->b ? SC_B(e, 0xF) : 0x7F, scVoiceBank, D_cinematic_overlay_800B1A10[e->c], 0);
                        scSongVol = e->b ? SC_B(e, 0xF) : 0x7F;
                    }
                    }
                }
                break;
            case 2:
                e->a &= 3;
                {
                s32 hv = D_cinematic_overlay_800B1A10[e->a];
                if (hv != -1) {
                    scQueueVoice(0, scVoiceBank, hv, 1);
                    D_cinematic_overlay_800B1A10[e->a] = -1;
                }
                }
                break;
            case 8:
                if ((u32)e->b < 15) {
                    *(ScKw *)kw = scTplKw;
                    *(ScV3 *)v68 = scTplV2;
                    if (*(s32 *)(SC_SLOT(e->a) + 0x50) != 0) {
                        if (e->c != 0) {
                            f = (f32)(u32)e->c / 10.0f;
                        } else {
                            f = 2.5f;
                        }
                        if (e->b == 13) {
                            scFrame(m, SC_SLOT(e->a) + 0x88);
                            m[9] = 0.0f;
                            m[10] = 0.0f;
                            m[11] = 0.0f;
                            m[0] += m[9];
                            m[1] += 0.1f;
                            m[2] += m[9];
                            scCue(e->b, 0xFFFF, m, v68, 1, f, 1.0f);
                        } else {
                            if (gCurrentLevel == 19) {
                                v68[0] += v68[0];
                                v68[1] += v68[1];
                                v68[2] += v68[2];
                            }
                            for (i = 0; i < 8; i++) {
                                if (scMatchKw(*(s32 *)(SC_SLOT(e->a) + 0x50), kw[i >> 1], i & 1) != 0) {
                                    if (scHmtByName(*(s32 *)(SC_SLOT(e->a) + 0x50), kw[i >> 1], i & 1, m, 0, 0) != 0) {
                                        m[9] = 0.0f;
                                        m[10] = 0.0f;
                                        m[11] = 0.0f;
                                        if (SC_SLOT(e->a)[2] == 11) {
                                            m[4] = 0.5f;
                                            scNormalize(&m[3]);
                                        }
                                        scCue(e->b, 0xFFFF, m, v68, 1, f, 1.0f);
                                    }
                                }
                            }
                        }
                        if (e->d != 0) {
                            scBsearch(SC_H(e, 0x16), 0x7F, 0x40);
                        }
                    }
                }
                break;
            case 9:
                scAF6BC = e->a;
                break;
            case 10:
                scB0B1C = 1;
                break;
            case 11:
                if (e->c != 0) {
                    scSchedule(SC_H(e, 0xA), (f32)(u32)e->b, arg3, (f32)(time + e->c) / (cf->f54 * cf->f50));
                }
                break;
            case 12:
                {
                s32 hs = D_cinematic_overlay_800B1A20[e->a];
                if (hs != -1) {
                    scStopVoice(hs);
                    D_cinematic_overlay_800B1A20[e->a] = -1;
                }
                }
                break;
            case 13:
                *(f32 *)(SC_SLOT(e->a) + 0x68) = (f32)(u32)e->b / 10.0f;
                break;
            case 14:
                scSimpleAudio(SC_B(e, 0xB), SC_H(e, 0xE), 0xFD);
                break;
            case 15:
                scDebrisField(e);
                break;
            case 16:
                scBurst(SC_B(e, 0xB), SC_B(e, 0xF), NULL, NULL);
                break;
            case 17:
                scBounds2((f32)(u32)e->a, (f32)(u32)e->b);
                break;
            case 19:
                D_cinematic_overlay_800B0B22 = SC_H(e, 0xA);
                break;
            case 20:
                scDestroyChain(3);
                break;
            case 21:
                scB0B24 = SC_H(e, 0xA);
                break;
            case 22:
                scB0B14 = e->a != 0;
                break;
        }
        if (++D_cinematic_overlay_800B0B20 == cf->nEv) {
            break;
        }
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", initCutsceneAudioChannels);

struct M12 { f32 f[12]; };
void clearVec4QuadStruct(void *);
void mat3x4Multiply(Mat4x3, Mat4x3, Mat4x3);

void initCutsceneScene(u8 *arg0) {
    s32 sp10[8];
    struct M12 sp30;
    s16 i;
    s16 s0;
    s16 s1;
    u8 *node;
    u8 *a1;
    u8 *base;

    i = 0;
    if (*(u16 *)(arg0 + 0x4A) != 0) {
        do {
            u8 *q = arg0 + i * 0x4C;
            if (!(q[0x13F7] & 0x80)) {
                base = (u8 *)(i * 0x13C + (s32)D_cinematic_overlay_800B1900);
                *(s32 *)(base + 0x70) = 0;
                *(s32 *)(base + 0x74) = 0;
                *(s32 *)(base + 0x78) = 0;
                clearVec4QuadStruct((void *)(base + 0x88));
            } else {
                node = *(u8 **)((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C + 0x50);
                s0 = 0;
                a1 = node + 0xC;
                __asm__("" :: "r"(s0));
                sp10[0] = (s32)(node + 0x28);
                for (; *(u8 **)(a1 + 8) != 0; ) {
                    s32 *p = sp10;
                    s0++;
                    a1 = *(u8 **)(a1 + 8);
                    *(s32 *)((s32)p + (s0 << 2)) = (s32)(a1 + 0x1C);
                }
                clearVec4QuadStruct((void *)((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C + 0x88));
                s1 = s0;
                while (s1 >= 0) {
                    sp30 = *(struct M12 *)((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C + 0x88);
                    mat3x4Multiply((void *)&sp30, (void *)sp10[s1], (void *)((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C + 0x88));
                    s1--;
                }
                base = (u8 *)(i * 0x13C + (s32)D_cinematic_overlay_800B1900);
                *(f32 *)(base + 0x70) = *(f32 *)(base + 0xAC);
                *(f32 *)(base + 0x74) = *(f32 *)(base + 0xB0);
                *(f32 *)(base + 0x78) = *(f32 *)(base + 0xB4);
            }
            i++;
        } while (i < *(u16 *)(arg0 + 0x4A));
    }
}

typedef struct {
    u8 p0[0x12];
    u16 f12;
    u16 f14;
    u16 f16;
    u8 f18;
    u8 p19[3];
    s32 f1C;
    u8 f20;
    u8 f21;
    u8 f22;
    u8 p23;
    u8 p24[4];
    s32 f28;
    u8 p2C[4];
    s32 f30;
    s32 f34;
    s32 f38;
    u16 f3C;
    u16 f3E;
    u16 f40;
    u16 f42;
    s32 f44;
    u8 p48[8];
} IsBoot;
typedef struct {
    u16 a;
    u16 b;
    u16 c;
    u16 d;
} IsCam;
typedef struct {
    u8 p0[4];
    s32 f4;
    s32 f8;
    s32 fC;
    u32 f10;
    u32 f14;
    u32 f18;
    u32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
} IsOut;
extern IsBoot isBc __asm__("gBootConfig");
extern struct { u8 p[0x10]; u32 f10; u8 p14[0xF]; u8 b23; } isGs __asm__("gGameSettings");
extern u8 isSave[] __asm__("D_cinematic_overlay_800B0960");
extern u16 isW __asm__("D_cinematic_overlay_800B09B2");
extern u16 isH __asm__("D_cinematic_overlay_800B09B4");
extern u16 isTot __asm__("D_cinematic_overlay_800B09B6");
extern u16 isTop __asm__("D_cinematic_overlay_800B09B8");
extern IsCam isCams[][20] __asm__("D_800B072C");
extern s32 isManifest __asm__("D_main_bss_80137CFC");
extern s32 isSlotA __asm__("D_cinematic_overlay_800B0AFC");
extern s32 isSlotB __asm__("D_cinematic_overlay_800B0B00");
void isZmemcpy(void *, void *, u32) __asm__("zmemcpy");
void isVidTick(void *, void *, void *) __asm__("runVideoFrameTick");
s32 isFindMan(char *) __asm__("findManifestEntryByName");
void isClearBss(s32) __asm__("clearSceneBssRegion");
void isInitSlots(void) __asm__("initNpcSlotList");
void isAllocCtx(void) __asm__("allocNpcContextArrays");
void isAllocNpcs(void) __asm__("allocAllInitialNpcSlots");
void isLoadSnd(void) __asm__("loadSndFiles");
void isLoadTxt(char *) __asm__("loadGameOrFrontTxtFile");
void isInitVoice(void) __asm__("initVoiceSubtitleSystem");
void isSubPos(s32, s32) __asm__("setSubtitleOverlayScreenPos");
void isPreset(s32) __asm__("selectRenderPresetByIndex");
s32 isAllocSlots(s32) __asm__("allocateSlotTable");

void initSceneForMission(IsOut *out, u8 level, u8 craft) {
    IsCam *e;
    s32 h;
    s32 top;
    u16 tot;
    s32 av;

    isZmemcpy(isSave, &isBc, 0x50);
    isW = 0x280;
    isH = 0xAA;
    isTop = 0x23;
    if (level == 0x13) {
        isH = 0xE0;
        isTop = 8;
    }
    if (isGs.f10 & 1) {
        isH = 0x154;
        isTop = isTop * 2;
    }
    isBc.f16 = 0x10;
    isBc.f20 = 0x10;
    isBc.f21 = 0xE;
    isBc.f22 = 7;
    isBc.f1C = 0x5622;
    isBc.f12 = 0x280;
    isBc.f18 = 2;
    top = isTop;
    h = isH;
    isBc.f40 = top;
    isBc.f42 = top;
    isBc.f14 = h;
    tot = h + top * 2;
    {
        s32 big = tot >= 0xF1;
        isBc.f44 = big << 6;
    }
    {
        s32 cb = (s32)isCams;
        e = (IsCam *)((level * 8 + craft * 0xA0) + cb);
    }
    isBc.f34 = e->d << 10;
    isBc.f38 = e->b << 10;
    isBc.f30 = e->c << 10;
    av = e->a;
    isBc.f3E = av;
    isTot = tot;
    if (isGs.b23 != 0) {
        isBc.f34 += 0x20000;
        isBc.f38 += 0x80000;
        isBc.f30 += 0x20000;
        isBc.f3E = 0x800;
        isBc.f3C = 0x800;
        isBc.f28 |= 0x40000;
    }
    isVidTick((u8 *)&isBc + 0x10, (u8 *)&isBc + 0x2C, (u8 *)&isBc + 0x1C);
    isManifest = isFindMan("data");
    isClearBss(2);
    isInitSlots();
    isAllocCtx();
    isAllocNpcs();
    isLoadSnd();
    isLoadTxt("game_TXT");
    isInitVoice();
    isSubPos(0, -4);
    out->f4 = 0;
    out->f8 = 0;
    out->fC = 0;
    out->f10 = isW;
    out->f14 = isH;
    out->f18 = isW >> 1;
    out->f1C = isH >> 1;
    out->f20 = 65.0f;
    out->f24 = 0.1171875f;
    out->f28 = 93.75f;
    isPreset(1);
    isSlotA = isAllocSlots(4);
    isSlotB = isAllocSlots(4);
}

struct V3 { s32 a, b, c; };
extern void *rs_memset(void *, s32, s32);
extern void play3DSoundEventP(void *, void *, void *, f32, f32, s32, s32, s32, s32) __asm__("play3DSoundEvent");
extern void play3DSoundEventVariantP(void *, void *, void *, f32, f32, s32, s32, s32, s32, s32) __asm__("play3DSoundEventVariant");
extern void register3DAudioListenerNodeP(void *, void *, void *, void *, void *, f32, f32, f32, s32, s32) __asm__("register3DAudioListenerNode");
extern u8 D_cinematic_overlay_800B1A50[];
extern s32 D_cinematic_overlay_800B1A40[];

void emit3DSoundsForActiveNpcs(u8 *arg0, f32 *arg1) {
    f32 sp28[3];
    f32 sp38[3];
    f32 sp48[3];
    s32 sp58[3];
    u32 i;
    u8 *p;
    s32 q;

    rs_memset(sp58, 0, 0xC);
    for (i = 0; i < *(u16 *)(arg0 + 0x4A); i++) {
        {
            p = (u8 *)(i * 0x13C + (s32)D_cinematic_overlay_800B1900);
            if (p[3] & 2) {
                p[0x100] = 0;
                switch (((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C)[2]) {
                case 0:
                    play3DSoundEventP((void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0xBC), (void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0x70), sp58, 10.0f, 0.3f, 0xF, 0xF, 0x78, 0);
                    ((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C)[0x100] = 0x5A;
                    break;
                case 4:
                    play3DSoundEventP((void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0xBC), (void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0x70), sp58, 10.0f, 0.0f, 0xF, 0x13, 0x78, 0);
                    ((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C)[0x100] = 0x5A;
                    break;
                case 1:
                    play3DSoundEventP((void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0xBC), (void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0x70), sp58, 10.0f, 0.3f, 0xF, 0x12, 0x78, 0);
                    ((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C)[0x100] = 0x64;
                    break;
                case 2:
                    play3DSoundEventP((void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0xBC), (void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0x70), sp58, 10.0f, 0.5f, 0xF, 0xE, 0x78, 0);
                    ((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C)[0x100] = 0x64;
                    break;
                case 3:
                    play3DSoundEventP((void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0xBC), (void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0x70), sp58, 10.0f, 0.3f, 0xF, 0x11, 0x78, 0);
                    ((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C)[0x100] = 0x64;
                    break;
                case 5:
                    play3DSoundEventP((void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0xBC), (void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0x70), sp58, 12.0f, 0.6f, 0xF, 0x2E, 0x78, 0);
                    ((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C)[0x100] = 0x78;
                    break;
                case 6:
                    play3DSoundEventP((void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0xBC), (void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0x70), sp58, 10.0f, 0.7f, 0xF, 0x6F, 0x5A, 0);
                    ((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C)[0x100] = 0x6E;
                    break;
                case 7:
                case 8:
                case 9:
                case 10:
                    play3DSoundEventVariantP((void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0xBC), (void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0x70), sp58, 21.0f, 0.6f, 0xF, 7, 1, 0x7F, 0x28);
                    ((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C)[0x100] = 0x7F;
                    break;
                case 15:
                case 16:
                case 17:
                    play3DSoundEventVariantP((void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0xBC), (void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0x70), sp58, 10.0f, 0.4f, 0xF, 0x39, 1, 0x5A, 0x28);
                    ((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C)[0x100] = 0x78;
                    break;
                case 14:
                    play3DSoundEventVariantP((void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0xBC), (void *)((s32)D_cinematic_overlay_800B1900 + i * 0x13C + 0x70), sp58, 34.0f, 0.8f, 0xF, 0x38, 1, 0x7F, 0x50);
                    ((u8 *)D_cinematic_overlay_800B1900 + i * 0x13C)[0x100] = 0x7F;
                    break;
                }
            }
        }
    }
    sp28[0] = arg1[9];
    sp28[1] = arg1[10];
    sp28[2] = arg1[11];
    sp38[0] = arg1[2];
    sp38[1] = arg1[5];
    sp38[2] = arg1[8];
    sp48[0] = -arg1[1];
    sp48[1] = -arg1[4];
    sp48[2] = -arg1[7];
    register3DAudioListenerNodeP(D_cinematic_overlay_800B1A50, sp28, sp38, sp38, sp48, 2.0f, 2.0f, 50.0f, 1, 0x7F);
    *(struct V3 *)D_cinematic_overlay_800B1A40 = *(struct V3 *)sp28;
}

typedef struct { f32 x, y, z; } PaV3;
typedef struct {
    u8 b0;
    u8 pad1[2];
    u8 b3;
    u8 pad4[0x6C];
    PaV3 v70;
    PaV3 v7C;
    u8 pad88[0x34];
    u8 aBC[0x44];
    u8 b100;
    u8 pad101[0x3B];
} PaSlot;

extern PaV3 paPrev __asm__("D_cinematic_overlay_800B1A40");
extern f32 vec3Length(void *);
s32 setMusyX3DProperties(void *, void *, void *, void *, void *, s32);
void updateActive3DAudioSource(void *, void *, void *, s32);

#define PA_SLOT(i) (((PaSlot *)D_cinematic_overlay_800B1900)[i])

void updatePositionalAudioSource(u8 *sc, f32 *m, f32 dt) {
    PaV3 pos;
    f32 up[3];
    f32 fw[3];
    PaV3 vel;
    PaV3 d;
    f32 len;
    u16 i;

    pos.x = m[9];
    pos.y = m[10];
    pos.z = m[11];
    if (dt > 0.0f) {
        vel.x = (pos.x - paPrev.x) / dt;
        vel.y = (pos.y - paPrev.y) / dt;
        vel.z = (pos.z - paPrev.z) / dt;
    } else {
        vel.x = 0.0f;
        vel.y = 0.0f;
        vel.z = 0.0f;
    }
    paPrev = pos;
    len = vec3Length(&vel);
    if (len > 50.0f) {
        f32 s = 50.0f / (len * 1.5f);
        f32 x = vel.x * s;
        f32 z = vel.z * s;
        f32 y = vel.y * s;
        vel.x = x;
        vel.y = y;
        vel.z = z;
    }
    up[0] = m[2];
    up[1] = m[5];
    up[2] = m[8];
    fw[0] = -m[1];
    fw[1] = -m[4];
    fw[2] = -m[7];
    setMusyX3DProperties(D_cinematic_overlay_800B1A50, &pos, &vel, up, fw, 0x7F);
    for (i = 0; i < *(u16 *)(sc + 0x4A); i++) {
        if (PA_SLOT(i).b3 & 2) {
            f32 f;
            if (PA_SLOT(i).b0 != 1) {
                f = PA_SLOT(i).b100;
            } else {
                f = 0.0f;
            }
            {
                PaSlot *sl = (PaSlot *)(i * sizeof(PaSlot) + (s32)D_cinematic_overlay_800B1900);
                PaV3 *a = &sl->v70;
                PaV3 *b = &sl->v7C;
                d.x = a->x - b->x;
                d.y = a->y - b->y;
                d.z = a->z - b->z;
                if (dt > 0.0f) {
                    f32 k = 1.0f / dt;
                    d.x = d.x * k;
                    d.y = d.y * k;
                    d.z = d.z * k;
                }
                updateActive3DAudioSource(sl->aBC, a, &d, (u8)(u32)f);
            }
            PA_SLOT(i).v7C = PA_SLOT(i).v70;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A54A8);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A54B4);

extern u8 D_cinematic_overlay_800A54A8[];
extern u8 D_cinematic_overlay_800A54B4[];
extern s32 lookupHmtMaterialByName(s32, u8 *, s32 *);
extern void composeInterpolatedNodeMatricesAltCall(s32, s32, s32, s32, f32) __asm__("composeInterpolatedNodeMatricesAlt");

void applyCutsceneSlotMaterialOverrides(void) {
    s32 sp18;
    s32 sp1C;
    u32 val;
    s32 off = 0;
    s32 m1;
    u8 *slot;
    u8 st;
    u16 i;
    f32 fv;

    for (i = 0; i < D_cinematic_overlay_800B1904->unk0058_active_count; i++) {
        {
            if (D_cinematic_overlay_800B1904->unk0058[i].sub_type == 0xB &&
                D_cinematic_overlay_800B1904->unk0058[i].unk04 == 0 &&
                D_cinematic_overlay_800B1904->unk0058[i].unk10 == 0) {
                off = *(u16 *)((u8 *)&D_cinematic_overlay_800B1904->unk0058[i] + 0xA) * 0x13C;
                slot = (u8 *)(off + (s32)D_cinematic_overlay_800B1900);
                switch (slot[2]) {
                case 2:
                case 0xF:
                case 0x10:
                    val = D_cinematic_overlay_800B1904->unk0058[i].unk0C;
                    fv = (f32)val;
                    m1 = lookupHmtMaterialByName(*(s32 *)(slot + 0x50), D_cinematic_overlay_800A54A8, &sp18);
                    composeInterpolatedNodeMatricesAltCall(m1, lookupHmtMaterialByName(*(s32 *)(off + (s32)D_cinematic_overlay_800B1900 + 0x50), D_cinematic_overlay_800A54B4, &sp1C), sp18, sp1C, fv);
                    break;
                }
            }
        }
    }
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
extern u8 D_cinematic_overlay_800A54A8[];
extern u8 D_cinematic_overlay_800A54B4[];
f32 quadraticEaseInOut(f32);
extern s32 lookupHmtMaterialByName(s32, u8 *, s32 *);
extern void composeInterpolatedNodeMatricesAltCall(s32, s32, s32, s32, f32) __asm__("composeInterpolatedNodeMatricesAlt");

void tickCutsceneActionSlots(f32 arg0) {
    s32 sp18;
    s32 sp1C;
    CutsceneActionSlot *slot;
    CutsceneActionSlot *cur;
    f32 t;
    f32 v;
    s32 a;
    s32 b;
    u16 type;
    u16 i;

    for (i = 0; i < 0x10; i++) {
        cur = &D_cinematic_overlay_800B0BC0[i];
        if (cur->active != 0) {
            slot = cur;
            type = ((u8 *)D_cinematic_overlay_800B1900)[(u16)slot->unk10 * 0x13C + 2];
            t = (arg0 - slot->unk8) / (slot->unkC - slot->unk8);
            if (t > 1.0f) {
                t = 1.0f;
                slot->active = 0;
                *(f32 *)&slot->unk0 = slot->unk4;
            } else if (t < 0.0f) {
                t = 0.0f;
            }
            t = quadraticEaseInOut(t);
            switch (type) {
            case 2:
            case 0xF:
            case 0x10:
            {
                v = (slot->unk4 - *(f32 *)&slot->unk0) * t + *(f32 *)&slot->unk0;
                a = lookupHmtMaterialByName(*(s32 *)((u8 *)D_cinematic_overlay_800B1900 + (u16)slot->unk10 * 0x13C + 0x50), D_cinematic_overlay_800A54A8, &sp18);
                b = lookupHmtMaterialByName(*(s32 *)((u8 *)D_cinematic_overlay_800B1900 + (u16)slot->unk10 * 0x13C + 0x50), D_cinematic_overlay_800A54B4, &sp1C);
                composeInterpolatedNodeMatricesAltCall(a, b, sp18, sp1C, v);
            }
            break;
            default:
                slot->active = 0;
                break;
            }
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A54CC);

static const char D_cinematic_overlay_800A54D8[16] = "i_gtu_hi_dst";
static const char D_cinematic_overlay_800A54E8[12] = "i_mtu_hi";

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

typedef struct { char c[13]; } AnS13;
typedef struct { char c[11]; } AnS11;
typedef struct { char c[10]; } AnS10;
typedef struct { char c[12]; } AnS12;
extern char D_cinematic_overlay_800A54CC[];
extern char D_cinematic_overlay_800A54F4[];
extern char D_cinematic_overlay_800A550C[];
extern char D_cinematic_overlay_800A5524[];
extern AnS11 D_cinematic_overlay_800A5500;
extern AnS10 D_cinematic_overlay_800A5518;
extern AnS10 D_cinematic_overlay_800A5530;
extern AnS10 D_cinematic_overlay_800A553C;
extern AnS10 D_cinematic_overlay_800A5548;
extern AnS10 D_cinematic_overlay_800A5554;
extern AnS12 D_cinematic_overlay_800A5560;
extern u8 D_cinematic_overlay_800B0B1F;
extern u16 D_cinematic_overlay_800B0B24;
extern u8 gGameSettings;
s32 rs_strcmp(char *, char *);
void scaleVec3ByRandomRange(f32 *, s32, s32);
void scaleVec3ByRandomRangeF(f32 *, f32, f32) __asm__("scaleVec3ByRandomRange");
void spawnNpcBurstAlongSegment(s32, s32, s32, f32 *);

u8 applyNamedEffectParameterDefault(char *name, u8 *dst, s32 arg2, u8 arg3) {
    f32 v[3];
    u8 found = 0;
    u8 flag = 0;
    u8 ok;

    if (D_cinematic_overlay_800B0B24 != 0) {
        if (rs_strcmp(D_cinematic_overlay_800A54CC, name) == 0) {
            if (dst != NULL) {
                *(AnS13 *)dst = *(AnS13 *)D_cinematic_overlay_800A54D8;
            }
            found = 1;
        }
        if (rs_strcmp((char *)D_cinematic_overlay_800A54E8, name) == 0) {
            if (dst != NULL) {
                *(AnS13 *)dst = *(AnS13 *)D_cinematic_overlay_800A54D8;
            }
            found = 1;
        }
        if (rs_strcmp(D_cinematic_overlay_800A54F4, name) == 0) {
            if (dst != NULL) {
                *(AnS11 *)dst = D_cinematic_overlay_800A5500;
            }
            found = 1;
        }
        if (rs_strcmp(D_cinematic_overlay_800A550C, name) == 0) {
            if (dst != NULL) {
                *(AnS10 *)dst = D_cinematic_overlay_800A5518;
            }
            found = 1;
        }
        if (rs_strcmp(D_cinematic_overlay_800A5524, name) == 0) {
            if (dst != NULL) {
                *(AnS10 *)dst = D_cinematic_overlay_800A5530;
            }
            found = 1;
        }
        ok = 1;
        if (gGameSettings != 7) {
            goto check;
        }
        if (found) {
            goto check;
        }
        switch ((u8)arg3) {
        case 1:
            if (dst != NULL) {
                *(AnS10 *)dst = D_cinematic_overlay_800A553C;
            }
            flag = 1;
            found = flag;
            break;
        case 2:
            if (dst != NULL) {
                *(AnS10 *)dst = D_cinematic_overlay_800A5548;
            }
            flag = 1;
            found = flag;
            break;
        case 3:
            if (dst != NULL) {
                *(AnS10 *)dst = D_cinematic_overlay_800A5554;
            }
            flag = 1;
            found = flag;
            break;
        case 4:
            if (dst != NULL) {
                *(AnS12 *)dst = D_cinematic_overlay_800A5560;
            }
            flag = 1;
            found = flag;
            break;
        default:
            ok = 1;
            goto check;
        }
    }
    ok = 1;
check:
    if (flag) {
        D_cinematic_overlay_800B0B1F++;
        ok = (D_cinematic_overlay_800B0B1F & 1) ^ 1;
    }
    if (found) {
        if (arg2 != 0 && ok) {
            v[0] = 0.3f;
            v[1] = 1.0f;
            v[2] = 0.2f;
            { union { s32 i; f32 f; } u, w; u.i = 0x3FC00000; w.i = 0x3F4CCCCD; scaleVec3ByRandomRangeF(v, w.f, u.f); }
            spawnNpcBurstAlongSegment(0, 5, arg2, v);
        }
    }
    return found;
}

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5578);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5594);

typedef struct { f32 x, y, z; } DfV3;
typedef struct {
    u16 type;
    u16 sub;
    DfV3 pos;
    DfV3 v10;
    f32 f1C;
    f32 f20;
    f32 f24;
    s32 f28;
    void *p2C;
} DfSlot;
typedef struct {
    u16 a;
    u16 b;
    u16 c;
    u16 d;
    DfV3 *posp;
    s32 f5C;
    DfV3 pos;
    DfV3 dir;
    s32 f78;
    f32 f7C;
    f32 f80;
    char *name;
} DfParams;
typedef struct { char *name; } DfModel;
typedef struct {
    u8 pad0[0x48];
    f32 f48;
} DfR48;
typedef struct {
    u8 pad0[0x28];
    f32 f28;
} DfR28;
typedef struct {
    f32 x, y, z;
    u8 pad0C[0x24];
    DfR48 **p30;
    DfR28 *p34;
} DfObj;
typedef struct {
    u8 pad0[4];
    DfObj *obj;
    DfV3 *pos;
    DfModel *model;
} DfCtx;
typedef struct { u8 r, g, b, a; } DfCol;

extern DfCol dfTplCol __asm__("D_cinematic_overlay_800A52FC");
extern u16 dfChain __asm__("D_main_bss_8013957C");
extern u8 *dfSlots __asm__("D_cinematic_overlay_800B1900");
s32 dfFindActive(u16, void *) __asm__("findActiveNpcInSlotChain");
s32 dfRevalidate(void *) __asm__("revalidateNpcSlotIterator");
DfCtx *dfCtxByIndex(u16) __asm__("getNpcContextByIndex");
s32 dfStrcmp(char *, char *) __asm__("rs_strcmp");
void dfInsert(DfSlot *) __asm__("insertCutsceneSlot");
void dfDispatch(u16, s32, void *) __asm__("slotDispatcherIter");
void dfOriented(s32, DfV3 *, DfV3 *, DfCol *, f32, f32, f32, f32) __asm__("spawnOrientedNpc");
void dfRandRot(DfV3 *, DfV3 *, f32, s32, s32, s32) __asm__("composeRandomRotationMatrix");
void dfScaleRand(DfV3 *, f32, f32) __asm__("scaleVec3ByRandomRange");
void dfDebris1(DfV3 *, DfV3 *, f32, f32, f32) __asm__("spawnDebris1Npc");
void dfBurst(s32, s32, DfV3 *, DfV3 *) __asm__("spawnNpcBurstAlongSegment");
void dfNormalize(DfV3 *) __asm__("normalize_vector");
void dfRamped(DfV3 *, s32, f32, f32, f32, f32, f32, f32, f32, f32) __asm__("spawnEffectNpcWithRampedScaleExt");
s16 dfRand(void) __asm__("rand");
static __inline__ f32 dfSqrt(f32 x) { f32 r; __asm__ volatile("sqrt.s %0, %1" : "=f"(r) : "f"(x)); return r; }
static __inline__ f32 dfAbs(f32 x) { f32 r; __asm__ volatile("abs.s %0, %1" : "=f"(r) : "f"(x)); return r; }

static __inline__ DfCtx *dfFindByName(char *name, void *iter, u16 *out) {
    s32 idx;
    DfCtx *ctx;

    for (idx = dfFindActive(dfChain, iter); (idx & 0xFFFF) != 0xFFFF; idx = dfRevalidate(iter)) {
        ctx = dfCtxByIndex(idx);
        if (ctx != NULL && ctx->model != NULL && dfStrcmp(name, ctx->model->name) == 0) {
            if (out != NULL) {
                *out = idx;
            }
            return ctx;
        }
    }
    return NULL;
}

#define DF_SPOS (*(DfV3 *)(dfSlots + 0x2CE0))

void dfImpl(ScEv *e) __asm__("spawnCutsceneDebrisField");
void dfImpl(ScEv *e) {
    DfCol col;
    DfV3 v30;
    DfV3 v40;
    DfParams p;
    DfV3 pos;
    DfSlot s;
    u8 iter[8];
    DfSlot s2;
    DfV3 v100;
    u16 idx;
    DfCtx *ctx;
    DfObj *o;
    f32 r;
    f32 c;
    f32 a;
    f32 b;
    u16 i;

    col = dfTplCol;
    p.a = 0xFFFF;
    p.b = 0xFFFF;
    p.c = 7;
    p.d = 10000;
    p.posp = &p.pos;
    p.f78 = 0;
    p.name = NULL;
    p.dir.x = 0.0f;
    p.dir.z = 0;
    p.f7C = 2.0f;
    p.f80 = 10.0f;
    p.dir.y = 1.0f;
    switch (e->a) {
        case 0:
            ctx = dfFindByName("b_fac_hi", iter, NULL);
            if (ctx != NULL) {
                o = ctx->obj;
                s2.type = 1;
                r = dfSqrt((*o->p30)->f48) * 0.25f;
                s2.f20 = 6.0f;
                s2.f1C = r;
                s2.pos.x = o->x;
                s2.pos.y = o->y - r * 0.5f * o->p34->f28;
                s2.pos.z = o->z;
                s2.f24 = 6.0f;
                s2.sub = 3;
                s2.v10.y = 5.0f;
                s2.v10.x = 4.0f;
                s2.v10.z = 4.0f;
                dfInsert(&s2);
            }
            break;
        case 1:
            ctx = dfFindByName("b_fac_hi", iter, &idx);
            if (ctx != NULL) {
                p.pos = *ctx->pos;
                p.pos.y -= 3.0f;
                dfOriented(0, &p.pos, &p.dir, &col, 0.5f, 15.0f, 1.5f, 0.7f);
                dfOriented(0, &p.pos, &p.dir, &col, 0.5f, 14.0f, 1.5f, 1.4f);
                dfOriented(0, &p.pos, &p.dir, &col, 0.5f, 13.0f, 1.5f, 2.1f);
                dfOriented(2, &p.pos, &p.dir, &col, 0.5f, 12.0f, 0.75f, 0.25f);
                dfDispatch(idx, 5, &p);
            }
        case 3:
            ctx = dfFindByName("b_pwrtran_hi", iter, &idx);
            if (ctx != NULL) {
                p.pos = *ctx->pos;
                p.name = "cb_trns8";
                p.pos.y -= 6.0f;
                dfOriented(0, &p.pos, &p.dir, &col, 0.5f, 15.0f, 1.5f, 0.7f);
                dfOriented(0, &p.pos, &p.dir, &col, 0.5f, 14.0f, 1.5f, 1.4f);
                dfOriented(0, &p.pos, &p.dir, &col, 0.5f, 13.0f, 1.5f, 2.1f);
                for (i = 0; i < 12; i++) {
                    dfRandRot(&v30, &v40, 1.5f, 120, 0, 0);
                    v30.x = p.pos.x + v30.x;
                    v30.y = p.pos.y + v30.y;
                    v30.z = p.pos.z + v30.z;
                    dfScaleRand(&v40, 2.0f, 4.0f);
                    a = dfAbs(((dfRand() & 0x7F) - 64.0f) / 12.8f) + 12.0f;
                    b = (dfAbs(((dfRand() & 0x7F) - 64.0f) * 0.0078125f) + 1.0f) * 3.0f + 6.0f;
                    c = (dfAbs(((dfRand() & 0x7F) - 64.0f) / 320.0f) + 0.6f) * 1.5f;
                    dfDebris1(&v30, &v40, a, b, c);
                }
                dfDispatch(idx, 5, &p);
            }
        case 4:
            ctx = dfFindByName("b_20sb_hi", iter, &idx);
            if (ctx != NULL) {
                p.pos = *ctx->pos;
                p.pos.y -= 7.0f;
                dfOriented(0, &p.pos, &p.dir, &col, 0.5f, 15.0f, 1.5f, 0.7f);
                dfOriented(0, &p.pos, &p.dir, &col, 0.5f, 14.0f, 1.5f, 1.4f);
                dfOriented(0, &p.pos, &p.dir, &col, 0.5f, 13.0f, 1.5f, 2.1f);
                dfOriented(2, &p.pos, &p.dir, &col, 0.5f, 8.0f, 0.75f, 0.35f);
                dfDispatch(idx, 5, &p);
                v40.x = 0.0f;
                v40.y = 1.0f;
                v40.z = 0.0f;
                v30.x = -3.2f;
                v30.y = 4.0f;
                v30.z = -1.2f;
                v30.x = p.pos.x + v30.x;
                v30.y = p.pos.y + v30.y;
                v30.z = p.pos.z + v30.z;
                dfBurst(0, 4, &v30, &v40);
                v30.x = 2.5f;
                v30.y = 4.0f;
                v30.z = -0.8f;
                v30.x = p.pos.x + v30.x;
                v30.y = p.pos.y + v30.y;
                v30.z = p.pos.z + v30.z;
                dfBurst(0, 4, &v30, &v40);
                v30.x = -1.0f;
                v30.y = 4.0f;
                v30.z = 1.2f;
                v30.x = p.pos.x + v30.x;
                v30.y = p.pos.y + v30.y;
                v30.z = p.pos.z + v30.z;
                dfBurst(0, 4, &v30, &v40);
                v30.x = 2.8f;
                v30.y = 4.0f;
                v30.z = 1.7f;
                v30.x = p.pos.x + v30.x;
                v30.y = p.pos.y + v30.y;
                v30.z = p.pos.z + v30.z;
                dfBurst(0, 4, &v30, &v40);
            }
            break;
        case 5:
            pos.x = 191.93f;
            pos.y = 4.04f;
            pos.z = 152.96f;
            pos.x = 47.9825f;
            pos.y = 1.01f;
            pos.z = 38.24f;
            for (i = 0; i < 12; i++) {
                dfRandRot(&v100, &v40, 2.0f, 25, 96, -2);
                dfScaleRand(&v40, 2.0f, 8.0f);
                {
                f32 a5, b5;
                a5 = ((dfRand() & 0x7F) - 64.0f) * 0.125f + 11.0f;
                b5 = ((dfRand() & 0x7F) - 64.0f) * 0.00390625f + 1.25f;
                dfDebris1(&pos, &v40, a5, b5, ((dfRand() & 0x7F) - 64.0f) / 320.0f + 0.6f);
                }
            }
            dfOriented(2, &pos, &v40, &col, 0.7f, 0.7f * 1.2f, 1.0f, 0.55f);
            dfOriented(2, &pos, &v40, &col, 0.5f, 1.05f * 1.2f, 1.0f, 0.5f);
            dfOriented(2, &pos, &v40, &col, 0.3f, 1.4f * 1.2f, 1.0f, 0.45f);
            s.type = 2;
            s.pos = pos;
            s.f24 = 3.0f;
            dfInsert(&s);
            s.type = 1;
            s.sub = 1;
            s.f1C = 1.7f;
            s.f20 = 0.8f;
            s.v10.x = 0.4f;
            s.v10.y = 0.4f;
            s.v10.z = 0.4f;
            s.f24 = 1.5f;
            dfInsert(&s);
            break;
        case 6:
            pos.x = DF_SPOS.x - 1.25f;
            pos.y = DF_SPOS.y;
            pos.z = DF_SPOS.z + 0.5f;
            s.pos = pos;
            s.f24 = 3.5f;
            s.v10.x = 0.0f;
            s.type = 3;
            dfInsert(&s);
            s.type = 1;
            s.sub = 2;
            s.f20 = 2.0f;
            s.f1C = 5.0f;
            s.v10.x = 9.0f;
            s.v10.y = 0.01f;
            s.v10.z = 4.5f;
            s.f24 = 2.5f;
            dfInsert(&s);
            s.f24 = 2.0f;
            s.sub = 1;
            s.v10.x *= 0.7077f;
            s.v10.y *= 0.7077f;
            s.v10.z *= 0.7077f;
            dfInsert(&s);
            v40.x = 1.0f;
            v40.y = 0.1f;
            v40.z = 0.1f;
            dfNormalize(&v40);
            dfOriented(0, &pos, &v40, &col, 0.5f, 22.0f, 1.5f, 1.2f);
            dfOriented(0, &pos, &v40, &col, 0.5f, 21.0f, 1.5f, 2.4f);
            dfOriented(0, &pos, &v40, &col, 0.5f, 20.0f, 1.5f, 3.6f);
            dfOriented(0, &pos, &v40, &col, 0.5f, 19.0f, 1.5f, 4.8f);
            break;
        case 7:
            pos.x = DF_SPOS.x - 1.25f;
            pos.y = DF_SPOS.y;
            pos.z = DF_SPOS.z + 0.5f;
            pos.y += 2.9f;
            dfRamped(&pos, 0xFFFF, 10.0f, 20.0f, 1.0f, 3.0f, 2.0f, 0.45f, 0.5f, 0.2f);
            pos.y -= 2.9f;
            col.r = 0x8C;
            col.g = 0x1E;
            col.b = 0x1E;
            col.a = 0x40;
            v40.x = 1.0f;
            v40.y = 0.1f;
            v40.z = 0.1f;
            dfOriented(1, &pos, &v40, &col, 0.5f, 6.0f, 6.5f, 1.5f);
            dfOriented(1, &pos, &v40, &col, 0.5f, 5.0f, 5.0f, 1.0f);
            break;
        case 8:
            s.f28 = 0;
            s.type = 5;
            s.f24 = 6.0f;
            s.pos.x = 82.5f;
            s.pos.y = -1.6f;
            s.pos.z = 77.5f;
            s.v10.x = 1.6f;
            s.v10.y = 0.3f;
            s.v10.z = 1.6f;
            dfInsert(&s);
            break;
        case 9:
            s.f28 = 0;
            s.type = 5;
            s.f24 = 20.0f;
            s.pos.x = 144.3f;
            s.pos.y = -12.5f;
            s.pos.z = 73.0f;
            s.v10.x = 1.6f;
            s.v10.y = 0.8f;
            s.v10.z = 1.6f;
            dfInsert(&s);
            break;
    }
}

typedef struct { u8 r, g, b, a; } NimCol;
typedef struct D_cinematic_overlay_800B0D00_type NimSlot;
typedef struct NimNode {
    struct NimNode *next;
    struct NimNode *prev;
} NimNode;
typedef struct NimMesh {
    u8 pad0[0xC];
    NimNode node;
} NimMesh;

extern NimCol D_cinematic_overlay_800A52FC;
s16 rand(void);
void zmemcpy(u8 *, u8 *, u32);
extern void *rs_memset(void *, s32, s32);
f32 quadraticEaseInOut(f32);
f32 sinf(f32);
void nimCompRandRot(f32 *, f32 *, f32, s32, s32, s32) __asm__("composeRandomRotationMatrix");
void nimScaleRand(f32 *, f32, f32) __asm__("scaleVec3ByRandomRange");
void nimDebris1(f32 *, f32 *, f32, f32, f32) __asm__("spawnDebris1Npc");
void nimType0xA(f32 *, f32) __asm__("spawnNpcType0xAFromTemplate");
void nimOriented(s32, f32 *, f32 *, NimCol *, f32, f32, f32, f32) __asm__("spawnOrientedNpc");
NimMesh *nimWalkMeshdef0(char *) __asm__("walkMeshdef0List");
void nimPlay3D(s32, f32 *, u8 *, f32, f32, s32, s32, s32, s32) __asm__("play3DSoundEvent");
void nimBurst(s32, s32, f32 *, f32 *) __asm__("spawnNpcBurstAlongSegment");
void nimRelease(NimMesh *) __asm__("releaseMeshAsset");
void nimInitTriplet(void *, f32, f32, f32) __asm__("initVec4TripletFromArgs");
void nimRotSlot0(void *, f32) __asm__("composeRotationMatrixSlot0");
void nimAddVec(void *, f32, f32, f32) __asm__("addVec3At0x24");

static __inline__ void nimInsertSlot(NimSlot *arg0) {
    u32 var_v1;

    for (var_v1 = 0; var_v1 < 0x40; var_v1++) {
        if (D_cinematic_overlay_800B0D00[var_v1].unk00 == 0) {
            zmemcpy((u8 *)&D_cinematic_overlay_800B0D00[var_v1], (u8 *)arg0, sizeof(NimSlot));
            break;
        }
    }
}

void npcIncomingMissileUpdate(NimNode **list, f32 dt) {
    f32 p28[3];
    f32 p38[3];
    f32 v48[3];
    u8 snd[0xC];
    NimSlot tmp;
    NimCol col;
    NimSlot *s;
    u32 i;
    u32 j;
    f32 sc;
    f32 k;
    f32 a;
    f32 b;

    rs_memset(snd, 0, 0xC);
    for (i = 0; i < 0x40; i++) {
        s = &D_cinematic_overlay_800B0D00[i];
        if (s->unk00 != 0) {
            s->unk24 -= dt;
            if (s->unk24 < 0.0f) {
                s->unk24 = 0.0f;
                s->unk00 = 0;
            }
        }
        switch (s->unk00) {
        case 0:
            break;
        case 1:
            if (rand() % s->unk02 == 0) {
                p28[0] = s->unk04[0] + ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->unk10[0]);
                p28[1] = s->unk04[1] + ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->unk10[1]);
                p28[2] = s->unk04[2] + ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->unk10[2]);
                nimType0xA(p28, s->unk1C + ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->unk20));
            }
            break;
        case 2:
            j = 0;
            k = 2.0f;
            for (; j < 3; j++) {
                if (rand() & 1) {
                    sc = (1.0f < s->unk24) ? 1.0f : s->unk24;
                    nimCompRandRot(p38, v48, k, 0x23, 0x60, -2);
                    nimScaleRand(v48, k, 8.0f);
                    a = ((f32)(rand() & 0x7F) - 64.0f) / 12.8f + 14.0f;
                    b = (((f32)(rand() & 0x7F) - 64.0f) * 0.00390625f + 1.25f) * sc;
                    nimDebris1(s->unk04, v48, a, b, ((f32)(rand() & 0x7F) - 64.0f) / 320.0f + 0.6f);
                }
            }
            break;
        case 3:
            s->unk10[0] += dt;
            if (0.075f < s->unk10[0]) {
                col = D_cinematic_overlay_800A52FC;
                p38[0] = s->unk04[0];
                p38[1] = s->unk04[1];
                p38[2] = s->unk04[2] + ((f32)(rand() & 0x7F) - 64.0f) * 0.0078125f * 30.0f;
                quadraticEaseInOut(s->unk24 / 3.5f);
                v48[0] = 0.0f;
                v48[1] = 1.0f;
                v48[2] = 0.0f;
                nimOriented(2, p38, v48, &col, 0.5f, 3.0f, 1.0f, 0.35f);
                for (j = 0; j < 8; j++) {
                    p28[0] = p38[0] + ((f32)(rand() & 0x7F) - 64.0f) / 42.666668f;
                    p28[1] = p38[1];
                    p28[2] = p38[2] + ((f32)(rand() & 0x7F) - 64.0f) / 25.6f;
                    nimType0xA(p28, ((f32)(rand() & 0x7F) - 64.0f) / 28.444445f + 4.0f);
                }
                s->unk10[0] = 0.0f;
            }
            break;
        case 4:
            switch (s->unk02) {
            case 0:
                s->unk2C = (void *)nimWalkMeshdef0("i_missile");
                s->unk28 = 0.0f;
                s->unk02 = 1;
                p38[0] = s->unk04[0];
                p38[1] = s->unk04[1] + 1.5f;
                p38[2] = s->unk04[2];
                if (!(rand() & 1)) {
                    s32 snd2;
                    if (!(rand() & 1)) {
                        snd2 = 0x35;
                    } else {
                        snd2 = 0x30;
                    }
                    nimPlay3D(0, p38, snd, 24.0f, 0.2f, 0, snd2, 0x55, 0);
                }
            case 1:
                s->unk28 += dt * 1.1f;
                p38[0] = s->unk04[0];
                p38[1] = s->unk04[1] + sinf((1.0f - s->unk28) * 1.5707964f) * 1.5f;
                p38[2] = s->unk04[2];
                if (1.0f < s->unk28) {
                    f32 up[3] = { 0.0f, -1.0f, 0.0f };
                    nimBurst(0, 6, s->unk04, up);
                    if (!(rand() & 1)) {
                        nimPlay3D(0, p38, snd, 24.0f, 0.2f, 0, 0xC, 0x78, 0);
                    }
                    s->unk28 = 0.0f;
                    s->unk02 = 2;
                } else {
                    NimNode *h;
                    nimInitTriplet((u8 *)s->unk2C + 0x28, 0.1f, 0.1f, 0.1f);
                    nimRotSlot0((u8 *)s->unk2C + 0x28, 90.0f);
                    nimAddVec((u8 *)s->unk2C + 0x28, p38[0], p38[1], p38[2]);
                    ((NimMesh *)s->unk2C)->node.next = h = *list;
                    if (h != NULL) {
                        ((NimMesh *)s->unk2C)->node.next->prev = &((NimMesh *)s->unk2C)->node;
                    }
                    ((NimMesh *)s->unk2C)->node.prev = NULL;
                    *list = &((NimMesh *)s->unk2C)->node;
                }
                break;
            case 2:
                s->unk28 += 1.0f;
                if (3.0f < s->unk28) {
                    nimRelease((NimMesh *)s->unk2C);
                    s->unk24 = 0.0f;
                }
                break;
            }
            break;
        case 5:
            s->unk28 += dt;
            if (0.3f < s->unk28) {
                tmp.unk04[0] = s->unk04[0] + ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->unk10[0]);
                tmp.unk04[1] = s->unk04[1] + ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->unk10[1]);
                tmp.unk04[2] = s->unk04[2] + ((f32)(rand() & 0x7F) - 64.0f) / (64.0f / s->unk10[2]);
                tmp.unk02 = 0;
                tmp.unk28 = 0.0f;
                tmp.unk00 = 4;
                tmp.unk24 = 99.0f;
                nimInsertSlot(&tmp);
                s->unk28 = 0.0f;
            }
            break;
        }
    }
}

extern void *rs_malloc(u32, u16);
extern u8 *D_cinematic_overlay_800B1AE0[];

void buildCutsceneGradientBuffers(void) {
    s8 i;
    s8 j;
    u8 r;
    u8 g;
    u8 b;
    u8 a;

    for (i = 0; i < 3; i++) {
        D_cinematic_overlay_800B1AE0[i] = rs_malloc(0x80, 0x10);
        for (j = 0; j < 0x20; j++) {
            b = 0;
            g = 0;
            r = 0;
            a = 0xFF;
            if (j & 1) {
                switch (i) {
                case 0:
                    r = g = b = a = ~(j * 7);
                    break;
                case 1:
                    g = ~(j * 7);
                    break;
                case 2:
                    r = ~(j * 7);
                    g = r / 3;
                    break;
                }
            } else {
                switch (i) {
                case 1:
                    r = g = b = a = 0;
                    break;
                case 0:
                    r = g = b = a = 0;
                    break;
                case 2:
                    b = a = 0xC8;
                    r = g = 0x50;
                    break;
                }
            }
            D_cinematic_overlay_800B1AE0[i][j * 4] = r;
            D_cinematic_overlay_800B1AE0[i][j * 4 + 1] = g;
            D_cinematic_overlay_800B1AE0[i][j * 4 + 2] = b;
            D_cinematic_overlay_800B1AE0[i][j * 4 + 3] = a;
        }
    }
}

































INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", spawnNpcBurstAlongSegment);

typedef struct { s32 a, b, c, d; } Str16;
typedef struct { s32 a, b, c, d, e; s16 f; } Str22;
typedef struct { s32 a, b, c, d; s8 e; } Str17;
typedef struct { s32 a, b; s16 c; } Str10;
typedef struct { s32 a, b, c; s16 d; } Str14;
typedef struct { s32 a, b, c, d; s16 e; } Str18;
extern char strCinPlCraftsVwing[];
extern char D_cinematic_overlay_800A518C[];
extern u16 D_cinematic_overlay_800B0B24;
extern u8 D_cinematic_overlay_800B0B1E;
extern u8 D_main_bss_80130B38;

void processCutsceneActions(u8 *arg0, s32 arg1) {
    u32 i;
    u32 kind;
    u8 *a3;
    s32 a2;
    s32 v1;
    u8 *dst;

    i = 0;
    if (*(u16 *)(arg0 + 0x4E) != 0) {
        kind = arg1 & 0xFF;
        do {
            a3 = arg0 + i * 0x18;
            if (*(s32 *)(a3 + 0x58) == 0x15) {
                D_cinematic_overlay_800B0B24 = *(u16 *)(a3 + 0x62);
            }
            if (D_main_bss_80130B38 != 0 && D_cinematic_overlay_800B0B1E == 0) {
                if (*(s32 *)(a3 + 0x58) == 6 && *(s32 *)(a3 + 0x60) == 0x1B) {
                    *(s32 *)(a3 + 0x58) = 7;
                }
                if (*(s32 *)(a3 + 0x58) == 0) {
                    *(s32 *)(a3 + 0x58) = 7;
                    *(s32 *)(a3 + 0x60) = 0x1B;
                }
            }
            if (*(s32 *)(a3 + 0x58) == 0x12) {
                a2 = *(s32 *)(a3 + 0x64);
                v1 = *(s32 *)(a3 + 0x60);
                if (a2 != 0 && kind == 5) {
                    v1 = a2;
                    if (v1 == 0x63) {
                        return;
                    }
                }
                {
                    switch (kind) {
                    case 0:
                        *(Str16 *)(arg0 + v1 * 0x4C + 0x13D8) = *(Str16 *)"pl_crafts/xwing";
                        break;
                    case 1:
                        *(Str16 *)(arg0 + v1 * 0x4C + 0x13D8) = *(Str16 *)"pl_crafts/ywing";
                        break;
                    case 2:
                        *(Str16 *)(arg0 + v1 * 0x4C + 0x13D8) = *(Str16 *)"pl_crafts/awing";
                        break;
                    case 3:
                        *(Str16 *)(arg0 + v1 * 0x4C + 0x13D8) = *(Str16 *)strCinPlCraftsVwing;
                        break;
                    case 4:
                        { s32 *d = (s32 *)(v1 * 0x4C + (s32)arg0 + 0x13D8); const s32 *sr = (const s32 *)"pl_crafts/snowspeeder"; __builtin_memcpy(d, sr, 22); }
                        break;
                    case 5:
                        { s32 *d = (s32 *)(v1 * 0x4C + (s32)arg0 + 0x13D8); const s32 *sr = (const s32 *)"pl_crafts/falcon"; __builtin_memcpy(d, sr, 17); }
                        break;
                    case 6:
                        { s32 *d = (s32 *)(v1 * 0x4C + (s32)arg0 + 0x13D8); const s32 *sr = (const s32 *)"tie_inter"; __builtin_memcpy(d, sr, 10); }
                        break;
                    case 7:
                        { s32 *d = (s32 *)(v1 * 0x4C + (s32)arg0 + 0x13D8); const s32 *sr = (const s32 *)D_cinematic_overlay_800A518C; __builtin_memcpy(d, sr, 14); }
                        break;
                    case 8:
                        { s32 *d = (s32 *)(v1 * 0x4C + (s32)arg0 + 0x13D8); const s32 *sr = (const s32 *)"pl_crafts/koelsch"; __builtin_memcpy(d, sr, 18); }
                        break;
                    }
                }
            }
            i += 1;
        } while (i < *(u16 *)(arg0 + 0x4E));
    }
}

struct CS { u8 p0[0x14]; u32 f14; f32 f18; f32 f1C; u8 p20[4]; f32 f24; f32 f28; };
extern s32 getCinematicStateSubObject(void *);
extern void setGridLayerScrollBounds(f32, f32);
extern s8 D_cinematic_overlay_800B09B0;
extern u16 D_cinematic_overlay_800B09B2;
extern u16 D_cinematic_overlay_800B09B6;
extern void *D_cinematic_overlay_800B0B00;
extern void *D_cinematic_overlay_800B0B04;
extern void *D_cinematic_overlay_800B0B08;
extern void *D_cinematic_overlay_800B0B0C;
extern s32 D_main_bss_80130B50;
extern u8 D_main_bss_80136E18[];
extern s32 D_main_bss_80138898;
extern s32 D_main_bss_80138928;

f32 computeCutsceneScreenScale(u32 arg0) {
    struct CS *o;
    f32 a, b, c, d, r;
    s32 lt;

    o = (struct CS *)getCinematicStateSubObject(D_cinematic_overlay_800B0B0C);
    o->f24 = (f32)D_cinematic_overlay_800B09B2 * 0.34f / 240.0f;
    o->f28 = (f32)D_cinematic_overlay_800B09B6 * 0.48f / 240.0f;
    lt = arg0 >= 0x3E4;
    o->f14 |= 0x02400001;
    o->f18 = o->f24 * -256.0f;
    o->f1C = o->f28 * -48.0f + 5.0f;
    setLookupEntryField5ByKey(D_cinematic_overlay_800B0B00, o, lt);

    { struct CS *o2 = (struct CS *)getCinematicStateSubObject(D_cinematic_overlay_800B0B08);
    o = o2;
    o->f24 = (f32)D_cinematic_overlay_800B09B2 * 0.38f / 240.0f; }
    o->f28 = (f32)D_cinematic_overlay_800B09B6 * 0.47f / 240.0f;
    o->f14 |= 0x02400001;
    o->f18 = o->f24 * -96.0f;
    o->f1C = o->f28 * -128.0f;
    setLookupEntryField5ByKey(D_cinematic_overlay_800B0B00, o, lt);

    o = (struct CS *)getCinematicStateSubObject(D_cinematic_overlay_800B0B04);
    o->f24 = (f32)D_cinematic_overlay_800B09B2 * 0.28f / 240.0f;
    o->f28 = (f32)D_cinematic_overlay_800B09B6 * 0.37f / 240.0f;
    o->f14 |= 0x02400000;
    o->f18 = o->f24 * -128.0f;
    o->f1C = o->f28 * -128.0f;
    setLookupEntryField5ByKey(D_cinematic_overlay_800B0B00, o, arg0 < 0x5F);

    if (arg0 - 0x2E9 < 0x1F) {
        register f32 t asm("$f0") = (f32)arg0 - 745.0f;
        register f32 dd asm("$f2") = t / 30.0f;
        c = quadraticEaseInOut(1.0f - dd) * 255.0f;
        D_main_bss_80136E18[0] = (u32)c;
        D_main_bss_80136E18[1] = (u32)c;
        D_main_bss_80136E18[2] = (u32)c;
    }
    if (arg0 - 0x12D < 0x13) {
        setGridLayerScrollBounds(19.75f, 19.75f);
    }
    D_cinematic_overlay_800B09B0 = 0;
    r = 1.0f;
    if (arg0 < 0x50) {
        r = 2.0f;
    }
    if (arg0 - 0x6E < 0xB) {
        r = ((f32)arg0 - 110.0f) / 10.0f + 1.0f;
    }
    if (arg0 - 0x79 < 0x289) {
        r = 2.0f;
    }
    if (!(D_main_bss_80130B50 & 1)) {
        if (arg0 - 0x30C < 0xD8) {
            D_main_bss_80138898 |= 0x11;
            D_main_bss_80138928 &= ~0x11;
        } else {
            D_main_bss_80138898 &= ~0x11;
            D_main_bss_80138928 |= 0x11;
        }
    }
    return r;
}

typedef struct { u8 p0[0x14]; u32 f14; f32 f18; f32 f1C; u8 p20[4]; f32 f24; f32 f28; u8 b2C; u8 b2D; u8 b2E; u8 b2F; } TcObj;
typedef struct { f32 x; f32 y; f32 z; } TcRgb;
extern void *D_cinematic_overlay_800B0B10;
extern u8 D_cinematic_overlay_800B0B34[4];
extern TcRgb D_cinematic_overlay_800AF6C0[];
extern u8 D_cinematic_overlay_800B0B1D;
extern f32 D_cinematic_overlay_800B0B2C;
void applyRgbaTintToMeshVertices(s32, u8 *);
f32 cosf(f32);
f32 sinf(f32);
struct DirObjFwd;
void transformAndNormalizeDirectionByMatrixP(void *, void *, f32 *, f32) __asm__("transformAndNormalizeDirectionByMatrix");

void tickCutsceneCameraFromTimeline(u32 arg0) {
    f32 v[3];
    TcObj *o;
    f32 k;

    o = (TcObj *)getCinematicStateSubObject(D_cinematic_overlay_800B0B10);
    o->f24 = (f32)D_cinematic_overlay_800B09B2 * 0.8f / 240.0f;
    o->f28 = (f32)D_cinematic_overlay_800B09B6 / 240.0f;
    o->f14 |= 0x02400003;
    o->f18 = o->f24 * -64.0f + 4.0f;
    o->f1C = o->f28 * -64.0f + 5.0f;
    setLookupEntryField5ByKey(D_cinematic_overlay_800B0B00, o, D_cinematic_overlay_800B0B1E != 0 ? arg0 < 0xC8 : arg0 < 0x1A4);
    k = 1.0f;
    o->b2C = 0xFF;
    o->b2D = 0xFF;
    o->b2E = 0xFF;
    D_cinematic_overlay_800B0B34[0] = 0xFF;
    D_cinematic_overlay_800B0B34[1] = 0xFF;
    D_cinematic_overlay_800B0B34[2] = 0xFF;
    D_cinematic_overlay_800B0B30 = 1.34f;
    if (arg0 - 0xAA < 0x1F) {
        k = 1.0 - ((f32)arg0 - 170.0) / 30.0;
    }
    if (arg0 - 0x186 < 0x1F) {
        k = ((f32)arg0 - 390.0) / 30.0;
    }
    D_cinematic_overlay_800B0B34[3] = (u32)((1.0f - k) * 255.0f);
    o->b2F = D_cinematic_overlay_800B0B1E != 0 ? (u32)(k * 255.0f) : 0xFF;
    if (D_cinematic_overlay_800B0B1E != 0) {
        if (arg0 - 0xAA < 0x1F || arg0 - 0x186 < 0x1F) {
            D_cinematic_overlay_800B0B34[0] = (u32)(D_cinematic_overlay_800AF6C0[D_cinematic_overlay_800B0B1E - 1].x * 255.0f / 1.7f);
            D_cinematic_overlay_800B0B34[1] = (u32)(D_cinematic_overlay_800AF6C0[D_cinematic_overlay_800B0B1E - 1].y * 255.0f / 1.7f);
            D_cinematic_overlay_800B0B34[2] = (u32)(D_cinematic_overlay_800AF6C0[D_cinematic_overlay_800B0B1E - 1].z * 255.0f / 1.7f);
            applyRgbaTintToMeshVertices(*(s32 *)((u8 *)D_cinematic_overlay_800B1900 + 0x21A8), D_cinematic_overlay_800B0B34);
        }
        if (arg0 - 0xAB < 0xF9) {
            v[0] = cosf(D_cinematic_overlay_800B0B2C * 30.0f * 1.1f * 3.1415927f / 180.0f) * 50.0f;
            v[1] = sinf(D_cinematic_overlay_800B0B2C * 30.0f * 1.2f * 3.1415927f / 180.0f) * 50.0f;
            v[2] = sinf(D_cinematic_overlay_800B0B2C * 30.0f * 1.3f * 3.1415927f / 180.0f) * 10.0f;
            transformAndNormalizeDirectionByMatrixP((void *)(*(s32 *)((u8 *)D_cinematic_overlay_800B1900 + 0x21A8) + 0x58), (u8 *)D_cinematic_overlay_800B1900 + 0x21DC, v, 0.9f);
        }
    }
    D_cinematic_overlay_800B0B1D = arg0 < 0x1A4;
}

extern u16 D_cinematic_overlay_800B1B20[];
extern Vec3f D_cinematic_overlay_800B1BA0[];
extern void normalize_vector(Vec3f);

typedef struct {
    u8 pad0[0x8];
    u8 *base;
    s32 count;
} DirHdr;

typedef struct {
    u8 pad0[0x20];
    DirHdr *hdr;
    s16 *pts;
    s16 *dirs;
} DirObj;

void transformAndNormalizeDirectionByMatrix(DirObj *obj, Mat4x3 mat, Vec3f origin, f32 scale) {
    Vec3f in;
    s32 ff;
    Vec3f out;
    u8 *p;
    u16 *dirIdx;
    u16 *ptIdx;
    s16 *dst;
    s32 left;
    s32 k;
    s32 i;
    u32 w;
    u32 a;
    u32 id;
    Vec3f *n;
    u16 *tb;
    f32 d;
    s16 *q;

    ff = 0xFFFF;
    for (id = 0x3F; (s32)id >= 0; id--) {
        D_cinematic_overlay_800B1B20[id] = ff;
    }
    left = obj->hdr->count;
    p = obj->hdr->base;
    if (left > 0) {
        do {
            w = *(u32 *)(p + 4);
            a = *(u32 *)p;
            dirIdx = (u16 *)(p + ((w & 0xFC0) >> 4));
            ptIdx = (u16 *)(p + ((w >> 16) & 0xFC));
            dst = (s16 *)(p + (w & 0x3F) * 4);
            if (a & 4) {
                k = 2;
                if (a & 8) {
                    k = 3;
                }
                if (k >= 0) {
                    do {
                        id = *dirIdx;
                        dirIdx += 1;
                        n = &D_cinematic_overlay_800B1BA0[id & 0x3F];
                        tb = &D_cinematic_overlay_800B1B20[id & 0x3F];
                        if (*tb != id) {
                            *tb = id;
                            q = obj->dirs + id * 4;
                            in[0] = q[0];
                            in[1] = q[1];
                            in[2] = q[2];
                            rotateVec3ByMat3x3(mat, in, *n);
                            normalize_vector(*n);
                        }
                        q = obj->pts + *ptIdx * 4;
                        in[0] = q[0] * 0.00390625f;
                        in[1] = q[1] * 0.00390625f;
                        in[2] = q[2] * 0.00390625f;
                        transformVec3ByMat34(mat, in, out);
                        out[0] -= origin[0];
                        out[1] -= origin[1];
                        out[2] -= origin[2];
                        normalize_vector(out);
                        d = (*n)[0] * out[0] + (*n)[1] * out[1] + (*n)[2] * out[2];
                        d = d + d;
                        out[0] -= d * (*n)[0];
                        out[1] -= d * (*n)[1];
                        out[2] -= d * (*n)[2];
                        ptIdx += 1;
                        dst[0] = (u32)(scale * (1.0f - out[0]) * 4096.0f);
                        dst[1] = (u32)(scale * (1.0f - out[2]) * 4096.0f);
                        k -= 1;
                        dst += 2;
                    } while (k >= 0);
                }
            }
            left -= 1;
            p += (*(u32 *)(p + 4) >> 22) & 0xFC;
        } while (left > 0);
    }
}

static const char D_cinematic_overlay_800A5B60[12] = "backdrop/%s";

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A5B6C);

__asm__(".section .rodata\n.align 2\n.globl D_cinematic_overlay_800A5B74\nD_cinematic_overlay_800A5B74:\n.asciz \"Q_____\"\n.space 1\n.globl D_cinematic_overlay_800A5B7C\nD_cinematic_overlay_800A5B7C:\n.asciz \"%03ld\"\n.space 2\n.section .text");
extern s32 D_cinematic_overlay_800A5B74[];
extern s32 D_cinematic_overlay_800A5B7C[];

typedef struct { u16 flags; u16 pad2; u16 w; u16 h; u8 pad8[4]; u8 data[1]; } BdAsset;
typedef struct { u8 pad0[8]; s16 tilesX; s16 tilesY; u16 *ids; u8 pad10[0x14]; f32 f24; f32 f28; u8 b2C; u8 b2D; u8 b2E; u8 b2F; } BdTexSet;
typedef struct { u16 w; u16 h; u16 bpp; u16 pad6; s32 count; BdTexSet *ts; BdAsset *asset; u16 *ids; u8 idx; u8 pad19[3]; s32 x1C; u8 pad20[0x18]; } Backdrop;
typedef struct { u8 pad0[0x14]; char name[16]; } BdMat;
typedef struct { u8 *pix[8]; u8 *plte; char *name; u16 w; u16 h; u8 one; u8 depth; u16 flags; u32 trans; } BdTex;
extern s32 D_cinematic_overlay_800A5B6C[];
extern u8 D_cinematic_overlay_800AF6E4;
s32 sprintf(char *, const char *, ...);
void *load_asset(char *);
void rs_free(void *);
u8 *rs_strcpy(u8 *, u8 *);
s32 registerHmtTextureInTable(BdMat *, BdTex *, u8);

Backdrop *loadBackdropAsset(char *name, u16 w, u16 h, u8 arg3) {
    union { s32 w; char c[8]; } n1;
    union { s32 w; char c[8]; } n2;
    char path[0x40];
    BdTex tex;
    BdMat mat;
    Backdrop *b;
    BdTexSet *ts;
    u8 *src;
    s32 n;
    u32 i;
    u32 j;
    u32 off;
    u32 tilesX;
    u16 flags;
    s32 fmt;
    u32 aw;
    u8 idx;

    b = rs_malloc(0x38, 0x10);
    rs_memset(b, 0, 0x38);
    sprintf(path, D_cinematic_overlay_800A5B60, name);
    b->asset = load_asset(path);
    b->x1C = 0;
    b->w = w;
    b->h = h;
    b->bpp = 2;
    idx = D_cinematic_overlay_800AF6E4++;
    b->idx = idx;
    n = 0x100;
    if ((b->asset->flags & 0xF) == 0) {
        b->bpp = 1;
        n = 0x10;
    }
    if ((b->asset->flags & 0xF) == 2) {
        b->bpp = 4;
    }
    if ((b->asset->flags & 0xF) == 3) {
        b->bpp = 8;
    }
    b->count = (b->asset->w + b->w - 1) / b->w;
    b->count *= (b->asset->h + b->h - 1) / b->h;
    b->ids = rs_malloc(b->count * 2, 0x10);
    for (i = 0; i < b->count; i++) {
        b->ids[i] = 0xFFFF;
    }
    ts = rs_malloc(0x30, 0x10);
    b->ts = ts;
    rs_memset(ts, 0, 0x30);
    b->ts->ids = rs_malloc(b->count * 2, 0x10);
    __builtin_memcpy(n1.c, (char *)D_cinematic_overlay_800A5B6C, 6);
    __builtin_memcpy(n2.c, (char *)D_cinematic_overlay_800A5B74, 7);
    n1.c[1] = b->idx + 0x41;
    n2.c[1] = b->idx + 0x41;
    rs_memset(&mat, 0, 0x24);
    rs_memset(&tex, 0, 0x34);
    rs_strcpy((u8 *)mat.name, (u8 *)n1.c);
    tex.name = n2.c;
    tex.w = b->w;
    tex.h = b->h;
    tex.one = 1;
    flags = b->asset->flags;
    if (arg3) {
        flags |= 0x2000;
    }
    tex.flags = flags;
    tex.plte = b->asset->data;
    tex.pix[0] = rs_malloc((b->w * b->h * b->bpp) / 2, 0x10);
    src = b->asset->data + ((b->asset->flags & 0x8000) ? n * 4 : n * 3);
    fmt = b->asset->flags & 0xF;
    if ((u32)(fmt - 4) < 2 || (u16)fmt == 2 || (u16)fmt == 3) {
        src = b->asset->data;
    }
    for (i = 0; i < b->count; i++) {
        sprintf(mat.name + 2, (char *)D_cinematic_overlay_800A5B7C, i);
        sprintf(tex.name + 2, (char *)D_cinematic_overlay_800A5B7C, i);
        aw = b->asset->w;
        tilesX = aw / b->w;
        off = (i % tilesX) * b->w;
        off += (i / tilesX) * b->h * aw;
        off *= b->bpp;
        off >>= 1;
        for (j = 0; j < b->h; j++) {
            zmemcpy(tex.pix[0] + ((j * b->w * b->bpp) >> 1), src + (off + ((j * b->asset->w * b->bpp) >> 1)), (b->w * b->bpp) / 2);
        }
        {
            s16 id = registerHmtTextureInTable(&mat, &tex, 1);
            b->ids[i] = ts->ids[i] = id;
        }
    }
    rs_free(tex.pix[0]);
    ts->tilesX = (u16)b->asset->w / (u16)b->w;
    { u16 ty = (u16)b->asset->h / (u16)b->h;
    ts->f24 = 1.0f;
    ts->f28 = 1.0f;
    ts->b2C = 0xFF;
    ts->b2D = 0xFF;
    ts->b2E = 0xFF;
    ts->b2F = 0xFF;
    ts->tilesY = ty; }
    rs_free(b->asset);
    b->asset = NULL;
    return b;
}




typedef struct { u8 b[4]; f32 f4; f32 f8; s32 wC; s32 w10; char name[16]; } IcMat;
s32 icRegister(IcMat *, BdTex *, u8) __asm__("registerHmtTextureInTable");

Backdrop *icImpl(s16 w, s16 h) __asm__("initCinematicSceneAssets");
Backdrop *icImpl(s16 w, s16 h) {
    IcMat mat = { { 0, 1, 0, 0 }, 1.0f, 1.0f, 0, 0, "P____" };
    BdTex tex = { { 0, 0, 0, 0, 0, 0, 0, 0 }, 0, (char *)D_cinematic_overlay_800A5B6C, 0, 0, 1, 0, 2, 0 };
    Backdrop *b;
    BdTexSet *ts;
    s32 n;
    s32 q;
    u32 i;
    s16 id;

    b = rs_malloc(0x38, 0x10);
    rs_memset(b, 0, 0x38);
    b->w = 0x40;
    b->h = 0x10;
    q = (w + b->w - 1) / b->w;
    b->bpp = 4;
    b->count = q;
    b->count = q * ((h + b->h - 1) / b->h);
    b->ids = rs_malloc(b->count * 2, 0x10);
    ts = rs_malloc(0x30, 0x10);
    b->ts = ts;
    rs_memset(ts, 0, 0x30);
    ts->ids = rs_malloc(b->count * 2, 0x10);
    n = b->w * b->h * b->bpp / 2;
    tex.w = b->w;
    tex.h = b->h;
    tex.pix[0] = rs_malloc(n, 0x10);
    rs_memset(tex.pix[0], 0xFF, n);
    tex.name[1] = D_cinematic_overlay_800AF6E4 + 'A';
    mat.name[1] = D_cinematic_overlay_800AF6E4 + 'A';
    id = icRegister(&mat, &tex, 1);
    ts->ids[0] = b->ids[0] = id;
    rs_free(tex.pix[0]);
    ts->tilesX = w / b->w;
    { s16 ty = h / b->h;
    ts->f24 = ts->f28 = 1.0f;
    ts->tilesY = ty; }
    for (i = 1; i < b->count; i++) {
        ts->ids[i] = ts->ids[0];
        b->ids[i] = 0xFFFF;
    }
    b->idx = D_cinematic_overlay_800AF6E4++;
    return b;
}

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

void clearVec4QuadStruct(void *);
void addVec3At0x24(void *, f32, f32, f32);
void applyScaleToMat3x4(void *, f32, f32, f32);
void composeQuatToMat3x4(void *, void *);
void composeRotationMatrixSlot2(void *, f32);

void composeInterpolatedNodeMatricesAlt(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, f32 arg4) {
    u16 i;
    u16 sel;
    s32 v;
    u8 *mat;
    u8 *n;

    if (arg0 != 0) {
        if (arg1 != 0) {
            for (i = 0; i < 2; i++) {
                mat = (i == 0) ? arg0 + 0x1C : arg1 + 0x1C;
                sel = i;
                n = arg3;
                if (sel == 0) {
                    n = arg2;
                }
                clearVec4QuadStruct(mat);
                if (*(u32 *)(n + 0x4C) & 1) {
                    addVec3At0x24(mat, -*(f32 *)(n + 0x50), -*(f32 *)(n + 0x54), -*(f32 *)(n + 0x58));
                }
                if (*(u32 *)(n + 0x4C) & 2) {
                    applyScaleToMat3x4(mat, *(f32 *)(n + 0x5C), *(f32 *)(n + 0x60), *(f32 *)(n + 0x64));
                }
                if (*(u32 *)(n + 0x4C) & 4) {
                    composeQuatToMat3x4(mat, n + 0x68);
                }
                composeRotationMatrixSlot2(mat, (sel != 0) ? -arg4 : arg4);
                if ((*(u32 *)(n + 0x4C) & 9) == 9) {
                    addVec3At0x24(mat, *(f32 *)(n + 0x78) + *(f32 *)(n + 0x50), *(f32 *)(n + 0x7C) + *(f32 *)(n + 0x54), *(f32 *)(n + 0x80) + *(f32 *)(n + 0x58));
                } else if ((*(u32 *)(n + 0x4C) & 9) == 8) {
                    addVec3At0x24(mat, *(f32 *)(n + 0x78), *(f32 *)(n + 0x7C), *(f32 *)(n + 0x80));
                } else if (*(u32 *)(n + 0x4C) & 1) {
                    addVec3At0x24(mat, *(f32 *)(n + 0x50), *(f32 *)(n + 0x54), *(f32 *)(n + 0x58));
                }
            }
        }
    }
}

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

void destroyNpcSlotByIndexU16(s32);
void despawnCutsceneNpcSlot(s32 arg0) {
    u32 i;
    register u16 slot asm("$17");
    s32 next;

    i = arg0 & 0xFF;
    { register s32 b asm("$3") = (s32)D_cinematic_overlay_800B1900; register CutNpcSlotB *e asm("$2") = (CutNpcSlotB *)(i * sizeof(CutNpcSlotB) + b); slot = e->slot; }
    if (slot != 0xFFFF) {
        next = getNextSlotNpcTypeId(slot) & 0xFFFF;
        if (next != 0xFFFF) {
            destroyNpcSlotByIndexU16(next);
        }
        destroyNpcSlotChain(slot);
        (&((CutNpcSlotB *)D_cinematic_overlay_800B1900)[i])->slot = 0xFFFF;
    }
}

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

typedef struct {
    u8 pad0[0xC];
    u8 *unkC;
} CineHolder;
struct CineObj {
    u8 pad0[0x14];
    u32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
};
struct CineSize {
    u8 pad0[0x10];
    s32 w;
    s32 h;
};
extern s32 D_cinematic_overlay_800B0934;
extern u8 D_cinematic_overlay_800B0938;
extern f32 D_cinematic_overlay_800B1EE8;
extern u8 gBootConfig;
extern CineHolder *initCinematicSceneAssets(s32, s32);
extern void insertLookupEntry(s32, void *, s32);
extern void setLookupEntryField5ByKey(s32, void *, s32);
extern void beginSceneRenderFrame(s32);

void cinematicInitializer(s32 arg0, struct CineSize *arg1, f32 arg2) {
    CineHolder *v0;
    struct CineObj *s0;

    if (D_cinematic_overlay_800B0934 == 0) {
        D_cinematic_overlay_800B0938 = 0;
        D_cinematic_overlay_800B1EE8 = arg2 * 30.0f;
        v0 = initCinematicSceneAssets(0x40, 0x10);
        s0 = (struct CineObj *)v0->unkC;
        s0->unk24 = (f32)arg1->w * 0.015625f;
        s0->unk28 = (f32)arg1->h * 0.0625f;
        D_cinematic_overlay_800B0934 = (s32)v0;
        s0->unk18 = -((f32)arg1->w * 0.5f);
        s0->unk1C = -((f32)arg1->h * 0.5f);
        s0->unk14 |= 0x02400003;
        s0->unk20 = -100.0f;
        insertLookupEntry(arg0, s0, 0);
        setLookupEntryField5ByKey(arg0, s0, 1);
    }
    if (!(*(s32 *)(&gBootConfig + 0x44) & 0x80)) {
        beginSceneRenderFrame(8);
    }
}

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

__asm__(".section .text\n.word 0x0C03A807, 0x00000000\n");
