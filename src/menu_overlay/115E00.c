#include "common.h"
#include "common_types.h"

#include "PR/os.h"

#include "hud.h"
#include "textures.h"

#include "main/02420.h"
#include "main/08120.h"
#include "main/1EE30.h"
#include "main/55AF0.h"
#include "main/64EA0.h"
#include "menu_overlay/115E00.h"
#include "menu_overlay/12CA40.h"

// Interim BSS externs
extern struct ui_element bridgeShipBlueprints[9];
extern u16 bridgeShipBlueprintTextureIds[8]; // This would make it undersized by 1, what gives?
extern struct xy_offset D_menu_overlay_800CDF80[9];

struct rgba bridgeYellowColor = {
    0xE1, 0xAF, 0x00, 0xFF
};
struct rgba bridgeWhiteColor = {
    0xD7, 0xD8, 0xD7, 0xFF
};
struct rgba bridgeGreenColor = {
    0x91, 0xFF, 0x91, 0x00
};
struct rgba bridgeRedColor = {
    0xFF, 0x6E, 0x6E, 0x00
};

s32 D_menu_overlay_800CC700 = -1;

f32 bridgeShipBlueprintWidthScales[9] = {
    1.0f, 1.0f, 0.9f,
    1.1f, 0.9f, 1.1f,
    0.9f, 1.0f, 1.0f,
};
f32 bridgeShipBlueprintHeightScales[9] = {
    1.0f, 1.0f, 0.9f,
    0.9f, 0.9f, 1.1f,
    0.7f, 0.9f, 1.0f,
};

struct xy_offset bridgeShipBlueprintScreenPositions[8][8] = {
    {{   0, -16}, {  0,   0}, {   0,   0}, {   0,   0}, {   0,  0}, {  0,  0}, {  0,  0}, {  0,  0}},
    {{   0, -64}, {  0,  64}, {   0,   0}, {   0,   0}, {   0,  0}, {  0,  0}, {  0,  0}, {  0,  0}},
    {{   0, -64}, {-64,  64}, {  64,  64}, {   0,   0}, {   0,  0}, {  0,  0}, {  0,  0}, {  0,  0}},
    {{ -64, -64}, { 64, -64}, { -64,  64}, {  64,  64}, {   0,  0}, {  0,  0}, {  0,  0}, {  0,  0}},
    {{ -64, -64}, { 64, -64}, {-128,  64}, {   0,  64}, { 128, 64}, {  0,  0}, {  0,  0}, {  0,  0}},
    {{-128, -64}, {  0, -64}, { 128, -64}, {-128,  64}, {   0, 64}, {128, 64}, {  0,  0}, {  0,  0}},
    {{-128, -64}, {  0, -64}, { 128, -64}, {-192,  64}, { -64, 64}, { 64, 64}, {192, 64}, {  0,  0}},
    {{-192, -64}, {-64, -64}, {  64, -64}, { 192, -64}, {-192, 64}, {-64, 64}, { 64, 64}, {192, 64}},
};

// DO NOT DELTE ME I AM REQUIRED FOR MATCHING
u32 data_pad_115E00 = 0x27C30020;

__asm__(".section .rodata\n.align 2\nD_menu_overlay_800A5870: .asciz \"frontend/bridge\"\n.align 2\nD_menu_overlay_800A5880: .asciz \"+bridge\"\n.align 2\nD_menu_overlay_800A5888: .asciz \"-console\"\n.align 2\nD_menu_overlay_800A5894: .asciz \"-steps\"\n.align 2\nD_menu_overlay_800A589C: .asciz \"-lights\"\n.align 2\nD_menu_overlay_800A58A4: .asciz \"frontend/bridge/bridge\"\n.align 2\n.section .text");
INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A58BC);
extern char D_menu_overlay_800A5870[];
extern char D_menu_overlay_800A5880[];
extern char D_menu_overlay_800A5888[];
extern char D_menu_overlay_800A5894[];
extern char D_menu_overlay_800A589C[];
extern char D_menu_overlay_800A58A4[];
typedef struct {
    s32 pad0;
    void *f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
} CsMain;

typedef struct {
    void *next;
    void *prev;
    u8 f8;
    u8 pad9[3];
    s32 fC;
    f32 f10;
    s32 f14;
    s32 f18;
    f32 f1C;
    s32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
    u8 pad38[0x20];
} CsEntry;

typedef struct {
    char *name;
    s32 mesh;
    u8 *dat;
    s32 fC;
    s32 f10;
    s32 f14;
    u8 *f18;
    f32 f1C;
} CsModel;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} CsQuad;

typedef struct {
    s32 a;
    s32 b;
    s32 c;
} CsV3;

extern char D_menu_overlay_800A58BC[];
extern u8 D_menu_overlay_800CDABB;
extern s8 D_menu_overlay_800CDABC;
extern u8 D_menu_overlay_800CDABE;
extern s8 D_menu_overlay_800CDAC0;
extern u8 D_menu_overlay_800CDAC7;
extern u8 D_menu_overlay_800CDAC8;
extern s32 D_menu_overlay_800CDACC;
extern s32 D_menu_overlay_800CDFA8;
extern s32 D_menu_overlay_800CDFAC;
extern s32 D_menu_overlay_800CE6A4;
extern f32 D_menu_overlay_800CE6A8;
extern u8 bridgeMenuState;
extern u8 bridgeTransitionState;
extern s32 D_menu_overlay_800CDFB0;
extern u8 bridgeMenuDesiredLevel;
extern u8 D_menu_overlay_800CDABF;
extern f32 D_menu_overlay_800CDB0C;
extern u8 bridgeMenuDisplayLevel;
extern u8 bridgeMenuPreviousLevel;
extern s32 D_menu_overlay_800CDAD0;
extern u8 D_main_bss_80130B62;
extern s32 D_main_bss_80138920;
extern s32 D_main_bss_8013889C;
extern f32 D_menu_overlay_800CDB04;
extern f32 D_menu_overlay_800CDB14;
extern f32 D_menu_overlay_800CDB18;
extern s32 D_menu_overlay_800CDCE0;
extern s32 D_menu_overlay_800CDCE4;
extern s32 D_menu_overlay_800CDFA4;
extern s32 D_menu_overlay_800CDD70;
extern struct ui_element *D_menu_overlay_800CDD74;
extern struct ui_element *D_menu_overlay_800CDD78;
extern struct ui_element D_menu_overlay_800CDD80;
extern s32 D_menu_overlay_800CDCDC;
extern s32 bridgeDatFilePointer;
extern CsMain csMain __asm__("D_menu_overlay_800CDC80");
extern CsEntry D_menu_overlay_800CDB20[];
extern CsModel csModels[] __asm__("D_menu_overlay_800CDCF0");

void initSpeechSubsystem(s32, u8);
void parseLoadedSndSection(s32);
void loadSongAssetByName(s32, s32);
void playSimpleAudioCmd(s32, s32, s32);
s32 findAudioChannelById(s32);
s32 playSongById(s32, s32, s32, s32);
void clearVec4QuadStruct(void *);
void setRenderStateFlagByteOne(s32);
void setRenderStateFlagByteTwo(s32);
void setRenderStateFlagByteThree(s32);
s32 loadDatFile(char *);
void initNpcBookkeepingTables(void);
void load_hmt_and_hob(char *, s32, s32, s32);
char *extractTextBeforeFmtChar(char *);
void *walkMeshdef0List(char *);
extern void applyFlagsToMeshTreeOrList(s32, s32, s32, s32);
void *getDatItemByName(s32, char *);
void loadFontAsset(s32);
void loadCharTextureSet(struct some_ui_list_root *, s32, s32, s32);
void setMenuOverlayHeaderState(s32, s32, s32);
void resetPlayerSlotAllChannels(s32, s32);
void printLevelSelectWeaponText2(u8, u8) __asm__("printLevelSelectWeaponText");
s32 startPlayerSlotAnimationChannelExt(s32, char *, s32, s32, s32, s32);
s32 initPlayerSlotAnimationChannelFull(s32, s32, s32, s32, s32, s32, f32);
s32 buildScaledFormatTextElement(char *, s32, s32, s32, s32, s32);
struct ui_element *getStructField0xC(s32);
void initMenuWidgetArray(void);
void setupPlayerCraftDisplayAnim();
void initFormatMessageWorker(s32);
extern s32 bsearchFactor5TableByU16Key(s32, s32, s32);

