#include "common.h"

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B9600", D_mission_overlay_800A5C20);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0B9600", D_mission_overlay_800A5C28);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B9600", playerVwingInit);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B9600", updateVwingEngineEffect);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B9600", orientVwingSubmodelByQuat);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0B9600", tickVwingEngineAudio);

#include "common_types.h"
typedef struct {
    u8 pad0[0x2A0];
} VwSlot;

extern VwSlot D_main_bss_80137DBC[];
typedef struct {
    u8 p0[4];
    u8 *ptr;
    u8 p8[0x144 - 8];
} Row144;

typedef struct {
    u8 p0[2];
    u16 f2;
    u8 p4[0x18];
    u16 f1C;
} Tail;

extern Row144 D_main_bss_80138D18[];
extern Tail D_main_bss_80139560;
extern s32 D_main_bss_80130B58;
extern s32 D_mission_overlay_8010CA1C;
extern u8 D_mission_overlay_8010996C[];
extern u8 attached3DSoundEmitterNpcHandler[];
extern u8 attachedMeshOverlayNpcHandler[];

extern s32 rs_malloc(s32, s32);
extern void rs_free(s32);
extern s32 walkMeshdef0List(char *);
extern void loadPlayerStartPosition(void *, void *);
extern void playerVwingInit(s32 *, s32, s32);
extern s32 refreshPlayerSecondaryWeaponHud(s32);
extern void allocateCraftAnimationStateForSlot(void *, s32, void *);
extern void popNpcSlotFromTail(u16, void *);
extern s32 allocateAndInitCraftNpcContext(f32, f32, s32);
extern void spawnNpcOfType(void *, void *, s32, s32);
extern void resetTransientPlayerStateFlags(void);
extern void resetCraftAnimationStateForSlot(s32);
extern void cancelSceneQueueHandle(void *);
extern void destroySceneNpcsAndUnlink(void *);
extern void releaseMeshAsset(s32);
extern void teardownHudInstancesAndUnbindNpcs(void);
extern void freePlayerAuxBuffersIfActive(s32);
extern void updateVwingEngineEffect(s32 *, s32);
extern void tickVwingEngineAudio(s32 *, s32);
extern void tryPlaySpatialSoundWithGates(void *, void *);
extern void destroyNpcSlotByIndex(u16);
extern void enqueueMeshTypeForCleanup(s32);
extern void initVec4TripletFromArgs(void *, f32, f32, f32);
extern void mat3x4Multiply(s32, void *, s32);
extern void addNpcToVisibilityBucket(s32, s32, void *, f32);
extern void advanceNpcOnCurvedPath(s32, s32, void *, s32);
extern void updatePlayerHudFrame(s32, void *, void *);

