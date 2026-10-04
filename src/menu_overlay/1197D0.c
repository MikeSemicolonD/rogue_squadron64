#include "common.h"
#include "common_types.h"

#include "compiler/gcc/string.h"

#include "main/08120.h"
#include "menu_overlay/1197D0.h"

/*
BSS, for when matching it is possible
char D_menu_overlay_800CE6B0[0x40];
nonmatching D_menu_overlay_800CE6F0, 0x2
nonmatching D_menu_overlay_800CE6F2, 0x2
nonmatching D_menu_overlay_800CE6F4, 0xC
*/

// Interim BSS externs
extern char D_menu_overlay_800CE6B0[0x40];

/* Data Variables, uncomment when Data matching is possible
u8  D_menu_overlay_800CC850 = 0;
s32 D_menu_overlay_800CC85C = 0;
*/

// Interim `extern` definitions for Data variables. Remove these when Data matching is possible.
extern u8  D_menu_overlay_800CC850;
extern s32 D_menu_overlay_800CC85C;

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5C20);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5C2C);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5C34);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", buildFormatMessageGlyphBuffer);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5C40);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", allocFormatTextElement);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", loadNamedTextureDescriptor);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", strMenuAlpha);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5C58);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", strMenuP);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5C7C);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", allocTextRenderTarget);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", tickFormatMessageWorker);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5CB4);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", strMenuGRAD1);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5CD8);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", strMenuGRAD2);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", strMenuGRAD1A);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5D04);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", strMenuGRAD2A);

INCLUDE_RODATA("asm/nonmatchings/menu_overlay/1197D0", D_menu_overlay_800A5D40);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", buildLevelSelectTextTextures);

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", buildScaledFormatTextElement);

s32 buildFormatMessageGlyphBuffer(void *, void *, s32, s32);
s32 rasterizeFormatMessageGlyphs(void *, void *, u16);
void disposeFormatMsgQueueMember(void *arg0, void *arg1);

void processAndDisposeFormatMessage(u8 *arg0, s32 arg1, s32 arg2) {
    u8 buf[0x78];

    buildFormatMessageGlyphBuffer(arg0, buf, arg1, arg2);
    rasterizeFormatMessageGlyphs(arg0, buf, *(u16 *)(arg0 + 0xA));
    disposeFormatMsgQueueMember(arg0, buf);
}

void decrementTextTextureRefcount(void) {
    D_menu_overlay_800CC850--;
}

void setChildPosFromI16Pair(void *arg0, s16 arg1, s16 arg2) {
    (*(f32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0xC))) + 0x18)) = (f32) arg1;
    (*(f32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0xC))) + 0x1C)) = (f32) arg2;
}

