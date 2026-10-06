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

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", slotEffectHandlerDispatch);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", cutscenePopulateSlotsFromLevelLists);

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

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", initSceneForMission);

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

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", updatePositionalAudioSource);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A54A8);

INCLUDE_RODATA("asm/nonmatchings/cinematic_overlay/1381D0", D_cinematic_overlay_800A54B4);

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", applyCutsceneSlotMaterialOverrides);

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

INCLUDE_ASM("asm/nonmatchings/cinematic_overlay/1381D0", fake_func_800AF6A8);