void initCraftSelectScreen(u8 arg0, s32 arg1, s32 arg2) {
    char buf[0x28];
    u32 i;
    f32 fl;
    CsEntry *e;
    CsModel *m;
    s32 mesh;
    u8 *d;
    s32 txt;
    struct ui_element *src;
    struct ui_element *dst;
    struct ui_element *end;
    s32 res;

    D_menu_overlay_800CDAD0 = arg2;
    if (!(arg1 & arg2)) {
        arg1 = 1;
    }
    bridgeMenuDesiredLevel = 0xFF;
    for (i = 0; i < 0x13; i++) {
        if (arg1 & (1 << i)) {
            bridgeMenuPreviousLevel = bridgeMenuDisplayLevel = bridgeMenuDesiredLevel = i;
            break;
        }
    }
    fl = 1.0f;
    D_menu_overlay_800CDAC7 = 0;
    D_menu_overlay_800CDACC = 0xFFFFFF;
    D_menu_overlay_800CDABB = 0;
    D_menu_overlay_800CDABC = 0;
    D_menu_overlay_800CDAC0 = 0;
    D_menu_overlay_800CDABE = 0;
    D_menu_overlay_800CE6A4 = 0;
    D_menu_overlay_800CE6A8 = 0;
    D_menu_overlay_800CDB04 = fl;
    D_menu_overlay_800CDB0C = 2.0f;
    initSpeechSubsystem(0, D_main_bss_80130B62);
    D_menu_overlay_800CDFB0 = 0;
    D_menu_overlay_800CDABF = 0;
    parseLoadedSndSection(3);
    loadSongAssetByName(D_main_bss_80138920, 5);
    playSimpleAudioCmd(0x74, 0, 0xFD);
    playSimpleAudioCmd(0x7F, 0, 0xFE);
    D_menu_overlay_800CDCE0 = playSongById(3, 5, findAudioChannelById(5), 0);
    D_menu_overlay_800CDCE4 = bsearchFactor5TableByU16Key(0x2B, 0x3C, 0x40);
    D_menu_overlay_800CDAC8 = arg0;
    D_main_bss_8013889C = 0;
    csMain.f4 = D_menu_overlay_800CDB20;
    csMain.f8 = 0;
    csMain.fC = 0;
    D_menu_overlay_800CDB14 = D_menu_overlay_800CDB18 = 0.0f;
    csMain.f20 = 45.0f;
    csMain.f24 = 0.1171875f;
    csMain.f28 = 97.65625f;
    csMain.f10 = 0x200;
    csMain.f14 = 0x154;
    csMain.f18 = 0x100;
    csMain.f1C = 0xAA;
    clearVec4QuadStruct((u8 *)&csMain + 0x2C);
    setRenderStateFlagByteOne(1);
    setRenderStateFlagByteTwo(1);
    setRenderStateFlagByteThree(0);
    D_menu_overlay_800CDCDC = (s32)allocateSlotTable(0x40);
    i = 0;
    do {
        e = &D_menu_overlay_800CDB20[i];
        if (i != 0) {
            e->prev = &D_menu_overlay_800CDB20[i - 1];
        } else {
            e->prev = 0;
        }
        if (i < 3) {
            e->next = &D_menu_overlay_800CDB20[i + 1];
        } else {
            e->next = 0;
        }
        e->f8 = 1;
        e->fC = 0;
        e->f10 = 0;
        e->f14 = 0;
        e->f18 = 0;
        e->f1C = fl;
        e->f20 = 0;
        e->f24 = 0.3f;
        e->f28 = 0.3f;
        e->f2C = 0.3f;
        e->f30 = 0;
        e->f34 = fl;
        i++;
    } while (i < 4);
    D_menu_overlay_800CDB20[1].f8 = 0;
    D_menu_overlay_800CDB20[2].f8 = 2;
    D_menu_overlay_800CDB20[2].fC = 0;
    D_menu_overlay_800CDB20[2].f14 = 0;
    D_menu_overlay_800CDB20[3].f8 = 2;
    D_menu_overlay_800CDB20[3].fC = 0;
    D_menu_overlay_800CDB20[3].f10 = 0;
    D_menu_overlay_800CDB20[3].f14 = 0;
    D_menu_overlay_800CDB20[1].f24 = 0.1f;
    D_menu_overlay_800CDB20[1].f28 = 0.1f;
    D_menu_overlay_800CDB20[1].f2C = 0.1f;
    D_menu_overlay_800CDB20[2].f24 = 1.0f;
    D_menu_overlay_800CDB20[2].f28 = 1.0f;
    D_menu_overlay_800CDB20[2].f2C = 1.8f;
    D_menu_overlay_800CDB20[2].f10 = -8.0f;
    D_menu_overlay_800CDB20[2].f30 = 55.0f;
    D_menu_overlay_800CDB20[3].f24 = 0.8f;
    D_menu_overlay_800CDB20[3].f28 = 0.8f;
    D_menu_overlay_800CDB20[3].f2C = 0.8f;
    D_menu_overlay_800CDB20[3].f30 = 250.0f;
    bridgeDatFilePointer = loadDatFile(D_menu_overlay_800A5870);
    i = 0;
    csModels[0].name = D_menu_overlay_800A5880;
    csModels[1].name = D_menu_overlay_800A5888;
    csModels[2].name = D_menu_overlay_800A5894;
    csModels[3].name = D_menu_overlay_800A589C;
    initNpcBookkeepingTables();
    load_hmt_and_hob(D_menu_overlay_800A58A4, 0, 0, 0);
    do {
        m = &csModels[i];
        mesh = (s32)walkMeshdef0List(extractTextBeforeFmtChar(m->name));
        m->mesh = mesh;
        clearVec4QuadStruct((u8 *)mesh + 0x28);
        applyFlagsToMeshTreeOrList(m->mesh, 0, 0x14800000, 0);
        d = getDatItemByName(bridgeDatFilePointer, m->name + 1);
        m->dat = d;
        *(CsV3 *)&m->fC = *(CsV3 *)(d + 0x10);
        m->f18 = d + 0x1C;
        m->f1C = *(f32 *)(d + 0x28);
        i++;
    } while (i < 4);
    applyFlagsToMeshTreeOrList(csModels[0].mesh, 0, 0x40000, 0);
    loadFontAsset(0);
    loadCharTextureSet((struct some_ui_list_root *)D_menu_overlay_800CDCDC, 0, 0xA, 0x80);
    loadCharTextureSet((struct some_ui_list_root *)D_menu_overlay_800CDCDC, 2, 2, 0x80);
    loadCharTextureSet((struct some_ui_list_root *)D_menu_overlay_800CDCDC, 6, 1, 0x200);
    setMenuOverlayHeaderState(2, 0x200, 0);
    resetPlayerSlotAllChannels(0, 0xA);
    resetPlayerSlotAllChannels(2, 0xA);
    resetPlayerSlotAllChannels(6, 0x14);
    setPlayerSlotEntryRGB(0, 0, &bridgeWhiteColor);
    setPlayerSlotEntryRGB(0, 1, &bridgeWhiteColor);
    setPlayerSlotEntryRGB(0, 2, &bridgeYellowColor);
    setPlayerSlotEntryRGB(0, 3, &bridgeYellowColor);
    printLevelSelectWeaponText2(0, 0);
    D_menu_overlay_800CDFA4 = startPlayerSlotAnimationChannelExt(0, getGameOrFrontText(bridgeMenuDesiredLevel), 0x10, 0, -0x100, 0x75);
    D_menu_overlay_800CDFA8 = startPlayerSlotAnimationChannelExt(0, getGameOrFrontText(0x39), 0x10, 2, -0x100, -0xA3);
    setPlayerSlotEntryRGB(2, 0, &bridgeWhiteColor);
    setPlayerSlotAnimationFlag(2, getGameOrFrontText(0x36), 0, -0x100, 0x97);
    setPlayerSlotEntryRGB(6, 0, &bridgeGreenColor);
    D_menu_overlay_800CDFAC = initPlayerSlotAnimationChannelFull(6, 0x3C, 0, -0x94, -0x5F, 0x96, 1.35f);
    sprintf(buf, D_menu_overlay_800A58BC, bridgeMenuDesiredLevel);
    res = buildScaledFormatTextElement(buf, 2, 0x40, 0x14, 4, D_main_bss_80138920);
    D_menu_overlay_800CDD70 = res;
    src = getStructField0xC(res);
    D_menu_overlay_800CDD74 = src;
    D_menu_overlay_800CDD78 = &D_menu_overlay_800CDD80;
    src->flags |= 0x09000003;
    D_menu_overlay_800CDD80 = *src;
    initMenuWidgetArray();
    bridgeLoadShipBlueprints((struct some_ui_list_root *)D_menu_overlay_800CDCDC);
    setupPlayerCraftDisplayAnim(bridgeMenuDesiredLevel);
    insertLookupEntry((struct some_ui_list_root *)D_menu_overlay_800CDCDC, D_menu_overlay_800CDD74, 0xA);
    insertLookupEntry((struct some_ui_list_root *)D_menu_overlay_800CDCDC, D_menu_overlay_800CDD78, 0xA);
    setLookupEntryField5ByKey((struct some_ui_list_root *)D_menu_overlay_800CDCDC, D_menu_overlay_800CDD74, 1);
    setLookupEntryField5ByKey((struct some_ui_list_root *)D_menu_overlay_800CDCDC, D_menu_overlay_800CDD78, 1);
    layoutMenuTextRow((struct some_ui_list_root *)D_menu_overlay_800CDCDC, bridgeMenuDesiredLevel);
    initFormatMessageWorker(5);
    bridgeTransitionState = 0;
    bridgeMenuState = 0;
}
