s32 getStructField0xC(void *arg0) {
    return (*(s32 *)((u8 *)(arg0) + 0xC));
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", rasterizeFormatMessageGlyphs);

s32 freeJfifDecodeState(s32);
s32 rs_free(s32);

void disposeFormatMsgQueueMember(void *arg0, void *arg1) {
    if ((*(s32 *)((u8 *)(arg0) + 0x1C)) & 6) {
        rs_free((*(s32 *)((u8 *)(arg1) + 0x3C)));
        freeJfifDecodeState((*(s32 *)((u8 *)(arg1) + 0x70)));
    }
    rs_free((*(s32 *)((u8 *)(arg1) + 0x38)));
    freeJfifDecodeState((*(s32 *)((u8 *)(arg1) + 0x6C)));
}

extern s32 D_menu_overlay_800CC858;
s32 registerServiceWorker(s32, s32, s32, s32 *);
s32 startServiceWorker(s32);
extern s32 D_menu_overlay_800CC854;
extern s32 tickFormatMessageWorker;

void initFormatMessageWorker(s32 arg0) {
    s32 temp_v0;

    D_menu_overlay_800CC854 = 1;
    temp_v0 = registerServiceWorker(8, 0x800, arg0 & 0xFF, &tickFormatMessageWorker);
    D_menu_overlay_800CC858 = temp_v0;
    startServiceWorker(temp_v0);
}

s32 unregisterServiceWorker(s32);
extern s32 D_menu_overlay_800CC858;

void shutdownFormatMessageWorker(void) {
    unregisterServiceWorker(D_menu_overlay_800CC858);
}

extern s32 D_main_bss_80138920;
extern s32 D_menu_overlay_800CC854;
extern s32 D_menu_overlay_800CC858;
s32 sendServiceMessage(s32, s32, void *, s32);

typedef struct {
    u8 pad0[0x14];
    s32 f14;
    u8 text[0x40];
    s32 f58;
    s32 f5C;
} FormatMsg;

u8 enqueueFormatMessage(s32 arg0, u8 *arg1) {
    FormatMsg *msg;

    msg = rs_malloc(0x60, 0);
    rs_memset((u8 *)msg, 0, 0x60);
    msg->f14 = arg0;
    msg->f58 = D_main_bss_80138920;
    msg->f5C = D_menu_overlay_800CC854;
    rs_strcpy(msg->text, arg1);
    sendServiceMessage(D_main_bss_80138920, D_menu_overlay_800CC858, msg, 0);
    D_menu_overlay_800CC854 += 1;
    return msg->text[0x47];
}

void *tryRecvServiceMessage(s32);
extern s32 D_main_bss_80138920;

s32 pollServiceMessageByte(u8 *arg0) {
    void *temp_v0;

    temp_v0 = tryRecvServiceMessage(D_main_bss_80138920);
    if (temp_v0 != NULL) {
        *arg0 = (*(u8 *)((u8 *)(temp_v0) + 0x17));
    }
    return temp_v0 != NULL;
}

s32 allocTextRenderTarget(s32, s32);
extern s32 D_menu_overlay_800CC864;

void initTextTextureTarget(void) {
    D_menu_overlay_800CC864 = allocTextRenderTarget(0x40, 0x10);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", updateTextOverlayLookupEntry);

extern f32 D_menu_overlay_800CE6F4;
extern u8 D_menu_overlay_800CC860;

s32 accumulateShipThrottleCharge(s32 arg0, s32 arg1, f32 dt) {
    f32 charge;

    if (D_menu_overlay_800CC85C != 0) {
        charge = D_menu_overlay_800CE6F4 * dt + (*(u8 **)((u8 *)D_menu_overlay_800CC85C + 0xC))[0x2F];
        if (charge > 255.0f) {
            (*(u8 **)((u8 *)D_menu_overlay_800CC85C + 0xC))[0x2F] = 0xFF;
            if (++D_menu_overlay_800CC860 >= 7) {
                return 1;
            }
        } else {
            (*(u8 **)((u8 *)D_menu_overlay_800CC85C + 0xC))[0x2F] = charge;
        }
    }
    return 0;
}

f32 computeThrottleChargeFraction(void) {
    f32 var_ft0;

    var_ft0 = 1.0f;
    if (D_menu_overlay_800CC85C != 0) {
        var_ft0 = 1.0f - ((f32) (*(u8 *)((u8 *)((*(void **)((u8 *)(D_menu_overlay_800CC85C) + 0xC))) + 0x2F)) / 255.0f);
    }
    return var_ft0;
}

s32 isPlayerShipActive(void) {
    return D_menu_overlay_800CC85C != 0;
}

void removeLookupTableEntry(s32, s32);
void requestViFeatureChange(s32);
extern u8 gBootConfig[];

void destroyPlayerShipRecord(s32 arg0) {
    if (D_menu_overlay_800CC85C != 0) {
        removeLookupTableEntry(arg0, *(s32 *)((u8 *)D_menu_overlay_800CC85C + 0xC));
        D_menu_overlay_800CC85C = 0;
        D_menu_overlay_800CC850--;
        if (!(*(s32 *)(gBootConfig + 0x44) & 0x80)) {
            requestViFeatureChange(8);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", spawnProjectileObject);

typedef struct {
    u8 pad0[8];
    u32 count;
    u8 *morph;
    u8 pad10[4];
    u16 *verts;
} MorphMesh;

void copyMorphTargetVertices(MorphMesh *arg0, MorphMesh *arg1, u16 base) {
    u32 i;



    for (i = 0; i < arg0->count; i++) {
        (*(u16 **)(arg0->morph + 0xC))[i] = arg0->verts[i] = arg1->verts[i + base];
    }
}

#if 0
// Text matching, have not check if rodata works yet
// Appends "alplha" to the end of arg0, placing the combined result in D_menu_overlay_800CE6B0
char *buildPrefixedAssetName(char *arg0) {
    s32 temp_s3;
    char *temp_v0;
    u32 var_s1;

    temp_v0 = "alpha";
    rs_strcpy(D_menu_overlay_800CE6B0, arg0);
    temp_s3 = strlen(D_menu_overlay_800CE6B0);
    for (var_s1 = 0; var_s1 < strlen(temp_v0) + 1; var_s1++) {
        D_menu_overlay_800CE6B0[temp_s3 + var_s1] = temp_v0[var_s1];
    }
    return D_menu_overlay_800CE6B0;
}
#else
extern char strMenuAlpha[];

char *buildPrefixedAssetName(char *arg0) {
    char *alpha;
    s32 len;
    u32 i;

    alpha = strMenuAlpha;
    rs_strcpy(D_menu_overlay_800CE6B0, arg0);
    len = strlen(D_menu_overlay_800CE6B0);
    for (i = 0; i < strlen(alpha) + 1; i++) {
        D_menu_overlay_800CE6B0[len + i] = alpha[i];
    }
    return D_menu_overlay_800CE6B0;
}
#endif

typedef struct {
    u8 pad[4];
    u16 w;
    u16 h;
} HudMeshBounds;

typedef struct {
    u8 pad[0xC];
    s32 unkC;
    HudMeshBounds *bounds;
    u8 pad14[0xC];
    u8 unk20[1];
} HudMeshRef;

void spawnHudReticleAtMeshBounds(s32 arg0, HudMeshRef *arg1, s32 arg2, u8 arg3) {
    HudMeshBounds *b = arg1->bounds;
    s32 c = arg1->unkC;

    createHudSpritePair(arg0, arg1->unk20, c, b->w, b->h, arg2, arg3);
}

void layoutHudSpriteScreenRect(s32 a, s32 b, s32 c, f32 d);
void positionHudSpriteOffset(s32 a, s32 b, s32 c, f32 d) {
    layoutHudSpriteScreenRect(a, b, c + 0x20, d);
}

s32 insertLookupEntry(s32, u8 *, s32);
u8 *rs_malloc(s32, s32);
extern s32 D_menu_overlay_800CE6F0;
extern s32 D_menu_overlay_800CE6F2;

void createHudSpritePair(s32 arg0, void *arg1, s32 arg2, s16 arg3, s32 arg4, f32 arg5, u8 arg6) {
    s32 temp_s3;
    u8 *temp_v0;
    u8 *temp_v0_2;

    temp_v0 = rs_malloc(0x30, 0);
    (*(u8 **)((u8 *)(arg1) + 0)) = temp_v0;
    temp_v0_2 = rs_malloc(0x30, 0);
    (*(u8 **)((u8 *)(arg1) + 4)) = temp_v0_2;
    rs_memset(temp_v0, 0U, 0x30U);
    rs_memset(temp_v0_2, 0U, 0x30U);
    (*(s32 *)((u8 *)(arg1) + 8)) = arg2;
    (*(s16 *)((u8 *)(arg1) + 0x10)) = arg3;
    temp_s3 = arg6 & 0xFF;
    (*(f32 *)((u8 *)(arg1) + 0xC)) = arg5;
    (*(s16 *)((u8 *)(arg1) + 0x12)) = (s16) arg4;
    (*(s32 **)((u8 *)(temp_v0) + 0xC)) = &D_menu_overlay_800CE6F0;
    (*(s32 **)((u8 *)(temp_v0_2) + 0xC)) = &D_menu_overlay_800CE6F2;
    (*(s16 *)((u8 *)(temp_v0_2) + 0xA)) = 1;
    (*(s16 *)((u8 *)(temp_v0_2) + 8)) = 1;
    (*(s16 *)((u8 *)(temp_v0) + 0xA)) = 1;
    (*(s16 *)((u8 *)(temp_v0) + 8)) = 1;
    (*(s32 *)((u8 *)(temp_v0_2) + 0x14)) = 0x23;
    (*(s32 *)((u8 *)(temp_v0) + 0x14)) = 0x23;
    insertLookupEntry(arg0, temp_v0, temp_s3);
    insertLookupEntry(arg0, temp_v0_2, temp_s3);
}

typedef struct HudElemF {
    u8 pad0[0x18];
    f32 f18;
    f32 f1C;
    u8 pad20[4];
    f32 f24;
    f32 f28;
    u8 pad2C[3];
    u8 b2F;
} HudElemF;

typedef struct HudRectDesc {
    HudElemF *e0;
    HudElemF *e1;
    HudElemF *e2;
    f32 scale;
    u16 w;
    u16 h;
} HudRectDesc;

extern u32 getLookupEntryField5(s32, HudElemF *);
extern void setLookupEntryField5ByKey(s32, HudElemF *, s32);

void layoutHudSpriteScreenRect(s32 a, s32 b, s32 cc, f32 off) {
    HudRectDesc *c = (HudRectDesc *)cc;
    HudElemF *s0 = c->e0;
    HudElemF *s1 = c->e1;
    HudElemF *a1 = c->e2;
    s32 v;

    s0->f24 = ((f32)c->w + c->scale) * 0.015625f;
    s0->f28 = c->scale * 0.125f * 1.25f;
    s1->f24 = c->scale * 0.125f;
    s1->f28 = ((f32)c->h + c->scale * 0.0f * 0.5f) * 0.015625f;
    s0->f24 = s0->f24 * a1->f24;
    s1->f24 = s1->f24 * a1->f24;
    s0->f28 = s0->f28 * a1->f28;
    s1->f28 = s1->f28 * a1->f28;
    s0->f18 = a1->f18 + off;
    s0->f1C = a1->f1C + off + (f32)c->h * a1->f28;
    s1->f18 = a1->f18 + off + (f32)c->w * a1->f24;
    s1->f1C = a1->f1C + off;
    v = (s0->b2F = s1->b2F = a1->b2F) ? getLookupEntryField5(a, a1) : 0;
    setLookupEntryField5ByKey(b, s0, v & 0xFF);
    setLookupEntryField5ByKey(b, s1, v & 0xFF);
}

INCLUDE_ASM("asm/nonmatchings/menu_overlay/1197D0", fake_func_800B47C4);

static u32 D_menu_overlay_800A5DC4[] __attribute__((section(".rodata"))) = { 0x4602003E, 0, 0x45000003 };
