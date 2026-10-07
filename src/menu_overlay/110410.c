#include "common.h"
#include "common_types.h"

#include "PR/ultratypes.h"
#include "game_settings.h"
#include "secondary_weapons.h"
#include "textures.h"

#include "main/1EE30.h"
#include "main/55AF0.h"
#include "main/562A0.h"
#include "main/64EA0.h"
#include "main/6C310.h"
#include "menu_overlay/110410.h"
#include "menu_overlay/12CA40.h"

// Interim Data externs
extern u8 hangarActiveSecondaryWeaponString;

// Interim BSS externs
extern char hangarSecondaryWeaponStrings[4][0x30];
extern u8  D_menu_overlay_800CD520[0x20];
extern u8  D_menu_overlay_800CD6D0;

typedef struct {
    s32 unk0;
    s32 *unk4;
    u8 pad8[0x38];
    u16 flags;
    u8 pad42[0x22F];
    u8 unk271;
    u8 pad272[6];
} CutAssetEnt;

extern CutAssetEnt *gCutAssetEnts __asm__("D_menu_overlay_800CDA5C");
extern s32 *gCutAssetHead __asm__("D_menu_overlay_800CD670");
u8 projectModelBoundsToScreen(void *, void *, void *, void *, s32, s32);

void loadCutsceneAssetsByIndex(u16 idx) {
    if ((gCutAssetEnts[idx].flags & 8) || projectModelBoundsToScreen(&gCutAssetHead, (u8 *)gCutAssetEnts[idx].unk4 + 0x28, (u8 *)*gCutAssetEnts[idx].unk4 + 0x5C, (u8 *)*gCutAssetEnts[idx].unk4 + 0x68, (gCutAssetEnts[idx].flags >> 4) & 1, gCutAssetEnts[idx].unk0)) {
        gCutAssetEnts[idx].unk4[3] = (s32)gCutAssetHead;
        if (gCutAssetHead) {
            *(s32 *)(gCutAssetEnts[idx].unk4[3] + 4) = (s32)(gCutAssetEnts[idx].unk4 + 3);
        }
        gCutAssetEnts[idx].unk4[4] = 0;
        gCutAssetHead = gCutAssetEnts[idx].unk4 + 3;
        gCutAssetEnts[idx].unk271 = 1;
    } else {
        gCutAssetEnts[idx].unk271 = 0;
    }
}

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", D_menu_overlay_800A5130);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEDread);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", D_menu_overlay_800A514C);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuECalamari);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEBacta);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEVolcano);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEChandrila);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEResearch);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuETaloraan);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEKessel);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEKile);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuECon);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEJade);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEKasan);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuECorellia);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEChorax);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuEBarkesh);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", strMenuETatooine);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", hangarInitialize);

extern f32 D_menu_overlay_800CD604;
extern f32 D_menu_overlay_800CD608;
extern s32 D_menu_overlay_800CD66C;
extern s32 D_menu_overlay_800CD6D4;
extern f32 D_menu_overlay_800CD6E0;
extern u8 D_menu_overlay_800CDA10;
extern u8 D_menu_overlay_800CDA11;
extern f32 D_menu_overlay_800CDA14;
extern s32 D_menu_overlay_800CDA18;
extern u16 D_menu_overlay_800CDA42;
extern u16 D_menu_overlay_800CDA4A;
extern u16 D_menu_overlay_800CDA4C;
extern u16 D_menu_overlay_800CDA54;
extern s32 D_menu_overlay_800CD668;
extern s32 D_menu_overlay_800CD6DC;
extern u8 hangarBaytoMap1Map[];
extern u8 hangarBaytoCraftNameMap[];
extern u8 hangarDesiredBay;
f32 advanceWrappingPhaseAccumulator(void);
void waitForPrevFrameDone(void);
void frameStartReset(void);
void advancePlayerAnimationPhase(s32, s32, f32);
void activateAnimationKeyframe(s32, s32, u8);
u8 tickMultiPartVoiceLine(s32, f32);
void tickWrappingTimerAccumulatorList(f32);
void hangarUpdateSecWeaponIfChanged(u8, u8, f32);
void updateHangarBayScene(u8);
void composeNpcOrientationMatrix(void);
void setupCameraMatrices(void *);
void initRenderStateArrays(void);
s32 rebuildActiveDisplayObjectListI(s32) __asm__("rebuildActiveDisplayObjectList");
void hangarTickCameraOrbit(void);
void drawFrameProfilerBars(void);
void submitGfxFrame(void);
u8 isPlayerShipActiveB(void) __asm__("isPlayerShipActive");
void playSimpleAudioCmd(s32, s32, s32);
void setVoiceLineLoopFlag(s32);
void updateTextOverlayLookupEntry(s32, void *, f32);
u8 accumulateShipThrottleCharge(s32, void *, f32);