s32 playerVwingUpdate(u8 *npc, s32 msg, u8 *ctx) {
    u16 sp10[2];
    f32 sp18[12];
    s32 *s0;
    u8 *s1;
    s32 flag;
    s32 a2;
    f32 fa0;
    f32 fa1;
    s32 *mem;
    u8 *c1;
    u8 *p4;

    s0 = *(s32 **)(npc + 4);
    if ((msg & 0xFFFF) == 2 || !(D_mission_overlay_8010CA1C & 4)) {
        switch ((u16)msg) {
        case 1:
            c1 = ctx;
            s0 = (s32 *)rs_malloc(0x30, 0);
            *(s32 **)(npc + 4) = s0;
            s1 = (u8 *)&D_main_bss_80137DBC[(s32)*(f32 *)ctx];
            *(s32 *)s1 = walkMeshdef0List("vwing");
            *(u16 *)(s1 + 0xB6) = *(u16 *)(npc + 0x16);
            *(s32 *)(npc + 0xC) = *(s32 *)s1;
            *(u8 **)(npc + 8) = s1 + 4;
            if (*(f32 *)ctx >= 0.0f) {
                *(u16 *)((u8 *)&D_main_bss_80137DBC[(s32)*(f32 *)ctx] - 2) = *(u16 *)(npc + 0x16);
                *(s32 *)(s1 + 0xB8) = (s32)*(f32 *)ctx;
                flag = 1;
            } else {
                flag = 0;
            }
            loadPlayerStartPosition(s1, 0);
            playerVwingInit(s0, (s32)*(f32 *)c1, flag);
            *(s32 *)(s1 + 0x178) = refreshPlayerSecondaryWeaponHud(0) & 0xFF;
            allocateCraftAnimationStateForSlot(s1, 0, D_mission_overlay_8010996C);
            popNpcSlotFromTail(D_main_bss_80139560.f2, npc);
            popNpcSlotFromTail(D_main_bss_80139560.f1C, npc);
            if (D_main_bss_80130B58 & 2) {
                a2 = allocateAndInitCraftNpcContext(0.13f, 0.26f, 0xB);
            } else {
                a2 = allocateAndInitCraftNpcContext(0.2f, 0.15f, 1);
            }
            *(s32 *)(s1 + 0xBC) = a2;
            sp10[0] = *(u16 *)(npc + 0x16);
            sp10[1] = *(u16 *)(s1 + 0xB4);
            spawnNpcOfType(attached3DSoundEmitterNpcHandler, sp10, 1, 0x64);
            spawnNpcOfType(attachedMeshOverlayNpcHandler, npc + 0x16, 1, 0x64);
            return 1;
        case 12:
            s1 = (u8 *)&D_main_bss_80137DBC[*s0];
            *(f32 *)(s1 + 0x184) = 2.0f;
            *(u16 *)(s1 + 0x180) = (*(u16 *)(s1 + 0x180) & 0xFFDF) | 0x40;
            loadPlayerStartPosition(s1, s1 + 4);
            playerVwingInit(s0, *(s32 *)(s1 + 0xB8), 0x40);
            resetTransientPlayerStateFlags();
            resetCraftAnimationStateForSlot(0);
            return 1;
        case 2:
            s1 = (u8 *)&D_main_bss_80137DBC[*s0];
            cancelSceneQueueHandle(s1);
            destroySceneNpcsAndUnlink(s1);
            rs_free(*(s32 *)(s1 + 0xBC));
            releaseMeshAsset(*(s32 *)s1);
            teardownHudInstancesAndUnbindNpcs();
            freePlayerAuxBuffersIfActive(0);
            return 1;
        case 3:
            updateVwingEngineEffect(s0, *(s32 *)ctx);
            tickVwingEngineAudio(s0, *(s32 *)ctx);
            return 1;
        case 5:
            tryPlaySpatialSoundWithGates(&D_main_bss_80137DBC[*s0], ctx);
            if (*(u16 *)ctx != 0xFFFF) {
                destroyNpcSlotByIndex(*(u16 *)ctx);
            }
            return 1;
        case 4:
            s1 = (u8 *)&D_main_bss_80137DBC[*s0];
            enqueueMeshTypeForCleanup(*(s32 *)s1);
            if (!(*(u16 *)(s1 + 0x180) & 0x100)) {
                if (*(u16 *)(D_main_bss_80138D18[*(s32 *)(s1 + 0xB8)].ptr + 4) != 3) {
                    if (D_main_bss_80130B58 & 2) {
                        initVec4TripletFromArgs(sp18, 1.4f, 1.4f, 1.4f);
                        mat3x4Multiply(*(s32 *)s1 + 0x28, sp18, *(s32 *)s1 + 0x28);
                    }
                    p4 = s1 + 4;
                    addNpcToVisibilityBucket(*(s32 *)ctx, *(s32 *)s1, p4, 1.0f);
                    if (!(*(u16 *)(s1 + 0x180) & 0x80)) {
                        advanceNpcOnCurvedPath(*(s32 *)(ctx + 8), *(s32 *)ctx, p4, *(s32 *)(s1 + 0xBC));
                    }
                }
                updatePlayerHudFrame(0, ctx, s1 + 4);
            }
            return 1;
        }
    }
    return 1;
}