typedef struct TcNode { struct TcNode *next; struct TcNode *prev; } TcNode;
typedef struct { u8 pad[0xC]; TcNode node; } TcMesh;
typedef struct { char *name; TcMesh *mesh; u8 pad[0x18]; } TcModel;
typedef struct { TcNode *head; void *f4; s32 f8; } TcMain;
extern TcNode *tcHead __asm__("D_menu_overlay_800CDC80");
extern TcMain tcMain __asm__("D_menu_overlay_800CDC80");
extern TcModel tcModels[] __asm__("D_menu_overlay_800CDCF0");
extern f32 bridgeRotationVelocityMultiplier;
extern f32 tcB14 __asm__("D_menu_overlay_800CDB14");
extern s32 tcAFC __asm__("D_menu_overlay_800CDAFC");
extern s32 tcFA4 __asm__("D_menu_overlay_800CDFA4");
extern s32 tcFA8 __asm__("D_menu_overlay_800CDFA8");
extern f32 tcE6A4 __asm__("D_menu_overlay_800CE6A4");
extern f32 tcE6A8 __asm__("D_menu_overlay_800CE6A8");
extern s32 tcCDC __asm__("D_menu_overlay_800CDCDC");
extern s32 tcACC __asm__("D_menu_overlay_800CDACC");
f32 advanceWrappingPhaseAccumulator(void);
void pollControllerInputs(void);
void setNewAndPreviousButtonsPressed(void);
void waitForPrevFrameDone(void);
void startSlotLoopAnimWithVoiceSync(f32 arg0);
void handleCraftSelectInput(void);
void tickMenuTransitionState(void);
void tickTimedScreenFadeFloat(f32 arg0);
void advancePlayerAnimationPhase(s32, s32, f32);
void applyPlayerSlotAnimChannelKeyframe(u8 s0, s32 s1, f32 alpha);
void activateAnimationKeyframe(s32, s32, u8);
void runScriptedCraftCinematicEvent(f32 dt);
void spawnOrientedEffectWithEasedSpin(void);
void frameStartReset(void);
s32 tcRebuild(s32) __asm__("rebuildActiveDisplayObjectList");
void setupCameraMatrices(void *);
void drawFrameProfilerBars(void);
void submitGfxFrame(void);
void handleLevelSelectStartConfirm(void);
u8 accumulateShipThrottleCharge(s32, void *, f32);

#define TC_PUSH(k) do { tcModels[k].mesh->node.next = tcHead; if (tcHead != NULL) { tcModels[k].mesh->node.next->prev = &tcModels[k].mesh->node; } tcModels[k].mesh->node.prev = NULL; tcHead = &tcModels[k].mesh->node; } while (0);

s32 tickCraftSelectScreen(void) {
    TcNode *nx;
    s32 r;

    bridgeRotationVelocityMultiplier = advanceWrappingPhaseAccumulator();
    pollControllerInputs();
    setNewAndPreviousButtonsPressed();
    tcB14 += bridgeRotationVelocityMultiplier * 30.0f;
    waitForPrevFrameDone();
    startSlotLoopAnimWithVoiceSync(bridgeRotationVelocityMultiplier);
    handleCraftSelectInput();
    tickMenuTransitionState();
    tickTimedScreenFadeFloat(bridgeRotationVelocityMultiplier);
    advancePlayerAnimationPhase(tcFA4, tcAFC, bridgeRotationVelocityMultiplier);
    advancePlayerAnimationPhase(tcFA8, tcAFC, bridgeRotationVelocityMultiplier);
    tcE6A4 += tcE6A8 * bridgeRotationVelocityMultiplier;
    if (tcE6A4 > 1.0f) {
        tcE6A4 = 1.0f;
    }
    if (tcE6A4 < 0.0f) {
        tcE6A4 = 0.0f;
    }
    applyPlayerSlotAnimChannelKeyframe(bridgeMenuDesiredLevel, bridgeMenuPreviousLevel, tcE6A4);
    activateAnimationKeyframe(2, 0, (u32)(*(f32 *)&tcAFC * 255.0f));
    runScriptedCraftCinematicEvent(bridgeRotationVelocityMultiplier);
    tcHead = NULL;
    spawnOrientedEffectWithEasedSpin();
    TC_PUSH(3)
    TC_PUSH(1)
    TC_PUSH(2)
    TC_PUSH(0)
    frameStartReset();
    ((TcMain *)&tcHead)->f8 = tcRebuild(tcCDC);
    setupCameraMatrices((TcMain *)&tcHead);
    drawFrameProfilerBars();
    submitGfxFrame();
    handleLevelSelectStartConfirm();
    if (accumulateShipThrottleCharge(tcCDC, (TcMain *)&tcHead, bridgeRotationVelocityMultiplier)) {
        r = 0xFFFFFE;
        if (tcACC != 0xFFFFFE) {
            r = tcACC;
        }
        return r;
    }
    return 0xFFFFFF;
}

extern f32 bridgeRotationVelocityMultiplier;
extern f32 bridgeRotationAngle;
extern f32 bridgeDisplayFlickerTimer;
extern f32 D_menu_overlay_800CDB00;
extern f32 D_menu_overlay_800CDAF0;
extern u8 D_menu_overlay_800CDAB8;
extern u8 D_menu_overlay_800CDAB9;
extern u8 D_menu_overlay_800CDABA;
extern u8 D_menu_overlay_800CDABD;
extern u8 D_menu_overlay_800CDAC6;
extern char D_menu_overlay_800CDA90[];
extern f32 D_menu_overlay_800CDAFC;
extern f32 D_menu_overlay_800CDAE4;
extern f32 D_menu_overlay_800CDADC;
extern f32 D_menu_overlay_800CDAD4;
extern f32 D_menu_overlay_800CDAD8;
extern f32 D_menu_overlay_800CDAE8;
extern f32 D_menu_overlay_800CDAEC;
extern s32 D_menu_overlay_800CDAF4;
extern f32 D_menu_overlay_800CDB08;
void safeLookup3DSoundEntry(s32, s32);
void playExitSoundAndToggleScreenMeshes(void);
void enqueueFormatMessage(s32, char *);
s32 pollServiceMessageByte(void *);
void requestViFeatureChange(s32);
s32 isStructUninitialized(s32);
void startPlayerSlotAnimationChannelFlagged(s32, s32, s32);
f32 sinf(f32);
f32 quadraticEaseInOut(f32);
void composeRotationMatrixSlot0(Mat4x3, f32);
void composeRotationMatrixSlot1(Mat4x3, f32);
void addVec3At0x24(Mat4x3, f32, f32, f32);
void mat3x3InverseInto(Mat4x3, Mat4x3);
extern void releaseSceneObjectMeshTree(s32);
extern s32 getControllerNewButtonsPressed(u8);
extern s32 getGameOrFrontText(s32);
extern s32 isAnimInstanceActive(s32);
extern s32 isPlayerShipActive();
extern void markStructInitializedOnce(s32);
extern void startPlayerSlotAnimationChannel(s32, s32);
extern void stopVoiceByHandleLocked(s32);
extern void setVoiceLineLoopFlag(s32);
extern void queueAudioVoiceCmd(s32, s32, s32, s32);

