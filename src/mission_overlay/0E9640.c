#include "common.h"
#include "common_types.h"

f32 fabsf(f32);
s32 rand(void);
typedef struct { f32 x, y, z; } RdVec3;
typedef struct {
    RdVec3 pos;
    RdVec3 v0C;
    RdVec3 v18;
    u8 pad24[0xC];
    s32 meshPart;
    u8 pad34[4];
    u8 *def;
    s16 phase;
    u8 pad3E[2];
    f32 radius;
    f32 speed;
} RdObj;
extern void transformLimbStrideAnchorsLocal(u16, RdVec3 *, s32);
extern void transformMeshPartIntoWorld(s32, RdVec3 *);
extern void spawnByteAnimDebrisDefault(void *);
extern void spawnNpcType0xAFromTemplate(void *, f32);
extern void composeRandomRotationMatrix(RdVec3 *, RdVec3 *, f32, s32, s32, s32);
extern void scaleVec3ByRandomRange(RdVec3 *, f32, f32);
extern void spawnDebris1Npc(RdVec3 *, RdVec3 *, f32, f32, f32);
extern void spawnSplineWalkerCraft(void *, f32, f32, s32);
extern void gameStateByteGatedNpcHelper(s32, RdVec3 *, s32, f32, f32, f32);

void runDestructionPhaseSequence(RdObj *obj) {
    RdVec3 v[4];
    RdVec3 limb;
    RdVec3 mesh;
    RdVec3 pos;
    RdVec3 dir;
    f32 a;
    f32 b;
    f32 c;
    s32 i;
    s32 n;

    transformLimbStrideAnchorsLocal(*(u16 *)(obj->def + 0x198), &limb, 0);
    transformMeshPartIntoWorld(obj->meshPart, &mesh);
    switch (obj->phase) {
    case 0:
        spawnByteAnimDebrisDefault(obj);
        spawnNpcType0xAFromTemplate(obj, obj->radius * 1.2f);
        n = (s16)((s16)rand() % 3) + 5;
        for (i = 0; i < n; i++) {
            composeRandomRotationMatrix(&pos, &dir, obj->radius * 0.25f, 0x46, 0, 0);
            pos.x += obj->pos.x;
            pos.y += obj->pos.y;
            pos.z += obj->pos.z;
            scaleVec3ByRandomRange(&dir, 1.0f, 2.0f);
            __asm__ volatile("abs.s %0, %1" : "=f"(a) : "f"(((f32)(rand() & 0x7F) - 64.0f) / 12.8f)); a += 12.0f;
            __asm__ volatile("abs.s %0, %1" : "=f"(b) : "f"(((f32)(rand() & 0x7F) - 64.0f) / 213.33333f)); b += 0.6f;
            __asm__ volatile("abs.s %0, %1" : "=f"(c) : "f"(((f32)(rand() & 0x7F) - 64.0f) / 320.0f)); c += 0.2f; spawnDebris1Npc(&pos, &dir, a, b, c);
        }
        spawnSplineWalkerCraft(obj, obj->speed, obj->speed * 1.5f, 0xC);
        break;
    case 1:
        v[2] = obj->v18;
        v[1] = obj->v0C;
        v[3] = limb;
        v[0] = mesh;
        gameStateByteGatedNpcHelper(2, v, 0, 0.8f, 1.2f, 0.6f);
        spawnNpcType0xAFromTemplate(obj, obj->radius * 5.0f);
        spawnByteAnimDebrisDefault(obj);
        for (i = 0; i < 15; i++) {
            composeRandomRotationMatrix(&pos, &dir, obj->radius * 0.25f, 0x32, 0, 0);
            pos.x += obj->pos.x;
            pos.y += obj->pos.y;
            pos.z += obj->pos.z;
            scaleVec3ByRandomRange(&dir, 1.5f, 4.0f);
            __asm__ volatile("abs.s %0, %1" : "=f"(a) : "f"(((f32)(rand() & 0x7F) - 64.0f) / 12.8f)); a += 12.0f;
            __asm__ volatile("abs.s %0, %1" : "=f"(b) : "f"(((f32)(rand() & 0x7F) - 64.0f) / 25.6f)); b += 2.5f;
            __asm__ volatile("abs.s %0, %1" : "=f"(c) : "f"(((f32)(rand() & 0x7F) - 64.0f) / 320.0f)); c += 0.2f; spawnDebris1Npc(&pos, &dir, a, b, c);
        }
        spawnSplineWalkerCraft(obj, obj->speed * 6.0f, obj->speed * 10.0f, 0xC);
        break;
    case 2:
        spawnNpcType0xAFromTemplate(obj, obj->radius * 3.0f);
        break;
    case 3:
        spawnNpcType0xAFromTemplate(obj, obj->radius * 3.0f);
        break;
    case 4:
        spawnNpcType0xAFromTemplate(obj, obj->radius * 3.0f);
        break;
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E9640", tickCraftWithPhasedDestruction);

extern void setNpcHealth(s32, void *, void *);
extern void setObjectDetailLevel(s32, s32);

void initNpcHealthAndDetailFromChild(void *arg0) {
    u8 *npc = *(u8 **)((u8 *)arg0 + 4);
    u8 *def = *(u8 **)(npc + 0x34);

    *(s16 *)(npc + 0x3E) = 0;
    *(f32 *)(npc + 0x50) = *(f32 *)(def + 0x94);
    setNpcHealth(*(s32 *)(npc + 0x38), *(u8 **)(npc + 0x34) + 0x6C, *(u8 **)(npc + 0x34));
    setObjectDetailLevel(*(s32 *)(npc + 0x38), *(s32 *)(*(u8 **)(npc + 0x34) + 0xAC));
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0E9640", fake_func_800E9AD8);

INCLUDE_RODATA("asm/nonmatchings/mission_overlay/0E9640", D_mission_overlay_800A86C8);