s32 runHangarSelectionFrame(s32 arg0) {
    s32 i;
    f32 t;

    D_menu_overlay_800CD604 = advanceWrappingPhaseAccumulator();
    pollControllerInputs();
    setNewAndPreviousButtonsPressed();
    D_menu_overlay_800CD608 += D_menu_overlay_800CD604 * 30.0f;
    waitForPrevFrameDone();
    frameStartReset();
    advancePlayerAnimationPhase(D_menu_overlay_800CD66C, D_menu_overlay_800CD6DC, D_menu_overlay_800CD604);
    activateAnimationKeyframe(0, 0, (u32)(*(f32 *)&D_menu_overlay_800CD6DC * 255.0f));
    activateAnimationKeyframe(2, 0, (u32)(D_menu_overlay_800CD6E0 * *(f32 *)&D_menu_overlay_800CD6DC * 255.0f));
    if (D_menu_overlay_800CDA18 != 0 && tickMultiPartVoiceLine(D_menu_overlay_800CDA18, D_menu_overlay_800CD604) == 1) {
        D_menu_overlay_800CDA18 = 0;
        if (hangarBaytoMap1Map[hangarDesiredBay] != D_menu_overlay_800CDA11) {
            t = 3.0f;
            if (D_menu_overlay_800CDA10 != 0) {
                t = 5.0f;
            }
            D_menu_overlay_800CDA14 = t;
            D_menu_overlay_800CDA10 = 0;
        }
    }
    tickWrappingTimerAccumulatorList(D_menu_overlay_800CD604);
    hangarUpdateSecWeaponIfChanged((u8)arg0, hangarBaytoCraftNameMap[hangarDesiredBay], D_menu_overlay_800CD604);
    updateHangarBayScene((u8)arg0);
    ((s32 *)&gCutAssetHead)[0] = 0;
    ((s32 *)&gCutAssetHead)[2] = 0;
    composeNpcOrientationMatrix();
    loadCutsceneAssetsByIndex(D_menu_overlay_800CDA4A);
    loadCutsceneAssetsByIndex(D_menu_overlay_800CDA4C);
    if (D_menu_overlay_800CDA42 == 0x30) {
        loadCutsceneAssetsByIndex(D_menu_overlay_800CDA54);
    }
    for (i = 0; i < D_menu_overlay_800CDA42; i++) {
        if ((*(s32 *)&gCutAssetEnts[i].flags & 0x08040000) == 0x40000) {
            loadCutsceneAssetsByIndex(i);
        }
    }
    setupCameraMatrices(&gCutAssetHead);
    initRenderStateArrays();
    ((s32 *)&gCutAssetHead)[0] = 0;
    ((s32 *)&gCutAssetHead)[2] = rebuildActiveDisplayObjectListI(D_menu_overlay_800CD668);
    hangarTickCameraOrbit();
    for (i = 0; i < D_menu_overlay_800CDA42; i++) {
        if ((*(s32 *)&gCutAssetEnts[i].flags & 0x08060000) == 0x20000) {
            loadCutsceneAssetsByIndex(i);
        }
    }
    setupCameraMatrices(&gCutAssetHead);
    drawFrameProfilerBars();
    submitGfxFrame();
    if ((getControllerNewButtonsPressed(D_menu_overlay_800CD6D0) & 0x4000) && !isPlayerShipActiveB()) {
        playSimpleAudioCmd(0, 0x190, 0xFD);
        playSimpleAudioCmd(0, 0x190, 0xFE);
        D_menu_overlay_800CD6D4 = 0xFFFFFE;
        if (D_menu_overlay_800CDA18 != 0) {
            setVoiceLineLoopFlag(D_menu_overlay_800CDA18);
        }
        updateTextOverlayLookupEntry(D_menu_overlay_800CD668, &gCutAssetHead, 24.0f);
    }
    if (accumulateShipThrottleCharge(D_menu_overlay_800CD668, &gCutAssetHead, D_menu_overlay_800CD604)) {
        return D_menu_overlay_800CD6D4;
    }
    return 0xFFFFFF;
}