void handleCraftSelectInput(void) {
    Mat4x3 m;
    u8 sp40[8];
    f32 e;
    f32 t;
    f32 inv;
    u8 v;
    s32 n;

    bridgeRotationAngle = bridgeRotationAngle + bridgeRotationVelocityMultiplier * 5.0f;
    if (bridgeRotationAngle >= 360.0f) {
        bridgeRotationAngle = bridgeRotationAngle - 360.0f;
    }
    switch (bridgeTransitionState) {
    case 0:
        if (bridgeMenuDisplayLevel != bridgeMenuDesiredLevel) {
            safeLookup3DSoundEntry(bsearchFactor5TableByU16Key(0x2C, 0x51, 0x40), 0);
            D_menu_overlay_800CDB00 = 0.0f;
            bridgeTransitionState = 1;
        }
        break;
    case 1:
        D_menu_overlay_800CDB00 = D_menu_overlay_800CDB00 + bridgeRotationVelocityMultiplier * 1.2717f;
        if (D_menu_overlay_800CDB00 > 1.0f) {
            D_menu_overlay_800CDB00 = 1.0f;
        }
        D_menu_overlay_800CDAF0 = 1.0f - quadraticEaseInOut(D_menu_overlay_800CDB00);
        if (D_menu_overlay_800CDB00 >= 1.0f) {
            if (D_menu_overlay_800CDAB9 == 1) {
                if (!(isPlayerShipActive() & 0xFF)) {
                    playExitSoundAndToggleScreenMeshes();
                }
                bridgeMenuState = 4;
                D_menu_overlay_800CDACC = bridgeMenuDesiredLevel;
            } else {
                D_menu_overlay_800CDAC6 = 0;
                bridgeTransitionState = 2;
                bridgeMenuDisplayLevel = bridgeMenuDesiredLevel;
                if (D_menu_overlay_800CDABA == 0) {
                    sprintf(D_menu_overlay_800CDA90, D_menu_overlay_800A58BC, bridgeMenuDisplayLevel);
                    enqueueFormatMessage(D_menu_overlay_800CDD70, D_menu_overlay_800CDA90);
                }
            }
        }
        break;
    case 2:
        if ((pollServiceMessageByte(sp40) & 0xFF) || D_menu_overlay_800CDABA != 0) {
            if (D_menu_overlay_800CDABA == 0) {
                layoutMenuTextRow((struct some_ui_list_root *)D_menu_overlay_800CDCDC, bridgeMenuDisplayLevel);
            }
            safeLookup3DSoundEntry(bsearchFactor5TableByU16Key(0x2C, 0x51, 0x40), 0x3000);
            D_menu_overlay_800CDB00 = 0.0f;
            D_menu_overlay_800CDABA = 0;
            bridgeTransitionState = 3;
        }
        break;
    case 3:
        D_menu_overlay_800CDB00 = D_menu_overlay_800CDB00 + bridgeRotationVelocityMultiplier * 1.2717f;
        if (D_menu_overlay_800CDB00 > 1.0f) {
            D_menu_overlay_800CDB00 = 1.0f;
        }
        D_menu_overlay_800CDAF0 = e = quadraticEaseInOut(D_menu_overlay_800CDB00);
        if (D_menu_overlay_800CDAB8 == 1) {
            t = quadraticEaseInOut(D_menu_overlay_800CDB00) * -300.0f;
            D_menu_overlay_800CDAFC = e;
            D_menu_overlay_800CDAE4 = t;
            inv = 1.0f - e;
            D_menu_overlay_800CDADC = inv * -8.0f + e * -1.6f;
            D_menu_overlay_800CDAD4 = inv * -6.1f + e * -3.6f;
            D_menu_overlay_800CDAD8 = inv * -43.0f + e * -36.5f;
        }
        if (D_menu_overlay_800CDB00 == 1.0f) {
            if (D_menu_overlay_800CDAB8 == 1) {
                D_menu_overlay_800CDB20[2].next = NULL;
                applyFlagsToMeshTreeOrList(csModels[2].mesh, 0, 0x20000000, 0);
                applyFlagsToMeshTreeOrList(csModels[3].mesh, 0, 0x20000000, 0);
                releaseSceneObjectMeshTree(csModels[2].mesh);
                releaseSceneObjectMeshTree(csModels[3].mesh);
                requestViFeatureChange(1);
                D_menu_overlay_800CDAB8 = 0;
            }
            v = 2;
            D_menu_overlay_800CDB00 = 0.0f;
            if (D_menu_overlay_800CDAC7 == 1) {
                v = 3;
            }
            bridgeMenuState = v;
            D_menu_overlay_800CDABF = 0;
            bridgeTransitionState = 0;
        }
        break;
    }
    if (bridgeMenuState == 2 || bridgeMenuState == 3) {
        if (bridgeTransitionState == 0 && D_menu_overlay_800CDAC0 == 0
            && ((getControllerNewButtonsPressed(D_menu_overlay_800CDAC8) & 0xF) || D_menu_overlay_800CDABD != 0)) {
            D_menu_overlay_800CDABD = 0;
            if (D_menu_overlay_800CDABB == 0) {
                if (isStructUninitialized(D_menu_overlay_800CDFAC) & 0xFF) {
                    D_menu_overlay_800CDABB = 1;
                    setMenuOverlayHeaderState(5, 0, 0x128);
                    startPlayerSlotAnimationChannelFlagged(D_menu_overlay_800CDFAC, getGameOrFrontText(bridgeMenuDesiredLevel + 0x21), 8);
                    setMenuOverlayHeaderState(2, 0x200, 0);
                    D_menu_overlay_800CDAC0 = -1;
                }
            } else {
                markStructInitializedOnce(D_menu_overlay_800CDFAC);
                if (D_menu_overlay_800CC700 != -1) {
                    stopVoiceByHandleLocked(D_menu_overlay_800CC700);
                    D_menu_overlay_800CC700 = -1;
                }
                D_menu_overlay_800CDABC = 1;
                D_menu_overlay_800CDABF = 1;
                D_menu_overlay_800CDB0C = -10.0f;
            }
        }
    }
    switch (bridgeMenuState) {
    case 0:
        D_menu_overlay_800CDAE8 = 0.0f;
        D_menu_overlay_800CDAEC = 0.0f;
        D_menu_overlay_800CDAE4 = 0.0f;
        D_menu_overlay_800CDAB8 = 1;
        D_menu_overlay_800CDAB9 = 0;
        D_menu_overlay_800CDAF0 = 0.0f;
        D_menu_overlay_800CDAF4 = 0;
        D_menu_overlay_800CDAFC = 0.0f;
        bridgeMenuState = 1;
        D_menu_overlay_800CDABA = 0;
        D_menu_overlay_800CDABD = 0;
        bridgeDisplayFlickerTimer = 5.0f;
        D_menu_overlay_800CDADC = -8.0f;
        D_menu_overlay_800CDAD4 = -6.1f;
        D_menu_overlay_800CDAD8 = -43.0f;
        D_menu_overlay_800CDB08 = 0.8f;
    case 1:
        D_menu_overlay_800CDAE8 = D_menu_overlay_800CDAE8 + bridgeRotationVelocityMultiplier;
        if (D_menu_overlay_800CDAE8 >= 0.5f) {
            D_menu_overlay_800CDAE8 = 0.0f;
            bridgeMenuState = 2;
            D_menu_overlay_800CDB00 = 0.0f;
            bridgeTransitionState = 3;
            safeLookup3DSoundEntry(bsearchFactor5TableByU16Key(0x2C, 0x51, 0x40), 0x3000);
            D_menu_overlay_800CE6A8 = 1.0f;
        }
        break;
    case 2:
        D_menu_overlay_800CDAE8 = D_menu_overlay_800CDAE8 + bridgeRotationVelocityMultiplier;
        D_menu_overlay_800CDAEC = D_menu_overlay_800CDAE8 / 5.0f;
        if (D_menu_overlay_800CDAEC >= 0.3f) {
            D_menu_overlay_800CDAEC = 0.3f;
        }
        if (getControllerNewButtonsPressed(D_menu_overlay_800CDAC8) & 0x800200) {
            bridgeMenuPreviousLevel = bridgeMenuDesiredLevel;
            if (bridgeMenuDesiredLevel != 0) {
                bridgeMenuDesiredLevel--;
            }
        lvl_changed:
            if (bridgeMenuPreviousLevel != bridgeMenuDesiredLevel) {
                bsearchFactor5TableByU16Key(0x17, 0x64, 0x40);
                startPlayerSlotAnimationChannel(D_menu_overlay_800CDFA4, getGameOrFrontText(bridgeMenuDesiredLevel));
                if (D_menu_overlay_800CDFB0 != 0) {
                    setVoiceLineLoopFlag(D_menu_overlay_800CDFB0);
                }
                D_menu_overlay_800CDB0C = 1.0f;
                if (D_menu_overlay_800CDABB != 0) {
                    markStructInitializedOnce(D_menu_overlay_800CDFAC);
                    if (D_menu_overlay_800CC700 != -1) {
                        stopVoiceByHandleLocked(D_menu_overlay_800CC700);
                        D_menu_overlay_800CC700 = -1;
                    }
                    D_menu_overlay_800CDABC = 1;
                    D_menu_overlay_800CDABB = 0;
                    D_menu_overlay_800CDABD = 1;
                }
            }
        } else if (getControllerNewButtonsPressed(D_menu_overlay_800CDAC8) & 0x400100) {
            bridgeMenuPreviousLevel = bridgeMenuDesiredLevel;
            n = bridgeMenuDesiredLevel + 1;
            if ((1 << n) & D_menu_overlay_800CDAD0) {
                bridgeMenuDesiredLevel = n;
            }
            goto lvl_changed;
        } else if ((getControllerNewButtonsPressed(D_menu_overlay_800CDAC8) & 0x9000) && !(isAnimInstanceActive(D_menu_overlay_800CDFA8) & 0xFF)
            && bridgeTransitionState == 0) {
            if (D_menu_overlay_800CDABB != 0) {
                markStructInitializedOnce(D_menu_overlay_800CDFAC);
                if (D_menu_overlay_800CC700 != -1) {
                    stopVoiceByHandleLocked(D_menu_overlay_800CC700);
                    D_menu_overlay_800CC700 = -1;
                }
                D_menu_overlay_800CDABB = 0;
                D_menu_overlay_800CDABC = 1;
            }
            bsearchFactor5TableByU16Key(0x18, 0x5F, 0x40);
            startPlayerSlotAnimationChannel(D_menu_overlay_800CDFA8, getGameOrFrontText(0x3A));
            printLevelSelectWeaponText2(bridgeMenuDesiredLevel, 0);
            bridgeMenuState = 3;
            D_menu_overlay_800CDAC7 = 1;
            D_menu_overlay_800CE6A8 = -1.0f;
        }
        break;
    case 3:
        if ((getControllerNewButtonsPressed(D_menu_overlay_800CDAC8) & 0x9000) && !(isAnimInstanceActive(D_menu_overlay_800CDFA8) & 0xFF)
            && D_menu_overlay_800CDAB9 == 0) {
            if (D_menu_overlay_800CDABB != 0) {
                markStructInitializedOnce(D_menu_overlay_800CDFAC);
                if (D_menu_overlay_800CC700 != -1) {
                    stopVoiceByHandleLocked(D_menu_overlay_800CC700);
                    D_menu_overlay_800CC700 = -1;
                }
                D_menu_overlay_800CDABB = 0;
                D_menu_overlay_800CDABC = 1;
            }
            bsearchFactor5TableByU16Key(0x18, 0x5F, 0x40);
            queueAudioVoiceCmd(0, 0x3E8, D_menu_overlay_800CDCE0, 1);
            playSimpleAudioCmd(0, 0x3E8, 0xFE);
            D_menu_overlay_800CDAB9 = 1;
            D_menu_overlay_800CDABA = 1;
            bridgeMenuDisplayLevel = 0xFF;
            bridgeMenuState = 4;
        }
        break;
    case 4:
        break;
    }
    clearVec4QuadStruct(m);
    composeRotationMatrixSlot0(m, D_menu_overlay_800CDADC);
    addVec3At0x24(m, 0.0f, D_menu_overlay_800CDAD4, D_menu_overlay_800CDAD8 + sinf(D_menu_overlay_800CDB14 / 10.0f) * D_menu_overlay_800CDAEC * 0.1f + 0.2f);
    composeRotationMatrixSlot1(m, bridgeRotationAngle);
    mat3x3InverseInto((void *)((u8 *)&csMain + 0x2C), m);
}

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A5994);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", bridgeOuterBlueLightPositions);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A59C4);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/115E00", spawnOrientedEffectWithEasedSpin);

