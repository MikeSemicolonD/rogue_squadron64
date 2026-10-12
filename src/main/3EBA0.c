#include "common.h"

#include "main/3EBA0.h"

typedef struct {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 pad3[0xD];
    u32 f10;
    u8 pad14[4];
    u32 f18;
} MgSettings;
typedef struct {
    u8 b0;
    u8 pad1[3];
    u8 b4;
    u8 pad5[0x1A];
    u8 b1F;
    u8 b20;
    u8 b21;
    u8 b22;
    u8 pad23[2];
    u8 b25;
} MgState;
typedef struct { u8 b0, b1, b2, b3; } MgCraft;
extern MgSettings mgGs __asm__("gGameSettings");
extern MgState mgMs __asm__("gMissionState");
extern u8 mgBoot[] __asm__("gBootConfig");
extern MgCraft mgCraft[] __asm__("dDefaultCraftForLevel");
extern s32 D_main_bss_80138920;
extern u8 D_main_bss_80130B88[];
extern u8 D_main_bss_80130B1C[];
extern u16 D_main_bss_80137D00;
extern u16 D_main_bss_8013805C;
extern u8 D_main_bss_80137CE0;
extern s32 D_main_bss_80137CFC;
void setProfilerBarGate(s32);
void bindControllerStatusBuffer(s32, void *);
void initAllPlayerSlots(void);
void setRngSeed(s32);
void loadOverlay(s32);
void runIdleFramesAndLoadSaveData(void);
void menuOverlayInit(void *, s32, s32);
u8 isViModeTypePal(void);
u8 isUnlockBitSet(s32);
void setUnlockBitAndPersist(s32);
void cinematicLoopBody(s32, s32, s32);
void cycleIdleDemoId(void);
void applyLevelScreenAndCameraSettings(void);
void runVideoFrameTick(void *, void *, void *);
s32 findManifestEntryByName(char *);
void func_mission_overlay_800FA250(void);
void func_800FA6A4(void);
void endMissionCleanup(void);
void freeManifestSegmentAssets(s32);
void func_800BF358(void);
void func_800BF3A4(void);
void syncMissionUnlockBitsToSettings(void);
void initializeNumLives(void);
void dispatchCinematicFromMainLoop(void *, s32);
void mainGameLoop(s32 *arg0) {
    u8 i;
    u8 lives;
    u32 sh;
    s32 md;
    u32 f;
    u8 *boot;
    MgSettings *gs;
    MgState *ms;
    s32 m20;
    s32 ma;
    MgCraft *c;
    u8 *cin;
    s32 x, y;

    D_main_bss_80138920 = *arg0;
    setProfilerBarGate(0);
    bindControllerStatusBuffer(1, D_main_bss_80130B88);
    initAllPlayerSlots();
    setRngSeed(1);
    loadOverlay(1);
    runIdleFramesAndLoadSaveData();
    {
        s32 f0 = mgGs.f10;
        D_main_bss_80137D00 = f0 & 1;
        D_main_bss_8013805C = f0 & 1;
    }
    for (;;) {
        ms = &mgMs;
        gs = &mgGs;
        boot = mgBoot + 0x10;
        m20 = ~0x20;
        {
            u32 t = gs->f10 & m20;
            s32 m200 = ~0x200;
            gs->f10 = t & m200 & ~0x400;
            gs->f18 = gs->f18 & m20;
        }
        loadOverlay(1);
        if (ms->b20 != 0) {
            menuOverlayInit(gs, 9, 0);
            if (isViModeTypePal() != 0 && isUnlockBitSet(5) == 0) {
                loadOverlay(1);
                menuOverlayInit(gs, 2, 0xB);
                setUnlockBitAndPersist(5);
            }
        }
        if (ms->b21 == 0 && ms->b4 != 5 && ms->b4 != 3) {
            loadOverlay(2);
            cinematicLoopBody(0x13, 2, 0);
        }
menu:
        sh = (ms->b22 != 0) * 4;
        loadOverlay(1);
        md = 1;
        if (ms->b21 != md) {
            md = 2;
        }
        menuOverlayInit(gs, md, sh);
        f = gs->f10;
        D_main_bss_8013805C = D_main_bss_80137D00 = f & 1;
        if (f & 0x400) {
            ma = ~0x800;
            gs->f10 = f & ma;
            loadOverlay(2);
            for (i = 0; i < 0x10; i++) {
                gs->b1 = mgCraft[i].b3;
                cinematicLoopBody(i, 0, 0);
                if (gs->f10 & 0x800) {
                    break;
                }
                gs->b1 = mgCraft[i].b3;
                cinematicLoopBody(i, 1, 0);
                if (gs->f10 & 0x800) {
                    break;
                }
            }
            mgGs.b0 = 0;
            ms->b21 = 0;
            {
                u32 t1 = gs->f10 & ~0x800;
                gs->f10 = t1 & ~0x400;
            }
            goto menu;
        }
        goto chk;
caseD:
        loadOverlay(1);
        menuOverlayInit(&mgGs, 3, 2);
        continue;
demoRet:
        ma = ~0x800;
        gs->f10 = f & ma & m20;
        ms->b21 = 0;
        cycleIdleDemoId();
        goto menu;
chk:
        if (gs->f18 & 0x2000000) {
            gs->f18 &= ~0x2000000;
            loadOverlay(0);
            gs->b1 = 0;
            mgGs.b0 = 0x14;
            gs->b2 = 0;
            {
                s32 one = 1;
                mgMs.b0 = one;
            }
            applyLevelScreenAndCameraSettings();
            runVideoFrameTick(boot, boot + 0x1C, boot + 0xC);
            D_main_bss_80137CFC = findManifestEntryByName("data");
            func_mission_overlay_800FA250();
            func_800FA6A4();
            endMissionCleanup();
            freeManifestSegmentAssets(D_main_bss_80137CFC);
            ms->b21 = 0;
            mgGs.b0 = 0;
            goto menu;
        }
        D_main_bss_80137CE0 = 1;
        for (;;) {
            if (!(gs->f10 & 0x100)) {
                loadOverlay(2);
                cinematicLoopBody(mgGs.b0, 0, 0);
                f = gs->f10;
                if ((f & 0x820) == 0x820) {
                    goto demoRet;
                }
            }
            loadOverlay(0);
            func_800BF358();
            applyLevelScreenAndCameraSettings();
            runVideoFrameTick(boot, boot + 0x1C, boot + 0xC);
            D_main_bss_80137CFC = findManifestEntryByName("data");
            func_mission_overlay_800FA250();
            func_800FA6A4();
            endMissionCleanup();
            freeManifestSegmentAssets(D_main_bss_80137CFC);
            if (ms->b4 != 4 && ms->b4 != 5 && ms->b4 != 1) {
                syncMissionUnlockBitsToSettings();
            }
            switch (ms->b4) {
            case 1:
                loadOverlay(2);
                cinematicLoopBody(mgGs.b0, 1, 0);
                lives = ms->b1F;
                initializeNumLives();
                {
                    s32 n = mgGs.b0 + 1;
                    s32 x = ms->b1F;
                    if (x < n) {
                        x = n;
                    }
                    ms->b1F = x;
                }
                loadOverlay(1);
                menuOverlayInit(gs, 3, 0);
                if (mgGs.b0 < 0x10) {
                    if ((mgGs.b0 == 0xF && lives < 0x10) || ms->b25 != 0) {
                        loadOverlay(2);
                        cin = D_main_bss_80130B1C;
                        x = y + (s32)cin;
                        y = x;
                        dispatchCinematicFromMainLoop(cin, 0);
                        loadOverlay(1);
                        menuOverlayInit(&mgGs, 8, 0);
                        ms->b22 = 1;
                        ms->b21 = 0;
                        ms->b4 = 3;
                    } else {
                        mgGs.b0 = mgGs.b0 + 1;
                    }
                }
                goto top;
            case 2:
                D_main_bss_80137CE0 = 0;
                if ((s8)--mgMs.b0 > 0) {
                    loadOverlay(1);
                    menuOverlayInit(&mgGs, 3, 1);
                    continue;
                }
                goto over;
            case 0:
                if ((s8)--mgMs.b0 > 0) {
                    goto caseD;
                }
            case 3:
            over:
                ms->b21 = 0;
                ms->b4 = 3;
                loadOverlay(1);
                menuOverlayInit(&mgGs, 3, 3);
                ms->b22 = 1;
                goto top;
            case 4:
            case 5:
                func_800BF3A4();
                ms->b21 = 0;
                cycleIdleDemoId();
                goto top;
            }
        }
top:;
    }
}

INCLUDE_ASM("asm/nonmatchings/main/3EBA0", fake_func_8003E55C);
