#include "common.h"
#include "common_types.h"

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", allocObjectPoolNode);

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", unlinkAndFreeChildNpcNode);

s32 clearObjectPoolStateFlag();
s32 resetCraftSubsystemGlobal();
s32 resetObjectPoolListHead();
extern s32 D_mission_overlay_8010C0D0;
extern s32 D_mission_overlay_8010C0D4;

void resetObjectContextPool(void) {
    D_mission_overlay_8010C0D0 = 0;
    D_mission_overlay_8010C0D4 = 0;
    D_mission_overlay_8010C0D0 = 0;
    resetCraftSubsystemGlobal();
    resetObjectPoolListHead();
    clearObjectPoolStateFlag();
}

s32 rs_free(s32);

void freeAllObjectContextPoolNodes(void) {
    s32 temp_a0;
    s32 temp_a0_2;

    if (D_mission_overlay_8010C0D0 != 0) {
        do {
            temp_a0 = D_mission_overlay_8010C0D0;
            D_mission_overlay_8010C0D0 = (*(s32 *)((u8 *)(temp_a0) + 0xC));
            rs_free(temp_a0);
        } while (D_mission_overlay_8010C0D0 != 0);
    }
    if (D_mission_overlay_8010C0D4 != 0) {
        do {
            temp_a0_2 = D_mission_overlay_8010C0D4;
            D_mission_overlay_8010C0D4 = (*(s32 *)((u8 *)(temp_a0_2) + 0xC));
            rs_free(temp_a0_2);
        } while (D_mission_overlay_8010C0D4 != 0);
    }
}

typedef struct {
    u8 pad0[0x110];
    s16 unk110;
    u8 unk112;
    u8 pad113[0x15];
    s32 unk128;
    u8 unk12C;
    u8 unk12D;
    u8 pad12E[2];
    s16 unk130;
    u8 pad132[2];
    u8 unk134;
    u8 unk135;
    u8 pad136[0x1A];
    s32 unk150;
    u8 pad154[0x28];
    s32 unk17C;
    u8 pad180[0x18];
    u16 unk198;
    s16 unk19A;
    s32 unk19C;
    s32 unk1A0;
    u8 unk1A4;
    u8 unk1A5;
    u8 unk1A6;
    u8 unk1A7;
    void *unk1A8;
    u8 data[1];
} PooledObject;
typedef struct {
    u8 pad0[0x10];
    PooledObject *obj;
    u8 pad14[2];
    u16 unk16;
} ObjectOwnerNpc;
void *allocObjectPoolNode(s32);
s16 allocateNpcSlot(void *);
s32 createAndInitObject(PooledObject **out, s32 extra, ObjectOwnerNpc *npc, void (*init)(void *, void *, void *), u8 *spawn) {
    PooledObject *obj = allocObjectPoolNode(extra + 0x1AC);

    if (obj != NULL) {
        *out = obj;
        obj->unk198 = npc->unk16;
        obj->unk1A4 = 0;
        obj->unk1A6 = 0;
        obj->unk1A5 = 0;
        obj->unk19A = 3;
        if (spawn == NULL) {
            obj->unk1A7 = 0;
        } else {
            obj->unk1A7 = 1;
            obj->unk19C = *(s32 *)(spawn + 0x14);
            obj->unk1A0 = *(s32 *)(spawn + 0x10);
        }
        obj->unk112 = 0;
        obj->unk110 = 0;
        obj->unk134 = 0;
        obj->unk135 = 0;
        obj->unk128 = 0;
        obj->unk12C = 6;
        obj->unk12D = 6;
        obj->unk130 = allocateNpcSlot(npc);
        obj->unk150 = 0;
        obj->unk17C = 0;
        npc->obj = obj;
        obj->unk1A8 = obj->data;
        if (init != NULL) {
            init(npc, obj->data, spawn);
        }
        return 1;
    }
    return 0;
}

s32 clearPendingChildNpc(s32);
s32 unlinkAndFreeChildNpcNode(s32);

s32 clearPendingAndDestroyChildNpc(s32 *arg0) {
    clearPendingChildNpc(*arg0);
    unlinkAndFreeChildNpcNode(*arg0);
    return 1;
}

s32 destroyNpcSlotByIndex(u16);

void destroyObjectOwnedNpcSlot(void *arg0) {
    if ((*(u8 *)((u8 *)(arg0) + 0x1A4)) != 0) {
        destroyNpcSlotByIndex((*(u16 *)((u8 *)(arg0) + 0x198)));
    }
}

INCLUDE_ASM("asm/nonmatchings/mission_overlay/0ECD10", fake_func_800EC6EC);