extern u8 D_menu_overlay_800CDABB;
extern s8 D_menu_overlay_800CDABC;
extern u8 D_menu_overlay_800CDABE;
extern s8 D_menu_overlay_800CDAC0;
extern u8 D_menu_overlay_800CDAC7;
extern u8 D_menu_overlay_800CDAC8;
extern s32 D_menu_overlay_800CDACC;
extern s32 D_menu_overlay_800CDFA8;
extern s32 D_menu_overlay_800CDFAC;
extern f32 D_menu_overlay_800CE6A8;
extern u8 bridgeMenuState;
extern u8 bridgeTransitionState;
extern s32 getControllerNewButtonsPressed(u8);
extern s32 getGameOrFrontText(s32);
extern s32 isAnimInstanceActive(s32);
extern s32 isPlayerShipActive();
extern void markStructInitializedOnce(s32);
extern void startPlayerSlotAnimationChannel(s32, s32);
extern void stopVoiceByHandleLocked(s32);
extern s32 bsearchFactor5TableByU16Key(s32, s32, s32);

void handleLevelSelectStartConfirm(void) {
    u8 start = 0;
    if ((u8)(bridgeMenuState - 2) < 2U) {
        if (bridgeTransitionState == 0 && D_menu_overlay_800CDAC0 == 0) {
            if (getControllerNewButtonsPressed(D_menu_overlay_800CDAC8) & 0x4000) {
                start = D_menu_overlay_800CDABE == 0;
            }
        }
    }
    if ((start != 0) || (D_menu_overlay_800CDABE != 0)) {
        if (!(isAnimInstanceActive(D_menu_overlay_800CDFA8) & 0xFF)) {
            if (D_menu_overlay_800CDABB != 0) {
                markStructInitializedOnce(D_menu_overlay_800CDFAC);
                if (D_menu_overlay_800CC700 != -1) {
                    stopVoiceByHandleLocked(D_menu_overlay_800CC700);
                    D_menu_overlay_800CC700 = -1;
                }
                D_menu_overlay_800CDABB = 0;
                D_menu_overlay_800CDABC = 1;
            }
            if (D_menu_overlay_800CDAC7 == 1) {
                startPlayerSlotAnimationChannel(D_menu_overlay_800CDFA8, getGameOrFrontText(0x39));
                bsearchFactor5TableByU16Key(0x19, 0x5F, 0x40);
                bridgeMenuState = 2;
                D_menu_overlay_800CDAC7 = 0;
                D_menu_overlay_800CE6A8 = 1.0f;
            } else if (!(isPlayerShipActive() & 0xFF)) {
                playExitSoundAndToggleScreenMeshes();
                bridgeMenuState = 4;
                bridgeTransitionState = 0;
                D_menu_overlay_800CDACC = 0xFFFFFE;
            }
        }
    }
}

void tickMenuTransitionState(void) {
    if (*(u8 *)&D_menu_overlay_800CDABC != 0 && (u8)isStructUninitialized(D_menu_overlay_800CDFAC) != 0) {
        D_menu_overlay_800CDAC0 = 1;
        D_menu_overlay_800CDABC = 0;
    }
    if (D_menu_overlay_800CDAC0 == -1) {
        if (D_menu_overlay_800CDB04 <= 0.3f) {
            D_menu_overlay_800CDB04 = 0.3f;
            D_menu_overlay_800CDAC0 = 0;
        } else {
            D_menu_overlay_800CDB04 -= bridgeRotationVelocityMultiplier;
            if (D_menu_overlay_800CDB04 <= 0.0f) {
                D_menu_overlay_800CDB04 = 0.0f;
            }
        }
    } else if (D_menu_overlay_800CDAC0 == 1) {
        if (1.0f <= D_menu_overlay_800CDB04) {
            D_menu_overlay_800CDB04 = 1.0f;
            D_menu_overlay_800CDAC0 = 0;
            D_menu_overlay_800CDABB = 0;
        } else {
            D_menu_overlay_800CDB04 += bridgeRotationVelocityMultiplier;
            if (1.0f <= D_menu_overlay_800CDB04) {
                D_menu_overlay_800CDB04 = 1.0f;
            }
        }
    }
}

extern f32 D_menu_overlay_800CDB08;
s16 rand(void);
void activateAnimationKeyframe(s32, s32, u8);