typedef struct { f32 x, y, z; } HV3;
typedef struct {
    s32 unk0;
    u8 **unk4;
    u8 pad8[4];
    HV3 pos;
    f32 rx, ry, rz;
    u8 pad24[0x1C];
    u16 flags;
    u8 pad42[6];
    s32 link[2];
    u8 pad50[0x14];
    u8 mtx[0x8C];
    u8 rest[0x188];
} HEnt;
extern u8 D_menu_overlay_800CC518[];
extern f32 D_menu_overlay_800CDA20[];
extern HV3 D_menu_overlay_800CC52C[];
extern u16 D_menu_overlay_800CDA42;
extern u8 hangarMap1ToCraftIdMap[];
extern u8 hangarTieInterceptorAvailable;
extern u8 hangarNabooStarfighterAvailable;
void initVec4TripletFromArgs(void *, f32, f32, f32);
void composeRotationMatrixSlot0(void *, f32);
void composeRotationMatrixSlot1(void *, f32);
void composeRotationMatrixSlot2(void *, f32);
void addVec3At0x24(void *, f32, f32, f32);
void setByteAcrossEntryList(u8 *, u8);
u8 transformVec3ToNpcLocalWithScale(void *, s32, HV3 *, f32, void *);

void composeNpcOrientationMatrix(void) {
    HV3 pos;
    s32 buf[2];
    u8 i;
    u8 idx;
    s32 *p;
    u8 *m;
    f32 sx, sz, sc;
    s32 *head;
    u8 c;
    HEnt *ent;
    s32 **hp;

    for (i = 0; i < 8; i++) {
        idx = D_menu_overlay_800CC518[i];
        ent = &((HEnt *)gCutAssetEnts)[idx];
        pos = ent->pos;
        p = ent->link;
        if (D_menu_overlay_800CDA20[i] != pos.y) {
            setByteAcrossEntryList((u8 *)&((HEnt *)gCutAssetEnts)[idx] + 0xF0, (u32)((pos.y - 26.0f) / 3.3500004f * 128.0f + 130.0f));
            D_menu_overlay_800CDA20[i] = pos.y;
        }
        m = (u8 *)p + 0x1C;
        sx = D_menu_overlay_800CC52C[i].x;
        sz = D_menu_overlay_800CC52C[i].z;
        pos.y = 29.35f;
        initVec4TripletFromArgs(m, sx, 1.0f, sz);
        composeRotationMatrixSlot2(m, -((HEnt *)gCutAssetEnts)[idx].rz);
        composeRotationMatrixSlot1(m, ((HEnt *)gCutAssetEnts)[idx].ry + 180.0f);
        addVec3At0x24(m, pos.x, pos.y, pos.z);
        if (transformVec3ToNpcLocalWithScale(&gCutAssetHead, 0, &pos, sx > sz ? sx : sz, buf)) {
            c = hangarMap1ToCraftIdMap[idx];
            if (c == 6 && !hangarTieInterceptorAvailable) {
                continue;
            }
            if (c == 8 && !hangarNabooStarfighterAvailable) {
                continue;
            }
            head = gCutAssetHead;
            p[0] = (s32)head;
            if (head) {
                head[1] = (s32)p;
            }
            p[1] = 0;
            gCutAssetHead = p;
        }
    }
    for (i = 0; i < D_menu_overlay_800CDA42; i++) {
        HEnt *e;
        u8 *q;
        u8 *m2;
                u16 fl;
        if (((HEnt *)gCutAssetEnts)[i].flags & 0xC0) {
            pos = ((HEnt *)gCutAssetEnts)[i].pos;
            e = (HEnt *)(i * sizeof(HEnt) + (s32)gCutAssetEnts);
            q = *e->unk4;
            __asm__ volatile("abs.s %0, %1" : "=f"(sx) : "f"(*(f32 *)(q + 0x68) - *(f32 *)(q + 0x5C)));
            __asm__ volatile("abs.s %0, %1" : "=f"(sz) : "f"(*(f32 *)(q + 0x70) - *(f32 *)(q + 0x64)));
            fl = e->flags;
            p = e->link;
            if (fl & 0x100) {
                sx *= 2.5f;
                sz *= 2.5f;
            }
            m2 = e->mtx;
            if (fl & 0x1000) {
                sx *= 0.35f;
                sz *= 0.35f;
            }
            initVec4TripletFromArgs(m2, sx, 1.0f, sz);
            composeRotationMatrixSlot0(m2, ((HEnt *)gCutAssetEnts)[i].rx);
            composeRotationMatrixSlot1(m2, ((HEnt *)gCutAssetEnts)[i].ry);
            composeRotationMatrixSlot2(m2, ((HEnt *)gCutAssetEnts)[i].rz);
            addVec3At0x24(m2, pos.x, 29.35f, pos.z);
            if (projectModelBoundsToScreen(&gCutAssetHead, m2, *((HEnt *)gCutAssetEnts)[i].unk4 + 0x5C, *((HEnt *)gCutAssetEnts)[i].unk4 + 0x68, 0, 0)) {
                head = gCutAssetHead;
                e->link[0] = (s32)head;
                if (head) {
                    head[1] = (s32)p;
                }
                p[1] = 0;
                gCutAssetHead = p;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", updateHangarBayScene);

typedef struct { f32 x, y, z; } OV3;
typedef struct {
    s32 unk0;
    u8 *mesh;
    u8 *unk8;
    OV3 pos;
    f32 rx, ry, rz;
    OV3 delta;
    OV3 prev;
    f32 scale;
    u16 flags;
    u8 pad42[0x1CA];
    s32 tex;
    u8 anim[0xC];
    f32 t;
    f32 dur;
    f32 f224;
    u8 snd[8];
    s32 sndActive;
    u8 pad234[0x38];
    u16 sndId;
    u16 dir;
    u8 pad270[3];
    u8 b273;
    u8 pad274[4];
} OEnt;
extern u16 D_menu_overlay_800CDA48;
extern u16 D_menu_overlay_800CDA52;
extern u16 D_menu_overlay_800CDA56;
extern u8 D_menu_overlay_800CD6E4;
extern f32 D_menu_overlay_800CC3E8;
extern u8 D_menu_overlay_800CC3EC[];
extern f32 D_menu_overlay_800CD70C;
f32 sinf(f32);
void setupActorAnchorTransformType1(void *, void *, void *, void *, f32);
void buildPositionAndCallTransformHelper(void *, void *, void *, void *, f32, f32, f32);
void updateAnimatedTextureStreaming(s32, void *, f32);
s32 mostlyMusyxFlagGatedHelper(void *);
void safeLookup3DSoundEntry(s32, u16);
void updateActive3DAudioSource(void *, void *, void *, u8);

static __inline__ void orbVec3Sub(f32 *d, f32 *a, f32 *b) {
    d[0] = a[0] - b[0];
    d[1] = a[1] - b[1];
    d[2] = a[2] - b[2];
}

#define EI(i) (*(OEnt *)((i) * sizeof(OEnt) + (s32)gCutAssetEnts))

void hangarTickCameraOrbit(void) {
    u32 i;
    OEnt *e;
    f32 amp;
    f32 t;
    f32 d;
    f32 dur;
    f32 x;
    f32 lim;
    OEnt *ed;
    OEnt *e3;
    u16 fl;
    OEnt *ea;
    OEnt *eb;
    OEnt *ec;
    OEnt *e2;

    for (i = 0; i < D_menu_overlay_800CDA42; i++) {
        e = &EI(i);
        if (e->flags & 2) {
            continue;
        }
        e->prev = e->pos;
        initVec4TripletFromArgs(EI(i).mesh + 0x28, EI(i).scale, EI(i).scale, EI(i).scale);
        e = &EI(i);
        dur = e->dur;
        if (0.0f < dur) {
            if (!(e->flags & 1)) {
                t = e->t;
                e->t = t + D_menu_overlay_800CD604;
                amp = t / dur;
                if (1.0f <= amp) {
                    e->t = e->t - e->dur;
                    amp = e->t / e->dur;
                    setupActorAnchorTransformType1(e->anim, e->unk8 + 0x10, &e->pos, &e->rx, amp);
                }
#define EB (*(OEnt *)((s32)gCutAssetEnts + i * sizeof(OEnt)))
                buildPositionAndCallTransformHelper(EB.anim, EB.unk8 + 0x10, &EB.pos, &EB.rx, EB.f224, EB.scale, amp);
            } else {
                if (i == D_menu_overlay_800CD6E4) {
                    amp = D_menu_overlay_800CC3E8;
                } else {
                    amp = 0.5f;
                }
                if (EI(i).flags & 0x400) {
                    composeRotationMatrixSlot2(EI(i).mesh + 0x28, amp * sinf(D_menu_overlay_800CD608 / 9.0f));
                    amp = amp * sinf(D_menu_overlay_800CD608 / 11.0f);
                    composeRotationMatrixSlot0(EI(i).mesh + 0x28, amp);
                }
            }
            composeRotationMatrixSlot2(EI(i).mesh + 0x28, EI(i).rz);
            composeRotationMatrixSlot0(EI(i).mesh + 0x28, EI(i).rx);
            composeRotationMatrixSlot1(EI(i).mesh + 0x28, EI(i).ry);
        } else {
            if (i == D_menu_overlay_800CDA48) {
                e2 = e;
                x = e2->pos.x;
                if (e2->dir != 0) {
                    d = -D_menu_overlay_800CD604;
                } else {
                    d = D_menu_overlay_800CD604;
                }
                { s32 t; do { e2->pos.x = x + (d + d); t = (s32)gCutAssetEnts; } while (0); lim = -14.0f; ed = (OEnt *)(i * sizeof(OEnt) + t); }
                if ((ed->pos.x < lim && ed->dir != 0) || (14.0f < ed->pos.x && ed->dir == 0)) {
                    EI(i).dir = ~EI(i).dir;
                }
            } else if (i == D_menu_overlay_800CDA4A || i == D_menu_overlay_800CDA4C) {
                e->pos.x = e->pos.x - D_menu_overlay_800CD604 / 1.2717f;
                lim = -50.0f;
                if (e->pos.x < lim) {
                    e->pos.x = 50.0f;
                }
            }
            composeRotationMatrixSlot0(EI(i).mesh + 0x28, EI(i).rx);
            composeRotationMatrixSlot1(EI(i).mesh + 0x28, EI(i).ry);
            composeRotationMatrixSlot2(EI(i).mesh + 0x28, EI(i).rz);
        }
        addVec3At0x24(EI(i).mesh + 0x28, EI(i).pos.x, EI(i).pos.y, EI(i).pos.z);
        ea = &EI(i);
        fl = ea->flags;
        if (fl & 1) {
            if (fl & 0x200) {
                e3 = ea;
                updateAnimatedTextureStreaming(e3->tex, D_menu_overlay_800CC3EC, i == D_menu_overlay_800CD6E4 ? D_menu_overlay_800CD70C : 3.0f);
            }
            eb = &EI(i);
            if (eb->sndActive) {
                safeLookup3DSoundEntry(mostlyMusyxFlagGatedHelper(eb->snd), EI(i).sndId);
                ec = &EI(i);
                orbVec3Sub(&ec->delta.x, &ec->pos.x, &ec->prev.x);
                updateActive3DAudioSource(ec->snd, &ec->pos, &ec->delta, ec->b273);
            }
        }
        if (i == D_menu_overlay_800CDA52 && !hangarTieInterceptorAvailable) {
            continue;
        }
        if (i == D_menu_overlay_800CDA56 && !hangarNabooStarfighterAvailable) {
            continue;
        }
        if (!(EI(i).flags & 0x800)) {
            loadCutsceneAssetsByIndex(i);
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/110410", D_menu_overlay_800A5804);

#include "common_types.h"
extern u16 D_main_bss_8013A528[];
extern u8 hangarShipShadowFaces[];
extern void clearStructPair2C30(u8 *);
extern void zmemcpy(u8 *, u8 *, u32);

void hangarInitializeShipShadowHob(u8 *p, s32 id, u8 *arg2)
{
  s32 j;
  u16 sid;
  s32 v;
  u8 *q;
  u8 *face;
  s32 *new_var;
  s32 i;
  f32 *vtx;
  u8 *new_var2;
  *((s32 *) (p + 0x58)) = 0x02860021;
  sid = id;
  *((s32 *) (p + 0x60)) = 9;
  *((u8 **) (p + 0x6C)) = p + 0xA8;
  *((s32 *) (p + 0xC)) = 0;
  *((s32 *) (p + 0x8)) = 0;
  *((s32 *) (p + 0x4)) = 0;
  *((s32 *) (p + 0x0)) = 0;
  *((u8 **) (p + 0x10)) = p + 0x4C;
  *((s32 *) (p + 0x14)) = 0;
  new_var = (s32 *) (p + 0x50);
  *new_var = 0;
  *((s32 *) (p + 0x4C)) = 0;
  *((s32 *) (p + 0x54)) = 0;
  *((s32 *) (p + 0x68)) = 0;
  *((s32 *) (p + 0x5C)) = 0;
  new_var2 = p;
  *((s32 *) (p + 0x64)) = 0;
  *((u8 **) (p + 0x70)) = new_var2 + 0xB8;
  *((s32 *) (p + 0x74)) = 0;
  clearStructPair2C30(p + 0x4C);
  *((s32 *) (p + 0xAC)) = 0;
  *((s32 *) (p + 0xA8)) = 0;
  *((u8 **) (p + 0xB0)) = p + 0x124;
  *((s32 *) (p + 0xB4)) = 4;
  zmemcpy(p + 0x124, hangarShipShadowFaces, 0xA0);
  v = sid << 16;
  *((s32 *) (p + 0x1A4)) = v;
  *((s32 *) (p + 0x17C)) = v;
  *((s32 *) (p + 0x154)) = v;
  *((s32 *) (p + 0x12C)) = v;
  if ((sid == D_main_bss_8013A528[5]) || (sid == D_main_bss_8013A528[12]))
  {
    *((u16 *) (p + 0x1B4)) = 0x800;
    *((u16 *) (p + 0x1B0)) = 0x800;
    *((u16 *) (p + 0x194)) = 0x800;
    *((u16 *) (p + 0x190)) = 0x800;
    *((u16 *) (p + 0x164)) = 0x800;
    *((u16 *) (p + 0x160)) = 0x800;
    *((u16 *) (p + 0x144)) = 0x800;
    *((u16 *) (p + 0x140)) = 0x800;
    *((u16 *) (p + 0x1BC)) = 0x1000;
    *((u16 *) (p + 0x1B8)) = 0x1000;
    *((u16 *) (p + 0x16C)) = 0x1000;
    *((u16 *) (p + 0x168)) = 0x1000;
  }
  face = p + 0x124;
  for (i = 0; i < 2; i++)
  {
    for (j = 0; j < 2; j++)
    {
      face[0x24] = 0;
      face[0x25] = 0;
      face[0x26] = 0;
      face[0x27] = arg2[3];
      face += 0x28;
    }

 do { } while (0);
  }

  vtx = *((f32 **) (p + 0x70));
  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      vtx[0] = ((f32) (j - 1)) * 0.5f;
      vtx[1] = 0;
      vtx[2] = ((f32) (i - 1)) * 0.5f;
      vtx += 3;
    }

  }

}

extern u8 D_menu_overlay_800CDA08[];
extern u8 hangarCameraState;
extern s32 D_menu_overlay_800CC4F8[];
s32 mallocVoiceLineStruct(s32, f32, s32);

void craftSelectionVoiceLineHelper(void) {
    u8 idx;

    if (getControllerNewButtonsPressed(D_menu_overlay_800CD6D0) & 0xF) {
        { u8 m = hangarBaytoMap1Map[hangarDesiredBay];
        D_menu_overlay_800CDA08[m - 1] = 0;
        if (D_menu_overlay_800CDA18 == 0) {
            D_menu_overlay_800CDA14 = 5.0f;
        } else if (m != D_menu_overlay_800CDA11) {
            setVoiceLineLoopFlag(D_menu_overlay_800CDA18);
            D_menu_overlay_800CDA10 = 1;
        } }
    }
    if (hangarCameraState < 5) {
        D_menu_overlay_800CDA14 += D_menu_overlay_800CD604;
        if (5.0f < D_menu_overlay_800CDA14 && D_menu_overlay_800CDA14 < 6.0f) {
            idx = hangarBaytoMap1Map[hangarDesiredBay];
            if (D_menu_overlay_800CDA18 == 0 && D_menu_overlay_800CDA08[idx - 1] == 0) {
                D_menu_overlay_800CDA18 = mallocVoiceLineStruct(D_menu_overlay_800CC4F8[idx - 1], 0.7f, 0x78);
                D_menu_overlay_800CDA08[idx - 1] = 1;
                D_menu_overlay_800CDA14 = 6.0f;
                D_menu_overlay_800CDA11 = idx;
            }
        }
    }
}

s32 lerpVec3(s32 *, s32 *, s32, f32);
f32 quadraticEaseInOut(f32);
extern f32 D_menu_overlay_800CD704;
extern f32 D_menu_overlay_800CD708;
extern s32 D_menu_overlay_800CD800;
extern s32 D_menu_overlay_800CD810;
extern s32 D_menu_overlay_800CDA60;
extern s32 D_menu_overlay_800CDA70;

s32 tickEasedCameraKeyframeBlend(s32 arg0, s32 arg1, f32 arg2) {
    f32 temp_fv0;
    f32 temp_fv0_2;
    s32 var_v0;

    if (D_menu_overlay_800CD708 < 1.0f) {
        temp_fv0 = D_menu_overlay_800CD708 + (arg2 / 7.5f);
        D_menu_overlay_800CD708 = temp_fv0;
        if (temp_fv0 > 1.0f) {
            D_menu_overlay_800CD708 = 1.0f;
        }
    }
    if (D_menu_overlay_800CD704 < 1.0f) {
        temp_fv0_2 = D_menu_overlay_800CD704 + (arg2 / 5.0f);
        D_menu_overlay_800CD704 = temp_fv0_2;
        if (temp_fv0_2 >= 1.0f) {
            D_menu_overlay_800CD704 = 1.0f;
        }
    }
    lerpVec3(&D_menu_overlay_800CD810, &D_menu_overlay_800CDA60, arg0, quadraticEaseInOut(D_menu_overlay_800CD708));
    lerpVec3(&D_menu_overlay_800CD800, &D_menu_overlay_800CDA70, arg1, quadraticEaseInOut(D_menu_overlay_800CD704));
    var_v0 = 0;
    if ((D_menu_overlay_800CD704 >= 1.0f) && (D_menu_overlay_800CD708 >= 1.0f)) {
        var_v0 = 1;
    }
    return var_v0;
}

extern char D_menu_overlay_800A514C[];
char *hangarGenerateSecondaryWeaponString(enum Level level, enum PlayerCraft craft) {
    u16 bridgeSecondaryWeaponTextIds[10] = {
        0x0000, 0x004E, 0x0050, 0x0051, 0x0052, 0x0053, 0x004F, 0x0054, 0x0055, 0x0056
    };
    u8 isAdvanced;
    char *temp_s3;
    char *var_s1_2;
    u8 temp_s0;
    u8 temp_s2;
    u8 why;

    isAdvanced = 0;
    temp_s2 = hangarActiveSecondaryWeaponString;
    temp_s0 = getSecondaryWeaponForLevelAndCraft(level, craft, D_menu_overlay_800CD6D0);
    if (temp_s0 != SECONDARY_WEAPON_NONE) {
        why = temp_s0 - 2;
        if ((why < 2U) && (ADVANCED_MISSILES_UNLOCKED)) isAdvanced = 1;
        if ((temp_s0 == SECONDARY_WEAPON_BOMBS) && (ADVANCED_BOMBS_UNLOCKED)) isAdvanced = 1;
        if ((temp_s0 == SECONDARY_WEAPON_PROTON_TORPEDOS) && (ADVANCED_TORPEDOS_UNLOCKED)) isAdvanced = 1;
        temp_s0 = bridgeSecondaryWeaponTextIds[temp_s0];
        temp_s3 = getGameOrFrontText(0x49);
        if (isAdvanced) {
            var_s1_2 = getGameOrFrontText(0x4B);
        } else {
            var_s1_2 = D_menu_overlay_800A514C;
        }
        sprintf(hangarSecondaryWeaponStrings[temp_s2], "%s%s%s", temp_s3, var_s1_2, getGameOrFrontText(temp_s0));
    } else {
        sprintf(hangarSecondaryWeaponStrings[temp_s2], "%s%s", getGameOrFrontText(0x49), getGameOrFrontText(0x57));
    }
    hangarActiveSecondaryWeaponString++;
    hangarActiveSecondaryWeaponString &= 3; // the really ought to be %= 4, but that leads to a ton of intruction reordering
    return hangarSecondaryWeaponStrings[temp_s2];
}
__asm__(".section .rodata\n.byte 0x04,0x18,0x80,0x00,0x62,0x18,0x21,0x00,0x03,0x21,0x00,0x00,0x82,0x20,0x21\n.section .text");

void tickMusyXIfActive(void);
u8 anyAudioSlotActive(void);
void bufferArbiterProducerScanWait(void);
void destroyPlayerShipRecord(s32, void *);
s32 finalizeCurrentSpeechBuffer();
extern s32 D_menu_overlay_800CD668;
extern u8 D_menu_overlay_800CD670[];
void gracefulMenuShutdown(void) {
    s32 i;

    tickMusyXIfActive();
    while (!anyAudioSlotActive()) {
    }
    bufferArbiterProducerScanWait();
    destroyPlayerShipRecord(D_menu_overlay_800CD668, D_menu_overlay_800CD670);
    for (i = 7; i >= 0; i--) {
    }
    finalizeCurrentSpeechBuffer();
}

void extractTextBeforeFmtChar(char *s) {
    s32 i = 0;
    register u8 c asm("$5");
    if (s[1] != 0 && s[1] != 0x23) {
        s++;
        while (1) {
            c = s[i];
            if (c == 0x2A) break;
            D_menu_overlay_800CD520[i] = c;
            i++;
            if (s[i] == 0 || s[i] == 0x23) break;
        }
    }
    i += (s32)D_menu_overlay_800CD520;
    *(u8 *)i = 0;
}

typedef struct {
    u8 pad[0x4C];
    u32 flags;
    f32 pos[3];
    f32 scale[3];
    f32 quat[4];
    f32 offs[3];
} NodeXform;
void clearVec4QuadStruct(void *);
void addVec3At0x24(void *, f32, f32, f32);
void applyScaleToMat3x4(void *, f32, f32, f32);
void composeQuatToMat3x4(void *, void *);
void composeRotationMatrixSlot2(void *, f32);

void composeInterpolatedNodeMatrices(u8 *arg0, u8 *arg1, NodeXform *arg2, NodeXform *arg3, f32 arg4) {
    s32 i;
    u16 j;
    u8 *dst;
    NodeXform *s;
    f32 ang;
    s32 fl;

    if (arg0 != NULL) {
        if (arg1 != NULL) {
            for (i = 0; (u16)i < 2; i++) {
                dst = arg1 + 0x1C;
                if ((u16)i == 0) {
                    dst = arg0 + 0x1C;
                }
                j = i & 0xFFFF;
                s = arg3;
                if (j == 0) {
                    s = arg2;
                }
                clearVec4QuadStruct(dst);
                if (s->flags & 1) {
                    addVec3At0x24(dst, -s->pos[0], -s->pos[1], -s->pos[2]);
                }
                if (s->flags & 2) {
                    applyScaleToMat3x4(dst, s->scale[0], s->scale[1], s->scale[2]);
                }
                if (s->flags & 4) {
                    composeQuatToMat3x4(dst, s->quat);
                }
                ang = arg4;
                if (j != 0) {
                    ang = -ang;
                }
                composeRotationMatrixSlot2(dst, ang);
                fl = s->flags;
                if ((fl & 9) == 9) {
                    addVec3At0x24(dst, s->offs[0] + s->pos[0], s->offs[1] + s->pos[1], s->offs[2] + s->pos[2]);
                } else if ((fl & 9) == 8) {
                    addVec3At0x24(dst, s->offs[0], s->offs[1], s->offs[2]);
                } else if (fl & 1) {
                    addVec3At0x24(dst, s->pos[0], s->pos[1], s->pos[2]);
                }
            }
        }
    }
}

extern char D_menu_overlay_800A5804[];
void hangarLoadShadows(void) {
    struct material_entry sp10;
    struct full_image_header *temp_s4;
    struct full_image_header *var_s1;
    s32 var_s2;
    s32 var_v1;

    temp_s4 = load_asset(D_menu_overlay_800A5804);
    for (var_s2 = 0; var_s2 < 14; var_s2++) {
        var_s1 = temp_s4;
        for (var_v1 = 0; var_v1 < var_s2; var_v1++) {
            var_s1 = (struct full_image_header *)(((u32)var_s1 + var_s1->image_size + 7) & ~3);
        }
        full_header_image_offset_convert(&var_s1->ent, (u32)&var_s1->ent);
        var_s1->ent.flags_type |= 0x2000;
        sp10.material_type = 1;
        D_main_bss_8013A528[var_s2] = registerHmtTextureInTable(&sp10, &var_s1->ent, 1U);
    }
    rs_free(temp_s4);
}

typedef struct {
    u8 pad[0x27];
    u8 b;
} SetByteEntry;
void setByteAcrossEntryList(u8 *arg0, u8 arg1) {
    u32 i;
    SetByteEntry *e = *(SetByteEntry **)(arg0 + 8);

    for (i = 0; i < *(u32 *)(arg0 + 0xC); i++) {
        e->b = arg1;
        e++;
    }
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} CraftSelectVec3;
void initCraftSelectVectors(CraftSelectVec3 *arg0, CraftSelectVec3 *arg1) {
    D_menu_overlay_800CD704 = 0.0f;
    D_menu_overlay_800CD708 = 0.0f;
    *(CraftSelectVec3 *)&D_menu_overlay_800CDA60 = *arg0;
    *(CraftSelectVec3 *)&D_menu_overlay_800CDA70 = *arg1;
}

s32 setPlayerSlotEntryRGB(s32, s32, s32 *);
s32 startPlayerSlotAnimationChannelExt(s32, s8 *, s32, s32, s32, s32);
extern s32 D_menu_overlay_800CDA7C;
extern s8 D_menu_overlay_800CDA80;
extern s32 hangarWhiteColor;

void hangarSetSecondaryWeaponDisplay(s32 arg0, s8 arg1) {
    D_menu_overlay_800CDA7C = startPlayerSlotAnimationChannelExt(2, hangarGenerateSecondaryWeaponString(arg0 & 0xFF, arg1 & 0xFF), 0x10, 1, -0x100, 0x97);
    setPlayerSlotEntryRGB(2, 1, &hangarWhiteColor);
    setPlayerSlotEntryRGB(2, 2, &hangarWhiteColor);
    D_menu_overlay_800CDA80 = arg1;
}

void startPlayerSlotAnimationChannel(s32, char *);
void advancePlayerAnimationPhase(s32, s32, f32);
extern s32 D_menu_overlay_800CD6DC;
void hangarUpdateSecWeaponIfChanged(u8 arg0, u8 arg1, f32 arg2) {
    if (arg1 != (u8)D_menu_overlay_800CDA80) {
        startPlayerSlotAnimationChannel(D_menu_overlay_800CDA7C, hangarGenerateSecondaryWeaponString(arg0, arg1));
        D_menu_overlay_800CDA80 = arg1;
    }
    advancePlayerAnimationPhase(D_menu_overlay_800CDA7C, D_menu_overlay_800CD6DC, arg2);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/110410", fake_func_800AEC54);