void runScriptedCraftCinematicEvent(f32 dt) {
    f32 glow;
    f32 base;
    f32 wave;
    f32 w;
    f32 h;
    f32 a;
    f32 b;
    f32 lim;
    f32 alpha;
    f32 t;
    f32 b04;
    u32 i;
    struct xy_offset *pos;
    f32 *hs;
    f32 *ws;
    struct ui_element *bp;

    D_menu_overlay_800CDD74->rgba.a = 0xD2;
    D_menu_overlay_800CDD78->rgba.a = 0x8C;
    if (bridgeMenuState == 2 || bridgeMenuState == 3) {
        bridgeDisplayFlickerTimer = bridgeDisplayFlickerTimer - dt;
        if (bridgeDisplayFlickerTimer < 0.0f) {
            if (bridgeDisplayFlickerTimer + dt >= 0.0f) {
                bsearchFactor5TableByU16Key(0x2D, 0x50, 0x40);
            }
            D_menu_overlay_800CDD78->rgba.a = rand() % 63 + 0x50;
            if (bridgeDisplayFlickerTimer < -0.4f) {
                bridgeDisplayFlickerTimer = (rand() & 7) + 2.0f;
            }
        }
    }
    glow = sinf(D_menu_overlay_800CDB18 * 0.125f) * 0.3f + 0.6f;
    if ((bridgeTransitionState == 1 || bridgeTransitionState == 3) && bridgeMenuState != 4) {
        glow *= D_menu_overlay_800CDAF0;
    }
    D_menu_overlay_800CDB20[2].f2C = glow;
    D_menu_overlay_800CDB20[3].f10 = D_menu_overlay_800CDAE4;
    D_menu_overlay_800CDB20[2].f24 = glow * 0.25f;
    D_menu_overlay_800CDB20[2].f28 = glow * 0.4f;
    if (bridgeTransitionState != 2 && bridgeMenuState != 4) {
        applyFlagsToMeshTreeOrList(csModels[0].mesh, 0, 0x20, 0x100000);
        applyFlagsToMeshTreeOrList(csModels[1].mesh, 0, 0x20, 0x100000);
        applyFlagsToMeshTreeOrList(csModels[2].mesh, 0, 0x20, 0x100000);
        applyFlagsToMeshTreeOrList(csModels[3].mesh, 0, 0x20, 0x100000);
        D_menu_overlay_800CDB18 += dt * 30.0f;
    } else {
        applyFlagsToMeshTreeOrList(csModels[0].mesh, 0, 0, 0x20);
        applyFlagsToMeshTreeOrList(csModels[1].mesh, 0, 0, 0x20);
        applyFlagsToMeshTreeOrList(csModels[2].mesh, 0, 0, 0x20);
        applyFlagsToMeshTreeOrList(csModels[3].mesh, 0, 0, 0x20);
    }
    wave = sinf(D_menu_overlay_800CDB14 / 3.0f);
    base = (quadraticEaseInOut(D_menu_overlay_800CDAF0) * 0.85f + 0.15f) * 0.9f;
    D_menu_overlay_800CDD74->rgba.r = wave * 24.0f + 200.0f;
    D_menu_overlay_800CDD74->rgba.g = wave * 24.0f + 200.0f;
    D_menu_overlay_800CDD74->rgba.b = wave * 25.0f + 230.0f;
    w = sinf(D_menu_overlay_800CDB14 / 13.0f) * 0.03f + base;
    h = sinf(D_menu_overlay_800CDB14 / 19.0f) * 0.03f + base;
    D_menu_overlay_800CDD74->width_scale = w;
    D_menu_overlay_800CDD74->xpos = w * -160.0f;
    D_menu_overlay_800CDD74->height_scale = h;
    D_menu_overlay_800CDD74->ypos = h * -105.0f - 45.0f;
    if (bridgeDisplayFlickerTimer < 0.0f) {
        w += (rand() & 0xF) / 100.0f;
        h += (rand() & 0xF) / 100.0f;
        wave = (rand() & 0xF) / 15.0f;
    }
    D_menu_overlay_800CDD78->rgba.r = wave * 25.0f + 230.0f;
    D_menu_overlay_800CDD78->rgba.b = wave * 24.0f + 200.0f;
    D_menu_overlay_800CDD78->rgba.g = wave * 24.0f + 200.0f;
    D_menu_overlay_800CDD78->xpos = w * -160.0f + (rand() & 3);
    D_menu_overlay_800CDD78->ypos = h * -105.0f - 45.0f + (rand() & 1);
    D_menu_overlay_800CDD78->width_scale = w;
    D_menu_overlay_800CDD78->height_scale = h;
    if (D_menu_overlay_800CDAC7 == 1) {
        if (D_menu_overlay_800CDB08 > 0.09f) {
            D_menu_overlay_800CDB08 = D_menu_overlay_800CDB08 - dt;
            if (D_menu_overlay_800CDB08 < 0.09f) {
                D_menu_overlay_800CDB08 = 0.09f;
            }
        }
    } else {
        if (D_menu_overlay_800CDB08 < 0.8f) {
            D_menu_overlay_800CDB08 = D_menu_overlay_800CDB08 + dt;
            if (D_menu_overlay_800CDB08 > 0.8f) {
                D_menu_overlay_800CDB08 = 0.8f;
            }
        }
    }
    t = D_menu_overlay_800CDB08;
    D_menu_overlay_800CDD74->rgba.a = D_menu_overlay_800CDD74->rgba.a * D_menu_overlay_800CDAF0 * quadraticEaseInOut(D_menu_overlay_800CDB04) * t;
    D_menu_overlay_800CDD78->rgba.a = D_menu_overlay_800CDD78->rgba.a * D_menu_overlay_800CDAF0 * quadraticEaseInOut(D_menu_overlay_800CDB04) * t;
    b04 = D_menu_overlay_800CDB04;
    __asm__("" :: "f"(b04));
    if (D_menu_overlay_800CDAC7 != 1) {
        wave = 0.0f;
    } else {
        wave = D_menu_overlay_800CDAF0 * 245.0f * b04;
        if (bridgeDisplayFlickerTimer < 0.0f) {
            wave = D_menu_overlay_800CDAF0 * ((s16)(rand() % 63) + 0x50);
        }
    }
    for (i = 0; i < 9; i++) {
        if (getAvailablePlayerCraftFlagsIgnoreUnlocks(bridgeMenuDesiredLevel) & (1 << i)) {
            bridgeShipBlueprints[i].rgba.a = wave;
            bridgeShipBlueprints[i].width_scale = w * bridgeShipBlueprintWidthScales[i];
            bridgeShipBlueprints[i].height_scale = h * bridgeShipBlueprintHeightScales[i];
            bridgeShipBlueprints[i].xpos = D_menu_overlay_800CDF80[i].x - (bridgeShipBlueprints[i].width_scale * 64.0f - 64.0f) * 0.5f;
            bridgeShipBlueprints[i].ypos = D_menu_overlay_800CDF80[i].y - (bridgeShipBlueprints[i].height_scale * 64.0f - 64.0f) * 0.5f;
            setLookupEntryField5ByKey((struct some_ui_list_root *)D_menu_overlay_800CDCDC, &bridgeShipBlueprints[i], wave != 0.0f);
        }
    }
    a = 1.0f - (D_menu_overlay_800CDB08 - 0.09f) * 1.4084506f;
    if (a < 0.0f) {
        a = 0.0f;
    }
    if (a > 1.0f) {
        a = 1.0f;
    }
    if (bridgeMenuState == 4) {
        a *= D_menu_overlay_800CDAF0;
    }
    b = (D_menu_overlay_800CDB04 - 0.3f) * 1.4285715f;
    if (b < 0.0f) {
        b = 0.0f;
    }
    if (b > 1.0f) {
        b = 1.0f;
    }
    a *= b;
    activateAnimationKeyframe(2, 1, (u8)(a * 255.0f));
}

struct HobBlk { u8 b[0xFC]; };
extern struct HobBlk bridgeBlueLightHobs[7];
extern void clearStructPair2C30(u8 *);

void initMenuWidgetArray(void) {
    u32 i;
    u32 j;
    u8 *p;
    u8 *q;
    u8 v;
    f32 *vtx;

    for (i = 0; i < 7; i++) {
        p = bridgeBlueLightHobs[i].b;
        q = p + 0x4C;
        *(s32 *)(p + 0x58) = 0x09000009;
        *(s32 *)(p + 0xC) = 0;
        *(s32 *)(p + 0x8) = 0;
        *(s32 *)(p + 0x4) = 0;
        *(s32 *)(p + 0x0) = 0;
        *(u8 **)(p + 0x10) = q;
        *(s32 *)(p + 0x60) = 3;
        *(u8 **)(p + 0x6C) = p + 0xA8;
        *(s32 *)(p + 0x14) = 0;
        *(s32 *)(p + 0x50) = 0;
        *(s32 *)(p + 0x4C) = 0;
        *(s32 *)(p + 0x54) = 0;
        *(s32 *)(p + 0x68) = 0;
        *(s32 *)(p + 0x5C) = 0;
        *(s32 *)(p + 0x64) = 0;
        *(u8 **)(p + 0x70) = p + 0xD8;
        *(s32 *)(p + 0x74) = 0;
        clearStructPair2C30(q);
        *(u8 **)(p + 0xB0) = p + 0xB8;
        *(s32 *)(p + 0xB8) = 0x10;
        *(s32 *)(p + 0xAC) = 0;
        *(s32 *)(p + 0xA8) = 0;
        *(s32 *)(p + 0xB4) = 1;
        *(s32 *)(p + 0xBC) = 0x080C5000;
        *(s32 *)(p + 0xC0) = 0;
        *(f32 *)(p + 0xC0) = 0;
        *(s32 *)(p + 0xB8) |= 0x82;
        for (j = 0; j < 3; j++) {
            *(u16 *)(p + 0xC4 + j * 2) = j;
        }
        if (i == 0) {
            p[0xCC] = 0xB4;
            p[0xCD] = 0xB4;
            p[0xCE] = 0xF5;
            p[0xCF] = 0;
            p[0xD0] = 0xB4;
            p[0xD1] = 0xB4;
            p[0xD2] = 0xF5;
            p[0xD3] = 0;
            p[0xD4] = 0;
            p[0xD5] = 0;
            p[0xD6] = 0xA0;
            p[0xD7] = 0;
        } else {
            if (i < 4) {
                p[0xD4] = 0x50;
                p[0xD5] = 0x50;
                p[0xCC] = 0xFF;
                p[0xCD] = 0xFF;
                p[0xCE] = 0xFF;
                p[0xCF] = 0;
                p[0xD0] = 0xFF;
                p[0xD1] = 0xFF;
                p[0xD2] = 0xFF;
                p[0xD3] = 0;
                p[0xD6] = 0xFF;
                p[0xD7] = 0xC8;
            } else {
                p[0xD4] = 0x1E;
                p[0xD5] = 0x1E;
                p[0xD6] = 0xE1;
                p[0xCC] = 0;
                p[0xCD] = 0;
                p[0xCE] = 0x37;
                p[0xCF] = 0;
                p[0xD0] = 0;
                p[0xD1] = 0;
                p[0xD2] = 0x37;
                p[0xD3] = 0;
                p[0xD7] = 0x9B;
            }
        }
        vtx = *(f32 **)(p + 0x70);
        vtx[0] = 1.0f;
        vtx[1] = -2.0f;
        vtx[2] = 0;
        vtx[3] = -1.0f;
        vtx[4] = -2.0f;
        vtx[5] = 0;
        vtx[6] = 0;
        vtx[7] = 0;
        vtx[8] = 0;
    }
}

void bridgeLoadShipBlueprints(struct some_ui_list_root *arg0) {
    char sp10[0x20];
    char *bridgeShipBlueprintNames[9] = {
        "xwing",
        "ywing",
        "awing",
        "vwing",
        "speeder",
        "falcon",
        "interceptor",
        "t16",
        "xwing",
    };
    struct material_entry sp58;
    u32 var_s4;
    struct full_image_header *temp_v0;
    struct texture_entry *temp_s0;

    for (var_s4 = 0; var_s4 < 9; var_s4++) {
        sprintf(sp10, "blueprints/%s", bridgeShipBlueprintNames[var_s4]);
        temp_v0 = load_asset(sp10);
        temp_s0 = &temp_v0->ent;
        full_header_image_offset_convert(temp_s0, (u32)temp_s0);
        sp58.material_type = 1;
        rs_strcpy(sp58.material_name, (u8 *) temp_s0->texture_name_offset);
        temp_s0->flags_type = 0x2004;
        bridgeShipBlueprintTextureIds[var_s4] = registerHmtTextureInTable(&sp58, temp_s0, 1U);
        rs_memset(&bridgeShipBlueprints[var_s4], 0U, 0x30U);
        bridgeShipBlueprints[var_s4].texture_id_pointer = &bridgeShipBlueprintTextureIds[var_s4];
        bridgeShipBlueprints[var_s4].unknown0A = 1;
        bridgeShipBlueprints[var_s4].texture_count = 1;
        bridgeShipBlueprints[var_s4].width_scale = bridgeShipBlueprintWidthScales[var_s4];
        bridgeShipBlueprints[var_s4].height_scale = bridgeShipBlueprintHeightScales[var_s4];
        bridgeShipBlueprints[var_s4].flags = 3;
        bridgeShipBlueprints[var_s4].rgba.r = 0;
        bridgeShipBlueprints[var_s4].rgba.g = 0;
        bridgeShipBlueprints[var_s4].rgba.b = 0;
        bridgeShipBlueprints[var_s4].rgba.a = 0xFF;
        insertLookupEntry(arg0, &bridgeShipBlueprints[var_s4], 0xAU);
        rs_free(temp_v0);
    }
}

#if 0
// Really close, permuter hasn't turned anything up yet
// Functionally identical though, which is a good sign
// https://decomp.me/scratch/mkgBu
void layoutMenuTextRow(struct some_ui_list_root *arg0, u8 arg1) {
    f32 temp_fv0;
    s32 temp_s4;
    s32 temp_s6;
    s32 var_v1;
    u32 var_s0;

    temp_s6 = getAvailablePlayerCraftFlagsConsiderUnlocks(arg1);
    temp_s4 = getAvailablePlayerCraftFlagsIgnoreUnlocks(arg1);
    var_v1 = 0;
    for (var_s0 = 0; var_s0 < 9; var_s0++) {
        if (temp_s4 & (1 << var_s0)) var_v1++;
    }
    for (var_s0 = 0; var_s0 < 9; var_s0++) {
        if (temp_s4 & (1 << var_s0)) {
            temp_fv0 = (((bridgeShipBlueprintScreenPositions[var_v1 - 1][var_s0].x / 1.5f) - 32.0f) * 512.0f) / 512.0f;
            bridgeShipBlueprints[var_s0].xpos = temp_fv0;
            D_menu_overlay_800CDF80[var_s0].x = temp_fv0;
            temp_fv0 = (((bridgeShipBlueprintScreenPositions[var_v1 - 1][var_s0].y / 1.1f) - 75.0f) * 340.0f) / 340.0f;
            bridgeShipBlueprints[var_s0].ypos = temp_fv0;
            D_menu_overlay_800CDF80[var_s0].y = temp_fv0;
        }
        if (temp_s6 & (1 << var_s0)) {
            bridgeShipBlueprints[var_s0].rgba = bridgeGreenColor;
        } else {
            bridgeShipBlueprints[var_s0].rgba = bridgeRedColor;
        }
        setLookupEntryField5ByKey(arg0, &bridgeShipBlueprints[var_s0], (temp_s4 & (1 << var_s0)) != 0);
    }
}
#else
void layoutMenuTextRow(struct some_ui_list_root *arg0, u8 arg1) {
    f32 temp_fv0;
    s32 temp_s4;
    s32 temp_s6;
    s32 var_v1;
    u32 var_s0;
    s32 j;

    temp_s6 = getAvailablePlayerCraftFlagsConsiderUnlocks(arg1);
    temp_s4 = getAvailablePlayerCraftFlagsIgnoreUnlocks(arg1);
    var_v1 = 0;
    var_s0 = 0;
    do {
        if (temp_s4 & (1 << var_s0)) var_v1++;
        var_s0++;
    } while (var_s0 < 9);
    j = 0;
    for (var_s0 = 0; var_s0 < 9; var_s0++) {
        if (temp_s4 & (1 << var_s0)) {
            temp_fv0 = (((bridgeShipBlueprintScreenPositions[var_v1 - 1][j].x / 1.5f) - 32.0f) * 512.0f) * 0.001953125f;
            bridgeShipBlueprints[var_s0].xpos = temp_fv0;
            D_menu_overlay_800CDF80[var_s0].x = temp_fv0;
            temp_fv0 = (((bridgeShipBlueprintScreenPositions[var_v1 - 1][j].y / 1.1f) - 75.0f) * 340.0f) / 340.0f;
            bridgeShipBlueprints[var_s0].ypos = temp_fv0;
            D_menu_overlay_800CDF80[var_s0].y = temp_fv0;
            j++;
        }
        if (temp_s6 & (1 << var_s0)) {
            bridgeShipBlueprints[var_s0].rgba = bridgeGreenColor;
        } else {
            bridgeShipBlueprints[var_s0].rgba = bridgeRedColor;
        }
        setLookupEntryField5ByKey(arg0, &bridgeShipBlueprints[var_s0], (temp_s4 & (1 << var_s0)) != 0);
    }
}
#endif

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/115E00", D_menu_overlay_800A5BA4);

extern u32 D_main_bss_80130B4C;
extern char D_menu_overlay_800A5BA4[];
void setPlayerSlotAnimationFlag(s32, char *, s32, s32, s16);

void printLevelSelectWeaponText(u8 arg0) {
    char buf[0x100];
    char *a;
    char *b;
    char *c;
    char *d;
    char *e;
    s32 flags;
    s32 n;
    s32 i;
    u16 y;

    n = 0;
    flags = getAvailablePlayerCraftFlagsIgnoreUnlocks(arg0);
    i = 0;
    do {
        if (flags & (1 << i)) {
            n++;
        }
        i++;
    } while ((u8)i < 9U);
    a = getGameOrFrontText(0x48);
    if (D_main_bss_80130B4C & 0x200) {
        b = getGameOrFrontText(0x4B);
    } else {
        b = D_menu_overlay_800A5BA4;
    }
    c = getGameOrFrontText(0x4D);
    d = getGameOrFrontText(0x4A);
    if (D_main_bss_80130B4C & 0x10000) {
        e = getGameOrFrontText(0x4B);
    } else {
        e = D_menu_overlay_800A5BA4;
    }
    sprintf(buf, "%s%s%s\n%s%s%s", a, b, c, d, e, getGameOrFrontText(0x4C));
    y = 0xFFD0;
    if (n == 1) {
        y = 0xFFFD;
    }
    setPlayerSlotAnimationFlag(2, buf, 1, -0x100, y);
    setPlayerSlotEntryRGB(2, 1, &bridgeWhiteColor);
}

extern s32 D_menu_overlay_800CDFB0;
extern u8 bridgeMenuDesiredLevel;
extern u8 D_menu_overlay_800CDABF;
extern f32 D_menu_overlay_800CDB0C;
extern void setVoiceLineLoopFlag(s32);
s32 mallocVoiceLineStruct(u16 *, f32, s32);
s32 startPlayerSlotAnimationChannelLooping(s32, f32);

void startSlotLoopAnimWithVoiceSync(f32 arg0) {
    u16 sp10[2] = {0, 0xFFFF};
    s32 r;

    r = startPlayerSlotAnimationChannelLooping(D_menu_overlay_800CDFAC, arg0) & 0xFF;
    switch (r) {
    case 1:
        if (D_menu_overlay_800CDFB0 == 0) {
            sp10[0] = bridgeMenuDesiredLevel + 0x279;
            D_menu_overlay_800CDFB0 = mallocVoiceLineStruct(sp10, 0.7f, 0x6E);
            D_menu_overlay_800CDABF = r;
            D_menu_overlay_800CDB0C = -10.0f;
        }
        D_menu_overlay_800CC700 = bsearchFactor5TableByU16Key(0x43, 0x32, 0x40);
        break;
    case 2:
        stopVoiceByHandleLocked(D_menu_overlay_800CC700);
        D_menu_overlay_800CC700 = -1;
        break;
    case 3:
        if (D_menu_overlay_800CDFB0 != 0) {
            setVoiceLineLoopFlag(D_menu_overlay_800CDFB0);
        }
        stopVoiceByHandleLocked(D_menu_overlay_800CC700);
    case 4:
        bsearchFactor5TableByU16Key(0x42, 0x55, 0x40);
        break;
    }
    if (bridgeTransitionState == 0) {
        D_menu_overlay_800CDB0C = D_menu_overlay_800CDB0C - arg0;
        if (D_menu_overlay_800CDB0C > -5.0f && D_menu_overlay_800CDB0C < 0.0f && D_menu_overlay_800CDABF == 0 && D_menu_overlay_800CDFB0 == 0 && bridgeMenuState != 4) {
            sp10[0] = bridgeMenuDesiredLevel + 0x279;
            D_menu_overlay_800CDFB0 = mallocVoiceLineStruct(sp10, 0.7f, 0x6E);
            D_menu_overlay_800CDABF = 1;
            D_menu_overlay_800CDB0C = -10.0f;
        }
    }
}

void samplePlayerAnimChannel(s32, s32, f32);
void activateAnimationKeyframe(s32, s32, u8);
struct ui_element *getPlayerSlotFieldAt34(u16, u16);
void setPlayerSlotEntryRGB(u16, u16, struct rgba *);
extern s32 D_menu_overlay_800CDCDC;

void setupPlayerCraftDisplayAnim(void) {
    u8 i;
    s32 k;

    setPlayerSlotAnimationFlag(0, "XX", 6, -0x100, 0x72);
    setPlayerSlotAnimationFlag(0, "XX", 9, -0x100, 0x72);
    samplePlayerAnimChannel(0, 6, 1.0f);
    i = 4;
    samplePlayerAnimChannel(0, 9, 1.0f);
    relocateLookupEntryToNewKey((struct some_ui_list_root *)D_menu_overlay_800CDCDC, getPlayerSlotFieldAt34(0, 6), 0x19);
    relocateLookupEntryToNewKey((struct some_ui_list_root *)D_menu_overlay_800CDCDC, getPlayerSlotFieldAt34(0, 9), 0x19);
    setPlayerSlotAnimationFlag(0, "{", 4, -0x100, 0x76);
    setPlayerSlotAnimationFlag(0, "{", 7, -0x100, 0x76);
    setPlayerSlotAnimationFlag(0, "}", 5, -0x100, 0x76);
    setPlayerSlotAnimationFlag(0, "}", 8, -0x100, 0x76);
    do {
        k = i;
        activateAnimationKeyframe(0, k, 0);
        setPlayerSlotEntryRGB(0, k, &bridgeWhiteColor);
        samplePlayerAnimChannel(0, k, 1.0f);
        i++;
    } while (i < 10);
}

typedef struct { u16 x; u16 y; } ApXy;
typedef struct {
    u8 pad0[8];
    u16 count;
    u16 padA;
    u16 *ids;
    ApXy *xy;
    u8 pad14[0x1B];
    u8 alpha;
} ApElem;
extern u8 apMs[] __asm__("gMissionState");
struct ui_element *getPlayerAnimChannelEntryByIds(s32);
struct ui_element *getPlayerAnimChannelEntryReversed(s32);
s32 findCharEntryAltValueByKey(s32, s32);
void activateAnimationKeyframe(s32, s32, u8);
struct ui_element *getPlayerSlotFieldAt34(u16, u16);
void setLookupEntryField5ByKey(struct some_ui_list_root *, struct ui_element *, u8);
f32 sinf(f32);
extern s32 D_menu_overlay_800CDFA4;
extern s32 D_menu_overlay_800CDAD0;
extern s32 D_menu_overlay_800CDCDC;
extern f32 D_menu_overlay_800CDB14;

#define AP_BLOCK(GET, K0, K1, K2, IDX)                                                       \
    { ApElem *p; ApElem *q; s32 first; s32 last; u8 a; u8 m; \
    e = (ApElem *)GET(D_menu_overlay_800CDFA4);                                              \
    first = e->xy[0].x;                                                                      \
    last = e->xy[e->count - 1].x;                                                            \
    q = (ApElem *)getPlayerSlotFieldAt34(0, K1); \
    x = first - 0x22; \
    y = last + 0x1C; \
    first -= 0x20; \
    q->xy->x = first; \
    q = (ApElem *)getPlayerSlotFieldAt34(0, K2); \
    q->xy->x = last + 0x1A; \
    last += 0x1A; \
    p = (ApElem *)getPlayerSlotFieldAt34(0, K0);                                             \
    m = apMs[IDX + 0xC]; \
    p->ids[0] = p->ids[1] = findCharEntryAltValueByKey(0, m ? (u8)(m + 1) : -1); \
    p->xy[0].x = x - 2;                                                                      \
    p->xy[1].x = y - 7;                                                                      \
    if (e->alpha < 0xFF) {                                                                   \
        a = (u32)(e->alpha * alpha);                                                         \
    } else {                                                                                 \
        a = (u32)(alpha * 254.0f);                                                           \
    }                                                                                        \
    activateAnimationKeyframe(0, K0, a);                                                     \
    setLookupEntryField5ByKey((struct some_ui_list_root *)D_menu_overlay_800CDCDC, (struct ui_element *)p, p->ids[0] != 0xFFFF); \
    activateAnimationKeyframe(0, K1, fa ? (u8)(u32)(a * (sinf(D_menu_overlay_800CDB14 / 9.0f) * 0.5f + 0.5f)) : 0); \
    activateAnimationKeyframe(0, K2, fb ? ({ f32 t = sinf(D_menu_overlay_800CDB14 / 9.0f) * 0.5f + 0.5f; (u8)(u32)(a * t); }) : 0); \
    }

void applyPlayerSlotAnimChannelKeyframe(u8 s0, s32 s1, f32 alpha) {
    ApElem *e;
    s32 x;
    s32 y;
    u8 fa;
    u8 fb;
    s32 v = s1;

    fa = s0 != 0;
    fb = (D_menu_overlay_800CDAD0 & (1 << (s0 + 1))) != 0;
    AP_BLOCK(getPlayerAnimChannelEntryByIds, 6, 4, 5, s0)
    AP_BLOCK(getPlayerAnimChannelEntryReversed, 9, 7, 8, (u8)v)
}

s32 anyAudioSlotActive();
s32 bufferArbiterProducerScanWait();
s32 destroyPlayerShipRecord(s32, s32 *);
s32 finalizeCurrentSpeechBuffer();
s32 shutdownFormatMessageWorker();
s32 tickMusyXIfActive();
extern s32 D_menu_overlay_800CDC80;
extern s32 D_menu_overlay_800CDCDC;

void drainAudioAndFinalizeSpeechBuffer(void) {
    tickMusyXIfActive();
    do {

    } while (!(anyAudioSlotActive() & 0xFF));
    bufferArbiterProducerScanWait();
    destroyPlayerShipRecord(D_menu_overlay_800CDCDC, &D_menu_overlay_800CDC80);
    shutdownFormatMessageWorker();
    finalizeCurrentSpeechBuffer();
}

s32 tickMultiPartVoiceLine(s32, f32);
extern s32 D_menu_overlay_800CDFB0;

void tickTimedScreenFadeFloat(f32 arg0) {
    if ((D_menu_overlay_800CDFB0 != 0) && ((tickMultiPartVoiceLine(D_menu_overlay_800CDFB0, arg0) & 0xFF) == 1)) {
        D_menu_overlay_800CDFB0 = 0;
    }
}

extern void queueAudioVoiceCmd(s32, s32, s32, s32);
extern void playSimpleAudioCmd(s32, s32, s32);
extern void setVoiceLineLoopFlag(s32);
extern void applyFlagsToMeshTreeOrList(s32, s32, s32, s32);
extern void releaseSceneObjectMeshTree(s32);
extern void beginSceneRenderFrame(s32);
extern void updateTextOverlayLookupEntry(s32, s32 *, f32);
extern s32 D_menu_overlay_800CDCE0;
typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x18];
} MenuScreenMeshSlot;

extern MenuScreenMeshSlot D_menu_overlay_800CDCF0[];

void playExitSoundAndToggleScreenMeshes(void) {
    queueAudioVoiceCmd(0, 400, D_menu_overlay_800CDCE0, 1);
    playSimpleAudioCmd(0, 400, 0xFE);
    if (D_menu_overlay_800CDFB0 != 0) {
        setVoiceLineLoopFlag(D_menu_overlay_800CDFB0);
    }
    applyFlagsToMeshTreeOrList(D_menu_overlay_800CDCF0[2].unk4, 0, 0x10000000, 0);
    applyFlagsToMeshTreeOrList(D_menu_overlay_800CDCF0[3].unk4, 0, 0x10000000, 0);
    releaseSceneObjectMeshTree(D_menu_overlay_800CDCF0[2].unk4);
    releaseSceneObjectMeshTree(D_menu_overlay_800CDCF0[3].unk4);
    beginSceneRenderFrame(1);
    updateTextOverlayLookupEntry(D_menu_overlay_800CDCDC, &D_menu_overlay_800CDC80, 24.0f);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/115E00", fake_func_800B2628);

static u32 D_menu_overlay_800A5C1C[] __attribute__((section(".rodata"))) = { 0xC4229840 };
